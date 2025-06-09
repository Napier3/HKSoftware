#ifndef QVolInverAddMultDlg_H
#define QVolInverAddMultDlg_H

#include <QDialog>
//#include "ui_VolInverAddMultDlg.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../UI/Controls/SttLineEdit.h"

namespace Ui {
class QVolInverAddMultDlg;
}


class QVolInverAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QVolInverAddMultDlg(QWidget *parent = 0);
    ~QVolInverAddMultDlg();
	
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);
    void SetValueToPage(CDvmData *pData);
    void GetPageToValue(CDvmData *pData);

private:
    Ui::QVolInverAddMultDlg *ui;

	//CDataGroup m_oDataGroup;//当前页面参数

	void SetParasFont();
	void initConnections();
	void init();
	void initData();
	void initBaseData();

	virtual void InitLanuage();
	void CheckAllPresence();
	void CheckForPresence(CString strID);

	void OpenXmlFile();
	void SaveVolInverFile(CDataGroup *pParas);

	CDataGroup *m_pDataGroup;//当前页面参数

private slots:
	float slot_lne_Changed(QLineEdit* pLineEdit);
	/*void slot_lnePreFTime_editingFinished();
	void slot_lneFTimeMargin_editingFinished();
	void slot_lneVoltage_editingFinished();
	void slot_lneCurrent_editingFinished();
	void slot_lnePhaseDiff_editingFinished();*/
	void slot_lneVChangeStart_editingFinished();
	void slot_lneVChangeEnd_editingFinished();
	void slot_lneVChangeStep_editingFinished();
	void slot_lneDLCurrent_editingFinished();
	void slot_lneFPhaseDiff_editingFinished();
	void slot_lneFre_editingFinished();
	void slot_lneRelative_editingFinished();
	void slot_lneAbsAdd_editingFinished();
	void slot_lneAbsDown_editingFinished();
	//void slot_cmb_CT_Changed(int);
	void slot_cmb_ErrorType_Changed(int);
	void slot_chb_faultTypeClicked();

	void slot_pbn_OKClick();
	void slot_pbn_CancelClick();
	//void slot_pbn_CommonParasClicked();
	//void slot_pbn_ResultsClicked();



};

#endif // QVolInverAddMultDlg_H
