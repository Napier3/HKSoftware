//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgDataMngrRule_SMV.cpp  CIecGenCfgDataMngrRule_SMV


#include "stdafx.h"
#include "IecGenCfgDataMngrRule_SMV.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgDataMngrRule_SMV::CIecGenCfgDataMngrRule_SMV()
{
	//初始化属性

	//初始化成员变量
}

CIecGenCfgDataMngrRule_SMV::~CIecGenCfgDataMngrRule_SMV()
{
}

long CIecGenCfgDataMngrRule_SMV::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecGenCfgDataMngrRule_Base::XmlReadOwn(oNode, pXmlRWKeys);
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_SMV::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecGenCfgDataMngrRule_Base::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_SMV::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecGenCfgDataMngrRule_SMV::InitAfterRead()
{
}

BOOL CIecGenCfgDataMngrRule_SMV::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecGenCfgDataMngrRule_Base::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenCfgDataMngrRule_SMV *p = (CIecGenCfgDataMngrRule_SMV*)pObj;

	return TRUE;
}

BOOL CIecGenCfgDataMngrRule_SMV::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecGenCfgDataMngrRule_Base::CopyOwn(pDest);

	CIecGenCfgDataMngrRule_SMV *p = (CIecGenCfgDataMngrRule_SMV*)pDest;

	return TRUE;
}

CBaseObject* CIecGenCfgDataMngrRule_SMV::Clone()
{
	CIecGenCfgDataMngrRule_SMV *p = new CIecGenCfgDataMngrRule_SMV();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgDataMngrRule_SMV::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgDataMngrRule_SMV *p = new CIecGenCfgDataMngrRule_SMV();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgDataMngrRule_SMV::CanPaste(UINT nClassID)
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

CExBaseObject* CIecGenCfgDataMngrRule_SMV::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

CExBaseObject* CIecGenCfgDataMngrRule_SMV::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
// 
// BOOL CIecGenCfgDataMngrRule_SMV::GenarateIecCfgDatasSMV(CIecCfgDatasSMV *pSmvMngr)
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
// 			pCurCtrlBlock->GenerateIecCfgDatas(pSmvMngr);
// 		}
// 	}
// 
// 	return TRUE;
// }
