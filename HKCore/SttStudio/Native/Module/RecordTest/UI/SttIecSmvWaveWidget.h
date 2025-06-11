#ifndef QSttIecSmvWaveWidget_H
#define QSttIecSmvWaveWidget_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFont>

#include "SttIecRcdFuncInterface.h"

#include "../../../../Module/SmartCap/61850Cap/Record/CapViewAnalyse.h"

#define STT_IECRCD_WAVE_CHS_PAGE  6

#ifdef QT_Wnd_USE_QWIDGET
class QSttIecSmvWaveWidget : public CCapViewAnalyse, public CSttIecRcdFuncInterface, public CWnd
#else
class QSttIecSmvWaveWidget : public QWidget ,public CCapViewAnalyse, public CSttIecRcdFuncInterface, public CWnd
#endif
{
    //Q_OBJECT
public:
	explicit QSttIecSmvWaveWidget(QWidget *parent = 0);
	virtual  ~QSttIecSmvWaveWidget();

public://CWnd
	//���غ���OnWndMsg��ʵ����Ϣ����
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent) ;

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

	void ReleaseUI();

	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();

	LRESULT OnVariableAddRemoved(WPARAM wParam, LPARAM lParam);
	void IecRcdInitFromRecordTest();
	virtual void InitTimeAxis();  //2022-4-24  lijunqing ��ʼ��ʱ�����꣬�ɱ��������ø��Ի�

	BOOL m_bInitTimeAxis;
	BOOL m_bUpdateFlag;
protected:
	long m_nCurrRcdChIndex;
	long m_nUpdateCount;//��linux�¼���ˢ�´���
	void CalIndex_NextPage();
	void CalIndex_PrevPage();

	//2022-6-12  lijunqing ��ǰCapDevice��¼��ͨ��
	CExBaseList m_listRcdVariable;
	void GetCurrDeviceAllRcdVariables();
	void UpdateDrawVariablesRange();
	void SetDrawVariablesRange();

public:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);

	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

// public:
// 
// signals:
// 
public slots:
	 void MoveLeft();
	 void MoveRight();
	 void ZoomInChan();
	 void ZoomOutChan();
	 void slot_Reset();
	 void ZoomInTime();
	 void ZoomOutTime();
};

#endif // QSttIecSmvWaveWidget_H
