#ifndef _PpSttIotEngineClientWidgetBase_H_
#define _PpSttIotEngineClientWidgetBase_H_

#include <QDialog>
#include <QFont>
#include "../../../../Module/API/StringApi.h"

#include "../PpSttIotEngineClientApp.h"
#include "PpSttIotEngineClientAppWnd.h"
#include "PpSttIotEngineClientWidget.h"

class CPpSttIotEngineClientInterface
{
public:
	virtual void OnCommCommandMsg(WPARAM wParam,LPARAM lParam) = 0;
	virtual void OnEngineSystemMessage(WPARAM wParam, LPARAM lParam) = 0;
};


class QPpSttIotEngineClientWidgetMain : public QPpSttIotEngineClientWidget
{
    Q_OBJECT

public:
    explicit QPpSttIotEngineClientWidgetMain(QWidget *parent = 0);
    virtual ~QPpSttIotEngineClientWidgetMain();

	virtual void NewPpSttIotDeviceClient(CPpSttCommConfig *pCommConfig, CDvmDevice *pDvmDevice);
	virtual void OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam);
    virtual void OnEngineSystemMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam);

	void UpdateTitleAndSize(const CString &strTitle,long nWidth,long nHeight);

	void emit_sig_NewDevice()
	{
		emit sig_NewDevice();
	}

	CPpSttIotEngineClientInterface *m_pPpSttIotEngineClientInterface;
	//QTimer m_oInitCmdTimer;

public slots:
    void slot_NewDevice();
	void slot_InitCmdTimer();//发送初始化命令的槽函数

signals:
    void sig_NewDevice();

};

QPpSttIotEngineClientWidgetMain* CreateEngineClientWidgetMain();
void ReleaseEngineClientWidgetMain();

#ifdef _SttIotEngineClientWidgetMain_
void PopNewDeviceDlg();
#endif


#endif // _PpSttIotEngineClientWidgetBase_H_
