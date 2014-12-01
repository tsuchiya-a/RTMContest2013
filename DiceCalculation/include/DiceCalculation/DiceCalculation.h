// -*- C++ -*-
/*!
 * @file  DiceCalculation.h
 * @brief Calculate dice number based on the acceleration data and output the number if the dice is stationary
 * @date  $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef DICECALCULATION_H
#define DICECALCULATION_H

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
 * @class DiceCalculation
 * @brief Calculate dice number based on the acceleration data and output the number if the dice is stationary
 *
 * 正六面体のサイコロの出目を算出するコンポーネント。InPortのdiceA
 * ccelerationから3軸加速度センサの値を読み込み、静止状態の時サイコ
 * ロの上面にあたる目を現在の出目としてOutPortのdiceNumberから出力
 * する。
 * Configurationでは静止判定と上面判定の閾値を変更可能。静止判定は
 * 、現在の加速度と重力加速度を比較することで行い、SensorThreshold
 * で与えられた閾値より低い時間が、StopTimeThresholdで設定した時間
 * 続いた場合静止状態となる。また、SlopeThresholdで設定した角度をサ
 * イコロの傾き誤差とし、この範囲内であれば上面の決定が出来る。
 * アクティブ後、InPortのdiceAccelerationからセンサの値が入力される
 * 度に静止状態の判定に入る。静止状態と判定された場合は上面の判定を
 * 行い、その結果上面が決定されたときは、その面の値をOutPortのDice
 * Numberから出力する。判定ができない場合は-1をOutPortから出力する
 * 。その後、静止状態が解除されるまでは出力を行わない。解除されてい
 * る間は0を出力する。
 * また、PlusX～MinusZでは各面の目の値を設定できる。実機製作時に、
 * 軸が各面に対して90°になるように設置すること。その後、設置した面
 * に対応する数値を設定する。デフォルト値は+X軸方向に1、+Y軸方向に
 * 2、+Z軸方向に3が来て、それぞれ対面との和が7になるようにして設定
 * してある。
 *
 * InPort
 * ポート名/型/説明
 * DiceAcceleration/TimedAcceleration3D/3軸加速度センサから得られた
 * 加速度。
 * OutPort
 * ポート名/型/説明
 * DiceNumber/TimedShort/サイコロの出目。サイコロの静止状態が確認さ
 * れ、上面が決定する場合、上面にある目の値を出力する。上面が決定出
 * 来ない場合は-1を出力する。静止していない時は0を出力する。
 *
 */
class DiceCalculation
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  DiceCalculation(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~DiceCalculation();

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
   * diceAccelerationから3軸加速度センサの値を読み込み、静止状態の
   * 判定と、静止状態の場合はサイコロの上面にあたる目を計算し、現在
   * の出目としてOutPortのdiceNumberから出力する。
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
   * +X軸方向にある面に対応する目の数値。
   * - Name: PlusX PlusX
   * - DefaultValue: 1
   */
  int m_PlusX;
  /*!
   * +Y軸方向にある面に対応する目の数値。
   * - Name: PlusY PlusY
   * - DefaultValue: 2
   */
  int m_PlusY;
  /*!
   * Z軸方向にある面に対応する目の数値。
   * - Name: PlusZ PlusZ
   * - DefaultValue: 3
   */
  int m_PlusZ;
  /*!
   * -X軸方向にある面に対応する目の数値。
   * - Name: MinusX MinusX
   * - DefaultValue: 6
   */
  int m_MinusX;
  /*!
   * -Y軸方向にある面に対応する目の数値。
   * - Name: MinusY MinusY
   * - DefaultValue: 5
   */
  int m_MinusY;
  /*!
   * -Z軸方向にある面に対応する目の数値。
   * - Name: MinusZ MinusZ
   * - DefaultValue: 4
   */
  int m_MinusZ;
  /*!
   * 重力加速度と入力加速度を比較し、差がこの値より小さい場合、静止
   * していると判断するための閾値。単位はm/s^2。
   * - Name: SensorThreshold SensorThreshold
   * - DefaultValue: 0.15
   * - Unit: m/s^2
   * - Range: 0以上
   * - Constraint: x>=0
   */
  double m_SensorThreshold;
  /*!
   * この時間、静止している状態が続いたら、サイコロが静止状態にある
   * と判断する。単位は秒。
   * - Name: StopTimeThreshold StopTimeThreshold
   * - DefaultValue: 1.0
   * - Unit: s
   * - Range: 0以上
   * - Constraint: x>=0
   */
  double m_StopTimeThreshold;
  /*!
   * 上面を特定するための閾値。この傾きの角度分を誤差とする。単位は
   * 度。範囲は0?SlopeThreshold<45。
   * - Name: SlopeThreshold SlopeThreshold
   * - DefaultValue: 15
   * - Unit: deg
   * - Range: 0<=x<45
   * - Constraint: 0<=x<45
   */
  int m_SlopeThreshold;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedAcceleration3D m_DiceAcceleration;
  /*!
   * 3軸加速度センサから得られた加速度。
   * - Type: TimedAcceleration3D
   * - Unit: m/s^2
   */
  InPort<TimedAcceleration3D> m_DiceAccelerationIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  TimedShort m_DiceNumber;
  /*!
   * サイコロの出目。サイコロの静止状態が確認され、上面が決定する場
   * 合、上面にある目の値を出力する。上面が決定出来ない場合は-1を出
   * 力する。静止していない時は0を出力する。
   * - Type: TimedShort
   */
  OutPort<TimedShort> m_DiceNumberOut;
  
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
  int status; //現在のサイコロの状態 0:動いている、1:静止判定中、2:止まっている
  coil::TimeValue tm_start; //静止判定開始時刻
  double a_prev[3]; //1ステップ前の加速度の値
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void DiceCalculationInit(RTC::Manager* manager);
};

#endif // DICECALCULATION_H
