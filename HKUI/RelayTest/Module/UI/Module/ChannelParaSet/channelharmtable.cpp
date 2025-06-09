#include "channelharmtable.h"
#include <QFontMetrics>
#include <QLineEdit>
#include <QScrollBar>
#include <cmath>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../SttTestSysGlobalPara.h"
#include "../ScrollCtrl/ScrollComboBox.h"
#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

#include <QProxyStyle>

//#define GenHao3	1.7320508 //根号三

QChannelHarmTable::QChannelHarmTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent)
	: QChannelTable(moudleType,pChList,pArrUI,parent)
{
	m_pCurrKeyboardItem = NULL;
	m_pComboBoxHarmDelegate = NULL;

}

QChannelHarmTable::~QChannelHarmTable()
{

}

QString QChannelHarmTable::getHarmString(int nHarmCount)
{
	CString strHarm;
	CString strHarmCount;
	xlang_GetLangStrByFile(strHarmCount, "State_HarmCount");

	if (nHarmCount < 1 || (nHarmCount == 1 && !m_bDC))
	{
		strHarm = CString("----");
	}
	else if (nHarmCount == 1 && m_bDC)
	{
		CString strBaseHarm;
		xlang_GetLangStrByFile(strBaseHarm, "Native_Fundamental");
		strHarm = strBaseHarm;
	}
	else
	{
		if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
//			strHarm.Format("%d次谐波",nHarmCount);
			strHarm.Format(_T("%d"),nHarmCount);
			strHarm += strHarmCount;			
		}
		else
		{
			strHarm.Format("Harm %d",nHarmCount);
		}
	}

	return strHarm;
}

int QChannelHarmTable::getHarmCount(CString strHarmDesc)
{
	int nHarmCount = 0;

	CString szHarmDesc = strHarmDesc;
	CString strHarmCount;
	xlang_GetLangStrByFile(strHarmCount, "State_HarmCount");

	CString strBaseHarm;
	xlang_GetLangStrByFile(strBaseHarm, "Native_Fundamental");

	if (strHarmDesc == QString("----"))
	{
		nHarmCount = 0; 
	}
	else if (strHarmDesc == strBaseHarm)
	{
		nHarmCount = 1; 
	}
	else
	{
		if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
//			int pos = strHarmDesc.indexOf(QString::fromLocal8Bit("次谐波"));
			int pos = szHarmDesc.Find(strHarmCount);
			nHarmCount = szHarmDesc.left(pos).toInt();
		}
		else
		{
			nHarmCount = strHarmDesc.mid(5).toInt();
		}
	}

	return nHarmCount;
}

void QChannelHarmTable::setProperty(bool bDC)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)));

	if (m_pComboBoxHarmDelegate != NULL)
	{
		disconnect(m_pComboBoxHarmDelegate,SIGNAL(commitData(QWidget*)),this,SLOT(slot_HarmCountChanged(QWidget*)));
	}

	m_bDC = bDC;
	setComboxHarmDelegate();

	int nHarmCount = 0;
	if (m_bDC)
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
	
	connect(m_pComboBoxHarmDelegate,SIGNAL(commitData(QWidget*)),this,SLOT(slot_HarmCountChanged(QWidget*)),Qt::UniqueConnection);
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

void QChannelHarmTable::setItemValue(int row,int col,float fv)
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
				item(row,col)->setText(QString::number(fv,'f',1));
			}
			else if (col==3)
			{
				int nHarmCount = getHarmSelectedCount(&m_pArrUI[row]);
				item(row,col)->setText(getHarmString(nHarmCount));
			}
		}
	}
}

void QChannelHarmTable::setComboxHarmDelegate()
{

	if (m_pComboBoxHarmDelegate == NULL)
	{
		m_pComboBoxHarmDelegate = new CComboBoxHarmDelegate(m_bDC,this);
		setItemDelegateForColumn(3,m_pComboBoxHarmDelegate);
	}

//	connect(m_pComboBoxHarmDelegate,SIGNAL(commitData(QWidget*)),this,SLOT(slot_HarmCountChanged(QWidget*)));
}


void QChannelHarmTable::initTable()
{
	ASSERT(m_pChDatas);
	setRowCount(m_pChDatas->GetCount());
	setColumnCount(4);

	QStringList headers;

	CString strChannel, strAmplitude, strPhase, strHarmSet;
	xlang_GetLangStrByFile(strChannel, "Native_Channel");
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
	xlang_GetLangStrByFile(strHarmSet, "Harm_Set");

#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°)");
#else
	strPhase += "(°)";
#endif
	if (m_moudleType==Moudle_U)//U
	{
		strAmplitude += "(V)";
	}
	else
	{
		strAmplitude += "(A)";
	}
	headers << strChannel << strAmplitude << strPhase << strHarmSet;

	QFontMetrics fontMetrics = QFontMetrics(this->font());
	int nLabelWidth1 = fontMetrics.width(strChannel) + 40;
	int nLabelWidth2 = fontMetrics.width(tr("-57.735")) + 20;
	int nLabelWidth3 = fontMetrics.width(strPhase) + 10;
	int nLabelWidth4 = fontMetrics.width(strHarmSet) + 10 ;

	this->setColumnWidth(0,nLabelWidth1);
	this->setColumnWidth(1,nLabelWidth2);
	this->setColumnWidth(2,nLabelWidth3);
	this->setColumnWidth(3,nLabelWidth4);
/*
	CComboBoxHarmDelegate* comboBox = new CComboBoxHarmDelegate();
	setItemDelegateForColumn(3,comboBox);
	connect(comboBox,SIGNAL(commitData(QWidget*)),this,SLOT(slot_HarmCountChanged(QWidget*)));
*/
	setComboxHarmDelegate();

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
// #ifdef _PSX_QT_LINUX_
// 			else if (((col+1)<this->columnCount()))
// 			{
// 				item->setFlags(Qt::ItemIsEnabled);
// 			}
// #endif
			if (col == 0)
			{
				if(m_MacroType == MACROTYPE_State)
				{
//					item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
					item->setFlags(Qt::NoItemFlags);
				}
				else if (m_MacroType == MACROTYPE_Manual)
				{
					item->setFlags(Qt::NoItemFlags);
				}
				item->setTextColor(QColor(0, 0, 0));
			}

			setItem(row,col,item);
			setRowHeight(row,m_nRowHeight);
		}
	}
	
	int ntableHight = this->horizontalHeader()->height() + ((m_nRowHeight)*this->rowCount());
	
//	setFixedHeight(ntableHight);
	creatTableMenu();
}

int QChannelHarmTable::getHarmSelectedCount(tmt_channel *pCh)
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

void QChannelHarmTable::UpdateTable()
{
	ASSERT(m_pChDatas);
	POS pos = m_pChDatas->GetHeadPosition();
	//CExBaseObject *pCh = NULL;
	CSttChResource *pCh = NULL;
	long nChIndex = 0;
	int nHarmCount = 0;

	while(pos)
	{
		pCh = (CSttChResource *)m_pChDatas->GetNext(pos);
		nHarmCount = getHarmSelectedCount(&m_pArrUI[nChIndex]);
		if(nHarmCount == 1 && !m_bDC)
		{
			nHarmCount = 0;
			for (int j=1;j<=MAX_HARM_COUNT;j++)
			{
				m_pArrUI[nChIndex].Harm[j].m_bSelect = false;
			}

			m_pArrUI[nChIndex].Harm[nHarmCount].m_bSelect = true;
		}
		item(nChIndex,0)->setText(pCh->m_strName);
		
		//20240204 suyang 增加合并电流输出时 电流通道判断
		float fAmp =m_pArrUI[nChIndex].Harm[nHarmCount].fAmp;

		if (fAmp > m_fAmpMax)
		{
			fAmp= m_fAmpMax;
		}

		if (fAmp < m_fAmpMin)
		{
			fAmp = m_fAmpMin;
		}

		if (m_pArrUI[nChIndex].Harm[nHarmCount].fAmp != fAmp)
		{
			m_pArrUI[nChIndex].Harm[nHarmCount].fAmp = fAmp;
		}

		item(nChIndex,1)->setText(QString::number(m_pArrUI[nChIndex].Harm[nHarmCount].fAmp,'f',3));
		item(nChIndex,2)->setText(QString::number(m_pArrUI[nChIndex].Harm[nHarmCount].fAngle,'f',1));
		item(nChIndex,3)->setText(getHarmString(nHarmCount));

		if (nHarmCount >= 1)
		{
			UpdateHarmCell(nChIndex,true);
		}
		else
		{
			UpdateHarmCell(nChIndex,false);
		}

		if(m_MacroType == MACROTYPE_State)
		{
#ifdef _PSX_QT_WINDOWS_
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
#else
			if (m_pArrUI[nChIndex].Ramp[0].nIndex == 1 || m_pArrUI[nChIndex].Ramp[1].nIndex == 1 || m_pArrUI[nChIndex].Ramp[2].nIndex == 1)
			{
				item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/gradual.png"));
			}
			else
			{
// 				if (g_oSystemParas.m_nHasAnalog && !g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/analog.png"));
// 				}
// 				else if (!g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/digital.png"));
// 				}
// 				else if (g_oSystemParas.m_nHasAnalog && g_oSystemParas.m_nHasDigital)
// 				{
// 					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/mix.png"));
// 				}
				if (pCh->m_nHasMapType == 1)
				{
					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/analog.png"));
				}
				else if (pCh->m_nHasMapType == 2)
				{
					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/digital.png"));
				}
				else if (pCh->m_nHasMapType == 4)
				{
					item(nChIndex,0)->setIcon(QPixmap(":/ctrls/images/mix.png"));
				}
			}
#endif
		}
		
		nChIndex++;
	}

	changeTableColor();
}

void QChannelHarmTable::UpdateHarmCell(int row,bool bEnable)
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

void QChannelHarmTable::setTableData(tmt_channel *pArrUI)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	disconnect(this,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)));

 	m_pArrUI = pArrUI;
 	UpdateTable(); 

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(slot_OnItemClicked(QTableWidgetItem *)),Qt::UniqueConnection);
}

bool QChannelHarmTable::IsHarmBaseAddValid(int row,int col,int nHarmCount,float fv)
{
	ASSERT(!m_bDC);
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

void QChannelHarmTable::UpdateText(const QString &strText)
{
	if (m_pCurrKeyboardItem == NULL)
	{
		return;
	}

	long nRow = m_pCurrKeyboardItem->row();
	long nCol = m_pCurrKeyboardItem->column();
	m_pCurrKeyboardItem->setText(strText);
	slot_OnCellChanged(nRow,nCol);
}

void QChannelHarmTable::slot_OnItemClicked(QTableWidgetItem *pItem)
{
	if(!(pItem->flags() & Qt::ItemIsEnabled))
	{
		return;
	}

	int nRow = row(pItem);
	int nCol = column(pItem);

	CString strValue = pItem->text();

	long nEditType;
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
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::Attach330Channel(this, nEditType);
#endif

	m_pCurrKeyboardItem = pItem;

}

void QChannelHarmTable::slot_OnCellChanged(int row,int col)
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
						if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("谐波设置值%f(%d,%d)与基波的叠加超出范围(%fV)."),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
						}
						else
						{ 
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("The Superposition of Harmonic settin value %f(%d,%d)and fundamental wave is out of range(%fV)."),fv,row,col,g_oLocalSysPara.m_fAC_VolMax);
						}
					}
					else
					{
						if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("谐波设置值%f(%d,%d)与基波的叠加超出范围(%fA)."),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
						}
						else
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("The Superposition of Harmonic settin value %f(%d,%d)and fundamental wave is out of range(%fA)."),fv,row,col,g_oLocalSysPara.m_fAC_CurMax);
						}
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
			if (fv<=9999 && fv>=-9999)
			{
			float f1 = fv - (int)fv;
			int f2 = ((int)fv)%360;
			fv = f1+f2;
			}
			else
			{
				fv=0;
			}
			int temp = (int)(fv*10)%10;
			if (temp == 9 ||temp == -9)
			{
				fv = (int)fv+temp*0.1;
			}
			strText.setNum(fv,'f',1);
			pItem->setText(strText);

			if(m_pArrUI[row].Harm[nHarmCount].fAngle != fv)
			{
				m_pArrUI[row].Harm[nHarmCount].fAngle = fv;
				bChg = true;
			}
		}
		break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

// 	if (m_pCurrKeyboardItem != NULL)//20230112 zhouhj 目前只有状态序列谐波设置界面用到此表格,无需发送更新命令,表格内已对结构体参数内容更改
// 	{
// 		long nRow = m_pCurrKeyboardItem->row();
// 		long nCol = m_pCurrKeyboardItem->column();
// 		emit sig_ChannelValueChanged(m_moudleType,nRow,nCol, m_pCurrKeyboardItem->text().toFloat());//valueFlag=（1:幅值 2:相位 3:频率）
// 	}
}

void QChannelHarmTable::slot_HarmCountChanged(QWidget* editor)
{
	if (editor == NULL)
	{
		return;
	}

	QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
	int nHarmCount = getHarmCount(pComboBox->currentText());
    int nRow = currentRow();

	for (int j=0;j<=MAX_HARM_COUNT;j++)
	{
		m_pArrUI[nRow].Harm[j].m_bSelect = false;
	}

	m_pArrUI[nRow].Harm[nHarmCount].m_bSelect = true;

	UpdateTable();
}

void QChannelHarmTable::slot_TableShowMent(QPoint pos)
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

void QChannelHarmTable::UpdateValidTableDatas()
{
	for (int i=0;i<rowCount();i++)
	{
		for (int j=0;j<columnCount();j++)
		{
			slot_OnCellChanged(i,j);
		}
	}
}


CComboBoxHarmDelegate::CComboBoxHarmDelegate(bool bDC,QObject *parent):QItemDelegate (parent)
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

    QScrollComboBox *pComboBox = new QScrollComboBox(parent);

#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
	pComboBox->SetIgnoreFirstHidePopup(true);
#endif
	return pComboBox;

	
}


void CComboBoxHarmDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;

	CString strHarm;
	strHarm = CString("----");;
	strItemList<<strHarm;

	if (m_bDC)
	{
		CString strBaseHarm;
		xlang_GetLangStrByFile(strBaseHarm, "Native_Fundamental");
		strItemList<<strBaseHarm;
	}

	CString strHarmCount;
	xlang_GetLangStrByFile(strHarmCount, "State_HarmCount");

	for(int i=2;i<=31;i++)
	{
		if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
//			strHarm = QString::number(i,10)+QString::fromLocal8Bit("次谐波");
			strHarm.Format("%d",i);
			strHarm += strHarmCount;
		}
		else
		{
			strHarm = QString("Harm %1").arg(i);
		}

		strItemList<<strHarm;
	}

	QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox *>(editor);
	pComboBox->clear();
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (strValue == strItem)
		{
			id = i;
		}
		pComboBox->addItem(strValue);
	}
	pComboBox->setCurrentIndex(id);

	if (pComboBox->isHidden())
	{
		pComboBox->showPopup();
	}
	
}

void CComboBoxHarmDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									 const QModelIndex &index) const
{
	QComboBox *pComboBox = qobject_cast<QComboBox *>(editor);
	model->setData(index,pComboBox->currentText(),Qt::EditRole);
	
}

void CComboBoxHarmDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											 const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

// 鼠标单击单元格的时候，重绘事件触发
void CComboBoxHarmDelegate::paint(QPainter * painter,
									   const QStyleOptionViewItem & option,
									   const QModelIndex & index) const
{  
//	QTableWidgetItem* pCurItem = GetCurrItem(index);
	QProxyStyle oProxyStyle;
	QStyleOptionComboBox oStyleOptionComboBox;
	oStyleOptionComboBox.state = QStyle::State_On;
	oStyleOptionComboBox.rect = option.rect;
	QPalette oPalette;
	QChannelHarmTable *pParent = (QChannelHarmTable*)parent();

	if (pParent != NULL)
	{
		QTableWidgetItem *pTableWidgetItem = pParent->item(index.row(),index.column());

		if (pTableWidgetItem != NULL)
		{
			oStyleOptionComboBox.editable = true;
			oStyleOptionComboBox.frame = false;
			oStyleOptionComboBox.currentText = pTableWidgetItem->text();
		}
	}

	oProxyStyle.drawComplexControl(QStyle::CC_ComboBox,&oStyleOptionComboBox, painter);
	oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText);

}
