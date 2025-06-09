#include "SttReportView.h"
#include "ui_SttReportView.h"
#include "../../../Module/API/FileApi.h"
#include "../../../../AutoTest/Module/TestMacroRptTemplate/TestMacroRptTemplateGlobal.h"
#include "../../../../Module/System/TickCount32.h"
#include <QUrl>

QSttReportView::QSttReportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSttReportView)
{
    m_pDocument = new QTextDocument();
    m_nCurPosition = 0;

    ui->setupUi(this);
    ui->btnTextEdit->resize(1200, 800);
    this->resize(1300, 800);
    init();
	m_oRptUpdateMsgList.AllocBuffer(500);

	connect(&m_oTimerRptUpdate, SIGNAL(timeout()), this, SLOT(slot_TimerRptUpdate()));
	m_oTimerRptUpdate.start(100);
}

QSttReportView::~QSttReportView()
{
    delete ui;
    delete m_pDocument;
}

void QSttReportView::init()
{
    m_oTitleFormat.setFontWeight(QFont::Bold);
    m_oTitleFormat.setFontFamily("Source Han Sans CN");
    m_oTitleBlockFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);

    m_oTextBlockFormat.setLineHeight(130, QTextBlockFormat::ProportionalHeight);
    //m_oGridBlockFormat.setAlignment(Qt::AlignCenter);

    m_oGridFormat.setFontPointSize(10.4);
    //m_oCellFormat.setFontPointSize(10.4);
    //m_oCellFormat.setVerticalAlignment(QTextTableCellFormat::AlignMiddle);
}

void QSttReportView::TestMacroUiRptToTxDoc(const CString &strItemsPath, CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt)
{
    if (pRptTemp_TestMacroUiRpt == NULL)
    {
        return;
    }

    POS pos = pRptTemp_TestMacroUiRpt->GetHeadPosition();
    CExBaseObject* pObj = NULL;

    while (pos != NULL)
    {
        pObj = pRptTemp_TestMacroUiRpt->GetNext(pos);
        if(pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_ITEMS)
        {
            CRptTemp_Items* pRptTemp_Items = (CRptTemp_Items*)pObj;
            ReportHeadToTxDoc(strItemsPath, pRptTemp_Items);
            break;
        }
    }
}

void QSttReportView::ReportHeadToTxDoc(const CString &strItemsPath, CRptTemp_Items *pRptTemp_Items/*, bool bNewTest*/)
{
    if (pRptTemp_Items == NULL)
    {
        return;
    }

    int nOldVecNum = -1;
    //if(!m_vecNodeInfo.empty())
    {
        for (int i = 0; i < m_vecNodeInfo.GetCount(); ++i)
        {
            if (m_vecNodeInfo[i]->m_strItemsPath == strItemsPath)
            {
                QTextCursor tempCursor(m_pDocument);
                tempCursor.setPosition(m_vecNodeInfo[i]->m_nStartPos);
                tempCursor.setPosition(m_vecNodeInfo[i]->m_nEndPos, QTextCursor::KeepAnchor);
                tempCursor.removeSelectedText();
                m_nCurPosition = tempCursor.position();

                nOldVecNum = i; //获取要替换的Node在vec中的下标
                break;
            }
        }
    }
    QTextCursor cursor(m_pDocument);
    cursor.setPosition(m_nCurPosition);

    int startPos = cursor.position();

    //TitleToTxDoc(pRptTemp_Items->m_strName, pRptTemp_Items->m_ntitle_level/*, titleID*/);

    POS pos = pRptTemp_Items->GetHeadPosition();
    CExBaseObject* pObj = NULL;

    while (pos != NULL)
    {
        pObj = pRptTemp_Items->GetNext(pos);
        if(pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
        {
            CRptTemp_ReportTemplate* pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToTxDoc(pRptTemp_ReportTemplate);
        }
    }

    if(nOldVecNum == -1) //新增items
    {
        CStcNodeInfo *itemsNode = new CStcNodeInfo();
        itemsNode->m_strItemsPath = strItemsPath;
        itemsNode->m_nStartPos = startPos;
        itemsNode->m_nEndPos = m_nCurPosition;
        m_vecNodeInfo.AddTail(itemsNode);
    }
    else //更新已存在的items
    {
        m_vecNodeInfo[nOldVecNum]->m_nStartPos = startPos;
        m_vecNodeInfo[nOldVecNum]->m_nEndPos = m_nCurPosition;

        //更新某个items后，需要同时更新后续vec中所有items坐标
        UpdatePosAfterChangeItems(nOldVecNum);

        cursor.movePosition(QTextCursor::End);
        m_nCurPosition = cursor.position();
    }    

    ui->btnTextEdit->setDocument(m_pDocument);
}

//ftt 2024.10.22 CSttItems *pRootNode
void QSttReportView::RptItemsToTxDoc(const CString &strItemsPath, CRptTemp_Items* pRptTemp_Items)
{
    if (pRptTemp_Items == NULL)
    {
        return;
    }

    int nOldVecNum = -1;
    //if(!m_vecNodeInfo.empty())
    {
        for (int i = 0; i < m_vecNodeInfo.GetCount(); ++i)
        {
            if (m_vecNodeInfo[i]->m_strItemsPath == strItemsPath)
            {
                QTextCursor tempCursor(m_pDocument);
                tempCursor.setPosition(m_vecNodeInfo[i]->m_nStartPos);
                tempCursor.setPosition(m_vecNodeInfo[i]->m_nEndPos, QTextCursor::KeepAnchor);
                tempCursor.removeSelectedText();
                m_nCurPosition = tempCursor.position();

                nOldVecNum = i; //获取要替换的Node在vec中的下标
                break;
            }
        }
    }
    QTextCursor cursor(m_pDocument);
    cursor.setPosition(m_nCurPosition);

    int startPos = cursor.position();

    if(pRptTemp_Items->m_nRpt_Title == 1)
    {
        TitleToTxDoc(pRptTemp_Items->m_strName, pRptTemp_Items->m_ntitle_level/*, titleID*/);
    }

    POS pos = pRptTemp_Items->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject* pObj = NULL;

    while (pos != NULL)
    {
        pObj = pRptTemp_Items->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_ITEMS:
        {
            CRptTemp_Items* pRptItems = (CRptTemp_Items*)pObj;
            RptItemsToTxDoc(strItemsPath, pRptItems);
        }
        break;
        case MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE:
        {
            CRptTemp_ReportTemplate* pRptTemp_ReportTemplate = (CRptTemp_ReportTemplate*)pObj;
            RptTemplateToTxDoc(pRptTemp_ReportTemplate);
        }
        break;
        default:
            return;
        }
    }

    if(nOldVecNum == -1) //新增items
    {
        CStcNodeInfo *itemsNode = new CStcNodeInfo();
        itemsNode->m_strItemsPath = strItemsPath;
        itemsNode->m_nStartPos = startPos;
        itemsNode->m_nEndPos = m_nCurPosition;
        m_vecNodeInfo.AddTail(itemsNode);
    }
    else //更新某个items后，需要同时更新后续vec中所有items坐标
    {
        m_vecNodeInfo[nOldVecNum]->m_nStartPos = startPos;
        m_vecNodeInfo[nOldVecNum]->m_nEndPos = m_nCurPosition;

        //更新某个items后，需要同时更新后续vec中所有items坐标
        UpdatePosAfterChangeItems(nOldVecNum);

        cursor.movePosition(QTextCursor::End);
        m_nCurPosition = cursor.position();
    }

    ui->btnTextEdit->setDocument(m_pDocument);
}

void QSttReportView::RptTemplateToTxDoc(CRptTemp_ReportTemplate* pRptTemp_ReportTemplate)
{
    if (pRptTemp_ReportTemplate == NULL)
    {
        return;
    }

    POS pos = pRptTemp_ReportTemplate->GetHeadPosition();
    UINT nClassID = 0;
    CExBaseObject* pObj = NULL;
    //long titleID = 1;

    while (pos != NULL)
    {
        pObj = pRptTemp_ReportTemplate->GetNext(pos);
        nClassID = pObj->GetClassID();

        switch (nClassID)
        {
        case MNGRCLASSID_CRPTTEMP_TITLE:
        {
            CRptTemp_Title* pTitle = (CRptTemp_Title*)pObj;
            TitleToTxDoc(pTitle->m_strText, pTitle->m_nLevel/*, titleID*/);
            //titleID++;
        }
        break;
        case MNGRCLASSID_CRPTTEMP_TEXT:
        {
            CRptTemp_Text* pText = (CRptTemp_Text*)pObj;
            TextToTxDoc(pText->m_strText, pText->m_fSize, pText->m_nBold, pText->m_strFont);
        }
        break;
        case MNGRCLASSID_CRPTTEMP_GRID:
        {
            CRptTemp_Grid* pGrid = (CRptTemp_Grid*)pObj;
            GridToTxDoc(pGrid);
        }
        break;
        case MNGRCLASSID_CRPTTEMP_PNG:
        {
            CRptTemp_Png* pPng = (CRptTemp_Png*)pObj;
            PngToTxDoc(pPng->m_strPngPath);
        }
        break;
        default:
            return;
        }
    }
}

void QSttReportView::TitleToTxDoc(const CString& strText, long nLevel/*, long titleID*/)
{
    QTextCursor cursor(m_pDocument);

    double nSize;
    GetTitleFontSize(nLevel, nSize);
    m_oTitleFormat.setFontPointSize(nSize);

    cursor.setPosition(m_nCurPosition);
    cursor.setCharFormat(m_oTitleFormat);
    cursor.setBlockFormat(m_oTitleBlockFormat);

    //cursor.insertText(QString(QString::number(titleID)));
    //cursor.insertText("  ");
    cursor.insertText(strText);
    cursor.insertBlock();

    //cursor.setCharFormat(m_oTitleFormat);
    //cursor.setBlockFormat(m_oTitleBlockFormat);
    m_nCurPosition = cursor.position();
}

void QSttReportView::TextToTxDoc(const CString& strText, float nSize, long bBold, CString strFontFamily)
{
    QTextCursor cursor(m_pDocument);

    if (strFontFamily == "")
    {
        strFontFamily = "Source Han Sans CN";
    }
    m_oTextFormat.setFontFamily(strFontFamily);
    m_oTextFormat.setFontPointSize(nSize);
    if (bBold)
    {
        m_oTextFormat.setFontWeight(QFont::Bold);
    }
    else
    {
        m_oTextFormat.setFontWeight(QFont::Normal);
    }
    cursor.setPosition(m_nCurPosition);
    cursor.setCharFormat(m_oTextFormat);
    cursor.setBlockFormat(m_oTextBlockFormat);

    cursor.insertText(strText);
    cursor.insertBlock();
    m_nCurPosition = cursor.position();
}

void QSttReportView::PngToTxDoc(const CString& strPath)
{
    if (!QFile::exists(strPath))
    {
        return;
    }
    QImage image(strPath);
    if (image.isNull())
    {
        return;
    }

    image = image.scaled(500, image.height() * 500 / image.width(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    buffer.close();

    QTextCursor cursor(m_pDocument);
    cursor.setPosition(m_nCurPosition);

    QTextImageFormat m_oTextFormat;
    m_oTextFormat.setName("image");
	QUrl oUrl;
	oUrl = (m_oTextFormat.name());
    m_pDocument->addResource(QTextDocument::ImageResource, oUrl, buffer.buffer());
    cursor.insertImage(m_oTextFormat);
    cursor.insertBlock();
    m_nCurPosition = cursor.position();
}

void QSttReportView::GridToTxDoc(CRptTemp_Grid* pRptTemp_Grid)
{
    POS pos = pRptTemp_Grid->GetHeadPosition();
    CExBaseObject* pObj = NULL;
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
    CRptTemp_Head* pHead = (CRptTemp_Head*)pRptTemp_Grid->GetNext(pos);
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
    cursor.setPosition(m_nCurPosition);
    QTextTableFormat tableFormat;
    QVector<QTextLength> columnWidths;

    for (int i = 0; i < colCount; i++)
    {
        columnWidths << QTextLength(QTextLength::FixedLength, 900 / colCount);
    }

    tableFormat.setColumnWidthConstraints(columnWidths);
    QTextTable* table = cursor.insertTable(rowCount, colCount, tableFormat);
    if(!table)
        return;

    pos = pRptTemp_Grid->GetHeadPosition();
    long nRow = 0;

    //QTextCursor cellCursor = table->firstCursorPosition();
    //cellCursor.setCharFormat(m_oCellFormat);
    //cellCursor.setBlockFormat(m_oGridBlockFormat);

    while (pos != NULL)
    {
        pObj = pRptTemp_Grid->GetNext(pos);

        if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_HEAD)
        {
            CRptTemp_Head* pHead = (CRptTemp_Head*)pObj;
            HeadToTxDoc(pHead, nRow, table);
            nRow++;
        }
        else
        {
            CRptTemp_Row* pRow = (CRptTemp_Row*)pObj;
            RowToTxDoc(pRow, nRow, table);
            nRow++;
        }
    }

    cursor = table->lastCursorPosition();
    cursor.setPosition(cursor.position() + 1);
    cursor.insertBlock();
    cursor.insertBlock();
    m_nCurPosition = cursor.position();
}

void QSttReportView::HeadToTxDoc(CRptTemp_Head* pRptTemp_Head, long nRow, QTextTable* table)
{
    POS pos = pRptTemp_Head->GetHeadPosition();
    CExBaseObject* pObj = NULL;
    long nCol = 0;

    while (pos != NULL)
    {
        pObj = pRptTemp_Head->GetNext(pos);
        if (pObj->GetClassID() != MNGRCLASSID_CRPTTEMP_CELL)
        {
            return;
        }
        else
        {
            CRptTemp_Cell* pCell = (CRptTemp_Cell*)pObj;

            QTextTableCell cell = table->cellAt(nRow, nCol++);
            QTextCursor cellCursor = cell.firstCursorPosition();

            //cellCursor.setBlockFormat(m_oGridBlockFormat); //水平居中
            //cell.setFormat(m_oCellFormat); //垂直居中

            if (pCell->m_nRow_Span > 1 || pCell->m_nCol_Span > 1)
            {
                table->mergeCells(nRow, nCol - 1, pCell->m_nRow_Span, pCell->m_nCol_Span);
            }

            cellCursor.insertText(pCell->m_strText, m_oGridFormat);
        }
    }
}

void QSttReportView::RowToTxDoc(CRptTemp_Row* pRptTemp_Row, long nRow, QTextTable* table)
{
    POS pos = pRptTemp_Row->GetHeadPosition();
    CExBaseObject* pObj = NULL;
    long nCol = 0;

    while (pos != NULL)
    {
        pObj = pRptTemp_Row->GetNext(pos);

        if (pObj->GetClassID() != MNGRCLASSID_CRPTTEMP_CELL)
        {
            continue;
        }

        CRptTemp_Cell* pCell = (CRptTemp_Cell*)pObj;
        QTextTableCell cell = table->cellAt(nRow, nCol++);
        QTextCursor cellCursor = cell.firstCursorPosition();

        //cellCursor.setBlockFormat(m_oGridBlockFormat); //水平居中
        //cell.setFormat(m_oCellFormat); //垂直居中

        if (pCell->m_nRow_Span > 1 || pCell->m_nCol_Span > 1)
        {
            table->mergeCells(nRow, nCol - 1, pCell->m_nRow_Span, pCell->m_nCol_Span);
        }

        cellCursor.insertText(pCell->m_strText, m_oGridFormat);
    }
}

void QSttReportView::GetTitleFontSize(long nLevel, double& nSize)
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

void QSttReportView::UpdatePosAfterChangeItems(int nStartNum)
{
    for(int i = nStartNum; i < m_vecNodeInfo.GetCount()-1; ++i)
    {
        int nlength = m_vecNodeInfo[i+1]->m_nEndPos - m_vecNodeInfo[i+1]->m_nStartPos;
        m_vecNodeInfo[i+1]->m_nStartPos = m_vecNodeInfo[i]->m_nEndPos;
        m_vecNodeInfo[i+1]->m_nEndPos = m_vecNodeInfo[i+1]->m_nStartPos + nlength;
    }
}

void QSttReportView::UpdatePosAfterDeleteItems(int nStartNum, int nStartPos)
{
    if(nStartNum <= m_vecNodeInfo.GetCount()-1)
    {
        int nlength = m_vecNodeInfo[nStartNum]->m_nEndPos - m_vecNodeInfo[nStartNum]->m_nStartPos;
        m_vecNodeInfo[nStartNum]->m_nStartPos = nStartPos;
        m_vecNodeInfo[nStartNum]->m_nEndPos = m_vecNodeInfo[nStartNum]->m_nStartPos + nlength;
    }

    for(int i = nStartNum+1; i < m_vecNodeInfo.GetCount(); ++i)
    {
        int nlength = m_vecNodeInfo[i]->m_nEndPos - m_vecNodeInfo[i]->m_nStartPos;
        m_vecNodeInfo[i]->m_nStartPos = m_vecNodeInfo[i-1]->m_nEndPos;
        m_vecNodeInfo[i]->m_nEndPos = m_vecNodeInfo[i]->m_nStartPos + nlength;
    }

}

void QSttReportView::slot_AddUpdateReportQT(QString strItemsPath, CExBaseObject *pObj)
{
	Stt_RptUpdateMsg *pSttRptUpdateMsg = new Stt_RptUpdateMsg;
    pSttRptUpdateMsg->m_strItemsPath = strItemsPath;
	pSttRptUpdateMsg->m_pObj = pObj;
    //pSttRptUpdateMsg->m_bIsClearAllReports = bIsClearAllReports;
	pSttRptUpdateMsg->m_nMsgType = STT_RPT_UPDATE_TYPE_AddUpdate;
	m_oRptUpdateMsgList.Add(pSttRptUpdateMsg);
// 	return;
//     if(pObj == NULL)
//     {
//         return;
//     }
// 	CTickCount32 oTickCount;
// 	long nIndex = 0;
// 
// 	while (nIndex>1000)
// 	{
// 		oTickCount.DoEvents(1);
// 	}
// 	oTickCount.Enter();
//     //判断是否为报告头
//     CString strItemsId = pObj->m_strID;
// 
//     if(strItemsId == "ReportHead")
//     {
// 		ReportHeadToTxDoc(pRootNode, (CRptTemp_Items*)pObj, bIsClearAllReports); //用于新建测试时更新报告头
//     }
//     else
//     {
//         RptItemsToTxDoc(pRootNode, (CRptTemp_Items*)pObj); //更新测试功能节点
//     }
// 
//     delete pObj;
//     pObj = NULL;
// 	long nUseTime = oTickCount.GetTickCountLong();
// 	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("slot_AddUpdateReportQT用时(%ld)."), nUseTime);
}

void QSttReportView::slot_DeleteReportQT(QString strItemsPath)
{
	Stt_RptUpdateMsg *pSttRptUpdateMsg = new Stt_RptUpdateMsg;
    pSttRptUpdateMsg->m_strItemsPath = strItemsPath;
	pSttRptUpdateMsg->m_pObj = NULL;
    //pSttRptUpdateMsg->m_bIsClearAllReports = 0;
	pSttRptUpdateMsg->m_nMsgType = STT_RPT_UPDATE_TYPE_Delete;
	m_oRptUpdateMsgList.Add(pSttRptUpdateMsg);
//     if (pRootNode == NULL)
//     {
//         return;
//     }
// 
//     if(m_vecNodeInfo.empty())
//     {
//         return;
//     }
// 
//     for (int i = 0; i < m_vecNodeInfo.GetCount(); ++i)
//     {
//         if (m_vecNodeInfo[i]->pObj == pRootNode)
//         {
//             int delStartPos = m_vecNodeInfo[i]->startPos;
//             QTextCursor tempCursor(m_pDocument);
//             tempCursor.setPosition(m_vecNodeInfo[i]->startPos);
//             tempCursor.setPosition(m_vecNodeInfo[i]->endPos, QTextCursor::KeepAnchor);
//             tempCursor.removeSelectedText();
//             tempCursor.movePosition(QTextCursor::End);
//             m_nCurPosition = tempCursor.position();
// 
//             m_vecNodeInfo.erase(m_vecNodeInfo.begin() + i);
// 
//             //删除某个items后，后面的所有items坐标需前移
//             UpdatePosAfterDeleteItems(i, delStartPos);
//             break;
//         }
//     }
}

void QSttReportView::slot_ClearAllReportsQT()
{
    if(!m_pDocument->isEmpty())
    {
        QTextCursor cursor(m_pDocument);
        cursor.select(QTextCursor::Document);
        cursor.removeSelectedText();
        cursor.setPosition(0);
        m_nCurPosition = cursor.position();
    }

    //if(!m_vecNodeInfo.empty())
    {
        m_vecNodeInfo.DeleteAll();
    }
}

void QSttReportView::AddUpdateReportQT(const QString &strItemsPath, CExBaseObject *pObj)
{
	//	return;
	if (pObj == NULL)
	{
		return;
	}
	CTickCount32 oTickCount;
// 	long nIndex = 0;
// 
// 	while (nIndex > 1000)
// 	{
// 		oTickCount.DoEvents(1);
// 	}
 	oTickCount.Enter();

    //2024.10.25 ftt 报告头根节点更改为TestMacroUiRpt
    if (pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_TESTMACROUIRPT)
    {
        TestMacroUiRptToTxDoc(strItemsPath, (CRptTemp_TestMacroUiRpt*)pObj); //用于新建测试时更新报告头
    }
    else if(pObj->GetClassID() == MNGRCLASSID_CRPTTEMP_ITEMS)
    {
        RptItemsToTxDoc(strItemsPath, (CRptTemp_Items*)pObj); //更新测试功能节点
    }
    //delete 2024.10.25之前的处理方法
//	//判断是否为报告头
//    CString strItemsId = pObj->m_strID;

//	if (strItemsId == "ReportHead")
//	{
//        ReportHeadToTxDoc(strItemsPath, (CRptTemp_Items*)pObj); //用于新建测试时更新报告头
//	}
//	else
//	{
//        RptItemsToTxDoc(strItemsPath, (CRptTemp_Items*)pObj); //更新测试功能节点
//	}

	delete pObj;
	pObj = NULL;
	long nUseTime = oTickCount.GetTickCountLong();
	//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("slot_AddUpdateReportQT用时(%ld)."), nUseTime);
}

void QSttReportView::DeleteReportQT(const QString &strItemsPath)
{
    if (strItemsPath.isEmpty())
	{
		return;
	}

	if (m_vecNodeInfo.GetCount() == 0)
	{
		return;
	}

	for (int i = 0; i < m_vecNodeInfo.GetCount(); ++i)
	{
        if (m_vecNodeInfo[i]->m_strItemsPath == strItemsPath)
		{
            int delStartPos = m_vecNodeInfo[i]->m_nStartPos;
			QTextCursor tempCursor(m_pDocument);
            tempCursor.setPosition(m_vecNodeInfo[i]->m_nStartPos);
            tempCursor.setPosition(m_vecNodeInfo[i]->m_nEndPos, QTextCursor::KeepAnchor);
			tempCursor.removeSelectedText();
			tempCursor.movePosition(QTextCursor::End);
			m_nCurPosition = tempCursor.position();

			m_vecNodeInfo.DeleteAtIndex(i);

			//删除某个items后，后面的所有items坐标需前移
			UpdatePosAfterDeleteItems(i, delStartPos);
			break;
		}
	}
}

void QSttReportView::slot_TimerRptUpdate()
{
	if (m_oRptUpdateMsgList.CanRead())
	{
		Stt_RptUpdateMsg *pSttRptUpdateMsg = m_oRptUpdateMsgList.Read();

		if (pSttRptUpdateMsg->m_nMsgType == STT_RPT_UPDATE_TYPE_AddUpdate)
		{
            AddUpdateReportQT(pSttRptUpdateMsg->m_strItemsPath, pSttRptUpdateMsg->m_pObj);
		}
		else if (pSttRptUpdateMsg->m_nMsgType == STT_RPT_UPDATE_TYPE_Delete)
		{
            DeleteReportQT(pSttRptUpdateMsg->m_strItemsPath);
		}

		delete pSttRptUpdateMsg;
	}
}

