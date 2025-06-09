#ifndef STTMULTIMACROPARAEDITVIEWDIFF_H
#define STTMULTIMACROPARAEDITVIEWDIFF_H

#include <QWidget>
#include "./DiffAddSearchLineDlg.h"
#include "./DiffAddBatchDlg.h"
//#include "./QLowFrepAddMultDlg.h"
#include "./DiffRateItemParaEditWidget.h"
#include "./DiffTimeItemParaEditWidget.h"
#include "./DiffHarmItemParaEditWidget.h"
#include "./DiffCommonParasDlg.h"
#include "./DiffBinarysDlg.h"
#include "./QDiffWiringWidget.h"

#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "../../UI/SttTestCntrFrameApi.h"

#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "../../../../Module/FaultCal/DiffCharCal.h"

class QSttMultiMacroParaEditViewDiff : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewDiff(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewDiff();

	virtual void InitUI_OneMacro();
    virtual void InitUI_MultiMacro();
	virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_DiffTest_I; }
	//virtual void Update_MultiMacroParaEditView();

	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);

	virtual void Update_MultiMacroParaEditView();
	virtual QWidget* GetWiringDiagramWidget(){ return m_pDiffWiringWidget; }//获取模块中的接线图窗口指针

	virtual BOOL DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);
	virtual BOOL AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = CHAR_TEST_OBJECT_STATE_NORMAL);
	virtual BOOL AddUpdateTestPoint_To_Charact();
	//从特性曲线添加测试项
	virtual BOOL AddItem_From_Charact(double dX, double dY);
	virtual void UpdateParasByCharEdit();
	virtual void UpdateCharacteristicParas(CSttMacroTest *pCurrMacroTest);
	virtual BOOL UpdateTestUI_To_Charact(CSttMacroTest *pCurrMacroTest, int nState);
	//修改和获取结构体 最新的值 
	virtual void GetDatas(CDataGroup *pParas);
public:
	QDiffWiringWidget *m_pDiffWiringWidget;
protected:
	CSttGdGridInst *m_pGridInst_DiffRate;
	CSttGdGridInst *m_pGridInst_DiffTime;
	CSttGdGridInst *m_pGridInst_DiffHarm;

public slots:

	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量
	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_ClearResultBtnClick();//清除测试结果
	void slot_CurrMacroParaEditGridChanged(int);//当前显示测试项表格改变


	virtual void slot_DeleteSelItemBtnClick();//删除当前选择
	virtual void slot_DeleteAllItemBtnClick();//删除全部

	virtual void slot_ClearSelResultBtnClick();//清除全部结果
	virtual void slot_ClearAllResultBtnClick();//清除所有结果

	void slot_AddSearchLineBtnClick();//添加搜索线
	void slot_AddBatchItemBtnClick();//批量添加
	void slot_UpdateDiffWiringWidget();//更新右侧接线图
	void slot_CalculateId(double dIr);//计算比率制动曲线对应的差动电流值
private: 
	CDataGroup *m_pParas;
	QStringList m_strTabTitleList;
	CDiffCharCal m_oDiffCharCal;
	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
	BOOL InitDiffCharCal();
	float CalLineK(CCharElementLined* pLine);
	void GetParasDataToMacroTest(CDataGroup *pParas, CExBaseList* pTestmacro);//使paras和MacroTest的通用参数保持一致
	void SetValueToMacroTest(CDataGroup *pParas, CSttMacroTestParaData *pData);

	void UpdateMinaxis(int nMinaxis);//0:有名值(A) 1:标幺值(In)
	BOOL AddItem_From_SearchLine(int nFaultType, double dId, double dFaultTime, int nErrorLogic, double dAbsErr, double dRelErr);
	void InitGridTitleLanguage();   //表格表头多语言处理
	void SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col);
	typedef enum{
		ADDMULTIITEM_DLG = 0,//添加系列
		DELETEITEM_DLG   = 1,//删除测试项目
		CLEARSELRESULT   = 2//清除测试结果
	}SELECTDLG_STATE;

};
void Global_GetAllMacroTest(CExBaseList *pSingleMacroItemsRef,CSttItems *pMulitMacroRootItems,CTestMacro *pSingleMacroRef);
#endif // STTMULTIMACROPARAEDITVIEWDIFF_H
