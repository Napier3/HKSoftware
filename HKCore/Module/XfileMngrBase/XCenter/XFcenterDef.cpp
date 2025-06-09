#include "StdAfx.h"
#include "XFcenterDef.h"

//////////////////////////////////////////////////////////////////////////
//CXFcenterFile
CXFcenterFile::CXFcenterFile()
{
	ZeroMemory(&m_dtTime, sizeof(m_dtTime));
	m_nFileSize = 0;
}

CXFcenterFile::~CXFcenterFile()
{

}

long CXFcenterFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_dtTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nFileSize);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_dtTime);
		BinarySerializeRead(oBinaryBuffer, m_nFileSize);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_dtTime);
		BinarySerializeWrite(oBinaryBuffer, m_nFileSize);
	}

	return 0;
}

BOOL CXFcenterFile::CopyOwn(CBaseObject* pDest)
{
	CXFcenterFile *pFile = (CXFcenterFile*)pDest;

	pFile->m_strID = m_strID;
	pFile->m_dtTime = m_dtTime;
	pFile->m_nFileSize = m_nFileSize;

	return TRUE;
}

CBaseObject* CXFcenterFile::Clone()
{
	CXFcenterFile *pNew = new CXFcenterFile();
	Copy(pNew);

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
//CXFcenterFolder
CXFcenterFolder::CXFcenterFolder()
{

}

CXFcenterFolder::~CXFcenterFolder()
{

}

long CXFcenterFolder::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_dtTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_dtTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_dtTime);
	}

	return 0;
}

BOOL CXFcenterFolder::CopyOwn(CBaseObject* pDest)
{
	CXFcenterFolder *pFolder = (CXFcenterFolder*)pDest;

	pFolder->m_strID = m_strID;
	pFolder->m_dtTime = m_dtTime;

	return TRUE;
}

CBaseObject* CXFcenterFolder::Clone()
{
	CXFcenterFolder *pNew = new CXFcenterFolder();
	Copy(pNew);

	return pNew;
}

CExBaseObject* CXFcenterFolder::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if (nClassID == XFCENTER_FILE)
	{
		return new CXFcenterFile();
	}

	if (nClassID == XFCENTER_FOLDER)
	{
		return new CXFcenterFolder();
	}

	return NULL;
}
// 
// void XFile_QueryAllFiles(CXFolder *pFolder, CXFcenterFolder *pDest)
// {
// 	POS pos = pFolder->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	CString strFile;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CExBaseObject *)pFolder->GetNext(pos);
// 
// 		if (p->GetClassID() == CLASSID_XFOLDER)
// 		{
// 			CXFcenterFolder *pNewFolder = new CXFcenterFolder();
// 			pNewFolder->m_strID = p->m_strID;
// 			pDest->AddNewChild(pNewFolder);
// 			strFile = ((CXFolder*)p)->GetFolderPath();
// 
// 			if (strFile.Right(1) == _T("\\"))
// 			{
// 				strFile = strFile.Left(strFile.GetLength() - 1);
// 			}
// 
// 			xfile_GetFileInfo(strFile, pNewFolder->m_nFileSize, pNewFolder->m_dtTime);
// 			XFile_QueryAllFiles((CXFolder*)p, pNewFolder);
// 		}
// 		else
// 		{
// 			CXFcenterFile *pNewFile = new CXFcenterFile();
// 			pNewFile->m_strID = p->m_strID;
// 			strFile = ((CXFile*)p)->GetTotalFileName();
// 			xfile_GetFileInfo(strFile, pNewFile->m_nFileSize, pNewFile->m_dtTime);
// 			pDest->AddNewChild(pNewFile);
// 		}
// 	}
// }

void xfcenter_log_thread_param(XFCENTER_THREAD_PARAM *pParam)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>>%s:%s"), pParam->strCmdID, pParam->strBucket);

	long nCount = pParam->astrPath.GetCount();
	long nIndex = 0;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("************%s"), pParam->astrPath.GetAt(nIndex));
	}
}


void xfcenter_set_thread_finish(XFCENTER_THREAD_PARAM *pParam)
{
	ASSERT (pParam != NULL);

	if (pParam->pbXFcenterFinish != NULL)
	{
		*pParam->pbXFcenterFinish = TRUE;
	}

	if (pParam->pEvent != NULL)
	{
		pParam->pEvent->SetEvent();
	}

	if (pParam->pThread != NULL && pParam->nCmdFinishMsg > 0)
	{
		pParam->pThread->PostThreadMessage(pParam->nCmdFinishMsg, 0, 0);
	}
// 	if (pParam->pMsgRcv != NULL && pParam->nMsg != 0)
// 	{
// 		if (::IsWindow(pParam->pMsgRcv->m_hWnd))
// 		{
// 			pParam->pMsgRcv->PostMessage(pParam->nMsg, 0, 0);
// 		}
// 	}
}

//////////////////////////////////////////////////////////////////////////
//
/*
CXFolder* xfcenter_add_folder(CXFileMngr *pXFileMngr, const CString &strFolder)
{
	if (strFolder.GetLength() == 0)
	{
		return pXFileMngr;
	}

	CXFolder *pFolderNew = NULL;
	CStringArray astrID;
	xfile_SplitPath(strFolder, astrID);
	long nCount = astrID.GetCount();
	long nIndex = 0;
	CString strID;
	CXFolder *pParentFolder = pXFileMngr;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strID = astrID.GetAt(nIndex);
		pFolderNew = (CXFolder*)pParentFolder->FindByID(strID);

		if (pFolderNew == NULL)
		{
			pFolderNew = new CXFolder();
			pFolderNew->m_strID = strID;
			pFolderNew->m_strName = strID;
			pParentFolder->AddNewChild(pFolderNew);
		}

		pFolderNew->SetYunFolder();
		pParentFolder = pFolderNew;
	}

	return pFolderNew;
}

CXFile* xfcenter_add_file(CXFileMngr *pXFileMngr, const CString &strPath)
{
	if (strPath.GetLength() == 0)
	{
		return NULL;
	}

	CString strFolder = GetPathFromFilePathName(strPath);
	CString strFile = GetPathFileNameFromFilePathName(strPath);

	CXFolder *pFolder = xfcenter_add_folder(pXFileMngr, strFolder);
	CString strTemp = strFile;
	CXFile *pFile = (CXFile*)pFolder->FindByLowerName(strFile);

	if (pFile == NULL)
	{
		pFile = new CXFile();
		pFile->m_strName = strTemp;
		pFile->m_strID = strTemp;
		pFile->m_strFileName = strTemp;
		pFolder->AddNewChild(pFile);
	}

	pFile->SetYunFile();

	return pFile;
}
*/
BOOL g_bLogXFcenterTransInfo = FALSE;