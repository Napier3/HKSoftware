#include "SttXMainFrameBase.h"
#include "Ctrls/SttWgtNativeMainLinux.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "Module/SttWgtFactory.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include <QScreen>
#ifndef _PSX_QT_LINUX_
#include <Windows.h>
#endif
#include <QDesktopWidget>
#include <QApplication>

QSttXMainFrameBase *g_theSttXMainFrame = NULL;
long g_nComBoxItemHeight = 50;
long g_nComBoxVertScrollWidth = 30;
long g_nTableVertScrollWidth = 30;
long g_nTableHorizontalScrollHeight = 30;
QFont *g_pSttGlobalFont = NULL;

QSttXMainFrameBase::QSttXMainFrameBase(QWidget *parent, CString strConfigFile)
: QMainWindow(parent)
{
	m_pMainConfig = NULL;
	g_theSttXMainFrame = this;
	g_pSttWgtCmdMainWindow = this;

// 	HDC hd = GetDC(NULL);
// 	int dotPix1 = GetDeviceCaps(hd, LOGPIXELSX);
// 	int dotPix2 = GetDeviceCaps(hd, LOGPIXELSY);	//获取放大比例
// 	///windows函数获取 end/
// 
// 
// 	//Qt///
// 	QDesktopWidget* desktopWidget = QApplication::desktop(); 
// 	int nMainScreenID = desktopWidget->primaryScreen();
// 	QRect oScreenRect = desktopWidget->screenGeometry(nMainScreenID);
// 	int nScreenWidth = oScreenRect.width();
// 	int nScreenHeight = oScreenRect.height();

//#ifdef _PSX_QT_LINUX_
	m_gFont = font();
	g_pSttGlobalFont = &m_gFont;
//#endif
	InitResource();
	InitUI(strConfigFile);
}

QSttXMainFrameBase::~QSttXMainFrameBase()
{
	g_pSttWgtCmdMainWindow = NULL;
	ReleaseResource();
}

void QSttXMainFrameBase::InitResource()
{
	CLogPrint::Create(this);
	CSttXMainConfigXmlRWKeys::Create();
}

void QSttXMainFrameBase::ReleaseResource()
{
	CSttXMainConfigXmlRWKeys::Release();
	CLogPrint::SetLog(NULL);
	CLogPrint::Release();
}

void QSttXMainFrameBase::InitUI(CString strConfigFile)
{
	//窗口生成
	QSize size(1024, 768);
	resize(1024,768);
#ifndef _PSX_QT_WINDOWS_
	setMaximumSize(size);
#endif
	setMinimumSize(size/*900,600*/);
#ifdef _PSX_QT_LINUX_
	setWindowFlags(Qt::FramelessWindowHint);
#else
	setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
#endif

// 	setWindowFlags(Qt::FramelessWindowHint);
// 	setAttribute(Qt::WA_TranslucentBackground,true);


	//读取配置文件
	CString strFile = _P_GetConfigPath();
	if(strConfigFile.GetLength())
	{
		strFile += strConfigFile;
	}
	else
	{
		strFile += "SttXMainConfig.xml";
	}

	m_pMainConfig = new CSttXuiDataMainConfig();
	if(!m_pMainConfig->OpenXmlFile(strFile, CSttXMainConfigXmlRWKeys::g_pXmlKeys))
	{
		return;
	}

	g_dStartupDelayTime =  m_pMainConfig->m_dStartupDelayTime;

#ifndef NOT_USE_XLANGUAGE
	if(strConfigFile.GetLength())
	{
		xlang_TranslateByResourceFileEx(m_pMainConfig, strConfigFile);
	}
	else
	{
		xlang_TranslateByResourceFileEx(m_pMainConfig, _T("SttXMainConfig.xml"));
	}
#endif

	if(m_pMainConfig->m_nCx && m_pMainConfig->m_nCy)
	{
#ifdef _PSX_QT_WINDOWS_
		HDC hd = GetDC(NULL);
		double dDotPix1 = GetDeviceCaps(hd, LOGPIXELSX);
		g_dUIShowCoef = dDotPix1 / 96;
#endif
		QSize sizeNew(m_pMainConfig->m_nCx * g_dUIShowCoef, m_pMainConfig->m_nCy* g_dUIShowCoef);
#ifndef _PSX_QT_WINDOWS_
		setMaximumSize(sizeNew);
#endif
		setMinimumSize(sizeNew/*900,600*/);
	}

	//开始对Main进行界面生成
	//QSttWgtNativeMainLinux* p = (QSttWgtNativeMainLinux*)QSttWgtFactory::CreateSttWgt(pMainConfig);
	QSttWgtNativeMainLinux* p = new QSttWgtNativeMainLinux();
	p->InitUI(strFile, m_pMainConfig);
	setCentralWidget(p);

#ifndef _PSX_QT_LINUX_
//	CreateCloseHidingBtns();
#endif
}

void QSttXMainFrameBase::CreateCloseHidingBtns()
{
	//创建最小化以及关闭按钮
	QRect rc = geometry();
	QSize szBtn = QSize(36, 24);
	long nX = rc.right() - szBtn.width();
	QPushButton* pBtn = new QPushButton(this);
	pBtn->setText("×");
	pBtn->setGeometry(nX, 0, szBtn.width(), szBtn.height());
	pBtn->setStyleSheet("QPushButton{border:0px solid white; color: white; background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #058a93, stop: 0.4 #06a1ac, stop: 0.5 #06a1ac, stop: 1.0 #058a93);}"
		"QPushButton:hover{border:1px solid white;background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff0000, stop: 0.4 #ff8080, stop: 0.5 #ff8080, stop: 1.0 #ff0000);}");
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_CloseApp()));
	nX = nX - szBtn.width();
	pBtn = new QPushButton(this);
	pBtn->setText("—");
	pBtn->setStyleSheet("QPushButton{border:0px solid white; color: white; background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #058a93, stop: 0.4 #06a1ac, stop: 0.5 #06a1ac, stop: 1.0 #058a93);}"
		"QPushButton:hover{border:1px solid white;background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #4d4dff, stop: 0.4 #9a9aff, stop: 0.5 #9a9aff, stop: 1.0 #4d4dff);}");
	pBtn->setGeometry(nX, 0, szBtn.width(), szBtn.height());
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_HideApp()));
}

// long Global_GetComBoxItemHeight()
// {
//	return 50;
//}

void QSttXMainFrameBase::slot_CloseApp()
{
	close();
}

void QSttXMainFrameBase::slot_HideApp()
{
	showMinimized();
}
