#ifndef QSTTINTELGOUTTOBINPARAWIDGET_H
#define QSTTINTELGOUTTOBINPARAWIDGET_H

#include <QWidget>
#include "SttIntelGoutToBinPubWidget.h"
#include <QTabWidget>

class QSttIntelGoutToBinParaWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIntelGoutToBinParaWidget(CIecCfgGoutDatas* pCfgGoutDatas ,bool bInitEditable = TRUE);
	~QSttIntelGoutToBinParaWidget();

	void initGoosePubTable( CIecCfgGoutDatas* pCfgGoutDatas );
        int GetCurrentRow(){	return m_tab_GoosePub->currentIndex();	}
	BOOL m_bGooseFlag;

	QTabWidget* getGoosePub(){
		return m_tab_GoosePub;}

	QList<QSttIntelGoutToBinPubWidget *> getGoosePubList(){
		return m_pGoosePubList;}

protected:
	virtual void initUI();
	void initOneGooseBlockTable( QSttIntelGoutToBinPubWidget *p,CIecCfgGoutData *pCfgGoutData);

public:
	void SetRunState(int nRunState);
	void SetGooseDisabled(bool bFlag);
	//void SetTestCheckBox_Visible(BOOL bVisible);//���ü���״̬��ѡ���Ƿ�ɼ�
	void setGooseTabEnable(bool bEnable);
	void setGooseResultVlaues();
	void startInit();

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();
	void sig_RevertData();
	void sig_GoutMapChanged();//GOOOSE����ͨ��ӳ������������͸ı�
	void sig_GoutRowIndex(int nRowIndex);

protected slots:
	void slot_GooseDataChanged();
	void slot_RepairDataChanged();
	void slot_RevertData();
	void slot_GoutMapChanged();
	void slot_GoutRowIndex(int nRowIndex);

private:
	bool m_bInitEditable;
	QTabWidget* m_tab_GoosePub;
	QList<QSttIntelGoutToBinPubWidget *> m_pGoosePubList;
	CIecCfgGoutDatas* m_pCfgGoutDatas;

	int m_nRunState;
	bool m_bGooseDisabled;
	BOOL m_bTestCheckBox_Visible;

	void initGoosePubTable( );
	void SetRunState();
	void SetGooseDisabled();
	//void SetTestCheckBox_Visible();//���ü���״̬��ѡ���Ƿ�ɼ�
	void setGooseTabEnable();

public:
	virtual void showEvent(QShowEvent *);

};

extern QFont *g_pSttGlobalFont; 

#endif // QSTTINTELGOUTTOBINPARAWIDGET_H
