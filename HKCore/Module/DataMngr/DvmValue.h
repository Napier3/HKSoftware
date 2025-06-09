//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmValue.h  CDvmValue

#pragma once

#include "DataMngrGlobal.h"

#define  _DVM_VALUE_LENGTH_   128

class CDvmValue : public CExBaseList  //CExBaseObject  //2015-3-17修改
{
public:
	CDvmValue();
	virtual ~CDvmValue();


	CString  m_strDataType;

#ifdef _DVM_VALUE_USE_CHAR_
	wchar_t m_strValue[_DVM_VALUE_LENGTH_];
#else
	CString  m_strValue;
#endif

#ifdef DVM_USE_MAP
	CExBaseObject *m_pDvmMapObj;
#endif

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	
	//缓冲区串行化
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	CDvmValue* FindByID_Has(const CString &strID);
	CDvmValue* FindByID_HasEx(const CString &strSubID);
	CDvmValue* FindByID_MmsAttr(const CString &strAttrID);  //2022-5-13  lijunqing
	CString GetAttrByID_MmsAttr(const CString &strAttrID);  //2022-5-13  lijunqing

	BOOL SetValue_Mms(const CString &strAttrID, const CString &strValue);
	BOOL SetValue_Mms(const CString &strAttrID, long nValue);
	BOOL SetValue_Mms(const CString &strAttrID, unsigned long nValue);
	BOOL SetValue_Mms(const CString &strAttrID, float fValue, long nDecimal=-1);
	BOOL SetValue_Mms(const CString &strAttrID, double dValue, long nDecimal=-1);
	BOOL SetValue_Mms_Hex(const CString &strAttrID, unsigned long nValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

#ifdef DVM_USE_MAP
	BOOL IsAllMap();
	void ResetDvmMap();
#endif
	CDvmValue* FindValueByID(const CString &strValueID, BOOL bUseHas=TRUE);

	CDvmValue* AddValue(const CString &strAttrID, const CString &strValue);
	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, const CString &strValue);
	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, const CString &strDataType, const CString &strValue);

	BOOL UpdateChildValue(CDvmValue *pSrcParentValue, BOOL bIsNew = FALSE);

	//2021-10-22  lijunqing
	void InitByValues(CExBaseList *pValues); 
	CString GetIDPath_Root_Dataset(const CString &strPathSp = _T("$"));

	//shaolei 2021-12-04
	BOOL GetValueByID(const CString &strValueID, CString &strValue);

	void InitValueByData(CDvmValue *pData);

};

//2022-5-13  lijunqing
CDvmValue* dvm_FindByID_Has(CExBaseList *pParent, const CString &strAttrID);
CDvmValue* dvm_FindByID_MmsAttr(CExBaseList *pParent, const CString &strAttrID);


//////////////////////////////////////////////////////////////////////////
//CDvmBrcb
class CDvmBrcbValue : public CDvmValue
{
public:
	CDvmBrcbValue();
	virtual ~CDvmBrcbValue();

	//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMBRCBVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDataKey();     }
	virtual CBaseObject* Clone();
};

//////////////////////////////////////////////////////////////////////////
//CDvmValueKeyMngr

#define VALUE_KEY_TEXT_MAX_LEN   20
#define VALUE_KEY_MAX_COUNT       40
class CDvmValueKeyMngr
{
public:
	CDvmValueKeyMngr();
	virtual ~CDvmValueKeyMngr();

	void InitValueKeyMngr(const CString &strFile);

	BOOL IsValueID(const CString &mmsID)
	{
#ifdef _UNICODE
		char *pszID = NULL;
		CString_to_char(mmsID, &pszID);
		BOOL bTrue = IsValueID(pszID);
		delete pszID;
		return bTrue;
#else
		for (long nIndex=0; nIndex<m_nKeyCount; nIndex++)
		{
			if (m_pszValueKey[nIndex][0] == 0)
			{
				break;
			}

            if (mmsID.Find((char*)(m_pszValueKey[nIndex]))  >= 0)
			{
				return TRUE;
			}
		}

		return FALSE;
#endif
	}

	BOOL IsValueID(char *mmsID)
	{
		for (long nIndex=0; nIndex<m_nKeyCount; nIndex++)
		{
			if (strstr(mmsID, m_pszValueKey[nIndex]) != NULL)
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	char* FindVarID(char *pszVarID)
	{
		char *pszFind = NULL;

		for (long nIndex=0; nIndex<m_nKeyCount; nIndex++)
		{
			if (strstr(pszVarID, m_pszValueKey[nIndex]) != NULL)
			{
				pszFind = m_pszValueKey[nIndex];
				break;
			}
		}

		return pszFind;
	}

protected:
	long m_nKeyCount;
	char m_pszValueKey[VALUE_KEY_MAX_COUNT][VALUE_KEY_TEXT_MAX_LEN];

public:
	CStringArray m_astrLdIDKey;
};
