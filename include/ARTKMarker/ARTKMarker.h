// -*- C++ -*-
/*!
 * @file  ARTKMarker.h
 * @brief ARToolKit Marker Detector (4x4 2D BarCode)
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef ARTKMARKER_H
#define ARTKMARKER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include "ARTKMarkerInfoStub.h"
#include "ImgStub.h"

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">


// </rtc-template>

using namespace RTC;
using namespace artk;
using namespace Img;


#include <coil/Mutex.h>
#include <opencv2/opencv.hpp>

#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>


/*!
 * @class ARTKMarker
 * @brief ARToolKit Marker Detector (4x4 2D BarCode)
 *
 * AR Tool Kit Marker Detector RT-component. This uses
 * ARToolkit5.
 *
 */
class ARTKMarker
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  ARTKMarker(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~ARTKMarker();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * deprecated
   * - Name:  debug
   * - DefaultValue: 0
   */
  int m_debug;
  /*!
   * 
   * - Name:  markerWidth
   * - DefaultValue: 0.4
   */
  double m_markerWidth;
  /*!
  *
  * - Name: cameraParamFile
  * - DefaultValue: Data/camera.param
  */
  std::string m_cameraParamFile;
  /*!
  *
  * - Name:  imageWidth
  * - DefaultValue: 1280
  */
  int m_imageWidth;
  /*!
  *
  * - Name:  imageHeight
  * - DefaultValue: 960
  */
  int m_imageHeight;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  Img::TimedCameraImage m_image;
  /*!
   */
  InPort<Img::TimedCameraImage> m_imageIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  artk::ARTKMarkerInfo m_mostConfidentMarkerInfo;
  /*!
   * ARTK Marker Info Data (with 2d position and 3d position)
   */
  OutPort<artk::ARTKMarkerInfo> m_mostConfidentMarkerInfoOut;

  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  artk::ARTKMarkerInfoSeq m_markerInfoSeq;
  /*!
   * ARTK Marker Info Data (with 2d position and 3d position)
   */
  OutPort<artk::ARTKMarkerInfoSeq> m_markerInfoSeqOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

  coil::Mutex m_MatrixMutex;
  
  artk::ARTKMarkerInfo m_MarkerInfo;
  
  cv::Mat m_srcImage;
  ARParam m_cameraParam;
  ARParamLT* m_pCameraParamLT;
  ARHandle* m_pARHandle;
  AR3DHandle* m_pAR3DHandle;
  
public:

  
  void getMarkerInfo(artk::ARTKMarkerInfo& info) {
    m_MatrixMutex.lock();
    //info.id = m_MarkerInfo.id;
    //for (int i = 0; i < 3; i++) {
    //  for (int j = 0; j < 4; j++) {
    //info.matrix.value[i][j] = m_MarkerInfo.matrix.value[i][j];
    //  }
    //}
    m_MatrixMutex.unlock();
  }
  
  RTC::ReturnCode_t detectMarker();
};


extern "C"
{
  DLL_EXPORT void ARTKMarkerInit(RTC::Manager* manager);
};

#endif // ARTKMARKER_H
