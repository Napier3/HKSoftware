#ifndef QSTTMULTIMACROPARAEDITVIEWBASE_H
#define QSTTMULTIMACROPARAEDITVIEWBASE_H

#define STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM	   8//测试项表格的最大数目

#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "Interface/QItemParaEditWidgetBase.h"

#include "../UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../UI/Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttCmd/GuideBook/SttItems.h"
#include "Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "Module/SttTestGridDefine/SttTestGridDefine.h"
#include "../UI/Module/CharLibWidget/InternationalCharactInterface.h"
#include "../UI/Module/CharLibWidget/InternationalZTInterface.h"
//#include "../../../Module/XDrawBase/XDrawTestPoint.h"

class QSttMultiMacroParaEditViewBase : public CSttMacroParaEditViewOriginal, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttMultiMacroParaEditViewBase(const CString &strGridFile,QWidget *parent);
	virtual ~QSttMultiMacroParaEditViewBase();

	//创建单功能多点界面
	virtual void InitUI_OneMacro();
	//创建多功能多点界面
	virtual void InitUI_MultiMacro(QStringList strTabTitleList);
	virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();

	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual BOOL ItemStateChanged(CSttItemBase *pSttItem);//测试过程中,更新当前测试的项目状态
	virtual BOOL GetMacroIDAndFaultType(CSttItemBase *pSttItem,CString &strMacroID,long &nFaultType);//测试过程中,获取当前测试项MacroID及故障类型
	virtual BOOL ShowRslt(CSttItemBase *pSttItem);//更新测试结果
	virtual void Update_MultiMacroParaEditView();
	virtual BOOL IsInternationalMode(){return TRUE;}
	virtual BOOL IsManualTriggerMode_MacroTestItem(CSttMacroTest* pMacroTest);
	////多功能多点使用,用于切换当前tab显示界面
	virtual void SyncCurrMacroItemParaEditWidget(CSttItemBase *pSttItem);

//	virtual BOOL AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);//添加测试项时,在特性曲线界面添加对应测试点
	virtual BOOL DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);
	virtual BOOL AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = CHAR_TEST_OBJECT_STATE_NORMAL);
	virtual BOOL AddUpdateTestPoint_To_Charact();

	virtual BOOL UpdateTestUI_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = -1);//20240805 gongyiping添加测试项时,在特性曲线界面更新特性图界面图像

	//从特性曲线添加测试项
	virtual BOOL AddItem_From_Charact(double dX, double dY);
    virtual BOOL AddItem_From_Charact(double dBegX, double dBegY, double dEndX, double dEndY);
	virtual BOOL UpdateCurrItem_From_Charact(double dX, double dY);

	//更新特性曲线参数 20240724 luozibing
	virtual void UpdateParasByCharEdit();
	virtual void UpdateCharacteristicParas(CSttMacroTest *pMacroTest);

    //更新ZT视图 20240808 luozibing
    virtual void UpdateParas_To_ZTView();//更新折线图
	virtual BOOL AddTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest);//添加测试项时,在ZT视图界面添加对应测试点
	virtual BOOL DeleteTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest);
	virtual BOOL UpdateTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest,bool bSelPoint = false);

	virtual void SetMacroTestNameByParas(CSttMacroTest *pMacroTest);//通过参数拼接测试项id 20240919 luozibing

	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
	//对于低周等模块,实际对应多个测试功能,根据MacroID单独创建对应的Items
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);

	//添加单个测试项时,获取当前需要添加的参数数据
	virtual CDataGroup* GetAddOneItem_DataGroup(CSttMacroTest *pSttMacroTest);
	//更新单个测试项时,获取当前需要添加的参数数据
//	virtual CDataGroup* GetUpdateOneItem_DataGroup(CSttMacroTest *pSttMacroTest);

	//删除单个测试功能，同时删除链表及表格中显示内容
	BOOL MultiMacroParaEdit_DeleteOneMacroItem(CSttMacroTest *pSttMacroTest,CExBaseList *pMacroItemsRef);
	//判断当前总的根节点下,是否有测试功能项的参数被修改
	BOOL HasMacroParasModified();

	//获取当前测试功能添加系列使用的参数数据
	CDataGroup* GetAddMultItems_Paras();
    virtual CExBaseList* GetCurrentMacroDatas();  //20240716 wanmj 单功能多点的测试功能获取当前测试项的数据

	BOOL Ats_UpdateMacroTestItems();//更新当前全部修改的测试项目
	BOOL Ats_ClearReportRslts(CSttItemBase *pCurrItem);//清除当前传参数据的结果
	CSttItems* Get_MulitMacroRootItems();
	void UpdateZoneSelDataTypes();

	virtual void UpdateTestResource(BOOL bCreateChMaps);
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	virtual void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	virtual void RemoveGooseParaWidget();//移除Goose界面
	virtual void AddGooseParaWidget(QWidget *pWidget);//添加Goose界面

    virtual bool eventFilter(QObject *obj, QEvent *event); //20240813 wanmj 点击空白,取消选中项
	virtual void UpdateBottomBtnsEnable();//2024-8-22 wuxinyi 更新底部按钮使能
	virtual bool PrepStartTest();//2024-8-23 wuxinyi 开始测试前的准备工作,主要用于不添加任何测试项目点开始试验，应有提示
	virtual char* GetMacroID(){ return ""; }

public:
	//上半部分界面显示的QTabWidget,显示当前表格选择的单个测试项的参数
	QTabWidget *m_pSingleItemEditTab;
	QItemParaEditWidgetBase *m_pSingleItemParaEditWidget;//单个测试功能编辑界面
	QGooseParaWidget* m_pGoosePubsWidget;//GOOSE发布界面

	//当前显示测试项表格
	QSttMacroParaEditGrid *m_pCurrMacroParaEditGrid;
	//add wangtao 20240701 多个测试项表格时，根据传入表头的QStringlist长度创建
    QSttMacroParaEditGrid *m_pMultiMacroParaEditGrid[STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM];

	//多功能多点模式时,创建Tab界面,不同的Tab显示不同的测试功能表格
	QTabWidget *m_pMultiMacroGridTab;


	QPushButton *m_pAddOneItemBtn;//添加单个测试项
	QPushButton *m_pAddMultiItemBtn;//添加系列
	QPushButton *m_pCommonParasBtn;//通用参数
	QPushButton *m_pBinarysBtn;//开关量
	QPushButton *m_pDeleteItemBtn;//删除测试项
	QPushButton *m_pClearResultBtn;//清除测试结果
	QVBoxLayout *m_pMainVboxLayout;
	QHBoxLayout *m_pBottomHboxLayout;


	CSttTestGridDefine m_oSttTestGridDefine;//测试功能表格配置
	CTestMacro *m_pSingleMacroRef;//单功能多点,对应的单功能的缺省数据对象指针

	BOOL m_bCharTestObjectHasChanged;//zhouhj 2024.10.11 该测试功能对应的特性曲线测试点或测试线被修改了

	CExBaseList m_oSingleMacroItemsRef;//单功能多点测试项,全部Items展示链表
	CExBaseList *m_pCurrMacroItemsRef;//当前测试功能链表对应的对象
	
	CTestMacro *m_pMultiMacroRef[STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM];//多功能多点,对应的单功能的缺省数据对象指针
	CExBaseList m_oMultiMacroItemsRef[STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM];//多功能多点测试项,全部Items展示链表
    QItemParaEditWidgetBase *m_pMultiItemParaEditWidget[STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM];//多个测试功能编辑界面
	QStackedWidget *m_pMultiItemStackedWidget;//多个测试功能编辑界面切换页

    CInternationalZTInterface *m_pZTViewInterface;//20240711 luozibing ZT视图接口
	CInternationalCharactInterface *m_pCharactInterface;//20240712 luozibing	特性图接口

	CFont m_oModuleFont;
	CFont m_oTileFont;
protected:
	void UpdateBtnEnable(QPushButton *pPushButton, bool bEnable);
	//当前多功能测试项对应的总的根节点,对于距离等单功能多点模式,其也是距离的根节点,对应低周等模块,其是对应多个测试功能的总的根节点,每个测试功能的根节点为其子对象
	CSttItems *m_pMulitMacroRootItems;

	QDialog *m_pAddMultiItemSelectDlg;  //放入基类  zhouhj 2024.9.15

    //20240910 wanmj 表格鼠标右键点击新增快捷功能
    QMenu *m_menuTest;
    QAction *m_actSelectAll;    //全选
    QAction *m_actDeselectAll;  //全不选
    QAction *m_actAddOneItem;   //添加测试项
    QAction *m_actAddMultiItem; //添加系列
    QAction *m_actDeleteSelItem;    //删除当前测试项
    QAction *m_actDeleteAllItem;    //删除所有测试项
    QAction *m_actClearResult;      //清除当前结果
    QAction *m_actClearAllResult;   //清除所有结果

private:
//	CDataGroup *m_pAddMultItems_Paras;
    void InitTestMenu();    //20240910 wanmj 表格鼠标右键点击新增快捷功能

public slots:
	virtual void slot_AddOneItemBtnClick();//添加单个测试项
	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量
	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_ClearResultBtnClick();//清除测试结果

	virtual void slot_DeleteSelItemBtnClick();//删除当前选择
	virtual void slot_DeleteAllItemBtnClick();//删除全部

    virtual void slot_ClearSelResultBtnClick();//清除当前结果
	virtual void slot_ClearAllResultBtnClick();//清除所有结果

	//表格参数修改后,更新到当前参数编辑界面
	virtual void slot_Grid_To_ParaEditWidget(CSttMacroTest* pMacroTest);
	//参数编辑界面修改后,更新到当前选择表格
	virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);

    //20240910 wanmj
    virtual void slot_SelectAllItems(); //全选
    virtual void slot_DeselectAllItems();  //全不选
};

extern CFont *g_pSttGlobalFont;

#endif // QSTTMULTIMACROPARAEDITVIEWBASE_H
