#ifndef SttCommCmdWzd_SelMacroWidget_H
#define SttCommCmdWzd_SelMacroWidget_H

#include <QDialog>
#include <QFont>
#include "../Config/MacroTestUI/SttMacroTestUI_TestMacroUIRef.h"
#include "../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "Tree_CommCmdWzd.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../Config/MacroTestUI/SttMacroTestUI_TestMacroUIMngr.h"

namespace Ui {
class QSttCommCmdWzd_SelMacroWidget;
}

//通讯命令向导，第一步：选择测试功能。
class QSttCommCmdWzd_SelMacroWidget : public QDialog, public CExBaseListTreeOptrInterface
{
    Q_OBJECT

	virtual void OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);

public:
    explicit QSttCommCmdWzd_SelMacroWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCommCmdWzd_SelMacroWidget();

	CExBaseListTreeCtrl *m_pTreeCtrl_Macro;
	CTree_CommCmdWzd *m_pTreeCtrl_Cmd;
	//QScrollComboBox* m_cmbTestClass;
	CSttMacroTestUI_TestMacroUIRef *m_pCurrUIRef;
	CSttMacroTestUI_TestMacroUIMngr *m_pTestMacroUIMngr;
	QFont m_font;

	CGbMacroGenWzd *m_pGbMacroGenWzd;
	long m_nRptTitle;
	long m_nTitleLevel;

public:
	void UI_SetFont();
	//void InitCommCmdCfg();
	//void InitTestClass();
	void EnableBtns();
	void InitCmbTitleLevel();
	void InitLanguage();
	void ShowGbMacroGenWzd();
	BOOL IsHasCmdSelected();   //向导中是否勾选了通讯命令项目
	BOOL IsHasWriteCmdSelected();   //向导中，是否勾选了write的通讯命令项目
	long CalAutoIndex(const CString& strID);
	long GetRepeatTimes();
	long GetRptTitle();
	long GetTitleLevel();
	BOOL IsSelMacroHasErrEvalute();  //当前选中的电气量功能，是否含有误差评估
	virtual void keyPressEvent(QKeyEvent *event);
public slots:

signals:

private slots:
	void on_m_cmbTestClass_currentIndexChanged(int index);
	void on_lineEdit_Name_textChanged(const QString &arg1);
	void on_lineEdit_ID_textChanged(const QString &arg1);
    void on_m_btnSelItemsName_clicked();
	void on_slot_CmdTreeItemChanged(QExBaseTreeWidgetItem* pTreeItem);
	void on_m_chkRptTitle_clicked();
	void on_m_cmbTitleLevel_currentIndexChanged(int index);

private:
    Ui::QSttCommCmdWzd_SelMacroWidget *ui;


};

#endif // SttCommCmdWzd_SelMacroWidget_H
