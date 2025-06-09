#ifndef GOOSEPUBWIDGET_H
#define GOOSEPUBWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
//#include "QGooseTable.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"
#include "IecCfgGoutChsGrid.h"

class GoosePubWidget : public QWidget
{
	Q_OBJECT

public:
	GoosePubWidget(QWidget *parent = 0);
	~GoosePubWidget();

	void initUI();
	void initData(CIecCfgGoutData *pCfgGoutData,bool bInitEditable=TRUE);
	void SetRunState(int nRunState);
//	void initDisabled(bool bedit = false);
	void EnableInverseCol(BOOL bEnable);

	CIecCfgGoutChsGrid *m_pIecCfgGoutChsGrid;
//	QGooseTable *m_pGoosePubTable;
	QLabel *label_IEDName;
	QLineEdit *lne_IEDName;
	QLabel *label_APPID;
	QLineEdit *lne_APPID;
	QCheckBox *chb_Invert;
	QCheckBox *chb_Repair;

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();

private slots:
	void slot_chb_InvertStateChanged(int);
	void slot_chb_RepairStateChanged(int);
	void slot_dataChanged();

private:
	bool m_bAll;
	CIecCfgGoutData *m_pCfgGoutData;
};

#endif // GOOSEPUBWIDGET_H
