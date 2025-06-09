#include "StdAfx.h"
#include "EpDeviceCmmConfig.h"

CEpDeviceCmmConfig::CEpDeviceCmmConfig(void)
{

	m_strName = "EpDeviceCmmConfig";
	m_strID = m_strName;


}

CEpDeviceCmmConfig::~CEpDeviceCmmConfig(void)
{
}

//基本方法
void CEpDeviceCmmConfig::Init()
{

}

long CEpDeviceCmmConfig::InitAfterSerialize()
{
	return 0;
}

//串行化
long CEpDeviceCmmConfig::BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff)
{
	return 0;
}

long CEpDeviceCmmConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


long CEpDeviceCmmConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}


//编辑
BOOL CEpDeviceCmmConfig::IsEqualOwn(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CEpDeviceCmmConfig::CopyOwn(CBaseObject* pDest)
{
	return FALSE;
}

CBaseObject* CEpDeviceCmmConfig::Clone()
{
	return NULL;
}


//创建子对象
CExBaseObject* CEpDeviceCmmConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

CExBaseObject* CEpDeviceCmmConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew = NULL;

	if (strClassID == CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strSerialKey)
	{
		pNew = new CEpCmmSerialConfig();
	}
	else if (strClassID == CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strNetKey)
	{
		pNew = new CEpCmmNetConfig();
	}
	else
	{

	}


	if (pNew != NULL)
	{
		pNew->m_strName = strClassID;
		pNew->m_strID = pNew->m_strName;
	}


	return pNew;
}


BOOL CEpDeviceCmmConfig::OpenPpTemplateXmlFile(const CString &strFile)
{
	return OpenXmlFile(strFile,  CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey, CEpCmmConfigXmlKeys::g_pXmlRWKeys);
}

long CEpDeviceCmmConfig::InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	return 0;
}

CExBaseObject* CEpDeviceCmmConfig::GetChildByClassID(UINT nClassID)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
	UINT nID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);
		nID = p->GetClassID();

		if (nClassID == nID)
		{
			pFind = p;
			break;
		}

		if (nID == EPCLASSID_NET_CONFIG)
		{
			pFind = ((CEpCmmNetConfig*)p)->GetChildByClassID(nClassID);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}