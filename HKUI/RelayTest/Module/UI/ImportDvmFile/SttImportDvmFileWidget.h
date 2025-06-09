#ifndef SttImportDvmFileWidget_H
#define SttImportDvmFileWidget_H

#include <QDialog>
#include <QFont>
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"

//lijunqing 2022-9-9
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "SttImportDvmFile_StepGrid.h"
#include "SttImportDvmFile_EditGrid.h"

namespace Ui {
class QSttImportDvmFileWidget;
}

//通讯命令向导，主窗口
class QSttImportDvmFileWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttImportDvmFileWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttImportDvmFileWidget();

	QFont m_font;
	CSttItems *m_pItems;  //导入模型后，19815返回的应答报文结构
	CSttItems *m_pCurrStep;  //当前步骤
	CExBaseList *m_pListSort;  //整理后的数据列表
	CSttImportDvmFile_StepGrid *m_pGridStep;  //显示步骤的表格
	CSttImportDvmFile_EditGrid *m_pGridEdit;  //编辑参数的表格

public:
	virtual void reject();
	virtual void accept();
	void UI_SetFont();
	long InitShow();
	void ShowSetp(CSttItems *pItemsStep);
	void GetCommCmds(CSttItems *pItemsStep, CExBaseList *pListCommCmds);//根据当前步骤，查找对应步骤的通讯命令
	void SortItems();
	BOOL IsItemsDevReset(const CString &strID);  //判断是否是复归态
	void GetCmdArray(CStringArray &strCmdArray, CSttItems *pItems); //找出有几个类型的通讯命令
	void GetItemName(CString &strName, const CString &strPath, const CString &strCmdKey);  //根据项目路径，查找功能模块的名称
	void InitLanguage();
	
	BOOL IsFirstStep();
	BOOL IsLastStep();
	CSttItems* GetNextStep();
	CSttItems* GetPreStep();

	void NextClick_Finish();
	void UpdateCommCmds();
	BOOL UpdateCommCmd(CSttCommCmd *pCommCmd, CExBaseList *pListDatas);

public slots:
	void slot_PreClick();
	void slot_NextClick();
	void slot_CancelClick();

signals:
	void sig_FreeImportDvmFileWidget();

private slots:

private:
    Ui::QSttImportDvmFileWidget *ui;
};

#endif // SttImportDvmFileWidget_H
