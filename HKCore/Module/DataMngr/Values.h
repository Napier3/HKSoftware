//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Values.h  CValues

#pragma once

#include "DataMngrGlobal.h"

//2021-5-18  shaolei,lijunqing 
//AtsWorkBench：可能是61850的代码与CValue存在冲突，导致编译出错
//因此将CValue改为CXValue，同时保持兼容性
#ifdef _use_cxvalue_
#include "XValue.h"
#else
#include "Value.h"
#endif

class CValues : public CExBaseList
{
public:
	CValues();
	virtual ~CValues();


//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CVALUES;   }
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
	CValue* AddValue(const CString &strID, const CString &strValue);
	CValue* AddNew(const CString &strID=_T(""), const CString &strValue=_T(""))
	{
		return AddValue(strID, strValue);
	}

	CValue* AddValue(const CString &strID, const CString &strName, const CString &strValue);
	CValue* AddNew(const CString &strID/*=_T("")*/, const CString &strName/*=_T("")*/, const CString &strValue/*=_T("")*/)
	{
		//2024-3-10  lijunqing 合并代码，发现此函数与 AddNew(const CString &strID=_T(""), const CString &strValue=_T("")) 是有冲突的
		//因此注释掉缺省值
		return AddValue(strID, strName, strValue);
	}

	void SetValuesByDatas(CValues *pValues);
	CString GetDatasString();
	long SetValuesByString(const CString &strValues);
    //long SetValuesByGroup(CDataGroup *pGroup);
	BOOL SetValue(const CString &strID, const CString &strValue);
	
	BOOL GetValue(const CString &strID, CString &strValue);
	BOOL GetValue(const CString &strID, double &dValue);
	BOOL GetValue(const CString &strID, long &nValue);
};

