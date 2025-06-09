#include "SttIecSmvWaveMainWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"

extern CFont *g_pSttGlobalFont;  

QSttIecSmvWaveMainWidget ::QSttIecSmvWaveMainWidget (QWidget *parent)
    : QWidget(parent)
{
	InitUI();
	initConnect();
}

QSttIecSmvWaveMainWidget ::~QSttIecSmvWaveMainWidget ()
{

	if (m_pSttIecSmvWaveWidget != NULL)
	{
		m_pSttIecSmvWaveWidget ->Release();
		m_pSttIecSmvWaveWidget = NULL;
		delete m_pSttIecSmvWaveWidget;
	}
	
}


void QSttIecSmvWaveMainWidget::InitUI()
{
	m_pIecRcdFuncWidget = this;
	m_pSttIecSmvWaveWidget = new QSttIecSmvWaveWidget(this);

	CString strPngPath, strBntIcon;

// 	m_pBtnReset =new QPushButton("复归",this);
// 	m_pBtnReset->setFont(*g_pSttGlobalFont);


#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();

	strBntIcon = strPngPath + _T("ZoomOutTime.png");
#else
	strBntIcon =  ":/ctrls/images/ZoomOutTime.png";
#endif
	m_pBtnZoomOutTime=new QPushButton(/*"横放大",*/this);
	m_pBtnZoomOutTime->setIcon(QIcon(strBntIcon));
	m_pBtnZoomOutTime->setIconSize(m_pBtnZoomOutTime->size());

	m_pBtnZoomInTime=new QPushButton(/*"横缩小",*/this);
#ifdef _PSX_QT_WINDOWS_
	strBntIcon = strPngPath + _T("ZoomInTime.png");
#else
	strBntIcon =  ":/ctrls/images/ZoomInTime.png";
#endif
	m_pBtnZoomInTime->setIcon(QIcon(strBntIcon));
	m_pBtnZoomInTime->setIconSize(m_pBtnZoomInTime->size());

// 	m_pBtnZoomOutChan=new QPushButton(/*"纵放大",*/this);
// 	strBntIcon = strPngPath + _T("ZoomOutChan.png");
// 	m_pBtnZoomOutChan->setIcon(QIcon(strBntIcon));
// 	m_pBtnZoomOutChan->setIconSize(m_pBtnZoomOutChan->size());
// 
// 	m_pBtnZoomInChan=new QPushButton(/*"纵缩小",*/this);
// 	strBntIcon = strPngPath + _T("ZoomInChan.png");
// 	m_pBtnZoomInChan->setIcon(QIcon(strBntIcon));
// 	m_pBtnZoomInChan->setIconSize(m_pBtnZoomInChan->size());
// 
// 	m_pBtnMoveLeft=new QPushButton("左移",this);
// 	// 	strBntIcon = strPngPath + _T("moveleft.png");
// 	// 	m_pBtnMoveLeft->setIcon(QIcon(strBntIcon));
// 
// 	m_pBtnMoveRight=new QPushButton("右移",this);
	// 	strBntIcon = strPngPath + _T("moveright.png");
	// 	m_pBtnMoveRight->setIcon(QIcon(strBntIcon));

	m_pBtnHBoxLayout = new QHBoxLayout();

	m_pBtnHBoxLayout->addStretch();
	m_pBtnHBoxLayout->addWidget(m_pBtnZoomOutTime);
	m_pBtnHBoxLayout->addWidget(m_pBtnZoomInTime);
// 	m_pBtnHBoxLayout->addWidget(m_pBtnZoomOutChan);
// 	m_pBtnHBoxLayout->addWidget(m_pBtnZoomInChan);
// 	m_pBtnHBoxLayout->addWidget(m_pBtnMoveLeft);
// 	m_pBtnHBoxLayout->addWidget(m_pBtnMoveRight);
// 	m_pBtnHBoxLayout->addWidget(m_pBtnReset);
	m_pBtnHBoxLayout->addStretch();

	m_pMainVBoxLayout = new QVBoxLayout();

	m_pMainVBoxLayout->addWidget(m_pSttIecSmvWaveWidget);
	m_pMainVBoxLayout->addLayout(m_pBtnHBoxLayout);

	this->setLayout(m_pMainVBoxLayout);
}

void QSttIecSmvWaveMainWidget ::initConnect()
{
// 	connect(m_pBtnReset,SIGNAL(clicked()),this,SLOT(slot_Reset()));
	connect(m_pBtnZoomOutTime,SIGNAL(clicked()),this,SLOT(ZoomOutTime()));
	connect(m_pBtnZoomInTime,SIGNAL(clicked()),this,SLOT(ZoomInTime()));
// 	connect(m_pBtnZoomOutChan,SIGNAL(clicked()),this,SLOT(ZoomInChan()));
// 	connect(m_pBtnZoomInChan,SIGNAL(clicked()),this,SLOT(ZoomOutChan()));
// 	connect(m_pBtnMoveLeft,SIGNAL(clicked()),this,SLOT(MoveLeft()));
// 	connect(m_pBtnMoveRight,SIGNAL(clicked()),this,SLOT(MoveRight()));

}

void QSttIecSmvWaveMainWidget ::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	
	m_pSttIecSmvWaveWidget->IecRcdFunc(pCapDevice);

}

void QSttIecSmvWaveMainWidget ::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->IecRcdFuncUpdate(pCapDevice);
}

BOOL QSttIecSmvWaveMainWidget ::NeedConfig()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return FALSE;
	}

	return m_pSttIecSmvWaveWidget->NeedConfig();;
}

void QSttIecSmvWaveMainWidget ::Release()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->Release();
	m_pSttIecSmvWaveWidget = NULL;
    delete	m_pSttIecSmvWaveWidget;

	delete this;
}

BOOL QSttIecSmvWaveMainWidget ::NeedNextAndPrev()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return FALSE;
	}
	
	return m_pSttIecSmvWaveWidget->NeedNextAndPrev();
}

void QSttIecSmvWaveMainWidget ::NextPage()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->NextPage();


}

void QSttIecSmvWaveMainWidget ::PrevPage()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->PrevPage();
}

void QSttIecSmvWaveMainWidget ::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->mouseDoubleClickEvent(event);
}

void QSttIecSmvWaveMainWidget ::mouseMoveEvent(QMouseEvent *event)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->mouseMoveEvent(event);
}

void QSttIecSmvWaveMainWidget ::mousePressEvent(QMouseEvent *event)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->mousePressEvent(event);
}

void QSttIecSmvWaveMainWidget ::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->mouseReleaseEvent(event);
}

void QSttIecSmvWaveMainWidget ::wheelEvent(QWheelEvent *event)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->wheelEvent(event);
}

void QSttIecSmvWaveMainWidget ::paintEvent(QPaintEvent *event)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->paintEvent(event);
}

void QSttIecSmvWaveMainWidget ::resizeEvent(QResizeEvent *pReSizeEvent)
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->resizeEvent(pReSizeEvent);

}

//根据录波数据缓冲区的数据长度，计算获得当前显示的波形的长度
//同时设置时间坐标的范围
void QSttIecSmvWaveMainWidget ::InitTimeAxis()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->InitTimeAxis();
}

void QSttIecSmvWaveMainWidget ::MoveLeft()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->MoveLeft();

}

void QSttIecSmvWaveMainWidget ::MoveRight()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->MoveRight();
}

void QSttIecSmvWaveMainWidget ::ZoomInChan()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->ZoomInChan();
}

void QSttIecSmvWaveMainWidget ::ZoomOutChan()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->ZoomOutChan();
}

void QSttIecSmvWaveMainWidget ::ZoomInTime()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->ZoomInTime();
}

void QSttIecSmvWaveMainWidget ::ZoomOutTime()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->ZoomOutTime();
}

void QSttIecSmvWaveMainWidget ::slot_Reset()
{
	if (m_pSttIecSmvWaveWidget == NULL)
	{
		return;
	}
	m_pSttIecSmvWaveWidget->slot_Reset();
}	