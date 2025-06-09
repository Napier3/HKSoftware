#include "StdAfx.h"
#include "GbWzdCommCmdAdd.h"
#include "GbSmartGenWzd.h"

CGbWzdCommCmdAdd::CGbWzdCommCmdAdd(void)
{

}

CGbWzdCommCmdAdd::~CGbWzdCommCmdAdd(void)
{

}


long CGbWzdCommCmdAdd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CGbWzdXItemBase::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strCommCmdIDKey, oNode, m_strCommCmdID);

	return 0;
}

long CGbWzdCommCmdAdd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdXItemBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strCommCmdIDKey, oElement, m_strCommCmdID);

	return 0;
}

long CGbWzdCommCmdAdd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbWzdXItemBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}

	return 0;
}

BOOL CGbWzdCommCmdAdd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CGbWzdXItemBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdCommCmdAdd *p = (CGbWzdCommCmdAdd*)pObj;

	if (m_strCommCmdID != p->m_strCommCmdID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdCommCmdAdd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbWzdXItemBase::CopyOwn(pDest);

	CGbWzdCommCmdAdd *p = (CGbWzdCommCmdAdd*)pDest;
	p->m_strCommCmdID = m_strCommCmdID;

	return TRUE;
}

CBaseObject* CGbWzdCommCmdAdd::Clone()
{
	CGbWzdCommCmdAdd *p = new CGbWzdCommCmdAdd();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdCommCmdAdd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdCommCmdAdd *p = new CGbWzdCommCmdAdd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdCommCmdAdd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CGbWzdXItemBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdCommCmdAdd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else
	{
		pNew = CGbWzdXItemBase::CreateNewChild(nClassID);
	}

	return pNew;
}

void CGbWzdCommCmdAdd::AddDataToWzdCmdCfg(CDvmData *pData ,CDvmDataset *pDataset)
{
	//ID 应当= 数据集路径的group对象，应当有且只有一个
	CDataGroup *pGrp_Dataset = (CDataGroup *)FindByClassID(DTMCLASSID_CDATAGROUP);
	CString strDatasetPath;
	CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
	strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;

	if (pGrp_Dataset == NULL)
	{
		pGrp_Dataset = AddNewGroup(_T(""), strDatasetPath, _T(""), FALSE);
	}
	else if (pGrp_Dataset->m_strID != strDatasetPath)
	{
		//如果数据集路径不一致，则删除原来的，创建一个新的
		Delete(pGrp_Dataset);
		pGrp_Dataset = AddNewGroup(_T(""), strDatasetPath, _T(""), FALSE);
	}

	if (pData != NULL)
	{
		CDvmData *pFind = (CDvmData*)pGrp_Dataset->FindByID(pData->m_strID);

		if (pFind != NULL)
		{
			if (pData->m_strValue.IsEmpty())
			{
				//删除值为空的
				pGrp_Dataset->Delete(pFind);
				return;
			}

			pFind->m_strValue = pData->m_strValue;
			return;
		}

		//此处只需要拷贝自身即可
		pFind = (CDvmData*)pData->CloneEx(TRUE, FALSE);
		pGrp_Dataset->AddNewChild(pFind);
	}
}

void CGbWzdCommCmdAdd::AddDataToWzdCmdCfg(CValue *pValue ,CDvmDataset *pDataset)
{
	//ID 应当= 数据集路径的group对象，应当有且只有一个
	CDataGroup *pGrp_Dataset = (CDataGroup *)FindByClassID(DTMCLASSID_CDATAGROUP);
	CString strDatasetPath;
	CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
	strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;

	if (pGrp_Dataset == NULL)
	{
		pGrp_Dataset = AddNewGroup(_T(""), strDatasetPath, _T(""), FALSE);
	}
	else if (pGrp_Dataset->m_strID != strDatasetPath)
	{
		//如果数据集路径不一致，则删除原来的，创建一个新的
		Delete(pGrp_Dataset);
		pGrp_Dataset = AddNewGroup(_T(""), strDatasetPath, _T(""), FALSE);
	}

	if (pValue != NULL)
	{
		CDvmData *pFind = (CDvmData*)pGrp_Dataset->FindByID(pValue->m_strID);

		if (pFind != NULL)
		{
			if (pValue->m_strValue.IsEmpty())
			{
				//删除值为空的
				pGrp_Dataset->Delete(pFind);
				return;
			}

			pFind->m_strValue = pValue->m_strValue;
			return;
		}

		pFind = new CDvmData();
		pFind->m_strValue = pValue->m_strValue;
		pFind->m_strID = pValue->m_strID;
		pGrp_Dataset->AddNewChild(pFind);
	}
}

void CGbWzdCommCmdAdd::DeleteAllDatasToWzdCmdCfg()
{
	//ID 应当= 数据集路径的group对象，应当有且只有一个
	CDataGroup *pGrp_Dataset = (CDataGroup *)FindByClassID(DTMCLASSID_CDATAGROUP);

	if (pGrp_Dataset != NULL)
	{
		pGrp_Dataset->DeleteAll();
	}
}

void CGbWzdCommCmdAdd::DeleteDataFromWzdCmdCfg(const CString &strDataID)
{
	//ID 应当= 数据集路径的group对象，应当有且只有一个
	CDataGroup *pGrp_Dataset = (CDataGroup *)FindByClassID(DTMCLASSID_CDATAGROUP);

	if (pGrp_Dataset != NULL)
	{
		pGrp_Dataset->DeleteByID(strDataID);
	}
}

void CGbWzdCommCmdAdd::UpdateDataToWzdCmdCfg(CDvmData *pDvmData)
{
	//ID 应当= 数据集路径的group对象，应当有且只有一个
	CDataGroup *pGrp_Dataset = (CDataGroup *)FindByClassID(DTMCLASSID_CDATAGROUP);

	if (pGrp_Dataset == NULL)
	{
		return;
	}

	CDvmData *pFind = (CDvmData *)pGrp_Dataset->FindByID(pDvmData->m_strID);

	if (pFind != NULL)
	{
		pFind->m_strValue = pDvmData->m_strValue;
	}
}

void CGbWzdCommCmdAdd::UpdateZoneIndexToWzdCmdCfg(int nZoneIndex)
{
	CDvmData *pZoneIndex = (CDvmData *)FindByID(STT_CMD_PARA_ZoneIndex);

	if (pZoneIndex == NULL)
	{
		pZoneIndex = AddNewData(STT_CMD_PARA_ZoneIndex, (long)nZoneIndex);
		return;
	}

	pZoneIndex->m_strValue.Format(_T("%d"), nZoneIndex);
}

void CGbWzdCommCmdAdd::UpdateDelayBftToWzdCmdCfg(const CString &strDelay)
{
	CDvmData *pDelay = (CDvmData *)FindByID(STT_CMD_PARA_DelayBeforeCmd);

	if (pDelay == NULL)
	{
		pDelay = AddNewData(STT_CMD_PARA_DelayBeforeCmd, strDelay);
		return;
	}

	pDelay->m_strValue = strDelay;
}

void CGbWzdCommCmdAdd::UpdateDelayAftToWzdCmdCfg(const CString &strDelay)
{
	CDvmData *pDelay = (CDvmData *)FindByID(STT_CMD_PARA_DelayAfterCmd);

	if (pDelay == NULL)
	{
		pDelay = AddNewData(STT_CMD_PARA_DelayAfterCmd, strDelay);
		return;
	}

	pDelay->m_strValue = strDelay;
}

void CGbWzdCommCmdAdd::ClearEmptyCmdParas(CDvmDataset *pDataset)
{
	if(!pDataset)
	{
		return;
	}

	CDataGroup *pGrp_Dataset = (CDataGroup *)FindByClassID(DTMCLASSID_CDATAGROUP);
	CString strDatasetPath;
	CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDataset->GetParent();
	strDatasetPath = pLd->m_strID + _T("$") + pDataset->m_strID;

	if (pGrp_Dataset == NULL)
	{
		return;
	}
	else if (pGrp_Dataset->m_strID != strDatasetPath)
	{
		return;
	}

	POS pos = pGrp_Dataset->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pGrp_Dataset->GetNext(pos);

		if (pData->m_strValue.IsEmpty())
		{
			pGrp_Dataset->Delete(pData);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
CGbWzdCommCmdUpdate::CGbWzdCommCmdUpdate(void)
{
	m_pCommCmd = NULL;
}

CGbWzdCommCmdUpdate::~CGbWzdCommCmdUpdate(void)
{

}

CDvmContents* CGbWzdCommCmdUpdate::GetCommCmd()
{
	if (m_pCommCmd != NULL)
	{
		return m_pCommCmd;
	}

	m_pCommCmd = new CDvmContents();
	AddNewChild(m_pCommCmd);

	return m_pCommCmd;
}

void CGbWzdCommCmdUpdate::GetCommCmd_String(CString &strCommCmd)
{
	if (m_pCommCmd == NULL)
	{
		return;
	}

	strCommCmd = m_pCommCmd->m_strText;
}

long CGbWzdCommCmdUpdate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsNameKey, oNode, m_strItemsName);
	xml_GetAttibuteValue(pXmlKeys->m_strItemsIDKey, oNode, m_strItemsID);

	return 0;
}

long CGbWzdCommCmdUpdate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strItemsNameKey, oElement, m_strItemsName);
	xml_SetAttributeValue(pXmlKeys->m_strItemsIDKey, oElement, m_strItemsID);

	return 0;
}

long CGbWzdCommCmdUpdate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataGroup::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}

	return 0;
}

BOOL CGbWzdCommCmdUpdate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdCommCmdUpdate *p = (CGbWzdCommCmdUpdate*)pObj;

	if (m_strParentItemsID != p->m_strParentItemsID)
	{
		return FALSE;
	}

	if (m_strItemsName != p->m_strItemsName)
	{
		return FALSE;
	}

	if (m_strItemsID != p->m_strItemsID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdCommCmdUpdate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdCommCmdUpdate *p = (CGbWzdCommCmdUpdate*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_strItemsName = m_strItemsName;
	p->m_strItemsID = m_strItemsID;

	return TRUE;
}

void CGbWzdCommCmdUpdate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CCONTENTS)
		{
			m_pCommCmd = (CDvmContents*)p;
		}
	}
}

CBaseObject* CGbWzdCommCmdUpdate::Clone()
{
	CGbWzdCommCmdUpdate *p = new CGbWzdCommCmdUpdate();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdCommCmdUpdate::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdCommCmdUpdate *p = new CGbWzdCommCmdUpdate();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdCommCmdUpdate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strContentsKey)
	{
		pNew = new CDvmContents();
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CGbWzdCommCmdUpdate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else if (nClassID == DTMCLASSID_CCONTENTS)
	{
		pNew = new CDvmContents();
	}
	else
	{
		pNew = CDataGroup::CreateNewChild(nClassID);
	}

	return pNew;
}

void CGbWzdCommCmdUpdate::GetItemPath(CString &strItemPath)
{
	if (m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = m_strParentItemsID + _T("$");
	}

	strItemPath += m_strItemsID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
CGbWzdCommCmdAddGrp::CGbWzdCommCmdAddGrp(void)
{
	m_nAftUseReset = 0;
	m_nAddCommCmd = 0;
}

CGbWzdCommCmdAddGrp::~CGbWzdCommCmdAddGrp(void)
{

}

long CGbWzdCommCmdAddGrp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strParentItemsIDKey, oNode, m_strParentItemsID);
	xml_GetAttibuteValue(pXmlKeys->m_strAftUseResetKey, oNode, m_nAftUseReset);
	xml_GetAttibuteValue(pXmlKeys->m_strAddCommCmdKey, oNode, m_nAddCommCmd);

	return 0;
}

long CGbWzdCommCmdAddGrp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strParentItemsIDKey, oElement, m_strParentItemsID);
	xml_SetAttributeValue(pXmlKeys->m_strAftUseResetKey, oElement, m_nAftUseReset);
	xml_SetAttributeValue(pXmlKeys->m_strAddCommCmdKey, oElement, m_nAddCommCmd);

	return 0;
}

long CGbWzdCommCmdAddGrp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDataGroup::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strDataType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strDataType);
	}

	return 0;
}

BOOL CGbWzdCommCmdAddGrp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataGroup::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbWzdCommCmdAddGrp *p = (CGbWzdCommCmdAddGrp*)pObj;

	if (m_strParentItemsID != p->m_strParentItemsID)
	{
		return FALSE;
	}

	if (m_nAftUseReset != p->m_nAftUseReset)
	{
		return FALSE;
	}

	if (m_nAddCommCmd != p->m_nAddCommCmd)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbWzdCommCmdAddGrp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataGroup::CopyOwn(pDest);

	CGbWzdCommCmdAddGrp *p = (CGbWzdCommCmdAddGrp*)pDest;
	p->m_strParentItemsID = m_strParentItemsID;
	p->m_nAftUseReset = m_nAftUseReset;
	p->m_nAddCommCmd = m_nAddCommCmd;

	return TRUE;
}

void CGbWzdCommCmdAddGrp::InitAfterRead()
{

}

CBaseObject* CGbWzdCommCmdAddGrp::Clone()
{
	CGbWzdCommCmdAddGrp *p = new CGbWzdCommCmdAddGrp();
	Copy(p);
	return p;
}

CBaseObject* CGbWzdCommCmdAddGrp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbWzdCommCmdAddGrp *p = new CGbWzdCommCmdAddGrp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CGbWzdCommCmdAddGrp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	pNew = CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CGbWzdCommCmdAddGrp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;
	pNew = CDataGroup::CreateNewChild(nClassID);

	return pNew;
}