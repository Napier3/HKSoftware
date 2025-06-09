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
	void ShowIED(CSclIed *pSclIed);//����IED

	void UpdateViewScale(qreal scale);// ���ó�����ͼ������

public slots:
	void slot_ZoomIn();
	void slot_ZoomOut();
public:
	QSttSclIedDrawViewWidget *m_pSttSclViewWidget;
	QPushButton *m_pBtnZoomIn;//��С
	QPushButton *m_pBtnZoomOut;//�Ŵ�
	
};
#endif