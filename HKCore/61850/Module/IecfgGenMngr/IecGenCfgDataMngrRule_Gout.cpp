//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgDataMngrRule_Gout.cpp  CIecGenCfgDataMngrRule_Gout


#include "stdafx.h"
#include "IecGenCfgDataMngrRule_Gout.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgDataMngrRule_Gout::CIecGenCfgDataMngrRule_Gout()
{
	//初始化属性

	//初始化成员变量
}

CIecGenCfgDataMngrRule_Gout::~CIecGenCfgDataMngrRule_Gout()
{
}

long CIecGenCfgDataMngrRule_Gout::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecGenCfgDataMngrRule_Base::XmlReadOwn(oNode, pXmlRWKeys);
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_Gout::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecGenCfgDataMngrRule_Base::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_Gout::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecGenCfgDataMngrRule_Gout::InitAfterRead()
{
}

BOOL CIecGenCfgDataMngrRule_Gout::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecGenCfgDataMngrRule_Base::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgDataMngrRule_Gout *p = (CIecGenCfgDataMngrRule_Gout*)pObj;

	return TRUE;
}

BOOL CIecGenCfgDataMngrRule_Gout::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecGenCfgDataMngrRule_Base::CopyOwn(pDest);

	CIecGenCfgDataMngrRule_Gout *p = (CIecGenCfgDataMngrRule_Gout*)pDest;

	return TRUE;
}

CBaseObject* CIecGenCfgDataMngrRule_Gout::Clone()
{
	CIecGenCfgDataMngrRule_Gout *p = new CIecGenCfgDataMngrRule_Gout();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgDataMngrRule_Gout::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgDataMngrRule_Gout *p = new CIecGenCfgDataMngrRule_Gout();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgDataMngrRule_Gout::CanPaste(UINT nClassID)
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

CExBaseObject* CIecGenCfgDataMngrRule_Gout::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

CExBaseObject* CIecGenCfgDataMngrRule_Gout::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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

// BOOL CIecGenCfgDataMngrRule_Gout::GenarateIecCfgGoutDatas(CIecCfgGoutDatas* pGoutMngr)
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
// 			pCurCtrlBlock->GenerateIecCfgDatas(pGoutMngr);
// 		}
// 	}
// 
// 	GenerateIecCfgDatas_Bout(pGoutMngr);
// 	return TRUE;
// }
// 
// BOOL CIecGenCfgDataMngrRule_Gout::GenerateIecCfgDatas_Bout(CIecCfgGoutDatas* pGoutMngr)
// {
// 	POS pos_bin = GetHeadPosition();
// 	CExBaseObject *pCurObj = NULL,*pIecCfgDataBase = NULL;
// //	CIecCfgGoutData *pIecCfgGoutData = NULL;
// 	CIecGenCfgBout *pBout = NULL;
// 	BOOL bFind = FALSE;
// 
// 	while (pos_bin != NULL)
// 	{
// 		pCurObj = GetNext(pos_bin);
// 
// 		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENCFGBOUT)
// 		{
// 			pBout = (CIecGenCfgBout *)pCurObj;
// 			bFind = FALSE;
// 
// 			POS pos_gindata = pGoutMngr->GetHeadPosition();
// 
// 			while(pos_gindata)
// 			{
// 				pIecCfgDataBase = (CIecCfgDataBase *)pGoutMngr->GetNext(pos_gindata);
// 
// 				if (pGoutMngr->IsCfgData(pIecCfgDataBase->GetClassID()))
// 				{
// 					if (pBout->SetChMap((CIecCfgGoutData*)pIecCfgDataBase))
// 					{
// 						bFind = TRUE;
// 						break;
// 					}
// 				}
// 			}
// 
// 			if (!bFind)
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE订阅控制块(%s)中开入(%s)映射为(%s)失败."),m_strID,pBout->m_strID,pBout->m_strAppCh);
// 			}
// 		}
// 	}
// 
// 	return TRUE;
// }

