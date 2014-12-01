// -*- C++ -*-
/*!
 * @file  DiceColorPattern.h
 * @brief Determine LED color based on the input dice number
 * @date  $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef DICECOLORPATTERN_H
#define DICECOLORPATTERN_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class DiceColorPattern
 * @brief Determine LED color based on the input dice number
 *
 * サイコロの出目を取得し、その目に応じたLEDの色を出力するコンポー
 * ネント。
 * Configurationで、各目に対して好きな色をRGBで設定することが出来る
 * 。
 * サイコロが動いている間や出目が取得できない場合はLEDを消灯させる
 * 。
 *
 * InPort:<name>/<datatype>/<documentation>
 * DiceNumber/TimedShort/サイコロの出目を取得するポート。1～6がそれ
 * ぞれサイコロの目に対応しており、それ以外の値が来た場合、LEDを消
 * 灯させる。
 * OutPort: <name>/<datatype>/<documentation>
 * DiceColorRGB/TimedRGBColour/LEDの色を出力するポート。
 * Configuration:<name>/<datatype>/<default>
 * /<widget>/<documentation>
 * Dice1/std::vector<int>/255,0,255/text/サイコロの目が1の時のLEDの
 * 色(RGB)。デフォルト値はmagenta。
 * Dice2/std::vector<int>/255,0,0/text/サイコロの目が2の時のLEDの色
 * (RGB)。デフォルト値はred。
 * Dice3/std::vector<int>/255,255,0/text/サイコロの目が3の時のLEDの
 * 色(RGB)。デフォルト値はyellow。
 * Dice4/std::vector<int>/0,255,0/text/サイコロの目が4の時のLEDの色
 * (RGB)。デフォルト値はgreen。
 * Dice5/std::vector<int>/0,0,255/text/サイコロの目が5の時のLEDの色
 * (RGB)。デフォルト値はblue。
 * Dice6/std::vector<int>/255,255,255/text/サイコロの目が6の時のLE
 * Dの色(RGB)。デフォルト値はwhite。
 *
 */
class DiceColorPattern
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  DiceColorPattern(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~DiceColorPattern();

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
   * 初期化処理を行う。
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
   * LEDを消灯して終了する。
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
   * 入力された目に対応したRGBを出力する。
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
   * サイコロの目が1の時のLEDの色(RGB)。
   * デフォルト値はmagenta。
   * - Name: Dice1 Dice1
   * - DefaultValue: 255,0,255
   * - Range: 各項0～255
   * - Constraint: 表記：R,G,B
   */
  std::vector<int> m_Dice1;
  /*!
   * サイコロの目が2の時のLEDの色(RGB)。
   * デフォルト値はred。
   * - Name: Dice2 Dice2
   * - DefaultValue: 255,0,0
   * - Range: 各項0～255
   * - Constraint: 表記：R,G,B
   */
  std::vector<int> m_Dice2;
  /*!
   * サイコロの目が3の時のLEDの色(RGB)。
   * デフォルト値はyellow。
   * - Name: Dice3 Dice3
   * - DefaultValue: 255,255,0
   * - Range: 各項0～255
   * - Constraint: 表記：R,G,B
   */
  std::vector<int> m_Dice3;
  /*!
   * サイコロの目が4の時のLEDの色(RGB)。
   * デフォルト値はgreen。
   * - Name: Dice4 Dice4
   * - DefaultValue: 0,255,0
   * - Range: 各項0～255
   * - Constraint: 表記：R,G,B
   */
  std::vector<int> m_Dice4;
  /*!
   * サイコロの目が5の時のLEDの色(RGB)。
   * デフォルト値はblue。
   * - Name: Dice5 Dice5
   * - DefaultValue: 0,0,255
   * - Range: 各項0～255
   * - Constraint: 表記：R,G,B
   */
  std::vector<int> m_Dice5;
  /*!
   * サイコロの目が6の時のLEDの色(RGB)。
   * デフォルト値はwhite。
   * - Name: Dice6 Dice6
   * - DefaultValue: 255,255,255
   * - Range: 各項0～255
   * - Constraint: 表記：R,G,B
   */
  std::vector<int> m_Dice6;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedShort m_DiceNumber;
  /*!
   * サイコロの出目を取得するポート。
   * 1～6がそれぞれサイコロの目に対応しており、
   * それ以外の値が来た場合、LEDを消灯させる。
   * - Type: TimedShort
   */
  InPort<RTC::TimedShort> m_DiceNumberIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedRGBColour m_DiceColorRGB;
  /*!
   * LEDの色を出力するポート。
   * - Type: TimedRGBColour
   */
  OutPort<RTC::TimedRGBColour> m_DiceColorRGBOut;
  
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

};


extern "C"
{
  DLL_EXPORT void DiceColorPatternInit(RTC::Manager* manager);
};

#endif // DICECOLORPATTERN_H
