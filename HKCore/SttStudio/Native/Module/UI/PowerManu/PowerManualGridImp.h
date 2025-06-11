#ifndef QPowerManualGridImp_H
#define QPowerManualGridImp_H

#include "../Module/ChannelParaSet/QParaSetBase.h"
#include "../Controls/SttTabWidget.h"
#include "../../SttTest/Common/Power/tmt_power_manu_test.h"
#include "../Module/ChannelParaSet/channelpowertable.h"
#include "../../../Module/OSInterface/OSInterface.h"
#include <QGridLayout>

class QPowerManualGridImp : public QParaSetBase
{
	Q_OBJECT

public:
	QPowerManualGridImp(QWidget *parent = 0);
	~QPowerManualGridImp();

public:
	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_channel *pArrUIVOL,tmt_ChannelPower *pArrPOW,bool bDC = false);
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

	void UpdateValidTableDatas();
	void setHarmIndex(int *pnHarmIndex);
	int* GetHarmIndex() { return m_pnHarmIndex; }


	QTabWidget* m_tabWidget;
	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;

	QList<QChannelTable *> m_UCHannelTableList;
	QList<QChannelPowerTable *> m_ICHannelTableList;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;
	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;

	plugin_type m_type;
	tmt_channel *m_pArrUIVOL;
	tmt_ChannelPower *m_pArrPOW;
	bool m_bDC;
	CSttTestResourceBase *m_pParaSetSttTestResource;
	//int m_ndc_type;

	float m_fpower[3];//add wangtao 20240816 �������ڹ��ʳ�Ա�����������������Сֵ
	float m_fMultAmpMax[MAX_VOLTAGE_COUNT];//add wangtao 20240828 ͨ��ʵ��-���ʸ���ÿ��ͨ���Ĺ������ƶ�Ӧ��ѹ��С
	float m_fMultAmpMin[MAX_VOLTAGE_COUNT];
private:
	int *m_pnHarmIndex;

};

extern QFont *g_pSttGlobalFont;

#endif // QBasicTestParaSetImp_H
