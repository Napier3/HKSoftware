#ifndef IECGLOBALDEFINE_H
#define IECGLOBALDEFINE_H

#include "../../../SttTest/Common/tmt_common_def.h"
#include "../../../SttTest/Common/tmt_system_config.h"
#include "QStringList"
#include "QVector"

//机箱类型
//_MainBoard_PI_ (例如Pi1000)
//_MainBoard_PN_ (例如PN466 PN800)
//_MainBoard_PTU_ (例如PTU100)
//_MainBoard_PNS330_ (例如PNS330)
//_MainBoard_L336D_ (例如L336D)

#define Digital_MODULE_MAX		4
#if defined(_MainBoard_PI_)
	#define ALG_MODULE_MAX			12//12个插件位
    #define BIO_MODULE_MAX 			9//主板开关+8个插件位
#else
    #define ALG_MODULE_MAX			5//主板小信号+4个插件位
    #define BIO_MODULE_MAX 			5//主板开关+4个插件位
#endif

#define PNS330_RegAddr_AnalogCtrl   0x70004078
#define PNS330_RegAddr_DigitalCtrl  0x7000407c

//bit0电流电源斜率使能 1:有斜率
#define PNS330_RegAddr_FPGACtrl		0x7000104c

typedef struct
{
    long nFirstValue;
    long nLen;
    QString strMap;
    long nChanPos1;//无效为-1
    long nChanLen1;
    long nChanPos2;
    long nChanLen2;
    long nBiIdxSub[16];
    long nValidBitSub;//0x0~0xFFFF
} FT3ChanInfo;

typedef struct
{
    int port;
    int group;
    long m_nSampleType;//采样计数器类型
    long m_nSampleDataLen;//采样位宽
    long m_nDelayTimeValue;//额定延时
    long m_nChanNum;

    long m_nTotalSizeSub;
    long m_nSampleValSub;
    long m_nBaudValSub;

    QList<FT3ChanInfo> m_oChanList;
} tmt_ft3_6044;

typedef struct
{
    long nFirstValue;
    long nLen;
    long nPos;//通道相对位置，订阅用
} Stable2MChanInfo;

typedef struct
{
    long m_nUseFlag;
    long m_nChanNum;
    long m_nAddr;
    long m_nPort;//DataPkg用到
    long nIdxVal;//DataPkg用到
    long m_nIdxMapChan;//Idx关联的通道号,从1开始
    long m_nPkgLen;//单帧报文有效长度，订阅用
    Stable2MChanInfo m_oChanList[MAX_2M_CHANNEL_COUNT];
} tmt_Stable2M;

typedef struct
{
    int port;
    int group;
    QString m_MacDesc;
    QString m_MacSrc;
    QString m_SVID;
    QString m_AppID;
    QString m_ChanNum;
    QString m_ASDUNum;
    QString m_SyncMode;
    QString m_SmpCnt;
    QString m_ConfRev;
    QString m_SmpRate;
    QString m_VLanID;
    QString m_VLanPri;
    QString m_NetType;
    QString m_DelayTimeValue;
    QByteArray m_ChanValueList;
    QStringList m_FactorList;
    QString m_Datset;
    unsigned short nreserved1;
    unsigned short nreserved2;

    bool m_bSecurity;
    bool m_bDatset;
    bool m_bRefrTm;
    bool m_bSmpRate;
} tmt_sv_92;

typedef struct
{
    QString data_type;
    QString firstvalue;
    QString strMap;//app-ch
    QString strDevCh;//dev-ch
    int nPos;
    int nLen;
    int nBoPos;
    int nBOIndex;
    int nBOExIndex;
    char nTrueValue;
    char nFalseVlaue;
    int bHasUTC;//下一个通道是UTC
    int nUTCPos;
} ChanelInfo;

typedef struct
{
    int m_nModuleIndex;//数字板编号
    int port;
    int group;
    QString m_MacDesc;
    QString m_MacSrc;
    QString m_AppID;
    QString m_GcRef;
    QString m_TTL;
    QString m_DataSetRef;
    QString m_GoID;
    QString m_NdsCom;
    QString m_ConfRev;
    QString m_TestMode;
    QString m_VLanID;
    QString m_VLanPri;
    QString m_NetType;
    QString m_StNum;
    QString m_SqNum;
    unsigned int nreserved1;
    unsigned int nreserved2;
    char ntimequality;
    int m_ChanNum;

    QByteArray m_DataSetList;
    QVector<ChanelInfo> vChanelInfo;
    int nDataSetPos;
    int nTestModePos;
    int nUTCPos;
} tmt_goose;

typedef struct
{
    QByteArray m_PduLength;
    QByteArray m_GcRef;
    QByteArray m_TTL;
    QByteArray m_DataSetRef;
    QByteArray m_GoID;
    QByteArray m_TimeStamp;
    QByteArray m_StNum;
    QByteArray m_SqNum;
    QByteArray m_TestMode;
    QByteArray m_ConfRev;
    QByteArray m_NdsCom;
    QByteArray m_EntriesNum;
    QByteArray m_DataSetList;
} GoosePduStruct;

typedef struct
{
    QByteArray m_DesMac;
    QByteArray m_SrcMac;
    QByteArray m_VLan;
    QByteArray m_Type;
    QByteArray m_AppID;
    QByteArray m_ApplicationLength;
    QByteArray m_Reserve1;
    QByteArray m_Reserve2;
    GoosePduStruct m_GoosePdu;
} GooseStruct;

typedef struct
{
    QByteArray m_StartLength;
    QByteArray m_smvID;
    QByteArray m_Datset;//zhangsen 20190906
    QByteArray m_SmpCnt;
    QByteArray m_ConRev;
    QByteArray m_RefrTm;//zhangsen 20190906
    QByteArray m_SmpSynch;
    QByteArray m_SmpRate;//zhangsen 20190906
    QByteArray m_SequenceData;
} ASDUStruct;

typedef struct
{
    QByteArray m_pduLength;
    QByteArray m_NumOfASDU;
    QByteArray m_Security; //zhangsen 20190906
    QByteArray m_SequenceofASDU;
    QVector<ASDUStruct *> p_ASDUVector;
} PDUStruct;


typedef struct
{
    QByteArray m_DesMac;
    QByteArray m_SrcMac;
    QByteArray m_VLan;
    QByteArray m_Type;
    QByteArray m_AppID;
    QByteArray m_ApplicationLength;
    QByteArray m_Reserve1;
    QByteArray m_Reserve2;
    PDUStruct m_PDU;
} SMV92Struct;

#define SMV_MAX           8
#define GOOSE_MAX        16
#define FT3_MAX          12
#define FT3_Recv_MAX     4
#define DATA_MAX         1536

typedef struct
{
    unsigned int datCnt;
    unsigned int GroupWithBit;
    unsigned char dat[DATA_MAX];
    unsigned int PortIdx;//0-7
    unsigned int GroupIdxWithNum;//在数字板上的序号
    unsigned int Delaytime;
    unsigned int IecXmlIndex;//在配置文件里面的序号，主要用于异常模拟实验
} DatConfig;

typedef struct
{
    unsigned int module;
    unsigned int smvCount;
    unsigned int gsCount;
	unsigned int gsSubCount;//用于330遍历光口电源
    DatConfig sv[SMV_MAX];
    DatConfig gs[GOOSE_MAX];
    DatConfig gsSub[GOOSE_MAX];
    long nLCBeginIdx;//默认8个
    long nLCEndIdx;    
} DatConfigItems;

typedef struct
{
    unsigned int mdCnt;
    DatConfigItems item[Digital_MODULE_MAX];
} Drv_IECConfig; //0x320-0

typedef struct
{
	unsigned int moduletype;//对应插件模块类型
	unsigned int module;
	unsigned int ft3Count;
	DatConfig ft3[FT3_MAX];
	long nSTSendBeginIdx;
	long nSTSendEndIdx;
	long nSTRecvBeginIdx;
	long nSTRecvEndIdx;
} DatConfigItemsFt3;

typedef struct
{
	unsigned int mdCnt;
	DatConfigItemsFt3 item[ALG_MODULE_MAX];
} Drv_IECConfigFt3;//单独管理，兼容柔直板、ADMU

typedef struct
{
    unsigned int count;
    unsigned char dat[DATA_MAX];//所有报文片段一起下载
} DatConfig_2M;

typedef struct
{
    unsigned int module;
    DatConfig_2M dats[MAX_2M_BLOCK_COUNT];
} DatConfigItems_2M;

typedef struct
{
    unsigned int moduleCount;
    DatConfigItems_2M item[MAX_2M_MODULE_COUNT];
} Drv_IECConfig_2M; //0x320-1

typedef struct
{
    unsigned int data0;
    unsigned int data1;
    unsigned int data2;
    unsigned int data3;

    unsigned int data4;//SV1-4
    unsigned int data5;//SV5-8

    unsigned int data6;//GSE1-4
    unsigned int data7;//GSE5-8
    unsigned int data8;//GSE9-12
    unsigned int data9;//GSE13-16
} FiberConf; //0x321-0

//typedef struct{
//    unsigned int PortIdx;//0-7
//    unsigned int GroupIdxWithNum;//在数字板上的序号
//    unsigned int Delaytime;
//    unsigned int IecXmlIndex;//在配置文件里面的序号，主要用于异常模拟实验
//}FiberDat;

//typedef struct{
//    long  bIsDRT;
//    unsigned int module;
//    unsigned int smvCount;
//    unsigned int gsCount;
//    unsigned int gsSubCount;
//    unsigned int ft3Count;
//    FiberDat sv[SMV_MAX];
//    FiberDat gs[GOOSE_MAX];
//    FiberDat gsSub[GOOSE_MAX];
//    FiberDat ft3[FT3_MAX];
//    long nLCBeginIdx;//默认8个
//    long nLCEndIdx;
//    long nSTSendBeginIdx;
//    long nSTSendEndIdx;
//    long nSTRecvBeginIdx;
//    long nSTRecvEndIdx;
//}FiberItems;

//typedef struct
//{
//    int nCnt;
//    FiberItems item[Digital_MODULE_MAX];
//}DigitalModulesInfo;

typedef struct
{
    unsigned int module;
    unsigned int reserved[3];

    unsigned int sampleCount;
    unsigned int beginCode[4];
    //	unsigned int data5;//SV12
    //	unsigned int data6;//SV34
    //	unsigned int data7;//SV56
    //	unsigned int data8;//SV78
} SendConfSV; //0x321-1

typedef struct
{
    unsigned int module;
    unsigned int reserved[3];

    unsigned int data4;//T0
    unsigned int data5;//T1
    unsigned int data6;//T2
    unsigned int data7;//T3
} SendConfGSE; //0x321-2

//FT3发送配置信息
typedef struct
{
    unsigned int module;				//模块编号
    unsigned int reserved[3];			//占位数据
    unsigned int sampleCnt;
    unsigned int baud;
    unsigned int dat[6];
} SendConfFT3;

/***********GOOSE通道值更新结构体***********/
typedef struct
{
    unsigned int nPos;
    unsigned int nCnt;
    unsigned char szdat[20];
} DrvGseChgData;

typedef struct
{
    unsigned int nDatCnt;				//数据个数
    unsigned int nGroupIndex;				//数据组编号
    DrvGseChgData oDat[MAX_GOOSE_CHANNEL_COUNT];

    unsigned int nUTCCnt;     //如果为0,不用打时标
    unsigned int nUTCPos[MAX_GOOSE_CHANNEL_COUNT];  //需要打时标的位置
} DrvGseChgItem;

typedef struct
{
    unsigned int nModuleIndex;			//模块编号
    unsigned int nItemsCnt;				//组数总和
    DrvGseChgItem oItem[GOOSE_MAX];				//数据信息，详见SV/GOOSE数据信息
} DrvGseChgModule;

typedef struct
{
    unsigned int nModulesCnt;    //模块数
    DrvGseChgModule oModule[Digital_MODULE_MAX];
} DrvGseChgParas;        //状态序列每个状态预设的GOOSE变位参数

/***********GOOSE通道值更新结构体***********/

/***********FT3通道值更新结构体***********/
typedef struct
{
    unsigned int nGroupWithBit;			//数据组编号
    unsigned int nDatCnt;				//数据个数
    unsigned char szdat[200];
} DrvFT3ChgItem;

typedef struct
{
    unsigned int nModuleIndex;			//模块编号
    unsigned int nItemsCnt;				//组数总和
    DrvFT3ChgItem oItem[12];
} DrvFT3ChgModule;

typedef struct
{
    unsigned int nModulesCnt;    //模块数
	DrvFT3ChgModule oModule[ALG_MODULE_MAX];
} DrvFT3ChgParas;        //状态序列每个状态预设的FT3变位参数

/***********FT3通道值更新结构体***********/

/***********稳控2M通道值更新结构体***********/
typedef struct
{
    unsigned int nCnt;
    unsigned char szdat[64];
} Drv2MChgData;

typedef struct
{
    unsigned int nModuleIndex;			//模块编号
    unsigned int nItemsCnt;				//组数总和
    Drv2MChgData oItem[8];				//数据信息
} Drv2MChgModule;

typedef struct
{
    unsigned int nModulesCnt;    //模块数
    Drv2MChgModule oModule[3];
} Drv2MChgParas;        //状态序列每个状态预设的GOOSE变位参数

/***********稳控2M通道值更新结构体***********/

//GseTestMode
typedef struct
{
    unsigned int pos;
    unsigned int value;
    unsigned int group;
} StructGSTestMdUnit;

typedef struct
{
    unsigned int module;
    unsigned int nCount;
    StructGSTestMdUnit gs[GOOSE_MAX];
} StructGSTestData;

typedef struct
{
    unsigned int nCount;
    StructGSTestData dat[Digital_MODULE_MAX];
} Drv_GseTest;

//BOMap
typedef struct
{
    unsigned int pos;
    unsigned int group;
    unsigned int module;
    unsigned char trueValue;
    unsigned char falseValue;
    unsigned int hasUTC;
    unsigned int utcPos;
} StructMap;

typedef struct
{
    unsigned int cnt;
    StructMap stMap[16];
} StructBoInfo;

typedef struct
{
    StructBoInfo info[8];//DO1-8
} StructBoMap;

//GOOSESUBDATA,GOOSE订阅
typedef struct
{
    int nPos;           //倒数字节位置
    int nDBIIndex;      //开入序号，???0开???
    unsigned long nTrueValue;     //True 的比较???
    unsigned long nFalseValue;    //False 的比较???
} GooseMapChanelValue;


//FT3SUBDATA,ft3订阅
typedef struct
{
    int nBiSwitch[16];//位映射的开关量，开入n
    int nChanPos1;//映射首地址,遇到跨CRC，需要拆分通道
    int nChanLen1;//映射长度
    int nChanPos2;
    int nChanLen2;//映射长度,为0时代表通道未拆分
    int nValidBit;//有效位置1,bit15~bit0
} Ft3SubChanel;

typedef struct
{
	int nPort;//硬件端口绝对位置0～3,用于下载配置命令
	int nPortEx;//硬件端口相对位置,用于订阅报文识别
    int nbaud;
    int npacketLen;
    int nMapCnt;//ft3映射数量
    Ft3SubChanel ft3Chanel[8];//每路预留8个状态通道
} Ft3SubItem;

typedef struct
{
    unsigned int nModule;
	unsigned int nOffset;//光口偏移量
    int nCnt;
	Ft3SubItem ft3Item[FT3_Recv_MAX];//每个插件最多4个接收口
} Ft3SubData;

typedef struct
{
	int nModuleCnt;
	Ft3SubData ft3SubData[4];//支持4个插件
} Ft3SubDatas;

typedef struct
{
	unsigned int nModule;
	unsigned int nCnt;
	unsigned int nPkgLen[FT3_Recv_MAX];//=0564 + Pkg + CRC
} Ft3SubCrc;

typedef struct
{
	int nModuleCnt;
	int nCrcType;
	Ft3SubCrc ft3SubCrc[4];//支持4个插件,每个插件4个接收口
} Ft3SubCrcs;
/***********GOOSE开出映射结构体***********/
typedef struct
{
    unsigned int pos;
    unsigned int group;
    unsigned int module;
    unsigned char trueValue;
    unsigned char falseValue;
    unsigned int hasUTC;
    unsigned int utcPos;
} structBOMap;

typedef struct
{
    unsigned int cnt;
    structBOMap stMap[16];
} structGSOutInfo;

typedef struct
{
    structGSOutInfo info[64];
} structGSOutModule;

typedef struct
{
    structGSOutModule boMd[BIO_MODULE_MAX];
} Drv_GSOutMap;
/***********GOOSE开出映射结构体***********/

/***********GOOSE订阅映射结构体***********/
typedef struct
{
    unsigned int pos;
    unsigned int mdPos;
    unsigned int index;
    unsigned int trueValue;
    unsigned int falseValue;
} structGooseSubValue;

#define GOOSE_MAP_MAX					64
#define GOCB_LEN_MAX					MAX_GOOSE_CHANNEL_COUNT
#define GOID_LEN_MAX					GOCB_LEN_MAX
#define DATASET_LEN_MAX					GOCB_LEN_MAX

typedef struct
{
    int paramAdvance;
    int gocbLen;
    char GOCB[GOCB_LEN_MAX];
    int goidLen;
    char GOID[GOID_LEN_MAX];
    int dataSetLen;
    char dataSet[DATASET_LEN_MAX];
    unsigned int testMode;
    int count;
    unsigned int StNum_H;
    unsigned int StNum_L;
    unsigned int SqNum_H;
    unsigned int SqNum_L;
    structGooseSubValue val[GOOSE_MAP_MAX];
} GooseSubItem;

typedef struct
{
    int CRC;//录波、订阅
    GooseSubItem oItem;//订阅
} IecRecvItem;

typedef struct
{
    unsigned int nType;//bit0-bit7 1 enabled 2 unenabled
    unsigned int ncount;
    IecRecvItem oIecSub[16];
} IecRecvCfg;
/***********GOOSE订阅映射结构体***********/

/***********异常模拟结构体***********/
typedef struct
{
    unsigned int	pt;					//?????
    unsigned short	isLost;				//???  	1:????	0:?????
    unsigned short	jitter;				//????		0:??????,1?0.1us??250us????2500
    int				errcmpt;			//????   	-1?????,0-3999????
    unsigned int	flyPtEn;			//??????
    int				flyPtV;				//??????
    int		 		flyPtI;				//???????
} structSVabn;

typedef struct
{
    unsigned int 	module;//数字模块编号
    unsigned int	ptCnt;//异常点数
    structSVabn		stSVabn[80];//每周波各点的异常设置
    unsigned int  	group;//SMV组号 8bit有效，0无效 1使能 如 0011 则是第一第二组使能，其他无效。
    unsigned int 	abnCycle;//异常周波数
    unsigned int 	normalCycle;// 正常周波数
    unsigned int  	loop;//循环个数
} structSVabnPara;

typedef struct
{
    unsigned int	module;
    unsigned int	group;
    unsigned int 	len;
    unsigned char 	dat[1536];
    unsigned int 	gsTimePos;

    unsigned int nUTCCnt;     //如果为0,不用打时标
    unsigned int nUTCPos[MAX_GOOSE_CHANNEL_COUNT];  //需要打时标的位置
} StructComAbn;

typedef struct
{
    unsigned int		abnType;			//异常模拟类型	0：无异常	1：SMV异常	2：GOOSE异常
    StructComAbn		stGSItem;			//GOOSE异常控制块参数
    StructComAbn		stSVItem;			//SMV异常控制块参数
    structSVabnPara 	stSVabn;			//SMV异常类型配置参数
    unsigned int 		reConfig;			//是否重新下发 SendConfSV
    SendConfSV			stSendCfg;				//SMV异常发送配置参数
} Drv_AbnPara;

/***********异常模拟结构体***********/

typedef struct
{
    unsigned int Cnt;
    SendConfSV   confsv[Digital_MODULE_MAX];//预留3个数字板
} SvConfigTotal;

union ConverStruct
{
    unsigned char b[4];
    unsigned long l;
    float f;
};//4个字节，利用共用体，进行转换


inline QString Get0String(int m_0Length)
{
    if(m_0Length <= 0)
    {
        return "";
    }

    QString t_R1 = "";
    QString t_0 = "0";

    for(int p = 0; p < m_0Length; p++)
    {
        t_R1 += t_0;
    }

    return t_R1;
}

inline QString DecToBin(QString strDec)//10杩涘埗锟斤拷?2杩涘埗
{
    int nDec = strDec.toInt();
    QString strBin("%1");
    strBin = strBin.arg(nDec, 4, 2, QChar('0'));
    return strBin;
}

inline QString HexToBin(QString m_Value)//16-2
{
    int t_Value = m_Value.toInt();
    QString t_strValue = "";
    t_strValue.setNum(t_Value);
    return DecToBin(t_strValue);
}

inline QString BinToHex(QString m_strBin)//2-16
{
    bool ok;
    long t_V = m_strBin.toLong(&ok, 2);
    QString t_Dec = "";
    t_Dec = t_Dec.setNum(t_V, 16);
    return t_Dec;
}

inline QString DecToHex(QString strDec)//10->16
{
    bool ok;
    long t_V = strDec.toLong(&ok, 10);
    QString t_Hex = "";
    return t_Hex.setNum(t_V, 16);
}

inline unsigned long GetIntegerFromString(QString pStr)
{
    int t_Length = pStr.length();
    char  *ch;
    QByteArray ba = pStr.toLatin1();
    ch = ba.data();
    unsigned long nValue = 0;

    for(int i = 0; i < t_Length; i++)
    {
        int nLetterValue ;

        switch(ch[i])
        {
            case 'a':
            case 'A':
                nLetterValue = 10;
                break;

            case 'b':
            case 'B':
                nLetterValue = 11;
                break;

            case 'c':
            case 'C':
                nLetterValue = 12;
                break;

            case 'd':
            case 'D':
                nLetterValue = 13;
                break;

            case 'e':
            case 'E':
                nLetterValue = 14;
                break;

            case 'f':
            case 'F':
                nLetterValue = 15;
                break;

            default:
                nLetterValue = ch[i] - '0';
        }

        nValue = nValue * 16 + nLetterValue; //16杩涘埗
    }

    return nValue;
}

inline void AddLongStrToByte(QString m_Value, QByteArray &m_ByteArray, int m_Length)
{
    int m_StratPos = 0;
    QString t_temp = "";

    for(int m = 0; m < m_Length; m++)
    {
        m_StratPos = m * 2;
        t_temp = m_Value.mid(m_StratPos, 2);
        unsigned char t_V = GetIntegerFromString(t_temp);
        m_ByteArray.push_back(t_V);
    }
}

inline void AddASN1StrToByte(QString m_Value, QByteArray &m_ByteArray, unsigned short m_Flag, int m_Length)
{
    int t_V = GetIntegerFromString(m_Value);

    if(t_V >= 0x80)
    {
        m_ByteArray.push_back(m_Flag);
        m_ByteArray.push_back(0x80 + m_Length);
        AddLongStrToByte(m_Value, m_ByteArray, m_Length);//SrcMac
    }
    else
    {
        m_ByteArray.push_back(m_Flag);
        m_ByteArray.push_back(m_Length);
        AddLongStrToByte(m_Value, m_ByteArray, m_Length);//SrcMac
    }
}

inline void GetASDUData(QByteArray &m_ASDUDataArray, QByteArray &m_ChanListData, QStringList &m_ChanFactorList, int &m_OffsetChanValue, int m_ChanNum)
{
    m_ASDUDataArray.push_back(0x87);
    QByteArray t_Array;
    int t_ChanNum = m_ChanNum;

    for(int m = 0; m < t_ChanNum; m++)
    {
        if(m >= m_ChanListData.size()) //2
        {
            AddLongStrToByte("00000000", t_Array, 4);
            AddLongStrToByte("00000000", t_Array, 4);
            continue;
        }

        unsigned char t_ChanID = m_ChanListData[m];

        for(int tt = 0; tt < 4; tt++)
        {
            t_Array.push_back(t_ChanID);
        }

        AddLongStrToByte(m_ChanFactorList[m], t_Array, 4);
    }

    int t_CDataLength = t_Array.size();

    if(t_CDataLength >= 0x80 && t_CDataLength <= 0xFF)
    {
        m_OffsetChanValue = 3;
        m_ASDUDataArray.push_back(0x81);
        m_ASDUDataArray.push_back(t_CDataLength);
    }
    else
    {
        if(t_CDataLength > 0xFF)
        {
            m_OffsetChanValue = 4;
            m_ASDUDataArray.push_back(0x82);
            QString t_strCDataLength = "";
            t_strCDataLength = t_strCDataLength.setNum(t_CDataLength);
            QString t_HexCL = DecToHex(t_strCDataLength);
            t_HexCL = Get0String(4 - t_HexCL.length()) + t_HexCL;
            m_ASDUDataArray.push_back(GetIntegerFromString(t_HexCL.mid(0, 2)));
            m_ASDUDataArray.push_back(GetIntegerFromString(t_HexCL.mid(2, 2)));
        }
        else
        {
            m_OffsetChanValue = 2;
            m_ASDUDataArray.push_back(t_CDataLength);
        }
    }

    for(int j = 0; j < t_CDataLength; j++)
    {
        m_ASDUDataArray.push_back(t_Array.at(j));
    }
}

inline unsigned short CRC16(unsigned char *pszdata, unsigned int datalen, unsigned short wCRCin, unsigned short wCPoly, unsigned short wCXOR, bool input_invert, bool ouput_invert)
{
    unsigned char wChar = 0;
    unsigned char wTemp;

    for(unsigned int i = 0; i < datalen; i++)
    {
        wTemp = pszdata[i];

        if(input_invert)
        {
            wChar = wTemp;
            wTemp = 0;

            for(unsigned int j = 0; j < 8; j++)
            {
                if(wChar & 0x01)
                {
                    wTemp |= 0x01 << (7 - j);
                }

                wChar >>= 1;
            }
        }

        wCRCin ^= (wTemp << 8);

        for(unsigned int j = 0; j < 8; j++)
        {
            if(wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }

    if(ouput_invert)
    {
        unsigned short nTemp;
        nTemp = wCRCin;
        wCRCin = 0;

        for(unsigned int j = 0; j < 16; j++)
        {
            if(nTemp & 0x01)
            {
                wCRCin |= 0x01 << (15 - j);
            }

            nTemp >>= 1;
        }
    }

    return (wCRCin ^ wCXOR);
}

inline unsigned short CalCRC(QString appid, QString dest_mac, int port, int ntype)
{
    QString type = "aa";
    type += QString::number(ntype);
    type += QString::number(port, 16); //aa1*-SV,aa2*-goose,aa3*-ft3,接收光口序号：0-15，示例为光口3收SV
    unsigned char data[10];
    bool ok;
    data[0] = dest_mac.mid(0, 2).toInt(&ok, 16);
    data[1] = dest_mac.mid(2, 2).toInt(&ok, 16);
    data[2] = dest_mac.mid(4, 2).toInt(&ok, 16);
    data[3] = dest_mac.mid(6, 2).toInt(&ok, 16);
    data[4] = dest_mac.mid(8, 2).toInt(&ok, 16);
    data[5] = dest_mac.mid(10, 2).toInt(&ok, 16);
    data[6] = type.mid(0, 2).toInt(&ok, 16);
    data[7] = type.mid(2, 2).toInt(&ok, 16);
    data[8] = appid.mid(0, 2).toInt(&ok, 16);
    data[9] = appid.mid(2, 2).toInt(&ok, 16);
    return CRC16(data, 10, 0x0000, 0x3D65, 0x0000, false, false);
}

inline unsigned int ModuleIndexTransToDrv(long nModuleIndex)
{
    return 1 << (nModuleIndex - 1); //驱动按bit存储模块位置信息
}

#endif // IEC61850CONFIG_H
