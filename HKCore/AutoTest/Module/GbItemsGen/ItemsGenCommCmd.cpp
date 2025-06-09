//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenCommCmd.cpp  CItemsGenCommCmd


#include "stdafx.h"
#include "ItemsGenCommCmd.h"
#include "ItemsGenDataMap.h"
#include "ItemsGenNode.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenCommCmd::CItemsGenCommCmd()
{
	//初始化属性
	m_nRptFillDs = 0;
	//初始化成员变量
}

CItemsGenCommCmd::~CItemsGenCommCmd()
{
}

long CItemsGenCommCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmdIDKey, oNode, m_strCmdID);
	xml_GetAttibuteValue(pXmlKeys->m_strRwOptrKey, oNode, m_strRwOptr);
	xml_GetAttibuteValue(pXmlKeys->m_strRptFillDsKey, oNode, m_nRptFillDs);
	return 0;
}

long CItemsGenCommCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmdIDKey, oElement, m_strCmdID);
	xml_SetAttributeValue(pXmlKeys->m_strRwOptrKey, oElement, m_strRwOptr);
	xml_SetAttributeValue(pXmlKeys->m_strRptFillDsKey, oElement, m_nRptFillDs);
	return 0;
}

long CItemsGenCommCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCmdID);
		BinarySerializeCalLen(oBinaryBuffer, m_strRwOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_nRptFillDs);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCmdID);
		BinarySerializeRead(oBinaryBuffer, m_strRwOptr);
		BinarySerializeCalLen(oBinaryBuffer, m_nRptFillDs);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCmdID);
		BinarySerializeWrite(oBinaryBuffer, m_strRwOptr);
		BinarySerializeWrite(oBinaryBuffer, m_nRptFillDs);
	}
	return 0;
}

void CItemsGenCommCmd::InitAfterRead()
{
}

BOOL CItemsGenCommCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CItemsGenCommCmd *p = (CItemsGenCommCmd*)pObj;

	if(m_strCmdID != p->m_strCmdID)
	{
		return FALSE;
	}

	if(m_strRwOptr != p->m_strRwOptr)
	{
		return FALSE;
	}

	if (m_nRptFillDs != p->m_nRptFillDs)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsGenCommCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CItemsGenCommCmd *p = (CItemsGenCommCmd*)pDest;

	p->m_strCmdID = m_strCmdID;
	p->m_strRwOptr = m_strRwOptr;
	p->m_nRptFillDs = m_nRptFillDs;
	return TRUE;
}

CBaseObject* CItemsGenCommCmd::Clone()
{
	CItemsGenCommCmd *p = new CItemsGenCommCmd();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenCommCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenCommCmd *p = new CItemsGenCommCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenCommCmd::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATASET)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenCommCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCItemsGenDataMapKey)
	{
		pNew = new CItemsGenDataMap();
	}

	if (strClassID == pXmlKeys->m_strCItemsGenDatasetKey)
	{
		pNew = new CItemsGenDataset();
	}

	return pNew;
}

CExBaseObject* CItemsGenCommCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP)
	{
		pNew = new CItemsGenDataMap();
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDATASET)
	{
		pNew = new CItemsGenDataset();
	}

	return pNew;
}

void CItemsGenCommCmd::InitDataMapsByInterface()
{
	CItemsGenNode *pNode = (CItemsGenNode *)GetParent();
	CItemsGenInterface *pInterface = pNode->GetGenInterface();

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		//此处子对象，应当还包括CItemsGenDataset
		CItemsGenDataMap *pDataMap = (CItemsGenDataMap *)GetNext(pos);   

		if (pDataMap->m_strID_Map.IsEmpty())
		{
			continue;
		}

		CItemsGenData *pData = (CItemsGenData *)pInterface->FindByID(pDataMap->m_strID_Map);

		if (pData != NULL)
		{
			pDataMap->m_strValue = pData->m_strValue;
		}
		else
		{
			pDataMap->InitParaByInterface_Expression(pInterface);
		}
	}
}