#include "vectorwidget.h"
#include <QStringList>
#include <QList>
#include <QPen>
#include "../Module/CommonMethod/Complexp.h"
#include "../Module/TestWinFrame/testwinbase.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

VectorWidget::VectorWidget(QWidget *parent)
	: Diagram(parent)
{
	m_AllGroup = 0;
	m_NeedUGroup = 0;
	m_NeedIGroup = 0;
	m_nCurrentGroup = 1;
	m_bDCTest = false;
	m_bTimeStart = FALSE;

	m_nTimerID = startTimer(500);

	m_pVOL = NULL;
	m_pCUR = NULL;
	m_pSttTestResource = NULL;

	setPbnDisp(true);
	connect(this,SIGNAL(sig_Pbn_NextClicked()),this,SLOT(slot_PbnNextClicked()));
	connect(this,SIGNAL(sig_Pbn_PreClicked()),this,SLOT(slot_PbnPreClicked()));
}

VectorWidget::~VectorWidget()
{
	m_bTimeStart = FALSE;
	killTimer(m_nTimerID);
	m_nTimerID = -1;

}

void VectorWidget::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource,int VectorType)
{
	if (pSttTestResource == NULL)
	{
		return;
	}

	m_pSttTestResource = pSttTestResource;

	int AllChanelNum=0;
	int AllUChanelNum = 0;
	int AllIChanelNum = 0;
	m_NeedUGroup = 0;
	m_NeedIGroup = 0;
	int nChannelNum = 0;
	int nVChNumOfModule = 0;
	int nIChNUmOfModule = 0;

	m_VectorType = VectorType;
	nChannelNum = m_pSttTestResource->m_oVolChRsListRef.GetCount();
		
	if (nChannelNum <= 4)
	{
		m_NeedUGroup++;
		nVChNumOfModule = nChannelNum;
	}
	else
	{
		if (nChannelNum%3 == 0)
		{
			m_NeedUGroup = nChannelNum/3;
			
		}
		else
		{
			m_NeedUGroup = nChannelNum/3+1;
		}

		nVChNumOfModule = 3;
	}
		
	nChannelNum = m_pSttTestResource->m_oCurChRsListRef.GetCount();
	if (nChannelNum <= 4)
	{
		m_NeedIGroup++;
		nIChNUmOfModule = nChannelNum;
	}
	else
	{
		if (nChannelNum%3 == 0)
		{
			m_NeedIGroup = nChannelNum/3;
		}
		else
		{
			m_NeedIGroup = nChannelNum/3+1;
		}

		nIChNUmOfModule = 3;
	}

	m_AllGroup = (m_NeedUGroup >= m_NeedIGroup)?m_NeedUGroup:m_NeedIGroup;

#ifndef USE_VECTOR_MORE_LINE
	if (m_VectorType == STT_LowVolDvdt_VECTOR)
	{
		initTable(nVChNumOfModule+nIChNUmOfModule+1);
	}
	else if(m_VectorType == STT_LowFreqDfdt_VECTOR)
	{
		initTable(nVChNumOfModule+nIChNUmOfModule+1);
	}
	else
	{
	initTable(nVChNumOfModule+nIChNUmOfModule); 
	}
#else
	initTable(nVChNumOfModule+nIChNUmOfModule + 1); 
#endif
	

	QStringList headers;
	headers<</*tr("名称")*/g_sLangTxt_Name<</*tr("幅值")*/g_sLangTxt_Native_Amplitude<</*tr("单位")*/g_sLangTxt_Unit<</*tr("相位(°)")*/g_sLangTxt_Gradient_DPhase<</*tr("频率(HZ)")*/g_sLangTxt_Native_FreqHz;
	setHeader(headers);
}

void VectorWidget::setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList, CSttMacroChannel *pUfCh, CSttMacroChannel *pIfCh)
{
	m_pVOL = pVOL;
	m_pCUR = pCUR;

	m_pVolChList = pVolChList;
	m_pCurChList = pCurChList;

	m_pIfCh = pIfCh;
	m_pUfCh = pUfCh;

	initData();
}

void VectorWidget::setDispMode(int dispmode)
{
	m_nDispMode = dispmode;
	ASSERT(m_pSttTestResource);

	QStringList str;
	str.clear();
	
	if (m_pSttTestResource->m_oVolChRsListRef.GetCount()>0 && m_pSttTestResource->m_oCurChRsListRef.GetCount()>0)
	{
		str<<tr("V")<<tr("V")<<tr("V")<<tr("A")<<tr("A")<<tr("A");
	}
	else if (m_pSttTestResource->m_oVolChRsListRef.GetCount() <=0 && m_pSttTestResource->m_oCurChRsListRef.GetCount() >0)
	{
		str<<tr("A")<<tr("A")<<tr("A");
	}
	else if (m_pSttTestResource->m_oVolChRsListRef.GetCount() >0 && m_pSttTestResource->m_oCurChRsListRef.GetCount() <=0)
	{
		str<<tr("V")<<tr("V")<<tr("V");
	}

	setUnitOfTable(str);
}

void VectorWidget::updateData(bool bRt)
{
	initData(bRt);
}

LineInfo VectorWidget::makeLineInfo(QString name,int linetype,QColor color,tmt_Channel* pChannel)
{
	LineInfo lineInFor;
	lineInFor.m_UIType = name;

	lineInFor.m_RealValue = pChannel->Harm[1].fAmp;		
	if (pChannel->Harm[1].fAmp>=0)
	{
		lineInFor.m_XW = pChannel->Harm[1].fAngle;		
	}
	else
	{
		lineInFor.m_XW = pChannel->Harm[1].fAngle+180;	
	}
	lineInFor.m_Fre = pChannel->Harm[1].fFreq;			

	lineInFor.m_bShowOrHide = true;
	lineInFor.m_Color = QPen(color);
	lineInFor.m_ChangeFactor = 1.0;
	if (linetype==0)
	{
		lineInFor.m_lineType = Line_U;
	}
	else
	{
		lineInFor.m_lineType = Line_I;
	}
	lineInFor.m_strTableName = name;
	return lineInFor;
}

void VectorWidget::initChannelData(int nStart,int nEnd,int nModuleType,int mapKey,QMap<int,QList<tmt_Channel>>& ChanelDataMap,bool bRt)
{
	int j;
	tmt_Channel channelPara;
	QList<tmt_Channel> ChanelDataList;
	CSttMacroChannel* pMacroCh = NULL;

	ChanelDataList.clear();

	if (nModuleType == Moudle_U)
	{
		for (j = nStart; j < nEnd; j++)
		{
			if(!bRt && m_pVOL)
			{
				ChanelDataList.append(m_pVOL[j]);
			}
			else
			{
				pMacroCh = (CSttMacroChannel*)m_pVolChList->GetAtIndex(j);
				if (pMacroCh)
				{
					channelPara.Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;
					channelPara.Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;
					channelPara.Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;
					ChanelDataList.append(channelPara);
				}
			}
		}
	}
	else if (nModuleType == Moudle_I)
	{
		for (j = nStart; j < nEnd; j++)
		{
			if(!bRt && m_pCUR)
			{
				ChanelDataList.append(m_pCUR[j]);
			}
			else
			{
				pMacroCh = (CSttMacroChannel*)m_pCurChList->GetAtIndex(j);
				if (pMacroCh)
				{
					channelPara.Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;
					channelPara.Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;
					channelPara.Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;
					ChanelDataList.append(channelPara);
				}
			}
		}
	}

	ChanelDataMap.insert(mapKey,ChanelDataList);
}

void VectorWidget::initData(bool bRt)
{
	QString str = QString(/*tr("  总组数: %1")*/g_sLangTxt_Native_TotalGroupsParam).arg(m_AllGroup)+ "\n" + QString(/*tr("  当前组: %1")*/g_sLangTxt_Native_CurrentGroupParam).arg(m_nCurrentGroup);
	setlabNumText(str);

	initData(m_nCurrentGroup, bRt);
}

void VectorWidget::getGroupPosRange(int nModuleType, int nGroup, int& nStart, int& nEnd)
{
	if (nModuleType == Moudle_U)
	{
		if (m_NeedUGroup == 0 || nGroup <= 0 || nGroup > m_NeedUGroup)
		{
			nStart = nEnd = 0;
			return;
		}

		if (m_NeedUGroup == 1) 
		{
			nStart = 0;
			nEnd = m_pSttTestResource->m_oVolChRsListRef.GetCount()-1;
		}
		else
		{
			if (nGroup <= m_NeedUGroup-1)
			{
				nStart = (nGroup-1)*3;
				nEnd = nStart + 2;
			}
			else
			{
				nStart = (nGroup-1)*3;
				nEnd = m_pSttTestResource->m_oVolChRsListRef.GetCount()-1;
			}
		}
	}
	else
	{
		if (m_NeedIGroup == 0 || nGroup <= 0 || nGroup > m_NeedIGroup)
		{
			nStart = nEnd = 0;
			return;
		}

		if (m_NeedIGroup == 1) 
		{
			nStart = 0;
			nEnd = m_pSttTestResource->m_oCurChRsListRef.GetCount()-1;
		}
		else
		{
			if (nGroup <= m_NeedIGroup-1)
			{
				nStart = (nGroup-1)*3;
				nEnd = nStart + 2;
			}
			else
			{
				nStart = (nGroup-1)*3;
				nEnd = m_pSttTestResource->m_oCurChRsListRef.GetCount()-1;
			}
		}
	}
}

void VectorWidget::initData(int nCurrentGroup, bool bRt)
{
	setFaultInfo(m_pUfCh, m_pIfCh);
	Complex p1,fVa,fVb,fVc,fVz,fUbc,fUca,fUab,f3U0,fU2,falpha,falpha2;
	Complex	Comp1;
	falpha = Comp1.polar(1,120.0);
	falpha2 = Comp1.polar(1,240.0);
	QString name;
	QList<LineInfo> infoList;
	LineInfo lineInFor;

	tmt_Channel channelPara;
	QList<tmt_Channel> ChanelDataList;
	QMap<int,QList<tmt_Channel>> UChanelDataMap;
	QMap<int,QList<tmt_Channel>> IChanelDataMap;

	UChanelDataMap.clear();
	IChanelDataMap.clear();
	
	if (m_pSttTestResource == NULL)
	{
		return;
	}

	int mapKey = 0;

	//将数据分组
	int startpos = 0;
	int endpos = 0;
	if (m_pSttTestResource->m_oVolChRsListRef.GetCount()<=4) 
	{
		mapKey ++;
		initChannelData(startpos, startpos+m_pSttTestResource->m_oVolChRsListRef.GetCount(), Moudle_U, mapKey, UChanelDataMap, bRt);
	}
	else
	{
		//每3个量一组
		for (int k=0;k<m_NeedUGroup;k++)
		{
			mapKey ++;
			endpos = startpos+3*(k+1);
			if (endpos>m_pSttTestResource->m_oVolChRsListRef.GetCount())
			{
				endpos = m_pSttTestResource->m_oVolChRsListRef.GetCount();
			}
			initChannelData(startpos+3*k, endpos, Moudle_U, mapKey, UChanelDataMap, bRt);
		}
	}

	mapKey = 0;
	startpos = 0;

	if (m_pSttTestResource->m_oCurChRsListRef.GetCount()<=4 )
	{
		mapKey ++;
		initChannelData(startpos, startpos+m_pSttTestResource->m_oCurChRsListRef.GetCount(), Moudle_I, mapKey, IChanelDataMap, bRt);
	}
	else
	{
		//每3个量一组
		for (int k=0;k<m_pSttTestResource->m_oCurChRsListRef.GetCount()/3;k++)
		{
			mapKey ++;
			endpos = startpos+3*(k+1);
			if (endpos>m_pSttTestResource->m_oCurChRsListRef.GetCount())
			{
				endpos = m_pSttTestResource->m_oCurChRsListRef.GetCount();
			}
			initChannelData(startpos+3*k, endpos, Moudle_I, mapKey, IChanelDataMap, bRt);
		}
	}

	ChanelDataList.clear();
	int nStart = 0;
	int nEnd = 0;
	if (nCurrentGroup <= UChanelDataMap.size())
	{
		ChanelDataList = UChanelDataMap.value(nCurrentGroup);
		/*if (m_bDCTest)
		{
			for (int i = 0; i < ChanelDataList.size(); i++)
			{
				channelPara = ChanelDataList[i];
				channelPara.Harm[1].fAngle = 0;
				channelPara.Harm[1].fFreq = 0;
			}
		}*/
		if (ChanelDataList.size() > 0)
		{
			getGroupPosRange(Moudle_U,nCurrentGroup,nStart,nEnd);

			for (int i=nStart;i<=nEnd;i++)
			{
				channelPara = ChanelDataList.at(i-nStart);
				if (m_bDCTest)
				{
					channelPara.Harm[1].fAngle = 0;
					channelPara.Harm[1].fFreq = 0;
				}
				CSttMacroChannel *pChannel = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
				if (pChannel)
				{
					QString name=pChannel->m_strName;
					if (nEnd - nStart >= 3)
					{
						if(i%4==0)
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::yellow,&channelPara);
						}
						else if(i%4==1)
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::green,&channelPara);
						}
						else if (i%4==2)
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::red,&channelPara);
						}
						else 
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::gray,&channelPara);
						}
					}
					else
					{
						if(i%3==0)
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::yellow,&channelPara);
						}
						else if(i%3==1)
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::green,&channelPara);
						}
						else if (i%3==2)
						{
							lineInFor = makeLineInfo(name,Line_U,Qt::red,&channelPara);
						}
					}
					
					infoList.append(lineInFor);
					fVa = p1.polar(lineInFor.m_RealValue,lineInFor.m_XW);
				}
			}
		}
	}

	if (nCurrentGroup <= IChanelDataMap.size())
	{
		ChanelDataList = IChanelDataMap.value(nCurrentGroup);
		/*if (m_bDCTest)
		{
			for (int i = 0; i < ChanelDataList.size(); i++)
			{
				channelPara = ChanelDataList[i];
				channelPara.Harm[1].fAngle = 0;
				channelPara.Harm[1].fFreq = 0;
			}
		}*/
		if (ChanelDataList.size() > 0)
		{
			getGroupPosRange(Moudle_I,nCurrentGroup,nStart,nEnd);

			for (int i=nStart;i<=nEnd;i++)
			{
				if (ChanelDataList.size()<=(i-nStart))//zhouhj 20210623  增加防止h获取容器中数据失败(在电压、电流通道数都为0时,此处有问题)
				{
					break;
				}

				channelPara = ChanelDataList.at(i-nStart);
				if (m_bDCTest)
				{
					channelPara.Harm[1].fAngle = 0;
					channelPara.Harm[1].fFreq = 0;
				}
				CSttMacroChannel *pChannel = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
				if (pChannel)
				{
					QString name=pChannel->m_strName;
					if (nEnd - nStart >= 3)
					{
						if(i%4==0)
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::yellow,&channelPara);
						}
						else if(i%4==1)
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::green,&channelPara);
						}
						else if (i%4==2)
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::red,&channelPara);
						}
						else 
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::gray,&channelPara);
						}
					}
					else
					{
						if(i%3==0)
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::yellow,&channelPara);
						}
						else if(i%3==1)
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::green,&channelPara);
						}
						else if (i%3==2)
						{
							lineInFor = makeLineInfo(name,Line_I,Qt::red,&channelPara);
						}
					}

					infoList.append(lineInFor);
					fVa = p1.polar(lineInFor.m_RealValue,lineInFor.m_XW);
				}
			}
		}
	}


	setLineInfos(infoList);

	QStringList nameList;
	nameList<</*tr("A相")*/g_sLangTxt_Aphase<</*tr("B相")*/g_sLangTxt_Bphase<</*tr("C相")*/g_sLangTxt_Aphase<</*tr("0相")*/g_sLangTxt_Native_PhaseO;
	QList<QPen> colorList;
	colorList.append(QPen(Qt::yellow));
	colorList.append(QPen(Qt::green));
	colorList.append(QPen(Qt::red));
	colorList.append(QPen(Qt::magenta));
	setLegends( nameList,colorList);
	updateDiagram();
	setDC(m_bDCTest);
}

void VectorWidget::slot_PbnNextClicked()
{
	QString str;
	
	m_nCurrentGroup++;
	if (m_nCurrentGroup>m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}
	str = QString(/*tr("  总组数: %1")*/g_sLangTxt_Native_TotalGroupsParam).arg(m_AllGroup)+ "\n" + QString(/*tr("  当前组: %1")*/g_sLangTxt_Native_CurrentGroupParam).arg(m_nCurrentGroup);

	setlabNumText(str);
	updateData();
	emit sig_Sequencemanutest();

}

void VectorWidget::slot_PbnPreClicked()
{
	m_nCurrentGroup--;
	if (m_nCurrentGroup<1)
	{
		m_nCurrentGroup = 1;
	}
	QString str = QString(/*tr("  总组数: %1")*/g_sLangTxt_Native_TotalGroupsParam).arg(m_AllGroup)+ "\n" + QString(/*tr("  当前组: %1")*/g_sLangTxt_Native_CurrentGroupParam).arg(m_nCurrentGroup);
	
	setlabNumText(str);
	updateData();
	emit sig_Sequencemanutest();
}

void VectorWidget::setDCChanged(bool bDCTest)
{
	m_bDCTest = bDCTest;
	updateData();
}

void VectorWidget::OnRtDataChanged()
{
	//updateData();
	m_bTimeStart = TRUE;	
}

void VectorWidget::timerEvent( QTimerEvent *event )
{
	
	if (m_bTimeStart)
	{
		if(event->timerId() == m_nTimerID )
		{
			updateData(TRUE);
			m_bTimeStart = FALSE;
		}
		else
		{
			killTimer(m_nTimerID);
			m_nTimerID = -1;
		}
	}

	

	QWidget::timerEvent( event );
}