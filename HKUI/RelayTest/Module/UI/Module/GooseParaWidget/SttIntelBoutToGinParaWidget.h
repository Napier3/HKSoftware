#ifndef QSTTINTELBOUTTOGINPARAWIDGET_H
#define QSTTINTELBOUTTOGINPARAWIDGET_H

#include <QWidget>
#include "SttIntelBoutToGinPubWidget.h"
#include <QTabWidget>

class QSttIntelBoutToGinParaWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIntelBoutToGinParaWidget(CIecCfgGinDatas* pCfgGinDatas ,bool bInitEditable = TRUE);
	~QSttIntelBoutToGinParaWidget();

	void initGoosePubTable( CIecCfgGinDatas* pCfgGinDatas );
	BOOL m_bGooseFlag;

	int GetCurrentRow(){	return m_tab_GoosePub->currentIndex();	}

	QTabWidget* getGoosePub(){
		return m_tab_GoosePub;}

	QList<QSttIntelBoutToGinPubWidget *> getGoosePubList(){
		return m_pGoosePubList;}
	
protected:
	void initUI();
	void initOneGooseBlockTable( QSttIntelBoutToGinPubWidget *p,CIecCfgGinData *pCfgGinData);
	
public:
	void SetRunState(int nRunState);
	void SetGooseDisabled(bool bFlag);
	void setGooseTabEnable(bool bEnable);
	void startInit();

signals:
	void sig_GooseDataChanged();
	void sig_setBinOut(int nbout ,bool bStateChanged);
	void sig_GinRowIndex(int nRowIndex,float fActTime);

protected slots:
	void slot_GooseDataChanged();
	void slot_setBinOut(int nbout ,bool bStateChanged);
	void slot_GinRowIndex(int nRowIndex,float m_fActTime);

private:
	bool m_bInitEditable;
	QTabWidget* m_tab_GoosePub;
	QList<QSttIntelBoutToGinPubWidget *> m_pGoosePubList;
	CIecCfgGinDatas* m_pCfgGinDatas;

};
extern CFont *g_pSttGlobalFont; 

#endif // QSTTINTELBOUTTOGINPARAWIDGET_H
