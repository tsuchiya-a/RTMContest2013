// -*- C++ -*-
/*!
 * @file  DiceSort.h
 * @brief Sort Dice Numbers
 * @date  $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef DICESORT_H
#define DICESORT_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <vector>
#include "dynamic_port.hpp"
// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class DiceSort
 * @brief Sort Dice Numbers
 *
 * DiceSortは、サイコロの出目を複数取得し、ソート結果を配列としてO
 * utPortのSortDiceNumbersから出力するコンポーネントである。InPort
 * 数は、サイコロの目に応じてConfigurationで変更することが出来る。
 * また、ソート順を選択することが可能。
 *
 * InPort
 * ポート名/型/説明
 * InDiceNumber/TimedShort/サイコロの出目。1～6がそれぞれサイコロの
 * 目に対応している。それ以外の値が来たときは待機状態となる。
 * OutPort
 * ポート名/型/説明
 * SortDiceNumbers/TimedShortSeq/ソートされた順に出目の値を出力する
 * 。
 * 配列の0番目を含めた偶数番目にはサイコロのPort情報が入り、奇数番
 * 目には出目が入る。
 *
 */
class DiceSort
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  DiceSort(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~DiceSort();

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
   * 終了処理を行う
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
   * サイコロの出目を複数取得し、ソート結果を配列としてOutPortのSo
   * rtDiceNumbersから出力する。
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
   * InPortの数を決めることが出来る。サイコロの実機数に合わせて指定
   * する。
   * - Name: AddPort AddPort
   * - DefaultValue: 1
   * - Range: x>=1
   */
  int m_AddPort;
  /*!
   * ソート順を決めることが出来る。
   * 0：大きい・早い順にソート
   * 1：小さい・遅い順にソート
   * - Name: SortBase SortBase
   * - DefaultValue: 0
   */
  int m_SortBase;
  /*!
   * ソート対象を決めることが出来る。
   * 0：出目
   * 1：入力のあった時間
   * - Name: SortObject SortObject
   * - DefaultValue: 0
   */
  int m_SortObject;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  //TimedShort m_InDiceNumber;
  /*!
   * サイコロの出目。1～6がそれぞれサイコロの目に対応している。それ
   * 以外の値が来たときは待機状態となる。
   * - Type: TimedShort
   */
  DynamicInPort<TimedShort> m_InDiceNumberIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  TimedShortSeq m_SortDiceNumbers;
  /*!
   * ソートされた順に出目の値を出力する。
   * 配列の0番目を含めた偶数番目にはサイコロのPort情報が入り、奇数
   * 番目には出目が入る。
   * - Type: TimedShortSeq
   */
  OutPort<TimedShortSeq> m_SortDiceNumbersOut;
  
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
  std::vector<int> numbers;
  std::vector<int> arrived_order;
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void DiceSortInit(RTC::Manager* manager);
};

#endif // DICESORT_H
