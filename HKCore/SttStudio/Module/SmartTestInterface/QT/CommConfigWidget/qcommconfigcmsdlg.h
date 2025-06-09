#ifndef QCOMMCONFIGCMSDLG_H
#define QCOMMCONFIGCMSDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCOmmConfigCmsDlg;
}

class QCOmmConfigCmsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCOmmConfigCmsDlg(QWidget *parent = 0);
    ~QCOmmConfigCmsDlg();

    CDvmData *m_pCms;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();

private slots:

    void on_isClientIP_stateChanged(int arg1);

private:
    Ui::QCOmmConfigCmsDlg *ui;
};

#endif // QCOMMCONFIGCMSDLG_H
