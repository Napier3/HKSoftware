#ifndef CB_DEFINE_H
#define CB_DEFINE_H
#include <QMap>
#include <QString>
#include <QPen>
#include <QMetaType>

#include "Define.h"


//矢量图线
// struct LineInfor
// {
// 	QString m_UIType;
// 	float m_RealValue;
// 	float m_XW;
// 	bool m_bShowOrHide;
// 	QPen m_Color;
// 	float m_ChangeFactor;
// };

//Id 制动电流 Ir 差动电流
// struct TestInfo
// {
// 	QString strName;
// 	ErrorType type;	
// 	bool bSelected;
// 	int index;								//因为可重复的 所以从1   -   N
// 	QString strResult;
// 	int iStatus;							//0:未测试 1 已测试并成功 2已测试但是失败
// 	TestInfo()
// 	{
// 		iStatus = 0;
// 		bSelected = false;
// 	}
// 
// 	TestInfo &operator = (const TestInfo &right)
// 	{
// 		iStatus = right.iStatus;
// 		type = right.type;
// 		strName = right.strName;
// 		bSelected = right.bSelected;
// 		strResult = right.strResult;
// 
// 		return *this;
// 	}
// };

/*
struct SwitchPara
{
	int KA;
	bool bKA;
	int KB;
	bool bKB;
	int KC;
	bool bKC;
	int KCHZ;
	int K1;
	int K2;
	int K3;
	int K4;
	int K5;
	int K6;
	int K7;
	int K8;
	int OutMode;
	float TurnTime;
	float HoldTime;

	SwitchPara()
	{
		KA = 0;
		KB = 1;
		KC = 2;
		KCHZ = 3;
		K1 = 0;
		K2 = 0;
		K3 = 0;
		K4 = 0;
		K5 = 0;
		K6 = 0;
		K7 = 0;
		K8 = 0;
		OutMode = 0;
		TurnTime = 0.1;
		HoldTime = 0.2;

		bKA = false;
		bKB = false;
		bKC = false;

	}

	SwitchPara &operator = (const SwitchPara &right)
	{
		KA = right.KA;
		KB = right.KB;
		KC = right.KC;
		KCHZ = right.KCHZ;
		K1 = right.K1;
		K2 = right.K2;
		K3 = right.K3;
		K4 = right.K4;
		K5 = right.K5;
		K6 = right.K6;
		K7 = right.K7;
		K8 = right.K8;
		OutMode = right.OutMode;
		TurnTime = right.TurnTime;
		HoldTime = right.HoldTime;

		bKA = right.bKA;
		bKB = false; //right.bKB;
		bKC = false;//right.bKC;

		return *this;
	}
};

*/
struct Chanel3U3I
{
	float fIa;
	float fIb;
	float fIc;
	float fVa;
	float fVb;
	float fVc;

	float fAngle_Ia;
	float fAngle_Ib;
	float fAngle_Ic;
	float fAngle_Va;
	float fAngle_Vb;
	float fAngle_Vc;

	Chanel3U3I()
	{
		fIa = 0;
		fIb = 0;
		fIc = 0;
		fVa = 0;
		fVb = 0;
		fVc = 0;

		fAngle_Ia = 0;
		fAngle_Ib = 0;
		fAngle_Ic = 0;
		fAngle_Va = 0;
		fAngle_Vb = 0;
		fAngle_Vc = 0;

	}

	Chanel3U3I &operator = (const Chanel3U3I &right)
	{
		fIa = right.fIa;
		fIb = right.fIb;
		fIc = right.fIc;
		fVa = right.fVa;
		fVb= right.fVb;
		fVc = right.fVc;

		fAngle_Ia = right.fAngle_Ia;
		fAngle_Ib = right.fAngle_Ib;
		fAngle_Ic = right.fAngle_Ic;
		fAngle_Va = right.fAngle_Va;
		fAngle_Vb = right.fAngle_Vb;
		fAngle_Vc = right.fAngle_Vc;

		return *this;
	}
};

struct TimeResult
{
	float fta ;  //跳A
	float ftb ;  //跳B
	float ftc ;  //跳C
	float fchz ; //重合闸
	float fhjs ; //后加速
	float frta ; //A相保持时间
	float frtb ; //B相保持时间
	float frtc ; //C相保持时间
	float frtd ; //重合闸保持时间

	TimeResult()
	{
		fta = 0;
		ftb = 0;
		ftc = 0;
		fchz = 0;
		fhjs = 0;
		frta=0;
		frtb=0;
		frtc=0;
		frtd=0;
	}

	TimeResult &operator = (const TimeResult &right)
	{
		fta = right.fta;
		ftb = right.ftb;
		ftc = right.ftc;
		fchz = right.fchz;
		fhjs = right.fhjs;
		frta=right.frta;
		frtb=right.frtb;
		frtc=right.frtc;
		frtd=right.frtd;

		return *this;
	}

};

struct TestDataCondition_Ex
{
	bool bFirst;
	float fFv;  //第一个值
	bool bSecond;
	float fSv;  //第二个值
	int index;  //与 或

	TestDataCondition_Ex()
	{
		bFirst = false;
		fFv = 1.0;
		bSecond = true;
		fSv = 0.001;
		index = 0;
	}

	TestDataCondition_Ex &operator = (const TestDataCondition_Ex &right)
	{
		bFirst = right.bFirst;
		fFv = right.fFv;
		bSecond = right.bSecond;
		fSv = right.fSv;
		index = right.index;
		return *this;
	}
};

struct TestData  
{
	QString strName;
	ErrorType type;
	bool bResult;
	float fDL_ZK;  //短路阻抗
	float fZK_Angle;   //阻抗角
	float fR;
	float fX;
	float fHz;
	float fDL_I;
	float fDL_V;
	int iErrorDirc;  //0 反向 1正向
	int iErrorNature; //0:瞬时 1：永久
	float fErrorTime;
	float fMaxErrorTime;  //最大故障时间
	float fFH_I;
	float fFH_Angle;
	Chanel3U3I basic3U3I;

	//GPS时间
	int iHour;
	int iMin;
	int iSec;

	bool bIsCheckTransFault; //是否选择转换性故障
	ErrorType type2;
	float fTranslateTime; //转换时间
	float fDL_ZK2;  //转换性故障短路阻抗
	float fZK_Angle2;   //转换性故障阻抗角
	float fDL_I2;
	float fDL_V2;
	int iErrorDirc2;  //转换性故障方向，0 反向 1正向

// 	TestDataCondition_Ex sConditionA;
// 	TestDataCondition_Ex sConditionB;
// 	TestDataCondition_Ex sConditionC;
// 	TestDataCondition_Ex sConditionCHZ;  //重合闸
// 	TestDataCondition_Ex sConditionHJS;  //后加速
// 	//hqyGoose_Pub_Setting::Goose_Publish *pGoosePublish;

	//result
	//TimeResult tResult;

	TestData()
	{
		type = Error_A_JD;
		bResult = false;
		fDL_ZK = 0;
		fZK_Angle = 0;   //阻抗角
		fR = 0;
		fX = 0;
		fHz = 50;
		fDL_I = 0;
		fDL_V = 0;
		iErrorDirc = 1;
		iErrorNature = 0;
		fErrorTime =0.5;
		fMaxErrorTime=0;
		fFH_I=0.0;
		fFH_Angle=20;

		bIsCheckTransFault=false;
		type2=Error_A_JD;
		fTranslateTime=0; //转换时间
		fDL_ZK2=0;  //转换性故障短路阻抗
		fZK_Angle2=0;   //转换性故障阻抗角
		fDL_I2=0;
		fDL_V2=0;
		iErrorDirc2=1;  //转换性故障方向，0 反向 1正向
		//pGoosePublish = NULL;
		iHour = 0;
		iMin = 0;
		iSec = 0;

	}

	TestData &operator = (const TestData &right)
	{
		strName=right.strName;
		type = right.type;
		bResult = right.bResult;
		fDL_ZK = right.fDL_ZK;
		fZK_Angle = right.fZK_Angle;   //阻抗角
		fR = right.fR;
		fX = right.fX;
		fHz = right.fHz;
		fDL_I = right.fDL_I;
		fDL_V = right.fDL_V;
		iErrorDirc = right.iErrorDirc;
		iErrorNature = right.iErrorNature;
		fErrorTime = right.fErrorTime;
		fMaxErrorTime=right.fMaxErrorTime;
		fFH_I=right.fFH_I;
		fFH_Angle=right.fFH_Angle;

		bIsCheckTransFault=right.bIsCheckTransFault;
		type2=right.type2;
		fTranslateTime=right.fTranslateTime; //转换时间
		fDL_ZK2=right.fDL_ZK2;  //转换性故障短路阻抗
		fZK_Angle2=right.fZK_Angle2;   //转换性故障阻抗角
		fDL_I2=right.fDL_I2;
		fDL_V2=right.fDL_V2;
		iErrorDirc2=right.iErrorDirc2;  //转换性故障方向，0 反向 1正向

// 		sConditionA = right.sConditionA;
// 		sConditionB = right.sConditionB;
// 		sConditionC = right.sConditionC;
// 		sConditionCHZ = right.sConditionCHZ; 
// 		sConditionHJS = right.sConditionHJS;
		//pGoosePublish = right.pGoosePublish;
		iHour = right.iHour;
		iMin = right.iMin;
		iSec = right.iSec;

		return *this;
	}
};

struct SysPara
{
	int TestType; //测试仪类型
	int CHVNum;
	int CHINum;
	bool b4U3IChecked;
	float fAcVMax;
	float fAcIMax;
	float fDcVMax;
	float fDcIMax;
	float fAuxDc; // 辅助直流
	float fVNormal;//额定电压
	float fINormal;//额定电流
	float fFreNormal;//额定频率
	bool bIsHasDigitalOut;//是否具有数字输出功能
	int nDigVoltModuleNum;
	int nDigCurrMoudleNum;
	QList<int> ChNumOfDigVoltMoudleList;
	QList<int> ChNumOfDigCurrMoudleList;
	bool bIsHasVoltAnalogOut;//是否具有模拟输出功能
	int nAnaVoltModuleNum;
	int nAnaCurrMoudleNum;
	QList<int> ChNumOfAnaVoltMoudleList;
	QList<int> ChNumOfAnaCurrMoudleList;
	bool bAnaCurrChNum3ITo6I;
	int nOutputUgroup;
	int nOutputIgroup;
	int nUzOutput;


	SysPara()
	{
		TestType = 0;
		CHVNum = 6;
		CHINum = 6;
		b4U3IChecked = false;
		fAcVMax = 120;
		fAcIMax = 20;
		fDcVMax = 120;
		fDcIMax = 10;
		fAuxDc = 300;
		fVNormal = 57.735;
		fINormal = 1.0;
		fFreNormal = 50.0;
		bIsHasDigitalOut = true;
		nDigCurrMoudleNum = 1;
		nDigVoltModuleNum = 1;
		ChNumOfDigVoltMoudleList<<18;
		ChNumOfDigCurrMoudleList<<18;
		bIsHasVoltAnalogOut = true;
		nAnaVoltModuleNum = 1;
		nAnaCurrMoudleNum = 1;
		ChNumOfAnaVoltMoudleList<<6;
		ChNumOfAnaCurrMoudleList<<6;
		bAnaCurrChNum3ITo6I = false;
		nOutputUgroup = 0;
		nOutputIgroup = 0;
		nUzOutput = 0;
	}

	SysPara &operator = (const SysPara &right)
	{
		TestType = right.TestType;
		CHVNum = right.CHVNum;
		CHINum = right.CHINum;
		b4U3IChecked = right.b4U3IChecked;
		fAcVMax = right.fAcVMax;
		fAcIMax = right.fAcIMax;
		fDcVMax = right.fDcVMax;
		fDcIMax = right.fDcIMax;
		fAuxDc = right.fAuxDc;
		fVNormal = right.fVNormal;
		fINormal = right.fINormal;
		fFreNormal = right.fFreNormal;
		bIsHasDigitalOut = right.bIsHasDigitalOut;
		nDigVoltModuleNum = right.nDigVoltModuleNum;
		nDigCurrMoudleNum = right.nDigCurrMoudleNum;
		ChNumOfDigVoltMoudleList = right.ChNumOfDigVoltMoudleList;
		ChNumOfDigCurrMoudleList = right.ChNumOfDigCurrMoudleList;
		bIsHasVoltAnalogOut = right.bIsHasVoltAnalogOut;
		nAnaVoltModuleNum = right.nAnaVoltModuleNum;
		nAnaCurrMoudleNum = right.nAnaCurrMoudleNum;
		ChNumOfAnaVoltMoudleList = right.ChNumOfAnaVoltMoudleList;
		ChNumOfAnaCurrMoudleList = right.ChNumOfAnaCurrMoudleList;
		bAnaCurrChNum3ITo6I = right.bAnaCurrChNum3ITo6I;
		nOutputUgroup = right.nOutputUgroup;
		nOutputIgroup = right.nOutputIgroup;
		nUzOutput = right.nUzOutput;
		return *this;
	}

	bool operator==(const SysPara right) const
	{
		return (TestType==right.TestType && CHVNum==right.CHVNum && CHINum==right.CHINum && fAcVMax==right.fAcVMax\
			&& fAcIMax==right.fAcIMax && fDcVMax==right.fDcVMax && fDcIMax==right.fDcIMax && fAuxDc==right.fAuxDc\
			&& fVNormal==right.fVNormal && fINormal==right.fINormal \
			&& bIsHasDigitalOut==right.bIsHasDigitalOut && nDigVoltModuleNum == right.nDigVoltModuleNum && nDigCurrMoudleNum == right.nDigCurrMoudleNum\
			&& ChNumOfDigVoltMoudleList == right.ChNumOfDigVoltMoudleList && ChNumOfDigCurrMoudleList == right.ChNumOfDigCurrMoudleList\
			&& bIsHasVoltAnalogOut==right.bIsHasVoltAnalogOut && nAnaVoltModuleNum == right.nAnaVoltModuleNum && nAnaCurrMoudleNum == nAnaCurrMoudleNum \
			&& ChNumOfAnaVoltMoudleList == right.ChNumOfAnaVoltMoudleList && ChNumOfAnaCurrMoudleList == right.ChNumOfAnaCurrMoudleList \
			&& bAnaCurrChNum3ITo6I == right.bAnaCurrChNum3ITo6I \
			&& nOutputUgroup == right.nOutputUgroup && nOutputIgroup == right.nOutputIgroup && nUzOutput == right.nUzOutput);
	};
};


//通用参数
struct CommonPara
{
	float EDV;  //额定线电压
	float EDI;  //额定电流
	int  EDHZ;  //额定频率
	float PreFaultTime;//故障前时间
	float PostFaultTime; 
	int FaultTrigMode;//
	int PTCON;
	int CTPOINT ;//

	int ControlMode; //实验过程
	int RecloseMode; //重合方式
	float TripTimeset; //开关跳开后持续时间
	float RecloseTimeSet; //重合持续时间
	float AccTripTimeSet; //后加速开关跳开后持续时间
	int KOMode; //零序补偿系数计算方式
	float KOA; //零序补偿系数(|KO|@@KR@@|Z0/Z1)
	float KOB; //零序补偿系数(Phi(KO)@@KX@@Phi(Z0/Z1))
	int TestMode; //计算方式
	float Zs; //系统阻抗
	float Phis;//系统阻抗角

	int BCSIMULATION;//断路器模拟
	float TripTime;//分闸时间
	float CloseTime;//合闸时间

	int FaultIncMode;//合闸角选择
	float FaultAngle; //合闸角
	int DCSIM; //叠加非周期分量

	int RXS;//阻抗表示方式
	int VzDefine ;//Uz输出定义
	int VzPhDefine ;//Uz参考项定义
	float VzPhdiff;//Uz相角（相对参考项）
	int SwitchChanel; //开关量出发时，对应的开关量
	
	CommonPara()
	{
		EDV = 100;
		EDI = 5;
		EDHZ =50;
		PreFaultTime = 2;//故障前时间
		PostFaultTime = 2; 
		FaultTrigMode = 0;//
		PTCON = 0;
		CTPOINT = 1 ;//
		ControlMode=0; //实验过程
		RecloseMode=0; //重合方式
		TripTimeset=1.1; //开关跳开后持续时间
		RecloseTimeSet=0.15; //重合持续时间
		AccTripTimeSet=5.0; //后加速开关跳开后持续时间
		KOMode=1; //零序补偿系数计算方式
		KOA=0.67; //零序补偿系数(|KO|@@KR@@|Z0/Z1)
		KOB=0.67; //零序补偿系数(Phi(KO)@@KX@@Phi(Z0/Z1))
		TestMode=0; //计算方式
		Zs=1.0; //系统阻抗
		Phis=90.0;//系统阻抗角

		FaultIncMode=0;//合闸角选择
		FaultAngle=0.0; //合闸角
		DCSIM=0; //叠加非周期分量

		BCSIMULATION = 0;//
		TripTime = 200;//
		CloseTime = 100;//
		RXS = 0;//
		VzDefine = 0;//
		VzPhDefine = 0;//
		VzPhdiff = 0.0;//
		SwitchChanel=0;
	
	}

	CommonPara &operator = (const CommonPara &right)
	{
		EDV = right.EDV;
		EDI = right.EDI;
		EDHZ = right.EDHZ;
		PreFaultTime = right.PreFaultTime;//故障前时间
		PostFaultTime = right.PostFaultTime; 
		FaultTrigMode = right.FaultTrigMode;//
		PTCON = right.PTCON;
		CTPOINT = right.CTPOINT ;//
		BCSIMULATION = right.BCSIMULATION;//
		TripTime = right.TripTime;//
		CloseTime = right.CloseTime;//
		RXS = right.RXS;//
		VzDefine = right.VzDefine;//
		VzPhDefine = right.VzPhDefine;//
		VzPhdiff = right.VzPhdiff;//

		ControlMode=right.ControlMode; //实验过程
		RecloseMode=right.RecloseMode; //重合方式
		TripTimeset=right.TripTimeset; //开关跳开后持续时间
		RecloseTimeSet=right.RecloseTimeSet; //重合持续时间
		AccTripTimeSet=right.AccTripTimeSet; //后加速开关跳开后持续时间
		KOMode=right.KOMode; //零序补偿系数计算方式
		KOA=right.KOA; //零序补偿系数(|KO|@@KR@@|Z0/Z1)
		KOB=right.KOB; //零序补偿系数(Phi(KO)@@KX@@Phi(Z0/Z1))
		TestMode=right.TestMode; //计算方式
		Zs=right.Zs; //系统阻抗
		Phis=right.Phis;//系统阻抗角

		FaultIncMode=right.FaultIncMode;//合闸角选择
		FaultAngle=right.FaultAngle; //合闸角
		DCSIM=right.DCSIM; //叠加非周期分量
		SwitchChanel=right.SwitchChanel;

		return *this;
	}
};

struct cbOperateTestData
{
	QMap<int,   TestData>  m_mapData;
	cbOperateTestData()
	{
		TestData data;
		data.strName = QObject::tr("Z=2Ω,A-E,瞬时");
		data.type = Error_A_JD;
		data.fDL_ZK= 2;   //短路阻抗
		data.fZK_Angle = 90;
		data.fR =0.000;
		data.fX = 2.850;
		data.fHz = 50;
		data.fDL_I = 5;
		data.fDL_V = 50;
		data.iErrorDirc = 1;
		data.iErrorNature = 0;
		data.fMaxErrorTime = 0.5;
		data.fErrorTime=0.5;
		data.fFH_I=0.0;
		data.fFH_Angle=20;

		data.bIsCheckTransFault=false;
		data.type2=Error_A_JD;
		data.fTranslateTime=0.05; //转换时间
		data.fDL_ZK2=2;  //转换性故障短路阻抗
		data.fZK_Angle2=90;   //转换性故障阻抗角
		data.fDL_I2=5;
		data.fDL_V2=50;
		data.iErrorDirc2=1;  //转换性故障方向，0 反向 1正向

		m_mapData.insert(1,data);
	}


	cbOperateTestData &operator = (const cbOperateTestData &right)
	{
		m_mapData.clear();
		
		QMapIterator <int,TestData> i(right.m_mapData);
		while(i.hasNext())
		{
			i.next();
			TestData data;	
			data.strName = i.value().strName;
			data.type = i.value().type;
			data.bResult = i.value().bResult;
			data.fDL_ZK = i.value().fDL_ZK;
			data.fDL_ZK= i.value().fDL_ZK;   //短路阻抗
			data.fZK_Angle =i.value().fZK_Angle;
			data.fR = i.value().fR;
			data.fX = i.value().fX;
			data.fHz = i.value().fHz;
			data.fDL_I = i.value().fDL_I;
			data.fDL_V = i.value().fDL_V;
			data.iErrorDirc = i.value().iErrorDirc;
			data.iErrorNature = i.value().iErrorNature;
			data.fErrorTime = i.value().fErrorTime;
			data.fMaxErrorTime = i.value().fMaxErrorTime;
			data.basic3U3I = i.value().basic3U3I;
			//data.tResult  = i.value().tResult;

			data.fFH_I=i.value().fFH_I;
			data.fFH_Angle=i.value().fFH_Angle;

			data.bIsCheckTransFault=i.value().bIsCheckTransFault;
			data.type2=i.value().type2;
			data.fTranslateTime=i.value().fTranslateTime; //转换时间
			data.fDL_ZK2=i.value().fDL_ZK2;  //转换性故障短路阻抗
			data.fZK_Angle2=i.value().fZK_Angle2;   //转换性故障阻抗角
			data.fDL_I2=i.value().fDL_I2;
			data.fDL_V2=i.value().fDL_V2;
			data.iErrorDirc2=i.value().iErrorDirc2;  //转换性故障方向，0 反向 1正向
			m_mapData.insert(i.key(),data);
		}

		return *this;
	}
};

struct cbOperateData
{
	CommonPara ParaCommon;
	SwitchPara ParaSwitch;
	cbOperateTestData testData;
	SysPara ParaSys;


	cbOperateData &operator = (const cbOperateData &right)
	{
		ParaCommon = right.ParaCommon;
		ParaSwitch = right.ParaSwitch;
		testData =  right.testData;
		ParaSys = right.ParaSys;

		return *this;
	}
};

struct DeviceAbnormal
{
	int		nCurrentInfo;
	int		nVoltInfo;					
	DeviceAbnormal()
	{
		nCurrentInfo  = 0;
		nVoltInfo = 0;
	}

	DeviceAbnormal &operator = (const DeviceAbnormal &right)
	{
		if (this == &right)
		{
			return *this;
		}
		nCurrentInfo = right.nCurrentInfo;
		nVoltInfo = right.nVoltInfo;

		return *this;
	}
};

/*
struct GPSDATA
{

	int nSecond;
	int nNanoSec;					
	GPSDATA()
	{
		nSecond  = 0;
		nNanoSec = 0;
	}

	GPSDATA &operator = (const GPSDATA &right)
	{
		if (this == &right)
		{
			return *this;
		}
		nSecond = right.nSecond;
		nNanoSec = right.nNanoSec;

		return *this;
	}
};
Q_DECLARE_METATYPE(GPSDATA);

*/

// extern cbOperateData   g_CBOperateData;

// #define  GETDATA           g_CBOperateData.testData
// #define  GETCOMMON   g_CBOperateData.ParaCommon
// #define  GETSWITCH      g_CBOperateData.ParaSwitch
// #define   GETSYS              g_CBOperateData.ParaSys


// TestData getTestDataByTestInfo( TestInfo info )
// {
// 
// 	QMapIterator<int,TestData> i(GETDATA.m_mapData);
// 	while(i.hasNext())
// 	{
// 		i.next();
// 		if (i.key() == info.index)
// 		{
// 			return i.value();
// 		}
// 	}
// 	TestData temp;
// 	return temp;
// }


#endif

//CB_DEFINE_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
