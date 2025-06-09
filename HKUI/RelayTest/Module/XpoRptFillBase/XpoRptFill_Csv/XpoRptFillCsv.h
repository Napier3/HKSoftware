// XpoRptFillCsv.h : header file

#pragma once

#include "../../XpoRptTemplate/RptTemp_TestMacroUiRpt.h"
#include "../../XpoRptTemplate/RptTemp_Png.h"
#include "../XpoRptFillFactory.h"

class XpoRptFillCsv : public XpoRptFillBase
{
public:
    XpoRptFillCsv(void);
    virtual ~XpoRptFillCsv(void);

public:
    void Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile);

protected:
    CRptTemp_TestMacroUiRpt *m_pTestMacroUiRpt;
    QList<QStringList> rptData;

protected:
    void OpenXmlRptFile(const CString &strXmlFile);

    void SaveAsCsv(const CString &strOutFile);

    void TestMacroUiRptToList(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt);
    void RptItemsToList(CRptTemp_Items *pRptTemp_Items);
    void RptTemplateToList(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate);
    void TitleToList(const CString &strText/*, long titleID*/);
    void TextToList(const CString &strText);
    void GridToList(CRptTemp_Grid *pRptTemp_Grid);
    void HeadToList(CRptTemp_Head *pRptTemp_Head);
    void RowToList(CRptTemp_Row *pRptTemp_Row);
};





