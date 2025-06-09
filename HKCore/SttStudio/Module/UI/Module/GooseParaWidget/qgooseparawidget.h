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
	void SetTestCheckBox_Visible(BOOL bVisible);//���ü���״̬��ѡ���Ƿ�ɼ�

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();
	void sig_GoutMapChanged();//GOOOSE����ͨ��ӳ������������͸ı�

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
	void SetTestCheckBox_Visible();//���ü���״̬��ѡ���Ƿ�ɼ�

public:
	virtual void showEvent(QShowEvent *);

};

extern QFont *g_pSttGlobalFont; 

#endif // QGOOSEPARAWIDGET_H
