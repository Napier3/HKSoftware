#pragma once

//�������� ��������ӳ���ļ�

#include "RptMapBase.h"

class CRptMapRepeat : public CRptMapBase
{
public:
	CRptMapRepeat(void);
	virtual ~CRptMapRepeat(void);

//����
public:
	long m_nIndex;

//�����ӿ�
public:

//��д���෽��
public:
	virtual UINT GetClassID() {        return RPTCLASSID_RPTMAPREPEAT;             }     
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strMapRepeatKey;     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CBaseObject* Clone();//						{		return NULL;						}
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	CString GetRptMapRepeatName();
};

//CExBaseObject* _FindTheItemByID(CExBaseList *pList, CString strID);