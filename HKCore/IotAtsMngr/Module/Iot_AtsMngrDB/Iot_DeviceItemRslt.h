//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceItemRslt.h  CIot_DeviceItemRslt

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_DeviceItemRslt : public CExBaseObject
{
public:
	CIot_DeviceItemRslt();
	virtual ~CIot_DeviceItemRslt();


	long  m_nIndex_Item_Rslt;
	long  m_nIndex_Bench;
	long  m_nIndex_Test_Task;
	long  m_nIndex_Device;
	CString  m_strName_Item_Path;
	CString  m_strId_Item_Path;
	long  m_nState;
	long  m_nRsltjdg;
	CString  m_strRsltdsc;
	CString  m_strFile_Report;
	CString  m_strFile_Report_S;
	CString  m_strFile_Pkgs;
	CString  m_strFile_Pkgs_S;
	long  m_nSelect_State;
	long  m_nIndex_Item;
	SYSTEMTIME  m_tmCreate_Time;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICEITEMRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceItemRsltKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Item_Rslt;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceItemRsltKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Item_RsltKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Item_Rslt);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Item_Rslt = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL QueryDeviceItemRslt(CXDbBaseLib *pXDbLib,long nIndex_TestTask,long nIndex_Device
		,const CString &strItemPath);
	BOOL UpdateRsltEx(CXDbBaseLib *pXDbLib,long nIndex_TestTask
		,long nIndex_Device,const CString &strItemPath,long nState);
	BOOL UpdateRslt(CXDbBaseLib *pXDbLib,long nState);
};

