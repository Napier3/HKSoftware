// XpoRptFillWord.cpp : implementation file

#include "XpoRptFillWord.h"
#include "../../../Module/API/FileApi.h"

#include <QFileInfo>

XpoRptFillWord::XpoRptFillWord()
{
    m_pApp = new QAxObject();
    m_pTestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
}

XpoRptFillWord::~XpoRptFillWord()
{
    delete m_pApp;
    delete m_pTestMacroUiRpt;
}

void XpoRptFillWord::Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile)
{
    OpenXmlRptFile(strXmlFile);

    FillWord(strOutFile);

    SaveAsWord(strOutFile);
    CloseWord();
}

void XpoRptFillWord::OpenXmlRptFile(const CString &strXmlFile)
{
    if (!IsFileExist(strXmlFile))
    {
        return ;
    }
    CTestMacroRptTemplateXmlRWKeys *RptTemplateXmlRWKeys = CTestMacroRptTemplateXmlRWKeys::Create();

    m_pTestMacroUiRpt->OpenXmlFile(strXmlFile, RptTemplateXmlRWKeys->g_pXmlKeys);

    CTestMacroRptTemplateXmlRWKeys::Release();
}

void XpoRptFillWord::FillWord(const CString &strOutFile)
{
    BOOL bRet = m_pApp->setControl("Word.Application");
    if (!bRet)
    {
        bRet = m_pApp->setControl("kwps.Application");// wps
        if(!bRet)
        {
            return ;
        }
    }
    m_pApp->setProperty("Visible", FALSE);
    m_pApp->setProperty("DisplayAlerts", FALSE); //ftt 7.8

    QFileInfo file(strOutFile);
    if(file.exists())
    {
        OpenWord(strOutFile);
    }
    else
    {
        CreateWord();
        //AddText("1.1 ");
    }
    AddTestMacroUiRpt();
}

void XpoRptFillWord::AddTestMacroUiRpt()
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

void XpoRptFillWord::AddItems(CRptTemp_Items *pRptItems)
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

void XpoRptFillWord::AddRptTemplate(CRptTemp_ReportTemplate *pRptTemp)
{
    if (pRptTemp == NULL)
    {
        return ;
    }

    POS pos = pRptTemp->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject *pObj = NULL;
    int titleID = 1;

    while (pos != NULL)
    {
        pObj = pRptTemp->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_TITLE:
            {
                CRptTemp_Title *pTitle = (CRptTemp_Title*)pObj;
                AddTitle(pTitle->m_strText, pTitle->m_nLevel, titleID);
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

void XpoRptFillWord::AddTitle(const CString &strText, long nLevel, int titleID)
{
    QAxObject *selection  = m_pApp->querySubObject("Selection");
    selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphLeft");
    if(!selection)
    {
        return;
    }

    QString strLevel = QString::fromLocal8Bit("标题 ") + QString(QString::number(nLevel));

    QAxObject *range = selection->querySubObject("Range");
    range->dynamicCall("SetStyle(QVariant)", strLevel);
    range->dynamicCall("InsertAfter(const QString&)", QString(QString::number(titleID)));
    range->dynamicCall("InsertAfter(const QString&)", "  ");
    range->dynamicCall("InsertAfter(const QString&)", strText);
    JumpToTheEnd();

    delete selection;
}

void XpoRptFillWord::AddText(const QString &strText)
{
    QAxObject *selection = m_pApp->querySubObject("Selection");
    selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphLeft");
    if(!selection)
    {
        return;
    }
    selection->dynamicCall("TypeText(const QString&)", strText);
    JumpToTheEnd();

    delete selection;
}

void XpoRptFillWord::AddPng(const QString &strFullFileName)
{
    QAxObject *selection = m_pApp->querySubObject("Selection");
    selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");
    QAxObject *inlineShapes = selection->querySubObject("InlineShapes");
    inlineShapes->dynamicCall("AddPicture(const QString&)", strFullFileName);
    JumpToTheEnd();

    delete selection;
}

void XpoRptFillWord::AddTable(CRptTemp_Grid *pRptTemp_Grid)
{
    POS pos = pRptTemp_Grid->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    int rowCount = 0, colCount = 0;

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

    QAxObject *selection = m_pApp->querySubObject("Selection");
    selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");
    QAxObject *range = selection->querySubObject("Range");
    QAxObject *tables = selection->querySubObject("Tables");

    QVariantList params;
    params.append(range->asVariant());
    params.append(rowCount);
    params.append(colCount);
    tables->querySubObject("Add(QAxObject*, int, int, QVariant&, QVariant&)", params);
    QAxObject *table = selection->querySubObject("Tables(int)", 1);
    table->setProperty("Style", "      ");

    QAxObject *borders = table->querySubObject("Borders");
    borders->setProperty("InsideLineStyle", 1);
    borders->setProperty("OutsideLineStyle", 1);

    pos = pRptTemp_Grid->GetHeadPosition();
    int nRow = 1;

    while (pos != NULL)
    {
        pObj = pRptTemp_Grid->GetNext(pos);
        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD)
        {
            CRptTemp_Head *pHead = (CRptTemp_Head*)pObj;
            FillHead(pHead, nRow, table);
            nRow++;
        }
        else
        {
            CRptTemp_Row *pRow = (CRptTemp_Row*)pObj;
            FillRow(pRow, nRow, table);
            nRow++;
        }
    }
    JumpToTheEnd();

    delete selection;
}

void XpoRptFillWord::FillHead(CRptTemp_Head *pRptTemp_Head, int nRow, QAxObject *pTable)
{
    POS pos = pRptTemp_Head->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    int nCol = 1;

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

            if(pCell->m_nRow_Span > 1)
            {
                int nEndRow = nRow + pCell->m_nRow_Span - 1;
                MergeCells(pTable, nRow, nCol, nEndRow, nCol);
            }
            if(pCell->m_nCol_Span > 1)
            {
                int nEndCol = nCol + pCell->m_nCol_Span - 1;
                MergeCells(pTable, nRow, nCol, nRow, nEndCol);
            }

            if(pCell->m_strText != "")
            {
                SetCellText(pTable, nRow, nCol, pCell->m_strText);
            }
            nCol = nCol + 2 - pCell->m_nCol_Span;
        }
    }
}

void XpoRptFillWord::FillRow(CRptTemp_Row *pRptTemp_Row, int nRow, QAxObject *pTable)
{
    POS pos = pRptTemp_Row->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    int nCol = 1;

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

            if(pCell->m_nRow_Span > 1)
            {
                int nEndRow = nRow + pCell->m_nRow_Span - 1;
                MergeCells(pTable, nRow, nCol, nEndRow, nCol);
            }
            if(pCell->m_nCol_Span > 1)
            {
                int nEndCol = nCol + pCell->m_nCol_Span - 1;
                MergeCells(pTable, nRow, nCol, nRow, nEndCol);
            }

            if(pCell->m_strText != "")
            {
                SetCellText(pTable, nRow, nCol, pCell->m_strText);
            }
            nCol = nCol + 2 - pCell->m_nCol_Span;
        }
    }
}

void XpoRptFillWord::SetCellText(QAxObject *pTable, int nRow, int nCol, const QString &strText)
{
    if (pTable)
    {
        QAxObject *pCell = pTable->querySubObject("Cell(int, int)", nRow, nCol);
        if (pCell)
        {
            QAxObject *pRange = pCell->querySubObject("Range");
            if (pRange)
            {
                pRange->querySubObject("Cells")->setProperty("VerticalAlignment","wdCellAlignVerticalCenter");
                pRange->dynamicCall("SetText(QString)", strText);
            }
        }
        delete pCell;
    }
}

void XpoRptFillWord::MergeCells(QAxObject *pTable, int nStartRow, int nStartCol, int nEndRow, int nEndCol)
{
    if (pTable)
    {
        QAxObject *pStartCell = pTable->querySubObject("Cell(int, int)", nStartRow, nStartCol);
        QAxObject *pEndCell = pTable->querySubObject("Cell(int, int)", nEndRow, nEndCol);
        if (pStartCell || pEndCell)
        {
            pStartCell->dynamicCall("Merge(LPDISPATCH)", pEndCell->asVariant());
        }
        delete pStartCell;
        delete pEndCell;
    }
}

void XpoRptFillWord::OpenWord(const QString &strFullFileName)
{
    QAxObject *docs = m_pApp->querySubObject("Documents");
    QAxObject *doc = docs->querySubObject("Open(const QString&)", strFullFileName);
    if (doc)
    {
        QAxObject *range = doc->querySubObject("Range()");
        range->dynamicCall("Select()");
        range->dynamicCall("Delete()");
        //doc->dynamicCall("Save()");
    }
    delete docs;
    //delete doc;
}

void XpoRptFillWord::CreateWord() //这里可以直接把文件名传过来，给add的新文档命名
{
    QAxObject *docs = m_pApp->querySubObject("Documents");
    docs->dynamicCall("Add()");
    m_pApp->querySubObject("ActiveDocument"); //ftt 7.8

    delete docs;
}

void XpoRptFillWord::SaveAsWord(const CString &strOutFile)
{
    QAxObject *activeDocument = m_pApp->querySubObject("ActiveDocument");
    activeDocument->dynamicCall("SaveAs (const QString&, const QVariant&)", strOutFile, 16);

    delete activeDocument;
}

void XpoRptFillWord::CloseWord()
{
    QAxObject *activeDocument = m_pApp->querySubObject("ActiveDocument");
    activeDocument->dynamicCall("Close (boolean)", true);
    m_pApp->dynamicCall("Quit(void)");
    delete activeDocument;
}

void XpoRptFillWord::JumpToTheEnd()
{
    QAxObject *selection = m_pApp->querySubObject("Selection");
    QVariantList params;
    params.append(6);
    params.append(0);
    selection->dynamicCall("EndOf(QVariant&, QVariant&)", params).toInt();
    selection->dynamicCall("TypeParagraph(void)");

    delete selection;
}
