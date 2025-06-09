//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchToolBase.cpp  CXMatchToolBase


#include "stdafx.h"
#include "XMatchToolBase.h"
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchToolBase::CXMatchToolBase()
{
	//初始化属性

	//初始化成员变量
	m_pKeyDB = NULL;
}

CXMatchToolBase::~CXMatchToolBase()
{
}

BOOL CXMatchToolBase::IsMatchValid()
{
	return m_listDst.IsXMatchValid();
}

BOOL CXMatchToolBase::IsXMatchValid_LEqual_1()
{
	return m_listDst.IsXMatchValid_LEqual_1();
}

void CXMatchToolBase::Match(CXKeyDB *pKeyDB, CExBaseList *pSrcRefList, CExBaseList *pDstRefList, long nMatchRatio, CThreadProgressInterface *pThradProgress)
{
	ASSERT (pKeyDB != NULL);
	ASSERT (pSrcRefList != NULL);
	ASSERT (pDstRefList != NULL);

	long nSteps = pDstRefList->GetCount() + pSrcRefList->GetCount();
	m_pKeyDB = pKeyDB;
	m_listDst.DeleteAll();
	m_listSrc.DeleteAll();

	m_listSrc.Init(pSrcRefList, pKeyDB, pThradProgress);
	m_listDst.Init(pDstRefList, pKeyDB, pThradProgress);

	m_listDst.Match(&m_listSrc, nMatchRatio, pThradProgress, TRUE);
	m_pSrcRefList = pSrcRefList;
}

void CXMatchToolBase::MatchRead(CXMatchDatarefs *pXMatchDatarefs, CExBaseList *pListSrcRefList, CExBaseList *pDstRefList, UINT nRootClassID)
{
	CExBaseList oListDestDatas;
	POS pos = pListSrcRefList->GetHeadPosition();
	CExBaseList *pSrcRefList = NULL;

	while (pos != NULL)
	{
		pSrcRefList = (CExBaseList *)pListSrcRefList->GetNext(pos);
		oListDestDatas.Append(pSrcRefList);
	}

	MatchReadSingle(pXMatchDatarefs, &oListDestDatas, pDstRefList, nRootClassID);

	oListDestDatas.RemoveAll();
}


void CXMatchToolBase::MatchReadSingle(CXMatchDatarefs *pXMatchDatarefs, CExBaseList *pSrcRefList, CExBaseList *pDstRefList, UINT nRootClassID)
{
	POS pos = NULL;
	pos = m_listDst.GetHeadPosition();
	CXMatchObject *pXMatchObj = NULL;
	CExBaseObject *pRef = NULL;
	CXMatchDataref *pDataRef = NULL;

	while (pos != NULL)
	{
		pXMatchObj = (CXMatchObject *)m_listDst.GetNext(pos);
		pDataRef = pXMatchDatarefs->FindBySrcPath(pXMatchObj->m_pRefObject->GetIDPathEx(nRootClassID));

		if (pDataRef != NULL)
		{
			pRef = pSrcRefList->FindByIDPathEx(nRootClassID, FALSE, pDataRef->m_strDestPath);

			if (pRef != NULL)
			{
				pXMatchObj->SetMacthRefObj(pRef);
			}
			else
			{
				pXMatchObj->SetMacthRefObj(NULL);
			}
		}
		else
		{
			pXMatchObj->SetMacthRefObj(NULL);
		}
	}
}


CString wzd_GetXMatchFilePath()
{
	CString strPath;

	strPath = _P_GetLibraryPath();
	strPath += _T("GbXMatchFiles\\");
	return strPath;
}

CString wzd_GetXMatchFileDlgFilter()
{
	CString strFilter;
    strFilter.Format(_T("%s|(*.%s)||"), g_sLangTxt_TemDataFileChange.GetString()/*g_strGbXMatchFileName*/, g_strGbXMatchFilePostFix.GetString());
	return strFilter;
}

