//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgDataMngrRule_Gin.cpp  CIecGenCfgDataMngrRule_Gin


#include "stdafx.h"
#include "IecGenCfgDataMngrRule_Gin.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgDataMngrRule_Gin::CIecGenCfgDataMngrRule_Gin()
{
	//初始化属性

	//初始化成员变量
}

CIecGenCfgDataMngrRule_Gin::~CIecGenCfgDataMngrRule_Gin()
{
}

long CIecGenCfgDataMngrRule_Gin::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecGenCfgDataMngrRule_Base::XmlReadOwn(oNode, pXmlRWKeys);
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_Gin::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecGenCfgDataMngrRule_Base::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_Gin::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CIecGenCfgDataMngrRule_Base::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CIecGenCfgDataMngrRule_Gin::InitAfterRead()
{
}

BOOL CIecGenCfgDataMngrRule_Gin::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecGenCfgDataMngrRule_Base::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgDataMngrRule_Gin *p = (CIecGenCfgDataMngrRule_Gin*)pObj;

	return TRUE;
}

BOOL CIecGenCfgDataMngrRule_Gin::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecGenCfgDataMngrRule_Base::CopyOwn(pDest);

	CIecGenCfgDataMngrRule_Gin *p = (CIecGenCfgDataMngrRule_Gin*)pDest;

	return TRUE;
}

CBaseObject* CIecGenCfgDataMngrRule_Gin::Clone()
{
	CIecGenCfgDataMngrRule_Gin *p = new CIecGenCfgDataMngrRule_Gin();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgDataMngrRule_Gin::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgDataMngrRule_Gin *p = new CIecGenCfgDataMngrRule_Gin();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgDataMngrRule_Gin::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENRULE_CTRLBLOCK)
	{
		return TRUE;
	}

	if (nClassID == GENRATECLASSID_CIECGENRULE_CTRLCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenCfgDataMngrRule_Gin::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenRule_CtrlBlockKey)
	{
		pNew = new CIecGenRule_CtrlBlock();
	}
	else if (strClassID == pXmlKeys->m_strCIecGenRule_CtrlChKey)
	{
		pNew = new CIecGenRule_CtrlCh();
	}

	return pNew;
}

CExBaseObject* CIecGenCfgDataMngrRule_Gin::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENRULE_CTRLBLOCK)
	{
		pNew = new CIecGenRule_CtrlBlock();
	}
	else if (nClassID == GENRATECLASSID_CIECGENRULE_CTRLCH)
	{
		pNew = new CIecGenRule_CtrlCh();
	}

	return pNew;
}

// BOOL CIecGenCfgDataMngrRule_Gin::GenarateIecCfgGinDatas(CIecCfgGinDatas* pGinMngr)
// {
// 	POS pos = GetHeadPosition();
// 	CExBaseObject *pCurObj = NULL;
// 	CIecGenRule_CtrlBlock *pCurCtrlBlock = NULL;
// 
// 	while(pos)
// 	{
// 		pCurObj = GetNext(pos);
// 
// 		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLBLOCK)
// 		{
// 			pCurCtrlBlock = (CIecGenRule_CtrlBlock *)pCurObj;
// 			pCurCtrlBlock->GenerateIecCfgDatas(pGinMngr);
// 		}
// 	}
// 
// 	GenerateIecCfgDatas_Bin(pGinMngr);
// 	return TRUE;
// }

// BOOL CIecGenCfgDataMngrRule_Gin::GenerateIecCfgDatas_Bin(CIecCfgGinDatas* pGinMngr)
// {
// 	POS pos_bin = GetHeadPosition();
// 	CExBaseObject *pCurObj = NULL,*pIecCfgDataBase = NULL;
// //	CIecCfgGinData *pIecCfgGinData = NULL;
// 	CIecGenCfgBin *pBin = NULL;
// 	BOOL bFind = FALSE;
// 
// 	while (pos_bin != NULL)
// 	{
// 		pCurObj = GetNext(pos_bin);
// 
// 		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGBIN)
// 		{
// 			pBin = (CIecGenCfgBin *)pCurObj;
// 			bFind = FALSE;
// 
// 			POS pos_gindata = pGinMngr->GetHeadPosition();
// 
// 			while(pos_gindata)
// 			{
// 				pIecCfgDataBase = (CIecCfgDataBase *)pGinMngr->GetNext(pos_gindata);
// 
// 				if (pGinMngr->IsCfgData(pIecCfgDataBase->GetClassID()))
// 				{
// 					if (pBin->SetChMap((CIecCfgGinData*)pIecCfgDataBase))
// 					{
// 						bFind = TRUE;
// 						break;
// 					}
// 				}
// 			}
// 
// 			if (!bFind)
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE订阅控制块(%s)中开入(%s)映射为(%s)失败."),m_strID,pBin->m_strID,pBin->m_strAppCh);
// 			}
// 		}
// 	}
// 
// 	return TRUE;
// }
