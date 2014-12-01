// -*- C++ -*-
/*!
 * @file  DiceMemory.h
 * @brief Record input numbers and output them in series after the recording
 * @date  $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef DICEMEMORY_H
#define DICEMEMORY_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <list>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class DiceMemory
 * @brief Record input numbers and output them in series after the recording
 *
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
 *
 * InPort
 * ポート名/型/説明
 * DiceNumber/TimedShort/サイコロの出目。1～6がそれぞれサイコロの目
 * に対応している。0は静止していない時、-1は上面が決定出来ない場合
 * を表す。
 * OutPort
 * ポート名/型/説明
 * RecordedNumber/TimedShort/サイコロの出目。1~6がそれぞれサイコロ
 * の目に対応している。記録順に出力される。出力間隔はConfiguration
 * のTimeIntervalで指定される。
 *
 */
class DiceMemory
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  DiceMemory(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~DiceMemory();

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
   * 初期化を行う。
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
  // virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   * InPortのDiceNumberから入力されたサイコロの出目の値をConfigura
   * tionのDiceStoreで指定された回数記録する。
   * 記録が完了したら、次にサイコロが静止したとき（＝新たなサイコロ
   * の出目がInPortに入力されたとき）に、記録された値をOutPortのRe
   * cordedNumberから順に出力する。
   * Configurationでは、再生時の時間間隔とループのON/OFFを切り替え
   * ることができるTimeIntervalでは出力の時間間隔を指定できる。Loo
   * pModeでは再生時のループのON/OFFが切り替えられる。OFF(0)の場合
   * は、記録されたすべての値を出力し終わった後に消灯し、ON(1)の場
   * 合は、また初めから出力する。
   * ConfigurationのDiceStoreが変更されるか再生時に再び動かされた場
   * 合は、記録を最初からやり直す。
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
   * 出目を出力する際の時間間隔。単位は秒。
   * - Name: TimeInterval TimeInterval
   * - DefaultValue: 2.0
   * - Unit: s
   * - Range: 0以上
   * - Constraint: x>=0
   */
  double m_TimeInterval;
  /*!
   * 出力がループするかどうかの変更。
   * 1:ON。ループする。
   * 0:OFF。ループしない。
   * - Name: LoopMode LoopMode
   * - DefaultValue: 0
   * - Range: 0または1
   * - Constraint: (0,1)
   */
  int m_LoopMode;
  /*!
   * 出目の記録数。
   * - Name: DiceStore DiceStore
   * - DefaultValue: 5
   * - Range: 自然数
   * - Constraint: x>0
   */
  int m_DiceStore;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedShort m_DiceNumber;
  /*!
   * サイコロの出目。1～6がそれぞれサイコロの目に対応している。0は
   * 静止していない時、-1は上面が決定出来ない場合を表す。
   * - Type: TimedShort
   */
  InPort<TimedShort> m_DiceNumberIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  TimedShort m_RecordedNumber;
  /*!
   * サイコロの出目。1~6がそれぞれサイコロの目に対応している。記録
   * 順に出力される。出力間隔はConfigurationのTimeIntervalで指定さ
   * れる。
   * - Type: TimedShort
   */
  OutPort<TimedShort> m_RecordedNumberOut;
  
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
  coil::TimeValue prev_tm;
  std::list<int> number_list;
  std::list<int>::iterator it;
  bool recording; //trueなら保存状態、falseなら初期状態もしくは再生状態
  int store_num;
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void DiceMemoryInit(RTC::Manager* manager);
};

#endif // DICEMEMORY_H
