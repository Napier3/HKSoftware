//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmValues.h  CDvmValues

#pragma once

#include "DataMngrGlobal.h"

#include "DvmValue.h"

class CDvmValues : public CExBaseList
{
public:
	CDvmValues();
	virtual ~CDvmValues();


//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//��������
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

