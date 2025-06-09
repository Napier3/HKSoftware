#ifndef DISTANCEBINARYSDLG_H
#define DISTANCEBINARYSDLG_H

#include <QDialog>
#include "./DistanceCommonParasDlg.h"

namespace Ui {
class QDistanceBinarysDlg;
}

class QDistanceBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceBinarysDlg(QWidget *parent = 0);
    ~QDistanceBinarysDlg();

	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);
private slots:
	void on_m_cmbSel_currentIndexChanged(int index);
	void on_m_cmb_SwitchMode_currentIndexChanged(int index);

	void on_m_txtDelayTime_editingFinished();
	void on_m_txtKeepTime_editingFinished();

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDistanceBinarysDlg *ui;
	CDataGroup *m_pParas;
	void InitUI();
	void CheckInputSel(int index);

	void SetValueToPage(CShortData *pData);
	void GetPageToValue(CShortData *pData);
};

#endif // DISTANCEBINARYSDLG_H
