#ifndef SttCreateNewDeviceWidget_H
#define SttCreateNewDeviceWidget_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/OSInterface/OSInterface.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SmartTestInterface/PpSttCommConfig.h"

namespace Ui {
class QSttCreateNewDeviceWidget;
}

class QSttCreateNewDeviceWidget : public QDialog
{
    Q_OBJECT

public:
    explicit QSttCreateNewDeviceWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCreateNewDeviceWidget();

    QFont m_font;
	void UI_SetFont();
    void EnableOK();
	void SaveDevInfoToCfg();   //将IP、设备信息写入通讯模块的配置文件中
	void SaveDevInfoToCfg_MMS(); 
	void SaveDevInfoToCfg_CMS(); 

	CPpSttCommConfig m_oCommConfig;
	CString m_strLocalIP;

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

private:
    Ui::QSttCreateNewDeviceWidget *ui;
};

#endif // SttCreateNewDeviceWidget_H
