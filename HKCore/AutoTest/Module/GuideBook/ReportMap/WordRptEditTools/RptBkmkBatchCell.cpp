//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptBkmkBatchCell.cpp  CRptBkmkBatchCell


#include "stdafx.h"
#include "RptBkmkBatchCell.h"

CRptBkmkBatchCell::CRptBkmkBatchCell()
{
	//��ʼ������
	m_pGbItem = NULL;
	m_pData = NULL;
	m_strPrecision;
	m_strDataAttr = _T("value");
	m_nRepeatIndex = 0;

	//��ʼ����Ա����
}

CRptBkmkBatchCell::~CRptBkmkBatchCell()
{
}

long CRptBkmkBatchCell::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptBkmkBatchCell::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CRptBkmkBatchAddXmlRWKeys *pXmlKeys = (CRptBkmkBatchAddXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CRptBkmkBatchCell::InitAfterRead()
{
}

