//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenCfgDataMngrRule_Base.cpp  CIecGenCfgDataMngrRule_Base


#include "stdafx.h"
#include "IecGenCfgDataMngrRule_Base.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenCfgDataMngrRule_Base::CIecGenCfgDataMngrRule_Base()
{
	//初始化属性

	//初始化成员变量
#ifdef IECFG_USE_KEYDB
	m_pCtrlMatchList = NULL;
#endif
}

CIecGenCfgDataMngrRule_Base::~CIecGenCfgDataMngrRule_Base()
{
#ifdef IECFG_USE_KEYDB
	if (m_pCtrlMatchList != NULL)
	{
		delete m_pCtrlMatchList;
		m_pCtrlMatchList = NULL;
	}
#endif
}

#ifdef IECFG_USE_KEYDB
void CIecGenCfgDataMngrRule_Base::InitMatchList(CXKeyDB *pKeyDB)
{
	if (m_pCtrlMatchList == NULL)
	{
		m_pCtrlMatchList = new CXMatchList;
	}

	m_pCtrlMatchList->DeleteAll();
	m_pCtrlMatchList->Init(this,pKeyDB);
}
#endif

long CIecGenCfgDataMngrRule_Base::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_Base::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGenCfgDataMngrRule_Base::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIecGenCfgDataMngrRule_Base::InitAfterRead()
{
}

BOOL CIecGenCfgDataMngrRule_Base::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecGenCfgDataMngrRule_Base *p = (CIecGenCfgDataMngrRule_Base*)pObj;

	return TRUE;
}

BOOL CIecGenCfgDataMngrRule_Base::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecGenCfgDataMngrRule_Base *p = (CIecGenCfgDataMngrRule_Base*)pDest;

	return TRUE;
}

CBaseObject* CIecGenCfgDataMngrRule_Base::Clone()
{
	CIecGenCfgDataMngrRule_Base *p = new CIecGenCfgDataMngrRule_Base();
	Copy(p);
	return p;
}

CBaseObject* CIecGenCfgDataMngrRule_Base::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenCfgDataMngrRule_Base *p = new CIecGenCfgDataMngrRule_Base();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenCfgDataMngrRule_Base::CanPaste(UINT nClassID)
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

CExBaseObject* CIecGenCfgDataMngrRule_Base::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

CExBaseObject* CIecGenCfgDataMngrRule_Base::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
