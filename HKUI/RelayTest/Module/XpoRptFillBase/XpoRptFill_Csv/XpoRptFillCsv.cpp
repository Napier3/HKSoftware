// XpoRptFillCsv.cpp : implementation file

#include "XpoRptFillCsv.h"
#include "../../../Module/API/FileApi.h"

#include <QTextStream>
#pragma execution_character_set("utf-8")

XpoRptFillCsv::XpoRptFillCsv()
{
    m_pTestMacroUiRpt = new CRptTemp_TestMacroUiRpt();
}

XpoRptFillCsv::~XpoRptFillCsv()
{
    delete m_pTestMacroUiRpt;
}

void XpoRptFillCsv::Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile)
{
    OpenXmlRptFile(strXmlFile);
    TestMacroUiRptToList(m_pTestMacroUiRpt);
    SaveAsCsv(strOutFile);
}

void XpoRptFillCsv::OpenXmlRptFile(const CString &strXmlFile)
{
    if (!IsFileExist(strXmlFile))
    {
        return ;
    }
    CTestMacroRptTemplateXmlRWKeys *RptTemplateXmlRWKeys = CTestMacroRptTemplateXmlRWKeys::Create();

    m_pTestMacroUiRpt->OpenXmlFile(strXmlFile, RptTemplateXmlRWKeys->g_pXmlKeys);

    CTestMacroRptTemplateXmlRWKeys::Release();
}

void XpoRptFillCsv::SaveAsCsv(const CString &strOutFile)
{
    QFile file(strOutFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream outStream(&file);
    for (const QStringList &row : rptData)
    {
        QString line = row.join(",");
        outStream << line << "\n"; //写入一行，并在末尾添加换行符
    }
    file.close();
}

void XpoRptFillCsv::TestMacroUiRptToList(CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt)
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
            RptItemsToList(pRptTemp_Items);
        }
            break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToList(pRptTemp_ReportTemplate);
        }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillCsv::RptItemsToList(CRptTemp_Items *pRptTemp_Items)
{
    if (pRptTemp_Items == NULL)
    {
        return ;
    }

    TitleToList(pRptTemp_Items->m_strName/*, titleID*/);

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
            RptItemsToList(pRptItems);
        }
            break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            CRptTemp_ReportTemplate *pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToList(pRptTemp_ReportTemplate);
        }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillCsv::RptTemplateToList(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate)
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
                TitleToList(pTitle->m_strText/*, titleID*/);
                //titleID++;
            }
            break;
        case MNGRCLASSID_CRPTTEMP_TEXT:
            {
                CRptTemp_Text *pText = (CRptTemp_Text*)pObj;
                TextToList(pText->m_strText);
            }
            break;
        case MNGRCLASSID_CRPTTEMP_GRID:
            {
                CRptTemp_Grid *pGrid = (CRptTemp_Grid*)pObj;
                GridToList(pGrid);
            }
            break;
        default:
            return ;
        }
    }
}

void XpoRptFillCsv::TitleToList(const CString &strText/*, long titleID*/)
{
    QStringList titleList;
//    QString test = QString::fromUtf8("测试项目");
//    test = test + QString(QString::number(titleID)) + "：";
    titleList << /*test <<*/ strText;
    rptData.append(titleList);
}

void XpoRptFillCsv::TextToList(const CString &strText)
{
    QStringList TextList;
    TextList << strText;
    rptData.append(TextList);
}

void XpoRptFillCsv::GridToList(CRptTemp_Grid *pRptTemp_Grid)
{
    POS pos = pRptTemp_Grid->GetHeadPosition();
    CExBaseObject *pObj = NULL;

    while (pos != NULL)
    {
        pObj = pRptTemp_Grid->GetNext(pos);
        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD)
        {
            CRptTemp_Head *pHead = (CRptTemp_Head*)pObj;
            HeadToList(pHead);
        }
        else
        {
            CRptTemp_Row *pRow = (CRptTemp_Row*)pObj;
            RowToList(pRow);
        }
    }
}

void XpoRptFillCsv::HeadToList(CRptTemp_Head *pRptTemp_Head)
{
    POS pos = pRptTemp_Head->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    QStringList HeadList;

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
            HeadList << pCell->m_strText;
        }
    }
    rptData.append(HeadList);
}

void XpoRptFillCsv::RowToList(CRptTemp_Row *pRptTemp_Row)
{
    POS pos = pRptTemp_Row->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    QStringList RowList;

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
            RowList << pCell->m_strText;
        }
    }
    rptData.append(RowList);
}

