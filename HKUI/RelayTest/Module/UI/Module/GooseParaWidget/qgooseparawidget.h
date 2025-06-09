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
	BOOL m_bGooseFlag;
	

protected:
	void initUI();
	void initOneGooseBlockTable( GoosePubWidget *p,CIecCfgGoutData *pCfgGoutData);

public:
	void SetRunState(int nRunState);
	void SetGooseDisabled(bool bFlag);
	void SetTestCheckBox_Visible(BOOL bVisible);//设置检修状态勾选框是否可见

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();
	void sig_GoutMapChanged();//GOOOSE开出通道映射或者数据类型改变

protected slots:
	void slot_GooseDataChanged();
	void slot_RepairDataChanged();
	void slot_GoutMapChanged();

private:
	bool m_bInitEditable;
	QTabWidget* m_tab_GoosePub;
	QList<GoosePubWidget *> m_pGoosePubList;
	CIecCfgGoutDatas* m_pCfgGoutDatas;


	int m_nRunState;
	bool m_bGooseDisabled;
	BOOL m_bTestCheckBox_Visible;

	void initGoosePubTable( );
	void SetRunState();
	void SetGooseDisabled();
	void SetTestCheckBox_Visible();//设置检修状态勾选框是否可见

public:
	virtual void showEvent(QShowEvent *);

};

extern CFont *g_pSttGlobalFont; 

#endif // QGOOSEPARAWIDGET_H
