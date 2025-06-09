#include "stdafx.h"

#include "misc.h"
#include "pqdexamp.h"
#include "pqread.h"
#include "pqdif_id.h"
#include "..\zlib-1.2.8\zlib.h"
#include <float.h>
#include "validate.h"
#include "pqdif_ph.h"
#include "names.h"
#include "pqdifr.h"

CStoreSeriesInfo g_StoreSeriesInfo;

int  g_fileNum = 0;
int  g_obserNum = 0;

long    g_verifyByStdXml = 0;


/* 
保存 <标准数据源通道序列号> -> <被解析文件数据源通道序列号> 的映射关系
定义这个数组的原因在于：标准xml文件的数据源定义顺序可能和被解析文件的定义顺序不一致
[0][MAP_LEN] 保存标准xml文件通道的序列号
[1][MAP_LEN] 保存被解析文件的序列号 
*/
int MapForDataSrc[2][MAP_LEN]; 

int testFileReservedChannel[PQDIF_MAX_DEFINE_CHANNEL_NUM];//1024
int revTotalNum = 0;

int get_DataSrc_TestIndex_From_StdIndex( int stdIndex )
{
	int i = 0;
	int mapcnt = 0;
	int testIndex;

	for (mapcnt = 0; mapcnt < MAP_LEN; ++mapcnt)
	{
		if(MapForDataSrc[0][mapcnt] == -1)
		{
			return -1; // 越限,没有对应关系
		}

		if(MapForDataSrc[0][mapcnt] == stdIndex)
		{
			testIndex = MapForDataSrc[1][mapcnt]; // 被解析文件数据源通道序列号 
			if (testIndex != -1)
			{
				for (i = 0; i < revTotalNum; ++i)
				{
					if (testIndex == testFileReservedChannel[i])
					{
						return -1;
					}
				}
				return testIndex; 
			}
		}
	}

	return -1;
}

int get_DataSrc_StdIndex_From_TestIndex( int testIndex )
{
	int i = 0;
	int mapcnt = 0;
	int stdIndex = -1;

	for (i = 0; i < revTotalNum; ++i)
	{
		if (testIndex == testFileReservedChannel[i])
		{
			return -1;
		}
	}

	for (mapcnt = 0; mapcnt < MAP_LEN; ++mapcnt)
	{
		if(MapForDataSrc[1][mapcnt] == -1)
		{
			return -1; // 越限
		}

		if(MapForDataSrc[1][mapcnt] == testIndex)
		{
			stdIndex = MapForDataSrc[0][mapcnt]; // 标准通道序列号
			if (stdIndex != -1)
			{
				return stdIndex; 
			}
		}
	}

	return -1;
}

// used @ pqread.cpp
void init_Store_Sereis_Info( datasource_example &stdDatasource, CStoreSeriesInfo &storeSeriesInfo )
{
	int i;
	bool revflag;
	int nodeindex = 0;

	storeSeriesInfo.DeleteAll();

	INT4 channelTotalNum = stdDatasource.nChannel;
	for( INT4 channelIndex = 0; channelIndex < channelTotalNum; ++channelIndex )
	{
		// 排除多余的通道
		revflag = false;
		for (i = 0; i < revTotalNum; ++i)
		{
			if (channelIndex == testFileReservedChannel[i])
			{
				revflag = true;
				break;
			}
		}

		if (revflag == true)
		{
			continue;
		}

		channel_defn *pchannel = stdDatasource.Get_channel( channelIndex );

		storeSeriesInfo.AddNode(); // 增加一个节点
		CStoreSeriesInfo_Node *pInfoNode = storeSeriesInfo.GetNode( nodeindex ); // 取末尾
		++nodeindex; /* */
		pInfoNode->stdDataSrcIndex = get_DataSrc_StdIndex_From_TestIndex( channelIndex ); // 序列号
		pInfoNode->channelName = pchannel->szChannelName; // 名称
		pInfoNode->idQuantityMeasured = pchannel->idQuantityMeasured; // 名称

		INT4 seriesTotalNum = pchannel->nSeries;
		pInfoNode->seriesNum = seriesTotalNum;
		for( INT4 seriesIndex = 0; seriesIndex < seriesTotalNum; ++seriesIndex )
		{
			series_defn *pseries = pchannel->Get_series( seriesIndex );

			if ( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_TIME ) )
			{
				pInfoNode->indexTime = seriesIndex;
			}
			else if (( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_VAL ) )||( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_FLUKE ) ))//增加用于FlukePQDIF   zhouhj20210119
			{
				pInfoNode->indexOtherVal = seriesIndex;
			}
			else if ( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_MIN ) )
			{
				pInfoNode->indexMin = seriesIndex;
			}
			else if ( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_MAX ) )
			{
				pInfoNode->indexMax = seriesIndex;
			}
			else if ( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_AVG ) )
			{
				pInfoNode->indexAvg = seriesIndex;
			}
			else if ( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_P95 ) )
			{
				pInfoNode->indexCp95 = seriesIndex;
			}
		} // end of for(seriesIndex)

		// 判断数据源通道的类型
		// 无效的通道类型
		if( pInfoNode->seriesNum==0 
			&& pInfoNode->indexTime==-1 && pInfoNode->indexOtherVal==-1
			&& pInfoNode->indexMin==-1  && pInfoNode->indexMax==-1 
			&& pInfoNode->indexAvg==-1  && pInfoNode->indexCp95==-1 
		  )
		{
			pInfoNode->typeOfDataSrc = CStoreSeriesInfo_Node::None_TypeOfDatasrc;
		}
		// 统计数据的通道类型
		if( (pInfoNode->seriesNum>=2 && pInfoNode->indexTime>=0 && pInfoNode->indexOtherVal==-1)
			     && (pInfoNode->indexMax>=0 || pInfoNode->indexMin>=0 || pInfoNode->indexAvg>=0 || pInfoNode->indexCp95>=0) 
		  )
		{
			pInfoNode->typeOfDataSrc = CStoreSeriesInfo_Node::Stat_TypeOfDataSrc;
		}
		// 波形或者事件的通道类型
		if( (pInfoNode->seriesNum==2 && pInfoNode->indexTime>=0 && pInfoNode->indexOtherVal>=0)
			     && (pInfoNode->indexMax==-1 && pInfoNode->indexMin==-1 && pInfoNode->indexAvg==-1 && pInfoNode->indexCp95==-1)	
		  )
		{
			pInfoNode->typeOfDataSrc = CStoreSeriesInfo_Node::Wave_TypeOfDatasrc;
		}
	} // end of for(channelIndex)
}

void doSomeInit()
{
	g_verifyByStdXml = 0;//zhouhj 20201128 在重新导入标准文件后，需要重新校验格式
	g_fileNum = 0;
	g_obserNum = 0;

	freeStdFormatData();
	freePqTotalData();
	freeQueryData();
}

void queryData_ByTimestamp( time_t qrtime )
{
	g_queryTotalData.DeleteAll();
	g_queryTotalData.queryTime = qrtime;

	observation_example &observation = g_pqTotalData.observation;
	long observTotalNum = observation.nChannels;

	time_t minTimeVal = 9223372036854775807/*__int64最大值*/, maxTimeVal = 0;
	CTime tmCurr(qrtime);
	CTimeSpan ts(0, 0, 1, 40);
	CTime tmMin , tmMax;
	tmMax = tmCurr + ts;
	tmMin = tmCurr - ts;
	SYSTEMTIME systm1, systm2;
	tmMin.GetAsSystemTime(systm1);
	tmMax.GetAsSystemTime(systm2);
	minTimeVal = tmMin.GetTime();
	maxTimeVal = tmMax.GetTime();

	
	for( long indexObser = 0; indexObser < observTotalNum; ++indexObser )
	{
		channel_instance *pObserChannel = observation.Get_channel( indexObser );
		int stdIndex = pObserChannel->idxChannelDefn;
		CStoreSeriesInfo_Node *pNodeInfo = g_StoreSeriesInfo.FindNode( stdIndex );
	
		if (pNodeInfo == NULL)
		{
			continue;
		}
// 		if( stdIndex != pNodeInfo->stdDataSrcIndex )
// 		{
// 			continue;
// 		}

		if( (pNodeInfo->typeOfDataSrc == CStoreSeriesInfo_Node::Wave_TypeOfDatasrc) 
			|| (pNodeInfo->typeOfDataSrc == CStoreSeriesInfo_Node::None_TypeOfDatasrc) 
		  ) 
		{
			continue; // 波形事件不参与时间查询
		}
	
		int timeSeries = -1;
		timeSeries = pNodeInfo->indexTime;
		series_instance *pseries = pObserChannel->Get_series( timeSeries );
		SIZE4 valTotalNum = pseries->nTotalValues;
	
		if( valTotalNum <= 0 )
		{
			continue;
		}

		SIZE4 indexVal = 0;
		SIZE4 keyQueryIndex = -1;
		//time_t keyQueryTimestamp = 9223372036854775807/*__int64最大值*/;
		//time_t minTimeVal = 9223372036854775807/*__int64最大值*/, maxTimeVal = 0;

// 		if (valTotalNum <= 2)
// 		{
// 			continue;
// 		}

		if (pseries->paData == NULL)
		{
			continue;
		}
	
		for( indexVal = 1; indexVal < valTotalNum; indexVal++ )
		{
			time_t timeval = (time_t)pseries->paData[indexVal];
// 			CTime tm(timeval);
// 			SYSTEMTIME systm;
// 			tm.GetAsSystemTime(systm);

			if (minTimeVal <= timeval && timeval <= maxTimeVal)
			{
				keyQueryIndex = indexVal;
				break;
			}
// 			if( timeval < minTimeVal )
// 			{
// 				minTimeVal = timeval;
// 			}
// 			if( timeval > maxTimeVal )
// 			{
// 				maxTimeVal = timeval;
// 			}

// 			if( qrtime >= timeval )
// 			{
// 				if( timeval < keyQueryTimestamp )
// 				{
// 					keyQueryIndex = indexVal;
// 					keyQueryTimestamp = timeval;
// 				}
// 			}
		}
		if( /*(qrtime < minTimeVal) || (qrtime > maxTimeVal) || */(keyQueryIndex == -1) )
		{
			continue;
		}

		int minSeries = pNodeInfo->indexMin;
		int maxSeries = pNodeInfo->indexMax;
		int avgSeries = pNodeInfo->indexAvg;
		int cp95Series = pNodeInfo->indexCp95;
		
		STRUCT_QueryNodeData *pQueryNode = g_queryTotalData.AddNode();
// 		STRUCT_QueryNodeData *pQueryNode = (STRUCT_QueryNodeData *)g_queryTotalData.GetTail();
		pQueryNode->channelName = pNodeInfo->channelName;
		pQueryNode->idQuantityMeasured = pNodeInfo->idQuantityMeasured;
		pQueryNode->stdDataSrcIndex = pNodeInfo->stdDataSrcIndex;
		pQueryNode->freqVal = pObserChannel->channelFreq;
		
		if( minSeries >= 0 )
		{
			pQueryNode->minVal  = pObserChannel->GeSerialValue(minSeries, keyQueryIndex);//Get_series( minSeries )->paData[keyQueryIndex];
		}
	
		if( maxSeries >= 0 )
		{
			pQueryNode->maxVal  = pObserChannel->GeSerialValue(maxSeries, keyQueryIndex);//Get_series( maxSeries )->paData[keyQueryIndex];
		}
		
		if( avgSeries >= 0 )
		{
			pQueryNode->avgVal  = pObserChannel->GeSerialValue(avgSeries, keyQueryIndex);//Get_series( avgSeries )->paData[keyQueryIndex];
		}
		
		if( cp95Series >= 0 )
		{
			pQueryNode->cp95Val = pObserChannel->GeSerialValue(cp95Series, keyQueryIndex);//Get_series( cp95Series)->paData[keyQueryIndex];
		}
	} 
}

void queryData_ByChannel( UINT4 stdIndex, CBaseList *pListDest )
{
	observation_example *pObservation= &g_pqTotalData.observation;

	long nChannelIndex = 0;
	POS pos = pObservation->GetHeadPosition();

	while (pos != NULL)
	{
		channel_instance *paci = (channel_instance *)pObservation->GetNext(pos);

		if (nChannelIndex == stdIndex)//zhouhj 20201127 按通道查询时，g_pqTotalData.observation链表中对应的总数，对应界面显示的总通道数，如果以paci->idxChannelDefn为基准，可能查询不到
//		if (paci->idxChannelDefn == stdIndex)
		{
			pListDest->AddTail(paci);
		}

		nChannelIndex++;
	}
}

void addContainerToTotalData()
{
	if( g_fileNum == 1 ) 
	{
		memcpy( &(g_pqTotalData.container), &s_container, sizeof(container_example) );
	}
}

void addDataSourceToTotalData()
{
	if( g_fileNum == 1 ) 
	{
		g_pqTotalData.datasource.DeleteAll();
		s_datasource.Copy( &g_pqTotalData.datasource ); 
	}
}

void addMonitorSettingToTotalData()
{
	if( g_fileNum == 1 ) 
	{
		g_pqTotalData.monitorsetting.DeleteAll();
		s_monsett.Copy( &g_pqTotalData.monitorsetting );
	}
}

// 将被测试文件中obsevation.channel_instance 中idxChannelDefn 全部换成 标准文件中的index 
static void convert_TestIndex_To_StdIndex_InTestFile()
{
	POS pos = s_observation.GetHeadPosition();
	while( pos != NULL )
	{
		channel_instance *paci = (channel_instance *)s_observation.GetNext( pos );
		int testIndex = paci->idxChannelDefn;
		int stdIndex = get_DataSrc_StdIndex_From_TestIndex( testIndex );
		// stdIndex可能返回-1，因为是多余的通道
		paci->idxChannelDefn = stdIndex;
	}
}

void addObservationToTotalData()
{
	try
	{

	}
	catch (...)
	{
		
	}
	
	int i;
	bool revflag;
	//int keyindex;
	int timeSeries = 0;

	// 转换index
	convert_TestIndex_To_StdIndex_InTestFile();
	
	// 用开始时间和时间间隔组成绝对时间
	long observTotalNum = s_observation.nChannels;
	for( long observIndex = 0; observIndex < observTotalNum; ++observIndex )
	{
		channel_instance *paci = s_observation.Get_channel( observIndex );
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("observIndex=%d"), observIndex);

		if (paci->idxChannelDefn == -1)
		{
			continue;
		}

		//CStoreSeriesInfo_Node 
		//keyindex = 0;
		POS posNode = g_StoreSeriesInfo.GetHeadPosition();
		CStoreSeriesInfo_Node *pInfoNode = NULL;

		while (posNode != NULL)
		{
			CStoreSeriesInfo_Node *pnode = (CStoreSeriesInfo_Node *)g_StoreSeriesInfo.GetNext(posNode);

			if (paci->idxChannelDefn == pnode->stdDataSrcIndex)
			{
				pInfoNode = pnode;
				break;
			}

			//++keyindex;
		}

		//CStoreSeriesInfo_Node *pInfoNode = g_StoreSeriesInfo.GetNode( keyindex );

		if (pInfoNode == NULL)
		{
			continue;;
		}

		if( pInfoNode->typeOfDataSrc != CStoreSeriesInfo_Node::None_TypeOfDatasrc )
		{
			timeSeries = pInfoNode->indexTime;
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("timeSeries=%d"), timeSeries);
			paci->InitTmtimeSeries( timeSeries, s_observation.tsStart );
		}
		
		if (g_b_channel_instance_error == 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s【idxChannel=%d】 Error"),pInfoNode->channelName, paci->idxChannelDefn);
		}
	}

	// 加入total数据中
	POS pos = s_observation.GetHeadPosition();

	while( pos != NULL )
	{
		channel_instance *pSrc = (channel_instance *)s_observation.GetNext(pos);

		if (pSrc->idxChannelDefn == -1)
		{
			continue; // 如果是多余的通道则不加入总体数据中
		}

		g_pqTotalData.observation.AppendChannelDatas(pSrc); //将读取的数据添加到g_pqTotalData.observation中
	}

	// 每次加入新的observation record，都重新计算通道数量
// 	pos = g_pqTotalData.observation.GetHeadPosition();
// 	size_t channel_instance_num = 0;
// 	while ( pos != NULL )
// 	{
// 		++channel_instance_num;
// 		g_pqTotalData.observation.GetNext( pos );
// 	}
	g_pqTotalData.observation.nChannels = g_pqTotalData.observation.GetCount(); 
}

void freeDataSource( datasource_example * record )
{
	record->DeleteAll();
}

void freeMonitorSettings( monitorsettings_example * record )
{
	record->DeleteAll();
} 

void freeObservation( observation_example * record )
{
	record->DeleteAll();
}

void freeDataInOneFile()
{
	freeDataSource( &s_datasource );
	freeMonitorSettings ( &s_monsett );
	/* s_observation 释放在endOfRecord()函数中 */
	s_container.Init();
	s_datasource.Init();
	s_datasource.DeleteAll();
	s_monsett.Init();
	s_monsett.DeleteAll();
}

void freePqTotalData()
{
	g_pqTotalData.datasource.DeleteAll();
	g_pqTotalData.monitorsetting.DeleteAll();
	g_pqTotalData.observation.DeleteAll();
}

void freeStdFormatData()
{
	g_stdFormat.datasource.DeleteAll();
}

void freeQueryData()
{
	g_queryTotalData.DeleteAll();
}

int parseStdXml(const CString &stdxml)
{
	CMarkup xml;
	bool flag;

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "标准XML文件开始导入" );

	flag = xml.Load(stdxml);

	if ( ! flag )
	{
		// CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "标准XML文件加载失败" );
		return -1;
	}

	xml.ResetPos();  // 定位到根节点<pqdif>  
	flag = xml.FindElem( TEXT("pqdif") );
	if ( ! flag )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "标准XML文件中无法定位标签<pqdif>" );
		return -1;
	}
	xml.IntoElem();   //进入<pqdif>

	flag = xml.FindElem ( TEXT("tagRecDataSource") );
	if ( ! flag )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "标准XML文件中无法定位标签<tagRecDataSource>" );
		return -1;
	}
	xml.IntoElem(); // 进入<tagRecDataSource>

	flag = xml.FindElem ( TEXT("tagChannelDefns") );
	if ( ! flag )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "标准XML文件中无法定位标签<tagChannelDefns>" );
		return -1;
	}
	xml.IntoElem(); // 进入<tagChannelDefns>

	size_t idxChannel = 0; 
	g_stdFormat.datasource.strStdFile = stdxml;

	while ( xml.FindElem( _T("tagOneChannelDefn") ) )
	{
		xml.IntoElem();   //进入<tagOneChannelDefn></tagOneChannelDefn>

		++idxChannel;
		g_stdFormat.datasource.nChannel = idxChannel;
		channel_defn *p_channel_defn = g_stdFormat.datasource.add();

		// 通道名称
		flag = xml.FindElem( TEXT("tagChannelName") );

		if ( flag )
		{
			p_channel_defn->szChannelName = xml.GetData();
		}

		flag = xml.FindElem( TEXT("tagPhaseID") );

		if ( flag )
		{
			//CString cstrName = xml.GetData();
			p_channel_defn->idPhase = get_TagPhaseID_From_Str( xml.GetData() );
			//printf ("%s    ", cstrName);
		}

		//flag = xml.FindElem ( TEXT("tagQuantityTypeID") );
		//if ( flag )
		//{
		//	CString cstrName = xml.GetData();
		//	p_channel_defn->idQuantityType = get_tagQuantityTypeID_FromStr ( cstrName );
		//}

		flag = xml.FindElem( TEXT("tagQuantityMeasuredID") );
		if ( flag )
		{
			CString cstrName = xml.GetData();
			p_channel_defn->idQuantityMeasured = get_TagQuantityMeasuredID_From_Str( cstrName );
			//printf ("%s \n", cstrName);
		}

		flag = xml.FindElem( TEXT("tagSeriesDefns") );
		if ( ! flag )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "标准XML文件中无法定位标签<tagSeriesDefn>" );
		    return -1;
		}
		xml.IntoElem(); // 进入<tagSeriesDefns>

		size_t idxSeries = 0;

		while ( xml.FindElem(_T("tagOneSeriesDefn")) )
		{
			xml.IntoElem(); // 进入<tagOneSeriesDefn>

			++idxSeries;
			p_channel_defn->nSeries = idxSeries;
			series_defn *p_series_defn = p_channel_defn->add();

			flag = xml.FindElem ( TEXT("tagValueTypeID") );
			if ( flag )
			{
				CString cstrName = xml.GetData();
				p_series_defn->idValueType = get_TagValueTypeID_From_Str ( cstrName );
			}

			flag = xml.FindElem ( TEXT("tagQuantityUnitsID") ); 
			if ( flag )
			{
				CString cstrName = xml.GetData();
				p_series_defn->idQuantityUnits = get_TagQuantityUnitsID_From_Str( cstrName );
			}

			flag = xml.FindElem ( TEXT("tagQuantityCharacteristicID") );
			
			if ( flag )
			{
				CString cstrName = xml.GetData();
				p_series_defn->idCharacteristicType = get_TagQuantityCharacteristicID_From_Str( cstrName );
				//printf ("%s \n", cstrName);
			}

			//flag = xml.FindElem ( TEXT("tagStorageMethodID") );
			//if ( flag )
			//{
			//	CString cstrName = xml.GetData();
			//	p_series_defn->idMethod = get_tagStorageMethodID_FromStr( cstrName );
			//}

			//flag = xml.FindElem ( TEXT("tagHintGreekPrefixID") );
			//if ( flag )
			//{
			//	CString cstrName = xml.GetData();
			//	p_series_defn->idGreekPrefix = get_tagHintGreekPrefixID_FromStr ( cstrName );
			//}

			xml.OutOfElem();  //跳出<tagOneSeriesDefn>
		}

		xml.OutOfElem();  //跳出<tagSeriesDefns>
		xml.OutOfElem();  //跳出<tagOneChannelDefn>
	}

	xml.OutOfElem();  //跳出<tagChannelDefns>
	xml.OutOfElem();  //跳出<tagRecDataSource>
	xml.OutOfElem();  //跳出<pqdif>

	return 0;
}

static int is_series_defn_same(series_defn *p_series_defn1, series_defn *p_series_defn2)
{
	if (memcmp(p_series_defn1, p_series_defn2, sizeof(series_defn)) == 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
// 	if ( p_series_defn1->idValueType != p_series_defn2->idValueType ) // 测量单位
// 	{
// 		return -1;
// 	}
// 
// 	if ( p_series_defn1->idQuantityUnits != p_series_defn2->idQuantityUnits ) // 测量单位
// 	{
// 		return -1;
// 	}
// 
// 	if ( ! PQDIF_IsEqualGUID ( p_series_defn1->idCharacteristicType, p_series_defn2->idCharacteristicType ) ) // 值类型
// 	{
// 		return -1;
// 	}
// 
// 	return 1;
}


static int is_series_defn_same2(series_defn *p_series_defn1, series_defn *p_series_defn2)
{
	if ( p_series_defn1->idValueType != p_series_defn2->idValueType ) // 值类型
	{
		return -1;
	}

	if ( p_series_defn1->idQuantityUnits != p_series_defn2->idQuantityUnits ) // 测量单位
	{
		return -1;
	}

	if ( ! PQDIF_IsEqualGUID ( p_series_defn1->idCharacteristicType, p_series_defn2->idCharacteristicType ) ) // 值类型
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("未定义通道中存在tagOneSeriesDefn的值类型定义错误;"));
		return -1;
	}

	return 1;
}

static series_defn* find_series_defn(channel_defn *p_channel_defn, series_defn *p_series_defn)
{
	series_defn *p = NULL;
	series_defn *pFind = NULL;

	for ( int j = 0; j < p_channel_defn->nSeries; ++j )
	{
		p = p_channel_defn->Get_series(j);

		if (is_series_defn_same2(p, p_series_defn) > 0)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

static series_defn* find_series_defn2(channel_defn *p_channel_defn, GUID &idValueType)
{
	series_defn *p = NULL;
	series_defn *pFind = NULL;

	for ( int j = 0; j < p_channel_defn->nSeries; ++j )
	{
		p = p_channel_defn->Get_series(j);

		if (p->idValueType == idValueType)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

static int is_series_defn_exist(channel_defn *p_channel_defn, series_defn *p_series_defn)
{
	series_defn *p = NULL;
	series_defn *pFind = NULL;

	for ( int j = 0; j < p_channel_defn->nSeries; ++j )
	{
		p = p_channel_defn->Get_series(j);

		if ( p->idQuantityUnits != p_series_defn->idQuantityUnits ) // 测量单位
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "数据源通道(序号%d 名称%s)的子通道(序号%d)tagQuantityUnitsID错误", i, pTest->szChannelName, j);
			continue;
		}

		if ( ! PQDIF_IsEqualGUID ( p->idCharacteristicType, p_series_defn->idCharacteristicType ) ) // 值类型
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "数据源通道(序号%d 名称%s)的子通道(序号%d)tagQuantityCharacteristicID错误", i, pTest->szChannelName, j );
			continue;
		}

		pFind = p;
		break;
	}

	if (pFind == NULL)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

static int isDataSrcSame(channel_defn *pTest, channel_defn *pStd, BOOL bOnllyHasStd)
{
	if (pTest->szChannelName != pStd->szChannelName)
	{
		return -1;
	}

	if (pStd->szChannelName.Find(_T("DVC A"))>=0)//调试使用zhouhj
	{
		bOnllyHasStd = 1;
	}

	if ( pTest->idPhase != pStd->idPhase ) // 相位
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "数据源通道(序号%d 名称%s)的tagPhaseID错误", i, pTest->szChannelName);
		return -1;
	}
	if ( pTest->idQuantityMeasured != pStd->idQuantityMeasured ) // 测量类型
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "PQDIF文件中，数据源通道(序号%d 名称%s)的tagQuantityMeasuredID错误", i, pTest->szChannelName );
		return -1;
	}

// 	if (!bOnllyHasStd)
// 	{
// 		if ( pTest->nSeries != pStd->nSeries ) // 子通道数量
// 		{
// 			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "数据源通道(序号%d 名称%s)的子通道数量错误");
// 			return -1;
// 		}
// 	}

	series_defn *pSStd = NULL, *p = NULL;

	for ( int j = 0; j < pStd->nSeries; ++j )
	{
		pSStd = pStd->Get_series(j);

		p = find_series_defn(pTest, pSStd);
		//p = pTest->Get_series(j);

		if (p == NULL)
		{
			return -1;
		}

// 		if ( pSStd->idQuantityUnits != p->idQuantityUnits ) // 测量单位
// 		{
// 			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "数据源通道(序号%d 名称%s)的子通道(序号%d)tagQuantityUnitsID错误", i, pTest->szChannelName, j);
// 			return -1;
// 		}
// 
// 		if ( ! PQDIF_IsEqualGUID ( pSStd->idCharacteristicType, p->idCharacteristicType ) ) // 值类型
// 		{
// 			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "数据源通道(序号%d 名称%s)的子通道(序号%d)tagQuantityCharacteristicID错误", i, pTest->szChannelName, j );
// 			return -1;
// 		}
	}
	
	return 1;
}

// datasource的定义顺序可以不一致 
int verifyByStdXml()
{
	if (g_verifyByStdXml == 1)
	{
		return 1;
	}

	revTotalNum = 0;//zhouhj 20201128 初始化该值，否则打开更换规则后，解析pqdif文件内容不能正常存入
	g_verifyByStdXml = 1;
	int i, j, mapcnt = 0;
	BOOL channelStatus[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // 某一通道已经被检测并通过的状态数组
	ULONG channelPoint[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // 某一通道已经被检测并通过的状态数组
	memset(channelStatus, 0, PQDIF_MAX_DEFINE_CHANNEL_NUM*sizeof(BOOL)); // default to false
	memset(channelPoint, 0, PQDIF_MAX_DEFINE_CHANNEL_NUM*sizeof(ULONG)); // default to false

	memset(MapForDataSrc, -1, sizeof(MapForDataSrc));
	memset(testFileReservedChannel, -1, sizeof(testFileReservedChannel));

	if ( g_stdFormat.datasource.nChannel == 0 )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "标准XML文件尚未被导入");
		goto fail1;
	}

	// 测试文件的通道可以多于标准文件，但一定要包括标准通道，多余的通道忽略不计
// 	if (s_datasource.nChannel < g_stdFormat.datasource.nChannel)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "### 错误：测试文件数据通道定义(通道数量%d)没有完全包含标准XML文件通道定义(通道数量%d)", 
// 			                                         s_datasource.nChannel, g_stdFormat.datasource.nChannel );
// 		goto fail1;
// 	}

	INT4 testChannelNum = s_datasource.nChannel;
	INT4 stdChannelNum = g_stdFormat.datasource.nChannel;
	channel_defn *p_channel_defn = NULL, *p_std_channel_defn = NULL;
	
	for (j = 0; j < stdChannelNum; ++j)
	{
		p_std_channel_defn = g_stdFormat.datasource.Get_channel(j);

// 		if (p_std_channel_defn->szChannelName == _T("I_RMS MAX NEUTRAL "))
// 		{
// 			j++;
// 			j--;
// 		}

		for (i = 0; i < testChannelNum; ++i)
		{
			p_channel_defn = s_datasource.Get_channel(i);

			//if (stricmp(p_channel_defn->szChannelName , p_std_channel_defn->szChannelName) == 0)
			//if (p_channel_defn->szChannelName == p_std_channel_defn->szChannelName )
			if ( isDataSrcSame( p_channel_defn, p_std_channel_defn , TRUE) > 0 )
			{
				channelPoint[j] = (ULONG)p_channel_defn;
				// 查找某一通道数据时，用户点击的是标准通道序列号，需要转换成被测试文件中的通道序列号
				MapForDataSrc[0][mapcnt] = j; // 标准通道
				MapForDataSrc[1][mapcnt] = i; // 被测试文件通道
				++mapcnt;

				//if ( isDataSrcSame( p_channel_defn, p_std_channel_defn , TRUE) > 0 ) // 为查找的通道不符合则继续向下查找
				{
					channelStatus[j] = true; // 数据通道定义一致，退出这一通道的循环，并继续查找下一通道
					break;
				}
			}
		}
	}

	BOOL flag = FALSE;
	for ( j = 0; j < stdChannelNum; ++j ) // 找出所有未定义的通道，并报错
	{
		p_std_channel_defn = g_stdFormat.datasource.Get_channel(j);
		BOOL bSame = TRUE;

		if (channelPoint[j] == 0)
		{
			flag = TRUE;
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "没有定义通道%d(%s)",(j+1), p_std_channel_defn->szChannelName);
			continue;
		}

		p_channel_defn = (channel_defn *)channelPoint[j];

		if (p_channel_defn->szChannelName != p_std_channel_defn->szChannelName )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "--------数据源通道(%d)名称(%s)与标准(%s)不一致", 
				s_datasource.FindIndex(p_channel_defn), p_channel_defn->szChannelName, p_std_channel_defn->szChannelName);
		}

		if ( channelStatus[j] == false ) 
		{
			flag = TRUE;
			CString errInfo, errInfo2;
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "***********************************************************");
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "数据源通道(%s)定义有错误", p_std_channel_defn->szChannelName);

			long seriesSize = 0, seriesIndex=0;


			if ( p_channel_defn->idPhase != p_std_channel_defn->idPhase ) // 相位
			{
				errInfo = get_Str_From_TagPhaseID( p_std_channel_defn->idPhase );
				errInfo2 = get_Str_From_TagPhaseID( p_channel_defn->idPhase );
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagPhaseID %s 与标准 %s 不一致", errInfo2, errInfo);
			}

			if ( p_channel_defn->idQuantityMeasured != p_std_channel_defn->idQuantityMeasured ) // 测量类型
			{
				errInfo = get_Str_From_TagQuantityMeasuredID( p_std_channel_defn->idQuantityMeasured );
				errInfo2 = get_Str_From_TagQuantityMeasuredID( p_channel_defn->idQuantityMeasured );
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityMeasuredID %s 与标准 %s 不一致", errInfo2, errInfo);
			}

			seriesSize = p_std_channel_defn->nSeries;

			for( seriesIndex = 0; seriesIndex < seriesSize; ++seriesIndex )
			{
				series_defn *p1 = p_std_channel_defn->Get_series( seriesIndex );
				//series_defn *p2 = p_channel_defn->Get_series( seriesIndex );
				series_defn *p2 = find_series_defn2(p_channel_defn, p1->idValueType);
				
				if (p2 == NULL)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "子通道(%d)没有定义", seriesIndex+1);

					errInfo = get_Str_From_TagValueTypeID( p1->idValueType );
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagValueTypeID %s", errInfo);

					errInfo = get_Str_From_TagQuantityUnitsID( p1->idQuantityUnits );
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityUnitsID %s", errInfo);

					errInfo = get_Str_From_TagQuantityCharacteristicID( p1->idCharacteristicType );
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityCharacteristicID %s", errInfo);
					bSame = FALSE;
				}
				else
				{
					if (is_series_defn_same2(p1, p2) == -1)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "子通道(%d)定义与标准不一致", seriesIndex+1);

						if ( p1->idQuantityUnits != p2->idQuantityUnits ) // 测量单位
						{
							errInfo = get_Str_From_TagQuantityUnitsID( p1->idQuantityUnits );
							errInfo2 = get_Str_From_TagQuantityUnitsID( p2->idQuantityUnits );
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityUnitsID %s 与标准 %s 不一致",errInfo2, errInfo);
						}

// 						if ( p1->idMethod != p2->idMethod )
// 						{
// 							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagStorageMethodID %d 与标准 %d 不一致",p1->idMethod, p2->idMethod);
// 						}

						if ( p1->idGreekPrefix != p2->idGreekPrefix )
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagHintGreekPrefixID %d 与标准 %d 不一致",p1->idGreekPrefix, p2->idGreekPrefix);
						}

						if ( ! PQDIF_IsEqualGUID ( p1->idCharacteristicType, p2->idCharacteristicType ) ) // 值类型
						{
							errInfo = get_Str_From_TagQuantityCharacteristicID( p1->idCharacteristicType );
							errInfo2 = get_Str_From_TagQuantityCharacteristicID( p2->idCharacteristicType );
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityCharacteristicID %s 与标准 %s 不一致",errInfo2, errInfo);
						}
						
						bSame = FALSE;
					}
				}

// 				if (!bSame)
// 				{
// 					if (p_std_channel_defn->nSeries != p_channel_defn->nSeries)
// 					{
// 						CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "子通道数量(%d)与标准（%d）不一致", p_channel_defn->nSeries, p_std_channel_defn->nSeries);
// 					}
// 				}

// 				if (is_series_defn_exist(p_channel_defn, p) == -1)
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "子通道(%d)没有定义", seriesIndex+1);
// 					errInfo = get_Str_From_TagQuantityUnitsID( p->idQuantityUnits );
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    测量单位 %s", errInfo);
// 					errInfo = get_Str_From_TagQuantityCharacteristicID( p->idCharacteristicType );
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    值类型 %s", errInfo);
// 				}
			}
// 
// 
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "数据源通道(%s)正确定义如下所示：", p_std_channel_defn->szChannelName );
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "***********************************************************");
// 			errInfo = get_Str_From_TagPhaseID( p_std_channel_defn->idPhase );
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "相位 %s", errInfo);
// 			errInfo = get_Str_From_TagQuantityMeasuredID( p_std_channel_defn->idQuantityMeasured );
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "测量类型 %s", errInfo);
// 			seriesSize = p_std_channel_defn->nSeries;
// 			for( seriesIndex = 0; seriesIndex < seriesSize; ++seriesIndex )
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "子通道(%d)", seriesIndex+1);
// 				errInfo = get_Str_From_TagQuantityUnitsID( p_std_channel_defn->Get_series( seriesIndex )->idQuantityUnits );
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    测量单位 %s", errInfo);
// 				errInfo = get_Str_From_TagQuantityCharacteristicID( p_std_channel_defn->Get_series( seriesIndex )->idCharacteristicType );
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    值类型 %s", errInfo);
// 			}
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "***********************************************************");
		}
	}
	if (flag == TRUE)
	{
		memset(MapForDataSrc, -1, sizeof(MapForDataSrc));
		goto fail1;
	}

	// 如果找到了所有的标准通道，再看看是否有范围之外的数据通道
	int tmp;
	for (i = 0; i < testChannelNum; ++i)
	{
		for (tmp = 0; tmp < mapcnt; ++tmp)
		{
			if (MapForDataSrc[1][tmp] == i)
			{
				break;
			}
		}
		if (tmp == mapcnt) // 多余的通道
		{
			testFileReservedChannel[revTotalNum] = i;
			++revTotalNum;
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "文件格式验证通过" );
	return 1;
fail1:
	return -1;
}

int VerifyStdXmlOfRepeat()//zhouhj 检测标准文件中的通道是否有重复
{
	int i, j, mapcnt = 0;
	BOOL channelStatus[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // 某一通道已经被检测并通过的状态数组
	ULONG channelPoint[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // 某一通道已经被检测并通过的状态数组
	memset(channelStatus, 0, PQDIF_MAX_DEFINE_CHANNEL_NUM*sizeof(BOOL)); // default to false
	memset(channelPoint, 0, PQDIF_MAX_DEFINE_CHANNEL_NUM*sizeof(ULONG)); // default to false

	memset(MapForDataSrc, -1, sizeof(MapForDataSrc));
	memset(testFileReservedChannel, -1, sizeof(testFileReservedChannel));

	INT4 stdChannelNum = g_stdFormat.datasource.nChannel;
	channel_defn *p_channel_defn = NULL, *p_std_channel_defn = NULL;
	INT4 iRet = 1;
	CStringArray asStrError;
	CString strTemp;
	
	for (j = 0; j < stdChannelNum; ++j)
	{
		p_std_channel_defn = g_stdFormat.datasource.Get_channel(j);

		for (i = j+1; i < stdChannelNum; ++i)
		{
			p_channel_defn = g_stdFormat.datasource.Get_channel(i);

#ifdef UNICODE
			CString strTmp1,strTmp2;
			strTmp1 = p_channel_defn->szChannelName;
			strTmp2 = p_std_channel_defn->szChannelName;
			if (strTmp1.MakeLower() == strTmp2.MakeLower())
#else
			if (stricmp(p_channel_defn->szChannelName , p_std_channel_defn->szChannelName) == 0)
#endif
			{
				strTemp.Format(_T("    通道(%d)名称(%s)与通道(%d)名称(%s)相同"), i+1,p_channel_defn->szChannelName, j+1, p_std_channel_defn->szChannelName);
				asStrError.Add(strTemp);
				iRet = -1;
			}
		}
	}

	if (iRet == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,   _T("++++++++++++标准文件错误++++++++++++++"));

		for (i=0; i<asStrError.GetSize(); i++)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,   "    %s", asStrError.GetAt(i) );
		}
		CLogPrint::LogString(XLOGLEVEL_TRACE,   _T("++++++++++++标准文件错误++++++++++++++") );
	}

	return iRet;
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/

//  Parse through all records in the file
int parseFile( CWSerializeBuff &oBuffer)//FILE *oBuffer )
{
	BOOL                status = FALSE;
    long                idxRecord;
    c_record_mainheader hdrRecord;
    UINT4               styleCompression = ID_COMP_STYLE_NONE;
    UINT4               algCompression = ID_COMP_ALG_NONE;

	CWSerializeBuff oBuffScratch;
	oBuffScratch.SetBufferLength(1024*1024*32);

    //  Read the first record
    oBuffer.ResetBufferPointer();// fseek( oBuffer, 0, SEEK_SET );
    status = parseOneRecord( oBuffer, oBuffScratch, hdrRecord, styleCompression, algCompression, false );
    if( status )
    {
        //  See if we need to do anything with decompression.
        Valid_GetCompressionInfo( styleCompression, algCompression ); /*此函数没有起任何作用*/
    }
	else
	{
		return FALSE;
	}

    //  Seek to the next record
    oBuffer.SeekTo(hdrRecord.linkNextRecord);

    //  Loop through the records
    //  NOTE:   There is currently no way to detect an infinite loop.
    //          If a .linkNextRecord refers to a record already read,
    //          the program will continue forever.
    for( idxRecord = 0; /* no stopping point */; idxRecord++ )
    {
        status = parseOneRecord( oBuffer, oBuffScratch, hdrRecord, styleCompression, algCompression, false );
        
		if( status == TRUE )
        {
            //  Was this the last record?
            if( hdrRecord.linkNextRecord == 0 )
            {
                //  This is how we find the end of the file.
                break;
            }
            //  Seek to the next record (absolute file reference)
            oBuffer.SeekTo(hdrRecord.linkNextRecord);//fseek( oBuffer, hdrRecord.linkNextRecord, SEEK_SET );
        }
        else
        {
              //Unexpected end of file...
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Error:******** Unexpected end of file; or found an invalid .linkNextRecord.\n" ); 
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Error:******** The end of the file should be marked by a .linkNextRecord of 0 (zero).\n" ); 
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "无法解析文件" ); 
            return FALSE;
        }
    }

    return TRUE;
}

BOOL parseOneRecord
(	
	CWSerializeBuff &oBufOriginal, //FILE *                  oBuffer,        //  Input file (input)
    CWSerializeBuff &oBufScratch, //FILE *                  pfiScratch,         //  Scratch file (modified)
    c_record_mainheader&    hdrRecord,          //  Record header (output)
    UINT4                   styleCompression,   //  Compression style (input)
    UINT4                   algCompression,     //  Compression algorithm (input)
    bool                    bHeaderOnly         //  parse header only
 )
{
    BOOL        status = FALSE;
    BOOL        accepted;
    size_t      countRead;
    long        pos;
    UINT4       checksumBlock;
    SIZE4       sizeDecompressed = 0;

    // 读取Record头部
    countRead = oBufOriginal.ReadBuffer( &hdrRecord, sizeof( hdrRecord ), 1);//, pfiOriginal );
    BOOL bEOF = oBufOriginal.IsEof();//feof( pfiOriginal ); 
	if (bEOF)
    { 
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "到达文件末尾，无法继续读取" );
        return FALSE;
    }

    if( countRead == 1 && !bEOF )
    {
        //  See where we are... (after the header; need the start of the body)
        pos = oBufOriginal.Tell();//ftell( pfiOriginal ); 

        //  Validate this record header
        if ( hdrRecord.sizeHeader != sizeof( hdrRecord ) )
        {
            //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error:Header record size invalid. Read %d, should be %d\n", hdrRecord.sizeHeader, sizeof(hdrRecord)); /* ERROR INFO */
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"错误：一个Record的Head数据长度错误");
            return FALSE;
        }
      
		if ( ! PQDIF_IsEqualGUID( hdrRecord.guidRecordSignature, guidRecordSignaturePQDIF ) )
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error:The GUID Signature for PQDIF is not same \n"); /* ERROR INFO 
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "错误：一个Record头部GUID签名错误");
			return FALSE;
		}

        if( ! bHeaderOnly )
        {
            acceptNewRecord( pos, hdrRecord.tagRecordType ); // 数据结构体清零初始化 
            accepted = acceptCollection( hdrRecord.tagRecordType, 0 ); // 根据level和tag动态申请数据空间
            
			if( accepted )
            {
				/* PQMD装置生成的pqdif文件采用的压缩 ID_COMP_STYLE_RECORDLEVEL ID_COMP_ALG_ZLIB */
                switch( styleCompression )
                {
                    case ID_COMP_STYLE_NONE: //  Start at level 0
						if( parseCollection( oBufOriginal, pos, 0, hdrRecord.sizeData ) == FALSE )
						{
							return FALSE;
						}
                        break;
                    case ID_COMP_STYLE_RECORDLEVEL:
                        /* Decompress the entire record into the scratch file. Checksum only calculated and compared compression used. Checksum is on the compressed data (the file image) */
                        decompBlock( oBufOriginal, pos, hdrRecord.sizeData, oBufScratch, 0, sizeDecompressed, algCompression, checksumBlock );
                        parseCollection( oBufScratch, 0, 0, sizeDecompressed );
                        break;
                }
                
                endOfCollection( 0 ); //  End of the record -- back to level 0
            } 
        }

		status = TRUE;

        //  Notify it that we're done with this record
        if (!bHeaderOnly)
		{
			/* 拷贝s_container s_datasource s_monsett s_observation 到 g_pqTotalData */
            if ( endOfRecord() < 0 ) 
			{
				status = FALSE;
			}
		}
        
    } // end of if( countRead == 1 && !bEOF )
    else
    {
        status = FALSE;
    }

    return status;
}

// Parse through all elements in this collection will recursively parse through any collections it finds.
BOOL parseCollection
( 
	CWSerializeBuff &oBuffer,  //FILE *  pfi,                  //  File which contains the record (input)
    long    posStartOfRecord,     //  record中body开始位置，这是固定不变的
    int     level,                //  Current level in the hierarchy (input)
    SIZE4   sizeOfRecord          //  record中body的大小
)
{
    INT4            idx;
    BOOL            accepted = FALSE;
    c_collection    collection; // SIZE4 count;
    c_vector        vector; // SIZE4 count;
    long            size;
    long            posThisElement; // 元素中数据的位置
    SIZE4           sizeVerify;
    size_t          countRead;
    char *          pdata;
    c_collection_element*  arrayElements;

    countRead = oBuffer.ReadBuffer( &collection, sizeof( collection ), 1);//, pfi ); 
    if (countRead != 1) 
	{
        return FALSE;
	}

    // if ((collection.count < 0L) || (collection.count > 100000L))
	if ((collection.count < 0L))
    {
        //CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "ERROR:  Parsing of this collection aborted.  Invalid collection size count: %lX (%ld)\n", collection.count);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "错误：一个Collection数量读取错误");
        return FALSE;
    }

    arrayElements = new c_collection_element[ collection.count ];
    countRead = oBuffer.ReadBuffer( arrayElements, sizeof( c_collection_element ), collection.count);//, pfi ); // 把level级别的collection_element全部读出来
  
	if (countRead != (size_t) collection.count)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Error:number of elements read (%d) in collection different from count (%d).\n", countRead, collection.count );
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "错误：文件中Element数量读取错误" );
		goto fail1;
    }

    for( idx = 0; idx < collection.count; idx++ )
    {
        if( ! arrayElements[ idx ].isEmbedded ) // 非内嵌数据
        {
            if( arrayElements[ idx ].link.linkElement >= sizeOfRecord )
            {
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Error:A relative position (.linkElement) is past the end of the record.\n" );
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "错误：文件中Element位置偏移错误" );
                goto fail1;
            }

			// 指针移动到实际数据位置
            posThisElement = posStartOfRecord + arrayElements[ idx ].link.linkElement;
            oBuffer.SeekTo(posThisElement);//fseek( pfi, posThisElement, SEEK_SET ); 
        }

        switch( arrayElements[ idx ].typeElement )
        {
            case ID_ELEMENT_TYPE_COLLECTION:
                accepted = acceptCollection( arrayElements[ idx ].tagElement, level + 1 );
                if( accepted )
                {
                    accepted = parseCollection( oBuffer, posStartOfRecord, level + 1, sizeOfRecord ); // 根据上面，pfi已经移动到level+1级别的collection的位置
                }
				else
				{
					goto fail1;
				}
                endOfCollection( level + 1 ); /* 核算出最终各通道的数量 */
                break;

            case ID_ELEMENT_TYPE_SCALAR:
                size = GetNumBytesOfType( arrayElements[ idx ].typePhysical ); // 获得数据类型长度

                if( arrayElements[ idx ].isEmbedded )
                {
                    pdata = (char *) arrayElements[ idx ].valueEmbedded; // char[8]
                }
                else
                {
                    sizeVerify = padSizeTo4Bytes( size ); 
                    if ( sizeVerify != arrayElements[ idx ].link.sizeElement )
                    {
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "link.sizeElement (%d) not equal to size of scalar padded to 4 byte multiple (%d).\n", arrayElements[ idx ].link.sizeElement, sizeVerify);
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "错误：Element数据大小非4字节对齐");
						goto fail1;
                    }

                    pdata = new char[ size ];
                    countRead = oBuffer.ReadBuffer( pdata, size, 1);//, pfi );
                }
				/* 填充数据 */
                accepted = acceptScalar( arrayElements[ idx ].tagElement, arrayElements[ idx ].typePhysical, (void *)pdata, level );
                if( ! arrayElements[ idx ].isEmbedded )
				{
                    delete [] pdata;
				}
                break;

            case ID_ELEMENT_TYPE_VECTOR:
                countRead = oBuffer.ReadBuffer( &vector, sizeof( vector ), 1);//, pfi );
                size = GetNumBytesOfType( arrayElements[ idx ].typePhysical );
                sizeVerify = padSizeTo4Bytes( sizeof( c_vector ) + ( size * vector.count ) );
                if ( sizeVerify != arrayElements[ idx ].link.sizeElement )
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "******** link.sizeElement (%d) not equal to size of vector padded to 4 byte multiple (%d).\n", arrayElements[ idx ].link.sizeElement, sizeVerify);
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "错误：Element数据大小非4字节对齐");
					goto fail1;
                }
                //  Alloc & read
                pdata = new char[ size * vector.count ];
                countRead = oBuffer.ReadBuffer( pdata, size, vector.count);//, pfi );
                if ( countRead != (size_t) vector.count )
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "******** number of bytes read (%d) for vector is not equal to vector.count (%d).\n", countRead, vector.count);
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "错误：Vector数量读取错误");
					delete[] pdata;
					goto fail1;
                }
                /* 填充数据 */
                accepted = acceptVector ( arrayElements[ idx ].tagElement, arrayElements[ idx ].typePhysical, &vector, (void *)pdata, level );
                delete[] pdata;
                break;
        } // end of switch
    } // end of for()
    
    delete [] arrayElements;
    return TRUE;
fail1:
	delete[] arrayElements;
	return FALSE;
}

//  Decompresses a block of data from one file into another file.
BOOL decompBlock
( 
        CWSerializeBuff &oBufCompressed, //FILE *      pfiCompressed,      //  File which contains the compressed block (input)
        long        pos,                //  Position of the compressed block (input)
        long        size,               //  Size of the compressed block (input)
        CWSerializeBuff &oBufDecompressed, //FILE *      pfiDecompressed,    //  File where the decompressed block will go (modified)
        long        posInDecomp,        //  Position where the block should be put (input)
        SIZE4&      sizeDecompressed,   //  Size of the block after decompressed (output)
        UINT4       algCompression,     //  Algorithm to be used for decompression (input)
        UINT4&      checksum            //  Checksum of compressed block (output)
)
{
            BOOL    status = TRUE;
    const   long    sizeInput = 4096;     //  Input buffer
    static  Bytef   bufferInput[ 4096 ];
    const   long    sizeOutput = 4096;    //  Output buffer
    static  Bytef   bufferOutput[ 4096 ];
            long    sizeLeft = size;
            long    sizeActual;
            BOOL    haveData;

    sizeDecompressed = 0;
    oBufCompressed.SeekTo(pos);//fseek( pfiCompressed, pos, SEEK_SET );
    oBufDecompressed.SeekTo(posInDecomp);//fseek( pfiDecompressed, posInDecomp, SEEK_SET );

    //  This is the only compression algorithm currently supported.
    if( algCompression == ID_COMP_ALG_ZLIB )
        {
        z_stream    c_stream; /* decompression stream */
        int         err;

        //  Init
        memset( &c_stream, 0, sizeof( c_stream ) );
        c_stream.zalloc = (alloc_func)0;
        c_stream.zfree = (free_func)0;
        c_stream.opaque = (voidpf)0;
        err = inflateInit(&c_stream);
        //
        //
        //  Initialize checksum
        //
        checksum = adler32(0L, Z_NULL, 0);

        //  Init output buffer
        c_stream.next_out  = bufferOutput;
        c_stream.avail_out = sizeOutput;
        c_stream.total_out = 0;

        do
            {
            //  Fill up the input buffer?
            if( c_stream.avail_in == 0 )
                {
                //  Assume it will fail
                haveData = FALSE;

                //  Read the next block
                sizeActual = PQDIF_min( sizeInput, sizeLeft );
                if( sizeActual > 0 )
                    {
                    if( oBufCompressed.ReadBuffer( bufferInput, sizeActual, 1/*, pfiCompressed*/ ) > 0 )
                        {
                        //
                        //
                        //  calculate running checksum of the data on disk (compressed)
                        //
                        checksum = adler32( checksum, bufferInput, sizeActual);

                        haveData = TRUE;
                        sizeLeft -= sizeActual;
                        }
                    }
                if( !haveData )
                    {
                    //  End of data
                    break;
                    }
                c_stream.next_in  = bufferInput;
                c_stream.avail_in = sizeActual;
                }        

            //  Decompress!
            err = inflate( &c_stream, Z_NO_FLUSH );

            //  Flush output buffer?
            if( c_stream.total_out > 0 )
                {
                //  Suck up what's in there
                oBufDecompressed.WriteBuffer( bufferOutput, c_stream.total_out);//, 1, pfiDecompressed );
                sizeDecompressed += c_stream.total_out;

                //  Keep running checksum
                //  EWG - this was a bug.  The pqdif library generates the checksum
                //  on the compressed data.  We therefore have to do the checksum
                //  on the file image reads above.
//                checksum = crc32( checksum, bufferOutput, c_stream.total_out );

                //  Re-init the output buffer
                c_stream.next_out  = bufferOutput;
                c_stream.avail_out = sizeOutput;
                c_stream.total_out = 0;
                }

            if (err == Z_STREAM_END) 
                break;
            }
        while( err == Z_OK );

        err = inflateEnd(&c_stream);
        }

	oBufDecompressed.SeekTo(0);
    //fseek( pfiDecompressed, 0, SEEK_SET );

    return status;
}

time_t CPQDTimeToLocalTime ( TIMESTAMPPQDIF *pqdtime )
{
	time_t time;

	time = (time_t) ( ( pqdtime->day - EXCEL_DAYCOUNT_ADJUST ) * SECONDS_PER_DAY + pqdtime->sec - SECONDS_SYS_LOCAL_TIME_SUB );

	return time;
}