#ifndef QSTTCAPIOTENGINEFRAMEBASE_H
#define QSTTCAPIOTENGINEFRAMEBASE_H
#include "..\XLanguage\XLanguageResource.h"
#include "..\DataMngr\DvmDevice.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgDatasMngr.h"
#include "..\SmartCap\XSttCap_61850.h"
#include "..\KeyDb\XKeyDB.h"
#include "..\SmartCap\61850Cap\CapDevice\CapDevice92.h"
#include <QTimer>
#include <QMainWindow>
#include "..\Log\LogPrint.h"
class QSttCapIotEngineFrameBase:public QMainWindow, public CLogBase
{
	Q_OBJECT
public:
	QSttCapIotEngineFrameBase(QWidget *parent = NULL);
	virtual~QSttCapIotEngineFrameBase();

	BOOL m_bConnected;
	CXKeyDB m_oKeyDB;
	CXSttCap_61850 *m_pXSttCap_61850;
	CDvmDevice m_oDvmDevice;//设备数据模型
	CIecCfgDatasMngr m_oIecDatasMngr;//Iec配置
	CCapDevice92 *m_pCapDevice92;
	QTimer m_oTimerClearPkgStc;//用于报文统计复归

	void CreatSever();//创建服务端
	void ExitServer();//析构服务端
	BOOL BeginIecRecord();//进入录波通道监视
	void ExitIecRecord();//退出监视
	void SttOpen();//g_oSttTestAppCfg读取配置
	void StartClearPkgStc(int nDelayTime);

	void InitIecCfg();
	void InitDevMods();
	BOOL ConnectState() {return m_bConnected;};

	virtual void InitTestApp(CXLanguageResourceBase *pLanguage=NULL);
	virtual void ExitTestApp();
	virtual void InitSttIecRecord(CSttTestAppCfg* pSttTestAppCfg);
	virtual void ExitSttIecRecord();
	virtual void InitKeyDB();

signals:
	void sig_ClearPkgStc();
	void sig_StartClearPkgStc(int nDelayTime);

public slots:
	void slot_ClearPkgStc();//清空报文统计
	void slot_StartClearPkgStc(int nDelayTime);
};

#endif