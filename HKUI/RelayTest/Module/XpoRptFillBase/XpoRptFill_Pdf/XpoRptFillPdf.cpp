// XpoRptFillPdf.cpp : implementation file

#include "XpoRptFillPdf.h"
#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


XpoRptFillPdf::XpoRptFillPdf()
{
    m_pTestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
}

XpoRptFillPdf::~XpoRptFillPdf()
{
    delete m_pTestMacroUiRpt;
}

void XpoRptFillPdf::Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile)
{   
    OpenXmlRptFile(strXmlFile);
    TestMacroUiRptToTxDoc(m_pTestMacroUiRpt);
    SaveAsPdf(strOutFile);
}

void XpoRptFillPdf::OpenXmlRptFile(const CString &strXmlFile)
{
    if (!IsFileExist(strXmlFile))
    {
        return ;
    }   

//    CTestMacroRptTemplateXmlRWKeys *RptTemplateXmlRWKeys = CTestMacroRptTemplateXmlRWKeys::Create();
//    m_pTestMacroUiRpt->OpenXmlFile(strXmlFile, RptTemplateXmlRWKeys->g_pXmlKeys);
//    CTestMacroRptTemplateXmlRWKeys::Release();

    CTestMacroRptTemplateXmlRWKeys *pXmlKeys = CTestMacroRptTemplateXmlRWKeys::Create();
    m_pTestMacroUiRpt->OpenXmlFile(strXmlFile, pXmlKeys->m_strCRptTemp_TestMacroUiRptKey, pXmlKeys);
    CTestMacroRptTemplateXmlRWKeys::Release();
}

void XpoRptFillPdf::SaveAsPdf(const CString &strOutFile)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFileName(strOutFile);
    printer.setOrientation(QPrinter::Portrait);
    printer.setPageMargins(5, 10, 5, 10, QPrinter::Millimeter);
    m_oTextDoc.print(&printer);
}

void XpoRptFillPdf::TestMacroUiRptToTxDoc(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt)
{
    if (pRptTemp_TestMacroUiRpt == NULL)
    {
        return ;
    }

    POS pos = pRptTemp_TestMacroUiRpt->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;

    while (pos != NULL)
    {
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
            CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToTxDoc(pRptTemp_ReportTemplate);
        }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillPdf::RptItemsToTxDoc(CRptTemp_Items *pRptTemp_Items)
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

void XpoRptFillPdf::RptTemplateToTxDoc(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate)
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
}

void XpoRptFillPdf::TitleToTxDoc(const CString &strText, long nLevel/*, long titleID*/)
{
    QTextCharFormat format;
    QTextBlockFormat blockFormat;
    QTextCursor cursor(&m_oTextDoc);

    double nSize;
    GetTitleFontSize(nLevel, nSize);
    format.setFontPointSize(nSize); //文本和表格是10.4 标题是由标题等级决定
    format.setFontWeight(QFont::Bold);
    format.setFontFamily("Source Han Sans CN");
    blockFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);

    cursor.movePosition(QTextCursor::End);
    cursor.setCharFormat(format);
    cursor.setBlockFormat(blockFormat);

//    cursor.insertText(QString(QString::number(titleID)));
//    cursor.insertText("  ");
    cursor.insertText(strText);
    cursor.insertBlock();
}

void XpoRptFillPdf::TextToTxDoc(const CString &strText, float nSize, long bBold, CString strFontFamily)
{
    QTextCharFormat format;
    QTextBlockFormat blockFormat;
    QTextCursor cursor(&m_oTextDoc);

    if(strFontFamily == "")
    {
        strFontFamily = "Source Han Sans CN";
    }
    format.setFontFamily(strFontFamily);
    format.setFontPointSize(nSize);
    if(bBold)
    {
        format.setFontWeight(QFont::Bold);
    }
    blockFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);
    cursor.movePosition(QTextCursor::End);
    cursor.setCharFormat(format);
    cursor.setBlockFormat(blockFormat);

    cursor.insertText(strText);
    cursor.insertBlock();
}

void XpoRptFillPdf::PngToTxDoc(const CString &strPath)
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

    QTextCursor cursor(&m_oTextDoc);
    cursor.movePosition(QTextCursor::End);

    //可以设置图片的大小，也可以设置一行排几个图片 950/900/850/800 //450
    image = image.scaled(300, image.height() * 300 / image.width(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();

    QTextImageFormat format;
    format.setName("image");
    //format.setVerticalAlignment(QTextCharFormat::VerticalAlignment::AlignTop); // 设置对齐方式
    m_oTextDoc.addResource(QTextDocument::ImageResource, format.name(), buffer.buffer());
    cursor.insertImage(format);
    cursor.insertBlock(); //此处换行 表示一行只放一个图片
}

void XpoRptFillPdf::GridToTxDoc(CRptTemp_Grid *pRptTemp_Grid)
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

    QTextCursor cursor(&m_oTextDoc);
    cursor.movePosition(QTextCursor::End);
    QTextTableFormat tableFormat;
    if(pRptTemp_Grid->m_nShowBorders == 0)
    {
        tableFormat.setBorder(0);
    }
    QVector<QTextLength> columnWidths;
    for(int i = 0; i < colCount; i++)
    {
        columnWidths << QTextLength(QTextLength::FixedLength, 900/colCount);
    }
    tableFormat.setColumnWidthConstraints(columnWidths);

    QTextTable *table = cursor.insertTable(rowCount, colCount, tableFormat);

    pos = pRptTemp_Grid->GetHeadPosition();
    long nRow = 0;
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

    cursor.movePosition(QTextCursor::End);
    cursor.insertBlock();
    cursor.insertBlock();
}


void XpoRptFillPdf::HeadToTxDoc(CRptTemp_Head *pRptTemp_Head, long nRow, QTextTable *table)
{
    QTextCharFormat format;
    QTextBlockFormat blockFormat;
    format.setFontPointSize(10.4);
    blockFormat.setAlignment(Qt::AlignCenter);

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
            cellCursor.setCharFormat(format);
            cellCursor.setBlockFormat(blockFormat);

            QTextTableCellFormat cellFormat;
            cellFormat.setVerticalAlignment(QTextTableCellFormat::AlignMiddle);
            cell.setFormat(cellFormat);
            if(pCell->m_nRow_Span >1 || pCell->m_nCol_Span >1)
            {
                table->mergeCells(nRow, nCol-1, pCell->m_nRow_Span, pCell->m_nCol_Span);
            }
            cellCursor.insertText(pCell->m_strText);
        }
    }
}

void XpoRptFillPdf::RowToTxDoc(CRptTemp_Row *pRptTemp_Row, long nRow, QTextTable *table)
{
    QTextCharFormat format;
    QTextBlockFormat blockFormat;
    format.setFontPointSize(10.4);
    blockFormat.setAlignment(Qt::AlignCenter);

    POS pos = pRptTemp_Row->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    long nCol = 0;

    while (pos != NULL)
    {
        pObj = pRptTemp_Row->GetNext(pos);
        if (pObj->GetClassID() != MNGRCLASSID_CRPTTEMP_CELL)
        {
            return ;
        }
        else
        {
            CRptTemp_Cell *pCell = (CRptTemp_Cell*)pObj;

            QTextTableCell cell = table->cellAt(nRow, nCol++);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.setCharFormat(format);
            cellCursor.setBlockFormat(blockFormat);

            QTextTableCellFormat cellFormat;
            cellFormat.setVerticalAlignment(QTextTableCellFormat::AlignMiddle);
            cell.setFormat(cellFormat);
            if(pCell->m_nRow_Span >1 || pCell->m_nCol_Span >1)
            {
                table->mergeCells(nRow, nCol-1, pCell->m_nRow_Span, pCell->m_nCol_Span);
            }
            cellCursor.insertText(pCell->m_strText);
       }
    }
}

void XpoRptFillPdf::GetTitleFontSize(long nLevel, double &nSize)
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
