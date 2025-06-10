#ifndef TMT_ADJUST_SYS_PARAMETER_H
#define TMT_ADJUST_SYS_PARAMETER_H

//系统硬件启动时，还没有校准系数文件，此时系统创建缺省的没有校准系数的文件
//缺省的校准系数文件，只有模块的一些从基础属性，例如模块的对应的FPGA版本号
//校准工具程序连接测试仪，获取校准的系数文件，根据模块的属性，从本地库中获取标准的
//        模块校准系数模板文件初始化各模块

#define STT_ADJUST_SYS_PARA_VERSION_1_0     0X00010000

//2020-12-27  LIJUNQING  后续如果结构体增加数据，则递增版本号
//g_dwSttAdjSysParaCurrVersion表示当前最新的版本号
//二进制文件向老版本兼容，所以必须得增加版本控制
//老版本软件兼容新版本文件的方法：
//    新增加的数据，永远都在之前版本的后面写入，这样就能够保证老版本程序读取新版本的文件不出错
extern long g_dwSttAdjSysParaCurrVersion;// = STT_ADJUST_SYS_PARA_VERSION_1_0;

//20231030 zhoulei 读写模块系数时参数结构体
#define STT_ADJUST_MODULE_PARA_VERSION_1    1
#define STT_ADJUST_MODULE_PARA_VERSION_2    2//扩展开关量从4组拆分成8组，配合硬件改动
#define STT_ADJUST_MODULE_PARA_VERSION_3    3//增加交流电压电流模块属性软件标称最大值
#define STT_ADJUST_MODULE_PARA_VERSION		STT_ADJUST_MODULE_PARA_VERSION_3
#ifdef _PSX_IDE_QT_
extern bool g_bWriteHdInfor;
#else
extern BOOL g_bWriteHdInfor;
#endif

//2020-10-21  lijunqing 
#include "../SttTestGlobaoConfig.h"
//#include "../../SttDevice/Module/PowerCtrl/SttPowerCtrlBase.h"//zhouhj 20210511 该文件类中包含了系统参数类,系统参数中需要用到最大模块数宏定义,避免出现重复包含,此处只声明类
class CSttPowerCtrlBase;

//////////////////////////////////////////////////////////////////////////
//校准系数结构体
#define ADJUST_MAX_MODULE_COUNT      12//硬件可支撑最大模块数
#define ADJUST_MAX_CHANNEL_COUNT     12//12路小信号
#define ADJUST_MAX_HARM_COUNT        31
#define ADJUST_CHANNEL_INDEX_IDC     65
#define ADJUST_CHANNEL_INDEX_UDC     64

//0=DC 1=BASE 2=HARM 2
#define ADJUST_MAX_CH_WAVE_COUNT            (ADJUST_MAX_HARM_COUNT+1)

#define ADJUST_MAX_TEMPRERATURE_COUNT   3
#define ADJUST_MAX_GEAR_COUNT           10

#define ADJUST_MAX_CH_MAPS_COUNT        12

//2021-5-2  lijunqing  因为外部需要访问，所以将模块属性定义部分放到  tmt_adjust_sys_para_module_def.h
#include "tmt_adjust_sys_para_module_def.h"

//硬件通道ID缓冲区的长度
#define STT_HD_CH_ID_BUF_LEN   8

#define DIGITAL_CHANNEL_MAX      37 //18U+18I+Uz
#define WEEK_MAIN_MODULEPOS    16//主板小信号固定位置16
#define BINARY_CHANNEL_MAX  64  //

#define STT_MODULE_CHANNEL_MAX  BINARY_CHANNEL_MAX

typedef struct stt_Module_Ch_Def
{//用short 、 char，节省空间
	char m_pszChId[STT_HD_CH_ID_BUF_LEN];   //Ua~Uc,Ia~Ic,......
	long m_nChIndex;  //通道编号(参数数组的编号），0~5表示模块的通道，64表示独立的直流通道。6~63的数字保留
	long m_nWorkMode;  //// 采集、输出：WorkMode：
	long m_nEeType;  //电压、电流？：EeType
	long m_nChEeIndex;//
	long m_nChRsIndex;  // 对应的软件资源编号
	float m_fChACMaxValue;      //     最大值：ChACMaxValue
	float m_fChDCMaxValue;      //    最大值：ChDCMaxValue
	long m_nChMeasPos;//20220211zhoulei 通道采集的映射位置

	//适配ADMU的FT3
	char m_pszChIdEx[STT_HD_CH_ID_BUF_LEN];
	long m_nEeTypeEx;
	long m_nChEeIndexEx;
	long m_nChRsIndexEx;

	void init(long nModuleIndex, long nChIndex, char chSubType)
	{//m_nEeType首先被初始化的：下载配置文件的时候或者是创建模块的时候
		//参见文件开头注释
		//chSubType：模拟量插件=0   数字量插件'd'   小信号'w'   开入为'i'   开出为'o'
		m_nChIndex = nChIndex;

		if (chSubType <= 0)
		{
            sprintf(m_pszChId, "%c%d_%d",m_nEeType , nModuleIndex+1, m_nChEeIndex+1);
		}
		else
		{
            sprintf(m_pszChId, "%c%c%d_%d",m_nEeType , chSubType,  nModuleIndex+1, m_nChEeIndex+1);
		}
	}
}STT_MODULE_CH_DEF, *PSTT_MODULE_CH_DEF;

typedef struct stt_Module_Ch_Defs
{
	STT_MODULE_CH_DEF m_oChDef[STT_MODULE_CHANNEL_MAX];  //硬件资源的最大通道数

	void init(long nModuleIndex, long nChCount)
	{//pszChType:U1、I1、Uw1等
		long nIndex=0;
		for (nIndex=0; nIndex< nChCount; nIndex++)
	{
			if (nIndex >=STT_MODULE_CHANNEL_MAX)
			{
				break;
			}

			m_oChDef[nIndex].init(nModuleIndex, nIndex, 0); //chSubType = 0,  表示电压或者电流
		}
	}

	void init_weak(long nModuleIndex, long nChCount)
	{
		long nIndex=0;
		for (nIndex=0; nIndex< nChCount; nIndex++)
		{
			if (nIndex >=STT_MODULE_CHANNEL_MAX)
			{
				break;
			}

			//20220209 zhoulei 系数文件未定义的小信号关联软件资源默认为电压类型
			long nEeType;
			nEeType = m_oChDef[nIndex].m_nEeType;
			m_oChDef[nIndex].m_nEeType = STT_CH_EETYPE_VOLTAGE;//保持'Uw'
			m_oChDef[nIndex].m_nChEeIndex = nIndex;
			m_oChDef[nIndex].init(nModuleIndex, nIndex, 'w');//chSubType = 'w',  表示小信号
			m_oChDef[nIndex].m_nEeType = nEeType;
		}
	}

	void init_digital(long nModuleIndex)
	{
// 20220309 zhoulei
//		int nCnt=DIGITAL_CHANNEL_MAX/2;
//		for (long nIndex=0; nIndex< nCnt; nIndex++)
//		{
//			sprintf(m_oChDef[nIndex].m_pszChId, "%c%c%d_%d",STT_CH_EETYPE_VOLTAGE , 'd',  nModuleIndex+1, nIndex+1);
//		}
//		//Uz-Ud1_19
//		sprintf(m_oChDef[nCnt].m_pszChId, "%c%c%d_%d",STT_CH_EETYPE_VOLTAGE , 'd',  nModuleIndex+1, nCnt+1);

//		for (long nIndex=0; nIndex< nCnt; nIndex++)
//		{
//			sprintf(m_oChDef[nIndex+nCnt+1].m_pszChId, "%c%c%d_%d",STT_CH_EETYPE_CURRENT , 'd',  nModuleIndex+1, nIndex+1);
//		}

        for (long nIndex=0; nIndex< DIGITAL_CHANNEL_MAX; nIndex++)
		{
            sprintf(m_oChDef[nIndex].m_pszChId, "%c%c%d_%d",m_oChDef[nIndex].m_nEeType ,
                    'd',  nModuleIndex+1, m_oChDef[nIndex].m_nChEeIndex+1);
		}
	}

	void init_binary_sub(long nModuleIndex, long nOffset, long &nBinnaryIndex, char chSubType)
	{
		long nIndex = 0;
		for (nIndex=0; nIndex<16; nIndex++)
		{
			m_oChDef[nIndex+nOffset].init(nModuleIndex, nBinnaryIndex, chSubType);
			nBinnaryIndex++;
		}
	}

	void init_binary(long nModuleIndex, long nCount, long *pSwitchIn)
	{
		long nGrouCount = nCount / 16;
		long nGroupIndex = 0;
		long nBinnaryIndex = 0;

		//处理开入  1 表示 开出
		for (nGroupIndex=0; nGroupIndex<nGrouCount; nGroupIndex++)
		{
			if (pSwitchIn[nGroupIndex] == 1)
			{
				init_binary_sub(nModuleIndex, nGroupIndex * 16, nBinnaryIndex, 'i');
			}
		}

		//处理开入  1 表示 开出
		for (nGroupIndex=0; nGroupIndex<nGrouCount; nGroupIndex++)
		{
			if (pSwitchIn[nGroupIndex] == 0)
			{
				init_binary_sub(nModuleIndex, nGroupIndex * 16, nBinnaryIndex, 'o');
			}
		}

	}
}STT_MODULE_CH_DEFS, *PSTT_MODULE_CH_DEFS;

typedef struct stt_Adjust_Item
{
public:
	float m_fCoef;//幅值系数
	float m_fZero;//零漂
	float m_fAngle;//相位补偿

	void init()
	{
		m_fCoef = 1;
		m_fZero = 0;
		m_fAngle = 0;
	}

	stt_Adjust_Item(){}
	virtual ~stt_Adjust_Item(){}
}STT_ADJUST_ITEM, *PSTT_ADJUST_ITEM;

typedef struct stt_Channel_Gear_Adjust
{
public:
	float m_fGearValue;  //档位值
	STT_ADJUST_ITEM m_oAdjItem;

	void init()
	{
		m_fGearValue = 0;
		m_oAdjItem.init();
	}

	stt_Channel_Gear_Adjust(){}
	virtual ~stt_Channel_Gear_Adjust(){}
}STT_CHANNEL_GEAR_ADJUST, *PSTT_CHANNEL_GEAR_ADJUST;

typedef struct stt_Channel_Wave_Adjust
{
public:
	long m_nGearCount;  //档位数
	STT_CHANNEL_GEAR_ADJUST m_oChGearAdj[ADJUST_MAX_GEAR_COUNT];

	void init()
	{
		m_nGearCount = 1;

		long nIndex = 0;

		for (nIndex=0; nIndex<ADJUST_MAX_GEAR_COUNT; nIndex++)
		{
			m_oChGearAdj[nIndex].init();
		}
	}

	stt_Channel_Wave_Adjust(){}
	virtual ~stt_Channel_Wave_Adjust(){}
}STT_CHANNEL_WAVE_ADJUST, *PSTT_CHANNEL_WAVE_ADJUST;

typedef struct stt_Channel_Adjusts
{
public:
	//2021-5-2  下面两个校准系数，是否放到  STT_TRANGE_ADJUST？
	//????????????????????????????????????????????????
	float m_fDcZero[3];  //交流端子的直流分量，0V、0Hz时测量
	float m_fLargeCurrentRatio; //大电流非线性系数


	long nHarmCount;//由模块属性m_nHarmCount复制
	//实际的谐波次数在模块属性中定义
	PSTT_CHANNEL_WAVE_ADJUST m_pChWaveAdj;

	//2021-4-30  lijunqing
	//讨论结果：为方便将来的版本扩充，为每个通道都增加独立的属性如下
	//           采集、输出：WorkMode：
	//           电压、电流？：EeType
	//           最大值：ChACMaxValue
	//           最大值：ChDCMaxValue
	//long m_nWorkMode;  //
	//long m_nEeType;
	//float m_fChACMaxValue;
	//float m_fChDCMaxValue;
	PSTT_MODULE_CH_DEF m_pHdChDef; //关联的硬件通道定义对象

	void init()
	{
        m_fDcZero[0]=m_fDcZero[1]=m_fDcZero[2]=0;
		m_fLargeCurrentRatio=1;//等于1时代表线性
		m_pHdChDef = NULL;
		m_pChWaveAdj = NULL;
		nHarmCount = 0;
	}

	stt_Channel_Adjusts(){}
	virtual ~stt_Channel_Adjusts(){}
}STT_CHANNEL_ADJUSTS, *PSTT_CHANNEL_ADJUSTS;

typedef struct stt_TRange_Adjust
{
public:
	float m_fTemperature;  //温度
	long  nChannelNum;//从模块熟悉m_nChannelNum复制;
	STT_CHANNEL_WAVE_ADJUST m_oChIdcAdj;  //独立Idc校准系数
	STT_CHANNEL_WAVE_ADJUST m_oChUdcAdj;  //独立Udc校准系数

	PSTT_CHANNEL_ADJUSTS m_pChsAdjust;
	//	STT_CHANNEL_ADJUSTS m_oChsAdjust[ADJUST_MAX_CHANNEL_COUNT];

	//2021-5-2  lijunqing  以下的部分，是否有必要单独作为一个对象
	//????????????????????????????????????????????????
	STT_CHANNEL_ADJUSTS m_oChsAdjust_PTU_Is;//6合1,大电流端子Is通道校准

	void init()
	{
		m_fTemperature = 0;
		nChannelNum = 0;
		m_oChIdcAdj.init();
		m_oChUdcAdj.init();

		long nIndex=0;
		m_pChsAdjust=NULL;
		//		for (nIndex=0; nIndex<ADJUST_MAX_CHANNEL_COUNT; nIndex++)
		//		{
		//			m_oChsAdjust[nIndex].init();
		//		}
	}

	stt_TRange_Adjust(){}
	virtual ~stt_TRange_Adjust(){}
}STT_TRANGE_ADJUST, *PSTT_TRANGE_ADJUST;

//硬件档位定义
typedef struct stt_Hd_Gear
{
public:
	long m_nGearID;  //档位ID，用于驱动通用化，即切档位时的参数
	float m_fGearValue;   //档位数值

	void init()
	{
		m_nGearID = 0;
		m_fGearValue = 0;
	}

	stt_Hd_Gear(){}
	virtual ~stt_Hd_Gear(){}
}STT_HD_GEAR, *PSTT_HD_GEAR;

typedef struct stt_Hd_Gears
{
public:
	long m_nHdGearCount;
	STT_HD_GEAR m_oHdGear[ADJUST_MAX_GEAR_COUNT];

	void init()
	{
		m_nHdGearCount = 0;
		memset(m_oHdGear, 0, sizeof(STT_HD_GEAR) * ADJUST_MAX_GEAR_COUNT);
	}

	stt_Hd_Gears(){}
	virtual ~stt_Hd_Gears(){}
}STT_HD_GEARS, *PSTT_HD_GEARS;

typedef struct stt_Hd_Gears_Ex
{
public:
	STT_HD_GEARS m_oChanHdGears[12];//小信号最多12路

	void init()
	{
		for(int i=0;i<12;i++)
		{
			m_oChanHdGears[i].init();
		}
	}

	stt_Hd_Gears_Ex(){}
	virtual ~stt_Hd_Gears_Ex(){}
}STT_HD_GEARS_EX, *PSTT_HD_GEARS_EX;

typedef struct stt_Module_Adjust
{
public:
	long m_nTemperatureCount;    //温区数

	//温区校准系数
	STT_TRANGE_ADJUST m_oTempAdjust[ADJUST_MAX_TEMPRERATURE_COUNT];

	void init()
	{
		m_nTemperatureCount = 0;
		long nIndex = 0;

		for (nIndex=0; nIndex<ADJUST_MAX_TEMPRERATURE_COUNT; nIndex++)
		{
			m_oTempAdjust[nIndex].init();
		}
	}

	stt_Module_Adjust(){}
	virtual ~stt_Module_Adjust(){}
}STT_MODULE_ADJUST, *PSTT_MODULE_ADJUST;

//typedef struct stt_Module_Ch_Group
//{
//	//不定义为 char m_pszCh1ID[3][8]的方式，就是为了查看方便
//	char m_pszCh1ID[8];
//	char m_pszCh2ID[8];
//	char m_pszCh3ID[8];
//}STT_MODULE_CH_GROUP, *PSTT_MODULE_CH_GROUP;

//typedef struct stt_Module_Ch_Groups
//{
//	long m_nChGroupCount;
//	STT_MODULE_CH_GROUP m_oChGroups[2];//暂定为最多2个分组，六个通道
//}STT_MODULE_CH_GROUPS, *PSTT_MODULE_CH_GROUPS;

typedef struct stt_Ch_Drv_Pos
{
	long m_nChDrvPos[STT_MODULE_CHANNEL_MAX];

	void init()
	{
        for (long k=0; k<STT_MODULE_CHANNEL_MAX; k++)
		{
			m_nChDrvPos[k] = k;
		}
	}
}STT_CH_DRV_POS, *PSTT_CH_DRV_POS;

typedef struct stt_Module_Ch_Map_Def
{
public:
	//通道数，在模块定义，此处不重复定义
	//long m_nChannelCount；
	//	STT_MODULE_CH_MAPS m_oChMaps;
	//	STT_MODULE_CH_GROUPS m_oChGroups;

	//2021-4-29  lijunqing
	//硬件通道定义：即硬件通道的ID，用于通道映射
	//系统初始化的时候初始化，不改变
	STT_MODULE_CH_DEFS m_oChDefs;
	STT_CH_DRV_POS m_oChDrvPos;

	void init()
	{
		memset(&m_oChDefs, 0, sizeof(STT_MODULE_CH_DEFS));
		//		memset(&m_oChGroups, 0, sizeof(STT_MODULE_CH_GROUPS));
		m_oChDrvPos.init();
	}
}STT_MODULE_CH_MAP_DEF, *PSTT_MODULE_CH_MAP_DEF;

//单独定义一个结构体，从代码阅读上面以及xml串行化上方便些
typedef struct stt_Module_Attr
{
	//////////////////////////////////////////////////////////////////////////
	//已经确定的属性  lijunqing
	char m_strModelName[32];//模块型号
	char m_strModuleSN[32];//模块序列号
	long m_nChannelNum;//通道数
	long m_nHarmCount;     //谐波数
	float m_fUdcMax;  //辅助直流电压通道最大值
	float m_fUdcMin;  //辅助直流电压通道最小值
//    float m_fDCCurrMax;  //直流电流通道最大值
	float m_fChMax;  //模块通道出交流最大值
	float m_fChDcMax;  //模块通道出直流最大值
	float m_fDefChMax;  //软件标称交流最大值，只有交流电压电流模块适用
	float m_fDefChDcMax;  //软件标称直流最大值，只有交流电压电流模块适用

	//模块类型 见宏定义
	long m_nModuleType;     //m_nvoltorcur;
	long m_nModuleIndex; //模块位置 1~11
	long m_nModuleAddr;//RTDS使用时PI的模块网内标记

	//模块硬件特性 功率控制模式
	long m_nModulePower; //见 SttPowerCtrlCom.h 宏定义
	CSttPowerCtrlBase *m_pPowerCtrlBase;
	//模块通道映射定义
	STT_MODULE_CH_MAP_DEF m_oChDefMap;
	long m_nErr;//用来标记系数文件内的异常模块，禁止端口输出
	long m_nUsed;//用来标记系数文件内的可用模块

	//硬件档位
//    STT_HD_GEARS m_oHdGears;
//    STT_HD_GEARS_EX m_oHdGearsEx;//小信号插件
//    STT_HD_GEARS m_oHdGears_Idc; //独立直流电流通道硬件档位
//    STT_HD_GEARS m_oHdGears_Udc; //独立直流电压通道硬件档位

	//////////////////////////////////////////////////////////////////////////
	//下面的属性不确定，需周磊确定**********************
	float m_fFreCoef;//频率补偿系数,电压时有效
	float m_fgain; //增益
	char m_strFPGAVer[32]; //FPGA版本号
//	UINT  m_nFiberPortNum;//数字模块光口数 【数字模块目前固定为每个模块8光口】【后续可参考电压、电流配置每个模块的光口数】
	long m_nFiberPortNum_LC;//LC光口数
	long m_nFiberPortNum_STSend;//STSend光口数
	long m_nFiberPortNum_STRecv;//STRecv光口数

	float m_fDigitalDelay;//数字模块相位延时

	long  m_nSwitchIn[8];//最大4组16IO元件，共64IO
	//2021-6-2  lijunqing 将各种合并模式统一定义
	long  m_nChMergeMode;//通道合并模式：0=不支持；1=6合1； 2=6合3；
	//2023-10-30 zhoulei 用于小信号插件
	long  m_nChTypeChg;//通道电气类型可变；1:可变,0:不可变
	//其他参数
	char m_strDateProduce[24]; //2020-10-10，多留几位，避免字符串多了
	char m_strFactory[64]; //2020-10-10，多留几位，避免字符串多了

	//2021-4-30  lijunqing
	//讨论结果：为方便将来的版本扩充，为每个通道都增加独立的属性如下
	//           采集、输出：WorkMode：
	//           电压、电流？：EeType
	//           最大值：ChACMaxValue
	//           最大值：ChDCMaxValue
	//为了兼容新老版本，为模块增加版本号，表示校准系数模式的版本
	long m_dwVersion;

//    bool has_idc()
//    {
//        return (m_fDCCurrMax > 0);
//    }
//    bool has_udc()
//    {
//        return (m_fDCVoltMax > 0);
//    }

	void init()
	{
		m_dwVersion = -1;  //-1，初始化，表示没有读到校准系数文件
		strcpy(m_strModelName, "Stt2020");
		strcpy(m_strModuleSN, "PONV-2020-1001-000");
		strcpy(m_strFactory, "北京博电新力电气股份有限公司");
		strcpy(m_strDateProduce, "2020-01-01");
		strcpy(m_strFPGAVer, "-");
		m_nModuleAddr = 0;
		m_fUdcMax = -1.0f;
		m_fUdcMin = -1.0f;
//        m_fDCCurrMax = 0;
		m_fChMax = 0;
		m_fChDcMax=0;
		m_fDefChMax = 0;
		m_fDefChDcMax = 0;
		m_fFreCoef=1.0;
		m_pPowerCtrlBase=NULL;
		m_nModulePower=0;
		m_nChMergeMode=STT_CURRENT_ChMergeMode_No;
		m_nChannelNum=ADJUST_MAX_CHANNEL_COUNT;
		m_nHarmCount=ADJUST_MAX_CH_WAVE_COUNT;
		m_nFiberPortNum_LC = 0;//LC光口数
		m_nFiberPortNum_STSend = 0;//STSend光口数
		m_nFiberPortNum_STRecv = 0;//STRecv光口数
		m_nSwitchIn[0] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[1] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[2] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[3] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[4] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[5] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[6] = -1; //默认是无效,0-开出,1-开入
		m_nSwitchIn[7] = -1; //默认是无效,0-开出,1-开入
		m_fDigitalDelay = 0;
		m_nChTypeChg = 1;//默认小信号插件通道电气可选电压或电流
		m_oChDefMap.init();
	}

	void init_hd_ch_def(long nModuleIndex, char chType)
	{
		if (chType == STT_MODULETYPE_ID_ANALOG_CHAR) //模拟量插件
		{
			m_oChDefMap.m_oChDefs.init(nModuleIndex, m_nChannelNum);
			return;
		}

		if (chType == STT_MODULETYPE_ID_DIGITAL_CHAR) //数字量插件
		{
			m_oChDefMap.m_oChDefs.init_digital(nModuleIndex);
			return;
		}

		if (chType == STT_MODULETYPE_ID_WEEK_CHAR) //小信号插件
		{
			m_oChDefMap.m_oChDefs.init_weak(nModuleIndex, m_nChannelNum);
			return;
		}

		if (chType == STT_MODULETYPE_ID_BINARY_CHAR) //开关量插件
		{
			m_oChDefMap.m_oChDefs.init_binary(nModuleIndex, m_nChannelNum, m_nSwitchIn);
			return;
		}
	}
}ST_MODULE_ATTR, *PST_MODULE_ATTR;

typedef struct stt_Module
{
	ST_MODULE_ATTR m_oModuleAttr;  //模块属性
	STT_MODULE_ADJUST m_oModuleAdjust;  //模块校准系数

	void init()
	{
		memset(&m_oModuleAttr, 0, sizeof(ST_MODULE_ATTR));
		m_oModuleAttr.init();
		m_oModuleAdjust.init();
	}

	//2020-10-05 zhoulei
	long m_nChMeasPos[STT_MODULE_CHANNEL_MAX];
	long m_nChDrvPos[STT_MODULE_CHANNEL_MAX];//方便使用，初始化提取自m_oModuleAttr.m_oChDefMap
	long m_nChTmtPos[STT_MODULE_CHANNEL_MAX];//映射到软件资源
	long m_nChTmtPosEx[STT_MODULE_CHANNEL_MAX];//映射到软件资源ADMU

	//2021-6-2  lijunqing
	float m_fChTmtCoef[STT_MODULE_CHANNEL_MAX];   //映射通道的系数：例如电流多通道合并输出，每个通道的系数设置
	//	long m_nArrayBeginIndex;

	void init_ch_drv_pos()
	{
		memcpy(m_nChDrvPos, m_oModuleAttr.m_oChDefMap.m_oChDrvPos.m_nChDrvPos, sizeof(long)*STT_MODULE_CHANNEL_MAX);
        for(int i=0;i<STT_MODULE_CHANNEL_MAX;i++)
		{
			m_nChMeasPos[i] = m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nChMeasPos;
		}
	}

	void InitChTmtPos()
	{//根据通道的映射资源对象Index，初始化ChTmtPos
		//
		long nChannelNum = m_oModuleAttr.m_nChannelNum;
		if(m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_DIGITAL_0G8M
				||m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_DIGITAL_2G6M
				||m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_DIGITAL_4G4M
				||m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_FT3)
		{
			nChannelNum = DIGITAL_CHANNEL_MAX;//数字板在系数文件中通道值是0
		}

		PSTT_MODULE_CH_DEFS pChDefs = &m_oModuleAttr.m_oChDefMap.m_oChDefs;
		long nIndex = 0;

		for (nIndex=0; nIndex<nChannelNum;nIndex++)
		{
			m_nChTmtPos[nIndex] = pChDefs->m_oChDef[nIndex].m_nChRsIndex;
		}

		if(m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
		{
			for (nIndex=0; nIndex<DIGITAL_CHANNEL_MAX;nIndex++)
			{
				m_nChTmtPosEx[nIndex] = pChDefs->m_oChDef[nIndex].m_nChRsIndexEx;
			}
		}
	}

	void InitChTmtCoef()
	{//根据通道的映射资源对象Index，初始化ChTmtPos
		//
		long nChannelNum = m_oModuleAttr.m_nChannelNum;
		long nIndex = 0;

		for (nIndex=0; nIndex<nChannelNum;nIndex++)
		{
			m_fChTmtCoef[nIndex] = 1.0f;
		}

	}

	//2021-5-2  lijunqing  根据m_dwVersion做初始化处理
	void init_after_read()
	{

	}
}STT_MODULE, *PSTT_MODULE;

typedef struct stt_Bout_Attrs
{
	UINT m_nBout[16];//主板16个开出导通值，0-断开，1-闭合
	void init()
	{
		for(int i = 0; i < 16; i++)
		{
			m_nBout[i]=1;
		}
	}
}STT_BOUT_ATTRS, *PSTT_BOUT_ATTRS;

typedef struct stt_Bin_Adjust
{
public:
	long m_nGearCount;  //档位数
	STT_CHANNEL_GEAR_ADJUST m_oBinGearAdj[ADJUST_MAX_GEAR_COUNT];

	void init()
	{
		m_nGearCount = 1;
		long nIndex = 0;

		for (nIndex=0; nIndex < ADJUST_MAX_GEAR_COUNT; nIndex++)
		{
			m_oBinGearAdj[nIndex].init();
		}
	}

	stt_Bin_Adjust(){}
	virtual ~stt_Bin_Adjust(){}
}STT_BIN_ADJUST, *PSTT_BIN_ADJUST;

typedef struct stt_Device_Attrs
{
	float m_fBaseFre;//额定频率
	long m_nStateCount;//状态序列容量(个)，改为驱动上报
	long m_nBinCount;//主板开入数量(个)
	long m_nBinVoltMeas;//0-无开入电压采集功能，1-有开入电压采集功能
	long m_nBoutCount;//主板开出数量(个)
	long m_nBoutReplay;//开出回放(0-不支持，1-支持)
	float m_fPhaseForMUTest;//合并单元实验相位补偿
//	UINT  m_nInputbinaryMode;//开入量采集模式

//	UINT  m_nSMVTotalSize;//SMV最大组数
//	UINT  m_nGseOutTotalSize;//GOOSE最大组数
//	UINT  m_nGseInTotalSize;//goosein 最大组数

	char m_strMngrVer[32]; //TestMngr版本号
	char m_strAppVer[32]; //TestServer版本号
	char m_strAppName[32]; //TestServer名称
	char m_strFPGAVer[32]; //FPGA版本号
	char m_strDriverVer[32]; //驱动版本号
	char m_strDriverName[32]; //驱动名称

	char m_strDeviceName[32];//仪器型号：例如PN466
	char  m_strSN[32];//装置序列号，字符串型 2020-10-14  lijunqing

	//其他参数
	char m_strDateProduce[24]; //2020-10-10，多留几位，避免字符串多了
	char m_strFactory[64]; //2020-10-10，多留几位，避免字符串多了

	long m_nCheckAuthority;//启用控制权限判断
	long m_nSTModeSet;//N-主板ST口模式可设置数量 0-不可设置
	long m_nWindSpeed;//开机后风扇默认模式，//1-正常风速 0-静音风速
	void init()
	{
		m_nCheckAuthority = 0;
		m_nSTModeSet = 0;
		m_nWindSpeed = 1;
		m_fBaseFre=50;
		m_nBinCount = 10;
		m_nBinVoltMeas = 0;
		m_nBoutCount = 8;
		m_nBoutReplay = 0;
		m_fPhaseForMUTest = 0.0f;
		strcpy(m_strDeviceName, "PN");
		strcpy(m_strSN, "PONV-2020-1001-000");
		strcpy(m_strFactory, "北京博电新力电气股份有限公司");
		strcpy(m_strDateProduce, "2020-01-01");

		strcpy(m_strMngrVer, "-");
		strcpy(m_strAppVer, "-");
		strcpy(m_strFPGAVer, "-");
		strcpy(m_strDriverVer, "-");
	}
}STT_DEVICE_ATTRS, *PSTT_DEVICE_ATTRS;

typedef struct stt_Device_System_Parameter
{
	STT_DEVICE_ATTRS m_oDeviceAttrs;
	STT_BOUT_ATTRS m_oBoutTurnOnValue;//开关量导通值
	STT_BIN_ADJUST m_oBinAdj[16];//开入量采集校准

	//模块管理
	long m_nModuleCount;
	//2021-03-24 zhoulei
	//PI1000最大控制光口12个.常用11个,备用1个做1588对时
	//FPGA只有位置一具备GOOSE订阅功能

	STT_MODULE m_oModules[ADJUST_MAX_MODULE_COUNT+1];//12模块+主板小信号=13

	void init()
	{
		memset(&m_oDeviceAttrs, 0, sizeof (m_oDeviceAttrs));
		m_oDeviceAttrs.init();
		m_oBoutTurnOnValue.init();

		m_nModuleCount_U = 0;
		m_nModuleCount_I = 0;
		m_nModuleCount_D = 0;
		m_nModuleCount_FT3 = 0;
		m_nModuleCount_S = 0;
		m_nModuleCount_WEEK = 0;
		m_nModuleCount_Stable2M = 0;
		m_nModuleCount = 0;

		long nIndex=0;
		for (nIndex=0; nIndex<16; nIndex++)
		{
			m_oBinAdj[nIndex].init();
		}

		for (nIndex=0; nIndex<ADJUST_MAX_MODULE_COUNT; nIndex++)
		{
			m_oModules[nIndex].init();
			m_oModules_U[nIndex] = 0;
			m_oModules_I[nIndex] = 0;
			m_oModules_D[nIndex] = 0;
			m_oModules_FT3[nIndex] = 0;
			m_oModules_UI[nIndex] = 0;
			m_oModules_S[nIndex] = 0;
			m_oModules_WEEK[nIndex] = 0;
		}
		m_oModules_WEEK[ADJUST_MAX_MODULE_COUNT] = 0;
	}

	//2021-04-13 zhoulei
	long m_nModuleCount_U;//电压
	long m_nModuleCount_I;//电流
	long m_nModuleCount_D;//数字9-2+ft3
	long m_nModuleCount_FT3;//数字ft3
	long m_nModuleCount_S;//开关量
	long m_nModuleCount_WEEK;//小信号
	long m_nModuleCount_UI;//UI混合插件
	long m_nModuleCount_Stable2M;//稳控2M插件
	long m_nModuleCount_ADMU;//ADMU插件
	long m_nModuleCount_U_MEAS;//采集模块
	long m_nModuleCount_I_MEAS;//采集模块

	PSTT_MODULE m_oModules_U[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_I[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_D[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_FT3[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_S[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_WEEK[ADJUST_MAX_MODULE_COUNT+1];//包含主板小信号
	PSTT_MODULE m_oModules_UI[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_Stable2M[ADJUST_MAX_MODULE_COUNT];//稳控2M
	PSTT_MODULE m_oModules_ADMU[ADJUST_MAX_MODULE_COUNT];//ADMU
	PSTT_MODULE m_oModules_U_MEAS[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_I_MEAS[ADJUST_MAX_MODULE_COUNT];

	void init_module_ref(long &nCount, PSTT_MODULE *ppModuleRef, long nModuleType)
	{
		for(int nModuleIndex = 1; nModuleIndex <= 16; nModuleIndex++)
		{
			for(long k = 0; k < m_nModuleCount; k++)
			{
				if(m_oModules[k].m_oModuleAttr.m_nModuleType == nModuleType)
				{
					if(m_oModules[k].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_WEEK_EX)
					{
						if(m_oModules[k].m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
								|| m_oModules[k].m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
						{
							m_oModules[k].m_oModuleAttr.m_nModuleIndex = 16;//PN主板小信号固定在位置16
						}
					}

					if(m_oModules[k].m_oModuleAttr.m_nModuleIndex == nModuleIndex)
					{
						ppModuleRef[nCount] = &m_oModules[k];
						ppModuleRef[nCount]->InitChTmtCoef();
						nCount++;
						break;
					}
				}
			}
		}
	}

	void init_array_index(long nModuleType)
	{
		long nIndex = 0;
		for (long k=0; k<m_nModuleCount; k++)
		{
			if (m_oModules[k].m_oModuleAttr.m_nModuleType == nModuleType)
			{
				//				m_oModules[k].m_nArrayBeginIndex = nIndex;
				//				nIndex += ADJUST_MAX_CHANNEL_COUNT;
				nIndex +=m_oModules[k].m_oModuleAttr.m_nChannelNum;
				m_oModules[k].init_ch_drv_pos();
			}
		}
	}

	void set_DigitalTmtPos(PSTT_MODULE pModule)
	{
		PSTT_MODULE_CH_DEF pChDef;
		int nVoltChEeIndex = 0;
		int nCurrChEeIndex = 0;

		for(int nChanIndex = 0; nChanIndex < 18; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
			pChDef->m_nChRsIndex = nChanIndex;//U0~U17
			pChDef->m_nChEeIndex = nVoltChEeIndex;
			nVoltChEeIndex++;
		}

		for(int nChanIndex = 19; nChanIndex < 37; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDef->m_nChRsIndex = nChanIndex - 19; //I0~I17
			pChDef->m_nChEeIndex = nCurrChEeIndex;
			nCurrChEeIndex++;
		}

		pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[18];
		pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
		pChDef->m_nChRsIndex = 0;//默认Uz抽取的是U0
		pChDef->m_nChEeIndex = 18;
		pModule->InitChTmtPos();
	}

	void set_DigitalTmtPosADMU(PSTT_MODULE pModule)
	{
		PSTT_MODULE_CH_DEF pChDef;
		int nVoltChEeIndex = 0;
		int nCurrChEeIndex = 0;

		for(int nChanIndex = 0; nChanIndex < 18; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeTypeEx = STT_CH_EETYPE_VOLTAGE;
			pChDef->m_nChRsIndexEx = nChanIndex;//U0~U17
			pChDef->m_nChEeIndexEx = nVoltChEeIndex;
			nVoltChEeIndex++;
		}

		for(int nChanIndex = 19; nChanIndex < 37; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeTypeEx = STT_CH_EETYPE_CURRENT;
			pChDef->m_nChRsIndexEx = nChanIndex - 19; //I0~I17
			pChDef->m_nChEeIndexEx = nCurrChEeIndex;
			nCurrChEeIndex++;
		}

		pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[18];
		pChDef->m_nEeTypeEx = STT_CH_EETYPE_VOLTAGE;
		pChDef->m_nChRsIndexEx = 0;//默认Uz抽取的是U0
		pChDef->m_nChEeIndexEx = 18;
	}

	void init_module_ByIndexandType()
	{
		m_nModuleCount_U = 0;
		m_nModuleCount_I = 0;
		m_nModuleCount_D = 0;
		m_nModuleCount_FT3 = 0;
		m_nModuleCount_S = 0;
		m_nModuleCount_WEEK = 0;
		m_nModuleCount_UI = 0;
		m_nModuleCount_Stable2M = 0;
		m_nModuleCount_U_MEAS = 0;
		m_nModuleCount_I_MEAS = 0;

		for(long k = 0; k < m_nModuleCount; k++)
		{
			m_oModules[k].m_oModuleAttr.m_nErr = 0; //初始化时启用
			m_oModules[k].m_oModuleAttr.m_nUsed = 1;
		}

		init_module_ref(m_nModuleCount_U_MEAS, m_oModules_U_MEAS, STT_MODULE_TYPE_MEAS_VOLT);
		init_module_ref(m_nModuleCount_I_MEAS, m_oModules_I_MEAS, STT_MODULE_TYPE_MEAS_CURRENT);
		init_module_ref(m_nModuleCount_U, m_oModules_U, STT_MODULE_TYPE_VOLT);
		init_module_ref(m_nModuleCount_I, m_oModules_I, STT_MODULE_TYPE_CURRENT);
		init_module_ref(m_nModuleCount_D, m_oModules_D, STT_MODULE_TYPE_DIGITAL_0G8M);
		init_module_ref(m_nModuleCount_D, m_oModules_D, STT_MODULE_TYPE_DIGITAL_2G6M);
		init_module_ref(m_nModuleCount_D, m_oModules_D, STT_MODULE_TYPE_DIGITAL_4G4M);
		init_module_ref(m_nModuleCount_FT3, m_oModules_FT3, STT_MODULE_TYPE_FT3);
		init_module_ref(m_nModuleCount_S, m_oModules_S, STT_MODULE_TYPE_SWITCH);
		init_module_ref(m_nModuleCount_WEEK, m_oModules_WEEK, STT_MODULE_TYPE_WEEK_EX);
		init_module_ref(m_nModuleCount_UI, m_oModules_UI, STT_MODULE_TYPE_VOLT_CURRENT);
		init_module_ref(m_nModuleCount_Stable2M, m_oModules_Stable2M, STT_MODULE_TYPE_Stable2M);
		init_module_ref(m_nModuleCount_ADMU, m_oModules_ADMU, STT_MODULE_TYPE_ADMU);
	}

	void init_module_ChDefMap()
	{
		int nBeginIndex = 0;
		int nVoltIndex = 0;
		int nCurrentIndex = 0;
		int nChannelNum;
		PSTT_MODULE_CH_DEF pChDef;
		PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj;

		for(int nIndex = 0; nIndex < m_nModuleCount_U; nIndex++)
		{
			if(m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum > 6)
			{
				m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum = 6;
			}

			nChannelNum = m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum;
			m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChDcMax =
				m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChMax * 1.414;

			for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
			{
				pChDef = &m_oModules_U[nIndex]->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
				pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDef->m_nChRsIndex = nBeginIndex + nChanIndex;
				pChDef->m_nChEeIndex = nChanIndex;
				pChDef->m_fChACMaxValue = m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChMax;
				pChDef->m_fChDCMaxValue = m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChDcMax;

				pChWaveAdj = &m_oModules_U[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[0];
				long nCount = pChWaveAdj->m_nGearCount;
				if(nCount > 0)
				{
					pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChDCMaxValue;
				}

				long nHarmCnt = m_oModules_U[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].nHarmCount;
				for(int j = 1; j < nHarmCnt; j++)
				{
					pChWaveAdj = &m_oModules_U[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[j];
					nCount = pChWaveAdj->m_nGearCount;
					if(nCount > 0)
					{
						pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChACMaxValue;
					}
				}
			}

			nBeginIndex += nChannelNum;
			m_oModules_U[nIndex]->init_ch_drv_pos();
			m_oModules_U[nIndex]->InitChTmtPos();
		}

		nVoltIndex = nBeginIndex;
		nBeginIndex = 0;

		for(int nIndex = 0; nIndex < m_nModuleCount_I; nIndex++)
		{
			if(m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum > 6)
			{
				m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum = 6;
			}

			nChannelNum = m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum;

			float fDefChDcMax1 = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChMax * 0.5;
			float fDefChDcMax2 = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChMax;
			if(m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax < fDefChDcMax1
					|| m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax > fDefChDcMax2)
			{
				m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax = fDefChDcMax1;
			}

			for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
			{
				pChDef = &m_oModules_I[nIndex]->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
				pChDef->m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDef->m_nChRsIndex = nBeginIndex + nChanIndex;
				pChDef->m_nChEeIndex = nChanIndex;
				pChDef->m_fChACMaxValue = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChMax;
				pChDef->m_fChDCMaxValue = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax;

				pChWaveAdj = &m_oModules_I[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[0];
				long nCount = pChWaveAdj->m_nGearCount;
				if(nCount > 0)
				{
					pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChDCMaxValue;
				}

				long nHarmCnt = m_oModules_I[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].nHarmCount;
				for(int j = 1; j < nHarmCnt; j++)
				{
					pChWaveAdj = &m_oModules_I[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[j];
					nCount = pChWaveAdj->m_nGearCount;
					if(nCount > 0)
					{
						pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChACMaxValue;
					}
				}
			}

			nBeginIndex += nChannelNum;
			m_oModules_I[nIndex]->init_ch_drv_pos();
			m_oModules_I[nIndex]->InitChTmtPos();
		}

		nCurrentIndex = nBeginIndex;

		for(int nIndex = 0; nIndex < m_nModuleCount_UI; nIndex++)
		{
			nChannelNum = m_oModules_UI[nIndex]->m_oModuleAttr.m_nChannelNum;
			int nVoltChEeIndex = 0;
			int nCurrChEeIndex = 0;

			for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
			{
				pChDef = &m_oModules_UI[nIndex]->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];

				if(pChDef->m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pChDef->m_nChRsIndex = nVoltIndex++;
					pChDef->m_nChEeIndex = nVoltChEeIndex;
					nVoltChEeIndex++;
				}
				else
				{
					pChDef->m_nEeType = STT_CH_EETYPE_CURRENT;
					pChDef->m_nChRsIndex = nCurrentIndex++;
					pChDef->m_nChEeIndex = nCurrChEeIndex;
					nCurrChEeIndex++;
				}
			}

			m_oModules_UI[nIndex]->init_ch_drv_pos();
			m_oModules_UI[nIndex]->InitChTmtPos();
		}

		for(int nIndex = 0; nIndex < m_nModuleCount_D; nIndex++)
		{
			m_oModules_D[nIndex]->m_oModuleAttr.m_nChannelNum = 0;
			set_DigitalTmtPos(m_oModules_D[nIndex]);			
		}

		//20240111 zhoulei
		//小信号、ADMU的软件资源映射统一初始化
		nVoltIndex = 0;
		nCurrentIndex = 0;
		for(int k = 1; k <= 16; k++)
		{
			for(int nIndex = 0; nIndex < m_nModuleCount; nIndex++)
			{
				PSTT_MODULE pModule = &m_oModules[nIndex];
				if(pModule == NULL)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_nModuleIndex == k)
				{
					if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_WEEK_EX
							|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
					{
						nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

						for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
						{
							pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];

							if(pChDef->m_nEeType == 0)
							{
								pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
							}

							if(pChDef->m_nEeType == STT_CH_EETYPE_VOLTAGE)
							{
								pChDef->m_nChRsIndex = nVoltIndex++;
							}
							else
							{
								pChDef->m_nChRsIndex = nCurrentIndex++;
							}

							pChDef->m_nChEeIndex = nChanIndex;
						}
						pModule->init_ch_drv_pos();

						if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
						{
							set_DigitalTmtPosADMU(pModule);
						}

						pModule->InitChTmtPos();
					}
				}
			}
		}

		for(int nIndex = 0; nIndex < m_nModuleCount_FT3; nIndex++)
		{
			m_oModules_FT3[nIndex]->m_oModuleAttr.m_nChannelNum = 0;
			set_DigitalTmtPos(m_oModules_FT3[nIndex]);			
		}		
	}

	void init_after_read()
	{
		init_module_ByIndexandType();
		init_module_ChDefMap();

		for(int i = 0;i<m_nModuleCount_WEEK;i++)
		{
			PSTT_MODULE pModule = m_oModules_WEEK[i];
			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331
					||pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
			{
				//通道电气类型不可变原因
				//1、实际输出电压信号或电流信号
				//2、电压电流的档位定义固化
				pModule->m_oModuleAttr.m_nChTypeChg = 0;
			}
		}
	}

	void init_module_hd_ch_id(PSTT_MODULE *pModules, char chType, long nCount, long &nModuleIndex)
	{
		for (long nIndex=0; nIndex<nCount; nIndex++)
		{
			pModules[nIndex]->m_oModuleAttr.init_hd_ch_def(nModuleIndex, chType);
			nModuleIndex++;
		}
	}

	void init_hd_ch_id()
	{
		long nModuleIndex_U = 0;
		long nModuleIndex_I = 0;
		long nModuleIndex = 0;

		//模拟量
		init_module_hd_ch_id(m_oModules_U, STT_MODULETYPE_ID_ANALOG_CHAR, m_nModuleCount_U, nModuleIndex_U);
		init_module_hd_ch_id(m_oModules_I, STT_MODULETYPE_ID_ANALOG_CHAR, m_nModuleCount_I, nModuleIndex_I);
        nModuleIndex = nModuleIndex_U > nModuleIndex_I ? nModuleIndex_U: nModuleIndex_I;//max(nModuleIndex_U, nModuleIndex_I);
		init_module_hd_ch_id(m_oModules_UI, STT_MODULETYPE_ID_ANALOG_CHAR, m_nModuleCount_UI, nModuleIndex);

		//数字
		//20230918 zhoulei FT3、9-2数字版、ADMU统一排序
		//安装位置先后顺序FT3、ADMU、9-2数字版
		nModuleIndex = 0;
		for(int k = 1; k <= 16; k++)
		{
			for(long nIndex = 0; nIndex < m_nModuleCount; nIndex++)
			{
				PST_MODULE_ATTR pModuleAttr = &m_oModules[nIndex].m_oModuleAttr;

				if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_FT3
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
				{
					if(pModuleAttr->m_nModuleIndex == k)
					{
						if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
						{
							PSTT_MODULE_CH_DEFS  pChDefs = &pModuleAttr->m_oChDefMap.m_oChDefs;
							for (long nIndex=0; nIndex< DIGITAL_CHANNEL_MAX; nIndex++)
							{
								sprintf(pChDefs->m_oChDef[nIndex].m_pszChIdEx, "%c%c%d_%d",pChDefs->m_oChDef[nIndex].m_nEeTypeEx ,
										'd',  nModuleIndex+1, pChDefs->m_oChDef[nIndex].m_nChEeIndexEx+1);
							}
						}
						else
						{
							pModuleAttr->init_hd_ch_def(nModuleIndex, STT_MODULETYPE_ID_DIGITAL_CHAR);
						}
						nModuleIndex++;
						break;
					}
				}
			}
		}

		//小信号插件、ADMU插件统一编号
		nModuleIndex = 0;
		for(int k = 1; k <= 16; k++)
		{
			for(long nIndex = 0; nIndex < m_nModuleCount; nIndex++)
			{
				PST_MODULE_ATTR pModuleAttr = &m_oModules[nIndex].m_oModuleAttr;

				if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_WEEK_EX
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
				{
					if(pModuleAttr->m_nModuleIndex == k)
					{
						pModuleAttr->init_hd_ch_def(nModuleIndex++, STT_MODULETYPE_ID_WEEK_CHAR);
						break;
					}
				}
			}
		}

		//开关量
		nModuleIndex = 0;
		init_module_hd_ch_id(m_oModules_S, STT_MODULETYPE_ID_BINARY_CHAR, m_nModuleCount_S, nModuleIndex);
	}

}STT_DEVICESYSTEMPARAMETER, *PSTT_DEVICESYSTEMPARAMETER;

extern PSTT_DEVICESYSTEMPARAMETER g_theDeviceSystemParameter;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
///
///
void stt_create_adjust_ex();
void stt_init_adj_para_config();
void stt_xml_serialize_adj_para_config(CSttXmlSerializeBase *pXmlSerialize);

bool stt_open_adjust_file(const char *pszFileName);
bool stt_open_adjust_file_path(const CString &strFilePath);//zhouhj 20210506 增加根据文件路径去读取Device功能，
void stt_xml_serialize_write_adjust();
void stt_xml_serialize_register_adjust(const CString &strXMLPath);

//2021-5-2  lijunqing save-adjust-file
bool stt_save_adjust_file(const char *pszFileName);


void stt_xml_serialize_register_adjust(CSttXmlSerializeTool &oSttXmlSerializeTool);
void stt_xml_serialize_register_adjust();
void stt_xml_serialize_register_adjust(CSttXmlSerializeBase *pXmlSerialize);
void stt_init_paras(STT_DEVICESYSTEMPARAMETER *pParas);

void stt_xml_serialize_AdjItem(PSTT_ADJUST_ITEM pPara,  CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize(STT_MODULE &oPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(STT_DEVICESYSTEMPARAMETER *pPara, CSttXmlSerializeBase *pXmlSerialize);


//创建校准参数文件
void stt_create_adjust();
PSTT_DEVICESYSTEMPARAMETER stt_create_adjust(long nTemperatureCount, long nModuleCount, long nHarmCount, long nGearCount, long nHdGearCount);
bool stt_init_adjust(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nTemperatureCount, long nModuleCount, long nHarmCount, long nGearCount, long nHdGearCount);
void stt_free_adjust();

//2021-11-15 zhoulei 修改原来同类型多模块问题,PSTT_MODULE pModule
PSTT_MODULE stt_adj_find_module_byModulePos(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModulePos, long nModuleType);
PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PSTT_MODULE pModule, float fTemperature, long nChannel, long nFreqSel);
PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_TRANGE_ADJUST  pTemperatureAdj, long nChannel, long nFreqSel);
PSTT_CHANNEL_ADJUSTS stt_adj_find_channel(PSTT_MODULE pModule, long nChannel, float fTemperature);

PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PSTT_MODULE pModule, float fTemperature, long nChannel, long nFreqSel, float fAmp);
PSTT_ADJUST_ITEM stt_adj_get_ac(float fAmp,PSTT_MODULE pModule,int nChannel,float fTemperature,int nHarm=1);

//获得硬件档位最大值
//float stt_adj_get_ac_max(float fAmp, PSTT_MODULE pModule);
//int stt_adj_get_ac_HGearID(float fAmp, PSTT_MODULE pModule);
float stt_adj_get_ac_max_GearVal(float nChannel, PSTT_MODULE pModule, int nHarm = 1);

//获得采集系数
PSTT_ADJUST_ITEM stt_adj_find_meas_u_item(float fGearVal,int nModulePos,int nChannel,float fTemperature,int nHarm=1);
PSTT_ADJUST_ITEM stt_adj_find_meas_i_item(float fGearVal,int nModulePos,int nChannel,float fTemperature,int nHarm=1);
//////////////////////////////////////////////////////////////////////////
//
//序列化数据类型：字符串 ==>>  文本  2021-5-4  lijunqing
void stt_xml_serialize_data_type(CSttXmlSerializeBase *pXmlSerialize, const char *pszName, const char *pszID, const char *pszUnit, const char *pszDataType, long &nValue);

#endif // TMT_ADJUST_SYS_PARAMETER_H

