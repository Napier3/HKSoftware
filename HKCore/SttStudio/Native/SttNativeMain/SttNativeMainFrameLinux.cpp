#include "SttNativeMainFrameLinux.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../../../Module/API/StringConvertApi.h"
#include "../../Module/SttTestBase/SttMacroXmlKeys.h"
#include "../../Module/SttSocket/SttCmdOverTimeMngr.h"
#include "../../Module/SttCmd/SttCmdDefineGlobal.h"
#include "../../Module/SttTestAppConfig/SttTestAppConfigTool.h"
#include "../../Module/TestClient/SttTestClientBase.h"

#include "../../../61850/Module/XLanguageResourceIec.h"
#include "XLangResource_SttNativeMain.h"
#include <QMouseEvent>
#include<QApplication>

//#define  USE_IN_Astra_LINUX //如果在Astra系列仪器里开放这个宏
CSttTestAppConfigTool g_oSttTestAppConfigTool;
extern CSttTestClientBase *g_theSingleSttTestClient;
QSttNativeMainFrameLinux::QSttNativeMainFrameLinux(QWidget *parent) :
    QSttXMainFrameBase(parent)
{
	m_bLeftPressed = false;
	CMacroXmlKeys::Create();
	CSttCmdOverTimeTool::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CCfgDataMngrConstGlobal::Create();

	stt_CreateSingleSttTestClient();
	g_oSttTestAppConfigTool.m_strServerID = STT_SOFT_ID_TEST;
	g_oSttTestAppConfigTool.m_strSoftID = STT_SOFT_ID_DEBUG;
#ifdef USE_IN_Astra_LINUX
    m_bConnected = 1;
    m_nConnectCnt = 1;
    CreateCloseHidingBtns();//2024-2-26 zhouyangyong 在Astra系列中，增加关闭和最小化按钮
#else
#ifdef _PSX_OS_CENTOS_
    CreateCloseBtns();
#endif
	m_bConnected = 0;
	m_bConnected = g_theSingleSttTestClient->ConnectSttServer(&g_oSttTestAppConfigTool);
	m_nConnectCnt = 1;//第一次联机，如果未成功，后面3秒一次继续尝试9次
	if (m_bConnected)
	{
		g_oSttTestAppConfigTool.m_pClientEngine = g_theSingleSttTestClient->GetTestEngineClient();
		g_oSttTestAppConfigTool.m_pClientEngine->SetTestEventInterface((CTestEventBaseInterface*)this);
	}
	else
	{
		m_oTimerForConnect.start(3000);
		connect(&m_oTimerForConnect,SIGNAL(timeout()),this,SLOT(slot_SttConnect()));
	}

	m_nTesterVerIdx = -1;
	InitBatteryBtn();
	connect(this,SIGNAL(sig_UpdateBatteryState()),this,SLOT(slot_UpdateBatteryState()),Qt::QueuedConnection);
#endif
}

QSttNativeMainFrameLinux::~QSttNativeMainFrameLinux()
{
	CMacroXmlKeys::Release();
	CSttCmdOverTimeTool::Release();
	CCfgDataMngrConstGlobal::Release();
	CSttCmdDefineXmlRWKeys::Release();
	stt_RelaseSingleSttTestClient();
}

#ifdef USE_IN_Astra_LINUX
bool QSttNativeMainFrameLinux::eventFilter(QObject *obj, QEvent *event)
{
	return QObject::eventFilter(obj,event);//反回到上一级 即重复使用
}

void QSttNativeMainFrameLinux::mousePressEvent(QMouseEvent *event)
{
	//鼠标左键按下事件
	if(event->button() == Qt::LeftButton && event->pos().y() < 36)
	{
		//记录鼠标左键状态
		m_bLeftPressed = true;
		//记录鼠标在屏幕中的位置
		m_ptStart = event->globalPos();
		//        qDebug()<<QString::fromLocal8Bit("左键被按下了");
	}
}

void QSttNativeMainFrameLinux::mouseMoveEvent(QMouseEvent *event)
{
	if(m_bLeftPressed)
	{
		//将父窗体移动到父窗体原来的位置加上鼠标移动的位置:event->globalPos()-m_ptStart
		//this->window（）获取
		this->window()->move(this->window()->geometry().topLeft()+event->globalPos()-m_ptStart);
		//将鼠标在屏幕中的位置替换为新的位置
		m_ptStart = event->globalPos();
	}
}

void QSttNativeMainFrameLinux::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_bLeftPressed = false;
	}
}
#endif

void QSttNativeMainFrameLinux::InitBatteryBtn()
{
	if (m_pMainConfig->m_nShowBatteryBtn != 1)
	{
		return;
	}
	m_nBatCapValue = 0;
	m_nPowerAC = 0;
	m_oBatteryBtn.setToolButtonStyle(Qt::ToolButtonIconOnly);
	m_oBatteryBtn.setStyleSheet("QToolButton {border: none;}");
	int nWidth = 38;
	int nHeight = 40;
    m_oBatteryBtn.setParent(this);

	m_oBatteryBtn.setFixedSize(nWidth*g_dUIShowCoef,nHeight*g_dUIShowCoef);
	m_oBatteryBtn.setIconSize(QSize(nWidth*g_dUIShowCoef, nWidth*g_dUIShowCoef));
    m_oBatteryBtn.move(960*g_dUIShowCoef,11*g_dUIShowCoef);

	UpdateBatteryState(0);
	m_strBatCapString = "0%";
	m_oBatteryBtn.setText(m_strBatCapString);
}

void QSttNativeMainFrameLinux::UpdateBatteryState(int nState)
{
	CString strText;

	switch(nState)
	{
	case 1:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sMAINPOWER-1.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/MAINPOWER-1.png) center";
#endif
		break;
	case 2:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sMAINPOWER-2.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/MAINPOWER-2.png) center"/*,_P_GetResourcePath()*/;
#endif
		break;
	case 3:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sMAINPOWER-3.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/MAINPOWER-3.png) center";
#endif
		break;
	case 4:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sMAINPOWER-4.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/MAINPOWER-4.png) center";
#endif
		break;
	case 5:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sMAINPOWER-5.png) center",_P_GetResourcePath());//20 round;
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/MAINPOWER-5.png) center";//20 round;
#endif
		break;
	default:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sMAINPOWER-0.png) center",_P_GetResourcePath());//padding-top:5px;
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/MAINPOWER-0.png) center";//padding-top:5px;
#endif
		break;
	} 

	if (m_strCurrStyleString != strText)
	{
		m_strCurrStyleString = strText;
		m_oBatteryBtn.setStyleSheet(m_strCurrStyleString);
	}
}

long QSttNativeMainFrameLinux::OnRtData(CSttParas *pParas)
{
	CExBaseObject *pChildObj = NULL;
	POS pos = pParas->GetHeadPosition();
	CDataGroup *pRtDataGroup = NULL;
	long nPowerAC = m_nPowerAC;
	long nBatCapValue = m_nBatCapValue;

	while(pos)
	{
		pChildObj = pParas->GetNext(pos);

		if (pChildObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pRtDataGroup = (CDataGroup *)pChildObj;
		if (pRtDataGroup->m_strID == SYS_STATE_XEVENT_EVENTID_SYNCTIME)
		{
			stt_GetDataValueByID(pRtDataGroup, _T("PowerAC"), nPowerAC);
			stt_GetDataValueByID(pRtDataGroup, _T("BatCap"), nBatCapValue);
		}
	}

	if ((nPowerAC != m_nPowerAC)||(nBatCapValue != m_nBatCapValue))
	{
		m_nPowerAC = nPowerAC;
		m_nBatCapValue = nBatCapValue;
		emit sig_UpdateBatteryState();
	}

#ifdef _PSX_QT_LINUX_
// 	CExBaseObject *pFindObj = pRtDataGroup->FindByID("InputDev");   //20240621 xueyangfan 根据实时数据更新鼠标
// 
// 	if (pFindObj == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	if (pFindObj->GetClassID() != DTMCLASSID_CDATAGROUP)
// 	{
// 		return 0;
// 	}
// 
// 	CDataGroup *pCurrMouseKeyBoard = (CDataGroup*)pFindObj;
// 
// 	CDvmData *pVerIdxData = (CDvmData*)pCurrMouseKeyBoard->FindByID("VerIdx");
// 	CDvmData *pMouseData = (CDvmData*)pCurrMouseKeyBoard->FindByID("Mouse");
// 	CDvmData *pKeybData = (CDvmData*)pCurrMouseKeyBoard->FindByID("QWS_KEYBOARD");
// 
// 	if (pVerIdxData == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	long nValue = CString_To_long(pVerIdxData->m_strValue);
// 
// 	if (m_nTesterVerIdx == nValue)
// 	{
// 		return 0;
// 	}
// 
// 	m_nTesterVerIdx = nValue;
// 
// 	if (pMouseData != NULL)
// 	{
// 		nValue = CString_To_long(pMouseData->m_strValue);
// 		qputenv("Mouse", pMouseData->m_strValue.GetString());
// 
// 		if(nValue == 0)
// 		{
// 			QApplication::setOverrideCursor(Qt::BlankCursor);
// 		}
// 		else if(nValue == 1)
// 		{
// 			QApplication::setOverrideCursor(Qt::ArrowCursor);
// 		}
// 	}
// 
// 	if (pKeybData != NULL)
// 	{
// 		qputenv("QWS_KEYBOARD", pKeybData->m_strValue.GetString());
// 	}
#endif

	return 1;
}

void QSttNativeMainFrameLinux::slot_UpdateBatteryState()
{
	if (isHidden())//后台运行时,不更新
	{
		m_nPowerAC = -1;
		m_nBatCapValue = -1;
		return;
	}

	if (m_nPowerAC == 1)
	{
		UpdateBatteryState(5);
	}
	if (m_nPowerAC == 0)
	{
		if (m_nBatCapValue > 0 && m_nBatCapValue <= 20)
		{
			UpdateBatteryState(1);
		}
		else if (m_nBatCapValue > 20 && m_nBatCapValue <= 50)
		{
			UpdateBatteryState(2);
		}
		else if (m_nBatCapValue > 50 && m_nBatCapValue <= 80)
		{
			UpdateBatteryState(3);
		}
		else if (m_nBatCapValue > 80 && m_nBatCapValue <= 100)//2024-1-22 zhouyangyong 修改电量显示图标
		{
			UpdateBatteryState(4);
		}
	}
	m_strBatCapString.Format(_T("%d%"), m_nBatCapValue);
	m_oBatteryBtn.setText(m_strBatCapString);

}

long QSttNativeMainFrameLinux::OnDisConnect()
{
	m_nPowerAC = 0;
	m_nBatCapValue = 0;
	emit sig_UpdateBatteryState();
	return 0;
}

void QSttNativeMainFrameLinux::slot_SttConnect()
{
	m_nConnectCnt ++;
	if (m_nConnectCnt == 10)
	{
		m_oTimerForConnect.stop();//10次都未联机上，关闭该计时器
		QMessageBox::warning(NULL,/* "警告"*/g_sLangTxt_warning.GetString(),/* "联机失败"*/g_sLangTxt_LinkFail.GetString(), QMessageBox::Ok);
		return;
	}
	m_bConnected = g_theSingleSttTestClient->ConnectSttServer(&g_oSttTestAppConfigTool);
	if (m_bConnected)
	{
		g_oSttTestAppConfigTool.m_pClientEngine = g_theSingleSttTestClient->GetTestEngineClient();
		g_oSttTestAppConfigTool.m_pClientEngine->SetTestEventInterface((CTestEventBaseInterface*)this);
		m_oTimerForConnect.stop();//联机成功，关闭该计时器
	}
}
