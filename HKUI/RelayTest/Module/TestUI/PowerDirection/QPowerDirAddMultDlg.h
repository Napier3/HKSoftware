#ifndef QPowerDirAddMultDlg_H
#define QPowerDirAddMultDlg_H

#include <QDialog>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../UI/Controls/SttLineEdit.h"

namespace Ui {
	class QPowerDirAddMultDlg;
}

class QPowerDirAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QPowerDirAddMultDlg(QWidget *parent = 0);
	~QPowerDirAddMultDlg();
	
	//CDataGroup *m_pDataGroup;//当前页面参数
	CExBaseList *m_pDataGroup;//当前页面参数

	bool IsConnect;
	void SetParasFont();
    void InitUI();
	void initConnections();
	void initData();

	void SetDatas(/*CDataGroup *pParas*/CExBaseList *pParas);
	void GetDatas(CDataGroup *pParas);
	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);

private:
	Ui::QPowerDirAddMultDlg *ui;

	void CheckAllPresence();
	void CheckForPresence(CString strID);

	void OpenXmlFile();
	void SavePowerDirFile(CDataGroup *pParas);



private slots:
	float slot_lne_Changed(QSttLineEdit* pLineEdit);
	void slot_lneStep_editingFinished();
	void slot_lneMaxSensitAngle_editingFinished();
	void slot_lneActRange_editingFinished();
	void slot_lneFaultV_editingFinished();
	void slot_lneFaultI_editingFinished();
	void slot_lneFaultTime_editingFinished();
	void slot_lneAbsError_editingFinished();
	void slot_lneRelError_editingFinished();
	void slot_chb_TestTypeClicked();
	void slot_chb_ATypeClicked();
	void slot_chb_BTypeClicked();
	void slot_chb_CTypeClicked();
	void slot_chb_ABTypeClicked();
	void slot_chb_BCTypeClicked();
	void slot_chb_CATypeClicked();
	void slot_chb_ZeroTypeClicked();
	void slot_chb_NegativeTypeClicked();
	void slot_chb_ATestClicked();
	void slot_chb_BTestClicked();
	void slot_chb_CTestClicked();
	void slot_chb_ABTestClicked();
	void slot_chb_BCTestClicked();
	void slot_chb_CATestClicked();
	void slot_chb_ZeroSeqTestClicked();
	void slot_chb_NegativeSeqTestClicked();

	void slot_cmb_EerrorType_Changed();

	void slot_pbn_OKClick();
	void slot_pbn_CancelClick();
	//void slot_pbn_ResultsClicked();

};

#endif // QPowerDirAddMultDlg_H
