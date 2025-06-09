#include "SttSclCommonComponent.h"
#include <qmath.h>

#include <qpainter.h>
#include <qwt_scale_map.h>
#include <qwt_plot_curve.h>
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

#include "../SttSclFileParseDialog.h"
//--------

 //0.linedialog.cpp
 //1.arrow.cpp
 //3.small_rect.cpp
 //4.RectMAkRer.cpp

//////////////////////////////
//0.linedialog.cpp

//--------------------------------

QList<_IED_INFO*> g_oTotalIEDList;
QList<CString> g_oGloalIEDNameList;
QHash<QString,int>  g_oIED_Hash;
//------------------------------------

class CArrowLine
{
public:
	CArrowLine()
	{
		m_heigh = 14;
		m_width = 8;
	};

	void Draw(QPainter *painter, QPointF m_startPointF, QPointF m_endPointF)
	{
		painter->save();

		QPen pen = painter->pen();
		pen.setWidthF(2);
		pen.setColor(qRgb(238, 187, 107));
		painter->setPen(pen);

		//坐标变换
		painter->translate(m_endPointF);

		//顺时针旋转角度(度)
		double angle = 180*qAtan((m_endPointF.x() - m_startPointF.x())/(m_startPointF.y() - m_endPointF.y()))/M_PI;
		if(m_startPointF.x() > m_endPointF.x())
			angle = angle > 0 ? angle-180 : angle;
		else
			angle = angle < 0 ? angle+180 : angle;

		painter->rotate(angle);

		static QPointF arrow[3]=
		{
			QPointF(-m_width/2, m_heigh),
			QPointF(m_width/2, m_heigh),
			QPointF(0,0)
		};
		painter->drawConvexPolygon(arrow, 3);

		QPointF disPointF = m_endPointF - m_startPointF;
		double distance = qSqrt(disPointF.x()*disPointF.x() + disPointF.y()*disPointF.y());
		painter->drawLine(QPointF(0,0), QPointF(0,distance));

		painter->restore();
	}

private:
	double m_width;
	double m_heigh;
};

class CDrawItem: public QwtPlotItem
{
public:
	CDrawItem(Arrow_Struct *_pData)
	{
		m_pData = _pData;

		m_parament.width = 274;
		m_parament.leftMargin = 80;
		m_parament.textMargin = 10;
		m_parament.textWidth = m_parament.width - 2*m_parament.textMargin;
		m_parament.rowHeight = 25;
		m_parament.topMargin = 20;

		setRenderHint( QwtPlotItem::RenderAntialiased, true );
	}

	~CDrawItem()
	{
		Clear();
	}

	void Clear()
	{

		foreach(Channel_Struct *pChannel_Struct, m_leftRect.channelList)
		{
			delete pChannel_Struct;
		}

		m_leftRect.channelList.clear();

		foreach(Channel_Struct *pChannel_Struct, m_rightRect.channelList)
		{
			delete pChannel_Struct;
		}

		m_rightRect.channelList.clear();

		foreach(Line_Struct *line, m_lineList)
		{
			delete line;
		}
		m_lineList.clear();
	}

	//返回矩形的最大高度
	double InitData()
	{
		Clear();

		switch(m_pData->type)
		{
		case Arrow_Struct::ARROW_GSE:
			{
				m_pos = POS_RIGHT;

				//接收方在右边，发送方在左边
				_IED_INFO *subIedInfo = g_oTotalIEDList.at(m_pData->dat.pub.subIED);
				m_rightRect.text = subIedInfo->name + "\n" + subIedInfo->desc;
	                        m_rightRect.typeText = /*QObject::tr("GOOSE 接收")*/g_sLangTxt_Native_gooseReceive;
				//m_rightRect.typeText = CString("GOOSE 接收");

				_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);
				_GSE_INFO gseInfo = iedInfo->GSEList.at(m_pData->dat.pub.block);
				m_leftRect.text = iedInfo->name + "\n" + iedInfo->desc;
				m_leftRect.typeText = "GOOSE 0x" + gseInfo.APPID;
				int iChannel = 1;
				foreach(_PUB_REC_INFO pubInfo, gseInfo.pubList)
				{
					foreach(_CONNECT_PUB_INFO conInfo, pubInfo.recPubList)
					{
						if (conInfo.index_IED == m_pData->dat.pub.subIED)
						{
							Line_Struct *lineStru = new Line_Struct;
							lineStru->color = qRgb(238,174,14);
							m_lineList.append(lineStru);

							Channel_Struct *channel = new Channel_Struct;
							QString descTemRec="";
							int inCHANNELMDY=conInfo.index_Rec + 1;
							int outCHANNELMDY=iChannel;
							if (conInfo.index_Rec<subIedInfo->GOSubList.size())
							{
								_SUB_REC_INFO subrecinfo=subIedInfo->GOSubList.at(conInfo.index_Rec);
								 inCHANNELMDY=subrecinfo.ExtCHIndex;
								 outCHANNELMDY=subrecinfo.ExtCHOutIndex;
								descTemRec=subIedInfo->GOSubList.at(conInfo.index_Rec).desc;
							}
							
							//inCHANNELMDY
							//channel->name = QString("%1-%2").arg(conInfo.index_Rec + 1).arg(descTemRec);
							channel->name = QString("%1-%2").arg(inCHANNELMDY).arg(descTemRec);
							channel->line = lineStru;
							m_rightRect.channelList.append(channel);
						
							//outCHANNELMDY
							channel = new Channel_Struct;
							//channel->name = QString("%1-%2").arg(iChannel).arg(pubInfo.desc);
							channel->name = QString("%1-%2").arg(outCHANNELMDY).arg(pubInfo.desc);
							channel->line = lineStru;
							m_leftRect.channelList.append(channel);
						}
					}

					iChannel++;
				}

				break;
			}
		case Arrow_Struct::ARROW_SMV:
			{
				m_pos = POS_RIGHT;

				//接收方在右边，发送方在左边
				_IED_INFO *subIedInfo = g_oTotalIEDList.at(m_pData->dat.pub.subIED);
				m_rightRect.text = subIedInfo->name + "\n" + subIedInfo->desc;
				//m_rightRect.typeText = CString("SMV 接收");
                                m_rightRect.typeText = /*QObject::tr("SMV 接收")*/g_sLangTxt_Native_smvReceive;

				_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);
				_SMV_INFO gseInfo = iedInfo->SMVList.at(m_pData->dat.pub.block);
				m_leftRect.text = iedInfo->name + "\n" + iedInfo->desc;
				m_leftRect.typeText = "SMV 0x" + gseInfo.APPID;
				int iChannel = 1;
				foreach(_PUB_REC_INFO pubInfo, gseInfo.pubList)
				{
					foreach(_CONNECT_PUB_INFO conInfo, pubInfo.recPubList)
					{
						if (conInfo.index_IED == m_pData->dat.pub.subIED)
						{
							Line_Struct *lineStru = new Line_Struct;
							lineStru->color = qRgb(238,174,14);
							m_lineList.append(lineStru);

							Channel_Struct *channel = new Channel_Struct;
							QString descTemaaA="";
							int inCHANNELMDY=conInfo.index_Rec + 1;
							int outCHANNELMDY=iChannel;
							if (conInfo.index_Rec<subIedInfo->SVSubList.size())
							{
								_SUB_REC_INFO subrecinfo=subIedInfo->SVSubList.at(conInfo.index_Rec);
								inCHANNELMDY=subrecinfo.ExtCHIndex;
								outCHANNELMDY=subrecinfo.ExtCHOutIndex;
								descTemaaA=subIedInfo->SVSubList.at(conInfo.index_Rec).desc;
							}
							//inCHANNELMDY
							//channel->name = QString("%1-%2").arg(conInfo.index_Rec + 1).arg(descTemaaA);
							channel->name = QString("%1-%2").arg(inCHANNELMDY).arg(descTemaaA);
							channel->line = lineStru;
							m_rightRect.channelList.append(channel);
							
							//outCHANNELMDY
							channel = new Channel_Struct;
							//channel->name = QString("%1-%2").arg(iChannel).arg(pubInfo.desc);
							channel->name = QString("%1-%2").arg(outCHANNELMDY).arg(pubInfo.desc);
							channel->line = lineStru;
							m_leftRect.channelList.append(channel);
						}
					}

					iChannel++;
				}

				break;
			}
		case Arrow_Struct::ARROW_GOOSE_SUB:
			{
				m_pos = POS_LEFT;

				//接收方在左边，发送方在右边
				_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);
				m_leftRect.text = iedInfo->name + "\n" + iedInfo->desc;
				//m_leftRect.typeText = CString("GOOSE 接收");
				m_leftRect.typeText = /*QObject::tr("GOOSE 接收")*/g_sLangTxt_Native_gooseReceive;

				_IED_INFO *subIedInfo = g_oTotalIEDList.at(m_pData->dat.sub.subIED);
				_GSE_INFO gseInfo = subIedInfo->GSEList.at(m_pData->dat.sub.subBlock);
				m_rightRect.text = subIedInfo->name + "\n" + subIedInfo->desc;
				m_rightRect.typeText = "GOOSE 0x" + gseInfo.APPID;
				int iChannel = 1;
				foreach(_SUB_REC_INFO subInfo, iedInfo->GOSubList)
				{
					if (subInfo.index_IED == m_pData->dat.sub.subIED
						&& subInfo.index_GSE_SMV == m_pData->dat.sub.subBlock)
					{
						int inCHANNELMDY=subInfo.ExtCHIndex;
						int outCHANNELMDY=subInfo.ExtCHOutIndex;
						Line_Struct *lineStru = new Line_Struct;
						lineStru->color = qRgb(238,174,14);
						m_lineList.append(lineStru);

						Channel_Struct *channel = new Channel_Struct;
						//channel->name = QString("%1-%2").arg(subInfo.index_Rec + 1).
						//	arg(subIedInfo.GSEList.at(subInfo.index_GSE_SMV).pubList.at(subInfo.index_Rec).desc);
						//-------------
						channel->name = QString("%1-%2").arg(outCHANNELMDY).
								arg(subIedInfo->GSEList.at(subInfo.index_GSE_SMV).pubList.at(subInfo.index_Rec).desc);
						//--------------
						channel->line = lineStru;
						m_rightRect.channelList.append(channel);

						channel = new Channel_Struct;
						//channel->name = QString("%1-%2").arg(iChannel).arg(subInfo.desc);
						//--------------
						channel->name = QString("%1-%2").arg(inCHANNELMDY).arg(subInfo.desc);
						//-------------
						channel->line = lineStru;
						m_leftRect.channelList.append(channel);
					}

					iChannel++;
				}

				break;
			}
		case Arrow_Struct::ARROW_SMV_SUB:
			{
				m_pos = POS_LEFT;

				//接收方在左边，发送方在右边
				_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);
				m_leftRect.text = iedInfo->name + "\n" + iedInfo->desc;
				//m_leftRect.typeText = CString("SMV 接收");
				m_leftRect.typeText = /*QObject::tr("SMV 接收")*/g_sLangTxt_Native_smvReceive;


				_IED_INFO *subIedInfo = g_oTotalIEDList.at(m_pData->dat.sub.subIED);
				_SMV_INFO gseInfo = subIedInfo->SMVList.at(m_pData->dat.sub.subBlock);
				m_rightRect.text = subIedInfo->name + "\n" + subIedInfo->desc;
				m_rightRect.typeText = "SMV 0x" + gseInfo.APPID;
				int iChannel = 1;
				foreach(_SUB_REC_INFO subInfo, iedInfo->SVSubList)
				{
					if (subInfo.index_IED == m_pData->dat.sub.subIED
						&& subInfo.index_GSE_SMV == m_pData->dat.sub.subBlock)
					{
						int inCHANNELMDY=subInfo.ExtCHIndex;
						int outCHANNELMDY=subInfo.ExtCHOutIndex;
						Line_Struct *lineStru = new Line_Struct;
						lineStru->color = qRgb(238,174,14);
						m_lineList.append(lineStru);

						Channel_Struct *channel = new Channel_Struct;
	/*					channel->name = QString("%1-%2").arg(subInfo.index_Rec + 1).
							arg(subIedInfo.SMVList.at(subInfo.index_GSE_SMV).pubList.at(subInfo.index_Rec).desc);*/
						//-----------------
						channel->name = QString("%1-%2").arg(outCHANNELMDY).
							arg(subIedInfo->SMVList.at(subInfo.index_GSE_SMV).pubList.at(subInfo.index_Rec).desc);
						//-----------------
						channel->line = lineStru;
						m_rightRect.channelList.append(channel);

						channel = new Channel_Struct;
						
						//channel->name = QString("%1-%2").arg(iChannel).arg(subInfo.desc);
						//--------------
						channel->name = QString("%1-%2").arg(inCHANNELMDY).arg(subInfo.desc);
						//-------------
						channel->line = lineStru;
						m_leftRect.channelList.append(channel);
					}

					iChannel++;
				}

				break;
			}
		default:
			break;
		}

		//求出左右矩形的最高高度
		QwtText text("", QwtText::RichText);
		QFont font = plot()->axisFont(QwtPlot::yLeft);
		text.setFont(font);
		text.setText(m_leftRect.text);
		text.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);
		m_parament.leftTextHeight = text.heightForWidth(m_parament.textWidth);

		//求出左右矩形的最高高度
		text.setText(m_rightRect.text);
		m_parament.rightTextHeight = text.heightForWidth(m_parament.textWidth);

		if (m_leftRect.channelList.size() > m_rightRect.channelList.size())
		{

			double height = m_parament.leftTextHeight + (m_leftRect.channelList.size()+1)*m_parament.rowHeight + 2*m_parament.topMargin 
				+ 2*m_parament.textMargin;

			return height;
		}
		else
		{
			double height =m_parament.rightTextHeight + (m_rightRect.channelList.size()+1)*m_parament.rowHeight + 2*m_parament.topMargin 
				+ 2*m_parament.textMargin;

			return height;
		}
	}


	virtual int rtti() const
	{
		return QwtPlotItem::Rtti_PlotUserItem;
	};

	virtual void draw( QPainter *painter,
		const QwtScaleMap &xMap, const QwtScaleMap &yMap, const QRectF &/*rect*/ ) const
	{
		double xValue,yValue;
		double coordWidth,coordHeight; //x y坐标
		QPointF topLeftPointF, bottomRightPointF;

		coordWidth = xMap.sDist();
		coordHeight = yMap.sDist();

		QPen pen = painter->pen();
		pen.setWidth(2);
		painter->setPen(pen);

		//画左边的矩形
		QwtText text(m_leftRect.text, QwtText::RichText);
		QFont font = plot()->axisFont(QwtPlot::xBottom);
		text.setFont(font);
		text.setText(m_leftRect.text);
		text.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);

		xValue = m_parament.leftMargin;
		yValue = m_parament.topMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));

		xValue += m_parament.width;
		yValue += m_parament.leftTextHeight + m_leftRect.channelList.size()*m_parament.rowHeight 
			+ m_parament.rowHeight + 3*m_parament.textMargin;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));

		QBrush brush = painter->brush();
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(qRgb(196,243,196));
		painter->setBrush(brush);
		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));

		xValue = m_parament.leftMargin + m_parament.textMargin;
		yValue = m_parament.topMargin + m_parament.textMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));
		
		xValue += m_parament.textWidth;
		yValue += m_parament.leftTextHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));
		text.draw(painter, QRectF(topLeftPointF, bottomRightPointF));

		xValue -= m_parament.textWidth;
		yValue += m_parament.textMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));
		xValue += m_parament.textWidth;
		yValue += m_parament.rowHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));

		brush.setColor(qRgb(250, 167, 243));
		painter->setBrush(brush);

		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
		text.setText(m_leftRect.typeText);
		text.draw(painter,QRectF(topLeftPointF, bottomRightPointF));

		brush.setColor(qRgb(208, 206, 209));
		painter->setBrush(brush);
		text.setRenderFlags(Qt::AlignVCenter|Qt::AlignLeft);
		
		foreach(Channel_Struct *channel, m_leftRect.channelList)
		{
			xValue -= m_parament.textWidth;
			topLeftPointF.setX(xMap.transform(xValue));
			topLeftPointF.setY(yMap.transform(yValue));
			xValue += m_parament.textWidth;
			yValue += m_parament.rowHeight;
			bottomRightPointF.setX(xMap.transform(xValue));
			bottomRightPointF.setY(yMap.transform(yValue));
			
			painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
			text.setText(" "+channel->name);
			text.draw(painter,QRectF(topLeftPointF, bottomRightPointF));

			if (m_pos == POS_LEFT)
			{
				channel->line->endPointF.setX(xMap.transform(xValue));
				channel->line->endPointF.setY(yMap.transform(yValue - m_parament.rowHeight/2));
			}
			else
			{
				channel->line->startPointF.setX(xMap.transform(xValue));
				channel->line->startPointF.setY(yMap.transform(yValue - m_parament.rowHeight/2));
			}
		}

		//右边的矩形
		text.setText(m_rightRect.text);
		text.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);

		xValue = coordWidth - m_parament.leftMargin - m_parament.width;
		yValue = m_parament.topMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));

		xValue += m_parament.width;
		yValue += m_parament.rightTextHeight + m_leftRect.channelList.size()*m_parament.rowHeight 
			+ m_parament.rowHeight + 3*m_parament.textMargin;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));

		brush.setStyle(Qt::SolidPattern);
		brush.setColor(qRgb(229,242,196));
		painter->setBrush(brush);
		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));

		xValue = coordWidth - m_parament.leftMargin - m_parament.width + m_parament.textMargin;
		yValue = m_parament.topMargin + m_parament.textMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));

		xValue += m_parament.textWidth;
		yValue += m_parament.rightTextHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));
		text.draw(painter, QRectF(topLeftPointF, bottomRightPointF));

		xValue -= m_parament.textWidth;
		yValue += m_parament.textMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));
		xValue += m_parament.textWidth;
		yValue += m_parament.rowHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));

		brush.setColor(qRgb(250, 167, 243));
		painter->setBrush(brush);

		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
		text.setText(m_rightRect.typeText);
		text.draw(painter,QRectF(topLeftPointF, bottomRightPointF));

		brush.setColor(qRgb(208, 206, 209));
		painter->setBrush(brush);
		text.setRenderFlags(Qt::AlignVCenter|Qt::AlignLeft);

		foreach(Channel_Struct *channel, m_rightRect.channelList)
		{
			xValue -= m_parament.textWidth;
			topLeftPointF.setX(xMap.transform(xValue));
			topLeftPointF.setY(yMap.transform(yValue));
			xValue += m_parament.textWidth;
			yValue += m_parament.rowHeight;
			bottomRightPointF.setX(xMap.transform(xValue));
			bottomRightPointF.setY(yMap.transform(yValue));

			painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
			text.setText(" "+channel->name);
			text.draw(painter,QRectF(topLeftPointF, bottomRightPointF));

			if (m_pos == POS_RIGHT)
			{
				channel->line->endPointF.setX(xMap.transform(xValue-m_parament.textWidth));
				channel->line->endPointF.setY(yMap.transform(yValue - m_parament.rowHeight/2));
			}
			else
			{
				channel->line->startPointF.setX(xMap.transform(xValue-m_parament.textWidth));
				channel->line->startPointF.setY(yMap.transform(yValue - m_parament.rowHeight/2));
			}
		}

		//画线
		foreach(Line_Struct *line, m_lineList)
		{
			CArrowLine arrowLine;
			arrowLine.Draw(painter, line->startPointF, line->endPointF);
		}
	}

private:
	struct Line_Struct
	{
		QPointF startPointF;
		QPointF endPointF;
		QColor color;

		Line_Struct()
		{
			startPointF.setX(0);
			startPointF.setY(0);
			endPointF.setX(0);
			endPointF.setY(0);
		}
	};

	struct Channel_Struct
	{
		QString name;
		//QList<Line_Struct *> lineList;
		Line_Struct *line;
	};

	struct Rect_Struct
	{
		QString text;
		QString typeText;

		QList<Channel_Struct *> channelList;
	};

	enum
	{
		POS_LEFT,    //箭头朝左
		POS_RIGHT    //箭头朝右
	}m_pos;

	struct
	{
		int leftMargin;  //大矩形框左边的间隔
		int topMargin;   //大矩形框顶部的间隔
		int width;       //矩形宽度

		int textMargin;  //文字与矩形之间的间隔
		int textWidth;
		int rowHeight;    //行高

		int leftTextHeight;  //左边矩形文字占用的高度，只能初始的字体进行计算，否则放大缩小的时候，就会有错误
		int rightTextHeight;

	}m_parament;

	Rect_Struct m_leftRect;
	Rect_Struct m_rightRect;
	QList<Line_Struct *> m_lineList;

	Arrow_Struct *m_pData;

};

//////////////////////////////////////////////////////////////////////////

CLineDialog::CLineDialog(Arrow_Struct *_pData,QWidget *parent)
	: QDialog(parent),m_pData(_pData),m_coordWidth(800),m_coordHeight(500),m_minCoordHeight(500)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::WindowCloseButtonHint);//只显示关闭按钮。
//	setWindowFlags(Qt::Drawer);
	InitUI();

	m_zoomCount = 0;
	factor = 1.0;
	QFont font = m_plot->axisFont(QwtPlot::yLeft);
	//初始化，将字体还原到原始状态
	m_pointWidth = font.pointSizeF();
	font.setPointSizeF(m_pointWidth);
	m_plot->setAxisFont(QwtPlot::xBottom, font);

	//最大不超过25:738 30:863
	int clientTotalHeigt=(int)m_coordHeight;
	if (clientTotalHeigt > 738) 
	{
		m_coordHeight=(double)738;
	}

	resize(m_coordWidth, m_coordHeight);

//	setWindowTitle(CString("虚端子连接图"));
	setWindowTitle(/*tr("虚端子连接图")*/g_sLangTxt_Native_vTerminalConnectDia);

	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

CLineDialog::~CLineDialog()
{
}

//---------------------
void CLineDialog::InitScrollData()
{
#ifdef _PSX_QT_LINUX_
	QScrollBar* pScollBar=m_scrollArea->verticalScrollBar();
	InitScrollCtrl(pScollBar);
#endif

}

void CLineDialog::mousePressEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	mousePressEvent_ScrollBase(ev);
#endif
	QWidget::mousePressEvent( ev );
}


void CLineDialog::mouseMoveEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseMoveEvent_ScrollBase(ev))
	{
		//emit sig_MouseMoveGbTree(ev);
		return;
	}
#endif
	QWidget::mouseMoveEvent( ev );
}

void CLineDialog::mouseReleaseEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseReleaseEvent_ScrollBase(ev))
	{
		return;
	}
#endif
	QWidget::mouseReleaseEvent( ev );
}

void CLineDialog::InitUI()
{
	m_plot = new QwtPlot();

	m_scrollArea = new QScrollArea(this);
	m_scrollArea->setWidget(m_plot);

	QPushButton *zoomInButton = new QPushButton(/*tr("放大")*/g_sLangTxt_State_Magnify);

	connect(zoomInButton, SIGNAL(clicked()), SLOT(OnZoomInBtnClicked()));
	QPushButton *zoomOutButton = new QPushButton(/*tr("缩小")*/g_sLangTxt_State_Shrink);
	connect(zoomOutButton, SIGNAL(clicked()), SLOT(OnZoomOutBtnClicked()));
	QPushButton *exitButton = new QPushButton(CString("退出"));
	connect(exitButton, SIGNAL(clicked()), this,SLOT(close()));
	QHBoxLayout *hBoxLayout = new QHBoxLayout;
	hBoxLayout->setMargin(0);
	hBoxLayout->addStretch();
	hBoxLayout->addWidget(zoomInButton);
	hBoxLayout->addWidget(zoomOutButton);
	hBoxLayout->addWidget(exitButton);
	QVBoxLayout *vBoxLayout = new QVBoxLayout;
	//vBoxLayout->setMargin(0);
	//hBoxLayout->addWidget(button, Qt::AlignRight);
	vBoxLayout->addLayout(hBoxLayout);
	vBoxLayout->addWidget(m_scrollArea);
	setLayout(vBoxLayout);

	CDrawItem *item = new CDrawItem(m_pData);
	item->attach(m_plot);
	m_coordHeight = item->InitData();
	m_coordHeight = m_coordHeight > m_minCoordHeight ? m_coordHeight : m_minCoordHeight;
	m_plot->setAxisScale(QwtPlot::xBottom, 0, m_coordWidth);
	m_plot->setAxisScale(QwtPlot::yLeft, m_coordHeight, 0);
	m_canvasHeight = m_plot->transform(QwtPlot::yLeft,m_coordHeight);
	m_canvasWidth = m_plot->transform(QwtPlot::xBottom, m_coordWidth);
	m_plot->resize(m_canvasWidth, m_canvasHeight);
	m_plot->enableAxis(QwtPlot::yLeft, false);
	m_plot->enableAxis(QwtPlot::xBottom, false);

	// canvas
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setFocusIndicator( QwtPlotCanvas::CanvasFocusIndicator );
	canvas->setFocusPolicy( Qt::StrongFocus );
	canvas->setPalette( Qt::white );
	canvas->setCursor(QCursor(Qt::ClosedHandCursor));
	m_plot->setCanvas(canvas);
}

// 滚轮事件
void CLineDialog::wheelEvent(QWheelEvent *event)
{
	return;

	// 当滚轮远离使用者时进行放大，当滚轮向使用者方向旋转时进行缩小
	QFont font = m_plot->axisFont(QwtPlot::xBottom);
	if(event->delta() > 0)
	{
		if (m_zoomCount >= 3)
			return ;

		factor *= 1.25;
		m_plot->resize(factor*QSize(m_canvasWidth, m_canvasHeight));

		m_pointWidth *= 1.25;
		font.setPointSizeF(m_pointWidth);
		m_plot->setAxisFont(QwtPlot::xBottom, font);

		m_zoomCount++;
	}
	else
	{
		if(m_zoomCount == 0)
			return;

		factor *= 0.8;
		m_plot->resize(factor*QSize(m_canvasWidth, m_canvasHeight));

		m_pointWidth *= 0.8;
		font.setPointSizeF(m_pointWidth);
		m_plot->setAxisFont(QwtPlot::xBottom, font);

		m_zoomCount--;
	}
}

void CLineDialog::OnZoomOutBtnClicked()
{
	QFont font = m_plot->axisFont(QwtPlot::xBottom);
	if(m_zoomCount == 0)
		return;

	factor *= 0.8;
	m_plot->resize(factor*QSize(m_canvasWidth, m_canvasHeight));

	m_pointWidth *= 0.8;
	font.setPointSizeF(m_pointWidth);
	m_plot->setAxisFont(QwtPlot::xBottom, font);

	m_zoomCount--;
}

void CLineDialog::OnZoomInBtnClicked()
{
	QFont font = m_plot->axisFont(QwtPlot::xBottom);
	if (m_zoomCount >= 3)
			return ;

	factor *= 1.25;
	m_plot->resize(factor*QSize(m_canvasWidth, m_canvasHeight));

	m_pointWidth *= 1.25;
	font.setPointSizeF(m_pointWidth);
	m_plot->setAxisFont(QwtPlot::xBottom, font);

	m_zoomCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1.arrow.cpp

void CArrow::slot_ArrowBtnClicked(void)
{

#ifdef _PSX_QT_LINUX_
	QSttSclFileParseDialog *dlg =(QSttSclFileParseDialog *)m_pParentWgt;
	if (NULL != dlg)
	{
		//dlg->m_pIedSearch_LineEdit->clearFocus();
		dlg->m_pIedSearch_LineEdit->setFocusPolicy(Qt::NoFocus);

		dlg->m_pSCLSelect_PushButton->setFocus();
		////dlg->m_pIedSearch_LineEdit->setFocusPolicy(Qt::StrongFocus);

		//5000, 3000
		Delay_MSec(500);

		dlg->m_pIedSearch_LineEdit->setFocusPolicy(Qt::StrongFocus);
	}

#endif

}


CArrow::CArrow(Arrow_Struct *_pData,QWidget* parent)
	:m_errorDis(3),m_pParentWgt(parent),m_pData(_pData)
{
//	QSttSclFileParseDialog *dlg =(QSttSclFileParseDialog *)m_pParentWgt;
	connect(this,SIGNAL(arrow_SigBtnClicked()),this,SLOT(slot_ArrowBtnClicked()));
	//connect(this,SIGNAL(arrow_SigBtnClicked()),dlg,SLOT(dlg->slot_DialogBtnClicked()));

	m_heigh = 14;
	m_width = 8;
	m_pointSizeF = 1.0;

	switch(m_pData->type)
	{
	case Arrow_Struct::ARROW_GSE:
		{
			m_color = qRgb(238,174,14);

			break;
		}
	case Arrow_Struct::ARROW_SMV:
		{
			m_color = qRgb(238,174,14);

			break;
		}
	case Arrow_Struct::ARROW_GOOSE_SUB:
		{
			m_color = qRgb(72, 118, 255);

			break;
		}
	case Arrow_Struct::ARROW_SMV_SUB:
		{
			m_color = qRgb(72, 118, 255);

			break;
		}
	default:
		break;
	}
}

CArrow::~CArrow(void)
{
}


void CArrow::Draw(QPainter *painter)
{
	//获取数据值
	switch(m_pData->type)
	{
	case Arrow_Struct::ARROW_GSE:
		{
			m_startPointF = m_pData->startPointF;
			m_endPointF = m_pData->endPointF;

			break;
		}
	case Arrow_Struct::ARROW_SMV:
		{
			m_startPointF = m_pData->startPointF;
			m_endPointF = m_pData->endPointF;

			break;
		}
	case Arrow_Struct::ARROW_GOOSE_SUB:
		{
			m_startPointF = m_pData->startPointF;
			m_endPointF = m_pData->endPointF;

			break;
		}
	case Arrow_Struct::ARROW_SMV_SUB:
		{
			m_startPointF = m_pData->startPointF;
			m_endPointF = m_pData->endPointF;

			break;
		}
	default:
		break;
	}

	painter->save();

	QPen pen = painter->pen();
	pen.setWidthF(m_pointSizeF);
	pen.setColor(m_color);
	painter->setPen(pen);

	QBrush brush = painter->brush();
	brush.setColor(m_color);
	painter->setBrush(brush);

	//坐标变换
	painter->translate(m_endPointF);

	//顺时针旋转角度(度)
	double angle = 180*qAtan((m_endPointF.x() - m_startPointF.x())/(m_startPointF.y() - m_endPointF.y()))/M_PI;
	if(m_startPointF.x() > m_endPointF.x())
		angle = angle > 0 ? angle-180 : angle;
	else
		angle = angle < 0 ? angle+180 : angle;

	painter->rotate(angle);
	
	static QPointF arrow[3]=
	{
		QPointF(-m_width/2, m_heigh),
		QPointF(m_width/2, m_heigh),
		QPointF(0,0)
	};
	painter->drawConvexPolygon(arrow, 3);

	QPointF disPointF = m_endPointF - m_startPointF;
	double distance = qSqrt(disPointF.x()*disPointF.x() + disPointF.y()*disPointF.y());
	painter->drawLine(QPointF(0,0), QPointF(0,distance));

	painter->restore();
}

inline double qwtSqrTemTem( double x )
{
	return x * x;
}

bool CArrow::Contains(const QPointF &_point)
{
	//求出起点和终点之间的距离
	double distAB = qwtSqrTemTem(m_startPointF.x() - m_endPointF.x()) + qwtSqrTemTem(m_startPointF.y() - m_endPointF.y());

	//求出当前点和起点之间的距离
	double distAP = qwtSqrTemTem(m_startPointF.x() - _point.x()) + qwtSqrTemTem(m_startPointF.y() - _point.y());
	double distBP = qwtSqrTemTem(_point.x() - m_endPointF.x()) + qwtSqrTemTem(_point.y() - m_endPointF.y());

	//A、B、P分别代表起点、终点和当前点
	double dis = qAbs(qSqrt(distAP) + qSqrt(distBP) - qSqrt(distAB));
	if(dis < m_errorDis)
	{
		//获取数据值
		m_color = Qt::green;
		m_pointSizeF = 2;
		return true;
	}
	else
	{
		//获取数据值
		switch(m_pData->type)
		{
		case Arrow_Struct::ARROW_GSE:
			{
				m_color = qRgb(238,174,14);

				break;
			}
		case Arrow_Struct::ARROW_SMV:
			{
				m_color = qRgb(238,174,14);

				break;
			}
		case Arrow_Struct::ARROW_GOOSE_SUB:
			{
				m_color = qRgb(72, 118, 255);

				break;
			}
		case Arrow_Struct::ARROW_SMV_SUB:
			{
				m_color = qRgb(72, 118, 255);

				break;
			}
		default:
			break;
		}
		m_pointSizeF = 1.0;
		return false;
	}
}

bool CArrow::LeftButtonClicked(const QPointF &_point)
{
	//求出起点和终点之间的距离
	double distAB = qwtSqrTemTem(m_startPointF.x() - m_endPointF.x()) + qwtSqrTemTem(m_startPointF.y() - m_endPointF.y());

	//求出当前点和起点之间的距离
	double distAP = qwtSqrTemTem(m_startPointF.x() - _point.x()) + qwtSqrTemTem(m_startPointF.y() - _point.y());
	double distBP = qwtSqrTemTem(_point.x() - m_endPointF.x()) + qwtSqrTemTem(_point.y() - m_endPointF.y());

	//A、B、P分别代表起点、终点和当前点
	double dis = qAbs(qSqrt(distAP) + qSqrt(distBP) - qSqrt(distAB));
	if(dis < m_errorDis)
	{
		CLineDialog dlg(m_pData);
		dlg.InitScrollData();
		dlg.raise();
		int res=dlg.exec();
		int testrest=res;

		emit arrow_SigBtnClicked();


		return true;
	}

	return false;
}

void CArrow::Recover()
{
	switch(m_pData->type)
	{
	case Arrow_Struct::ARROW_GSE:
		{
			m_color = qRgb(238,174,14);

			break;
		}
	case Arrow_Struct::ARROW_SMV:
		{
			m_color = qRgb(238,174,14);

			break;
		}
	case Arrow_Struct::ARROW_GOOSE_SUB:
		{
			m_color = qRgb(72, 118, 255);

			break;
		}
	case Arrow_Struct::ARROW_SMV_SUB:
		{
			m_color = qRgb(72, 118, 255);

			break;
		}
	default:
		break;
	}
	m_pointSizeF = 1.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//3.small_rect.cpp

//#include "SmallRect.h"

CSmallRect::CSmallRect(SmallRect_Struct *_pData, QwtPlot *_plot)
	:m_plot(_plot),m_pData(_pData)
{
	m_width = 124;
	m_margin = 60;

	m_textMargin = 10;
	m_textWidth = m_width - 2*m_textMargin;

	m_blockWidth = 96;
	m_blockHeight = 25;
	m_blockMargin = 10;

	_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);

	m_text = iedInfo->name + "\n" + iedInfo->desc;
}

CSmallRect::~CSmallRect(void)
{
}

//获取小矩形的高度
double CSmallRect::Heigh()
{
	//文本的高度，依据默认字体大小计算
	QFont font = m_plot->axisFont(QwtPlot::yLeft);
	QwtText qwtText("",QwtText::RichText);
	qwtText.setText(m_text);
	qwtText.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);
	qwtText.setFont(font);
	m_textHeight = qwtText.heightForWidth(m_textWidth);
	double heigh =m_textHeight + 2*m_textMargin;

	m_blockTotalHeight = m_pData->blockList.size()*(m_blockHeight + m_blockMargin) + m_blockMargin;
	
	return heigh > m_blockTotalHeight ? heigh : m_blockTotalHeight;
}

	//绘制小矩形
void CSmallRect::Draw(QPainter *painter,double _yValue, 
		const QwtScaleMap &xMap, const QwtScaleMap &yMap)
{
	if (m_pData->pos == SmallRect_Struct::POSITION_LEFT)
	{
		DrawLeft(painter, _yValue, xMap, yMap);
	}
	else
	{
		DrawRight(painter, _yValue, xMap, yMap);
	}
}

bool CSmallRect::Contains(const QPoint &pos)
{
	if (m_blockRectF.contains(pos))
	{
		QCursor cursor;
		cursor.setShape(Qt::OpenHandCursor);
		m_plot->canvas()->setCursor(cursor);

		return true;
	}
	else
	{
		return false;
	}
}

int CSmallRect::LeftButtonClicked(const QPoint &pos)
{
	if (m_blockRectF.contains(pos))
	{
		return m_pData->ied_index;
	}
	else
	{
		return -1;
	}
}

void CSmallRect::DrawLeft(QPainter *painter, double _yValue, const QwtScaleMap &xMap, 
						  const QwtScaleMap &yMap)
{
	QPointF topLeftPointF,bottomRightPointF;	//坐标转换以后的点
	double xValue,yValue;	//坐标转换之前的值
	double height = Heigh(); //矩形框的高度

	double coordWidth = xMap.sDist();
	//double coordHeight = yMap.sDist();

	QBrush brush = painter->brush();
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(qRgb(229,242,196));
	painter->setBrush(brush);

	QFont font = m_plot->axisFont(QwtPlot::xBottom);

	//绘制控制块矩形
	xValue = m_margin + m_width;
	yValue = _yValue + (height - m_blockTotalHeight)/2 + m_blockMargin;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_blockWidth;
	yValue += m_blockHeight;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	brush.setStyle(Qt::SolidPattern);
	brush.setColor(qRgb(158,221,247));
	painter->setBrush(brush);

	_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);
	foreach(Block_Struct blockStru, m_pData->blockList)
	{
		//QString strBlock = CString("无");
		QString strBlock = /*QObject::tr("无")*/g_sLangTxt_None;
		switch(blockStru.type)
		{
		case Block_Struct::BLOCK_GSE:
			{
				_GSE_INFO smvInfo = iedInfo->GSEList.at(blockStru.block_index);

				if(smvInfo.APPID.toInt(0,16)==0)
				{
					strBlock = smvInfo.APPID;
				}
				else
				{
					strBlock = QString("%1").arg(smvInfo.APPID.toInt(0,16),4,16,QChar('0'));
					strBlock = "GOOSE 0x" + strBlock.toUpper(); 
				}

				//更新箭头的坐标
				foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
				{
					arrowStru->startPointF.setX(xMap.transform(xValue));
					arrowStru->startPointF.setY(yMap.transform(yValue - m_blockHeight/2));

					arrowStru->endPointF.setY(arrowStru->startPointF.y());
					arrowStru->endPointF.setX(xMap.transform(coordWidth/2 - g_mainRect_width/2));
				}

				brush.setStyle(Qt::SolidPattern);
				brush.setColor(qRgb(158,221,247));
				painter->setBrush(brush);

				QPen pen = painter->pen();
				pen.setStyle(Qt::SolidLine);
				painter->setPen(pen);

				break;
			}
		case Block_Struct::BLOCK_SMV:
			{
				_SMV_INFO smvInfo = iedInfo->SMVList.at(blockStru.block_index);

				if(smvInfo.APPID.toInt(0,16)==0)
				{
					strBlock = smvInfo.APPID;
				}
				else
				{
					strBlock = QString("%1").arg(smvInfo.APPID.toInt(0,16),4,16,QChar('0'));
					strBlock = "SMV 0x" + strBlock.toUpper(); 
				}

				//更新箭头的坐标
				foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
				{
					arrowStru->startPointF.setX(xMap.transform(xValue));
					arrowStru->startPointF.setY(yMap.transform(yValue - m_blockHeight/2));

					arrowStru->endPointF.setY(arrowStru->startPointF.y());
					arrowStru->endPointF.setX(xMap.transform(coordWidth/2 - g_mainRect_width/2));
				}

				brush.setStyle(Qt::SolidPattern);
				brush.setColor(qRgb(250,167,243));
				painter->setBrush(brush);

				QPen pen = painter->pen();
				pen.setStyle(Qt::SolidLine);
				painter->setPen(pen);

				break;
			}
		case Block_Struct::BLOCK_SUB:
			{
				//strBlock = CString("接收");
				strBlock = /*QObject::tr("接收")*/g_sLangTxt_Native_receive;


				//更新箭头的坐标
				foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
				{
					arrowStru->endPointF.setX(xMap.transform(xValue));
					arrowStru->endPointF.setY(yMap.transform(yValue - m_blockHeight/2));
				}

				brush.setStyle(Qt::NoBrush);
				//brush.setColor(qRgb(158,221,247));
				painter->setBrush(brush);

				QPen pen = painter->pen();
				pen.setStyle(Qt::DashLine);
				painter->setPen(pen);

				break;
			}
		default:
			break;
		}

		//绘制矩形和文字
		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
		QwtText text(strBlock, QwtText::AutoText);
		text.setFont(font);
		text.setRenderFlags(Qt::AlignCenter);
		text.draw(painter, QRectF(topLeftPointF, bottomRightPointF));

		//更新下一个控制块的坐标
		xValue -= m_blockWidth;
		yValue += m_blockMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));

		xValue += m_blockWidth;
		yValue += m_blockHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));
	}

	//绘制主矩形框
	xValue = m_margin;
	yValue = _yValue;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue = m_margin + m_width;
	yValue = _yValue + height;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

// 	QBrush brush = painter->brush();
 	brush.setStyle(Qt::SolidPattern);
	brush.setColor(qRgb(229,242,196));
	painter->setBrush(brush);

	QPen pen = painter->pen();
	pen.setStyle(Qt::SolidLine);
	painter->setPen(pen);

	m_blockRectF.setTopLeft(topLeftPointF);
	m_blockRectF.setBottomRight(bottomRightPointF);
	painter->drawRect(m_blockRectF);

	//文字矩形框
	xValue = m_margin +m_textMargin;
	yValue = _yValue + m_textMargin;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_textWidth;
	yValue += height - 2*m_textMargin;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	QwtText qwtText("",QwtText::RichText);
	qwtText.setText(m_text);
	qwtText.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);
	qwtText.setFont(font);
	qwtText.draw(painter, QRectF(topLeftPointF, bottomRightPointF));
}

void CSmallRect::DrawRight(QPainter *painter, double _yValue, const QwtScaleMap &xMap, 
						   const QwtScaleMap &yMap)
{
	QPointF topLeftPointF,bottomRightPointF;	//坐标转换以后的点
	double xValue,yValue;	//坐标转换之前的值
	double height = Heigh(); //矩形框的高度

	double coordWidth = xMap.sDist();
	//double coordHeight = yMap.sDist();

	QFont font = m_plot->axisFont(QwtPlot::xBottom);
	QBrush brush = painter->brush();

	//绘制控制块矩形
	xValue = coordWidth - m_margin - m_width - m_blockWidth;
	yValue = _yValue + (height - m_blockTotalHeight)/2 + m_blockMargin;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_blockWidth;
	yValue += m_blockHeight;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	_IED_INFO *iedInfo = g_oTotalIEDList.at(m_pData->ied_index);
	foreach(Block_Struct blockStru, m_pData->blockList)
	{
		QString strBlock = CString("无");
		switch(blockStru.type)
		{
		case Block_Struct::BLOCK_GSE:
			{
				_GSE_INFO smvInfo = iedInfo->GSEList.at(blockStru.block_index);

				if(smvInfo.APPID.toInt(0,16)==0)
				{
					strBlock = smvInfo.APPID;
				}
				else
				{
					strBlock = QString("%1").arg(smvInfo.APPID.toInt(0,16),4,16,QChar('0'));
					strBlock = "GOOSE 0x" + strBlock.toUpper(); 
				}

				//更新箭头的坐标
				foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
				{
					arrowStru->startPointF.setX(xMap.transform(xValue - m_blockWidth));
					arrowStru->startPointF.setY(yMap.transform(yValue - m_blockHeight/2));

					arrowStru->endPointF.setY(arrowStru->startPointF.y());
					arrowStru->endPointF.setX(xMap.transform(coordWidth/2 + g_mainRect_width/2));
				}

				brush.setStyle(Qt::SolidPattern);
				brush.setColor(qRgb(158,221,247));
				painter->setBrush(brush);

				QPen pen = painter->pen();
				pen.setStyle(Qt::SolidLine);
				painter->setPen(pen);

				break;
			}
		case Block_Struct::BLOCK_SMV:
			{
				_SMV_INFO smvInfo = iedInfo->SMVList.at(blockStru.block_index);

				if(smvInfo.APPID.toInt(0,16)==0)
				{
					strBlock = smvInfo.APPID;
				}
				else
				{
					strBlock = QString("%1").arg(smvInfo.APPID.toInt(0,16),4,16,QChar('0'));
					strBlock = "SMV 0x" + strBlock.toUpper(); 
				}

				//更新箭头的坐标
				foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
				{
					arrowStru->startPointF.setX(xMap.transform(xValue - m_blockWidth));
					arrowStru->startPointF.setY(yMap.transform(yValue - m_blockHeight/2));

					arrowStru->endPointF.setY(arrowStru->startPointF.y());
					arrowStru->endPointF.setX(xMap.transform(coordWidth/2 + g_mainRect_width/2));
				}

				brush.setStyle(Qt::SolidPattern);
				brush.setColor(qRgb(250,167,243));
				painter->setBrush(brush);

				QPen pen = painter->pen();
				pen.setStyle(Qt::SolidLine);
				painter->setPen(pen);

				break;
			}
		case Block_Struct::BLOCK_SUB:
			{
				//strBlock = CString("接收");
				strBlock = /*QObject::tr("接收")*/g_sLangTxt_Native_receive;


				//更新箭头的坐标
				foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
				{
					arrowStru->endPointF.setX(xMap.transform(xValue - m_blockWidth));
					arrowStru->endPointF.setY(yMap.transform(yValue - m_blockHeight/2));
				}

				brush.setStyle(Qt::NoBrush);
				//brush.setColor(qRgb(158,221,247));
				painter->setBrush(brush);

				QPen pen = painter->pen();
				pen.setStyle(Qt::DashLine);
				painter->setPen(pen);

				break;
			}
		default:
			break;
		}

		//绘制矩形和文字
		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
		QwtText text(strBlock, QwtText::AutoText);
		text.setFont(font);
		text.setRenderFlags(Qt::AlignCenter);
		text.draw(painter, QRectF(topLeftPointF, bottomRightPointF));

		//更新下一个控制块的坐标
		xValue -= m_blockWidth;
		yValue += m_blockMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));

		xValue += m_blockWidth;
		yValue += m_blockHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));
	}

	//绘制主矩形框
	xValue = coordWidth - m_margin - m_width;
	yValue = _yValue;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_width;
	yValue = _yValue + height;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	brush.setStyle(Qt::SolidPattern);
	brush.setColor(qRgb(229,242,196));
	painter->setBrush(brush);

	QPen pen = painter->pen();
	pen.setStyle(Qt::SolidLine);
	painter->setPen(pen);

	m_blockRectF.setTopLeft(topLeftPointF);
	m_blockRectF.setBottomRight(bottomRightPointF);
	painter->drawRect(m_blockRectF);

	//文字矩形框
	xValue = coordWidth - m_margin - m_width +m_textMargin;
	yValue = _yValue + m_textMargin;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_textWidth;
	yValue += height - 2*m_textMargin;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	QwtText qwtText("",QwtText::RichText);
	qwtText.setText(m_text);
	qwtText.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);
	qwtText.setFont(font);
	qwtText.draw(painter, QRectF(topLeftPointF, bottomRightPointF));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

//4.RectMARer.cpp


CRectMark::CRectMark(Rect_Struct *_pData,QWidget* parent)
	: QwtPlotItem(),m_pParentWgt(parent),m_data(_pData)
{
	m_width = 124;
	m_margin = 10;
	m_rectMargin = 10;

	m_blockMargin = 10;
	m_blockHeight = 25;
	m_blockWidth = m_width - 30;

	m_textMargin = 10;
	m_textWidth = m_width - 2*m_textMargin;

	setZ( 1000 );
	setRenderHint( QwtPlotItem::RenderAntialiased, true );
}

CRectMark::~CRectMark()
{

}

//void CRectMark::slot_rectmarkBtnClicked()
//{
//
//
//}

double CRectMark::InitData()
{
	if(m_data->ied_index == -1)
		return 0;

	Clear();

	_IED_INFO *iedInfo = g_oTotalIEDList.at(m_data->ied_index);
	m_text = iedInfo->name + "\n" + iedInfo->desc;

	for(int iRect = 0; iRect<m_data->smallBlockList.size(); iRect++)
	{
		SmallRect_Struct *pRectStru = &m_data->smallBlockList[iRect];
		if (pRectStru->pos == SmallRect_Struct::POSITION_LEFT)
		{
			CSmallRect *rect = new CSmallRect(pRectStru, plot());
			m_leftRectList.append(rect);
		}
		else
		{
			CSmallRect *rect = new CSmallRect(pRectStru, plot());
			m_rightRectList.append(rect);
		}
	}

	//连线
	foreach(Arrow_Struct *arrowStru, m_data->arrowList)
	{
		CArrow *arrow = new CArrow(arrowStru,m_pParentWgt);

		m_arrowList.append(arrow);
	}

	//计算左边和右边矩形的总高度，判断是否超出最大纵坐标
	m_leftTotalHeight = 0;
	foreach(CSmallRect *rect, m_leftRectList)
	{
		m_leftTotalHeight += rect->Heigh();
		m_leftTotalHeight += m_rectMargin;
	}
	m_leftTotalHeight -= m_rectMargin;

	m_rightTotalHeight = 0;
	foreach(CSmallRect *rect, m_rightRectList)
	{
		m_rightTotalHeight += rect->Heigh();
		m_rightTotalHeight += m_rectMargin;
	}
	m_rightTotalHeight -= m_rectMargin;

	return m_leftTotalHeight > m_rightTotalHeight ? m_leftTotalHeight : m_rightTotalHeight;
}

void CRectMark::Clear()
{
	foreach(CSmallRect *rect, m_leftRectList)
	{
		delete rect;
	}
	m_leftRectList.clear();
	foreach(CSmallRect *rect, m_rightRectList)
	{
		delete rect;
	}
	m_rightRectList.clear();
	foreach(CArrow *arrow, m_arrowList)
	{
		delete arrow;
	}
	m_arrowList.clear();

}

void CRectMark::SetWidth(int _width)
{
	m_width = _width;
}

void CRectMark::SetMargin(int _margin)
{
	m_margin = _margin;
}

void CRectMark::SetBlockMargin(int _margin /* = 10 */)
{
	m_blockMargin = _margin;
}

int CRectMark::rtti() const
{
	return QwtPlotItem::Rtti_PlotUserItem;
}

void CRectMark::draw( QPainter *painter,
						const QwtScaleMap &xMap, const QwtScaleMap &yMap,
						const QRectF & ) const
{
	double xValue,yValue;
	QPointF topLeftPointF, bottomRightPointF;

	double coordWidth = xMap.sDist();
	double coordHeight = yMap.sDist();
	
	//主矩形
	xValue = coordWidth/2 - m_width/2;
	yValue = m_margin;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));
	
	xValue += m_width;
	yValue += coordHeight - m_margin;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));
	
	QBrush brush = painter->brush();
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(qRgb(196,234,196));
	painter->setBrush(brush);
	painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));

	//控制块矩形框
	double minHeight = MinHeight();
	xValue = coordWidth/2 - m_width/2 + (m_width - m_blockWidth)/2;
	yValue = coordHeight - m_margin - m_textMargin - 
		(coordHeight - 2*m_margin - 2*m_textMargin - minHeight)/2 - m_blockHeight;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_blockWidth;
	yValue += m_blockHeight;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	if(m_data->ied_index == -1)
		return ;

	_IED_INFO *iedInfo = g_oTotalIEDList.at(m_data->ied_index);
	foreach(Block_Struct blockStru, m_data->blockList)
	{
		QString strBlock;
		switch(blockStru.type)
		{
		case Block_Struct::BLOCK_GSE:
			{
				_GSE_INFO gseInfo = iedInfo->GSEList.at(blockStru.block_index);
				if(gseInfo.APPID.toInt(0,16)==0)
				{
					strBlock = gseInfo.APPID;
				}
				else
				{
					strBlock = QString("%1").arg(gseInfo.APPID.toInt(0,16),4,16,QChar('0'));
					strBlock = "GOOSE 0x" + strBlock.toUpper(); 
				}

				brush.setColor(qRgb(158,221,247));
				painter->setBrush(brush);

				break;
			}
		case Block_Struct::BLOCK_SMV:
			{
				_SMV_INFO gseInfo = iedInfo->SMVList.at(blockStru.block_index);
				if(gseInfo.APPID.toInt(0,16)==0)
				{
					strBlock = gseInfo.APPID;
				}
				else
				{
					strBlock = QString("%1").arg(gseInfo.APPID.toInt(0,16),4,16,QChar('0'));
					strBlock = "SMV 0x" + strBlock.toUpper(); 
				}

				brush.setColor(qRgb(250,167,243));
				painter->setBrush(brush);

				break;
			}
		default:
			break;
		}

		//更新箭头坐标
		foreach(Arrow_Struct *arrowStru, blockStru.arrowList)
		{
			if (arrowStru->pos == Arrow_Struct::POSITION_LEFT)
			{
				arrowStru->startPointF.setX(xMap.transform(xValue - m_blockWidth));
				arrowStru->startPointF.setY(yMap.transform(yValue - m_blockHeight/2));
			}
			else
			{
				arrowStru->startPointF.setX(xMap.transform(xValue));
				arrowStru->startPointF.setY(yMap.transform(yValue - m_blockHeight/2));
			}
		}

		painter->drawRect(QRectF(topLeftPointF, bottomRightPointF));
		QwtText text(strBlock, QwtText::RichText);
		QFont font = plot()->axisFont(QwtPlot::xBottom);
		text.setFont(font);
		text.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);
		text.draw(painter, QRectF(topLeftPointF, bottomRightPointF));

		//移动到上一个控制块
		xValue -= m_blockWidth;
		yValue = yValue - 2*m_blockHeight - m_blockMargin;
		topLeftPointF.setX(xMap.transform(xValue));
		topLeftPointF.setY(yMap.transform(yValue));

		xValue += m_blockWidth;
		yValue += m_blockHeight;
		bottomRightPointF.setX(xMap.transform(xValue));
		bottomRightPointF.setY(yMap.transform(yValue));
	}

	//绘制文字
	xValue = coordWidth/2 - m_width/2 + m_textMargin;
	yValue = m_margin + m_textMargin + (coordHeight - 2*m_margin - 2*m_textMargin - minHeight)/2;
	topLeftPointF.setX(xMap.transform(xValue));
	topLeftPointF.setY(yMap.transform(yValue));

	xValue += m_textWidth;
	yValue += coordHeight;
	bottomRightPointF.setX(xMap.transform(xValue));
	bottomRightPointF.setY(yMap.transform(yValue));

	QwtText text("",QwtText::RichText);
	text.setText(m_text);
	QFont font = plot()->axisFont(QwtPlot::xBottom);
	text.setFont(font);
	text.setRenderFlags(Qt::AlignHCenter|Qt::AlignTop|Qt::TextWordWrap);
	text.draw(painter, QRectF(topLeftPointF, bottomRightPointF));

	//左边的小矩形
	yValue = coordHeight/2 - m_leftTotalHeight/2;
	foreach(CSmallRect *rect, m_leftRectList)
	{
		rect->Draw(painter, yValue, xMap, yMap);
		yValue += rect->Heigh() + m_blockMargin;
	}

	//右边的小矩形
	yValue = coordHeight/2 - m_rightTotalHeight/2;
	foreach(CSmallRect *rect, m_rightRectList)
	{
		rect->Draw(painter, yValue, xMap, yMap);
		yValue += rect->Heigh() + m_blockMargin;
	}

	//箭头
	foreach(CArrow *arrow, m_arrowList)
	{
		arrow->Draw(painter);
	}
}

void CRectMark::Contains(const QPoint &pos)
{
	QCursor cursor;
	cursor.setShape(Qt::ArrowCursor);
	plot()->canvas()->setCursor(cursor);

	bool flag = true;

	foreach(CSmallRect *rect, m_leftRectList)
	{
		if(rect->Contains(pos))
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		foreach(CSmallRect *rect, m_rightRectList)
		{
			if(rect->Contains(pos))
			{
				flag = false;
				break;
			}
		}
	}
	if (flag)
	{
		foreach (CArrow *arrow, m_arrowList)
		{
			arrow->Recover();
		}

		foreach(CArrow *arrow, m_arrowList)
		{
			if(arrow->Contains(pos))
			{
				QCursor cursor;
				cursor.setShape(Qt::SplitVCursor);
				plot()->canvas()->setCursor(cursor);
				break;
			}
		}
	}
	
	plot()->replot();
}

int CRectMark::LeftButtonClicked(const QPoint &pos)
{
	int ret = -1;

	foreach(CSmallRect *rect, m_leftRectList)
	{
		ret = rect->LeftButtonClicked(pos);
		if(ret != -1)
		{
			return ret;
		}
	}

	foreach(CSmallRect *rect, m_rightRectList)
	{
		ret = rect->LeftButtonClicked(pos);
		if(ret != -1)
		{
			return ret;
		}
	}

	foreach (CArrow *arrow, m_arrowList)
	{
		if(arrow->LeftButtonClicked(pos))
		{
			break;
		}
	}

	return ret;
}

double CRectMark::MinHeight() const
{
	double heigth;

	//获取文字的高度
	QFont font = plot()->axisFont(QwtPlot::yLeft);
	QwtText qwtText(m_text, QwtText::RichText);
	qwtText.setFont(font);
	qwtText.setRenderFlags(Qt::AlignCenter|Qt::TextWordWrap);
	heigth = qwtText.heightForWidth(m_textWidth);

	//获取控制块的高度
	heigth += (m_blockMargin + m_blockHeight)*m_data->blockList.size();
	heigth += m_blockMargin;

	return heigth;
}

void Global_SclCtrlGsOut_To_IedInfor(CSclCtrlGsOut* pDvmData,_IED_INFO* refiedInfo)
{
	_GSE_INFO gsInforGsOut;
	_GSE_INFO* gseInfo=&gsInforGsOut;
	gseInfo->apName=pDvmData->apName;
	gseInfo->apDesc="";
	gseInfo->cbName=pDvmData->gocbref;
	gseInfo->ldInst=pDvmData->ldName;
	gseInfo->MAC_Adress=pDvmData->m_strMac;
	gseInfo->VLAN_ID=QString("%1").arg(pDvmData->m_dwVLandID); 
	gseInfo->VLAN_PRIORITY=QString("%1").arg(pDvmData->m_dwVLandPriority);

	//gseInfo->APPID=QString("%1").arg(pDvmData->m_dwAppID);
	gseInfo->APPID.Format(_T("%04X"),pDvmData->m_dwAppID);

	gseInfo->MinTime=pDvmData->scl_gse_MinTime;
	gseInfo->MaxTime=pDvmData->scl_gse_MaxTime;
	gseInfo->datSet=pDvmData->m_strDataSet;
	//gseInfo->confRev=pDvmData->m_strDataSet;
	gseInfo->recNum=pDvmData->m_nChnCount;		
	gseInfo->DataSetDesc=pDvmData->m_strDataSetDesc;

	gseInfo->appID=pDvmData->m_strGooseId;

	refiedInfo->GSEList.push_back(gsInforGsOut);

	//return gseInfo;
}

void Global_SclCtrlSmvOut_To_IedInfor(CSclCtrlSmvOut* pDvmData,_IED_INFO* refiedInfo)
{
	_SMV_INFO smvInforSmvOut;
	_SMV_INFO* smvInfo=&smvInforSmvOut;
	smvInfo->apName=pDvmData->apName;
	smvInfo->apDesc="";
	smvInfo->cbName=pDvmData->m_strName;
	smvInfo->ldInst=pDvmData->ldName;
	smvInfo->MAC_Adress=pDvmData->m_strMac;
	smvInfo->VLAN_ID=QString("%1").arg(pDvmData->scl_smv_VLANID);  
	smvInfo->VLAN_PRIORITY=QString("%1").arg(pDvmData->scl_smv_VLANPRI); 

	//smvInfo->APPID=QString("%1").arg(pDvmData->m_dwAppID);
	smvInfo->APPID.Format(_T("%04X"),pDvmData->m_dwAppID);

	smvInfo->smpRate=pDvmData->scl_svcb_smpRate;
	smvInfo->nofASDU=pDvmData->scl_svcb_nofASDU;
	smvInfo->datSet=pDvmData->m_strDataSet;
	smvInfo->confRev=QString::number(pDvmData->scl_svcb_confRev);
	smvInfo->SmvID=pDvmData->m_strID;
	smvInfo->recNum=pDvmData->m_nChnCount;		
	smvInfo->DataSetDesc=pDvmData->m_strDataSetDesc;

	refiedInfo->SMVList.push_back(smvInforSmvOut);
}

void Global_SclChGsIn_To_IedInfor(CSclChGsIn* pChGsIn,_IED_INFO* refiedInfo,CString strExtName,CString appidStr)
{
	_SUB_REC_INFO subRecInforGsIn;
	_SUB_REC_INFO* sub=&subRecInforGsIn;
	sub->ref=pChGsIn->m_strName;
	sub->desc=pChGsIn->inDODesc;
	//外部虚端子信息
	sub->sub_IED_name=strExtName;
	sub->sub_ldInst="";
	sub->sub_ref=pChGsIn->fcda_name;

	sub->index_IED=Global_FindSclIedIndex(strExtName);

	sub->index_GSE_SMV=0;
	//outIndex从0开始，需要加一
	sub->index_Rec=pChGsIn->outIndex+1;
	int test=CString_To_long(appidStr);
	CString strTmpText;
	strTmpText.Format(_T("%04X"),test);
	sub->ExtMineOutAppid = strTmpText;

	sub->ExtCHIndex=pChGsIn->inIndex;
	//outIndex从0开始，需要加一
	sub->ExtCHOutIndex=pChGsIn->outIndex+1;
	//-----------------

	refiedInfo->GOSubList.push_back(subRecInforGsIn);
}

int Global_FindSclIedIndex(CString search)
{
	int totalSize=g_oGloalIEDNameList.size();
	for(int idx=0;idx<totalSize;idx++)
	{
		CString idIfoName=g_oGloalIEDNameList.at(idx);
		if(idIfoName==search)
		{
			return idx;
		}
	}

	return -1;
}

void Global_SclChSmvIn_To_IedInfor(CSclChSmvIn* pChSmvIn,_IED_INFO* refiedInfo,CString strExtName,CString strLdDesc)
{
	_SUB_REC_INFO subRecInforSmvIn;
	_SUB_REC_INFO* sub=&subRecInforSmvIn;
	sub->ref=pChSmvIn->m_strName;
	sub->desc=pChSmvIn->inDODesc;
	//外部虚端子信息
	sub->sub_IED_name=strExtName;
	sub->sub_ldInst=strLdDesc;
	sub->sub_ref=pChSmvIn->fcda_name;

	sub->index_IED=Global_FindSclIedIndex(strExtName);

	sub->index_GSE_SMV=0;
	//outIndex从0开始，需要加一
	sub->index_Rec=pChSmvIn->outIndex+1;
	//-----------------
	sub->ExtCHIndex=pChSmvIn->inIndex;
	//outIndex从0开始，需要加一
	sub->ExtCHOutIndex=pChSmvIn->outIndex+1;
	//----------------
	refiedInfo->SVSubList.push_back(subRecInforSmvIn);
}



void Global_SclIed_To_IedInfor(CSclIed *pSclIed,_IED_INFO* refiedInfo)
{
	CSclCtrlsGsOut* pGsOutList=pSclIed->GetGsOuts();
	POS posGsOut = pGsOutList->GetHeadPosition();
	long nIndexGsOut = 0;
	_PUB_REC_INFO oPubRecInfo;
	_GSE_INFO *pGseInfo = NULL;

	while(posGsOut)
	{
		CSclCtrlGsOut* pDvmData = (CSclCtrlGsOut*)pGsOutList->GetNext(posGsOut);
		CString strNminner = pDvmData->m_strName;	
		CString strIDinner = pDvmData->m_strID;			
		nIndexGsOut++;
		Global_SclCtrlGsOut_To_IedInfor(pDvmData,refiedInfo);
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("myGsOutbegin-%s: %s"), strNminner.GetString(), strIDinner.GetString());
		POS posInner = pDvmData->GetHeadPosition();
		int totalChsTest=0;
		CSclChGsOut* pChGsOut=NULL;

		while(posInner)
		{
			pChGsOut=(CSclChGsOut*)pDvmData->GetNext(posInner);
			oPubRecInfo.ref=pChGsOut->m_strID;
			oPubRecInfo.desc=pChGsOut->m_strName;
			pGseInfo =  (_GSE_INFO*)&(refiedInfo->GSEList.at(nIndexGsOut-1));
			pGseInfo->pubList.push_back(oPubRecInfo);
			totalChsTest++;
		}
	}
	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("myend-GSout:%d"),nIndexGsOut);
	/////////////////////////////////////////////////////////////////////
	CSclCtrlsSmvOut* pSmvOutList=pSclIed->GetSmvOuts();
	POS posSmvOut = pSmvOutList->GetHeadPosition();
	long nIndexSmvOut = 0;
	while(posSmvOut)
	{
		CSclCtrlSmvOut* pDvmData=(CSclCtrlSmvOut*)pSmvOutList->GetNext(posSmvOut);
		CString strNminner = pDvmData->m_strName;	
		CString strIDinner = pDvmData->m_strID;	
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("mySmvOutbegin-%s: %s"), strNminner.GetString(), strIDinner.GetString());	
		nIndexSmvOut++;
		Global_SclCtrlSmvOut_To_IedInfor(pDvmData,refiedInfo);
		POS posInner = pDvmData->GetHeadPosition();
		int totalChsTest=0;
		CSclChSmvOut* pChSmvOut=NULL;
		_SMV_INFO *pSmvInfo = NULL;

		while(posInner)
		{
			pChSmvOut=(CSclChSmvOut*)pDvmData->GetNext(posInner);	
			oPubRecInfo.ref=pChSmvOut->m_strID;
			oPubRecInfo.desc=pChSmvOut->m_strName;
			pSmvInfo =  (_SMV_INFO*)&(refiedInfo->SMVList.at(nIndexSmvOut-1));
			pSmvInfo->pubList.push_back(oPubRecInfo);
			totalChsTest++;
		}
	}
	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("myend-SmvOut:%d"),nIndexSmvOut);
	//////////////////////////////////////////////////////////
	CSclCtrlsGsIn* pGsInList=pSclIed->GetGsIns();
	POS posGsIn = pGsInList->GetHeadPosition();
	long nIndexGsIn = 0;
	while(posGsIn)
	{
		CSclCtrlGsIn* pDvmData=(CSclCtrlGsIn*)pGsInList->GetNext(posGsIn);
		CString strNminner = pDvmData->m_strName;	
		CString strIDinner = pDvmData->m_strID;	
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("myGsInbegin-%s: %s"), strNminner.GetString(), strIDinner.GetString());
		nIndexGsIn++;
		CString strLdDesc = pDvmData->m_strLDdesc;	
		CString strExtName = pDvmData->m_strIedID;
		//-----------
		CString APPIDStr = QString::number(pDvmData->m_dwAppID);
		//-----------------appidStr
		POS posInner = pDvmData->GetHeadPosition();
		int totalChsTest=0;
		CSclChGsIn* pChGsIn=NULL;

		while(posInner)
		{
			pChGsIn=(CSclChGsIn*)pDvmData->GetNext(posInner);
			Global_SclChGsIn_To_IedInfor(pChGsIn,refiedInfo,strExtName, APPIDStr);
			totalChsTest++;
		}
	}
	//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("myend-GsIn:%d"),nIndexGsIn);
	//////////////////////////////////////////////////////////////////////////
	CSclCtrlsSmvIn* pSmvInList=pSclIed->GetSmvIns();
	POS posSmvIn = pSmvInList->GetHeadPosition();
	long nIndexSmvIn = 0;

	while(posSmvIn)
	{
		CSclCtrlSmvIn* pDvmData=(CSclCtrlSmvIn*)pGsInList->GetNext(posSmvIn);
		CString strNminner = pDvmData->m_strName;	
		CString strIDinner = pDvmData->m_strID;	
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("mySmvInbegin-%s: %s"), strNminner.GetString(), strIDinner.GetString());
		nIndexSmvIn++;
		CString strLdDesc = pDvmData->m_strLDdesc;	
		CString strExtName = pDvmData->iedExtName;	

		POS posInner = pDvmData->GetHeadPosition();
		int totalChsTest=0;
		CSclChSmvIn* pChSmvIn=NULL;
		while(posInner){
			pChSmvIn=(CSclChSmvIn*)pDvmData->GetNext(posInner);
			CString testname=pChSmvIn->m_strName;
			CString testidid=pChSmvIn->m_strID;
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("SmvIn: %s , %s"), testname.GetString(), testidid.GetString());
			Global_SclChSmvIn_To_IedInfor(pChSmvIn,refiedInfo,strExtName,strLdDesc);
			totalChsTest++;
		}
	}
}