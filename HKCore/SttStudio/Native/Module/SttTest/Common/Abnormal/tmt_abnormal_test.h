#pragma once
#include"../../../SttTestBase/SttXmlSerialize.h"

#define SMV_ABNORMAL_TYPE_NULL                                0  //没有异常
#define SMV_ABNORMAL_TYPE_FrameDrop                           1  //丢帧
#define SMV_ABNORMAL_TYPE_FrampShaking                        2  //抖动
#define SMV_ABNORMAL_TYPE_FlyPoint                            3  //飞点
#define SMV_ABNORMAL_TYPE_OutOfOrder                          4  //错序
#define SMV_ABNORMAL_TYPE_DelayDeviation                      5  //延时偏差
#define SMV_ABNORMAL_TYPE_DelayChange                         6  //延时变化
#define SMV_ABNORMAL_TYPE_SeqNumDevt                          7  //序号偏差
#define SMV_ABNORMAL_TYPE_QualitySet                          8  //品质异常



typedef struct tmt_smv_abnormal_msg		//9-2配置参数
{
	char     m_strMacAddrDst[MAX_PATH];	//目的地址/
	char     m_strMacAddrSrc[MAX_PATH];	//源地址/
	int	     m_nAppID;				//APPID转换为进制，供组GetDataFromHex/
	int	     m_nVLanID;          //
	int	     m_nVLanPriority;         //
//	int      m_nPort;		//输出口选择m_nPNFSendMode0 默认为	m_nSendMode/
	int      m_nVersion;		//SMV版本号/
//	int		 m_nSmpDelay;			//采样延时m_nDelayTime0/
	int		 m_nSyn;					//同步方式0-未同步1-本地同步2-全站同步即SmpSynch 目前只用默认值为	m_nSynMode/
	char	 m_strSVID[MAX_PATH];	//m_strSVID0/
	char	 m_strDataset[MAX_PATH];	//数据集m_strDatSet0/
	int      m_nNetType;
	int      m_nUseOrigPkgSet;//使用原始报文设置 为0时不设置原始报文

	void init()
	{
		memset(m_strMacAddrDst,0, MAX_PATH);
		memset(m_strMacAddrSrc,0, MAX_PATH);
		memset(m_strSVID,0, MAX_PATH);
		memset(m_strDataset,0, MAX_PATH);
		m_nAppID = 0;
		m_nVLanID = 0;
		m_nVLanPriority = 0;
//		m_nPort = 0;
		m_nVersion = 0;
//		m_nSmpDelay = 0;
		m_nSyn = 1;
		m_nNetType = 0x88ba;
		m_nUseOrigPkgSet = 0;
	}

	tmt_smv_abnormal_msg()
	{

	}
	virtual ~tmt_smv_abnormal_msg()
	{
	}
}tmt_SmvAbnormalMsg;

// typedef struct tmt_smv_quality_set
// {
// 	int m_nValid;       //bit0-1: 00-好, 01-无效, 10-保留，11-可疑
// 	int m_nOverflow;    //无溢出  溢出
// 	int m_nOutRange;    //正常  超值域
// 	int m_nBadBmVal;    //正常坏基准值
// 	int m_nJitter;      //无抖动   抖动
// 	int m_nFault;       //无故障  故障
// 	int m_nOldDataOT;   //无超时  数据超时
// 	int m_nInconformity;//一致 不一致
// 	int m_nImprecise;   //精确   不精确
// 	int m_nSrc;         //过程   被取代
// 	int m_nTest;        //运行   测试
// 	int m_nOprLock;     //操作员闭锁
// 
// 	void init()
// 	{
// 		m_nValid = 0;
// 		m_nOverflow = 0;
// 		m_nOutRange = 0;
// 		m_nBadBmVal = 0;
// 		m_nJitter = 0;
// 		m_nFault = 0;
// 		m_nOldDataOT = 0;
// 		m_nInconformity = 0;
// 		m_nImprecise = 0;
// 		m_nSrc = 0;
// 		m_nTest = 0;
// 		m_nOprLock = 0;
// 	}
// 	tmt_smv_quality_set()	{}
// 	virtual ~tmt_smv_quality_set(){}
// }tmt_SmvQualitySet;

typedef struct tmt_state_abnormal_smv		// SMV异常参数
{
	UINT	m_nGroupIndex;			// 发生异常的报文组号，从开始，选择后将其配置拷贝到hqyIEC61850_9_2_Setting.Control_Block block变量中(从0开始编号)
	UINT	m_nSendMode;		// 发送方式：0-每周波发送1-每秒发送
	UINT	m_nCircleNum_TypeCircle;		// 发送周波数，nSendMode = type_circle有效
	UINT	m_nCircleNum_TypeSecond;// 每秒发送周波数type= type_second有效
	UINT	m_nSendTime_TypeSecond;		// 发送时间nSendMode= type_second有效

	UINT	m_nAbnormalType;			// 异常类型：-是否异常1-丢帧2-抖动3-飞点4-错序5-延时偏差6-延时变化7-序号偏差8-品质异常
	int	    m_nAbnormalPoint[80];		// 80点异常值
//	int		m_nLoseStep;			// 失步无此功能，暂时未用到
	int		m_nQualityBit[12];	// 品质
	UINT	m_nInvalidChanel[80];	// 通道使能（有效通道选择）最多个
//	UINT	m_nTestmode;			// 检修
	UINT	m_nDelayDeviation;		// 延时偏差
	UINT	m_nDelayChangeValue;		// 延时变化
//	float	m_fDelayTime;			// 延时时间
	float	m_fFlyPointVolt;		// 飞点电压值
	float	m_fFlyPointCurrent;	// 飞点电流值
//	UINT	m_uJitterDirection;	// 抖动方向,默认先向下再向上，此参数不用选
	UINT	m_uFrampShakingValue;			// 抖动值单位ns,根据主界面设置值统一修改
	int		m_nOutOfOrderValue;			// 错序，-80,没有错序设为
	UINT	m_nSeqNumDevtValue;			// 序号偏差

	int     m_nVolChEnable[6];//飞点电压使能
	int     m_nCurChEnable[6];//飞点电流使能
//	tmt_SmvQualitySet   m_oQualitySet;
	tmt_SmvAbnormalMsg  m_oSmvMsg;

	void init()
	{
		m_nGroupIndex = 0;			// 发生异常的报文组号，从0开始，选择后将其配置拷贝到hqyIEC61850_9_2_Setting.Control_Block block变量中
		m_nSendMode = 0;			// 发送方式：-每周波发送1-每秒发送
		m_nCircleNum_TypeCircle = 1;		// 发送周波数，nSendMode = type_circle有效
		m_nCircleNum_TypeSecond = 1;// 每秒发送周波数type= type_second有效
		m_nSendTime_TypeSecond = 1;		// 发送时间nSendMode= type_second有效

		m_nAbnormalType = SMV_ABNORMAL_TYPE_NULL;			// 异常类型：-是否异常1-丢帧2-抖动3-飞点4-错序5-延时偏差6-延时变化7-序号偏差

		for (int nIndex=0;nIndex<80;nIndex++)
		{
			m_nAbnormalPoint[nIndex] = 0;
			m_nInvalidChanel[nIndex] = 0;// 80点异常值从品质通道开始
		}

		for (int nIndex = 0;nIndex<6;nIndex++)
		{
			m_nVolChEnable[nIndex] = 0;
			m_nCurChEnable[nIndex] = 0;
		}

		for (int nIndex = 0;nIndex<12;nIndex++)
		{
			m_nQualityBit[nIndex] = 0;
		}

// 		m_nLoseStep = 0;			// 失步????
// 		m_nTestmode = FALSE;			// 检修
		m_nDelayDeviation = 0;		// 延时偏差(us)
		m_nDelayChangeValue = 0;		// 延时变化(us)
//		m_fDelayTime;			// 延时时间????
		m_fFlyPointVolt = 0;		// 飞点电压值
		m_fFlyPointCurrent = 0;	// 飞点电流值
		m_uFrampShakingValue = 10000;		// 抖动值单位ns,根据主界面设置值统一修改
		m_nOutOfOrderValue = 0;			// 错序，-1999 - 20000,没有错序设为????
		m_nSeqNumDevtValue = 5;			// 序号偏差
//		m_oQualitySet.init();
		m_oSmvMsg.init();
	}

	tmt_state_abnormal_smv()	{	init();	}
	virtual ~tmt_state_abnormal_smv(){}
}tmt_StateAbnormalSMV;

typedef struct tmt_state_abnormal_goose		// GOOSE异常参数
{
	int		m_nGroupIndex;	//组号从0开始
	BOOL    m_bSrcMac_Sel;
	char	m_strSrcMac[MAX_PATH];
	BOOL    m_bDestMac_Sel;
	char	m_strDestMac[MAX_PATH];
	BOOL    m_bGocbRef_Sel;
	char	m_strGocbRef[MAX_PATH];
	BOOL    m_bGoID_Sel;
	char	m_strGoID[MAX_PATH];
	BOOL    m_bDataSet_Sel;
	char	m_strDataSet[MAX_PATH];
	BOOL	m_bStNumSet_Sel;
	int		m_nStNum;	
	BOOL	m_bSqNumSet_Sel;
	int		m_nSqNum;	
	BOOL	m_bTtlSet_Sel;
	int		m_nTimeAllowToLive;    // 允许生存时间单位毫秒
	BOOL    m_bAppID_Sel;
	int  	m_nAppID;
	BOOL    m_bNdsCom_Sel;
	BOOL	m_nNdsCom;	//委托的使能恒为TRUE，默认nNdsCom为False
	BOOL	m_bTestFlag_Sel;
	BOOL	m_nTestFlag;	//测试标记的使能恒为TRUE，默认nTestFlag为False
	BOOL	m_bVlanSet_Sel;
	int		m_nVlanID;
	BOOL	m_bNetTypeSet_Sel;
	int		m_nNetType;//网络标识
	BOOL	m_bConfRecvSet_Sel;
	int		m_nConfRecv;	// 配置版本
	int		m_nVLanPriority;
	int		m_nTimequality;//时间品质
	int		m_nPort;   // 发送端口号，第一个端口号为，-1表示不发布
	int		m_nReserved1;
	int		m_nReserved2;

	void init()
	{
		m_nGroupIndex = 0;	//组号从开始
		m_bSrcMac_Sel = TRUE;
		m_bDestMac_Sel = TRUE;
		m_bGocbRef_Sel = TRUE;
		m_bGoID_Sel = TRUE;
		m_bDataSet_Sel = TRUE;
		m_bAppID_Sel = TRUE;
		m_bNdsCom_Sel = TRUE;
		m_bTestFlag_Sel = TRUE;
		memset(m_strSrcMac,0, MAX_PATH);
		memset(m_strDestMac,0, MAX_PATH);
		memset(m_strGocbRef,0, MAX_PATH);
		memset(m_strGoID,0, MAX_PATH);
		memset(m_strDataSet,0, MAX_PATH);
		strcpy(m_strSrcMac,"08-08-08-08-08-08");
		strcpy(m_strDestMac,"01-0C-CD-01-00-02");
		strcpy(m_strGocbRef,"HBDY221MUGO/LLN0$GO$gocb0");
		strcpy(m_strGoID,"HBDY221MUGO/LLN0.gocb0");
		strcpy(m_strDataSet,"HBDY221MUGO/LLN0$dsGOOSE0");
		m_nAppID = 0x4001;
		m_bStNumSet_Sel = TRUE;
		m_nStNum = 1;	
		m_bSqNumSet_Sel = TRUE;
		m_nSqNum = 1;	
		m_bTtlSet_Sel = TRUE;
		m_nTimeAllowToLive = 10000;    // 允许生存时间单位毫秒
		m_nNdsCom = FALSE;	//委托的使能恒为TRUE，默认nNdsCom为False
		m_nTestFlag = FALSE;	//测试标记的使能恒为TRUE，默认nTestFlag为False
		m_bVlanSet_Sel = TRUE;
		m_nVlanID = 0;
		m_bNetTypeSet_Sel = TRUE;
		m_nNetType = 0x88b8;//网络标识
		m_bConfRecvSet_Sel = TRUE;
		m_nConfRecv = 1;	// 配置版本
		m_nVLanPriority = 4;
		m_nTimequality = 0;//时间品质
		m_nPort = 1;   // 发送端口号，第一个端口号为，-1表示不发布
		m_nReserved1 = 0;
		m_nReserved2 = 0;
	}

	tmt_state_abnormal_goose()	{	init();	}
	virtual ~tmt_state_abnormal_goose(){}
}tmt_StateAbnormalGOOSE;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_AbnormalSMV(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AbnormalGOOSE(tmt_StateAbnormalGOOSE *pAbnormalGOOSE, CSttXmlSerializeBase *pXmlSierialize);



