#include "QSttLicenseFileGrid.h"
#include "../../../../../Module/XfileMngrBase/XFile.h"

QSttLicenseFileGrid::QSttLicenseFileGrid(QWidget *parent)
:QExBaseListGridBase(parent)
{
}

QSttLicenseFileGrid::~QSttLicenseFileGrid()
{

}

void QSttLicenseFileGrid::InitGrid()
{
	InitGridTitle();
}

void QSttLicenseFileGrid::InitGridTitle()
{
    CString astrGridTitle[3] = {_T("Path"), _T("Size"), _T("Time")};
    int iGridWidth[3] = { 600, 60, 80 };
    QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void QSttLicenseFileGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
    CXFile *pFile = (CXFile*)pData;
    CString strText;
     Show_StaticString(pFile, nRow, 0, pFile->GetTotalFileName());

     strText.Format(_T("%d"), pFile->GetFileSize());
     Show_StaticString(pFile, nRow, 1, strText);

     pFile->GetModifyTime(strText);
     Show_StaticString(pFile, nRow, 2, strText);
     nRow++;
}

