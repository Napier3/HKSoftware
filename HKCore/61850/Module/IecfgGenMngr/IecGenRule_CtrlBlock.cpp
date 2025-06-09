//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenRule_CtrlBlock.cpp  CIecGenRule_CtrlBlock


#include "stdafx.h"
#include "IecGenRule_CtrlBlock.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenRule_CtrlBlock::CIecGenRule_CtrlBlock()
{
	//初始化属性
	m_nFiberIndex = 0;
	m_nMatchRatio = 70;

	//初始化成员变量
#ifdef IECFG_USE_KEYDB
	m_pChMatchList = NULL;
#endif
}

CIecGenRule_CtrlBlock::~CIecGenRule_CtrlBlock()
{
#ifdef IECFG_USE_KEYDB
	if (m_pChMatchList != NULL)
	{
		delete m_pChMatchList;
		m_pChMatchList = NULL;
	}
#endif
}

#ifdef IECFG_USE_KEYDB
void CIecGenRule_CtrlBlock::InitMatchList(CXKeyDB *pKeyDB)
{
	if (m_pChMatchList == NULL)
	{
		m_pChMatchList = new CXMatchList;
	}

	m_pChMatchList->DeleteAll();
	m_pChMatchList->Init(this,pKeyDB);
}
#endif

long CIecGenRule_CtrlBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFiber_IndexKey, oNode, m_nFiberIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strMatch_RatioKey, oNode, m_nMatchRatio);
	return 0;
}

long CIecGenRule_CtrlBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFiber_IndexKey, oElement, m_nFiberIndex);
	xml_SetAttributeValue(pXmlKeys->m_strMatch_RatioKey, oElement, m_nMatchRatio);
	return 0;
}

long CIecGenRule_CtrlBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nFiberIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_nMatchRatio);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nFiberIndex);
		BinarySerializeRead(oBinaryBuffer, m_nMatchRatio);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nFiberIndex);
		BinarySerializeWrite(oBinaryBuffer, m_nMatchRatio);
	}
	return 0;
}

void CIecGenRule_CtrlBlock::InitAfterRead()
{
}

BOOL CIecGenRule_CtrlBlock::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenRule_CtrlBlock *p = (CIecGenRule_CtrlBlock*)pObj;

	if(m_nFiberIndex != p->m_nFiberIndex)
	{
		return FALSE;
	}

	if(m_nMatchRatio != p->m_nMatchRatio)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecGenRule_CtrlBlock::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenRule_CtrlBlock *p = (CIecGenRule_CtrlBlock*)pDest;

	p->m_nFiberIndex = m_nFiberIndex;
	p->m_nMatchRatio = m_nMatchRatio;
	return TRUE;
}

CBaseObject* CIecGenRule_CtrlBlock::Clone()
{
	CIecGenRule_CtrlBlock *p = new CIecGenRule_CtrlBlock();
	Copy(p);
	return p;
}

CBaseObject* CIecGenRule_CtrlBlock::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenRule_CtrlBlock *p = new CIecGenRule_CtrlBlock();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenRule_CtrlBlock::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENCFGKEYS)
	{
		return TRUE;
	}

	if (nClassID == GENRATECLASSID_CIECGENCFGKEY)
	{
		return TRUE;
	}

	if (nClassID == GENRATECLASSID_CIECGENRULE_CTRLCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenRule_CtrlBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenCfgKeysKey)
	{
		pNew = new CIecGenCfgKeys();
	}
	else if (strClassID == pXmlKeys->m_strCIecGenCfgKeyKey)
	{
		pNew = new CIecGenCfgKey();
	}
	else if (strClassID == pXmlKeys->m_strCIecGenRule_CtrlChKey)
	{
		pNew = new CIecGenRule_CtrlCh();
	}

	return pNew;
}

CExBaseObject* CIecGenRule_CtrlBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENCFGKEYS)
	{
		pNew = new CIecGenCfgKeys();
	}
	else if (nClassID == GENRATECLASSID_CIECGENCFGKEY)
	{
		pNew = new CIecGenCfgKey();
	}
	else if (nClassID == GENRATECLASSID_CIECGENRULE_CTRLCH)
	{
		pNew = new CIecGenRule_CtrlCh();
	}

	return pNew;
}
long CIecGenRule_CtrlBlock::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strFiber_IndexKey, m_nFiberIndex);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strMatch_RatioKey, m_nMatchRatio);
	return 0;
}

long CIecGenRule_CtrlBlock::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strFiber_IndexKey, m_nFiberIndex);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strMatch_RatioKey, m_nMatchRatio);
	return 0;
}

// BOOL CIecGenRule_CtrlBlock::GenerateIecCfgDatas(CIecCfgDatasSMV *pSmvMngr)
// {
// //	CStringArray astrDesc;
// 	CIecGenCfgKeys *pKeys = (CIecGenCfgKeys*)FindByClassID(GENRATECLASSID_CIECGENCFGKEYS);
// 	CIecGenCfgAnalogs *pAnalogs = (CIecGenCfgAnalogs*)FindByClassID(GENRATECLASSID_CIECGENCFGANALOGS);
// 
// 	if (pAnalogs == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("iecfg-generate-mngr文件中,采样值控制块(%s)缺少模拟量通道映射."),m_strID);
// //		pSmvMngr->SetAllFiberIndex(m_nFiberIndex-1);
// 		return FALSE;
// 	}
// 
// 	if (pKeys != NULL)
// 	{
// //		pKeys->GetKeys(astrDesc);
// 		CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pKeys->FindIecCfgData(pSmvMngr/*,astrDesc*/);
// 
// 		if (pIecCfg92Data != NULL)
// 		{
// 			pIecCfg92Data->m_nFiberIndex = m_nFiberIndex-1;
// 			return pAnalogs->SetAllChMaps(pIecCfg92Data);
// 		} 
// 		else
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找采样值控制块(%s)失败."),m_strID);
// 			return FALSE;
// 		}
// 	} 
// 
// 	return pAnalogs->SetAllChMaps(pSmvMngr);
// }
// 
// BOOL CIecGenRule_CtrlBlock::GenerateIecCfgData_Bin(CIecCfgGinData *pIecCfgGinData)
// {
// 	POS pos_bin = GetHeadPosition();
// 	CExBaseObject *pCurObj = NULL;
// 	CIecGenCfgBin *pBin = NULL;
// 
// 	while (pos_bin != NULL)
// 	{
// 		pCurObj = GetNext(pos_bin);
// 
// 		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGBIN)
// 		{
// 			pBin = (CIecGenCfgBin *)pCurObj;
// 
// 			if (!pBin->SetChMap(pIecCfgGinData))
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE订阅控制块(%s)中开入(%s)映射为(%s)失败."),m_strID,pBin->m_strID,pBin->m_strAppCh);
// 			}
// 		}
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CIecGenRule_CtrlBlock::GenerateIecCfgData_Bout(CIecCfgGoutData *pIecCfgGoutData)
// {
// 	POS pos_bin = GetHeadPosition();
// 	CExBaseObject *pCurObj = NULL;
// 	CIecGenCfgBout *pBout = NULL;
// 
// 	while (pos_bin != NULL)
// 	{
// 		pCurObj = GetNext(pos_bin);
// 
// 		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGBOUT)
// 		{
// 			pBout = (CIecGenCfgBout *)pCurObj;
// 
// 			if (!pBout->SetChMap(pIecCfgGoutData))
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE发布控制块(%s)中开出(%s)映射为(%s)失败."),m_strID,pBout->m_strID,pBout->m_strAppCh);
// 			}
// 		}
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CIecGenRule_CtrlBlock::GenerateIecCfgDatas(CIecCfgGinDatas* pGinMngr)
// {
// //	CStringArray astrDesc;
// 	CIecGenCfgKeys *pKeys = (CIecGenCfgKeys*)FindByClassID(GENRATECLASSID_CIECGENCFGKEYS);
// 
// 	if (pKeys != NULL)
// 	{
// //		pKeys->GetKeys(astrDesc);
// 		CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pKeys->FindIecCfgData(pGinMngr/*,astrDesc*/);
// 
// 		if (pIecCfgGinData != NULL)
// 		{
// 			pIecCfgGinData->m_nFiberIndex = m_nFiberIndex-1;
// 			GenerateIecCfgData_Bin(pIecCfgGinData);
// 		} 
// 		else
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找GOOSE订阅控制块(%s)失败."),m_strID);
// 		}
// 	} 
// 	else
// 	{
// 		pGinMngr->SetAllFiberIndex(m_nFiberIndex-1);
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CIecGenRule_CtrlBlock::GenerateIecCfgDatas(CIecCfgGoutDatas* pGoutMngr)
// {
// //	CStringArray astrDesc;
// 	CIecGenCfgKeys *pKeys = (CIecGenCfgKeys*)FindByClassID(GENRATECLASSID_CIECGENCFGKEYS);
// 
// 	if (pKeys != NULL)
// 	{
// //		pKeys->GetKeys(astrDesc);
// 		CIecCfgGoutData *pIecCfgGoutData = (CIecCfgGoutData*)pKeys->FindIecCfgData(pGoutMngr/*,astrDesc*/);
// 
// 		if (pIecCfgGoutData != NULL)
// 		{
// 			pIecCfgGoutData->m_nFiberIndex = m_nFiberIndex-1;
// 			GenerateIecCfgData_Bout(pIecCfgGoutData);
// 		} 
// 		else
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找GOOSE发布控制块(%s)失败."),m_strID);
// 		}
// 	} 
// 	else
// 	{
// 		pGoutMngr->SetAllFiberIndex(m_nFiberIndex-1);
// 	}
// 
// 
// 	return TRUE;
// }

// CIecCfgDataBase* CCtrlBlock::FindIecCfgData(CIecCfgDatasBase *pIecCfgDatasBase,const CStringArray &astrDesc)
// {
// 	POS pos = pIecCfgDatasBase->GetHeadPosition();
// 	CIecCfgDataBase *pIecCfgDataBase = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasBase->GetNext(pos);
// 
// 		if (pIecCfgDatasBase->IsCfgData(pIecCfgDataBase->GetClassID()))
// 		{
// 			CIecCfgDataChBase* pCfgDataCh = NULL;
// 			ASSERT(pIecCfgDataBase->m_pCfgChs);
// 
// 			POS pos_ch = pIecCfgDataBase->m_pCfgChs->GetHeadPosition();
// 
// 			while(pos_ch)
// 			{
// 				pCfgDataCh = (CIecCfgDataChBase*)pIecCfgDataBase->m_pCfgChs->GetNext(pos_ch);
// 
// 				for (int nIndex = 0; nIndex < astrDesc.GetCount(); nIndex++)
// 				{
// 					if (pCfgDataCh->m_strName.Find(astrDesc[nIndex]) != -1)
// 					{
// 						return pIecCfgDataBase;
// 					}
// 				}
// 			}
// 		}
// 	}
//
//	return NULL;
//}