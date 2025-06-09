#ifndef RESULTESTIMATEDLG_H
#define RESULTESTIMATEDLG_H

#include <QDialog>
#include <QComboBox>
//#include "../SttTestCntrFrameApi.h"
#include "./DistanceCommonParasDlg.h"


namespace Ui {
class QDistanceResultEstimateDlg;
}

class QDistanceResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceResultEstimateDlg(QWidget *parent = 0);
    ~QDistanceResultEstimateDlg();

	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);

private slots:
    void on_m_btnOK_clicked();
    void on_m_btnCancel_clicked();

	void on_m_txtRel1_editingFinished();
	void on_m_txtPlus_1_editingFinished();
	void on_m_txtMinus_1_editingFinished();

	void on_m_txtRel2_editingFinished();
	void on_m_txtPlus_2_editingFinished();
	void on_m_txtMinus_2_editingFinished();

	void on_m_txtRel3_editingFinished();
	void on_m_txtPlus_3_editingFinished();
	void on_m_txtMinus_3_editingFinished();

	void on_m_txtRel4_editingFinished();
	void on_m_txtPlus_4_editingFinished();
	void on_m_txtMinus_4_editingFinished();

	void on_m_txtRel5_editingFinished();
	void on_m_txtPlus_5_editingFinished();
	void on_m_txtMinus_5_editingFinished();
private:
    Ui::QDistanceResultEstimateDlg *ui;

	CDataGroup *m_pParas;

	void InitUI();
	void SetValueToPage(int nRow);
	bool CheckZone(int nZone);
	void GetPageToValue(int nRow);
};

extern bool Stt_Global_IsSetting(QObject *pObject);		//20240805 huangliang 

#endif // RESULTESTIMATEDLG_H
