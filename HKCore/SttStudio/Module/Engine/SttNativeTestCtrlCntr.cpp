#include "stdafx.h"
#include "SttNativeTestCtrlCntr.h"
#include "../../Module/DataMngr/DataMngrTrans.h"
#include "SttNativeTestEngine.h"

#include "../../../AutoTest/Module/TestControl/SmartTestBaseApp.h"
#include "../../../AutoTest/Module/TestControl/TestControlWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttNativeTestCltlCntr::CSttNativeTestCltlCntr()
{
    m_pGuideBook->InitAfterRead();
}

CSttNativeTestCltlCntr::~CSttNativeTestCltlCntr()
{

}


//����ͨѶ��Լ�������
void CSttNativeTestCltlCntr::CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef)
{
    CString strDeviceID ;

    if (pDevieceRef->m_strID.GetLength() > 0)
    {
        strDeviceID = pDevieceRef->m_strID;
    }
    else
    {
        strDeviceID = GetPathFileNameFromFilePathName(m_pGuideBook->m_strDeviceModelFile);
    }

    pDevieceRef->m_oPpDevice = pEngine->CreateDevice(pDevieceRef->m_strPpTemplateFile, pDevieceRef->m_strDeviceModelFile, strDeviceID);

    if (pDevieceRef->m_oPpDevice != NULL )
    {
        CPpsttDevice *pPpsttDevice = (CPpsttDevice*)pDevieceRef->m_oPpDevice;
        pPpsttDevice->m_pPxiDevice->InitCmmConfig(&m_oCmmConfig, FALSE);
    }

    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CreatePpEngineDevice:%s"), pDevieceRef->m_strID.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("      TemplateFile:%s"), pDevieceRef->m_strPpTemplateFile.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("      DvmFile:%s"), pDevieceRef->m_strDeviceModelFile.GetString());

    //����¼���ļ�·��
    SetPpEngineRecordFilePath(pDevieceRef->m_oPpDevice);
}

BOOL CSttNativeTestCltlCntr::CreatePpEngineDevice(CCommCmd *pCmd)
{
    if (m_oDeviceRefs.IsAllDeviceConnectSucc())
    {
        return TRUE;
    }

    //����Ƕ����棬�ڴ��޸�  ���-20140918
    CProtocolEngineInterface *pEngine = g_theSmartTestBaseApp->GetPpEngine(m_pGuideBook->m_strPpEngineProgID);
    CPpDeviceRef *pPpDeviceRef = NULL;

    if (pEngine == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoPrtcCpnt/*L"û��ע���Լ�������"*/);
        return FALSE;
    }

    //@@�����豸��ID��IP��ַ��������ͨѶ�豸����
    //strDeviceID : �豸����ģ�͵�ID��IP��ַ��
    pPpDeviceRef = m_oDeviceRefs.GetPpDeviceRefToConnect();
    ASSERT (pPpDeviceRef != NULL);

    pEngine = g_theSmartTestBaseApp->GetPpEngine(pPpDeviceRef->m_strPpEngineProgID);

    if (pEngine == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_NoPrtcCpnt/*L"û��ע���Լ�������"*/);
        return FALSE;
    }

    try
    {
        if (pPpDeviceRef->m_oPpDevice == NULL)
        {
            //���  20140918
            CreatePpEngineDevice(pEngine, pPpDeviceRef);
        }
    }
    catch (...)
    {
        return FALSE;
    }

    //if (m_oPpDevice == NULL)
    if (pPpDeviceRef->m_oPpDevice == NULL)
    {
        g_theSmartTestBaseApp->ReleasePpEngine(pPpDeviceRef->m_strPpEngineProgID);//(m_pGuideBook->m_strPpEngineProgID);
        CLogPrint::LogString(XLOGLEVEL_ERROR, CXLanguageResourceAtsBase::g_sLangTxt_CreatPrtcFail/*L"������ԼͨѶ�豸ʧ��"*/);
    }
    else
    {
        try
        {
            ULONG hWnd = (ULONG)m_pTCtrlWnd->GetSafeHwnd();
            pPpDeviceRef->m_oPpDevice->AttachSystemWndMsg(hWnd, WM_ENGINE_SYSTEM_MSG);

            if (pCmd->IsUseConnect())
            {
                DeviceCmmConfig(pPpDeviceRef);
            }
            //Sleep (5000);
        }
        catch(...)
        {
            if (pPpDeviceRef != NULL)
            {
                if (pPpDeviceRef->m_oPpDevice != NULL)
                {
                    pPpDeviceRef->m_oPpDevice = NULL;
                    pPpDeviceRef->SetConnectState(FALSE);
                }
            }
            return FALSE;
        }
    }

	return TRUE;
}

long CSttNativeTestCltlCntr::TestItemSafety(CSafety* pItem)
{
    if (g_nSttLogServerDebugInfor)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, ">> TestItemSafety");
    }

    AddReport(pItem, -1, -1);

	//ִ�г�ʼ���ű�
	CString strSyntax;
	pItem->RunInitScriptScript(strSyntax);

    if (pItem->IsSafetyDataModeScript())
    {
        m_pTCtrlWnd->m_pTestItemRef = pItem;
        m_pTCtrlWnd->SetTestTimer(TIMER_EXEC_SAFETY_ITEM, 200);
        return 0;
    }

    CDataGroup oDataGroup;
    Append_Datas(&oDataGroup, pItem->GetDatas(), FALSE);
    CExBaseList *pMsgs = pItem->GetMsgs();

    if (g_nSttLogServerDebugInfor)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, ">> Ats_InputData");
    }

    g_theNativeTestEngine->Ats_InputData(NULL, &oDataGroup, pMsgs);

	return 0;
}

long CSttNativeTestCltlCntr::TestItemSysParaEdit(CSysParaEdit* pItem)
{
	AddReport(pItem, -1, -1); //2017.05.17

    //ִ�г�ʼ���ű�
    CString strSyntax;
    pItem->RunInitScriptScript(strSyntax);

    long nMode = 0;
    pItem->InitDataList(nMode);

    CDataGroup oDataGroup;
    Gb_Append_Datas(&oDataGroup,pItem->GetSysParaEditDataObjList() );
    g_theNativeTestEngine->Ats_InputData(NULL, &oDataGroup, NULL);

}
