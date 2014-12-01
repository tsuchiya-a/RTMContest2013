// -*- C++ -*-
/*!
 * @file  DiceColorPattern.cpp
 * @brief Determine LED color based on the input dice number
 * @date $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "DiceColorPattern.h"

#include "VectorConvert.h"

// Module specification
// <rtc-template block="module_spec">
static const char* dicecolorpattern_spec[] =
  {
    "implementation_id", "DiceColorPattern",
    "type_name",         "DiceColorPattern",
    "description",       "Determine LED color based on the input dice number",
    "version",           "1.0.1",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "Category",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Dice1", "255,0,255",
    "conf.default.Dice2", "255,0,0",
    "conf.default.Dice3", "255,255,0",
    "conf.default.Dice4", "0,255,0",
    "conf.default.Dice5", "0,0,255",
    "conf.default.Dice6", "255,255,255",
    // Widget
    "conf.__widget__.Dice1", "text",
    "conf.__widget__.Dice2", "text",
    "conf.__widget__.Dice3", "text",
    "conf.__widget__.Dice4", "text",
    "conf.__widget__.Dice5", "text",
    "conf.__widget__.Dice6", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DiceColorPattern::DiceColorPattern(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_DiceNumberIn("DiceNumber", m_DiceNumber),
    m_DiceColorRGBOut("DiceColorRGB", m_DiceColorRGB)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
DiceColorPattern::~DiceColorPattern()
{
}



RTC::ReturnCode_t DiceColorPattern::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("DiceNumber", m_DiceNumberIn);
  
  // Set OutPort buffer
  addOutPort("DiceColorRGB", m_DiceColorRGBOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Dice1", m_Dice1, "255,0,255");
  bindParameter("Dice2", m_Dice2, "255,0,0");
  bindParameter("Dice3", m_Dice3, "255,255,0");
  bindParameter("Dice4", m_Dice4, "0,255,0");
  bindParameter("Dice5", m_Dice5, "0,0,255");
  bindParameter("Dice6", m_Dice6, "255,255,255");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceColorPattern::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceColorPattern::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceColorPattern::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化処理を行う。
 */

RTC::ReturnCode_t DiceColorPattern::onActivated(RTC::UniqueId ec_id)
{
  while(m_DiceNumberIn.isNew()) m_DiceNumberIn.read();
  return RTC::RTC_OK;
}

/*!
 * LEDを消灯して終了する。
 */

RTC::ReturnCode_t DiceColorPattern::onDeactivated(RTC::UniqueId ec_id)
{
  m_DiceColorRGB.data.r=0;
  m_DiceColorRGB.data.g=0;
  m_DiceColorRGB.data.b=0;
  m_DiceColorRGBOut.write();
  return RTC::RTC_OK;
}

/*!
 * 入力された目に対応したRGBを出力する。
 */

RTC::ReturnCode_t DiceColorPattern::onExecute(RTC::UniqueId ec_id)
{
  if(m_DiceNumberIn.isNew()){
	m_DiceNumberIn.read();
	std::cout<<"Dice="<<m_DiceNumber.data<<std::endl;
	switch(m_DiceNumber.data){
		case(1):m_DiceColorRGB.data.r=m_Dice1[0];
			    m_DiceColorRGB.data.g=m_Dice1[1];
			    m_DiceColorRGB.data.b=m_Dice1[2];
			    break;
		case(2):m_DiceColorRGB.data.r=m_Dice2[0];
			    m_DiceColorRGB.data.g=m_Dice2[1];
			    m_DiceColorRGB.data.b=m_Dice2[2];
			    break;
		case(3):m_DiceColorRGB.data.r=m_Dice3[0];
			    m_DiceColorRGB.data.g=m_Dice3[1];
			    m_DiceColorRGB.data.b=m_Dice3[2];
			    break;
		case(4):m_DiceColorRGB.data.r=m_Dice4[0];
			    m_DiceColorRGB.data.g=m_Dice4[1];
			    m_DiceColorRGB.data.b=m_Dice4[2];
			    break;
		case(5):m_DiceColorRGB.data.r=m_Dice5[0];
			    m_DiceColorRGB.data.g=m_Dice5[1];
			    m_DiceColorRGB.data.b=m_Dice5[2];
			    break;
		case(6):m_DiceColorRGB.data.r=m_Dice6[0];
			    m_DiceColorRGB.data.g=m_Dice6[1];
			    m_DiceColorRGB.data.b=m_Dice6[2];
			    break;
		default:m_DiceColorRGB.data.r=0;
			    m_DiceColorRGB.data.g=0;
			    m_DiceColorRGB.data.b=0;
	}
	std::cout<<"R="<<m_DiceColorRGB.data.r<<" ,G="<<m_DiceColorRGB.data.g<<" ,B="<<m_DiceColorRGB.data.b<<std::endl;
	m_DiceColorRGBOut.write();
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceColorPattern::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceColorPattern::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceColorPattern::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceColorPattern::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceColorPattern::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void DiceColorPatternInit(RTC::Manager* manager)
  {
    coil::Properties profile(dicecolorpattern_spec);
    manager->registerFactory(profile,
                             RTC::Create<DiceColorPattern>,
                             RTC::Delete<DiceColorPattern>);
  }
  
};


