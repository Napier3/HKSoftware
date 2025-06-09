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

	CString  m_strDefaultValue;   //shaolei  2022-12-1
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

	CString m_strTime;//time属性

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	void XmlWriteOwn_Value(CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	void XmlReadOwn_Value(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	BOOL IsEqualOwn_Value(CBaseObject* pObj);   //value属性，根据data-type进行比较。

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL HasValueID(const CString &strValueID);
	BOOL HasValue(const CString &strValueID, const CString &strValue);
	BOOL HasValueEx(const CString &strValueID, const CString &strValue);
	BOOL HasValueHasStr(const CString &strValueID, const CString &strValue);
	BOOL HasValueHasNoStr(const CString &strValueID, const CString &strValue);
	//判断子对象是否strValueID == strValue的。有返回子对象。shaolei 2021-12-04
	CDvmValue* HasValueEx_Child(const CString &strValueID, const CString &strValue);
	CDvmValue* HasValueHasStr_Child(const CString &strValueID, const CString &strValue);
	CDvmValue* HasValueHasNoStr_Child(const CString &strValueID, const CString &strValue);
	
	CString GetAttrValue(const CString &strValueID)	{	return GetValueByID(strValueID);	}
	CString FindTag(const CString &strValueID)		{	return GetValueByID(strValueID);	}
	

	//xxy 20181126	
	CString GetValueByID(const CString &strValueID, BOOL bUseHas=TRUE);
	CString GetValueByID(BSTR strValueID, BOOL bUseHas=TRUE);

	BOOL GetValueByID(const CString &strValueID, CString &strValue, BOOL bUseHas=TRUE);
	BOOL GetValueByID(const CString &strValueID, long &nValue);
	BOOL GetValueByID(const CString &strValueID, DWORD &nValue);
// 	BOOL GetValueByID(const CString &strValueID, BOOL &bValue);
	BOOL GetValueByID(const CString &strValueID, SYSTEMTIME &tmValue);
	BOOL GetValueByID(const CString &strValueID, float &fValue);

	BOOL GetValueByID(BSTR &bstrValueID, CString &strValue, BOOL bUseHas=TRUE);
	BOOL GetValueByID(BSTR &bstrValueID, long &nValue);
// 	BOOL GetValueByID(BSTR &bstrValueID, BOOL &bValue);
	BOOL GetValueByID(BSTR &bstrValueID, SYSTEMTIME &tmValue);
	BOOL GetValueByID(BSTR &bstrValueID, float &fValue);

	CDvmValue* AddValue(const CString &strAttrID, const CString &strValue);
	CDvmValue* AddValue2(const CString &strAttrID, const CString &strValue, const CString &strDataType);
	CDvmValue* AddValue(const CString &strAttrID, long nValue);
	CDvmValue* AddValue(const CString &strAttrID, BOOL bValue);
	CDvmValue* AddValue(const CString &strAttrID, SYSTEMTIME tmValue);

	CDvmValue* AddValue(BSTR &bstrAttrID, const CString &strValue);
	CDvmValue* AddValue(BSTR &bstrAttrID, long nValue);
	CDvmValue* AddValue(BSTR &bstrAttrID, BOOL bValue);
	CDvmValue* AddValue(BSTR &bstrAttrID, SYSTEMTIME tmValue);

	BOOL SetAttr(const CString &strAttrID, const CString &strValue);
	BOOL SetAttr(const CString &strAttrID, long &nValue);
	BOOL SetAttr(BSTR &bstrAttrID, const CString &strValue);
	BOOL SetAttr(BSTR &bstrAttrID, long &nValue);

	BOOL SetValue(const CString &strAttrID, const CString &strValue);
	BOOL SetValue(const CString &strAttrID, long nValue);
	BOOL SetValue(const CString &strAttrID, DWORD nValue);

	BOOL SetValue_Mms(const CString &strAttrID, const CString &strValue);
	BOOL SetValue_Mms(const CString &strAttrID, long nValue);
	BOOL SetValue_Mms(const CString &strAttrID, unsigned long nValue);
	BOOL SetValue_Mms(const CString &strAttrID, float fValue, long nDecimal=-1);
	BOOL SetValue_Mms(const CString &strAttrID, double dValue, long nDecimal=-1);
	BOOL SetValue_Mms_Hex(const CString &strAttrID, unsigned long nValue);

	void SetIndex(long nIndex)	{		m_nIndex = nIndex;	}
	long GetIndex()				{		return m_nIndex;	}
	CDvmValue* AddNewValue(CDvmValue *pSrc = NULL);
	BOOL GetTime(CString &strTime);
	CString GetTime();

	CDvmValue* FindByID_Has(const CString &strDataID);
	CDvmValue* FindByID_MmsAttr(const CString &strAttrID);

	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, long &nValue);
	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, const CString &strValue);
	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, const CString &strDataType, const CString &strValue);
	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, BOOL bValue);
	CDvmValue* AddValue(const CString &strName, const CString &strAttrID, SYSTEMTIME tmValue);

	CDvmValue* AddValue(const CString &strName, BSTR &bstrAttrID, long &nValue);
	CDvmValue* AddValue(const CString &strName, BSTR &bstrAttrID, BOOL bValue);
	CDvmValue* AddValue(const CString &strName, BSTR &bstrAttrID, SYSTEMTIME tmValue);
	CDvmValue* AddValue(const CString &strName, BSTR &bstrAttrID, const CString &strValue);

	BOOL GetValueByID(const CString &strAttrID, long &nValue, CString &strName);
	BOOL GetValueByID(BSTR &bstrAttrID, long &nValue, CString &strName);

#ifdef DVM_USE_MAP
	BOOL IsAllMap();
	void ResetDvmMap();
	void ResetDvmMapEx();
#endif
	CDvmValue* FindValueByID(const CString &strValueID, BOOL bUseHas=TRUE);

#ifdef _DVM_VALUE_USE_CHAR_
	long ValueToLong();
#else
#endif

	//shaolei 20210913
	BOOL GetChildValueByID(const CString &strID, CString &strValue);
	BOOL GetChildValueByID(const CString &strID, long &nValue);
	BOOL GetChildValueByID(const CString &strID, double &dValue);
	BOOL UpdateChildValue(CDvmData *pSrcData, BOOL bIsNew = FALSE);

	virtual BOOL UpdateOwn(CBaseObject* pDest);//zhouhj 20220404 增加用于更新当前值

	void ResetData();

	//2021-10-22  lijunqing
	void InitByValues(CExBaseList *pValues); 
	CString GetIDPath_Root_Dataset(const CString &strPathSp = _T("$"));
	//add by shaolei 20220518
	void InitDataTypeByGsData(const CString &strDataType);

public:
	CDvmValue* FindDataObjValueByID_Has(const CString &strIDPath);
	void InitValueByData(CDvmData *pData, BOOL bSetMinMax);
	BOOL CmpDataType(CDvmData *pDataSrc);
	BOOL CmpDataType(const CString &strDataType);
	CExBaseObject* FindValueObject(CExBaseList *pList);

	//返回除$t  $q之外的第一个pDvmData子对象
	CDvmValue* GetDataValue();

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
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

CString dvm_GetTimeString(double dTime);
BOOL dvm_CmpDvmData(CDvmData *pData1, CDvmData *pData2);
BOOL dvm_CmpDvmDataValue(CDvmValue *pValue1, CDvmValue *pValue2);

BOOL XDS_InStringDataPath(const CString &strText);
