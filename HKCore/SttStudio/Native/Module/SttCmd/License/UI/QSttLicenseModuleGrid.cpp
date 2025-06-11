#include "QSttLicenseModuleGrid.h"
#include "../SttLicenseModule.h"

QSttLicenseModuleGrid::QSttLicenseModuleGrid(QWidget *parent)
:QExBaseListGridBase(parent)
{
}

QSttLicenseModuleGrid::~QSttLicenseModuleGrid()
{

}

void QSttLicenseModuleGrid::InitGrid()
{
	InitGridTitle();
}

void QSttLicenseModuleGrid::InitGridTitle()
{
    CString astrGridTitle[7] = { _T("Name"), _T("SN"), _T("Key"), _T("Date"), _T("Days"), _T("Times"), _T("")};
    int iGridWidth[7] = { 250, 200 , 600, 100, 60, 60, 50 };
    QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 7);
}

void QSttLicenseModuleGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
    CSttLicenseModule *pModule = (CSttLicenseModule*)pData;

    CString strText;

     Show_StaticString(pModule, nRow, 0, pModule->m_strName);
     Show_StaticString(pModule, nRow, 1, pModule->m_strID);
     Show_StaticString(pModule, nRow, 2, pModule->m_strKey);

     if (pModule->m_nYear > 0)
     {
         strText.Format(_T("%d-%d-%d"), pModule->m_nYear, pModule->m_nMonth, pModule->m_nDay);
         Show_StaticString(pModule, nRow, 3, strText);
         strText.Format(_T("%d"), pModule->m_nDays);
         Show_StaticString(pModule, nRow, 4, strText);
     }
     else
     {
         Show_StaticString(pModule, nRow, 3, _T("---"));
         Show_StaticString(pModule, nRow, 4, _T("---"));
     }

     if (pModule->m_nTimes > 0)
     {
         strText.Format(_T("%d"), pModule->m_nTimes);
         Show_StaticString(pModule, nRow, 5, strText);
     }
     else
     {
         Show_StaticString(pModule, nRow, 5, _T("---"));
     }

     nRow++;
}

