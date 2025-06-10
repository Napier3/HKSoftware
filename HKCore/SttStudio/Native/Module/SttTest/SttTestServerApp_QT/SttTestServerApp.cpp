#include "stdafx.h"
#include "SttTestServerApp.h"

#ifndef _PSX_IDE_QT_
#include "../../../Module/SttSocket/TestServer/VC/SttTestServerSocket.h"
#else
#include "../../Module/SttSocket/TestServer/QT/SttTestServerSocket.h"
#include "../../Module/SttDevice/SttDeviceBase.h"
#include "../../Module/SttTest/Common/tmt_adjust_sys_parameter.h"
#endif

#include "../../Module/Engine/SttTestServerBase.h"
#include "../../Module/Engine/SttServerTestCtrlCntr.h"
#include "../../Module/Engine/QT/SttTestServerEngine.h"
#include "../../Module/SttSocket/SttServerSocketDataBase.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include"SttTestServerApp.h"
#include "../../Module/LiveUpdate/SttNativeConfig/SttNativeCfgMngrGlobal.h"
#include "../../Module/LiveUpdate/SttNativeConfig/SttNativeCfgMngr.h"
#include "../../API/NetworkInterface.h"

//#include "../../Module/SttTest/Common/Adjust/tmt_adjust_test.h"
//#include "../../Module/SttTest/Common/tmt_manu_test.h"
//#include "../../Module/SttTest/Common/tmt_harm_test.h"
//#include "../../Module/SttTest/Common/tmt_state_test.h"
//#include "../../Module/SttTest/PTU200L/tmt_pt_test.h"
//#include "../../Module/SttTest/Common/tmt_soe_test.h"
//#include "../../Module/SttTest/Common/SttSystemConfig.h"
//#include "../../Module/SttTest/Common/Meas/meas_define.h"
//#include "../../Module/SttTest/PID01/tmt_pid01_test.h"
//#include "../../Module/SttTest/PiLight/tmt_light_anglectrl.h"
//#include "../../Module/SttTest/PiLight/tmt_light_test.h"
//#include "../../Module/SttTest/Common/Adjust/tmt_adjust_test.h"

#include <QTextCodec>

//2022-4-7  lijunqing ��ͬ�Ĳ�Ʒ��ʹ�õķ�ʽ�ǲ�ͬ�ģ����磺AT02Dʹ�÷����ڴ淽ʽ
//330ʹ�ù����ڴ淽ʽ�����Ի������ڸ����̵�Main�д������Ա�֤ͨ����
CRingMemBuf *g_pSttRcdSndRingBuf = NULL;//20220331 zhoulei

CSttTestServerApp::CSttTestServerApp(int &argc, char **argv):QCoreApplication(argc, argv)
{
    CLogPrint::Create(this);
}

CSttTestServerApp::~CSttTestServerApp()
{
    CLogPrint::SetLog(NULL);
    CLogPrint::Release();
}

void CSttTestServerApp::LogString(long nLevel, const CString &strMsg)
{
    //�����жϺ����е��� currentTime���ܻ��쳣 FUTEX_WAIT_PRIVATE
    //	QTime tm = QTime::currentTime();
    //	CString str;
    //	str.Format(("%d:%d:%d.%d:"),
    //			   tm.hour(),tm.minute(), tm.second(),
    //			   tm.msec());
#ifdef _PSX_QT_LINUX_
    qDebug()<<strMsg;
#endif

    if (nLevel != XLOGLEVEL_DEBUG)
    {
        return;
    }

    CSttTestServerBase *pSttTestServer = CSttTestServerBase::GetServerEngine();

    if (pSttTestServer != NULL)
    {
        pSttTestServer->LogDebugInfor(strMsg);
    }
}

void CSttTestServerApp::LogString(long nLevel, const char *strMsg)
{
    LogString(nLevel, CString(strMsg));
}

void CSttTestServerApp::InitSttTestServerBaseApp()
{
    CSttTestServerBaseApp::InitSttTestServerBaseApp();

    QTextCodec *codec = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    CString strPath = qApp->applicationDirPath();
    long nIndex =  strPath.ReverseFind('/');
    strPath = strPath.left(nIndex);
    _P_SetSystemPath(strPath.GetString());

	strPath = _P_GetSystemPath();
	nIndex= strPath.lastIndexOf('/',-2);
	strPath = strPath.left(nIndex);
	strPath += "/Common/Language/LanguageConfig.xml";
	QFile fileConf(strPath);
	if(fileConf.open(QIODevice::Text | QIODevice::ReadOnly))
	{
		char pszBuf[100];
		fileConf.read(pszBuf, 100);
		pszBuf[99] = '\0';
		CString strData(pszBuf);
		int nPos = strData.indexOf("curr-language");
		strData = strData.right(nPos);
		nPos = strData.indexOf(">");
		strData = strData.left(nPos);
		if(!strData.contains("Chinese"))
		{
			g_nLogPrintIsZN = 0;
		}
		fileConf.close();
	}
    g_strFtpRootFile=_P_GetSystemPath();
    BOOL bRet = stt_open_adjust_file("DeviceSystemParas.xml");
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("stt_open_adjust_file result=%d"),bRet);

    g_nCheckAuthority = g_theDeviceSystemParameter->m_oDeviceAttrs.m_nCheckAuthority;//��ϵ���ļ�ָ��Ȩ���ж��Ƿ�����

    if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount > MAX_BINARYIN_COUNT)
    {
        g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount = MAX_BINARYIN_COUNT;
    }
    else if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount < 0)
    {
        g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount = 0;
    }
    g_nBinCount = g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinCount;

    if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBoutCount > MAX_BINARYOUT_COUNT)
    {
        g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBoutCount = MAX_BINARYOUT_COUNT;
    }
    else if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBoutCount < 0)
    {
        g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBoutCount = 0;
    }
    g_nBoutCount = g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBoutCount;

    g_MeasDevice =new MEAS_DEVICE;
    g_MeasDevice->init();
    g_theSystemConfig=new CSttDevSystemParas;
    g_theSystemConfig->init();

    CSttCmdOverTimeTool::Create();
#ifdef _PSX_QT_LINUX_
	int fd=CSttDeviceBase::g_pSttDeviceBase->InitDevice(bRet);
#endif

    CCfgDataMngrXmlRWKeys::Create();
    CCfgDataMngrConstGlobal::Create();
    CSttNativeCfgXmlRWKeys::Create();

#ifdef _PSX_QT_LINUX_
    CString strCmd;
    strCmd.Format(_T("rm -rf %sFPGA"),g_strFtpRootFile.GetString());
    system(strCmd.toUtf8());
    system("sync");
    strCmd.Format(_T("mkdir %sFPGA"),g_strFtpRootFile.GetString());
    system(strCmd.toUtf8());
    system("sync");

    //���SttNativeCfg.xml
    CSttNativeCfgMngr oNativeCfg;
    if(oNativeCfg.Open())
    {
        CSttNativeCfgLiveUpdate* pNativeLiveUpdate = oNativeCfg.GetCfgLiveUpdate();
        CSttNativeCfgHisVer* pNativeHisVer = pNativeLiveUpdate->GetCfgHisVer();

        if(pNativeHisVer->m_nUpdateDeviceXml==1)
        {
            g_bWriteHdInfor=TRUE;
            stt_xml_serialize_register_adjust();
            pNativeHisVer->m_nUpdateDeviceXml=0;
            oNativeCfg.Save();
            system("sync");
        }
    }

    Drv_SysUtc oSysUtc;
    memset(&oSysUtc, 0, sizeof(Drv_SysUtc));

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
    read(fd, (char *)&oSysUtc, 0x205);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    g_dwSttAdjSysParaCurrVersion = oSysUtc.tm_l;//��ϵͳ����ʱ�����벿�����汾��ʶ
#endif

    CString strIP, strMask;
    stt_net_get_deviceip(strIP, strMask);
    QByteArray ba = strIP.toLatin1();

    CSttTestServerEngine::Create(fd,ba.data(),STT_PORT_TEST_SERVER,STT_PORT_COMTRADE_SERVER);
}

void CSttTestServerApp::ExitSttTestServerBaseApp()
{
    CCfgDataMngrConstGlobal::Release();
    CCfgDataMngrXmlRWKeys::Release();
    CSttTestServerEngine::Release();
    CSttCmdOverTimeTool::Release();
    CSttNativeCfgXmlRWKeys::Release();
    delete g_theSystemConfig;
    delete g_MeasDevice;
    stt_free_adjust();
    CSttTestServerBaseApp::ExitSttTestServerBaseApp();
}

