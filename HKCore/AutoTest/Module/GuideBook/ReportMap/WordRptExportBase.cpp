#include "StdAfx.h"
#include "WordRptExportBase.h"
#include "..\..\TestControl/TCtrlCntrBaseApp.h"
#include "..\GuideBookUpdateTool.h"
#include "..\..\SmartTestRpcEventApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern 	CDataGroup g_oWordReportExGroup;

CWordRptExportBase::CWordRptExportBase()
{
	m_pListTestControls = NULL;
	m_pListTestProject = NULL;
	m_bShowWordApp = FALSE;
	m_bExportDetailWord = FALSE;
	m_bCmbnMgrp = TRUE;
	m_pNewGuideBook = NULL;
	m_bCloseWordApp = TRUE;
// 	m_nExcelRowIndex = 1;
	m_bUseUpdateGudeBook = FALSE;
	m_bNotExportErrRpt = FALSE;

	m_bCmbnExort_XML = FALSE;
	m_bCmbnExort_GBRPT = FALSE;

}

CWordRptExportBase::~CWordRptExportBase()
{

}

void CWordRptExportBase::AttachMsgRcvWnd(CWnd *pWnd, UINT nMsg)
{
	m_nExportMsg = nMsg;
	m_pExportMsgRcvWnd = pWnd;
}

//2021-1-2 lijunqing Word��XML��Gbrpt��ʹ�õ������ļ��е���
void CWordRptExportBase::SetCmbnMgrp(const CString &strCmbnDestPath, const CString &strWordFileSubPath , const CString &strXmlFileSubPath , const CString &strGbrptFileSubPath)
{
	m_strCmbnDestPath = strCmbnDestPath;
	m_strWordFileSubPath = strWordFileSubPath;
	m_strXmlFileSubPath = strXmlFileSubPath;
	m_strGbrptFileSubPath = strGbrptFileSubPath;

	path_CheckSeparater(m_strCmbnDestPath);
	path_CheckSeparater(m_strWordFileSubPath);
	path_CheckSeparater(m_strXmlFileSubPath);
	path_CheckSeparater(m_strGbrptFileSubPath);

	CString strPath;

	strPath = m_strCmbnDestPath;
	CreateAllDirectories(strPath);

	if (m_strWordFileSubPath.GetLength() > 0)
	{
		strPath = m_strCmbnDestPath + m_strWordFileSubPath;
		CreateAllDirectories(strPath);
	}

	if (m_strXmlFileSubPath.GetLength() > 0)
	{
		strPath = m_strCmbnDestPath + m_strXmlFileSubPath;
		CreateAllDirectories(strPath);
	}

	if (m_strGbrptFileSubPath.GetLength() > 0)
	{
		strPath = m_strCmbnDestPath + m_strGbrptFileSubPath;
		CreateAllDirectories(strPath);
	}
}
void CWordRptExportBase::SetCmbnMgrpExportUse(BOOL bUseXmlFile, BOOL bUseGbrptFile)
{
	m_bCmbnExort_XML = bUseXmlFile;
	m_bCmbnExort_GBRPT = bUseGbrptFile;
}

void CWordRptExportBase::AttachGuideBook(CGuideBook *pGuideBook)
{
	m_pNewGuideBook = pGuideBook;

	if (m_pNewGuideBook == NULL)
	{
		return;
	}

	m_strNewWordRptFile = m_pNewGuideBook->m_strGuideBookFile;
	m_strNewWordRptFile = ChangeFilePostfix(m_strNewWordRptFile, g_strDocFilePostfix);
}

void CWordRptExportBase::ExportReport(CTestControlBase *pTestControl, CTestProject *pTestProject, CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd)
{
	if (pTestProject  != NULL)
	{
		ASSERT (m_pExportMsgRcvWnd != NULL);
		pTestProject->m_dwReserved = 0;
		m_pExportMsgRcvWnd->PostMessage(m_nExportMsg, (WPARAM)pTestProject, WORD_EXPORT_STATE_EXPORT_BEGIN);
	}

	//ʹ���µı���ģ��������д����
	if (m_pNewGuideBook != NULL)
	{
		CString strWordFile = pTestControl->GetReportFilePath();
		::X_CopyFile(m_strNewWordRptFile, strWordFile, FALSE);//���µı���ģ�壬����֮ǰ�ı���
	}

	g_oWordReportExGroup.DeleteAll();
	ExportReport_AllWord(pTestControl, oBuffer, pMsgWnd);	//����ȫ���Ĳ��Ա���

	if (m_bExportDetailWord)
	{
		//ExportDetailWord(pTestControl);
		ExportDetailExcel(pTestControl);
	}

	if (pTestProject  != NULL)
	{
		pTestProject->m_dwReserved = 1;
		m_pExportMsgRcvWnd->PostMessage(m_nExportMsg, (WPARAM)pTestProject, WORD_EXPORT_STATE_EXPORT_FINISH);
	}

	//2021-1-27  lijunqing  �ͷ���ʱ����
	pTestControl->ClearItemInDbState();
}

void CWordRptExportBase::ExportReport_Word(CTestControlBase *pTestControl, CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd, const CString &strDocFile)
{
	if (pTestControl->OpenWordReportFile(TRUE, strDocFile))
	{
		pTestControl->GenerateWordReport(oBuffer, pMsgWnd);
		pTestControl->SaveReport();
		pTestControl->CloseReportFill();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Open Project [%s] Word Report File Failed!"), pTestControl->GetGbBinaryFile());
	}

	//2019-1-28  lijq  ������������xml�ļ�
	//pTestControl->SaveFinalXMLReport();
}

void CWordRptExportBase::SaveFinalXMLReport(CTestControlBase *pTestControl)
{
	//2021-1-2  lijunqing  ��������ݿ�ģʽ��û�����ݣ��޷�����������Word��ʱ������ݿ��ȡ��Ȼ�󵼳�������ͷ�
	pTestControl->SaveFinalXMLReport(); 

	if ( pTestControl->m_pGuideBook->IsSaveRptToDB() || g_theSmartTestBaseApp->IsSaveRptToDB())
	{
		CString strTempFilePath = pTestControl->GetItemTempPath();
		gb_ClearItemInDbState(pTestControl->m_pGuideBook, _T(""), g_theSmartTestBaseApp->IsWriteTestTempFile()); //�ͷ�
	}

}

void CWordRptExportBase::ExportReport_AllWord(CTestControlBase *pTestControl, CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd)
{
	if (m_bNotExportErrRpt)
	{
		if (pTestControl->m_pGuideBook->IsTestError())
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��%s�����ϸ񣬲�����"), pTestControl->GetGbBinaryFileName());
			return;
		}
	}

	CRptFillInterface* pReportFill = pTestControl->m_pReportFill;
	pTestControl->m_pReportFill = NULL;
	
	CString strRptTempFile, strNewWordFile;
	strRptTempFile = pTestControl->m_pGuideBook->GetReportTemplateFullPath(_T(""));

	if (m_bUseUpdateGudeBook)
	{
		CGuideBookUpdateTool oGbUpdate;
		oGbUpdate.Update_ReportMap(pTestControl->m_pGuideBook);
	}

	//�������������ļ�
	//2021-1-2  lijunqing  ��������ݿ�ģʽ��û�����ݣ��޷�����������Word��ʱ������ݿ��ȡ��Ȼ�󵼳�������ͷ�
	//pTestControl->SaveFinalXMLReport();  

	//������ĵ�����ֻ����ϵͳ�����ģʽ�£�����Ҫ����
	if (pReportFill == NULL)
	{
		ExportReport_Word(pTestControl, oBuffer, pMsgWnd, _T(""));
	}
	else 
	{
		if (pReportFill->IsReportFill_System())
		{
			ExportReport_Word(pTestControl, oBuffer, pMsgWnd, _T(""));
		}
		else
		{
			//WORD����ģʽ�£����������ҵָ���飬����Ҫ�ر�WORD���棬�����µ���
			if (m_bUseUpdateGudeBook)
			{
				pReportFill->CloseDoc(FALSE); //�ر�WORD����
				strNewWordFile = pTestControl->GetReportFilePath();
				::X_CopyFile(strRptTempFile, strNewWordFile, FALSE);//���µı���ģ�壬����֮ǰ�ı���
				ExportReport_Word(pTestControl, oBuffer, pMsgWnd, _T(""));//���µ���
			}
			//ʹ���±���ģ�壬��������  shaolei  20210619
		}
	}
	//��չ�����ĵ�����20180907  lijq
	CDvmDataset *pExtendRptTemplates = pTestControl->m_pGuideBook->GetExtendRptTemplateDef(FALSE);

	if (pExtendRptTemplates == NULL)
	{
		//2021-1-2  lijunqing  ��������ݿ�ģʽ��û�����ݣ��޷�����������Word��ʱ������ݿ��ȡ��Ȼ�󵼳�������ͷ�
		SaveFinalXMLReport(pTestControl);
		pTestControl->m_pReportFill = pReportFill;
		return;
	}

	if (pExtendRptTemplates->GetCount() == 0)
	{
		pTestControl->m_pReportFill = pReportFill;

		//2021-1-2  lijunqing  ��������ݿ�ģʽ��û�����ݣ��޷�����������Word��ʱ������ݿ��ȡ��Ȼ�󵼳�������ͷ�
		SaveFinalXMLReport(pTestControl);

		return;
	}

	POS pos = pExtendRptTemplates->GetHeadPosition();
	CDvmData *pRptTemp = NULL;
	long nIndex = 0;
	CString strID = _T("doc-ex-file");

	while (pos != NULL)
	{
		pRptTemp = (CDvmData *)pExtendRptTemplates->GetNext(pos);
		strRptTempFile = pTestControl->m_pGuideBook->GetReportTemplateFullPath(pRptTemp->m_strName);
		strNewWordFile = pTestControl->GetReportFilePath(pRptTemp->m_strFormat);
		::X_CopyFile(strRptTempFile, strNewWordFile, FALSE);//���µı���ģ�壬����֮ǰ�ı���
		ExportReport_Word(pTestControl, oBuffer, pMsgWnd, strNewWordFile);

		if (nIndex > 0)
		{
			strID.Format(_T("%s%d"), strID, nIndex);
		}

		CDvmData *pNewData = new CDvmData();
		pNewData->m_strName = strID;
		pNewData->m_strID = strID;
		pNewData->m_strValue = strNewWordFile;
		g_oWordReportExGroup.AddNewChild(pNewData);
		nIndex++;
	}

	//2021-1-2  lijunqing  ��������ݿ�ģʽ��û�����ݣ��޷�����������Word��ʱ������ݿ��ȡ��Ȼ�󵼳�������ͷ�
	SaveFinalXMLReport(pTestControl);

	pTestControl->m_pReportFill = pReportFill;

	
	if (atsrpc_IsSmartTestRpc())
	{
		//shaolei  20210929
		//������ⲿCOM���ã������´򿪱��档
		//�ⲿϵͳ������Ҫ���кϲ������������Ҫ���ĵ������˴��򿪱��棬����ܻᵼ���ⲿϵͳ��ʧ��
		return;
	}
	//���������ģ�壬�����´򿪱���
	if (pReportFill != NULL)
	{
		if (m_bUseUpdateGudeBook && (!pReportFill->IsReportFill_System()))
		{
			//pTestControl->OpenWordReportFile();
			pReportFill->Open(pTestControl->GetReportFile(), FALSE);
		}
	}
}

void CWordRptExportBase::CopyReportFileToDest(CTestControlBase *pTestControl)
{
	if (m_bNotExportErrRpt)
	{
		if (pTestControl->m_pGuideBook->IsTestError())
		{
			//�������浽Ŀ��λ��
			return;
		}
	}

	//�򿪱����ļ�
	CString strWordFile = pTestControl->GetReportFilePath();
	CString strDestFile = GetPathFileNameFromFilePathName(strWordFile);

	if (m_strWordFileSubPath.GetLength() > 0)
	{
		strDestFile = m_strCmbnDestPath + m_strWordFileSubPath + strDestFile;
	}
	else
	{
		strDestFile = m_strCmbnDestPath + strDestFile;
	}

	::CopyFile(strWordFile, strDestFile, FALSE);

	if (m_bCmbnExort_XML)
	{
		strDestFile = GetPathFileNameFromFilePathName(strWordFile);
		if (m_strXmlFileSubPath.GetLength() > 0)
		{
			strDestFile = m_strCmbnDestPath + m_strXmlFileSubPath + strDestFile;
		}
		else
		{
			strDestFile = m_strCmbnDestPath + strDestFile;
		}

		strDestFile = ChangeFilePostfix(strDestFile, "xml");
		strWordFile = ChangeFilePostfix(strWordFile, "xml");
		::CopyFile(strWordFile, strDestFile, FALSE);
	}

	if (m_bCmbnExort_GBRPT)
	{
		strDestFile = GetPathFileNameFromFilePathName(strWordFile);
		if (m_strGbrptFileSubPath.GetLength() > 0)
		{
			strDestFile = m_strCmbnDestPath + m_strGbrptFileSubPath + strDestFile;
		}
		else
		{
			strDestFile = m_strCmbnDestPath + strDestFile;
		}

		strDestFile = ChangeFilePostfix(strDestFile, g_strGuideBookBinaryPostfix);
		strWordFile = ChangeFilePostfix(strWordFile, g_strGuideBookBinaryPostfix);
		::CopyFile(strWordFile, strDestFile, FALSE);
	}
}

//û���ӱ��棬�����ı��浼����Ŀ���ַ
//���ӱ��棬���ܵı��浼����Ŀ���ַ
void CWordRptExportBase::CmbnMgrpReport(CTestControlBase *pTestControl, CTestProject *pTestProject, CWnd *pMsgWnd)
{
	if (pTestControl->GetCount() == 0)
	{//û���ӱ��棬�����ı��浼����Ŀ���ַ
		m_pExportMsgRcvWnd->PostMessage(m_nExportMsg, (WPARAM)pTestProject, WORD_EXPORT_STATE_CMBN_FINISH);
		return;
	}

	//���ӱ��棬���ܵı��浼����Ŀ���ַ
	m_pExportMsgRcvWnd->PostMessage(m_nExportMsg, (WPARAM)pTestProject, WORD_EXPORT_STATE_CMBN_BEGIN);
	CString strWordRptFile;
	CWordRptFillBase* pReportFill = (CWordRptFillBase*)pTestControl->m_pReportFill;
	pTestControl->m_pReportFill = NULL;

	if (!pTestControl->OpenWordReportFileOnly(strWordRptFile))
	{
		pTestControl->m_pReportFill = pReportFill;
		return;
	}

	if (m_pNewGuideBook != NULL)
	{
		pTestControl->m_pReportFill->SetGuideBook(m_pNewGuideBook);
	}

	CTestControlManyReport *pManyReport = (CTestControlManyReport*)pTestControl;

	if (pManyReport->m_strCmbdDocFile.Find(_T(":")) < 0)
	{//�����ȫ·������ʹ��ȫ·��
		strWordRptFile = m_strCmbnDestPath + GetFileNameFromFilePath(pManyReport->m_strCmbdDocFile);
	}
	else
	{
		strWordRptFile = pManyReport->m_strCmbdDocFile;
	}

	pTestControl->m_pReportFill->SaveAs(strWordRptFile);	

	CWordRptFill *pWordReportFill = (CWordRptFill*)pTestControl->m_pReportFill;
	pWordReportFill->InitWordRptBkmkMgrpCmbn();

	POS pos = pTestControl->GetTailPosition();
	CTestControlBase *pGbrpt = NULL;
	long nMgrpIndex = pTestControl->GetCount();
	nMgrpIndex--;

	while (pos != NULL)
	{
		pGbrpt = (CTestControlBase *)pTestControl->GetPrev(pos);
		CmbnMgrpReport(pTestControl, pGbrpt, nMgrpIndex);
		nMgrpIndex--;
	}

	pTestControl->m_pReportFill->SaveAs(strWordRptFile);
	pTestControl->CloseReportFill();
	pTestControl->m_pReportFill = pReportFill;
	m_pExportMsgRcvWnd->PostMessage(m_nExportMsg, (WPARAM)pTestProject, WORD_EXPORT_STATE_CMBN_FINISH);
}

void CWordRptExportBase::CmbnMgrpReport(CTestControlBase *pTestControl, CTestControlBase *pGbrpt, long nIndex)
{
	CString strWordRptFile;
	CWordRptFillBase* pReportFill = (CWordRptFillBase*)pGbrpt->m_pReportFill;
	pGbrpt->m_pReportFill = NULL;

	if (!pGbrpt->OpenWordReportFileOnly(strWordRptFile))
	{
		pGbrpt->m_pReportFill = pReportFill;
		return;
	}

	pTestControl->m_pReportFill->CmbmMgrpt(pGbrpt->m_pReportFill, nIndex);
	pGbrpt->CloseReportFill();
	pGbrpt->m_pReportFill = pReportFill;
}

void CWordRptExportBase::ExportDetailWord_GbItem(CGbItemBase *pGbItem)
{
	UINT nClassID = pGbItem->GetClassID();

	if (nClassID == GBCLASSID_DEVICE || nClassID == GBCLASSID_JOBGUIDE || nClassID == GBCLASSID_ITEMS)
	{
		return;
	}

	CReports *pReports = pGbItem->GetReports();

	if (pReports->GetCount() == 0)
	{
		return;
	}

	CString strTitle = pGbItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
	InsertTitle(strTitle, 0);

	CReport *pReort = NULL;
	POS pos = pReports->GetHeadPosition();
	long nIndex = 1;

	if (pReports->GetCount() == 1)
	{
		pReort = (CReport *)pReports->GetNext(pos);

		ExportReport_Values(_T(""), pReort->m_pValues);
		ExportReport_Datasets(_T("��������"), pReort->m_pRptDvmDataset);
	}
	else
	{
		while (pos != NULL)
		{
			pReort = (CReport *)pReports->GetNext(pos);
			strTitle.Format(_T("��%d�β��Ա���"), nIndex);
			InsertTitle(strTitle, 0);
			ExportReport_Values(_T(""), pReort->m_pValues);
			ExportReport_Datasets(_T("��������"), pReort->m_pRptDvmDataset);
			nIndex++;
		}
	}
}

void CWordRptExportBase::ExportDetailWord_CommCmd(CCommCmd *pCommCmd)
{
	
}

void CWordRptExportBase::ExportDetailWord_MacroTest(CMacroTest *pMacroTest)
{

}

void CWordRptExportBase::ExportDetailWord_Safety(CSafety *pSafety)
{

}

void CWordRptExportBase::ExportDetailWord_SysParaEdit(CSysParaEdit *pSysparaEdit)
{

}

//////////////////////////////////////////////////////////////////////////
//
void CWordRptExportBase::ExportDetailExcel(CTestControlBase *pTestControl)
{

}
// 
// BOOL CWordRptExportBase::AddReportFileExcel(const CString &strGbFile)
// {
// 	return TRUE;
// }
// 
// void CWordRptExportBase::ExportDetailExcel_GbItem(CGbItemBase *pGbItem)
// {
// 
// }
// 
// void CWordRptExportBase::ExportReport_Values_Excel(const CString &strTitle, CValues *pValues)
// {
// 
// }
// 
// void CWordRptExportBase::ExportReport_Values_Excel(const CString &strTitle, CValues *pValues, CExBaseList *pListPara)
// {
// 
// }
// 
// void CWordRptExportBase::ExportReport_Datasets_Excel(const CString &strTitle, CDvmDataset *pDvmDataset)
// {
// 
// }
// 
// void CWordRptExportBase::InsertTitle_Excel(const CString &strTitle, long nCol, long nTitleLevel)
// {
// 
// }
