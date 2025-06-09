#ifndef WaveGraphWidget_H
#define WaveGraphWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "../../../Module/SttXTestMngrBaseApp.h"
#include "../../../../../Module/Record\Draw/ViewAnalyse.h"
#include "../../../../../Module/Record/RecordTest/RecordTest.h"
#include "../../../../Module/ReplayTest/SttModuleChComtradeBind.h"
// #include <afxwin.h>

#define STT_ToolBtn_Width                  45//右侧放大、缩小、上移、下移等按钮的宽度 

class CWnd_WaveGraph;

class QWaveGraphWidget : public QWidget, public CViewAnalyse
{
    Q_OBJECT

public:
    explicit QWaveGraphWidget(QWidget *parent = 0);
    ~QWaveGraphWidget();

	CDC* GetDC()	{	return m_pDC;	}
private:
    CDC *m_pDC;
	CWnd_WaveGraph *m_pWndWaveGraph;
	QPushButton *m_pBtnReset;   //复归
	QPushButton *m_pBtnZoomOutTime; //横坐标放大
	QPushButton *m_pBtnZoomInTime; //横坐标缩小
	QPushButton *m_pBtnZoomOutChan; //纵坐标放大
	QPushButton *m_pBtnZoomInChan; //纵坐标缩小
	QPushButton *m_pBtnMoveLeft; //左移
	QPushButton *m_pBtnMoveRight; //右移
	QLabel *m_pChInforLable; //信息表--显示当前波形的最大值、最小值、光标时间和时间
	QLabel *m_pT1Lable; //T1
	QLabel *m_pT2Lable; //T2



protected:
    virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);

	bool m_bMoveCursor;//移动事件鼠标释放标志

public:
	void AddDrawBtns();
	void UpdateDrawBtns();
	void RecordDraw();
	void CreateRecordDraw(long cx, long cy);
	void CreateRecordDrawByComtrade();
	void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	void GetTwoCursorTimeValues(double &dTimeA,double &dTimeB);
	void SendUpdateTwoCursorTimeValues(BOOL bCompare = FALSE);//zhouhj 20211104 在界面上光标改变后,通知外部界面更新时间值,参数值为是否进行比较
	void UpdateButtonEnable(BOOL bState);//2023-11-06 wuxinyi 更新左移、右移..按钮是否可用
	void UpdateWaveDraws();
	void UpdateInsertWaveBackColor(double nValue1,double nValue2);//更新插入底色
	void UpdateDeleteWaveBackColor(double nValue1,double nValue2);//更新删除底色
	bool m_bInsertWaveformBackColor;//是否有需要波形编辑插入底色
	bool m_bDeleteWaveformBackColor;//是否有需要波形编辑删除底色
	CString FormatTime(double dSeconds);//dSeconds转成h：m：S

	void ChangeTimeCursorDrawPos(double dATime,double dBTime);//根据光标AB时间改变位置 

private:
	CRecordTest *m_pReplayRecordTest;
	long m_nAnalogChanAmount;
	long m_nTotalPoints;
	double m_dTimeA;
	double m_dTimeB;
	BOOL m_bIsCreateRecordDraw;

	void InitRecordTestBySttModulesComtradeBind();
	void CreateBySttModulesComtradeBind();
	void CreateBySttModulesComtradeBind(CSttModuleComtradeBind *pModule);
	void CreateBySttModulesComtradeBind(CSttModuleChComtradeBind *pCh);
	void CreateBySttModulesComtradeBind(CSttModuleChComtradeBind *pCh, CRtSingleVariable **ppVariable);
	void AttachOnlineRecordExBuffer();

private:
	void initPlot();

signals:
	void sig_UpdateTwoCursorTimeValues(double dValueA,double dValueB);

public slots:
	void slot_UpdateDrawWaveGraph();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void ZoomInChan();
	virtual void ZoomOutChan();
	void slot_Reset();
	void ZoomInTime();
	void ZoomOutTime();


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
