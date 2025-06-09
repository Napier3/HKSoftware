#include "stdafx.h"
#include "SttUIGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QGuiApplication>  
#include <QScreen>  


double GetDeviceCaps_LOGPIXELSX()
{
	// 获取主屏幕的QScreen对象
	QScreen *screen = QGuiApplication::primaryScreen();

	// 获取沿屏幕宽度每逻辑英寸的像素数
	qreal dpiX = screen->logicalDotsPerInchX();

	return dpiX;
}

double GetDeviceCaps_LOGPIXELSY()
{
	// 获取主屏幕的QScreen对象
	QScreen *screen = QGuiApplication::primaryScreen();

	// 获取沿屏幕宽度每逻辑英寸的像素数
	qreal dpiX = screen->logicalDotsPerInchY();

	return dpiX;
}



#else

#include <QApplication>
#include <QDesktopWidget>

double GetDeviceCaps_LOGPIXELSX()
{
	return 96;
}

double GetDeviceCaps_LOGPIXELSY()
{
	return 96;
}

#endif

