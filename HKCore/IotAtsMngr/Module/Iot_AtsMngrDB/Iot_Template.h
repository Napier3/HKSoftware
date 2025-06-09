//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Template.h  CIot_Template

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_Template : public CExBaseObject
{
public:
	CIot_Template();
	virtual ~CIot_Template();


	long  m_nIndex_Template;
	long  m_nIndex_Template_Dir;
	long  m_nIndex_Device_Classify;
	long  m_nIndex_Device_Type;
	CString  m_strTemplate_File;
	CString  m_strProtocol_File;
	CString  m_strIecfg_File;
	CString  m_strDvm_File;
	CString  m_strGbxml_File;
	CString  m_strDoc_File;
	CString  m_strXml_File;
	SYSTEMTIME  m_tmUpload_Time;
	long  m_nCnt_File_Doc_Ex;
	long  m_nVersion;
	CString  m_strFile_Report;
	CString  m_strSvr_Relate_Path;
	CString  m_strItem_Gen_File;
	CString  m_strItem_Gen_File_S;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TEMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TemplateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Template;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TemplateKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_TemplateKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Template);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Template = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL QureyTemplateByName(CXDbBaseLib *pXDbLib,const CString &strFileName);
};

