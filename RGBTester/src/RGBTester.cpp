// -*- C++ -*-
/*!
 * @file  RGBTester.cpp
 * @brief Display input RGB color
 * @date $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "RGBTester.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// Module specification
// <rtc-template block="module_spec">
static const char* rgbtester_spec[] =
  {
    "implementation_id", "RGBTester",
    "type_name",         "RGBTester",
    "description",       "Display input RGB color",
    "version",           "1.0.0",
    "vendor",            "AyakaTsuchiya",
    "category",          "LEDColour",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Width", "500",
    "conf.default.Height", "100",
    // Widget
    "conf.__widget__.Width", "text",
    "conf.__widget__.Height", "text",
    // Constraints
    "conf.__constraints__.Width", "x>0",
    "conf.__constraints__.Height", "x>0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RGBTester::RGBTester(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_InRGBColourIn("InRGBColour", m_InRGBColour)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RGBTester::~RGBTester()
{
}



RTC::ReturnCode_t RGBTester::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("InRGBColour", m_InRGBColourIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Width", m_Width, "100");
  bindParameter("Height", m_Height, "100");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RGBTester::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBTester::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBTester::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t RGBTester::onActivated(RTC::UniqueId ec_id)
{
  color = cv::Scalar(0,0,0);
  cv::namedWindow("color", CV_WINDOW_AUTOSIZE); //ウインドウを作成

  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t RGBTester::onDeactivated(RTC::UniqueId ec_id)
{
  cv::destroyWindow("color"); //ウインドウを削除

  return RTC::RTC_OK;
}

/*!
 * 入力されたRGBの色を、RGB値とともにウインドウに表示する。
 */

RTC::ReturnCode_t RGBTester::onExecute(RTC::UniqueId ec_id)
{
  if(m_Width<=0||m_Height<=0){
    std::cout << "Invalid configuration" << std::endl;
    return RTC::RTC_OK;
  }

  cv::Mat img(cv::Size(m_Width, m_Height), CV_8UC3);
  std::stringstream rgb_str;
  int baseline=0;
  cv::Size txt_size;
  cv::Point txt_pos;

  if(m_InRGBColourIn.isNew()){ //新しいデータが来たら
    m_InRGBColourIn.read();
    //色を設定
    color = cv::Scalar(m_InRGBColour.data.b, m_InRGBColour.data.g, m_InRGBColour.data.r);
  }

  //画像を色で塗りつぶす
  img = color;

  //表示用の文字列を設定
  rgb_str << "<R=" << std::setw(3) << color[2] << ", G=" << std::setw(3) << color[1] << ", B=" << std::setw(3) << color[0] << ">";
  txt_size = cv::getTextSize(rgb_str.str(), CV_FONT_HERSHEY_COMPLEX, 1.0, 1, &baseline);
  txt_pos = cv::Point((img.cols - txt_size.width)/2, (img.rows + txt_size.height)/2);
  cv::putText(img, rgb_str.str(), txt_pos, CV_FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(255,255,255)-color);

  imshow("color", img);
  cv::waitKey(10);

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RGBTester::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBTester::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBTester::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBTester::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RGBTester::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RGBTesterInit(RTC::Manager* manager)
  {
    coil::Properties profile(rgbtester_spec);
    manager->registerFactory(profile,
                             RTC::Create<RGBTester>,
                             RTC::Delete<RGBTester>);
  }
  
};


