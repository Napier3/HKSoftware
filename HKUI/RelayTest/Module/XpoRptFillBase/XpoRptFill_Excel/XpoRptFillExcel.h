// XpoRptFillExcel.h : header file

#pragma once

#include "../../XpoRptTemplate/RptTemp_TestMacroUiRpt.h"
#include "../../XpoRptTemplate/RptTemp_Png.h"
#include "../XpoRptFillFactory.h"

#include "ActiveQt/QAxObject"

struct stcMergeData
{
    int curRow = 0;
    int curCol = 0;
    long rowSpan = 0;
    long colSpan = 0;
};
struct stcBordersRange
{
    int startRow = 0;
    int startCol = 0;
    int endRow = 0;
    int endCol = 0;
};

class XpoRptFillExcel : public XpoRptFillBase
{
public:
    XpoRptFillExcel(void);
    virtual ~XpoRptFillExcel(void);

public:
    void Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile);

protected:
    CRptTemp_TestMacroUiRpt *m_pTestMacroUiRpt;
    QAxObject *m_pApp;

    std::vector<stcMergeData> vecMergeData;
    std::vector<stcBordersRange> vecBordersRange;

protected:
    void OpenXmlRptFile(const CString &strXmlFile);

    void FillExcel(const CString &strOutFile);

    void AddTestMacroUiRpt();
    void AddItems(CRptTemp_Items *pRptItems);
    void AddRptTemplate(CRptTemp_ReportTemplate *m_pRptTemp);
    void AddTitle(const CString &strText, int titleID);
    void AddText(const QString &strText);
    void AddPng(const QString &strFullFileName);
    void AddTable(CRptTemp_Grid *pRptTemp_Grid);
    void AddHead(CRptTemp_Head *pRptTemp_Head);
    void AddRow(CRptTemp_Row *pRptTemp_Row);

    void MergeCells();
    void MergeCell(int curRow, int curCol, long rowSpan, long colSpan);
    void BorderCells();
    void BorderCell(int startRow, int startCol, int endRow, int endCol);

    //ftt 7.15 原本excel文件中图片还在
    //ftt 9.18 图片已清除
    void OpenExcel(const QString &strOutFile);
    void CreateExcel();
    void SaveAsExcel(const CString &strOutFile);
    void CloseExcel();
};
