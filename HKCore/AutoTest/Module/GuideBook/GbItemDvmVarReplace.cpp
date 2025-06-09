#include "stdafx.h"
#include "GbItemDvmVarReplace.h"

//////////////////////////////////////////////////////////////////////////
//CGbReplaceBaseObj
CGbVarReplaceBaseObj::CGbVarReplaceBaseObj()
{
	m_nBufLength = 0;
	m_pRefSrcBuf  = NULL;
	m_pRefDestBuf = NULL;
	m_pTextRef = NULL;
	m_pGbItemRef = NULL;
	m_pGbObjRef = NULL;
}

CGbVarReplaceBaseObj::~CGbVarReplaceBaseObj()
{

}

long CGbVarReplaceBaseObj::CalBuffer()
{
	if (m_pTextRef == NULL)
	{
		return 0;
	}

	m_nBufLength = String_Char_Count(*m_pTextRef);

	if (m_pTextRef->GetLength() < 100)
	{
		m_nBufLength += 50;
	}
	else
	{
		m_nBufLength = m_nBufLength * 3 / 2;
	}

	return m_nBufLength;
}

void CGbVarReplaceBaseObj::BuidBuffer(TCHAR **ppBuffer)
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

BOOL CGbVarReplaceBaseObj::Replace(CGbVarReplacePara *pReplacePara)
{
#ifdef _UNICODE
	CStringVariableReplaceU oReplace;
#else
	CStringVariableReplace oReplace;
#endif

	//替换完成，交换位置
	if (oReplace.Replace(m_pRefSrcBuf, m_pRefDestBuf, pReplacePara->m_strSrcID, pReplacePara->m_strDestID) > 0)
	{
		TCHAR *pTemp = m_pRefDestBuf;
		m_pRefDestBuf = m_pRefSrcBuf;
		m_pRefSrcBuf = pTemp;
	}

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
	if (m_oReplace.Replace(pRptData->m_strID, m_strSrcID, m_strDestID) > 0)
	{
		if (pReplacePara->m_pGbObjRef != NULL)
		{
			if (pReplacePara->m_pGbObjRef->GetClassID() == GBCLASSID_GBTDATA)
			{
				pRptData->m_strName = pReplacePara->m_pGbObjRef->m_strName;
			}
		}
	}
*/

	return TRUE;
}

BOOL CGbVarReplaceBaseObj::FinishReplace()
{
	if (m_pTextRef == NULL)
	{
		return TRUE;
	}

	*m_pTextRef = m_pRefSrcBuf;

	return TRUE;
}

BOOL CGbVarReplaceBaseObj::HasReplace(CGbVarReplacePara *pReplacePara)
{

#ifdef _UNICODE
	CStringVariableReplaceU oReplace;
#else
	CStringVariableReplace oReplace;
#endif

	return oReplace.HasReplace(m_pRefSrcBuf, m_pRefDestBuf, pReplacePara->m_strSrcID);
}

//////////////////////////////////////////////////////////////////////////
//CGbReplace_RptData
CGbVarReplace_RptData::CGbVarReplace_RptData()
{
	m_bHasReplaced = FALSE;
}

CGbVarReplace_RptData::~CGbVarReplace_RptData()
{

}

BOOL CGbVarReplace_RptData::Replace(CGbVarReplacePara *pReplacePara)
{
	if (m_bHasReplaced)
	{
		return TRUE;
	}

#ifdef _UNICODE
	CStringVariableReplaceU oReplace;
#else
	CStringVariableReplace oReplace;
#endif

	if (oReplace.Replace(m_pRefSrcBuf, m_pRefDestBuf, pReplacePara->m_strSrcID, pReplacePara->m_strDestID) > 0)
	{

		TCHAR *pTemp = m_pRefDestBuf;
		m_pRefDestBuf = m_pRefSrcBuf;
		m_pRefSrcBuf = pTemp;

		m_bHasReplaced = TRUE;

		if (pReplacePara->m_pDestDataRef != NULL)
		{
			if (pReplacePara->m_pDestDataRef->GetClassID() == GBCLASSID_GBTDATA 
				|| pReplacePara->m_pDestDataRef->GetClassID() == GBCLASSID_DATAOBJ)
			{
				m_pGbObjRef->m_strName = pReplacePara->m_pDestDataRef->m_strName;
			}
		}
	}
	
	return TRUE;
}

BOOL CGbVarReplace_RptData::HasReplace(CGbVarReplacePara *pReplacePara)
{
	if (m_bHasReplaced)
	{
		return FALSE;
	}

#ifdef _UNICODE
	CStringVariableReplaceU oReplace;
#else
	CStringVariableReplace oReplace;
#endif

	return oReplace.HasReplace(m_pRefSrcBuf, m_pRefDestBuf, pReplacePara->m_strSrcID);
}

//////////////////////////////////////////////////////////////////////////
//CGbReplace_RptData
CGbVarReplace_DsvScript::CGbVarReplace_DsvScript()
{

}

CGbVarReplace_DsvScript::~CGbVarReplace_DsvScript()
{

}

long CGbVarReplace_DsvScript::CalBuffer()
{
	return 0;
}

BOOL CGbVarReplace_DsvScript::Replace(CGbVarReplacePara *pReplacePara)
{
	CDsvScript *pDsvScript = (CDsvScript *)m_pGbObjRef;

	POS pos = pDsvScript->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = pDsvScript->GetNext(pos);
		nClassID = p->GetClassID();

		if ( (nClassID == DVMCLASSID_CDSVELIMINATE)
			|| (DVMCLASSID_CDSVELEMENT == nClassID) )
		{
			if (p->m_strID == pReplacePara->m_strSrcID)
			{
				if (pReplacePara->m_pDestDataRef == NULL)
				{
					//2019-3-18  即使没有对应的数据，也不删除
					//pDsvScript->Delete(p);
					continue;
				}
			}
		}

		if (nClassID == DVMCLASSID_CDSVELIMINATE)
		{
			Replace((CDsvEliminate*)p, pReplacePara);
		}
		else if (DVMCLASSID_CDSVELEMENT == nClassID)
		{
			Replace((CDsvElement*)p, pReplacePara);
		}
	}

	return TRUE;
}


BOOL CGbVarReplace_DsvScript::HasReplace(CGbVarReplacePara *pReplacePara)
{
	CDsvScript *pDsvScript = (CDsvScript *)m_pGbObjRef;

	POS pos = pDsvScript->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDsvScript->GetNext(pos);
		nClassID = p->GetClassID();

// 		if ( (nClassID == DVMCLASSID_CDSVELIMINATE)
// 			|| (DVMCLASSID_CDSVELEMENT == nClassID) )
// 		{
// 			if (p->m_strID == pReplacePara->m_strSrcID)
// 			{
// 				if (pReplacePara->m_pDestDataRef == NULL)
// 				{
// 					continue;
// 				}
// 			}
// 		}

		if (p->m_strID == pReplacePara->m_strSrcID)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CGbVarReplace_DsvScript::Replace(CDsvElement *pDsvElement, CGbVarReplacePara *pReplacePara)
{
	//临时使用进行判断，是否被替换
	if (pDsvElement->m_bDsvSucc)
	{
		return;
	}

	if (pDsvElement->m_strID != pReplacePara->m_strSrcID)
	{
		return;
	}

	pDsvElement->m_bDsvSucc = TRUE;
	POS pos = pDsvElement->GetHeadPosition();
	CDsvElemAttr *p = NULL;
	UINT nClassID = 0;

	pDsvElement->m_strID = pReplacePara->m_pDestDataRef->m_strID;
	pDsvElement->m_strName = pReplacePara->m_pDestDataRef->m_strName;

	while (pos != NULL)
	{
		p = (CDsvElemAttr*)pDsvElement->GetNext(pos);

		if (p->m_strID == _T("name"))
		{
			p->m_strValue = pReplacePara->m_pDestDataRef->m_strName;
		}
		else if (p->m_strID == _T("id"))
		{
			p->m_strValue = pReplacePara->m_pDestDataRef->m_strID;
		}
	}
}

void CGbVarReplace_DsvScript::Replace(CDsvEliminate *pDsvEliminate, CGbVarReplacePara *pReplacePara)
{
	if (pDsvEliminate == NULL)
	{
		return;
	}

	POS pos = pDsvEliminate->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDsvEliminate->GetNext(pos);

		if (p->m_strID == pReplacePara->m_strSrcID)
		{
			if (pReplacePara->m_pDestDataRef == NULL)
			{
				pDsvEliminate->Delete(p);
				continue;
			}

			p->m_strID = pReplacePara->m_strDestID;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CGbItemDvmReplace
BOOL CGbItemDvmVarReplace::g_bShowReplaceItemPath = TRUE;

CGbItemDvmVarReplace::CGbItemDvmVarReplace()
{
	m_pGbItemDest = NULL;
	m_bReplaceMacroTest = TRUE;
	m_bReplaceSafety = TRUE;
	m_bReplaceCommCmd = TRUE;
	m_pGuideBook = NULL;

	m_pBufferForReplace = NULL;
	m_nLenBufferForReplace = 0;
	m_bFileVarReplace = FALSE;

	CString strFile;
	strFile = _P_GetBinPath();
	strFile += _T("GbItemDvmVarReplace.txt");
	m_bFileVarReplace = m_fileVarReplace.Open(strFile, CFile::modeCreate | CFile::modeWrite);
}

CGbItemDvmVarReplace::~CGbItemDvmVarReplace()
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

void CGbItemDvmVarReplace::BuildRepalce(CExBaseList *pGbItems)
{
	ASSERT (pGbItems != NULL);

	if (pGbItems == NULL)
	{
		return;
	}

	m_pGbItemDest = pGbItems;
	UINT nClassID = m_pGbItemDest->GetClassID();
	CGuideBook *pGuideBook = (CGuideBook *)m_pGbItemDest->GetAncestor(GBCLASSID_GUIDEBOOK);

	ASSERT (pGuideBook != NULL);
	m_pGuideBook = pGuideBook;
	CExBaseList *pLocalScriptLib = pGuideBook->GetScriptLibLocal();
	ASSERT (pLocalScriptLib != NULL);

	Build_Characteristics(nClassID, m_pGbItemDest);

	if (Gb_IsItemsBaseClassID(nClassID))
	{
		BuildItems(m_pGbItemDest);
	}
	else
	{
		BuildItem(m_pGbItemDest);
	}

	POS pos = pLocalScriptLib->GetHeadPosition();
	CScriptText *pText = NULL;

	while (pos != NULL)
	{
		pText = (CScriptText*)pLocalScriptLib->GetNext(pos);
		Build(pText);
	}

	BuildBuffer();
}

void CGbItemDvmVarReplace::Replace(CExBaseObject *pDestObject, const CString &strSrcID, const CString &strDestID)
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

	CGbVarReplacePara oReplacePara;
	oReplacePara.m_pDestDataRef = pDestObject;
	oReplacePara.m_strSrcID = strSrcID;
	oReplacePara.m_strDestID = strDestID;

	POS pos = GetHeadPosition();
	CGbVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CGbVarReplaceBaseObj*)GetNext(pos);
		p->Replace(&oReplacePara);
	}
}

BOOL CGbItemDvmVarReplace::HasReplace(CExBaseObject *pDestObject, const CString &strSrcID)
{
	if (strSrcID.GetLength() == 0)
	{
		return FALSE;
	}

	CGbVarReplacePara oReplacePara;
	oReplacePara.m_pDestDataRef = pDestObject;
	oReplacePara.m_strSrcID = strSrcID;

	POS pos = GetHeadPosition();
	CGbVarReplaceBaseObj *p = NULL;
	BOOL bHasReplace = FALSE;

	while (pos != NULL)
	{
		p = (CGbVarReplaceBaseObj*)GetNext(pos);

		if (p->HasReplace(&oReplacePara))
		{
			bHasReplace = TRUE;
			break;
		}
	}

	return bHasReplace;
}

void CGbItemDvmVarReplace::FinishReplace()
{
	POS pos = GetHeadPosition();
	CGbVarReplaceBaseObj *p = NULL;

	while (pos != NULL)
	{
		p = (CGbVarReplaceBaseObj*)GetNext(pos);
		p->FinishReplace();
	}
}

void CGbItemDvmVarReplace::BuildItems(CExBaseList *pGbItemDest)
{
	POS pos = pGbItemDest->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pGbItemDest->GetNext(pos);

		UINT nClassID = p->GetClassID();

		if (Gb_IsItemsBaseClassID(nClassID))
		{
			BuildItems((CExBaseList*)p);
		}
		else if (Gb_IsItemBaseClassID(nClassID))
		{
			BuildItem(p);
		}
	}
}

void CGbItemDvmVarReplace::BuildItem(CExBaseObject *pGbItemDest)
{
	UINT nClassID = pGbItemDest->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_MACROTEST:
		if (m_bReplaceMacroTest)
		{
			Build((CMacroTest*)pGbItemDest);
		}
		break;

	case GBCLASSID_MACROCHARITEMS:
		if (m_bReplaceMacroTest)
		{
			Build((CMacroCharItems*)pGbItemDest);
		}
		break;

	case GBCLASSID_SAFETY:
		if (m_bReplaceSafety)
		{
			Build((CSafety*)pGbItemDest);
		}
		break;

	case GBCLASSID_COMMCMD:
		if (m_bReplaceCommCmd)
		{
			Build((CCommCmd*)pGbItemDest);
		}
		break;

	case GBCLASSID_SYSPARAEDIT:
		if (m_bReplaceSysparaEdit)
		{
			Build((CSysParaEdit*)pGbItemDest);
		}
		break;

	default:
		break;
	}
}

void CGbItemDvmVarReplace::Build_RptData(CReportMap *pRptMap, CExBaseObject *pRptData)
{
	CGbVarReplace_RptData *pNew = new CGbVarReplace_RptData();
	pNew->m_pGbObjRef = pRptData;
	pNew->m_pTextRef = &pRptData->m_strID;
	AddTail(pNew);
}

void CGbItemDvmVarReplace::Build(CGbItemBase *pGbObj)
{
	if (pGbObj->m_pInitScriptText != NULL)
	{
		Build(pGbObj->m_pInitScriptText);
	}

	if (pGbObj->m_pResultScriptText != NULL)
	{
		Build(pGbObj->m_pResultScriptText);
	}

	//报告映射
	CReportMap *pRptMap = pGbObj->m_pRptMap;
	CRptData *pData = NULL;
	CRptMapRepeat *pRepeat = NULL;
	POS pos = pRptMap->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pRptMap->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == RPTCLASSID_RPTDATA)
		{
			Build_RptData(pRptMap, p);
		}
		else
		{
			 if (nClassID == RPTCLASSID_RPTMAPREPEAT)
			 {
				pRepeat = (CRptMapRepeat *)p;
				POS pos2 = pRepeat->GetHeadPosition();

				while (pos2 != NULL)
				{
					p = (CExBaseObject *)pRepeat->GetNext(pos2);
					nClassID = p->GetClassID();

					if (nClassID == RPTCLASSID_RPTDATA)
					{
						Build_RptData(pRptMap, p);
					}
				}
			 }
		}
	}
}


void CGbItemDvmVarReplace::Build(CMacroTest *pGbObj)
{
	Build((CGbItemBase*)pGbObj);

	//故障计算脚本
	CMacroTestPara *pMacroTestPara = pGbObj->GetMacroTestPara();
	Build(pMacroTestPara->GetScriptText());

	//参数对象
	CMacroTestParaDatas *pDatas = pMacroTestPara->GetFaultParaDatas();
	CMacroTestParaData *pData = NULL;
	POS pos = pDatas->GetHeadPosition();

	//子项目对象
	while (pos != NULL)
	{
		pData = (CMacroTestParaData *)pDatas->GetNext(pos);
		Build(pData->m_strExpression);
	}

	CExBaseList *pListSubItems = pGbObj->GetSubGbItems();
	pos = pListSubItems->GetHeadPosition();
	CExBaseObject *pSubItem = NULL;

	while (pos != NULL)
	{
		pSubItem = (CExBaseObject *)pListSubItems->GetNext(pos);
		BuildItem(pSubItem);
	}
}

void CGbItemDvmVarReplace::Build(CMacroCharItems *pGbObj)
{
	CMacroTestPara *pMacroTestPara = pGbObj->GetMacroTestPara();
	//Build(pMacroTestPara->GetScriptText());

	//参数对象
	CMacroTestParaDatas *pDatas = pMacroTestPara->GetFaultParaDatas();
	CMacroTestParaData *pData = NULL;
	POS pos = pDatas->GetHeadPosition();

	//子项目对象
	while (pos != NULL)
	{
		pData = (CMacroTestParaData *)pDatas->GetNext(pos);
		Build(pData->m_strExpression);
	}
}

void CGbItemDvmVarReplace::Build(CCommCmd *pGbObj)
{
	Build((CGbItemBase*)pGbObj);

	CCmd *pCmd = pGbObj->GetCmd();

	//CPUID
	Build(pCmd->m_strDatasetPath);

	//Values
	POS pos = pCmd->GetHeadPosition();
	CValue *pValue = NULL;

	if (pGbObj->m_nBatchItem > 0)
	{
		while (pos != NULL)
		{
			pValue = (CValue *)pCmd->GetNext(pos);
			Build(pValue->m_strID);
		}
	}
	else
	{
		while (pos != NULL)
		{
			pValue = (CValue *)pCmd->GetNext(pos);
			Build(pValue->m_strID, FALSE);

			//通讯命令参数数据可能是表达式，也需要处理
			if (!IsStringNumber(pValue->m_strValue))
			{
				Build(pValue->m_strValue);
			}
		}
	}

	Build(pGbObj->GetDsvScriptRef());
}

void CGbItemDvmVarReplace::Build(CSafety *pGbObj)
{
	Build((CGbItemBase*)pGbObj);
}

void CGbItemDvmVarReplace::Build(CSysParaEdit *pGbObj)
{
	Build((CGbItemBase*)pGbObj);

	if (pGbObj->m_strDatasetPath.GetLength() >= MINLEN_SCRIPT_TEXT)
	{
		CGbVarReplaceBaseObj *pNew = new CGbVarReplaceBaseObj();
		pNew->m_pTextRef = &pGbObj->m_strDatasetPath;
		AddTail(pNew);
	}
}

void CGbItemDvmVarReplace::Build(CScriptText *pText)
{
	//内部引用脚本替换
	if (pText->m_nIsRef)
	{
		return;
	}

	if (pText->m_strScriptText.GetLength() > MINLEN_SCRIPT_TEXT)
	{
		CGbVarReplaceBaseObj *pNew = new CGbVarReplaceBaseObj();
		pNew->m_pTextRef = &pText->m_strScriptText;
		AddTail(pNew);
	}
}

void CGbItemDvmVarReplace::Build(CString &strText, BOOL bUseMinLen)
{
	if (bUseMinLen)
	{
		if (strText.GetLength() < MINLEN_SCRIPT_TEXT)
		{
			return;
		}
	}

	if (::IsStringNumber(strText))
	{
		return;
	}

	CGbVarReplaceBaseObj *pNew = new CGbVarReplaceBaseObj();
	pNew->m_pTextRef = &strText;
	AddTail(pNew);
}

void CGbItemDvmVarReplace::ShowReplaceItemPath(CExBaseObject *pItem)
{
	if (g_bShowReplaceItemPath)
	{
		CString strPath = Gb_GetItemPathName(pItem);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
	}
}

void CGbItemDvmVarReplace::Build(CDsvScript *pDsvScript)
{
	if (pDsvScript == NULL)
	{
		return;
	}

	if (pDsvScript->GetCount() <= 1)
	{
		return;
	}

	CGbVarReplace_DsvScript *pNew = new CGbVarReplace_DsvScript();
	pNew->m_pGbObjRef = pDsvScript;
	AddTail(pNew);

	POS pos = pDsvScript->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pDsvScript->GetNext(pos);
		nClassID = p->GetClassID();

		if (DVMCLASSID_CDSVELEMENT == nClassID)
		{
			((CDsvElement*)p)->m_bDsvSucc = FALSE;
		}
	}
}

void CGbItemDvmVarReplace::Build(CCharacteristics *pCharacteristics)
{
	if (pCharacteristics == NULL)
	{
		return;
	}

	POS pos = pCharacteristics->GetHeadPosition();
	CCharacteristic *pCharTmpl = NULL;

	while (pos != NULL)
	{
		pCharTmpl = (CCharacteristic *)pCharacteristics->GetNext(pos);

		CCharInterface *pCharInterface = pCharTmpl->GetCharInterface();
		POS posVar = pCharInterface->GetHeadPosition();
		CCharInterfaceVariable *pVar = NULL;

		while (posVar != NULL)
		{
			pVar = (CCharInterfaceVariable *)pCharInterface->GetNext(posVar);
			Build(pVar->m_strScript);
		}
	}
}

void CGbItemDvmVarReplace::Build_Characteristics(UINT nClassID, CExBaseObject *pGbItemDest)
{
	if (nClassID != GBCLASSID_DEVICE)
	{
		return;
	}

	CDevice *pDevice = (CDevice*)pGbItemDest;
	Build(pDevice->m_pCharacteristics);
}

void CGbItemDvmVarReplace::BuildBuffer()
{
	POS pos = GetHeadPosition();
	CGbVarReplaceBaseObj *p = NULL;
	m_nLenBufferForReplace = 0;
	TCHAR *pPosBuffer = NULL;

	while (pos != NULL)
	{
		p = (CGbVarReplaceBaseObj*)GetNext(pos);
		m_nLenBufferForReplace += p->CalBuffer();
	}

	m_nLenBufferForReplace *= 2;
	m_pBufferForReplace = new TCHAR[m_nLenBufferForReplace+1000];
	pPosBuffer = m_pBufferForReplace;
	ZeroMemory(m_pBufferForReplace, sizeof(TCHAR) * (m_nLenBufferForReplace+1000));
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CGbVarReplaceBaseObj*)GetNext(pos);
		p->BuidBuffer(&pPosBuffer);
	}
}

