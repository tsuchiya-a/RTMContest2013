// -*- C++ -*-
/*!
 * @file  DiceSort.cpp
 * @brief Sort Dice Numbers
 * @date $Date$
 *
 * @author 土屋彩茜
 * y10157@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "DiceSort.h"
#include <iostream>
#include <map>

// Module specification
// <rtc-template block="module_spec">
static const char* dicesort_spec[] =
  {
    "implementation_id", "DiceSort",
    "type_name",         "DiceSort",
    "description",       "Sort Dice Numbers",
    "version",           "1.0.0",
    "vendor",            "Ayaka Tsuchiya",
    "category",          "Dice",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.AddPort", "1",
    "conf.default.SortBase", "0",
    "conf.default.SortObject", "0",
    // Widget
    "conf.__widget__.AddPort", "text",
    "conf.__widget__.SortBase", "radio",
    "conf.__widget__.SortObject", "radio",
    // Constraints
    "conf.__constraints__.AddPort", "x>=1",
    "conf.__constraints__.SortBase", "(0,1)",
    "conf.__constraints__.SortObject", "(0,1)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
DiceSort::DiceSort(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_InDiceNumberIn("InDiceNumber"),
    m_SortDiceNumbersOut("SortDiceNumbers", m_SortDiceNumbers)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
DiceSort::~DiceSort()
{
}



RTC::ReturnCode_t DiceSort::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  m_InDiceNumberIn.addPort();
  addInPort(m_InDiceNumberIn.getName(m_InDiceNumberIn.getSize()-1), m_InDiceNumberIn.m_port[m_InDiceNumberIn.getSize()-1]);

  // Set OutPort buffer
  addOutPort("SortDiceNumbers", m_SortDiceNumbersOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("AddPort", m_AddPort, "1");
  bindParameter("SortBase", m_SortBase, "0");
  bindParameter("SortObject", m_SortObject, "0");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceSort::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceSort::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceSort::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t DiceSort::onActivated(RTC::UniqueId ec_id)
{
  for(int i=0;i<(m_AddPort-1);i++){
     m_InDiceNumberIn.addPort();
     addInPort(m_InDiceNumberIn.getName(m_InDiceNumberIn.getSize()-1), m_InDiceNumberIn.m_port[m_InDiceNumberIn.getSize()-1]);
  }
  numbers.assign(m_AddPort,0);
  arrived_order.clear();

  return RTC::RTC_OK;
}


RTC::ReturnCode_t DiceSort::onDeactivated(RTC::UniqueId ec_id)
{
  while(m_InDiceNumberIn.getSize()>1){
    removeInPort(m_InDiceNumberIn.m_port[m_InDiceNumberIn.getSize()-1]);
    m_InDiceNumberIn.deletePort(m_InDiceNumberIn.getSize()-1);
  }
  return RTC::RTC_OK;
}


/*!
 * サイコロの出目を複数取得し、ソート結果を配列としてOutPortのSort
 * DiceNumbersから出力する。
 */

RTC::ReturnCode_t DiceSort::onExecute(RTC::UniqueId ec_id)
{
  unsigned int i,j;
  std::multimap<int,int> mm;
  std::multimap<int,int>::iterator it;

  //データの受け取り
  for(i=0;i<m_InDiceNumberIn.getSize();i++){
    if(m_InDiceNumberIn.m_port[i].isNew()){
      m_InDiceNumberIn.m_port[i].read();
      numbers[i] = m_InDiceNumberIn.m_data[i].data;

      //到着順序を登録
      //新しいデータに合わせるため、古いデータがあれば削除
      for(j=0;j<arrived_order.size();j++){
        if(arrived_order[j]==i){ //古いデータがあった
          arrived_order.erase(arrived_order.begin()+j); //削除する
        }
      }
      //新しいデータが有効なら登録
      if(numbers[i]>0){
        arrived_order.push_back(i);
      }
    }
  }


  //すべての出目の値が受信できた場合、結果を出力
  if(arrived_order.size()==numbers.size()){ //すべての出目の値が受信できた
    m_SortDiceNumbers.data.length(numbers.size()*2);

    if(m_SortObject==0){ //出目の値に合わせて出力
      for(i=0;i<numbers.size();i++){
        mm.insert(std::map<int,int>::value_type(numbers[i], i));
      }
      if(m_SortBase==0){ //大きい順に出力
        i = numbers.size()-1;
        it = mm.begin();
        while(it!=mm.end())
        {
          m_SortDiceNumbers.data[2*i] = (*it).second;
          m_SortDiceNumbers.data[2*i+1] = (*it).first;
          it++;
          i--;
        }
      }else{ //小さい順に出力
        i = 0;
        it = mm.begin();
        while(it!=mm.end())
        {
          m_SortDiceNumbers.data[2*i] = (*it).second;
          m_SortDiceNumbers.data[2*i+1] = (*it).first;
          it++;
          i++;
        }
      }
    }else{ //到着順序に合わせて出力
      if(m_SortBase==0){ //早い順に出力
        for(i=0;i<numbers.size();i++){
          m_SortDiceNumbers.data[2*i] = arrived_order[i];
          m_SortDiceNumbers.data[2*i+1] = numbers[arrived_order[i]];
        }
      }else{ //遅い順に出力
        for(i=0;i<numbers.size();i++){
          m_SortDiceNumbers.data[2*i] = arrived_order[numbers.size()-i-1];
          m_SortDiceNumbers.data[2*i+1] = numbers[arrived_order[numbers.size()-i-1]];
        }    
      }
    }

    setTimestamp(m_SortDiceNumbers);
    m_SortDiceNumbersOut.write();

    std::cout << "Ouput: Port index / Number" << std::endl;
    for(i=0;i<numbers.size();i++){
      std::cout << "Data " << i << ": " << m_SortDiceNumbers.data[2*i] << " / " << m_SortDiceNumbers.data[2*i+1] << std::endl;
    }
    std::cout << std::endl;

    //出力データのクリア
    numbers.assign(m_AddPort,0);
    arrived_order.clear();
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t DiceSort::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceSort::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceSort::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceSort::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t DiceSort::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void DiceSortInit(RTC::Manager* manager)
  {
    coil::Properties profile(dicesort_spec);
    manager->registerFactory(profile,
                             RTC::Create<DiceSort>,
                             RTC::Delete<DiceSort>);
  }
  
};


