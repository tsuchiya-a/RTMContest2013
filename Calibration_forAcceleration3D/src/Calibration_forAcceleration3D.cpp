// -*- C++ -*-
/*!
 * @file  Calibration_forAcceleration3D.cpp
 * @brief Calibration for Acceleration3D
 * @date $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "Calibration_forAcceleration3D.h"

#include <opencv2\core\core.hpp>
#include <vector>
#include <math.h>
#include "VectorConvert.h"

// センサ値の回転を行う
std::vector<double> rotation(double x,double y,double z,double theta,double psi,double phi);

// Module specification
// <rtc-template block="module_spec">
static const char* calibration_foracceleration3d_spec[] =
  {
    "implementation_id", "Calibration_forAcceleration3D",
    "type_name",         "Calibration_forAcceleration3D",
    "description",       "Calibration for Acceleration3D",
    "version",           "1.0.0",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "tool",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.params_x", "1.0,0.0",
    "conf.default.params_y", "1.0,0.0",
    "conf.default.params_z", "1.0,0.0",
    "conf.default.params_theta", "0",
    "conf.default.params_psi", "0",
    "conf.default.params_phi", "0",
    "conf.default.InPortSelect", "TimedDoubleSeqIn",
    "conf.default.OutPortSelect", "Acceleration3DOut",
    // Widget
    "conf.__widget__.params_x", "text",
    "conf.__widget__.params_y", "text",
    "conf.__widget__.params_z", "text",
    "conf.__widget__.params_theta", "text",
    "conf.__widget__.params_psi", "text",
    "conf.__widget__.params_phi", "text",
    "conf.__widget__.InPortSelect", "radio",
    "conf.__widget__.OutPortSelect", "radio",
    // Constraints
    "conf.__constraints__.InPortSelect", "(Acceleration3DIn,TimedDoubleSeqIn)",
    "conf.__constraints__.OutPortSelect", "(Acceleration3DOut,TimedDoubleSeqOut)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Calibration_forAcceleration3D::Calibration_forAcceleration3D(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_Acceleration3DInIn("Acceleration3DIn", m_Acceleration3DIn),
    m_TimedDoubleSeqInIn("TimedDoubleSeqIn", m_TimedDoubleSeqIn),
    m_Acceleration3DOutOut("Acceleration3DOut", m_Acceleration3DOut),
    m_TimedDoubleSeqOutOut("TimedDoubleSeqOut", m_TimedDoubleSeqOut)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Calibration_forAcceleration3D::~Calibration_forAcceleration3D()
{
}



RTC::ReturnCode_t Calibration_forAcceleration3D::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Acceleration3DIn", m_Acceleration3DInIn);
  addInPort("TimedDoubleSeqIn", m_TimedDoubleSeqInIn);
  
  // Set OutPort buffer
  addOutPort("Acceleration3DOut", m_Acceleration3DOutOut);
  addOutPort("TimedDoubleSeqOut", m_TimedDoubleSeqOutOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("params_x", m_params_x, "1.0,0.0");
  bindParameter("params_y", m_params_y, "1.0,0.0");
  bindParameter("params_z", m_params_z, "1.0,0.0");
  bindParameter("params_theta", m_params_theta, "0");
  bindParameter("params_psi", m_params_psi, "0");
  bindParameter("params_phi", m_params_phi, "0");
  bindParameter("InPortSelect", m_InPortSelect, "TimedDoubleSeqIn");
  bindParameter("OutPortSelect", m_OutPortSelect, "Acceleration3DOut");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化処理を行う。
 */

RTC::ReturnCode_t Calibration_forAcceleration3D::onActivated(RTC::UniqueId ec_id)
{
  while(m_Acceleration3DInIn.isNew()) m_Acceleration3DInIn.read();
  while(m_TimedDoubleSeqInIn.isNew()) m_TimedDoubleSeqInIn.read();
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t Calibration_forAcceleration3D::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
 * キャリブレーションや型の変換を行う。
 */

RTC::ReturnCode_t Calibration_forAcceleration3D::onExecute(RTC::UniqueId ec_id)
{
  double x,y,z;
  std::vector<double> data;
  if(m_InPortSelect=="Acceleration3DIn"){
	if(m_Acceleration3DInIn.isNew()){
		m_Acceleration3DInIn.read();
		std::cout<<"------start------"<<std::endl;
		std::cout<<"ax="<<m_Acceleration3DIn.data.ax<<"ay="<<m_Acceleration3DIn.data.ay<<"az="<<m_Acceleration3DIn.data.az<<std::endl;
		x=m_params_x[0]*m_Acceleration3DIn.data.ax+m_params_x[1];
		y=m_params_y[0]*m_Acceleration3DIn.data.ay+m_params_y[1];
		z=m_params_z[0]*m_Acceleration3DIn.data.az+m_params_z[1];
		data=rotation(x,y,z,m_params_theta,m_params_psi,m_params_phi);
		if(m_OutPortSelect=="Acceleration3DOut"){
			m_Acceleration3DOut.data.ax=data[0];
			m_Acceleration3DOut.data.ay=data[1];
			m_Acceleration3DOut.data.az=data[2];
			std::cout<<"ax="<<m_Acceleration3DOut.data.ax<<"ay="<<m_Acceleration3DOut.data.ay<<"az="<<m_Acceleration3DOut.data.az<<std::endl;
			m_Acceleration3DOutOut.write();
		}
		else if(m_OutPortSelect=="TimedDoubleSeqOut"){
			m_TimedDoubleSeqOut.data.length(3);
			m_TimedDoubleSeqOut.data[0]=data[0];
			m_TimedDoubleSeqOut.data[1]=data[1];
			m_TimedDoubleSeqOut.data[2]=data[2];
			std::cout<<"ax="<<m_TimedDoubleSeqOut.data[0]<<"ay="<<m_TimedDoubleSeqOut.data[1]<<"az="<<m_TimedDoubleSeqOut.data[2]<<std::endl;
			m_TimedDoubleSeqOutOut.write();
		}
	data.clear();
	std::cout<<"------end------"<<std::endl;
	}
  }
  else if(m_InPortSelect=="TimedDoubleSeqIn"){
	if(m_TimedDoubleSeqInIn.isNew()){
		m_TimedDoubleSeqInIn.read();
		if(m_TimedDoubleSeqIn.data.length()==3){
			std::cout<<"------start------"<<std::endl;
			std::cout<<"ax="<<m_TimedDoubleSeqIn.data[0]<<"ay="<<m_TimedDoubleSeqIn.data[1]<<"az="<<m_TimedDoubleSeqIn.data[2]<<std::endl;
			x=m_params_x[0]*m_TimedDoubleSeqIn.data[0]+m_params_x[1];
			y=m_params_y[0]*m_TimedDoubleSeqIn.data[1]+m_params_y[1];
			z=m_params_z[0]*m_TimedDoubleSeqIn.data[2]+m_params_z[1];
			data=rotation(x,y,z,m_params_theta,m_params_psi,m_params_phi);
		}
		else std::cerr<<"Invalid data length (m_TimedDoubleSeqIn): "<< m_TimedDoubleSeqIn.data.length() <<std::endl;
		if(m_OutPortSelect=="Acceleration3DOut"){
			m_Acceleration3DOut.data.ax=data[0];
			m_Acceleration3DOut.data.ay=data[1];
			m_Acceleration3DOut.data.az=data[2];
			std::cout<<"ax="<<m_Acceleration3DOut.data.ax<<"ay="<<m_Acceleration3DOut.data.ay<<"az="<<m_Acceleration3DOut.data.az<<std::endl;
			m_Acceleration3DOutOut.write();
		}
		else if(m_OutPortSelect=="TimedDoubleSeqOut"){
			m_TimedDoubleSeqOut.data.length(3);
			m_TimedDoubleSeqOut.data[0]=data[0];
			m_TimedDoubleSeqOut.data[1]=data[1];
			m_TimedDoubleSeqOut.data[2]=data[2];
			std::cout<<"ax="<<m_TimedDoubleSeqOut.data[0]<<"ay="<<m_TimedDoubleSeqOut.data[1]<<"az="<<m_TimedDoubleSeqOut.data[2]<<std::endl;
			m_TimedDoubleSeqOutOut.write();
		}
	data.clear();
	std::cout<<"------end------"<<std::endl;
	}
  } 
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Calibration_forAcceleration3D::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

// センサ値の回転を行う
std::vector<double> rotation(double x,double y,double z,double theta,double psi,double phi){
  cv::Mat prev_data=(cv::Mat_<double>(3,1) << x,y,z);

  cv::Mat x_rotation=(cv::Mat_<double>(3,3) << 1,0,0,0,std::cos(std::fabs(theta)*(180/3.141592)),std::sin(std::fabs(theta)*(180/3.141592)),0,-(std::sin(std::fabs(theta)*(180/3.141592))),std::cos(std::fabs(theta)*(180/3.141592)));
  cv::Mat y_rotation=(cv::Mat_<double>(3,3) << std::cos(std::fabs(psi)*(180/3.141592)),0,-(std::sin(std::fabs(psi)*(180/3.141592))),0,1,0,std::sin(std::fabs(psi)*(180/3.141592)),0,std::cos(std::fabs(psi)*(180/3.141592)));
  cv::Mat z_rotation=(cv::Mat_<double>(3,3) << std::cos(std::fabs(phi)*(180/3.141592)),std::sin(std::fabs(phi)*(180/3.141592)),0,-(std::sin(std::fabs(phi)*(180/3.141592))),std::cos(std::fabs(phi)*(180/3.141592)),0,0,0,1);

  cv::Mat new_data=x_rotation*y_rotation*z_rotation*prev_data;
  std::cout<<"data="<<new_data<<std::endl<<std::endl;

  std::vector<double> data;
  data.push_back(new_data.at<double>(0,0));
  data.push_back(new_data.at<double>(1,0));
  data.push_back(new_data.at<double>(2,0));

  return data;
}


extern "C"
{
 
  void Calibration_forAcceleration3DInit(RTC::Manager* manager)
  {
    coil::Properties profile(calibration_foracceleration3d_spec);
    manager->registerFactory(profile,
                             RTC::Create<Calibration_forAcceleration3D>,
                             RTC::Delete<Calibration_forAcceleration3D>);
  }
  
};


