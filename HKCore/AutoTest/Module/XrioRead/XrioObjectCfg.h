//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XrioObjectCfg.h

#pragma once

#include "XrioCfgMngrGlobal.h"

class CXrioUnit : public CExBaseObject
{
public:
	CXrioUnit();
	virtual ~CXrioUnit();
	
	CString m_strDecimalPlaces;
	CString m_strUnit;

//���غ���
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_UNIT;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::UnitKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
};

class CXrioRefParam : public CExBaseObject
{
public:
	CXrioRefParam();
	virtual ~CXrioRefParam();
	
	CString m_strRefID;
	CString m_strRefParam;

//���غ���
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_REFPARAM;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::RefParamKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
};

class CXrioRefEnum : public CExBaseObject
{
public:
	CXrioRefEnum();
	virtual ~CXrioRefEnum();
	
	CString m_strRefID;
	CString m_strRefEnum;

//���غ���
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_REFENUM;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::RefEnumKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
};

class CXrioEnumValue : public CExBaseObject
{
public:
	CXrioEnumValue();
	virtual ~CXrioEnumValue();

	CString m_strEnumId;

	//���غ���
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_ENUMVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::EnumValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};