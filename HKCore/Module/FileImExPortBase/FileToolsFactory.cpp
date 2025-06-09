#include "StdAfx.h"
#include "FileToolsFactory.h"

#include "..\API\FileApi.h"

CFileToolsFactory::CFileToolsFactory(void)
{
	
}

CFileToolsFactory::~CFileToolsFactory(void)
{
	m_listFileTool.DeleteAll();
}

CFileToolCreator* CFileToolsFactory::RegisterCreator(const CString &strName,const CString &strFilePostFix, PFILETOOLCREATE* pFunCreate)
{
	CFileToolCreator *pFind = (CFileToolCreator*)FindByID(strFilePostFix);
	ASSERT (pFind == NULL);

	pFind = new CFileToolCreator(strName, strFilePostFix, pFunCreate);
	AddNewChild(pFind);
	return pFind;
}

void CFileToolsFactory::GetAllFilters(CString &strFilter)
{
	POS pos = GetHeadPosition();
	CFileToolCreator *pFind = NULL;
	strFilter = _T("");

	while (pos != NULL)
	{
		pFind = (CFileToolCreator *)GetNext(pos);
		strFilter.AppendFormat(_T("%s(*.%s)|*.%s|"), m_strName, m_strID);
	}

	strFilter = _T("");
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pFind = (CFileToolCreator *)GetNext(pos);
		strFilter.AppendFormat(_T("%s(*.%s)|*.%s|"), pFind->m_strName, pFind->m_strID, pFind->m_strID);
	}

	strFilter += _T("|");
}

BOOL CFileToolsFactory::ExportFile(CExBaseObject *pObject, CWnd *pParentWnd, const CString &strPath, LPDISPATCH lpDispatch)
{
	CString strFilter;
	GetAllFilters(strFilter);
	ASSERT (strFilter.GetLength() > 4);

	CString strFile = strPath;
	
	if (PopupSaveAsFileDialog(pParentWnd, strFile, strFilter, _T("")))
	{
		TRACE (_T("%s"), strFile);
		ExportFile(pObject, strFile, lpDispatch);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CFileToolsFactory::ImportFile(CExBaseObject *pObject, CWnd *pParentWnd, const CString &strPath, LPDISPATCH lpDispatch)
{
	CString strFilter;
	GetAllFilters(strFilter);
	ASSERT (strFilter.GetLength() > 4);

	CString strFile = strPath;

	if (PopupOpenFileDialog(pParentWnd, strFile, strFilter, _T("")))
	{
		TRACE (_T("%s"), strFile);
		return ImportFile(pObject, strFile, lpDispatch);
	}
	else
	{
		return FALSE;
	}
}

BOOL CFileToolsFactory::ExportFile(CExBaseObject *pObject, const CString &strFile, LPDISPATCH lpDispatch)
{
	CFileToolInterface *pFileTool = CreateTool(strFile);
	ASSERT( pFileTool != NULL);

	if (pFileTool == NULL)
	{
		return FALSE;
	}

	pFileTool->SetRefObject( pObject );
	BOOL bTrue = pFileTool->ExportFile(strFile, lpDispatch);

	return bTrue;
}


BOOL CFileToolsFactory::ImportFile(CExBaseObject *pObject, const CString &strFile, LPDISPATCH lpDispatch)
{
	CFileToolInterface *pFileTool = CreateTool(strFile);
	ASSERT( pFileTool != NULL);

	if (pFileTool == NULL)
	{
		return FALSE;
	}

	pFileTool->SetRefObject( pObject );
	BOOL bTrue = pFileTool->ImportFile(strFile, lpDispatch);
	AfterImportFile(pFileTool->GetRefObject(), pFileTool->GetNewObject());

	return bTrue;
}

CFileToolInterface* CFileToolsFactory::CreateTool(const CString &strFile)
{
	CString strName, strPostFix;
	ParseFileNameAndPostfix(strFile, strName, strPostFix);
	CFileToolInterface *pFileTool = NULL;

	pFileTool = (CFileToolInterface*)m_listFileTool.FindByID(strPostFix);

	if (pFileTool == NULL)
	{
		CFileToolCreator *pCreator = (CFileToolCreator*)FindByID(strPostFix);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pFileTool = pCreator->Create();
		m_listFileTool.AddNewChild(pFileTool);
	}

	return pFileTool;
}

