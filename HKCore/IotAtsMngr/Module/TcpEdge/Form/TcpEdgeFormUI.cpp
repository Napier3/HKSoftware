#include "stdafx.h"
#include "TcpEdgeFormUI.h"
#include <QHBoxLayout>
#include <QGraphicsBlurEffect>
#include <qmath.h>

CTcpEdgeFormUI::CTcpEdgeFormUI(QWidget* parent)
	: QDialog(parent)
{
	m_bLButtonDown = false;
	m_pProducePkg = NULL;
	m_pDevice = NULL;
	m_pWidget = NULL;
	m_pTitle = NULL;
}

CTcpEdgeFormUI::~CTcpEdgeFormUI()
{

}

void CTcpEdgeFormUI::EnableBlur(bool bEnabled)
{
	if(bEnabled)
	{
		QGraphicsBlurEffect* blur = (QGraphicsBlurEffect*)graphicsEffect();
		if(!blur)
		{
			blur = new QGraphicsBlurEffect;
			blur->setBlurRadius(50);
			setGraphicsEffect(blur);
		}
	}
	else
	{
		QGraphicsBlurEffect* blur = (QGraphicsBlurEffect*)graphicsEffect();
		delete blur;
		setGraphicsEffect(NULL);
	}
}

void CTcpEdgeFormUI::InitFormUI(QWidget* pWidget, QWidget* pTitle)
{
	if(!pWidget)
	{
		return;
	}

	m_pWidget = pWidget;
	m_pWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	m_pWidget->setMouseTracking(true);

	m_pTitle = pTitle;
	if(!m_pTitle)
	{
		m_pTitle = pWidget;	
	}

	m_pTitle->setMouseTracking(true);
}

void CTcpEdgeFormUI::RecordToDataset()
{
	
}

QPushButton* CTcpEdgeFormUI::AddGridButton(QTableWidget* pTable, long nRow, long nCol, const QString& strName)
{
	QWidget* pWidget = pTable->cellWidget(nRow, nCol);
	if(pWidget)
	{
		QPushButton* pChild = pWidget->findChild<QPushButton*>("GridButton");
		return pChild;
	}

	pWidget = new QWidget(pTable);
	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	pWidget->setLayout(pLayout);
	QPushButton* pButton = new QPushButton(pWidget);
	pButton->setObjectName("GridButton");
	QTableWidgetItem* pItem = pTable->item(nRow, 0);
	pButton->setProperty("GridButtonRow", QVariant::fromValue(pItem));
	pButton->setProperty("GridButtonColumn", QVariant::fromValue(nCol));
	pButton->setText(strName);
	pLayout->setSpacing(0);
	pLayout->setMargin(0);
	pLayout->addWidget(pButton);
	pLayout->setAlignment(pButton, Qt::AlignCenter);
	pTable->setCellWidget(nRow, nCol, pWidget);
	return pButton;
}

void CTcpEdgeFormUI::mouseMoveEvent(QMouseEvent* event)
{
	if(m_bLButtonDown)
	{
		m_pWidget->move(m_pWidget->geometry().topLeft() + event->globalPos() - m_ptStart);
		m_ptStart = event->globalPos();		
	}
}

void CTcpEdgeFormUI::mousePressEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
		long nHeight = m_pTitle->height();
		if(event->pos().y() < nHeight)
		{
			m_bLButtonDown = true;
			m_ptStart = event->globalPos();
		}
	}
}

void CTcpEdgeFormUI::mouseReleaseEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_bLButtonDown = false;
	}
}

void CTcpEdgeFormUI::paintEvent(QPaintEvent *event)
{
// 	QPainterPath path;
// 	path.setFillRule(Qt::WindingFill);
// 	QRectF rect(10, 10, this->width()-20, this->height()-20);
// 	path.addRoundRect(rect, 8, 8);
// 
// 	QPainter painter(this);
// 	painter.setRenderHint(QPainter::Antialiasing, true);
// 	painter.fillPath(path, QBrush(Qt::white));
// 
// 	QColor color(0, 0, 0, 50);
// 	for(int i = 0; i < 10; i++) {
// 		QPainterPath path;
// 		path.setFillRule(Qt::WindingFill);
// 		path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
// 		color.setAlpha(150 - qSqrt(i)*50);
// 		painter.setPen(color);
// 		painter.drawPath(path);
// 	}
}

void CTcpEdgeFormUI::slot_autoConnected(int nState)
{
	QObject* pObj = sender();
	QString strName = pObj->objectName();
	long nStart = strName.indexOf("__") + 2;
	long nEnd = strName.lastIndexOf("__");
	QString strTempName = strName.mid(nStart, nEnd - nStart);
	QWidget* pTempObj = (QWidget*)findChild<QWidget*>("_" + strTempName + "_");

	if(!nState)
	{
		pTempObj->setEnabled(false);
	}
	else
	{
		pTempObj->setEnabled(true);
	}

	CDvmData* pData = (CDvmData*)m_pProducePkg->FindByID(strTempName);
	pData->m_dwItemData = (DWORD)(nState != 0);
}