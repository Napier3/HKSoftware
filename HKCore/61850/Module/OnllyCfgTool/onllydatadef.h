#ifndef _ONLLYDATADEF_H
#define _ONLLYDATADEF_H
#include <algorithm>
#include <vector>
#include <map>
#include <list>
using namespace std;


#include "IoMuGseDef.h"
// #include "..\..\OnllyDevMsgDef.h"
//#include "OnllyDevMsgDef.h"

//测试仪最多能支持的电压或电流通道数
#define MAX_CHANNEL_COUNT     16

// 测试仪最多能支持的开入量或开出量个数
#define MAX_IO_COUNT          16

// IO 测试装置最多能支持的开入量或开出量个数
#define MAX_IO_COUNT_EX      256

//最大UI通道数
#define MAX_TST_MUCHN     128
#define MAX_VOLT_NUMBER MAX_CHANNEL_COUNT 	// 16 路电压, 16 路电流
#define MAX_CURR_NUMBER MAX_CHANNEL_COUNT 
#define MAX_BIN_NUMBER  MAX_IO_COUNT 	    // 16 路开入, 16 路开出
#define MAX_BOUT_NUMBER MAX_IO_COUNT 


//--------------------------------------------------------------------------
// version 2012-07-12 增加SMV控制块的同步自适应参数:bSynAuto。


// version 2012-08-01 增加报文测试异常点数据。


// version 2012-08-07 增加9-2的0x81 0x84 0x86结构体 OTHER92OP

// version 2012-09-12 增加报文测试类型
//--------------------------------------------------------------------------


#pragma once

typedef struct _MU_CHNSET
{
	int nIndex;			// 通道编号
	int nChnSel;		// 通道选择
	DWORD m_DOWD_Q;		// 品质位数据


	CString strInput;   // 手动输入值


	CString strChnName;	// 通道名称
	CString strRemark;  // 备注
	BOOL bCheck;        // 是否进行报文测试(品质测试与错值测试时有效)

	// 2012-03-01
	int nTypeSel;       // 类型选择 0-电压,1-电流（保护）,2-电流（测量）,3-时间
}MU_CHNSET;

const int TestType = 11;
const int MaxItem = 3;
const int PointNum = 80;

typedef struct _tagMSGTestSet
{
	int nIndex;

	BOOL bCheck;		// 限制次数
	UINT nNum;			// 限制次数
	UINT nTestType;		// 测试类型
	int TestTypeSet[TestType][MaxItem];        // 测试类型参数设置
	UINT TestBeginPt;						   // 测试起始帧



	// 2011-10-20
	UINT logicCheck;
	int nStartType;

	// 2012-08-01 zy 增加异常点设置记录

	BYTE ExpPtSet[TestType][PointNum];
}MSGTESTSET,*PMSGTESETSET;

typedef std::tr1::shared_ptr<MSGTESTSET> MSGTESTSETPtr;

/************************************************************************/
/* zy 2012-03-12 通道数据设置                                           */
/************************************************************************/
typedef struct tagMuCfgData
{
	UINT uIndex;		// 通道索引
	UINT32 uChnType;	// 通道类型 0:电压；1:电流；3:时间
	int nChnSel;        // 通道映射

	int nSetData;		// 飞点测试用的一个设置值



	float Mag;			// 幅值*10000
	float Ang;			// 相位*10000 -> 0~360
	float Fre;			// 频率*10000
	float Quo;			// 9-2:PT/CT变比 * 10000 ; 9-1:比例(0x1cf,0x2d41)

	float fData1;		// PT/CT 额定值1
	float fData2;		// PT/CT 额定值2

	float fFirstData;	// 变化初值


	float fLastData;    // 变化终止
	float fStep;		// 变化步径

	BOOL  bQuaTest;		// 品质或错值测试


	BOOL  bVar;			// 是否为变量



	CString strName;	// 通道名称
}MuCfgData,*pMuCfgData;

typedef struct _tagOther92Op 
{
	BOOL m_bCheckDatSet; CString DatSet;  // 20字节ASCII文本，以NULL结尾
	BOOL m_bCheckRefrTm; UINT64 RefrTm;   // 48位时标


	BOOL m_bCheckSmpRate;UINT16 SmpRate;   // 16位 BigEndian无符号


}OTHER92OP,*POTHER92OP;


// MU通道设置
typedef struct _MU_SETTING
{
	int nIndex;		   // 序号
	BOOL bUsed;        // 启用标记
	CString strMac;    // 目标MAC地址
	CString SourceMac; // 源MAC地址
	int AppId;		   // AppId
	int nTCIPr;		   // TCI Priority;
	int nTciVid;       // TCI VID
	int nLanNo;		   // 光网口选择
	int nVersion;	   // 版本号


	CString strDes;	   // 描述
	int nChnNum;	   // 每帧通道数

	BOOL bSynAuto;     // 同步是否自适应
	USHORT CurrentA;		// 额定相电流

	USHORT CurrentScp;		// 额定相电流比例因子

	USHORT CurrentNeut;	    // 额定中线电流
	USHORT VoltA;			// 额定相电压


	int AsduNum;            // FT3固定为1


	// 除9-2外全部使用

	DWORD dwState1;      // 状态字1
	DWORD dwState2;      // 状态字2
	USHORT LDName;		 // LDName
	UINT16 LNName;		 // LNName
	USHORT DataName;     // 数据集名

	// 9-2使用
	CString strSvid;     // SVID
	BOOL bSyn;			 // 是否同步
	float fCTBitRate;	 // 9-2使用 界面值(可为float)*10000(建议使用2^14=16384，则ARM可通过移位完成除法)
	float fPTBitRate;
	OTHER92OP other92op; // 9-2其它选项,标记:tag:0x81,0x84,0x86

	// Ft3、Ft3Ex使用
	DWORD CurrentDelay;  // 额定延时

	// 输出通道选择
	vector<MU_CHNSET> pmu_chnset;

	/************************************************************************/
	/* zy 2012-03-12 通道数据定义   									    */
	/************************************************************************/
	MuCfgData UIs[MAX_TST_MUCHN];

	MSGTESTSETPtr msgtestsetPtr;

	/*2013-05-08  增加相角是否连续*/
	BOOL bConti;   // 相角是否连续
	
	BOOL bSCDInput;   // 是否从SCD文件导入的SMV输入
	bool operator==(const _MU_SETTING& musetting) const 
	{
		return (musetting.AppId == AppId && musetting.strMac == strMac);
	}
}MU_SETTING; 

// MU通用配置
typedef struct _MU_GENERALSETTTING
{
	int nSampleType;       // 0---9-1,1---9-2,2---9-1Ex,3---Ft3,4---Ft3Ex
	int nCurSelCtrl;       // 当前选择的控制块索引
	DWORD dSampleRate;    // 采样率
	UINT32 dRSR;           // 采样率翻转


	int nMode1588;		   // 1588同步方式 无(0)/主机(1)/从机(2)
	int nMuCfgNum;		   // 启用配置数不能超过7（4光网口、3Ft3）


	//	USHORT dwAsduLen;      // 单个Asdu数据长度 ; 9-1/Ex中，如含ASDU状态数据集，则长度应含状态集长度。FT3＝0
	int nAsduNum;		   // ASDU数 生成报文时，检测报文长度是否超1536字节。（超过1500时警告）FT3=1
	float dSecondCurrent; // 9-1/Ex Ft3/Ex使用  0x01:1 A制 0x05:5A制


	DWORD dwConfRev;       //     

	float dFTSampleRate;  // FT3采样速率	//2011-06-08
	int nFT3Format;        // FT3报文格式	//2011-06-30
	BOOL bConver;          // 光串口转换为光网口输出	//2011-07-11      
	BOOL bSynMode;         // TRUE---同步 FALSE---异步	//2012-02-02  
	UINT32 uAsyncSet;       // A板与B板异步传输数据设置


}MU_GENERALSETTTING;

//GOOSE 界面数据
#define MAXGSETYPE 9
typedef struct _tagGseChnCfg
{
	int nIndex;			// 序号
	int nIOIndex;		// 绑定开入开出序号


	CString strChnName; // 条目名称

	int nType;			// 类型:0---单点,1---双点，2---时间，3---品质，4---浮点，5---字符串，6---整型，7---结构

	CString strValue;	// 值


	BOOL bInStruct;		// 是否结构体内类型

	int nLenValue;
	DWORD dwLenStartPos; // 距开始的长度


	bool operator==(const _tagGseChnCfg& gsechncfg) const 
	{
		return (gsechncfg.nIOIndex == nIOIndex);
	}

	
}GSECHNCFG;

/************************************************************************/
/* zy 2012-4-12 增加 Goose 报文测试                                     */
/************************************************************************/
typedef struct _tagGsePktTestSet
{
	BOOL bLimit;			// 限制次数
	UINT nLmNum;			// 限制次数
	UINT nTestType;			// 测试类型
	int	 TestParam[10][5];	// 测试类型参数设置
	UINT nStartType;        // 启动类型
	UINT nTestPT;			// 测试起始帧

	UINT nTestPT2;

}GsePktTestSet,*pGsePktTestSet;


typedef std::tr1::shared_ptr<GsePktTestSet> GsePktTestSetPtr;

typedef struct _tagcfg_GseIn
{
	int nIndex;    // 序号

	// GOOSEIN使用
	UINT32 ChkMask;	//按位定义，对应以下项目，增加：TTL超时、虚端子类型匹配

	// GOOSEOUT使用
	USHORT LanNo;

	CString	GocbRef;
	CString	GoID;
	CString	DataSet;
	CString strDes;	// 描述
	BOOL Used;		//启用(1)/禁用(0)
	USHORT	ConfRev;
	USHORT	NdsCom;
	CString	MacAddr;
	CString SourceMac;
	USHORT	Priority;
	USHORT	VID;
	USHORT	AppID;
	DWORD T0;
	DWORD T1;
	DWORD T2;
	DWORD T3;
	USHORT TMult;
	BOOL Test;
	UINT BinNum;
	UINT OldBinNum;

	vector<GSECHNCFG> ChnCfg;

	/************************************************************************/
	/* zy 2012-4-12 Goose 报文测试定义                                      */
	/************************************************************************/
	GsePktTestSetPtr GsetestsetPtr;

	// 2013-04-01
	BOOL bTTL; DWORD  TTL;  // TTL时间
	BOOL bTQ; __int64 Time; // 时间品质

	bool operator==(const _tagcfg_GseIn& gsecfg) const 
	{
		return (gsecfg.AppID == AppID && gsecfg.MacAddr == MacAddr);
	}

} GSECFG;

typedef struct _tagUI_Gse
{
	UINT	Version;		//0x20110309

	int GseInNumSel;	// 启用配置	
	int GseOutNumSel;

	vector<GSECFG> GseInCfg;
	vector<GSECFG> GseOutCfg;

} GSEUI;

typedef struct MapBin_Get
{
	USHORT BinOrder;	
	USHORT BinType;	    
	UINT	MapType;	
}MAPBIN_GET;

typedef struct fillset_Mu_Content
{
	UINT FillType;//数据来源编码
	UINT FillCtrl;//填充控制，低16位=填充位置，高16位=填充长度
} FILLSETCONTENT;

typedef struct _tag_FillSet_MU
{
	USHORT FillSetNum;	                        //报文在PC机打包，此处指明报文中需要填充的项数
	FILLSETCONTENT FillSet[MAX_FILL_SET_NUM];   //填充配置项


}FILLSET_MU;

typedef struct _tag_MUCtrl_UI
{
	DWORD smpCntFill;     // 采样计数器填充


	UINT nFillStartPos;   // 通道填充起始位置
}MUCTRL_UI;

typedef struct _tag_GSECtrl_UI
{
	UINT tFill;
	UINT sqnumFill;
}GSECTRL_UI;

typedef struct _tag_mu_cfg
{
	//0422增加
	DWORD smpCntFill;     // 采样计数器填充


	UINT nFillStartPos;   // 通道填充起始位置

	UINT PacketDataLen;   // 报文数据的实际长度


	UCHAR PacketData[MAX_PACKET_SIZE];//报文数据

	UINT nAsduLen;        // ASDU长度
	FILLSET_MU FillSet;   // 填充配置项


	FILLSET_MU TestSet;   // 设置配置项，报文测试
}MUDOWN_CFG;

typedef struct _tagBin_Fill
{
	UINT MapType;	//数据来源编码
	UINT FillCtrl;	//填充控制，低16位=填充位置，高16位=填充长度
	USHORT BinType;	//虚端子类型 83/84
}BINFILL;

typedef struct _tagcfg_GseOutfile
{
	UCHAR GocbRef[MAX_GOCBREF_LEN];
	UINT GocbRefLen;
	UCHAR GoID[MAX_GOID_LEN];
	UINT GoIDLen;
	UCHAR DataSet[MAX_DATASET_LEN];
	UINT DataSetLen;
	UCHAR MacAddr[MAX_MACADDR_LEN];
	UCHAR SourceMac[MAX_MACADDR_LEN];

	UINT PacketLen;					    //报文长度
	UCHAR PacketData[MAX_PACKET_SIZE];  //报文数据
	UINT MapBinNum;					    //已映射虚端子个数
	UINT FillSetNum;	                //报文在PC机打包，此处指明报文中需要填充的项数
	UINT AllDataLen;
	BINFILL	MapBinCfg[MAX_MAP_BIN_NUM];

	UINT ttlFill;
	UINT tFill;
	UINT stnumFill;
	UINT sqnumFill;

	/************************************************************************/
	/* zy 2012-4-12 Goose报文测试填充位置                                   */
	/************************************************************************/
	FILLSET_MU PktTestSet;				//设置配置项，报文测试
} CFG_GSEOUTFILE;

typedef struct _tagBin_Get
{
	USHORT BinOrder;	//虚端子序号


	USHORT BinType;	    //虚端子类型 83/84
	UINT MapType;	//数据来源编码
}BIN_GET;

typedef struct _tagcfg_GseInfile
{
	UCHAR GocbRef[MAX_GOCBREF_LEN];
	USHORT GocbRefLen;
	UCHAR GoID[MAX_GOID_LEN];
	USHORT GoIDLen;
	UCHAR DataSet[MAX_DATASET_LEN];
	USHORT DataSetLen;

	UCHAR MacAddr[MAX_MACADDR_LEN];
	USHORT MapBinNum;      // 已映射虚端子个数
	BIN_GET	MapBinCfg[MAX_MAP_BIN_NUM];
} CFG_GSEINFILE;

typedef struct _tagPTCTDATA
{
	BOOL BIsVolt;
	UINT32 Primary;
	UINT32 Secondary;
	UINT32 SignalType;
}PTCTDATA;

typedef std::tr1::shared_ptr<CFG_GSEOUTFILE> GOUTFILESHAREPTR;
typedef std::tr1::shared_ptr<CFG_GSEINFILE> GINFILESHAREPTR;
typedef std::tr1::shared_ptr<MUDOWN_CFG> MUDOWNCFGSHAREPTR;


typedef std::vector<GOUTFILESHAREPTR > GOUTFILEGVECTOR;
typedef std::vector<GINFILESHAREPTR > GINFILEVECTOR;

typedef struct _tagGSEFILE
{
	UINT	Version;		//0x20110309
	GINFILEVECTOR pGseinCfg;
	GOUTFILEGVECTOR pGseoutCfg;
}GSEFILE;

typedef std::vector<MUDOWNCFGSHAREPTR > MUDOWNCFGVECTOR;

#endif