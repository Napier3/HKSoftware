#ifndef QCOMMCFGTCPCLIENTDLG_H
#define QCOMMCFGTCPCLIENTDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCommCfgTcpClientDlg;
}

class QCommCfgTcpClientDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCommCfgTcpClientDlg(QWidget *parent = 0);
    ~QCommCfgTcpClientDlg();
    CDvmData *m_pTcpClient;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();

private slots:

private:
    Ui::QCommCfgTcpClientDlg *ui;
};

#endif // QCOMMCFGTCPCLIENTDLG_H
