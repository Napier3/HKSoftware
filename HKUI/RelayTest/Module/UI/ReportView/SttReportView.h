#pragma once

#include "../../SttCmd/GuideBook/SttItems.h"
#include "../../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_TestMacroUiRpt.h"
#include "../../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_Png.h"
#include "../../../../Module/MemBuffer/TxRingPtrBuffer.h"

#include <QWidget>
#include <QTextTable>
#include <QBuffer>
#include <QTimer>
#define STT_RPT_UPDATE_TYPE_NULL                        0
#define STT_RPT_UPDATE_TYPE_AddUpdate                   1
#define STT_RPT_UPDATE_TYPE_Delete                      2

typedef struct stt_rpt_update_msg
{
    //CSttItems *m_pRootNode; //ftt 2024.10.22
    CString m_strItemsPath;     //ftt 2024.10.22
	CExBaseObject *m_pObj;
	bool m_bIsClearAllReports;
	long m_nMsgType;

	stt_rpt_update_msg(){ init(); }
	virtual ~stt_rpt_update_msg(){}
	void init()
	{
        //m_pRootNode = NULL;  //ftt 2024.10.22
        m_strItemsPath = _T(""); //ftt 2024.10.22
		m_pObj = NULL;
		m_bIsClearAllReports = 0;
		m_nMsgType = STT_RPT_UPDATE_TYPE_NULL;
	}
}Stt_RptUpdateMsg;

//模板结点指针：Title/Text/Png/Grid
typedef struct stcNodeInfo
{
    //ftt 2024.10.22 CSttItems *pRootNode
    //CExBaseObject* pObj; //存储CSttItems *pRootNode结点
    CString m_strItemsPath; //项目对应的模版路径，用于唯一标识某个功能项目，报告头的strItemsPath固定为"ReportHead"
    int m_nStartPos; //节点内容起始位置
    int m_nEndPos; //节点内容终止位置
}CStcNodeInfo;

typedef CTLinkList<CStcNodeInfo> CStcNodeInfoList;

namespace Ui {
class QSttReportView;
}
class QSttReportView : public QWidget
{
    Q_OBJECT
public:
    explicit QSttReportView(QWidget *parent = 0);
    virtual ~QSttReportView();

private:
    void AddUpdateReportQT(const QString &strItemsPath, CExBaseObject *pObj); //ftt 2024.10.22
    void DeleteReportQT(const QString &strItemsPath); //ftt 2024.10.22
    Ui::QSttReportView *ui;
    QTextDocument *m_pDocument;

    QTextCharFormat m_oTitleFormat;
    QTextBlockFormat m_oTitleBlockFormat;

    QTextCharFormat m_oTextFormat;
    QTextBlockFormat m_oTextBlockFormat;

    QTextCharFormat m_oGridFormat;
    //QTextBlockFormat m_oGridBlockFormat;
    //QTextTableCellFormat m_oCellFormat;

    CStcNodeInfoList m_vecNodeInfo;
    int m_nCurPosition;

	QTimer m_oTimerRptUpdate;//zhouhj 2024.10.19  //报告更新及删除采用定时器更新

	CTxRingPtrBuffer<Stt_RptUpdateMsg> m_oRptUpdateMsgList;

public:
    void init();

    void TestMacroUiRptToTxDoc(const CString &strItemsPath, CRptTemp_TestMacroUiRpt *pRptTemp_TestMacroUiRpt);
    void ReportHeadToTxDoc(const CString &strItemsPath, CRptTemp_Items *pRptTemp_Items/*, bool bNewTest*/);  //ftt 2024.10.22
    void RptItemsToTxDoc(const CString &strItemsPath, CRptTemp_Items *pRptTemp_Items); //ftt 2024.10.22
    void RptTemplateToTxDoc(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate);
    void TitleToTxDoc(const CString &strText, long nLevel/*, long titleID*/);
    void TextToTxDoc(const CString &strText, float nSize, long bBold, CString strFontFamily);
    void PngToTxDoc(const CString &strPath);
    void GridToTxDoc(CRptTemp_Grid *pRptTemp_Grid);
    void HeadToTxDoc(CRptTemp_Head *pRptTemp_Head, long nRow, QTextTable *table);
    void RowToTxDoc(CRptTemp_Row *pRptTemp_Row, long nRow, QTextTable *table);

    void GetTitleFontSize(long nLevel, double &nSize);
    void UpdatePosAfterChangeItems(int nStartNum);
    void UpdatePosAfterDeleteItems(int nStartNum, int nStartPos);

public slots:
    void slot_AddUpdateReportQT(QString strItemsPath, CExBaseObject *pObj); //ftt 2024.10.22
    void slot_DeleteReportQT(QString strItemsPath); //ftt 2024.10.22
    void slot_ClearAllReportsQT(); //ftt 2024.10.16
	void slot_TimerRptUpdate();

};
