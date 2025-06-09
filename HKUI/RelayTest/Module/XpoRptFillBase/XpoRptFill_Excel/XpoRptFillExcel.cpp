// XpoRptFillExcel.cpp : implementation file

#include "XpoRptFillExcel.h"
#include "../../../Module/API/FileApi.h"

#include <QFileInfo>
#pragma execution_character_set("utf-8")

XpoRptFillExcel::XpoRptFillExcel()
{
    m_pApp = new QAxObject();
    m_pTestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
}

XpoRptFillExcel::~XpoRptFillExcel()
{
    delete m_pApp;
    delete m_pTestMacroUiRpt;
}

void XpoRptFillExcel::Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile)
{
    OpenXmlRptFile(strXmlFile);
    FillExcel(strOutFile);

    MergeCells();
    BorderCells();

    SaveAsExcel(strOutFile);
    CloseExcel();
}

void XpoRptFillExcel::OpenXmlRptFile(const CString &strXmlFile)
{
    if (!IsFileExist(strXmlFile))
    {
        return ;
    }
    CTestMacroRptTemplateXmlRWKeys *RptTemplateXmlRWKeys = CTestMacroRptTemplateXmlRWKeys::Create();

    m_pTestMacroUiRpt->OpenXmlFile(strXmlFile, RptTemplateXmlRWKeys->g_pXmlKeys);

    CTestMacroRptTemplateXmlRWKeys::Release();
}

void XpoRptFillExcel::FillExcel(const CString &strOutFile)
{
    BOOL bRet = m_pApp->setControl("Excel.Application");
    if (!bRet)
    {
        bRet = m_pApp->setControl("kwps.Application");//      wps
        if(!bRet)
        {
            return ;
        }
    }
    m_pApp->setProperty("Visible", FALSE); //FALSE
    m_pApp->setProperty("DisplayAlerts", FALSE); //ftt 7.8

    QFileInfo file(strOutFile);
    if(file.exists())
    {
        OpenExcel(strOutFile); //ftt 7.15 这里需要更改，重新新建一个excel替代原来的
    }
    else
    {
        CreateExcel();
    }
    AddTestMacroUiRpt();
}

void XpoRptFillExcel::AddTestMacroUiRpt()
{
    if (m_pTestMacroUiRpt == NULL)
    {
        return ;
    }

    POS pos = m_pTestMacroUiRpt->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;

    while (pos != NULL)
    {
        pObj = m_pTestMacroUiRpt->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_ITEMS:
        {
            CRptTemp_Items *pRptTemp_Items = (CRptTemp_Items*)pObj;
            AddItems(pRptTemp_Items);
        }
            break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            CRptTemp_ReportTemplate *pRptTemp = (CRptTemp_ReportTemplate*)pObj;
            AddRptTemplate(pRptTemp);
        }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillExcel::AddItems(CRptTemp_Items *pRptItems)
{
    if (pRptItems == NULL)
    {
        return ;
    }

    //ftt !!这里需要输出Items结点的文本!!

    POS pos = pRptItems->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;

    while (pos != NULL)
    {
        pObj = pRptItems->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_ITEMS:
        {
            CRptTemp_Items *pItems = (CRptTemp_Items*)pObj;
            AddItems(pItems);
        }
            break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            CRptTemp_ReportTemplate *pRptTemp = (CRptTemp_ReportTemplate*)pObj;
            AddRptTemplate(pRptTemp);
        }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillExcel::AddRptTemplate(CRptTemp_ReportTemplate *m_pRptTemp)
{
    if (m_pRptTemp == NULL)
    {
        return ;
    }

    POS pos = m_pRptTemp->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;
    int titleID = 1;

    while (pos != NULL)
    {
        pObj = m_pRptTemp->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_TITLE:
            {
                CRptTemp_Title *pTitle = (CRptTemp_Title*)pObj;
                AddTitle(pTitle->m_strText, titleID);
                titleID++;
            }
            break;
        case MNGRCLASSID_CRPTTEMP_TEXT:
            {
                CRptTemp_Text *pText = (CRptTemp_Text*)pObj;
                AddText(pText->m_strText);
            }
            break;
        case MNGRCLASSID_CRPTTEMP_GRID:
            {
                CRptTemp_Grid *pGrid = (CRptTemp_Grid*)pObj;
                AddTable(pGrid);
            }
            break;
        case MNGRCLASSID_CRPTTEMP_PNG:
            {
                CRptTemp_Png *pPng = (CRptTemp_Png*)pObj;
                AddPng(pPng->m_strPngPath);
            }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillExcel::AddTitle(const CString &strText, int titleID)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");
    //QAxObject *pWorkSheet = worksheets->querySubObject("Item(int)", 1); //获取sheet的另一种方式，使用索引（索引从1开始）

    QAxObject *selection = m_pApp->querySubObject("Selection");
    int currentRow = selection->property("Row").toInt();
    int currentColumn = selection->property("Column").toInt();

    //遇到Title时，表示新的测试项目，隔一行再输出
    if(titleID > 1)
    {
        currentRow++;
    }

    QString test = QString::fromUtf8("测试项目");
    test = test + QString(QString::number(titleID)) + "：";
    QAxObject *currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, currentColumn);
    currentCell->dynamicCall("SetValue(const QString&)", test);

    currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, currentColumn + 1);    
    currentCell->dynamicCall("SetValue(const QString&)", strText);

    QAxObject *nextRowCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow + 1, 1);
    nextRowCell->querySubObject("Select");

    delete pWorkBook;
    delete selection;
}

void XpoRptFillExcel::AddText(const QString &strText)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QAxObject *selection = m_pApp->querySubObject("Selection");
    int currentRow = selection->property("Row").toInt();
    int currentColumn = selection->property("Column").toInt();

    QAxObject *currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, currentColumn);
    currentCell->dynamicCall("SetValue(const QString&)", strText);

    QAxObject *nextRowCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow + 1, 1);
    nextRowCell->querySubObject("Select");

    delete pWorkBook;
    delete selection;
}

void XpoRptFillExcel::AddPng(const QString &strFullFileName)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QAxObject *selection = m_pApp->querySubObject("Selection");
    int currentRow = selection->property("Row").toInt();
    int currentColumn = selection->property("Column").toInt();

    QAxObject *currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, currentColumn);

    //QString strPngPath = "D://FTTWork//Qt//QTextDocumentToPdf//image.png";
    QImage image(strFullFileName); //strPngPath
    //这个大小是保证打印预览能看到完整图片的情况下的最大尺寸
    image = image.scaled(image.width() * 280 / image.height(), 280, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QAxObject *shapes = pWorkSheet->querySubObject("Shapes");   //插入图片
    shapes->dynamicCall("AddPicture(QString&, bool, bool, double, double, double, double)",
       strFullFileName, true, true, currentCell->property("Left"), currentCell->property("Top"), image.width(), image.height());

    //用固定尺寸的图片大小：280磅，所以这里下次输入需要隔固定的行数：21
    QAxObject *nextRowCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow + 21, 1);
    nextRowCell->querySubObject("Select");

    delete pWorkBook;
    delete selection;
}

void XpoRptFillExcel::AddTable(CRptTemp_Grid *pRptTemp_Grid)
{
    //直接这这里遍历两遍，得到表格宽高
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

    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QAxObject *selection = m_pApp->querySubObject("Selection");
    int currentRow = selection->property("Row").toInt();
    int currentColumn = selection->property("Column").toInt();

    stcBordersRange borderRange;
    borderRange.startRow = currentRow;
    borderRange.startCol = currentColumn;
    borderRange.endRow = currentRow + rowCount - 1;
    borderRange.endCol = currentColumn + colCount - 1;
    vecBordersRange.push_back(borderRange);

    pos = pRptTemp_Grid->GetHeadPosition();
    while (pos != NULL)
    {
        pObj = pRptTemp_Grid->GetNext(pos);
        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD)
        {
            CRptTemp_Head *pHead = (CRptTemp_Head*)pObj;
            AddHead(pHead);
        }
        else
        {
            CRptTemp_Row *pRow = (CRptTemp_Row*)pObj;
            AddRow(pRow);
        }
    }

    delete pWorkBook;
    delete selection;
}

void XpoRptFillExcel::AddHead(CRptTemp_Head *pRptTemp_Head)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QAxObject *selection = m_pApp->querySubObject("Selection");
    int currentRow = selection->property("Row").toInt();
    int currentColumn = selection->property("Column").toInt();    

    QAxObject *currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, currentColumn);

    POS pos = pRptTemp_Head->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    stcMergeData data;

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
            currentCell->dynamicCall("SetValue(const QString&)", pCell->m_strText);

            if(pCell->m_nRow_Span > 1 || pCell->m_nCol_Span > 1)
            {                
                data.curRow = currentRow;
                data.curCol = currentColumn;
                data.rowSpan = pCell->m_nRow_Span;
                data.colSpan = pCell->m_nCol_Span;
                vecMergeData.push_back(data);
            }
            QAxObject *column = pWorkSheet->querySubObject("Columns(int)", currentColumn); //1表示第一列
            column->setProperty("ColumnWidth", 13);

            currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, ++currentColumn);
            currentCell->querySubObject("Select");
            delete column;
        }
    }
    QAxObject *nextRowCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow + 1, 1);
    nextRowCell->querySubObject("Select");

    delete pWorkBook;
    delete selection;
}

void XpoRptFillExcel::AddRow(CRptTemp_Row *pRptTemp_Row)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QAxObject *selection = m_pApp->querySubObject("Selection");
    int currentRow = selection->property("Row").toInt();
    int currentColumn = selection->property("Column").toInt();

    QAxObject *currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, currentColumn);

    POS pos = pRptTemp_Row->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    stcMergeData data;

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
            currentCell->dynamicCall("SetValue(const QString&)", pCell->m_strText);

            if(pCell->m_nRow_Span > 1 || pCell->m_nCol_Span > 1)
            {               
                data.curRow = currentRow;
                data.curCol = currentColumn;
                data.rowSpan = pCell->m_nRow_Span;
                data.colSpan = pCell->m_nCol_Span;
                vecMergeData.push_back(data);
            }            
            currentCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow, ++currentColumn);
            currentCell->querySubObject("Select");
        }
    }
    QAxObject *nextRowCell = pWorkSheet->querySubObject("Cells(int,int)", currentRow + 1, 1);
    nextRowCell->querySubObject("Select");

    delete pWorkBook;
    delete selection;
}

void XpoRptFillExcel::MergeCells()
{
    stcMergeData data;
    for(int i = 0; i < vecMergeData.size(); i++)
    {
        data = vecMergeData[i];
        MergeCell(data.curRow, data.curCol, data.rowSpan, data.colSpan);
    }
}

void XpoRptFillExcel::MergeCell(int curRow, int curCol, long rowSpan, long colSpan)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QString cellMerge;
    cellMerge.append(QChar('A' + curCol - 1));
    cellMerge.append(QString::number(curRow));
    cellMerge.append(":");
    cellMerge.append(QChar('A' + curCol + colSpan - 2));
    cellMerge.append(QString::number(curRow + rowSpan - 1));
    QAxObject *range = pWorkSheet->querySubObject("Range(const QString&)", cellMerge);
    range->setProperty("WrapText", true);
    range->setProperty("MergeCells", true);
    range->setProperty("HorizontalAlignment", -4108); //xlCenter
    range->setProperty("VerticalAlignment", -4108); //xlCenter

    delete pWorkBook;
}

void XpoRptFillExcel::BorderCells()
{
    stcBordersRange range;
    for(int i = 0; i < vecBordersRange.size(); i++)
    {
        range = vecBordersRange[i];
        BorderCell(range.startRow, range.startCol, range.endRow, range.endCol);
    }
}

void XpoRptFillExcel::BorderCell(int startRow, int startCol, int endRow, int endCol)
{
    //获取选中的区域
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    QString rangeString;
    rangeString.append(QChar('A' + startCol - 1));
    rangeString.append(QString::number(startRow));
    rangeString.append(":");
    rangeString.append(QChar('A' + endCol - 1));
    rangeString.append(QString::number(endRow));
    QAxObject *range = pWorkSheet->querySubObject("Range(const QString&)", rangeString);

    range->dynamicCall("Select()");
    QAxObject *borders = range->querySubObject("Borders");
    borders->dynamicCall("LineStyle", 1); // xlContinuous
    borders->dynamicCall("Weight", 2); // xlThin
    borders->dynamicCall("ColorIndex", 0);

    delete pWorkBook;
}

//2024.9.18 原本excel中的图片没有删掉，需要手动delete图片
void XpoRptFillExcel::OpenExcel(const QString &strOutFile)
{
    QAxObject *pWorkBooks = m_pApp->querySubObject("Workbooks");
    pWorkBooks->dynamicCall("Open(const QVariant&)", strOutFile);

    QAxObject *pWorkSheet = m_pApp->querySubObject("ActiveSheet");
    QAxObject *usedRange = pWorkSheet->querySubObject("UsedRange");
    usedRange->dynamicCall("Clear()");

    //获取Shapes集合以删除其中的图片 9.18
    QAxObject *shapes = pWorkSheet->querySubObject("Shapes");
    int shapeCount = shapes->property("Count").toInt();
    for (int i = shapeCount; i >= 1; --i)
    {
        QAxObject *shape = shapes->querySubObject("Item(int)", i);
        shape->dynamicCall("Delete()");
    }
    //pWorkBooks->dynamicCall("Save()");
    QAxObject *nextRowCell = pWorkSheet->querySubObject("Cells(int,int)", 1, 1);
    nextRowCell->querySubObject("Select");

    delete pWorkBooks;
    delete usedRange;
}

void XpoRptFillExcel::CreateExcel()
{
    QAxObject *pWorkBooks = m_pApp->querySubObject("WorkBooks");
    pWorkBooks->dynamicCall("Add");

    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    //QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");

    delete pWorkBooks;
    delete pWorkBook;
}

void XpoRptFillExcel::SaveAsExcel(const CString &strOutFile)
{
    QAxObject *pWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    QAxObject *pWorkSheet = pWorkBook->querySubObject("ActiveSheet");
    pWorkSheet->querySubObject("Range(\"A1\")")->dynamicCall("Select()");
    pWorkBook->dynamicCall("SaveAs(const QString&)", strOutFile);

    delete pWorkBook;
}

void XpoRptFillExcel::CloseExcel()
{
    QAxObject *activeWorkBook = m_pApp->querySubObject("ActiveWorkBook");
    activeWorkBook->dynamicCall("Close()");
    m_pApp->dynamicCall("Quit()");

    delete activeWorkBook;
}

