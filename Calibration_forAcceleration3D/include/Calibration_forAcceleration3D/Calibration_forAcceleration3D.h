// -*- C++ -*-
/*!
 * @file  Calibration_forAcceleration3D.h
 * @brief Calibration for Acceleration3D
 * @date  $Date$
 *
 * @author 土屋彩茜
 * ma14076@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef CALIBRATION_FORACCELERATION3D_H
#define CALIBRATION_FORACCELERATION3D_H

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
 * @class Calibration_forAcceleration3D
 * @brief Calibration for Acceleration3D
 *
 * 入力されたセンサ値に対し、Configurationで設定したキャリブレーシ
 * ョンパラメータでキャリブレーションを行い、結果を出力するコンポー
 * ネント。
 * 入力と出力の型は、TimedDoubleSeq型とAcceleration３D型から選択で
 * き、
 * 型の変換用に使用することもできる。
 *
 * InPort:<name>/<datatype>/<documentation>
 * Acceleration3DIn/ Acceleration3D
 * /Acceleration3D型のセンサ値を取得するポート。
 * TimedDoubleSeqIn/
 * TimedDoubleSeq/TimedDoubleSeq型のセンサ値を取得するポート。
 * OutPort: <name>/<datatype>/<documentation>
 * Acceleration3DOut/ Acceleration3D
 * /Acceleration3D型のセンサ値を出力するポート。
 * TimedDoubleSeqOut/
 * TimedDoubleSeq/TimedDoubleSeq型のセンサ値を出力するポート。
 * Configuration:<name>/<datatype>/<default>
 * /<widget>/<documentation>
 * params_x/std::vector<double>/1.0,0.0/text/x軸に対するパラメータ
 * 。x軸のセンサ値をAx+Bの線形で表し、(A,B)の順で設定する。
 * params_y/std::vector<double>/1.0,0.0/text/y軸に対するパラメータ
 * 。y軸のセンサ値をAy+Bの線形で表し、(A,B)の順で設定する。
 * params_z/std::vector<double>/1.0,0.0/text/z軸に対するパラメータ
 * 。z軸のセンサ値をAz+Bの線形で表し、(A,B)の順で設定する。
 * params_theta/double/0/text/x軸の角度に対するパラメータ。
 * params_psi/double/0/text/y軸の角度に対するパラメータ。
 * params_phi/double/0/text/z軸の角度に対するパラメータ。
 * InPortSelect/string/TimeDoubleSeqIn/radio/入力ポートの型を選択す
 * る。
 * OutPortSelect/string/Accelaration3DOut/radio/出力ポートの型を選
 * 択する。
 *
 */
class Calibration_forAcceleration3D
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Calibration_forAcceleration3D(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Calibration_forAcceleration3D();

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
   * キャリブレーションや型の変換を行う。
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
   * x軸に対するパラメータ。
   * x軸のセンサ値をAx+Bの線形で表し、(A,B)の順で設定する。
   * - Name: params_x params_x
   * - DefaultValue: 1.0,0.0
   */
  std::vector<double> m_params_x;
  /*!
   * y軸に対するパラメータ。
   * y軸のセンサ値をAy+Bの線形で表し、(A,B)の順で設定する。
   * - Name: params_y params_y
   * - DefaultValue: 1.0,0.0
   */
  std::vector<double> m_params_y;
  /*!
   * z軸に対するパラメータ。
   * z軸のセンサ値をAz+Bの線形で表し、(A,B)の順で設定する。
   * - Name: params_z params_z
   * - DefaultValue: 1.0,0.0
   */
  std::vector<double> m_params_z;
  /*!
   * x軸の角度に対するパラメータ。
   * - Name: params_theta params_theta
   * - DefaultValue: 0
   */
  double m_params_theta;
  /*!
   * y軸の角度に対するパラメータ。
   * - Name: params_psi params_psi
   * - DefaultValue: 0
   */
  double m_params_psi;
  /*!
   * z軸の角度に対するパラメータ。
   * - Name: params_phi params_phi
   * - DefaultValue: 0
   */
  double m_params_phi;
  /*!
   * 入力ポートの型を選択する。
   * - Name: InPortSelect InPortSelect
   * - DefaultValue: TimedDoubleSeqIn
   */
  std::string m_InPortSelect;
  /*!
   * 出力ポートの型を選択する。
   * - Name: OutPortSelect OutPortSelect
   * - DefaultValue: Acceleration3DOut
   */
  std::string m_OutPortSelect;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedAcceleration3D m_Acceleration3DIn;
  /*!
   * Acceleration3D型のセンサ値を取得するポート。
   * - Type: Acceleration3D
   * - Unit: m/s/s
   */
  InPort<RTC::TimedAcceleration3D> m_Acceleration3DInIn;
  RTC::TimedDoubleSeq m_TimedDoubleSeqIn;
  /*!
   * TimedDoubleSeq型のセンサ値を取得するポート。
   * - Type: TimedDoubleSeq
   * - Unit: m/s/s
   */
  InPort<RTC::TimedDoubleSeq> m_TimedDoubleSeqInIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedAcceleration3D m_Acceleration3DOut;
  /*!
   * Acceleration3D型のセンサ値を出力するポート。
   * - Type: Acceleration3D
   * - Unit: m/s/s
   */
  OutPort<RTC::TimedAcceleration3D> m_Acceleration3DOutOut;
  RTC::TimedDoubleSeq m_TimedDoubleSeqOut;
  /*!
   * TimedDoubleSeq型のセンサ値を出力するポート。
   * - Type: TimedDoubleSeq
   * - Unit: m/s/s
   */
  OutPort<RTC::TimedDoubleSeq> m_TimedDoubleSeqOutOut;
  
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
  DLL_EXPORT void Calibration_forAcceleration3DInit(RTC::Manager* manager);
};

#endif // CALIBRATION_FORACCELERATION3D_H
