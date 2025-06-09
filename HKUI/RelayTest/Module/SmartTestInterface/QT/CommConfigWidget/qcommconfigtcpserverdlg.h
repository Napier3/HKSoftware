#ifndef QCOMMCONFIGSERVERDLG_H
#define QCOMMCONFIGSERVERDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCommConfigServerDlg;
}

class QCommConfigServerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCommConfigServerDlg(QWidget *parent = 0);
    ~QCommConfigServerDlg();

    CDvmData *m_pTcpServer;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();

private slots:


private:
    Ui::QCommConfigServerDlg *ui;
};

#endif // QCOMMCONFIGSERVERDLG_H
