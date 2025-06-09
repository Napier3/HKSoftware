#ifndef STTMACROPARAEDITVIEWSTATE_H
#define STTMACROPARAEDITVIEWSTATE_H

#include <QMainWindow>

#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMap>
#include "StateParaTab.h"
#include "StateButtonWidget.h"
#include "StateTrigerWidget.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../../Module/SttTest/Common/tmt_result_def.h"
#include "../Controls/SttLineEdit.h"
#include "SmvAbnormal/SmvAbnormalParaset.h"
#include "../Module/CommonCtrl_QT/SttDiffCurrCalDlg.h"

#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Controls/SettingCtrls/settingselectdlg.h"


#define POSTFIX_STATETEST   "sttxml"

#define USE_STT_STATE_EX_REPORT          //当状态数大于一定范围后,或者循环次数较多时,采用简化版的状态序列报告

class QSttMacroParaEditViewState: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
    explicit QSttMacroParaEditViewState(bool bHorizontal = true,QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewState();

	//virtual
	virtual void initUI_Paras(bool bSmvAbnormal);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pDataset);

	//2023-2-4  lijunqing 提高程序界面初始化打开的速度，将矢量图、状态图等的初始化放到线程
	virtual void InitSpyToolWidget();

	tmt_state_test m_oStateTest;
	tmt_StatePara* m_pStatePara;
	tmt_StatePara* m_pCopyStatePara; //拷贝状态指针
	CIecCfgGoutDatas* m_pCopyGoutDatas;
	CIecCfgDatasSMV* m_pCopyFT3Datas;//chenling20230518

	ShortCalcuPara m_ShortCalcuPara;
	Stt_DiffCurrCalParas m_oDiffCurrCalParas;

	long m_nCircle;
	void setData(tmt_StatePara* pStatePara);
	int m_nCurStateIndex;
	void UpdateReportFile();

	void AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize);
	void AddCheckBox(QCheckBox** ppChk,QString strName,int nFontSize);
	void AddLabel(QLabel** ppLabel,QString strName,int nFontSize);
	void AddLineEdit(QLineEdit** ppLabel, int nFontSize);

	void CopyStatePara();
	void GetAtsCmdParas(CDataGroup* pDataGroup);

	void CopyDatasSMV();

	virtual void SysStateReport_OnStateChanged(CEventResult *pEventInfo);
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);//dingxy 20240522 处理动作时间动作值操作
	void InitManuTrigerButton();

	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml);
	virtual  void GetMacroItemsXml(CSttItems &oRootItems);

	//20230213  zhangyq
	virtual void ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook);  //测试模板
	virtual void ProcessRptAfterGenTemplate(QSttReportViewHtml *pSttReportViewHtml);  //报告模板
	virtual CString ProcessItemID(const CString & strItemID,long nLoopIndex);

public:
	bool m_bHorizontal;
	bool m_bSmvAbnormal;       //SV异常模拟
	QBoxLayout* m_pMainLayout;	
	QSmvAbnormalParaset* m_pSVParaSet;		//SV异常模拟页面

	QStateParaTab* m_pParaTab;
	QStateButtonWidget* m_pBtnWidget;
	QStateTrigerWidget*m_pTrigerWidget;

	QPushButton* m_pSettingValue;
	QPushButton* m_pEstimate;
	QPushButton* m_pBinarySet;//开关量设置
	QPushButton* m_pCommonPara;
	QPushButton* m_pShortCalc;
	QPushButton* m_pDiffCurrCalcBtn;//差流计算按钮
	QPushButton* m_pGradientSet;
	//QLabel* m_pFreLabel;
	//QSttLineEdit* m_pFreEdit;
	QCheckBox* m_pDC;
	QCheckBox* m_pDCPlus;
	QLabel* m_pLabelTao;
	QLineEdit* m_pTao;

	QMap<int, CString> m_mapState;//勾选状态的名称替换
	long m_nRepeatNum_GenerateRpt;//记录当前生成报告中的重复次数,在下一次生成报告时,如总循环次数减少了,需要将其删除
	QStringList m_aStrActValue;//记录所有动作值
	QList<int >m_SelStateList;//2024-8-30 wuxinyi 勾选的状态序号

public:
	virtual void initUI();
	virtual void initUI_TabBase();
	virtual void initUI_LayoutBase(bool bGradientSet);

	virtual void initConnection_Base();
	virtual void initConnections();

	virtual void UpdateStateParas_Base();
	virtual void UpdateStateParas();
	void CopyBinaryConfig(BOOL b=TRUE);

	CSttTestResourceBase* CreateTestResource();
	virtual void UpdateTestResource(BOOL bCreateChMaps);

	virtual PTMT_PARAS_HEAD GetTestParas(){ return &m_oStateTest;};
	virtual char* GetMacroID();/*{ return "StateTest"; }*/

	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual void SerializeTestParas_Base(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub, BOOL bSmvAbnormal,BOOL bGooseAbnormal);
	void ResetStateSerialize();

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual void initTestParas();
	virtual void InitUI_OpenParas();

	virtual void InitGoosePubDataGroups();
	virtual void InitFT3PubDataGroups();
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	void UpdateFT3Tab_UI(CIecCfgDatasSMV *pIecCfgDatasSMV);

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	void InitSvAbnormalTmt();
	virtual void UpdateBinBoutExTab();

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);

	virtual void OnViewTestLink(BOOL b=FALSE);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void UpdateAuxDCEdit();//20240613 suyang 新增用于更新L336D 状态序列 通用 辅助直流编辑框 

	bool HasHarmParaset(tmt_StatePara* pStatePara);
	void ClearHarmParaset(tmt_StatePara* pStatePara);
	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateVectorObject();

	void EnableButtons();
	void SetStateFont();//字体设置
	void setDcoffsetEnable();//叠加衰减直流分量可编辑状态
	void UpdateActValue(CEventResult *pEventInfo);//dingxy 20240520 更新动作值
	void GetActValue(int nCurStepIndex, int nIndex);

//	void GetSMVDataAppIDs(QList<int> &m_olistAppIDs);

	//void GetSMVDataAppID(int nIndex);

protected:
	void InsertGoutDatas(CIecCfgGoutDatas *pIecCfgGoutDatas,long nInsertStateIndex);
	void InsertFT3Datas(CIecCfgDatasSMV *pIecCfgDatasSMV,long nInsertStateIndex);//chenling

signals:
	void sig_updataParas();
	void sig_DataOfChannelChanged();

protected slots:
	virtual void slot_UpdateVecterViews();//更新矢量图相关实时数据视图
	virtual void slot_updateParas();
		//virtual void slot_PasteStateBF();
		virtual void slot_PreviosState();//上一状态
		virtual void slot_NextState();//下一状态
	virtual void slot_InsertStateBF();
	virtual void slot_InsertStateAF();
		//virtual void slot_PasteStateAF();
		//virtual void slot_CopyState();
	virtual void slot_DeleteState();
	virtual void slot_EditState();
	virtual void slot_StatesIndexChanged(int nIndex);
		virtual void slot_BinarySet();
	virtual void slot_CommonPara();
	virtual void slot_Estimate();
	virtual void slot_SettingValue();
	virtual void slot_ShortClac();
	virtual void slot_DiffCurrCalcBtnClicked();
	virtual void slot_GradientSet();
		//virtual void slot_lne_FreChanged();
		//virtual void slot_lne_FreChangedKeyBoard();
	virtual void slot_chb_DcStateChanged(int);
	virtual void slot_chb_DcPlusStateChanged(int);
	virtual void slot_lne_TaoChanged();
	virtual void slot_DcCoffsetStateChanged();
	
	virtual void slot_SwitchStateChanged();
	virtual void slot_GooseDataChanged();
	virtual void slot_FT3DataChanged();

		//virtual void slot_RepairDataChanged();
	virtual void slot_ShortCalcuOk(ShortCalcuPara &para);
	virtual void slot_currentChangedTabWidget(int nCurrIndex);

	void slot_UpdateToolButtons();
// 	void slot_UpdateAuxDcEnabled();
};

CIecCfg92Data* Global_GetSMVDataByIndex(int nGroupIndex);
BOOL Global_SetSvAbnormalData(CIecCfg92Data* pIecCfgSmvData,tmt_StatePara* pStatePara);
BOOL Global_SetSvAbnormalData(long nGroupIndex,tmt_StateParas *pStateParas);
BOOL Global_SetSvAbnormalData(CIecCfg92Data* pIecCfgSmvData,tmt_StateAbnormalSMV *pAbnormalSMV);
void Global_SetSvAbnormalTmtValues_ByIecConfig(tmt_StateAbnormalSMV *pAbnormalSMV,BOOL bJudgeMacEmpty);//参数2判断Mac地址是否为空,如果为空才赋值

extern QSttMacroParaEditViewState* g_pStateTest;

#endif // STTMACROPARAEDITVIEWSTATE_H
