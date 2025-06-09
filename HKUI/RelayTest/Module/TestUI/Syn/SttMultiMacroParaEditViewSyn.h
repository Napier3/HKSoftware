#ifndef STTMULTIMACROPARAEDITVIEWSYN_H
#define STTMULTIMACROPARAEDITVIEWSYN_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SynActVoltageItemParaEditWidget.h"
#include "SynActFreqItemParaEditWidget.h"
#include "SynLeadAngItemParaEditWidget.h"
#include "SynAutoAdjItemParaEditWidget.h"
#include "SynAdjVolItemParaEditWidget.h"
#include "SynAdjFreqItemParaEditWidget.h"
#include "SynAddMultDlg.h"
#include "SynAddMultQuickDlg.h"
#include "SynCommonParasDlg.h"
#include "SynBinarysDlg.h"
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"

#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
//#include "SttMultiMacroSynParasDefine.h"
#include "SynWiringDiagramWidget.h"
class QSttMultiMacroParaEditViewSyn : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewSyn(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewSyn();

	QSynWiringDiagramWidget *m_pSynWiringDiagramWidget;

	virtual void InitUI_OneMacro();
    virtual void InitUI_MultiMacro();
	virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_SynTest_I; }

	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);
	virtual void Update_MultiMacroParaEditView();

	//对测试项的数据更新特性曲线
	virtual BOOL UpdateTestUI_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = -1);
	
	virtual QWidget* GetWiringDiagramWidget(){ return m_pSynWiringDiagramWidget; }//获取模块中的接线图窗口指针

	CString SynValueCheck(CString strValue, float nMax, float nMin, int nAfterPoint);
	void SynCheckParaExist(CExBaseList *pParas, CString strID);
protected:
	CSttGdGridInst *m_pGridInst_VoltageTest;
	CSttGdGridInst *m_pGridInst_FreqTest;
	CSttGdGridInst *m_pGridInst_LeadAng;
	CSttGdGridInst *m_pGridInst_AutoAdj;
	CSttGdGridInst *m_pGridInst_AdjVol;
	CSttGdGridInst *m_pGridInst_AdjFreq;

public slots:

	virtual void slot_AddOneItemBtnClick();//添加单个测试项
	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量
	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_ClearResultBtnClick();//清除测试结果

	virtual void slot_DeleteSelItemBtnClick();//删除当前选择
	virtual void slot_DeleteAllItemBtnClick();//删除全部

	virtual void slot_ClearSelResultBtnClick();//清除全部结果
	virtual void slot_ClearAllResultBtnClick();//清除所有结果

	void slot_CurrMacroParaEditGridChanged(int);//当前显示测试项表格改变	
	void UpdateTestUI_To_Wiring();//更新右侧接线图
private slots:
	void slot_AddMultQuickClick();
	void slot_AddMultBtnClick();

private: 
    int nOldMacroItemsRef;//记录切换前的测试项表格
	CDataGroup *m_pParas;
//	QDialog *m_pAddMultiItemSelectDlg;//添加系列选择页面//放入基类  zhouhj 2024.9.15
	QStringList m_strTabTitleList;

	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
	void GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro); //20240806 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras
	void SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData);  //20240806 wanmj
	void CheckAllPresence(CExBaseList *pParas);

	typedef enum{
		ADDMULTIITEM_DLG = 0,//添加系列
		DELETEITEM_DLG   = 1,//删除测试项目
		CLEARSELRESULT   = 2//清除测试结果
	}SELECTDLG_STATE;

};
void Global_GetAllMacroTest(CExBaseList *pSingleMacroItemsRef,CSttItems *pMulitMacroRootItems,CTestMacro *pSingleMacroRef);
#endif // STTMULTIMACROPARAEDITVIEWSYN_H
