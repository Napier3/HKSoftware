//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptBatchItemMap.h  CRptBatchItemMap

#pragma once

#include "RptBkmkBatchAddGlobal.h"



class CRptBatchItemMap : public CExBaseObject
{
public:
	CRptBatchItemMap();
	virtual ~CRptBatchItemMap();


	long  m_nItemIndex;
	long  m_nMapIndex;

	CExBaseObject *m_pItemRef;
//���غ���
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHITEMMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchItemMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void ClearMap()
	{
		m_nMapIndex = -1;
		m_nItemIndex = -1;
		m_strID.Empty();
		m_strName.Empty();
	}

	BOOL IsMaped()	{	return m_strID.GetLength() > 0;	}
};

