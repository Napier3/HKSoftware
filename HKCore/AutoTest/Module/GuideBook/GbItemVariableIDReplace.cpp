#include "stdafx.h"
#include "GbItemVariableIDReplace.h"
#include "..\GuideBookWizard\GbtBatchItem.h"

BOOL CGbItemVariableIDReplace::g_bShowReplaceItemPath = TRUE;

CGbItemVariableIDReplace::CGbItemVariableIDReplace()
{
	m_pGbItemDest = NULL;
	m_bReplaceMacroTest = TRUE;
	m_bReplaceSafety = TRUE;
	m_bReplaceCommCmd = TRUE;
	m_pGuideBook = NULL;
	m_pLocalScriptLib = NULL;
	m_pDestObject = NULL;

	//缺省都开辟100K空间
	m_oReplace.InitBuffer(102400, 102400);

	//缺省都开辟1M空间
	//m_oReplace.InitBuffer(1048576, 1048576);
}

CGbItemVariableIDReplace::~CGbItemVariableIDReplace()
{
	
}



void CGbItemVariableIDReplace::Replace(CExBaseList *pGbItemDest, const CString &strSrcID, const CString &strDestID)
{
	CGuideBook *pGuideBook = (CGuideBook *)pGbItemDest->GetAncestor(GBCLASSID_GUIDEBOOK);
	m_pGuideBook = pGuideBook;
	
	if (pGuideBook != NULL)
	{
		m_pLocalScriptLib = pGuideBook->GetScriptLibLocal();
	}

	m_pGbItemDest = pGbItemDest;
	ASSERT (m_pGbItemDest != NULL);

	if (m_pGbItemDest == NULL)
	{
		return;
	}

	m_strSrcID = strSrcID;
	m_strDestID = strDestID;

	UINT nClassID = m_pGbItemDest->GetClassID();
	Replace_Characteristics(nClassID, m_pGbItemDest);

	if (Gb_IsItemsBaseClassID(nClassID))
	{
		ReplaceItems(m_pGbItemDest);
	}
	else
	{
		ReplaceItem(m_pGbItemDest);
	}

	if (m_pLocalScriptLib == NULL)
	{
		return;
	}

	POS pos = m_pLocalScriptLib->GetHeadPosition();
	CScriptText *pText = NULL;

	while (pos != NULL)
	{
		pText = (CScriptText*)m_pLocalScriptLib->GetNext(pos);
		Replace(pText);
	}

}

void CGbItemVariableIDReplace::ReplaceItems(CExBaseList *pGbItemDest)
{
	POS pos = pGbItemDest->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pGbItemDest->GetNext(pos);

		UINT nClassID = p->GetClassID();

		if (Gb_IsItemsBaseClassID(nClassID))
		{
			ReplaceItems((CExBaseList*)p);
		}
		else if (Gb_IsItemBaseClassID(nClassID))
		{
			ReplaceItem(p);
		}
	}
}

void CGbItemVariableIDReplace::ReplaceItem(CExBaseObject *pGbItemDest)
{
	UINT nClassID = pGbItemDest->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_MACROCHARITEMS:
		if (m_bReplaceMacroTest)
		{
			Replace((CMacroCharItems*)pGbItemDest);
		}
		break;

	case GBCLASSID_MACROTEST:
		if (m_bReplaceMacroTest)
		{
			Replace((CMacroTest*)pGbItemDest);
		}
		break;

	case GBCLASSID_SAFETY:
		if (m_bReplaceSafety)
		{
			Replace((CSafety*)pGbItemDest);
		}
		break;

	case GBCLASSID_COMMCMD:
		if (m_bReplaceCommCmd)
		{
			Replace((CCommCmd*)pGbItemDest);
		}
		break;

	case GBCLASSID_SYSPARAEDIT:
		if (m_bReplaceSysparaEdit)
		{
			Replace((CSysParaEdit*)pGbItemDest);
		}
		break;

	default:
		break;
	}
}

void CGbItemVariableIDReplace::Replace_RptData(CReportMap *pRptMap, CExBaseObject *pRptData)
{
	BOOL bTrue = FALSE;

	if (pRptData->m_strID.Find(m_strSrcID) >= 0)
	{
		bTrue = TRUE;
	}
	else
	{
// 		if (pRptData->m_strID.Mid(4) == m_strSrcID)
// 		{
// 			bTrue = TRUE;
// 		}
	}

	if (bTrue)
	{
// 		CStringVariableReplace oReplace;
		if (m_oReplace.Replace(pRptData->m_strID, m_strSrcID, m_strDestID) > 0)
		{
			if (m_pDestObject != NULL)
			{
				if (m_pDestObject->GetClassID() == GBCLASSID_GBTDATA)
				{
					pRptData->m_strName = m_pDestObject->m_strName;
				}
			}
		}

#if 0
		pRptData->m_strID.Replace(m_strSrcID, m_strDestID);

		if (m_pDestObject != NULL)
		{
			pRptData->m_strName = m_pDestObject->m_strName;
		}
		else
		{
			pRptData->m_strName.Replace(m_strSrcID, m_strDestID);
		}
// 		if (m_strDestID.Find('$') >= 0)
// 		{
// 			CDevice *pDevice = (CDevice*)pRptMap->GetAncestor(GBCLASSID_DEVICE);
// 			CExBaseObject *pFind = pDevice->m_pCpus->SelectDataObj(m_strDestID);
// 
// 			if (pFind != NULL)
// 			{
// 				pRptData->m_strName = pFind->m_strName;
// 			}
// 			else
// 			{
// 				pRptData->m_strName = m_strDestID;//.Replace(m_strSrcID, m_strDestID);
// 			}
// 		}
// 		else
// 		{
// 			pRptData->m_strName.Replace(m_strSrcID, m_strDestID);
// 		}
#endif
	}
}

void CGbItemVariableIDReplace::Replace(CGbItemBase *pGbObj)
{
	if (pGbObj->m_pInitScriptText != NULL)
	{
		Replace(pGbObj->m_pInitScriptText);
	}

	if (pGbObj->m_pResultScriptText != NULL)
	{
		Replace(pGbObj->m_pResultScriptText);
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
			//if (p->m_strID.Find(m_strSrcID) >= 0)
			Replace_RptData(pRptMap, p);
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
						//if (p->m_strID.Find(m_strSrcID) >= 0)
						Replace_RptData(pRptMap, p);
					}
				}
			 }
		}
	}
}

void CGbItemVariableIDReplace::Replace(CMacroTestPara *pMacroTestPara)
{
	//故障计算脚本
	Replace(pMacroTestPara->GetScriptText());

	//参数对象
	CMacroTestParaDatas *pDatas = pMacroTestPara->GetFaultParaDatas();
	CMacroTestParaData *pData = NULL;
	POS pos = pDatas->GetHeadPosition();

	//子项目对象
	while (pos != NULL)
	{
		pData = (CMacroTestParaData *)pDatas->GetNext(pos);
		Replace(pData->m_strExpression);
	}

}

void CGbItemVariableIDReplace::Replace(CMacroTest *pGbObj)
{
	//ShowReplaceItemPath(pGbObj);
	Replace((CGbItemBase*)pGbObj);

	CMacroTestPara *pMacroTestPara = pGbObj->GetMacroTestPara();
	Replace(pMacroTestPara);

	CExBaseList *pListSubItems = pGbObj->GetSubGbItems();
	POS pos = pListSubItems->GetHeadPosition();
	CExBaseObject *pSubItem = NULL;

	while (pos != NULL)
	{
		pSubItem = (CExBaseObject *)pListSubItems->GetNext(pos);
		ReplaceItem(pSubItem);
	}
}

void CGbItemVariableIDReplace::Replace(CMacroCharItems *pGbObj)
{
	//ShowReplaceItemPath(pGbObj);
	Replace((CGbItemBase*)pGbObj);

	CMacroTestPara *pMacroTestPara = pGbObj->GetMacroTestPara();
	Replace(pMacroTestPara);
}

void CGbItemVariableIDReplace::Replace(CCommCmd *pGbObj)
{
	//ShowReplaceItemPath(pGbObj);
	Replace((CGbItemBase*)pGbObj);

	CCmd *pCmd = pGbObj->GetCmd();

	//CPUID
	Replace(pCmd->m_strDatasetPath);

	//Values
	POS pos = pCmd->GetHeadPosition();
	CValue *pValue = NULL;

	if (pGbObj->m_nBatchItem > 0)
	{
		while (pos != NULL)
		{
			pValue = (CValue *)pCmd->GetNext(pos);
			Replace(pValue->m_strID);
		}
	}
	else
	{
		while (pos != NULL)
		{
			pValue = (CValue *)pCmd->GetNext(pos);
			Replace(pValue->m_strID);

			//通讯命令参数数据可能是表达式，也需要处理
			if (!IsStringNumber(pValue->m_strValue))
			{
				Replace(pValue->m_strValue);
			}
		}
	}

	Replace(pGbObj->GetDsvScriptRef());
}

void CGbItemVariableIDReplace::Replace(CSafety *pGbObj)
{
	//ShowReplaceItemPath(pGbObj);
	Replace((CGbItemBase*)pGbObj);
}

void CGbItemVariableIDReplace::Replace(CSysParaEdit *pGbObj)
{
	//ShowReplaceItemPath(pGbObj);

	Replace((CGbItemBase*)pGbObj);

	//Type
	//CStringVariableReplace oReplace;
	m_oReplace.Replace(pGbObj->m_strDatasetPath, m_strSrcID, m_strDestID);
}

void CGbItemVariableIDReplace::Replace(CScriptText *pText)
{
	//内部引用脚本替换
	if (pText->m_nIsRef)
	{
		return;
// 		if (m_pLocalScriptLib == NULL)
// 		{
// 			return;
// 		}
// 
// 		pText = (CScriptText *)m_pLocalScriptLib->FindByID(pText->m_strID);
// 
// 		if (pText == NULL)
// 		{
// 			return;
// 		}

	}

	if (pText->m_strScriptText.GetLength() < m_strSrcID.GetLength())
	{
		return;
	}

	//CStringVariableReplace oReplace;
	m_oReplace.Replace(pText->m_strScriptText, m_strSrcID, m_strDestID);
	//Replace(pText->m_strScriptText);
}

void CGbItemVariableIDReplace::Replace(CString &strText)
{
	if (strText.GetLength() < m_strSrcID.GetLength())
	{
		return;
	}

	if (strText == m_strSrcID)
	{
		strText = m_strDestID;
		return;
	}

	if (strText.Find(m_strSrcID) < 0)
	{
		return;
	}

	//CStringVariableReplace oReplace;
	m_oReplace.Replace(strText, m_strSrcID, m_strDestID);
}

void CGbItemVariableIDReplace::ShowReplaceItemPath(CExBaseObject *pItem)
{
	if (g_bShowReplaceItemPath)
	{
		CString strPath = Gb_GetItemPathName(pItem);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
	}
}

void CGbItemVariableIDReplace::ReplaceGbtBatchItemGroup(CExBaseList *pBatchGroup, const CString &strSrcID, const CString &strDestID)
{
	m_strSrcID = strSrcID;
	m_strDestID = strDestID;
	POS pos = pBatchGroup->GetHeadPosition();
	CGbtBatchItemRef *pRef = NULL;

	while (pos != NULL)
	{
		pRef = (CGbtBatchItemRef *)pBatchGroup->GetNext(pos);
		ReplaceBatchItemRef(pRef);
	}
}

void CGbItemVariableIDReplace::ReplaceScriptLibLocal(CExBaseList *pGbItemDest, const CString &strSrcID, const CString &strDestID)
{
	m_pGbItemDest = pGbItemDest;
	ASSERT (m_pGbItemDest != NULL);

	if (m_pGbItemDest == NULL)
	{
		return;
	}

	m_strSrcID = strSrcID;
	m_strDestID = strDestID;

	CGuideBook *pGuideBook = NULL;
	
	if (pGbItemDest->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		pGuideBook = (CGuideBook*)pGbItemDest;
	}
	else
	{
		pGuideBook = (CGuideBook*)pGbItemDest->GetAncestor(GBCLASSID_GUIDEBOOK);
	}

	CScriptTextMngr *pLibLocal = pGuideBook->GetScriptLibLocal();

	POS pos = pLibLocal->GetHeadPosition();
	CScriptText *pScript = NULL;

	while (pos != NULL)
	{
		pScript = (CScriptText *)pLibLocal->GetNext(pos);
		Replace(pScript);
	}
}

void CGbItemVariableIDReplace::ReplaceBatchItemRef(CExBaseList *pBatchItemRef)
{
	CValue *pDest = NULL;
	CGbtBatchItemRefValue *pValue = NULL;
	POS pos = pBatchItemRef->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CGbtBatchItemRefValue*)pBatchItemRef->GetNext(pos);
//		pValue->m_strRelValue = pValue->m_strValue;
		
		if (!IsStringNumber(pValue->m_strRelValue))
		{
			Replace(pValue->m_strRelValue);
		}
	}
}

void CGbItemVariableIDReplace::Replace(CDsvScript *pDsvScript)
{
	if (pDsvScript == NULL)
	{
		return;
	}

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
			if (p->m_strID == m_strSrcID)
			{
				if (m_pDestObject == NULL)
				{
					pDsvScript->Delete(p);
					continue;
				}
			}
		}

		if (nClassID == DVMCLASSID_CDSVELIMINATE)
		{
			Replace((CDsvEliminate*)p);
		}
		else if (DVMCLASSID_CDSVELEMENT == nClassID)
		{
			Replace((CDsvElement*)p);
		}
	}
}

void CGbItemVariableIDReplace::Replace(CDsvElement *pDsvElement)
{
	if (pDsvElement->m_strID != m_strSrcID)
	{
		return;
	}

	POS pos = pDsvElement->GetHeadPosition();
	CDsvElemAttr *p = NULL;
	UINT nClassID = 0;


	pDsvElement->m_strID = m_pDestObject->m_strID;
	pDsvElement->m_strName = m_pDestObject->m_strName;

	while (pos != NULL)
	{
		p = (CDsvElemAttr*)pDsvElement->GetNext(pos);

		if (p->m_strID == _T("name"))
		{
			p->m_strValue = m_pDestObject->m_strName;
		}
		else if (p->m_strID == _T("id"))
		{
			p->m_strValue = m_pDestObject->m_strID;
		}
	}
}

void CGbItemVariableIDReplace::Replace(CDsvEliminate *pDsvEliminate)
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
		
		if (p->m_strID == m_strSrcID)
		{
			if (m_pDestObject == NULL)
			{
				pDsvEliminate->Delete(p);
				continue;
			}

			p->m_strID = m_strDestID;
		}
	}
}

void CGbItemVariableIDReplace::Replace(CCharacteristics *pCharacteristics)
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
			Replace(pVar->m_strScript);
		}
	}
}

void CGbItemVariableIDReplace::Replace_Characteristics(UINT nClassID, CExBaseObject *pGbItemDest)
{
	if (nClassID != GBCLASSID_DEVICE)
	{
		return;
	}

	CDevice *pDevice = (CDevice*)pGbItemDest;
	Replace(pDevice->m_pCharacteristics);
}

