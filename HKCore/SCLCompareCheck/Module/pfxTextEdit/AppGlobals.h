#pragma once
#include <shlwapi.h>

/////////////////////////////////////////////////////////////////////////////
#ifndef SIZEOF
#define SIZEOF(x)               (sizeof(x) / sizeof(x[0]))
#endif

#ifndef SIZEOF_NO_NULL
#define SIZEOF_NO_NULL(x)       (sizeof(x) / sizeof(x[0]) - 1)
#endif


/////////////////////////////////////////////////////////////////////////////
// 用户接口状态（这些数值是定值不能更改）
const int UI_UNCHECK            = 0;
const int UI_CHECK              = 1;
const int UI_INDETERMINATE      = 2;
static const TCHAR STR_MODIFIED_DOCUMENT_TITLE_FLAG[]   = _T(" *");

/////////////////////////////////////////////////////////////////////////////
class CSCLCompareCheckDevApp;
class CMainFrame;

class CAppData
{
public:
        CAppData();
        ~CAppData();
public:
        void           Initialize();

private: // 程序相关
        struct CDataApp
        {
                CSCLCompareCheckDevApp*          pApp;
                CMainFrame*     pAppFrame;
        };
        CDataApp       m_dataApp;

public:
        CSCLCompareCheckDevApp*          App() const;
        CMainFrame*     AppFrame() const;

        void           SetApp(CSCLCompareCheckDevApp* pApp);
        void           SetAppFrame(CMainFrame* pAppFrame);

};
extern CAppData appData;

/////////////////////////////////////////////////////////////////////////////
inline CSCLCompareCheckDevApp*           CAppData::App() const               { ASSERT(this != NULL); return m_dataApp.pApp; }
inline CMainFrame*      CAppData::AppFrame() const          { ASSERT(this != NULL); return m_dataApp.pAppFrame; }
inline void            CAppData::SetApp(CSCLCompareCheckDevApp* pApp)        { m_dataApp.pApp = pApp; }
inline void            CAppData::SetAppFrame(CMainFrame* pAppFrame) { m_dataApp.pAppFrame = pAppFrame; }

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
namespace CGlobals
{
        /////////////////////////////////////////////////////////////////////
        CSCLCompareCheckDevApp*          GetApp();
        CMainFrame*     GetAppFrame();

        /////////////////////////////////////////////////////////////////////
        int            appAlert1(UINT nID, UINT nType);
        int            appAlert1(LPCTSTR pszText, UINT nType);
        int _cdecl     appAlert2(UINT nID, UINT nType, ...);

}


/////////////////////////////////////////////////////////////////////////////
inline CSCLCompareCheckDevApp*           CGlobals::GetApp()          { return appData.App(); }
inline CMainFrame*      CGlobals::GetAppFrame()     { return appData.AppFrame(); }

/////////////////////////////////////////////////////////////////////////////
using namespace CGlobals;
