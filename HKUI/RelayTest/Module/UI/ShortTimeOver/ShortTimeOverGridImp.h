#ifndef QShortTimeOverGridImp_H
#define QShortTimeOverGridImp_H

#include "../Module/ChannelParaSet/QParaSetBase.h"
#include "../Controls/SttTabWidget.h"
#include "../../../../Module/OSInterface/OSInterface.h"
#include <QGridLayout>

class QShortTimeOverGridImp : public QParaSetBase
{
	Q_OBJECT

public:
	QShortTimeOverGridImp(QWidget *parent = 0);
	~QShortTimeOverGridImp();

public:
	void DCStateChanged(int type,bool bdc);

	void UpdateTables();

	virtual void setUAmpMaxMinValue();
	virtual void setIAmpMaxMinValue();
	virtual void setUAmpEDValue(float fUEDVal);
	virtual void setIAmpEDValue(float fIEDVal);

	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	virtual void setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus);//序分量表格值改变  20230209

	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData();
	virtual void Release();

	void UpdateValidTableDatas();
	void setHarmIndex(int *pnHarmIndex);
	int* GetHarmIndex() { return m_pnHarmIndex; }


	QTabWidget* m_tabWidget;
	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;

	QList<QChannelTable *> m_UCHannelTableList;
	QList<QChannelTable *> m_ICHannelTableList;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;

private:
	int *m_pnHarmIndex;

};

extern CFont *g_pSttGlobalFont; 

#endif // QBasicTestParaSetImp_H
