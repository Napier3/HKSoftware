//CPMData.c
#include "stdafx.h"
#include "PMData.h"


CTestControl* CPMData::m_pTestControl = NULL;

CPMData::CPMData()
{
	InitData();
}

CPMData::~CPMData()
{
}

///////////////////////////////////////////////////////////////////////
//						Out���ݣ�
///////////////////////////////////////////////////////////////////////
void CPMData::InitOutData()
{
	int i;
	m_stPMOutData.fFreq = 0.0f;
	m_stPMOutData.nU4Mode = 0;
	m_stPMOutData.fFPoint = 0;
	for(i=0;i<PNUM_CH;i++)
	{
		m_stPMOutData.fAnlg[i]	= 0.0f;	
		m_stPMOutData.fPhase[i]	= 0.0f;	
		m_stPMOutData.nFD[i]	= 0;
		m_stPMOutData.fALP[i] = 0.0f;
	}
	UpdateOutDataOld();

	for(i=0;i<5;i++)
	{
		m_fTmp[i]	= 0.0f;	
		m_nCurTmpZone[i]  = 0;
	}
}

BOOL CPMData::IsOutDataChanged()
{
	int i;
	//�ж����ݱ仯
	BOOL bTemp1 = FALSE;
	if(m_stPMOutDataOld.fFreq != m_stPMOutData.fFreq)	bTemp1 = TRUE;
	if(m_stPMOutDataOld.nU4Mode	!= m_stPMOutData.nU4Mode)	bTemp1 = TRUE;
	if(m_stPMOutDataOld.fFPoint	!= m_stPMOutData.fFPoint)	bTemp1 = TRUE;
	for(i=0;i<PNUM_CH;i++)
	{
		if(m_stPMOutDataOld.fAnlg[i]	!= m_stPMOutData.fAnlg[i])	bTemp1 = TRUE;	
		if(m_stPMOutDataOld.fPhase[i]	!= m_stPMOutData.fPhase[i])	bTemp1 = TRUE;	
		if(m_stPMOutDataOld.nFD[i]	!= m_stPMOutData.nFD[i])	bTemp1 = TRUE;
		if(m_stPMOutDataOld.fALP[i]	!= m_stPMOutData.fALP[i])	bTemp1 = TRUE;
	}
	UpdateOutDataOld();
	return bTemp1;
}

void CPMData::UpdateOutDataOld()
{
	int i;
	m_stPMOutDataOld.fFreq = m_stPMOutData.fFreq;
	m_stPMOutDataOld.nU4Mode = m_stPMOutData.nU4Mode;
	m_stPMOutDataOld.fFPoint = m_stPMOutData.fFPoint;
	for(i=0;i<PNUM_CH;i++)
	{
		m_stPMOutDataOld.fAnlg[i]	= m_stPMOutData.fAnlg[i];	
		m_stPMOutDataOld.fPhase[i]	= m_stPMOutData.fPhase[i];	
		m_stPMOutDataOld.nFD[i]	= m_stPMOutData.nFD[i];
		m_stPMOutDataOld.fALP[i] = m_stPMOutData.fALP[i];
	}
}

//	���ֵ��仯
//	�����Զ������ġ����ݷ�ֵ�ı��´���λֵ
void CPMData::CheckFDChg()
{
	ASSERT(m_pTestControl != NULL);

	double fCompstPonit[PNUM_CH][10] = {
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,20.0f,4.0f,1.0f,0.2f,},    // *0.0001mA = 0.1uA
		{3.0f,m_pTestControl->m_fMaxU,130.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,130.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,130.0f,60.0f,},   // *0.0001V = 100mV
		{8.0f,10.0f,2.0f,0.5f,0.1f,-0.1f,-0.5f,-2.0f,-10.0f,},
		{1.0f,20.0f,},
		{1.0f,10.0f,},
		{2.0f,456.0f,91.2f,},
	};  // *0.0001V = 100mV
	double fCompstPonit2[PNUM_CH][10] = {
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,20.0f,4.0f,1.0f,0.2f,},    // *0.0001mA = 0.1uA
		{3.0f,m_pTestControl->m_fMaxU,300.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,300.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,300.0f,60.0f,},   // *0.0001V = 100mV
		{8.0f,10.0f,2.0f,0.5f,0.1f,-0.1f,-0.5f,-2.0f,-10.0f,},
		{1.0f,20.0f,},
		{1.0f,10.0f,},
		{2.0f,456.0f,91.2f,},
	};  // *0.0001V = 100mV
	
	//����û������÷����˱仯������仯��ĵ�λ������Զ������Ļ����͵�λ���ֵ
	int i,j,Num,temp;
	unsigned char nFlag=0;
	double fTemp;

	for(i=0;i<PNUM_CH;i++)
	{
		if(m_stPMOutData.nFD[i] == 0)	//�Զ�����
		{
			fTemp = m_stPMOutData.fAnlg[i];
			//if(fTemp<0.0f) fTemp= -fTemp;

			Num = (int)fCompstPonit[i][0];
			if(fTemp ==0)
			{
				temp=Num-1;
				m_fFDMax[i] = fCompstPonit2[i][Num];
			}
			else
			{
				for(j=0;j<Num;j++)
				{
					if(fTemp > fCompstPonit[i][j+2] || j == Num-1) 
					{
						temp=j;
						m_fFDMax[i] = fCompstPonit2[i][j+1];
						break;
					}
				}
			}
			m_nFDSet[i] = temp;
		}
		else
		{
			m_nFDSet[i] = m_stPMOutData.nFD[i] - 1;
			m_fFDMax[i] = fCompstPonit2[i][m_nFDSet[i]+1];
		}
		
		if(m_fFDMax[i]<0) m_fFDMax[i] = 0-m_fFDMax[i];
		m_nAutoSetFD[i] = 0;	//�´����ݶ����趨��λ���������滻��
	}
}


void CPMData::InitData()
{
	ASSERT(m_pTestControl != NULL);
	int i,j,nn;
	double fCompstPonit[PNUM_CH][10] = {
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,20.0f,4.0f,1.0f,0.2f,},    // *0.0001mA = 0.1uA
		{3.0f,m_pTestControl->m_fMaxU,130.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,130.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,130.0f,60.0f,},   // *0.0001V = 100mV
		{8.0f,10.0f,2.0f,0.5f,0.1f,-0.1f,-0.5f,-2.0f,-10.0f,},
		{1.0f,20.0f,},
		{1.0f,10.0f,},
		{2.0f,456.0f,91.2f,},
	};  // *0.0001V = 100mV
	double fCompstPonit2[PNUM_CH][10] = {
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,m_pTestControl->m_fMaxI,2.6f,0.65f,0.13f,},   // *0.0001A = 100uA
		{4.0f,20.0f,4.0f,1.0f,0.2f,},    // *0.0001mA = 0.1uA
		{3.0f,m_pTestControl->m_fMaxU,300.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,300.0f,60.0f,},   // *0.0001V = 100mV
		{3.0f,m_pTestControl->m_fMaxU,300.0f,60.0f,},   // *0.0001V = 100mV
		{8.0f,10.0f,2.0f,0.5f,0.1f,-0.1f,-0.5f,-2.0f,-10.0f,},
		{1.0f,20.0f,},
		{1.0f,10.0f,},
		{2.0f,456.0f,91.2f,},
	};  // *0.0001V = 100mV
	
	for (j=0;j<PNUM_CH;j++)
	{
		m_PMData[j].InitOutData();
		if (j==3 || j==7 || j==8 || j==9)
		{
			m_PMData[j].m_stCHData.m_nDC = 1;			//ֱ����1��������0��
		}
		else
		{
			m_PMData[j].m_stCHData.m_nDC = 0;			//ֱ����1��������0��
		}
		nn =  (unsigned char)fCompstPonit[j][0];
		m_PMData[j].m_stCHData.m_nFDNum = nn;
		for(i=0;i<nn;i++)
		{
			m_PMData[j].m_stCHData.m_fFDMax[i] = fCompstPonit2[j][i + 1];
		}
	}
	
	UpdateOutDataOld2();
	m_nVarChanged = IsOutDataChanged2();

	//////////////////////////////////////
	
	m_fFreqMax = 65.0f;				//Ƶ�����ֵ
	m_fFreqMin = 45.0f;				//Ƶ����Сֵ
	m_fPhaseMax = 360.0f;				//��λ���ֵ
	m_fPhaseMin = -360.0f;				//��λ��Сֵ
	m_nHarmMax = m_pTestControl->m_nHarmCount;		//г���������ֵ
	
	m_lCmpstF = 0;  //Ƶ���������� = 41841;
	
	//������������
	m_iSampleMode = 0;     //ֱ��������ʽ
	m_iSampleMode2 = 0;     //ֱ�������ֵ�
	m_iU4Mode = 0;    //����������
	m_iInputStatus = 0xffff;    //����
	m_iAlarmStatus = 0xffff;    //����
	m_iOutStatus = 0;      //����
	m_iDSPState = 0;
	
	//�¶Ȳ����������й�
	//m_nRom[6][9];    //�¶ȴ�����ID��5�� 
	for(i=0;i<5;i++)	m_fTmp[i] = 0.0f;    //5���¶ȴ����������¶�ֵ
	
	//����������
	for(i=0;i<5;i++)	m_ftime_S[i] = 0.0f;
	for(i=0;i<4;i++)	m_nState_S[i] = 0;
}

void CPMData::UpdateOutDataOld2()
{
	int j;
	for (j=0;j<PNUM_CH;j++)
	{
		m_PMData[j].UpdateOutDataOld();
	}
}

////////////////////////////////////////////////////////////////////////////////

unsigned char CPMData::IsOutDataChanged2()
{
	unsigned char nTemp1 = 0;
	int j;
	for (j=0;j<PNUM_CH;j++)
	{
		if(m_PMData[j].IsOutDataChanged() != 0)	nTemp1 = 1;
	}
	
	UpdateFDChg();
	UpdateOutDataOld2();
	return nTemp1;
}


////////////////////////////////////////////////////////////////////////////////

//	���ֵ��仯
//	�����Զ������ġ����ݷ�ֵ�ı��´���λֵ
void CPMData::UpdateFDChg()
{
	int j;
	for (j=0;j<PNUM_CH;j++)
	{
		m_PMData[j].UpdateFDChg();
	}
}

