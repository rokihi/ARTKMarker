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
    "conf.default.param_file_path", "camera_param.dat",
    // Widget
    "conf.__widget__.debug", "text",
    "conf.__widget__.param_file_path", "text",
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
  bindParameter("param_file_path", m_param_file_path, "camera_param.dat");
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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ARTKMarker::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ARTKMarker::onExecute(RTC::UniqueId ec_id)
{
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


