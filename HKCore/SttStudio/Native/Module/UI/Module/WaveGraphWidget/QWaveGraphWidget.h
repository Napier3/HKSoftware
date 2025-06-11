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
	void SendUpdateTwoCursorTimeValues(BOOL bCompare = FALSE);//zhouhj 20211104 在界面上光标改变后,通知外部界面更新时间值,参数值为是否进行比较

	//更新背景色
	void UpdateInsertWaveBackColor(double nValue1,double nValue2);//更新插入底色
	void UpdateDeleteWaveBackColor(double nValue1,double nValue2);//更新删除底色
	bool m_bInsertWaveformBackColor;//是否有需要波形编辑插入底色
	bool m_bDeleteWaveformBackColor;//是否有需要波形编辑删除底色
	void UpdateButtonEnable(BOOL bState);

private:
	CRecordTest *m_pReplayRecordTest;
	long m_nAnalogChanAmount;
	long m_nTotalPoints;
	double m_dTimeA;
	double m_dTimeB;
	int m_nMaxChannels;//一页最大通道数
	int m_nCurrPageIndex;//当前页面
	int m_nPageCount;//总通道数
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
	//重载函数OnWndMsg，实现消息处理
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
