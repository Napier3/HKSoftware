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

	void initGoosePubTable( CIecCfgGoutDatas* pCfgGoutDatas);
	void SetCurrentIndex(int nIndex);//设置当前tab序号
	int GetCurrentRow(){	return m_tab_GoosePub->currentIndex();	}//获取当前tab序号

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
	void setGooseTabEnable(bool bEnable);
	void setGooseResultVlaues();
	void startInit();

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();
	void sig_RevertData();
	void sig_TabChanged(int index);
	void sig_GoutRowIndex(int nRowIndex);

protected slots:
	void slot_GooseDataChanged();
	void slot_RepairDataChanged();
	void slot_RevertData();
	void slot_GoutRowIndex(int nRowIndex);

private:
	bool m_bInitEditable;
	QTabWidget* m_tab_GoosePub;
	QList<QSttIntelGoutToBinPubWidget *> m_pGoosePubList;
};

#endif // QSTTINTELGOUTTOBINPARAWIDGET_H
