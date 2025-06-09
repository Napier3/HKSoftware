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

class QSttIntelBoutToGinPubWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIntelBoutToGinPubWidget(QWidget *parent = 0,bool bInitEditable = TRUE);
	~QSttIntelBoutToGinPubWidget();

	void initUI();
	void initData(CIecCfgGinData *pCfgGoutData,bool bInitEditable=TRUE);
	void SetRunState(int nRunState);
	void GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex);//测试结果及开入量A~F
	void UpdateState( int nStateValue);//快速开出状态值
	void startInit();

	CSttIntelBoutToGinGrid *m_pSttIntelBoutToGinGrid;

	QLabel *label_IEDName;
	QLineEdit *lne_IEDName;
	QLabel *label_APPID;
	QLineEdit *lne_APPID;

signals:
	void sig_GooseDataChanged();
	void sig_GinRowIndex(int nRowIndex,float fActTime);

private slots:
	void slot_dataChanged();
	void slot_GinRowIndex(int nRowIndex,float fActTime);

private:
	bool m_bAll;
	CIecCfgGinData *m_pCfgGinData;
	QVBoxLayout *m_pMainLayout;
};

#endif // QSTTINTELBOUTTOGINPUBWIDGET_H
