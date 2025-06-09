#include "StdAfx.h"
#include "CmmOnConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCmmOnConnect::CCmmOnConnect(void)
{
	
}

CCmmOnConnect::~CCmmOnConnect(void)
{
}



//´®ÐÐ»¯
long CCmmOnConnect::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CCmmOnConnect::XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys)
{
	m_strText = oNode.Gettext();
	m_strText.Trim();

	m_strID = m_strText;
	m_strName = m_strText;

	return 0;
}

long CCmmOnConnect::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	try {
// 		MSXML2::IXMLDOMNodePtr oNode;
// 
// 		oNode = oXMLDoc->createCDATASection(_T(""));
// 		ASSERT( oNode != NULL);
// 		oElement->appendChild(oNode);
//
//		oNode->put_text((_bstr_t)m_strText);
		oElement.put_text(m_strText);
	} 
	catch(...)
	{

	}

	return 0;
}


BOOL CCmmOnConnect::CopyOwn(CBaseObject* pDest)
{
	((CCmmOnConnect*)pDest)->m_strText = m_strText;
	((CCmmOnConnect*)pDest)->m_strName = m_strName;
	((CCmmOnConnect*)pDest)->m_strID = m_strID;

	return TRUE;
}

CBaseObject* CCmmOnConnect::Clone()
{
	CCmmOnConnect *pNew = new CCmmOnConnect();

	Copy(pNew);

	return pNew;
}
