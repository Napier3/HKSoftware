#include "stdafx.h"
#include "vectorwidget.h"
#include <QStringList>
#include <QList>
#include <QPen>
#include "../../SttTestCntrFrameAPI.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include"../../../Module/SttCmd/SttChMap.h"

QVectorWidget::QVectorWidget(QWidget *parent)
	: QSttInfWidgetBase(parent)
{
	m_pDiagram = NULL;
	m_fUMax = 120;
	m_fIMax = 30;

	m_AllGroup = 0;
	m_NeedUGroup = 0;
	m_NeedIGroup = 0;
	m_nCurrentGroup = 1;

	m_bDCTest = false;

	m_pVOL = NULL;
	m_pCUR = NULL;
	m_pVectorSttTestResource = NULL;

	m_pVolChList = NULL;
	m_pCurChList = NULL;

	m_nTimerID = -1;
}

QVectorWidget::~QVectorWidget()
{

}


void QVectorWidget::setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource,int VectorType)
{
	if (pSttTestResource == NULL)
	{
		return;
	}
	m_VectorType = VectorType;
	m_pVectorSttTestResource = pSttTestResource;

	if (m_pDiagram == NULL)
	{
		return;
	}
	else
	{
		setPropertyOfParaSet();
	}
}

void QVectorWidget::setPropertyOfParaSet()
{
	int AllChanelNum=0;
	int AllUChanelNum = 0;
	int AllIChanelNum = 0;
	m_NeedUGroup = 0;
	m_NeedIGroup = 0;
	int nChannelNum = 0;
	int nVChNumOfModule = 0;
	int nIChNUmOfModule = 0;

	m_pDiagram->m_VectorType = m_VectorType;

	nChannelNum = m_pVectorSttTestResource->m_oVolChRsListRef.GetCount();

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

	nChannelNum = m_pVectorSttTestResource->m_oCurChRsListRef.GetCount();
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

    //mod wangtao 20240522 防止在已经切换过矢量图组数的情况下，重新加载输出报文类型导致按钮变灰
	if (m_nCurrentGroup>m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}

	if (m_nCurrentGroup == 1)
	{
		m_pDiagram->m_pbnPre->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnPre->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup)
	{
		m_pDiagram->m_pbnNext->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnNext->setDisabled(false);
	}
	//end
	/*if(m_AllGroup == 1)
	{
		m_pDiagram->m_pbnNext->setDisabled(true);
		m_pDiagram->m_pbnPre->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnNext->setDisabled(false);
		m_pDiagram->m_pbnPre->setDisabled(true);
	}*/


	//矢量图的table需要显示全部的通道
	nVChNumOfModule = m_pVectorSttTestResource->m_oVolChRsListRef.GetCount();
	nIChNUmOfModule = m_pVectorSttTestResource->m_oCurChRsListRef.GetCount();

	//m_pDiagram->initTable(nVChNumOfModule+nIChNUmOfModule);

#ifndef USE_VECTOR_MORE_LINE
	if (m_pDiagram->m_VectorType == STT_LowVolDvdt_VECTOR)
	{
		m_pDiagram->initTable(nVChNumOfModule+nIChNUmOfModule+1);
	}
	else if(m_pDiagram->m_VectorType == STT_LowFreqDfdt_VECTOR)
	{
		m_pDiagram->initTable(nVChNumOfModule+nIChNUmOfModule+1);
	}
	else
	{
		m_pDiagram->initTable(nVChNumOfModule+nIChNUmOfModule); 
	}
#else
	initTable(nVChNumOfModule+nIChNUmOfModule + 1); 
#endif


	QStringList headers;
	CString strChannel, strAmplitude, strPhase, strFreq, strUnit;//通道，幅值，相位，频率，单位
	xlang_GetLangStrByFile(strChannel, "Native_Channel");//从资源文件、资源类中获取ID对应的字符串
	xlang_GetLangStrByFile(strAmplitude, "Native_Amplitude");
	xlang_GetLangStrByFile(strPhase, "Native_Angle");
#ifndef _PSX_QT_LINUX_
	strPhase += QString::fromLocal8Bit("(°)");
#else
	strPhase += "(°)";
#endif
	xlang_GetLangStrByFile(strFreq, "Native_Freq");
	strFreq += "(Hz)";
	strUnit = g_sLangTxt_Unit;
//	xlang_GetLangStrByFile(strUnit, "Native_Unit");

	headers<<strChannel<<strAmplitude<<strUnit<<strPhase<<strFreq;//设置首行
	m_pDiagram->setHeader(headers);
}


void QVectorWidget::setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList)
{
	m_pVOL = pVOL;
	m_pCUR = pCUR;

	m_pVolChList = pVolChList;
	m_pCurChList = pCurChList;

	initData();
}

void QVectorWidget::setUIMax(float fUMax,float fIMax)
{
	m_fUMax = fUMax;
	m_fIMax = fIMax;

	setUIMax();
}

void QVectorWidget::setUIMax()
{
	if (m_pDiagram == NULL)
	{
		return;
	}

	m_pDiagram->setUIMax(m_fUMax, m_fIMax);
}


void QVectorWidget::updateData()
{
	initData();
}

LineInfo QVectorWidget::makeLineInfo(QString name,int linetype,QColor color,tmt_Channel* pChannel)
{
	LineInfo lineInFor;
	lineInFor.m_UIType = name;//通道类型

	lineInFor.m_RealValue = pChannel->Harm[1].fAmp;//幅值		
	if (pChannel->Harm[1].fAmp>=0)
	{
		lineInFor.m_XW = pChannel->Harm[1].fAngle;//相位		
	}
	else
	{
		lineInFor.m_XW = pChannel->Harm[1].fAngle+180;	
	}
	lineInFor.m_Fre = pChannel->Harm[1].fFreq;//频率			

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

void QVectorWidget::initChannelData(int nStart,int nEnd,int nModuleType,int mapKey,QMap<int,QList<tmt_Channel> >& ChanelDataMap)
{
	int j;
	tmt_Channel channelPara;
	QList<tmt_Channel> ChanelDataList;
	CSttMacroChannel* pMacroCh = NULL;
	ChanelDataList.clear();

	if (nModuleType == Moudle_U)//通道类型为电压
	{
		for (j = nStart; j < nEnd; j++)
		{
			if(!stt_Frame_IsTestStarted() && m_pVOL)
			{
				ChanelDataList.append(m_pVOL[j]);
			}
			else
			{
				pMacroCh = (CSttMacroChannel*)m_pVolChList->GetAtIndex(j);
				if (pMacroCh)
				{
						
						channelPara.Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;//幅值
						channelPara.Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;//相位
						channelPara.Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;//频率
// 					if(m_pVOL)
// 					{
// 						m_pVOL[j].Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;
// 						m_pVOL[j].Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;
// 						m_pVOL[j].Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;
// 					}
					ChanelDataList.append(channelPara);
				}
			}
		}
	}
	else if (nModuleType == Moudle_I)//通道类型为电流
	{
		for (j = nStart; j < nEnd; j++)
		{
			if(!stt_Frame_IsTestStarted() && m_pCUR)
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
// 					if(m_pCUR)
// 					{
// 						m_pCUR[j].Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;
// 						m_pCUR[j].Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;
// 						m_pCUR[j].Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;
// 					}				
					ChanelDataList.append(channelPara);
				}
			}
		}
	}

	ChanelDataMap.insert(mapKey,ChanelDataList);
}

void QVectorWidget::initTableInfos()//初始化表格信息
{
	LineInfo lineInFor;
	QList<LineInfo> infoList;
	tmt_Channel channelPara;//通道参数
	QList<tmt_Channel> ChanelDataList;
	QMap<int,QList<tmt_Channel> > UChanelDataMap;
	QMap<int,QList<tmt_Channel> > IChanelDataMap;

	initChannelData(0, m_pVectorSttTestResource->m_oVolChRsListRef.GetCount(), Moudle_U, 0, UChanelDataMap);
	initChannelData(0, m_pVectorSttTestResource->m_oCurChRsListRef.GetCount(), Moudle_I, 0, IChanelDataMap);
	ChanelDataList = UChanelDataMap.value(0);
	for (int i = 0; i < ChanelDataList.size(); i++)
	{
		channelPara = ChanelDataList.at(i);
		if (m_bDCTest)
		{
			channelPara.Harm[1].fAngle = 0;
			channelPara.Harm[1].fFreq = 0;
		}
		CSttMacroChannel *pChannel = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);

		if (pChannel==NULL)
		{
			continue;
		}

		if(pChannel->m_pHdMaps==NULL)//判断是否有对应的硬件资源  20230201 zhouyy
		{
			continue;
		}

			QString name=pChannel->m_strName;
			lineInFor = makeLineInfo(name, Line_U, Qt::black, &channelPara);
			infoList.append(lineInFor);
	}
	ChanelDataList = IChanelDataMap.value(0);
	for (int i = 0; i < ChanelDataList.size(); i++)
	{
		channelPara = ChanelDataList.at(i);
		if (m_bDCTest)
		{
			channelPara.Harm[1].fAngle = 0;
			channelPara.Harm[1].fFreq = 0;
		}
		CSttMacroChannel *pChannel = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
		if (pChannel==NULL)
		{
			continue;
		}
		if(pChannel->m_pHdMaps==NULL)
		{
			continue;
		}

			QString name=pChannel->m_strName;
			lineInFor = makeLineInfo(name, Line_I, Qt::black, &channelPara);
			infoList.append(lineInFor);
	}

	m_pDiagram->setTableInfos(infoList);
}

void QVectorWidget::initData()
{
	if (m_pDiagram == NULL)
	{
		return;
	}
//	QString str = QString(tr("  总组数: %1")).arg(m_AllGroup)+ "\n" + QString(tr("  当前组: %1")).arg(m_nCurrentGroup);

	if(m_nCurrentGroup > m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}
	
	m_pDiagram->setlabNumText(getAllCurGroupStr());
	initData(m_nCurrentGroup);
	initTableInfos();
	m_pDiagram->updateDiagram();
}

void QVectorWidget::getGroupPosRange(int nModuleType, int nGroup, int& nStart, int& nEnd)
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
			nEnd = m_pVectorSttTestResource->m_oVolChRsListRef.GetCount()-1;
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
				nEnd = m_pVectorSttTestResource->m_oVolChRsListRef.GetCount()-1;
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
			nEnd = m_pVectorSttTestResource->m_oCurChRsListRef.GetCount()-1;
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
				nEnd = m_pVectorSttTestResource->m_oCurChRsListRef.GetCount()-1;
			}
		}
	}
}

void QVectorWidget::initData(int nCurrentGroup)
{
	Complex p1,fVa,fVb,fVc,fVz,fUbc,fUca,fUab,f3U0,fU2,falpha,falpha2;
	Complex Comp1;
	falpha = Comp1.polar(1,120.0);
	falpha2 = Comp1.polar(1,240.0);
	QString name;
	QList<LineInfo> infoList;
	LineInfo lineInFor;

	tmt_Channel channelPara;
	QList<tmt_Channel> ChanelDataList;
	QMap<int,QList<tmt_Channel> > UChanelDataMap;
	QMap<int,QList<tmt_Channel> > IChanelDataMap;

	UChanelDataMap.clear();
	IChanelDataMap.clear();
	
	if (m_pVectorSttTestResource == NULL)
	{
		return;
	}

	int mapKey = 0;

	//将数据分组
	int startpos = 0;
	int endpos = 0;
	if (m_pVectorSttTestResource->m_oVolChRsListRef.GetCount()<=4) 
	{
		mapKey ++;
		initChannelData(startpos, startpos+m_pVectorSttTestResource->m_oVolChRsListRef.GetCount(), Moudle_U, mapKey, UChanelDataMap);
	}
	else
	{
		//每3个量一组
		for (int k=0;k<m_NeedUGroup;k++)
		{
			mapKey ++;
			endpos = startpos+3*(k+1);
			if (endpos>m_pVectorSttTestResource->m_oVolChRsListRef.GetCount())
			{
				endpos = m_pVectorSttTestResource->m_oVolChRsListRef.GetCount();
			}
			initChannelData(startpos+3*k, endpos, Moudle_U, mapKey, UChanelDataMap);
		}
	}

	mapKey = 0;
	startpos = 0;

	if (m_pVectorSttTestResource->m_oCurChRsListRef.GetCount()<=4 )
	{
		mapKey ++;
		initChannelData(startpos, startpos+m_pVectorSttTestResource->m_oCurChRsListRef.GetCount(), Moudle_I, mapKey, IChanelDataMap);
	}
	else
	{
		//每3个量一组
		for (int k=0;k<m_pVectorSttTestResource->m_oCurChRsListRef.GetCount()/3;k++)
		{
			mapKey ++;
			endpos = startpos+3*(k+1);
			if (endpos>m_pVectorSttTestResource->m_oCurChRsListRef.GetCount())
			{
				endpos = m_pVectorSttTestResource->m_oCurChRsListRef.GetCount();
			}
			initChannelData(startpos+3*k, endpos, Moudle_I, mapKey, IChanelDataMap);
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

	m_pDiagram->setLineInfos(infoList);

	QStringList nameList;
	CString strPhaseA,strPhaseB,strPhaseC,strPhaseO;
	xlang_GetLangStrByFile(strPhaseA, "sAphase");
	xlang_GetLangStrByFile(strPhaseB, "sBphase");
	xlang_GetLangStrByFile(strPhaseC, "sCphase");
	xlang_GetLangStrByFile(strPhaseO, "Native_PhaseO");

//	nameList<<tr("A相")<<tr("B相")<<tr("C相")<<tr("0相");
	nameList<<strPhaseA<<strPhaseB<<strPhaseC<<strPhaseO;

	QList<QPen> colorList;
	colorList.append(QPen(Qt::yellow));
	colorList.append(QPen(Qt::green));
	colorList.append(QPen(Qt::red));
	colorList.append(QPen(Qt::magenta));
	m_pDiagram->setLegends( nameList,colorList);
}

void QVectorWidget::slot_PbnNextClicked()
{
	m_nCurrentGroup++;
	if (m_nCurrentGroup>m_AllGroup)
	{
		m_nCurrentGroup = m_AllGroup;
	}

	if (m_nCurrentGroup == 1)
	{
		m_pDiagram->m_pbnPre->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnPre->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup)
	{
		m_pDiagram->m_pbnNext->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnNext->setDisabled(false);
	}

//	str = QString(tr("  总组数: %1")).arg(m_AllGroup)+ "\n" + QString(tr("  当前组: %1")).arg(m_nCurrentGroup);

	m_pDiagram->setlabNumText(getAllCurGroupStr());
	updateData();
}

void QVectorWidget::slot_PbnPreClicked()
{
	m_nCurrentGroup--;
	if (m_nCurrentGroup<1)
	{
		m_nCurrentGroup = 1;
	}

	if (m_nCurrentGroup == 1)
	{
		m_pDiagram->m_pbnPre->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnPre->setDisabled(false);
	}

	if (m_nCurrentGroup == m_AllGroup)
	{
		m_pDiagram->m_pbnNext->setDisabled(true);
	}
	else
	{
		m_pDiagram->m_pbnNext->setDisabled(false);
	}

//	QString str = QString(tr("  总组数: %1")).arg(m_AllGroup)+ "\n" + QString(tr("  当前组: %1")).arg(m_nCurrentGroup);
	
	m_pDiagram->setlabNumText(getAllCurGroupStr());
	updateData();
}

CString QVectorWidget::getAllCurGroupStr()
{
	CString strAllGroup,strCurGroup,strNum;
	xlang_GetLangStrByFile(strAllGroup, "Native_AllGroup");
	xlang_GetLangStrByFile(strCurGroup, "Native_CurGroup");

	CString strText1,strText2;
	strText1 = _T("  ");
	strText1 += strAllGroup;
	strNum.Format(_T("%d"),m_AllGroup);
	strText1 += strNum;

	strText2 = _T("  ");
	strText2 += strCurGroup;
	strNum.Format(_T("%d"),m_nCurrentGroup);
	strText2 += strNum;

	CString str = strText1;
	str += "\n";
	str += strText2;

	return str;
}

void QVectorWidget::setDCChanged(bool bDCTest)
{
	m_bDCTest = bDCTest;
	updateData();
}

void QVectorWidget::setAutoChanged(bool bAutoTest)
{
	//当前不需要判断是否递变就能够区别绘图停止的逻辑
}

void QVectorWidget::OnRtDataChanged()
{
	
}

void QVectorWidget::TimerStart()
{
	if(m_nTimerID != -1)
	{
		return;
	}
	m_nTimerID = startTimer(200);
}

void QVectorWidget::TimerStop(bool bUpdate)
{
	killTimer(m_nTimerID);
	m_nTimerID = -1;

	if(bUpdate)
	{
		//更新完成时的数据至表格和edit
		if(m_pVOL)
		{
			for (int i = 0; i < m_pVectorSttTestResource->m_oVolChRsListRef.GetCount(); i++)
			{
				CSttMacroChannel* pMacroCh = (CSttMacroChannel*)m_pVolChList->GetAtIndex(i);
				m_pVOL[i].Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;
				m_pVOL[i].Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;
				m_pVOL[i].Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;
			}
		}
		if(m_pCUR)
		{
			for (int i = 0; i < m_pVectorSttTestResource->m_oCurChRsListRef.GetCount(); i++)
			{
				CSttMacroChannel* pMacroCh = (CSttMacroChannel*)m_pCurChList->GetAtIndex(i);
				m_pCUR[i].Harm[1].fAmp = pMacroCh->m_oRtDataCh.m_fMag;
				m_pCUR[i].Harm[1].fAngle = pMacroCh->m_oRtDataCh.m_fAng;
				m_pCUR[i].Harm[1].fFreq = pMacroCh->m_oRtDataCh.m_fFreq;
			}
		}

		m_pDiagram->updateDiagram();
	}
}

void QVectorWidget::timerEvent( QTimerEvent *event )
{
	if(m_nTimerID == event->timerId())
	{
		updateData();
		QWidget::timerEvent( event );
	}
}

void QVectorWidget::showEvent(QShowEvent *)
{
	if (m_pDiagram != NULL)
	{
		return;
	}

	m_pDiagram = new Diagram(this);
	InitSttInfWidget(m_pDiagram);

	m_pDiagram->setPbnDisp(true);
	connect(m_pDiagram, SIGNAL(sig_Pbn_NextClicked()), this, SLOT(slot_PbnNextClicked()));
	connect(m_pDiagram, SIGNAL(sig_Pbn_PreClicked()), this, SLOT(slot_PbnPreClicked()));

	setPropertyOfParaSet();
	setUIMax();
	initData();
}

void QVectorWidget::SetVectorMode(int nVectorType, CDataGroup *pGroup)
{
	if (nVectorType == VECTOR_POWERWORK)
	{
		if (m_pDiagram)
		{
			m_pDiagram->setIsDrawSectorFlag(true);
			SetDatas_PowerDir(pGroup);
		}
	}
    else if(nVectorType == VECTOR_POWERWORK_I)
    {
        if (m_pDiagram)
        {
            m_pDiagram->setIsDrawSectorFlag(true);
            SetDatas_PowerDir_I((CExBaseList*)pGroup);
        }
    }
	else
	{
		if (m_pDiagram)
		{
			m_pDiagram->setIsDrawSectorFlag(false);
		}
	}
}

void QVectorWidget::SetDatas_PowerDir(CDataGroup *pGroup)
{
	if (pGroup == NULL)
	{
		return;
	}

	long lAngleMode = 0;
	float fMaxSensAngle,fLagAngle,fLeadAngle,fStart,fEnd = 0.0;

	CDvmData *pAngleModeData = (CDvmData*)pGroup->FindByID("AngleMode");
	if (pAngleModeData)
	{
		lAngleMode = CString_To_long(pAngleModeData->m_strValue);
	}

	CDvmData *pMaxSensAngleData = (CDvmData*)pGroup->FindByID("MTA");	
	if (pMaxSensAngleData)
	{
		fMaxSensAngle = atof(pMaxSensAngleData->m_strValue.GetString());
	}

	CDvmData *pLagAngleData = (CDvmData*)pGroup->FindByID("Lag");
	if (pLagAngleData)
	{
		fLagAngle = atof(pLagAngleData->m_strValue.GetString());
	}

	CDvmData *pLeadAngleData = (CDvmData*)pGroup->FindByID("Lead");
	if (pLeadAngleData)
	{
		fLeadAngle = atof(pLeadAngleData->m_strValue.GetString());
	}

	CDvmData *pStartData = (CDvmData*)pGroup->FindByID("StartValueMargin");
	if (pStartData)
	{
		fStart = atof(pStartData->m_strValue.GetString());
	}

	CDvmData *pEndData = (CDvmData*)pGroup->FindByID("EndValueMargin");
	if (pEndData)
	{
		fEnd = atof(pEndData->m_strValue.GetString());
	}

	float fStarts = fMaxSensAngle-fLagAngle-fStart;
	float fEnds = fMaxSensAngle+fLagAngle+fEnd;
	if (lAngleMode == 0)
	{
		m_pDiagram->setSectorAngle(-(fMaxSensAngle + fLagAngle) , fLeadAngle - fMaxSensAngle);
		m_pDiagram->setSearchArcAngle(-fStarts,-fEnds);

		if (fMaxSensAngle < 0)
			m_pDiagram->setMTAAngle(-fMaxSensAngle);
		else
			m_pDiagram->setMTAAngle(360 - fMaxSensAngle);
	}
	else
	{
		m_pDiagram->setSectorAngle(fMaxSensAngle - fLeadAngle,fMaxSensAngle + fLagAngle);
		m_pDiagram->setSearchArcAngle(fStarts,fEnds);

		if (fMaxSensAngle < 0)
			m_pDiagram->setMTAAngle(360 + fMaxSensAngle);
		else
			m_pDiagram->setMTAAngle(fMaxSensAngle);
	}
	update();
}

void QVectorWidget::SetDatas_PowerDir_I(CExBaseList *pParas)
{
	if (pParas == NULL)
	{
		return;
	}

	long lAngleMode = 0;
	float fMaxSensAngle,fLagAngle,fLeadAngle,fStart,fEnd = 0.0;
	float fAngleRange, fAngleMargin = 0.0;

	POS pos = pParas->GetHeadPosition();
	while (pos!= NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pParas->GetNext(pos);
		if(pData->m_strID == "AngleMode")
		{
			lAngleMode = CString_To_long(pData->m_strValue);
		}
		else if(pData->m_strID == "MTA")
		{
			fMaxSensAngle = atof(pData->m_strValue.GetString());
		}
		else if(pData->m_strID == "AngleRange")
		{
			fAngleRange = atof(pData->m_strValue.GetString());
		}
		else if(pData->m_strID == "AngleMargin")
		{
			fAngleMargin = atof(pData->m_strValue.GetString());
		}
	}

	float fStarts = fMaxSensAngle - 0.5*fAngleRange - fAngleMargin;
	float fEnds = fMaxSensAngle + 0.5*fAngleRange + fAngleMargin;
	if (lAngleMode == 0)
	{
		m_pDiagram->setSectorAngle(-(fMaxSensAngle + 0.5*fAngleRange) , 0.5*fAngleRange - fMaxSensAngle);
		m_pDiagram->setSearchArcAngle(-fStarts,-fEnds);

		if (fMaxSensAngle < 0)
			m_pDiagram->setMTAAngle(-fMaxSensAngle);
		else
			m_pDiagram->setMTAAngle(360 - fMaxSensAngle);
	}
	else
	{
		m_pDiagram->setSectorAngle(fMaxSensAngle - 0.5*fAngleRange,fMaxSensAngle + 0.5*fAngleRange);
		m_pDiagram->setSearchArcAngle(fStarts,fEnds);

		if (fMaxSensAngle < 0)
			m_pDiagram->setMTAAngle(360 + fMaxSensAngle);
		else
			m_pDiagram->setMTAAngle(fMaxSensAngle);
	}

    /*20240826 wanmj 功率方向U0改为Uref*/
    CSttMacroChannel *pChannel = (CSttMacroChannel*)m_pVolChList->GetAtIndex(3);
    if (pChannel != NULL)
    {
        pChannel->m_strName = tr("Uref");
    }

	update();
}