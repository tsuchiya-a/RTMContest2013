// -*- C++ -*-
/*!
 * @file  DiceCalculation.cpp
 * @brief Calculate dice number based on the acceleration data and output the number if the dice is stationary
 * @date $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "DiceCalculation.h"

#include <iostream>
#include <cmath>

// Module specification
// <rtc-template block="module_spec">
static const char* dicecalculation_spec[] =
  {
    "implementation_id", "DiceCalculation",
    "type_name",         "DiceCalculation",
    "description",       "Calculate dice number based on the acceleration data and output the number if the dice is stationary",
    "version",           "1.0.0",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "Dice",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.PlusX", "1",
    "conf.default.PlusY", "2",
    "conf.default.PlusZ", "3",
    "conf.default.MinusX", "6",
    "conf.default.MinusY", "5",
    "conf.default.MinusZ", "4",
    "conf.default.SensorThreshold", "0.15",
    "conf.default.StopTimeThreshold", "1.0",
    "conf.default.SlopeThreshold", "15",
    // Widget
    "conf.__widget__.PlusX", "text",
    "conf.__widget__.PlusY", "text",
    "conf.__widget__.PlusZ", "text",
    "conf.__widget__.MinusX", "text",
    "conf.__widget__.MinusY", "text",
    "conf.__widget__.MinusZ", "text",
    "conf.__widget__.SensorThreshold", "text",
    "conf.__widget__.StopTimeThreshold", "text",
    "conf.__widget__.SlopeThreshold", "text",
    // Constraints
    "conf.__constraints__.SensorThreshold", "x>=0",
    "conf.__constraints__.StopTimeThreshold", "x>=0",
    "conf.__constraints__.SlopeThreshold", "0<=x<45",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DiceCalculation::DiceCalculation(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_DiceAccelerationIn("DiceAcceleration", m_DiceAcceleration),
    m_DiceNumberOut("DiceNumber", m_DiceNumber)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
DiceCalculation::~DiceCalculation()
{
}



RTC::ReturnCode_t DiceCalculation::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("DiceAcceleration", m_DiceAccelerationIn);
  
  // Set OutPort buffer
  addOutPort("DiceNumber", m_DiceNumberOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("PlusX", m_PlusX, "1");
  bindParameter("PlusY", m_PlusY, "2");
  bindParameter("PlusZ", m_PlusZ, "3");
  bindParameter("MinusX", m_MinusX, "6");
  bindParameter("MinusY", m_MinusY, "5");
  bindParameter("MinusZ", m_MinusZ, "4");
  bindParameter("SensorThreshold", m_SensorThreshold, "0.15");
  bindParameter("StopTimeThreshold", m_StopTimeThreshold, "1.0");
  bindParameter("SlopeThreshold", m_SlopeThreshold, "15");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceCalculation::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceCalculation::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceCalculation::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t DiceCalculation::onActivated(RTC::UniqueId ec_id)
{
  status = 0;
  for(int i=0;i<3;i++){
    a_prev[i] = 0;
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceCalculation::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * diceAccelerationから3軸加速度センサの値を読み込み、静止状態の判
 * 定と、静止状態の場合はサイコロの上面にあたる目を計算し、現在の出
 * 目としてOutPortのdiceNumberから出力する。
 */

RTC::ReturnCode_t DiceCalculation::onExecute(RTC::UniqueId ec_id)
{
  const double gravity = 9.8; //重力加速度[m/s/s]

  double angle; //サイコロの傾き
  double a_now[3]; //受信した加速度センサの値
  int dice[6]={m_PlusX,m_PlusY,m_PlusZ,m_MinusX,m_MinusY,m_MinusZ}; //サイコロの姿勢に対応する出目の値
  coil::TimeValue tm; //現在時刻（十分な時間静止しているかの判定に使用）
  double acc; //加速度の大きさ
  int max_abs_pos; //加速度が最大の軸を表す
  int number; //出力する出目の値

  if(m_DiceAccelerationIn.isNew()){
    m_DiceAccelerationIn.read();

    a_now[0]=m_DiceAcceleration.data.ax;
    a_now[1]=m_DiceAcceleration.data.ay;
    a_now[2]=m_DiceAcceleration.data.az;

    acc = std::sqrt(a_now[0]*a_now[0]+a_now[1]*a_now[1]+a_now[2]*a_now[2]); //加速度の大きさを計算
    if((std::fabs(a_now[0]-a_prev[0])<m_SensorThreshold)&&(std::fabs(a_now[1]-a_prev[1])<m_SensorThreshold)&&(std::fabs(a_now[2]-a_prev[2])<m_SensorThreshold)&&(std::fabs(acc-gravity)<m_SensorThreshold)){ //加速度による静止判定: 加速度の変化が少なく1gからのずれも少なかったら
      if(status==0){ //動いているとき
        tm_start = coil::gettimeofday(); //静止判定開始時刻を基準時刻として取得
        status = 1; //判定中に移る
      }else if(status==1){ //判定中のとき
        tm = coil::gettimeofday(); //基準時刻と比較するための時刻を取得
        if((tm.sec()-tm_start.sec() + (tm.usec()-tm_start.usec())/1000000.0)>=m_StopTimeThreshold){ //時間による静止判定: 指定時間以上、加速度が静止条件に当てはまっていたら
          status = 2; //静止状態に移る
          std::cout << "Stopped" << std::endl;

          //出目の判定
          //加速度の大きさが最大の軸を探す
          max_abs_pos = 0;
          for(int i=1;i<3;i++){
            if(std::fabs(a_now[max_abs_pos])<std::fabs(a_now[i])){
              max_abs_pos = i;
            }
          }
          //重力方向とのなす角を求める
          angle = std::acos(std::fabs(a_now[max_abs_pos])/acc)*(180/3.141592); //角度は度に変換
          std::cout << "maximum acceleration (absolute):" << a_now[max_abs_pos] << " at:" << max_abs_pos << std::endl;
          std::cout << "angle:" << angle << std::endl;
          if(angle <= m_SlopeThreshold){ //角度が指定範囲内にあったら
            //出目を判断する
            if(a_now[max_abs_pos]<0){ //最大の加速度の軸が負の値の場合は、目があるのは正の方向
              number = dice[max_abs_pos];
            }else{ //最大の加速度の軸が正の値の場合は、目があるのは負の方向
              number = dice[max_abs_pos+3];
            }
          }else{
            //出目が不明
            number = -1;
          }
          //結果を出力
          m_DiceNumber.data = number;
          setTimestamp(m_DiceNumber);
          m_DiceNumberOut.write();
          std::cout << "number:" << number << std::endl;
        }
      }
    }else{ //静止判定の条件を満たさないとき
      status = 0; //動いている状態に
      //結果を出力
      m_DiceNumber.data = 0;
      setTimestamp(m_DiceNumber);
      m_DiceNumberOut.write();
      std::cout << "number (moving):" << m_DiceNumber.data << std::endl;
    }

    //取得した加速度データを保存
    for(int i=0;i<3;i++){
      a_prev[i]=a_now[i];
    }

  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceCalculation::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceCalculation::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceCalculation::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceCalculation::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceCalculation::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void DiceCalculationInit(RTC::Manager* manager)
  {
    coil::Properties profile(dicecalculation_spec);
    manager->registerFactory(profile,
                             RTC::Create<DiceCalculation>,
                             RTC::Delete<DiceCalculation>);
  }
  
};


