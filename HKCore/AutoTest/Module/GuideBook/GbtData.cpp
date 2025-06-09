#include "StdAfx.h"
#include "GbtData.h"
#include "GbDataTypeMngr.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbtData::CGbtData(void)
{
	m_strName = g_sLangTxt_DataItfcVari/*_T("数据接口变量")*/;
}

CGbtData::~CGbtData(void)
{
}

long CGbtData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataObj::XmlReadOwn(oNode, pXmlRWKeys);

// 	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
// 
// 	if (m_strName.GetLength() == 0)
// 	{
// 		m_strName = m_strID;
// 	}

	return 0;
}

long CGbtData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataObj::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

//	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	
	return 0;
}

long CGbtData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataObj::SerializeOwn(oBinaryBuffer);

	
	
	return 0;
}

CBaseObject* CGbtData::Clone()
{
	CGbtData* pGbtData = new CGbtData();
	Copy(pGbtData);

	return pGbtData;
}

void CGbtData::InitAfterRead()
{
	if (m_strDataType.GetLength() == 0)
	{
		m_strDataType = g_strGbtDataObjTypeID_Script;
	}
}

BOOL CGbtData::IsGbtScriptObj()
{
	return m_strDataType == g_strGbtDataObjTypeID_Script;
}

BOOL CGbtData::IsBatchObj()
{
	return m_strDataType == g_strGbtDataObjTypeID_Batch;
}

CDataTypeValue* CGbtData::GetDataTypeValue()
{
	CDataType *pDataType = CGbDataTypeMngr::GetGbtDataObjDataType();
	CDataTypeValue *pFind = NULL;

	pFind = (CDataTypeValue*)pDataType->FindByID(m_strDataType);

	if (pFind == NULL)
	{
		m_strDataType = g_strGbtDataObjTypeID_Script;
		pFind = (CDataTypeValue*)pDataType->FindByID(m_strDataType);
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////

static const CString g_strGbtDatasName = _T("数据接口变量定义");

CGbtDatas::CGbtDatas(void)
{
	m_strName = g_sLangTxt_DataVariousDefin/*g_strGbtDatasName*/;
	m_strID = _T("DIVars");
}

CGbtDatas::~CGbtDatas(void)
{
}


long CGbtDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataSet::SerializeOwn(oBinaryBuffer);



	return 0;
}

long CGbtDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataSet::XmlReadOwn(oNode, pXmlRWKeys);

	// 	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;
	// 
	// 	if (m_strName.GetLength() == 0)
	// 	{
	// 		m_strName = m_strID;
	// 	}

	return 0;
}

long CGbtDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataSet::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	//	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;


	return 0;
}


CExBaseObject* CGbtDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataKey)
	{
		return new CGbtData();
	}

	return NULL;
}

CExBaseObject* CGbtDatas::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GBTDATA)
	{
		return new CGbtData();
	}

	return NULL;
}


CBaseObject* CGbtDatas::Clone()
{
	CGbtDatas* pGbtData = new CGbtDatas();
	Copy(pGbtData);

	return pGbtData;
}

BOOL CGbtDatas::CanPaste(UINT nClassID)
{
	if (nClassID != GBCLASSID_GBTDATA)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbtDatas::IsBatchGbtDataMode()
{
	POS pos = GetHeadPosition();
	CGbtData *pGbtData = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pGbtData = (CGbtData *)GetNext(pos);

		if (pGbtData->IsBatchObj())
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

void CGbtDatas::CreateGbtDatas(CExBaseList *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CDataObj *pData = NULL;
	CGbtData *pNew = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)pDatas->GetNext(pos);
		pNew = new CGbtData();
		pData->CopyOwn(pNew);
		pNew->m_strDataType = g_strGbtDataObjTypeID_Script;
		AddNewChild(pNew);
	}
}

