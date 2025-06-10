#include "SttWgtCmdExecTool.h"
#include "../Ctrls/SttWgtNativeMainLinux.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/System/TickCount32.h"
#include "../../LiveUpdate/SttLiveUpdateShell.h"
#include "../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../../UI/SCL/QSttSelSclFileWidget.h"
#include <QTableWidget>
#include <QProcess>
#include <QStyleOption>
#include <QMessageBox>
#include <QDesktopServices>
#include <QString>
#include <QStringList>
#include "../SttMainArgvDef.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"


QSttWgtCmdExecTool* g_pQSttWgtCmdExecTool = NULL;
QMainWindow *g_pSttWgtCmdMainWindow = NULL;
QSharedMemory g_oTestMacroSM(STT_UPDATE_TESTMACRO_SM_ID);//2023-12-26 wuxinyi 切换测试模块共享内存

double g_dStartupDelayTime = 3.0f;//开机后等待自动测试启动需要的延时时间

QSttWgtCmdExecTool::QSttWgtCmdExecTool()
{
 	//创建共享内存
	if (!g_oTestMacroSM.attach()) 
	{
		if (!g_oTestMacroSM.create(STT_UPDATE_TESTMACRO_SM_SIZE)) 
		{
			CXMessageBox::information(NULL,_T("提示"),_T("创建共享内存段失败!"),QMessageBox::Yes);
		}
	}
	g_pQSttWgtCmdExecTool = this;
	m_nType = LINUX;
}

QSttWgtCmdExecTool::~QSttWgtCmdExecTool()
{
	// 在析构函数中分离共享内存
	if(g_oTestMacroSM.isAttached())
		g_oTestMacroSM.detach();
}

CString QSttWgtCmdExecTool::GetCmdParasString_WaitingTime()
{
	double dHasWaitingTime = m_oStartTickCount.GetTickCountLong(FALSE);
	dHasWaitingTime /= 1000;
	CString strText;
	strText = ARGV_CMD_PARA_ID_waiting_time;

	//延时最大等待时间,不超过10s；如果当前程序已经打开超过10s,则不再需要等待
	if ((dHasWaitingTime>g_dStartupDelayTime)||(dHasWaitingTime<=0))
	{
		strText += _T("=0;");
		return strText;
	}

	long nNeedWaitTime = (g_dStartupDelayTime - dHasWaitingTime)*1000;//转换为ms
	strText.AppendFormat(_T("=%ld;"),nNeedWaitTime);
	return strText;
}

void QSttWgtCmdExecTool::ExecCmd(const CString& strType, const CString& strID, const CString& strSrcData, const CString &strArgv)
{
//	if(g_pQSttWgtCmdExecTool->m_nType == LINUX)
	{
		if(strType == "cmd")
		{
			OnCmd(strID);
		}
		else if(strType == ARGV_CMD_ID_MACROTEST)
		{
			OnMacroTest(strID, strArgv);
		}
		else if (strType == ARGV_CMD_ID_OPENFILE)
		{
			OnOpenFile(strSrcData, strArgv);
		}
		else if (strType == ARGV_CMD_ID_OPENDIALOG)
		{
			OnOpenDialog(strID, strArgv);
		}
		else if (strType == ARGV_CMD_ID_OPENMACROEXE)//2023-12-11 wuxinyi 传入测试项Id
		{
			OnMacroExe(strID, strArgv);
		}
	}
// 	else
// 	{
// 		OnMacroTest(strID);
// 	}
}

void QSttWgtCmdExecTool::ExecCmd(const CString& strType, QStringList strings)
{
	g_pQSttWgtCmdExecTool->m_oThread.m_strPath = _P_GetBinPath();

	if (g_pQSttWgtCmdExecTool->m_nType == WINDOWS)
	{
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrWin.exe";
	} 
	else
	{
	}

	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd.clear();
	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strType << strings;
	g_pQSttWgtCmdExecTool->m_oThread.start();
}

void QSttWgtCmdExecTool::OnOpenFile( const CString& strDataSrc , const CString &strArgv)
{
	if(strDataSrc.GetLength() <= 1)
	{
		return;
	}

	QTableWidget* pWgt = m_gQSttWgtNativeMainLinux->findChild<QTableWidget*>(strDataSrc);
	QTableWidgetItem* pItem = pWgt->itemAt(pWgt->currentRow(), 0);

	if (pItem == NULL)
	{
		//QMessageBox 
		return;
	}

	CString strFileName = pItem->text();

}

//2022-10-5  lijunqing
//macrotest macro_id=XXXX;iec=1/0;meas_svr=1/0;
void QSttWgtCmdExecTool::OnMacroTest( const CString& strID , const CString &strArgv)
{
// 	if (strID.IsEmpty())//20220627 zhouhj 未发布的功能模块,ID填空,不进行打开操作
// 	{
// 		QMessageBox oMessageBox;
// 		oMessageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
// 		oMessageBox.information(NULL, QObject::tr("提示"), QObject::tr("此功能模块正在测试中,待发布."));
// 		return;
// 	}

	g_pQSttWgtCmdExecTool->m_oThread.m_strPath = _P_GetBinPath();

	if (g_pQSttWgtCmdExecTool->m_nType == WINDOWS)
	{
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrWin.exe";
	} 
	else
	{
#ifndef _PSX_QT_LINUX_
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrLinux.exe";
#else
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrLinux";
#endif
	}

	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd.clear();
	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << ARGV_CMD_ID_MACROTEST;

	CString strParas,strSsclPath;
	strParas.Format(_T("%s=%s;"), ARGV_CMD_PARA_ID_MACROID, strID.GetString());
	strSsclPath = g_oXSclFileMngr.GetCurrSelSsclFilePah();
	strParas.AppendFormat(_T("%s="),ARGV_CMD_PARA_ID_sscl_path);
	strParas += strSsclPath;
	strParas += _T(";");
	strParas += g_pQSttWgtCmdExecTool->GetCmdParasString_WaitingTime();
	strParas += strArgv;
	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strParas;

	g_pQSttWgtCmdExecTool->m_oThread.start();

	CTickCount32 time;
	while(!g_pQSttWgtCmdExecTool->m_oThread.isFinished())
	{
		time.DoEvents(10);
	}

	if (g_pSttSelSclFileWidget != NULL)
	{
		g_oXSclFileMngr.OpenSclFileMngrCfg();
		g_pSttSelSclFileWidget->InitDatas();
	}
}

void QSttWgtCmdExecTool::OnMacroExe( const CString& strID , const CString &strArgv)
{
	g_pQSttWgtCmdExecTool->m_oThread.m_strPath = _P_GetBinPath();
	g_pQSttWgtCmdExecTool->m_oThread.m_strExe = strID;

	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd.clear();
	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strArgv;

	CString strParas,strSsclPath;
// 	strParas.Format(_T("%s=%s;"), ARGV_CMD_PARA_ID_MACROID, strID.GetString());
// 	strSsclPath = g_oXSclFileMngr.GetCurrSelSsclFilePah();
// 	strParas.AppendFormat(_T("%s="),ARGV_CMD_PARA_ID_sscl_path);
// 	strParas += strSsclPath;
// 	strParas += _T(";");
// 	strParas += strArgv;
//	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strParas;

	g_pQSttWgtCmdExecTool->m_oThread.start();

#ifndef _PSX_QT_LINUX_
	if (g_pSttWgtCmdMainWindow != NULL)
	{
		g_pSttWgtCmdMainWindow->showMinimized();
	}
#endif

	CTickCount32 time;
	while(!g_pQSttWgtCmdExecTool->m_oThread.isFinished())
	{
		time.DoEvents(10);
	}
	ReadSharedData();//进程结束读取数据

#ifndef _PSX_QT_LINUX_
	if (g_pSttWgtCmdMainWindow != NULL)
	{
		g_pSttWgtCmdMainWindow->showNormal();
	}
#endif

// 	if (g_pSttSelSclFileWidget != NULL)
// 	{
// 		g_oXSclFileMngr.OpenSclFileMngrCfg();
// 		g_pSttSelSclFileWidget->InitDatas();
// 	}
}

void QSttWgtCmdExecTool::OnOpenDialog( const CString& strID , const CString &strArgv)
{
	g_pQSttWgtCmdExecTool->m_oThread.m_strPath = _P_GetBinPath();

	if (g_pQSttWgtCmdExecTool->m_nType == WINDOWS)
	{
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrWin.exe";
	} 
	else
	{
#ifndef _PSX_QT_LINUX_
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrLinux.exe";
#else
		g_pQSttWgtCmdExecTool->m_oThread.m_strExe = "TestCtrlCntrLinux";
#endif
	}

	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd.clear();
	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << ARGV_CMD_ID_OPENDIALOG;

	BOOL bUpdateScl = FALSE;
		CString strParas,strSsclPath;
	strParas.Format(_T("%s=%s;"), ARGV_CMD_PARA_ID_DIALOGID, strID.GetString());

	if (strID == _T("IecCapDialog"))
	{
		strSsclPath = g_oXSclFileMngr.GetCurrSelSsclFilePah();
		strParas.AppendFormat(_T("%s="),ARGV_CMD_PARA_ID_sscl_path);
		strParas += strSsclPath;
		strParas += _T(";");	
		bUpdateScl = TRUE;
	}

	strParas += g_pQSttWgtCmdExecTool->GetCmdParasString_WaitingTime();
	strParas += strArgv;
	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strParas;

// 	strParas += strArgv;
// 	g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strParas;

	g_pQSttWgtCmdExecTool->m_oThread.start();

#ifndef _PSX_QT_LINUX_
	if (g_pSttWgtCmdMainWindow != NULL)
	{
		g_pSttWgtCmdMainWindow->showMinimized();
	}
#endif

	CTickCount32 time;
	while(!g_pQSttWgtCmdExecTool->m_oThread.isFinished())
	{
		time.DoEvents(10);
	}

#ifndef _PSX_QT_LINUX_
	if (g_pSttWgtCmdMainWindow != NULL)
	{
		g_pSttWgtCmdMainWindow->showNormal();
	}
#endif

	if ((g_pSttSelSclFileWidget != NULL)&&bUpdateScl)
	{
		g_oXSclFileMngr.OpenSclFileMngrCfg();
		g_pSttSelSclFileWidget->InitDatas();
	}
}

void QSttWgtCmdExecTool::OnCmd( const CString& strID )
{
	if (TOOL_TEST_SET == strID)
	{
		theLiveUpdate.Init();
		theLiveUpdate.LocalUpdate();
	}
	else if (TOOL_TEST_APP_UPDATE == strID)
	{
		theLiveUpdate.Init();
		theLiveUpdate.TestAppUpdate();
	}
	else if (TOOL_TEST_TESTER_UPDATE == strID)
	{
		
	}
	else if (TOOL_TEST_SUPPORT == strID)
	{
		//QDesktopServices::openUrl(QUrl("http://www.ponovo333x33.cn/service/marketin.html"));
	}
	else if (TOOL_TEST_POWERSET == strID)
	{
	}
	else if (TOOL_TEST_VERSION == strID)
	{
	}
	else
	{
		QMessageBox::information(NULL, QObject::tr("提示"), QObject::tr("此功能需获取相关权限后方可使用,可咨询测试仪生成厂家了解功能授权详情."));
	}
}

void QSttWgtCmdExecTool::ReadSharedData()
{
	 CString strTplID, strParaFilePath;
	char *TestMacroSM_addr = static_cast<char *>(g_oTestMacroSM.data());
	if (TestMacroSM_addr != NULL) 
	{
		QString strRevData = QString::fromLocal8Bit(TestMacroSM_addr, STT_UPDATE_TESTMACRO_SM_SIZE);//2024-01-03 wuxinyi 修改中文乱码

		QStringList parts = strRevData.split(";");

		if (parts.size() >= 2) 
		{
			strTplID = parts.at(0);
			strParaFilePath = parts.at(1);

			//读取完数据，清空共享内存数据
			if(g_oTestMacroSM.create(sizeof(STT_UPDATE_TESTMACRO_SM_ID)))
			{
				char *fszTestMacroData = static_cast<char *>(g_oTestMacroSM.data());
				if (fszTestMacroData != NULL)
				{
// 					qint64 nSharedMemorySize = g_oTestMacroSM.size();
					memset(fszTestMacroData, 0, g_oTestMacroSM.size());
				}
			}
			if(!(strTplID.IsEmpty()) && IsFileExist(strParaFilePath))
			{
				CString strExeID,  strType,  strArgv;
				UpdateExecCmd(strParaFilePath, strTplID);
			}
		} 

	} 
	return;


}

void QSttWgtCmdExecTool::UpdateExecCmd( const CString &strTmpFile, const CString &strTplID )
{
	CString strEXE ,strExePath;
	CString strAbnormalType;
		g_pQSttWgtCmdExecTool->m_oThread.m_listCmd.clear();

	if(strTplID == SMVABNTEST_TPL_ID)//sv异常模拟
		{
		CString strSVExe = _T("StateTest");
		strAbnormalType.Format(_T("%s=%s;"), STATE_ABNORMAL_TYPE, "1");
		g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strAbnormalType;
		strEXE =  strSVExe  + _T(".exe");//StateTest.exe
		}
	else
		{
		strEXE =  strTplID  + _T(".exe");//ReplayTest.exe
	}
	strExePath = _P_GetBinPath() + strEXE;

			if(IsFileExist(strExePath))
			{
				g_pQSttWgtCmdExecTool->m_oThread.m_strPath = _P_GetBinPath();
				g_pQSttWgtCmdExecTool->m_oThread.m_strExe = strEXE;

// 			CString strParas;
//  			strParas.Format(_T("%s=%s;"), ARGV_CMD_PARA_ID_TmpPath, strTmpFile.GetString());

				CString strParas;
			QString strQPara = QString("%1=%2;").arg(ARGV_CMD_PARA_ID_TmpPath).arg(strTmpFile);//2024-01-03 wuxinyi 解决中文路径乱码问题
			// 			strParas.Format(_T("%s=%s;"), ARGV_CMD_PARA_ID_TmpPath, strParasFile.GetString());
			strParas.Format(strQPara);

				g_pQSttWgtCmdExecTool->m_oThread.m_listCmd << strParas;

				g_pQSttWgtCmdExecTool->m_oThread.start();

#ifndef _PSX_QT_LINUX_
				if (g_pSttWgtCmdMainWindow != NULL)
				{
					g_pSttWgtCmdMainWindow->showMinimized();
				}
#endif

				CTickCount32 time;
				while(!g_pQSttWgtCmdExecTool->m_oThread.isFinished())
				{
					time.DoEvents(10);
				}
				ReadSharedData();//进程结束读取数据

#ifndef _PSX_QT_LINUX_
				if (g_pSttWgtCmdMainWindow != NULL)
				{
					g_pSttWgtCmdMainWindow->showNormal();
				}
#endif

			}
	else
	{
		CString strTip = _T("");
			strTip.Format( _T("找不到该【%s】文件路径！"), strExePath.GetString());
		CXMessageBox::information(NULL, _T("提示"), strTip);
	}

	return;
		}

