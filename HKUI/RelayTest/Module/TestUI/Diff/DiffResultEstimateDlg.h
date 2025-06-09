#ifndef DIFFRESULTESTIMATEDLG_H
#define DIFFRESULTESTIMATEDLG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../../DataMngr/DataGroup.h"
#include "../../DataMngr/DataMngrGlobal.h"
#include "../../API/GlobalConfigApi.h"
#include "SttMultiMacroDiffParasDefine.h"

namespace Ui {
class QDiffResultEstimateDlg;
}

class QDiffResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
	explicit QDiffResultEstimateDlg(CDataGroup *m_oDiffDataGroup, QWidget *parent = 0);
    ~QDiffResultEstimateDlg();

	void InitUI();
	void InitFont();
	void InitConnections();
	void UpdataResultAssess();
	void ComboxModelStyle(QComboBox *pCombox);
	void CbbErrorType(int nIndex, CString strText);
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);

public:
	QStringList m_Headers;
	QTableWidget *m_pResultTableWidget;

	QPushButton *m_pBtnOK;
	QPushButton *m_pBtnCancel;
	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pButtonLayout;

	QLabel *m_pLabRateName;
	QLabel *m_pLabTimeName;
	QLabel *m_pLabHarmName;

	QComboBox *m_pCmbRate;
	QComboBox *m_pCmbTime;
	QComboBox *m_pCmbHarm;

	QTableWidgetItem *m_pItem1;
	QTableWidgetItem *m_pItem2;
	QTableWidgetItem *m_pItem3;
	QTableWidgetItem *m_pItem4;
	QTableWidgetItem *m_pItem5;
	QTableWidgetItem *m_pItem6;
	QTableWidgetItem *m_pItem7;
	QTableWidgetItem *m_pItem8;

	QLabel *m_pLabRateNeg;

	CDataGroup *m_pParas;

public slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

	void slot_cellClicked(int row, int col);
	void slot_cmbErrorChanged(const QString& strText);
};

#endif // DIFFRESULTESTIMATEDLG_H
