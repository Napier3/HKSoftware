#include "GradientGroupGrid.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/API/MathApi.h"
#include <QApplication>

#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#define GROUPGRID_COLS 4


//QGradientGroupGrid::QGradientGroupGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
QGradientGroupGrid::QGradientGroupGrid(QWidget* pParent) : QSettingGridBase(pParent)	//20270708 huangliang
{
	m_fAmpMax = 120;
	m_fAmpMin = 0;
	m_fEDVal = 0;
	m_MenuAmp = FALSE;
	m_MenuPhase = FALSE;
	m_MenuFre = FALSE;
	m_ActUAmpED = FALSE;
	m_ActUZero = FALSE;
	m_ActUEqualAmp = FALSE;
	m_ActIAmp1 = FALSE;
	m_ActIAmp5 = FALSE;
	m_ActIAmp0 = FALSE;
	m_ActIqualAmp = FALSE;
	m_ActIAmpED = FALSE;
	m_bRunning = FALSE;
	m_bDC = FALSE;
	installEventFilter(this);
}

QGradientGroupGrid::~QGradientGroupGrid()
{

}

void QGradientGroupGrid::InitGrid(long nType)
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(TRUE);
	CreatTableMenu(nType);

	connect(this,SIGNAL(cellDoubleClicked(int , int)),SLOT(slot_cellDoubleClicked(int , int )));
}

void QGradientGroupGrid::InitGridTitle()
{
	CString strChannal, strAmplitude, strPhase, strFreq;
	xlang_GetLangStrByFile(strChannal, "Native_Channel");
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strFreq, "Native_Freq");
	CString astrGridTitle[GROUPGRID_COLS] = {strChannal, strAmplitude, strPhase, strFreq};
	int iGridWidth[GROUPGRID_COLS]={100, 100, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, GROUPGRID_COLS);
}

void QGradientGroupGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	QGradientGroupData* pGroupData = (QGradientGroupData*)pData;

	Show_StaticString(pData, nRow, 0, pGroupData->m_strName);
	Show_Float(pData, nRow, 1, 3, pGroupData->m_pfAmp,1,EndEditCell_Value_Float);
	Show_Float(pData, nRow, 2, 3, pGroupData->m_pfAngle,1,EndEditCell_Value_Float);
	Show_Float(pData, nRow, 3, 3, pGroupData->m_pfFreq,1,EndEditCell_Value_Float);

	nRow++;
}

void QGradientGroupGrid::SetDatas(CExBaseList *pList)
{
	m_pChDatas = pList;

}
void QGradientGroupGrid::slot_cellDoubleClicked(int nRow, int nCol)
{
	long nEditType = 0;

	if (nCol == 1)
	{
		if(m_moudleType == Moudle_U)
		{
			nEditType = 0;
		}
		else
		{
			nEditType = 1;
		}
	}
	else if (nCol == 2)
	{
		nEditType = 2;
	}
	else if (nCol == 3)
	{
		nEditType = 3;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif
	
}
bool QGradientGroupGrid::eventFilter(QObject *obj, QEvent *event)
{
	DisableSystemMenu(obj, event);

	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent * pMouseEvent = (QMouseEvent*) event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent*)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);
}

void QGradientGroupGrid::CreatTableMenu(long nType)
{
	m_MenuAmp = new QMenu(this);
	m_MenuPhase = new QMenu(this);
	m_MenuFre = new QMenu(this);
	QString str;

    if (nType==Moudle_U)//
	{
		m_moudleType = Moudle_U;
		m_fEDVal = g_oSystemParas.m_fVNom;
        m_ActUAmpED = new QAction(tr("utf8-change error"),this);
		m_ActUZero = new QAction(tr("'A~a"),this);
        m_ActUEqualAmp = new QAction(tr("utf8-change error"),this);

		xlang_SetLangStrToAction(m_ActUAmpED,"Native_EDPhaseV");
		xlang_SetLangStrToAction(m_ActUZero,"Native_Zero");
		xlang_SetLangStrToAction(m_ActUEqualAmp,"Native_EqualAmp");

		connect (m_ActUAmpED,SIGNAL(triggered()),this,SLOT(slot_ActUAmpEDClicked())); 
		connect (m_ActUZero,SIGNAL(triggered()),this,SLOT(slot_ActUZeroClicked()));
		connect (m_ActUEqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActUEqualAmpClicked())); 
		m_MenuAmp->addAction(m_ActUAmpED); 
		m_MenuAmp->addAction(m_ActUZero);
		m_MenuAmp->addAction(m_ActUEqualAmp);

        QAction* pActUAmpED20 = new QAction(tr("20% utf8-Error"),this);
        QAction* pActUAmpED40 = new QAction(tr("40% utf8-Error"),this);
        QAction* pActUAmpED60 = new QAction(tr("60% utf8-Error"),this);
        QAction* pActUAmpED80 = new QAction(tr("80% utf8-Error"),this);
        QAction* pActUAmpED120 = new QAction(tr("120% utf8-Error"),this);
		CString strEDPhaseV;
		xlang_GetLangStrByFile(strEDPhaseV, "Native_EDPhaseV");
		pActUAmpED20->setText("20%" + strEDPhaseV);
		pActUAmpED40->setText("40%" + strEDPhaseV);
		pActUAmpED60->setText("60%" + strEDPhaseV);
		pActUAmpED80->setText("80%" + strEDPhaseV);
		pActUAmpED120->setText("120%" + strEDPhaseV);
		connect (pActUAmpED20,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
		connect (pActUAmpED40,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
		connect (pActUAmpED60,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
		connect (pActUAmpED80,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
		connect (pActUAmpED120,SIGNAL(triggered()),this,SLOT(slot_ActPerUAmpEDClicked())); 
		m_MenuAmp->addAction(pActUAmpED20); 
		m_MenuAmp->addAction(pActUAmpED40); 
		m_MenuAmp->addAction(pActUAmpED60); 
		m_MenuAmp->addAction(pActUAmpED80); 
		m_MenuAmp->addAction(pActUAmpED120); 
	}
	else//uc'A÷"Alb?é
	{
		m_moudleType = Moudle_I;
		m_fEDVal = g_oSystemParas.m_fINom;
		m_ActIAmp1 = new QAction(tr("1A"),this);
		m_ActIAmp5 = new QAction(tr("5A"),this);
		m_ActIAmp0 = new QAction(tr("'A~a"),this);
        m_ActIqualAmp = new QAction(tr("utf8-Error"),this);
        m_ActIAmpED = new QAction(tr("utf8-Error"),this);

		xlang_SetLangStrToAction(m_ActIAmp0,"Native_Zero");
		xlang_SetLangStrToAction(m_ActIqualAmp,"Native_EqualAmp");
		xlang_SetLangStrToAction(m_ActIAmpED,"Native_EDCurrent");

		connect (m_ActIAmp1,SIGNAL(triggered()),this,SLOT(slot_ActIAmp1Clicked())); 
		connect (m_ActIAmp5,SIGNAL(triggered()),this,SLOT(slot_ActIAmp5Clicked()));
		connect (m_ActIAmp0,SIGNAL(triggered()),this,SLOT(slot_ActIAmp0Clicked())); 
		connect (m_ActIqualAmp,SIGNAL(triggered()),this,SLOT(slot_ActIqualAmpClicked())); 
		connect (m_ActIAmpED,SIGNAL(triggered()),this,SLOT(slot_ActIAmpEDClicked())); 

		m_MenuAmp->addAction(m_ActIAmp1);
		m_MenuAmp->addAction(m_ActIAmp5); 
		m_MenuAmp->addAction(m_ActIAmp0); 
		m_MenuAmp->addAction(m_ActIqualAmp); 
		m_MenuAmp->addAction(m_ActIAmpED);

		QAction* pActIAmpED20 = new QAction(tr("20%P^iP¨uc'A÷"),this);
		QAction* pActIAmpED40 = new QAction(tr("40%P^iP¨uc'A÷"),this);
		QAction* pActIAmpED60 = new QAction(tr("60%P^iP¨uc'A÷"),this);
		QAction* pActIAmpED80 = new QAction(tr("80%P^iP¨uc'A÷"),this);
		QAction* pActIAmpED120 = new QAction(tr("120%P^iP¨uc'A÷"),this);
		CString strEDPhaseA;
		xlang_GetLangStrByFile(strEDPhaseA, "Native_EDCurrent");
		pActIAmpED20->setText("20%" + strEDPhaseA);
		pActIAmpED40->setText("40%" + strEDPhaseA);
		pActIAmpED60->setText("60%" + strEDPhaseA);
		pActIAmpED80->setText("80%" + strEDPhaseA);
		pActIAmpED120->setText("120%" + strEDPhaseA);
		connect (pActIAmpED20,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
		connect (pActIAmpED40,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
		connect (pActIAmpED60,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
		connect (pActIAmpED80,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
		connect (pActIAmpED120,SIGNAL(triggered()),this,SLOT(slot_ActPerIAmpEDClicked())); 
		m_MenuAmp->addAction(pActIAmpED20); 
		m_MenuAmp->addAction(pActIAmpED40); 
		m_MenuAmp->addAction(pActIAmpED60); 
		m_MenuAmp->addAction(pActIAmpED80); 
		m_MenuAmp->addAction(pActIAmpED120); 
	}

	QAction *m_ActUPhaseP = new QAction(tr("~O'yDò"),this);
	QAction *m_ActUPhaseN = new QAction(tr(",oDò"),this);
	QAction *m_ActUPhaseZ = new QAction(tr("'A~aDò"),this);

	xlang_SetLangStrToAction(m_ActUPhaseP,"Native_PositiveSeq");
	xlang_SetLangStrToAction(m_ActUPhaseN,"Native_NegativeSeq");
	xlang_SetLangStrToAction(m_ActUPhaseZ,"Native_ZeroSeq");

	connect (m_ActUPhaseP,SIGNAL(triggered()),this,SLOT(slot_ActPhasePClicked())); 
	connect (m_ActUPhaseN,SIGNAL(triggered()),this,SLOT(slot_ActPhaseNClicked()));
	connect (m_ActUPhaseZ,SIGNAL(triggered()),this,SLOT(slot_ActPhaseZClicked())); 
	m_MenuPhase->addAction(m_ActUPhaseP);
	m_MenuPhase->addAction(m_ActUPhaseN); 
	m_MenuPhase->addAction(m_ActUPhaseZ); 

	QAction *m_ActIHz50 = new QAction(tr("50Hz"),this);
	QAction *m_ActIHz60 = new QAction(tr("60Hz"),this);
	QAction *m_ActIHzEqual = new QAction(tr("u`EAEu^A^E"),this);
	xlang_SetLangStrToAction(m_ActIHzEqual,"Native_EqualFreq");

	connect (m_ActIHz50,SIGNAL(triggered()),this,SLOT(slot_ActHz50Clicked())); 
	connect (m_ActIHz60,SIGNAL(triggered()),this,SLOT(slot_ActHz60Clicked()));
	connect (m_ActIHzEqual,SIGNAL(triggered()),this,SLOT(slot_ActHzEqualClicked()));
	m_MenuFre->addAction(m_ActIHz50);
	m_MenuFre->addAction(m_ActIHz60); 
	m_MenuFre->addAction(m_ActIHzEqual); 
}

void QGradientGroupGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	if(event->button() == Qt::RightButton)
	{
		QTableWidgetItem *item = itemAt(event->pos());
		if (item)//add wangtao 20240902 防止空指针导致崩溃
		{
		setCurrentItem(itemAt(event->pos()));
		if(itemAt(event->pos())->flags() & Qt::ItemIsEditable)
		{
			slot_GridShowMenu(event->pos());
		}
	}
	}
	else
	{
		QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
		QApplication::postEvent(this,pEvent);
		QExBaseListGridBase::mousePressEvent(event);
	}
}

long QGradientGroupGrid::GetRow(long nCol, CString strName)
{
	long nRows = rowCount();
	for (int i = 0; i < nRows; i++)
	{
		QTableWidgetItem* pItem = item(i, nCol);
		if(pItem->text() == strName)
		{
			return i;
		}
	}
	return -1;
}

long QGradientGroupGrid::GetColumn(long nRow, CString strName)
{
	long nCols = columnCount();
	for (int i = 0; i < nCols; i++)
	{
		QTableWidgetItem* pItem = itemAt(nRow, i);
		if(pItem->text() == strName)
		{
			return i;
		}
	}
	return -1;
}

void QGradientGroupGrid::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if ((currentRow >= 0))
	{
		OnDataSelChanged(currentRow,currentColumn);
	}
}

void QGradientGroupGrid::focusOutEvent(QFocusEvent *event)
{
	DisableSystemMenu();
}

void QGradientGroupGrid::slot_GridShowMenu(QPoint pos)
{
	int x = pos.x(); 
	int y = pos.y(); 
	QModelIndex index = this->indexAt(QPoint(x,y)); 
	int col = index.column();

	switch(col)
	{
	case 1:
		m_MenuAmp->move(cursor().pos()); 
		m_MenuAmp->show(); 
		break;
	case 2:
		m_MenuPhase->move(cursor().pos()); 
		m_MenuPhase->show(); 
		break;
	case 3:
		m_MenuFre->move(cursor().pos()); 
		m_MenuFre->show(); 
		break;
	default:
		break;
	}
}

void QGradientGroupGrid::Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll)
{
	if (pItem == NULL)
	{
		return;
	}

	QString strVal = QString::number(fVal,'f',3);

	if (!bAll)
	{
		pItem->setText(strVal);
		return;
	}

	ASSERT(m_pChDatas);

	if (m_pChDatas->GetCount()==4)
	{
		for (int i=0;i<rowCount();i++)
		{
			item(i,1)->setText(strVal);
		}
	}
	else
	{
	int row = pItem->row();
	int imin = (int(row/3))*3;
	int imax = (int(row/3))*3 +2;
	if (imax>=rowCount())
	{
		imax = rowCount()-1;
	}
	for (int i=imin; i<=imax;i++)
	{
		if(item(i,1)->flags() & Qt::ItemIsEditable)
		{
			item(i,1)->setText(strVal);
		}
	}
	}

	
}

void QGradientGroupGrid::Act_setPrasePValue(int nSwitch,int nOffset,float fv)
{
	float fVal1 = 0,fVal2 = 0;
	long nMaxCount = rowCount();

	switch(nSwitch)
	{
	case 0:
		fVal1 = fv-120;
		fVal2 = fv+120;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if ((nOffset+2)<nMaxCount)
		{
			if(item(nOffset+1,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+1,2)->setText(QString::number(fVal1,'f',1));
			}
			if(item(nOffset+2,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+2,2)->setText(QString::number(fVal2,'f',1));
			}
		}
		else if ((nOffset+1)<nMaxCount)
		{
			if(item(nOffset+1,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+1,2)->setText(QString::number(fVal1,'f',1));
			}
		}

		break;
	case 1:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if(item(nOffset,2)->flags() & Qt::ItemIsEditable)
		{
			item(nOffset,2)->setText(QString::number(fVal1,'f',1));
		}
		
		if ((nOffset+2)<nMaxCount)
		{
			if(item(nOffset+2,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+2,2)->setText(QString::number(fVal2,'f',1));
			}
		}

		break;
	case 2:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		if(item(nOffset,2)->flags() & Qt::ItemIsEditable)
		{
			item(nOffset,2)->setText(QString::number(fVal1,'f',1));
		}
		if(item(nOffset+1,2)->flags() & Qt::ItemIsEditable)
		{
			item(nOffset+1,2)->setText(QString::number(fVal2,'f',1));
		}
		break;
	default:
		break;
	}
}

void QGradientGroupGrid::Act_setPraseNValue(int nSwitch,int nOffset,float fv)
{
	float fVal1 = 0,fVal2 = 0;
	long nMaxCount = rowCount();

	switch(nSwitch)
	{
	case 0:
		fVal1 = fv+120;
		fVal2 = fv-120;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);

		if ((nOffset+2)<nMaxCount)
		{
			if(item(nOffset+1,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+1,2)->setText(QString::number(fVal1,'f',1));
			}

			if(item(nOffset+2,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+2,2)->setText(QString::number(fVal2,'f',1));
			}
		}
		else if ((nOffset+1)<nMaxCount)
		{
			if(item(nOffset+1,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+1,2)->setText(QString::number(fVal1,'f',1));
			}
		}

		break;
	case 1:
		fVal1 = fv-120;
		fVal2 = fv-240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		if(item(nOffset,2)->flags() & Qt::ItemIsEditable)
		{
			item(nOffset,2)->setText(QString::number(fVal1,'f',1));
		}

		if ((nOffset+2)<nMaxCount)
		{
			if(item(nOffset+2,2)->flags() & Qt::ItemIsEditable)
			{
				item(nOffset+2,2)->setText(QString::number(fVal2,'f',1));
			}
		}

		break;
	case 2:
		fVal1 = fv+120;
		fVal2 = fv+240;
		LimitAngle180(fVal1);
		LimitAngle180(fVal2);
		if(item(nOffset,2)->flags() & Qt::ItemIsEditable)
		{
			item(nOffset,2)->setText(QString::number(fVal1,'f',1));
		}

		if(item(nOffset+1,2)->flags() & Qt::ItemIsEditable)
		{
			item(nOffset+1,2)->setText(QString::number(fVal2,'f',1));
		}
		break;
	default:
		break;
	}
}

void QGradientGroupGrid::Act_setPraseZValue(int nStart,int nEnd)
{
	QString strVal = QString::number(0,'f',1);
	long nMaxCount = rowCount();

	if (nEnd>=nMaxCount)
	{
		nEnd = (nMaxCount-1);
	}

	for (int i=nStart; i<=nEnd; i++)
	{
		if(item(i,2)->flags() & Qt::ItemIsEditable)
		{
			item(i,2)->setText(strVal);
		}
	}
}

void QGradientGroupGrid::Act_setHzEqualValue(int nStart,int nEnd,float fv)
{
	QString strVal = QString::number(fv,'f',3);

	for (int i=nStart; i<=nEnd; i++)
	{
		item(i,3)->setText(strVal);
	}
}

void QGradientGroupGrid::slot_ActUAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		Act_setUIAmpValue(pItem,m_fEDVal / SQRT3,FALSE);
	}
}

void QGradientGroupGrid::slot_ActPerUAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		float fEDVal = m_fEDVal / SQRT3;
		QAction* pAction = (QAction*)sender();
		if(pAction->text().indexOf("120%") != -1)
		{
			fEDVal *= 1.2;
		}
		else if (pAction->text().indexOf("80%") != -1)
		{
			fEDVal *= 0.8;
		}
		else if (pAction->text().indexOf("60%") != -1)
		{
			fEDVal *= 0.6;
		}
		else if (pAction->text().indexOf("40%") != -1)
		{
			fEDVal *= 0.4;
		}
		else if (pAction->text().indexOf("20%") != -1)
		{
			fEDVal *= 0.2;
		}

		Act_setUIAmpValue(pItem,fEDVal,FALSE);
	}
}

void QGradientGroupGrid::slot_ActUZeroClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setText(QString::number(0,'f',3));
	}
}
void QGradientGroupGrid::slot_ActUEqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		float fVal = pItem->text().toFloat();
		Act_setUIAmpValue(pItem,fVal);
	}
}

void QGradientGroupGrid::slot_ActIAmp1Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setText(QString::number(1,'f',3));
	}
}

void QGradientGroupGrid::slot_ActIAmp5Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setText(QString::number(5,'f',3));
	}
}

void QGradientGroupGrid::slot_ActIAmp0Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setText(QString::number(0,'f',3));
	}
}

void QGradientGroupGrid::slot_ActIqualAmpClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		float fVal = pItem->text().toFloat();
		Act_setUIAmpValue(pItem,fVal);
	}
}

void QGradientGroupGrid::slot_ActIAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		Act_setUIAmpValue(pItem,m_fEDVal,FALSE);
	}
}

void QGradientGroupGrid::slot_ActPerIAmpEDClicked()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		float fEDVal = m_fEDVal;
		QAction* pAction = (QAction*)sender();
		if (pAction->text().indexOf("120%") != -1)
		{
			fEDVal *= 1.2;
		}
		else if (pAction->text().indexOf("80%") != -1)
		{
			fEDVal *= 0.8;
		}
		else if (pAction->text().indexOf("60%") != -1)
		{
			fEDVal *= 0.6;
		}
		else if (pAction->text().indexOf("40%") != -1)
		{
			fEDVal *= 0.4;
		}
		else if (pAction->text().indexOf("20%") != -1)
		{
			fEDVal *= 0.2;
		}

		Act_setUIAmpValue(pItem, fEDVal, FALSE);
	}
}

void QGradientGroupGrid::slot_ActPhasePClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		int row = pItem->row();
		float fv = pItem->text().toFloat();
		ASSERT(m_pChDatas);

		if (m_moudleType==Moudle_U)	//uc~N^1"Alb?é
		{
			if (m_pChDatas->GetCount()==4)
			{
				Act_setPrasePValue(row,0,fv);
			}
			else
			{
			int imin = (int(row/3))*3;
			Act_setPrasePValue(row%3,imin,fv);
		}
		
		}
		else				//uc'A÷"Alb?é
		{
			int imin = (int(row/3))*3;
			Act_setPrasePValue(row%3,imin,fv);
		}
	}
}

void QGradientGroupGrid::slot_ActPhaseNClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		int row = pItem->row();
		float fv = pItem->text().toFloat();
		ASSERT(m_pChDatas);

		if (m_moudleType==Moudle_U)
		{
			if (m_pChDatas->GetCount()==4)
			{
				Act_setPraseNValue(row,0,fv);
			}
			else
			{
			int imin = (int(row/3))*3;
			Act_setPraseNValue(row%3,imin,fv);
		}

		}
		else
		{
			int imin = (int(row/3))*3;
			Act_setPraseNValue(row%3,imin,fv);
		}
	}
}

void QGradientGroupGrid::slot_ActPhaseZClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		int row = pItem->row();
		ASSERT(m_pChDatas);

		if (m_moudleType==Moudle_U)//uc~N^1"Alb?é
		{
			if (m_pChDatas->GetCount()==4)
			{
				Act_setPraseZValue(0,3);
			}
			else
			{
			int imin = (int(row/3))*3;
			Act_setPraseZValue(imin,imin+2);
		}
		}
		else
		{
			int imin = (int(row/3))*3;
			Act_setPraseZValue(imin,imin+2);
		}
	}
}

void QGradientGroupGrid::slot_ActHz50Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setText(QString::number(50,'f',3));
	}
}

void QGradientGroupGrid::slot_ActHz60Clicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setText(QString::number(60,'f',3));
	}
}

void QGradientGroupGrid::slot_ActHzEqualClicked()
{
	QTableWidgetItem *pItem = this->currentItem();
	if (pItem && (pItem->flags() & Qt::ItemIsEditable))
	{
		ASSERT(m_pChDatas);
		int row = pItem->row();
		float fv = pItem->text().toFloat();

		if (m_pChDatas->GetCount()==4)
		{
			Act_setHzEqualValue(0,3,fv);
		}
		else
		{
		int imin = (int(row/3))*3;
		int imax = imin +2;
		Act_setHzEqualValue(imin,imax,fv);
	}
	}
}
void QGradientGroupGrid::EndEditCell_Value_Float(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
//	QExBaseListGridBase::EndEditCell_Value(nRow, nCol, pCell,pGrid);
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	float fValue =  math_GetValueFromString(pCell->text());
	CString strTmp;
	//		float fValue = math_GetValueFromString(pCell->szText);

// 	if (fabs(fValue-*(pVCellData->pfValue) ) > 0.00001)
// 	{
// 		*(pVCellData->pfValue) = fValue;
// 		long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;
// 
// 		if (nPrecision > 0 )
// 		{
// 			CString strFormat;
// 			strFormat.Format(_T("%%.%df"), nPrecision);
// 			strTmp.Format(strFormat.GetString(), *(pVCellData->pfValue));
// 			pCell->setText(strTmp);
// 		}
// 		else
// 		{
// 			math_GetStringFromValue(strTmp, *(pVCellData->pfValue), _T(""), pCell->dwValue);
// 			pCell->setText(strTmp);
// 		}
// 
// 		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// 	}

	
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	CString strFormat;
	int nPrecision=3;
	strFormat.Format(_T("%%.%df"), nPrecision);
	strTmp.Format(strFormat.GetString(), *(pVCellData->pfValue));

	if (nCol==1)//20230823 gyp 对幅值的输入限制
	{
		if (pVCellData->pObj == NULL)
		{
			return;
		}

		QGradientGroupData* pGroupData  = (QGradientGroupData*)pVCellData->pObj;

		if(fValue<0)
		{
			fValue = 0;
		}

		if (pGroupData->m_strName.Find("U")>=0)					
		{			
			if (fValue > fAcVMax)
			{
				fValue = fAcVMax;
				
			}
		}
		else if(pGroupData->m_strName.Find("I")>=0)
		{
			if (fabs(fValue) > fAcIMax)
			{
				fValue = fAcIMax;
			}
		}

		*(pVCellData->pfValue) = fValue;
	}				
	else if (nCol==2)//20230823 gyp 对相位（-9999~9999）的360°以内的转换
	{	
		if ((fValue>=-9999)&& (fValue<=9999))
		{
			float f1 =fValue - (int)fValue;	
			int f2 = ((int)fValue)%360;
			*(pVCellData->pfValue) = f1+f2;			
		}
		else
		{
			*(pVCellData->pfValue) = 0;
		}

		int temp = (int)(*(pVCellData->pfValue)*10)%10;
		if (temp == 9 ||temp == -9)
		{
			*(pVCellData->pfValue) = (int)*(pVCellData->pfValue)+temp*0.1;
		}			
	}	
	else if (nCol==3)//20230823 gyp 对频率的输入限制
	{
//		strTmp.Format(strFormat.GetString(), *(pVCellData->pfValue));	
		if (fValue- Global_GetMaxFreq() > 0)
		{
			QString str1 =  QString("%1").arg(Global_GetMaxFreq());
			*(pVCellData->pfValue) = str1.toFloat();
		}
		else if (fValue<0)
		{
			*(pVCellData->pfValue) = 0;
		}
		else
		{
//			QString str1 = strTmp;
			*(pVCellData->pfValue) = fValue;
		}	
	}
	else
		return;

	strTmp.Format(strFormat.GetString(), *(pVCellData->pfValue));								
	pCell->setText(strTmp);

	((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void QGradientGroupGrid::slot_UpdataVamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActUEqualAmpClicked();

}


void QGradientGroupGrid::slot_UpdataIamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActIqualAmpClicked();
}

void QGradientGroupGrid::slot_UpdataZX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActPhasePClicked();
}

void QGradientGroupGrid::slot_UpdataFX(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);
	slot_ActPhaseNClicked();
}

void QGradientGroupGrid::slot_UpdataLX()
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText("0");
	slot_ActPhaseZClicked();

}

void QGradientGroupGrid::slot_UpdataHzamp(QString strValue)
{
	QTableWidgetItem *pItem = this->currentItem();

	if (pItem == NULL)
	{
		return;
	}

	pItem->setText(strValue);

	slot_ActHzEqualClicked();
}
