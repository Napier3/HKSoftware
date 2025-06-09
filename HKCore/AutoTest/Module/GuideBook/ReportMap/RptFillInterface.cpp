#include "StdAfx.h"
#include "RptFillInterface.h"
#include "../../TestControl/SmartTestBaseApp.h"
#include "../../../../Module/API/FileApi.h"

BOOL CRptFillInterface::g_bClearBeforeFillRpt = TRUE;  //填充报告数据的时候，首先清除标签位置的数据

CRptFillInterface::CRptFillInterface(void)
{
	m_nCommCmdCpusIndex = 0;
	m_bFillReport = TRUE;

	m_pGuideBook = NULL;
}

CRptFillInterface::~CRptFillInterface(void)
{
}

void CRptFillInterface::SetParentWnd(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

CWnd* CRptFillInterface::GetReportMainWnd()
{
	return NULL;
}

HWND CRptFillInterface::FindRptDocWindow()
{
	CString strDoc = GetPathFileNameFromFilePathName(m_strReportFile);
	strDoc = strDoc.Left(strDoc.GetLength() - 4);//去掉后缀，有些WORD标题，没有带【.doc】
	return FindRptDocWindow(strDoc);
}

CWnd* CRptFillInterface::FindRptDocWindowEx()
{
	HWND hWnd = FindRptDocWindow();

	if (hWnd == NULL)
	{
		return NULL;
	}
	else
	{
		return CWnd::FromHandle(hWnd);
	}
}

HWND CRptFillInterface::FindRptDocWindow(const CString &strDoc)
{
    HWND hWndFind = NULL;

#ifndef _PSX_QT_LINUX_
    //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("FindRptDocWindow(%s)"), strDoc);
	CWnd *pWnd = CWnd::GetDesktopWindow();

	TCHAR strBuff[200];
	CString strWindowTitle;
	HWND hChildWnd;
	HWND hWnd=::GetWindow(pWnd->m_hWnd, GW_CHILD);
	hChildWnd=hWnd;
	long nLen = strDoc.GetLength();

	while(hChildWnd!=NULL)
	{
		::GetWindowText(hChildWnd,strBuff,100);

		if (strBuff[0] != 0)
		{
			strWindowTitle = strBuff;

			if (strWindowTitle.GetLength() > nLen)
			{
				strWindowTitle = strWindowTitle.Left(nLen);
				//CLogPrint::LogString(XLOGLEVEL_TRACE, strWindowTitle);

				if (strWindowTitle.CompareNoCase(strDoc) == 0)
				{
					//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>>>>>>>>>>FindWindow=%s"), strWindowTitle);
					hWndFind = hChildWnd;
					break;
				}
			}
		}

		hChildWnd=::GetNextWindow(hChildWnd,GW_HWNDNEXT);	
	}

#endif

    return hWndFind;
}

void CRptFillInterface::FreeReportMap()
{
}

CGbItemBase* CRptFillInterface::GetParentGbItem(CReport *pReport)
{
	CExBaseObject *pParent = (CExBaseObject*)pReport->GetParent();
	CGbItemBase *pGbItem = NULL;

	while (pParent != NULL)
	{
		if (Gb_IsItemBaseClassID(pParent->GetClassID()))
		{
			pGbItem = (CGbItemBase*)pParent;
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	pParent = (CExBaseObject*)pParent->GetParent();

	if (pParent != NULL && pParent->GetClassID() == GBCLASSID_MACROCHARITEMS)
	{
		pGbItem = (CGbItemBase*)pParent;
	}

	return pGbItem;
}

long CRptFillInterface::InitFillReport(CGbItemBase* pItemBase)
{
	return 0;
}

long CRptFillInterface::InitFillReport(CReport* pReport)
{
	return FillReport(pReport, 0, FALSE);
}

long CRptFillInterface::UpdateReport(CReport* pReport)
{
	FillReport(pReport, 0, 0);
	return 0;
}

void CRptFillInterface::ChopValueString(CRptData *pData, CString &strValue)
{
	if (!IsStringNumber(strValue))
	{
		return;
	}

	long nPrecision = pData->GetPrecision();

	if (nPrecision > 0)
	{
		if (strValue.GetLength() > 0)
		{
			strValue.Trim();
			CString strFormat;
			strFormat.Format(_T("%%.%df"), nPrecision);
#ifdef _UNICODE
			double dValue = _wtof(strValue);
#else
            double dValue = atof(strValue.GetString());
#endif
			strValue.Format(strFormat, dValue);
		}
	}
	else
	{
		ChopFloatString(strValue, -1);
	}
}

CValue* CRptFillInterface::FindValue(CValues *pValues, const CString &strID)
{
	CValue * oValue = (CValue*)pValues->FindByID(strID);

	if (oValue != NULL)
	{
		return oValue;
	}

	POS pos = pValues->GetHeadPosition();
	CValue *p = NULL;

	while (pos != NULL)
	{
		p = (CValue *)pValues->GetNext(pos);

		if (p->m_strID.Right(strID.GetLength()) == strID)
		{
			oValue = p;
			break;
		}

		if (strID.Right(p->m_strID.GetLength()) == p->m_strID)
		{
			oValue = p;
			break;
		}
	}

	return oValue;
}

CString CRptFillInterface::GetReportString(CRptData *pData, CRptBkmk *pBkmk, CReport *pReport)
{
	BOOL bTrue = FALSE;
	CString strValue;
	CExBaseObject *pItem = (CExBaseObject*)pReport->GetParent()->GetParent();
	ASSERT (pItem != NULL);
	UINT nClassID = pItem->GetClassID();
	CString strAdd;

	CString strDataID = pData->m_strID;

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		{
			CCommCmd *pCommCmd = (CCommCmd *)pItem;
			bTrue = GetReportString_CommCmd(pCommCmd, pBkmk, pReport, pData, strValue);
		}
		break;

	case GBCLASSID_MACROTEST:
		{
			CMacroTest *pMacroTest = (CMacroTest*)pItem;
			bTrue = GetReportString_MacroTest(pMacroTest, pBkmk, pReport, pData, strValue, strDataID);
		}
		break;

	case GBCLASSID_SYSPARAEDIT:
		{
			CSysParaEdit *pSysparaEdit = (CSysParaEdit*)pItem;
			bTrue = GetReportString_SysParaEdit(pSysparaEdit, pBkmk, pReport, pData, strValue);
		}
		break;

	case GBCLASSID_SAFETY:
		{
			CSafety *pSafety = (CSafety *)pItem;
			bTrue = GetReportString_Safety(pSafety, pBkmk, pReport, pData, strValue);
		}
		break;
	}

	if (!bTrue)
	{
		CValues * oValues = pReport->GetValues();
		CValue * oValue = FindValue(oValues, strDataID);
		strValue.Empty();

		if (oValue == NULL)
		{
			//shaolei  20211018
			//对于全局数据部分的书签，例如TestAppDef部分，也有可能是扩展报告（m_pRptDataset）中的数据
			CDvmValue *pValue = pReport->FindRptValueExByValueID(pBkmk->m_strDataAttrID);

			if (pValue == NULL)
			{
				CDvmData *pRptData = pReport->FindRptExDataByDataID(pBkmk->m_strDataAttrID);

				if (pRptData != NULL)
				{
					strValue = pRptData->m_strValue;
				}
			}
			else
			{
				strValue = pValue->m_strValue;
			}
		}
		else
		{
			strValue = oValue->m_strValue;
			//ChopValueString(pData, strValue);
		}
	}

	if (pBkmk->m_strProcess.GetLength() > 0 && strValue.GetLength() > 0)
	{
#ifndef GUIDEBOOK_DEV_MODE
		CBkmkDataProcessMngr *pProcessMngr = g_theSmartTestBaseApp->GetBkmkDataProcessMngr();
		pProcessMngr->ProcessData(pBkmk->m_strProcess, strValue, strAdd, pData->GetPrecision());
#endif
	}

	if (strValue.GetLength() > 0)
	{
		ChopValueString(pData, strValue);
	}

	strValue += strAdd;
	
	return strValue;
}

BOOL CRptFillInterface::GetReportString_CommCmd(CCommCmd *pCommCmd, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue)
{
	CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);

	//扩展报告数据对象
	CDvmData *pDvmData = (CDvmData*)pReport->m_pRptDvmDataset->FindByID_Has(pData->m_strID);

	if (pDvmData != NULL)
	{
		//strValue = pDvmData->GetAttrValue(pBkmk->m_strDataAttrID);
		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
		{
			strValue = pDvmData->m_strName;
		}
		else
		{
			strValue = pDvmData->m_strValue;
		}

		return TRUE;
	}

	//扩展报告数据-扩展属性
	CDvmValue *pDvmValue = pReport->FindRptValueByID(pData->m_strID, pBkmk->m_strDataAttrID);

	if (pDvmValue == NULL)
	{
		pDvmValue = pReport->FindRptValueExByValueID(pData->m_strID);
	}

	if (pDvmValue != NULL)
	{
		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
		{
			strValue = pDvmValue->m_strName;
		}
		else
		{
			strValue = pDvmValue->m_strValue;
		}

		return TRUE;
	}

	if (pBkmk->m_strDataAttrID == g_strDataAttrID_Value)
	{
		CValues * oValues = pReport->GetValues();
		CValue * oValue = FindValue(oValues, pData->m_strID);

		if (oValue != NULL)
		{
			strValue = oValue->m_strValue;
			return TRUE;
		}
	}

	//通讯命令关联的数据集   //数据集保存的是最新的一次数据
	CDataSet *pDataset = pCommCmd->GetDataset(m_nCommCmdCpusIndex);

	if (pDataset == NULL)
	{
		return FALSE;
	}

	//数据对象
	CDataObj *pDataObj = pDataset->FindDataObjByID_Has(pData->m_strID);

	if (pDataObj != NULL)
	{
		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
		{
			strValue = pDataObj->m_strName;
		}
		else
		{
			strValue = pDataObj->m_strValue;
		}

		return TRUE;
	}

	//数据对象的扩展属性Value
	CDataObjValue *pDataObjVal = pDataset->FindDataObjValueByID_Has(pData->m_strID);

	if (pDataObjVal != NULL)
	{
		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
		{
			strValue = pDataObjVal->m_strName;
		}
		else
		{
			strValue = pDataObjVal->m_strValue;
		}

		return TRUE;
	}

	return FALSE;
}

/*
BOOL CRptFillInterface::GetReportString_CommCmd(CCommCmd *pCommCmd, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue)
{
	CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);
	CDataObj *pDataObj = NULL;

	if (pGbCmd != NULL)
	{
		if (pGbCmd->m_strDataType == g_strGbCommCmdDataType_Struct)
		{
			if (pBkmk->m_strDataAttrID == g_strDataAttrID_Value)
			{
				CDvmData *pDvmData = (CDvmData*)pReport->m_pRptDvmDataset->FindByID_Has(pData->m_strID);

				if (pDvmData != NULL)
				{
					strValue = pDvmData->m_strValue;
					return TRUE;
				}
			}

			CDvmValue *pDvmValue = pReport->FindRptValueByID(pData->m_strID, pBkmk->m_strDataAttrID);

			if (pDvmValue != NULL)
			{
				strValue = pDvmValue->m_strValue;
				return TRUE;
			}
		}
	}

	CDataSet *pDataset = pCommCmd->GetDataset(m_nCommCmdCpusIndex);

	if (pDataset != NULL)
	{
		CDataObj *pDataObj = pDataset->FindDataObjByID_Has(pData->m_strID);

		if (pDataObj != NULL)
		{
			if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
			{
				strValue = pDataObj->m_strName;
				return TRUE;
			}
		}

		// 		else    //data中找不到，就从Value中找   shaolei 2019.07.23
		// 		{
		// 			CDataObjValue *pDataObjVal = pDataset->FindDataObjValueByID_Has(pData->m_strID);
		// 
		// 			if (pDataObjVal != NULL)
		// 			{
		// 				if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
		// 				{
		// 					strValue = pDataObjVal->m_strName;
		// 					return TRUE;
		// 				}
		// 			}
		// 		}
	}

	return FALSE;
}
*/

BOOL CRptFillInterface::GetReportString_SysParaEdit(CSysParaEdit *pSysParaEdit, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue)
{
	CString strDatasetPath = pSysParaEdit->GetDatasetPath();
	CDevice *pDevice = (CDevice*)pSysParaEdit->GetAncestor(GBCLASSID_DEVICE);
	CExBaseList oListDataSet;
	CDataSet *pDataset = NULL;

	if (pDevice->SelectDataSetList(strDatasetPath, oListDataSet, DSID_ALL_DVM) == 1)
	{
		pDataset = (CDataSet *)oListDataSet.GetHead();
		CDataObj *pDataObj = pDataset->FindDataByID(pData->m_strID);

		if (pDataObj != NULL)
		{
			if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
			{
				strValue = pDataObj->m_strName;
				oListDataSet.RemoveAll();
				return TRUE;
			}
		}
	}

	oListDataSet.RemoveAll();
	return FALSE;
}

BOOL CRptFillInterface::GetReportString_MacroTest(CMacroTest *pMacroTest, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue, CString &strDataID)
{
	CGuideBook *pGuideBook = (CGuideBook*)pMacroTest->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook->m_pTestMacros != NULL);

	if (pGuideBook->m_pTestMacros == NULL)
	{
		return FALSE;
	}

	CMacroTestPara *pTestPara = pMacroTest->GetMacroTestPara();
	CTestMacro *pTestMacro = (CTestMacro*)pGuideBook->m_pTestMacros->FindByID(pTestPara->GetMacroID());

	if (pTestMacro == NULL)
	{
		return FALSE;
	}

	if (pMacroTest->GetParent()->GetClassID() == GBCLASSID_MACROCHARITEMS)
	{
		CMacroCharItems *pCMacroCharItems = (CMacroCharItems*)pMacroTest->GetParent();
		strDataID = pCMacroCharItems->GetMacroTestDataID(pData->m_strID);
	}
	else
	{
		strDataID = pData->m_strID;
	}

	CShortData *pShortData = pTestMacro->FindDataByID(strDataID);

	if (pShortData == NULL)
	{
		return FALSE;
	}

	//名称属性
	if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
	{
		strValue = pShortData->m_strName;
		return TRUE;
	}

	//处理数据类型
	CDataTypes *pDataTypes = pGuideBook->m_pTestMacros->GetDataTypes();

	if (pDataTypes == NULL)
	{
		return FALSE;
	}

	CDataType *pDataType = (CDataType*)pDataTypes->FindByID(pData->m_strDataType);

	if (pDataType == NULL)
	{
		return FALSE;
	}

	if (pDataType->GetCount() == 0)
	{
		return FALSE;
	}

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(strValue);

	if (pValue == NULL)
	{
		return FALSE;
	}
	else
	{
		strValue = pValue->m_strName;
		return TRUE;
	}

	return FALSE;
}

BOOL CRptFillInterface::GetReportString_Safety(CSafety *pSafety, CRptBkmk *pBkmk, CReport *pReport, CRptData *pData, CString &strValue)
{
	CShortData *pShortData = (CShortData*)pSafety->m_pDatas->FindByID(pData->m_strID);

	if (pShortData != NULL)
	{
		if (pBkmk->m_strDataAttrID == g_strDataAttrID_Name)
		{
			strValue = pShortData->m_strName;
			return TRUE;
		}
	}

	return FALSE;
}
