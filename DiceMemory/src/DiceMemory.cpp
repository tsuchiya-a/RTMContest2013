// -*- C++ -*-
/*!
 * @file  DiceMemory.cpp
 * @brief Record input numbers and output them in series after the recording
 * @date $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "DiceMemory.h"

// Module specification
// <rtc-template block="module_spec">
static const char* dicememory_spec[] =
  {
    "implementation_id", "DiceMemory",
    "type_name",         "DiceMemory",
    "description",       "Record input numbers and output them in series after the recording",
    "version",           "1.0.0",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "Dice",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.TimeInterval", "2.0",
    "conf.default.LoopMode", "0",
    "conf.default.DiceStore", "5",
    // Widget
    "conf.__widget__.TimeInterval", "text",
    "conf.__widget__.LoopMode", "radio",
    "conf.__widget__.DiceStore", "text",
    // Constraints
    "conf.__constraints__.TimeInterval", "x>=0",
    "conf.__constraints__.LoopMode", "(0,1)",
    "conf.__constraints__.DiceStore", "x>0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DiceMemory::DiceMemory(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_DiceNumberIn("DiceNumber", m_DiceNumber),
    m_RecordedNumberOut("RecordedNumber", m_RecordedNumber)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
DiceMemory::~DiceMemory()
{
}



RTC::ReturnCode_t DiceMemory::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("DiceNumber", m_DiceNumberIn);
  
  // Set OutPort buffer
  addOutPort("RecordedNumber", m_RecordedNumberOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("TimeInterval", m_TimeInterval, "2.0");
  bindParameter("LoopMode", m_LoopMode, "0");
  bindParameter("DiceStore", m_DiceStore, "5");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceMemory::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceMemory::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceMemory::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t DiceMemory::onActivated(RTC::UniqueId ec_id)
{
  number_list.clear();
  recording = false;
  store_num = m_DiceStore;

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceMemory::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * InPortのDiceNumberから入力されたサイコロの出目の値をConfigurati
 * onのDiceStoreで指定された回数記録する。
 * 記録が完了したら、次にサイコロが静止したとき（＝新たなサイコロの
 * 出目がInPortに入力されたとき）に、記録された値をOutPortのRecord
 * edNumberから順に出力する。
 * Configurationでは、再生時の時間間隔とループのON/OFFを切り替える
 * ことができるTimeIntervalでは出力の時間間隔を指定できる。LoopMod
 * eでは再生時のループのON/OFFが切り替えられる。OFF(0)の場合は、記
 * 録されたすべての値を出力し終わった後に消灯し、ON(1)の場合は、ま
 * た初めから出力する。
 * ConfigurationのDiceStoreが変更されるか再生時に再び動かされた場合
 * は、記録を最初からやり直す。
 */

RTC::ReturnCode_t DiceMemory::onExecute(RTC::UniqueId ec_id)
{
  coil::TimeValue tm;

  //コンフィギュレーションのDiceStoreが変更された場合は記録されたデータがあってもリセット
  if(store_num != m_DiceStore){
    number_list.clear();
    recording = false;
    store_num = m_DiceStore;
    std::cout << "Clear stored data" << std::endl << std::endl;
    std::cout << "Data to be stored:" << store_num << std::endl;
  }

  //データの取得
  if(m_DiceNumberIn.isNew()){
    m_DiceNumberIn.read();

    if(m_DiceNumber.data==0 && !recording){ //初期状態もしくは再生モードのときにサイコロが最初に動き出したら記録開始
      recording = true;
      number_list.clear();
      std::cout << "Start recording" << std::endl;
    }else if(m_DiceNumber.data>0 && recording){ //記録中に出目の値が来たら
      if(number_list.size()<store_num){ //まだ指定された数の保存がされていないなら
        number_list.push_back(m_DiceNumber.data); //データを保存する
        std::cout << "Store data (" << number_list.size() << "/" << store_num << "): " << m_DiceNumber.data << std::endl;
      }else{ //指定されたデータ数を満たしているなら（つまり、データ数を満たして、次に静止したとき）
        //何らかの理由で指定数よりも多くデータが保存されていたら消す→必要？
        //while(number_list.size()>store_num && !number_list.empty()){
        //  number_list.pop_front();
        //}

        recording = false; //記録をストップ（再生モードへ）
        //データ出力のための変数の初期化
        it = number_list.begin(); //再生箇所の初期化
        prev_tm = coil::gettimeofday(); //この時点での時刻を保存
        std::cout << "Done recording" << std::endl << std::endl;
      }
    }
  }

  //記録データの出力
  if(!recording && !number_list.empty()){ 
    tm = coil::gettimeofday(); //現在時刻を取得
    if((tm.sec()-prev_tm.sec() + (tm.usec()-prev_tm.usec())/1000000.0)>=m_TimeInterval){ //前回の出力から指定された時間以上経過したら
      if(it==number_list.end() && m_LoopMode==1){ //ループ指定がある場合は、終わりまでいっていたら最初に戻す
        it = number_list.begin();
        std::cout << std::endl;
	  }
	  if(it!=number_list.end()){
        m_RecordedNumber.data = *it;
        m_RecordedNumberOut.write();
        std::cout << "Output data:" << m_RecordedNumber.data << std::endl;
        it++;
        prev_tm = tm;
      }
    }
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceMemory::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceMemory::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceMemory::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceMemory::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceMemory::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void DiceMemoryInit(RTC::Manager* manager)
  {
    coil::Properties profile(dicememory_spec);
    manager->registerFactory(profile,
                             RTC::Create<DiceMemory>,
                             RTC::Delete<DiceMemory>);
  }
  
};


