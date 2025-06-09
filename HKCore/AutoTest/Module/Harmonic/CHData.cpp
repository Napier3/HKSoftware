//CHData.c
#include "stdafx.h"
#include "CHData.h"

CCHData::CCHData()
{
}

CCHData::~CCHData()
{
}

void CCHData::InitOutData()
{
	int i,j;

	m_stCHData.m_fFreq = 0.0f;
	m_stCHData.m_fAnlg	= 0.0f;	
	m_stCHData.m_fPhase = 0.0f;
	
	m_stCHData.m_nDC = 0;			//直流（1）或交流（0）

	m_stCHData.m_nAutoSetFD = 1;		//自动换档（1）或固定档位（0）
	m_stCHData.m_nFD = 0;				//最大档
	m_stCHData.m_nFDNum = 8;

	m_stCHData.m_fCmpstLP = 0.0f;

	for(i=0;i<8;i++)
	{
		m_stCHData.m_fFDMax[i] = 1.0f;
	}

	for(i=0;i<8;i++)
	{
		m_stCHData.m_fCmpst[i][0] = 0.0f;
		m_stCHData.m_fCmpst[i][1] = 1.0f;
		m_stCHData.m_fCmpst[i][2] = 0.0f;

		for(j=0;j<15;j++)
		{
			m_stCHData.m_fCmpstT[j][i][0] = 0.0f;
			m_stCHData.m_fCmpstT[j][i][1] = 1.0f;
			m_stCHData.m_fCmpstT[j][i][2] = 0.0f;
		}
		for(j=0;j<50;j++)
		{
			m_stCHData.m_fCmpstH[j][i][0] = 1.0f;
			m_stCHData.m_fCmpstH[j][i][1] = 0.0f;
		}
	}

	for(i=0;i<50;i++)
	{
		m_stCHData.m_fAnlgH[i] = 0.0f;
		m_stCHData.m_fPhaseH[i] = 0.0f;
	}

	UpdateOutDataOld();
}

void CCHData::UpdateOutDataOld()
{
	int i,j;
	
	m_stCHDataOld.m_fFreq = m_stCHData.m_fFreq;
	m_stCHDataOld.m_fAnlg	= m_stCHData.m_fAnlg;	
	m_stCHDataOld.m_fPhase = m_stCHData.m_fPhase;
	
	m_stCHDataOld.m_nDC = m_stCHData.m_nDC;			//直流（1）或交流（0）
	
	m_stCHDataOld.m_nAutoSetFD = m_stCHData.m_nAutoSetFD;		//自动换档（1）或固定档位（0）
	m_stCHDataOld.m_nFD = m_stCHData.m_nFD;				//最大档
	m_stCHDataOld.m_nFDNum = m_stCHData.m_nFDNum;
	
	m_stCHDataOld.m_fCmpstLP = m_stCHData.m_fCmpstLP;
	
	for(i=0;i<8;i++)
	{
		m_stCHDataOld.m_fFDMax[i] = m_stCHData.m_fFDMax[i];
	}

	for(i=0;i<8;i++)
	{
		m_stCHDataOld.m_fCmpst[i][0] = m_stCHData.m_fCmpst[i][0];
		m_stCHDataOld.m_fCmpst[i][1] = m_stCHData.m_fCmpst[i][1];
		m_stCHDataOld.m_fCmpst[i][2] = m_stCHData.m_fCmpst[i][2];
		
		for(j=0;j<15;j++)
		{
			m_stCHDataOld.m_fCmpstT[j][i][0] = m_stCHData.m_fCmpstT[j][i][0];
			m_stCHDataOld.m_fCmpstT[j][i][1] = m_stCHData.m_fCmpstT[j][i][1];
			m_stCHDataOld.m_fCmpstT[j][i][2] = m_stCHData.m_fCmpstT[j][i][2];
		}
		for(j=0;j<50;j++)
		{
			m_stCHDataOld.m_fCmpstH[j][i][0] = m_stCHData.m_fCmpstH[j][i][0];
			m_stCHDataOld.m_fCmpstH[j][i][1] = m_stCHData.m_fCmpstH[j][i][1];
		}
	}
	
	for(i=0;i<50;i++)
	{
		m_stCHDataOld.m_fAnlgH[i] = m_stCHData.m_fAnlgH[i];
		m_stCHDataOld.m_fPhaseH[i] = m_stCHData.m_fPhaseH[i];
	}
}

////////////////////////////////////////////////////////////////////////////////

unsigned char CCHData::IsOutDataChanged()
{
	int i;
	unsigned char nTemp1 = 0;
	
	//判断数据变化
	if(m_stCHDataOld.m_fFreq != m_stCHData.m_fFreq)	nTemp1 = 1;
	if(m_stCHDataOld.m_fAnlg	!= m_stCHData.m_fAnlg)	nTemp1 = 1;	
	if(m_stCHDataOld.m_fPhase != m_stCHData.m_fPhase)	nTemp1 = 1;
	
	if(m_stCHDataOld.m_nDC != m_stCHData.m_nDC)	nTemp1 = 1;

	if(m_stCHDataOld.m_fCmpstLP != m_stCHData.m_fCmpstLP)	nTemp1 = 1;
	
	if(m_stCHDataOld.m_nAutoSetFD != m_stCHData.m_nAutoSetFD)	nTemp1 = 1;
	if(m_stCHDataOld.m_nFD != m_stCHData.m_nFD)	nTemp1 = 1;

	for(i=0;i<50;i++)
	{
		if(m_stCHDataOld.m_fAnlgH[i] != m_stCHData.m_fAnlgH[i])	nTemp1 = 1;
		if(m_stCHDataOld.m_fPhaseH[i] != m_stCHData.m_fPhaseH[i])	nTemp1 = 1;
	}
	
	UpdateFDChg();
	UpdateOutDataOld();
	return nTemp1;
}


////////////////////////////////////////////////////////////////////////////////

//	检查分档变化
//	对于自动换档的、根据幅值改变下传档位值
void CCHData::UpdateFDChg()
{
	//如果用户的设置发生了变化，计算变化后的档位（如果自动换档的话）和档位最大值
	int j,Num,nn;
	double fTemp;
	double fMax[9];

	if(m_stCHData.m_nAutoSetFD == 1)	//自动换档
	{
		Num = m_stCHData.m_nFDNum;

		for(j=0;j<9;j++)
		{
			fMax[j] = 0;
		}
		for(j=0;j<Num;j++)
		{
			if(m_stCHData.m_fFDMax[j] >= 0) 
			{
				fMax[j] = m_stCHData.m_fFDMax[j];
			}
			else
			{
				fMax[j+1] = m_stCHData.m_fFDMax[j];
			}
		}

		fTemp = m_stCHData.m_fAnlg;
		for(j=0;j<Num;j++)
		{
			if(fTemp > fMax[j+1] || j == Num-1) 
			{
				nn = j;
				break;
			}
		}
		m_stCHData.m_nFD = nn;
	}
}

