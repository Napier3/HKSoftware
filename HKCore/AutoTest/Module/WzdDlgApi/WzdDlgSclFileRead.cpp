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

	//20230615 huangliang 重写进度条
	m_DlgProgress.SetModal();
	CWinThread *pThread = AfxBeginThread(ReadSCLNewThread, this);
	pThread->m_bAutoDelete = TRUE;
	m_DlgProgress.DoModal();

	//m_pScdFileRWDlg = new CWzdScdFileRWDlg();
	//m_pThreadProgress=(CThreadProgressInterface*)m_pScdFileRWDlg;
	//m_pScdFileRWDlg->SetWindowTitle(_T("读取SCD文件"));
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

	pSclFileRead->m_DlgProgress.ShowStart(_T("读取SCD文件"));
	pSclFileRead->m_bIsInReadState = TRUE;
	pSclFileRead->m_DlgProgress.SetMaxRange(3);
	pSclFileRead->m_DlgProgress.StepIt();

#ifdef SCL_USE_MMS_STRING_
	pSclFileRead->m_DlgProgress.ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
	pSclFileRead->Free_SCL_INFO();
#else
#endif

	pSclFileRead->m_DlgProgress.ShowMsg(_T("读取SCD文件......"));
	g_bUseSmemEnable = FALSE;
	ST_RET ret = scl_parse(pSclFileRead->m_strFile.GetBuffer(), &pSclFileRead->m_SclInfo);
	g_bUseSmemEnable = TRUE;
	pSclFileRead->m_bCan_Free_SCL_INFO = TRUE;
	CString strMsg;

	if (ret == SD_SUCCESS)
	{
		pSclFileRead->m_DlgProgress.StepIt();
		pSclFileRead->m_DlgProgress.ShowMsg(_T("处理IED数据......"));
		pSclFileRead->ReadStationInfo();
		pSclFileRead->ReadIedInfoAndCtrls(&pSclFileRead->m_SclInfo);
		//		pSclFileRead->ReadDataTypeTemplates(&pSclFileRead->m_SclInfo);//zhow:解析DataTypeTemplates 用到的
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
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("解析IED:%d对象为空"), nIndex);
					continue;
				}
				if(pTemp->GetClassID() != SCLIECCLASSID_IED)
				{
					continue;
				}

				strMsg.Format(_T("处理IED【%s】"), pTemp->m_strName);
				pSclFileRead->m_DlgProgress.ShowMsg(strMsg);
				pSclFileRead->ReadIedDetail((CSclIed*)pTemp);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("完成解析IED:%d对象"), nIndex);

				pSclFileRead->m_DlgProgress.StepIt();
				nIndex++;
			}
		}

		if (pSclFileRead->m_pOwnerWnd != NULL)
		{
			pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);//显示树形视图
		}

		//20230612 huangliang 添加提示，以免界面看上去卡顿		
		pSclFileRead->m_DlgProgress.ShowMsg(_T("保存tscd数据文件......"));
		pSclFileRead->m_DlgProgress.SetMaxRange(2);
		pSclFileRead->m_DlgProgress.StepIt();
		pSclStation->SaveStationFile();
		pSclFileRead->m_DlgProgress.StepIt();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("无法解析SCL文件【%s】！"), pSclFileRead->m_strFile);
	}

#ifdef SCL_USE_MMS_STRING_
#else
	pSclFileRead->m_DlgProgress.ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
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
	pSclFileRead->m_pThreadProgress->ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
	pSclFileRead->Free_SCL_INFO();
#else
#endif

	pSclFileRead->m_pThreadProgress->ShowMsg(_T("读取SCD文件......"));
	g_bUseSmemEnable = FALSE;
	ST_RET ret = scl_parse(pSclFileRead->m_strFile.GetBuffer(), &pSclFileRead->m_SclInfo);
	g_bUseSmemEnable = TRUE;
	pSclFileRead->m_bCan_Free_SCL_INFO = TRUE;
	CString strMsg;

	if (ret == SD_SUCCESS)
	{
		pSclFileRead->m_pThreadProgress->StepIt();
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("处理IED数据......"));
		pSclFileRead->ReadStationInfo();
		pSclFileRead->ReadIedInfoAndCtrls(&pSclFileRead->m_SclInfo);
		//		pSclFileRead->ReadDataTypeTemplates(&pSclFileRead->m_SclInfo);//zhow:解析DataTypeTemplates 用到的
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
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("解析IED:%d对象为空"), nIndex);
					continue;
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("解析IED:%d, ClassID:%d "), nIndex, pTemp->GetClassID());
				if(pTemp->GetClassID() != SCLIECCLASSID_IED)
				{
					continue;
				}

				strMsg.Format(_T("%d / %d 处理IED【%s】"), nIndex, nCount, pTemp->m_strName);
				pSclFileRead->m_pThreadProgress->ShowMsg(strMsg);

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开始解析IED:%d对象"), nIndex);
				pSclFileRead->ReadIedDetail((CSclIed*)pTemp);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("完成解析IED:%d对象"), nIndex);

				pSclFileRead->m_pThreadProgress->StepIt();
				nIndex++;
			}
		}

		if (pSclFileRead->m_pOwnerWnd != NULL)
		{
			pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);//显示树形视图
		}

		//20230612 huangliang 添加提示，以免界面看上去卡顿
		pSclFileRead->m_pThreadProgress->SetMaxRange(1);
		pSclFileRead->m_pThreadProgress->ResetProcess();
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("保存tscd数据文件......"));
		pSclStation->SaveStationFile();
		pSclFileRead->m_pThreadProgress->StepIt();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("无法解析SCL文件【%s】！"), pSclFileRead->m_strFile);
	}

#ifdef SCL_USE_MMS_STRING_
#else
	pSclFileRead->m_pThreadProgress->ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
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