#pragma once

//�������� ���鱨����������Ӷ���ΪCRptBkmk

#include "RptBkmk.h"

#define RPT_AREA_TYPE_ADJUST     _T("adjust")  
#define RPT_AREA_TYPE_MGRP        _T("mgrp")

class CRptArea :	public CExBaseList
{
public:
	CRptArea(void);
	virtual ~CRptArea(void);

//����
public:
	CRptBkmk *m_pBkmkBegin;
	CRptBkmk *m_pBkmkEnd;
	CString m_strAreaType;   //�����ǩ����  0=������������ǩ��1=��ͨ������ϲ���ǩ

//�����ӿ�
public:
// 	CExBaseObject* AddNew();					//�½���ǩ����,�����ض��Ĺ����Զ�����IRptBkmk�ı�ǩ
// 	CExBaseObject* AddNew2(const CString  strRptBkmk);

	//��д���෽��
public:
	virtual UINT GetClassID()									{        return RPTCLASSID_RPTAREA;             }
	virtual BSTR GetXmlElementKey()				{      return CGbXMLKeys::g_pGbXMLKeys->m_strAreaKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CBaseObject* Clone();

	virtual void InitAfterRead();
	void ClearDWData();
	virtual BOOL CopyOwn(CBaseObject* pDest);

	//�����ǩ����  0=������������ǩ��1=��ͨ������ϲ���ǩ
	BOOL IsRptAdjustArea();
	BOOL IsRptMgrpCmbArea();
	void SetRptAdjustArea();
	void SetRptMgrpCmbArea();
	void SetRptAreaType(const CString &strType);

	void DeleteArea();
	void InitAreaBkmkID(CRptBkmk *pBkmk, DWORD &dwBkmkIndex);
};
