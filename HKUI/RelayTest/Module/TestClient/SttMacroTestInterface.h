#pragma once
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttAtsCmd.h"

#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"

extern long g_nLogDebugInfor;

class CTestEventBaseInterface
{
    //2022-8-20  lijunqing
public:
    virtual long Event_OnItemStateChanged(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestFinished(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestStarted(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestStoped(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestFinished(CSttParas *pSttParas, BOOL& bState)////2024.1.8 yzj 判断test-cmd是错误的，需要判断ats-cmd，新增BOOL&改变ats下的状态
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
        (void)bState;
#endif
        return 0;
    }
    virtual long Event_OnTestStarted(CSttParas *pSttParas, BOOL& bState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
        (void)bState;
#endif
        return 0;
    }
    virtual long Event_OnTestStoped(CSttParas *pSttParas, BOOL& bState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
        (void)bState;
#endif
        return 0;
    }
    virtual long Event_OnExportRptFinished(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestAppEvent(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestCreated(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnOpenGbrptFileFailed(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnEngineEvent(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnSearchPointReport(CSttParas *pSttParas)//zhouhj 20210925新增用于返回测试点报告
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnSearchPointFinish(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnExportRpt(CSttParas *pSttParas)  //shaolei 20220718  导出报告事件
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    virtual long Event_OnTestProcess(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
    //重测结束   测试不合格项结束  shaolei 2022-11-15
    virtual long Event_OnReTestFinished(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }

    //zhouhj 2024.1.23 增加用于报文监视
    virtual long Event_OnPkgSpy(CSttParas *pSttParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pSttParas;
#endif
        return 0;
    }
public:
    virtual long Event_OnItemStateChanged(CSttSysState &oSysState)		{	return Event_OnItemStateChanged(oSysState.GetSttParas());	}
    virtual long Event_OnTestFinished(CSttSysState &oSysState)				{	return Event_OnTestFinished(oSysState.GetSttParas());	}
    virtual long Event_OnTestStarted(CSttSysState &oSysState)				{	return Event_OnTestStarted(oSysState.GetSttParas());	}
    virtual long Event_OnTestStoped(CSttSysState &oSysState)				{	return Event_OnTestStoped(oSysState.GetSttParas());	}
    virtual long Event_OnTestFinished(CSttSysState &oSysState, BOOL& bState){	return Event_OnTestFinished(oSysState.GetSttParas(), bState);	}
    virtual long Event_OnTestStarted(CSttSysState &oSysState, BOOL& bState){	return Event_OnTestStarted(oSysState.GetSttParas(), bState);	}
    virtual long Event_OnTestStoped(CSttSysState &oSysState, BOOL& bState){	return Event_OnTestStoped(oSysState.GetSttParas(), bState);	}
    virtual long Event_OnExportRptFinished(CSttSysState &oSysState)		{	return Event_OnExportRptFinished(oSysState.GetSttParas());	}
    virtual long Event_OnTestAppEvent(CSttSysState &oSysState)			{	return Event_OnTestAppEvent(oSysState.GetSttParas());	}
    virtual long Event_OnTestCreated(CSttSysState &oSysState)				{	return Event_OnTestCreated(oSysState.GetSttParas());	}
    virtual long Event_OnOpenGbrptFileFailed(CSttSysState &oSysState)	{	return Event_OnOpenGbrptFileFailed(oSysState.GetSttParas());	}
    virtual long Event_OnEngineEvent(CSttSysState &oSysState)				{	return Event_OnEngineEvent(oSysState.GetSttParas());	}
    virtual long Event_OnEngineReport(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long Event_OnSearchPointReport(CSttSysState &oSysState)		{	return Event_OnSearchPointReport(oSysState.GetSttParas());	}//zhouhj 20210925新增用于返回测试点报告
    virtual long Event_OnSearchPointFinish(CSttSysState &oSysState)		{	return Event_OnSearchPointFinish(oSysState.GetSttParas());	}
    virtual long Event_OnExportRpt(CSttSysState &oSysState)					{	return Event_OnExportRpt(oSysState.GetSttParas());	}  //shaolei 20220718  导出报告事件
    virtual long Event_OnTestProcess(CSttSysState &oSysState)			{	return Event_OnTestProcess(oSysState.GetSttParas());	}
    //重测结束   测试不合格项结束  shaolei 2022-11-15
    virtual long Event_OnReTestFinished(CSttSysState &oSysState)			{	return Event_OnReTestFinished(oSysState.GetSttParas());	}

    virtual long Event_OnPkgSpy(CSttSysState &oSysState)			{	return Event_OnPkgSpy(oSysState.GetSttParas());	}
    //定义挪到基类中，由于脱机软件中，底层自动测试需要将事件转发给脱机软件，故挪到此处  shaolei 2022-1-11
    virtual long Event_OnTestState(CSttSysState &oSysState)
    {
        CSttParas *pParas = oSysState.GetSttParas();
        POS pos = pParas->GetHeadPosition();
        CExBaseObject *pCurObj = NULL;

        while(pos)
        {
            pCurObj = pParas->GetNext(pos);

            //shaolei yangyijun zhoulei 20210806
            //为方便上位机区分具体是何种事件，将事件的Group的ID，统一为:"Event***";
            //"Evnet"作为固定前缀，例如：EventSwithChanged
            if (pCurObj->m_strID.Find(_T("Event")) >= 0)
            {
                OnTestState(_T(""),(CDataGroup*)pCurObj);
            }
        }

        return 1;
    }

    //zhouhj 2023.11.17 增加此接口,方便单机软件派生后使用底层上送的打印信息
    virtual long Process_SysState_Log(CSttSysState &oSysState)
    {
        CSttMsgs *pMsgs = oSysState.GetSttMsgs();
        POS pos = pMsgs->GetHeadPosition();
        CSttMsg *pData = NULL;
        CString strLog;

        while (pos != NULL)
        {
            pData = (CSttMsg *)pMsgs->GetNext(pos);
            strLog = _T("*********************");
            strLog += pData->m_strMsg;
            if (g_nLogDebugInfor == 1) CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);//2024-8-26 wuxinyi 需要调试时，打印消息放出
        }

        return 0;
    }

    virtual long Event_OnProcessInputDataCmd(CSttAtsCmd &oAtsCmd)
    {
#ifdef _PSX_IDE_QT_
        (void)oAtsCmd;
#endif
        return 0;
    }
    virtual long Event_OnProcessComtradeRequstData(long nIndex)
    {
#ifdef _PSX_IDE_QT_
        (void)nIndex;
#endif
        return 0;
    }
    virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex)
    {
#ifdef _PSX_IDE_QT_
        (void)nIndex;
#endif
        return 0;
    }

    virtual void OnException(CDataGroup *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
    }
    virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex
                          , long nItemIndex, const CString & strItemID
                          , long nState, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)nDeviceIndex;
        (void)nReportIndex;
        (void)nItemIndex;
        (void)strItemID;
        (void)nState;
        (void)pParas;
#endif
    }
    virtual void OnReport(CDataGroup *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
    }
    virtual void OnReport(CSttSysState &oSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)oSysState;
#endif
    }
    virtual long OnUpdate(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnViewPackage(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnRtData(CSttParas *pParas)//实时数据处理
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnMeas(CDataGroup *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnAts_Stop(CDataGroup *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnRecvLiveUpdate(CSttSysState &oSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)oSysState;
#endif
        return 0;
    }
    virtual long OnRecvLicense(CSttSysState &oSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)oSysState;
#endif
        return 0;
    }
    //shaolei 2022-1-11
    virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strMacroID;
        (void)pParas;
#endif
    }

    virtual void OnRecvSttDebugData(CSttSysState &oSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)oSysState;
#endif
    }
    virtual BOOL OnRecvSttDebugData(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor
                                    , char *pszRetCmdType)
    {
#ifdef _PSX_IDE_QT_
        (void)pBuf;
        (void)nLen;
        (void)pszCmdID;
        (void)pszTestor;
        (void)pszRetCmdType;
#endif
        return 0;
    }

    //2020-10-22  lijunqing 接收设备信息数据，例如：装置信息、模块信息等，以及系统的参数设置等
    virtual void OnRecvSttDeviceData(CSttSysState &oSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)oSysState;
#endif
    }
    virtual long OnDisConnect(){    return 0;   }

    //2020-11-29 lijunqing
    virtual void OnTestMsg(BYTE *pBuf, long nLen)
    {
#ifdef _PSX_IDE_QT_
        (void)pBuf;
        (void)nLen;
#endif
    }

    //2022-01-18  lijunqing
    virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strAtsCmd;
        (void)pParas;
#endif
    }
    //2022-04-18  shaolei
    virtual void On_Ats_SaveTest(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }
    virtual void On_Ats_SaveTemplate(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }
    virtual void On_Ats_CreateTest(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }
    virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }

    //2022-06-25  shaolei
    virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }

    //shaolei 20220812  处理REPLY应答
    virtual void On_SysState_Test(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }

    //2022-9-13  lijunqing
    virtual void On_Ats_QueryItem(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }

    //lijunqing 2022-10-8  处理REPLY应答-IOT
    virtual void On_SysState_IOT(CSttSysState *pSysState)
    {
#ifdef _PSX_IDE_QT_
        (void)pSysState;
#endif
    }
};


class CMacroTestEventInterface : public CTestEventBaseInterface
{
public:
    CMacroTestEventInterface(){};
    virtual ~CMacroTestEventInterface(){};

public:
    virtual long Event_OnTestFinished(CSttSysState &oSysState)
    {
        Event_OnTestState(oSysState);//先解析测试结束Event中的开入量内容 zhouhj20210603
        CSttMacro *pMacro = oSysState.GetSttMacro();

        if (pMacro != NULL)
        {
            /*
                        SYSTEMTIME tm;
                        ::GetLocalTime(&tm);
                        CString strTmpPath = _P_GetLibraryPath();
                        strTmpPath.AppendFormat(_T("OnTestFinished%d-%d-%d %d-%d-%d.%d.xml"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);
                        oSysState.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
*/
            CSttParas *pParas = oSysState.GetSttParas();// zhouhj 20210712 改为oSysState.GetParas()，原来为pMacro下的，返回的结果应该是在oSysState下的paras
            CSttResults *pResult = pMacro->GetResults();
            OnTestFinished(pMacro->m_strID,pParas,pResult);
        }

        return 1;
    }

    virtual long Event_OnTestStarted(CSttSysState &oSysState)
    {
        //		oSysState.SaveXmlFile(_T("D:\\0001.xml"),CSttCmdDefineXmlRWKeys::g_pXmlKeys);
        CString strMacroID;
        CSttParas *pParas = oSysState.GetSttParas();
        CSttMacro *pMacro = oSysState.GetSttMacro();

        if (pMacro != NULL)
        {
            strMacroID = pMacro->m_strID;
        }

        OnTestStarted(strMacroID, pParas);
        return 1;
    }

    virtual long Event_OnTestStoped(CSttSysState &oSysState)
    {
        CString strMacroID;
        CSttParas *pParas = oSysState.GetSttParas();
        CSttMacro *pMacro = oSysState.GetSttMacro();

        if (pMacro != NULL)
        {
            strMacroID = pMacro->m_strID;
        }

        OnTestStoped(strMacroID, pParas);
        return 1;
    }

    virtual long Event_OnTestFinished(CSttSysState &oSysState, BOOL& bState)
    {
#ifdef _PSX_IDE_QT_
        (void)bState;
#endif
        return Event_OnTestFinished(oSysState);
    }

    virtual long Event_OnTestStarted(CSttSysState &oSysState, BOOL& bState)
    {
#ifdef _PSX_IDE_QT_
        (void)bState;
#endif
        return Event_OnTestStarted(oSysState);
    }

    virtual long Event_OnTestStoped(CSttSysState &oSysState, BOOL& bState)
    {
#ifdef _PSX_IDE_QT_
        (void)bState;
#endif
        return Event_OnTestStoped(oSysState);
    }

    virtual long Event_OnSearchPointFinish(CSttSysState &oSysState)//zhouhj 20210925 新增用于返回测试点报告
    {
        CSttMacro *pMacro = oSysState.GetSttMacro();

        if (pMacro != NULL)
        {
            CSttParas *pParas = pMacro->GetParas();
            CSttResults *pResult = pMacro->GetResults();
            OnSearchPointFinish(pMacro->m_strID,pParas,pResult);
        }
        return 1;
    }

    virtual long Event_OnSearchPointReport(CSttSysState &oSysState)
    {
        CSttMacro *pMacro = oSysState.GetSttMacro();

        if (pMacro != NULL)
        {
            CSttSearchResults *pSearchResults = pMacro->GetSearchResults();
            OnSearchPointReport(pMacro->m_strID,pSearchResults);
        }

        Event_OnTestState(oSysState);
        return 1;
    }

    virtual long Process_SysState_Log(CSttSysState &oSysState)
    {
        return CTestEventBaseInterface::Process_SysState_Log(oSysState);
    }

    //挪到基类中  shaolei 2022-1-11
    //virtual long Event_OnTestState(CSttSysState &oSysState)


public:
    virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas) = 0;
    virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas) = 0;
    virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults) = 0;
    virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults) = 0;
    virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults) = 0;
    //挪到基类中  shaolei  2022-1-11
    //virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas) = 0;
};

class CTestEventInterface : public CTestEventBaseInterface
{
public:
    virtual BOOL IsAtsRetCmd(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return FALSE;
    }

    virtual long Event_OnTestFinished(CSttSysState &oSysState)
    {
        CString strTestID = _T("");
        long nDeviceIndex = 0,nReportIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

        return OnTestFinished(strTestID,nDeviceIndex,nReportIndex,pParas);
    }

    virtual long Event_OnTestFinished(CSttSysState &oSysState, BOOL& bState)
    {
        CString strTestID = _T("");
        long nDeviceIndex = 0,nReportIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

        if(IsAtsRetCmd(pParas))
        {
            bState = FALSE;
        }

        return OnTestFinished(strTestID,nDeviceIndex,nReportIndex,pParas);
    }

    virtual long Event_OnItemStateChanged(CSttSysState &oSysState)
    {
        CString strTestID = _T(""),strItemID = _T(""), strState = _T(""), strSelect = _T("");
        long nDeviceIndex = 0,nReportIndex = 0,nItemIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemIndex,nItemIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemID,strItemID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_State,strState);
        long nState = GB_GetTestStateByIDEx(strState);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_State,strSelect);

        return OnItemStateChanged(strTestID,nDeviceIndex,nReportIndex,nItemIndex,strItemID,nState,pParas);
    }

    virtual long Event_OnTestStarted(CSttSysState &oSysState)
    {
        CString strTestID = _T("");
        long nDeviceIndex = 0,nReportIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

        return OnTestStarted(strTestID,nDeviceIndex,nReportIndex,pParas);
    }

    virtual long Event_OnTestStarted(CSttSysState &oSysState, BOOL& bState)
    {
        CString strTestID = _T("");
        long nDeviceIndex = 0,nReportIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

        if(IsAtsRetCmd(pParas))
        {
            bState = TRUE;
        }

        return OnTestStarted(strTestID,nDeviceIndex,nReportIndex,pParas);
    }

    virtual long Event_OnTestStoped(CSttSysState &oSysState)
    {
        CString strTestID = _T("");
        long nDeviceIndex = 0,nReportIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

        return OnTestStoped(strTestID,nDeviceIndex,nReportIndex,pParas);
    }

    virtual long Event_OnTestStoped(CSttSysState &oSysState, BOOL& bState)
    {
        CString strTestID = _T("");
        long nDeviceIndex = 0,nReportIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_ReportIndex,nReportIndex);

        if(IsAtsRetCmd(pParas))
        {
            bState = FALSE;
        }

        return OnTestStoped(strTestID,nDeviceIndex,nReportIndex,pParas);
    }

    virtual long Event_OnSearchPointReport(CSttSysState &oSysState)
    {
        CSttMacro *pMacro = oSysState.GetSttMacro();

        if (pMacro != NULL)
        {
            CSttSearchResults *pSearchResults = pMacro->GetSearchResults();
            OnSearchPointReport(pMacro->m_strID,pSearchResults);
        }

        Event_OnTestState(oSysState);
        return 1;
    }


    virtual long Event_OnTestCreated(CSttSysState &oSysState)
    {
        CString strTestID = _T("");

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);

        return OnTestCreated(strTestID,pParas);
    }

    virtual long Event_OnEngineEvent(CSttSysState &oSysState)
    {
        CString strTestID = _T(""),strEvent = _T("");
        long nDeviceIndex = 0;

        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.GetParasDataValueByID(STT_CMD_PARA_Test_ID,strTestID);
        oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceIndex,nDeviceIndex);
        oSysState.GetParasDataValueByID(_T("EventID"),strEvent);

        return OnEngineEvent(strTestID,nDeviceIndex,strEvent,pParas);
    }

    virtual long Event_OnProcessInputDataCmd(CSttAtsCmd &oAtsCmd)
    {
        return OnProcessInputDataCmd(oAtsCmd.GetSttParas(),oAtsCmd.GetSttMsgs());
    }

    virtual long Event_OnTestProcess(CSttSysState &oSysState)
    {
        return OnTestProcess(oSysState.GetSttParas());
    }

    virtual long Event_OnExportRpt(CSttSysState &oSysState)
    {
        CSttParas *pParas = oSysState.GetSttParas();
        return OnExportRptEvent(pParas);
    }

    virtual long Event_OnReTestFinished(CSttSysState &oSysState)
    {
        CSttParas *pParas = oSysState.GetSttParas();
        return OnReTestFinished(pParas);
    }

public:
    virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)nDeviceIndex;
        (void)nReportIndex;
        (void)nItemIndex;
        (void)strItemID;
        (void)nState;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)nDeviceIndex;
        (void)nReportIndex;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)nDeviceIndex;
        (void)nReportIndex;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)nDeviceIndex;
        (void)nReportIndex;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)strTestID;
        (void)nDeviceIndex;
        (void)strEvent;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs)
    {
#ifdef _PSX_IDE_QT_
        (void)pMsgs;
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnTestProcess(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnExportRptEvent(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnReTestFinished(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }

    virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
    {
#ifdef _PSX_IDE_QT_
        (void)strMacroID;
        (void)pSearchResults;
#endif
    }


};

//2022-1-14  lijunqing  为了使用的方便，增加自动测试的接口。CTestEventInterface以后可以考虑从下面的接口派生，双基类
class CAtsEventInterface
{
public:
    //2022-6-9  lijunqing批注：OnUpdateGpsTime函数设计有严重的问题，此部分真是的含义是时间同步SyncTime
    //参数不能用这么多的参数变量，参考On_IecDetect，应该用DataGroup参数进行数据传递
    //Error?????????????????
    virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime)
    {
#ifdef _PSX_IDE_QT_
        (void)pRtSyncTime;
#endif
        return 0;
    }//
    virtual long OnUpdateException(){return 0;}//20220914 zhouhj 更新异常信息
    //GpsTime(long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
    //	long nPowerAC, long nBatCap,long nUSB){	return 0;	}//更新GPS时间、电池电量以及USB状态，没想好函数叫啥，沿用以前名称 sf 20220228

    virtual long OnConnectStateChanged(bool bState)
    {
#ifdef _PSX_IDE_QT_
        (void)bState;
#endif
        return 0;
    } //sf 20220225 连接状态改变
    virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas) = 0;
    virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
    virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
    virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas) = 0;
    virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas) = 0;
    virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas) = 0;
    virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs) = 0;
    virtual long OnTestProcess(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual long OnExportRptEvent(CSttParas *pParas) = 0;
    virtual long OnReTestFinished(CSttParas *pParas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParas;
#endif
        return 0;
    }
    virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
    {
#ifdef _PSX_IDE_QT_
        (void)strMacroID;
        (void)pSearchResults;
#endif
    }


    virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas) = 0;
    virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup)
    {
#ifdef _PSX_IDE_QT_
        (void)pDeviceGroup;
#endif
    }

    //2022-01-18  lijunqing
    virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas) = 0;
    //2022-04-18  shaolei
    virtual void On_Ats_SaveTest(CSttSysState *pSysState) = 0;
    virtual void On_Ats_SaveTemplate(CSttSysState *pSysState) = 0;
    virtual void On_Ats_CreateTest(CSttSysState *pSysState) = 0;
    virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState) = 0;

    //2022-06-25  shaolei
    virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState) = 0;

    //2022-4-13  lijunqing
    virtual void On_IecDetect(CDataGroup *pIecCb) = 0;

    //2022-9-13  lijunqing
    virtual void On_Ats_QueryItem(CSttSysState *pSysState) = 0;

    //2022-10-6  lijunqing
    virtual long On_RtData(CDataGroup *pRtData)
    {
#ifdef _PSX_IDE_QT_
        (void)pRtData;
#endif
        return 0;
    }

};
