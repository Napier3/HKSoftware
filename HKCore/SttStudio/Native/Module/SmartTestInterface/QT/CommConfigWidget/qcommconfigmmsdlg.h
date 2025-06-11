#ifndef QCOMMCONFIGMMSDLG_H
#define QCOMMCONFIGMMSDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCommConfigMmsDlg;
}

class QCommConfigMmsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCommConfigMmsDlg(QWidget *parent = 0);
    ~QCommConfigMmsDlg();

    CDvmData *m_pMms;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();

private slots:

private:
    Ui::QCommConfigMmsDlg *ui;
};

#endif // QCOMMCONFIGMMSDLG_H
