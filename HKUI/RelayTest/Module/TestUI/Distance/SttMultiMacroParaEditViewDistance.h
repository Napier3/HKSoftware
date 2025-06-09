#ifndef STTMULTIMACROPARAEDITVIEWDISTANCE_H
#define STTMULTIMACROPARAEDITVIEWDISTANCE_H

#include <QWidget>
#include "./DistanceAddMultDlg.h"
#include "./DistanceAddInterPhaseDlg.h"
#include "./DistanceAddSinglePhaseDlg.h"
#include "./DistanceItemParaEditWidget.h"
#include "./DistanceCommonParasDlg.h"
#include "./DistanceBinarysDlg.h"
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"

#include "../../../../Module/TestMacro/TestMacro.h"

class QSttMultiMacroParaEditViewDistance : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewDistance(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewDistance();

	virtual void InitUI_OneMacro();
	virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();
	void CheckAllPresence(CExBaseList *pMacroTest);

	virtual char* GetMacroID(){ return STT_ORG_MACRO_DistanceTest_I; }

	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
	//对于低周等模块,实际对应多个测试功能,根据MacroID单独创建对应的Items
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);

	//virtual void UpdateItemTestPoint(CSttMacroTest* pMacroTest,int nState  = -1);//20240712 luozibing 更新当前选中测试项对应的测试点
	//virtual BOOL AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);//添加测试项时,在特性曲线界面添加对应测试点
	virtual BOOL DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);
	virtual BOOL AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = -1);

	//从特性曲线添加测试项
	virtual BOOL AddItem_From_Charact(double dX, double dY);
	virtual BOOL UpdateCurrItem_From_Charact(double dX, double dY);

	//更新特性曲线参数 20240724 luozibing
	virtual void UpdateParasByCharEdit();
	virtual void UpdateCharacteristicParas(CSttMacroTest *pCurrMacroTest);
	virtual void UpdateCharacterisByFaultType();//未选中测试项时 故障参数改变更新特性曲线图20241012 luozibing

//	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);//20240726 luozibing 更新GOOSE数据

    //20240813 wanmj 移到基类
    //virtual bool eventFilter(QObject *obj, QEvent *event);/20240729 luozibing 点击空白,取消选中项

    virtual void UpdateParas_To_ZTView();//20240729 luozibing 根据测试项参数更新ZT视图
	virtual BOOL AddTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest);//添加测试项时,在ZT视图界面添加对应测试点
	virtual BOOL DeleteTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest);
	virtual BOOL UpdateTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest, bool bSelPoint = false);
	//20240926 设置Z/T视图对应曲线类型的数据
	void Update_FaultTypeParas_To_ZTView(CSttMacroTestParaDatas *pDstDatas,CString strFaultType, CString strZAng, CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[]);
	CString GetFaultNameByID(CSttMacroTestParaDatas *pDataParas);//20240926 luozibing 获取故障类型对应界面显示名称

	virtual void SetMacroTestNameByParas(CSttMacroTest *pMacroTest);//通过参数拼接测试项id 20240919 luozibing

	virtual void OnViewTestStart();//开始测试函数
	virtual void SetAddMultiItemByZSetLine(CDataGroup *pGroup, CString strID, CString strZSet_Line);//设置添加系列 线路长度阻抗值参数20241017luozibing
protected:
	CSttGdGridInst *m_pZPhiGridInst;
	CSttGdGridInst *m_pRXGridInst;
	CDataGroup *m_pAddSinglePhase_Paras;//20240820 luozibing 单项接地故障参数
	CDataGroup *m_pAddInterPhase_Paras;//20240820 luozibing 相间接地故障参数
	CDataGroup *m_pAddMult_Paras;//20240820 luozibing 多个区段参数

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

	//表格参数修改后,更新到当前参数编辑界面
	virtual void slot_Grid_To_ParaEditWidget(CSttMacroTest* pMacroTest);
	//参数编辑界面修改后,更新到当前选择表格
	virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);
private slots:
	void slot_AddOneLNBtnClick();//20240620 luozibing 添加单项接地故障页面
	void slot_AddOneLLBtnClick();//20240620 luozibing 添加相间接地故障
	void slot_AddMultBtnClick();//20240620 luozibing 添加多个区段页面

private:

//	QDialog *m_pAddMultiItemSelectDlg;//选择页面//放入基类  zhouhj 2024.9.15
    BOOL m_bDefault;

	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
	void GetLastBinarysAndCommonToAddMult(CExBaseList *pTestMacro);
	void CompareTestMacroUI_Paras(CString strID, CExBaseList *pTestMacro);
	void UpdateCharacteristicParasToAddMult(CDataGroup *pMaroTest_UI_Paras);
	

	typedef enum{
		ADDMULTIITEM_DLG = 0,//添加系列
		DELETEITEM_DLG   = 1,//删除测试项目
		CLEARSELRESULT   = 2//清除测试结果
	}SELECTDLG_STATE;
};

#endif // STTMULTIMACROPARAEDITVIEWDISTANCE_H
