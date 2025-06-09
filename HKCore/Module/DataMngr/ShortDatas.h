//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ShortDatas.h  CShortDatas

#pragma once

#include "DataMngrGlobal.h"


#include "ShortData.h"
#include "Values.h"
#include "../MemBuffer/EquationBuffer.h"

class CShortDatas : public CExBaseList
{
public:
	CShortDatas();
	virtual ~CShortDatas();


//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CSHORTDATAS;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CShortDatasKey();     }
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
	void AppendValues( CValues *pValues);
	CShortData* AddNew()
	{
		CShortData *pData = new CShortData();
		pData->SetParent(this);
		AddTail(pData);
		return pData;
	}

	CValues* GetValues();
	CShortData* AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID, const CString &strValue, LONG nReserved,const CString &bstrFormat,const CString &bstrRemark, BOOL bAddSame=TRUE);
	void ResetDatas();

	void StringSerialize(CStringSerializeBuffer &oBinaryBuffer);
// 	virtual BSTR GetXml();
// 	virtual void SetXml(BSTR strXml);
	virtual void Parser(CEquationBuffer *pEquation);

	//2021-8-10  lijunqing
	void InitDatasValue(CShortDatas *pSrcDatas);

	//2021-10-13  lijunqing
	void SetDataValue(const CString &strID, const CString &strValue, BOOL bAddNew=TRUE);
};

