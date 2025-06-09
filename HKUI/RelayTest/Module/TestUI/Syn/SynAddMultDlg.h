#ifndef QSynAddMultDlg_H
#define QSynAddMultDlg_H

#include <QDialog>
#include <QObject>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../UI/Controls/SttLineEdit.h"
#include "../../UI/Controls/SttCheckBox.h"

namespace Ui {
	class QSynAddMultDlg;
}


class QSynAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QSynAddMultDlg(QWidget *parent = 0);
	virtual  ~QSynAddMultDlg();
	
	CDataGroup *m_pDataGroup;//当前页面参数

	void SetParasFont();
	void initConnections();
	void init();
	void initData();
	void InitUI();

	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);
	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);

	void CheckAllPresence();
	void CheckForPresence(CString strID);
	void OpenXmlFile();
	void SaveSynFile(CDataGroup *pParas);

private:
	Ui::QSynAddMultDlg *ui;
	void InitLanuage();

private slots:
	float slot_lne_Changed(QLineEdit* pLineEdit);
	void slot_lneAllowPressure_editingFinished();
	void slot_lneAllowFre_editingFinished();
	void slot_lneLeadAnglet_editingFinished();
	void slot_lneLeadTime_editingFinished();
	void slot_lnePressure_editingFinished();
	void slot_lneFre_editingFinished();
	void slot_lneDescalingV_editingFinished();
	void slot_lneDescalingV2_editingFinished();
	void slot_lneDescalingV3_editingFinished();
	void slot_lneDescalingV4_editingFinished();
	void slot_lneDescalingV5_editingFinished();
	void slot_lneDescalingV6_editingFinished();
	void slot_lneDescalingF_editingFinished();
	void slot_lneDescalingF2_editingFinished();
	void slot_lneDescalingF3_editingFinished();
	void slot_lneDescalingF4_editingFinished();
	void slot_lneDescalingF5_editingFinished();
	void slot_lneDescalingF6_editingFinished();
	
	void slot_lneVolChangeStep_editingFinished();
	void slot_lneFreChangeStep_editingFinished();
	
	void slot_chb_TestItemsClicked();
	void slot_chb_VolBoundTest_Click();
	void slot_chb_FreBoundTest_Click(); 
	void slot_chb_LeadTest_Click();
	void slot_chb_SelfAdjustTest_Click();
	void slot_chb_PressureTest_Click();
	void slot_chb_FreTest_Click();

	void slot_pbn_OKClick();
	void slot_pbn_CancelClick();
	//void slot_pbn_BinaryConfigClicked();
	void slot_pbn_ResultsClicked();
	//void slot_pbn_CommonParasClicked();




};

#endif //QSynAddMultDlg_H
