// XpoRptFillFactory.cpp : implementation file

#include "XpoRptFillFactory.h"
#include "XpoRptFillBase/XpoRptFill_Word/XpoRptFillWord.h"
#include "XpoRptFillBase/XpoRptFill_Pdf/XpoRptFillPdf.h"
#include "XpoRptFillBase/XpoRptFill_Excel/XpoRptFillExcel.h"
#include "XpoRptFillBase/XpoRptFill_Csv/XpoRptFillCsv.h"

XpoRptFillBase* XpoRptFillFactory::CreateXpoRpt(long &strRptId) //, CString &rptfilename
{
    switch (strRptId) //word-1 pdf-2 excel-3 csv-4 system-0
    {
    case 1:
        return new XpoRptFillWord();
        break;
    case 2:
        return new XpoRptFillPdf();
        break;
    case 3:
        return new XpoRptFillExcel();
        break;
    case 4:
        return new XpoRptFillCsv();
        break;
    default:
        return NULL;
        break;
    }
}
