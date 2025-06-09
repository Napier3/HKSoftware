//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmValues.h  CDvmValues

#pragma once

#include "DataMngrGlobal.h"

#include "DvmValue.h"

class CDvmValues : public CExBaseList
{
public:
	CDvmValues();
	virtual ~CDvmValues();


//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDVMVALUES;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CValuesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//其他方法
public:
	CDvmValue* AddValue(const CString &strID, const CString &strValue);
	CDvmValue* AddNew(const CString &strID=_T(""), const CString &strValue=_T(""))
	{
		return AddValue(strID, strValue);
	}

	CDvmValue* AddValue(const CString &strID, const CString &strName, const CString &strValue);
	CDvmValue* AddNew(const CString &strID=_T(""), const CString &strName=_T(""), const CString &strValue=_T(""))
	{
		return AddValue(strID, strName, strValue);
	}

	void SetValuesByDatas(CDvmValues *pValues);
	CString GetDatasString();
	long SetValuesByString(const CString &strValues);
    //long SetValuesByGroup(CDataGroup *pGroup);
	BOOL SetValue(const CString &strID, const CString &strValue);
	
	BOOL GetValue(const CString &strID, CString &strValue);
	BOOL GetValue(const CString &strID, double &dValue);
	BOOL GetValue(const CString &strID, long &nValue);
};

