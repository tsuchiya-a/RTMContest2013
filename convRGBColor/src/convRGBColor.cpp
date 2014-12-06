// -*- C++ -*-
/*!
 * @file  convRGBColor.cpp
 * @brief convert to RGBColor
 * @date $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "convRGBColor.h"
#include <vector>
#include <math.h>

// 入力データをRGBに変換する。（参考：Arduino map関数）
double convRGB(int data,double MaxData,double MinData);
double convRGB(double data,double MaxData,double MinData);

// Module specification
// <rtc-template block="module_spec">
static const char* convrgbcolor_spec[] =
  {
    "implementation_id", "convRGBColor",
    "type_name",         "convRGBColor",
    "description",       "convert to RGBColor",
    "version",           "1.1.0",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "tool",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.InPortSelect", "TimedRGBColourIn",
    "conf.default.OutPortSelect", "TimedLongSeqOut",
    "conf.default.MaxData", "255",
    "conf.default.MinData", "0",
    // Widget
    "conf.__widget__.InPortSelect", "radio",
    "conf.__widget__.OutPortSelect", "radio",
    "conf.__widget__.MaxData", "text",
    "conf.__widget__.MinData", "text",
    // Constraints
    "conf.__constraints__.InPortSelect", "(TimedDoubleSeqIn,TimedShortSeqIn,TimedRGBColourIn)",
    "conf.__constraints__.OutPortSelect", "(TimedDoubleSeqOut,TimedShortSeqOut,TimedRGBColourOut,TimedLongSeqOut)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
convRGBColor::convRGBColor(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_TimedDoubleSeqInIn("TimedDoubleSeqIn", m_TimedDoubleSeqIn),
    m_TimedShortSeqInIn("TimedShortSeqIn", m_TimedShortSeqIn),
    m_TimedRGBColourInIn("TimedRGBColourIn", m_TimedRGBColourIn),
    m_TimedDoubleSeqOutOut("TimedDoubleSeqOut", m_TimedDoubleSeqOut),
    m_TimedShortSeqOutOut("TimedShortSeqOut", m_TimedShortSeqOut),
    m_TimedRGBColourOutOut("TimedRGBColourOut", m_TimedRGBColourOut),
    m_TimedLongSeqOutOut("TimedLongSeqOut", m_TimedLongSeqOut)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
convRGBColor::~convRGBColor()
{
}



RTC::ReturnCode_t convRGBColor::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("TimedDoubleSeqIn", m_TimedDoubleSeqInIn);
  addInPort("TimedShortSeqIn", m_TimedShortSeqInIn);
  addInPort("TimedRGBColourIn", m_TimedRGBColourInIn);
  
  // Set OutPort buffer
  addOutPort("TimedDoubleSeqOut", m_TimedDoubleSeqOutOut);
  addOutPort("TimedShortSeqOut", m_TimedShortSeqOutOut);
  addOutPort("TimedRGBColourOut", m_TimedRGBColourOutOut);
  addOutPort("TimedLongSeqOut", m_TimedLongSeqOutOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("InPortSelect", m_InPortSelect, "TimedRGBColourIn");
  bindParameter("OutPortSelect", m_OutPortSelect, "TimedLongSeqOut");
  bindParameter("MaxData", m_MaxData, "255");
  bindParameter("MinData", m_MinData, "0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t convRGBColor::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t convRGBColor::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t convRGBColor::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化処理を行う。
 */

RTC::ReturnCode_t convRGBColor::onActivated(RTC::UniqueId ec_id)
{
  while(m_TimedDoubleSeqInIn.isNew()) m_TimedDoubleSeqInIn.read();
  while(m_TimedShortSeqInIn.isNew()) m_TimedShortSeqInIn.read();
  while(m_TimedRGBColourInIn.isNew()) m_TimedRGBColourInIn.read();
  input=false;
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t convRGBColor::onDeactivated(RTC::UniqueId ec_id)
{
  for(int i=0;i<3;i++){
	  m_TimedDoubleSeqOut.data[i]=0;
  }
  m_TimedDoubleSeqOutOut.write(); //TimedDoubleSeqOutからRGB(0,0,0)を出力

  for(int i=0;i<3;i++){
	  m_TimedShortSeqOut.data[i]=0;
  }
  m_TimedShortSeqOutOut.write(); //TimedShortSeqOutからRGB(0,0,0)を出力

  for(int i=0;i<3;i++){
	  m_TimedLongSeqOut.data[i]=0;
  }
  m_TimedLongSeqOutOut.write(); //TimedLongSeqOutからRGB(0,0,0)を出力

  m_TimedRGBColourOut.data.r=0;
  m_TimedRGBColourOut.data.g=0;
  m_TimedRGBColourOut.data.b=0;
  m_TimedRGBColourOutOut.write(); //TimedRGBColourOutからRGB(0,0,0)を出力
  return RTC::RTC_OK;
}

/*!
 * 0~255の範囲にデータを変換し、RGB値の出力を行う。
 */

RTC::ReturnCode_t convRGBColor::onExecute(RTC::UniqueId ec_id)
{
  std::vector<double> color_data;

  if(m_TimedDoubleSeqInIn.isNew()){
	m_TimedDoubleSeqInIn.read();
	if(m_InPortSelect=="TimedDoubleSeqIn"){
		for(int i=0;i<3;i++){
			color_data.push_back(convRGB(m_TimedDoubleSeqIn.data[i],m_MaxData,m_MinData));
		}
	input=true;
	}
  }
  else if(m_TimedShortSeqInIn.isNew()){
	m_TimedShortSeqInIn.read();
	if(m_InPortSelect=="TimedShortSeqIn"){
		for(int i=0;i<3;i++){
			color_data.push_back(convRGB(m_TimedShortSeqIn.data[i],m_MaxData,m_MinData));
		}
	input=true;
	}
  }
  else if(m_TimedRGBColourInIn.isNew()){
	m_TimedRGBColourInIn.read();
	if(m_InPortSelect=="TimedRGBColourIn"){
		color_data.push_back(convRGB(m_TimedRGBColourIn.data.r,m_MaxData,m_MinData));
		color_data.push_back(convRGB(m_TimedRGBColourIn.data.g,m_MaxData,m_MinData));
		color_data.push_back(convRGB(m_TimedRGBColourIn.data.b,m_MaxData,m_MinData));
		input=true;
	}
  }

  if(input){
	if(m_OutPortSelect=="TimedDoubleSeqOut"){
		m_TimedDoubleSeqOut.data.length(3);
		m_TimedDoubleSeqOut.data[0]=color_data[0];
		m_TimedDoubleSeqOut.data[1]=color_data[1];
		m_TimedDoubleSeqOut.data[2]=color_data[2];
		m_TimedDoubleSeqOutOut.write();
	}
	else if(m_OutPortSelect=="TimedShortSeqOut"){
		m_TimedShortSeqOut.data.length(3);
		m_TimedShortSeqOut.data[0]=color_data[0];
		m_TimedShortSeqOut.data[1]=color_data[1];
		m_TimedShortSeqOut.data[2]=color_data[2];
		m_TimedShortSeqOutOut.write();
	}
	else if(m_OutPortSelect=="TimedRGBColourOut"){
		m_TimedRGBColourOut.data.r=color_data[0];
		m_TimedRGBColourOut.data.g=color_data[1];
		m_TimedRGBColourOut.data.b=color_data[2];
		m_TimedRGBColourOutOut.write();
	}
	else if(m_OutPortSelect=="TimedLongSeqOut"){
		m_TimedLongSeqOut.data.length(3);
		m_TimedLongSeqOut.data[0]=color_data[0];
		m_TimedLongSeqOut.data[1]=color_data[1];
		m_TimedLongSeqOut.data[2]=color_data[2];
		m_TimedLongSeqOutOut.write();
	}
	std::cout<<"InPort:"<<m_InPortSelect<<"->OutPort:"<<m_OutPortSelect<<std::endl;
	std::cout<<"R="<<color_data[0]<<" ,G="<<color_data[1]<<" ,B="<<color_data[2]<<std::endl<<std::endl;
	color_data.clear();
	input=false;
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t convRGBColor::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t convRGBColor::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t convRGBColor::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t convRGBColor::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t convRGBColor::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

// 入力データをRGBに変換する
double convRGB(int data,double MaxData,double MinData){
  double color;

  // MinData～MaxDataの範囲外のデータをMinDataかMaxDataと同値にする
  if(MaxData<MinData){
	if(data>MinData) data=MinData;
	else if(data<MaxData) data=MaxData;
  }
  else if(MaxData>MinData){
	if (data>MaxData) data=MaxData;
	else if(data<MinData) data=MinData;
  }

  color=(data-MinData)*255/(MaxData-MinData);
  return color;
}
double convRGB(double data,double MaxData,double MinData){
  double color;

  // MinData～MaxDataの範囲外のデータをMinDataかMaxDataと同値にする
  if(MaxData<MinData){
	if(data>MinData) data=MinData;
	else if(data<MaxData) data=MaxData;
  }
  else if(MaxData>MinData){
	if (data>MaxData) data=MaxData;
	else if(data<MinData) data=MinData;
  }

  color=(data-MinData)*255/(MaxData-MinData);
  return color;
}

extern "C"
{
 
  void convRGBColorInit(RTC::Manager* manager)
  {
    coil::Properties profile(convrgbcolor_spec);
    manager->registerFactory(profile,
                             RTC::Create<convRGBColor>,
                             RTC::Delete<convRGBColor>);
  }
  
};


