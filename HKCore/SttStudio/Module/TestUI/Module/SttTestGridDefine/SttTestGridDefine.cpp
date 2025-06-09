//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestGridDefine.cpp  CSttTestGridDefine


#include "stdafx.h"
#include "SttTestGridDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttTestGridDefine::CSttTestGridDefine()
{
	//初始化属性

	//初始化成员变量
}

CSttTestGridDefine::~CSttTestGridDefine()
{
}

long CSttTestGridDefine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttTestGridDefine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttTestGridDefine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttTestGridDefine::InitAfterRead()
{
}

BOOL CSttTestGridDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttTestGridDefine *p = (CSttTestGridDefine*)pObj;

	return TRUE;
}

BOOL CSttTestGridDefine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttTestGridDefine *p = (CSttTestGridDefine*)pDest;

	return TRUE;
}

CBaseObject* CSttTestGridDefine::Clone()
{
	CSttTestGridDefine *p = new CSttTestGridDefine();
	Copy(p);
	return p;
}

CBaseObject* CSttTestGridDefine::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttTestGridDefine *p = new CSttTestGridDefine();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttTestGridDefine::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDTESTMACRO)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttTestGridDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdTestMacroKey)
	{
		pNew = new CSttGdTestMacro();
	}

	return pNew;
}

CExBaseObject* CSttTestGridDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDTESTMACRO)
	{
		pNew = new CSttGdTestMacro();
	}

	return pNew;
}

CSttGdGridInst* CSttTestGridDefine::GetGridInst(const CString &strMacroID,const CString &strInstID)
{
	POS pos_macro = GetHeadPosition();
	CExBaseObject *pCurrMacroObj = NULL;
	CSttGdTestMacro *pSttGdTestMacro = NULL;

	while(pos_macro)
	{
		pCurrMacroObj = GetNext(pos_macro);

		if (pCurrMacroObj->GetClassID() != MNGRCLASSID_CSTTGDTESTMACRO)
		{
			continue;
		}

		pSttGdTestMacro = (CSttGdTestMacro *)pCurrMacroObj;

		if (pSttGdTestMacro->m_strMacroID != strMacroID)
		{
			continue;
		}

		CSttGdGridInsts *pSttGdGridInsts = (CSttGdGridInsts*)pSttGdTestMacro->FindByClassID(MNGRCLASSID_CSTTGDGRIDINSTS);

		if (pSttGdGridInsts == NULL)
		{
			return NULL;
		}

		return (CSttGdGridInst*)pSttGdGridInsts->FindByID(strInstID);
	}
	
	return NULL;
}
