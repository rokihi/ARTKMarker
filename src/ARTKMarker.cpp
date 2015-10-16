// -*- C++ -*-
/*!
 * @file  ARTKMarker.cpp
 * @brief ARToolKit Marker Detector (4x4 2D BarCode)
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "ARTKMarker.h"

#include "ImageUtil.h"
#include <coil/Mutex.h>

// Module specification
// <rtc-template block="module_spec">
static const char* artkmarker_spec[] =
  {
    "implementation_id", "ARTKMarker",
    "type_name",         "ARTKMarker",
    "description",       "ARToolKit Marker Detector (4x4 2D BarCode)",
    "version",           "1.0.0",
    "vendor",            "SugarSweetRobotics",
    "category",          "ImageProcessing",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.debug", "0",
    "conf.default.cameraParamFile", "camera_para_isight640x480.dat",
    "conf.default.markerWidth", "80",
    "conf.default.imageWidth", "640",
    "conf.default.imageHeight", "480",

    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.cameraParamFile", "text",
    "conf.__widget__.markerWidth", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ARTKMarker::ARTKMarker(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_imageIn("image", m_image),
    m_markerInfoOut("markerInfo", m_markerInfo)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ARTKMarker::~ARTKMarker()
{
}



RTC::ReturnCode_t ARTKMarker::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("image", m_imageIn);
  
  // Set OutPort buffer
  addOutPort("markerInfo", m_markerInfoOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("debug", m_debug, "0");
  bindParameter("markerWidth", m_markerWidth, "0.4");
  bindParameter("cameraParamFile", m_cameraParamFile, "Data/camera.param");
  bindParameter("imageWidth", m_imageWidth, "1280");
  bindParameter("imageHeight", m_imageHeight, "960");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ARTKMarker::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarker::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarker::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ARTKMarker::onActivated(RTC::UniqueId ec_id)
{
	if (arParamClear(&m_cameraParam, m_imageWidth, m_imageHeight, AR_DIST_FUNCTION_VERSION_DEFAULT) < 0) {
		std::cout << "[RTC::ARMarkerDetector] Error Initializing parameter data " << std::endl;
		return RTC::RTC_ERROR;
	}
	
	// Load the camera parameters, resize for the window and init.
	if (arParamLoad(m_cameraParamFile.c_str(), 1, &m_cameraParam) < 0) {
		std::cout << "[RTC::ARMarkerDetector] Error loading parameter file " << m_cameraParamFile << std::endl;
		return RTC::RTC_ERROR;
	}
	
	if (m_cameraParam.xsize != m_imageWidth || m_cameraParam.ysize != m_imageHeight) {
		std::cout << "[RTC::ARMarkerDetector] Camera Parameter resized from " << m_cameraParam.xsize << ", " << m_cameraParam.ysize << std::endl;
		arParamChangeSize(&m_cameraParam, m_imageWidth, m_imageHeight, &m_cameraParam);
	}

	if ((m_pCameraParamLT = arParamLTCreate(&m_cameraParam, AR_PARAM_LT_DEFAULT_OFFSET)) == NULL) {
		std::cout << "[RTC::ARMarkerDetector] Error: arParamLTCreate." << std::endl;
		return RTC::RTC_ERROR;
	}

	if ((m_pARHandle = arCreateHandle(m_pCameraParamLT)) == NULL) {
		std::cout << "[RTC::ARMarkerDetector] Error: arCreateHandle" << std::endl;
		return RTC::RTC_ERROR;
	}

	if ((m_pAR3DHandle = ar3DCreateHandle(&m_cameraParam)) == NULL) {
		std::cout << "[RTC::ARMarkerDetector] Error: arCreate3DHandle" << std::endl;
		return RTC::RTC_ERROR;
	}


	if (arSetPatternDetectionMode(m_pARHandle, AR_MATRIX_CODE_DETECTION) != 0) {
		std::cout << "[RTC::ARMarkerDetector] Error:arSetPatternDetectionMode " << std::endl;
		return RTC::RTC_ERROR;
	}

	if (arSetMatrixCodeType(m_pARHandle, AR_MATRIX_CODE_4x4) != 0) {
		std::cout << "[RTC::ARMarkerDetector] Error:arSetMatrixCodeType" << std::endl;
		return RTC::RTC_ERROR;
	}


  return RTC::RTC_OK;
}


RTC::ReturnCode_t ARTKMarker::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



::ARUint8 data;

RTC::ReturnCode_t ARTKMarker::detectMarker() {
  m_MatrixMutex.lock();
  
  arDetectMarker(m_pARHandle, m_srcImage.data);
  
  if (m_pARHandle->marker_num > 0) {
    int mostConfidentIndex = -1;
    double confidence = -1;
    for (int i = 0; i < m_pARHandle->marker_num; i++) {
      if (mostConfidentIndex == -1) {
	mostConfidentIndex = i; // First marker detected.
	confidence = m_pARHandle->markerInfo[i].cf;
      }
      else if (m_pARHandle->markerInfo[i].cf > m_pARHandle->markerInfo[mostConfidentIndex].cf)  {
	mostConfidentIndex = i; // Higher confidence marker detected.
	confidence = m_pARHandle->markerInfo[i].cf;
      }
    }
    
    if (confidence > 0.5) {
      ARdouble _trans[3][4];		// Per-marker, but we are using only 1 marker.
      ARdouble err;
      err = arGetTransMatSquare(m_pAR3DHandle, &(m_pARHandle->markerInfo[mostConfidentIndex]), m_markerWidth, _trans);
      
      
      std::stringstream sst;
      sst << m_pARHandle->markerInfo[mostConfidentIndex].idMatrix;
      //m_MarkerInfo.id = CORBA::string_dup(sst.str().c_str());
      m_MarkerInfo.id = m_pARHandle->markerInfo[mostConfidentIndex].idMatrix;
      m_MarkerInfo.name = CORBA::string_dup(sst.str().c_str());
      int x = 2; int signX = 1;
      int y = 0; int signY = -1;
      int z = 1; int signZ = -1;
      m_MarkerInfo.markerPoseMatrix[0][0] = _trans[x][2];
      m_MarkerInfo.markerPoseMatrix[0][1] = -_trans[x][0];
      m_MarkerInfo.markerPoseMatrix[0][2] = -_trans[x][1];
      m_MarkerInfo.markerPoseMatrix[1][0] = _trans[y][2];
      m_MarkerInfo.markerPoseMatrix[1][1] = -_trans[y][0];
      m_MarkerInfo.markerPoseMatrix[1][2] = -_trans[y][1];
      m_MarkerInfo.markerPoseMatrix[2][0] = _trans[z][2];
      m_MarkerInfo.markerPoseMatrix[2][1] = -_trans[z][0];
      m_MarkerInfo.markerPoseMatrix[2][2] = -_trans[z][1];
      m_MarkerInfo.markerPoseMatrix[0][3] = signX * _trans[x][3] / 1000;
      m_MarkerInfo.markerPoseMatrix[1][3] = signY * _trans[y][3] / 1000;
      m_MarkerInfo.markerPoseMatrix[2][3] = signZ * _trans[z][3] / 1000;
      
      if (m_debug == 0) {
	static int i;
	if (i % 2 == 0) {
	  std::cout << "Marker Id is " << m_MarkerInfo.id << " / " << confidence << std::endl;
	  for (int i = 0; i < 3; i++) {
	    for (int j = 0; j < 4; j++) {
	      std::cout << m_MarkerInfo.markerPoseMatrix[i][j] << ", ";
	    }
	    std::cout << "\n";
	  }
	}
	i++;
      }
      
    }
  }
  else {
    if (m_debug > 0) {
      std::cout << "No Marker Detected" << std::endl;
    }
    
    this->m_MarkerInfo.id = -1;
    this->m_MarkerInfo.name = "";
  }
  
  m_MatrixMutex.unlock();
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ARTKMarker::onExecute(RTC::UniqueId ec_id)
{
  if (m_imageIn.isNew()) {
    m_imageIn.read();
    if (convertImgToCvMat(m_image.data, m_srcImage)) {
      if (m_srcImage.size().width != m_imageWidth || m_srcImage.size().height != m_imageHeight) {
	std::cout << "[RTC::ARMarkerDetector] Image Size do not match." << std::endl;
	return RTC::RTC_ERROR;
      }
      detectMarker();
    }
    else {
      std::cout << "[RTC::ARMarkerDetector] Failed To Decode Image." << std::endl;
      return RTC::RTC_ERROR;
    }
  }
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ARTKMarker::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarker::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarker::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarker::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ARTKMarker::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ARTKMarkerInit(RTC::Manager* manager)
  {
    coil::Properties profile(artkmarker_spec);
    manager->registerFactory(profile,
                             RTC::Create<ARTKMarker>,
                             RTC::Delete<ARTKMarker>);
  }
  
};


