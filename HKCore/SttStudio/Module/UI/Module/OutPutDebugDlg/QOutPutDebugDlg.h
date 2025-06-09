#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QWidget>
#include <QStringList>
#include <QTableWidget>
#include <QTabWidget>
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../ChannelParaSet/QBasicTestParaSet.h"
#include "../ChannelParaSet/QBasicTestParaSetImp.h"
#include "../ChannelParaSet/QParaSetBase.h"
#include "../../../SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../../../SttTest/Common/tmt_manu_test.h"
#include "../SttUIDefine.h"
#include "../../../SttTestAppConfig/SttTestAppCfg.h"
#include "../../../../../Module/Socket/XPing.h"
#include "../../../TestClient/SttAtsTestClient.h"
#include "../../../SttCmd/SttTestCmd.h"
#include "../../../SttGlobalDef.h"
#include "../../../SttTest/Common/tmt_test_mngr.h"
#include "../ChannelParaSet/channeltable.h"
#include "../../../Engine/SttPowerTestEngineBase.h"
#include "../../../../../Module/API/GlobalConfigApi.h"

extern CSttTestAppCfg g_oSttTestAppCfg; 
 #define  Time_HeartbeatTimeGap 10000

class QOutPutDebug : public QDialog , public CSttPowerTestEngineBase 
{
	Q_OBJECT

public:

	QOutPutDebug(QWidget *parent = 0);
	virtual ~QOutPutDebug();

    tmt_manual_test m_oManualTest;
	CSttTestResourceBase *m_pParaSetSttTestResource;
	QBasicTestParaSet *m_pUIParaSet;
	BOOL m_bHasClosed;
	BOOL m_IsConnected;
    long m_nTimerID;

	void InitUI();
    void InitConnection();
	void InitUIGrid();

	QVBoxLayout* m_pAllVLayout;
	QHBoxLayout* m_pGrideLayout;
	QHBoxLayout* m_pButtonLayout;
	QPushButton* m_pbtnClose;
	QPushButton* m_ptnStartOutPut;
	QPushButton* m_ptnStopOutput;

    BOOL OnConnectTestApp();
	BOOL OnConnectTestApp(const CString &strIP, long nPort);
	BOOL IsTestAppExist(const CString &strIP);

	long SendDebugOutputCmd();
	long StopDebugOutputCmd();
	long SendUpdateParaCmd();
	long DisConnectCmd();
	void InitTestCmdFromParas(CSttTestCmd &oSttTestCmd, const CString &strCmdID);
   
public slots:
	void slot_CloseClicked();
	void slot_StartOutput();
	void slot_StopOutput();
	void slot_Paraschanged();
	
protected:
	virtual void timerEvent(QTimerEvent * );

};

