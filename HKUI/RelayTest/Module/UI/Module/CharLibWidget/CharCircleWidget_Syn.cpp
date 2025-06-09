#include "CharCircleWidget_Syn.h"
#include <QPolygonF>

#define ANGLE_MAX 360
#define ANGLE_HALF 180
#define ANGLE_HALFTOHALF 90
#define ANGLE_DEGREESYSTEM 16

QCharCircleWidget_Syn::QCharCircleWidget_Syn(QWidget *parent)
	: QWidget(parent)
{
	m_nStartAngle = ANGLE_HALFTOHALF/2 * ANGLE_DEGREESYSTEM; // 转换为1/16度制  
	m_nSpanAngle = ANGLE_HALFTOHALF * ANGLE_DEGREESYSTEM; // 跨越90度 

	m_fAngleDegrees = ANGLE_HALFTOHALF;
}


void QCharCircleWidget_Syn::SetAngle(int nStartAngle, int nSpanAngle)
{
	strStartAngle = QString::number(nStartAngle);
	strSpanAngle = QString::number(nSpanAngle);
	m_nStartAngle = (ANGLE_HALFTOHALF + nStartAngle) * ANGLE_DEGREESYSTEM; // 转换为1/16度制  
	m_nSpanAngle = (nSpanAngle - nStartAngle) * ANGLE_DEGREESYSTEM; // 转换为1/16度制  
}

void QCharCircleWidget_Syn::SetArrowhead(float fAngleDegrees)
{
	
	m_fAngleDegrees = (ANGLE_HALFTOHALF + fAngleDegrees);
}


void QCharCircleWidget_Syn:: paintEvent(QPaintEvent *event)  
{
	QPainter painter(this);
	// 圆的参数  
	// 获取窗口部件的宽度和高度  
	int nWidth = this->width();
	int nHeight = this->height();

	// 设定圆的半径和圆心位置（这里放在右下角）  减去一些空间以便标签可见  
	int radius = qMin(nWidth / 2, nHeight / 2) - 10;
	// 圆心位置是窗口部件的右下角减去圆的半径  
	int nCenterX = nWidth - radius; // 圆的圆心的x坐标  
	int nCenterY = nHeight - radius; // 圆的圆心的y坐标  

	QPen dashedPen(Qt::black, 2, Qt::DashLine);
	painter.setPen(dashedPen);

	// 绘制将圆均分为四份的虚线  
	// 第一条从圆的底部到顶部（水平）  
	painter.drawLine(nCenterX - radius, nCenterY, nCenterX + radius, nCenterY);
	// 第二条从圆的左侧到右侧（垂直）  
	painter.drawLine(nCenterX, nCenterY - radius, nCenterX, nCenterY + radius);

	QPen ArrowheadPen(Qt::red, 2);
	painter.setPen(ArrowheadPen);

	// 转换为弧度  绘制的角度（以度为单位），这里以90度为例
	float fAngleRadians = m_fAngleDegrees * _PI / ANGLE_HALF;

	// 计算角度对应的点  
	int x = nCenterX + static_cast<int>(radius * cos(fAngleRadians));
	int y = nCenterY - static_cast<int>(radius * sin(fAngleRadians));

	// 绘制箭头的主体部分  
	painter.drawLine(nCenterX, nCenterY, x, y);

	// 绘制箭头  
	int nArrowSize = 10; // 箭头大小  
	float fAngle = atan2((float)y - (float)nCenterY, (float)x - (float)nCenterX) + _PI / 2; // 计算箭头方向  

	// 计算箭头三个顶点的位置  
	QPointF p1(x - nArrowSize * cos(fAngle - _PI / 3), y - nArrowSize * sin(fAngle - _PI / 3));
	QPointF p2(x, y);
	QPointF p3(x + nArrowSize * cos(fAngle + _PI / 3), y + nArrowSize * sin(fAngle + _PI / 3));

	// 绘制箭头  
	QPolygonF oQPolygonF;
	oQPolygonF << p1 << p2 << p3;
	painter.drawPolygon(oQPolygonF/*QPolygonF({ p1, p2, p3 })*/);//???????编译问题

	// （圆心）  
	QPoint arrowStart(nCenterX, nCenterY); // 圆心位置  
	
	// 绘制扇形  
	QPen PiePen(Qt::green, 1, Qt::DashLine);
	painter.setPen(PiePen);

	// 外包矩形的宽度和高度都是2倍的半径，因为圆心在矩形的中心  
	painter.drawPie(nCenterX - radius, nCenterY - radius, 2 * radius, 2 * radius, m_nStartAngle, m_nSpanAngle);

	// 计算并绘制度数标签的位置  
	QString strDegreeText = strStartAngle + QString::fromLocal8Bit("°");
	QFontMetrics fm(painter.font());
	QRect textRect = fm.boundingRect(strDegreeText);

	// 文本标签1：放在扇形的起始侧  
	int nTextX1 = nCenterX + (radius + 10) * cos(m_nStartAngle * _PI / ANGLE_HALF / ANGLE_DEGREESYSTEM);
	int nTextY1 = nCenterY - radius / 2 * sin(m_nStartAngle * _PI / ANGLE_HALF / ANGLE_DEGREESYSTEM);
	painter.drawText(nTextX1, nTextY1, strDegreeText);

	// 文本标签2：放在扇形的结束侧  
	// 首先计算结束角度  
	strDegreeText = strSpanAngle + QString::fromLocal8Bit("°");
	int nEndAngle = m_nStartAngle + m_nSpanAngle;
	// 注意：如果endAngle大于360*16，需要取模以避免负值或过大值  
	nEndAngle %= ANGLE_MAX * ANGLE_DEGREESYSTEM;
	int nTextX2 = nCenterX + (radius + 10) * cos(nEndAngle * _PI / ANGLE_HALF / ANGLE_DEGREESYSTEM);
	int nTextY2 = nCenterY - radius / 2 * sin(nEndAngle * _PI / ANGLE_HALF / ANGLE_DEGREESYSTEM);
	painter.drawText(nTextX2, nTextY2, strDegreeText);

	// 字体设置  
	QFont font("Arial", 10);
	CString strPhase = QString::fromLocal8Bit("°");
	painter.setFont(font);
	// 绘制标签  
	painter.drawText(arrowStart + QPoint(radius - 25, 0), "-90" + strPhase);
	painter.drawText(arrowStart + QPoint(0, -radius + 15), "0" + strPhase);
	painter.drawText(arrowStart + QPoint(-radius + 5, 0), "+90" + strPhase);
	painter.drawText(arrowStart + QPoint(0, radius - 5), "180" + strPhase);

	// 设置圆的样式  
	QPen circlePen(Qt::black, 2); // 黑色，2像素宽  
	painter.setPen(circlePen);
	// 绘制圆  
	painter.drawEllipse(nCenterX - radius, nCenterY - radius, 2 * radius, 2 * radius);

}
