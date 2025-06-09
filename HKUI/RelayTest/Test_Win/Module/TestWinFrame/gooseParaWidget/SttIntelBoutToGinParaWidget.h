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
	
	int GetCurrentRow(){	return m_tab_GoosePub->currentIndex();	}//获取当前tab序号

	QTabWidget* getGoosePub(){
		return m_tab_GoosePub;}

	QList<QSttIntelBoutToGinPubWidget *> getGoosePubList(){
		return m_pGoosePubList;}

	QCheckBox *chb_cbBinOut5;
	QCheckBox *chb_cbBinOut6;
	QCheckBox *chb_cbBinOut7;
	QCheckBox *chb_cbBinOut8;

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
	void slot_GinRowIndex(int nRowIndex,float fActTime);

	//快速开出的状态值
	void slot_chb_BinOut5StateChanged( int nStateValue);
	void slot_chb_BinOut6StateChanged( int nStateValue);
	void slot_chb_BinOut7StateChanged( int nStateValue);
	void slot_chb_BinOut8StateChanged( int nStateValue);

private:
	bool m_bInitEditable;
	QTabWidget* m_tab_GoosePub;
	QList<QSttIntelBoutToGinPubWidget *> m_pGoosePubList;
};

#endif // QGOOSGINEPARAWIDGET_H
