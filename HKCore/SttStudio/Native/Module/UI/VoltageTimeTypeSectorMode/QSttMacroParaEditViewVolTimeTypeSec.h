#include "ui_QSttFAParasSetDialog.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
#include "../../UI/Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFAStateSequenceGroupGrid.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFATestResultViewGroupGrid.h"
#include "../../SttTest/Common/FAParasSet/tmt_fa_Paras_set.h"
#include "QSttVoltageTimeGroupTestItemWidget.h"


class QSttMacroParaEditViewVolTimeTypeSec : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewVolTimeTypeSec(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewVolTimeTypeSec();

public:
	void InitUI();
	void UpdateFaParasSet();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);//需要改结构体数据以及链表中的数据

	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_oTmtFaParasSet;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_VolTimeTypeSecTest; }
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);//序列化测试参数结构体,后期需要更改

	virtual void startInit();//对界面的控件进行失能状态处理
	virtual void stopInit();
	virtual void OnViewTestStart();//测试开始界面的响应
	virtual void OnViewTestStop();
	void SetData(PTMT_PARAS_HEAD pCur);

	QTabWidget *m_pVolTimeTypeSectorModeTab;					   //电压时间型分段模式Tab
	QSttVoltageTimeGroupTestItemWidget *m_pTestItemWidget;		   //测试项目
	QSttFAParasSetDialog *m_pSttFAParasSetDialog;				   //FA参数设置

	QSttFATestResultViewGroupGrid *m_pFATestResultViewGroupGrid;   //测试结果试图表格
	QSttFAStateSequenceGroupGrid *m_pFAStateSequenceGroupGrid;     //状态序列表格
	QSplitter* m_pVolTimeTypeSecSplitter;       //切割

	QHBoxLayout* m_pTestItemLayout;			    //测试项目布局
	QHBoxLayout* m_pTestResulLayout;			//测试结果视图布局
	QHBoxLayout* m_pStateLayout;				//状态序列布局

	QTabWidget* m_pTestWidget;					//测试项目标签页
	QTabWidget* m_pFACommonSpyWidget;		    //测试结果视图和状态序列标签页

	QWidget* m_pTestResultViewWidget;           //测试结果视图
	QWidget* m_pStateSequenceWidget;   		    //状态序列

	CDataGroup m_TotalDynamicList;              //测试结果试图链表
	tmt_FaParasSetTest* m_oTmtFaParasSet;
};

extern QSttMacroParaEditViewVolTimeTypeSec* g_pVolTimeTypeSecTestMain;

