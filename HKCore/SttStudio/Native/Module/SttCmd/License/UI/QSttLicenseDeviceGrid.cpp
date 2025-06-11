#include "QSttLicenseDeviceGrid.h"
#include "../SttLicense.h"

QSttLicenseDeviceGrid::QSttLicenseDeviceGrid(QWidget *parent)
:QExBaseListGridBase(parent)
{
}

QSttLicenseDeviceGrid::~QSttLicenseDeviceGrid()
{

}

void QSttLicenseDeviceGrid::InitGrid()
{
	InitGridTitle();
}

void QSttLicenseDeviceGrid::InitGridTitle()
{
    CString astrGridTitle[3] = {_T("Index"), _T("Model"), _T("SN")};
    int iGridWidth[3] = { 50, 200, 200 };
    QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void QSttLicenseDeviceGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
    CSttLicense *pSttLicense = (CSttLicense*)pData;

    CString strText;
    strText.Format(_T("%d"), nRow);
     Show_StaticString(pSttLicense, nRow, 0, strText);

     Show_StaticString(pSttLicense, nRow, 1, pSttLicense->m_strName);
     Show_StaticString(pSttLicense, nRow, 2, pSttLicense->m_strID);

     nRow++;
}

