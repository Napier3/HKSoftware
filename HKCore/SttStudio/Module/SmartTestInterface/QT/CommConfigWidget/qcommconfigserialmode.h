#ifndef QCOMMCONFIGSERIALMODE_H
#define QCOMMCONFIGSERIALMODE_H

#include <QDialog>
#include <QComboBox>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../PpSttCommConfig.h"

namespace Ui {
class QCommConfigSerialMode;
}

class QCommConfigSerialMode : public QDialog
{
    Q_OBJECT

public:
    explicit QCommConfigSerialMode(QWidget *parent = 0);
    ~QCommConfigSerialMode();

    CDvmData *m_pSerial;
    CPpSttCommConfig *m_pCommConfig;

    //void ShowData(CDvmData *pData);
    void ShowData(CPpSttCommConfig *pCommConfig);
    void SaveData();
	void SetComboSelIndex(QComboBox* pCombo, CString strNameFind);


private slots:

private:
    Ui::QCommConfigSerialMode *ui;
};

#endif // QCOMMCONFIGSERIALMODE_H
