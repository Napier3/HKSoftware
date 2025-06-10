#ifndef QPowerDiagramWidgetImp_H
#define QPowerDiagramWidgetImp_H

#include "powerdiagramwidget.h"
#include "../../QSttInfWidgetBase.h"

class QPowerDiagramWidgetImp : public QSttInfWidgetBase
{
	Q_OBJECT

public:
	explicit QPowerDiagramWidgetImp(QWidget *parent=0);
	~QPowerDiagramWidgetImp();

public:
	virtual void showEvent(QShowEvent *);

protected:
	PowerDiagramWidget *m_pPowerWidget;
	CSttTestResourceBase *m_pPowerSttTestResource;

	tmt_channel* m_pVOL;//��ʼ��ѹ
	tmt_channel* m_pCUR;//��ʼ����
	CExBaseList* m_pVolChList;//ȫ����ѹͨ����Դ����
	CExBaseList* m_pCurChList; //ȫ������ͨ����Դ����
	long m_nTimerID;


public:
	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList);
	void initData();
	void cmbVolSetChanged();
	void cmbCurSetChanged();
        void updatePowerData();
	void TimerStart();
	void TimerStop(bool bUpdate = false);
	virtual void timerEvent(QTimerEvent * );


private:
	void setPropertyOfParaSet();
	void setData();

};

#endif // QPowerDiagramWidgetImp_H
