#ifndef TMT_ADJUST_TEST_H
#define TMT_ADJUST_TEST_H

#include "../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_adjust_sys_parameter.h"

//lijunqing 2020-10-20
#define STT_ADJUST_MACRO_ID_AdjustOne		   "AdjustOne"
#define STT_ADJUST_MACRO_ID_AdjustOneCopy      "AdjustOneCopy"
#define STT_ADJUST_MACRO_ID_AdjustThree		   "AdjustThree"
#define STT_ADJUST_MACRO_ID_AdjustSwitch	   "AdjustSwitch"
#define STT_ADJUST_MACRO_ID_ReadModuleFlash    "ReadModuleFlash"
#define STT_ADJUST_MACRO_ID_WriteModuleFlash   "WriteModuleFlash"
#define STT_ADJUST_MACRO_ID_AdjustReboot       "AdjustReboot"
#define STT_ADJUST_MACRO_ID_AdjustOne2Points   "AdjustOne2Points"
#define STT_ADJUST_MACRO_ID_AdjustOneAngle	   "AdjustOneAngle"
#define STT_ADJUST_MACRO_ID_AdjustOneFreq	   "AdjustOneFreq"
#define STT_ADJUST_MACRO_ID_AdjustOneDcZero	   "AdjustOneDcZero"
#define STT_ADJUST_MACRO_ID_SetMeasGear		   "SetMeasGear"
#define STT_ADJUST_MACRO_ID_SetUTCTime         "SetUTCTime"
#define STT_ADJUST_MACRO_ID_GetUTCTime		   "GetUTCTime"

#define STT_ADJUST_MODULEFLASH_RESULT_SUCCESS             0
#define STT_ADJUST_MODULEFLASH_RESULT_ModuleNoResponse    1   //读模块无响应
#define STT_ADJUST_MODULEFLASH_RESULT_ModulePtrIsNull     2  //查找模块指针为空
#define STT_ADJUST_MODULEFLASH_RESULT_ModuleResponseErr   3  //写模块返回错误
#define STT_ADJUST_MODULEFLASH_RESULT_DataHeadErr         4  //返回数据内容头错误
#define STT_ADJUST_MODULEFLASH_RESULT_UnZipErr            5
//////////////////////////////////////////////////////////////////////////
//校准测试功能结构体
typedef struct tmt_adjust_meas_gear
{
    long m_nModuleType;  //模块类型
    long m_nModulePos;  //模块位置
    long m_nChannel;  //通道编号，目前最大为6个通道
    long m_nGearID; //档位 <0无效  0=缺省到位，即档位1 2=档位2......

    void init()
    {
        m_nModuleType = 0;
        m_nModulePos = 0;
        m_nChannel = 0;
        m_nGearID = 0;//根据g_theModuleOutPut和m_nChannel计算出,计算结果默认是最大档位
    }
}TMT_ADJUST_MEAS_GEAR;

//单通道校准参数结构体
typedef struct tmt_adjust_one_paras
{
    long m_nModuleType;  //模块类型
    long m_nModule;  //模块位置
    long m_nChannel;  //通道编号，目前最大为6个通道
    long m_nFreqSel; // 0=DC;1=基波；2=2此谐波，.......
    long m_nTempretureID;  //<=0无效   1=温区1......
    long m_nGearID; //软件补偿档位 <0无效  0=缺省到位，即档位1 2=档位2......
    float m_fMag;   //表计测量值：幅值、相位、频率
    float m_fAng;
    float m_fFreq;
    float m_fDeviation;//表计误差

    void init()
    {
        m_nModuleType = 0;
        m_nModule = 0;
        m_nChannel = 0;
        m_nFreqSel = 1;//从g_theModuleOutPut处获得,无需串行化
        m_nTempretureID = 0;
        m_nGearID = 0;//根据g_theModuleOutPut和m_nChannel计算出,计算结果默认是最大档位
        m_fMag = 0;
        m_fAng = 0;
        m_fFreq = 0;
		m_fDeviation=0;
    }
}TMT_ADJUST_ONE_PARAS, *PTMT_ADJUST_ONE_PARAS;

typedef struct tmt_Adjust_One_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_ONE_RESULTS, *PTMT_ADJUST_ONE_RESULTS;

//测试功能：单通道校准结构体
typedef struct tmt_adust_one
{
    TMT_ADJUST_ONE_PARAS m_oParas;  //参数
    TMT_ADJUST_ONE_RESULTS m_oResult;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_ONE, *PTMT_ADJUST_ONE;

/*********单通道双点幅值校准*********/
//基波及各次谐波幅值校准
//m_fPoint1RefMag m_fPoint2RefMag中最大值决定校准哪个软件档
typedef struct tmt_adjust_one2points_paras
{
    long m_nModuleType;  //被校模块类型
    long m_nModule;  //被校模块位置
    long m_nChannel;  //被校通道编号，目前最大为6个通道
    long m_nTempretureID;  //<=0无效   1=温区1......
    long m_nFreqSel; //参考频率 0=DC;1=基波；2=2此谐波，.......

    float m_fPoint1RefMag;   //参考值：幅值
    float m_fPoint2RefMag;   //参考值：幅值
    float m_fPoint1MeasMag;   //测量值：幅值
    float m_fPoint2MeasMag;   //测量值：幅值

    float m_fDeviation;//表计误差

    void init()
    {
        m_nModuleType = 0;
        m_nModule = 0;
        m_nChannel = 0;
        m_nFreqSel = 1;
        m_nTempretureID = 0;

        m_fPoint1RefMag = 0;
        m_fPoint2RefMag = 0;
        m_fPoint1MeasMag = 0;
        m_fPoint2MeasMag = 0;

		m_fDeviation=0;
    }
}TMT_ADJUST_ONE2POINTS_PARAS, *PTMT_ADJUST_ONE2POINTS_PARAS;

typedef struct tmt_Adjust_One2Points_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_ONE2POINTS_RESULTS, *PTMT_ADJUST_ONE2POINTS_RESULTS;

typedef struct tmt_adust_one2points
{
    TMT_ADJUST_ONE2POINTS_PARAS m_oParas;  //参数
    TMT_ADJUST_ONE2POINTS_RESULTS m_oResult;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_ONE2POINTS, *PTMT_ADJUST_ONE2POINTS;
/*********单通道双点幅值校准*********/

/*********单通道零点直流分量校准*********/
//只校准基波第一个软件档位
typedef struct tmt_adjust_DcZero_paras
{
    long m_nModuleType;  //被校模块类型
    long m_nModule;  //被校模块位置
    long m_nChannel;  //被校通道编号，目前最大为6个通道
    long m_nTap;      //被校通道硬件档位 0,1,2
    long m_nTempretureID;  //<=0无效   1=温区1......

    float m_fMeasDcZero;//测量值
    float m_fDeviation;//表计误差

    void init()
    {
        m_nModuleType = 0;
        m_nModule = 0;
        m_nChannel = 0;
        m_nTap = 0;
        m_nTempretureID = 0;
        m_fMeasDcZero = 0;
		m_fDeviation=0;
    }
}TMT_ADJUST_DCZERO_PARAS, *PTMT_ADJUST_DCZERO_PARAS;

typedef struct tmt_Adjust_DcZero_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_DCZERO_RESULTS, *PTMT_ADJUST_DCZERO_RESULTS;

typedef struct tmt_adjust_DcZero
{
    TMT_ADJUST_DCZERO_PARAS m_oParas;  //参数
    TMT_ADJUST_DCZERO_RESULTS m_oResult;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_DCZERO, *PTMT_ADJUST_DCZERO;
/*********单通道零点直流分量校准*********/

/*********单通道相位校准*********/
//只校准基波第一个软件档位
typedef struct tmt_adjust_angle_paras
{
    long m_nModuleType;  //被校模块类型
    long m_nModule;  //被校模块位置
    long m_nChannel;  //被校通道编号，目前最大为6个通道
    long m_nTempretureID;  //<=0无效   1=温区1......

    float m_fOutMag;//加量幅值
    float m_fMeasAng;//测量值：相位
    float m_fDeviation;//表计误差

    void init()
    {
        m_nModuleType = 0;
        m_nModule = 0;
        m_nChannel = 0;
        m_nTempretureID = 0;
        m_fOutMag = 0;
        m_fMeasAng = 0;
		m_fDeviation=0;
    }
}TMT_ADJUST_ANGLE_PARAS, *PTMT_ADJUST_ANGLE_PARAS;

typedef struct tmt_Adjust_Angle_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_ANGLE_RESULTS, *PTMT_ADJUST_ANGLE_RESULTS;

typedef struct tmt_adjust_angle
{
    TMT_ADJUST_ANGLE_PARAS m_oParas;  //参数
    TMT_ADJUST_ANGLE_RESULTS m_oResult;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_ANGLE, *PTMT_ADJUST_ANGLE;
/*********单通道相位校准*********/

/*********模块频率校准*********/
//只校准工频,随便哪个通道
typedef struct tmt_adjust_freq_paras
{
    long m_nModuleType;  //被校模块类型
    long m_nModule;  //被校模块位置

    float m_fRefFreq;//参考值
    float m_fMeasFreq;//测量值
    float m_fDeviation;//表计误差

    void init()
    {
        m_nModuleType = 0;
        m_nModule = 0;
        m_fRefFreq = 50.0f;
        m_fMeasFreq = 0;
		m_fDeviation=0;
    }
}TMT_ADJUST_FREQ_PARAS, *PTMT_ADJUST_FREQ_PARAS;

typedef struct tmt_Adjust_Freq_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_FREQ_RESULTS, *PTMT_ADJUST_FREQ_RESULTS;

typedef struct tmt_adjust_freq
{
    TMT_ADJUST_FREQ_PARAS m_oParas;  //参数
    TMT_ADJUST_FREQ_RESULTS m_oResult;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_FREQ, *PTMT_ADJUST_FREQ;
/*********模块频率校准*********/

//校准：三通道校准参数结构体
typedef struct tmt_adjust_three_paras : public TMT_ADJUST_ONE_PARAS
{
    //方便计算处理，就是用数组
    //注意：测试功能参数设置的时候，需要更新三个参数对象的公共部分
    long m_nChannel2;
    long m_nGearID2;
    float m_fMag2;
    float m_fAng2;
    float m_fFreq2;
    long m_nChannel3;
    long m_nGearID3;
    float m_fMag3;
    float m_fAng3;
    float m_fFreq3;
    long m_nLargeCurrent;//1:大电流系数校准 0:普通系数校准
    void init()
    {
        TMT_ADJUST_ONE_PARAS::init();

        m_nChannel2 = 0;
        m_nGearID2 = 0;
        m_fMag2 = 0;
        m_fAng2 = 0;
        m_fFreq2 = 0;
        m_nChannel3 = 0;
        m_nGearID3 = 0;
        m_fMag3 = 0;
        m_fAng3 = 0;
        m_fFreq3 = 0;
		m_nLargeCurrent=0;
    }
}TMT_ADJUST_THREE_PARAS, *PTMT_ADJUST_THREE_PARAS;

typedef struct tmt_Adjust_Three_Results
{
    STT_ADJUST_ITEM m_oResult[3];

    void init()
    {
        m_oResult[0].init();
        m_oResult[1].init();
        m_oResult[2].init();
    }
}TMT_ADJUST_THREE_RESULTS, *PTMT_ADJUST_THREE_RESULTS;

//测试功能：三通道校准参数结构体
typedef struct tmt_adjust_three
{
    TMT_ADJUST_THREE_PARAS m_oParas;   //校准参数：测量
    TMT_ADJUST_THREE_RESULTS m_oResults;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResults.init();
    }
}TMT_ADJUST_THREE, *PTMT_ADJUST_THREE;

//校准：拷贝线性校准参数
typedef struct tmt_adjust_onecopy_paras : public TMT_ADJUST_ONE_PARAS
{
    //方便计算处理，就是用数组
    //注意：测试功能参数设置的时候，需要更新三个参数对象的公共部分
    long m_nModule2;  //模块编号，同类型的模块顺序编号
    long m_nChannel2;  //通道编号，目前最大为6个通道
    long m_nTempretureID2;  //<=0无效   1=温区1......
    long m_nGearID2; //档位 <0无效  0=缺省到位，即档位1 2=档位2......

    void init()
    {
        TMT_ADJUST_ONE_PARAS::init();

        m_nChannel2 = 0;
        m_nModule2 = 0;
        m_nTempretureID2 = 0;
        m_nGearID2 = 0;
    }
}TMT_ADJUST_ONECOPY_PARAS, *PTMT_ADJUST_ONECOPY_PARAS;

typedef struct tmt_Adjust_OneCopy_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_ONECOPY_RESULTS, *PTMT_ADJUST_ONECOPY_RESULTS;

//测试功能：单通道校准结构体
typedef struct tmt_adust_onecopy
{
    TMT_ADJUST_ONECOPY_PARAS m_oParas;  //参数
    TMT_ADJUST_ONECOPY_RESULTS m_oResult;  //校准参数

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_ONECOPY, *PTMT_ADJUST_ONECOPY;

//模块输出：通道矢量结构体
typedef struct tmt_adj_channel_vector
{
    float m_fMag;
    float m_fAngle;
}TMT_ADJ_CHANNEL_VECTOR, *PTMT_ADJ_CHANNEL_VECTOR;
typedef struct tmt_adj_channel_vector_ex : public TMT_ADJ_CHANNEL_VECTOR
{
    float m_fFreq;
}TMT_ADJ_CHANNEL_VECTOR_EX, *PTMT_ADJ_CHANNEL_VECTOR_EX;

//模块输出：通道参数结构体
typedef struct tmt_adj_channel
{
    //0=dc, 1=base wave. 2=second harm,......
    TMT_ADJ_CHANNEL_VECTOR m_oVector;
    //    TMT_ADJ_CHANNEL_VECTOR m_harm[ADJUST_MAX_HARM_COUNT] ;
}TMT_ADJ_CHAANEL, *PTMT_ADJ_CHAANEL;

//模块输出参数结构体
typedef struct tmt_adj_module_output
{	
    long m_nModuleType;
    long m_nModuleIndex;
    long m_nFreqIndex;
    long m_nChannel;
    long m_nTap;//硬件档位继电器 0,1,2
    TMT_ADJ_CHAANEL m_oChannels[STT_MODULE_CHANNEL_MAX];//zhoulei20211009 兼容48路小信号

    void init()
    {
        m_nModuleType = 0;
        m_nModuleIndex = 0;
        m_nFreqIndex = 1;
        m_nChannel = 0;
        m_nTap = 0;
        memset(m_oChannels, 0,  sizeof(TMT_ADJ_CHAANEL) * STT_MODULE_CHANNEL_MAX);
    }
}TMT_ADJ_MODULE_OUTPUT, *PTMT_ADJ_MODULE_OUTPUT;

//切换装置
typedef struct tmt_adj_switch_output
{
    long m_nModuleType;
    long m_nModuleIndex;
    long m_nSwitchMode;
    void init()
    {
		m_nModuleType=0;
		m_nModuleIndex=0;
		m_nSwitchMode=0;
    }
}TMT_ADJ_SWITCH_OUTPUT, *PTMT_ADJ_SWITCH_OUTPUT;

//开关量导通测试
typedef struct tmt_adj_binary_output
{
    unsigned int m_nBoutTurnOnValue[16];
	unsigned int m_nBoutValue[16];
    void init()
    {
        for(int i = 0; i < 16; i++)
        {
            m_nBoutTurnOnValue[i] = 1;
			m_nBoutValue[i] = 0;
        }
    }
} TMT_ADJ_BINARY_OUTPUT, *PTMT_ADJ_BINARY_OUTPUT;

//开关量插件测试
typedef struct tmt_adj_binaryex_output
{
	unsigned int m_nModuleIndex;//模块位置0-11
	unsigned int m_nBoutExValue[64];//0-断开 1-闭合
	void init()
	{
		for(int i = 0; i < 64; i++)
		{
			m_nBoutExValue[i] = 0;
		}
	}
} TMT_ADJ_BINARYEX_OUTPUT, *PTMT_ADJ_BINARYEX_OUTPUT;

//寄存器值测试
typedef struct tmt_adj_register_output
{
    char m_nRegAddr[10];
    char m_nRegValue[10];
    void init()
    {
		strcpy(m_nRegAddr,"");
		strcpy(m_nRegValue,"");
    }
}TMT_ADJ_REGISTER_OUTPUT, *PTMT_ADJ_REGISTER_OUTPUT;

//读写模块FLASH
typedef struct tmt_adj_moduleflash_paras
{
    long m_nModuleIndex;//模块位置
    long m_nModuleAddr;//模块局域网内编号
    void init()
    {
        m_nModuleIndex = 0;
        m_nModuleAddr = 0;
    }
}TMT_ADJ_MODULEFLASH_PARAS, *PTMT_ADJ_MODULEFLASH_PARAS;

typedef struct tmt_adj_moduleflash_results
{
    int m_nResult;
    void init()
    {
		m_nResult=0;
    }
}TMT_ADJ_MODULEFLASH_RESULTS, *PTMT_ADJ_MODULEFLASH_RESULTS;

typedef struct tmt_adj_moduleflash
{
    TMT_ADJ_MODULEFLASH_PARAS m_oParas;
    TMT_ADJ_MODULEFLASH_RESULTS m_oResult;

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJ_MODULEFLASH, *PTMT_ADJ_MODULEFLASH;

//单通道校准计算结构体
typedef struct tmt_adj_cal_vector
{
    TMT_ADJ_CHANNEL_VECTOR_EX m_oOutputVector;  //device output value
    TMT_ADJUST_ONE_PARAS m_oAdjParas;  //adjust paras;
    PSTT_ADJUST_ITEM m_pAdjResults; //adjust coef referance
}TMT_ADJ_CAL_VECTOR, *PTMT_ADJ_CAL_VECTOR;

//单通道校准计算结构体
typedef struct tmt_adj_cal_vector_three
{
    TMT_ADJ_CHANNEL_VECTOR_EX m_oOutputVector[3];  //device output value
    TMT_ADJUST_THREE_PARAS m_oAdjParas;  //adjust paras;
    PSTT_ADJUST_ITEM m_pAdjResults[3]; //adjust coef referance
}TMT_ADJ_CAL_VECTOR_THREE, *PTMT_ADJ_CAL_VECTOR_THREE;


void stt_xml_serialize(TMT_ADJUST_MEAS_GEAR &pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_ONE pParas);
void stt_xml_serialize(PTMT_ADJUST_ONE_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ONE_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_ONE2POINTS pParas);
void stt_xml_serialize(PTMT_ADJUST_ONE2POINTS_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ONE2POINTS_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_ANGLE pParas);
void stt_xml_serialize(PTMT_ADJUST_ANGLE_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ANGLE_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_FREQ pParas);
void stt_xml_serialize(PTMT_ADJUST_FREQ_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_FREQ_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_DCZERO pParas);
void stt_xml_serialize(PTMT_ADJUST_DCZERO_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_DCZERO_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJUST_THREE pParas);
void stt_xml_serialize(PTMT_ADJUST_THREE_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_THREE_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_ONECOPY pParas);
void stt_xml_serialize(PTMT_ADJUST_ONECOPY_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ONECOPY_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_MODULE_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_MODULE_OUTPUT pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_SWITCH_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_SWITCH_OUTPUT pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_BINARY_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_BINARY_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize);

void stt_init_paras(PTMT_ADJ_REGISTER_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_REGISTER_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize);

void stt_init_paras(PTMT_ADJ_MODULEFLASH pParas);
void stt_xml_serialize(PTMT_ADJ_MODULEFLASH_PARAS pPara, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(PTMT_ADJ_MODULEFLASH_RESULTS pPara, CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize_write_ModuleOutPut();
void stt_xml_serialize_write_RegisterTest();
#endif // TMT_ADJUST_TEST_H

