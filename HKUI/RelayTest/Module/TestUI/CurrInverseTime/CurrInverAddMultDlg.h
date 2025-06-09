#ifndef CURRINVERADDMULTDLG_H
#define CURRINVERADDMULTDLG_H

#include <QDialog>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "SttMultiMacroCurrInverseTimeParasDefine.h"

namespace Ui {
class QCurrInverAddMultDlg;
}

class QCurrInverAddMultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCurrInverAddMultDlg(QWidget *parent = 0);
    ~QCurrInverAddMultDlg();

	void InitUI();
	void InitFont();
	void initConnections();
	void OpenXmlFile();
	void SaveCurInverFile(CDataGroup *pParas);

	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);
	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);

	void GetValueFromSelect(CString strID);
	void GetPageFromSelect();
	void CheckAllPresence();
	void CheckForPresence(CString strID);
	virtual void InitLanuage();
	CDataGroup *m_pDataGroup;//当前页面参数

private slots:
    void on_m_cmbSelect_currentIndexChanged(int index);
    void on_m_lineFaultVolt_editingFinished();
    void on_m_lineFaultAngle_editingFinished();
    void on_m_lineHz_editingFinished();
    void on_m_lineChangeStart_editingFinished();
    void on_m_lineChangeFinal_editingFinished();
    void on_m_lineChangeStep_editingFinished();
    void on_m_cmbErrorLogic_currentIndexChanged(int index);
    void on_m_lineRelErr_editingFinished();
    void on_m_linePlus_editingFinished();
    void on_m_lineMinus_editingFinished();
    void on_pbn_Ok_clicked();
    void on_pbn_Cancel_clicked();

	void slot_chb_faultTypeClicked();
	//void slot_ResultEstimateClick();

private:
    Ui::QCurrInverAddMultDlg *ui;
};

extern CFont *g_pSttGlobalFont;  

#endif // CURRINVERADDMULTDLG_H
