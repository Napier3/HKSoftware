#ifndef QSTTINTELBOUTTOGINPUBWIDGET_H
#define QSTTINTELBOUTTOGINPUBWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include "../../../61850/Module/CfgDataMngr/IecCfgGinDatas.h"
#include "SttIntelBoutToGinGrid.h"

class QSttIntelBoutToGinParaWidget;
class QSttIntelBoutToGinPubWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIntelBoutToGinPubWidget(QSttIntelBoutToGinParaWidget *pParaWidget,QWidget *parent = 0);
	~QSttIntelBoutToGinPubWidget();

	void initUI();
	void initData(CIecCfgGinData *pCfgGoutData,bool bInitEditable=TRUE);
	void SetRunState(int nRunState);
	void GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex);
	void startInit();
	void SetGoosePubFont();

	CSttIntelBoutToGinGrid *m_pSttIntelBoutToGinGrid;

	QLabel *label_IEDName;
	QLineEdit *lne_IEDName;
	QLabel *label_APPID;
	QLineEdit *lne_APPID;

	QCheckBox *chb_cbBinOut1;
	QCheckBox *chb_cbBinOut2;
	
signals:
	void sig_GooseDataChanged();
	void sig_setBinOut(int nbout ,bool bStateChanged);
	void sig_GinRowIndex(int nRowIndex,float fActTime);

private slots:
	void slot_dataChanged();
	void slot_GinRowIndex(int nRowIndex,float fActTime);

private:
	bool m_bAll;
	CIecCfgGinData *m_pCfgGinData;
	QVBoxLayout *m_pMainLayout;

protected slots:
	void slot_chb_BinOut1StateChanged( int nStateValue);
	void slot_chb_BinOut2StateChanged( int nStateValue);
};

#endif // QSTTINTELBOUTTOGINPUBWIDGET_H
