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

class QSttMacroParaEditViewTransPlay: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
    QSttMacroParaEditViewTransPlay(QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
	virtual ~QSttMacroParaEditViewTransPlay();

	virtual void SetDatas(CDataGroup *pParas);
	virtual void GetDatas(CDataGroup *pParas);
	virtual bool PrepStartTest();//zhouhj 20221027 ��ʼ����ǰ��׼������
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oTmtReplayTest;}
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual void UpdateTestResource(BOOL bCreateChMaps);

public:
	void initUI();
	void initConnections();
	void initData();
	void Updata_ChMapConfig();//zhouhj 20210821�ڲ�����Ӳ����Ϣ�л���,��Ҫ���¸���Ӳ��ͨ��ӳ���ļ�
	void StartProgDlg(const CString &strTitle);
	void CreateWaveGraphByComtrade();
	void CopyBinaryConfig(BOOL b=TRUE);
	void SwitchStateChanged();//2024.1.19  zhangyq����

	void StartInsertWaveThread();//���벨��
	void ReCoveryWave();
	bool isNeedAnalogModule();//��Ҫģ����ģ��
	bool isNeedDigitalModule();//��Ҫ������ģ��
	bool isNeedWeekModule();
	bool isNeedBinaryModule();


	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

public:
	tmt_ReplayTest m_oTmtReplayTest;
	QBoxLayout* m_pMainLayout;	
	CSttReplayParaSetWidget *m_ParaSetWidget;
	CSttModulesComtradeBind *m_pSttModulesComtradeBind;
	QWaveGraphWidget *m_pWaveGraphWidget;
	QSttProgDlg *m_pSttProgDlg;
	CString m_strComtradeFilePath;

protected:
	void UpdateEditData();

	bool m_bReadComtradeFile;		//�Ѿ���Comtrade����
	QTimer m_oProgTimer;
	bool m_bRecoverWave;//�Ƿ�Ϊ���θ���

public:
	void OpenComtradeFile();
//	BOOL OpenComtradeFile(const CString &strComtradeFile,BOOL bInitDefault=TRUE);

#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttOpenComtradeFileThread;
    static void* SttOpenComtradeFileThread(LPVOID pParam);
	
	//���벨���߳�
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
	void slot_ModuleChChanged(int nModuleIndex,int nChIndex);//���ڸ��²���ͼ
	void slot_ModuleChRangeChanged();//ģ��ͨ����Χ�ı���
	void slot_Timer();
	void slot_UpdateOpenComtradeFile(int bRet);
};

extern QSttMacroParaEditViewTransPlay* g_pReplayTestMain;

#endif // STTMACROPARAEDITVIEWTRANSPLAY_H
