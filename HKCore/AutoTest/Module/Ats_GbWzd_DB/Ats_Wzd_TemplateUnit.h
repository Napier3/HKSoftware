//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TemplateUnit.h  CAts_Wzd_TemplateUnit

#pragma once

#include "AtsGbWizrdGlobal.h"


//模板元件类
class CAts_Wzd_TemplateUnit : public CExBaseObject
{
public:
	CAts_Wzd_TemplateUnit();
	virtual ~CAts_Wzd_TemplateUnit();


	long  m_nIndex_TemplateUnit;
	long  m_nIndex_Folder;
	long  m_nIndex_Profession;
	long  m_nIndex_DeviceType;
	long  m_nIndex_Factory;
	long  m_nIndex_ULevel;
	CString  m_strTemplateFileName;
	CString  m_strDvmFileName;
	CString  m_strFullPath;   //此路径是模板元件在服务器上的绝对路径
	long  m_nIndex_DeviceModel;
	long  m_nIndex_DeviceVersion;
	long  m_nIndex_DeviceCheckCode;

	long m_nSelect;
//重载函数
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TemplateUnitKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_TemplateUnit;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TemplateUnitKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::Index_TemplateUnitKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_TemplateUnit);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_TemplateUnit = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:
	long GetSelect()	{	return m_nSelect;	}
	void SetSelect(long nSelect)	{	m_nSelect = nSelect;	}

//属性变量访问方法
public:
};

