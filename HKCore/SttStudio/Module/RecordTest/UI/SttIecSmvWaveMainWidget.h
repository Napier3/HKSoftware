#ifndef QSttIecSmvWaveMainWidget_H
#define QSttIecSmvWaveMainWidget_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFont>
#include <QPushButton>

#include "SttIecSmvWaveWidget.h"
#include "SttIecRcdFuncInterface.h"

#define STT_ToolBtn_Width                  45//右侧放大、缩小、上移、下移等按钮的宽度 


class QSttIecSmvWaveMainWidget  : public QWidget, public CSttIecRcdFuncInterface
{
    Q_OBJECT
public:
	explicit QSttIecSmvWaveMainWidget (QWidget *parent = 0);
	virtual  ~QSttIecSmvWaveMainWidget ();

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig();
	virtual void Release();

	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();

	virtual void InitTimeAxis();  //2022-4-24  lijunqing 初始化时间坐标，可被重载设置个性化

public:

	QVBoxLayout *m_pMainVBoxLayout;
	
	QHBoxLayout *m_pBtnHBoxLayout;

	QPushButton *m_pBtnReset;   //复归
	QPushButton *m_pBtnZoomOutTime; //横坐标放大
	QPushButton *m_pBtnZoomInTime; //横坐标缩小
	QPushButton *m_pBtnZoomOutChan; //纵坐标放大
	QPushButton *m_pBtnZoomInChan; //纵坐标缩小
	QPushButton *m_pBtnMoveLeft; //左移
	QPushButton *m_pBtnMoveRight; //右移

	QSttIecSmvWaveWidget *m_pSttIecSmvWaveWidget;
	
	void InitUI();
	void initConnect();

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);

	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);


 public slots:
	 void MoveLeft();
	 void MoveRight();
	 void ZoomInChan();
	 void ZoomOutChan();
	 void slot_Reset();
	 void ZoomInTime();
	 void ZoomOutTime();

};

#endif // QSttIecSmvWaveMainWidget _H
