#include "StdAfx.h"
#include "GbtDataInterfaces.h"
#include "../XLanguageResourceAts.h"
/*
<data-interfaces>   取代device-model
	<datas/>
		<data   …………/>
	</datas>
	<data-interface name="" prepare" id=" "> 
		<data-script data-id=" ">
			<key name=" " id=" ">
		</data-script>
	</data-interface>
</data-interfaces>

*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbtDataInterfaces::CGbtDataInterfaces(void)
{
	m_strName = g_sLangTxt_DataItfcMng/*_T("数据接口管理")*/;
	m_strID = _T("_datainterfaces");
	m_pGbtDatas = NULL;
}

CGbtDataInterfaces::~CGbtDataInterfaces(void)
{
}

long CGbtDataInterfaces::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataInterfaces::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	return 0;
}

long CGbtDataInterfaces::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	
	
	return 0;
}

CExBaseObject* CGbtDataInterfaces::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDataInterfaceKey)
	{
		return new CGbtDataInterface();
	}

	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strGbtDatasKey)
	{
		return new CGbtDatas();
	}

	return NULL;
}

CExBaseObject* CGbtDataInterfaces::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GBTDATAINTERFACE)
	{
		return new CGbtDataInterface();
	}

	if (nClassID == GBCLASSID_GBTDATAS)
	{
		return new CGbtDatas();
	}

	return NULL;
}

CBaseObject* CGbtDataInterfaces::Clone()
{
	CGbtDataInterfaces* pGbtDataInterfaces = new CGbtDataInterfaces();
	Copy(pGbtDataInterfaces);

	return pGbtDataInterfaces;
}



BOOL CGbtDataInterfaces::CanPaste(UINT nClassID)
{
	if (nClassID != GBCLASSID_GBTDATAINTERFACE)
	{
		return FALSE;
	}

	return TRUE;
}

void CGbtDataInterfaces::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch(nClassID)
		{
		case GBCLASSID_GBTDATAS:
			m_pGbtDatas = (CGbtDatas*)p;
			break;
		default:
			break;
		}
	}

	if (m_pGbtDatas == NULL)
	{
		m_pGbtDatas = new CGbtDatas();
		AddNewChild(m_pGbtDatas);
	}

	BringToHead(m_pGbtDatas);
}

void CGbtDataInterfaces::SetGbtDataInterfaceCount(long nCount)
{
	POS pos = Find(m_pGbtDatas);
	RemoveAt(pos);
	DeleteAll();
	AddNewChild(m_pGbtDatas);

	long nIndex = 0;
	CGbtDataInterface *pNew = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNew = new CGbtDataInterface();
		pNew->InitByGbtDatas(m_pGbtDatas);
		AddNewChild(pNew);
	}
}

BOOL CGbtDataInterfaces::IsBatchGbtDataMode()
{
	return m_pGbtDatas->IsBatchGbtDataMode();
}

CGbtDatas* CGbtDataInterfaces::CreateGbtDatas(CExBaseList *pDatas)
{
	if (m_pGbtDatas == NULL)
	{
		m_pGbtDatas = new CGbtDatas();
		AddNewChild(m_pGbtDatas);
	}
	
	if (pDatas != NULL)
	{
		m_pGbtDatas->CreateGbtDatas(pDatas);
	}

	return m_pGbtDatas;
}

CGbtDataInterface* CGbtDataInterfaces::CreateGbtDataInterface()
{
	CGbtDataInterface *pGbtDataInterface = new CGbtDataInterface();
	AddNewChild(pGbtDataInterface);
	pGbtDataInterface->InitByGbtDatas(m_pGbtDatas);

	return pGbtDataInterface;
}


