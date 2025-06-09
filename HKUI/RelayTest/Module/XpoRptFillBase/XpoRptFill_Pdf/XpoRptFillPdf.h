// XpoRptFillPdf.h : header file

#pragma once

#include "../../XpoRptTemplate/RptTemp_TestMacroUiRpt.h"
#include "../../XpoRptTemplate/RptTemp_Png.h"
#include "../XpoRptFillFactory.h"

#include <QTextDocument>
#include <QTextTable>
#include <QPrinter>
#include <QBuffer>

class XpoRptFillPdf : public XpoRptFillBase
{
public:
    XpoRptFillPdf(void);
    virtual ~XpoRptFillPdf(void);

public:
    void Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile);

protected:
    CRptTemp_TestMacroUiRpt *m_pTestMacroUiRpt;
    QTextDocument m_oTextDoc;    

protected:
    void OpenXmlRptFile(const CString &strXmlFile);

    void SaveAsPdf(const CString &strOutFile);

    void TestMacroUiRptToTxDoc(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt);
    void RptItemsToTxDoc(CRptTemp_Items *pRptTemp_Items);
    void RptTemplateToTxDoc(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate);
    void TitleToTxDoc(const CString &strText, long nLevel/*, long titleID*/); //titleID表示序号
    void TextToTxDoc(const CString &strText, float nSize, long bBold, CString strFontFamily);
    void PngToTxDoc(const CString &strPath);
    void GridToTxDoc(CRptTemp_Grid *pRptTemp_Grid);
    void HeadToTxDoc(CRptTemp_Head *pRptTemp_Head, long nRow, QTextTable *table);
    void RowToTxDoc(CRptTemp_Row *pRptTemp_Row, long nRow, QTextTable *table);

    void GetTitleFontSize(long nLevel, double &nSize);
};

