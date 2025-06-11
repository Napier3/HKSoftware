#ifndef PpSttIotEngineDebugWIDGET_H
#define PpSttIotEngineDebugWIDGET_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/API/StringApi.h"

#include "../PpSttIotEngineClientApp.h"

class QPpSttIotEngineDebugWidget;

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineDebugWidgetWnd
class QPpSttIotEngineDebugWidgetWnd : public CWnd
{
    Q_OBJECT

public:
	QPpSttIotEngineDebugWidgetWnd();
	virtual ~QPpSttIotEngineDebugWidgetWnd();

public://CWnd
	//重载函数OnWndMsg，实现消息处理
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent) ;

	QPpSttIotEngineDebugWidget *m_pRefWidget;

signals:
    void sig_OnCommCommandMsg(int wParam,int lParam);
    void sig_OnEngineSystemMessage(int wParam, int lParam);

};

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineDebugWidget
namespace Ui {
class QPpSttIotEngineDebugWidget;
}

class QPpSttIotEngineDebugWidget : public QDialog, public CLogBase
{
    Q_OBJECT

public:
    virtual void LogString(long nLevel, const CString &strMsg);
    virtual void LogString(long nLevel, const char *strMsg);

public:
    explicit QPpSttIotEngineDebugWidget(QWidget *parent = 0);
    virtual ~QPpSttIotEngineDebugWidget();

	QPpSttIotEngineDebugWidgetWnd m_oEngineMsgWnd;

public://CWnd
	//重载函数OnWndMsg，实现消息处理
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent) ;

	virtual void OnCommCommandMsg(WPARAM wParam,LPARAM lParam);
	virtual void OnEngineSystemMessage(WPARAM wParam, LPARAM lParam);

    void ShowDatasetAfterCmd();
    void ShowDatasetAfterCmd(CDvmDataset *pDataset);

private:
	void EnableBtns();

signals:
    void sig_OnCommCommandMsg(int wParam,int lParam);
    void sig_OnEngineSystemMessage(int wParam, int lParam);

private slots:
    void slot_OnCommCommandMsg(int wParam,int lParam);
    void slot_OnEngineSystemMessage(int wParam, int lParam);

    void on_m_btnCreateDevice_clicked();
    void on_m_btnCloseDevice_clicked();
    void on_m_btnReadAin_clicked();
    void on_m_btnWriteEna_clicked();
    void on_m_btnConnectDevice_clicked();
    void on_m_btnPpEngine_clicked();
    void on_m_btnMmsEngine_clicked();
    void on_m_btnCmsEngine_clicked();
    void on_m_btnReadSetting_clicked();
    void on_m_btnReadEna_clicked();
    void on_m_btnWriteSetting_clicked();
    void on_m_chkSttFormat_stateChanged(int arg1);
    void on_m_btnClose_clicked();

private:
    Ui::QPpSttIotEngineDebugWidget *ui;
};

void Create_PpSttIotEngineDebugWidget();
void Release_PpSttIotEngineDebugWidget();

#endif // PpSttIotEngineDebugWIDGET_H
