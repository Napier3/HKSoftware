//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SchemaCheckSetting.h  CSchemaCheckSetting

#pragma once

#include "CSchemaCheckSettingObjectGlobal.h"



class CSchemaCheckSetting : public CExBaseObject
{
public:
	CSchemaCheckSetting();
	virtual ~CSchemaCheckSetting();


	long  m_nBeSelected;
	CString  m_strDescription;
	CString  m_strVersionType;
	CString  m_strXmlMethod;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSCHEMACHECKSETTING;   }
	virtual BSTR GetXmlElementKey()  {      return CCSchemaCheckSettingObjectXmlRWKeys::CSchemaCheckSettingKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

