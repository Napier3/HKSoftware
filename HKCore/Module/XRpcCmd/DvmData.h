//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmData.h  CDvmData

#pragma once

#include "DataMngrGlobal.h"


#include "DvmValue.h"

//////////////////////////////////////////////////////////////////////////
//CDvmData
class CDvmData : public CExBaseList
{
public:
	CDvmData();
	virtual ~CDvmData();


	CString  m_strDataType;

#ifdef _DVM_VALUE_USE_CHAR_
	wchar_t m_strValue[_DVM_VALUE_LENGTH_];
#else
	CString  m_strValue;
#endif

	CString  m_strUnit;
	CString  m_strMin;
	CString  m_strMax;
	CString  m_strFormat;
	long     m_nIndex;
	long     m_nChange;
	double   m_dTime;
	CString  m_strStep;

#ifdef _USE_IN_PPPROTOCOL_
	long     m_nDataTypeID;
	CString  m_strExprRcv;
	CString  m_strExprSend;
#endif

#ifdef DVM_USE_MAP
	CExBaseObject *m_pDvmMapObj;
#endif

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDataKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL HasValueID(const CString &strValueID);
	BOOL HasValue(const CString &strValueID, const CString &strValue);
	BOOL HasValueEx(const CString &strValueID, const CString &strValue);
	BOOL HasValueHasStr(const CString &strValueID, const CString &strValue);
	BOOL HasValueHasNoStr(const CString &strValueID, const CString &strValue);
	BOOL GetValueByID(const CString &strValueID, CString &strValue);
	CString GetValueByID(const CString &strValueID);
	CString GetAttrValue(const CString &strValueID)	{	return GetValueByID(strValueID);	}
	CString FindTag(const CString &strValueID)		{	return GetValueByID(strValueID);	}
	BOOL SetAttr(const CString &strAttrID, const CString &strValue);

	void SetIndex(long nIndex)	{		m_nIndex = nIndex;	}
	long GetIndex()				{		return m_nIndex;	}
	CDvmValue* AddNewValue(CDvmValue *pSrc = NULL);
	CDvmValue* AddValue(const CString &strAttrID, const CString &strValue);
	void GetTime(CString &strTime);
	CString GetTime();

#ifdef DVM_USE_MAP
	BOOL IsAllMap();
#endif
	CDvmValue* FindValueByID(const CString &strValueID);

#ifdef _DVM_VALUE_USE_CHAR_
	long ValueToLong();
#else
#endif

};

//////////////////////////////////////////////////////////////////////////
//CDvmBrcb
class CDvmBrcb : public CDvmData
{
public:
	CDvmBrcb();
	virtual ~CDvmBrcb();

	//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMBRCB;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmBrcbKey();     }
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

};

CString dvm_GetTimeString(double dTime);
