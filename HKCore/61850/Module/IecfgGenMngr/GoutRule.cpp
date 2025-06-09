//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GoutRule.cpp  CGoutRule


#include "stdafx.h"
#include "GoutRule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGoutRule::CGoutRule()
{
	//初始化属性

	//初始化成员变量
}

CGoutRule::~CGoutRule()
{
}

long CGoutRule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGoutRule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGoutRule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CGoutRule::InitAfterRead()
{
}

BOOL CGoutRule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGoutRule *p = (CGoutRule*)pObj;

	return TRUE;
}

BOOL CGoutRule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGoutRule *p = (CGoutRule*)pDest;

	return TRUE;
}

CBaseObject* CGoutRule::Clone()
{
	CGoutRule *p = new CGoutRule();
	Copy(p);
	return p;
}

CBaseObject* CGoutRule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGoutRule *p = new CGoutRule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CGoutRule::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CBOUT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CCTRLBLOCK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGoutRule::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCBoutKey)
	{
		pNew = new CBout();
	}
	else if (strClassID == pXmlKeys->m_strCCtrlBlockKey)
	{
		pNew = new CCtrlBlock();
	}

	return pNew;
}

CExBaseObject* CGoutRule::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CBOUT)
	{
		pNew = new CBout();
	}
	else if (nClassID == MNGRCLASSID_CCTRLBLOCK)
	{
		pNew = new CCtrlBlock();
	}

	return pNew;
}

BOOL CGoutRule::GenarateIecCfgGoutDatas(CIecCfgGoutDatas* pGoutMngr)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CCtrlBlock *pCurCtrlBlock = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == MNGRCLASSID_CCTRLBLOCK)
		{
			pCurCtrlBlock = (CCtrlBlock *)pCurObj;
			pCurCtrlBlock->GenerateIecCfgDatas(pGoutMngr);
		}
	}

	GenerateIecCfgDatas_Bout(pGoutMngr);
	return TRUE;
}

BOOL CGoutRule::GenerateIecCfgDatas_Bout(CIecCfgGoutDatas* pGoutMngr)
{
	POS pos_bin = GetHeadPosition();
	CExBaseObject *pCurObj = NULL,*pIecCfgDataBase = NULL;
//	CIecCfgGoutData *pIecCfgGoutData = NULL;
	CBout *pBout = NULL;
	BOOL bFind = FALSE;

	while (pos_bin != NULL)
	{
		pCurObj = GetNext(pos_bin);

		if (pCurObj->GetClassID() == MNGRCLASSID_CBOUT)
		{
			pBout = (CBout *)pCurObj;
			bFind = FALSE;

			POS pos_gindata = pGoutMngr->GetHeadPosition();

			while(pos_gindata)
			{
				pIecCfgDataBase = (CIecCfgDataBase *)pGoutMngr->GetNext(pos_gindata);

				if (pGoutMngr->IsCfgData(pIecCfgDataBase->GetClassID()))
				{
					if (pBout->SetChMap((CIecCfgGoutData*)pIecCfgDataBase))
					{
						bFind = TRUE;
						break;
					}
				}
			}

			if (!bFind)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE订阅控制块(%s)中开入(%s)映射为(%s)失败."),m_strID,pBout->m_strID,pBout->m_strAppCh);
			}
		}
	}

	return TRUE;
}

