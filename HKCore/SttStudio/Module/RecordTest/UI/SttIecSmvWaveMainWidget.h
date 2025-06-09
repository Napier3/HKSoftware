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

#define STT_ToolBtn_Width                  45//�Ҳ�Ŵ���С�����ơ����ƵȰ�ť�Ŀ�� 


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

	virtual void InitTimeAxis();  //2022-4-24  lijunqing ��ʼ��ʱ�����꣬�ɱ��������ø��Ի�

public:

	QVBoxLayout *m_pMainVBoxLayout;
	
	QHBoxLayout *m_pBtnHBoxLayout;

	QPushButton *m_pBtnReset;   //����
	QPushButton *m_pBtnZoomOutTime; //������Ŵ�
	QPushButton *m_pBtnZoomInTime; //��������С
	QPushButton *m_pBtnZoomOutChan; //������Ŵ�
	QPushButton *m_pBtnZoomInChan; //��������С
	QPushButton *m_pBtnMoveLeft; //����
	QPushButton *m_pBtnMoveRight; //����

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
