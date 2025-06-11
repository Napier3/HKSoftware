#ifndef BASICPARASET_H
#define BASICPARASET_H

#include "QBasicTestParaSetImp.h"
#include "../../QSttInfWidgetBase.h"

class QBasicTestParaSet : public QSttInfWidgetBase
{
	Q_OBJECT

public:
	QBasicTestParaSet(QWidget *parent = 0);
	~QBasicTestParaSet();

public:
	void DCStateChanged(int type,bool bdc);
	
	void UpdateTables();

	virtual void setUAmpMaxMinValue(bool bCanUpdateTable);
	virtual void setIAmpMaxMinValue(bool bCanUpdateTable);
	virtual void setUAmpEDValue(float fUEDVal);
	virtual void setIAmpEDValue(float fIEDVal);
	
	virtual void setChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	virtual void setChannelTableItemValue_Sequence(QString str,float fstep,int valueFlag,int AddOrMinus);//��������ֵ�ı�  20230209
	
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData(bool bCanUpdateTable);
	virtual void Release();
	
	virtual void SetParaSetSecondValue(int nParaSetSecondValue);
	int m_nParaSetSecondValue;	//V_Primary:��ʾһ��ֵ��V_Secondary:��ʾ����ֵ

	void GetUIMaxMinValue(double& dUMin,double& dUMax,double& dIMin,double& dIMax,bool bStart = false); //zhouhj 20220819 �ú���δ�õ�ɾ��  //20241030 suyang ���ã����ڸ���״̬ͼ�ĵ�ѹ�������ֵ
	void UpdateValidTableDatas();
	void setHarmIndex(int *pnHarmIndex);

public:
	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,bool bDC = false);
	void setData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	void setMacroType(int type);
	void setMaxMinAndEDVal(bool bCanUpdateTable=true);

	void Send_UpdataParas();

	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

public:
	virtual void showEvent(QShowEvent *);

private:
	QBasicTestParaSetImp *m_pParaSetImp;
	
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

	//chenling 20250117 �����ʷ������ĵ�ѹ��������ֵ
	float m_fHistoryUMax;
	float m_fHistoryIMax;

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

	void SetBasicTestParaSetImp(QBasicTestParaSetImp* pParaSetImp);
	QBasicTestParaSetImp* GetBasicTestParaSetImp() { return m_pParaSetImp; }

signals:
	void sig_updataParas();

};

#endif // QBASICTESTPARASET_H
