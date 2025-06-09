#ifndef QASYNCDIGITALTESTPARASET_H
#define QASYNCDIGITALTESTPARASET_H

#include "QAsyncTestParaSetBase.h"

class QAsyncDigitalTestParaSet : public QAsyncTestParaSetBase
{
	Q_OBJECT

public:
	QAsyncDigitalTestParaSet(tmt_async_modules *pModules,QWidget *parent = 0);
	~QAsyncDigitalTestParaSet(void);

	virtual void initUI();
	virtual void initData();
	virtual void setData(tmt_async_modules *pModules);
	virtual void UpdateModulesData(tmt_async_modules *pModules);
	virtual void UpdateTableData();

	virtual void startInit();
	virtual void stopInit();
	virtual void setChannelTableItemValue(int nMouleIndex,MOUDLEType type,int nChIndex,float fstep,int valueFlag,int AddOrMinus,bool bDC);


	void IsTestInProgress( bool b );//是否为测试过程中

public:
	virtual void DCStateChanged(bool bDc);

public:
	QGridLayout *m_pGridLayout;//主布局
	QWidget *m_pMainWin;

	QAsyncChannelTable *m_pUTable;//电压模块
	QAsyncChannelTable *m_pITable;//电流模块
	QLabel * m_pLabel;

	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;
	QWidget *m_pUWidget;
	QWidget *m_pIWidget;

	QScrollArea *m_pMainScrollArea;
	QWidget* m_pScrollWidget;
	QVBoxLayout* m_pVScrollLayout;

	QHBoxLayout* m_pHLayout;
	QVBoxLayout* m_pVLayout;
	QHBoxLayout* m_pMainLayout;

signals:
	void sig_updataParas();

public slots:
	void slot_ChannelValueChanged();


};

#endif