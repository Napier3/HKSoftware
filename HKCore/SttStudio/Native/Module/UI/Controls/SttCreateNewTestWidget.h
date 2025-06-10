#ifndef STTCREATENEWTESTWIDGET_H
#define STTCREATENEWTESTWIDGET_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/OSInterface/OSInterface.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SmartTestInterface/PpSttCommConfig.h"

namespace Ui {
class QSttCreateNewTestWidget;
}

class QSttCreateNewTestWidget : public QDialog
{
    Q_OBJECT

public:
    explicit QSttCreateNewTestWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCreateNewTestWidget();

    QFont m_font;
	void UI_SetFont();
    void EnableOK();

	CString m_strLocalIP;
	long GetDeviceTypeIndex(const CString &strType);
       void InitLanguage();
public slots:
	void slot_OKClick();
	void slot_CancelClick();
	void slot_SelDvmFileClick();
	void slot_SelPpFileClick();
	void slot_SelIedFromSclClick();
	void slot_AdvancedCfgClick();


signals:
private slots:
    void on_m_edtDevIP_textChanged(const QString &arg1);
    void on_m_edtDevPort_textChanged(const QString &arg1);
	void on_m_cmbEngineID_currentIndexChanged(int index);
	void on_m_cmbDeviceType_currentIndexChanged(int index);
    void on_m_chkTSettingUnit_ms_clicked();
	void on_m_chkAddDevReset_clicked();


private:
    Ui::QSttCreateNewTestWidget *ui;
};

#endif // STTCREATENEWTESTWIDGET_H
