#ifndef QGOOSEPARAWIDGET_H
#define QGOOSEPARAWIDGET_H

#include <QWidget>
#include "GoosePubWidget.h"
#include <QTabWidget>

class QGooseParaWidget : public QWidget
{
	Q_OBJECT

public:
	QGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas ,bool bInitEditable = TRUE);
	~QGooseParaWidget();

	void initGoosePubTable( CIecCfgGoutDatas* pCfgGoutDatas );
		
protected:
	void initUI();
	void initOneGooseBlockTable( GoosePubWidget *p,CIecCfgGoutData *pCfgGoutData);

public:
	void SetRunState(int nRunState);
	void SetGooseDisabled(bool bFlag);

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();

protected slots:
	void slot_GooseDataChanged();
	void slot_RepairDataChanged();

private:
	bool m_bInitEditable;
	QTabWidget* m_tab_GoosePub;
	QList<GoosePubWidget *> m_pGoosePubList;
};

#endif // QGOOSEPARAWIDGET_H
