#ifndef STTSCLSKECTCHMAPWIDGET_H  
#define STTSCLSKECTCHMAPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include "SttSclIedDrawViewWidget.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"


class QSttSclIedSkectMapWidget : public QWidget
{
	Q_OBJECT
public:
	QSttSclIedSkectMapWidget(QWidget *parent = 0);
	~QSttSclIedSkectMapWidget();

public:
	void InitUI();
	void InitConnection();
	void ShowIED(CSclIed *pSclIed);//绘制IED

	void UpdateViewScale(qreal scale);// 设置场景视图的缩放

public slots:
	void slot_ZoomIn();
	void slot_ZoomOut();
public:
	QSttSclIedDrawViewWidget *m_pSttSclViewWidget;
	QPushButton *m_pBtnZoomIn;//缩小
	QPushButton *m_pBtnZoomOut;//放大
	
};
#endif