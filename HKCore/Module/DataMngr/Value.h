//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Value.h  CValue

#pragma once

#include "DataMngrGlobal.h"



class CValue : public CExBaseList  //CExBaseObject  //2015-3-17�޸�
{
public:
	CValue();
	virtual ~CValue();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	
	//���������л�
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

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
	void PutID(const CString &strID)
	{
		m_strID = strID;
	}

	void PutValue(const CString &strValue)
	{
		m_strValue = strValue;
	}

	void PutName(const CString &strName)
	{
		m_strName = strName;
	}
};

