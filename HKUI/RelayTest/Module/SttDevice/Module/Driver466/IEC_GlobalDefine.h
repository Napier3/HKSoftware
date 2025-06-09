#ifndef IECGLOBALDEFINE_H
#define IECGLOBALDEFINE_H

#include "../../../SttTest/Common/tmt_common_def.h"
#include "../../../SttTest/Common/tmt_system_config.h"
#include "QStringList"
#include "QVector"

//��������
//_MainBoard_PI_ (����Pi1000)
//_MainBoard_PN_ (����PN466 PN800)
//_MainBoard_PTU_ (����PTU100)
//_MainBoard_PNS330_ (����PNS330)
//_MainBoard_L336D_ (����L336D)

#define Digital_MODULE_MAX		4
#if defined(_MainBoard_PI_)
	#define ALG_MODULE_MAX			12//12�����λ
    #define BIO_MODULE_MAX 			9//���忪��+8�����λ
#else
    #define ALG_MODULE_MAX			5//����С�ź�+4�����λ
    #define BIO_MODULE_MAX 			5//���忪��+4�����λ
#endif

#define PNS330_RegAddr_AnalogCtrl   0x70004078
#define PNS330_RegAddr_DigitalCtrl  0x7000407c

//bit0������Դб��ʹ�� 1:��б��
#define PNS330_RegAddr_FPGACtrl		0x7000104c

typedef struct
{
    long nFirstValue;
    long nLen;
    QString strMap;
    long nChanPos1;//��ЧΪ-1
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
    long m_nSampleType;//��������������
    long m_nSampleDataLen;//����λ��
    long m_nDelayTimeValue;//���ʱ
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
    long nPos;//ͨ�����λ�ã�������
} Stable2MChanInfo;

typedef struct
{
    long m_nUseFlag;
    long m_nChanNum;
    long m_nAddr;
    long m_nPort;//DataPkg�õ�
    long nIdxVal;//DataPkg�õ�
    long m_nIdxMapChan;//Idx������ͨ����,��1��ʼ
    long m_nPkgLen;//��֡������Ч���ȣ�������
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
    int bHasUTC;//��һ��ͨ����UTC
    int nUTCPos;
} ChanelInfo;

typedef struct
{
    int m_nModuleIndex;//���ְ���
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
    unsigned int GroupIdxWithNum;//�����ְ��ϵ����
    unsigned int Delaytime;
    unsigned int IecXmlIndex;//�������ļ��������ţ���Ҫ�����쳣ģ��ʵ��
} DatConfig;

typedef struct
{
    unsigned int module;
    unsigned int smvCount;
    unsigned int gsCount;
	unsigned int gsSubCount;//����330������ڵ�Դ
    DatConfig sv[SMV_MAX];
    DatConfig gs[GOOSE_MAX];
    DatConfig gsSub[GOOSE_MAX];
    long nLCBeginIdx;//Ĭ��8��
    long nLCEndIdx;    
} DatConfigItems;

typedef struct
{
    unsigned int mdCnt;
    DatConfigItems item[Digital_MODULE_MAX];
} Drv_IECConfig; //0x320-0

typedef struct
{
	unsigned int moduletype;//��Ӧ���ģ������
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
} Drv_IECConfigFt3;//��������������ֱ�塢ADMU

typedef struct
{
    unsigned int count;
    unsigned char dat[DATA_MAX];//���б���Ƭ��һ������
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
//    unsigned int GroupIdxWithNum;//�����ְ��ϵ����
//    unsigned int Delaytime;
//    unsigned int IecXmlIndex;//�������ļ��������ţ���Ҫ�����쳣ģ��ʵ��
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
//    long nLCBeginIdx;//Ĭ��8��
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

//FT3����������Ϣ
typedef struct
{
    unsigned int module;				//ģ����
    unsigned int reserved[3];			//ռλ����
    unsigned int sampleCnt;
    unsigned int baud;
    unsigned int dat[6];
} SendConfFT3;

/***********GOOSEͨ��ֵ���½ṹ��***********/
typedef struct
{
    unsigned int nPos;
    unsigned int nCnt;
    unsigned char szdat[20];
} DrvGseChgData;

typedef struct
{
    unsigned int nDatCnt;				//���ݸ���
    unsigned int nGroupIndex;				//��������
    DrvGseChgData oDat[MAX_GOOSE_CHANNEL_COUNT];

    unsigned int nUTCCnt;     //���Ϊ0,���ô�ʱ��
    unsigned int nUTCPos[MAX_GOOSE_CHANNEL_COUNT];  //��Ҫ��ʱ���λ��
} DrvGseChgItem;

typedef struct
{
    unsigned int nModuleIndex;			//ģ����
    unsigned int nItemsCnt;				//�����ܺ�
    DrvGseChgItem oItem[GOOSE_MAX];				//������Ϣ�����SV/GOOSE������Ϣ
} DrvGseChgModule;

typedef struct
{
    unsigned int nModulesCnt;    //ģ����
    DrvGseChgModule oModule[Digital_MODULE_MAX];
} DrvGseChgParas;        //״̬����ÿ��״̬Ԥ���GOOSE��λ����

/***********GOOSEͨ��ֵ���½ṹ��***********/

/***********FT3ͨ��ֵ���½ṹ��***********/
typedef struct
{
    unsigned int nGroupWithBit;			//��������
    unsigned int nDatCnt;				//���ݸ���
    unsigned char szdat[200];
} DrvFT3ChgItem;

typedef struct
{
    unsigned int nModuleIndex;			//ģ����
    unsigned int nItemsCnt;				//�����ܺ�
    DrvFT3ChgItem oItem[12];
} DrvFT3ChgModule;

typedef struct
{
    unsigned int nModulesCnt;    //ģ����
	DrvFT3ChgModule oModule[ALG_MODULE_MAX];
} DrvFT3ChgParas;        //״̬����ÿ��״̬Ԥ���FT3��λ����

/***********FT3ͨ��ֵ���½ṹ��***********/

/***********�ȿ�2Mͨ��ֵ���½ṹ��***********/
typedef struct
{
    unsigned int nCnt;
    unsigned char szdat[64];
} Drv2MChgData;

typedef struct
{
    unsigned int nModuleIndex;			//ģ����
    unsigned int nItemsCnt;				//�����ܺ�
    Drv2MChgData oItem[8];				//������Ϣ
} Drv2MChgModule;

typedef struct
{
    unsigned int nModulesCnt;    //ģ����
    Drv2MChgModule oModule[3];
} Drv2MChgParas;        //״̬����ÿ��״̬Ԥ���GOOSE��λ����

/***********�ȿ�2Mͨ��ֵ���½ṹ��***********/

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

//GOOSESUBDATA,GOOSE����
typedef struct
{
    int nPos;           //�����ֽ�λ��
    int nDBIIndex;      //������ţ�???0��???
    unsigned long nTrueValue;     //True �ıȽ�???
    unsigned long nFalseValue;    //False �ıȽ�???
} GooseMapChanelValue;


//FT3SUBDATA,ft3����
typedef struct
{
    int nBiSwitch[16];//λӳ��Ŀ�����������n
    int nChanPos1;//ӳ���׵�ַ,������CRC����Ҫ���ͨ��
    int nChanLen1;//ӳ�䳤��
    int nChanPos2;
    int nChanLen2;//ӳ�䳤��,Ϊ0ʱ����ͨ��δ���
    int nValidBit;//��Чλ��1,bit15~bit0
} Ft3SubChanel;

typedef struct
{
	int nPort;//Ӳ���˿ھ���λ��0��3,����������������
	int nPortEx;//Ӳ���˿����λ��,���ڶ��ı���ʶ��
    int nbaud;
    int npacketLen;
    int nMapCnt;//ft3ӳ������
    Ft3SubChanel ft3Chanel[8];//ÿ·Ԥ��8��״̬ͨ��
} Ft3SubItem;

typedef struct
{
    unsigned int nModule;
	unsigned int nOffset;//���ƫ����
    int nCnt;
	Ft3SubItem ft3Item[FT3_Recv_MAX];//ÿ��������4�����տ�
} Ft3SubData;

typedef struct
{
	int nModuleCnt;
	Ft3SubData ft3SubData[4];//֧��4�����
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
	Ft3SubCrc ft3SubCrc[4];//֧��4�����,ÿ�����4�����տ�
} Ft3SubCrcs;
/***********GOOSE����ӳ��ṹ��***********/
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
/***********GOOSE����ӳ��ṹ��***********/

/***********GOOSE����ӳ��ṹ��***********/
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
    int CRC;//¼��������
    GooseSubItem oItem;//����
} IecRecvItem;

typedef struct
{
    unsigned int nType;//bit0-bit7 1 enabled 2 unenabled
    unsigned int ncount;
    IecRecvItem oIecSub[16];
} IecRecvCfg;
/***********GOOSE����ӳ��ṹ��***********/

/***********�쳣ģ��ṹ��***********/
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
    unsigned int 	module;//����ģ����
    unsigned int	ptCnt;//�쳣����
    structSVabn		stSVabn[80];//ÿ�ܲ�������쳣����
    unsigned int  	group;//SMV��� 8bit��Ч��0��Ч 1ʹ�� �� 0011 ���ǵ�һ�ڶ���ʹ�ܣ�������Ч��
    unsigned int 	abnCycle;//�쳣�ܲ���
    unsigned int 	normalCycle;// �����ܲ���
    unsigned int  	loop;//ѭ������
} structSVabnPara;

typedef struct
{
    unsigned int	module;
    unsigned int	group;
    unsigned int 	len;
    unsigned char 	dat[1536];
    unsigned int 	gsTimePos;

    unsigned int nUTCCnt;     //���Ϊ0,���ô�ʱ��
    unsigned int nUTCPos[MAX_GOOSE_CHANNEL_COUNT];  //��Ҫ��ʱ���λ��
} StructComAbn;

typedef struct
{
    unsigned int		abnType;			//�쳣ģ������	0�����쳣	1��SMV�쳣	2��GOOSE�쳣
    StructComAbn		stGSItem;			//GOOSE�쳣���ƿ����
    StructComAbn		stSVItem;			//SMV�쳣���ƿ����
    structSVabnPara 	stSVabn;			//SMV�쳣�������ò���
    unsigned int 		reConfig;			//�Ƿ������·� SendConfSV
    SendConfSV			stSendCfg;				//SMV�쳣�������ò���
} Drv_AbnPara;

/***********�쳣ģ��ṹ��***********/

typedef struct
{
    unsigned int Cnt;
    SendConfSV   confsv[Digital_MODULE_MAX];//Ԥ��3�����ְ�
} SvConfigTotal;

union ConverStruct
{
    unsigned char b[4];
    unsigned long l;
    float f;
};//4���ֽڣ����ù����壬����ת��


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

inline QString DecToBin(QString strDec)//10进制��?2进制
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

        nValue = nValue * 16 + nLetterValue; //16进制
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
    type += QString::number(port, 16); //aa1*-SV,aa2*-goose,aa3*-ft3,���չ����ţ�0-15��ʾ��Ϊ���3��SV
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
    return 1 << (nModuleIndex - 1); //������bit�洢ģ��λ����Ϣ
}

#endif // IEC61850CONFIG_H
