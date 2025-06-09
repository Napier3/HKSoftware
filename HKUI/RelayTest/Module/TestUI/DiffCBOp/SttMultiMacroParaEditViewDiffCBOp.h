#ifndef STTMULTIMACROPARAEDITVIEWDIFFPROTECTION_H
#define STTMULTIMACROPARAEDITVIEWDIFFPROTECTION_H

#include <QWidget>

#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "DiffCBOpWiringWidget.h"


class QSttMultiMacroParaEditViewDiffCBOp : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewDiffCBOp(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewDiffCBOp();

    virtual void InitUI_OneMacro();
    virtual void InitDatas(CSttItems *pCurrRootItems);
    virtual void ConnectAll_SigSlot();
    virtual void DisConnectAll_SigSlot();
	virtual QWidget* GetSystemDiagramWidget(){ return m_pDiagramTab; }			//获取模块中的系统图窗口指针
	virtual QWidget* GetWiringDiagramWidget(){ return m_pDiffCBOpWiringWidget; }//获取模块中的接线图窗口指针
//	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
    virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);

	virtual char* GetMacroID(){ return STT_ORG_MACRO_DiffCBOpTest_I; }
	void InitGridTitleLanguage();   //20241025 表格表头多语言处理
	void SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col);
public:
    QPushButton *m_pResultAssessBtn;
    QStackedWidget *m_pDiagramTab;
    QLabel *m_pLabel;
	QDiffCBOpWiringWidget *m_pDiffCBOpWiringWidget;
protected:
    CSttGdGridInst *m_pDiffProtectionGrid;

public slots:
    virtual void slot_AddOneItemBtnClick();//添加单个测试项
//		virtual void slot_AddMultiItemBtnClick();//添加系列
    virtual void slot_CommonParasBtnClick();//通用参数
    virtual void slot_BinarysBtnClick();//开关量
    virtual void slot_DeleteItemBtnClick();//删除测试项
    virtual void slot_ClearResultBtnClick();//清除测试结果


    virtual void slot_DeleteSelItemBtnClick();//删除当前选择
    virtual void slot_DeleteAllItemBtnClick();//删除全部

    virtual void slot_ClearSelResultBtnClick();//清除全部结果
    virtual void slot_ClearAllResultBtnClick();//清除所有结果
    void slot_strImagePath(const QString &strImagePath);
    void slot_ResultEstimateBtnClick();//结果评估


	void slot_UpdateDiffCBOpWiringWidget();//更新右侧接线图
    private slots:
        //void slot_AddOneLNBtnClick();
        //void slot_AddOneLLBtnClick();
        //void slot_AddMultBtnClick();

private:

//    QDialog *m_pAddMultiItemSelectDlg;//选择页面//放入基类  zhouhj 2024.9.15

    void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
    void CheckAllPresence(CExBaseList *pListItems);

    //参数编辑界面修改后,更新到当前选择表格
    virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);

	typedef enum{
		DELETEITEM_DLG = 0,//删除测试项目
		CLEARSELRESULT = 1//清除测试结果
	}SELECTDLG_STATE;
};

#endif // STTMULTIMACROPARAEDITVIEWDISTANCE_H
