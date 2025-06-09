#include "StdAfx.h"
#include "GbtDataInterface.h"
// #include "Set.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbtDataInterface::CGbtDataInterface(void)
{
	m_strName = g_sLangTxt_DataItfc/*_T("数据接口")*/;
}

CGbtDataInterface::~CGbtDataInterface(void)
{
}

long CGbtDataInterface::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	//CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataInterface::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	//CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	
	return 0;
}

long CGbtDataInterface::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);
	
	return 0;
}

CExBaseObject* CGbtDataInterface::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataScriptKey)
	{
		return new CGbtDataScript();
	}

	return NULL;
}

CExBaseObject* CGbtDataInterface::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GBTDATASCRIPT)
	{
		return new CGbtDataScript();
	}

	return NULL;
}

CBaseObject* CGbtDataInterface::Clone()
{
	CGbtDataInterface* pGbtDataInterface = new CGbtDataInterface();
	Copy(pGbtDataInterface);

	return pGbtDataInterface;
}



BOOL CGbtDataInterface::CanPaste(UINT nClassID)
{
	if (nClassID != GBCLASSID_GBTDATASCRIPT)
	{
		return FALSE;
	}

	return TRUE;
}

void CGbtDataInterface::InitByGbtDatas(CGbtDatas *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CGbtData *pData = NULL;
	CGbtDataScript *pDataScript = NULL;

	while (pos != NULL)
	{
		pData = (CGbtData *)pDatas->GetNext(pos);

		if (pData->IsGbtScriptObj())
		{
			pDataScript = new CGbtDataScript();
			pDataScript->InitGbtData(pData);
			AddNewChild(pDataScript);
		}
	}
}

