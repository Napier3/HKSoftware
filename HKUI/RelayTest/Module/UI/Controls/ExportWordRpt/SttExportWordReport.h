#ifndef QSttExportWordReport_H
#define QSttExportWordReport_H

#include <QDialog>
#include <QFont>
#include <QLabel>
#include "SttGbTreeCtrl_ExportRpt.h"
#include "SttGrid_ExportRpt_Tec.h"
#include "..\..\..\SttCmd\GuideBook\SttGuideBook.h"

namespace Ui {
class QSttExportWordReport;
}

//导出word报告，导出前对报告中的“技术要求”、“报告数据保留小数位数”进行编辑和配置
//左边树形结构，显示模板结构：仅显示人工创建才CSttItems和roonode的CSttItems
//右边表格：显示待编辑的“技术要求”和待配置的“报告数据保留小数位数”
//左边树形结构切换选择，右边表格刷新显示
class QSttExportWordReport : public QDialog, public CExBaseListTreeOptrInterface
{
    Q_OBJECT

	virtual void OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);

public:
    explicit QSttExportWordReport(CSttGuideBook *pGuideBook, QFont font,QWidget *parent = 0);
    virtual ~QSttExportWordReport();

	QSttGbTreeCtrl_ExportRpt *m_pTree_Gb;
	CSttGrid_ExportRpt *m_pGrid_DataDecimal;  //保留小数位数配置的表格
	CSttGrid_ExportRpt_Tec *m_pGrid_ItemsTec; //技术要求编辑的表格
	QLabel *m_pCurrSelText;
	QFont m_font;
	CDataGroup *m_pItemsTec;  //技术要求编辑
	CSttGuideBook *m_pGuideBook;
	CExBaseObject *m_pCurrSetItems;
	CString *m_pszFilePath;
	CExBaseList m_oListItems;  //额外整理的项目列表，用于“上一项”、“下一项”时遍历
	CExBaseList m_oDataTypes;  //记录所有技术要求的下拉框的内容：因为下拉框的内容是可编辑，是动态的。为了“上一步”能找回之前的配置

public:
	void Init(CDataGroup *pItemsTec, CString* pszFilePath);
	void InitItemsEnables();
	void InitItemsEnables(CDataGroup *pItemTec, const CString &strMacroUiID);
	void InitItemsTecDataTypes(CDataGroup *pItemTec);
	void UI_SetFont();
    void InitLanguage();
	void InitSttGuideBook(CSttGuideBook *pGuideBook);
	void InitSttGuideBook_Items(CSttItems *pNewItems, CSttItems *pItems);
	void ShowSttGuideBook(CSttGuideBook *pGuideBook);
	void OnGbTreeItemChanged(CExBaseObject *pSelObj);
	void GetItemsTecFromRptDataXml(CDataGroup *pItemTec, const CString &strMacroUiID);

	CString ExportWordRptDlg();
	void EnableBtns();
	void ExpandItems(CSttItems *pItems);
	void ClearItemsTecEnables();  //导出前，移除data下的enable节点
	void FormatItemsTec();  //导出前，将技术要求编辑配置的选择项，进行拼接。赋值到对应的data的value属性
	void FormatItemsTec(CDvmData *pData);

public slots:
	void slot_SelPath();
	void slot_ExportRpt();
	void slot_PrevClicked();
	void slot_NextClicked();

signals:

private slots:

private:
    Ui::QSttExportWordReport *ui;


};

#endif // QSttExportWordReport_H
