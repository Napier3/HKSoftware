//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestApp.h  CIot_TestApp

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_TestApp : public CExBaseObject
{
public:
	CIot_TestApp();
	virtual ~CIot_TestApp();


	long  m_nIndex_Testapp;
	long  m_nIndex_Dept;
	long  m_nIndex_Device_Classify;
	long  m_nIndex_Device_Type;
	long  m_nIndex_Factory;
	long  m_nIndex_Engine;
	CString  m_strIp;
	long  m_nPort;
	long  m_nIndex_Model;
	long  m_nTest_State;    //测试状态：  0-空闲；1-测试中
	long  m_nConnect_State; //连接状态；  0-未连接；1-已连接
	SYSTEMTIME  m_tmCreate_Time;
	long m_nIsUpdate;// 当天的更新天数是否已更新。一天可能使用多次，但只能累计使用天数+1
	long m_nUseDays;   //当年的使用天数，每年1月1日0点清零
	long m_nUseDaysAll;  //总的使用天数
	long m_nUseCounts;  //总使用次数
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TESTAPP;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Testapp;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_TestappKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Testapp);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Testapp = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL QueryByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN);
};

