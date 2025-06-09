
#ifndef _MISC_H_
#define _MISC_H_

#include <stdio.h>
#include "pqdexamp.h"
#include "Markup.h"
#include "pqdiftool.h"

#define PQDIF_MAX_DEFINE_CHANNEL_NUM                         2048    //zhouhj 20201201 之前默认是1024 不够用  增加此宏定义

BOOL parseOneRecord
(
        CWSerializeBuff &oBufOriginal, //FILE *                  pfiOriginal,        //  Input file (input)
        CWSerializeBuff &oBufScratch, //FILE *                  pfiScratch,         //  Scratch file (modified)
        c_record_mainheader&    hdrRecord,          //  Record header (output)
        UINT4                   styleCompression,   //  Compression style (input)
        UINT4                   algCompression,     //  Compression algorithm (input)
        bool                    bHeaderOnly
);

extern BOOL decompBlock
( 
        CWSerializeBuff &oBufCompressed,//FILE *      pfiCompressed, 
        long        pos, 
        long        size,
        CWSerializeBuff &oBufDecompressed, //FILE *      pfiDecompressed, 
        long        posInDecomp, 
        SIZE4&      sizeDecompressed,
        UINT4       algCompression,
        UINT4&      checksum
);

extern BOOL parseCollection
( 
        CWSerializeBuff &oBufOriginal,//FILE *  pfiOriginal,
        long    posStartOfRecord,
        int     level,
        SIZE4   sizeOfRecord
);
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/

// 定义用于记录每个数据源通道中，time,min,max,avg,cp95,val是否存在，若存在，都在第几个series中
class CStoreSeriesInfo_Node : public CBaseObject
{
public:
	CStoreSeriesInfo_Node()
	{
		stdDataSrcIndex = -1;
		seriesNum = 0;
		indexTime = -1;
		indexMin = -1;
		indexMax = -1;
		indexAvg = -1;
		indexCp95 = -1;
		indexOtherVal = -1;
		idQuantityMeasured = -1;
		typeOfDataSrc = CStoreSeriesInfo_Node::None_TypeOfDatasrc;
	};
	~CStoreSeriesInfo_Node()
	{
	};
public:
	int stdDataSrcIndex; // 在标准数据源通道中的序列号
	CString channelName; // 在标准数据源通道中的名称
	UINT4       idQuantityMeasured; // 

public:
	int seriesNum;
public:
	int indexTime;
	int indexOtherVal;
	int indexMin;
	int indexMax;
	int indexAvg;
	int indexCp95;
public:
	// None_TypeOfDatasrc 此通道数据无效; 成立条件: indexXXX = -1,seriesNum=0
	// Stat_TypeOfDataSrc 用于统计数据的通道; 成立条件: seriesNum>=2,indexTime有效，index<Min,Max,Avg,Cp95>至少一个有效
	// Wave_TypeOfDatasrc 用于记录事件或者波形的通道; 成立条件: seriesNum=2,indextime有效,indexOtherVal有效
	enum eTypeOfDataSrc { None_TypeOfDatasrc, Stat_TypeOfDataSrc, Wave_TypeOfDatasrc };
	enum eTypeOfDataSrc typeOfDataSrc;
};

class CStoreSeriesInfo : public CBaseList
{
public:
	CStoreSeriesInfo(){};
	~CStoreSeriesInfo(){};

public:
	CStoreSeriesInfo_Node* AddNode()
	{
		CStoreSeriesInfo_Node *p = new CStoreSeriesInfo_Node();
		AddTail(p);
		return p;
	}

	CStoreSeriesInfo_Node* GetNode(long nIndex)
	{
		return (CStoreSeriesInfo_Node*)GetAtIndex (nIndex );
	}
	CStoreSeriesInfo_Node* FindNode(long idxChannelDefn)
	{
		CStoreSeriesInfo_Node *p = NULL;
		CStoreSeriesInfo_Node *pFind = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			p = (CStoreSeriesInfo_Node*)GetNext(pos);

			if (p->stdDataSrcIndex == idxChannelDefn)
			{
				pFind = p;
				break;
			}
		}
		
		return pFind;
	}
};

extern CStoreSeriesInfo g_StoreSeriesInfo;

void init_Store_Sereis_Info( datasource_example &stdDatasource, CStoreSeriesInfo &storeSeriesInfo );

/***************************************************************************/
extern int  g_fileNum;
extern int  g_obserNum;

extern time_t CPQDTimeToLocalTime ( TIMESTAMPPQDIF *pqdtime );

#define  MAP_LEN (2048/*1024*/)
extern int MapForDataSrc[2][MAP_LEN];
int get_DataSrc_TestIndex_From_StdIndex( int stdIndex );
int get_DataSrc_StdIndex_From_TestIndex( int testIndex );
extern int testFileReservedChannel[PQDIF_MAX_DEFINE_CHANNEL_NUM/*1024*/];
extern int revTotalNum;

void doSomeInit();

int parseStdXml(const CString &stdxml);

int verifyByStdXml();
int VerifyStdXmlOfRepeat();

int parseFile( CWSerializeBuff &oBuffer);

void queryData_ByChannel( UINT4 queryChannelIdx, CBaseList *pListDest );

void queryData_ByTimestamp( time_t qrtime );

/* endOfRecord() */
void addContainerToTotalData();
void addDataSourceToTotalData();
void addMonitorSettingToTotalData();
void addObservationToTotalData();

void freeDataSource( datasource_example * record );
void freeMonitorSettings( monitorsettings_example * record );
void freeObservation( observation_example * record );

void freeDataInOneFile();

void freePqTotalData();

void freeStdFormatData();

void freeQueryData();

#endif // _MISC_H_






