#include "drv_shake_test.h"
#include <stdlib.h>

/*****
enum OutPutType	//输出类型
{
	analog_type = 0;//模拟量类型
	digital_type =1;//数字量类型
	analog_digital_type = 2;//数字量+模拟量
}
//故障类型
enum Error_type
{
  Error_A_JD = 0;//
  Error_B_JD = 1;//
  Error_C_JD = 2;//
  Error_AB_DL = 3;//
  Error_BC_DL = 4;//
  Error_CA_DL = 5;//
  Error_AB_JDDL = 6;
  Error_BC_JDDL = 7;
  Error_CA_JDDL = 8;
  Error_ABC_DL = 9;
  Error_SINGLE_ZK = 10;
}

//KoMode 零序补偿系数计算方式
enum KoMode
{
	K0 = 0;
	RERL = 1;
	Z0 = 2;
}
message Template
{
		OutPutType outputType = 1;//输出类型
		CommonPara oComm = 2;  //通用参数
		SwitchPara oSwitch = 3;  //开关量
		ProtectSetting oProtectSet = 4;  //整定值参数
		repeated testItem oItems = 5;    //下发的实验参数列表
		SystemConfigPara osystemconfigpara = 6;
}
//通用参数
message CommonPara
{
		 float ED_V =1; //额定线电压
		 float ED_I = 2; //额定电流
		 float ED_Hz = 3; //额定频率
		 float prefaulttime = 4; //振荡前时间
		 uint32 ctpoint = 5; //0 指向母线，1指向线路
		 float f_zs = 6;//系统侧阻抗
		 float f_phis = 7;//PHI(zs)
		 float f_zt = 8;//变压器阻抗
		 float f_phit = 9;//PHI
		 float f_xd = 10;//发电机暂态阻抗
}
message ProtectSetting
{
		uint32  n_FreAct=1;//震荡次数
		float  f_actTime=2;//动作时间
}
message SwitchPara
{
		repeated binaryinfo bis= 1;
		repeated binaryinfo bos = 2;
		BiLogic oBilogic = 3;
}
message binaryinfo
{
   int32 nIndex = 1;
   bool  bOpen = 2;
   string strName = 3;
   bool  bValue = 4;
}

enum BiLogic{
 BL_Or = 0;
 BL_And = 1;
}

message testItem
{
		testPara otestpara = 1;
		bool bselected = 2;
		int32 nJudgeCondation = 3; //测试状态，0未测试,1测试合格,2测试不合格
		OutPutCommon.result oprocessresult = 4;//测试过程数据
		OutPutCommon.acanalogpara channlePara = 5; //故障前3U3I通道数据
		criterion ocriterion = 6;
		string	name = 7;//实验名称
		float fActtime = 8;//动作时间
		float fAccelerationtime  = 9;//加速信号时间
		float fDecelerationtime = 10;//减速信号时间
}
message testPara
{
		float fPowerangbegin = 1;//功角始值
		float fPowerangend = 2;//功角终值
		float fCycle = 3; //振荡周期
		uint32 nNum= 4;//循环次数
		float fRate= 5;//em/en
		uint32 nTrip = 6;//跳闸接入点
		uint32 nTripspeedup = 7;
		uint32 nTripspeeddown = 8;
		float fFre = 9;//频率
		float fDZdt = 10;//dz/dt
		bool bReciprocating = 11;//往复
		bool bExtrafault = 12;//是否转换性故障
		Error_type nFaultType = 13;//故障类型
		float fImpedance = 14;//短路阻抗
		float fCurrent = 15;//短路电流
		float fTime = 16;//故障发生时间
		KoMode Emode = 17;   //零序补偿系数计算方式
		float fKoOrRe = 18;  //零序补偿比例系数
		float fPhiOrIm = 19; //零序相位补偿系数
		bool bAccelerate = 20;//加速
		bool bDzdt = 21;//DZDT
}
message SystemConfigPara
{
		OutPutType type = 1;//输出类型
		float acVolMax = 2;//交流电压
		float acCurrentMax = 3;//交流电流
		float dcVolMax = 4;//直流电压
		float dcCurrentMax = 5;//直流电流
		float dcAUX = 6;//辅助直流最大值
		float fdcauxout = 7;//辅助直流输出值
}
message  criterion
{
		bool bAbsoluteerrchecked = 1; //绝对误差
		bool bRefernceerrchecked = 2;//相对误差
		float fAbsoluteSet = 3;
		float frefernceSet = 4;	//评估值
}
****/

/*
void ConstructShakeAnalogData(drv_shakepara& data,tmt_channel &m_uiVOL,tmt_channel &m_uiCUR,unsigned int *nRetModule)
{
	int nAnalogCurrentModuleCount = 1;
	int nAnalogVoltModueCount = 1;

	int j=0;
	long buffer[CHANNEL_MAX*3];
	memset(buffer,0,sizeof(long)*18);
	int nChannelCount = 3;
	int nTemp = nChannelCount/CHANNEL_MAX;
	int nRem = nChannelCount%CHANNEL_MAX;
	if(nRem>0)
		nTemp+=1;
	for(int i =0;i<nTemp;i++)
	{
		memset(buffer,0,sizeof(long)*18);
		if(i<nAnalogCurrentModuleCount)
		{
			nRetModule[j] = Device::g_Device->getModuleNum(CURRENT,i);
			int nEndCount = (i+1)*CHANNEL_MAX;
			if(nEndCount>=nChannelCount)
				nEndCount = nChannelCount;

			getACCurrentBufferDCZero(pAcPara,data.alg[j].dat,i*CHANNEL_MAX,nEndCount);
			TranslateACCurrentBuffer(pAcPara, buffer,i*CHANNEL_MAX,nEndCount);

			memcpy(data.alg[j].dat+CHANNEL_MAX,buffer,18*sizeof(long));
			j++;
		}
	}
	nChannelCount = 3;
	nTemp = nChannelCount/CHANNEL_MAX;
	nRem = nChannelCount%CHANNEL_MAX;
	if(nRem>0)
		nTemp+=1;
	for(int i =0;i<nTemp;i++)
	{
		memset(buffer,0,sizeof(long)*18);
		if(i<nAnalogVoltModueCount)
		{
			nRetModule[j] = Device::g_Device->getModuleNum(VOLT,i);
			int nEndCount = (i+1)*CHANNEL_MAX;
			if(nEndCount>=nChannelCount)
				nEndCount = nChannelCount;

			getACVoltBufferDCZero(pAcPara,data.alg[j].dat,i*CHANNEL_MAX,nEndCount);
			TranslateACVoltBuffer(pAcPara, buffer,i*CHANNEL_MAX,nEndCount);
			memcpy(data.alg[j].dat+CHANNEL_MAX,buffer,18*sizeof(long));
			j++;
		}
	}
}

void ContructShakeDititalData(drv_shakepara& data,OutPutCommon::acanalogpara* pAcPara,unsigned int *nRetModule)
{
	int nModuleCount =1;
	nRetModule[0] =DIGITAL_CHANNEL_MARK;
	for(int i=0;i<nModuleCount;i++)
	{
		drv_shakesv& oItem = data.smv[i];
		memset(oItem.dat,0,DIGITAL_CHANNEL_MAX * 3*sizeof(long));
		CSttDevice::g_pSttDevice->TranslateACDigitalVoltBuffer(pAcPara,oItem.dat,false);
		CSttDevice::g_pSttDevice->TranslateACDigitalCurrentBuffer(pAcPara,oItem.dat,false);
	}

}

//故障类型
#define Error_A_JD       0
#define Error_B_JD       1
#define Error_C_JD       2
#define Error_AB_DL      3
#define Error_BC_DL      4
#define Error_CA_DL      5
#define Error_AB_JDDL    6
#define Error_BC_JDDL    7
#define Error_CA_JDDL    8
#define Error_ABC_DL     9
#define Error_SINGLE_ZK  10

//KoMode 零序补偿系数计算方式
#define K0    0
#define RERL  1
#define Z0    2

typedef struct
{
	float fPowerangbegin;//功角始值
	float fPowerangend;//功角终值
	float fCycle; //振荡周期
	unsigned int nNum;//循环次数
	float fRate;//em/en
	unsigned int nTrip;//跳闸接入点
	float fFre;//频率
	float fDZdt;//dz/dt
	bool bReciprocating;//往复
	bool bExtrafault;//是否转换性故障
	int nFaultType;//故障类型
	float fImpedance;//短路阻抗
	float fCurrent;//短路电流
	float fTime;//故障发生时间
	int nmode;   //零序补偿系数计算方式
	float fKoOrRe;  //零序补偿比例系数
	float fPhiOrIm; //零序相位补偿系数
	bool bAccelerate;//加速
	bool bDzdt;//DZDT
}tmt_testpara;

typedef struct
{
	float ED_V; //额定线电压
	float ED_Hz; //额定频率
	float prefaulttime; //振荡前时间
	float f_zs;//系统侧阻抗
	float f_phis;//PHI(zs)
	float f_zt;//变压器阻抗
	float f_phit;//PHI
	float f_xd;//发电机暂态阻抗
}tmt_CommonPara;

typedef struct
{
   tmt_testpara testpara;
}tmt_state;

typedef struct
{
	tmt_CommonPara compara;
	tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
	tmt_state state[100];
}tmt_states;

int m_nCurrentIndex=0;

void Init()
{
	tmt_states ostates;
	tmt_state current_state=ostates.state[m_nCurrentIndex];


	int Output=CSttDevice::g_pSttDevice->m_oDevSysParas.m_nOutputMode;//0-模拟 1-数字
	bool extrafault=current_state.testpara.bExtrafault;//振荡中在故障

	Complex pVg,pVs,pI[720],pV[720];
	Complex pVaf[720],pVbf[720],pVcf[720],pIaf[720],pIbf[720],pIcf[720];
	Complex pITemp[720];
	Complex p1,p2,pt,pK0,pa,pb;
	Complex fXs,fXt,fXd;

	float fVnom = ostates.compara.ED_V;
	pVs=p1.polar(fVnom,0.0);
	fXs = p1.polar(ostates.compara.f_zs,ostates.compara.f_phis);
	fXt = p1.polar(ostates.compara.f_zt,ostates.compara.f_phit);
	fXd = p1.polar(ostates.compara.f_xd,90);
	float fIf = current_state.testpara.fCurrent;
	float fZf = current_state.testpara.fImpedance;

	float fAngleStart = 0;
	float fAngleStep = 360.0;
	int nStep = 360;
	int binout = 0;
	for(int i =0;i<8;i++)
	{
		binout += ((!ostates.m_binOut[i].nState)*(1<<i));
	}

	CSttDriverOper::SetBinaryOut(binout);

	if(current_state.testpara.bReciprocating)
	{
		float fend2begin=current_state.testpara.fPowerangend-current_state.testpara.fPowerangbegin;
		fAngleStart = current_state.testpara.fPowerangbegin;
		fAngleStep = fend2begin;
		nStep=fabs(fend2begin*2.0);
	}
	else
	{
		fAngleStart=current_state.testpara.fPowerangbegin;
		nStep = 720;
		if(current_state.testpara.bAccelerate)
		{
			fAngleStep = 360.0;
		}
		else
		{
			fAngleStep = -360.0;
		}
	}

	int nStepCal = nStep-1;
	for(int i=0;i<nStep;i++)
	{
		pt=p2.polar(fVnom*current_state.testpara.fRate,fAngleStart+i*fAngleStep/nStepCal);
		pI[i]=(pt-pVs)/(fXs+fXd+fXt);
		pV[i]=pI[i]*(fXs+fXt)+pVs;
	}

	if(extrafault) //振荡中在故障
	{
		CFaultCalculat FaultCalculat;
		int nK0CalMode = current_state.testpara.nmode;
		float fKr=current_state.testpara.fKoOrRe;
		float fKx = current_state.testpara.fPhiOrIm;

		pa=FaultCalculat.GroundFactor(nK0CalMode,fKr,fKx,pb.arg(fXd));//m_fZPhi);
		float fK0l=pb.norm(pa);
		float fK0lPh=pb.arg(pa);
		pK0=pa.polar(fK0l+1.0,fK0lPh);
		float fVs;
		fVs=fIf*(p1.norm(fXd)+fZf);//powertest m_fIf 文件读取，文件确定是5A  m_fZf 1.0

		float frate=current_state.testpara.fRate;
		switch(current_state.testpara.nFaultType)
		{
		case Error_A_JD:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-78.0);
				pVaf[i]=pt-fXd*pK0*pIaf[i];
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVbf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVcf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-78.0);
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pIbf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pIcf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			break;
		}
		case Error_B_JD:
		{
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVaf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pI[i]));
				pVbf[i]=pt-fXd*pK0*pIbf[i];
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVcf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
				pIaf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pI[i]));
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pIcf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			break;
		}
		case Error_C_JD:
		{
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVaf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVbf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pI[i]));
				pVcf[i]=pt-fXd*pK0*pIcf[i];
			}
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
				pIaf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pIbf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pI[i]));
			}
			break;
		}
		case Error_AB_DL:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+120.0);
				pVaf[i]=pt-fXd*pIaf[i];
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-60.0);
				pVbf[i]=pt-fXd*pIbf[i];
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVcf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+120.0);
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-60.0);
			}
			pVs=p1.polar(fVnom,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pIcf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			break;
		}
		case Error_BC_DL:
		{
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVaf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
				pVbf[i]=pt-fXd*pIbf[i];
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+60.0);
				pVcf[i]=pt-fXd*pIcf[i];
			}
			pVs=p1.polar(fVnom,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
				pIaf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0+60.0);
			}
			break;
		}
		case Error_CA_DL:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0+180.0);
				pVaf[i]=pt-fXd*pIaf[i];
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pVbf[i]=pITemp[i]*(fXs+fXt)+pVs;
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
				pVcf[i]=pt-fXd*pIcf[i];
			}
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0+180.0);
			}
			pVs=p1.polar(fVnom,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pIbf[i]=(pt-pVs)/(fXs+fXd+fXt);
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
			}
			break;
		}
		case Error_ABC_DL:
		{
			pVs=p1.polar(fVs,0.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIaf[i]=pITemp[i]+p1.polar(fIf,-78.0);
				pVaf[i]=pt-fXd*pIaf[i];
			}
			pVs=p1.polar(fVs,-120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIbf[i]=pITemp[i]+p1.polar(fIf,-78.0-120.0);
				pVbf[i]=pt-fXd*pIbf[i];
			}
			pVs=p1.polar(fVs,120.0);
			for(int i=0;i<nStep;i++)
			{
				pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
				pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
				pIcf[i]=pITemp[i]+p1.polar(fIf,-78.0+120.0);
				pVcf[i]=pt-fXd*pIcf[i];
			}
			break;
		}
		default:
			break;
		}
	}

	drv_shake *oshake = new drv_shake;
	memset(oshake,0,sizeof(drv_shake));

	oshake->nBinaryInput = 1<<current_state.testpara.nTrip;

	switch(Output)
	{
	case 0:
		oshake->algCount = 2;
		oshake->digCount = 0;
		break;
	case 1:
		oshake->algCount = 0;
		oshake->digCount = 1;
		break;
	}

	oshake->shakeCount = nStep;
	oshake->isRecip = current_state.testpara.bReciprocating;
	oshake->timeBfShake = ostates.compara.prefaulttime*1000;
	oshake->timeDiv = current_state.testpara.fCycle*NANOSECOND/nStep;

	if(current_state.testpara.bReciprocating)
	{
		oshake->timeDiv /=2;
	}

	if(extrafault) //振荡中在故障
	{
		double fsumtime = current_state.testpara.fCycle*current_state.testpara.nNum*NANOSECOND;
		oshake->timeShake = (current_state.testpara.fTime*NANOSECOND)/oshake->timeDiv;
		oshake->timeFault = (fsumtime-current_state.testpara.fTime*NANOSECOND)/oshake->timeDiv;
	}
	else
	{
		double ftime = current_state.testpara.fCycle*current_state.testpara.nNum*NANOSECOND;
		oshake->timeShake = ftime/oshake->timeDiv;
		oshake->timeFault = 0;
	}

	tmt_channel m_uiVOL[3];
	tmt_channel m_uiCUR[3];

	float fPhe[3]= {0,-120,120};
	for(int i=0;i<3;i++)
	{
		m_uiVOL[i].Harm[1].fAmp=pV[0].norm();
		m_uiVOL[i].Harm[1].fAngle=fPhe[i]+pV[0].arg();
		m_uiVOL[i].Harm[1].fFreq=ostates.compara.ED_Hz;
		m_uiCUR[i].Harm[1].fAmp=pI[0].norm();
		m_uiCUR[i].Harm[1].fAngle=fPhe[i]+pI[0].arg();
		m_uiCUR[i].Harm[1].fFreq=ostates.compara.ED_Hz;
	}

	drv_shakepara preshake;
	memset(&preshake,0,sizeof(drv_shakepara));

	switch(Output)
	{
	case 0:
	{
		//alg
		ConstructShakeAnalogData(preshake,m_uiVOL,m_uiCUR,oshake->algModule);
	}
		break;
	case 1:
	{
		//dig
		ContructShakeDititalData(preshake,&preFault,oshake->digModule);
	}
		break;
	}
	oshake->bfShake = preshake;

	drv_shakepara shake;

	for(int i =0;i<nStep;i++)
	{
		for(int j=0;j<3;j++)
		{
			m_uiVOL[j].Harm[1].fAmp=pV[i].norm();
			m_uiVOL[j].Harm[1].fAngle=fPhe[j]+pV[i].arg();
			m_uiVOL[j].Harm[1].fFreq=ostates.compara.ED_Hz;
			m_uiCUR[j].Harm[1].fAmp=pI[i].norm();
			m_uiCUR[j].Harm[1].fAngle=fPhe[j]+pI[i].arg();
			m_uiCUR[j].Harm[1].fFreq=ostates.compara.ED_Hz;
		}
		switch(Output)
		{
		case 0:
		{
			//alg
			ConstructShakeAnalogData(shake,m_uiVOL,m_uiCUR,oshake->algModule);
		}
			break;
		case 1:
		{
			//dig
			ContructShakeDititalData(shake,&shakepara,oshake->digModule);
		}
			break;
		}
	}

	oshake->shake[i] = shake;

	if(extrafault)
	{
		for(int i =0;i<nStep;i++)
		{
			drv_shakepara shake;

			m_uiVOL[0].Harm[1].fAmp=pVaf[i].norm();
			m_uiVOL[0].Harm[1].fAngle=pVaf[i].arg();
			m_uiVOL[0].Harm[1].fFreq=ostates.compara.ED_Hz;
			m_uiVOL[1].Harm[1].fAmp=pVbf[i].norm();
			m_uiVOL[1].Harm[1].fAngle=pVbf[i].arg();
			m_uiVOL[1].Harm[1].fFreq=ostates.compara.ED_Hz;
			m_uiVOL[2].Harm[1].fAmp=pVcf[i].norm();
			m_uiVOL[2].Harm[1].fAngle=pVcf[i].arg();
			m_uiVOL[2].Harm[1].fFreq=ostates.compara.ED_Hz;

			m_uiCUR[0].Harm[1].fAmp=pIaf[i].norm();
			m_uiCUR[0].Harm[1].fAngle=pIaf[i].arg();
			m_uiCUR[0].Harm[1].fFreq=ostates.compara.ED_Hz;
			m_uiCUR[1].Harm[1].fAmp=pIbf[i].norm();
			m_uiCUR[1].Harm[1].fAngle=pIbf[i].arg();
			m_uiCUR[1].Harm[1].fFreq=ostates.compara.ED_Hz;
			m_uiCUR[2].Harm[1].fAmp=pIcf[i].norm();
			m_uiCUR[2].Harm[1].fAngle=pIcf[i].arg();
			m_uiCUR[2].Harm[1].fFreq=ostates.compara.ED_Hz;

			switch(Output)
			{
			case 0:
				ConstructShakeAnalogData(shake,&shakepara,oshake->algModule);
				break;
			case 1:
				ContructShakeDititalData(shake,&shakepara,oshake->digModule);
				break;
			}
			oshake->falut[i] = shake;
		}
	}

	CSttDriverOper::setSwingingPara((char*)(oshake),sizeof(drv_shake));
	delete oshake;
}

*/

void CalStepShakeUINormal(const Complex &cmpVIn, const Complex &cmpXs, const Complex &cmpXt, const Complex &cmpXd,
							float fRate, float fCurValue, Complex &cmpVOut, Complex &cmpIOut)
{
	Complex pt, p1;
	
	pt = p1.polar(cmpVIn.norm()*fRate, fCurValue);
	cmpIOut = (pt - cmpVIn)/(cmpXs+cmpXd+cmpXt);
	cmpVOut = cmpIOut*(cmpXs+cmpXt)+cmpVIn;
}

void CalStepShakeUISingle(const Complex &cmpVIn, const Complex &cmpIf, const Complex &cmpXs, 
							const Complex &cmpXt, const Complex &cmpXd, const Complex &cmpk0, 
							float fRate, float fCurValue, Complex &cmpVOut, Complex &cmpIOut)
{
	Complex pt, p1;
	
	pt = p1.polar(cmpVIn.norm()*fRate, fCurValue);
	cmpIOut = (pt - cmpVIn)/(cmpXs+cmpXd+cmpXt) + cmpIf;
	cmpVOut = pt - cmpXd*cmpk0*cmpIOut;
}

void CalStepShakeUINonSingle(const Complex &cmpVIn, const Complex & cmpIf, const Complex &cmpXs,
							const Complex &cmpXt, const Complex &cmpXd, float fRate, 
							float fCurValue, Complex &cmpVOut, Complex &cmpIOut)
{
	Complex pt, p1;
	
	pt = p1.polar(cmpVIn.norm()*fRate, fCurValue);
	cmpIOut = (pt - cmpVIn)/(cmpXs+cmpXd+cmpXt) + cmpIf;
	cmpVOut = pt - cmpXd*cmpIOut;
}

void tmt_to_drv_shake_alg(Complex *pV, Complex *pI, float fFreq, int nIndex, drv_shakepara &oShakePara, unsigned int *nModule)
{
    float fPhe[3] = {0, -120, 120};

    nModule[0] = CUR_CHANNEL_MARK;
    nModule[1] = VOL_CHANNEL_MARK;
    for(int i=0; i<CHANNEL_MAX; i++)//只需要前面三相电压即可
    {
       CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(pI[nIndex].norm(),
                fPhe[i]+pI[nIndex].arg(),
                fFreq, i,
                oShakePara.alg[0].ndat);

        CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(pV[nIndex].norm(),
                fPhe[i]+pV[nIndex].arg(),
                fFreq, i,
                oShakePara.alg[1].ndat);
    }
}

void tmt_to_drv_shake_dig(Complex *pV, Complex *pI, float fFreq, int nIndex, drv_shakepara &oShakePara, unsigned int *nModule)
{
    float fPhe[3] = {0, -120, 120};
    int nChannelA_drv_Index_Volt, nChannelA_drv_Index_Curr;

    nModule[0] = DIGITAL_CHANNEL_MARK;
    for(int i=0; i<MAX_DIGITAL_GROUP_NUM; i++)
    {
		//bool ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Volt,VOLT);
		//ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Curr,CURRENT);

		nChannelA_drv_Index_Volt=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,VOLT,Ang);
		nChannelA_drv_Index_Curr=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,CURRENT,Ang);
        for(int channel=0;channel<3;channel++)//A B C
        {
            CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(pV[nIndex].norm(),
                    fPhe[channel]+pV[nIndex].arg(),
                    fFreq, i ,
                    &oShakePara.smv[0].ndat[nChannelA_drv_Index_Volt + channel*3]);

            CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurToDrv(pI[nIndex].norm(),
                    fPhe[channel]+pI[nIndex].arg(),
                    fFreq, i ,
                    &oShakePara.smv[0].ndat[nChannelA_drv_Index_Curr + channel*3]);
        }
    }
}

void tmt_to_drv(tmt_ShakeTest *pTmt, drv_shake_test *pDrv)
{
    memset(pDrv, 0, sizeof(drv_shake_test));
    Complex pVs,pI[720],pV[720];
//    Complex pVaf[720],pVbf[720],pVcf[720],pIaf[720],pIbf[720],pIcf[720];
    Complex pVChannelF[720][CHANNEL_MAX] ;//故障时振荡电压点
    Complex pIChannelF[720][CHANNEL_MAX];//故障时振荡电流点
//    Complex pITemp[720];
    Complex p1,p2,pt,pK0,pa,pb;
    Complex fXs,fXt,fXd;

    float fVnom = pTmt->m_oShakeParas.oCommonPara.m_fUNom;
    pVs = p1.polar(fVnom, 0.0);
    fXs = p1.polar(pTmt->m_oShakeParas.m_fZS, pTmt->m_oShakeParas.m_fPhisS);
    fXt = p1.polar(pTmt->m_oShakeParas.m_fZT, pTmt->m_oShakeParas.m_fPhisT);
    fXd = p1.polar(pTmt->m_oShakeParas.m_fXD, 90);
    float fIf= pTmt->m_oShakeParas.m_fFaultCur;
    float fZf = pTmt->m_oShakeParas.m_fImpedance;
    float fAngleStart = 0;
    float fAngleStep = 360;
    //计算步数
    int nStep = 360;

    fAngleStart = pTmt->m_oShakeParas.m_fPowerAngStart;
    if(pTmt->m_oShakeParas.m_bReciprocating)//往复
    {      
        fAngleStep = pTmt->m_oShakeParas.m_fPowerAngEnd - pTmt->m_oShakeParas.m_fPowerAngStart;
    }
    else
    {
        if(pTmt->m_oShakeParas.m_bAccelerate)//加速
        {
            fAngleStep = 360;
        }
        else
        {
            fAngleStep = -360;
        }
    }
    nStep = fabs(fAngleStep)*2.0;
    int nStepCal = nStep-1;
	float frate = pTmt->m_oShakeParas.m_fRate;
    for(int i=0; i<nStep; i++)
    {
		float fCurValue = fAngleStart+i*fAngleStep/nStepCal;
		CalStepShakeUINormal(pVs, fXs, fXt, fXd, frate, fCurValue, pV[i], pI[i]);
/*         pt = p1.polar(fVnom*frate, fAngleStart+i*fAngleStep/nStepCal);
        pi[i] = (pt - pVs)/(fXs+fXd+fXt);
        pV[i] = pI[i]*(fXs+fXt)+pVs; */
    }

    if(pTmt->m_oShakeParas.m_bExtraFault)
    {
        CFaultCalculat faultCalculat;
        int nK0CalMode = pTmt->m_oShakeParas.m_nK0Mode;
        float fKr = pTmt->m_oShakeParas.m_fKoOrRe;
        float fKx = pTmt->m_oShakeParas.m_fPhiOrIm;

        pa = faultCalculat.GroundFactor(nK0CalMode,fKr,fKx,pb.arg(fXd));//m_fZPhi);
        float fK0l=pb.norm(pa);
        float fK0lPh=pb.arg(pa);
        pK0=pa.polar(fK0l+1.0,fK0lPh);
        float fVs;
        fVs=fIf*(p1.norm(fXd)+fZf);//powertest m_fIf 文件读取，文件确定是5A  m_fZf 1.0
 
        Complex pTemp[3] = {p1.polar(fVnom, 0.0), p1.polar(fVnom, -120.0), p1.polar(fVnom, 120.0)};
        switch(pTmt->m_oShakeParas.m_nFaultType)
        {
        case ERR_A_JD:
        {
			float fCurValue = 0;

			pVs = p1.polar(fVs,0.0);
			pTemp[0] = pVs;
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				
				CalStepShakeUISingle(pTemp[0], p1.polar(fIf,-78.0), fXs, fXt, fXd, 
										pK0, frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);
										
				CalStepShakeUINormal(pTemp[1], fXs, fXt, fXd, 
							frate, fCurValue-120, pVChannelF[i][1], pIChannelF[i][1]);
				CalStepShakeUINormal(pTemp[2], fXs, fXt, fXd, 
							frate, fCurValue+120, pVChannelF[i][2], pIChannelF[i][2]);
			}



/*             pVs = p1.polar(fVs,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt = p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][0]=pITemp[i]+p1.polar(fIf,-78.0);
                pVChannelF[i][0]=pt-fXd*pK0*pIChannelF[i][0];
            }
            pVs=p1.polar(fVnom,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pIChannelF[i][1]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][1]=pIChannelF[i][1]*(fXs+fXt)+pVs;
            }
            pVs=p1.polar(fVnom,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pIChannelF[i][2]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][2]=pIChannelF[i][2]*(fXs+fXt)+pVs;
            } */
            break;
        }
        case ERR_B_JD:
        {
			float fCurValue = 0;

			pVs = p1.polar(fVs,-120.0);
			pTemp[1] = pVs;
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				CalStepShakeUINormal(pTemp[0], fXs, fXt, fXd, 
							frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);
				CalStepShakeUISingle(pTemp[1], p1.polar(fIf,-78.0), fXs, fXt, fXd, 
										pK0, frate, fCurValue-120.0, pVChannelF[i][1], pIChannelF[i][1]);
				CalStepShakeUINormal(pTemp[2], fXs, fXt, fXd, 
							frate, fCurValue+120, pVChannelF[i][2], pIChannelF[i][2]);
			}
			
/*             pVs=p1.polar(fVnom,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
                pIChannelF[i][0]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][0]=pIChannelF[i][0]*(fXs+fXt)+pVs;
            }
            pVs=p1.polar(fVs,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][1]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pI[i]));
                pVChannelF[i][1]=pt-fXd*pK0*pIChannelF[i][1];
            }
            pVs=p1.polar(fVnom,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pIChannelF[i][2]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][2]=pIChannelF[i][2]*(fXs+fXt)+pVs;
            } */
            break;
        }
        case ERR_C_JD:
        {
			float fCurValue = 0;

			pVs = p1.polar(fVs,120.0);
			pTemp[2] = pVs;
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				CalStepShakeUINormal(pTemp[0], fXs, fXt, fXd, 
										frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);
				CalStepShakeUINormal(pTemp[1], fXs, fXt, fXd, 
										frate, fCurValue-120.0, pVChannelF[i][1], pIChannelF[i][1]);
				CalStepShakeUISingle(pTemp[2], p1.polar(fIf,-78.0), fXs, fXt, fXd, 
										pK0, frate, fCurValue-120.0, pVChannelF[i][2], pIChannelF[i][2]);
			}
/*             pVs=p1.polar(fVnom,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
                pIChannelF[i][0]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][0]=pIChannelF[i][0]*(fXs+fXt)+pVs;
            }
            pVs=p1.polar(fVnom,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pIChannelF[i][1]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][1]=pIChannelF[i][1]*(fXs+fXt)+pVs;
            }
            pVs=p1.polar(fVs,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][2]=pITemp[i]+p1.polar(fIf,-78.0);//p2.arg(pI[i]));
                pVChannelF[i][2]=pt-fXd*pK0*pIChannelF[i][2];
            } */
            break;
        }
        case ERR_AB_DL:
        {
			float fCurValue = 0;

			pTemp[0] = p1.polar(fVs,0.0);
			pTemp[1] = p1.polar(fVs,-120.0);
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				CalStepShakeUINonSingle(pTemp[0], p1.polar(fIf,-90.0+78.0+120.0), fXs, fXt, fXd, 
											frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);
				CalStepShakeUINonSingle(pTemp[1], p1.polar(fIf,-90.0+78.0-60.0), fXs, fXt, fXd, 
                                            frate, fCurValue-120.0, pVChannelF[i][1], pIChannelF[i][1]);
				CalStepShakeUINormal(pTemp[2], fXs, fXt, fXd, 
										frate, fCurValue+120, pVChannelF[i][2], pIChannelF[i][2]);				
			}
/*             pVs=p1.polar(fVs,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][0]=pITemp[i]+p1.polar(fIf,-90.0+78.0+120.0);
                pVChannelF[i][0]=pt-fXd*pIChannelF[i][0];
            }
            pVs=p1.polar(fVs,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][1]=pITemp[i]+p1.polar(fIf,-90.0+78.0-60.0);
                pVChannelF[i][1]=pt-fXd*pIChannelF[i][1];
            }
            pVs=p1.polar(fVnom,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pIChannelF[i][2]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][2]=pIChannelF[i][2]*(fXs+fXt)+pVs;
            } */
            break;
        }
        case ERR_BC_DL:
        {
			float fCurValue = 0;

			pTemp[1] = p1.polar(fVs,-120.0);
			pTemp[2] = p1.polar(fVs,120.0);
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				CalStepShakeUINormal(pTemp[0], fXs, fXt, fXd, 
										frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);	
				CalStepShakeUINonSingle(pTemp[1], p1.polar(fIf,-90.0+78.0-120.0), fXs, fXt, fXd, 
											frate, fCurValue-120.0, pVChannelF[i][1], pIChannelF[i][1]);
				CalStepShakeUINonSingle(pTemp[2], p1.polar(fIf,-90.0+78.0+60.0), fXs, fXt, fXd, 
                                            frate, fCurValue+120.0, pVChannelF[i][2], pIChannelF[i][2]);
			}
/*             pVs=p1.polar(fVnom,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal);
                pIChannelF[i][0]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][0]=pIChannelF[i][0]*(fXs+fXt)+pVs;
            }
            pVs=p1.polar(fVs,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][1]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
                pVChannelF[i][1]=pt-fXd*pIChannelF[i][1];
            }
            pVs=p1.polar(fVs,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][2]=pITemp[i]+p1.polar(fIf,-90.0+78.0+60.0);
                pVChannelF[i][2]=pt-fXd*pIChannelF[i][2];
            } */
            break;
        }
        case ERR_CA_DL:
        {
			float fCurValue = 0;

			pTemp[0] = p1.polar(fVs,0.0);
			pTemp[2] = p1.polar(fVs,120.0);
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				CalStepShakeUINonSingle(pTemp[0], p1.polar(fIf,-90.0+78.0-120.0+180.0), fXs, fXt, fXd, 
											frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);
				CalStepShakeUINormal(pTemp[1], fXs, fXt, fXd, 
										frate, fCurValue-120.0, pVChannelF[i][1], pIChannelF[i][1]);					
				CalStepShakeUINonSingle(pTemp[2], p1.polar(fIf,-90.0+78.0-120.0), fXs, fXt, fXd, 
                                            frate, fCurValue+120.0, pVChannelF[i][2], pIChannelF[i][2]);
			}
/*             pVs=p1.polar(fVs,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][0]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0+180.0);
                pVChannelF[i][0]=pt-fXd*pIChannelF[i][0];
            }
            pVs=p1.polar(fVnom,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVnom*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pIChannelF[i][1]=(pt-pVs)/(fXs+fXd+fXt);
                pVChannelF[i][1]=pIChannelF[i][1]*(fXs+fXt)+pVs;
            }
            pVs=p1.polar(fVs,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][2]=pITemp[i]+p1.polar(fIf,-90.0+78.0-120.0);
                pVChannelF[i][2]=pt-fXd*pIChannelF[i][2];
            } */
            break;
        }
        case ERR_ABC_DL:
        {
			float fCurValue = 0;

			pTemp[0] = p1.polar(fVs,0.0);
			pTemp[1] = p1.polar(fVs,-120.0);
			pTemp[2] = p1.polar(fVs,120.0);
			
			for(int i=0;i<nStep;i++)
			{
				fCurValue = fAngleStart+i*fAngleStep/nStepCal;
				CalStepShakeUINonSingle(pTemp[0], p1.polar(fIf,-78.0), fXs, fXt, fXd, 
											frate, fCurValue, pVChannelF[i][0], pIChannelF[i][0]);
				CalStepShakeUINonSingle(pTemp[1], p1.polar(fIf,-78.0-120.0), fXs, fXt, fXd, 
                                            frate, fCurValue-120.0, pVChannelF[i][1], pIChannelF[i][1]);
				CalStepShakeUINonSingle(pTemp[2], p1.polar(fIf,-78.0+120.0), fXs, fXt, fXd, 
                                            frate, fCurValue+120.0, pVChannelF[i][2], pIChannelF[i][2]);
			}
/*             pVs=p1.polar(fVs,0.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][0]=pITemp[i]+p1.polar(fIf,-78.0);
                pVChannelF[i][0]=pt-fXd*pIChannelF[i][0];
            }
            pVs=p1.polar(fVs,-120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal-120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][1]=pITemp[i]+p1.polar(fIf,-78.0-120.0);
                pVChannelF[i][1]=pt-fXd*pIChannelF[i][1];
            }
            pVs=p1.polar(fVs,120.0);
            for(int i=0;i<nStep;i++)
            {
                pt=p2.polar(fVs*frate,fAngleStart+i*fAngleStep/nStepCal+120.0);
                pITemp[i]=(pt-pVs)/(fXs+fXd+fXt);
                pIChannelF[i][2]=pITemp[i]+p1.polar(fIf,-78.0+120.0);
                pVChannelF[i][2]=pt-fXd*pIChannelF[i][2];
            } */
            break;
        }
        default:
            break;
        }
    }

    pDrv->nshakeCount = nStep;
    pDrv->nBinaryInput = 1<<pTmt->m_oShakeParas.m_nTripPt;
    pDrv->nisRecip = pTmt->m_oShakeParas.m_bReciprocating;
    pDrv->ntimeDiv = pTmt->m_oShakeParas.m_fCycle*NANOSECOND/nStep;
    pDrv->ntimeBfShake = pTmt->m_oShakeParas.m_fPreFaultTime*1000;

    if(pTmt->m_oShakeParas.m_bExtraFault)
    {
        double fSumTime = pTmt->m_oShakeParas.m_fCycle*pTmt->m_oShakeParas.m_nShakeNum*NANOSECOND;
        pDrv->ntimeShake = pTmt->m_oShakeParas.m_fFaultTime*NANOSECOND/ pDrv->ntimeDiv;
        pDrv->ntimeFault = (fSumTime-pTmt->m_oShakeParas.m_fFaultTime*NANOSECOND)/ pDrv->ntimeDiv;
    }
    else
    {
        double fSumTime = pTmt->m_oShakeParas.m_fCycle*pTmt->m_oShakeParas.m_nShakeNum*NANOSECOND;
        pDrv->ntimeShake = fSumTime/pDrv->ntimeDiv;
        pDrv->ntimeFault = 0;
    }

    pDrv->nalgCount = 2;
    pDrv->ndigCount = 1;
    //振荡前数据--模拟
    tmt_to_drv_shake_alg(pV, pI, pTmt->m_oShakeParas.m_fFreq, 0, pDrv->bfShake, pDrv->nalgModule);

    for(int i=0; i<nStep; i++)
    {
        tmt_to_drv_shake_alg(pV, pI, pTmt->m_oShakeParas.m_fFreq, i, pDrv->shake[i], pDrv->nalgModule);
    }
    //振荡前数据--数字
    tmt_to_drv_shake_dig(pV, pI, pTmt->m_oShakeParas.m_fFreq, 0, pDrv->bfShake, pDrv->ndigModule);
    for(int i=0; i<nStep; i++)
    {
        tmt_to_drv_shake_dig(pV, pI, pTmt->m_oShakeParas.m_fFreq, i, pDrv->shake[i], pDrv->ndigModule);
    }

    //振荡中故障
    if(pTmt->m_oShakeParas.m_bExtraFault)
    {
        for(int i=0; i<nStep; i++)
        {
            tmt_to_drv_shake_alg(pVChannelF[i], pIChannelF[i], pTmt->m_oShakeParas.m_fFreq, i, pDrv->falut[i], pDrv->nalgModule);
            tmt_to_drv_shake_dig(pVChannelF[i], pIChannelF[i], pTmt->m_oShakeParas.m_fFreq, i, pDrv->falut[i], pDrv->ndigModule);
        }
    }
}
