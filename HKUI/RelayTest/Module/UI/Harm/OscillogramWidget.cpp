#include "OscillogramWidget.h"
//#include "../SttTestCntrFrameBase.h"
#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
//#include "commonsingleton.h"
#include <QHBoxLayout>

QOscillogramWidget::QOscillogramWidget(QWidget *parent )
	:QWidget(parent)
{
	m_pArrUIVol = NULL;
	m_pArrUICur = NULL;
	m_nCurFlag = 0;
	m_nVolFlag = 0;
	m_nGroupIndex = -1;
	generagelsinData();
}
QOscillogramWidget::~QOscillogramWidget()
{
	m_oGroupResourceRef_Cur.RemoveAll();
	m_oGroupResourceRef_Vol.RemoveAll();

}

void QOscillogramWidget::clearPlot()
{

}

void QOscillogramWidget::updateWidget()
{
//	qRegisterMetaType<LogLevel>("LogLevel");
	clearPlot();
	m_PlotList.clear();

	CSttChGroupResource *pChResource = NULL;
	m_CheckBoxList_Vol.clear();//
	m_CheckBoxList_Cur.clear();//
	m_listLableCur.clear();
	m_listLableVol.clear();

	//操作电压
	POS posVol = m_oGroupResourceRef_Vol.GetHeadPosition();
	int nIndexVol = 0;
	QString strColor[4];

	strColor[0] = QString::fromUtf8("background-color: yellow;");
	strColor[1] = QString::fromUtf8("background-color: green;");
	strColor[2] = QString::fromUtf8("background-color: red;");
	strColor[3] = QString::fromUtf8("background-color: lightgray;");

	while(posVol)
	{
		pChResource = (CSttChGroupResource *)m_oGroupResourceRef_Vol.GetNext(posVol);

		QSttCheckBox *pV1 = new QSttCheckBox(pChResource->m_strName, this);//
		pV1->setAutoExclusive(false);
		pV1->setChecked(true);
		connect(pV1,SIGNAL(toggled(bool)),this,SLOT(slot_UpdateOscillogramV(bool)));
		pV1->setMaximumWidth(70);
		pV1->setFont(*g_pSttGlobalFont);
		//pV1->setMinimumWidth(70);

		m_CheckBoxList_Vol.push_back(pV1);//

		QLabel *pVL1 = new QLabel(this);
		pVL1->setMaximumWidth(50);
		pVL1->setMaximumHeight(2);
		pVL1->setStyleSheet(strColor[nIndexVol]);
		m_listLableVol.push_back(pVL1);

		nIndexVol++;
 
	}

	int nIndex = 0;
	QHBoxLayout *HvLayout1 = new QHBoxLayout;
	for(nIndex = 0; nIndex<nIndexVol; nIndex++)
	{
		HvLayout1->addWidget(m_CheckBoxList_Vol[nIndex]);
		HvLayout1->addWidget(m_listLableVol[nIndex]);
	}
	HvLayout1->setSpacing(5);
	PlotOscillogram *pV1 = new PlotOscillogram(TYPE_V, this);

	POS posCur = m_oGroupResourceRef_Cur.GetHeadPosition();
	int nIndexCur = 0;
	while(posCur)
	{
		pChResource = (CSttChGroupResource *)m_oGroupResourceRef_Cur.GetNext(posCur);
		QSttCheckBox *pI1 = new QSttCheckBox(pChResource->m_strName, this);//
		pI1->setChecked(true);
		pI1->setAutoExclusive(false);
		pI1->setFont(*g_pSttGlobalFont);
		connect(pI1, SIGNAL(toggled(bool)), this, SLOT(slot_UpdateOscillogramI(bool)));
		pI1->setMaximumWidth(70);
		//pI1->setMinimumWidth(70);
		m_CheckBoxList_Cur.push_back(pI1);//

		QLabel *pIL1 = new QLabel(this);
		pIL1->setMaximumHeight(2);
		pIL1->setMaximumWidth(50);
		pIL1->setStyleSheet(strColor[nIndexCur]);
		m_listLableCur.push_back(pIL1);

		nIndexCur++;
	}

	QHBoxLayout *HiLayout1 = new QHBoxLayout;
	for(nIndex = 0;nIndex<nIndexCur; nIndex++)
	{
		HiLayout1->addWidget(m_CheckBoxList_Cur[nIndex]);
		HiLayout1->addWidget(m_listLableCur[nIndex]);
	}
	HiLayout1->setSpacing(5);

	PlotOscillogram *pPI1 = new PlotOscillogram(TYPE_I, this);

	QVBoxLayout *V1Layout = new QVBoxLayout;
	V1Layout->addLayout(HvLayout1);
	V1Layout->addWidget(pV1);
	V1Layout->addLayout(HiLayout1);
	V1Layout->addWidget(pPI1);
	V1Layout->setMargin(2);

	this->setLayout(V1Layout);

	m_PlotList.append(pV1);
	m_PlotList.append(pPI1);

	QwtText t;
	QFont font;
	font.setBold(true);
	t.setFont(font);
	t.setText("U(V)");
	pV1->setAxisTitle(QwtPlot::yLeft, t);
	t.setText("I(A)");
	pPI1->setAxisTitle(QwtPlot::yLeft, t);

	update();

}
void QOscillogramWidget::slot_UpdateOscillogramI(bool b)
{
	POS pos = m_oGroupResourceRef_Cur.GetHeadPosition();
	int nIndex = 0;
	CSttChResource *pChResource = NULL;
	while(pos)
	{
		pChResource = (CSttChResource *)m_oGroupResourceRef_Cur.GetNext(pos);

		if(m_CheckBoxList_Cur[nIndex]->isChecked())//
		{
			if(m_PlotList.at(1)->existCurve(pChResource->m_strName))
			{
				m_PlotList.at(1)->showCurve(pChResource->m_strName, true);
			}
		}
		else if(m_PlotList.at(1)->existCurve(pChResource->m_strName))
		{
			m_PlotList.at(1)->showCurve(pChResource->m_strName, false);
		}
		nIndex++;
	}

}
void QOscillogramWidget::slot_UpdateOscillogramV(bool b)
{
	POS pos = m_oGroupResourceRef_Vol.GetHeadPosition();
	int nIndex = 0;
	CSttChResource *pChResource = NULL;
	while(pos)
	{
		pChResource = (CSttChResource *)m_oGroupResourceRef_Vol.GetNext(pos);
		
		if(m_CheckBoxList_Vol[nIndex]->isChecked())//
		{
			if(m_PlotList.at(0)->existCurve(pChResource->m_strName))
			{
				m_PlotList.at(0)->showCurve(pChResource->m_strName, true);
			}
		}
		else if(m_PlotList.at(0)->existCurve(pChResource->m_strName))
		{
				m_PlotList.at(0)->showCurve(pChResource->m_strName, false);
		}
		nIndex++;
	}

}

float QOscillogramWidget::getVMax(int index)
{
	float VAMax = 0;
	int nVolCount = getSttChGroupResource_Vol_ChCnt();
	for(int i = 0;i<nVolCount; i++)
	{
		for(int j = 0; j<CHANLEPOINT; j++)
		{
			if(i<m_WaveDataList_Vol.size() && j<m_WaveDataList_Vol.at(i).size())
				if(m_WaveDataList_Vol.at(i).at(j) > VAMax)
				{
					VAMax = m_WaveDataList_Vol.at(i).at(j);
				}
		}
	}
	return VAMax;
}

float QOscillogramWidget::getIMax(int index)
{
	float IAMax = 0;
	
	int nCurCount = getSttChGroupResource_CurCnt();
	
	for (int i = 0; i<nCurCount; i++)
	{
		for(int j = 0; j<CHANLEPOINT; j++)
		{
			if(i<m_WaveDataList_Cur.size()&& j<m_WaveDataList_Cur.at(i).size())
			{
				if(m_WaveDataList_Cur.at(i).at(j) > IAMax)
				{
					IAMax = m_WaveDataList_Cur.at(i).at(j);
				}
			}
		}
	}
	return IAMax;
}

void QOscillogramWidget::InitArrUIValue()
{
	//return;
	int k = 0;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;
	if(nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}
	int nVolCount = getSttChGroupResource_Vol_ChCnt();
	for(k = 0; k < nVolCount; k++)
	{
		for(int j = 0; j< nMaxHarmNum; j++)
		{
			m_pArrUIVol[k].Harm[j].m_bSelect = true;
			m_pArrUIVol[k].Harm[j].nIndex = j;
			if(j==0)
			{
				m_pArrUIVol[k].Harm[j].fAmp = 0;
				m_pArrUIVol[k].Harm[j].fContent = 0;
			}
			else if(j==1)
			{
				m_pArrUIVol[k].Harm[j].fAmp = 57.74;
				m_pArrUIVol[k].Harm[j].fContent = 100.00;
			}
			else
			{
				m_pArrUIVol[k].Harm[j].fAmp = 0;
				m_pArrUIVol[k].Harm[j].fContent = 0;
			}
		}
	}

	int nCurCount = getSttChGroupResource_CurCnt();
	for(int k = 0; k < nCurCount; k++)
	{
		for(int j = 0; j < nMaxHarmNum; j++)
		{
			m_pArrUICur[k].Harm[j].m_bSelect = true;
			m_pArrUICur[k].Harm[j].nIndex = j;
			if(j==0)
			{
				m_pArrUICur[k].Harm[j].fAmp = 0;
				m_pArrUICur[k].Harm[j].fContent = 0;
			}
			else if(j==1)
			{
				m_pArrUICur[k].Harm[j].fAmp = 5;
				m_pArrUICur[k].Harm[j].fContent = 100.00;
			}
			else
			{
				m_pArrUICur[k].Harm[j].fAmp = 0;
				m_pArrUICur[k].Harm[j].fContent = 0;
			}
		}
	}
}

void QOscillogramWidget::InitArrUIContent()
{
	int k = 0;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;
	if(nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}
	int nVolCount = getSttChGroupResource_Vol_ChCnt();
	for(k = 0; k < nVolCount; k++)
	{
		m_pArrUIVol[k].Harm[1].fContent = 100.00;
	}

	int nCurCount = getSttChGroupResource_CurCnt();
	for(int k = 0; k < nCurCount; k++)
	{
		m_pArrUICur[k].Harm[1].fContent = 100.00;
	}
	
}

void QOscillogramWidget::HarmSetZero()
{
	int k = 0;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;
	if(nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}

	int nVolCount = getSttChGroupResource_Vol_ChCnt();
	for(k = 0; k < nVolCount; k++)
	{
		for(int j = 0; j<nMaxHarmNum; j++)
		{
			m_pArrUIVol[k].Harm[j].m_bSelect = true;
			m_pArrUIVol[k].Harm[j].nIndex = j;
			if(j > 1)
			{
				m_pArrUIVol[k].Harm[j].fAmp = 0;
			}

		}
	}

		int nCurCount = getSttChGroupResource_CurCnt();
		for(int k = 0; k < nCurCount; k++)
		{
			for(int j = 0; j < nMaxHarmNum; j++)
			{
				m_pArrUICur[k].Harm[j].m_bSelect = true;
				m_pArrUICur[k].Harm[j].nIndex = j;
				if(j > 1)
				{
					m_pArrUICur[k].Harm[j].fAmp = 0;
				}
			}
		}
}

void QOscillogramWidget::selectDataChanged()
{
	if(m_pArrUICur == NULL || m_pArrUIVol == NULL)
		return;

	QVector<double>WaveVector;
	int k = 0;
	m_Hz = 50;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;

	if(nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}
	
	int nVoltCount = getSttChGroupResource_VolCnt();

	int nDrawFlag = 0;
	for(k = 0; k < nVoltCount; k++)
	{
 		for(int i = 0;i < nMaxHarmNum; i++)
		{
			if(m_pArrUIVol[k].Harm[i].m_bSelect)
			{
				nDrawFlag = 1;
				break;
			}
		}
	}

	if(nDrawFlag == 0)
	{
		m_WaveDataList_Vol.clear();

		for (k = 0; k < nVoltCount; k++)
		{
			m_WaveDataList_VolTemp[k].fill(0.0);  // 将所有元素填充为 0.0
		}

		m_WaveDataList_Vol.append(m_WaveDataList_VolTemp);
	}
	else
	{
		m_WaveDataList_Vol.clear();
		for(k = 0; k<nVoltCount; k++)
		{
			generateOneChData(&m_pArrUIVol[k], WaveVector);
			m_WaveDataList_Vol.append(WaveVector);
			if(m_nVolFlag ==0)
			{
				m_WaveDataList_VolTemp.append(WaveVector);
			}
		}

		m_nVolFlag = 1;
	}

	int nCurCount = getSttChGroupResource_CurCnt();
	nDrawFlag = 0;
	for( k = 0; k < nCurCount; k++)
	{
		for(int i = 0; i< nMaxHarmNum; i++)
		{
			if(m_pArrUICur[k].Harm[i].m_bSelect)
			{
				nDrawFlag = 1;
				break;
			}
		}
	}

	if(nDrawFlag ==0)
	{
		m_WaveDataList_Cur.clear();

		for (k = 0; k < nCurCount; k++)
		{
			m_WaveDataList_CurTemp[k].fill(0.0);  // 将所有元素填充为 0.0
		}

		m_WaveDataList_Cur.append(m_WaveDataList_CurTemp);
	}
	else
	{
		m_WaveDataList_Cur.clear();
		for(k = 0; k < nCurCount; k++)
		{
			generateOneChData(&m_pArrUICur[k], WaveVector);
			m_WaveDataList_Cur.append(WaveVector);

			if(m_nCurFlag == 0)
			{
				m_WaveDataList_CurTemp.append(WaveVector);
			}
		}	
			m_nCurFlag = 1;
		}

	exportOscillogram();
}
void QOscillogramWidget::exportOscillogram()
{
	float VMax = getVMax(1);

	if (abs(VMax) < 0.00001)
	{
		VMax = 100;
	}
	PlotOscillogram *pV = m_PlotList.at(0);
	pV->UpdateYInterval(VMax * RADIO);
	pV->clearCurve();
	
	CSttChResource *pChResource = NULL;

	int nIndex = 0;
	QColor color[4];
	color[0] = Qt::yellow;
	color[1] = Qt::green;
	color[2] = Qt::red;
	color[3] = Qt::lightGray;
	
	POS pos = m_oGroupResourceRef_Vol.GetHeadPosition();
	while(pos)
	{
		pChResource = (CSttChResource *)m_oGroupResourceRef_Vol.GetNext(pos);
		pV->insertCurve(pChResource->m_strName, m_WaveDataList_Vol[nIndex], color[nIndex]);
		if(m_CheckBoxList_Vol[nIndex]->isChecked())
		{
			pV->showCurve(pChResource->m_strName, true);
		}
		else
		{
			pV->showCurve(pChResource->m_strName, false);
		}
		nIndex++;
	}

	pV->replot();

	PlotOscillogram *pI = m_PlotList.at(1);
	float IMax = getIMax(1);
	if(IMax <= 10)
	{
		IMax = 10;
	}
	else if(IMax > 10 && IMax <= 20)
	{
		IMax = 20;
	}
	else if(IMax >20 && IMax <= 30)
	{
		IMax = 30;
	}
	else
	{
		IMax = 40;
	}

	pI->UpdateYInterval(IMax);
	pI->clearCurve();

	pos = m_oGroupResourceRef_Cur.GetHeadPosition();
	nIndex = 0;
	while(pos)
	{
		pChResource = (CSttChResource *)m_oGroupResourceRef_Cur.GetNext(pos);
		pI->insertCurve(pChResource->m_strName, m_WaveDataList_Cur[nIndex], color[nIndex]);
		if(m_CheckBoxList_Cur[nIndex]->isChecked())
		{
			pI->showCurve(pChResource->m_strName, true);
		}
		else
		{
			pI->showCurve(pChResource->m_strName, false);
		}
		nIndex++;
	}

	pI->replot();
}

void QOscillogramWidget::generateOneChData(tmt_channel *pCh, QVector<double>&vector)
{
	vector.clear();

	QVector<float>ContainVector;
	QVector<float>PhaseVector;
	QVector<float>fXSVector;
	QVector<float>fwVector;

	long nMaxHarmNum = g_oLocalSysPara.m_nMaxHarmCount;

	if(nMaxHarmNum > MAX_HARM_COUNT)
	{
		nMaxHarmNum = MAX_HARM_COUNT;
		g_oLocalSysPara.m_nMaxHarmCount = MAX_HARM_COUNT;
	}


	long nSinCnt = SINCOUNT;
	float fxxs = 0.02 * m_Hz * SINCOUNT/CIRCLECOUNT;
	float fAngle = 0;

	for(int i = 1;i < nMaxHarmNum; i++)
	{
		if(!pCh->Harm[i].m_bSelect)
		{
			continue;
		}

		fAngle = pCh->Harm[i].fAngle;
		LimitAngle360(fAngle);
		PhaseVector.append(fAngle * SINCOUNT / 360.0);
		ContainVector.append(pCh->Harm[i].fContent);
		fXSVector.append(fxxs * (pCh->Harm[i].nIndex));
		fwVector.append(0);
	}

	//yzj 2023.12.13 计算间谐波
	tmt_ChannelHarm oInterHarm = pCh->InterHarm;
	fAngle = oInterHarm.fAngle;
	LimitAngle360(fAngle);
	PhaseVector.append(fAngle * SINCOUNT / 360.0);
	ContainVector.append(oInterHarm.fContent);
	fXSVector.append(fxxs * oInterHarm.fFreq / m_Hz);
	fwVector.append(0);

	for(int j = 0; j < CHANLEPOINT; j++)
	{
		float fv = 0;
		float nIndex = 0;
		for(int i = 1; i < nMaxHarmNum; i++)
		{
			if(!pCh->Harm[i].m_bSelect)
			{
				continue;
			}
			fv += pCh->Harm[i].fContent / 100 * sinData[(unsigned long)(fwVector[nIndex] + PhaseVector[nIndex])];
			nIndex++;
		}

		//yzj 2023.12.13 计算间谐波
		fv += oInterHarm.fContent / 100 * sinData[(unsigned long)(fwVector[fwVector.size() - 1] + PhaseVector[PhaseVector.size() - 1])];

		float fv2 = (double)G2 * fv * pCh->Harm[1].fAmp + pCh->Harm[0].fAmp;

		for(int i = 0; i < fwVector.size(); i++)
		{
			fwVector[i] += fXSVector[i];
			if(fwVector[i] > nSinCnt)
			{
				fwVector[i] -= nSinCnt;
			}
		}

		vector.append(fv2);
	}
}

// void QOscillogramWidget::resizeEvent(QResizeEvent * resizeEvent)
// {
// 	QWidget::resizeEvent(resizeEvent);
// }

void QOscillogramWidget::setArrUIVOL(tmt_channel *pArrUIVOL)
{
	m_pArrUIVol = pArrUIVOL;
}

void QOscillogramWidget::setArrUICUR(tmt_channel *pArrUICUR)
{
	m_pArrUICur = pArrUICUR;
}

void QOscillogramWidget::setSttTestResource(CSttTestResourceBase *pSttTestResource)
{
	m_pSttTestResource = pSttTestResource;
}

void QOscillogramWidget::getSttChGroupResource_Vol()
{
	POS pos = m_pSttTestResource->m_oListGroups.GetHeadPosition();
	CSttChGroupResource *pObj = NULL;
	m_oGroupResourceRef_Vol.RemoveAll();

	int nIndex = 0;
	while(pos)
	{
		pObj = (CSttChGroupResource *)m_pSttTestResource->m_oListGroups.GetNext(pos);
		if(pObj->HasVolCh())
		{
			if(nIndex == m_nGroupIndex)
			{
				pObj->GetVolChs(&m_oGroupResourceRef_Vol);
				//nIndex++;
			}
			nIndex++;
		}
	}
}

void QOscillogramWidget::getSttChGroupResource_Cur()
{
	POS pos = m_pSttTestResource->m_oListGroups.GetHeadPosition();
	CSttChGroupResource *pObj = NULL;
	m_oGroupResourceRef_Cur.RemoveAll();
	int nIndex = 0;
	while(pos)
	{
		pObj = (CSttChGroupResource *)m_pSttTestResource->m_oListGroups.GetNext(pos);
		if(pObj->HasCurCh())
		{
			if(nIndex == m_nGroupIndex)
			{
				pObj->GetCurChs(&m_oGroupResourceRef_Cur);
				//nIndex++;
			}
			nIndex++;
		}
	}
}

int QOscillogramWidget::getSttChGroupResource_VolCnt()
{
	return m_oGroupResourceRef_Vol.GetCount();
}

int QOscillogramWidget::getSttChGroupResource_CurCnt()
{
	return m_oGroupResourceRef_Cur.GetCount();
}

int QOscillogramWidget::getSttChGroupResource_Vol_ChCnt()
{
	return m_oGroupResourceRef_Vol.GetCount();
}

int QOscillogramWidget::getSttChGroupResource_Cur_ChCnt()
{
	return m_oGroupResourceRef_Cur.GetCount();
}

void QOscillogramWidget::resizeEvent(QResizeEvent * resizeEvent)
{
	QWidget::resizeEvent(resizeEvent);
}
