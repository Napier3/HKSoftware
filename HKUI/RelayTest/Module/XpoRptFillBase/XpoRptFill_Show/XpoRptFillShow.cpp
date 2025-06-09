#include "XpoRptFillShow.h"
#include "ui_XpoRptFillShow.h"
#include "../../../Module/API/FileApi.h"

XpoRptFillShow::XpoRptFillShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XpoRptFillShow)
{
    m_pTestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
    m_pDocument = new QTextDocument();

    ui->setupUi(this);
    ui->btnTextEdit->resize(1200, 800);
    this->resize(1300, 800);    
    init();
}

XpoRptFillShow::~XpoRptFillShow()
{
    delete ui;
    delete m_pDocument;
    delete m_pTestMacroUiRpt;
}

void XpoRptFillShow::Xpo_RptShow(const CString &strXmlFile)
{
    OpenXmlRptFile(strXmlFile);
    TestMacroUiRptToTxDoc(m_pTestMacroUiRpt);
}

void XpoRptFillShow::init()
{
    m_oTitleFormat.setFontWeight(QFont::Bold);
    m_oTitleFormat.setFontFamily("Source Han Sans CN");
    m_oTitleBlockFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);

    m_oTextBlockFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);
    m_oGridBlockFormat.setAlignment(Qt::AlignCenter);

    m_oCellFormat.setFontPointSize(10.4);
    m_oCellFormat.setVerticalAlignment(QTextTableCellFormat::AlignMiddle);
}

void XpoRptFillShow::OpenXmlRptFile(const CString &strXmlFile)
{
    if (!IsFileExist(strXmlFile))
    {
        return ;
    }
    CTestMacroRptTemplateXmlRWKeys *RptTemplateXmlRWKeys = CTestMacroRptTemplateXmlRWKeys::Create();

    m_pTestMacroUiRpt->OpenXmlFile(strXmlFile, RptTemplateXmlRWKeys->g_pXmlKeys);

    CTestMacroRptTemplateXmlRWKeys::Release();
}

#include <QDebug>
void XpoRptFillShow::TestMacroUiRptToTxDoc(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt)
{
    if (pRptTemp_TestMacroUiRpt == NULL)
    {
        return ;
    }

    POS pos = pRptTemp_TestMacroUiRpt->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;

//    long nCount = 1;
//    QDateTime tmBegin0 = QDateTime::currentDateTime();
//    QDateTime tmBegin = QDateTime::currentDateTime();
//    QDateTime tm = QDateTime::currentDateTime();
//    quint64 startTimeStamp = tmBegin.msecsTo(tmBegin);
//    quint64 endTimeStamp;

    while (pos != NULL)
    {
//        tmBegin = QDateTime::currentDateTime();

//        CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pRptTemp_TestMacroUiRpt->GetNext(pos);
//        RptTemplateToTxDoc(pRptTemp_ReportTemplate);

//        nCount++;
//        tm = QDateTime::currentDateTime();
//        endTimeStamp = tmBegin.msecsTo(tm);
//        qDebug() << nCount << ":" << endTimeStamp << "ms";

        pObj = pRptTemp_TestMacroUiRpt->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_ITEMS:
        {
            CRptTemp_Items *pRptTemp_Items = (CRptTemp_Items*)pObj;
            RptItemsToTxDoc(pRptTemp_Items);
        }
            break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            //tmBegin = QDateTime::currentDateTime();

            CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToTxDoc(pRptTemp_ReportTemplate);

//            nCount++;
//            tm = QDateTime::currentDateTime();
//            endTimeStamp = tmBegin.msecsTo(tm);
//            qDebug() << nCount << ":" << endTimeStamp << "ms";
        }
            break;
        default:
            return ;
        }
    }

    //tmBegin = QDateTime::currentDateTime();
    ui->btnTextEdit->setDocument(m_pDocument);
//    tm = QDateTime::currentDateTime();
//    endTimeStamp = tmBegin.msecsTo(tm);
//    qDebug() <<  "View Document:" << endTimeStamp << "ms";

//    endTimeStamp = tmBegin0.msecsTo(tm);
//    qDebug() <<  "Total Time:" << endTimeStamp << "ms";
}

void XpoRptFillShow::RptItemsToTxDoc(CRptTemp_Items *pRptTemp_Items)
{
    if (pRptTemp_Items == NULL)
    {
        return ;
    }

    TitleToTxDoc(pRptTemp_Items->m_strName, pRptTemp_Items->m_ntitle_level/*, titleID*/);

    POS pos = pRptTemp_Items->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;

    while (pos != NULL)
    {
        pObj = pRptTemp_Items->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_ITEMS:
        {
            CRptTemp_Items *pRptItems = (CRptTemp_Items*)pObj;
            RptItemsToTxDoc(pRptItems);
        }
            break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToTxDoc(pRptTemp_ReportTemplate);
        }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillShow::RptTemplateToTxDoc(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate)
{
    if (pRptTemp_ReportTemplate == NULL)
    {
        return ;
    }

    POS pos = pRptTemp_ReportTemplate->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;
    //long titleID = 1;

    while (pos != NULL)
    {
        pObj = pRptTemp_ReportTemplate->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_TITLE:
            {
                CRptTemp_Title *pTitle = (CRptTemp_Title*)pObj;
                TitleToTxDoc(pTitle->m_strText, pTitle->m_nLevel/*, titleID*/);
                //titleID++;
            }
            break;
        case MNGRCLASSID_CRPTTEMP_TEXT:
            {
                CRptTemp_Text *pText = (CRptTemp_Text*)pObj;
                TextToTxDoc(pText->m_strText, pText->m_fSize, pText->m_nBold, pText->m_strFont);
            }
            break;
        case MNGRCLASSID_CRPTTEMP_GRID:
            {
                CRptTemp_Grid *pGrid = (CRptTemp_Grid*)pObj;
                GridToTxDoc(pGrid);
            }
            break;
        case MNGRCLASSID_CRPTTEMP_PNG:
            {
                CRptTemp_Png *pPng = (CRptTemp_Png*)pObj;
                PngToTxDoc(pPng->m_strPngPath);
            }
            break;
        default:
            return ;
        }
    }

    //QTextCursor cursor(m_pDocument);
    //cursor.insertBlock();
    //cursor.insertBlock();
}

void XpoRptFillShow::TitleToTxDoc(const CString &strText, long nLevel/*, long titleID*/)
{
    QTextCursor cursor(m_pDocument);

    double nSize;
    GetTitleFontSize(nLevel, nSize);
    m_oTitleFormat.setFontPointSize(nSize);

    cursor.movePosition(QTextCursor::End);
    cursor.setCharFormat(m_oTitleFormat);
    cursor.setBlockFormat(m_oTitleBlockFormat);

    //cursor.insertText(QString(QString::number(titleID)));
    //cursor.insertText("  ");
    cursor.insertText(strText);
    cursor.insertBlock();

    //cursor.setCharFormat(m_oTitleFormat);
    //cursor.setBlockFormat(m_oTitleBlockFormat);
}

void XpoRptFillShow::TextToTxDoc(const CString &strText, float nSize, long bBold, CString strFontFamily)
{
    QTextCursor cursor(m_pDocument);

    if(strFontFamily == "")
    {
        strFontFamily = "Source Han Sans CN";
    }
    m_oTextFormat.setFontFamily(strFontFamily);
    m_oTextFormat.setFontPointSize(nSize);
    if(bBold)
    {
        m_oTextFormat.setFontWeight(QFont::Bold);
    }
    else
    {
        m_oTextFormat.setFontWeight(QFont::Normal);
    }
    cursor.movePosition(QTextCursor::End);
    cursor.setCharFormat(m_oTextFormat);
    cursor.setBlockFormat(m_oTextBlockFormat);

    cursor.insertText(strText);
    cursor.insertBlock();
}

void XpoRptFillShow::PngToTxDoc(const CString &strPath)
{
    if(!QFile::exists(strPath))
    {
        return;
    }
    QImage image(strPath);
    if(image.isNull())
    {
        return;
    }
    //可以设置图片的大小，也可以设置一行排几个图片 950/900/850/800
    image = image.scaled(500, image.height() * 500 / image.width(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();

    QTextCursor cursor(m_pDocument);
    cursor.movePosition(QTextCursor::End);

    QTextImageFormat m_oTextFormat;
    m_oTextFormat.setName("image");
    m_pDocument->addResource(QTextDocument::ImageResource, m_oTextFormat.name(), buffer.buffer());
    cursor.insertImage(m_oTextFormat);
    cursor.insertBlock(); //此处换行 表示一行只放一个图片
}

void XpoRptFillShow::GridToTxDoc(CRptTemp_Grid *pRptTemp_Grid)
{
    POS pos = pRptTemp_Grid->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    long rowCount = 0, colCount = 0;

    while (pos != NULL)
    {
        pObj = pRptTemp_Grid->GetNext(pos);
        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD || pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_ROW)
        {
            rowCount++;
        }
    }

    pos = pRptTemp_Grid->GetHeadPosition();
    CRptTemp_Head *pHead = (CRptTemp_Head*)pRptTemp_Grid->GetNext(pos);
    pos = pHead->GetHeadPosition();
    while (pos != NULL)
    {
        pObj = pHead->GetNext(pos);
        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_CELL)
        {
            colCount++;
        }
    }

    QTextCursor cursor(m_pDocument);
    cursor.movePosition(QTextCursor::End);
    QTextTableFormat tableFormat;
    QVector<QTextLength> columnWidths;

    for(int i = 0; i < colCount; i++)
    {
        columnWidths << QTextLength(QTextLength::FixedLength, 900/colCount);
    }

    tableFormat.setColumnWidthConstraints(columnWidths);
    QTextTable *table = cursor.insertTable(rowCount, colCount, tableFormat);
    Tables.append(table);

    pos = pRptTemp_Grid->GetHeadPosition();
    long nRow = 0;

    QTextCursor cellCursor = table->firstCursorPosition();
    cellCursor.setCharFormat(m_oCellFormat);
    cellCursor.setBlockFormat(m_oGridBlockFormat);

    while (pos != NULL)
    {
        pObj = pRptTemp_Grid->GetNext(pos);

        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD)
        {
            CRptTemp_Head *pHead = (CRptTemp_Head*)pObj;
            HeadToTxDoc(pHead, nRow, table);
            nRow++;
        }
        else
        {
            CRptTemp_Row *pRow = (CRptTemp_Row*)pObj;
            RowToTxDoc(pRow, nRow, table);
            nRow++;
        }
    }

    cursor = table->lastCursorPosition();
    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertBlock();
}

void XpoRptFillShow::HeadToTxDoc(CRptTemp_Head *pRptTemp_Head, long nRow, QTextTable *table)
{
    POS pos = pRptTemp_Head->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    long nCol = 0;

    while (pos != NULL)
    {
        pObj = pRptTemp_Head->GetNext(pos);
        if (pObj->GetClassID() != MNGRCLASSID_CRPTTEMP_CELL)
        {
            return ;
        }
        else
        {
            CRptTemp_Cell *pCell = (CRptTemp_Cell*)pObj;

            QTextTableCell cell = table->cellAt(nRow, nCol++);
            QTextCursor cellCursor = cell.firstCursorPosition();
//          cellCursor.setCharFormat(m_oTextFormat);
            cellCursor.setBlockFormat(m_oGridBlockFormat);
           cell.setFormat(m_oCellFormat);

            if(pCell->m_nRow_Span >1 || pCell->m_nCol_Span >1)
            {
                table->mergeCells(nRow, nCol-1, pCell->m_nRow_Span, pCell->m_nCol_Span);
            }

            cellCursor.insertText(pCell->m_strText, m_oCellFormat);
        }
    }
}

void XpoRptFillShow::RowToTxDoc(CRptTemp_Row *pRptTemp_Row, long nRow, QTextTable *table)
{
    POS pos = pRptTemp_Row->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    long nCol = 0;

    while (pos != NULL)
    {
        pObj = pRptTemp_Row->GetNext(pos);

        if (pObj->GetClassID() != MNGRCLASSID_CRPTTEMP_CELL)
        {
            continue ;
        }

        CRptTemp_Cell *pCell = (CRptTemp_Cell*)pObj;
        QTextTableCell cell = table->cellAt(nRow, nCol++);
        QTextCursor cellCursor = cell.firstCursorPosition();
        //cellCursor.setCharFormat(m_oTextFormat);
        cellCursor.setBlockFormat(m_oGridBlockFormat);
        cell.setFormat(m_oCellFormat);

        if(pCell->m_nRow_Span >1 || pCell->m_nCol_Span >1)
        {
            table->mergeCells(nRow, nCol-1, pCell->m_nRow_Span, pCell->m_nCol_Span);
        }

        cellCursor.insertText(pCell->m_strText);
    }
}

void XpoRptFillShow::GetTitleFontSize(long nLevel, double &nSize)
{
    switch (nLevel)
    {
    case 1:
        nSize = 21.9;
        break;
    case 2:
    case 3:
        nSize = 15.9;
        break;
    case 4:
    case 5:
        nSize = 14.0;
        break;
    default:
        nSize = 10.4;
        break;
    }
}

void XpoRptFillShow::on_btnSetValue_clicked()
{
    long nRow = ui->edtRow->text().toLong();
    long nCol = ui->edtCol->text().toLong();
    QTextTable *table = Tables[0];

    if(nRow > 0 && nRow < 15 && nCol > 0 && nCol < 6)
    {
        QTextTableCell cell = table->cellAt(nRow-1, nCol-1);
        QTextCursor cellCursor = cell.firstCursorPosition();

        cellCursor.select(QTextCursor::LineUnderCursor);
        cellCursor.deleteChar();

        cellCursor.setCharFormat(m_oTextFormat);
        cellCursor.insertText(ui->edtValue->text());
    }
}
