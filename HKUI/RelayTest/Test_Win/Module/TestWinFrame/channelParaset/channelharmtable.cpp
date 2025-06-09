#include "channelharmtable.h"
#include <QFontMetrics>
#include <QScrollBar>
#include <cmath>
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"


#define GenHao3	1.7320508 //根号三

CHannelHarmTable::CHannelHarmTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent)
	: CHannelTable(moudleType,pChList,pArrUI,parent)
{
	
}

CHannelHarmTable::~CHannelHarmTable()
{

}

void CHannelHarmTable::setColumnNum(int num)
{
	initTable();
}

QString CHannelHarmTable::getHarmString(int nHarmCount)
{
	QString strHarm;
	if (nHarmCount < 1 || (nHarmCount == 1 && !m_bDCTest))
	{
		strHarm = tr("——");
	}
	else if(nHarmCount == 1 && m_bDCTest)
	{
		strHarm = /*tr("基波")*/g_sLangTxt_Native_Fundamental;
	}
	else
	{
		strHarm = QString::number(nHarmCount,10) + /*tr("次谐波")*/g_sLangTxt_State_HarmCount;
	}

	return strHarm;
}

int CHannelHarmTable::getHarmCount(QString strHarmDesc)
{
	int nHarmCount = 0;

	if (strHarmDesc == tr("——"))
	{
		nHarmCount = 0; 
	}
	else if (strHarmDesc == /*tr("基波")*/g_sLangTxt_Native_Fundamental)
	{
		nHarmCount = 1;
	}
	else
	{
		int pos = strHarmDesc.indexOf(/*tr("次谐波")*/g_sLangTxt_State_HarmCount);
		nHarmCount = strHarmDesc.left(pos).toInt();
	}

	return nHarmCount;
}

void CHannelHarmTable::setProperty(bool bDCTest)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	m_bDCTest = bDCTest;

	setComboxHarmDelegate();
	UpdateTable();

	int nHarmCount = 0;
	if (m_bDCTest)
	{
		for (int i=0;i<rowCount();i++)
		{
			m_pArrUI[i].Harm[nHarmCount].bDC = 1;
		}
	}
	else
	{
		for (int i=0;i<rowCount();i++)
		{
			m_pArrUI[i].Harm[nHarmCount].bDC = 0;
		}
	}
	
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void CHannelHarmTable::setItemValue(int row,int col,float fv)
{
	if (row<rowCount()&&col<columnCount())
	{
		if (col>0&&col<columnCount())
		{
			if (col==1)
			{
				item(row,col)->setText(QString::number(fv,'f',3));
			}
			else if (col==2)
			{
				item(row,col)->setText(QString::number(fv,'f',2));//zhouhj相位精度改为2位  20220901
			}
			else if (col==3)
			{
				int nHarmCount = getHarmSelectedCount(&m_pArrUI[row]);
				item(row,col)->setText(getHarmString(nHarmCount));
			}
		}
	}
}

void CHannelHarmTable::setComboxHarmDelegate()
{
	CComboBoxHarmDelegate* comboBox = new CComboBoxHarmDelegate(m_bDCTest);
	setItemDelegateForColumn(3,comboBox);
	connect(comboBox,SIGNAL(commitData(QWidget*)),this,SLOT(slot_HarmCountChanged(QWidget*)));
}

void CHannelHarmTable::initTable()
{
	ASSERT(m_pChDatas);
	setRowCount(m_pChDatas->GetCount());
	setColumnCount(4);

	QStringList headers;
	if (m_moudleType==Moudle_U)//U
	{
		headers<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(V)")*/g_sLangTxt_Native_amplitudeV<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("谐波设置")*/g_sLangTxt_Harm_Set;
	}
	else
	{
		headers<</*tr("通道")*/g_sLangTxt_Native_Channel<</*tr("幅值(A)")*/g_sLangTxt_Native_amplitudeA<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("谐波设置")*/g_sLangTxt_Harm_Set;
	}
	
	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(/*tr("通道")*/g_sLangTxt_Native_Channel) + 10;
	int nLabelWidth2 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth3 = fontMetrics.width(/*tr("相位(°))")*/g_sLangTxt_Gradient_DPhase) + 10;
	int nLabelWidth4 = fontMetrics.width(/*tr("谐波设置)")*/g_sLangTxt_Harm_Set) + 10 ;

	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);
/*
	CComboBoxHarmDelegate* comboBox = new CComboBoxHarmDelegate(m_bDCTest);
	setItemDelegateForColumn(3,comboBox);
	connect(comboBox,SIGNAL(commitData(QWidget*)),this,SLOT(slot_HarmCountChanged(QWidget*)));
*/
	setComboxHarmDelegate();

	this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	setHorizontalHeaderLabels(headers);
	setIconSize(QSize(20,20));

	for (int row=0;row<this->rowCount();row++)
	{
		for (int col=0;col<this->columnCount();col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			
			if(row==0 && col==0)
			{
				m_Originalflags = item->flags();
			}

			if (col == 0)
			{
				if(m_MacroType == MACROTYPE_State)
				{
					item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
				}
				else if (m_MacroType == MACROTYPE_Manual)
				{
					item->setFlags(Qt::NoItemFlags);
				}
			}
			if (col == 3)
			{
				item->setIcon(QPixmap("./images/add-line_vertical.png"));
			}
			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}
	
	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	
	setFixedHeight(ntableHight);
	creatTableMenu();
}

int CHannelHarmTable::getHarmSelectedCount(tmt_channel *pCh)
{
	if (pCh == NULL)
	{
		return 0;
	}

	for (int j=1;j<MAX_HARM_COUNT;j++)
	{
		if(pCh->Harm[j].m_bSelect)
		{
			return j;
		}
	}

	pCh->Harm[0].m_bSelect = true;
	return 0;
}

void CHannelHarmTable::UpdateTable()
{
	ASSERT(m_pChDatas);
	POS pos = m_pChDatas->GetHeadPosition();
// 	CExBaseObject *pCh = NULL;
	CSttChResource *pCh = NULL;
	long nChIndex = 0;
	int nHarmCount = 0;

	while(pos)
	{
		pCh = (CSttChResource *)m_pChDatas->GetNext(pos);
		nHarmCount = getHarmSelectedCount(&m_pArrUI[nChIndex]);
		if(nHarmCount == 1 && !m_bDCTest)
		{
			nHarmCount = 0;
			for (int j=1;j<=MAX_HARM_COUNT;j++)
			{
				m_pArrUI[nChIndex].Harm[j].m_bSelect = false;
			}

			m_pArrUI[nChIndex].Harm[nHarmCount].m_bSelect = true;
		}
		item(nChIndex,0)->setText(pCh->m_strName);
		item(nChIndex,1)->setText(QString::number(m_pArrUI[nChIndex].Harm[nHarmCount].fAmp,'f',3));
		item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[nHarmCount].fAngle,'f',2));//zhouhj相位精度改为2位  20220901
		item(nChIndex,3)->setText(getHarmString(nHarmCount));
		
		if (nHarmCount >= 1)
		{
			UpdateHarmCell(nChIndex,true);
		}
		else
		{
			UpdateHarmCell(nChIndex,false);
		}

		if((m_MacroType == MACROTYPE_State)|| (m_MacroType == MACROTYPE_Manual))
		{
			if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
			{
				item(nChIndex,0)->setIcon(QPixmap("./images/gradual.png"));
			}
			else
			{
// 				if (g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap("./images/analog.png"));
// 				}
// 				else if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap("./images/digital.png"));
// 				}
// 				else if (g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap("./images/mix.png"));
// 				}

				if (pCh->m_nHasMapType == 1)
				{
					item(nChIndex,0)->setIcon(QPixmap("./images/analog.png"));
				}
				else if (pCh->m_nHasMapType == 2)
				{
					item(nChIndex,0)->setIcon(QPixmap("./images/digital.png"));
				}
				else if (pCh->m_nHasMapType == 4)
				{
					item(nChIndex,0)->setIcon(QPixmap("./images/mix.png"));
				}
			}
		}
		
		nChIndex++;
	}

	changeTableColor();
}

void CHannelHarmTable::UpdateHarmCell(int row,bool bEnable)
{
	if (row < 0 || row >= m_pChDatas->GetCount())
	{
		return;
	}

	if(bEnable)
	{
		item(row,1)->setFlags(item(row,3)->flags());
		item(row,1)->setBackground(item(row,3)->background());

		item(row,2)->setFlags(item(row,3)->flags());
		item(row,2)->setBackground(item(row,3)->background());
	}
	else
	{
		item(row,1)->setFlags(Qt::NoItemFlags);
		item(row,1)->setBackground(Qt::gray);

		item(row,2)->setFlags(Qt::NoItemFlags);
		item(row,2)->setBackground(Qt::gray);
	}
}

bool CHannelHarmTable::IsHarmBaseAddValid(int row,int col,int nHarmCount,float fv)
{
	ASSERT(!m_bDCTest);
	ASSERT( row>=0 && row<=rowCount()-1 && col==1);

	bool bRet = true;

	float fTotal = m_pArrUI[row].Harm[1].fAmp*m_pArrUI[row].Harm[1].fAmp; //基波的平方
	if(nHarmCount>=2)
	{
		fTotal += fv*fv;  //高次谐波的平方
	}

	fTotal = sqrt(fTotal);

	if(m_moudleType == Moudle_U && fTotal > g_oLocalSysPara.m_fAC_VolMax)
	{
		bRet = false;
	}
	else if(m_moudleType == Moudle_I && fTotal > g_oLocalSysPara.m_fAC_CurMax)
	{
		bRet = false;
	}

	return bRet;
}

void CHannelHarmTable::slot_OnCellChanged(int row,int col)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;
	int nHarmCount = getHarmSelectedCount(&m_pArrUI[row]);

	switch (col)
	{
	case 1:
		{
			fv = str.toFloat();
			if (isPosiDigitstr(str))
			{
				str = initMaxAcV(str);
				fv = str.toFloat();
				if(!IsHarmBaseAddValid(row,col,nHarmCount,fv))
				{
					if (m_moudleType == Moudle_U)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("谐波设置值%f(%d,%d)与基波的叠加超出范围(%fV).")*/g_sLangTxt_Native_overflowV.GetString(),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
					}
					else
					{
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("谐波设置值%f(%d,%d)与基波的叠加超出范围(%fA).")*/g_sLangTxt_Native_overflowA.GetString(),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
					}

					fv = m_pArrUI[row].Harm[nHarmCount].fAmp;
				}
					
				pItem->setText(QString::number(fv,'f',3));
			}
			else
			{
				fv = m_pArrUI[row].Harm[nHarmCount].fAmp;
				if (fv > m_fAmpMax)
				{
					fv = m_fAmpMax;
				}
				if (fv < m_fAmpMin)
				{
					fv = m_fAmpMin;
				}

				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(m_pArrUI[row].Harm[nHarmCount].fAmp != fv)
			{
				m_pArrUI[row].Harm[nHarmCount].fAmp = fv;
				bChg = true;
			}
		}
		break;
	case 2:
		{
			fv = str.toFloat();
			float f1 = fv - (int)fv;
			int f2 = ((int)fv)%360;
			fv = f1+f2;
			int temp = (int)(fv*10)%10;
			if (temp == 9 ||temp == -9)
			{
				fv = (int)fv+temp*0.1;
			}
			strText.setNum(fv,'f',2);//zhouhj相位精度改为2位  20220901
			pItem->setText(strText);

			if(m_pArrUI[row].Harm[nHarmCount].fAngle != fv)
			{
				m_pArrUI[row].Harm[nHarmCount].fAngle = fv;
				bChg = true;
			}
		}
		break;
	case 3:
		{
			if (str.contains("—"))
			{
				this->item(row, 0)->setFlags(Qt::NoItemFlags);
			}
			else if (str.contains(g_sLangTxt_State_HarmCount))
			{
				this->item(row, 0)->setFlags(Qt::ItemIsEnabled);
			}
// 			this->item(row, col)->setIcon(QPixmap("./images/add-line_vertical.png"));


		}
		break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	if (col > 0 && bChg)
	{
		emit sig_ChannelValueChanged(m_moudleType,row,col,fv);//valueFlag=（1:幅值 2:相位 3:谐波次数）
	}
}

void CHannelHarmTable::slot_HarmCountChanged(QWidget* editor)
{
	if (editor == NULL)
	{
		return;
	}

	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	int nHarmCount = getHarmCount(comboBox->currentText());
    int nRow = currentRow();

	for (int j=0;j<=MAX_HARM_COUNT;j++)
	{
		m_pArrUI[nRow].Harm[j].m_bSelect = false;
	}

	m_pArrUI[nRow].Harm[nHarmCount].m_bSelect = true;

	UpdateTable();
}

void CHannelHarmTable::slot_TableShowMent(QPoint pos)
{
	//获得鼠标点击的x，y坐标点 
	int x = pos.x(); 
	int y = pos.y(); 
	QModelIndex index = this->indexAt(QPoint(x,y)); 
	int col = index.column();//获得QTableWidget列表点击的行数 

	switch(col)
	{
	case 1:
		{
			m_MenuAmp->move(cursor().pos()); 
			m_MenuAmp->show(); 
		}
		break;
	case 2:
		{
			int row = index.row();
			ASSERT(m_pChDatas);

			if((m_pChDatas->GetCount() != 4) || (row != 3))
			{
				m_MenuPhase->move(cursor().pos()); 
				m_MenuPhase->show(); 
			}	
		}
		break;
	case 3:
		{
			m_MenuFre->move(cursor().pos()); 
			m_MenuFre->show(); 
		}
		break;
	default:
		break;
	}
}

void CHannelHarmTable::UpdateValidTableDatas()
{
	for (int i=0;i<rowCount();i++)
	{
		for (int j=0;j<columnCount();j++)
		{
			slot_OnCellChanged(i,j);
		}
	}
}

CComboBoxHarmDelegate::CComboBoxHarmDelegate(bool bDC,QObject *parent): QItemDelegate(parent)
{
	m_bDC = bDC;
}

CComboBoxHarmDelegate::~CComboBoxHarmDelegate()
{

}

QWidget *CComboBoxHarmDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
										 const QModelIndex &index) const
{
	QVariant variant = index.data();

	QComboBox *comboBox = new QComboBox(parent);
	return comboBox;
}

void CComboBoxHarmDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;

	QString strHarm;
	strHarm = tr("——");
	strItemList<<strHarm;

	if (m_bDC)
	{
		strHarm = /*tr("基波")*/g_sLangTxt_Native_Fundamental;
		strItemList<<strHarm;
	}

	for(int i=2;i<=31;i++)
	{
		strHarm = QString::number(i,10)+/*tr("次谐波")*/g_sLangTxt_State_HarmCount;
		strItemList<<strHarm;
	}

	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	comboBox->clear();
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (strValue == strItem)
		{
			id = i;
		}
		comboBox->addItem(strValue);
	}
	comboBox->setCurrentIndex(id);
}

void CComboBoxHarmDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									 const QModelIndex &index) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	model->setData(index,comboBox->currentText(),Qt::EditRole);
}

void CComboBoxHarmDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											 const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}
void CComboBoxHarmDelegate ::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const 
{
	// 调用父类的paint方法绘制默认内容
//	QItemDelegate::paint(painter, option, index);

	QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
	QString text = index.data(Qt::DisplayRole).toString();

	QFontMetrics fontMetrics(option.font);
	int iconWidth = icon.actualSize(option.rect.size()).width();
	int iconHeight = icon.actualSize(option.rect.size()).height();
	int textWidth = fontMetrics.width(text);

	int iconX = option.rect.x() + option.rect.width() - iconWidth;
	int iconY = option.rect.y()  + option.rect.height() - iconHeight*2;
	int textX = option.rect.x() + option.rect.width()/2 - textWidth/2;
 
	painter->drawText(textX, option.rect.y(), textWidth, option.rect.height(), Qt::AlignCenter | Qt::AlignVCenter, text);
	painter->drawPixmap(iconX, iconY, icon.pixmap(option.rect.size()));
};