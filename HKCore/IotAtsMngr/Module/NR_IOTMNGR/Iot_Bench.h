//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Bench.h  CIot_Bench

#pragma once

#include "NR_IOTMNGRGlobal.h"


#include "Iot_BenchTestApps.h"
#include "Iot_TestTaskDevices.h"

class CIot_Bench : public CExBaseList
{
public:
	CIot_Bench();
	virtual ~CIot_Bench();


	long  m_nIndex_Bench;
	long  m_nIndex_Dept;
	CString  m_strTest_Type;
	long  m_nIndex_Tester;
	long  m_nTime_Long_Total_Test;
	long  m_nTime_Long_Used;
	long  m_nIndex_Test;
	SYSTEMTIME  m_tmTm_Begin;
	SYSTEMTIME  m_tmTm_End;
	CString  m_strTemplate_File;
	CString  m_strProtocol_File;
	CString  m_strDvm_File;
	long  m_nState;
	long  m_nIndex_Template;
	long  m_nIndex_Device_Classify;
	CString  m_strTemplate_File_S;
	CString  m_strProtocol_File_S;
	CString  m_strDvm_File_S;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_BENCH;   }
	virtual BSTR GetXmlElementKey()  {      return CNR_IOTMNGRXmlRWKeys::CIot_BenchKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Bench;     }
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CIot_BenchKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::Index_BenchKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Bench);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Bench = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:
	CIot_TestTaskDevices *m_pIot_TestTaskDevices;
	CIot_BenchTestApps *m_pIot_BenchTestApps;

//私有成员变量访问方法
public:
	CIot_TestTaskDevices* GetIot_TestTaskDevices()	{	return m_pIot_TestTaskDevices;	}
	CIot_BenchTestApps* GetIot_BenchTestApps()	{	return m_pIot_BenchTestApps;	}

//属性变量访问方法
public:
};

