//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DataTypeValue.h  CDataTypeValue

#pragma once

#include "DataMngrGlobal.h"



class CDataTypeValue : public CExBaseObject
{
public:
	CDataTypeValue();
	virtual ~CDataTypeValue();


	CString  m_strIndex;
//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATATYPEVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataTypeValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	long GetIndex()
	{
		return CString_To_long(m_strIndex);
	}
	void SetIndex(long nIndex)
	{
		m_strIndex.Format(_T("%d"), nIndex);
	}
};

