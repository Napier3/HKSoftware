#include "stdafx.h"
#include "WzdDlgSclFileRead.h"

CWzdDlgSclFileRead::CWzdDlgSclFileRead()
{

}

CWzdDlgSclFileRead::~CWzdDlgSclFileRead()
{
	g_bUseSmemEnable = FALSE;
	Free_SCL_INFO();
	g_bUseSmemEnable = TRUE;
}

BOOL CWzdDlgSclFileRead::ReadSclFile(const CString &strFile, CWnd *pOwnerWnd, CSclStation *pSclStation)
{	
	m_pSclStation=pSclStation;
	m_pSclStation->SetScdFile(strFile);
	m_strFile=strFile;
	m_pOwnerWnd = pOwnerWnd;

	//20230615 huangliang ��д������
	m_DlgProgress.SetModal();
	CWinThread *pThread = AfxBeginThread(ReadSCLNewThread, this);
	pThread->m_bAutoDelete = TRUE;
	m_DlgProgress.DoModal();

	//m_pScdFileRWDlg = new CWzdScdFileRWDlg();
	//m_pThreadProgress=(CThreadProgressInterface*)m_pScdFileRWDlg;
	//m_pScdFileRWDlg->SetWindowTitle(_T("��ȡSCD�ļ�"));
	//m_pScdFileRWDlg->SetUseModeless();
	//m_pScdFileRWDlg->DoModal();
	//CWzdDlgSclFileRead::ReadSCLThread(this);
	return TRUE;
}
UINT CWzdDlgSclFileRead::ReadSCLNewThread( LPVOID pParam )
{
	::CoInitialize(NULL);
	CWzdDlgSclFileRead *pSclFileRead = (CWzdDlgSclFileRead *)pParam;
	while(pSclFileRead->m_DlgProgress.m_hWnd == NULL)
		Sleep(100);

	pSclFileRead->m_DlgProgress.ShowStart(_T("��ȡSCD�ļ�"));
	pSclFileRead->m_bIsInReadState = TRUE;
	pSclFileRead->m_DlgProgress.SetMaxRange(3);
	pSclFileRead->m_DlgProgress.StepIt();

#ifdef SCL_USE_MMS_STRING_
	pSclFileRead->m_DlgProgress.ShowMsg(_T("�ͷ�SCL�ļ�����Ĺ����е���ʱ�ڴ�ռ䣬���Ժ�......"));
	pSclFileRead->Free_SCL_INFO();
#else
#endif

	pSclFileRead->m_DlgProgress.ShowMsg(_T("��ȡSCD�ļ�......"));
	g_bUseSmemEnable = FALSE;
	ST_RET ret = scl_parse(pSclFileRead->m_strFile.GetBuffer(), &pSclFileRead->m_SclInfo);
	g_bUseSmemEnable = TRUE;
	pSclFileRead->m_bCan_Free_SCL_INFO = TRUE;
	CString strMsg;

	if (ret == SD_SUCCESS)
	{
		pSclFileRead->m_DlgProgress.StepIt();
		pSclFileRead->m_DlgProgress.ShowMsg(_T("����IED����......"));
		pSclFileRead->ReadStationInfo();
		pSclFileRead->ReadIedInfoAndCtrls(&pSclFileRead->m_SclInfo);
		//		pSclFileRead->ReadDataTypeTemplates(&pSclFileRead->m_SclInfo);//zhow:����DataTypeTemplates �õ���
		pSclFileRead->m_DlgProgress.StepIt();	
		CSclStation *pSclStation=pSclFileRead->GetSclStation();
		long nCount = pSclStation->GetCount();
		POS pos =pSclStation->GetHeadPosition();		
		CExBaseObject *pTemp= NULL;

		if (nCount > 0)
		{
			pSclFileRead->m_DlgProgress.SetMaxRange(nCount);
			pSclFileRead->m_DlgProgress.StepIt();
			long nIndex=1;
			while (pos != NULL)
			{
				pTemp = pSclStation->GetNext(pos);
				if(pTemp == NULL)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����IED:%d����Ϊ��"), nIndex);
					continue;
				}
				if(pTemp->GetClassID() != SCLIECCLASSID_IED)
				{
					continue;
				}

				strMsg.Format(_T("����IED��%s��"), pTemp->m_strName);
				pSclFileRead->m_DlgProgress.ShowMsg(strMsg);
				pSclFileRead->ReadIedDetail((CSclIed*)pTemp);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ɽ���IED:%d����"), nIndex);

				pSclFileRead->m_DlgProgress.StepIt();
				nIndex++;
			}
		}

		if (pSclFileRead->m_pOwnerWnd != NULL)
		{
			pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);//��ʾ������ͼ
		}

		//20230612 huangliang �����ʾ��������濴��ȥ����		
		pSclFileRead->m_DlgProgress.ShowMsg(_T("����tscd�����ļ�......"));
		pSclFileRead->m_DlgProgress.SetMaxRange(2);
		pSclFileRead->m_DlgProgress.StepIt();
		pSclStation->SaveStationFile();
		pSclFileRead->m_DlgProgress.StepIt();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�޷�����SCL�ļ���%s����"), pSclFileRead->m_strFile);
	}

#ifdef SCL_USE_MMS_STRING_
#else
	pSclFileRead->m_DlgProgress.ShowMsg(_T("�ͷ�SCL�ļ�����Ĺ����е���ʱ�ڴ�ռ䣬���Ժ�......"));
	pSclFileRead->Free_SCL_INFO();
#endif

	if (pSclFileRead->m_pOwnerWnd != NULL)
	{
		pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_FINISH);
	}

	pSclFileRead->m_DlgProgress.Finish();
	::CoUninitialize();

	return 0;
}

UINT CWzdDlgSclFileRead::ReadSCLThread( LPVOID pParam )
{
	::CoInitialize(NULL);
	CWzdDlgSclFileRead *pSclFileRead = (CWzdDlgSclFileRead *)pParam;
	pSclFileRead->m_bIsInReadState = TRUE;
	pSclFileRead->m_pThreadProgress->SetMaxRange(3);

#ifdef SCL_USE_MMS_STRING_
	pSclFileRead->m_pThreadProgress->ShowMsg(_T("�ͷ�SCL�ļ�����Ĺ����е���ʱ�ڴ�ռ䣬���Ժ�......"));
	pSclFileRead->Free_SCL_INFO();
#else
#endif

	pSclFileRead->m_pThreadProgress->ShowMsg(_T("��ȡSCD�ļ�......"));
	g_bUseSmemEnable = FALSE;
	ST_RET ret = scl_parse(pSclFileRead->m_strFile.GetBuffer(), &pSclFileRead->m_SclInfo);
	g_bUseSmemEnable = TRUE;
	pSclFileRead->m_bCan_Free_SCL_INFO = TRUE;
	CString strMsg;

	if (ret == SD_SUCCESS)
	{
		pSclFileRead->m_pThreadProgress->StepIt();
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("����IED����......"));
		pSclFileRead->ReadStationInfo();
		pSclFileRead->ReadIedInfoAndCtrls(&pSclFileRead->m_SclInfo);
		//		pSclFileRead->ReadDataTypeTemplates(&pSclFileRead->m_SclInfo);//zhow:����DataTypeTemplates �õ���
		pSclFileRead->m_pThreadProgress->StepIt();	
		CSclStation *pSclStation=pSclFileRead->GetSclStation();
		long nCount = pSclStation->GetCount();
		POS pos =pSclStation->GetHeadPosition();		
		CExBaseObject *pTemp= NULL;

		if (nCount > 0)
		{
			pSclFileRead->m_pThreadProgress->SetMaxRange(nCount);
			pSclFileRead->m_pThreadProgress->ResetProcess();
			pSclFileRead->m_pThreadProgress->StepIt();
			long nIndex=1;
			while (pos != NULL)
			{
				pTemp = pSclStation->GetNext(pos);
				if(pTemp == NULL)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����IED:%d����Ϊ��"), nIndex);
					continue;
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����IED:%d, ClassID:%d "), nIndex, pTemp->GetClassID());
				if(pTemp->GetClassID() != SCLIECCLASSID_IED)
				{
					continue;
				}

				strMsg.Format(_T("%d / %d ����IED��%s��"), nIndex, nCount, pTemp->m_strName);
				pSclFileRead->m_pThreadProgress->ShowMsg(strMsg);

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ʼ����IED:%d����"), nIndex);
				pSclFileRead->ReadIedDetail((CSclIed*)pTemp);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ɽ���IED:%d����"), nIndex);

				pSclFileRead->m_pThreadProgress->StepIt();
				nIndex++;
			}
		}

		if (pSclFileRead->m_pOwnerWnd != NULL)
		{
			pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);//��ʾ������ͼ
		}

		//20230612 huangliang �����ʾ��������濴��ȥ����
		pSclFileRead->m_pThreadProgress->SetMaxRange(1);
		pSclFileRead->m_pThreadProgress->ResetProcess();
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("����tscd�����ļ�......"));
		pSclStation->SaveStationFile();
		pSclFileRead->m_pThreadProgress->StepIt();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�޷�����SCL�ļ���%s����"), pSclFileRead->m_strFile);
	}

#ifdef SCL_USE_MMS_STRING_
#else
	pSclFileRead->m_pThreadProgress->ShowMsg(_T("�ͷ�SCL�ļ�����Ĺ����е���ʱ�ڴ�ռ䣬���Ժ�......"));
	pSclFileRead->Free_SCL_INFO();
#endif

	if (pSclFileRead->m_pOwnerWnd != NULL)
	{
		pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_FINISH);
	}

	pSclFileRead->m_pScdFileRWDlg->ShowWindow(SW_HIDE);
	::CoUninitialize();

	return 0;
}