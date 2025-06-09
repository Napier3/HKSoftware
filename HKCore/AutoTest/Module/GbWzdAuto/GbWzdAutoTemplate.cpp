//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbWzdAutoTemplate.cpp  CGbWzdAutoTemplate


#include "stdafx.h"
#include "GbWzdAutoTemplate.h"

CGbWzdAutoTemplate::CGbWzdAutoTemplate()
{
	//初始化属性
	m_nBinOffset = 0;
	m_nBoutOffset = 0;
	m_nCnt_Bin = 0;
	m_nCnt_Bout = 0;

	//初始化成员变量
}

CGbWzdAutoTemplate::~CGbWzdAutoTemplate()
{
}

long CGbWzdAutoTemplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strGbxml_FileKey, oNode, m_strGbxmlFile);
	xml_GetAttibuteValue(pXmlKeys->m_strBin_OffsetKey, oNode, m_nBinOffset);
	xml_GetAttibuteValue(pXmlKeys->m_strBout_OffsetKey, oNode, m_nBoutOffset);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strDateKey, oNode, m_strDate);
	xml_GetAttibuteValue(pXmlKeys->m_strCnt_BinKey, oNode, m_nCnt_Bin);
	xml_GetAttibuteValue(pXmlKeys->m_strCnt_BoutKey, oNode, m_nCnt_Bout);
	return 0;
}

long CGbWzdAutoTemplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strGbxml_FileKey, oElement, m_strGbxmlFile);
	xml_SetAttributeValue(pXmlKeys->m_strBin_OffsetKey, oElement, m_nBinOffset);
	xml_SetAttributeValue(pXmlKeys->m_strBout_OffsetKey, oElement, m_nBoutOffset);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strDateKey, oElement, m_strDate);
	xml_SetAttributeValue(pXmlKeys->m_strCnt_BinKey, oElement, m_nCnt_Bin);
	xml_SetAttributeValue(pXmlKeys->m_strCnt_BoutKey, oElement, m_nCnt_Bout);
	return 0;
}

long CGbWzdAutoTemplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_nBinOffset);
		BinarySerializeCalLen(oBinaryBuffer, m_nBoutOffset);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strDate);
		BinarySerializeCalLen(oBinaryBuffer, m_nCnt_Bin);
		BinarySerializeCalLen(oBinaryBuffer, m_nCnt_Bout);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeRead(oBinaryBuffer, m_nBinOffset);
		BinarySerializeRead(oBinaryBuffer, m_nBoutOffset);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strDate);
		BinarySerializeRead(oBinaryBuffer, m_nCnt_Bin);
		BinarySerializeRead(oBinaryBuffer, m_nCnt_Bout);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strGbxmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_nBinOffset);
		BinarySerializeWrite(oBinaryBuffer, m_nBoutOffset);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strDate);
		BinarySerializeWrite(oBinaryBuffer, m_nCnt_Bin);
		BinarySerializeWrite(oBinaryBuffer, m_nCnt_Bout);
	}
	return 0;
}

void CGbWzdAutoTemplate::InitAfterRead()
{

}

BOOL CGbWzdAutoTemplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdAutoTemplate *p = (CGbWzdAutoTemplate*)pObj;

	if(m_strGbxmlFile != p->m_strGbxmlFile)
	{
		return FALSE;
	}

	if(m_nBinOffset != p->m_nBinOffset)
	{
		return FALSE;
	}

	if(m_nBoutOffset != p->m_nBoutOffset)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strDate != p->m_strDate)
	{
		return FALSE;
	}

	if(m_nCnt_Bin != p->m_nCnt_Bin)
	{
		return FALSE;
	}

	if(m_nCnt_Bout != p->m_nCnt_Bout)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdAutoTemplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CGbWzdAutoTemplate *p = (CGbWzdAutoTemplate*)pDest;

	p->m_strGbxmlFile = m_strGbxmlFile;
	p->m_nBinOffset = m_nBinOffset;
	p->m_nBoutOffset = m_nBoutOffset;
	p->m_strVersion = m_strVersion;
	p->m_strDate = m_strDate;
	p->m_nCnt_Bin = m_nCnt_Bin;
	p->m_nCnt_Bout = m_nCnt_Bout;
	return TRUE;
}

CBaseObject* CGbWzdAutoTemplate::Clone()
{
	CGbWzdAutoTemplate *p = new CGbWzdAutoTemplate();
	Copy(p);
	return p;
}

BOOL CGbWzdAutoTemplate::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CGbWzdAutoTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbXMLKeys *pXmlKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == CGbXMLKeys::CDvmDatasetMapKey())
	{
		pNew = new CDvmDatasetMap;
	}

	return pNew;
}

CExBaseObject* CGbWzdAutoTemplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DMPCLASSID_CDVMDATASETMAP)
	{
		pNew = new CDvmDatasetMap;
	}

	return pNew;
}

void CGbWzdAutoTemplate::InitDvmStand_Dataset(CExBaseList *pDataset)
{
	CDvmDatasetMap *pFind = FindDvmDatasetMap(pDataset->m_strID);

	if (pFind == NULL)
	{
		return;
	}

	POS pos = pFind->GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	POS posData = pDataset->GetHeadPosition();
	CExBaseObject *pData = NULL;

	while (pos != NULL && posData != NULL)
	{
		pDataMap = (CDvmDataMap *)pFind->GetNext(pos);
		pData = pDataset->GetNext(posData);
		pDataMap->m_strName = pData->m_strName;
		pDataMap->m_strID = pData->m_strID;
		pDataMap->m_pStand = pData;
	}
}

void CGbWzdAutoTemplate::InitDvmMaps_Dataset(CExBaseList *pDataset)
{
	CDvmDatasetMap *pFind = FindDvmDatasetMap(pDataset->m_strID);

	if (pFind == NULL)
	{
		return;
	}

	POS pos = pFind->GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	CExBaseObject *pData = NULL;

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)pFind->GetNext(pos);
		pDataMap->m_pMap = pDataset->FindByID(pDataMap->m_strMapID);

		if (pDataMap->m_pMap == NULL)
		{
			pDataMap->m_pMap = pDataset->FindByName(pDataMap->m_strMapName);
		}
	}
}
CDvmDatasetMap* CGbWzdAutoTemplate::FindDvmDatasetMap(const CString &strDatasetID)
{
	CDvmDatasetMap *p = (CDvmDatasetMap*)FindByID(strDatasetID);

	if (p != NULL)
	{
		ASSERT(p->GetClassID() == DMPCLASSID_CDVMDATASETMAP);

		if (p->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
		{
			p = NULL;
		}
	}

	return p;
}

void CGbWzdAutoTemplate::InitDvm_Stand(CExBaseList *pDsList, UINT nDatasetClassID)
{
	POS pos = pDsList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDsList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == nDatasetClassID)
		{
			InitDvmStand_Dataset((CExBaseList*)p);
		}
		else 
		{
			if (p->IsBaseList(nClassID))
			{
				InitDvm_Stand((CExBaseList*)p, nDatasetClassID);
			}
		}
	}
}

void CGbWzdAutoTemplate::InitDvm_Maps(CExBaseList *pDsList, UINT nDatasetClassID)
{
	POS pos = pDsList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDsList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == nDatasetClassID)
		{
			InitDvmMaps_Dataset((CExBaseList*)p);
		}
		else 
		{
			if (p->IsBaseList(nClassID))
			{
				InitDvm_Maps((CExBaseList*)p, nDatasetClassID);
			}
		}
	}
}

void CGbWzdAutoTemplate::GetAllMaps(CExBaseList &listVarMaps)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmMapObject *pDvmMapObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMPCLASSID_CDVMDATASETMAP || nClassID == DMPCLASSID_CDVMDEVICEMAP)
		{
			pDvmMapObj = (CDvmMapObject *)p;
			pDvmMapObj->GetAllMaps(listVarMaps);
		}
	}
}

