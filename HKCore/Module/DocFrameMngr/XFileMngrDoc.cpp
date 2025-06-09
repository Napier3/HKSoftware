// XFileMngrDoc.cpp : 实现文件
//

#include "stdafx.h"
// #include "StationTestMain.h"
#include "XFileMngrDoc.h"


// CXFileMngrDoc

IMPLEMENT_DYNCREATE(CXFileMngrDoc, CDocument)

CXFileMngrDoc::CXFileMngrDoc()
{
}

BOOL CXFileMngrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CXFileMngrDoc::~CXFileMngrDoc()
{
}


BEGIN_MESSAGE_MAP(CXFileMngrDoc, CDocument)
END_MESSAGE_MAP()


// CXFileMngrDoc 诊断

#ifdef _DEBUG
void CXFileMngrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CXFileMngrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CXFileMngrDoc 序列化

void CXFileMngrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
#endif


// CXFileMngrDoc 命令

BOOL CXFileMngrDoc::XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists)
{
	return TRUE;
}


DWORD CXFileMngrDoc::XOpenXFile(CXFile *pFile)
{
	// 	CString strFile = pFile->GetTotalFileName();
	// 	CIecCfgFile *pIecFile = CIecCfgTool::FindIecFile(strFile);
	// 
	// 	if (pIecFile != NULL)
	// 	{
	// 		//激活当前文档
	// 		CFrameWnd *pFrameWnd = pIecFile->GetRefFrameWnd();
	// 		ASSERT (pFrameWnd != NULL);
	// 		ASSERT (pFrameWnd->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)) );
	// 		CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrameWnd;
	// 		pIecConfigFrame->ActivateFrame(1);
	// 	}
	// 	else
	// 	{
	// 		theApp.OpenIecCfgFile(strFile);
	// 		theApp.UpdateIecCfgFilesComboBox();
	// 	}

	return 0;
}


DWORD CXFileMngrDoc::XDeleteXFile(CXFile *pFile)
{
	// 	CString strFile = pFile->GetTotalFileName();
	// 	CIecCfgFile *pIecFile = CIecCfgTool::FindIecFile(strFile);
	// 
	// 	if (pIecFile != NULL)
	// 	{
	// 		CString strMsg;
	// 		strMsg.Format(_T("配置文件【%s】已经打开，不能删除！"), pFile->m_strName);
	// 		MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONWARNING);
	// 		return XFILEMNGR_OPTR_FAILED;
	// 	}
	// 	else
	// 	{
	// 
	// 	}

	return XFILEMNGR_OPTR_SUCC;
}

DWORD CXFileMngrDoc::XDeleteXFolder(CXFolder *pFolder)
{
	// 	BOOL bHas = CIecCfgTool::HasFileInFolder(pFolder);
	// 
	// 	if (bHas)
	// 	{
	// 		CString strMsg;
	// 		strMsg.Format(_T("目录【%s】包含已经打开的文件，不能删除！"), pFolder->m_strName);
	// 		MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONWARNING);
	// 		return XFILEMNGR_OPTR_FAILED;
	// 	}

	return XFILEMNGR_OPTR_SUCC;
}

DWORD CXFileMngrDoc::XEditXFile(CXFile *pFile, const CString &strDestName)
{
	// 	CString strSrcFile = pFile->GetTotalFileName();
	// 	CString strDestFile = pFile->GetRelativePath(TRUE);
	// 	strDestFile = GetPathFromFilePathName(strDestFile);
	// 	strDestFile += strDestName;
	// 	
	// 	::MoveFile(strSrcFile, strDestFile);
	// 	pFile->m_strName = GetPathFileNameFromFilePathName(strDestFile);
	// 	pFile->m_strID = pFile->m_strName;

	return 0;
}

DWORD CXFileMngrDoc::XCanEditXFolder(CXFolder *pFolder)
{
	// 	BOOL bHas = CIecCfgTool::HasFileInFolder(pFolder);
	// 
	// 	if (bHas)
	// 	{
	// 		CString strMsg;
	// 		strMsg.Format(_T("目录【%s】包含已经打开的文件，不能修改名称！"), pFolder->m_strName);
	// 		MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONWARNING);
	// 		return XFILEMNGR_OPTR_FAILED;
	// 	}

	return XFILEMNGR_OPTR_SUCC;
}

UINT CXFileMngrDoc::GetImgIndex(CExBaseObject *pObj)
{
	// 	UINT nClassID = pObj->GetClassID();
	// 
	// 	if (nClassID != CLASSID_XFILE)
	// 	{
	// 		return 0xFFFFFFFF;
	// 	}
	// 
	// 	//if (ATS_IsTestTaskFile(pObj->m_strName))
	// 	{
	// 		return 4;
	// 	}
	//else
	{
		return 2;
	}
}

DWORD CXFileMngrDoc::XDownLoad(CExBaseObject *pXFileObj)
{
	return 0;
}

DWORD CXFileMngrDoc::XUpload(CExBaseObject *pXFileObj)
{
	return 0;
}
