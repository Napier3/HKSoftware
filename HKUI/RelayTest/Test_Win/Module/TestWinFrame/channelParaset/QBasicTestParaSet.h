#ifndef QBASICTESTPARASET_H
#define QBASICTESTPARASET_H

#include "QParaSetBase.h"

class QBasicTestParaSet : public QParaSetBase
{
	Q_OBJECT

public:
	QBasicTestParaSet(QWidget *parent = 0);
	~QBasicTestParaSet();

public:
	void DCStateChanged(int type,bool bdc);
	void setDispMode(int dispmode);
	void UpdateTables();
	virtual void setUAmpMaxMinValue();
	virtual void setIAmpMaxMinValue();
	virtual void setUAmpEDValue(float fUEDVal);
	virtual void setIAmpEDValue(float fIEDVal);
	virtual void setUAmpMaxMinValueZero(float fmax,float fmin);
	virtual void setIAmpMaxMinValueZero(float fmax,float fmin);

	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData();
	virtual void UpdateVolChsTable();//zhouhj 2023.8.9 只更新电压通道表格
	virtual void Release();

	void GetUIMaxMinValue(double& dUMin,double& dUMax,double& dIMin,double& dIMax);
	void UpdateValidTableDatas(BOOL bSendUpdateParas = TRUE);
//	virtual void keyPressEvent(QKeyEvent *event);

	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;

	QList<CHannelTable *> m_UCHannelTableList;
	QList<CHannelTable *> m_ICHannelTableList;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;
	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;

signals:
	void sig_pbnAddVal();
	void sig_pbnMinusVal();
private:
	
};

#endif // QBASICTESTPARASET_H
