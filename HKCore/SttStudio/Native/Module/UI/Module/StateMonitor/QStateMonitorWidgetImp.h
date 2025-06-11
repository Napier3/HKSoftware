#ifndef QStateMonitorWidgetImp_H
#define QStateMonitorWidgetImp_H

#include "StateMonitorWidget.h"
#include "../../QSttInfWidgetBase.h"

class QStateMonitorWidgetImp : public QSttInfWidgetBase, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	explicit QStateMonitorWidgetImp(QWidget *parent=0);
	~QStateMonitorWidgetImp();

// public:
// 	virtual void showEvent(QShowEvent *);

protected:
	QStateMonitorWidget *m_pStateMonitor;

	bool m_bModeIsSingle; //true-��ͨ��,false-��ͨ��
	int m_nChannel;
	int m_nType;
	bool m_bStart;
	QWidget* m_pConnectWidget;
//////////////////////////////////////////////////////////////////////////
public://CSttRtDataChangeEvent
	virtual void OnRtDataChanged();//�����麯��,ʵ���յ�ʵʱ���ݺ�Ĵ���

public:
	virtual void InitStateMonitor(int nChannel, int nType, bool bStart, QWidget* pConnectWidget = NULL);
	virtual void AddBinBoutPoint(long nIndex, double x, double y);

	virtual void StopStateMonitor();
	virtual void StartStateMonitor();
	virtual void UpdateLocalTime(double dLocalTime);
	virtual void UpdateStateMonitorChs();
	void SetSingle(bool bSingle);
// 	void SetPlotDigitMaxMinValue(int nChangedType);
	void SetPlotDigitMaxMinValue( int nChangedType,double fUMin,double fUMax,double fIMin,double fIMax );//20241030 suyang ����״̬ͼ��ѹ������С
	double m_dUMin,m_dUMax,m_dIMin,m_dIMax;
	void SetParaSetSecondValue(int nParaSetSecondValue);
	int m_nParaSetSecondValue;

private:
	void SetSingle();
	void InitStateMonitor();

//2024-9-10 lijunqing �Ż�ϵͳ����������Ч��
protected:
	bool m_bHasInitFinished;  //�Ƿ��Ѿ���ʼ����ɣ�û�г�ʼ�������ܽ��в���
	virtual void showEvent(QShowEvent *event);
	void InitStateMonitorWidget();

};

#endif // QStateMonitorWidgetImp_H
