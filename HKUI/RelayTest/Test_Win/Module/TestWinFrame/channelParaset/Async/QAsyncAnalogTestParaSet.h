#ifndef QASYNCANALOGTESTPARASET_H
#define QASYNCANALOGTESTPARASET_H

// #include <QWidget>
// #include "../../../../.././Module/SttTest/Common/tmt_common_def.h"
// #include "QAsyncChannelTable.h"
#include "QAsyncTestParaSetBase.h"
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>

class QAsyncAnalogTestParaSet : public QAsyncTestParaSetBase
{
	Q_OBJECT

public:
	QAsyncAnalogTestParaSet(tmt_async_modules *pModules,QWidget *parent = 0);
	~QAsyncAnalogTestParaSet(void);

	virtual void initUI();
	virtual void initData();
	virtual void setData(tmt_async_modules *pModules);
	virtual void UpdateModulesData(tmt_async_modules *pModules);
	virtual void UpdateTableData();

	virtual void startInit();
	virtual void stopInit();

	void IsTestInProgress( bool b );//是否为测试过程中


public:
	virtual void DCStateChanged(bool bDc);

public:
	QGridLayout *m_pGridLayout;//主布局
	QWidget *m_pMainWin;
	QList<QAsyncChannelTable*> m_UCHannelTableList;
	QList<QAsyncChannelTable*> m_ICHannelTableList;
	QList<QLabel*>m_UChTableLableList;//电压模块名称标签链表
	QList<QLabel*>m_IChTableLableList;//电流模块名称标签链表

	QScrollArea *m_pMainScrollArea;
	QWidget* m_pScrollWidget;
	QVBoxLayout* m_pVScrollLayout;
	QHBoxLayout* m_pHLayout;

public slots:
	void slot_ChannelValueChanged();

signals:
	void sig_updataParas();

};


#endif