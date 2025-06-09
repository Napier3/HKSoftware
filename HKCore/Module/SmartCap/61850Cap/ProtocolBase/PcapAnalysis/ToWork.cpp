
#include "StdAfx.h"
#include "ToWork.h"

#include "GetInforFormVector.h"


CDoMessage  *  g_pDoMesage;
CString                 g_strFileName;

//CDoMessage  *  g_pDoMesage;
//CString                 g_strFileName;

CToWork::CToWork(void)
{
	g_pDoMesage  = CDoMessage::Create();
}

CToWork::~CToWork(void)
{
	CDoMessage::Release();

	//delete g_pDoMesage;
	//g_pDoMesage = NULL;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#define XSTARTPOS 0
#define YSTARTPOS 0
#define VAVERDISTANCE 100
long CToWork::GetMaxValue(std::vector<int> & pChanData  ,  float & fFirstArc  ,  int &nZLNum)
{
	long nMax = 0;
	long nUpV;
	long nValue;
	int nZF0 = 0;//负数-1，正数1  ,  零0
	int nR = 0;//是否找初值角度
	std::vector<int> ZLNumVector;
	for (long chanid =0;chanid<pChanData.size();chanid++)
	{
		if (chanid==0)
		{
			nValue= pChanData[chanid];	
			nUpV = nValue;
			if (nValue>0)
			{
				nZF0 = 1;
			}
			else
			{
				if (nValue<0)
				{
					nZF0 = -1;
				}
			}
			continue;
		}
		nValue= pChanData[chanid];

		if (abs(nValue)>nMax)
		{
			nMax = abs(nValue);
		}
		else if (nValue==nUpV)
		{
			//直流情况
			ZLNumVector.push_back(chanid);
			nUpV = nValue;
			continue;
		}
		nUpV = nValue;
		if(nR ==0)
		{
			if (nValue>0&&nZF0==-1)//负变正
			{
				if(chanid>20)
				{
					fFirstArc = 180-4.5*(40+chanid);
				}
				else
				{
					fFirstArc = -4.5*chanid;
				}

				nR = 1;
			}
			else
			{
				if (nValue<0&&nZF0==1)//正变负
				{
					if(chanid>20)
					{
						fFirstArc = 4.5*(40-chanid);
					}
					else
					{
						fFirstArc = 180-4.5*chanid;
					}
					nR = 1;
				}
				else
				{
					if (nValue!=0&&nZF0==0)//0变正或负
					{
						int t_C = (4.5*(chanid-1))/180;
						fFirstArc = 180-(4.5*(chanid-1)-t_C*180);
						nR = 1;
					}

				}
			}
		}
	}
	nZLNum = ZLNumVector.size();
	return nMax;
}

void CToWork::GetChanValueToVector91( Content &content  ,  CMacDifWaveData &MacDif)
{
	int nASDUNum =1;
	int nCount =1;	
	int nOffset =0;
	int tt1;
	int nStartPos =0;
	int nLength = 0;
	int nChanNum = 0;
	//	std::vector<std::vector<int>> t_datavector;
	int nItemSize = content.m_Vector.size();
	int nSpecial = 0;
	std::vector<int> ASDUStartPosVector;
	for (int i =0;i<nItemSize;i++) 
	{
		if (i==0)
		{
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];
			CByteArray byArray;
			CGetInforFormVector::GetProtocolType(g_pDoMesage  ,  Pro  ,  tt1  ,  tt1  ,  tt1  ,  nOffset);	
			CGetInforFormVector::GetPackHexDataPart(g_pDoMesage  ,  Pro  ,  byArray);
			BYTE t1 =  byArray.GetAt(28+nOffset);
			BYTE t2 =  byArray.GetAt(29+nOffset);
			nASDUNum = t2+t1*pow(2.0  ,  8);
			MacDif.m_nASDUNum = nASDUNum;
			t1 = byArray.GetAt(30+nOffset);
			t2 = byArray.GetAt(31+nOffset);
			nChanNum = t2+t1*pow(2.0  ,  8)-20;
			nStartPos = 44+nOffset;
			for (int n =0;n<nASDUNum;n++)
			{
				nCount = nChanNum/2;
				if (nCount == 0)
				{
					//ExitThread(0);  mym 
				}
				else
				{
					int nStart = nStartPos;
					ASDUStartPosVector.push_back(nStartPos);
					for (int m =0;m<nCount;m++)
					{	
						if (n==0)
						{
							std::vector<int> nValue;
							BYTE t1  ,  t2;
							t1 = byArray.GetAt(nStart);
							t2 = byArray.GetAt(nStart+1);
							if ((t1>>7)&0x01==1)
							{
								int t_V =0xFFFF-(t2+t1*pow(2.0  ,  8));
								int t = -(t_V+1);
								nValue.push_back(t);
							}
							else
							{
								int t_V =t2+t1*pow(2.0  ,  8);
								nValue.push_back(t_V);

							}
							nStart  +=  2;
							MacDif.m_datavector.push_back(nValue);
							nSpecial =0;
						}
						else
						{
							std::vector<int> &nValue = MacDif.m_datavector[m];
							BYTE t1  ,  t2;
							t1 = byArray.GetAt(nStart);
							t2 = byArray.GetAt(nStart+1);
							if ((t1>>7)&0x01==1)
							{
								int t_V =0xFFFF-(t2+t1*pow(2.0  ,  8));
								int t = -(t_V+1);
								nValue.push_back(t);
							}
							else
							{
								int t_V =t2+t1*pow(2.0  ,  8);
								nValue.push_back(t_V);

							}
							nStart  +=  2;
							MacDif.m_datavector.push_back(nValue);
							nSpecial =0;
						}

					}
					nStartPos  +=  nCount*2;
					nStartPos  +=  22;
				}

			}
		}	
		else
		{
			///////////////////////////////////////////////
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];	
			int nBeginPos = Pro.m_nHeadStartPos+16;
			int t_V  ,  t_V1;
			for (int n =0;n<nASDUNum;n++)
			{
				int nSPos = ASDUStartPosVector[n];
				int nStart = nBeginPos+nSPos;
				for (int m =0;m<nCount;m++)
				{	
					std::vector<int> &nValue = MacDif.m_datavector[m];
					int t1  ,  t2;
					t1 = g_pDoMesage->DataArray.GetAt(nStart);
					t2 = g_pDoMesage->DataArray.GetAt(nStart+1);
					if ((t1>>7)&0x01==1)
					{
						t_V1 =0;
						t_V1 = t_V1|t2;
						t_V1 = t_V1|t1<<8;				
						t_V =0xFFFF-t_V1;
						nValue.push_back(-(t_V+1));

					}
					else
					{
						t_V1 =0;
						t_V1 = t_V1|t2;
						t_V1 = t_V1|t1<<8;
						nValue.push_back(t_V1);	
					}
					nStart  +=  2;

				}
			}
		}
	}
	//////////////////////转换成坐标值////////////////////////////////
	MacDif.m_nPonitSize = nItemSize*nASDUNum;
	int t_wavenum  = nCount;
	MacDif.m_WavetSize = t_wavenum;
	int t_FK = 2;
	for (int waveId =0;waveId<t_wavenum;waveId++)
	{
		int t_s =MacDif.p_WavePoint.size();
		if (t_s!=t_wavenum)
		{	
			std::vector<int> &nValue = MacDif.m_datavector[waveId];
			int nDataSize =  nValue.size();
			MacDif.m_nPonitSize = nValue.size();
			float t_FirstArc = 0.0;
			int t_ZLNum;//直流情况，影响判断飞点
			long nMax = GetMaxValue(nValue  ,  t_FirstArc  ,  t_ZLNum);
			MacDif.m_FirstArcVector.push_back(t_FirstArc);
			if (nMax>0&&nMax<10000)
			{
				nMax =nMax*4;
			}	

			MacDif.m_MaxValueVector.push_back(nMax);
			MacDif.pPoint = new CPoint[nDataSize];

			CPoint pStartPos;
			pStartPos.x = XSTARTPOS;
			pStartPos.y = VAVERDISTANCE*(waveId+1);
			for (int chanid =0;chanid<nDataSize;chanid++)
			{
				int t_v = nValue[chanid];
				MacDif.pPoint[chanid].x = pStartPos.x+chanid*1;
				if (nMax!=0)
				{
					MacDif.pPoint[chanid].y = pStartPos.y-(VAVERDISTANCE/t_FK+(45.0/nMax)*t_v);
				}
				else MacDif.pPoint[chanid].y = pStartPos.y-VAVERDISTANCE/t_FK;

			}
			MacDif.p_WavePoint.push_back(MacDif.pPoint);
		}
	}

	/////////////////////////////////////////
}

/*

*/
void CToWork::GetChanValueToVector92(Content &content  ,   CMacDifWaveData &MacDif  ,   CAbnormalPos & AbnPos)
{
	int nASDUNum  = 1;
	int nCount  = 1;	
	int nOffset  = 0;
	int tt1;
	int nStartPos = 0;
	std::vector<int> m_StartPosVector;
	int nLength  =  0;
	int nDataSize  = content.m_Vector.size();
	MacDif.m_nPonitSize  =  nDataSize;
	int nSpecial  = 0;
	BOOL bSMVFactorChangeFlag;
	for (int i  = 0; i < nDataSize; i++) 
	{
		bSMVFactorChangeFlag  =  FALSE;
		if (i==0)
		{
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];
			nASDUNum =  atoi(CGetInforFormVector::GetASN1Flag(g_pDoMesage  ,    Pro  ,    0x80));
			if (nASDUNum==0)
			{
				break;
			}
			MacDif.m_nASDUNum = nASDUNum;
			CByteArray byArray;
			CGetInforFormVector::GetPackHexDataPart(g_pDoMesage  ,   Pro  ,   byArray);
			CGetInforFormVector::GetProtocolType(g_pDoMesage  ,   Pro  ,   tt1  ,   tt1  ,   tt1  ,   nOffset);	
			for (int n = 0;  n < nASDUNum; n++)
			{
				CGetInforFormVector::Get92PrePacketChannelData(byArray  ,   nStartPos  ,   nLength  ,   nOffset  ,   n);
				nCount = nLength/8;
				if (nCount == 0)
				{
					/*ExitThread(0);*/
					return;
				}
				else
				{
					m_StartPosVector.push_back(nStartPos);
					int nStart =nStartPos;
					for (int m =0;m<nCount;m++)
					{	
						if (n==0)
						{
							std::vector<int> nValue;
							BYTE t1  ,  t2  ,  t3  ,  t4  ,  t5  ,  t6  ,  t7  ,  t8;
							if (nStart+7>=byArray.GetSize())
							{
								return;
							}
							t1 = byArray.GetAt(nStart);
							t2 = byArray.GetAt(nStart+1);
							t3 = byArray.GetAt(nStart+2);
							t4 = byArray.GetAt(nStart+3);	
							t5 = byArray.GetAt(nStart+4);
							t6 = byArray.GetAt(nStart+5);
							t7 = byArray.GetAt(nStart+6);
							t8 = byArray.GetAt(nStart+7);
							if (t1==0xFF)
							{
								int t_V = 0xFFFFFFFF-(t4+t3*pow(2.0  ,  8)+t2*pow(2.0  ,  16)+t1*pow(2.0  ,  24));
								nValue.push_back(-(t_V+1));
							}
							else
							{
								int t_V =t4+t3*pow(2.0  ,  8)+t2*pow(2.0  ,  16)+t1*pow(2.0  ,  24);
								nValue.push_back(t_V);
							}

							///判断品质是否异常	
							if (bSMVFactorChangeFlag == FALSE)
							{
								if(t5!=0||t6!=0||t7!=0||t8!=0)
								{
									bSMVFactorChangeFlag = TRUE;

									AbnPos.m_SMVFactorChangeGlobalPos.push_back(i);

									AbnPos.m_SMVFactorChangeContentPos.push_back(content.m_Vector[i]);

									AbnPos.m_AbnormalCurContentPos.push_back(i);

									AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

									g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

									Pro.SetAbronamlType(ABNORMAL_SMVFACTORCHANGE);
								}							
							}

							nStart  +=  8;
							MacDif.m_datavector.push_back(nValue);
							nSpecial =0;
						}
						else
						{
							std::vector<int> &nValue = MacDif.m_datavector[m]; ;
							BYTE t1  ,  t2  ,  t3  ,  t4;
							BYTE t5  ,  t6  ,  t7  ,  t8;
							if (nStart+7>=byArray.GetSize())
							{
								return;
							}
							t1 = byArray.GetAt(nStart);
							t2 = byArray.GetAt(nStart+1);
							t3 = byArray.GetAt(nStart+2);
							t4 = byArray.GetAt(nStart+3);
							t5 = byArray.GetAt(nStart+4);
							t6 = byArray.GetAt(nStart+5);
							t7 = byArray.GetAt(nStart+6);
							t8 = byArray.GetAt(nStart+7);
							if (t1==0xFF)
							{
								int t_V =0xFFFFFFFF-(t4+t3*pow(2.0  ,  8)+t2*pow(2.0  ,  16)+t1*pow(2.0  ,  24));
								nValue.push_back(-(t_V+1));
							}
							else
							{
								int t_V =t4+t3*pow(2.0  ,  8)+t2*pow(2.0  ,  16)+t1*pow(2.0  ,  24);
								nValue.push_back(t_V);

							}
							///判断品质是否异常			
							if (bSMVFactorChangeFlag == FALSE)
							{
								if(t5!=0||t6!=0||t7!=0||t8!=0)
								{
									bSMVFactorChangeFlag = TRUE;
									AbnPos.m_SMVFactorChangeGlobalPos.push_back(i);

									AbnPos.m_SMVFactorChangeContentPos.push_back(content.m_Vector[i]);

									AbnPos.m_AbnormalCurContentPos.push_back(i);

									AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

									g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

									Pro.SetAbronamlType(ABNORMAL_SMVFACTORCHANGE);
								}							
							}
							nStart  +=  8;
						}
					}
				}
			}
		}	
		else
		{
			///////////////
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];	
			int nBeginPos = Pro.m_nHeadStartPos + 16;
			int t_V  ,  t_V1;

			for (int n = 0;   n <  nASDUNum;  n++)
			{
				nStartPos = m_StartPosVector[n];
				int nStart = nBeginPos  +  nStartPos;
				for (int m = 0; m < nCount;m++)
				{	
					std::vector<int> &nValue = MacDif.m_datavector[m];
					BYTE t1  ,  t2  ,  t3  ,  t4;
					BYTE t5  ,  t6  ,  t7  ,  t8;

					t1 = g_pDoMesage->DataArray.GetAt(nStart);
					t2 = g_pDoMesage->DataArray.GetAt(nStart+1);
					t3 = g_pDoMesage->DataArray.GetAt(nStart+2);
					t4 = g_pDoMesage->DataArray.GetAt(nStart+3);
					t5 = g_pDoMesage->DataArray.GetAt(nStart+4);
					t6 = g_pDoMesage->DataArray.GetAt(nStart+5);
					t7 = g_pDoMesage->DataArray.GetAt(nStart+6);
					t8 = g_pDoMesage->DataArray.GetAt(nStart+7);
					if (t1==0xFF)
					{
						t_V1 =0;
						t_V1 = t_V1|t4;
						t_V1 = t_V1|t3<<8;
						t_V1 = t_V1|t2<<16;
						t_V1 = t_V1|t1<<24;				
						t_V =0xFFFFFFFF-t_V1;
						nValue.push_back(-(t_V+1));
					}
					else
					{
						t_V1 =0;
						t_V1 = t_V1|t4;
						t_V1 = t_V1|t3<<8;
						t_V1 = t_V1|t2<<16;
						t_V1 = t_V1|t1<<24;
						nValue.push_back(t_V1);	
					}
					///判断品质是否异常			
					if (bSMVFactorChangeFlag == FALSE)
					{
						if(t5!=0||t6!=0||t7!=0||t8!=0)
						{

							bSMVFactorChangeFlag = TRUE;

							AbnPos.m_SMVFactorChangeGlobalPos.push_back(i);

							AbnPos.m_SMVFactorChangeContentPos.push_back(content.m_Vector[i]);

							AbnPos.m_AbnormalCurContentPos.push_back(i);

							AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

							g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

							Pro.SetAbronamlType(ABNORMAL_SMVFACTORCHANGE);
						}							
					}
					nStart   +=   8;
				}
			}
		}
	}

	//////////////////////转换成坐标值////////////////////////////////
	int t_wavenum  = nCount;
	MacDif.m_WavetSize = t_wavenum;
	int t_FK = 2;
	for (int waveId = 0; waveId < t_wavenum; waveId++)
	{
		int t_s  = MacDif.p_WavePoint.size();
		if (MacDif.m_datavector.size()==0)
		{
			break;
		}
		if (t_s!=t_wavenum)
		{	
			std::vector<int> &nValue   =  MacDif.m_datavector[waveId];
			nDataSize = nValue.size();
			MacDif.m_nPonitSize = nDataSize;
			float t_FirstArc  = 0.0;
			int t_ZLNum;//直流情况，影响判断飞点
			long nMax = GetMaxValue(nValue  ,    t_FirstArc  ,    t_ZLNum);
			MacDif.m_FirstArcVector.push_back(t_FirstArc);
			//////////////////////////////判断飞点异常//////////////////////////////////
			//1.获取最大值
			//2.获取最大值的个数
			//3.最大值个数不符合实际，说明有飞点
			/*		
			std::vector<int> t_MaxValueNumVector;
			if(nMax!=0)
			{
			for (int t_N =0;t_N<nDataSize;t_N++)
			{
			if (nMax<abs(nValue[t_N])*1.05&&nMax>abs(nValue[t_N])*0.95)//飞点判据，试探性推测
			{
			t_MaxValueNumVector.push_back(t_N);
			}
			}
			int t_MaxNum = t_MaxValueNumVector.size();
			if (nDataSize>40)
			{
			int t_DifV = nDataSize-t_ZLNum;
			int t_CV = t_DifV/40-1;
			if(t_MaxNum<t_CV&&t_MaxNum<50)//说明有飞点  ,  超过100  ,  50个飞点无意义
			{	
			for (int t_FlyNum=0;t_FlyNum<t_MaxValueNumVector.size();t_FlyNum++)
			{
			int t_AP = t_MaxValueNumVector[t_FlyNum];
			std::vector<int>::iterator ret; 
			ret = std::find(AbnPos.m_SMVFlyPointGlobalPos.begin()  ,  AbnPos.m_SMVFlyPointGlobalPos.end()  ,  t_AP);
			if (ret!=AbnPos.m_SMVFlyPointGlobalPos.end())
			{
			continue;
			}	
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[t_AP]];
			AbnPos.m_SMVFlyPointGlobalPos.push_back(t_AP);
			AbnPos.m_SMVFactorChangeContentPos.push_back(content.m_Vector[t_AP]);
			AbnPos.m_AbnormalCurContentPos.push_back(t_AP);
			AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[t_AP]);
			g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[t_AP]);
			Pro.SetAbronamlType(ABNORMAL_SMVFLYPOINT);
			}
			}
			}
			}*/
			////////////////////////////////////////////////////////////////////////////
			if (nMax>0&&nMax<10000)
			{
				nMax =nMax*4;
			}	
			MacDif.m_MaxValueVector.push_back(nMax);
			MacDif.pPoint = new CPoint[nDataSize];
			CPoint pStartPos;
			pStartPos.x = XSTARTPOS;
			pStartPos.y = VAVERDISTANCE*(waveId+1);
			MacDif.m_WaveStartPosVector.push_back(pStartPos);
			for (int chanid =0;chanid<nDataSize;chanid++)
			{
				int t_v = nValue[chanid];
				MacDif.pPoint[chanid].x = pStartPos.x+chanid*1;
				if (nMax!=0)
				{
					MacDif.pPoint[chanid].y = pStartPos.y-(VAVERDISTANCE/t_FK+(45.0/nMax)*t_v);
				}
				else MacDif.pPoint[chanid].y = pStartPos.y-VAVERDISTANCE/t_FK;

			}
			MacDif.p_WavePoint.push_back(MacDif.pPoint);
		}
	}
	//////////////////////////////////////////
}

void CToWork::GetSMV92ChanFactorChange( Content &content)
{

}

void CToWork::GetMultiNoSync()
{
	int nASDUNum  = 1;
	int nCount = 1;	
	int nOffset = 0;
	int tt1;
	int nStartPos =0;
	int nAllCount = g_pDoMesage->m_92Vector.size();
	int nUpSmpCnt  =  0;
	for (int i = 0; i < nAllCount; i++)
	{
		CPacket & Pro = g_pDoMesage->m_NewPacketVector[g_pDoMesage->m_92Vector[i]];
		if(i==0)
		{
			int t_FindPos = 0;
			nASDUNum =  atoi(CGetInforFormVector::GetASN1Flag(g_pDoMesage  ,  Pro  ,  0x80));
			CGetInforFormVector::GetProtocolType(g_pDoMesage  ,  Pro  ,  tt1  ,  tt1  ,  tt1  ,  nOffset);
			nUpSmpCnt = CGetInforFormVector::GetSmpCntValue(g_pDoMesage  ,  Pro  ,  0x60  ,  nOffset);
		}
		int t_CurSmpCnt = CGetInforFormVector::GetSmpCntValue(g_pDoMesage  ,  Pro  ,  0x60  ,  nOffset);
		if(t_CurSmpCnt  - nUpSmpCnt > 20  || t_CurSmpCnt - nUpSmpCnt < -20)
		{
			nUpSmpCnt = t_CurSmpCnt;
			Pro.SetAbronamlType(ABNORMAL_MULTIMUNOSYNC);
			g_pDoMesage->m_GlobalAbnormalPointPos.push_back(g_pDoMesage->m_92Vector[i]);
			continue;
		}
		nUpSmpCnt  = t_CurSmpCnt;
	}
}

void CToWork::GetAbnormalPosToVector( Content &content  ,  CAbnormalPos &AbnPos)
{
	int nASDUNum = 1;

	int nCount = 1;	

	int nOffset = 0;

	int tt1;

	int nStartPos  = 0;

	int nLength     = 0;

	std::vector<std::vector<int>> t_datavector;

	int nDataSize  = content.m_Vector.size(); //同一类型的MAC有多少帧；

	int nUpSmpCnt  = 0;

	std::vector  <int>  SmSyncPosVector;

	for (int i   =  0;   i  < nDataSize;  i++) 
	{
		CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];	

		//////////////////////////////////////失去同步信号//////////////////////////////////////////////////
		if (i==0)
		{
			int t_FindPos   = 0;

			nASDUNum    =  atoi(CGetInforFormVector::GetASN1Flag(g_pDoMesage  ,    Pro  ,    0x80));

			CGetInforFormVector::GetProtocolType(g_pDoMesage  ,    Pro  ,    tt1  ,    tt1  ,    tt1  ,    nOffset);

			for (int t_Num   =  0;  t_Num  <  nASDUNum;  t_Num++)
			{
				int t_Pos = CGetInforFormVector::GetASN1FlagPos(g_pDoMesage  ,    Pro  ,    0x85  ,    0  ,    t_Num);

				if(t_Pos  !=  -1)
					SmSyncPosVector.push_back(t_Pos);

				int t_Value   =   atoi(CGetInforFormVector::GetASN1Flag(g_pDoMesage ,   Pro ,    0x85 ,    0,    t_Num));

				if (t_Value==0)
				{
					AbnPos.m_nAllNum++;

					AbnPos.m_LostSmSycGlobalPos.push_back(i);

					AbnPos.m_LostSmSycContentPos.push_back(content.m_Vector[i]);

					AbnPos.m_AbnormalCurContentPos.push_back(i);

					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

					Pro.SetAbronamlType(ABNORMAL_LOSTSMSYNC);
				}
			}
		}
		else
		{
			for (int t_Num  =  0;   t_Num   <   nASDUNum;   t_Num++)
			{
				if (SmSyncPosVector.size()    !=   nASDUNum)
				{
					break;
				}

				int t_FindPos    =   Pro.m_nHeadStartPos   +  16   +  SmSyncPosVector.at(t_Num);
				if (t_FindPos + 2 > g_pDoMesage->DataArray.GetSize())
				{
					break;
				}

				int   t_Value   =  g_pDoMesage->DataArray[t_FindPos   +   2];
				if (t_Value==0)
				{
					AbnPos.m_nAllNum++;

					AbnPos.m_LostSmSycGlobalPos.push_back(i);

					AbnPos.m_LostSmSycContentPos.push_back(content.m_Vector[i]);

					AbnPos.m_AbnormalCurContentPos.push_back(i);

					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

					Pro.SetAbronamlType(ABNORMAL_LOSTSMSYNC);
				}
			}
		}

		////////////////////////////////丢包/错序/重复/////////////////////////////////////////////
		if (i==0)
		{
			nUpSmpCnt    = CGetInforFormVector::GetSmpCntValue(g_pDoMesage  ,  Pro  ,   0x60  ,  nOffset);
		}
		else
		{
			int t_CurSmpCnt    =   CGetInforFormVector::GetSmpCntValue(g_pDoMesage  ,  Pro  ,  0x60  ,  nOffset);
			if(t_CurSmpCnt   -   nUpSmpCnt  ==  nASDUNum)
			{
				nUpSmpCnt    =   t_CurSmpCnt;
				continue;
			}
			else
			{
				if ((t_CurSmpCnt  + nUpSmpCnt + 1) % 4000==0)
				{
					nUpSmpCnt  = t_CurSmpCnt;
					continue;	
				}
				else
				{
					if (nUpSmpCnt  -  t_CurSmpCnt  !=  content.m_nMaxSmpCnt)
					{	
						if (t_CurSmpCnt   -   nUpSmpCnt <= 0)//错序/重复
						{
							AbnPos.m_nAllNum++;

							AbnPos.m_ErrorNumContentPos.push_back(i);
							AbnPos.m_ErrorNumGlobalPos.push_back(content.m_Vector[i]);

							AbnPos.m_AbnormalCurContentPos.push_back(i);
							AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

							g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

							nUpSmpCnt  = t_CurSmpCnt;

							Pro.SetAbronamlType(ABNORMAL_ERRORNUM);
						}
						else//丢点
						{
							AbnPos.m_nAllNum++;

							AbnPos.m_LostPointCurContentPos.push_back(i);
							AbnPos.m_LostPointGlobalPos.push_back(content.m_Vector[i]);

							AbnPos.m_AbnormalCurContentPos.push_back(i);
							AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);

							g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);

							nUpSmpCnt = t_CurSmpCnt;

							Pro.SetAbronamlType(ABNORMAL_LOSTPOINT);
						}
					}
					else
					{
						nUpSmpCnt = t_CurSmpCnt;
					}
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

void CToWork::GetGooseAbnormalPosToVector( Content &content  ,  CAbnormalPos &AbnPos)
{
	int nDataSize  =  content.m_Vector.size();
	CString strUpValue  = _T("");
	CString strUpSTNumValue  = _T("");
	CString strUpSqNumValue = _T("");
	int nTimeAllowToLiveValue  =  0;
	BOOL bExistErrorFlag =  FALSE;

	for (int i  =  0;    i    <   nDataSize;   i++) 
	{
		bExistErrorFlag  =  FALSE;
		int t_datsetPos;
		CPacket & Pro  =  g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];	
		if (i==0)
		{
			strUpValue = CGetInforFormVector::GetASN1Flag(g_pDoMesage  ,    Pro  ,    0xAB  ,    0xAB);
			strUpSTNumValue = CGetInforFormVector::GetStNum(g_pDoMesage  ,    Pro);
			strUpSqNumValue = CGetInforFormVector::GetSqNum(g_pDoMesage  ,    Pro);
			nTimeAllowToLiveValue  = CGetInforFormVector::GetTimeAllowToLive(g_pDoMesage  ,    Pro);
		}
		else
		{
			CString strCurValue = CGetInforFormVector::GetASN1Flag(g_pDoMesage  ,    Pro  ,    0xAB  ,    0xAB);
			if (strCurValue==_T("error"))
			{
				break;
			}	
			t_datsetPos = CGetInforFormVector::GetASN1FlagPos(g_pDoMesage  ,    Pro  ,   0xAB);

			CString strCurSTNum = CGetInforFormVector::GetStNum(g_pDoMesage  ,    Pro);
			CString strCurSqNum = CGetInforFormVector::GetSqNum(g_pDoMesage  ,    Pro);

			int t_STNumDif   =  atoi(strCurSTNum)    -   atoi(strUpSTNumValue);
			/////////////////////////////////////变位前提下///////////////////////////////////////////////
			if(strUpValue  !=  strCurValue)//变位
			{
				int nUpVLength   = strUpValue.GetLength();
				int nCurVLength  = strCurValue.GetLength();

				for (int j =  0;   j   <  nCurVLength;  j++)
				{
					if (j   >=   nUpVLength)
					{
						break;
					}

					if (strCurValue[j]   !=  strUpValue[j])
					{
						int t_APos = t_datsetPos   +  (j / 2  + 1);
						Pro.m_AbnPosvector.push_back(t_APos);
					}
				}
				AbnPos.m_nAllNum++;
				if (atoi(strCurSqNum)  !=  0)
				{
					AbnPos.m_GooseBitChangeAndFirstValueErrorGlobalPos.push_back(i);
					AbnPos.m_GooseBitChangeAndFirstValueErrorContentPos.push_back(content.m_Vector[i]);
					AbnPos.m_AbnormalCurContentPos.push_back(i);
					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
					Pro.SetAbronamlType(GOOSE_SQNUMFIRSTVALUE);// SQNum初值错误
				}
				else
				{
					if (atoi(strCurSTNum)  -  atoi(strUpSTNumValue)  >  1)
					{
						AbnPos.m_nAllNum++;
						AbnPos.m_GooseBitChangeLostSTNumGlobalPos.push_back(i);
						AbnPos.m_GooseBitChangeLostSTNumContentPos.push_back(content.m_Vector[i]);
						AbnPos.m_AbnormalCurContentPos.push_back(i);
						AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
						g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
						Pro.SetAbronamlType(GOOSE_BITCHANGESTNUMLOST);
						strUpValue  =  strCurValue;
						bExistErrorFlag  =  TRUE;
					}
					else
					{
						AbnPos.m_GooseBitChangeGlobalPos.push_back(i);
						AbnPos.m_GooseBitChangeContentPos.push_back(content.m_Vector[i]);
						AbnPos.m_AbnormalCurContentPos.push_back(i);
						AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
						g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
						Pro.SetAbronamlType(GOOSE_BITCHANGE);
					}
				}	
				bExistErrorFlag = TRUE;
			}

			if (bExistErrorFlag==TRUE)
			{	
				strUpValue   =   strCurValue;	
				strUpSqNumValue   =  strCurSqNum;
				strUpSTNumValue   =  strCurSTNum;
				continue;
			}

			//////////////////////////////STNum错误/////////////////////////////////////////////
			if (atoi(strCurSTNum)   -   atoi(strUpSTNumValue)  >  1)
			{
				AbnPos.m_nAllNum++;
				AbnPos.m_GooseLostSTNumGlobalPos.push_back(i);
				AbnPos.m_GooseLostSTNumContentPos.push_back(content.m_Vector[i]);
				AbnPos.m_AbnormalCurContentPos.push_back(i);
				AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
				g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
				Pro.SetAbronamlType(GOOSE_STNUMLOST);//STNum错误
				bExistErrorFlag = TRUE;
			}

			if (bExistErrorFlag==TRUE)
			{
				strUpValue   =  strCurValue;	
				strUpSqNumValue  =  strCurSqNum;
				strUpSTNumValue  =  strCurSTNum;
				continue;
			}

			////////////////////////////虚变位/////////////////////////////////////////////
			if(t_STNumDif==1  &&  atoi(strCurSqNum)==0)
			{
				if(strUpValue == strCurValue)//虚变位
				{
					AbnPos.m_nAllNum++;
					AbnPos.m_GooseVitrualBitChangeAndCountErrorGlobalPos.push_back(i);
					AbnPos.m_GooseVitrualBitChangeAndCountErrorContentPos.push_back(content.m_Vector[i]);
					AbnPos.m_AbnormalCurContentPos.push_back(i);
					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
					Pro.SetAbronamlType(GOOSE_VITRUALBITCHANGE);//虚变位
					bExistErrorFlag = TRUE;
				}
			}

			if (bExistErrorFlag==TRUE)
			{
				strUpValue = strCurValue;	
				strUpSqNumValue = strCurSqNum;
				strUpSTNumValue = strCurSTNum;
				continue;
			}

			///////////////////////////////////////////////////////////////////////////////
			CHAR * t_end;
			unsigned long t1  = strtoul(strCurSqNum  ,   &t_end  ,   10);//解决大数问题
			unsigned long t2  = strtoul(strUpSqNumValue  ,   &t_end  ,   16);//解决大数问题
			int t_case   =  t1  -  t2;

			if (t_case  > 1)
			{
				t_case  = 2;
			}

			switch(t_case)
			{
			case 0:
				{

					AbnPos.m_nAllNum++;
					AbnPos.m_GooseSqNumRepeatGlobalPos.push_back(i);
					AbnPos.m_GooseSqNumRepeatContentPos.push_back(content.m_Vector[i]);
					AbnPos.m_AbnormalCurContentPos.push_back(i);
					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
					Pro.SetAbronamlType(GOOSE_SQREPEAT);//SqNO重复； 
					bExistErrorFlag = TRUE;
				}
				break;
			case 2:
				{
					AbnPos.m_nAllNum++;
					AbnPos.m_GooseLostSqNumGlobalPos.push_back(i);
					AbnPos.m_GooseLostSqNumContentPos.push_back(content.m_Vector[i]);
					AbnPos.m_AbnormalCurContentPos.push_back(i);
					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
					Pro.SetAbronamlType(GOOSE_SQNUMLOST);//SqNO丢失；
					bExistErrorFlag = TRUE;
				}
				break;
			}		

			if (bExistErrorFlag == TRUE)
			{
				strUpSqNumValue = strCurSqNum;
				strUpSTNumValue = strCurSTNum;
				strUpValue = strCurValue;
				continue;
			}

			/////////////////////////////////////////////时间比较/////////////////////////////////////////////				
			if(strUpValue == strCurValue)//无变位做时间比较
			{
				nTimeAllowToLiveValue  = CGetInforFormVector::GetTimeAllowToLive(g_pDoMesage  ,   Pro);
				if(nTimeAllowToLiveValue==0)
				{
					AbnPos.m_GooseTimeLiveEqual0GlobalPos.push_back(i);
					AbnPos.m_GooseTimeLiveEqual0ContentPos.push_back(content.m_Vector[i]);
					AbnPos.m_AbnormalCurContentPos.push_back(i);
					AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
					g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
					Pro.SetAbronamlType(GOOSE_TIMELIVEEQUAL0);	 // timeAllowedtoLive = 0;
					bExistErrorFlag = TRUE;
				}
				else
				{	
					CPacket & t_UpPro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i - 1]];
					unsigned long t_TimeDifValue = CGetInforFormVector::GetDifTimeINT(g_pDoMesage  ,   Pro  ,   t_UpPro  ,   1);
					if(t_TimeDifValue   <  2 * nTimeAllowToLiveValue && t_TimeDifValue > nTimeAllowToLiveValue)
					{
						AbnPos.m_GooseTimeDelayGlobalPos.push_back(i);
						AbnPos.m_GooseTimeDelayContentPos.push_back(content.m_Vector[i]);
						AbnPos.m_AbnormalCurContentPos.push_back(i);
						AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
						g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
						Pro.SetAbronamlType(GOOSE_TIMEDELAY);      // GOOSE延时
						bExistErrorFlag = TRUE;
					}
					else if (t_TimeDifValue   >   2  *  nTimeAllowToLiveValue)
					{
						AbnPos.m_GooseBreakGlobalPos.push_back(i);
						AbnPos.m_GooseBreakContentPos.push_back(content.m_Vector[i]);
						AbnPos.m_AbnormalCurContentPos.push_back(i);
						AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
						g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
						Pro.SetAbronamlType(GOOSE_BREAK);  // GOOSE中断
						bExistErrorFlag = TRUE;
					}
				}
			}

			if (bExistErrorFlag == TRUE)
			{
				strUpSqNumValue = strCurSqNum;
				strUpSTNumValue = strCurSTNum;
				strUpValue = strCurValue;
				continue;
			}

			/////////////////////////////////////////////////////////////////////////////////
			if (atoi(strCurSTNum)==1&&atoi(strCurSqNum)==1)//装置重启
			{
				AbnPos.m_GooseBitChangeAndCountErrorGlobalPos.push_back(i);
				AbnPos.m_GooseBitChangeAndCountErrorContentPos.push_back(content.m_Vector[i]);
				AbnPos.m_AbnormalCurContentPos.push_back(i);
				AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
				g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
				Pro.SetAbronamlType(GOOSE_EQURESTART);//装置重启
				bExistErrorFlag = TRUE;
			}

			if (bExistErrorFlag==TRUE)
			{	
				strUpValue = strCurValue;	
				strUpSqNumValue = strCurSqNum;
				strUpSTNumValue = strCurSTNum;
				continue;
			}

			//////////////////////////////////时钟异常//////////////////////////////////////////////
			int nEventTimeFactor = CGetInforFormVector::GetEventTimeStampFactor(g_pDoMesage  ,  Pro);
			if (nEventTimeFactor==0x2a)//未同步
			{
				AbnPos.m_GooseClockUnSyncGlobalPos.push_back(i);
				AbnPos.m_GooseClockUnSyncContentPos.push_back(content.m_Vector[i]);
				AbnPos.m_AbnormalCurContentPos.push_back(i);
				AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
				g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
				Pro.SetAbronamlType(GOOSE_CLOCKUPSYNC);// 时钟未同步
			}
			else if (nEventTimeFactor==0x4a)//时钟故障
			{
				AbnPos.m_GooseClockErrorGlobalPos.push_back(i);
				AbnPos.m_GooseClockErrorContentPos.push_back(content.m_Vector[i]);
				AbnPos.m_AbnormalCurContentPos.push_back(i);
				AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
				g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
				Pro.SetAbronamlType(GOOSE_CLOCKERROR);// 时钟故障
			}
			else if (nEventTimeFactor!=0x0a)//时钟异常
			{
				AbnPos.m_GooseClockAbnormalGlobalPos.push_back(i);
				AbnPos.m_GooseClockAbnormalContentPos.push_back(content.m_Vector[i]);
				AbnPos.m_AbnormalCurContentPos.push_back(i);
				AbnPos.m_AbnormalGlobalPos.push_back(content.m_Vector[i]);
				g_pDoMesage->m_GlobalAbnormalPointPos.push_back(content.m_Vector[i]);
				Pro.SetAbronamlType(GOOSE_CLOCKABNORMAL);//时钟异常
			}
			////////////////////////////////////////////////////////////////////////////////////////////////
			strUpValue = strCurValue;	
			strUpSqNumValue = strCurSqNum;
			strUpSTNumValue = strCurSTNum;
		}	
	}
}

void CToWork::GetGooseAbnormalPos()
{
	////////////////开始/////////////////////	
	DWORD start  ,  end;
	start = 0;//timeGetTime();//mym

	/////////////////////////////////////////////
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	for (int j = 0; j < g_pDoMesage->m_GooseKindsVector.size(); j++)
	{	
		CAbnormalPos & AbnPos  = g_pDoMesage->m_GooseAbnormalPosArray[j];
		Content & content = g_pDoMesage->m_GooseKindsVector[j];
		//AbnPos.m_strMac.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,  content.m_DES[0]  ,  content.m_DES[1]  ,  content.m_DES[2]  ,  content.m_DES[3]  ,  content.m_DES[4]  ,  content.m_DES[5]);
		content.m_strAppID.Format(_T("0x%.2X%.2X")  ,  content.m_APPID[0]  ,   content.m_APPID[1]);;
		content.m_strDes.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,   content.m_DES[0]  ,    content.m_DES[1]  ,   content.m_DES[2]  ,   content.m_DES[3]  ,   content.m_DES[4]  ,   content.m_DES[5]);
		content.m_strSRC.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,   content.m_SRC[0]  ,   content.m_SRC[1]  ,   content.m_SRC[2]  ,   content.m_SRC[3]  ,   content.m_SRC[4]  ,   content.m_SRC[5]);

		AbnPos.m_strAPPID = content.m_strAppID;
		AbnPos.m_strMacDes  = content.m_strDes;
		AbnPos.m_strMacSRC  = content.m_strSRC;

		GetGooseAbnormalPosToVector(content  ,   AbnPos);
		
		CPacket & t_H = g_pDoMesage->m_NewPacketVector[content.m_Vector[0]];
		CPacket & t_E = g_pDoMesage->m_NewPacketVector[content.m_Vector[content.m_Vector.size()  -  1]];	
		
		content.t_TotalTime  = CGetInforFormVector::GetDifTimeDouble(g_pDoMesage  ,     t_E  ,    t_H  ,    1);
		
		if (AbnPos.m_AbnormalCurContentPos.size()  !=  0)
		{
			content.m_bAbnoState = TRUE;
		}
		//		g_pDoMesage->m_GooseAbnormalPosArray.push_back(AbnPos);
	}
	///////////////////结束/////////////////
	// 	t_end = timeGetTime();
	// 	int t_Dif = t_end - t_start;
	// 	CString temp1;
	// 	temp1.Format(_T("%d")  ,  t_Dif);	
	// 	AfxMessageBox(temp1);
	g_pDoMesage->m_GooseAbnormalFinshedFlag = 1;
	return ;
}

void CToWork::Get92AbnormalPos()
{
	////////////////开始//////////
	DWORD start  ,  end;
	start = 0;//timeGetTime();//mym

	/////////////////////////////
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	for (int j = 0; j < g_pDoMesage->m_92KindsVector.size(); j++)// 有几种9-2种类，比如有几个不同种类的MAC；
	{	
		CAbnormalPos & AbnPos  = g_pDoMesage->m_SMVAbnormalPosArray[j];
		Content & content  = g_pDoMesage->m_92KindsVector[j];
		AbnPos.m_strMacSRC.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,    content.m_SRC[0]  ,    content.m_SRC[1]  ,    content.m_SRC[2]  ,    content.m_SRC[3]  ,    content.m_SRC[4]  ,    content.m_SRC[5]);
		AbnPos.m_strMacDes.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,    content.m_DES[0]  ,    content.m_DES[1]  ,    content.m_DES[2]  ,    content.m_DES[3]  ,    content.m_DES[4]  ,    content.m_DES[5]);
		AbnPos.m_strAPPID.Format(_T("0x%.2X%.2X")  ,    content.m_APPID[0]  ,    content.m_APPID[1]);

		GetAbnormalPosToVector( content  ,    AbnPos);

		if (AbnPos.m_AbnormalCurContentPos.size()  !=  0)
		{
			content.m_bAbnoState  =  TRUE;
		}
		//g_pDoMesage->m_SMVAbnormalPosArray.push_back(AbnPos);
	}

	//GetMultiNoSync();
	g_pDoMesage->m_SMVAbnormalFinshedFlag = 1;
	return ;
}

void CToWork::Get92SMVChannelDataToDrawWave( )
{
	//CDoMessage * g_pDoMesage  =  (CDoMessage *)param;

     //这里的个数是报文种类的个数，以MAC地址来区分的；比如5个，还是10个不同的MAC地址；
	for (int j = 0;  j < g_pDoMesage->m_92KindsVector.size();  j++)
	{	
		CMacDifWaveData MacDif;

		// Content. m_Vector 这里头的存的，是相同MAC地址所在的报文中的索引，比如  0  ,   5  ,   10；另一个MAC就是1  ,    6  ,   11；另一个就是2  ,    7  ,   12等等；
		Content &content  = g_pDoMesage->m_92KindsVector[j];

		CAbnormalPos & AbnPos  = g_pDoMesage->m_SMVAbnormalPosArray[j];
		
		MacDif.m_strMac.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,    content.m_DES[0]  ,    content.m_DES[1]  ,    content.m_DES[2]  ,    content.m_DES[3]  ,    content.m_DES[4]  ,    content.m_DES[5]);
		MacDif.m_AppID.Format(_T("0x%.2X%.2X")  ,    content.m_APPID[0]  ,    content.m_APPID[1]);
		
		content.m_strAppID  =  MacDif.m_AppID;
		content.m_strDes      =  MacDif.m_strMac;
		content.m_strSRC.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,    content.m_SRC[0]  ,    content.m_SRC[1]  ,    content.m_SRC[2]  ,    content.m_SRC[3]  ,    content.m_SRC[4]  ,    content.m_SRC[5]);
		
		GetChanValueToVector92( content  ,    MacDif  ,    AbnPos);

		//总计有多少个报文的数量；比如68884；这里是获取了第一个和最后一个；
		CPacket & t_H = g_pDoMesage->m_NewPacketVector[content.m_Vector[0]];
		CPacket & t_E = g_pDoMesage->m_NewPacketVector[content.m_Vector[content.m_Vector.size()  -  1]];	

		content.t_TotalTime  = CGetInforFormVector::GetDifTimeDouble(g_pDoMesage  ,    t_E  ,    t_H  ,    1);
		if (AbnPos.m_AbnormalCurContentPos.size()  != 0)
		{
			content.m_bAbnoState = TRUE;
		}
		g_pDoMesage->m_MacWaveDataArray.push_back(MacDif);
	}

	// 启动分析92报文不正常的线程；  
	//AfxBeginThread(Get92AbnormalPos  ,     param  ,    THREAD_PRIORITY_NORMAL);
	Get92AbnormalPos();
	g_pDoMesage->m_FinshedFlag = 1;
	return ;
}

void CToWork::Get92SMVFactorChange()
{
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	for (int j  =  0;  j  <  g_pDoMesage->m_92KindsVector.size();j++)
	{	
		Content & content = g_pDoMesage->m_92KindsVector[j];
		GetSMV92ChanFactorChange( content);
	}
	return ;
}

void CToWork::Get91SMVChannelDataToDrawWave()
{
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	for (int j=0;j<g_pDoMesage->m_91KindsVector.size();j++)
	{
		CMacDifWaveData MacDif;
		Content &content = g_pDoMesage->m_91KindsVector[j];
		MacDif.m_strMac.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,  content.m_DES[0]  ,  content.m_DES[1]  ,  content.m_DES[2]  ,  content.m_DES[3]  ,  content.m_DES[4]  ,  content.m_DES[5]);
		MacDif.m_AppID.Format(_T("0x%.2X%.2X")  ,  content.m_APPID[0]  ,  content.m_APPID[1]);
		content.m_strAppID = MacDif.m_AppID;
		content.m_strDes = MacDif.m_strMac;
		content.m_strSRC.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,  content.m_SRC[0]  ,  content.m_SRC[1]  ,  content.m_SRC[2]  ,  content.m_SRC[3]  ,  content.m_SRC[4]  ,  content.m_SRC[5]);
		GetChanValueToVector91( content  ,  MacDif);
		g_pDoMesage->m_MacWaveDataArray.push_back(MacDif);

	}
	g_pDoMesage->m_FinshedFlag = 1;
	g_pDoMesage->m_SMVAbnormalFinshedFlag = 1;
	return ;
}

void CToWork::GetTimeDifDataToVector(Content &content  ,  CTimeDifData &TimeDifData)
{
	int nASDUNum =  content.m_nASDUNum;
	int nCount =1;	
	int nOffset =0;
	int tt1;
	int nStartPos =0;
	int nLength = 0;
	int nDataSize = content.m_Vector.size();
	TimeDifData.m_nASDUNum = nASDUNum;
	TimeDifData.m_nPonitSize = nDataSize;
	int nSpecial  = 0;
	for (int i = 0; i < nDataSize;i++) 
	{
		if (i==0)
		{
			TimeDifData.m_DifDataVector.push_back(0);
		}
		else
		{
			CPacket & t_UpPro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i-1]];	
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_Vector[i]];	
			unsigned long t_Dif = CGetInforFormVector::GetDifTimeINT(g_pDoMesage  ,  Pro  ,  t_UpPro);
			TimeDifData.m_DifDataVector.push_back(t_Dif);
		}
	}
}

void CToWork::Get91TimeDiffStatisticsData()
{
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	for (int j=0;j<g_pDoMesage->m_91KindsVector.size();j++)
	{	
		CTimeDifData TimeDifData;
		Content &content = g_pDoMesage->m_91KindsVector[j];
		TimeDifData.m_strMac.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,  content.m_DES[0]  ,  content.m_DES[1]  ,  content.m_DES[2]  ,  content.m_DES[3]  ,  content.m_DES[4]  ,  content.m_DES[5]);
		GetTimeDifDataToVector( content  ,  TimeDifData);
		TimeDifData.m_PreSecPointNum = content.m_nMaxSmpCnt+content.m_nASDUNum;
		g_pDoMesage->m_TimeStatisticDataArray.push_back(TimeDifData);

	}
	return ;
}

void CToWork::Get92TimeDiffStatisticsData()
{
	////////////////开始//////////
	//DWORD t_start  ,  t_end;
	//t_start = timeGetTime();
	/////////////////////////////
	//CDoMessage * g_pDoMesage  =  (CDoMessage *)param;
	for (int j = 0; j < g_pDoMesage->m_92KindsVector.size(); j++)
	{	
		CTimeDifData TimeDifData;
		Content &content = g_pDoMesage->m_92KindsVector[j];
		TimeDifData.m_strMac.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,  	content.m_DES[0]  ,  	content.m_DES[1]  ,  	content.m_DES[2]  ,  	content.m_DES[3]  ,  	content.m_DES[4]  ,  	content.m_DES[5]);
		GetTimeDifDataToVector(content  ,  	TimeDifData);
		TimeDifData.m_PreSecPointNum = content.m_nMaxSmpCnt	+	content.m_nASDUNum;
		g_pDoMesage->m_TimeStatisticDataArray.push_back(TimeDifData);

	}
	//t_end = timeGetTime();
	//int t_Dif = t_end - t_start;
	//CString temp1;
	//temp1.Format(_T("%d")  ,  t_Dif);
	//AfxMessageBox(temp1);
	return ;
}

void CToWork::GetMMSType()
{
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	int n8073PDUTypePos = 59;
	int nFindBEPos =0;
	int nFindA0Pos =0;
	int nMMSInit = 0;
	for (int j=0;j<g_pDoMesage->m_TcpKindsVector.size();j++)
	{	
		TCPContent &content = g_pDoMesage->m_TcpKindsVector[j];
		int nMMSSize = content.m_MMSVector.size();
		if(nMMSSize>0)
		{

			for (int m =0;m<nMMSSize;m++)
			{
				// 
				//      			if (m==5/*||m==52*/)
				//      			{
				//      				AfxMessageBox(_T("DFDFDFDFF"));
				//      			}
				CPacket & Pro = g_pDoMesage->m_NewPacketVector[content.m_MMSVector[m]];
				Pro.m_nInvokeID = -1;
				CByteArray byArray;
				CGetInforFormVector::GetPackHexDataPart(g_pDoMesage  ,  Pro  ,  byArray);
				BYTE t_PUD = byArray.GetAt(n8073PDUTypePos+content.m_TcpAddPos);
				switch(t_PUD)
				{
				case 0xE0:case 0xD0:
					{
						Pro.SetAbronamlType(MMS_COTPDATA);
					}
					break;
				case 0xF0:
					{
						int t_FlagType = 0;
						nFindBEPos = CGetInforFormVector::GetFlagPos(byArray  ,  0xBE  ,  n8073PDUTypePos+content.m_TcpAddPos);
						if (nFindBEPos==0)//正常情况
						{				
							nFindA0Pos = CGetInforFormVector::GetFlagPos(byArray  ,  0xA0  ,  n8073PDUTypePos+content.m_TcpAddPos);
							if (nFindA0Pos==0)
							{
								break;
							}
							int t_A0L = byArray.GetAt(nFindA0Pos+1);
							int t_FlagPos;
							int t_ServiceNameIDPos;
							if (t_A0L>0x80)
							{
								t_FlagPos = nFindA0Pos+t_A0L-0x80+2;
								t_ServiceNameIDPos = t_FlagPos+t_A0L-0x80+2;
							}
							else 
							{
								t_FlagPos= nFindA0Pos+2;
								t_ServiceNameIDPos = t_FlagPos+2;
							}
							if (t_FlagPos>=byArray.GetSize())
							{
								break;
							}
							else t_FlagType = byArray.GetAt(t_FlagPos);
							switch(t_FlagType)
							{
							case 0xA0://Confimed_RequestPDU
								{
									Pro.m_nInvokeID = atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x02  ,  t_FlagPos));
									int t_InvokIdL =atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x02  ,  t_FlagPos  ,  0xC11))+2;
									int t_ServiceNameID = byArray.GetAt(t_ServiceNameIDPos+t_InvokIdL);
									switch(t_ServiceNameID)
									{
									case 0xA4://读取报告控制块操作
										{
											int t_MMSType = CGetInforFormVector::GetMMSItemNameTypeA4(byArray  ,  t_ServiceNameIDPos+t_InvokIdL);
											if (t_MMSType==-1)
											{
												t_MMSType = MMS_READREPORT;
											}
											Pro.SetAbronamlType(t_MMSType);
										}
										break;
									case 0xA5://写报告操作
										{
											int t_MMSType = CGetInforFormVector::GetMMSItemNameTypeA5(byArray  ,  t_ServiceNameIDPos+t_InvokIdL);
											if (t_MMSType==-1)
											{
												t_MMSType = MMS_WRITEREPORT;
											}
											Pro.SetAbronamlType(t_MMSType);
										}
										break;
									case 0xAC://获取已命名变量列表属性结构体
										{
											Pro.SetAbronamlType(MMS_GETNAMEDATTRISTRUCT);
										}
										break;
									case 0xA1://获取IED变量列表
										{
											if (nMMSInit == 1)
											{
												Pro.SetAbronamlType(MMS_GETIEDLISTEX);	

											}
											else Pro.SetAbronamlType(MMS_GETIEDLIST);	

										}
										break;
									case 0xA6://获取IED变量表属性结构体
										{
											Pro.SetAbronamlType(MMS_GETVARIABLEACCESSATTRIBUTES);
										}
										break;
									case 0xBF://文件操作
										{
											int t_FileType = byArray.GetAt(t_ServiceNameIDPos+t_InvokIdL+1);
											if (t_FileType==0x48)
											{
												Pro.SetAbronamlType(MMS_OPENFILE);
											}
											else if (t_FileType==0x4C)
											{
												Pro.SetAbronamlType(MMS_FILEDEL);
											}
											else if (t_FileType==0x4D)
											{
												Pro.SetAbronamlType(MMS_FILEDIR);
											}
											else if (t_FileType==0x2E)
											{
												Pro.SetAbronamlType(MMS_FILEOBTAIN);
											}
										}
										break;
									case 0x9F:
										{
											int t_FileType = byArray.GetAt(t_ServiceNameIDPos+t_InvokIdL+1);
											if (t_FileType==0x49)
											{
												Pro.SetAbronamlType(MMS_FILEREAD);
											}
											else if (t_FileType==0x4a)
											{
												Pro.SetAbronamlType(MMS_FILECLOSE);
											}
										}
										break;

									}
								}
								break;
							case 0xA1:
								{
									Pro.m_nInvokeID = atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x02  ,  t_FlagPos));
									int t_InvokIdL =atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x02  ,  t_FlagPos  ,  0xC11))+2;
									int t_ServiceNameID = byArray.GetAt(t_ServiceNameIDPos+t_InvokIdL);
									switch(t_ServiceNameID)
									{
									case 0xA4://返回报告控制块操作
										{
											for (int t_UpSameInvokeID=1;t_UpSameInvokeID<100;t_UpSameInvokeID++)
											{
												int t = m-t_UpSameInvokeID;
												if (t>=0)
												{
													CPacket & t_ProUp = g_pDoMesage->m_NewPacketVector[content.m_MMSVector[t]];
													if (t_ProUp.m_nInvokeID==Pro.m_nInvokeID)
													{
														int t_AddV = 16;
														if(t_ProUp.m_nAbnormalType==MMS_READREPORT)t_AddV=1;
														else 
														{
															int t_80V = atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x80  ,  t_ServiceNameIDPos+t_InvokIdL));
															if (t_80V==0x0A)
															{
																Pro.SetAbronamlType(MMS_READREPORTFINSHED_ERROR);
															}
															else Pro.SetAbronamlType(t_ProUp.m_nAbnormalType+t_AddV);
														}

														break;

													}
												}
												else
												{
													Pro.SetAbronamlType(MMS_READREPORTFINSHED);
													break;
												}

											}
											//Pro.SetAbronamlType(MMS_READREPORTFINSHED);
										}
										break;
									case 0xA5://写报告操作完成
										{
											for (int t_UpSameInvokeID=1;t_UpSameInvokeID<100;t_UpSameInvokeID++)
											{
												int t = m-t_UpSameInvokeID;
												if (t>=0)
												{
													CPacket & t_ProUp = g_pDoMesage->m_NewPacketVector[content.m_MMSVector[t]];
													if (t_ProUp.m_nInvokeID==Pro.m_nInvokeID)
													{
														int t_SucValue =  atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x80  ,  t_FlagPos+t_InvokIdL+2));
														if (t_SucValue>1)
														{
															Pro.SetAbronamlType(MMS_WRITEREPORTFINSHED_ERROR);
														}
														else Pro.SetAbronamlType(t_ProUp.m_nAbnormalType+16);
														break;

													}
												}
												else
												{
													Pro.SetAbronamlType(MMS_READREPORTFINSHED);
													break;
												}
											}
										}
										break;
									case 0xAC://返回已命名变量列表属性结构体
										{
											Pro.SetAbronamlType(MMS_RETNAMEDATTRISTRUCT);
										}
										break;
									case 0xA1://返回IED变量列表
										{
											if (nMMSInit == 1)
											{
												nMMSInit = 0;
												Pro.SetAbronamlType(MMS_RETIEDLISTEX);
											}
											else Pro.SetAbronamlType(MMS_RETIEDLIST);
										}
										break;
									case 0xA6://返回IED变量表属性结构体
										{
											Pro.SetAbronamlType(MMS_RETURNVARIABLEACCESSATTRIBUTES);
										}
										break;
									case 0xBF://文件操作
										{
											int t_FileType = byArray.GetAt(t_ServiceNameIDPos+t_InvokIdL+1);
											if (t_FileType==0x48)
											{
												Pro.SetAbronamlType(MMS_OPENFILEFINSHED);
											}
											else if (t_FileType==0x4D)
											{
												Pro.SetAbronamlType(MMS_FILEDIRFINSHED);
											}
											else if (t_FileType==0x49)
											{
												Pro.SetAbronamlType(MMS_FILEREADFINSHED);
											}
										}
										break;
									case 0x9F:
										{
											int t_FileType = byArray.GetAt(t_ServiceNameIDPos+t_InvokIdL+1);
											if (t_FileType==0x4A)
											{
												Pro.SetAbronamlType(MMS_FILECLOSEFINSHED);
											}
											else if (t_FileType==0x4C)
											{
												Pro.SetAbronamlType(MMS_FILEDELFINSHED);
											}
											else if (t_FileType==0x2E)
											{
												Pro.SetAbronamlType(MMS_FILEOBTAINFINSHED);
											}

										}
										break;
									}
								}
								break;
							case 0xA2://mms交互失败
								{
									Pro.m_nInvokeID = atoi(CGetInforFormVector::GetASN1Flag(byArray  ,  0x80  ,  t_FlagPos));
									for (int t_UpSameInvokeID=1;t_UpSameInvokeID<100;t_UpSameInvokeID++)
									{
										int t = m-t_UpSameInvokeID;
										if (t>=0)
										{
											CPacket & t_ProUp = g_pDoMesage->m_NewPacketVector[content.m_MMSVector[t]];
											if (t_ProUp.m_nInvokeID==Pro.m_nInvokeID)
											{

												if (t_ProUp.m_nAbnormalType==MMS_GETIEDLIST)
												{
													Pro.SetAbronamlType(MMS_COMUNICATEERROR_GETNAMELIST);
												}
												else if (t_ProUp.m_nAbnormalType==MMS_GETVARIABLEACCESSATTRIBUTES)
												{
													Pro.SetAbronamlType(MMS_COMUNICATEERROR_GETNAMEDVARLISTATTR);
												}
												else if (t_ProUp.m_nAbnormalType==MMS_WRITEREPORT_ACTSG)
												{
													Pro.SetAbronamlType(MMS_COMUNICATEERROR_SELACTIVESG);
												}	
												else if (t_ProUp.m_nAbnormalType==MMS_OPENFILE)
												{
													Pro.SetAbronamlType(MMS_COMUNICATEERROR_GETSERVERFILEERROR);
												}	
												else Pro.SetAbronamlType(MMS_COMUNICATEERROR);
												break;

											}
										}
										else
										{

											Pro.SetAbronamlType(MMS_COMUNICATEERROR);
											break;
										}
									}
								}
								break;
							case 0xA3:
								{											
									Pro.SetAbronamlType(MMS_UPLOADREPORT);
								}
								break;
							case 0x8B:
								Pro.SetAbronamlType(MMS_REQUESTOVERMMS);
								break;
							case 0x8C:
								{
									int t_UpSameInvokeID;
									for (t_UpSameInvokeID=1;t_UpSameInvokeID<100;t_UpSameInvokeID++)
									{
										int t = m-t_UpSameInvokeID;
										if (t>=0)
										{
											CPacket & t_ProUp = g_pDoMesage->m_NewPacketVector[content.m_MMSVector[t]];
											if (t_ProUp.m_nAbnormalType==MMS_REQUESTOVERMMS)
											{
												Pro.SetAbronamlType(MMS_COMFIRMOVERMMS);
												break;
											}
										}

									}
									if (t_UpSameInvokeID==100)
									{
										Pro.SetAbronamlType(MMS_COTPDATA);
									}
								}

								break;
							case 0x62:
								Pro.SetAbronamlType(MMS_CLIENTREUESTREALSE);
								break;
							case 0x63:
								Pro.SetAbronamlType(MMS_CLIENCOMFIRMREALSE);
								break;

							}
						}
						else//客户端初始化MMS
						{
							nFindBEPos = CGetInforFormVector::GetFlagPos(byArray  ,  0xBE);
							nFindA0Pos = CGetInforFormVector::GetFlagPos(byArray  ,  0xA0  ,  nFindBEPos);
							int t_FlagType = byArray.GetAt(nFindA0Pos+2);
							switch(t_FlagType)
							{
							case 0xA8:
								{
									nMMSInit = 1;
									Pro.SetAbronamlType(MMS_CLIENTINIT);
								}

								break;
							case 0xA9:
								Pro.SetAbronamlType(MMS_SEVERRECV);
								break;
							}
						}
					}

					break;
				}

			}
		}

	}
	return ;
}

void CToWork::GetDiffertSRCMac()
{
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	int n91Size = g_pDoMesage->m_91Vector.size();
	int n92Size = g_pDoMesage->m_92Vector.size();

	int nGooseSize = g_pDoMesage->m_GooseVector.size();
	int nTcpSize =  g_pDoMesage->m_TcpVector.size();
	int n1588Size = g_pDoMesage->m_1588Vector.size();
	int nOhterSize= g_pDoMesage->m_OtherVector.size();

	
	if (nGooseSize==0&&(n91Size==0||n92Size==0))
	{
		g_pDoMesage->m_FinshedFlag = 1;

	}	
	if(nGooseSize==0) 
		g_pDoMesage->m_GooseAbnormalFinshedFlag = 1;

	if(n91Size==0)
	{
		if(n92Size==0)
		{
			g_pDoMesage->m_SMVAbnormalFinshedFlag = 1;
			g_pDoMesage->m_FinshedFlag = 1;
		}
	}

	if (n92Size != 0)
	{
		CGetInforFormVector::Get92Classification(g_pDoMesage);

		for (int j = 0;  j < g_pDoMesage->m_92KindsVector.size();  j++)
		{
			CAbnormalPos AbnPos;
			Content & content  = g_pDoMesage->m_92KindsVector[j];
			AbnPos.m_strMacDes.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,    content.m_DES[0]  ,    content.m_DES[1]  ,    content.m_DES[2]  ,   content.m_DES[3]  ,   content.m_DES[4]  ,   content.m_DES[5]);
			g_pDoMesage->m_SMVAbnormalPosArray.push_back(AbnPos);  
		}

		//AfxBeginThread(Get92SMVChannelDataToDrawWave  ,    param  ,   THREAD_PRIORITY_NORMAL);
		Get92SMVChannelDataToDrawWave();
		//AfxBeginThread(Get92AbnormalPos  ,  param  ,  THREAD_PRIORITY_NORMAL);

		//AfxBeginThread(Get92TimeDiffStatisticsData  ,    param  ,   THREAD_PRIORITY_NORMAL);
		Get92TimeDiffStatisticsData();
	}
/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (n1588Size!=0)
	{
		CGetInforFormVector::Get1588Classification(g_pDoMesage);
	}

	if (nOhterSize!=0)
	{
		CGetInforFormVector::GetOtherClassification(g_pDoMesage);
	}
	if (n91Size!=0)
	{
		CGetInforFormVector::Get91Classification(g_pDoMesage);

		//AfxBeginThread(Get91SMVChannelDataToDrawWave  ,   param  ,   THREAD_PRIORITY_NORMAL);
		//AfxBeginThread(Get91TimeDiffStatisticsData  ,   param  ,   THREAD_PRIORITY_NORMAL);
		Get91SMVChannelDataToDrawWave();
		Get91TimeDiffStatisticsData();
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

	if (nGooseSize!=0)
	{
		CGetInforFormVector::GetGooseClassification(g_pDoMesage);
		for (int j = 0; j < g_pDoMesage->m_GooseKindsVector.size(); j++)
		{	
			CAbnormalPos AbnPos;
			Content &content = g_pDoMesage->m_GooseKindsVector[j];
			AbnPos.m_strMacDes.Format(_T("%.2X%.2X%.2X%.2X%.2X%.2X")  ,   content.m_DES[0]  ,   content.m_DES[1]  ,   content.m_DES[2]  ,   content.m_DES[3]  ,   content.m_DES[4]  ,   content.m_DES[5]);
			g_pDoMesage->m_GooseAbnormalPosArray.push_back(AbnPos);
		}
		//AfxBeginThread(GetGooseAbnormalPos  ,   param  ,   THREAD_PRIORITY_NORMAL);
		GetGooseAbnormalPos();
	}
/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(nTcpSize!=0)
	{
		CGetInforFormVector::GetTcpClassification(g_pDoMesage);
		//AfxBeginThread(GetMMSType  ,  param  ,  THREAD_PRIORITY_NORMAL);		 
		GetMMSType();
	}
	else
		;//ExitThread(0);mym
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
	return ;
}

void CToWork::StartToDo()
{
	////////////////开始/////////////////////	
	DWORD start  ,  end;
	start = 0;//timeGetTime();//mym
	/////////////////////////////////////////////
	//CDoMessage * g_pDoMesage = (CDoMessage *)param;
	int nSize = g_pDoMesage->m_NewPacketVector.size();
	bool t1 = false;
	bool t2 = false;
	bool t3 = false;
	bool t4 = false;
	bool t5 = false;
	bool t6 = false;
	bool t7 = false;
	bool t8 = false;

	for (int i  = 0;  i  <  nSize;  i++)
	{
		CPacket & pPro = g_pDoMesage->m_NewPacketVector[i];
		int nProType  = -1;
		int nSMVOrGoose = 0;
		int n91Or92 = 0;
		int nOffset = 0;
		CGetInforFormVector::GetProtocolType(g_pDoMesage  ,   pPro  ,   nProType  ,   nSMVOrGoose  ,   n91Or92  ,   nOffset);
		switch(nProType)
		{
		case PRO_TCP:
			{
				g_pDoMesage->m_TcpVector.push_back(i);
				if (!t1)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("TCP"));	
					t1 = true;
				}
			}
			break;
		case PRO_UDP:
			{

				g_pDoMesage->m_UdpVector.push_back(i);
				if (!t2)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("UDP"));	
					t2 = true;
				}
			}
			break;
		case IEC_SMV91:
			{
				g_pDoMesage->m_91Vector.push_back(i);
				if (!t3)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("IEC_SMV91"));	
					t3 = true;
				}
			}
			break;
		case IEC_SMV92:
			{
				g_pDoMesage->m_92Vector.push_back(i);
				if (!t4)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("IEC_SMV92"));	
					t4 = true;
				}
			}
			break;
		case IEC_GOOSE:
			{
				g_pDoMesage->m_GooseVector.push_back(i);
				if (!t5)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("IEC_GOOSE"));	
					t5 = true;
				}
			}
			break;
		case PRO_ARP:
			{
				g_pDoMesage->m_ArpVector.push_back(i);
				if (!t6)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("ARP"));	
					t6 = true;
				}
			}
			break;
		case PRO_1588:
			{

				g_pDoMesage->m_1588Vector.push_back(i);
				if (!t8)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("IEEE_1588"));	
					t8 = true;
				}
			}
			break;
		case PRO_OTHER:
			{
				g_pDoMesage->m_OtherVector.push_back(i);
				if (!t7)
				{
					g_pDoMesage->m_ProTypeArray.Add(_T("Other"));	
					t7 = true;
				}
			}	
			break;
		}
	}
	g_pDoMesage->m_bGetTypeWork  =  true;
	///////////////////结束/////////////////
	end = 0;//timeGetTime();//mym

	int t_Dif = end  -  start;
	CString temp1;
	temp1.Format(_T("%d")  ,    t_Dif);		

//	AfxBeginThread(GetDiffertSRCMacThread  ,    param  ,   THREAD_PRIORITY_NORMAL);
	GetDiffertSRCMac();

	//ExitThread(0); mym
	/////////////////////////////////////////
	return ;
}

UINT  CToWork::ExecuteAnalysis( )
{
	//g_pDoMesage->m_DealPacpFile = g_strFileName;
	//g_pDoMesage->DoPacpFile();                                  //解析PCAP文件，拆分成一些结构；
	StartToDo(  );
	return 0;
}


CString CToWork::GetAllStatisticInfor()
{
	CString  strAllMsgNum,   strByteAllNum,  strTimeDif,   strFlow,   strErrorNum;
	int nAllMsgNum  = g_pDoMesage->m_NewPacketVector.size();
	int nErrorNum   = g_pDoMesage->m_GlobalAbnormalPointPos.size();

	strErrorNum.Format(_T("%d"),  nErrorNum);
	strAllMsgNum.Format(_T("%d"),   nAllMsgNum);
	strByteAllNum.Format(_T("%d"),   g_pDoMesage->m_nArrayLength  -   16   *  (nAllMsgNum)  -  32);

	strTimeDif = CGetInforFormVector::GetDifTimeString(g_pDoMesage,  g_pDoMesage->m_NewPacketVector[nAllMsgNum - 1],  g_pDoMesage->m_NewPacketVector[0],  1);

	int t_flow = atoi(strByteAllNum) / atoi(strTimeDif); 
	strFlow.Format(_T("%d"),t_flow);

	CString strShowResut = _T("Total messages:");
	strShowResut  +=  strAllMsgNum;
	strShowResut  +=  _T("\r\n");

	strShowResut  +=  _T("Total bytes:");
	strShowResut  +=  strByteAllNum;
	strShowResut  +=  _T("\r\n");

	strShowResut  +=  _T("Time (ms):");
	strShowResut  +=  strTimeDif;
	strShowResut  +=  _T("\r\n");

	strShowResut  +=  _T("Average flow (B/S):");
	strShowResut  +=  strFlow;
	strShowResut  +=  _T("\r\n");

	strShowResut  +=  _T("Error number:");
	strShowResut  +=  strErrorNum;
	strShowResut  +=  _T("\r\n");

	strShowResut  +=  _T("\r\n");
	strShowResut  +=  _T("Message types:");	
	strShowResut  +=  _T("\r\n");
	
	if (g_pDoMesage->m_91Vector.size()  >  0)
	{
		strShowResut    +=    _T("\r\n");
		int n91Size   =  g_pDoMesage->m_91Vector.size();
		CString t_91Infor;
		t_91Infor.Format(_T("IEC_SMV91 Totality: %d packet,ratio:%.3f%%"),  n91Size,  ((float)n91Size/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  t_91Infor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_92Vector.size()  >  0)
	{
		strShowResut  +=  _T("\r\n");
		int n92Size =  g_pDoMesage->m_92Vector.size();
		CString str92Infor;
		str92Infor.Format(_T("IEC_SMV92 Totality: %d packet,ratio:%.3f%%"),n92Size,  ((float)n92Size/(float)nAllMsgNum)  * 100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  str92Infor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_GooseVector.size()  >  0)
	{
		strShowResut  +=  _T("\r\n");
		int t_GSize =  g_pDoMesage->m_GooseVector.size();
		CString strGInfor;
		strGInfor.Format(_T("IEC_GOOSE Totality: %d packet,ratio:%.3f%%"),  t_GSize,  ((float)t_GSize/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  strGInfor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_TcpVector.size()  >  0)
	{
		strShowResut  +=  _T("\r\n");
		int nTSize =  g_pDoMesage->m_TcpVector.size();
		CString strTInfor;
		strTInfor.Format(_T("TCP Totality: %d packet,ratio:%.3f%%"),  nTSize,  ((float)nTSize/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  strTInfor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_UdpVector.size()  >  0)
	{
		strShowResut    +=    _T("\r\n");
		int nUSize  = g_pDoMesage->m_UdpVector.size();
		CString strUInfor;
		strUInfor.Format(_T("UDP Totality: %d packet,ratio:%.3f%%"),  nUSize,  ((float)nUSize/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  strUInfor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_ArpVector.size()  >  0)
	{
		strShowResut  +=  _T("\r\n");
		int nUSize = g_pDoMesage->m_ArpVector.size();
		CString strUInfor;
		strUInfor.Format(_T("ARP Totality: %d packet,ratio:%.3f%%"),  nUSize,  ((float)nUSize/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  strUInfor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_1588Vector.size()  >  0)
	{
		strShowResut  +=  _T("\r\n");
		int nUSize =  g_pDoMesage->m_1588Vector.size();
		CString strUInfor;
		strUInfor.Format(_T("1588 Totality: %d packet,ratio:%.3f%%"),  nUSize,  ((float)nUSize/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  strUInfor;
		strShowResut  +=  _T("\r\n");
	}

	if (g_pDoMesage->m_OtherVector.size()  >  0)
	{
		strShowResut  +=  _T("\r\n");
		int nUSize =  g_pDoMesage->m_OtherVector.size();
		CString strUInfor;
		strUInfor.Format(_T("Other Totality: %d packet,ratio:%.3f%%"),  nUSize,  ((float)nUSize/(float)nAllMsgNum)*100);
		strShowResut  +=  _T("         ");
		strShowResut  +=  strUInfor;
		strShowResut  +=  _T("\r\n");
	}

	return strShowResut;
}


CString CToWork::GetSMVStatisticInfor()
{
	// 暂时定9-2 ； 
	int  m_CurMsgType = 2;

	CString  strAllMsgNum,  strByteAllNum,   strTimeDif,   strFlow,  strErrorNum;
	int nAllMsgNum = 0;

	if (m_CurMsgType==IEC_SMV91)
	{
		nAllMsgNum  =  g_pDoMesage->m_92Vector.size();
	}

	if (m_CurMsgType==IEC_SMV92)
	{
		nAllMsgNum = g_pDoMesage->m_92Vector.size();
	}
	int nErrorNum  = 0;
	int t_arraysize = g_pDoMesage->m_SMVAbnormalPosArray.size();
	for (int m =  0;  m  <  t_arraysize;  m++)
	{
		CAbnormalPos & t_Pos = g_pDoMesage->m_SMVAbnormalPosArray[m];
		nErrorNum += t_Pos.m_nAllNum;
	}
	strErrorNum.Format(_T("%d"),  nErrorNum);
	strAllMsgNum.Format(_T("%d"),  nAllMsgNum);	

	int nAllByteNum  = 0;
	if (m_CurMsgType==IEC_SMV91)
	{
		int n91Kind = g_pDoMesage->m_91KindsVector.size();
		for (int n =  0;  n  < n91Kind;  n++)
		{
			Content & t_Con = g_pDoMesage->m_91KindsVector[n];
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[t_Con.m_Vector[0]];
			nAllByteNum+=(Pro.m_nDataPackLength*t_Con.m_Vector.size());
		}
	}

	if (m_CurMsgType==IEC_SMV92)
	{
		int t_92Kind  = g_pDoMesage->m_92KindsVector.size();
		for (int n = 0; n <  t_92Kind; n++)
		{
			Content & t_Con = g_pDoMesage->m_92KindsVector[n];
			CPacket & Pro = g_pDoMesage->m_NewPacketVector[t_Con.m_Vector[0]];
			nAllByteNum  += (Pro.m_nDataPackLength  *   t_Con.m_Vector.size());
		}
	}

	strByteAllNum.Format(_T("%d"),  nAllByteNum);
	// 	int t_flow = _wtoi(strByteAllNum)/_wtoi(strTimeDif); 
	// 	strFlow.Format(_T("%d"),t_flow);
	CString strShowResut = _T("总计报文数:");
	strShowResut+=strAllMsgNum;
	strShowResut+=_T("\r\n");

	strShowResut+=_T("总计字节数:");
	strShowResut+=strByteAllNum;
	strShowResut+=_T("\r\n");
	// 	strShowResut+=_T("平均流量(字节/秒):");
	// 	strShowResut+=strFlow;
	// 	strShowResut+=_T("\r\n");
	strShowResut+=_T("错误数量:");
	strShowResut+= strErrorNum;
	strShowResut+=_T("\r\n");

	//////////////////////////每个Content中的内容//////////////////////////////
	if (m_CurMsgType==IEC_SMV92)
	{
		int t_92Kind = g_pDoMesage->m_92KindsVector.size();
		for (int n = 0; n < t_92Kind; n++)
		{
			CString strConInfor = _T("");
			strConInfor+=_T("\r\n");
			//strConInfor+=_T("\t");
			CString t_Des = _T("");
			CString t_Src = _T("");
			CString t_AppID = _T("");
			Content & t_Con = g_pDoMesage->m_92KindsVector[n];
			t_Des = _T("目标地址:");	
			for (int k = 0;  k  <  6;  k++)
			{
				CString t_str;
				t_str.Format(_T("%.2X"),  t_Con.m_DES[k]);
				t_Des+=t_str;
			}

			strConInfor += t_Des;	 
			strConInfor += _T("\r\n");

			//strConInfor+=_T("  ");
			t_Src  +=  _T("源地址:");
			for (int k  =  0;  k < 6;  k++)
			{
				CString t_str;
				t_str.Format(_T("%.2X"),   t_Con.m_SRC[k]);
				t_Src  +=  t_str;
			}


			strConInfor+=t_Src;
			strConInfor+=_T("\r\n");
			//strConInfor+=_T("  ");	
			//t_Src+=_T(" APPID:");
			t_AppID = _T("APPID:");
			for (int k =0;k<2;k++)
			{
				CString t_str;
				t_str.Format(_T("%.2X"),t_Con.m_APPID[k]);
				t_AppID+=t_str;
			}

			//strConInfor+=t_AppID;

			strConInfor+=t_AppID;
			strConInfor+=_T("\r\n");

			//strConInfor+=_T("  ");
			CString t_Num;
			t_Num.Format(_T("总计帧数:%d"),t_Con.m_Vector.size());
			strConInfor+=t_Num;
			strConInfor+=_T("\r\n");
			//strConInfor+=_T("  ");
			CString nAllByteNum;
			nAllByteNum.Format(_T("总计字节数:%ld"),t_Con.m_Vector.size()*t_Con.m_nPrePacketSize);
			strConInfor+=nAllByteNum;

			//strConInfor+=_T("  ");
			strConInfor+=_T("\r\n");
			CString strAllTime;
			strAllTime.Format(_T("总计时间(s):%.3f"),t_Con.t_TotalTime);
			strConInfor+=strAllTime;

			strConInfor+=_T("\r\n");

			//strConInfor+=_T("  ");
			CString t_EverNum;
			t_EverNum.Format(_T("平均流量(字节/秒):%.0f"),(t_Con.m_Vector.size()*t_Con.m_nPrePacketSize)/t_Con.t_TotalTime);
			strConInfor+=t_EverNum;
			strConInfor+=_T("\r\n");

			int t_Abnormalnum = g_pDoMesage->m_SMVAbnormalPosArray.size();

			for (int q  =  0;  q  <  t_Abnormalnum;  q++ )
			{
				CAbnormalPos  & AbnPos = g_pDoMesage->m_SMVAbnormalPosArray[q];
				if (t_Des.Find(AbnPos.m_strMacDes)  !=  -1)
				{
					//strConInfor  +=  _T("");
					strConInfor  +=  AbnPos.GetInfor();
					break;
				}
			}

			strShowResut  +=  strConInfor;
			CString strTimeInfor = _T("");
			CTimeDifData &Time = g_pDoMesage->m_TimeStatisticDataArray[n];
			int nSize   =  Time.m_DifDataVector.size();
			int n0DifVector = 0;
			for (int k  =  1;  k  <  nSize;  k++)
			{
				int t_CurV =   Time.m_DifDataVector[k];

				// 这里头的1000 MYM 乘以,否则无偏差计算错误；
				int t_Dif   =  t_CurV  -  250  *  g_pDoMesage->m_usOrns  * 1000 *  Time.m_nASDUNum;	
				if (t_Dif  <=  g_pDoMesage->m_usOrns  *  1000 * Time.m_nASDUNum  &&  t_Dif  >=  (0  -  g_pDoMesage->m_usOrns  * 1000 *  Time.m_nASDUNum))
				{
					n0DifVector++;
				}
			}

			double t_Rate = (double)(n0DifVector)/(double)(Time.m_nPonitSize  -  1);
			strTimeInfor.Format(_T("无偏差:%.2f%%"),   t_Rate  *  100.000);
			strShowResut  +=  strTimeInfor;
			strShowResut  +=  _T("\r\n");
		}
	}
	//strShowResut.Replace('  ',   NULL);

	if (m_CurMsgType==IEC_SMV91)
	{
		int n91Kind  =  g_pDoMesage->m_91KindsVector.size();
		for (int n  = 0; n  < n91Kind; n++)
		{
			CString strConInfor  =  _T("");
			strConInfor += _T("\r\n");
			strConInfor += _T("\t");
			CString t_Des  =  _T("");
			CString t_Src  = _T("");
			CString t_AppID  = _T("");
			Content &  t_Con  = g_pDoMesage->m_91KindsVector[n];
			t_Des  += _T("目标地址:");	
			for (int k  = 0; k < 6; k++)
			{
				CString t_str;
				t_str.Format(_T("%.2X"),t_Con.m_DES[k]);
				t_Des+=t_str;

			}
			strConInfor+=t_Des;	
			strConInfor+=_T("  ");
			t_Src+=_T("源地址:");
			for (int k =0;k<6;k++)
			{
				CString t_str;
				t_str.Format(_T("%.2X"),t_Con.m_SRC[k]);
				t_Src+=t_str;

			}
			strConInfor+=t_Src;
			strConInfor+=_T("  ");	
			t_Src+=_T("APPID:");
			for (int k =0;k<2;k++)
			{
				CString t_str;
				t_str.Format(_T("%.2X"),t_Con.m_APPID[k]);
				t_AppID+=t_str;

			}
			strConInfor+=t_AppID;
			strConInfor+=_T("  ");
			CString t_Num;
			t_Num.Format(_T("总计帧数(packet):%d"),t_Con.m_Vector.size());
			strConInfor+=t_Num;

			int t_Abnormalnum = g_pDoMesage->m_SMVAbnormalPosArray.size();
			for (int q =0;q<t_Abnormalnum;q++ )
			{
				CAbnormalPos & AbnPos = g_pDoMesage->m_SMVAbnormalPosArray[q];
				if (t_Des.Find(AbnPos.m_strMacDes)!=-1)
				{
					strConInfor+=_T("  ");
					strConInfor+=AbnPos.GetInfor();
					break;
				}
			}
			strShowResut+=strConInfor;
			strShowResut+=_T("\r\n");
		}
	}

	return strShowResut;
}

CString CToWork::GetGooseStatisticInfor()
{
	CString  strAllMsgNum,strByteAllNum,strTimeDif,strFlow,strErrorNum;
	int nAllMsgNum =0;
	nAllMsgNum = g_pDoMesage->m_GooseVector.size();
	int nErrorNum = 0;
	int t_arraysize = g_pDoMesage->m_GooseAbnormalPosArray.size();
	for (int m =0;m<t_arraysize;m++)
	{
		CAbnormalPos & t_Pos = g_pDoMesage->m_GooseAbnormalPosArray[m];
		nErrorNum+=t_Pos.m_nAllNum;
	}
	strErrorNum.Format(_T("%d"),nErrorNum);
	strAllMsgNum.Format(_T("%d"),nAllMsgNum);	

	int nAllByteNum =0;
	int nGKind = g_pDoMesage->m_GooseKindsVector.size();
	for (int n =0;n<nGKind;n++)
	{
		Content & t_Con = g_pDoMesage->m_GooseKindsVector[n];
		CPacket & Pro = g_pDoMesage->m_NewPacketVector[t_Con.m_Vector[0]];
		nAllByteNum+=(Pro.m_nDataPackLength*t_Con.m_Vector.size());
	}
	strByteAllNum.Format(_T("%d"),nAllByteNum);

	CString strShowResut = _T("Total messages:");
	strShowResut+=strAllMsgNum;
	strShowResut+=_T("\r\n");

	strShowResut+=_T("Total bytes:");
	strShowResut+=strByteAllNum;
	strShowResut+=_T("\r\n");
	// 	strShowResut+=_T("平均流量(字节/秒):");
	// 	strShowResut+=strFlow;
	// 	strShowResut+=_T("\r\n");
	strShowResut+=_T("Error number:");
	strShowResut+=strErrorNum;
	strShowResut+=_T("\r\n");

	//////////////////////////每个Content中的内容//////////////////////////////

	for (int n =0;n<nGKind;n++)
	{
		CString strConInfor = _T("");
		strConInfor+=_T("\r\n");
		strConInfor+=_T("\t");
		CString t_Des = _T("");
		CString t_Src = _T("");
		CString t_AppID = _T("");
		Content & t_Con = g_pDoMesage->m_GooseKindsVector[n];
		t_Des+=_T("Destination address:");	
		for (int k =0;k<6;k++)
		{
			CString t_str;
			t_str.Format(_T("%.2X"),t_Con.m_DES[k]);
			t_Des+=t_str;

		}
		strConInfor+=t_Des;	
		strConInfor+=_T("  ");
		t_Src+=_T("Source address:");
		for (int k =0;k<6;k++)
		{
			CString t_str;
			t_str.Format(_T("%.2X"),t_Con.m_SRC[k]);
			t_Src+=t_str;

		}
		strConInfor+=t_Src;
		strConInfor+=_T("  ");	
		t_Src+=_T("APPID:");
		for (int k =0;k<2;k++)
		{
			CString t_str;
			t_str.Format(_T("%.2X"),t_Con.m_APPID[k]);
			t_AppID+=t_str;

		}
		strConInfor+=t_AppID;
		strConInfor+=_T("  ");
		CString t_Num;
		t_Num.Format(_T("Total(packet):%d"),t_Con.m_Vector.size());
		strConInfor+=t_Num;

		strConInfor+=_T("  ");
		CString nAllByteNum;
		nAllByteNum.Format(_T("Total bytes:%ld"),t_Con.m_Vector.size()*t_Con.m_nPrePacketSize);
		strConInfor+=nAllByteNum;

		strConInfor+=_T("  ");
		CString strAllTime; 
		strAllTime.Format(_T("Total time(s):%.3f"),t_Con.t_TotalTime);
		strConInfor+=strAllTime;

		strConInfor+=_T("  ");
		CString t_EverNum;
		t_EverNum.Format(_T("Average flow (B/S):%.0f"),(t_Con.m_Vector.size()*t_Con.m_nPrePacketSize)/t_Con.t_TotalTime);
		strConInfor+=t_EverNum;

		int t_Abnormalnum = g_pDoMesage->m_GooseAbnormalPosArray.size();
		for (int q =0;q<t_Abnormalnum;q++ )
		{
			CAbnormalPos & AbnPos = g_pDoMesage->m_GooseAbnormalPosArray[q];
			if (t_Des.Find(AbnPos.m_strMacDes)!=-1)
			{
				strConInfor+=_T("  ");
				strConInfor+=AbnPos.GetInfor();
				break;
			}
		}
		strShowResut+=strConInfor;
		strShowResut+=_T("\r\n");
	}

	return strShowResut;
}


CString  CToWork::GetTimeString(int nPacket)
{
	CPacket & Pro =   g_pDoMesage->m_NewPacketVector[nPacket];

	return CGetInforFormVector::GetTimeString(g_pDoMesage,  Pro);
}

unsigned int WINAPI CToWork::ThreadFunc(LPVOID lpParam) //线程函数
{
	ExecuteAnalysis();
	return 0;
}

BOOL  CToWork::CreateThreadToAnalysis(BOOL bBuffer, CString strFileName)
{
	g_strFileName   =   strFileName;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL,  0,  &ThreadFunc,  (LPVOID)this,  0,  NULL);
	return TRUE;
}


void CToWork::SetPacketFromXSmMemBuffe(BYTE *pBuffer,  int nBufferLen)
{
	g_pDoMesage->SetPacketFromXSmMemBuffe(pBuffer,  nBufferLen);
}

void CToWork::ClearAllData()
{
	g_pDoMesage->ClearAllData();
}

CString CToWork::GetErrorInfor( int nID,   int nType,   int nCurSelContentType,  int  &nPacketNO)
{
	return g_pDoMesage->GetErrorInfor(nID,  nType,  nCurSelContentType,  nPacketNO);
}

int   CToWork::GetPacketCnt()
{
	int  nCnt = 0;
	nCnt  = g_pDoMesage->m_NewPacketVector.size();
	return  nCnt;
}

int CToWork::GetErrorCnt()
{
	CString  strType  =  _T("");
	int  nItemCnt  = 0;
	nItemCnt  = g_pDoMesage->m_NewPacketVector.size();
	int nCnt  =  0;
	int  nCurSelContentType   = 0;
	int nPacket  = 0;

	for (int i = 0;  i < nItemCnt; i++)
	{
		strType = g_pDoMesage->GetErrorInfor(i,   2,   nCurSelContentType,  nPacket);	//第三个参数是独立显示的时候，MAC得索引；	

		if (strType  !=  "")
			nCnt++;
	}

	return nCnt;
}