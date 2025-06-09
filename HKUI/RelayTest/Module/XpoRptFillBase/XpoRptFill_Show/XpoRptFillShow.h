#pragma once

#include "../../XpoRptTemplate/RptTemp_TestMacroUiRpt.h"
#include "../../XpoRptTemplate/RptTemp_Png.h"

#include <QTextTable>
#include <QBuffer>

//模板结点指针：Title/Text/Png/Grid
struct NodeInfo
{
    CString text = ""; //Title和Text的文本值
    CString pngPath = ""; //Png
    int startPos = 0; //Title/Text/Png结点保存光标位置
    int endPos;
    //QTextTable *gridPointer = 0; //Grid结点保存对应的QTextTable指针
    //isTable
};

namespace Ui {
class XpoRptFillShow;
}

class XpoRptFillShow : public QWidget
{
    Q_OBJECT

public:
    explicit XpoRptFillShow(QWidget *parent = 0);
    ~XpoRptFillShow();
public:
    void Xpo_RptShow(const CString &strXmlFile);

private:
    Ui::XpoRptFillShow *ui;
    QTextDocument *m_pDocument;
    CRptTemp_TestMacroUiRpt *m_pTestMacroUiRpt;

    QList<QTextTable*> Tables;

    QTextCharFormat m_oTitleFormat;
    QTextBlockFormat m_oTitleBlockFormat;

    QTextCharFormat m_oTextFormat;
    QTextBlockFormat m_oTextBlockFormat;

    QTextBlockFormat m_oGridBlockFormat;
    QTextTableCellFormat m_oCellFormat;

protected:
    void init();

    void OpenXmlRptFile(const CString &strXmlFile);

    void TestMacroUiRptToTxDoc(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt);
    void RptItemsToTxDoc(CRptTemp_Items *pRptTemp_Items);
    void RptTemplateToTxDoc(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate);
    void TitleToTxDoc(const CString &strText, long nLevel/*, long titleID*/);
    void TextToTxDoc(const CString &strText, float nSize, long bBold, CString strFontFamily);
    void PngToTxDoc(const CString &strPath);
    void GridToTxDoc(CRptTemp_Grid *pRptTemp_Grid);
    void HeadToTxDoc(CRptTemp_Head *pRptTemp_Head, long nRow, QTextTable *table);
    void RowToTxDoc(CRptTemp_Row *pRptTemp_Row, long nRow, QTextTable *table);

    void GetTitleFontSize(long nLevel, double &nSize);

private slots:
    void on_btnSetValue_clicked();
};


