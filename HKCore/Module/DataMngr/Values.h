//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Values.h  CValues

#pragma once

#include "DataMngrGlobal.h"

//2021-5-18  shaolei,lijunqing 
//AtsWorkBench��������61850�Ĵ�����CValue���ڳ�ͻ�����±������
//��˽�CValue��ΪCXValue��ͬʱ���ּ�����
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


//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//��������
public:
	CValue* AddValue(const CString &strID, const CString &strValue);
	CValue* AddNew(const CString &strID=_T(""), const CString &strValue=_T(""))
	{
		return AddValue(strID, strValue);
	}

	CValue* AddValue(const CString &strID, const CString &strName, const CString &strValue);
	CValue* AddNew(const CString &strID/*=_T("")*/, const CString &strName/*=_T("")*/, const CString &strValue/*=_T("")*/)
	{
		//2024-3-10  lijunqing �ϲ����룬���ִ˺����� AddNew(const CString &strID=_T(""), const CString &strValue=_T("")) ���г�ͻ��
		//���ע�͵�ȱʡֵ
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

