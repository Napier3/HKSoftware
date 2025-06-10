#include "DiagramWidget.h"
#include <QPainter>
#include <QHeaderView>
#include <QMutex>
#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"
#include "../../Module/XLanguage/XLanguageResource.h"

//#include "../../SttTestCntrFrameBase.h"

#define PI 3.1415926
#include <qmath.h>
#define ZJOFFSET 15;
int Diagram::m_l =10;
float Diagram::m_a=0.9;
QMutex g_diagramMutex;

Diagram::Diagram(QWidget *parent) :QWidget(parent)
{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//��ֹ������ͼ���ػ�,������˸
	setAttribute(Qt::WA_OpaquePaintEvent);
	
	m_ZJoffset = 20;
	bIsDrawSector = false;
	fstartAngle = 0;
	fendAngle = 0;
	fMTAangle = 0;
	fSrarchAngle = 0;
	fstartAngle_arc = 0;
	fendAngle_arc = 0;
	bStartSearch = 0;
	m_bhasRadio = false;
	m_UnitDispMode = 0;
	m_bUse = false;

	m_VectorType = 0;
	fCurrSearchValue = 0;
	m_nRowHeight = 14;

	QRect rect  = this->rect();

#ifdef _PSX_QT_WINDOWS_ 
	setSize(rect.width(),rect.height() / 2);
#else
	setSize(rect.width() * 3/ 5,rect.height());
#endif

	m_fUMax = 2.0;
	m_fIMax = 0.5;
	m_TestMenu = NULL;
	m_UZoomOutAction = NULL;
	m_IZoomOutAction = NULL;
	m_UZoomInAction = NULL;
	m_IZoomInAction = NULL;

	m_TestMenu = new QMenu(this);
	m_UZoomOutAction = new QAction(tr("��ѹ�Ŵ�"),this);
	m_IZoomOutAction = new QAction(tr("�����Ŵ�"),this);
	m_UZoomInAction = new QAction(tr("��ѹ��С"),this);
	m_IZoomInAction = new QAction(tr("������С"),this);

	xlang_SetLangStrToAction(m_UZoomOutAction,"Native_UZoomOut");
	xlang_SetLangStrToAction(m_IZoomOutAction,"Native_IZoomOut");
	xlang_SetLangStrToAction(m_UZoomInAction,"Native_UZoomIn");
	xlang_SetLangStrToAction(m_IZoomInAction,"Native_IZoomIn");

	m_TestMenu->addAction(m_UZoomOutAction);
	m_TestMenu->addAction(m_UZoomInAction);
	m_TestMenu->addAction(m_IZoomOutAction);
	m_TestMenu->addAction(m_IZoomInAction);
	connect(m_UZoomOutAction, SIGNAL(triggered()), this, SLOT(slot_UZoomOutClicked()));
	connect(m_IZoomOutAction, SIGNAL(triggered()), this, SLOT(slot_IZoomOutClicked()));
	connect(m_UZoomInAction, SIGNAL(triggered()), this, SLOT(slot_UZoomInClicked()));
	connect(m_IZoomInAction, SIGNAL(triggered()), this, SLOT(slot_IZoomInClicked()));

	creatPbn();
	m_TableData = NULL;
}

void Diagram::initTable(int RowNum)
{
	m_nRowNum = RowNum;

	if (m_TableData != NULL)
	{
		delete m_TableData;
		m_TableData = NULL;
	}

	m_TableData = new QScrollTableWidget(this);

	//m_TableData->setStyleSheet(QString::fromUtf8("background-color: rgb(167,183,181);"));
	QHeaderView* pTop = m_TableData->horizontalHeader();
    pTop->setSectionsClickable(false);
    pTop->setSectionsMovable(false);
	pTop->setFont(*g_pSttGlobalFont);
	QHeaderView* pLeft = m_TableData->verticalHeader();
//	pLeft->setDefaultSectionSize(50);
	pLeft->setVisible(false);

	m_TableData->horizontalHeader()->setStretchLastSection(true); //���ó�������
	m_TableData->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TableData->setSelectionBehavior(QAbstractItemView::SelectRows);//Ĭ��ѡ��һ������
	m_TableData->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//���ô�ֱ������

	m_TableData->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
	m_TableData->setStyleSheet("selection-background-color: grey;selection-color: black");
//	m_TableData->horizontalHeader()->setFixedHeight(50);
	int temp = m_TableData->horizontalHeader()->height();

	m_TableData->setColumnCount(5);//����
	m_TableData->setHorizontalHeaderLabels(m_headerList);//һ����˳������ˮƽ��ͷ�������ʾ���ı�
	QFontMetrics fontMetrics = QFontMetrics(*g_pSttGlobalFont);
	int nLabelWidth1 = fontMetrics.width(/*tr("����")*/g_sLangTxt_Name) + 20; //lcq
	int nLabelWidth2 = fontMetrics.width(tr("900.000"))+ 40;
	int nLabelWidth3 = fontMetrics.width(/*tr("��λ")*/g_sLangTxt_Unit) + 10; //lcq
	int nLabelWidth4 = fontMetrics.width(/*tr("��λ(��)")*/g_sLangTxt_Gradient_DPhase) + 40; //lcq

	m_TableData->setColumnWidth(0,nLabelWidth1);//�����п�
	m_TableData->setColumnWidth(1,nLabelWidth2);
	m_TableData->setColumnWidth(2,nLabelWidth3);
	m_TableData->setColumnWidth(3,nLabelWidth4);
	m_TableData->setColumnWidth(4,80);

	m_nRowHeight = fontMetrics.height() + 25;

	for (int i=0; i< m_nRowNum;i++)
	{
		QTableWidgetItem *item1 = new QTableWidgetItem();
		item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//������ʾ�ı�����
		QTableWidgetItem *item2 = new QTableWidgetItem();
		item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item3 = new QTableWidgetItem();
		item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item4 = new QTableWidgetItem();
		item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		QTableWidgetItem *item5 = new QTableWidgetItem();
		item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

		int rowCount = m_TableData->rowCount();
		m_TableData->insertRow(rowCount);//��β������
		m_TableData->setRowHeight(rowCount,15);//�����и�
		m_TableData->setItem(rowCount, 0, item1);
		m_TableData->setItem(rowCount, 1, item2);  
		m_TableData->setItem(rowCount, 2, item3); 
		m_TableData->setItem(rowCount, 3, item4);
		m_TableData->setItem(rowCount, 4, item5);

		m_TableData->setRowHeight(rowCount,m_nRowHeight);
		
		//2022-10-24 sy ���������С
		m_TableData->setFont(*g_pSttGlobalFont);
//		m_TableData->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_TableData->horizontalHeader()->setFont(*g_pSttGlobalFont);
        m_TableData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //ƽ�������п�
	}
}

void Diagram::updateTable()//���±��
{
    g_diagramMutex.lock();//������
	if (m_TableData == NULL)
	{
		return;
	}

	int nLineCount  = m_infoList.count();//wangtao 20240508 ��m_infoTable�����е�ͨ������Ϊm_infoList����ǰ�����һ��ͨ����
    m_TableData->setRowCount(nLineCount);

	QTableWidgetItem  *pItem = NULL;//��ʼ��ָ��

	for(int i = 0;i < nLineCount;i++)
	{
		for (int j = 0; j < 5; j++) 
		{
			QTableWidgetItem *item = m_TableData->item(i, j); 
			if (item) // wangtao 20240522 �����Ŀ�Ƿ���ڣ���Ȼ���ܻᵼ�±���  
			{ 
				item->setText(""); // ������ڣ�������ı�  
			} 
			else 
			{  
				// ��������ڣ�����һ���µ���Ŀ����ӵ������  
				QTableWidgetItem *newItem = new QTableWidgetItem(""); 
				newItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
				m_TableData->setRowHeight(i,m_nRowHeight);
				m_TableData->setItem(i, j, newItem);  

			}  
		}
		
		QString name = m_infoList.at(i).m_strTableName;
		pItem = m_TableData->item(i,0);//�����еı�ͷԪ�ظ���ָ��

		if (pItem == NULL)//zhouhj 20210518 �ڵ��������ԴΪ5��ʱ����ִ�����
		{
			break;
		}

		pItem->setText(name);
		float realvalue = m_infoList.at(i).m_RealValue;
		m_TableData->item(i,1)->setText(QString::number(realvalue, 'f', 3));
		
		if (name == "df/dt")
		{
			m_TableData->item(i,2)->setText("Hz/s");
			m_TableData->item(i,3)->setText("-");
			m_TableData->item(i,4)->setText("-");
		}
		else if (name == "dU/dt")
		{
			m_TableData->item(i,2)->setText("V/s");
			m_TableData->item(i,3)->setText("-");
			m_TableData->item(i,4)->setText("-");
		}
		else if (m_bhasRadio)//�뾶����
		{
			if(m_infoList.at(i).m_lineType == Line_U)//��ʾ��λ
			{
				if (m_UnitDispMode == V_Primary)//һ��ֵ
				{
					m_TableData->item(i,2)->setText("kV");
				}
				else
				{
					m_TableData->item(i,2)->setText("V");
				}
			}
			else
			{
				m_TableData->item(i,2)->setText("A");
			}
		}
		else
		{
			QString strName = m_infoList.at(i).m_strTableName;
			if(m_infoList.at(i).m_lineType == Line_U)
			{
				m_TableData->item(i,2)->setText("V");
			}
			else
			{
				if (strName == tr("Kxb"))
				{
					m_TableData->item(i,2)->setText("");
				}
				else
				{
					m_TableData->item(i,2)->setText("A");
				}
			}

			if (strName == tr("Ir") || strName == tr("Id") || strName == tr("Kxb"))
			{
				m_TableData->item(i,3)->setText("");
				m_TableData->item(i,4)->setText("");
			}
			else
			{
				if (m_infoList.at(i).m_RealValue >=0)
				{
					m_TableData->item(i,3)->setText(QString::number(m_infoList.at(i).m_XW, 'f', 1));
				}
				else
				{
					m_TableData->item(i,3)->setText(QString::number(0, 'f', 1));
				}
				m_TableData->item(i,4)->setText(QString::number(m_infoList.at(i).m_Fre,'f',3));
			}
		}
	}

	if (m_bUse && nLineCount > 0)	//��ѹ�������⴦��,����ģ�鲻��
	{
		for (int i = 0;i < 3 ;i++)
		{
			QTableWidgetItem *pitem = new QTableWidgetItem();
			pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			if (m_strDataEx.size() < i || m_strDataEx.size() == 0)
			{
				pitem->setText(tr(""));
			}
			else
			{
				pitem->setText(m_strDataEx.at(i));
			}
			m_TableData->setItem(nLineCount,i,pitem);
		}
	}
	
/*  suyang 20231109 �ڶ��ν���updateTable()��m_TableData ��ͷ����Ϊ0��ֱ��break;

	if (nLineCount != m_TableData->rowCount())//20230201 ȥ������ı�� zhouyy
	{
		m_TableData->setRowCount(nLineCount);
	}
*/

// 	QTableWidgetItem *pTableWidgetItem = NULL;
// 	QString strText;
// 
// 	for(int i = nLineCount - 1;i >= 0 ;i--)
// 	{
// 		pTableWidgetItem = m_TableData->item(i,0);
// 
// 		if(pTableWidgetItem == NULL)
// 		{
// 			continue;
// 		}
// 
// 		strText = pTableWidgetItem->text();
// 		if (strText.isEmpty())
// 		{
// 			m_TableData->removeRow(i);
// 		}
// 	}

    g_diagramMutex.unlock();
}


void Diagram::setSize(int m_Width,int m_Height)//���û�ͼ�����С
{
	m_PicWidth = m_Width;
	m_PicHeight = m_Height;

	if(m_PicWidth>=m_PicHeight)
	{
		m_Radius = (m_PicHeight-m_ZJoffset)/2.0;
	}
	else
	{
		m_Radius = (m_PicWidth-m_ZJoffset)/2.0;
	}

	m_MidX = m_PicWidth/2.0;
	m_MidY = m_PicHeight/2.0;
	m_CenterPos.setX(m_MidX);
	m_CenterPos.setY(m_MidY);
}

void Diagram::resizeEvent(QResizeEvent* e)
{
#ifdef _PSX_QT_WINDOWS_ 
	setSize(e->size().width(),e->size().height() / 2);
#else
	setSize(e->size().width() * 3 / 5,e->size().height());
#endif
	repaint();
}

void Diagram::paintEvent(QPaintEvent *)
{
	if (!m_TableData)
	{
		return;
	}

	//yzj 2022-3-24 ͨ��������ͼ������,������˸
	QPixmap pix(this->size());
	QPainter pTemp(&pix);
	pTemp.setRenderHints(QPainter::Antialiasing);
	drawBackground(&pTemp);
	drawVector(&pTemp);

	QPainter painter(this);
	painter.drawPixmap(0, 0, pix);

	if (bIsDrawSector == true)
	{
		drawSector(fstartAngle,fendAngle);
		drawSearchArc(fstartAngle_arc,fendAngle_arc);
		drawMTALine(fMTAangle);
		if (bStartSearch)
		{
			drawSearchLine(fSrarchAngle);
		}
	}	
	/*QPainter painter(this);
	painter.drawPixmap(0, 0, pix);*/

	QRect rc = rect();

#ifdef _PSX_QT_WINDOWS_ 
	QRect rcRight(0, rc.height() / 2, rc.width(), rc.height() / 2);
	m_TableData->setGeometry(rcRight);
#else
	QRect rcRight(rc.width() * 3 / 5, rc.y(), 2*rc.width() / 5, rc.height());
	m_TableData->setGeometry(rcRight);
#endif
	//updateTableRowHightSize(rcRight.height());

	if(m_TableData->isHidden())
	{
		//�ػ���������
		m_TableData->show();
	}

	/*
	QPainter painter(this);
	//painter.setRenderHints(QPainter::Antialiasing);
	drawBackground(&painter);
	drawVector(&painter);

	if (bIsDrawSector == true)
	{
		drawSector(fstartAngle,fendAngle);
		drawSearchArc(fstartAngle_arc,fendAngle_arc);
		drawMTALine(fMTAangle);
		if (bStartSearch)
		{
			drawSearchLine(fSrarchAngle);
		}
	}	
	*/
}

void Diagram::updateTableRowHightSize(int height)//���±���и�
{
	if(m_TableData == NULL)
	{
		return;
	}

	QFontMetrics fontMetrics = QFontMetrics(font());
	int nLabelHeight = fontMetrics.height() + 15;

	m_TableData->horizontalHeader()->setFixedHeight(nLabelHeight);
	int H = height-30;
	for (int i=0; i< m_TableData->rowCount();i++)
	{
		m_TableData->setRowHeight(i,H/m_TableData->rowCount());
	}
}

void Diagram::drawBackground(QPainter *painter)//���û�ͼ���򱳾�
{
	QRect rectCenter(rect().left(),rect().top(),rect().width(),rect().height());

	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::black);
	painter->drawRect(rectCenter);

	painter->save();
	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::blue);
	painter->restore();

	QFont font1;
	font1.setPointSize(30);
	QFontMetrics fontMetrics = QFontMetrics(this->font());//��������ַ����ַ����Ĵ�С
	int nSpace = 2;
	int nMargin = 2;
	int nLabelNumHeight = fontMetrics.height()*2 + 20;
	int nLabelWidth = 0;

	if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
	{
		nLabelWidth = fontMetrics.width(QString::fromLocal8Bit("������: 00")) + 20;
	}
	else
	{
		nLabelWidth = fontMetrics.width("Group numbers: 00") + 20;
	}

#ifdef _PSX_QT_WINDOWS_
	QString strPicPath = _P_GetResourcePath();
	strPicPath += "Button-Next.png";
#else
    QString strPicPath = ":/ctrls/images/Button-Next.png";
#endif
	QPixmap pixmap(strPicPath);
	int nbtnHorizontalspace = 2;
	int nbtnHeight = pixmap.height() + 2;
	int nbtnWidth = (nLabelWidth - 2)/2;

#ifdef _PSX_QT_WINDOWS_ 
	m_labNum->setGeometry(rect().width() - (nSpace + nLabelWidth),rect().height() / 2 - (2*nSpace+ nbtnHeight + nLabelNumHeight),nLabelWidth,nLabelNumHeight);
	m_pbnPre->setGeometry(rect().width() - (nSpace + nLabelWidth),rect().height() / 2 - (nSpace+ nbtnHeight),nbtnWidth,nbtnHeight);
	m_pbnNext->setGeometry(rect().width() -(nSpace + nbtnWidth),rect().height() / 2 - (nSpace+ nbtnHeight),nbtnWidth,nbtnHeight);
#else
	m_labNum->setGeometry(rect().width() * 3 / 5 - (nSpace + nLabelWidth),rect().height() - (3*nSpace + nbtnHeight + nLabelNumHeight),nLabelWidth,nLabelNumHeight);
	m_pbnPre->setGeometry(rect().width() * 3 / 5 - (nSpace + nLabelWidth),rect().height() -(2*nSpace+ nbtnHeight),nbtnWidth,nbtnHeight);
	m_pbnNext->setGeometry(rect().width() * 3 / 5 -(nSpace + nbtnWidth),rect().height() -(2*nSpace + nbtnHeight),nbtnWidth,nbtnHeight);
	//m_btnInstruction->setGeometry(rect().width() * 3 / 5 - (nSpace + nLabelWidth),rect().height() / 2 -(nSpace + nLabelNumHeight),nLabelWidth,nLabelNumHeight);
#endif
}

void Diagram::drawCircle(QPainter *painter)
{
	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;
	t_MidY = m_PicHeight/2.0;

	QPointF t_CenterPos(t_MidX,t_MidY);
	painter->drawArc(t_MidX-m_Radius,t_MidY-m_Radius, m_Radius*2,m_Radius*2, 360*16, 360*16) ;
	painter->setPen(Qt::gray);
	painter->drawArc(t_MidX-3*m_Radius/4.0,t_MidY-3*m_Radius/4.0,6*m_Radius/4,6*m_Radius/4, 360*16, 360*16) ;
	painter->drawArc(t_MidX-2*m_Radius/4.0,t_MidY-2*m_Radius/4.0,4*m_Radius/4,4*m_Radius/4, 360*16, 360*16) ;
	painter->drawArc(t_MidX-1*m_Radius/4.0,t_MidY-1*m_Radius/4.0,2*m_Radius/4,2*m_Radius/4, 360*16, 360*16) ;
}

void Diagram::setIsDrawSectorFlag(bool flag)
{
	bIsDrawSector = flag;
	update();
}

void Diagram::setSectorAngle(float startangle,float endangle)
{
	fstartAngle = startangle;
	fendAngle = endangle;
}

void Diagram::setSearchArcAngle(float startangle,float endangle)
{
	fstartAngle_arc = startangle;
	fendAngle_arc = endangle;
}

void Diagram::setMTAAngle(float mtaangle)
{
	fMTAangle = mtaangle;
}

void Diagram::setSearchAngle(float angle)
{
	fSrarchAngle = angle;
}

void Diagram::setStartSearch(bool b)
{
	bStartSearch = b;
}

QPointF Diagram::getLineTopPoint(float angle)//��û����ߵ���ߵ�
{
	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;
	t_MidY = m_PicHeight/2.0;
	float temp = 0;
	float top_x,top_y;
	if (angle>=0 && angle<90)
	{
		top_x = t_MidX+m_Radius*qCos(angle*PI/180)+temp;
		top_y = t_MidY-m_Radius*qSin(angle*PI/180)-temp;
	}
	else if (angle>=90 && angle<180)
	{
		top_x = t_MidX-m_Radius*qCos((180-angle)*PI/180)-temp;
		top_y = t_MidY-m_Radius*qSin((180-angle)*PI/180)-temp;
	}
	else if (angle>=180 && angle<270)
	{
		top_x = t_MidX-m_Radius*qCos((angle-180)*PI/180)-temp;
		top_y = t_MidY+m_Radius*qSin((angle-180)*PI/180)+temp;
	}
	else if (angle>=270 && angle<=360)
	{
		top_x = t_MidX+m_Radius*qCos((360-angle)*PI/180)+temp;
		top_y = t_MidY+m_Radius*qSin((360-angle)*PI/180)+temp;
	}
	QPointF topPoint(top_x,top_y);
	return topPoint;
}

void Diagram::drawSearchArc(float startAngle,float endAngle)//�����Ѷ໡�߽߱�
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);//����������
	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;//�������ĵ�
	t_MidY = m_PicHeight/2.0;
	QPointF t_CenterPos(t_MidX,t_MidY);

	QRectF rectf(t_MidX-m_Radius,t_MidY-m_Radius, m_Radius*2,m_Radius*2);
	float spanAngle;
	spanAngle = endAngle-startAngle;

	painter.setPen(QColor(255,0,255));
	//�����߽�Ļ���
	painter.drawArc(t_MidX-2.5*m_Radius/4.0,t_MidY-2.5*m_Radius/4.0,5*m_Radius/4,5*m_Radius/4, startAngle*16, spanAngle*16) ;
}

void Diagram::drawSector(float startAngle,float endAngle)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);
	QRadialGradient gradient(0, 0, 90);
	gradient.setColorAt(0, Qt::white);
	gradient.setColorAt(1.0, QColor(218,112,214,100));
	painter.setBrush(gradient);

	painter.setPen(Qt::NoPen);  //���û���

	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;
	t_MidY = m_PicHeight/2.0;
	QPointF t_CenterPos(t_MidX,t_MidY);
	
	QRectF rectf(t_MidX-m_Radius,t_MidY-m_Radius, m_Radius*2,m_Radius*2);
	float spanAngle;
	spanAngle = endAngle-startAngle;
	if (spanAngle<0)
	{
		spanAngle = spanAngle+360;
	}
	
	QPen  gridPen( Qt::yellow, 1.2);
	gridPen.setStyle(Qt::DotLine);
	painter.setPen(gridPen);

	QPainterPath path;
	path.moveTo(t_CenterPos);
	path.arcTo(rectf, startAngle, spanAngle);
	path.closeSubpath();
	painter.drawPath(path);
}

void Diagram::drawMTALine(float mtaAngle)
{
	QPainter painter(this);
	QPen  gridPen( Qt::red, 1.5 );
	gridPen.setStyle(Qt::DotLine);
	painter.setPen(gridPen);

	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;
	t_MidY = m_PicHeight/2.0;
	QPointF t_CenterPos(t_MidX,t_MidY);
	QPointF topPoint = getLineTopPoint(mtaAngle);
	QLineF line1(t_CenterPos,topPoint);
	painter.drawLine(line1);
}

void Diagram::drawSearchLine(float angle)
{
	QPainter painter(this);
	QPen  gridPen( QColor(34,139,34), 1.5 );
	gridPen.setStyle(Qt::DotLine);
	painter.setPen(gridPen);

	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;
	t_MidY = m_PicHeight/2.0;
	QPointF t_CenterPos(t_MidX,t_MidY);
	QPointF topPoint = getLineTopPoint(angle);
	QLineF line1(t_CenterPos,topPoint);
	painter.drawLine(line1);
}

void Diagram::drawGrid(QPainter *painter)
{
	float t_MidX,t_MidY;
	t_MidX = m_PicWidth/2.0;
	t_MidY = m_PicHeight/2.0;

	QPen  gridPen( Qt::gray, 1 );
	gridPen.setStyle(Qt::DotLine);
	painter->setPen(gridPen);

	QPointF t_P1,t_P2,t_P3,t_P4;
	qreal t1 = t_MidX-m_Radius;
	qreal t2 = t_MidX+m_Radius;
	qreal t3 = t_MidY-m_Radius;
	qreal t4 = t_MidY+m_Radius;
	t_P1.setX(t1);
	t_P1.setY(t_MidY);

	t_P2.setX(t2);
	t_P2.setY(t_MidY);

	t_P3.setX(t_MidX);
	t_P3.setY(t3);

	t_P4.setX(t_MidX);
	t_P4.setY(t4);

	painter->drawLine(t_P1,t_P2);
	painter->drawLine(t_P3,t_P4);

	QPointF P1,P2,P3,P4;
	P1.setX(t_P1.x()-20);
	P1.setY(t_P1.y());

	P2.setX(t_P2.x()+10);
	P2.setY(t_P2.y());

	P3.setX(t_P3.x());
	P3.setY(t_P3.y());

	P4.setX(t_P4.x());
	P4.setY(t_P4.y());

	painter->drawText(P1,tr("180"));
	painter->drawText(P2,tr("0"));
	painter->drawText(P3,tr("+90"));
	painter->drawText(P4,tr("-90"));

	QPointF P5, P6;
	P5.setX(P1.x());
	P5.setY(P3.y() +10);
	P6.setX(P1.x());
	P6.setY(P3.y() + 30);
	painter->drawText(P5, "Umax: " + QString::number(m_fUMax) + "V");
	painter->drawText(P6, "Imax: " + QString::number(m_fIMax) + "A");
}

void Diagram::drawDesText(QPainter *painter)
{
	painter->setPen(Qt::white);
	QPoint t_InfPosBHDL,t_InfPosDY,t_InfPosCLDL,t_Ox;
	qreal t_inx = m_ZJoffset;
	qreal t_iny = m_ZJoffset;

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	
	int nLabelNumHeight = 19;
	int nLabelWidth = 0;
	if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
	{
		nLabelWidth = fontMetrics.width(QString::fromLocal8Bit("A��")) + 4;
	}
	else
	{
		nLabelWidth = fontMetrics.width("Phase A") + 4;
	}

	int textPos = m_PicWidth -nLabelWidth;
	int lineXPos = textPos-nLabelWidth;

	int lineWidth =20;

	t_InfPosBHDL.setX(textPos);
	t_InfPosBHDL.setY(t_iny);
	t_InfPosCLDL.setX(textPos);
	t_InfPosCLDL.setY(t_iny+nLabelNumHeight);
	t_InfPosDY.setX(textPos);
	t_InfPosDY.setY(t_iny+nLabelNumHeight*2);
	t_Ox.setX(textPos);
	t_Ox.setY(t_iny+nLabelNumHeight*3);

	CString strItemA,strItemB,strItemC,strItemO;
	xlang_GetLangStrByFile(strItemA,"sAphase");
	xlang_GetLangStrByFile(strItemB,"sBphase");
	xlang_GetLangStrByFile(strItemC,"sCphase");
	xlang_GetLangStrByFile(strItemO,"Native_PhaseO");

	painter->setPen(Qt::yellow);
	painter->drawLine(lineXPos,t_InfPosBHDL.y()-nLabelNumHeight/4,lineXPos+20,t_InfPosBHDL.y()-nLabelNumHeight/4);

	painter->drawText(t_InfPosBHDL,strItemA);

	painter->setPen(Qt::green);
	painter->drawLine(lineXPos,t_InfPosCLDL.y()-nLabelNumHeight/4,lineXPos+20,t_InfPosCLDL.y()-nLabelNumHeight/4);
	painter->drawText(t_InfPosCLDL,strItemB);

	painter->setPen(Qt::red);
	painter->drawLine(lineXPos,t_InfPosDY.y()-nLabelNumHeight/4,lineXPos+20,t_InfPosDY.y()-nLabelNumHeight/4);
	painter->drawText(t_InfPosDY,strItemC);

	painter->setPen(Qt::white);
	painter->drawLine(lineXPos,t_Ox.y()-nLabelNumHeight/4,lineXPos+20,t_Ox.y()-nLabelNumHeight/4);
	painter->drawText(t_Ox,strItemO);
}

void Diagram::drawVector(QPainter * painter)
{
    g_diagramMutex.lock();
	painter->save();
	painter->setPen(Qt::white);
	painter->setRenderHint(QPainter::Antialiasing);

	drawCircle(painter);
	drawGrid(painter);
	drawDesText(painter);

	QVector<float> t_IRealValueVector;
	QVector<float> t_URealValueVector;
	float t_IMaxValue = 0.0;
	float t_UMaxValue = 0.0;
	if(m_infoList.count()==0)
	{
		painter->restore();
        g_diagramMutex.unlock();  //2022-3-27  lijunqing lock�κ�ʱ��Ӧ����unlock��֮��Ӧ
		return;
	}

	for(int i = 0;i < m_infoList.count();i++)
	{
		if(m_infoList.at(i).m_lineType == Line_U && m_infoList.at(i).m_bShowOrHide)
		{
			t_URealValueVector.push_back(qAbs(m_infoList.at(i).m_RealValue));
		}
		else if(m_infoList.at(i).m_lineType == Line_I && m_infoList.at(i).m_bShowOrHide)
		{
			t_IRealValueVector.push_back(qAbs(m_infoList.at(i).m_RealValue));
		}
	}
	
	qSort(t_IRealValueVector.begin(),t_IRealValueVector.end());
	qSort(t_URealValueVector.begin(),t_URealValueVector.end());
	if(t_IRealValueVector.size()>0)
	{
		t_IMaxValue = t_IRealValueVector.at(t_IRealValueVector.size()-1);
	}
	
	if(t_URealValueVector.size()>0)
	{
		t_UMaxValue = t_URealValueVector.at(t_URealValueVector.size()-1);
	}

	bool bMaxValueChanged = false;

	if (m_fUMax<t_UMaxValue)
	{
		m_fUMax = t_UMaxValue*1.2;
		bMaxValueChanged = true;
	}
	if (m_fIMax<t_IMaxValue)
	{
		m_fIMax = t_IMaxValue*1.2;
		bMaxValueChanged = true;
	}

//	m_lneUMax->setText(QString::number(m_fUMax,'f',3));
//	m_lneIMax->setText(QString::number(m_fIMax,'f',3));

	for(int t_LineID =0;t_LineID < m_infoList.count();t_LineID++)
	{
		LineInfo  t_LineInfor = m_infoList.at(t_LineID);
		if(t_LineInfor.m_bShowOrHide==false)
		{
			continue;
		}
		float t_RealValue = qAbs(t_LineInfor.m_RealValue);
		if(t_RealValue ==0.0)
		{
			painter->restore();
			continue;
		}

		painter->setPen(t_LineInfor.m_Color);
		float t_FZ ;
		
		if (t_LineInfor.m_lineType == Line_U)
		{
			t_FZ = (qAbs(t_LineInfor.m_RealValue))*(m_Radius/(m_fUMax));
		}
		else
		{
			t_FZ = (qAbs(t_LineInfor.m_RealValue))*(m_Radius/(m_fIMax));
		}
		
		t_FZ*=t_LineInfor.m_ChangeFactor;
		if (t_FZ <0.1)
		{
			continue;
		}
		float t_XW ;
		t_XW = t_LineInfor.m_XW/180.0;
		t_XW*=PI;
		float t_realpart =t_FZ*cos(t_XW);
		float t_visualpart =t_FZ*sin(t_XW);

		QPointF t_End;
		t_End.setX (m_MidX+t_realpart);
		t_End.setY( m_MidY-t_visualpart) ;

		painter->drawLine(m_CenterPos,t_End);

		float flSx = (float)m_CenterPos.x();
		float flSy = (float)m_CenterPos.y();
		float flEx = (float)t_End.x();
		float flEy = (float)t_End.y();

		int flLength = Diagram::m_l;
		float flAngle = Diagram::m_a;
		if(GetDistance(flSx,flSy,flEx,flEy) == 0)   return;
		float tmpX = flEx + (flSx-flEx)*flLength/GetDistance(flSx,flSy,flEx,flEy);
		float tmpY = flEy + (flSy-flEy)*flLength/GetDistance(flSx,flSy,flEx,flEy);
		float fl1X = (tmpX-flEx)*cos(-flAngle/2) - (tmpY-flEy)*sin(-flAngle/2) + flEx;
		float fl1Y = (tmpY-flEy)*cos(-flAngle/2) + (tmpX-flEx)*sin(-flAngle/2) + flEy;
		float fl2X = (tmpX-flEx)*cos(flAngle/2) - (tmpY-flEy)*sin(flAngle/2) + flEx;
		float fl2Y = (tmpY-flEy)*cos(flAngle/2) + (tmpX-flEx)*sin(flAngle/2) + flEy;
		painter->drawLine(flEx,flEy,fl1X,fl1Y);
		painter->drawLine(flEx,flEy,fl2X,fl2Y);

		CString strItem1,strItem2,strItem3; 
		xlang_GetLangStrByFile(strItem1,"Native_Relay");
		xlang_GetLangStrByFile(strItem2,"Native_Measure");
		xlang_GetLangStrByFile(strItem3,"Native_Current");

		if (t_LineInfor.m_UIType == strItem1 || t_LineInfor.m_UIType == strItem2)
		{
			painter->drawText(t_End,t_LineInfor.m_UIType+strItem3);
		}
		else
		{
			painter->drawText(t_End,t_LineInfor.m_UIType);
		}
	}
	painter->restore();
    g_diagramMutex.unlock();
}

float Diagram::GetDistance(float flStartx,float flStarty,float flEndx,float flEndy)
{
	float flRlt;
	flRlt=(flStartx-flEndx)*(flStartx-flEndx)+(flStarty-flEndy)*(flStarty-flEndy);
	flRlt=(float)sqrt(flRlt);
	return flRlt;
}

void Diagram::updateDiagram()
{
	updateTable();
	update();
}

void Diagram::mousePressEvent( QMouseEvent *event )
{
	if (event->button()==Qt::RightButton)
	{
		m_TestMenu->exec(QCursor::pos());
	}
}

void Diagram::slot_UZoomOutClicked()
{
	m_fUMax -=20;
	if (m_fUMax<=10)
	{
		m_fUMax = 10;
	}
	repaint();
}

void Diagram::slot_IZoomOutClicked()
{
	m_fIMax -=5;
	if (m_fIMax<=5)
	{
		m_fIMax = 5;
	}
	repaint();
}

void Diagram::slot_UZoomInClicked()
{
	m_fUMax +=20;
	if (m_fUMax>=120)
	{
		m_fUMax = 120;
	}
	repaint();
}

void Diagram::slot_IZoomInClicked()
{
	m_fIMax +=5;
	if (m_fIMax>=20)
	{
		m_fIMax = 20;
	}
	repaint();
}

void Diagram::creatPbn()
{
	m_pbnNext = new QPushButton(this);
	m_pbnPre = new QPushButton(this);
#ifdef _PSX_QT_WINDOWS_
	QString strPicPath_Next = _P_GetResourcePath();
	strPicPath_Next += "Button-Next.png";

	m_pbnNext->setIcon(QPixmap(strPicPath_Next));
	m_pbnNext->setStyleSheet("background-color: white;"); //rgb(83, 92, 91)

	QString strPicPath_Pre = _P_GetResourcePath();
	strPicPath_Pre += "Button-Previous.png";

	m_pbnPre->setIcon(QPixmap(strPicPath_Pre));
	m_pbnPre->setStyleSheet("background-color: white;");
#else
	QString strPicPath_Next = ":/ctrls/images/Button-Next.png";
	m_pbnNext->setIcon(QPixmap(strPicPath_Next));
	m_pbnNext->setStyleSheet("background-color: white;"); //rgb(83, 92, 91)

	QString strPicPath_Pre = ":/ctrls/images/Button-Previous.png";
	m_pbnPre->setIcon(QPixmap(strPicPath_Pre));
	m_pbnPre->setStyleSheet("background-color: white;");
#endif
	m_labNum = new QLabel(this);
	m_labNum->setStyleSheet("color: black;background-color: white;");
/*
	if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
	{
		m_labNum->setText(QString::fromLocal8Bit("������: %1").arg(1) + "\n" + QString::fromLocal8Bit("��ǰ��: %1").arg(1));
	}
	else
	{
		m_labNum->setText(QString("group number: %1").arg(1) + "\n" + QString("current group: %1").arg(1));
	}
*/
	CString strAllGroup,strCurGroup;
	xlang_GetLangStrByFile(strAllGroup, "Native_AllGroup");
	xlang_GetLangStrByFile(strCurGroup, "Native_CurGroup");

	CString strText1,strText2;
	strText1 = _T("  ");
	strText1 += strAllGroup;
	strText1 += "1";
	
	strText2 = _T("  ");
	strText2 += strCurGroup;
	strText2 += "1";
	
	CString str = strText1;
	str += "\n";
	str += strText2;

	m_labNum->setText(str);
/*
	m_btnInstruction = new QLabel(this);
	m_btnInstruction->setStyleSheet("color: black;background-color: white;");

	if(CXLanguageMngr::xlang_IsCurrXLanguageChinese())
	{
		m_btnInstruction->setText(QString::fromLocal8Bit("  ��:��һ��") + "\n" + QString::fromLocal8Bit("  ��:��һ��"));
	}
	else
	{
		m_btnInstruction->setText(QString("  <--:last group") + "\n" + QString("  -->:next group"));
	}
*/
	CString strLastGroup,strNextGroup;
	xlang_GetLangStrByFile(strLastGroup, "Native_LastGroup");
	xlang_GetLangStrByFile(strNextGroup, "Native_NextGroup");

	strText1 = _T("  <--:");
	strText1 += strLastGroup;

	strText2 = _T("  -->:");
	strText2 += strNextGroup;

	str = strText1;
	str += "\n";
	str += strText2;

	//m_btnInstruction->setText(str);

	connect(m_pbnNext, SIGNAL(clicked()), this, SLOT(slot_Pbn_NextClicked()));
	connect(m_pbnPre, SIGNAL(clicked()), this, SLOT(slot_Pbn_PreClicked()));
}

void Diagram::setHeader(QStringList headerList)
{
	m_headerList = headerList;
	m_TableData->setHorizontalHeaderLabels(m_headerList);
}

void Diagram::setLineValue(float *fAmp,float *fPhe)
{
	int nLineCount  = m_infoList.count();
	for(int i = 0;i < nLineCount;i++)
	{
		m_TableData->item(i,0)->setText(m_infoList.at(i).m_strTableName);
		m_TableData->item(i,1)->setText(QString::number(fAmp[i], 'f', 3));
		if(m_infoList.at(i).m_lineType == Line_U)
		{
			m_TableData->item(i,2)->setText("V");
		}
		else
		{
			m_TableData->item(i,2)->setText("A");
		}
		m_TableData->item(i,3)->setText(QString::number(fPhe[i], 'f', 1));
	}

	update();
}

void Diagram::setColumnWidth(int nCol,int nWidth)
{
	m_TableData->setColumnWidth(nCol,nWidth);
}

void Diagram::setUIMax(float fUMax,float fIMax)
{
	if(fUMax > 0)
	{
		m_fUMax = fUMax;
	}
	if(fIMax > 0)
	{
		m_fIMax = fIMax;
	}
}

void Diagram::setLineInfos(QList<LineInfo> infoList)
{
	m_infoList = infoList;
	if(m_VectorType == STT_LowFreqDfdt_VECTOR)
	{
		LineInfo info;
		info.m_strTableName = _T("df/dt");
		info.m_RealValue = fCurrSearchValue;
		m_infoList.push_back(info);
	}
	else if(m_VectorType == STT_LowVolDvdt_VECTOR)
	{
		LineInfo info;
		info.m_strTableName = _T("dU/dt");
		info.m_RealValue = fCurrSearchValue;
		m_infoList.push_back(info);
	}
	updateTable();
	update();
}

void Diagram::setTableInfos(QList<LineInfo> infoList)
{
	m_infoTable = infoList;

	if(m_VectorType == STT_LowFreqDfdt_VECTOR)
	{
		LineInfo info;
		info.m_strTableName = _T("df/dt");
		info.m_RealValue = fCurrSearchValue;
		m_infoTable.push_back(info);
	}
	else if(m_VectorType == STT_LowVolDvdt_VECTOR)
	{
		LineInfo info;
		info.m_strTableName = _T("dU/dt");
		info.m_RealValue = fCurrSearchValue;
		m_infoTable.push_back(info);
	}
}

void Diagram::setLegends(QStringList nameList,QList<QPen> colorList)
{
	m_LegendNameList = nameList;
	m_LegendColorList = colorList;
}

void Diagram::setPbnDisp(bool b)
{
	m_pbnNext->setDisabled(!b);
	m_pbnPre->setDisabled(!b);
	m_labNum->setDisabled(!b);
	//m_btnInstruction->setDisabled(!b);
	m_pbnNext->setVisible(b);
	m_pbnPre->setVisible(b);
	m_labNum->setVisible(b);
	//m_btnInstruction->setVisible(b);
}

void Diagram::setlabNumText(QString str)
{
	m_labNum->setText(str);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
	update();
}

void Diagram::InsertNewLineOfTable( QStringList str,bool bUse)
{
	int nRow = m_TableData->rowCount();
	if (nRow < 8)
	{
		m_TableData->insertRow(nRow - 1);;
	}
	m_bUse = bUse;
	m_strDataEx = str;

}

void Diagram::slot_Pbn_NextClicked()
{
	emit sig_Pbn_NextClicked();
}

void Diagram::slot_Pbn_PreClicked()
{
	emit sig_Pbn_PreClicked();
}
