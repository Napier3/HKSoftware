#include "stdafx.h"
#include "XLuaToXvmToolBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CPpsReplaceBaseObj
CXLuaVarReplaceBaseObj::CXLuaVarReplaceBaseObj()
{
	m_nBufLength = 0;
	m_pRefSrcBuf  = NULL;
	m_pRefDestBuf = NULL;
	m_pTextRef = NULL;
	m_pPpScript = NULL;
}

CXLuaVarReplaceBaseObj::~CXLuaVarReplaceBaseObj()
{

}

long CXLuaVarReplaceBaseObj::CalBuffer()
{
	if (m_pTextRef == NULL)
	{
		return 0;
	}

	if (m_pTextRef->GetLength() < 100)
	{
		m_nBufLength = m_pTextRef->GetLength() + 100;
	}
	else
	{
		m_nBufLength = m_pTextRef->GetLength();
		m_nBufLength = m_nBufLength * 2;
	}

	return m_nBufLength;
}

void CXLuaVarReplaceBaseObj::BuidBuffer(TCHAR **ppBuffer)
{
	if (m_pTextRef == NULL || m_nBufLength == 0)
	{
		return;
	}

	m_pRefSrcBuf  = *ppBuffer;
	m_pRefDestBuf = m_pRefSrcBuf + m_nBufLength;
	*ppBuffer = m_pRefDestBuf + m_nBufLength;

#ifdef _UNICODE
	wcscpy(m_pRefSrcBuf, *m_pTextRef);
#else
	strcpy(m_pRefSrcBuf, *m_pTextRef);
#endif
}

BOOL CXLuaVarReplaceBaseObj::Replace(CXLuaVarReplacePara *pReplacePara, BOOL bValidSeparator)
{
#ifdef _UNICODE
	CStringVariableReplaceU oReplace;
#else
	CStringVariableReplace oReplace;
#endif

	//替换完成，交换位置
	if (oReplace.Replace(m_pRefSrcBuf, m_pRefDestBuf, pReplacePara->m_strSrcID, pReplacePara->m_strDestID, bValidSeparator) > 0)
	{
		TCHAR *pTemp = m_pRefDestBuf;
		m_pRefDestBuf = m_pRefSrcBuf;
		m_pRefSrcBuf = pTemp;
	}

	return TRUE;
}

BOOL CXLuaVarReplaceBaseObj::GetNextVarDef(TCHAR *pBuf, TCHAR *pBufEnd, TCHAR **ppVarBegin, TCHAR **ppVarEnd)
{
	TCHAR *pPos = pBuf;

	while ( ! CStringVariableReplaceU::IsVariableChar( *pPos) )
	{
		pPos++;
	}

	*ppVarBegin = pPos;

	while (CStringVariableReplaceU::IsVariableChar( *pPos))
	{
		pPos++;
	}

	*ppVarEnd = pPos;

	return *ppVarEnd > *ppVarBegin;
}

void CXLuaVarReplaceBaseObj::Offset(TCHAR* &pBuf)
{
	while (TRUE)
	{
		if ((*pBuf == ' ') || (*pBuf == '\t'))
		{
			pBuf++;
		}
		else
		{
			break;
		}
	}
}

void CXLuaVarReplaceBaseObj::CopyVars(TCHAR* &pCurr, long nSrcLen, TCHAR* &pEnd, TCHAR * &pDestCurr, TCHAR* &pBegin, long &nReplaceCount)
{
	long nCopyLen = 0, nVarLen = 0;
	TCHAR *pVarBegin = NULL, *pVarEnd = NULL;

	GetNextVarDef(pCurr+nSrcLen, pEnd, &pVarBegin, &pVarEnd);
	nCopyLen = pVarEnd - pCurr;

#ifdef _UNICODE
	wcsncpy(pDestCurr, pCurr, nCopyLen);
#else
	strncpy(pDestCurr, pCurr, nCopyLen);
#endif	

	pDestCurr += nCopyLen;

#ifdef _UNICODE
	wcscpy(pDestCurr, _T(";\r\n"));
#else
	strcpy(pDestCurr, _T(";\r\n"));
#endif
	
	pDestCurr += 3;
	pCurr = pCurr + nCopyLen;

	while (TRUE)
	{
		Offset(pCurr);

		if (*pCurr == ',')
		{
			pCurr++;

#ifdef _UNICODE
			wcscpy(pDestCurr, _T("var "));
#else
			strcpy(pDestCurr, _T("var "));
#endif
			pDestCurr += 4;

			GetNextVarDef(pCurr, pEnd, &pVarBegin, &pVarEnd);
			nCopyLen = pVarEnd - pCurr;

#ifdef _UNICODE
			wcsncpy(pDestCurr, pCurr, nCopyLen);
#else
			strncpy(pDestCurr, pCurr, nCopyLen);
#endif	
			pDestCurr += nCopyLen;

#ifdef _UNICODE
			wcscpy(pDestCurr, _T(";\r\n"));
#else
			strcpy(pDestCurr, _T(";\r\n"));
#endif
			pDestCurr += 3;
			pCurr = pCurr + nCopyLen;
		}
		else
		{
			break;
		}
	}

	nVarLen = pVarEnd - pVarBegin;
	TCHAR *pTemp = pVarEnd;

	Offset(pTemp);

	if (*pTemp != ';')
	{//var v=0;  
#ifdef _UNICODE
		wcsncpy(pDestCurr, pVarBegin, nVarLen);
#else
		strncpy(pDestCurr, pVarBegin, nVarLen);
#endif

		pDestCurr += nVarLen;
	}
	else
	{	//var v;  的情况
		//跳过 ";\r\n" 
		Offset(pCurr);
		pCurr++;
		Offset(pCurr);
	}

	pBegin = pCurr;
	nReplaceCount++;
}

void CXLuaVarReplaceBaseObj::ProcessVarDef()
{
	if (m_pTextRef == NULL)
	{
		return ;
	}

#ifdef _UNICODE
	ZeroMemory(m_pRefDestBuf, m_nBufLength * 2 - 10);
#else
	ZeroMemory(m_pRefDestBuf, m_nBufLength - 10);
#endif

	TCHAR pszVarKey[4];
#ifdef _UNICODE
	wcscpy(pszVarKey, _T("var"));
#else
	strcpy(pszVarKey, _T("var"));
#endif

	long nSrcLen = 3;
	TCHAR *pCurr = m_pRefSrcBuf;
	TCHAR *pDestCurr = m_pRefDestBuf;
	long nLen = abs(pCurr-pDestCurr);
	TCHAR *pEnd = pCurr + nLen;
	long nReplaceCount = 0;
	TCHAR *pVarBegin = NULL, *pVarEnd = NULL;
	long nCopyLen = 0, nVarLen = 0;
	TCHAR *pBegin = NULL;

	if ( ! CStringVariableReplaceU::IsVariableChar(*(pCurr + nSrcLen)))
	{
#ifdef _UNICODE
		if (wcsncmp(pCurr, pszVarKey, nSrcLen) == 0)
		{
#else
		if (strncmp(pCurr, pszVarKey, nSrcLen) == 0)
		{
#endif
			CopyVars(pCurr, nSrcLen, pEnd, pDestCurr, pBegin, nReplaceCount);
// 			GetNextVarDef(pCurr+nSrcLen, pEnd, &pVarBegin, &pVarEnd);
// 			nCopyLen = pVarEnd - pCurr;
// 
// 			wcsncpy(pDestCurr, pCurr, nCopyLen);
// 			pDestCurr += nCopyLen;
// 			wcscpy(pDestCurr, _T(";\r\n"));
// 			pDestCurr += 3;
// 			nVarLen = pVarEnd - pVarBegin;
// 			wcsncpy(pDestCurr, pVarBegin, nVarLen);
// 			pDestCurr += nVarLen;
// 
// 			pCurr = pCurr + nCopyLen;
// 			nReplaceCount++;
		}
	}

	pBegin = pCurr;

	while (pCurr < pEnd)
	{
		if (*pCurr == 0)
		{
			break;
		}

		//当前字符为分隔符号，字符串长度之外的也是分隔符
		if ((!CStringVariableReplaceU::IsVariableChar(*(pCurr))) && (!CStringVariableReplaceU::IsVariableChar(*(pCurr+nSrcLen+1)))  )
		{
#ifdef _UNICODE
			if (wcsncmp(pCurr+1, pszVarKey, nSrcLen) == 0)
			{
#else
			if (strncmp(pCurr+1, pszVarKey, nSrcLen) == 0)
			{
#endif
				pCurr++;

				//拷贝其他字符串数据 
				if (pBegin != NULL)
				{
					nCopyLen =  pCurr - pBegin;
#ifdef _UNICODE
					wcsncpy(pDestCurr, pBegin, nCopyLen);
#else
					strncpy(pDestCurr, pBegin, nCopyLen);
#endif	
					pDestCurr += nCopyLen;
				}

				CopyVars(pCurr, nSrcLen, pEnd, pDestCurr, pBegin, nReplaceCount);
			}
			else
			{
				pCurr++;		
			}
		}
		else
		{
			pCurr++;
		}
	}

	if (nReplaceCount > 0)
	{
		if (pBegin != pCurr)
		{
			nCopyLen =  pCurr - pBegin+1;
#ifdef _UNICODE
			wcsncpy(pDestCurr, pBegin, nCopyLen);
#else
			strncpy(pDestCurr, pBegin, nCopyLen);
#endif	
			pDestCurr += nCopyLen;
		}

		*pDestCurr = 0;

		pDestCurr = m_pRefDestBuf;
		m_pRefDestBuf = m_pRefSrcBuf;
		m_pRefSrcBuf = pDestCurr;
	}

}

BOOL CXLuaVarReplaceBaseObj::FinishReplace()
{
	if (m_pTextRef == NULL)
	{
		return TRUE;
	}

	*m_pTextRef = m_pRefSrcBuf;

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//CPpsItemDvmReplace
BOOL CXLuaToXvmToolBase::g_bShowReplaceItemPath = TRUE;

CXLuaToXvmToolBase::CXLuaToXvmToolBase()
{
	m_pObjctDest = NULL;
	m_pTemplate = NULL;

	m_pBufferForReplace = NULL;
	m_nLenBufferForReplace = 0;
	m_bFileVarReplace = FALSE;

	CString strFile;
	strFile = _P_GetBinPath();
	strFile += _T("GbLuaToXvmTool.txt");
	m_bFileVarReplace = m_fileVarReplace.Open(strFile, CFile::modeCreate | CFile::modeWrite);
}

CXLuaToXvmToolBase::~CXLuaToXvmToolBase()
{
	if (m_pBufferForReplace != NULL)
	{
		delete m_pBufferForReplace;
		m_pBufferForReplace = NULL;
	}

	if (m_bFileVarReplace)
	{
		m_fileVarReplace.Close();
	}
}

BOOL CXLuaToXvmToolBase::LuaToXvm(const CString &strFile, CString &strDestFile)
{
	CFile oFile;

	if (! oFile.Open(strFile, CFile::modeRead))
	{
		return FALSE;
	}

	long nLen = oFile.GetLength();
	char *pBuffer = new char [nLen+10];
	oFile.Read(pBuffer, nLen);
	pBuffer[nLen] = 0;
	m_strLuaToXvmScript = pBuffer;
	delete pBuffer;
	oFile.Close();

	CXLuaVarReplaceBaseObj *pNew = new CXLuaVarReplaceBaseObj();
	pNew->m_pTextRef = &m_strLuaToXvmScript;
	pNew->m_pPpScript = NULL;
	AddTail(pNew);

	BuildBuffer();
	LuaToXvm();

	strDestFile = strFile.Left(strFile.GetLength() - 4);
	strDestFile += _T("_Xvm.txt");
	
	oFile.Open(strDestFile, CFile::modeCreate | CFile::modeWrite);

#ifdef _UNICODE
	oFile.Write(m_strLuaToXvmScript, m_strLuaToXvmScript.GetLength()*2);
#else
	oFile.Write(m_strLuaToXvmScript, m_strLuaToXvmScript.GetLength());
#endif
	oFile.Close();

	return TRUE;
}

BOOL CXLuaToXvmToolBase::LuaToXvm(CExBaseList *pTemplate)
{
	m_pTemplate = pTemplate;

	if (!NeedLuaToXVM(pTemplate))
	{
		return FALSE;
	}
// 	if (pTemplate->IsScriptType_XVM())
// 	{
// 		return FALSE;
// 	}
// 
// 	pTemplate->SetScriptType_XVM();

	BuildRepalce(m_pTemplate);

	LuaToXvm();

	return TRUE;
}

//2020-7-9 lijunqing  额外的替换
void CXLuaToXvmToolBase::ReplaceEx()
{
}

void CXLuaToXvmToolBase::LuaToXvm()
{
	Replace(_T("if"), _T("if("));
	Replace(_T("then"), _T(")\r\n{"));
	Replace(_T("else"), _T("}\r\nelse\r\n{"));
	Replace(_T("elseif"), _T("}\r\nelse if("));
	Replace(_T("end"), _T("}"));
	Replace(_T("local"), _T("var"));
	Replace(_T("string.format"), _T("strformat"));
	Replace(_T("math.abs"), _T("abs"));
	Replace(_T("and"), _T("&&"));
	Replace(_T("or"), _T("||"));
	Replace(_T("not"), _T("!"));
	Replace(_T("ShowMsg"), _T("//ShowMsg"));
	Replace(_T("--"), _T("//"), FALSE);
	Replace(_T("//[["), _T("/*"), FALSE);
	Replace(_T("//]]"), _T("*/"), FALSE);
	Replace(_T("#"), _T(" "), FALSE);
	Replace(_T("\\\\"), _T("/"), FALSE);

	ReplaceEx();

	ProcessVarDef();

	FinishReplace();
}

void CXLuaToXvmToolBase::ProcessVarDef()
{
	POS pos = GetHeadPosition();
	CXLuaVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CXLuaVarReplaceBaseObj*)GetNext(pos);
		p->ProcessVarDef();
	} 
}

void CXLuaToXvmToolBase::BuildRepalce(CExBaseList *pPpObjcts)
{
	ASSERT (pPpObjcts != NULL);

	if (pPpObjcts == NULL)
	{
		return;
	}

	m_pObjctDest = pPpObjcts;
// 	UINT nClassID = m_pObjctDest->GetClassID();
// 	CPpTemplate *pPpTemplate = (CPpTemplate *)m_pObjctDest->GetAncestor(PPCLASSID_PPTEMPLATE);

	BuildItems(m_pObjctDest);

	BuildBuffer();
}

void CXLuaToXvmToolBase::Replace(const CString &strSrcID, const CString &strDestID, BOOL bValidSeparator)
{
	if (m_bFileVarReplace)
	{
		static CString strTextArrow = _T("==>>");
		static CString strTextLn = _T("\r\n");

#ifdef _UNICODE
		m_fileVarReplace.Write(strSrcID, strSrcID.GetLength()*2);
		m_fileVarReplace.Write(strTextArrow, 8);
		m_fileVarReplace.Write(strDestID, strDestID.GetLength()*2);
		m_fileVarReplace.Write(strTextLn, 4);
#else
		m_fileVarReplace.Write(strSrcID, strSrcID.GetLength());
		m_fileVarReplace.Write(strTextArrow, 4);
		m_fileVarReplace.Write(strDestID, strDestID.GetLength());
		m_fileVarReplace.Write(strTextLn, 2);
#endif
	}

	if (strSrcID.GetLength() == 0 || strDestID.GetLength() == 0)
	{
		return;
	}

	CXLuaVarReplacePara oReplacePara;
	oReplacePara.m_pDestDataRef = NULL;
	oReplacePara.m_strSrcID = strSrcID;
	oReplacePara.m_strDestID = strDestID;

	POS pos = GetHeadPosition();
	CXLuaVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CXLuaVarReplaceBaseObj*)GetNext(pos);
		p->Replace(&oReplacePara, bValidSeparator);
	}
}

void CXLuaToXvmToolBase::FinishReplace()
{
	POS pos = GetHeadPosition();
	CXLuaVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CXLuaVarReplaceBaseObj*)GetNext(pos);
		p->FinishReplace();
	}
}

void CXLuaToXvmToolBase::BuildItems(CExBaseList *pPpObjctDest)
{
	POS pos = pPpObjctDest->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pPpObjctDest->GetNext(pos);

		//if (PPCLASSID_PPSCRIPT == p->GetClassID())
		if (IsScript(p))
		{
			BuildItem(p);
		}
		else if (p->IsBaseList())
		{
			BuildItems((CExBaseList*)p);
		}
	}
}

void CXLuaToXvmToolBase::BuildItem(CExBaseObject *pPpObjctDest)
{
	if (!NeedBuild(pPpObjctDest))
	{
		return;
	}

	CXLuaVarReplaceBaseObj *pNew = new CXLuaVarReplaceBaseObj();
	pNew->m_pTextRef = GetItemScript(pPpObjctDest);
	pNew->m_pPpScript = pPpObjctDest;
	AddTail(pNew);
}
//
// void CXLuaToXvmToolBase::ShowReplaceItemPath(CExBaseObject *pItem)
// {
// 	if (g_bShowReplaceItemPath)
// 	{
// 		CExBaseObject *pAncesster = (CExBaseObject*)pItem->GetAncestor(PPCLASSID_PPPROCEDURES);
// 		CString strPath;
// 
// 		if (pAncesster != NULL)
// 		{
// 			strPath = pItem->GetNamePathEx(PPCLASSID_PPPROCEDURES, FALSE);
// 		}
// 		else
// 		{
// 			pAncesster = (CExBaseObject*)pItem->GetAncestor(PPCLASSID_PPPAKAGES);
// 
// 			if (pAncesster != NULL)
// 			{
// 				strPath = pItem->GetNamePathEx(PPCLASSID_PPPAKAGES, FALSE);
// 			}
// 		}
// 		
// 		if (strPath.GetLength() > 0)
// 		{
// 			CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
// 		}
// 	}
// }

void CXLuaToXvmToolBase::BuildBuffer()
{
	POS pos = GetHeadPosition();
	CXLuaVarReplaceBaseObj *p = NULL;
	m_nLenBufferForReplace = 0;
	TCHAR *pPosBuffer = NULL;

	while (pos != NULL)
	{
		p = (CXLuaVarReplaceBaseObj*)GetNext(pos);
		m_nLenBufferForReplace += p->CalBuffer();
	}

	m_nLenBufferForReplace *= 2;
	m_pBufferForReplace = new TCHAR[m_nLenBufferForReplace+1000];
	pPosBuffer = m_pBufferForReplace;
	ZeroMemory(m_pBufferForReplace, sizeof(TCHAR) * (m_nLenBufferForReplace+1000));
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXLuaVarReplaceBaseObj*)GetNext(pos);
		p->BuidBuffer(&pPosBuffer);
	}
}

