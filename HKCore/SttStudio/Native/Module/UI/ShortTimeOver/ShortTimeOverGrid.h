#ifndef QShortTimeOverGrid_H
#define QShortTimeOverGrid_H

#include "../QSttInfWidgetBase.h"
#include "ShortTimeOverGridImp.h"

class QShortTimeOverGrid : public QSttInfWidgetBase
{
	Q_OBJECT

public:
	QShortTimeOverGrid(QWidget *parent = 0);
	~QShortTimeOverGrid();

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

	//	void GetUIMaxMinValue(double& dUMin,double& dUMax,double& dIMin,double& dIMax); zhouhj 20220819 该函数未用到删除
	void UpdateValidTableDatas();
	void setHarmIndex(int *pnHarmIndex);

public:
	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC = false);
	void setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	void setMacroType(int type);
	void setMaxMinAndEDVal();

	void Send_UpdataParas();

	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

public:
	virtual void showEvent(QShowEvent *);

public:
	QShortTimeOverGridImp *m_pParaSetImp;

	CSttTestResourceBase *m_pParaSetSttTestResource;
	plugin_type m_type;
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;
	bool m_bDC;
	int m_ndc_type;

	float m_fUEDVal;
	float m_fIEDVal;
	int *m_pnHarmIndex;//2023.7.29 zhouhj

	QString m_strChannelTableItemValue;
	float m_fChannelTableItemValue_Step;
	int m_nChannelTableItemValue_ValueFlag;
	int m_nChannelTableItemValue_AndOrMinus;

	int m_MacroType;
protected:
	virtual void initUI();
	virtual void setPropertyOfParaSet();

	virtual void setUAmpEDValue();
	virtual void setIAmpEDValue();
	virtual void setChannelTableItemValue();
	virtual void setChannelTableItemValue_Sequence();
	void setData();
	void DCStateChanged();
	void setMacroType();

	void SetBasicTestParaSetImp(QShortTimeOverGridImp* pParaSetImp);
	QShortTimeOverGridImp* GetBasicTestParaSetImp() { return m_pParaSetImp; }

signals:
	void sig_updataParas();

};

extern QFont *g_pSttGlobalFont; 

#endif // QBasicTestParaSetImp_H
