#ifndef QSYNRESULTESTIMATEDLG_H
#define QSYNRESULTESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QTableWidgetItem>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "SttMultiMacroSynParasDefine.h"

namespace Ui {
class QSynResultEstimateDlg;
}

class QSynResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSynResultEstimateDlg(/*CDataGroup *pPara,*/QWidget *parent = 0);
    ~QSynResultEstimateDlg();
    void InitUI();
	void initBaseData();

    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);
	void SetTableWidgetItem(QTableWidgetItem *pItem, int nRow, int nCol);
	void ComboxModelStyle(QComboBox *pCombox, int nRow, int nCol);
	void SetLineEdit(QLineEdit *pLineEdit, int nRow, int nCol);
	void SetLabel(QLabel *pLabel, int nRow, int nCol);
	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);

	void CheckAllPresence();
	void CheckForPresence(CString strID);

	void CbbErrorType(int nIndex, CString strText);
	void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);

	void GetValueFromSelect(CString strID, int nindex);
	void GetValueFromSelect(CString strID, CString strID2);
public:
	CDataGroup *m_pCurrDataGroup;

	QComboBox *m_pCmb_AllowPressure;
	QComboBox *m_pCmb_AllowFre;
	QComboBox *m_pCmb_LeadAngle;
	QComboBox *m_pCmb_LeadTime;
	QComboBox *m_pCmb_Pressure;
	QComboBox *m_pCmb_Fre;
	QTableWidgetItem *m_pRelativeErrorEdit1;
    QLabel *m_pRelativeErrorLabel2;
	QLabel *m_pRelativeErrorLabel3;
	QLabel *m_pRelativeErrorLabel4;
	QTableWidgetItem *m_pRelativeErrorEdit5;
	QTableWidgetItem *m_pRelativeErrorEdit6;
	QTableWidgetItem *m_pAbsoluteErrorEdit1;
	QTableWidgetItem *m_pAbsoluteErrorEdit2;
	QTableWidgetItem *m_pAbsoluteErrorEdit3;
	QTableWidgetItem *m_pAbsoluteErrorEdit4;
	QTableWidgetItem *m_pAbsoluteErrorEdit5;
	QTableWidgetItem *m_pAbsoluteErrorEdit6;
	QLabel *m_pAbsoluteNegErrorLabel1;
	QLabel *m_pAbsoluteNegErrorLabel2;
	QLabel *m_pAbsoluteNegErrorLabel3;
	QLabel *m_pAbsoluteNegErrorLabel4;
	QTableWidgetItem *m_pAbsoluteNegErrorEdit5;
	QTableWidgetItem *m_pAbsoluteNegErrorEdit6;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

	void slot_cmbAllowPressureErrorChanged(const QString& strText);
	void slot_cmbPressureErrorChanged(const QString& strText);
	void slot_cmbFreErrorChanged(const QString& strText);
private:
    Ui::QSynResultEstimateDlg *ui;
	void InitLanuage();
	QStringList m_SynEstimateList;
protected slots:
void slot_OnCellChanged(int row, int col);
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
void CheckForPresence(CExBaseList *pParas,CString strID);
#endif // QSYNRESULTESTIMATEDLG_H
