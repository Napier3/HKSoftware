#include "channellowstable.h"

CHannelLowSTable::CHannelLowSTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent)
:CHannelTable(moudleType,pChList,pArrUI,parent)
{
	m_moudleChannelNum = 0;
}

CHannelLowSTable::~CHannelLowSTable()
{
}

void CHannelLowSTable::setAmpMaxMinValueZero(float fmax,float fmin)
{	
	m_fAmpMaxZero = fmax;
	m_fAmpMinZero = fmin;
}

QString CHannelLowSTable::initMaxAcV(int row,QString str)
{
	float fv = str.toFloat();

	if (m_pChDatas->GetCount()<=4)
	{
		if(row<3)
		{
			if (fv - m_fAmpMax > 0)
			{
				return QString("%1").arg(m_fAmpMax);
			}
			else
			{
				return str;
			}
		}
		else
		{
			if (fv - m_fAmpMaxZero > 0)
			{
				return QString("%1").arg(m_fAmpMaxZero);
			}
			else
			{
				return str;
			}
		}
	}
	else
	{
		if (fv - m_fAmpMax > 0)
		{
			return QString("%1").arg(m_fAmpMax);
		}
		else
		{
			return str;
		}
	}
}

QString CHannelLowSTable::initMaxAcI(int row,QString str)
{
	float fv = str.toFloat();
	if (m_pChDatas->GetCount()<=4)
	{
		if(row<3)
		{
			if (fv-m_fAmpMax > 0)
			{
				return QString("%1").arg(m_fAmpMax);
			}
			else
			{
				return str;
			}
		}
		else
		{
			if (fv-m_fAmpMaxZero > 0)
			{
				return QString("%1").arg(m_fAmpMaxZero);
			}
			else
			{
				return str;
			}
		}
	}
	else
	{
		if (fv-m_fAmpMax > 0)
		{
			return QString("%1").arg(m_fAmpMax);
		}
		else
		{
			return str;
		}
	}
}

QString CHannelLowSTable::initMaxHz(QString str)
{
	float fv = fabs(str.toFloat()- MAXHZ);
	if (str.toFloat()- MAXHZ > 0)
	{
		return QString("%1").arg(MAXHZ);
	}
	else
	{
		return str;
	}
}

void CHannelLowSTable::slot_OnCellChanged(int row,int col)
{
	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));
	QTableWidgetItem  *pItem  = this->item(row,col);
	QString str = pItem->text();
	QString strInfo;
	float fv;
	QString strText;
	bool bChg = false;

	switch (col)
	{
	case 1:
		{
			fv = str.toFloat();
			if (m_bDCTest)
			{
				if (fabs(fv) > m_fAmpMax)
				{
					if (fv > 0)
					{
						fv = m_fAmpMax;
					}
					else
					{
						fv = -m_fAmpMax;
					}
				}
				else if (fv<=m_fAmpMin)
				{
					fv = m_fAmpMin;
				}
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{	
				if (isPosiDigitstr(str))
				{
					str = initMaxAcV(row,str);
					fv = str.toFloat();
					pItem->setText(QString::number(fv,'f',3));
				}
				else
				{
					fv = m_pArrUI[row].Harm[1].fAmp;
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
			}

			if(m_pArrUI[row].Harm[1].fAmp != fv)
			{
				m_pArrUI[row].Harm[1].fAmp = fv;
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

			if(m_pArrUI[row].Harm[1].fAngle != fv)
			{
				m_pArrUI[row].Harm[1].fAngle = fv;
				bChg = true;
			}
		}
		break;
	case 3:
		{
			if (isPosiDigitstr(str))
			{
				str = initMaxHz(str);
				fv = str.toFloat();
				if (m_bDCTest)
				{
					if (fv < 0)
					{
						fv = 0;
					}
				}
				else
				{
					if (fv < 0.001)
					{
						fv = 0;
					}
				}
				
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}
			else
			{
				fv = m_pArrUI[row].Harm[1].fFreq;
				strText.setNum(fv,'f',3);
				pItem->setText(strText);
			}

			if(m_pArrUI[row].Harm[1].fFreq != fv)
			{
				m_pArrUI[row].Harm[1].fFreq = fv;
				bChg = true;
			}
		}
		break;
	default:
		break;
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);

	if (col > 0 && bChg)
	{
		emit sig_ChannelValueChanged(m_moudleType,/*m_moudleID,*/row,col,fv);//valueFlag=（1:幅值 2:相位 3:频率）
	}
}
