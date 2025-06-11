#ifndef PPCOMMCONFIGDLG_H
#define PPCOMMCONFIGDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

#include <QTabWidget>
#include "qcommconfigserialmode.h"
#include "qcommconfigcmsdlg.h"
#include "qcommconfigmmsdlg.h"
#include "qcommconfigtcpserverdlg.h"
#include "qcommcfgtcpclientdlg.h"
#include "qcommconfigudpclientdlg.h"
#include "qcommconfigudpserver.h"

namespace Ui {
class PpCommConfigDlg;
}

class PpCommConfigDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PpCommConfigDlg(CPpSttCommConfig *pCommConfig, QWidget *parent = 0);
    ~PpCommConfigDlg();

    //CDvmData *m_pTcpClient;
    CPpSttCommConfig *m_pCommConfig;
    QTabWidget *m_pTabCmmConfig;

    QCommConfigSerialMode         *m_pWidgetSerialMode;
    QCOmmConfigCmsDlg               *m_pWidgetCmsMode;
    QCommConfigMmsDlg               *m_pWidgetMmsMode;
    QCommConfigServerDlg           *m_pWidgetTcpServer;
    QCommCfgTcpClientDlg            *m_pWidgetTcpClient;
    QCommConfigUdpServer          *m_pWidgetUdpServer;
    QCommConfigUdpClientDlg      *m_pWidgetUdpClient;

    void DeleteAllCfgWidget();
    void DeleteNetCfgWidget();
    void HasChangedData();
    void ChangedNetModeUnChecked();        //使复选框全变为未选中

    void ShowData(CPpSttCommConfig *pCommConfig);
	void ShowData();
    void SaveData();
	void SaveSttCommConfigFile();

private slots:
    void on_m_btnSerial_clicked();
    void on_m_btnCms_clicked();
    void on_m_btnNet_clicked();
    void on_m_btnMms_clicked();
    void on_m_btnTcpServer_stateChanged(int arg1);
    void on_m_btnTcpClient_stateChanged(int arg1);
    void on_m_btnUdpServer_stateChanged(int arg1);
    void on_m_btnUdpClient_stateChanged(int arg1);
    void on_m_btnSave_clicked();
    void on_m_btnCancel_clicked();

private:
    Ui::PpCommConfigDlg *ui;
};

#endif // PPCOMMCONFIGDLG_H
