#pragma once

//�������� ���鱨�����ݶ����Ӷ���ΪCRptBkmk
//���������������Ҫ���뱨���һ�����ݣ��������ݾ���

#include "RptBkmk.h"

#define _RPTDATA_PRECISION_INIT -1
class CGbItemBase;

class CRptData :	public CExBaseList
{
public:
	CRptData(void);
	CRptData(const CString  &strName, const CString  &strID, const CString  &strPrecision);
	virtual ~CRptData(void);

//����
protected:
	long m_nPrecision;										//���ݵľ��ȣ�������д����ʱʹ��

public:
	CString m_strPrecision;
	CString m_strDataType;
	long m_nDataFill;

//�����ӿ�
public:
//	CExBaseObject* AddNew();					//�½���ǩ����,�����ض��Ĺ����Զ�����IRptBkmk�ı�ǩ
	CExBaseObject* AddNew2(const CString  strRptBkmk);
	void SetPrecision(long nPrecision);
	void SetPrecision(const CString &strPrecision)	;
	long GetPrecision();//												{		return m_nPrecision;					}

	//��д���෽��
public:
	virtual UINT GetClassID()									{        return RPTCLASSID_RPTDATA;             }
	virtual BSTR GetXmlElementKey()				{      return CGbXMLKeys::g_pGbXMLKeys->m_strDataKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

	void ClearDWData();
	CGbItemBase* GetParentItem();    //��ȡ����Ŀ
};
