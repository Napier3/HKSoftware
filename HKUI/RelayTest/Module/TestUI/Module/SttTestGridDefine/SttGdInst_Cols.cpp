//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdInst_Cols.cpp  CSttGdInst_Cols


#include "stdafx.h"
#include "SttGdInst_Cols.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdInst_Cols::CSttGdInst_Cols()
{
	//初始化属性

	//初始化成员变量
}

CSttGdInst_Cols::~CSttGdInst_Cols()
{
}

long CSttGdInst_Cols::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdInst_Cols::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdInst_Cols::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdInst_Cols::InitAfterRead()
{
}

BOOL CSttGdInst_Cols::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdInst_Cols *p = (CSttGdInst_Cols*)pObj;

	return TRUE;
}

BOOL CSttGdInst_Cols::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdInst_Cols *p = (CSttGdInst_Cols*)pDest;

	return TRUE;
}

CBaseObject* CSttGdInst_Cols::Clone()
{
	CSttGdInst_Cols *p = new CSttGdInst_Cols();
	Copy(p);
	return p;
}

CBaseObject* CSttGdInst_Cols::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdInst_Cols *p = new CSttGdInst_Cols();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdInst_Cols::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDINST_COL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdInst_Cols::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdInst_ColKey)
	{
		pNew = new CSttGdInst_Col();
	}

	return pNew;
}

CExBaseObject* CSttGdInst_Cols::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDINST_COL)
	{
		pNew = new CSttGdInst_Col();
	}

	return pNew;
}

BOOL CSttGdInst_Cols::GetGridColsTitleWidth(CString *pstrTitle,int *pnWidth,int nCols)
{
	long nIndex = 0;
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)GetNext(pos);

		if (pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
		{
			nIndex++;
			continue;
		}

		pstrTitle[nIndex] = pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName;
		pnWidth[nIndex] = pSttGdInst_Col->m_pSttGdColDef_Ref->m_nWidth;
		nIndex++;

		if (nIndex>nCols)
		{
			break;
		}
	}

	if (nCols != nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

void CSttGdInst_Cols::InitGridCols(CSttGdGridDefine *pSttGdGridDefine)
{
	CString strParentGridID;
	CExBaseObject *pParent = (CExBaseObject *)GetParent();

	if (pParent != NULL)
	{
		strParentGridID = pParent->m_strID;
	}

	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)GetNext(pos);
		pSttGdInst_Col->m_pSttGdColDef_Ref = (CSttGdColDef*)pSttGdGridDefine->FindByID(pSttGdInst_Col->m_strID);

		if (pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("表格(%s)对应列(%s)在对应表格列定义链表中未查找到."),strParentGridID.GetString(),pSttGdInst_Col->m_strID.GetString());
		}
	}
}