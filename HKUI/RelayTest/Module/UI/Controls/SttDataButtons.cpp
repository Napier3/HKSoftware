#include "SttDataButtons.h"
#include "../../SttTestSysGlobalPara.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../SttUIGlobalDef.h"

#include <QFontMetrics>
#include <QFont>

extern long SttFrame_Vert_Gap;  //框架按钮垂直方向上的间隔，系统为工具栏、状态栏绘制边框
extern long SttFrame_Line_Pix;    //绘制边框的像素点

QSttButtonIconMngr g_oSttButtonIconMngr;

/////////////////////////////////////
/// \brief QSttBatteryButton::QSttBatteryButton
///

#ifndef _PSX_QT_LINUX_
double GetUIShowCoef()
{
    double dDotPix1 = GetDeviceCaps_LOGPIXELSX();
    double dUIShowCoef = dDotPix1 / 96;

    return dUIShowCoef;
}
#endif

QSttBatteryButton::QSttBatteryButton(CExBaseObject *pCfgData,QFont font,QWidget *parent)
	: QSttToolButtonBase(pCfgData,parent)
{
	m_nBatCapValue = -1;
	m_nPowerAC = -1;
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(m_nWidth, m_nWidth));
	
	SetPic(0);
	m_strBatCapString = "0%";
	setText(m_strBatCapString);
}

void QSttBatteryButton::SetPic(int nState)
{
	CString strText;

    switch(nState)
    {
    case 1:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sPOWER-1.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/POWER-1.png) center";
#endif
        break;
    case 2:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sPOWER-2.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/POWER-2.png) center"/*,_P_GetResourcePath()*/;
#endif
        break;
    case 3:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sPOWER-3.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/POWER-3.png) center";
#endif
        break;
    case 4:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sPOWER-4.png) center",_P_GetResourcePath());
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/POWER-4.png) center";
#endif
        break;
    case 5:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sPOWER-5.png) center",_P_GetResourcePath());//20 round;
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/POWER-5.png) center";//20 round;
#endif
        break;
    default:
#ifdef _PSX_QT_WINDOWS_
		strText.Format("margin-top:9px;margin-bottom:9px; border-image: url(%sPOWER-0.png) center",_P_GetResourcePath());//padding-top:5px;
#else
		strText = "margin-top:9px;margin-bottom:9px; border-image: url(:/power/images/POWER-0.png) center";//padding-top:5px;
#endif
        break;
    } 

	if (m_strCurrStyleString != strText)
	{
		m_strCurrStyleString = strText;
		this->setStyleSheet(m_strCurrStyleString);
	}
}


void QSttBatteryButton::UpdateState(CDataGroup *pDataGroup)  //2022-6-9  lijunqing
{
	long nPowerAC = -1, nBatCap = -1;
	stt_GetDataValueByID(pDataGroup, _T("PowerAC"), nPowerAC);
	stt_GetDataValueByID(pDataGroup, _T("BatCap"), nBatCap);
	m_nPowerAC = nPowerAC;
	m_nBatCapValue = nBatCap;

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PowerAC=%ld,BatCap=%ld"),nPowerAC,nBatCap);

	if(nPowerAC == 1/*> 0*/)//zhouhj 2024.1.2 原先是大于0认为在充电,修改为等于1代表充电,等于2代表电池异常
	{
		SetPic(5);
//		setText("");
	}
	else
	{
		if (nPowerAC == 2)
		{
#ifdef NOT_USE_XLANGUAGE
            CLogPrint::LogString(XLOGLEVEL_ERROR,_T("电池电量信息获取异常."));
#else
            CLogPrint::LogString(XLOGLEVEL_ERROR,g_sLangTxt_Native_UnBatteryInfor);
#endif
		}

		if (nBatCap > 80)
		{
			SetPic(4);
		}
		else if (nBatCap > 50 && nBatCap <= 80)
		{
			SetPic(3);
		}
		else if (nBatCap > 20 && nBatCap <= 50)
		{
			SetPic(2);
		}
		else if (nBatCap > 0 && nBatCap <= 20)
		{
			SetPic(1);
		}
	}

	CString strBatCap;
	strBatCap.Format("%ld%",nBatCap);

	if (m_strBatCapString != strBatCap)
	{
		setText(strBatCap);
	}
}


////////////////////////////////////
/// \brief QSttSdCardButton::QSttSdCardButton
///
QSttSdCardButton::QSttSdCardButton(CExBaseObject *pCfgData,QFont font,QWidget *parent)
	: QSttToolButtonBase(pCfgData,parent)
{
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);

	SetPic(0);
}

void QSttSdCardButton::SetPic(int nState)
{
    switch(nState)
    {
    case 1:
        this->setIcon(g_oSttButtonIconMngr.m_IconSD_1);
        break;
    default:
        this->setIcon(g_oSttButtonIconMngr.m_IconSD_2);
        break;
    }
}
//////////////////////////////////////
/// \brief QSttLightButton::QSttLightButton
///

QSttLightButton::QSttLightButton(CExBaseObject *pCfgData,QFont font,QWidget *parent)
	: QSttToolButtonBase(pCfgData,parent)
{
#ifndef _PSX_QT_LINUX_
    //2024-7-24 wuxinyi 修改2240*1400 缩放150%状态灯显示不全
    double dUIShowCoef = GetUIShowCoef();
#endif
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 20;
	else
		m_nWidth = pButton->m_nWidth;

#ifndef _PSX_QT_LINUX_
    if(dUIShowCoef >= 1.5)
    {
        m_nWidth =40;
        font.setPointSize(6);
    }
#endif

    this->setFont(font);

	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->setStyleSheet("QToolButton {border: none;"
                        "             padding: 1px;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setText(pButton->m_strName);

	if (pCfgData->m_strID == "Run")
	{
		SetPic(STT_LIGHT_BTN_INDEX_ShutOff);
	} 
	else
	{
		SetPic(STT_LIGHT_BTN_INDEX_Red);
	}
}

void QSttLightButton::SetPic(int nState)
{
    switch(nState)
    {
	case STT_LIGHT_BTN_INDEX_ShutOff:
		this->setIcon(g_oSttButtonIconMngr.m_IconLight_ShutOff);
		break;
    case STT_LIGHT_BTN_INDEX_Run:
        this->setIcon(g_oSttButtonIconMngr.m_IconLight_Run);
        break;
	case STT_LIGHT_BTN_INDEX_Red:
		this->setIcon(g_oSttButtonIconMngr.m_IconLight_Red);
		break;
	case STT_LIGHT_BTN_INDEX_Yellow:
		this->setIcon(g_oSttButtonIconMngr.m_IconLight_Yellow);
		break;
    default:
        this->setIcon(g_oSttButtonIconMngr.m_IconLight_ShutOff);
        break;
    }
}

//////////////////////////////////////
/// \brief QSttBinButton::QSttBinButton
///
QSttBinButton::QSttBinButton(CExBaseObject *pCfgData,QFont font,QWidget *parent)
	: QSttToolButtonBase(pCfgData,parent)
{
#ifndef _PSX_QT_LINUX_
    //2024-7-24 wuxinyi 修改2240*1400 缩放150%状态灯显示不全
    double dUIShowCoef = GetUIShowCoef();
#endif

	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 20;
	else
		m_nWidth = pButton->m_nWidth;

#ifndef _PSX_QT_LINUX_
    if(dUIShowCoef >= 1.5)
    {
        m_nWidth =40;
        font.setPointSize(6);
    }
#endif

    this->setFont(font);

	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->setStyleSheet("QToolButton {border: none;"
                        "             padding: 1px;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setText(pButton->m_strName);

	SetPic(1);
}

void QSttBinButton::SetPic(int nState)
{
    switch(nState)
    {
    case 1:
        this->setIcon(g_oSttButtonIconMngr.m_IconBin_1);
        break;
	case 2:
		this->setIcon(g_oSttButtonIconMngr.m_IconBin_2);
		break;
	case 3:
		this->setIcon(g_oSttButtonIconMngr.m_IconBin_3);
		break;
    default:
        this->setIcon(g_oSttButtonIconMngr.m_IconBin_4);
        break;
    }
}

//////////////////////////////////////
/// \brief QSttBoutButton::QSttBoutButton
///
QSttBoutButton::QSttBoutButton(CExBaseObject *pCfgData,QFont font,QWidget *parent)
	: QSttToolButtonBase(pCfgData,parent)
{
#ifndef _PSX_QT_LINUX_
    double dUIShowCoef = GetUIShowCoef();
#endif

	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 20;
	else
		m_nWidth = pButton->m_nWidth;

#ifndef _PSX_QT_LINUX_
    if(dUIShowCoef >= 1.5)
    {
        m_nWidth =40;
        font.setPointSize(6);
    }
#endif

    this->setFont(font);

	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setText(pButton->m_strName);
	SetPic(0);
}

void QSttBoutButton::SetPic(int nState)
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_IconBin_4);
		break;
	case 2:
		this->setIcon(g_oSttButtonIconMngr.m_IconBin_3);
		break;
	case 3:
		this->setIcon(g_oSttButtonIconMngr.m_IconBin_2);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_IconBin_1);
		break;
	}
}
/////////////////////////////////////////
/// \brief QSttNetStatButton::QSttNetStatButton
///

QSttNetStatButton::QSttNetStatButton( CExBaseObject *pCfgData,QFont font,QWidget *parent/*=0*/ )
: QSttToolButtonBase(pCfgData,parent)
{
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 80;
	else
		m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(m_nWidth, m_nWidth));
	this->setText(pButton->m_strName);

	SetPic(0);
}

void QSttNetStatButton::SetPic( int nState )
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_IconNetStat_1);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_IconNetStat_2);
		break;
	}
}
/////////////////////////////////////////
/// \brief QSttGpsButton::QSttGpsButton
///

QSttGpsButton::QSttGpsButton( CExBaseObject *pCfgData,QFont font,QWidget *parent/*=0*/ )
: QSttToolButtonBase(pCfgData,parent)
{
#ifndef _PSX_QT_LINUX_
	double dUIShowCoef = GetUIShowCoef();
#endif
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 60;
	else
		m_nWidth = pButton->m_nWidth;

#ifndef _PSX_QT_LINUX_
	if (dUIShowCoef >= 1.5)
	{
		m_nWidth = 240;
		//font.setPointSize(6);
	}
#endif

	this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	this->setStyleSheet("QToolButton {border: none; }");

	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(20-SttFrame_Vert_Gap*2, 20-SttFrame_Vert_Gap*2));

	CString strGpsTime;
	xlang_GetLangStrByFile(strGpsTime, "Native_NoTimeSync");
	setText(strGpsTime);

	SetPic(0);
}

void QSttGpsButton::SetPic( int nState )
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_IconGps_1);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_IconGps_2);
		break;
	}
}

//#include "../SttTestCntrFrameBase.h"

void QSttGpsButton::UpdateState(CDataGroup *pDataGroup)  //2022-6-9  lijunqing
{
	CString strGpsString = _T("");
	long nSyn = 0, nSecond = 0, nNSecend = 0;
	stt_GetDataValueByID(pDataGroup, _T("Sync"), nSyn);
	stt_GetDataValueByID(pDataGroup, _T("Utc_s"), nSecond);
	stt_GetDataValueByID(pDataGroup, _T("Utc_ns"), nNSecend);
	stt_GetDataValueByID(pDataGroup, _T("CurDate"), strGpsString);

	CString strGpsTime;
	xlang_GetLangStrByFile(strGpsTime, "Native_NoTimeSync");

	if (nSyn != g_oLocalSysPara.m_nHasSyn)
	{
		g_oLocalSysPara.m_nHasSyn = nSyn;
	}

//	if(nSyn)
	{
//		nSecond += 3600*g_oSystemParas.m_nTimeZone;  20230224 zhouhj 底层已处理好,为用户时间,即实际时区时间
//		g_theTestCntrFrame->SendMenuButtonClick("ScreenShot");
		SetPic(nSyn>0);

		if (strGpsString.IsEmpty())//如果传递了字符串,使用字符串对应时间
		{
//是否使用自定义的时间对象
#ifdef USE_Custom_CDateTime
			int nYear = 1970, nMon = 1, nDay = 1, nHour = 0, nMin = 0, nSec = 0;
			CDateTime::GetTime_BySecond(nSecond,nYear,nMon,nDay,nHour,nMin,nSec);
			strGpsTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),nYear,nMon,nDay,nHour,nMin,nSec);
#else
			strGpsTime = QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss")/*+QString("%1").arg((int)(nNSecend/1000000))*/;
#endif
		} 
		else
		{
			strGpsTime = strGpsString;
		}
	}
// 	else
// 	{
// 		SetPic(0);
// 	}

// 	if (nSyn != g_oLocalSysPara.m_nHasSyn)
// 	{
// 		g_oLocalSysPara.m_nHasSyn = nSyn;
// 
// 		if (g_oLocalSysPara.m_nHasSyn == 0)
// 		{
// 			strGpsTime = tr("未对时");
// 		} 
// 		else
// 		{
// 			strGpsTime = QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss")/*+QString("%1").arg((int)(nNSecend/1000000))*/;
// 		}
// 	}
// 	else if (nSyn > 0 )
// 	{
// 		strGpsTime = QDateTime::fromTime_t(nSecond).toString("yyyy-MM-dd hh:mm:ss")/*+QString("%1").arg((int)(nNSecend/1000000))*/;
// 	}

	if (strGpsTime.GetLength())
	{
		setText(strGpsTime);
	}
}

/////////////////////////////////////////
/// \brief QSttGpsButton::QSttGpsButton
///

QStt4GButton::QStt4GButton( CExBaseObject *pCfgData,QFont font,QWidget *parent/*=0*/ )
: QSttToolButtonBase(pCfgData,parent)
{
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 60;
	else
		m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(m_nWidth, m_nWidth));
	this->setText(pButton->m_strName);

	SetPic(0);
}

void QStt4GButton::SetPic( int nState )
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_Icon4G_1);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_Icon4G_2);
		break;
	}
}

/////////////////////////////////////////
/// \brief QSttGpsButton::QSttGpsButton
///

QSttWifiButton::QSttWifiButton( CExBaseObject *pCfgData,QFont font,QWidget *parent/*=0*/ )
: QSttToolButtonBase(pCfgData,parent)
{
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 60;
	else
		m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(m_nWidth, m_nWidth));
	this->setText(pButton->m_strName);

	SetPic(0);
}

void QSttWifiButton::SetPic( int nState )
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_IconWifi_1);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_IconWifi_2);
		break;
	}
}

/////////////////////////////////////////
/// \brief QSttUSBButton::QSttUSBButton
///

QSttUSBButton::QSttUSBButton( CExBaseObject *pCfgData,QFont font,QWidget *parent/*=0*/ )
: QSttToolButtonBase(pCfgData,parent)
{
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 60;
	else
		m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(m_nWidth, m_nWidth));
	this->setText(pButton->m_strName);
	SetPic(0);
}

void QSttUSBButton::SetPic( int nState )
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_IconUSB_1);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_IconUSB_2);
		break;
	}
}

/////////////////////////////////////////
/// \brief QSttBlueToothButton::QSttBlueToothButton
///

QSttBlueToothButton::QSttBlueToothButton( CExBaseObject *pCfgData,QFont font,QWidget *parent/*=0*/ )
: QSttToolButtonBase(pCfgData,parent)
{
	CSttFrame_Data *pButton = (CSttFrame_Data*)pCfgData;

	CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());
	m_nHeight = pParent->GetBtnHeight();
	if(pButton->m_nWidth == 0)
		m_nWidth = 60;
	else
		m_nWidth = pButton->m_nWidth;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setStyleSheet("QToolButton {border: none;}");
	this->setFixedSize(m_nWidth,m_nHeight);
	this->setIconSize(QSize(m_nWidth, m_nWidth));
	this->setText(pButton->m_strName);

	SetPic(0);
}

void QSttBlueToothButton::SetPic( int nState )
{
	switch(nState)
	{
	case 1:
		this->setIcon(g_oSttButtonIconMngr.m_IconBlueTooth_1);
		break;
	default:
		this->setIcon(g_oSttButtonIconMngr.m_IconBlueTooth_2);
		break;
	}
}

void QSttBlueToothButton::UpdateState(CDataGroup *pDataGroup)  //2022-6-10  lijunqing
{
	long nBle = -1;
	stt_GetDataValueByID(pDataGroup, _T("Ble"), nBle);
	SetPic(nBle);
}

//////////////////////////////////////////////////////////////////////////
QSttBarDataBtnsMngr::QSttBarDataBtnsMngr()
{
	m_pBatteryButton = NULL;
}
QSttBarDataBtnsMngr::~QSttBarDataBtnsMngr()
{

}

void QSttBarDataBtnsMngr::UpdataDataButtons(CDataGroup *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;
	QSttToolButtonBase *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)pDatas->GetNext(pos);
		pFind = FindButtonByID(pData->m_strID);

		if (pFind != NULL)
		{
			pFind->UpdateState(pData);
		}
	}
}

void QSttBarDataBtnsMngr::UpdataDataButtons(CDataGroup *pDatas, const CString& strBtnID)
{
	QSttToolButtonBase *pFind = (QSttToolButtonBase *)FindButtonByID(strBtnID);
	if(pFind)
	{
		pFind->UpdateState(pDatas);
	}
}

QSttToolButtonBase* QSttBarDataBtnsMngr::FindButtonByID(const CString &strID)
{
    for(int i=0;i<size();i++)
    {
        QSttToolButtonBase *pObj = at(i);
        if(pObj->m_pCfgData->m_strID == strID)
        {
            return pObj;
        }
    }
    return NULL;
}

long QSttBarDataBtnsMngr::GetBatCapValue()
{
	if (m_pBatteryButton != NULL)
	{
		return m_pBatteryButton->m_nBatCapValue;
	}

	m_pBatteryButton = (QSttBatteryButton*)FindButtonByID("BatCap");

	if (m_pBatteryButton == NULL)
	{
		return -1;
	}

	return m_pBatteryButton->m_nBatCapValue;
}

BOOL QSttBarDataBtnsMngr::IsCharging()
{
	if (m_pBatteryButton != NULL)
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("IsCharging(%ld)."),m_pBatteryButton->m_nPowerAC);
		return (m_pBatteryButton->m_nPowerAC>0);
	}

	m_pBatteryButton = (QSttBatteryButton*)FindButtonByID("BatCap");

	if (m_pBatteryButton == NULL)
	{
		//zhouhj 2023.11.25 未找到电池图标,默认在充电中,如L336D
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("IsCharging(false)."));
		return TRUE;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("IsCharging2(%ld)."),m_pBatteryButton->m_nPowerAC);
	return (m_pBatteryButton->m_nPowerAC>0);
}

BOOL QSttBarDataBtnsMngr::IsLowPower()
{
	if (m_pBatteryButton == NULL)
	{
		m_pBatteryButton = (QSttBatteryButton*)FindButtonByID("BatCap");
	}

	if (m_pBatteryButton == NULL)
	{
		return FALSE;
	}

	if ((m_pBatteryButton->m_nPowerAC>0)//充电中,默认不是低电量
		||(m_pBatteryButton->m_nBatCapValue<0))//剩余电量值小于0,默认未收到电量信息
	{
		return FALSE;
	}

	if (m_pBatteryButton->m_nBatCapValue<=10)//剩余电量少于等于10时,为低电量模式
	{
		return TRUE;
	}

	return FALSE;
}

BOOL QSttBarDataBtnsMngr::UpdatePicSet(const CString &strID,long nValue)
{
	QSttToolButtonBase *pButton = FindButtonByID(strID);

	if (pButton == NULL)
	{
		return FALSE;
	}

	pButton->SetPic(nValue);
	return TRUE;
}


