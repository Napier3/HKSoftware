#ifndef WaveGraphWidget_H
#define WaveGraphWidget_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
//#include "../../../Module/SttXTestMngrBaseApp.h"
#include "../../../Module/Record/Draw/ViewAnalyse.h"
#include "../../../Module/Record/RecordTest/RecordTest.h"
#include "../Module/ReplayTest/SttModuleChComtradeBind.h"

class CWnd_WaveGraph;

class QWaveGraphWidget : public QWidget, public CViewAnalyse
{
    Q_OBJECT

public:
    explicit QWaveGraphWidget(QWidget *parent = 0);
    ~QWaveGraphWidget();
	void UpdateWaveDraws();

	CDC* GetDC()	{	return m_pDC;	}
private:
    CDC *m_pDC;
	CWnd_WaveGraph *m_pWndWaveGraph;

protected:
    virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);


public:
	void RecordDraw();
	void CreateRecordDraw(long cx, long cy);
	void CreateRecordDrawByComtrade();
	void InitWaveGraph();
	void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	void GetTwoCursorTimeValues(double &dTimeA,double &dTimeB);
	void SendUpdateTwoCursorTimeValues(BOOL bCompare = FALSE);//zhouhj 20211104 �ڽ����Ϲ��ı��,֪ͨ�ⲿ�������ʱ��ֵ,����ֵΪ�Ƿ���бȽ�

	//���±���ɫ
	void UpdateInsertWaveBackColor(double nValue1,double nValue2);//���²����ɫ
	void UpdateDeleteWaveBackColor(double nValue1,double nValue2);//����ɾ����ɫ
	bool m_bInsertWaveformBackColor;//�Ƿ�����Ҫ���α༭�����ɫ
	bool m_bDeleteWaveformBackColor;//�Ƿ�����Ҫ���α༭ɾ����ɫ
	void UpdateButtonEnable(BOOL bState);

private:
	CRecordTest *m_pReplayRecordTest;
	long m_nAnalogChanAmount;
	long m_nTotalPoints;
	double m_dTimeA;
	double m_dTimeB;
	int m_nMaxChannels;//һҳ���ͨ����
	int m_nCurrPageIndex;//��ǰҳ��
	int m_nPageCount;//��ͨ����
	QMap <int , CSttModuleComtradeBind *>m_oModuleMap;

	void initModuleMap();

	void InitRecordTestBySttModulesComtradeBind();
	void CreateBySttModulesComtradeBind();
	void CreateBySttModulesComtradeBind(int nPageIndex);
	void CreateBySttModulesComtradeBind(CSttModuleComtradeBind *pModule);
	void CreateBySttModulesComtradeBind(CSttModuleChComtradeBind *pCh);
	void CreateBySttModulesComtradeBind(CSttModuleChComtradeBind *pCh, CRtSingleVariable **ppVariable);
	void AttachOnlineRecordExBuffer();

private:
	void initPlot();


	QPushButton *m_pBtn_PrevPage ;
	QPushButton *m_pBtn_NextPage;

	void UpdateDrawOptrBtns();
	void AddDrawOptrBtns();

signals:
	void sig_UpdateTwoCursorTimeValues(double dValueA,double dValueB);

public slots:
	void slot_UpdateDrawWaveGraph();

	void slotDrawOptr_PrevPage();
	void slotDrawOptr_NextPage();

};

class CWnd_WaveGraph : public CWnd
{
public:
	CWnd_WaveGraph();
	virtual ~CWnd_WaveGraph();

	QWaveGraphWidget *m_pWaveGraph;

public:
	//���غ���OnWndMsg��ʵ����Ϣ����
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam) ;
	virtual void OnWndTimer(unsigned int nIDEvent);

	virtual CDC* GetDC();
	virtual void ReleaseDC(CDC *pDC);
	virtual void GetClientRect(CRect &rc);
	virtual void GetClientRect(CRect *pRect);

	virtual void InvalidateRect(CRect *pRect, BOOL b);
	virtual void InvalidateRect(CRect &rect, BOOL b);
	virtual void Invalidate(BOOL b);

};

#endif // WaveGraphWidget_H
