#ifndef QSTTMULTIMACROPARAEDITVIEWBASE_H
#define QSTTMULTIMACROPARAEDITVIEWBASE_H

#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "Interface/QItemParaEditWidgetBase.h"

#include "../UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../UI/Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttCmd/GuideBook/SttItems.h"
#include "Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "Module/SttTestGridDefine/SttTestGridDefine.h"

class QSttMultiMacroParaEditViewBase : public CSttMacroParaEditViewOriginal, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttMultiMacroParaEditViewBase(const CString &strGridFile,QWidget *parent);
	virtual ~QSttMultiMacroParaEditViewBase();

	//创建单功能多点界面
	virtual void InitUI_OneMacro();
	//创建多功能多点界面
	virtual void InitUI_MultiMacro();
	virtual void InitDatas();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();


public:
	//上半部分界面显示的QTabWidget,显示当前表格选择的单个测试项的参数
	QTabWidget *m_pSingleItemEditTab;
	QItemParaEditWidgetBase *m_pSingleItemParaEditWidget;//单个测试功能编辑界面
	QGooseParaWidget* m_pGoosePubsWidget;//GOOSE发布界面

	//当前显示测试项表格
	QSttMacroParaEditGrid *m_pCurrMacroParaEditGrid;


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


	CSttItems *m_pCurrRootItems;//当前测试项对应的根目录
	CSttTestGridDefine m_oSttTestGridDefine;//测试功能表格配置

public slots:
	virtual void slot_AddOneItemBtnClick();//添加单个测试项
	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量
	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_ClearResultBtnClick();//清除测试结果
};

extern QFont *g_pSttGlobalFont;

#endif // QSTTMULTIMACROPARAEDITVIEWBASE_H
