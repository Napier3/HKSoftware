#ifndef QSttMacroParaEditViewPrimFreqState_H
#define QSttMacroParaEditViewPrimFreqState_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMap>
#include "../State/SttMacroParaEditViewState.h"
#include "../Module/SttTest/Common/PrimFreq/tmt_prim_freq_state_test.h"

#include <QGroupBox>

#define POSTFIX_PRIMFREQSTATETEST   "pfsttxml"

#define USE_STT_STATE_EX_REPORT          //��״̬������һ����Χ��,����ѭ�������϶�ʱ,���ü򻯰��״̬���б���

class QSttMacroParaEditViewPrimFreqState: public QSttMacroParaEditViewState
{
	Q_OBJECT

public:
        explicit QSttMacroParaEditViewPrimFreqState(bool bHorizontal = true,QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QSttMacroParaEditViewPrimFreqState();

	//virtual
	virtual void initUI_Paras(bool bSmvAbnormal);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pDataset);

	//2023-2-4  lijunqing ��߳�������ʼ���򿪵��ٶȣ���ʸ��ͼ��״̬ͼ�ȵĳ�ʼ���ŵ��߳�
	virtual void InitSpyToolWidget();

	tmt_prim_freq_state_test *m_pPrimStateTest;

	void InitStateTest();//2024-9-11 lijunqing �Ż�

	long m_nCircle;
	void setData(tmt_StatePara* pStatePara);
	int m_nCurStateIndex;
	void UpdateReportFile();


	void CopyStatePara();
	void GetAtsCmdParas(CDataGroup* pDataGroup);

	void CopyDatasSMV();

	virtual void SysStateReport_OnStateChanged(CEventResult *pEventInfo);
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);//dingxy 20240522 ������ʱ�䶯��ֵ����
	void InitManuTrigerButton();

	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml);
	virtual  void GetMacroItemsXml(CSttItems &oRootItems);

	//20230213  zhangyq
	virtual void ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook);  //����ģ��
//	virtual void ProcessRptAfterGenTemplate(QSttReportViewHtml *pSttReportViewHtml);  //����ģ��
	virtual CString ProcessItemID(const CString & strItemID,long nLoopIndex);

public:
	QHBoxLayout *m_pDcLayout ;
	QGroupBox* m_pGrpDcSignal;
	QLabel* m_pLblDc1;
	QLabel* m_pLblDc2;
	QLineEdit* m_pEditDc1;
	QLineEdit* m_pEditDc2;

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

	virtual PTMT_PARAS_HEAD GetTestParas(){ return m_pPrimStateTest;};
	virtual char* GetMacroID(){ return STT_MACRO_ID_PrimFreqStateTest; }


	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	void ResetStateSerialize();

	virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);
	virtual void initTestParas();
	virtual void InitUI_OpenParas();

	virtual void InitGoosePubDataGroups();
	virtual void InitFT3PubDataGroups();
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	virtual void UpdateFT3Tab_UI(CIecCfgDatasSMV *pIecCfgDatasSMV);

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	void InitSvAbnormalTmt();
	virtual void UpdateBinBoutExTab();

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);

	virtual void OnViewTestLink(BOOL b=FALSE);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	void UpdateVectorObject();

	void EnableButtons();
	void SetStateFont();//��������
	void UpdateActValue(CEventResult *pEventInfo);//dingxy 20240520 ���¶���ֵ
	void GetActValue(int nCurStepIndex, int nIndex);
	
	virtual void UpdatePrimParaSetUI();

signals:
	void sig_updataParas();
	void sig_DataOfChannelChanged();

protected slots:
	virtual void slot_UpdateVecterViews();//����ʸ��ͼ���ʵʱ������ͼ
	virtual void slot_updateParas();
		//virtual void slot_PasteStateBF();
		virtual void slot_PreviosState();//��һ״̬
		virtual void slot_NextState();//��һ״̬
	virtual void slot_InsertStateBF();
	virtual void slot_InsertStateAF();
		//virtual void slot_PasteStateAF();
		//virtual void slot_CopyState();
	virtual void slot_DeleteState();
	virtual void slot_StatesIndexChanged(int nIndex);
	virtual void slot_BinarySet();
	virtual void slot_CommonPara();
	void slot_edt_Dc1();
	void slot_edt_Dc2();

	virtual void slot_SwitchStateChanged();

	virtual void slot_currentChangedTabWidget(int nCurrIndex);
// 	void slot_UpdateAuxDcEnabled();
};


extern QSttMacroParaEditViewPrimFreqState* g_pPrimFreqStateTest;

#endif // STTMACROPARAEDITVIEWSTATE_H
