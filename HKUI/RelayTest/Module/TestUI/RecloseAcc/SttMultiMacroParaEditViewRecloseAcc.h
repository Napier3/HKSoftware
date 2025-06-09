#ifndef STTMULTIMACROPARAEDITVIEWRECLOSEACC_H
#define STTMULTIMACROPARAEDITVIEWRECLOSEACC_H

#include <QWidget>
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "SttMultiMacroRecloseAccParasDefine.h"

class QSttMultiMacroParaEditViewRecloseAcc : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT
public:
    explicit QSttMultiMacroParaEditViewRecloseAcc(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewRecloseAcc();

    virtual void InitUI_OneMacro();
    virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);
	virtual BOOL IsManualTriggerMode_MacroTestItem(CSttMacroTest* pMacroTest);
	virtual char* GetMacroID(){ return STT_ORG_MACRO_RecloseAccTest_I; }

protected:
	CSttGdGridInst *m_pGridInst;

private:
//	QDialog *m_pAddMultiItemSelectDlg;//放入基类  zhouhj 2024.9.15

private:
	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
    void GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro); //20240806 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras
    void SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData);  //20240806 wanmj
    void CheckAllPresence(CExBaseList *pParas);
    void InitGridTitleLanguage();   //20241025 wanmj 表格表头多语言处理
    void SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col);
signals:

public slots:
	virtual void slot_AddOneItemBtnClick();//添加单个测试项
	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量

	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_DeleteSelItemBtnClick();//删除当前选择
	virtual void slot_DeleteAllItemBtnClick();//删除全部

	virtual void slot_ClearResultBtnClick();//清除测试结果
	virtual void slot_ClearSelResultBtnClick();//清除全部结果
	virtual void slot_ClearAllResultBtnClick();//清除所有结果

	virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);
};

#endif // STTMULTIMACROPARAEDITVIEWRECLOSEACC_H
