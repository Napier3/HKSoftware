//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBkmkBatchCell.cpp  CRptBkmkBatchCell


#include "stdafx.h"
#include "RptBkmkBatchCell.h"

CRptBkmkBatchCell::CRptBkmkBatchCell()
{
	//初始化属性
	m_pGbItem = NULL;
	m_pData = NULL;
	m_strPrecision;
	m_strDataAttr = _T("value");
	m_nRepeatIndex = 0;

	//初始化成员变量
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

