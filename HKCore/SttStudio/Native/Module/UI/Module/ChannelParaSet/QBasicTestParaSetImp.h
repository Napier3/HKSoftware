#ifndef QBasicTestParaSetImp_H
#define QBasicTestParaSetImp_H

#include "QParaSetBase.h"

class QBasicTestParaSetImp : public QParaSetBase
{
	Q_OBJECT

public:
	QBasicTestParaSetImp(QWidget *parent = 0);
	~QBasicTestParaSetImp();

public:
	void DCStateChanged(int type,bool bdc);
	
	void UpdateTables();

	virtual void setUAmpMaxMinValue(bool bCanUpdateTable);
	virtual void setIAmpMaxMinValue(bool bCanUpdateTable);
	virtual void setUAmpEDValue(float fUEDVal);
	virtual void setIAmpEDValue(float fIEDVal);
	
	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	virtual void setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus);//序分量表格值改变  20230209
	
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData(bool bCanUpdateTable);
	virtual void Release();
	virtual void SetParaSetSecondValue(int nParaSetSecondValue);

//	void GetUIMaxMinValue(double& dUMin,double& dUMax,double& dIMin,double& dIMax); zhouhj 20220819 该函数未用到删除
	void UpdateValidTableDatas();
	void setHarmIndex(int *pnHarmIndex);
	int* GetHarmIndex() { return m_pnHarmIndex; }

	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;

	QList<QChannelTable *> m_UCHannelTableList;
	QList<QChannelTable *> m_ICHannelTableList;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;
	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;

private:
	int *m_pnHarmIndex;
	
};

extern QFont *g_pSttGlobalFont; 

#endif // QBasicTestParaSetImp_H
