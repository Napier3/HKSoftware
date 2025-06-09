#ifndef STTMACROPARAEDITVIEWTRANSPLAY_H
#define STTMACROPARAEDITVIEWTRANSPLAY_H

#include <QMainWindow>
#include <QTimer>
#include "../../SttTest/Common/tmt_replay_test.h"
#include "../../ReplayTest/SttModuleChComtradeBind.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "SttReplayParaSetWidget.h"
#include "../Module/WaveGraphWidget/QWaveGraphWidget.h"
#include "../Module/CommonCtrl_QT/QSttProgDlg.h"


typedef struct replay_Output_Type_sel
{
	int nAnalogSel;
	int nDigtalSel;
	int nWeekSel;
	
	void init()
	{
		nAnalogSel = -1;
		nDigtalSel = -1;
		nWeekSel = -1;
	}
}ReplayOutputTypeSel;


class QSttMacroParaEditViewTransPlay: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
    QSttMacroParaEditViewTransPlay(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewTransPlay();

	virtual void SetDatas(CDataGroup *pParas);
	virtual void GetDatas(CDataGroup *pParas);
	virtual bool PrepStartTest();//zhouhj 20221027 开始测试前的准备工作
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oTmtReplayTest;}
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual void UpdateTestResource(BOOL bCreateChMaps);

public:
	void initUI();
	void initConnections();
	void initData();
	void Updata_ChMapConfig();//zhouhj 20210821在测试仪硬件信息切换后,需要重新更新硬件通道映射文件
	void StartProgDlg(const CString &strTitle);
	void CreateWaveGraphByComtrade();
	void CopyBinaryConfig(BOOL b=TRUE);
	void SwitchStateChanged();//2024.1.19  zhangyq新增

	void StartInsertWaveThread();//插入波形
	void ReCoveryWave();
	bool isNeedAnalogModule();//需要模拟量模块
	bool isNeedDigitalModule();//需要数字量模块
	bool isNeedWeekModule();
	bool isNeedBinaryModule();


	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual QWidget* GetWaveWidget();

public:
	tmt_ReplayTest m_oTmtReplayTest;
	QBoxLayout* m_pMainLayout;	
	CSttReplayParaSetWidget *m_ParaSetWidget;
	CSttModulesComtradeBind *m_pSttModulesComtradeBind;
	QWaveGraphWidget *m_pWaveGraphWidget;
	QSttProgDlg *m_pSttProgDlg;
	CString m_strComtradeFilePath;
	ReplayOutputTypeSel m_oOutputType;//新增存储输出类型选择

protected:
	void UpdateEditData();

	bool m_bReadComtradeFile;		//已经有Comtrade数据
	QTimer m_oProgTimer;
	bool m_bRecoverWave;//是否为波形复归

public:
	void OpenComtradeFile();
//	BOOL OpenComtradeFile(const CString &strComtradeFile,BOOL bInitDefault=TRUE);
	bool HasFT3ChMap();//输出报文类型为FT3（柔直/普通）,是否有映射到数字量前两组数据
	int GetFT3MaxCodeValue(int nChannelGroupIndex, CSttModuleChComtradeBind *pCh);
	bool CalDigitalChMaxValue(CSttModuleChComtradeBind *pCh, int nChannelGroupIndex);
	bool VaildDigitalChMaxValue(CSttModuleComtradeBind *pModule);
	bool VaildDigitalChMaxValue();

#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttOpenComtradeFileThread;
    static void* SttOpenComtradeFileThread(LPVOID pParam);
	
	//插入波形线程
	pthread_t m_pSttInsertWaveThread;
	static void* SttInsertWaveThread(LPVOID pParam);
#else
	HANDLE m_pSttOpenComtradeFileThread;
	static UINT SttOpenComtradeFileThread(LPVOID pParam);

	HANDLE m_pSttInsertWaveThread;
	static UINT SttInsertWaveThread(LPVOID pParam);

#endif

signals:
	void sig_UpdateDrawWaveGraph();
	void sig_UpdateOpenComtradeFile(int bRet);

protected slots:		
	void slot_ModuleChChanged(int nModuleIndex,int nChIndex);//用于更新波形图
	void slot_ModuleChRangeChanged();//模块通道范围改变了
	void slot_Timer();
	void slot_UpdateOpenComtradeFile(int bRet);
};

extern QSttMacroParaEditViewTransPlay* g_pReplayTestMain;

#endif // STTMACROPARAEDITVIEWTRANSPLAY_H
