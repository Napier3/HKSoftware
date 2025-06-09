#ifndef STTSCLLINEDIALOG_H  
#define STTSCLLINEDIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include "../../Module/CommonCtrl_QT/Draw/QSttCustomArrowLine.h"
#include "../../Module/CommonCtrl_QT/Draw/QSttCustomRect.h"
#include <QScrollBar>
#include <QMouseEvent>
#include "../../../../../Module/BaseClass/ExBaseObject.h"
#include <QVBoxLayout>
#include "../../Controls/SttCheckBox.h"

class CSclVirtualSubend :public CExBaseObject //虚子端
{
public: 
	CString strfcdaDesc;//发送描述
	CString strIndoDesc; //接收描述
	CString strAppID;

	long nInIndex;
	long nOutIndex;
	CSclVirtualSubend(){}
	virtual ~CSclVirtualSubend(){}
	CSclVirtualSubend& operator=(const CSclVirtualSubend &oObj)
	{
		m_strName = oObj.m_strName;
		m_strID = oObj.m_strID;
		strfcdaDesc = oObj.strfcdaDesc;
		strIndoDesc = oObj.strIndoDesc;
		strAppID = oObj.strAppID;
		nInIndex = oObj.nInIndex;
		nOutIndex = oObj.nOutIndex;
		return *this;
	}
};

class QCustomGraphicsView : public QGraphicsView
{
public:
	QPoint m_lastPos;
	QPointF m_lastScenePos;

	QCustomGraphicsView(QWidget* parent = NULL) : QGraphicsView(parent)
	{
		setMouseTracking(true);
	}

protected:
    void mousePressEvent(QMouseEvent* event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_lastScenePos = mapToScene(event->pos());
			m_lastPos = event->pos();
		}
		QGraphicsView::mousePressEvent(event);
	}

    void mouseMoveEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
		{
			int dx = event->x() - m_lastPos.x();
			int dy = event->y() - m_lastPos.y();

			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - dx);
			verticalScrollBar()->setValue(verticalScrollBar()->value() - dy);

			m_lastPos = event->pos();
		}
		QGraphicsView::mouseMoveEvent(event);
	}
};


class QSttSclIedLineDialog : public QDialog
{
	Q_OBJECT
public:
	QSttSclIedLineDialog(QList<CSclVirtualSubend > *pSubData,QList<CSclVirtualSubend > *pInputData,long nType ,QDialog *parent=NULL);
	virtual ~QSttSclIedLineDialog();

public:
	void InitUI();
	void UpdateUIScene();
	void InitData(QList<CSclVirtualSubend > *pSubData,QList<CSclVirtualSubend> *pInputData,long nType,bool bDrawAllRects);
	void InitConnection();
	void DrawLine(QList<CSclVirtualSubend > *pInputData,QList<CSclVirtualSubend> *pOutputData,long nType,bool bDrawAllRects);
	void Release();


public slots:
	void slot_ZoomIn();
	void slot_ZoomOut();
	void slot_Exit();
	void slot_checkbox(int nState);

private:
	QPushButton *m_pBtnZoomIn;//缩小
	QPushButton *m_pBtnZoomOut;//放大
	QPushButton *m_pBtnExit;//退出
	QCustomGraphicsView * m_pGraphicsView;
	QGraphicsScene* m_pGraphicsScene;

	QSttCustomRect *m_pInputRect;
	QSttCustomRect *m_pOutputRect;
	QList<QSttCustomRect*> m_pChInLeftRect;
	QList<QSttCustomRect*> m_pChInRightRect;
	QList<QSttCustomArrowLine*>m_pArrowLine;
	QList<CSclVirtualSubend> *m_pInputData;
	QList<CSclVirtualSubend > *m_pOutputData;
	long m_nType;//接收端还是发送端
	QVBoxLayout *m_pMainLayout;
	QSttCheckBox *m_pAllInputCheckBox;
};
#endif
