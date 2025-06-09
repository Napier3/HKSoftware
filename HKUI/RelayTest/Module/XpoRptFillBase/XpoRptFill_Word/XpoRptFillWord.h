// XpoRptFillWord.h : header file

#pragma once

#include "../../XpoRptTemplate/RptTemp_TestMacroUiRpt.h"
#include "../../XpoRptTemplate/RptTemp_Png.h"
#include "../XpoRptFillFactory.h"

#include "ActiveQt/QAxObject"

class XpoRptFillWord : public XpoRptFillBase
{
public:
    XpoRptFillWord(void);
    virtual ~XpoRptFillWord(void);

public:
    void Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile);

protected:
    CRptTemp_TestMacroUiRpt *m_pTestMacroUiRpt;
    QAxObject *m_pApp;

protected:
    void OpenXmlRptFile(const CString &strXmlFile);

    void FillWord(const CString &strOutFile);

    void AddTestMacroUiRpt();
    void AddItems(CRptTemp_Items *pRptItems);
    void AddRptTemplate(CRptTemp_ReportTemplate *pRptTemp);
    void AddTitle(const CString &strText, long nLevel, int titleID);
    void AddText(const QString &strText);
    void AddPng(const QString &strFullFileName);
    void AddTable(CRptTemp_Grid *pRptTemp_Grid);

    void FillHead(CRptTemp_Head *pRptTemp_Head, int nRow, QAxObject *pTable);
    void FillRow(CRptTemp_Row *pRptTemp_Row, int nRow, QAxObject *pTable);
    void SetCellText(QAxObject *pTable, int nRow, int nCol, const QString &strText);
    void MergeCells(QAxObject *pTable, int nStartRow, int nStartCol, int nEndRow, int nEndCol);

    void OpenWord(const QString &strFullFileName);
    void CreateWord();
    void SaveAsWord(const CString &strOutFile);
    void CloseWord();
    void JumpToTheEnd();
};





