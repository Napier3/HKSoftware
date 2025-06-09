//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DataTypes.h  CDataTypes

#pragma once

#include "DataMngrGlobal.h"


#include "DataType.h"

class CDataTypes : public CExBaseList
{
public:
	CDataTypes();
	virtual ~CDataTypes();


//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATATYPES;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
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
	CDataType* AddNew2(const CString &strName, const CString &strID)
	{
		CDataType *pDataType = new CDataType();
		pDataType->m_strName = strName;
		pDataType->m_strID = strID;
		pDataType->SetParent(this);
		AddTail(pDataType);
		return pDataType;
	}

	BOOL Open(const CString &strFile, CXmlRWKeys *pXmlKeys);
};

