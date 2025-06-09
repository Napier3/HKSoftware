#ifndef QRECLOSEADDMULTDLG_H
#define QRECLOSEADDMULTDLG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../UI/Controls/SttCheckBox.h"
#include <QGroupBox>
#include "ui_QRecloseAddMultDlg.h"
#include "QRecloseResultAssessDlg.h"
#include "QRecloseCommonParasDlg.h"
#include "../../DataMngr/DataGroup.h"
#include "../../DataMngr/DataMngrGlobal.h"
#include "../../API/GlobalConfigApi.h"
#include "../../UI/Controls/SttCheckBox.h"
namespace Ui{
	class QRecloseAddMultDlg;
}

class QRecloseAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::QRecloseAddMultDlg *ui;

	QRecloseAddMultDlg(QWidget *parent = 0);
	virtual ~QRecloseAddMultDlg();


public:
	CDataGroup *m_pRecloseAccDataGroup;

public:
    void InitUI();  //20241024 wanmj
	void initUI();
	void initFont();
	void initConnect();
	void initDatas();
	void ShowOneChecked(QCheckBox* currentCheckBox, bool state);
	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);
	void GetValue();

public slots:
	void slot_NoPreCheck();
	void slot_SamPerCheck(bool state);
	void slot_RecCheck(bool state);
	void slot_AftAccCheck(bool state);
	void slot_CmbK0Mode(int nIndex);
    void slot_FrequencyCheck(bool state);
	void slot_ResultAssess();
    //void slot_CommonParas();

	void slot_FaultNoPreCheck();
	void slot_FaultSamPerCheck();
	void slot_FaultRecCheck();
	void slot_FaultAftAccCheck();
	void slot_MultipleNoPreCheck();
	void slot_MultipleSamPerCheck();
	void slot_NoPreSet();
	void slot_SynAngleSetting();
	void slot_Z1();
	void slot_Z1Ph();
	void slot_ISet1();
	void slot_KlKr();
	void slot_AngKx();
	void slot_Exit();
	void slot_Ok();
	void slot_ActionTime();
	void slot_Reclose();
	void slot_Frequency();

	void slot_MultipleFrequencyCheck();
	void slot_frequencyCheck();
};

#endif 
