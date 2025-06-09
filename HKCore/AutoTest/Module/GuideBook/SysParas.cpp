#include "StdAfx.h"
#include "SysParas.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSysParas::CSysParas()
{
	m_strName = g_sLangTxt_TestPara/*L"测试参数"*/;

	//m_pDatas = new CShortDatas();
}

CSysParas::~CSysParas(void)
{
}

long CSysParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataSet::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CSysParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataSet::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}


long CSysParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataSet::SerializeOwn(oBinaryBuffer);

	return 0;
}

BOOL CSysParas::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(pDest == this)
		return TRUE;

	CDataSet::CopyOwn(pDest);

	CSysParas* pSysParas = (CSysParas*)pDest;
	
	return TRUE;
}

CBaseObject* CSysParas::Clone()
{
	CSysParas* pSysParas = new CSysParas();
	Copy(pSysParas);

	return pSysParas;
}


BOOL CSysParas::CanPaste(UINT nClassID)
{
	if (nClassID == GBCLASSID_DATAOBJ)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSysParas::FindTimeParas(CExBaseList *pTimeList)
{
	ASSERT(pTimeList != NULL && pTimeList->IsBaseList());

	CDataObj *pChild = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pChild = (CDataObj *)GetNext(pos);
	
		if (pChild != NULL && pChild->m_strUnit == g_strSysParaChild_unitTime)
		{
			pTimeList->AddTail(pChild);
		}
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
CTestParas::CTestParas()
{
	m_strName = g_sLangTxt_TestPara/*L"测试参数"*/;
}

CBaseObject* CTestParas::Clone()
{
	CTestParas *pNew = new CTestParas();
	Copy(pNew);
	return pNew;
}

