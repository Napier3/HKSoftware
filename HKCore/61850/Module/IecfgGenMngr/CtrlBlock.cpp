//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CtrlBlock.cpp  CCtrlBlock


#include "stdafx.h"
#include "CtrlBlock.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCtrlBlock::CCtrlBlock()
{
	//初始化属性
	m_nFiberIndex = 0;

	//初始化成员变量
}

CCtrlBlock::~CCtrlBlock()
{
}

long CCtrlBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFiber_IndexKey, oNode, m_nFiberIndex);
	return 0;
}

long CCtrlBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFiber_IndexKey, oElement, m_nFiberIndex);
	return 0;
}

long CCtrlBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nFiberIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nFiberIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nFiberIndex);
	}
	return 0;
}

void CCtrlBlock::InitAfterRead()
{
}

BOOL CCtrlBlock::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CCtrlBlock *p = (CCtrlBlock*)pObj;

	if(m_nFiberIndex != p->m_nFiberIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCtrlBlock::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CCtrlBlock *p = (CCtrlBlock*)pDest;

	p->m_nFiberIndex = m_nFiberIndex;
	return TRUE;
}

CBaseObject* CCtrlBlock::Clone()
{
	CCtrlBlock *p = new CCtrlBlock();
	Copy(p);
	return p;
}

CBaseObject* CCtrlBlock::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCtrlBlock *p = new CCtrlBlock();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCtrlBlock::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CKEYS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CANALOGS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CBIN)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CBOUT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCtrlBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCKeysKey)
	{
		pNew = new CKeys();
	}
	else if (strClassID == pXmlKeys->m_strCAnalogsKey)
	{
		pNew = new CAnalogs();
	}
	else if (strClassID == pXmlKeys->m_strCBinKey)
	{
		pNew = new CBin();
	}
	else if (strClassID == pXmlKeys->m_strCBoutKey)
	{
		pNew = new CBout();
	}

	return pNew;
}

CExBaseObject* CCtrlBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CKEYS)
	{
		pNew = new CKeys();
	}
	else if (nClassID == MNGRCLASSID_CANALOGS)
	{
		pNew = new CAnalogs();
	}
	else if (nClassID == MNGRCLASSID_CBIN)
	{
		pNew = new CBin();
	}
	else if (nClassID == MNGRCLASSID_CBOUT)
	{
		pNew = new CBout();
	}

	return pNew;
}
long CCtrlBlock::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strFiber_IndexKey, m_nFiberIndex);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CCtrlBlock::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strFiber_IndexKey, m_nFiberIndex);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

BOOL CCtrlBlock::GenerateIecCfgDatas(CIecCfgDatasSMV *pSmvMngr)
{
//	CStringArray astrDesc;
	CKeys *pKeys = (CKeys*)FindByClassID(MNGRCLASSID_CKEYS);
	CAnalogs *pAnalogs = (CAnalogs*)FindByClassID(MNGRCLASSID_CANALOGS);

	if (pAnalogs == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("iecfg-generate-mngr文件中,采样值控制块(%s)缺少模拟量通道映射."),m_strID);
//		pSmvMngr->SetAllFiberIndex(m_nFiberIndex-1);
		return FALSE;
	}

	if (pKeys != NULL)
	{
//		pKeys->GetKeys(astrDesc);
		CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pKeys->FindIecCfgData(pSmvMngr/*,astrDesc*/);

		if (pIecCfg92Data != NULL)
		{
			pIecCfg92Data->m_nFiberIndex = m_nFiberIndex-1;
			return pAnalogs->SetAllChMaps(pIecCfg92Data);
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找采样值控制块(%s)失败."),m_strID);
			return FALSE;
		}
	} 

	return pAnalogs->SetAllChMaps(pSmvMngr);
}

BOOL CCtrlBlock::GenerateIecCfgData_Bin(CIecCfgGinData *pIecCfgGinData)
{
	POS pos_bin = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CBin *pBin = NULL;

	while (pos_bin != NULL)
	{
		pCurObj = GetNext(pos_bin);

		if (pCurObj->GetClassID() == MNGRCLASSID_CBIN)
		{
			pBin = (CBin *)pCurObj;

			if (!pBin->SetChMap(pIecCfgGinData))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE订阅控制块(%s)中开入(%s)映射为(%s)失败."),m_strID,pBin->m_strID,pBin->m_strAppCh);
			}
		}
	}

	return TRUE;
}

BOOL CCtrlBlock::GenerateIecCfgData_Bout(CIecCfgGoutData *pIecCfgGoutData)
{
	POS pos_bin = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CBout *pBout = NULL;

	while (pos_bin != NULL)
	{
		pCurObj = GetNext(pos_bin);

		if (pCurObj->GetClassID() == MNGRCLASSID_CBOUT)
		{
			pBout = (CBout *)pCurObj;

			if (!pBout->SetChMap(pIecCfgGoutData))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE发布控制块(%s)中开出(%s)映射为(%s)失败."),m_strID,pBout->m_strID,pBout->m_strAppCh);
			}
		}
	}

	return TRUE;
}

BOOL CCtrlBlock::GenerateIecCfgDatas(CIecCfgGinDatas* pGinMngr)
{
//	CStringArray astrDesc;
	CKeys *pKeys = (CKeys*)FindByClassID(MNGRCLASSID_CKEYS);

	if (pKeys != NULL)
	{
//		pKeys->GetKeys(astrDesc);
		CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pKeys->FindIecCfgData(pGinMngr/*,astrDesc*/);

		if (pIecCfgGinData != NULL)
		{
			pIecCfgGinData->m_nFiberIndex = m_nFiberIndex-1;
			GenerateIecCfgData_Bin(pIecCfgGinData);
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找GOOSE订阅控制块(%s)失败."),m_strID);
		}
	} 
	else
	{
		pGinMngr->SetAllFiberIndex(m_nFiberIndex-1);
	}

	return TRUE;
}

BOOL CCtrlBlock::GenerateIecCfgDatas(CIecCfgGoutDatas* pGoutMngr)
{
//	CStringArray astrDesc;
	CKeys *pKeys = (CKeys*)FindByClassID(MNGRCLASSID_CKEYS);

	if (pKeys != NULL)
	{
//		pKeys->GetKeys(astrDesc);
		CIecCfgGoutData *pIecCfgGoutData = (CIecCfgGoutData*)pKeys->FindIecCfgData(pGoutMngr/*,astrDesc*/);

		if (pIecCfgGoutData != NULL)
		{
			pIecCfgGoutData->m_nFiberIndex = m_nFiberIndex-1;
			GenerateIecCfgData_Bout(pIecCfgGoutData);
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找GOOSE发布控制块(%s)失败."),m_strID);
		}
	} 
	else
	{
		pGoutMngr->SetAllFiberIndex(m_nFiberIndex-1);
	}


	return TRUE;
}

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