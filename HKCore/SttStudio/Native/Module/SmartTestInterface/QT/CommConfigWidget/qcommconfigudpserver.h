#ifndef QCOMMCONFIGUDPSERVER_H
#define QCOMMCONFIGUDPSERVER_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCommConfigUdpServer;
}

class QCommConfigUdpServer : public QDialog
{
    Q_OBJECT

public:
    explicit QCommConfigUdpServer(QWidget *parent = 0);
    ~QCommConfigUdpServer();

    CDvmData *m_pUdpServer;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();

private slots:

    void on_isBroadcast_stateChanged(int arg1);

private:
    Ui::QCommConfigUdpServer *ui;
};

#endif // QCOMMCONFIGUDPSERVER_H
