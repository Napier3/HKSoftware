#include "stdafx.h"
#include <strsafe.h>
#include "..\..\SclFileTest\SCLCompareCheckDev.h"
#include "AppGlobals.h"
#include "..\..\SclFileTest\MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
//#pragma comment(lib, "shlwapi.lib")

/////////////////////////////////////////////////////////////////////////////
// CAppData
CAppData appData;

/////////////////////////////////////////////////////////////////////////////
CAppData::CAppData()
{
        memset(&m_dataApp,  0, sizeof(m_dataApp));
}

CAppData::~CAppData()
{
        // ɾ��Ӱ����Դ��


}

void CAppData::Initialize()
{  

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int CGlobals::appAlert1(LPCTSTR pszText, UINT nType)
{
        // ����������޸Ĵ�����Ϣ��������ӳ������ȡ�
        HWND hWndFocus = ::GetFocus();
        int nResponse = AfxMessageBox(pszText, nType);
        if (::IsChild(AfxGetMainWnd()->GetSafeHwnd(), hWndFocus))
        {
                ::SetFocus(hWndFocus);
        }
        return nResponse;
}

int CGlobals::appAlert1(UINT nID, UINT nType)
{
        CString string;
        string.LoadString(nID);
        return appAlert1((LPCTSTR)string, nType);
}

int __cdecl CGlobals::appAlert2(UINT nID, UINT nType, ...)
{
        CString strFormat;
        CString strMessage;

        va_list arglist;
        va_start(arglist, nType);

        strFormat.LoadString(nID);
        strMessage.FormatV(strFormat, arglist);

        va_end(arglist);

        return appAlert1((LPCTSTR)strMessage, nType);
}
