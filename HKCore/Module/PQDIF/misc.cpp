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
���� <��׼����Դͨ�����к�> -> <�������ļ�����Դͨ�����к�> ��ӳ���ϵ
������������ԭ�����ڣ���׼xml�ļ�������Դ����˳����ܺͱ������ļ��Ķ���˳��һ��
[0][MAP_LEN] �����׼xml�ļ�ͨ�������к�
[1][MAP_LEN] ���汻�����ļ������к� 
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
			return -1; // Խ��,û�ж�Ӧ��ϵ
		}

		if(MapForDataSrc[0][mapcnt] == stdIndex)
		{
			testIndex = MapForDataSrc[1][mapcnt]; // �������ļ�����Դͨ�����к� 
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
			return -1; // Խ��
		}

		if(MapForDataSrc[1][mapcnt] == testIndex)
		{
			stdIndex = MapForDataSrc[0][mapcnt]; // ��׼ͨ�����к�
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
		// �ų������ͨ��
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

		storeSeriesInfo.AddNode(); // ����һ���ڵ�
		CStoreSeriesInfo_Node *pInfoNode = storeSeriesInfo.GetNode( nodeindex ); // ȡĩβ
		++nodeindex; /* */
		pInfoNode->stdDataSrcIndex = get_DataSrc_StdIndex_From_TestIndex( channelIndex ); // ���к�
		pInfoNode->channelName = pchannel->szChannelName; // ����
		pInfoNode->idQuantityMeasured = pchannel->idQuantityMeasured; // ����

		INT4 seriesTotalNum = pchannel->nSeries;
		pInfoNode->seriesNum = seriesTotalNum;
		for( INT4 seriesIndex = 0; seriesIndex < seriesTotalNum; ++seriesIndex )
		{
			series_defn *pseries = pchannel->Get_series( seriesIndex );

			if ( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_TIME ) )
			{
				pInfoNode->indexTime = seriesIndex;
			}
			else if (( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_VAL ) )||( PQDIF_IsEqualGUID( pseries->idValueType, ID_SERIES_VALUE_TYPE_FLUKE ) ))//��������FlukePQDIF   zhouhj20210119
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

		// �ж�����Դͨ��������
		// ��Ч��ͨ������
		if( pInfoNode->seriesNum==0 
			&& pInfoNode->indexTime==-1 && pInfoNode->indexOtherVal==-1
			&& pInfoNode->indexMin==-1  && pInfoNode->indexMax==-1 
			&& pInfoNode->indexAvg==-1  && pInfoNode->indexCp95==-1 
		  )
		{
			pInfoNode->typeOfDataSrc = CStoreSeriesInfo_Node::None_TypeOfDatasrc;
		}
		// ͳ�����ݵ�ͨ������
		if( (pInfoNode->seriesNum>=2 && pInfoNode->indexTime>=0 && pInfoNode->indexOtherVal==-1)
			     && (pInfoNode->indexMax>=0 || pInfoNode->indexMin>=0 || pInfoNode->indexAvg>=0 || pInfoNode->indexCp95>=0) 
		  )
		{
			pInfoNode->typeOfDataSrc = CStoreSeriesInfo_Node::Stat_TypeOfDataSrc;
		}
		// ���λ����¼���ͨ������
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
	g_verifyByStdXml = 0;//zhouhj 20201128 �����µ����׼�ļ�����Ҫ����У���ʽ
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

	time_t minTimeVal = 9223372036854775807/*__int64���ֵ*/, maxTimeVal = 0;
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
			continue; // �����¼�������ʱ���ѯ
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
		//time_t keyQueryTimestamp = 9223372036854775807/*__int64���ֵ*/;
		//time_t minTimeVal = 9223372036854775807/*__int64���ֵ*/, maxTimeVal = 0;

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

		if (nChannelIndex == stdIndex)//zhouhj 20201127 ��ͨ����ѯʱ��g_pqTotalData.observation�����ж�Ӧ����������Ӧ������ʾ����ͨ�����������paci->idxChannelDefnΪ��׼�����ܲ�ѯ����
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

// ���������ļ���obsevation.channel_instance ��idxChannelDefn ȫ������ ��׼�ļ��е�index 
static void convert_TestIndex_To_StdIndex_InTestFile()
{
	POS pos = s_observation.GetHeadPosition();
	while( pos != NULL )
	{
		channel_instance *paci = (channel_instance *)s_observation.GetNext( pos );
		int testIndex = paci->idxChannelDefn;
		int stdIndex = get_DataSrc_StdIndex_From_TestIndex( testIndex );
		// stdIndex���ܷ���-1����Ϊ�Ƕ����ͨ��
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

	// ת��index
	convert_TestIndex_To_StdIndex_InTestFile();
	
	// �ÿ�ʼʱ���ʱ������ɾ���ʱ��
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s��idxChannel=%d�� Error"),pInfoNode->channelName, paci->idxChannelDefn);
		}
	}

	// ����total������
	POS pos = s_observation.GetHeadPosition();

	while( pos != NULL )
	{
		channel_instance *pSrc = (channel_instance *)s_observation.GetNext(pos);

		if (pSrc->idxChannelDefn == -1)
		{
			continue; // ����Ƕ����ͨ���򲻼�������������
		}

		g_pqTotalData.observation.AppendChannelDatas(pSrc); //����ȡ��������ӵ�g_pqTotalData.observation��
	}

	// ÿ�μ����µ�observation record�������¼���ͨ������
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
	/* s_observation �ͷ���endOfRecord()������ */
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

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "��׼XML�ļ���ʼ����" );

	flag = xml.Load(stdxml);

	if ( ! flag )
	{
		// CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "��׼XML�ļ�����ʧ��" );
		return -1;
	}

	xml.ResetPos();  // ��λ�����ڵ�<pqdif>  
	flag = xml.FindElem( TEXT("pqdif") );
	if ( ! flag )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "��׼XML�ļ����޷���λ��ǩ<pqdif>" );
		return -1;
	}
	xml.IntoElem();   //����<pqdif>

	flag = xml.FindElem ( TEXT("tagRecDataSource") );
	if ( ! flag )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "��׼XML�ļ����޷���λ��ǩ<tagRecDataSource>" );
		return -1;
	}
	xml.IntoElem(); // ����<tagRecDataSource>

	flag = xml.FindElem ( TEXT("tagChannelDefns") );
	if ( ! flag )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "��׼XML�ļ����޷���λ��ǩ<tagChannelDefns>" );
		return -1;
	}
	xml.IntoElem(); // ����<tagChannelDefns>

	size_t idxChannel = 0; 
	g_stdFormat.datasource.strStdFile = stdxml;

	while ( xml.FindElem( _T("tagOneChannelDefn") ) )
	{
		xml.IntoElem();   //����<tagOneChannelDefn></tagOneChannelDefn>

		++idxChannel;
		g_stdFormat.datasource.nChannel = idxChannel;
		channel_defn *p_channel_defn = g_stdFormat.datasource.add();

		// ͨ������
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "��׼XML�ļ����޷���λ��ǩ<tagSeriesDefn>" );
		    return -1;
		}
		xml.IntoElem(); // ����<tagSeriesDefns>

		size_t idxSeries = 0;

		while ( xml.FindElem(_T("tagOneSeriesDefn")) )
		{
			xml.IntoElem(); // ����<tagOneSeriesDefn>

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

			xml.OutOfElem();  //����<tagOneSeriesDefn>
		}

		xml.OutOfElem();  //����<tagSeriesDefns>
		xml.OutOfElem();  //����<tagOneChannelDefn>
	}

	xml.OutOfElem();  //����<tagChannelDefns>
	xml.OutOfElem();  //����<tagRecDataSource>
	xml.OutOfElem();  //����<pqdif>

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
// 	if ( p_series_defn1->idValueType != p_series_defn2->idValueType ) // ������λ
// 	{
// 		return -1;
// 	}
// 
// 	if ( p_series_defn1->idQuantityUnits != p_series_defn2->idQuantityUnits ) // ������λ
// 	{
// 		return -1;
// 	}
// 
// 	if ( ! PQDIF_IsEqualGUID ( p_series_defn1->idCharacteristicType, p_series_defn2->idCharacteristicType ) ) // ֵ����
// 	{
// 		return -1;
// 	}
// 
// 	return 1;
}


static int is_series_defn_same2(series_defn *p_series_defn1, series_defn *p_series_defn2)
{
	if ( p_series_defn1->idValueType != p_series_defn2->idValueType ) // ֵ����
	{
		return -1;
	}

	if ( p_series_defn1->idQuantityUnits != p_series_defn2->idQuantityUnits ) // ������λ
	{
		return -1;
	}

	if ( ! PQDIF_IsEqualGUID ( p_series_defn1->idCharacteristicType, p_series_defn2->idCharacteristicType ) ) // ֵ����
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("δ����ͨ���д���tagOneSeriesDefn��ֵ���Ͷ������;"));
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

		if ( p->idQuantityUnits != p_series_defn->idQuantityUnits ) // ������λ
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "����Դͨ��(���%d ����%s)����ͨ��(���%d)tagQuantityUnitsID����", i, pTest->szChannelName, j);
			continue;
		}

		if ( ! PQDIF_IsEqualGUID ( p->idCharacteristicType, p_series_defn->idCharacteristicType ) ) // ֵ����
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "����Դͨ��(���%d ����%s)����ͨ��(���%d)tagQuantityCharacteristicID����", i, pTest->szChannelName, j );
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

	if (pStd->szChannelName.Find(_T("DVC A"))>=0)//����ʹ��zhouhj
	{
		bOnllyHasStd = 1;
	}

	if ( pTest->idPhase != pStd->idPhase ) // ��λ
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "����Դͨ��(���%d ����%s)��tagPhaseID����", i, pTest->szChannelName);
		return -1;
	}
	if ( pTest->idQuantityMeasured != pStd->idQuantityMeasured ) // ��������
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "PQDIF�ļ��У�����Դͨ��(���%d ����%s)��tagQuantityMeasuredID����", i, pTest->szChannelName );
		return -1;
	}

// 	if (!bOnllyHasStd)
// 	{
// 		if ( pTest->nSeries != pStd->nSeries ) // ��ͨ������
// 		{
// 			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "����Դͨ��(���%d ����%s)����ͨ����������");
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

// 		if ( pSStd->idQuantityUnits != p->idQuantityUnits ) // ������λ
// 		{
// 			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "����Դͨ��(���%d ����%s)����ͨ��(���%d)tagQuantityUnitsID����", i, pTest->szChannelName, j);
// 			return -1;
// 		}
// 
// 		if ( ! PQDIF_IsEqualGUID ( pSStd->idCharacteristicType, p->idCharacteristicType ) ) // ֵ����
// 		{
// 			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "����Դͨ��(���%d ����%s)����ͨ��(���%d)tagQuantityCharacteristicID����", i, pTest->szChannelName, j );
// 			return -1;
// 		}
	}
	
	return 1;
}

// datasource�Ķ���˳����Բ�һ�� 
int verifyByStdXml()
{
	if (g_verifyByStdXml == 1)
	{
		return 1;
	}

	revTotalNum = 0;//zhouhj 20201128 ��ʼ����ֵ������򿪸�������󣬽���pqdif�ļ����ݲ�����������
	g_verifyByStdXml = 1;
	int i, j, mapcnt = 0;
	BOOL channelStatus[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // ĳһͨ���Ѿ�����Ⲣͨ����״̬����
	ULONG channelPoint[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // ĳһͨ���Ѿ�����Ⲣͨ����״̬����
	memset(channelStatus, 0, PQDIF_MAX_DEFINE_CHANNEL_NUM*sizeof(BOOL)); // default to false
	memset(channelPoint, 0, PQDIF_MAX_DEFINE_CHANNEL_NUM*sizeof(ULONG)); // default to false

	memset(MapForDataSrc, -1, sizeof(MapForDataSrc));
	memset(testFileReservedChannel, -1, sizeof(testFileReservedChannel));

	if ( g_stdFormat.datasource.nChannel == 0 )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "��׼XML�ļ���δ������");
		goto fail1;
	}

	// �����ļ���ͨ�����Զ��ڱ�׼�ļ�����һ��Ҫ������׼ͨ���������ͨ�����Բ���
// 	if (s_datasource.nChannel < g_stdFormat.datasource.nChannel)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "### ���󣺲����ļ�����ͨ������(ͨ������%d)û����ȫ������׼XML�ļ�ͨ������(ͨ������%d)", 
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
				// ����ĳһͨ������ʱ���û�������Ǳ�׼ͨ�����кţ���Ҫת���ɱ������ļ��е�ͨ�����к�
				MapForDataSrc[0][mapcnt] = j; // ��׼ͨ��
				MapForDataSrc[1][mapcnt] = i; // �������ļ�ͨ��
				++mapcnt;

				//if ( isDataSrcSame( p_channel_defn, p_std_channel_defn , TRUE) > 0 ) // Ϊ���ҵ�ͨ����������������²���
				{
					channelStatus[j] = true; // ����ͨ������һ�£��˳���һͨ����ѭ����������������һͨ��
					break;
				}
			}
		}
	}

	BOOL flag = FALSE;
	for ( j = 0; j < stdChannelNum; ++j ) // �ҳ�����δ�����ͨ����������
	{
		p_std_channel_defn = g_stdFormat.datasource.Get_channel(j);
		BOOL bSame = TRUE;

		if (channelPoint[j] == 0)
		{
			flag = TRUE;
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "û�ж���ͨ��%d(%s)",(j+1), p_std_channel_defn->szChannelName);
			continue;
		}

		p_channel_defn = (channel_defn *)channelPoint[j];

		if (p_channel_defn->szChannelName != p_std_channel_defn->szChannelName )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "--------����Դͨ��(%d)����(%s)���׼(%s)��һ��", 
				s_datasource.FindIndex(p_channel_defn), p_channel_defn->szChannelName, p_std_channel_defn->szChannelName);
		}

		if ( channelStatus[j] == false ) 
		{
			flag = TRUE;
			CString errInfo, errInfo2;
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "***********************************************************");
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "����Դͨ��(%s)�����д���", p_std_channel_defn->szChannelName);

			long seriesSize = 0, seriesIndex=0;


			if ( p_channel_defn->idPhase != p_std_channel_defn->idPhase ) // ��λ
			{
				errInfo = get_Str_From_TagPhaseID( p_std_channel_defn->idPhase );
				errInfo2 = get_Str_From_TagPhaseID( p_channel_defn->idPhase );
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagPhaseID %s ���׼ %s ��һ��", errInfo2, errInfo);
			}

			if ( p_channel_defn->idQuantityMeasured != p_std_channel_defn->idQuantityMeasured ) // ��������
			{
				errInfo = get_Str_From_TagQuantityMeasuredID( p_std_channel_defn->idQuantityMeasured );
				errInfo2 = get_Str_From_TagQuantityMeasuredID( p_channel_defn->idQuantityMeasured );
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityMeasuredID %s ���׼ %s ��һ��", errInfo2, errInfo);
			}

			seriesSize = p_std_channel_defn->nSeries;

			for( seriesIndex = 0; seriesIndex < seriesSize; ++seriesIndex )
			{
				series_defn *p1 = p_std_channel_defn->Get_series( seriesIndex );
				//series_defn *p2 = p_channel_defn->Get_series( seriesIndex );
				series_defn *p2 = find_series_defn2(p_channel_defn, p1->idValueType);
				
				if (p2 == NULL)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "��ͨ��(%d)û�ж���", seriesIndex+1);

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
						CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "��ͨ��(%d)�������׼��һ��", seriesIndex+1);

						if ( p1->idQuantityUnits != p2->idQuantityUnits ) // ������λ
						{
							errInfo = get_Str_From_TagQuantityUnitsID( p1->idQuantityUnits );
							errInfo2 = get_Str_From_TagQuantityUnitsID( p2->idQuantityUnits );
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityUnitsID %s ���׼ %s ��һ��",errInfo2, errInfo);
						}

// 						if ( p1->idMethod != p2->idMethod )
// 						{
// 							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagStorageMethodID %d ���׼ %d ��һ��",p1->idMethod, p2->idMethod);
// 						}

						if ( p1->idGreekPrefix != p2->idGreekPrefix )
						{
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagHintGreekPrefixID %d ���׼ %d ��һ��",p1->idGreekPrefix, p2->idGreekPrefix);
						}

						if ( ! PQDIF_IsEqualGUID ( p1->idCharacteristicType, p2->idCharacteristicType ) ) // ֵ����
						{
							errInfo = get_Str_From_TagQuantityCharacteristicID( p1->idCharacteristicType );
							errInfo2 = get_Str_From_TagQuantityCharacteristicID( p2->idCharacteristicType );
							CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    tagQuantityCharacteristicID %s ���׼ %s ��һ��",errInfo2, errInfo);
						}
						
						bSame = FALSE;
					}
				}

// 				if (!bSame)
// 				{
// 					if (p_std_channel_defn->nSeries != p_channel_defn->nSeries)
// 					{
// 						CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "��ͨ������(%d)���׼��%d����һ��", p_channel_defn->nSeries, p_std_channel_defn->nSeries);
// 					}
// 				}

// 				if (is_series_defn_exist(p_channel_defn, p) == -1)
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "��ͨ��(%d)û�ж���", seriesIndex+1);
// 					errInfo = get_Str_From_TagQuantityUnitsID( p->idQuantityUnits );
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    ������λ %s", errInfo);
// 					errInfo = get_Str_From_TagQuantityCharacteristicID( p->idCharacteristicType );
// 					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    ֵ���� %s", errInfo);
// 				}
			}
// 
// 
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "����Դͨ��(%s)��ȷ����������ʾ��", p_std_channel_defn->szChannelName );
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "***********************************************************");
// 			errInfo = get_Str_From_TagPhaseID( p_std_channel_defn->idPhase );
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "��λ %s", errInfo);
// 			errInfo = get_Str_From_TagQuantityMeasuredID( p_std_channel_defn->idQuantityMeasured );
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "�������� %s", errInfo);
// 			seriesSize = p_std_channel_defn->nSeries;
// 			for( seriesIndex = 0; seriesIndex < seriesSize; ++seriesIndex )
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "��ͨ��(%d)", seriesIndex+1);
// 				errInfo = get_Str_From_TagQuantityUnitsID( p_std_channel_defn->Get_series( seriesIndex )->idQuantityUnits );
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    ������λ %s", errInfo);
// 				errInfo = get_Str_From_TagQuantityCharacteristicID( p_std_channel_defn->Get_series( seriesIndex )->idCharacteristicType );
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "    ֵ���� %s", errInfo);
// 			}
//			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "***********************************************************");
		}
	}
	if (flag == TRUE)
	{
		memset(MapForDataSrc, -1, sizeof(MapForDataSrc));
		goto fail1;
	}

	// ����ҵ������еı�׼ͨ�����ٿ����Ƿ��з�Χ֮�������ͨ��
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
		if (tmp == mapcnt) // �����ͨ��
		{
			testFileReservedChannel[revTotalNum] = i;
			++revTotalNum;
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "�ļ���ʽ��֤ͨ��" );
	return 1;
fail1:
	return -1;
}

int VerifyStdXmlOfRepeat()//zhouhj ����׼�ļ��е�ͨ���Ƿ����ظ�
{
	int i, j, mapcnt = 0;
	BOOL channelStatus[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // ĳһͨ���Ѿ�����Ⲣͨ����״̬����
	ULONG channelPoint[PQDIF_MAX_DEFINE_CHANNEL_NUM]; // ĳһͨ���Ѿ�����Ⲣͨ����״̬����
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
				strTemp.Format(_T("    ͨ��(%d)����(%s)��ͨ��(%d)����(%s)��ͬ"), i+1,p_channel_defn->szChannelName, j+1, p_std_channel_defn->szChannelName);
				asStrError.Add(strTemp);
				iRet = -1;
			}
		}
	}

	if (iRet == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,   _T("++++++++++++��׼�ļ�����++++++++++++++"));

		for (i=0; i<asStrError.GetSize(); i++)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,   "    %s", asStrError.GetAt(i) );
		}
		CLogPrint::LogString(XLOGLEVEL_TRACE,   _T("++++++++++++��׼�ļ�����++++++++++++++") );
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
        Valid_GetCompressionInfo( styleCompression, algCompression ); /*�˺���û�����κ�����*/
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "�޷������ļ�" ); 
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

    // ��ȡRecordͷ��
    countRead = oBufOriginal.ReadBuffer( &hdrRecord, sizeof( hdrRecord ), 1);//, pfiOriginal );
    BOOL bEOF = oBufOriginal.IsEof();//feof( pfiOriginal ); 
	if (bEOF)
    { 
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "�����ļ�ĩβ���޷�������ȡ" );
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
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"����һ��Record��Head���ݳ��ȴ���");
            return FALSE;
        }
      
		if ( ! PQDIF_IsEqualGUID( hdrRecord.guidRecordSignature, guidRecordSignaturePQDIF ) )
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error:The GUID Signature for PQDIF is not same \n"); /* ERROR INFO 
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "����һ��Recordͷ��GUIDǩ������");
			return FALSE;
		}

        if( ! bHeaderOnly )
        {
            acceptNewRecord( pos, hdrRecord.tagRecordType ); // ���ݽṹ�������ʼ�� 
            accepted = acceptCollection( hdrRecord.tagRecordType, 0 ); // ����level��tag��̬�������ݿռ�
            
			if( accepted )
            {
				/* PQMDװ�����ɵ�pqdif�ļ����õ�ѹ�� ID_COMP_STYLE_RECORDLEVEL ID_COMP_ALG_ZLIB */
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
			/* ����s_container s_datasource s_monsett s_observation �� g_pqTotalData */
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
    long    posStartOfRecord,     //  record��body��ʼλ�ã����ǹ̶������
    int     level,                //  Current level in the hierarchy (input)
    SIZE4   sizeOfRecord          //  record��body�Ĵ�С
)
{
    INT4            idx;
    BOOL            accepted = FALSE;
    c_collection    collection; // SIZE4 count;
    c_vector        vector; // SIZE4 count;
    long            size;
    long            posThisElement; // Ԫ�������ݵ�λ��
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
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "����һ��Collection������ȡ����");
        return FALSE;
    }

    arrayElements = new c_collection_element[ collection.count ];
    countRead = oBuffer.ReadBuffer( arrayElements, sizeof( c_collection_element ), collection.count);//, pfi ); // ��level�����collection_elementȫ��������
  
	if (countRead != (size_t) collection.count)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Error:number of elements read (%d) in collection different from count (%d).\n", countRead, collection.count );
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "�����ļ���Element������ȡ����" );
		goto fail1;
    }

    for( idx = 0; idx < collection.count; idx++ )
    {
        if( ! arrayElements[ idx ].isEmbedded ) // ����Ƕ����
        {
            if( arrayElements[ idx ].link.linkElement >= sizeOfRecord )
            {
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Error:A relative position (.linkElement) is past the end of the record.\n" );
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "�����ļ���Elementλ��ƫ�ƴ���" );
                goto fail1;
            }

			// ָ���ƶ���ʵ������λ��
            posThisElement = posStartOfRecord + arrayElements[ idx ].link.linkElement;
            oBuffer.SeekTo(posThisElement);//fseek( pfi, posThisElement, SEEK_SET ); 
        }

        switch( arrayElements[ idx ].typeElement )
        {
            case ID_ELEMENT_TYPE_COLLECTION:
                accepted = acceptCollection( arrayElements[ idx ].tagElement, level + 1 );
                if( accepted )
                {
                    accepted = parseCollection( oBuffer, posStartOfRecord, level + 1, sizeOfRecord ); // �������棬pfi�Ѿ��ƶ���level+1�����collection��λ��
                }
				else
				{
					goto fail1;
				}
                endOfCollection( level + 1 ); /* ��������ո�ͨ�������� */
                break;

            case ID_ELEMENT_TYPE_SCALAR:
                size = GetNumBytesOfType( arrayElements[ idx ].typePhysical ); // ����������ͳ���

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
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "����Element���ݴ�С��4�ֽڶ���");
						goto fail1;
                    }

                    pdata = new char[ size ];
                    countRead = oBuffer.ReadBuffer( pdata, size, 1);//, pfi );
                }
				/* ������� */
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
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "����Element���ݴ�С��4�ֽڶ���");
					goto fail1;
                }
                //  Alloc & read
                pdata = new char[ size * vector.count ];
                countRead = oBuffer.ReadBuffer( pdata, size, vector.count);//, pfi );
                if ( countRead != (size_t) vector.count )
                {
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "******** number of bytes read (%d) for vector is not equal to vector.count (%d).\n", countRead, vector.count);
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "����Vector������ȡ����");
					delete[] pdata;
					goto fail1;
                }
                /* ������� */
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