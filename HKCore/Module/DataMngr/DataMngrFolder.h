//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DataMngrFolder.h  CDataMngrFolder

#pragma once

#include "DataMngrGlobal.h"


#include "ShortData.h"
#include "Values.h"

class CDataMngrFolder : public CExBaseList
{
public:
	CDataMngrFolder();
	virtual ~CDataMngrFolder();


//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATAMNGRFOLDER;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataMngrFolderKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
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
	CShortData* AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID, const CString &strValue, LONG nReserved,const CString &bstrFormat,const CString &bstrRemark);
	void ResetDatas();

// 	virtual BSTR GetXml();
// 	virtual void SetXml(BSTR strXml);
};

