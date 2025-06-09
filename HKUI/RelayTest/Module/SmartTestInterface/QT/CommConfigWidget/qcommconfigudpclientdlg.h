#ifndef QCOMMCONFIGUDPCLIENTDLG_H
#define QCOMMCONFIGUDPCLIENTDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCommConfigUdpClientDlg;
}

class QCommConfigUdpClientDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCommConfigUdpClientDlg(QWidget *parent = 0);
    ~QCommConfigUdpClientDlg();

    CDvmData *m_pUdpClient;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();

private slots:

    void on_m_chkIsBroadcast_stateChanged(int arg1);

private:
    Ui::QCommConfigUdpClientDlg *ui;
};

#endif // QCOMMCONFIGUDPCLIENTDLG_H
