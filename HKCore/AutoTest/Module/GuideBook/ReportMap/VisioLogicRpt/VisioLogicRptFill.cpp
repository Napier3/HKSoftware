#include "StdAfx.h"
#include "VisioLogicRptFill.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//CVisioLogicRptFill

CVisioLogicRptFill::CVisioLogicRptFill(void)
{
	m_pVisioExec = NULL;
	m_pParentWnd = NULL;
	m_pTestControl = NULL;
}

CVisioLogicRptFill::~CVisioLogicRptFill(void)
{
	if (m_pVisioExec != NULL)
	{
		delete m_pVisioExec;
		m_pVisioExec = NULL;
	}
}

long CVisioLogicRptFill::InitVisioRptFill()
{
	m_pVisioExec = new CVFlowExec_Visio();
	return 0;
}

BOOL CVisioLogicRptFill::OpenVisioFile(const CString &strFile)
{
	if (m_pVisioExec == NULL)
	{
		return FALSE;
	}

	if (strFile.IsEmpty())
	{
		return m_pVisioExec->OpenVisioFile(m_strFilePath);
	}
	return m_pVisioExec->OpenVisioFile(strFile);
}

BOOL CVisioLogicRptFill::SaveVisioFile()
{
	if (m_pVisioExec == NULL)
	{
		return FALSE;
	}

	return m_pVisioExec->SaveVisioFile();
}

void CVisioLogicRptFill::CloseFile()
{
	if (m_pVisioExec == NULL)
	{
		return;
	}

	m_pVisioExec->CloseFile();
}

void CVisioLogicRptFill::CloseApplication()
{
	if (m_pVisioExec == NULL)
	{
		return;
	}

	m_pVisioExec->QuitApp();
}

void CVisioLogicRptFill::AdjustReportWindowOnSize()
{
#ifndef _PSX_QT_LINUX_
		CWnd *pWnd = NULL;

		if (::IsWindow(m_hVisioWnd))
		{
			pWnd = CWnd::FromHandle(m_hVisioWnd);
		}

		if (pWnd != NULL)
		{
			CRect rectWin;
			::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
			//rectWin.left += 100;
			pWnd->MoveWindow(rectWin);
			pWnd->SetFocus();
			pWnd->BringWindowToTop();
			pWnd->UpdateWindow();
			pWnd->ShowWindow(SW_SHOW);
			pWnd->Invalidate(TRUE);
		}	
#endif
}

void CVisioLogicRptFill::SetParentWnd(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

void CVisioLogicRptFill::AdjustVisioWindow()
{
	if (m_pVisioExec != NULL)
	{
		CWnd *pWnd = NULL;
		CVisioReadWrite *pVisioRw = m_pVisioExec->GetVisioReadWrite();
		//��ȡVisio�ĵ��Ĵ���
		try
		{
			if (pVisioRw->GetCurDoc() != NULL)
			{
				HWND hWnd = (HWND)pVisioRw->GetApplication().get_WindowHandle32();
				pWnd = CWnd::FromHandle(hWnd);	
				m_hVisioWnd = pWnd->m_hWnd;
			}
		}
		catch(...)
		{
		}

		if (pWnd != NULL)
		{
			AdjustDocWindow(pWnd);
		}
		else
		{

		}
	}
}

void CVisioLogicRptFill::AdjustDocWindow(CWnd *pWnd)
{
#ifndef _PSX_QT_LINUX_

	if (pWnd == NULL)
	{
		if (::IsWindow(m_hVisioWnd))
		{
			pWnd = CWnd::FromHandle(m_hVisioWnd);
		}
	}

	if (pWnd != NULL)
	{
		CRect rectWin;
		pWnd->GetWindowRect(rectWin);
		::SetParent(pWnd->GetSafeHwnd(),m_pParentWnd->GetSafeHwnd());

		pWnd->ModifyStyle(WS_SYSMENU,0);
		pWnd->ModifyStyle(WS_SIZEBOX,0);
		::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
		pWnd->MoveWindow(rectWin);
		pWnd->SetFocus();
	}
#endif
}

void CVisioLogicRptFill::OnItemTestFinished(CGbItemBase* pItem, const CString &strActLogic)
{
	if (m_pVisioExec == NULL)
	{
		return;
	}

	m_pVisioExec->InitFlowShapesFromPage(strActLogic);
	CDvmDataset *pOrign = &m_pVisioExec->m_oOrigDataDataset;
	CString strPath = Gb_GetItemPathID(pItem);   //��Ŀ��CDevice��һ����·����Ϣ

	POS pos = pOrign->GetHeadPosition();
	CDvmData *pOrignData = NULL;
	CString strValue, strID, strDataType, strUnit, strItemPath;

	while (pos != NULL)
	{
		pOrignData = (CDvmData *)pOrign->GetNext(pos);

		//Name��¼����ԭʼ���ݵ�·��(��Ŀ·��$$����ID)��·����ƥ�䣬��ֱ����һ��
		strItemPath = GetItemPath(pOrignData->m_strName, strID);  //������Ŀ·��������ID

		if (strItemPath.IsEmpty())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("�߼�ͼ������·������%s�������ܲ��ҵ���Ӧ����Ŀ·��"), pOrignData->m_strName);
			continue;
		}

		if (strItemPath != strPath)
		{
			continue;
		}

		if (strID.IsEmpty())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("�߼�ͼ������·������%s�������ܲ��ҵ���Ӧ������ID"), pOrignData->m_strName);
			continue;
		}

		//strID = pOrignData->m_strID;
		strValue = GetReportString(pItem, strID, strDataType, strUnit);

		if (strValue.GetLength() > 0)
		{
			pOrignData->m_strValue = strValue;
			pOrignData->m_nIndex = 1;
		}

		if (strDataType.GetLength() > 0)
		{
			pOrignData->m_strDataType = strDataType;
		}

		if (strUnit.GetLength() >0)
		{
			pOrignData->m_strUnit = strUnit;
		}
	}

	//ˢ���߼�ͼ
	m_pVisioExec->UpdataValue_AllOrigDatas();
	m_pVisioExec->UpdateAllShapes();
	SaveVisioFile();
}

CString CVisioLogicRptFill::GetItemPath(const CString &strOrignData, CString &strDataID)
{
	CString strItemPath;
	long nLen = 0;
	char *pChar = NULL;
	char *pBegin = NULL;
	char *pEnd = NULL;
	nLen = CString_to_char(strOrignData, &pChar);
	pBegin = pChar; 
	pEnd = pChar + nLen;

	char *p = pBegin;
	char *p1 = NULL;

	while (p < pEnd)
	{
		if (*p == '$')
		{
			p1 =p;
			p = p+1;

			if (*p == '$')
			{
				//��������$����
				p--;
				*p = 0;
				strItemPath = pBegin;
				pBegin = p + 2;
				strDataID = pBegin;
				break;
			}
		}

		p++;
	}

	delete pChar;
	
	return strItemPath;
}

CString CVisioLogicRptFill::GetReportString(CGbItemBase* pItem, const CString &strDataID, CString &strDataType, CString &strUnit)
{
	BOOL bTrue = FALSE;
	CString strValue;
	CReport *pReport = pItem->GetReport(-1);
	UINT nClassID = pItem->GetClassID();

	if (pReport == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("������Ŀ��%s��û���ҵ�����"), pItem->m_strName);
	}

	switch (nClassID)
	{
	case GBCLASSID_COMMCMD:
		{
			CCommCmd *pCommCmd = (CCommCmd *)pItem;
			bTrue = GetReportString_CommCmd(pCommCmd, pReport, strDataID, strValue, strDataType, strUnit);
		}
		break;

	case GBCLASSID_MACROTEST:
		{
			CMacroTest *pMacroTest = (CMacroTest*)pItem;
			bTrue = GetReportString_MacroTest(pMacroTest, pReport, strDataID, strValue, strDataType, strUnit);
		}
		break;

	case GBCLASSID_SYSPARAEDIT:
		{
			CSysParaEdit *pSysparaEdit = (CSysParaEdit*)pItem;
			bTrue = GetReportString_SysParaEdit(pSysparaEdit, pReport, strDataID, strValue, strDataType, strUnit);
		}
		break;

	case GBCLASSID_SAFETY:
		{
			CSafety *pSafety = (CSafety *)pItem;
			bTrue = GetReportString_Safety(pSafety, pReport, strDataID, strValue, strDataType, strUnit);
		}
		break;
	}

	if (!bTrue)
	{
		//��ʱֻ����ȫ�ַ�ƥ������������������Բο���
		//CValue* CRptFillInterface::FindValue(CValues *pValues, const CString &strID)
		if (pReport != NULL)
		{
			CValue *pValue = pReport->FindReportData(strDataID);

			if (pValue == NULL)
			{
				strValue.Empty();
			}
			else
			{
				strValue = pValue->m_strValue;
			}
		}
	}

	return strValue;
}

BOOL CVisioLogicRptFill::GetReportString_CommCmd(CCommCmd* pCommCmd, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit)
{
	CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
	CGbCommCmdMms *pGbCmd = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);
	long nCpuIndex = pCommCmd->GetCpusIndex();

	if (pReport != NULL)
	{
		//��չ�������ݶ���
		CDvmData *pDvmData = (CDvmData*)pReport->m_pRptDvmDataset->FindByID_Has(strDataID);

		if (pDvmData != NULL)
		{
			strValue = pDvmData->m_strValue;
			strUnit = pDvmData->m_strUnit;
			strDataType = pDvmData->m_strDataType;
			return TRUE;
		}

		//��չ��������-��չ����
		CDvmValue *pDvmValue = pReport->FindRptValueExByValueID(strDataID);

		if (pDvmValue != NULL)
		{
			strValue = pDvmValue->m_strValue;
			strDataType = pDvmValue->m_strDataType;
			return TRUE;
		}
	}

	//ͨѶ������������ݼ�   //���ݼ�����������µ�һ������
	CDataSet *pDataset = pCommCmd->GetDataset(nCpuIndex);

	if (pDataset == NULL)
	{
		return FALSE;
	}

	//���ݶ���
	CDataObj *pDataObj = pDataset->FindDataObjByID_Has(strDataID);

	if (pDataObj != NULL)
	{
		strValue = pDataObj->m_strValue;
		strUnit = pDataObj->m_strUnit;
		strDataType = pDataObj->m_strDataType;
		return TRUE;
	}

	//���ݶ������չ����Value
	CDataObjValue *pDataObjVal = pDataset->FindDataObjValueByID_Has(strDataID);

	if (pDataObjVal != NULL)
	{
		strValue = pDataObjVal->m_strValue;
		strDataType = pDataObjVal->m_strDataTypeID;
		return TRUE;
	}

	return FALSE;
}

BOOL CVisioLogicRptFill::GetReportString_MacroTest(CMacroTest* pMacroTest, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit)
{
	//��������Ŀ����Ҫ�����ݿ�����Դ�ڹ��ϲ��������ϲ���������ӵ������У��ʴ˴�ֱ��return FALSE
	return FALSE;
}

BOOL CVisioLogicRptFill::GetReportString_SysParaEdit(CSysParaEdit *pSysparaEdit, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit)
{
	CString strDatasetPath = pSysparaEdit->GetDatasetPath();
	CDevice *pDevice = (CDevice*)pSysparaEdit->GetAncestor(GBCLASSID_DEVICE);
	CExBaseList oListDataSet;
	CDataSet *pDataset = NULL;

	if (pDevice->SelectDataSetList(strDatasetPath, oListDataSet, DSID_ALL_DVM) == 1)
	{
		pDataset = (CDataSet *)oListDataSet.GetHead();
		CDataObj *pDataObj = pDataset->FindDataByID(strDataID);

		if (pDataObj != NULL)
		{
			strValue = pDataObj->m_strValue;
			strDataType = pDataObj->m_strDataType;
			strUnit = pDataObj->m_strUnit;
			oListDataSet.RemoveAll();
			return TRUE;
		}
	}

	oListDataSet.RemoveAll();
	return FALSE;
}

BOOL CVisioLogicRptFill::GetReportString_Safety(CSafety *pSafety, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit)
{
	CShortData *pShortData = (CShortData*)pSafety->m_pDatas->FindByID(strDataID);

	if (pShortData != NULL)
	{
		strValue = pShortData->m_strValue;
		strUnit = pShortData->m_strUnit;
		strDataType = pShortData->m_strDataTypeID;
		return TRUE;
	}

	return FALSE;
}

CString CVisioLogicRptFill::GetVisioFilePath()
{
	if (!m_strFilePath.IsEmpty())
	{
		return m_strFilePath;
	}

	CString strFile, strNewVisioFile;
	CGuideBook *pGuideBook = m_pTestControl->m_pGuideBook;
	strFile = ChangeFilePostfix(pGuideBook->m_strGbXmlFile, g_strVisioFilePostfix);

	strNewVisioFile = m_pTestControl->GetGbBinaryFile();
	strNewVisioFile = ChangeFilePostfix(strNewVisioFile, g_strVisioFilePostfix);

	if (!IsFileExist(strFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("���߼�ͼ��%s��ʧ�ܣ��ļ������ڣ�"), strFile);
		return m_strFilePath;
	}

	if (!IsFileExist(strNewVisioFile))
	{
		X_CopyFile(strFile,strNewVisioFile,FALSE);
	}
	
	m_strFilePath = strNewVisioFile;
	return m_strFilePath;
}

void CVisioLogicRptFill::LocateVisio(CExBaseObject *pItem)
{
	if (m_pVisioExec == NULL)
	{
		return;
	}

	CGbItemBase* pGbItem = (CGbItemBase *)pItem;

	CString strActLogic = pGbItem->GetActLogic_String();

	if (strActLogic.GetLength() <= 0)
	{
		return;
	}

	m_pVisioExec->ActivePage(strActLogic);
}