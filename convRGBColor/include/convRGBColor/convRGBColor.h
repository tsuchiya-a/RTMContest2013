// -*- C++ -*-
/*!
 * @file  convRGBColor.h
 * @brief convert to RGBColor
 * @date  $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef CONVRGBCOLOR_H
#define CONVRGBCOLOR_H

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
 * @class convRGBColor
 * @brief convert to RGBColor
 *
 * TimedDoubleSeq,TimedShortSeq,TimedRGBColourのいずれかで入力され
 * たデータをTimedDoubleSeq
 * ,TimedShortSeq,TimedRGBColour,TimedLongSeqのいずれかに変換し出力
 * するコンポーネント。
 * Configuration値で入力データの範囲を指定すると、0~255の範囲のデー
 * タとして出力される。
 *
 * InPort:<name>/<datatype>/<documentation>
 * TimedDoubleSeqIn/TimedDoubleSeq/TimedDoubleSeq型のデータを取得す
 * るポート。配列の要素は0~2の前3つを利用し、足りない場合は0で補填
 * する。
 * TimedShortSeqIn/TimedShortSeq/TimedShortSeq型のデータを取得する
 * ポート。配列の要素は0~2の前3つを利用し、足りない場合は0で補填す
 * る。
 * TimedRGBColourIn/TimedRGBColour/TimedRGBColour型のデータを取得す
 * るポート。
 * OutPort: <name>/<datatype>/<documentation>
 * TimedDoubleSeqOut/TimedDoubleSeq/TimedDoubleSeq型のデータを出力
 * するポート。配列の要素は0~2の前3つを利用し、足りない場合は0で補
 * 填する。
 * TimedShortSeqOut/TimedShortSeq/TimedShortSeq型のデータを出力する
 * ポート。配列の要素は0~2の前3つを利用し、足りない場合は0で補填す
 * る。
 * TimedRGBColourOut/TimedRGBColour/TimedRGBColour型のデータを出力
 * するポート。TimedLongSeqOut/TimedLongSeq/TimedLongSeq型のデータ
 * を出力するポート。配列の要素は0~2の前3つを利用し、足りない場合は
 * 0で補填する。
 * Configuration:<name>/<datatype>/<default>
 * /<widget>/<documentation>
 * InPortSelect/string/ TimedRGBColourIn
 * /radio/入力ポートの型を選択する。
 * OutPortSelect/string/TimedLongSeqOut/radio/出力ポートの型を選択
 * する。
 * MaxData/double/255/text/入力データの最大値を指定する。これを超え
 * た入力は最大値と等しいとみなす。
 * MinData/double/0/text/入力データの最小値を指定する。これより小さ
 * い入力は最小値と等しいとみなす。
 *
 */
class convRGBColor
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  convRGBColor(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~convRGBColor();

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
   * 終了処理を行う。
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
   * 0~255の範囲にデータを変換し、RGB値の出力を行う。
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
   * InPortの型を選択する。
   * - Name: InPortSelect InPortSelect
   * - DefaultValue: TimedRGBColourIn
   */
  std::string m_InPortSelect;
  /*!
   * 出力ポートの型を選択する。
   * - Name: OutPortSelect OutPortSelect
   * - DefaultValue: TimedLongSeqOut
   */
  std::string m_OutPortSelect;
  /*!
   * 入力データの最大値を指定する。
   * これを超えた入力は最大値と等しいとみなす。
   * - Name: MaxData MaxData
   * - DefaultValue: 255
   */
  double m_MaxData;
  /*!
   * 入力データの最小値を指定する。
   * これより小さい入力は最小値と等しいとみなす。
   * - Name: MinData MinData
   * - DefaultValue: 0
   */
  double m_MinData;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedDoubleSeq m_TimedDoubleSeqIn;
  /*!
   * TimedDoubleSeq型のデータを取得するポート。
   * 配列の要素は0~2の前3つを利用し、足りない場合は0で補填する。
   * - Type: TimedDoubleSeq
   */
  InPort<RTC::TimedDoubleSeq> m_TimedDoubleSeqInIn;
  RTC::TimedShortSeq m_TimedShortSeqIn;
  /*!
   * TimedShortSeq型のデータを取得するポート。
   * 配列の要素は0~2の前3つを利用し、足りない場合は0で補填する。
   * - Type: TimeShortSeq
   */
  InPort<RTC::TimedShortSeq> m_TimedShortSeqInIn;
  RTC::TimedRGBColour m_TimedRGBColourIn;
  /*!
   * TimedRGBColour型のデータを取得するポート。
   * - Type: TimedRGBColour
   */
  InPort<RTC::TimedRGBColour> m_TimedRGBColourInIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedDoubleSeq m_TimedDoubleSeqOut;
  /*!
   * TimedDoubleSeq型のデータを出力するポート。
   * 配列の要素は0~2の前3つを利用し、足りない場合は0で補填する。
   * - Type: TimedDoubleSeq
   */
  OutPort<RTC::TimedDoubleSeq> m_TimedDoubleSeqOutOut;
  RTC::TimedShortSeq m_TimedShortSeqOut;
  /*!
   * TimedShortSeq型のデータを出力するポート。
   * 配列の要素は0~2の前3つを利用し、足りない場合は0で補填する。
   * - Type: TimedShortSeq
   */
  OutPort<RTC::TimedShortSeq> m_TimedShortSeqOutOut;
  RTC::TimedRGBColour m_TimedRGBColourOut;
  /*!
   * TimedRGBColour型のデータを出力するポート。
   * - Type: TimedRGBColour
   */
  OutPort<RTC::TimedRGBColour> m_TimedRGBColourOutOut;
  RTC::TimedLongSeq m_TimedLongSeqOut;
  /*!
   * TimeLongSeq型のデータを出力するポート。
   * 配列の要素は0~2の前3つを利用し、足りない場合は0で補填する。
   * - Type: TimedLongSeq
   */
  OutPort<RTC::TimedLongSeq> m_TimedLongSeqOutOut;
  
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
  bool input;

  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void convRGBColorInit(RTC::Manager* manager);
};

#endif // CONVRGBCOLOR_H
