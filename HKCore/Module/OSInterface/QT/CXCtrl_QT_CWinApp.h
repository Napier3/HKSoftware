#ifndef _xctrl_qt_CWinApp_h__
#define _xctrl_qt_CWinApp_h__

#include <qfile.h>
#include <QObject>
#include "CString_QT.h"

class CWinApp
{
public:
    CWinApp()
    {

    }
    virtual ~CWinApp()
    {
    }

    void SetCursor()
    {

    }
    void ClipCursor()
    {

    }

    long LoadCursor(unsigned long nID)
    {
		nID = 0;
        return 0;
    }

#ifndef _USE_NO_GUI_
    QApplication *m_pApplication;
#endif
};

extern CWinApp* g_ptheApp;
CWinApp* AfxGetApp();

#ifdef _PSX_QT_LINUX_
void SetCursor(long nCursor);
void ClipCursor(CRect *pRect);
void ReleaseCapture();
#endif

#endif   //_xctrl_qt_CWinApp_h__
