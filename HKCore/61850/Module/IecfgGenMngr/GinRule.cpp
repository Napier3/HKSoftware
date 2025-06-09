//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GinRule.cpp  CGinRule


#include "stdafx.h"
#include "GinRule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGinRule::CGinRule()
{
	//初始化属性

	//初始化成员变量
}

CGinRule::~CGinRule()
{
}

long CGinRule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGinRule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGinRule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CGinRule::InitAfterRead()
{
}

BOOL CGinRule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGinRule *p = (CGinRule*)pObj;

	return TRUE;
}

BOOL CGinRule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGinRule *p = (CGinRule*)pDest;

	return TRUE;
}

CBaseObject* CGinRule::Clone()
{
	CGinRule *p = new CGinRule();
	Copy(p);
	return p;
}

CBaseObject* CGinRule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGinRule *p = new CGinRule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CGinRule::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CBIN)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CCTRLBLOCK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGinRule::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCBinKey)
	{
		pNew = new CBin();
	}
	else if (strClassID == pXmlKeys->m_strCCtrlBlockKey)
	{
		pNew = new CCtrlBlock();
	}

	return pNew;
}

CExBaseObject* CGinRule::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CBIN)
	{
		pNew = new CBin();
	}
	else if (nClassID == MNGRCLASSID_CCTRLBLOCK)
	{
		pNew = new CCtrlBlock();
	}

	return pNew;
}

BOOL CGinRule::GenarateIecCfgGinDatas(CIecCfgGinDatas* pGinMngr)
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
			pCurCtrlBlock->GenerateIecCfgDatas(pGinMngr);
		}
	}

	GenerateIecCfgDatas_Bin(pGinMngr);
	return TRUE;
}

BOOL CGinRule::GenerateIecCfgDatas_Bin(CIecCfgGinDatas* pGinMngr)
{
	POS pos_bin = GetHeadPosition();
	CExBaseObject *pCurObj = NULL,*pIecCfgDataBase = NULL;
//	CIecCfgGinData *pIecCfgGinData = NULL;
	CBin *pBin = NULL;
	BOOL bFind = FALSE;

	while (pos_bin != NULL)
	{
		pCurObj = GetNext(pos_bin);

		if (pCurObj->GetClassID() == MNGRCLASSID_CBIN)
		{
			pBin = (CBin *)pCurObj;
			bFind = FALSE;

			POS pos_gindata = pGinMngr->GetHeadPosition();

			while(pos_gindata)
			{
				pIecCfgDataBase = (CIecCfgDataBase *)pGinMngr->GetNext(pos_gindata);

				if (pGinMngr->IsCfgData(pIecCfgDataBase->GetClassID()))
				{
					if (pBin->SetChMap((CIecCfgGinData*)pIecCfgDataBase))
					{
						bFind = TRUE;
						break;
					}
				}
			}

			if (!bFind)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE订阅控制块(%s)中开入(%s)映射为(%s)失败."),m_strID,pBin->m_strID,pBin->m_strAppCh);
			}
		}
	}

	return TRUE;
}
