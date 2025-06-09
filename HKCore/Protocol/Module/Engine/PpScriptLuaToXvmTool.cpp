#include "stdafx.h"
#include "PpScriptLuaToXvmTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 
// //////////////////////////////////////////////////////////////////////////
// //CPpsReplaceBaseObj
// CPpsVarReplaceBaseObj::CPpsVarReplaceBaseObj()
// {
// 	m_nBufLength = 0;
// 	m_pRefSrcBuf  = NULL;
// 	m_pRefDestBuf = NULL;
// 	m_pTextRef = NULL;
// 	m_pPpScript = NULL;
// }
// 
// CPpsVarReplaceBaseObj::~CPpsVarReplaceBaseObj()
// {
// 
// }
// 
// long CPpsVarReplaceBaseObj::CalBuffer()
// {
// 	if (m_pTextRef == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	if (m_pTextRef->GetLength() < 100)
// 	{
// 		m_nBufLength = m_pTextRef->GetLength() + 100;
// 	}
// 	else
// 	{
// 		m_nBufLength = m_pTextRef->GetLength();
// 		m_nBufLength = m_nBufLength * 2;
// 	}
// 
// 	return m_nBufLength;
// }
// 
// void CPpsVarReplaceBaseObj::BuidBuffer(TCHAR **ppBuffer)
// {
// 	if (m_pTextRef == NULL || m_nBufLength == 0)
// 	{
// 		return;
// 	}
// 
// 	m_pRefSrcBuf  = *ppBuffer;
// 	m_pRefDestBuf = m_pRefSrcBuf + m_nBufLength;
// 	*ppBuffer = m_pRefDestBuf + m_nBufLength;
// 
// #ifdef _UNICODE
// 	wcscpy(m_pRefSrcBuf, *m_pTextRef);
// #else
// 	strcpy(m_pRefSrcBuf, *m_pTextRef);
// #endif
// }
// 
// BOOL CPpsVarReplaceBaseObj::Replace(CPpsVarReplacePara *pReplacePara, BOOL bValidSeparator)
// {
// #ifdef _UNICODE
// 	CStringVariableReplaceU oReplace;
// #else
// 	CStringVariableReplace oReplace;
// #endif
// 
// 	//替换完成，交换位置
// 	if (oReplace.Replace(m_pRefSrcBuf, m_pRefDestBuf, pReplacePara->m_strSrcID, pReplacePara->m_strDestID, bValidSeparator) > 0)
// 	{
// 		TCHAR *pTemp = m_pRefDestBuf;
// 		m_pRefDestBuf = m_pRefSrcBuf;
// 		m_pRefSrcBuf = pTemp;
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CPpsVarReplaceBaseObj::GetNextVarDef(wchar_t *pBuf, wchar_t *pBufEnd, wchar_t **ppVarBegin, wchar_t **ppVarEnd)
// {
// 	wchar_t *pPos = pBuf;
// 
// 	while ( ! CStringVariableReplaceU::IsVariableChar( *pPos) )
// 	{
// 		pPos++;
// 	}
// 
// 	*ppVarBegin = pPos;
// 
// 	while (CStringVariableReplaceU::IsVariableChar( *pPos))
// 	{
// 		pPos++;
// 	}
// 
// 	*ppVarEnd = pPos;
// 
// 	return *ppVarEnd > *ppVarBegin;
// }
// 
// void CPpsVarReplaceBaseObj::ProcessVarDef()
// {
// 	if (m_pTextRef == NULL)
// 	{
// 		return ;
// 	}
// 
// 	ZeroMemory(m_pRefDestBuf, m_nBufLength * 2 - 10);
// 	wchar_t pszVarKey[4];
// 	wcscpy(pszVarKey, L"var");
// 	long nSrcLen = 3;
// 	wchar_t *pCurr = m_pRefSrcBuf;
// 	wchar_t *pDestCurr = m_pRefDestBuf;
// 	long nLen = abs(pCurr-pDestCurr);
// 	wchar_t *pEnd = pCurr + nLen;
// 	long nReplaceCount = 0;
// 	wchar_t *pVarBegin = NULL, *pVarEnd = NULL;
// 	long nCopyLen = 0, nVarLen = 0;
// 	const wchar_t *pBegin = NULL;
// 
// 	if ( ! CStringVariableReplaceU::IsVariableChar(*(pCurr + nSrcLen)))
// 	{
// 		if (wcsncmp(pCurr, pszVarKey, nSrcLen) == 0)
// 		{
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
// 		}
// 	}
// 
// 	pBegin = pCurr;
// 
// 	while (pCurr < pEnd)
// 	{
// 		if (*pCurr == 0)
// 		{
// 			break;
// 		}
// 
// 		//当前字符为分隔符号，字符串长度之外的也是分隔符
// 		if ((!CStringVariableReplaceU::IsVariableChar(*(pCurr))) && (!CStringVariableReplaceU::IsVariableChar(*(pCurr+nSrcLen+1)))  )
// 		{
// 			if (wcsncmp(pCurr+1, pszVarKey, nSrcLen) == 0)
// 			{
// 				pCurr++;
// 
// 				//拷贝其他字符串数据 
// 				if (pBegin != NULL)
// 				{
// 					nCopyLen =  pCurr - pBegin;
// 					wcsncpy(pDestCurr, pBegin, nCopyLen);
// 					pDestCurr += nCopyLen;
// 				}
// 
// 				//Get Variable
// 				GetNextVarDef(pCurr+nSrcLen, pEnd, &pVarBegin, &pVarEnd);
// 				nCopyLen = pVarEnd - pCurr;
// 				wcsncpy(pDestCurr, pCurr, nCopyLen);
// 
// 				pDestCurr += nCopyLen;
// 				wcscpy(pDestCurr, _T(";\r\n"));
// 				pDestCurr += 3;
// 
// 				nVarLen = pVarEnd - pVarBegin;
// 				wcsncpy(pDestCurr, pVarBegin, nVarLen);
// 				pDestCurr += nVarLen;
// 
// 				pCurr = pCurr + nCopyLen;
// 				
// 				pBegin = pCurr;
// 				nReplaceCount++;
// 			}
// 			else
// 			{
// 				pCurr++;		
// 			}
// 		}
// 		else
// 		{
// 			pCurr++;
// 		}
// 	}
// 
// 	if (nReplaceCount > 0)
// 	{
// 		if (pBegin != pCurr)
// 		{
// 			nCopyLen =  pCurr - pBegin+1;
// 			wcsncpy(pDestCurr, pBegin, nCopyLen);
// 			pDestCurr += nCopyLen;
// 		}
// 
// 		*pDestCurr = 0;
// 
// 		pDestCurr = m_pRefDestBuf;
// 		m_pRefDestBuf = m_pRefSrcBuf;
// 		m_pRefSrcBuf = pDestCurr;
// 	}
// 
// }
// 
// BOOL CPpsVarReplaceBaseObj::FinishReplace()
// {
// 	if (m_pTextRef == NULL)
// 	{
// 		return TRUE;
// 	}
// 
// 	*m_pTextRef = m_pRefSrcBuf;
// 
// 	return TRUE;
// }


//////////////////////////////////////////////////////////////////////////
//CPpsItemDvmReplace
// BOOL CPpsLuaToXvmTool::g_bShowReplaceItemPath = TRUE;

CPpsLuaToXvmTool::CPpsLuaToXvmTool()
{
// 	m_pPpObjctDest = NULL;
// 	m_pPpTemplate = NULL;
// 
// 	m_pBufferForReplace = NULL;
// 	m_nLenBufferForReplace = 0;
// 	m_bFileVarReplace = FALSE;
// 
// 	CString strFile;
// 	strFile = _P_GetBinPath();
// 	strFile += _T("GbLuaToXvmTool.txt");
// 	m_bFileVarReplace = m_fileVarReplace.Open(strFile, CFile::modeCreate | CFile::modeWrite);
}

CPpsLuaToXvmTool::~CPpsLuaToXvmTool()
{
// 	if (m_pBufferForReplace != NULL)
// 	{
// 		delete m_pBufferForReplace;
// 		m_pBufferForReplace = NULL;
// 	}
// 
// 	if (m_bFileVarReplace)
// 	{
// 		m_fileVarReplace.Close();
// 	}
}

BOOL CPpsLuaToXvmTool::NeedLuaToXVM(CExBaseList *pTemplate)
{
	CPpTemplate *pPpTemplate = (CPpTemplate*)pTemplate;

	if (pPpTemplate->IsScriptType_XVM())
	{
		return FALSE;
	}

	pPpTemplate->SetScriptType_XVM();

	return TRUE;
}

void CPpsLuaToXvmTool::ShowReplaceItemPath(CExBaseObject *pItem)
{
	if (!g_bShowReplaceItemPath)
	{
		return;
	}

	CExBaseObject *pAncesster = (CExBaseObject*)pItem->GetAncestor(PPCLASSID_PPPROCEDURES);
	CString strPath;

	if (pAncesster != NULL)
	{
		strPath = pItem->GetNamePathEx(PPCLASSID_PPPROCEDURES, FALSE);
	}
	else
	{
		pAncesster = (CExBaseObject*)pItem->GetAncestor(PPCLASSID_PPPAKAGES);

		if (pAncesster != NULL)
		{
			strPath = pItem->GetNamePathEx(PPCLASSID_PPPAKAGES, FALSE);
		}
	}

	if (strPath.GetLength() > 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
	}
}

/*

BOOL CPpsLuaToXvmTool::LuaToXvm(CPpTemplate *pPpTemplate)
{
	m_pPpTemplate = pPpTemplate;

	if (pPpTemplate->IsScriptType_XVM())
	{
		return FALSE;
	}

	pPpTemplate->SetScriptType_XVM();
	BuildRepalce(m_pPpTemplate);

	Replace(_T("if"), _T("if("));
	Replace(_T("then"), _T(")\r\n{\r\n"));
	Replace(_T("else"), _T("}\r\nelse\r\n{\r\n"));
	Replace(_T("elseif"), _T("}\r\nelse if("));
	Replace(_T("end"), _T("}\r\n"));
	Replace(_T("local"), _T("var"));
	Replace(_T("string.format"), _T("strformat"));
	Replace(_T("and"), _T("&&"));
	Replace(_T("or"), _T("||"));
	Replace(_T("not"), _T("!"));
	Replace(_T("ShowMsg"), _T("//ShowMsg"));
	Replace(_T("--"), _T("//"), FALSE);
	Replace(_T("//[["), _T("/ *"), FALSE);
	Replace(_T("//]]"), _T("* /"), FALSE);
	Replace(_T("#"), _T(" "), FALSE);

	ProcessVarDef();

	FinishReplace();

	return TRUE;
}

void CPpsLuaToXvmTool::ProcessVarDef()
{
	POS pos = GetHeadPosition();
	CPpsVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CPpsVarReplaceBaseObj*)GetNext(pos);
		p->ProcessVarDef();
	} 
}

void CPpsLuaToXvmTool::BuildRepalce(CExBaseList *pPpObjcts)
{
	ASSERT (pPpObjcts != NULL);

	if (pPpObjcts == NULL)
	{
		return;
	}

	m_pPpObjctDest = pPpObjcts;
	UINT nClassID = m_pPpObjctDest->GetClassID();
	CPpTemplate *pPpTemplate = (CPpTemplate *)m_pPpObjctDest->GetAncestor(PPCLASSID_PPTEMPLATE);

	BuildItems(m_pPpObjctDest);

	BuildBuffer();
}

void CPpsLuaToXvmTool::Replace(const CString &strSrcID, const CString &strDestID, BOOL bValidSeparator)
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

	CPpsVarReplacePara oReplacePara;
	oReplacePara.m_pDestDataRef = NULL;
	oReplacePara.m_strSrcID = strSrcID;
	oReplacePara.m_strDestID = strDestID;

	POS pos = GetHeadPosition();
	CPpsVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CPpsVarReplaceBaseObj*)GetNext(pos);
		p->Replace(&oReplacePara, bValidSeparator);
	}
}

void CPpsLuaToXvmTool::FinishReplace()
{
	POS pos = GetHeadPosition();
	CPpsVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CPpsVarReplaceBaseObj*)GetNext(pos);
		p->FinishReplace();
	}
}

void CPpsLuaToXvmTool::BuildItems(CExBaseList *pPpObjctDest)
{
	POS pos = pPpObjctDest->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pPpObjctDest->GetNext(pos);

		if (PPCLASSID_PPSCRIPT == p->GetClassID())
		{
			BuildItem(p);
		}
		else if (p->IsBaseList())
		{
			BuildItems((CExBaseList*)p);
		}
	}
}

void CPpsLuaToXvmTool::BuildItem(CExBaseObject *pPpObjctDest)
{
	CPpScript *pScript = (CPpScript*)pPpObjctDest;

	if (pScript->m_strScript.GetLength() > MINLEN_SCRIPT_TEXT)
	{
		CPpsVarReplaceBaseObj *pNew = new CPpsVarReplaceBaseObj();
		pNew->m_pTextRef = &pScript->m_strScript;
		pNew->m_pPpScript = pScript;
		AddTail(pNew);
	}
}

void CPpsLuaToXvmTool::ShowReplaceItemPath(CExBaseObject *pItem)
{
	if (g_bShowReplaceItemPath)
	{
		CExBaseObject *pAncesster = (CExBaseObject*)pItem->GetAncestor(PPCLASSID_PPPROCEDURES);
		CString strPath;

		if (pAncesster != NULL)
		{
			strPath = pItem->GetNamePathEx(PPCLASSID_PPPROCEDURES, FALSE);
		}
		else
		{
			pAncesster = (CExBaseObject*)pItem->GetAncestor(PPCLASSID_PPPAKAGES);

			if (pAncesster != NULL)
			{
				strPath = pItem->GetNamePathEx(PPCLASSID_PPPAKAGES, FALSE);
			}
		}
		
		if (strPath.GetLength() > 0)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
		}
	}
}

void CPpsLuaToXvmTool::BuildBuffer()
{
	POS pos = GetHeadPosition();
	CPpsVarReplaceBaseObj *p = NULL;
	m_nLenBufferForReplace = 0;
	TCHAR *pPosBuffer = NULL;

	while (pos != NULL)
	{
		p = (CPpsVarReplaceBaseObj*)GetNext(pos);
		m_nLenBufferForReplace += p->CalBuffer();
	}

	m_nLenBufferForReplace *= 2;
	m_pBufferForReplace = new TCHAR[m_nLenBufferForReplace+1000];
	pPosBuffer = m_pBufferForReplace;
	ZeroMemory(m_pBufferForReplace, sizeof(TCHAR) * (m_nLenBufferForReplace+1000));
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpsVarReplaceBaseObj*)GetNext(pos);
		p->BuidBuffer(&pPosBuffer);
	}
}

*/
