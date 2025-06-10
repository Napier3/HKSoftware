#ifndef IEC61850CONFIG_H
#define IEC61850CONFIG_H

#include "../../SttDevice/RelayTest/drv_define.h"
#include "QMap"
#include "QtCore"
#include "QObject"
#include"../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "drv_state_test.h"

typedef struct
{
	int port;
	int group;
	QString m_MacDesc;//Ŀ����ַ
	QString m_MacSrc;//Դ��ַ
	QString m_SVID;//SVID
	QString m_AppID;//APPID
	QString m_ChanNum;//ͨ����Ŀ
	QString m_ASDUNum;//ASDU��Ŀ
	QString m_SyncMode;//ͬ����ʽ
	QString m_SmpCnt;//������
	QString m_ConfRev;//ConfRev
	QString m_SmpRate;//SmpRate
	QString m_VLanID;//VLANID
	QString m_VLanPri;//���ȼ�
	QString m_NetType;//
	QString m_DelayTimeValue;
	QByteArray m_ChanValueList;//��Ӧ������ֵ
	QStringList m_FactorList;//Chan Factor
	QString m_Datset;
	unsigned short nreserved1;
	unsigned short nreserved2;

	bool m_bSecurity;
	bool m_bDatset;
	bool m_bRefrTm;
	bool m_bSmpRate;
}tmt_sv_92;

typedef struct
{
	QString data_type;
	QString firstvalue;
	int nPos;
	int nLen;
	//	int nChanelIndex;

	int nmapIndex;
	int nBoPos;
	int nBOIndex;
	char nTrueValue;
	char nFalseVlaue;
	int bHasUTC;
	int nUTCPos;
}ChanelInfo;

typedef struct
{
	int port;
	int group;
	QString m_MacDesc;//Ŀ����ַ
	QString m_MacSrc;//Դ��ַ
	QString m_AppID;//APPID
	QString m_GcRef;
	QString m_TTL;//��������ʱ��
	QString m_DataSetRef;//DataSet Reference
	QString m_GoID;//GoID
	QString m_NdsCom;//ί��
	QString m_ConfRev;//���ð汾��
	QString m_TestMode;//����
	QString m_VLanID;//VLANID
	QString m_VLanPri;//���ȼ�
	QString m_NetType;//
	QString m_StNum;
	QString m_SqNum;
	unsigned int nreserved1;
	unsigned int nreserved2;
	char ntimequality;
	int m_ChanNum;//ͨ����Ŀ

	QByteArray m_DataSetList;//���ݼ��е�����,use for packet
	QVector<ChanelInfo> vChanelInfo;//use for Bout
	int nDataSetPos;
	int nTestModePos;
	int nUTCPos;
}tmt_goose;

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
}GoosePduStruct;

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
}GooseStruct;

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
}ASDUStruct;

typedef struct
{
	QByteArray m_pduLength;
	QByteArray m_NumOfASDU;
	QByteArray m_Security; //zhangsen 20190906
	QByteArray m_SequenceofASDU;
	QVector<ASDUStruct *> p_ASDUVector;
}PDUStruct;


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
}SMV92Struct;

typedef struct{
	unsigned int count;
	unsigned int group;
	unsigned char dat[DATA_MAX];
}DatConfig;

typedef struct{
	unsigned int module;
	unsigned int smvCount;
	unsigned int gsCount;
	unsigned int ft3Count;
	DatConfig sv[SMV_MAX];
	DatConfig gs[GOOSE_MAX];
	DatConfig ft3[FT3_MAX];
}DatConfigItems;

typedef struct{
	unsigned int moduleCount;
	DatConfigItems item[DIGITAL_MODULE_MAX];
}StructIECConfig;//0x320-0

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
}FiberConf;//0x321-0

typedef struct{
	unsigned int port;
	unsigned int group;
}FiberDat;

typedef struct{
	FiberDat sv[SMV_MAX];
	FiberDat gs[GOOSE_MAX];
	FiberDat ft3[FT3_MAX];
}FiberItems;

typedef struct
{
	FiberItems item[DIGITAL_MODULE_MAX];
}IECFiberInfo;

typedef struct
{
	unsigned int data0;
	unsigned int data1;
	unsigned int data2;
	unsigned int data3;

	unsigned int data4;

	unsigned int data5;//SV12
	unsigned int data6;//SV34
	unsigned int data7;//SV56
	unsigned int data8;//SV78
}SendConfSV;//0x321-1

typedef struct
{
	unsigned int data0;
	unsigned int data1;
	unsigned int data2;
	unsigned int data3;

	unsigned int data4;//T0
	unsigned int data5;//T1
	unsigned int data6;//T2
	unsigned int data7;//T3
}SendConfGSE;//0x321-2

//GseChanged
typedef struct{
	unsigned int pos;			//position
	unsigned int count;			//count
	unsigned char dat[20];		//data
}GoogseChanelChanged;

typedef struct{
	unsigned int count;
	unsigned int group;
	GoogseChanelChanged  dat[GOOSE_CHANGE_POS_MAX];   //modify  dat[512];
	unsigned int ChangeCount;//UTC
	unsigned int changePos[GOOSE_CHANGE_POS_MAX];
}DatConfigChanged;

typedef struct{
	unsigned int module;
	unsigned int groupCount;
	DatConfigChanged dat[GOOSE_MAX];
}DatConfigChangedItems;

typedef struct{
	unsigned int moduleCount;
	DatConfigChangedItems items[DIGITAL_MODULE_MAX];
}GooseChangedItems;

//GseTestMode
typedef struct{
	unsigned int pos;
	unsigned int value;
	unsigned int group;
}StructGSTestMdUnit;

typedef struct{
	unsigned int module;
	unsigned int cnt;
	StructGSTestMdUnit gs[GOOSE_MAX];
}StructGSTestData;

typedef struct{
	unsigned int cnt;
	StructGSTestData dat[DIGITAL_MODULE_MAX];
}StructGSTest;

//BOMap
typedef struct{
	unsigned int pos;
	unsigned int group;
	unsigned int module;
	unsigned char trueValue;
	unsigned char falseValue;
	unsigned int hasUTC;
	unsigned int utcPos;
}StructMap;

typedef struct{
	unsigned int cnt;
	StructMap stMap[16];
}StructBoInfo;

typedef struct{
	StructBoInfo info[8];//DO1-8
}StructBoMap;

typedef struct{
	unsigned int pos;
	unsigned int group;
	unsigned int module;
	unsigned char trueValue;
	unsigned char falseValue;
	unsigned int hasUTC;
	unsigned int utcPos;
}structBOMap;

typedef struct{
	unsigned int cnt;
	structBOMap stMap[16];
}structGSOutInfo;

typedef struct{
	structGSOutInfo info[2][32];
}structGSOutModule;

typedef struct{
	structGSOutModule boMd[BIO_MODULE_MAX];
}structGSOutMap;

//GOOSESUBDATA,GOOSE订阅
typedef struct
{
	int nPos;           //倒数字节位置
	int nDBIIndex;      //开入序号，��?0开��?
	unsigned long nTrueValue;     //True 的比较��?
	unsigned long nFalseValue;    //False 的比较��?
}GooseMapChanelValue;

#define GOOSE_MAP_MAX					64
#define GOCB_LEN_MAX					256
#define GOID_LEN_MAX					GOCB_LEN_MAX
#define DATASET_LEN_MAX					GOCB_LEN_MAX

typedef struct{
	unsigned int pos;
	unsigned int mdPos;
	unsigned int index;
	unsigned int trueValue;
	unsigned int falseValue;
}structGooseSubValue;

typedef struct
{
	int CRC;
	int paramAdvance;
	int gocbLen;
	char GOCB[GOCB_LEN_MAX];
	int goidLen;
	char GOID[GOID_LEN_MAX];
	int dataSetLen;
	char dataSet[DATASET_LEN_MAX];
	int testMode;
	int count;
	structGooseSubValue val[GOOSE_MAP_MAX];
}GooseSubItem;

typedef struct
{
	unsigned int nPort;//bit0-bit7 1 enabled 2 unenabled
	unsigned int ncount;
	GooseSubItem gooseSub[16];
}GooseSubData;


//FT3SUBDATA,ft3订阅
typedef struct{
	int nBiSwitch;//映射的开关量，开入n
	int nPos;//开关量字节位置
	int nBitLen;//映射bit长度 1bit or 2bit
	int nBitPos;//映射的bit起始
	int nBitTrueValue;//BitTrueValue; 两bit ��? 00 01 10 11 ��?1bit ��?0 ��? 1
	int nBitFalseValue;//同上，false ��?
}Ft3SubChanel;

typedef struct{
	int nPort;//映射端口
	int nLen;//ft3映射长度
	Ft3SubChanel ft3Chanel[GOOSESUB_MAX];
}Ft3SubItem;

typedef struct{
	int nLen;
	Ft3SubItem ft3Item[4];
}Ft3SubData;



class CIEC61850CfgMngr:public QObject
{
private:
	explicit CIEC61850CfgMngr(QObject *parent = 0);
	~CIEC61850CfgMngr();
	static long g_nIEC61850CfgMngrRef;

public:
	static void Create();
	static void Release();

	static CIEC61850CfgMngr *g_pIEC61850CfgMngr;

public:
	void Init();
	void InitChanelMap();
	void InitSv();
	void InitPara();
	void SetPara();
	void GseChange(int chan,QString value);
	void SetTestMode(bool Mode);
	void InitBoMap();
	void InitGooseSub();
	void InitFt3Sub();
	void AddLongStrToByte(QString m_Value, QByteArray &m_ByteArray, int m_Length);
	void AddASN1StrToByte(QString m_Value, QByteArray &m_ByteArray, unsigned short m_Flag, int m_Length);
	void GetASDUData(QByteArray & m_ASDUDataArray, QByteArray & m_ChanListData, QStringList & m_ChanFactorList, int & m_OffsetChanValue, int m_ChanNum);
	void Create92Packet(tmt_sv_92 &m_92Struct,QByteArray & m_ResultArray,QString m_SavePath, int m_pcapmode=0);

	void ProcessGooseDataSetList(QByteArray& oAr);
	void CreateGooseDataSetList(QByteArray& oAr, ChanelInfo &chan,char timequality);
	void CreateGooseData(QByteArray& oAr, tmt_goose &t_GOOSE);
	void FiberClose();
	void FiberOpen();
	void SetGooseValue(tmt_StateParas &oStateParas,int nIndex,drv_state *pDrvState);
	int nSample;
	QVector<tmt_sv_92> data_92;
	QVector<tmt_goose> data_gse;
	QMap<QString,int> m_ChanMapID;
	SendConfSV *confsv;
	SendConfGSE *confgse;
	CIecCfgDatasMngr *m_oIecCfgDatasMngr;
private:
	GooseSubData *gsesub;
	FiberConf *fiber;
	StructIECConfig *m_pIECConfig;
	Ft3SubData *ft3sub;
	structGSOutMap *stMaps;
	StructGSTest *stGseTest;
	GooseChangedItems *goosechange;
	IECFiberInfo *m_pIECFiberInfo;
};

#endif // IEC61850CONFIG_H
