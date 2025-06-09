#include "stdafx.h"

#include <string.h>
#include "pqdifr.h"
#include "misc.h"
#include "pqread.h"

// global var
GUID    s_arrayTags[ 16 ];
container_example       s_container;
datasource_example      s_datasource;
monitorsettings_example s_monsett;
observation_example     s_observation;

time_t s_observation_tsStart;

long    s_idxChannelDefn = -1;
long    s_idxSeriesDefn = -1;
long    s_idxChannelSett = -1;
long    s_idxChannelInst = -1;
long    s_idxSeriesInst = -1;


//  Local functions
static double * _NewResolvedSeries
            (
            long    idxChannel,
            long    idxSeries,
            long    idxChannelDefn,     //  If ptr is NULL, this is ignored
            long    countRawPoints,     //  If ptr is NULL, this is ignored
            void *  pvectSeriesArray,   //  Can be NULL
            INT1    idPhysicalType,     //  If ptr is NULL, this is ignored
            long&   countPoints
            );
/*
static long _GenerateSeriesCount
            ( 
            UINT4   idStorageMethod,
            INT1    idPhysicalType,
            long    countRawPoints,
            void *  pvectSeriesArray
            );*/
static double * _GenerateSeriesData
            ( 
            UINT4   idStorageMethod, 
            INT1    idPhysicalType,
            double  rScale, 
            double  rOffset, 
            long    countRawPoints,
            void *  pvectSeriesArray,
            long&   countPoints
            );
static BOOL _VectorArrayGetValue
            ( 
            void *  pdata, 
            INT1    typePhysical, 
            int     idx, 
            double& value 
            );


//  Record accept/end functions
void acceptNewRecord(long pos, const GUID& tag)
{   
    memset( &s_arrayTags, 0, sizeof( s_arrayTags ) );

	s_idxChannelDefn = -1;
	s_idxSeriesDefn  = -1;

	s_idxChannelSett = -1;

	s_idxChannelInst = -1;
	s_idxSeriesInst  = -1;

	if ( PQDIF_IsEqualGUID( tag, tagContainer ) )
	{
		//memset( &s_container, 0, sizeof(s_container) );
		s_container.Init();
	}
    
	if( PQDIF_IsEqualGUID( tag, tagRecDataSource ) )
	{
		//freeDataSource( &s_datasource );
		//memset( &s_datasource, 0, sizeof( s_datasource ) );
		s_datasource.Init();
		s_datasource.DeleteAll();
	}

	if( PQDIF_IsEqualGUID( tag, tagRecMonitorSettings ) )
	{
		//freeMonitorSettings( &s_monsett );
		//memset( &s_monsett, 0, sizeof( s_monsett ) );
		s_monsett.Init();
		s_monsett.DeleteAll();
	}

	if( PQDIF_IsEqualGUID( tag, tagRecObservation ) )
	{
		//memset( &s_observation, 0, sizeof( s_observation ) );	
		s_observation.DeleteAll();
	}
}

int endOfRecord( void )
{
    int idxChannel;
    int idxSeries;

	// CONTAINER
	if ( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagContainer ) )
	{
		++g_fileNum; // 对于每个pqdif文件，这里只运行一次

		addContainerToTotalData();
	}

    //  DATA SOURCE RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecDataSource ) )
    {
		addDataSourceToTotalData(); 

		if ( verifyByStdXml() < 0 )
		{
			return -1;
		}
		else // 如果文件格式验证成功，则记录数据源通道的信息
		{
			// 添加记录每个数据源通道序列号的
			init_Store_Sereis_Info( s_datasource, g_StoreSeriesInfo); // define @ misc.cpp
		}
    }
    
    //  MONITOR SETTINGS RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecMonitorSettings ) )
    {
		addMonitorSettingToTotalData();
    }

    //  OBSERVATION RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecObservation ) )
    {
		// 考虑到共享通道的问题
        for( idxChannel = 0; idxChannel < s_observation.nChannels; idxChannel++ )
        {
			channel_instance *p_channel_instance = s_observation.Get_channel(idxChannel);
            for( idxSeries = 0; idxSeries < p_channel_instance->nSeries; idxSeries++ )
            {
				series_instance *p_series_instance = p_channel_instance->Get_series(idxSeries);
                if( p_series_instance->paData == NULL )
                {
                    long    countPointsResolved;
					p_series_instance->Set_paData( _NewResolvedSeries( idxChannel, idxSeries, -1, 0, NULL, 0, countPointsResolved ) );

					if (countPointsResolved < 0)
					{
						p_series_instance->nTotalValues = countPointsResolved;
					}
					else
					{
						p_series_instance->nTotalValues = countPointsResolved;
					}
                }
            }
        }

		static int lastFileNum = 0; // 用于判断是否是新的文件
		if ( g_fileNum == 1 )
		{
			++g_obserNum;
			if ( g_fileNum != lastFileNum )
			{
				lastFileNum = g_fileNum; 
			}
		}
		else if ( g_fileNum > 1 )
		{
			if ( g_fileNum != lastFileNum ) // 新的文件
			{
				lastFileNum = g_fileNum; 
				g_obserNum = 0;  // 新的文件observation数量清零
			}
			++g_obserNum;
		}

		addObservationToTotalData();

		// 同一个文件中observation可能不止一个，使用后释放，便于存放下一个observation数据 
		freeObservation ( &s_observation );
		s_observation.Init();
    }  

    return 1;
}

//  Element accept functions
BOOL acceptCollection( const GUID& tag, int level )
{
	Valid_BeginCollection( s_arrayTags, level );

	s_arrayTags[ level ] = tag;

    //  DATA SOURCE RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecDataSource ) )
    {
        if( level == 0 ) 
        {
           // memset( &s_datasource, 0, sizeof( s_datasource ) );
			s_datasource.Init();
        }

        if( PQDIF_IsEqualGUID( tag, tagChannelDefns ) )
        {
            s_idxChannelDefn = -1;
            s_idxSeriesDefn  = -1;
        }
        else if( PQDIF_IsEqualGUID( tag, tagOneChannelDefn ) )
        {
            s_idxChannelDefn++;
            s_idxSeriesDefn  = -1;
			s_datasource.add();
            //s_datasource.acd = (channel_defn *) realloc( s_datasource.acd, sizeof(channel_defn)*(s_idxChannelDefn + 1) );
            //memset( s_datasource.acd + s_idxChannelDefn, 0, sizeof ( channel_defn ) );
        }
        else if( PQDIF_IsEqualGUID( tag, tagSeriesDefns ) ) 
        {
            s_idxSeriesDefn  = -1;
        }
        else if( PQDIF_IsEqualGUID( tag, tagOneSeriesDefn ) )
        {
            s_idxSeriesDefn++;
			s_datasource.Get_channel(s_idxChannelDefn)->add();
           // s_datasource.acd[ s_idxChannelDefn ].asd = (series_defn *) realloc( s_datasource.acd[ s_idxChannelDefn ].asd, sizeof( series_defn ) * ( s_idxSeriesDefn + 1 ) );
           // memset( s_datasource.acd[ s_idxChannelDefn ].asd + s_idxSeriesDefn, 0, sizeof ( series_defn ) );
        }
    }

    //  MONITOR SETTINGS RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecMonitorSettings ) )
    {
        if( level == 0 ) 
        {
            //memset( &s_monsett, 0, sizeof( s_monsett ) );
			s_monsett.Init();
        }

        if( PQDIF_IsEqualGUID( tag, tagChannelSettingsArray ) )
        {
            s_idxChannelSett = -1;
        }
        else if( PQDIF_IsEqualGUID( tag, tagOneChannelSetting ) )
        {
            s_idxChannelSett++;
			s_monsett.add();
            //s_monsett.ams = (mon_sett_one_channel *) realloc( s_monsett.ams, sizeof( mon_sett_one_channel ) * ( s_idxChannelSett + 1 ) );
            //memset( s_monsett.ams + s_idxChannelSett, 0, sizeof ( mon_sett_one_channel ) );
        }
    }

    //  OBSERVATION RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecObservation ) )
    {
        if( level == 0 ) 
        {
            //memset( &s_observation, 0, sizeof( s_observation ) );
			s_observation.Init();
        }

        if( PQDIF_IsEqualGUID( tag, tagChannelInstances ) )
        {
			s_idxChannelInst = -1;
            s_idxSeriesInst  = -1;
        }
        else if( PQDIF_IsEqualGUID( tag, tagOneChannelInst ) )
        {
            s_idxChannelInst++;
            s_idxSeriesInst  = -1;
			s_observation.add();
            //s_observation.aci = (channel_instance *) realloc( s_observation.aci, sizeof( channel_instance ) * ( s_idxChannelInst + 1 ) );
            //memset( s_observation.aci + s_idxChannelInst, 0, sizeof ( channel_instance ) );
        }
        else if( PQDIF_IsEqualGUID( tag, tagSeriesInstances ) )
        {
            s_idxSeriesInst  = -1;
        }
        else if( PQDIF_IsEqualGUID( tag, tagOneSeriesInstance ) )
        {
            s_idxSeriesInst++;
			s_observation.Get_channel(s_idxChannelInst)->add();
            //s_observation.Get_channel( s_idxChannelInst )->asi = (series_instance *) realloc( s_observation.Get_channel( s_idxChannelInst )->asi, sizeof( series_instance ) * ( s_idxSeriesInst + 1 ) );
            //memset( s_observation.Get_channel( s_idxChannelInst )->asi + s_idxSeriesInst, 0, sizeof ( series_instance ) );
        }
    }

    return TRUE;
} 

void endOfCollection ( int level )
{
	Valid_EndCollection( s_arrayTags, level );

    //  DATA SOURCE RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecDataSource ) )
    {
        //  Is this the end of the channel definitions?
        if( PQDIF_IsEqualGUID( s_arrayTags[ level ], tagChannelDefns ) )
        {
            //  How many channel defns did we get?
            s_datasource.nChannel = s_idxChannelDefn + 1;
        }

        if( s_idxChannelDefn >= 0 ) 
        {
            if( s_idxSeriesDefn >= 0 )
            {
                //  The end of a channel definition?
                if( PQDIF_IsEqualGUID( s_arrayTags[ level ], tagOneChannelDefn ) )
                {
                    //  Count how many series definitions we found for this channel defn
                    s_datasource.Get_channel( s_idxChannelDefn )->nSeries = s_idxSeriesDefn + 1;
                }
            }
        }
    }   

    //  MONITOR SETTINGS RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecMonitorSettings ) )
    {
        if( s_idxChannelSett >= 0 )
       {
            //  Is this the end of the channel settings?
            if( PQDIF_IsEqualGUID( s_arrayTags[ level ], tagChannelSettingsArray ) )
            {
                //  How many channel settings did we get?
                s_monsett.nChannel = s_idxChannelSett + 1;
            }
        }
    }   

    //  OBSERVATION RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecObservation ) )
    {
        if( s_idxChannelInst >= 0 ) 
       {
            //  Is this the end of the channel instances?
            if( PQDIF_IsEqualGUID( s_arrayTags[ level ], tagChannelInstances ) )
            {
                //  How many channels did we get?
                s_observation.nChannels = s_idxChannelInst + 1;
            }

            if( s_idxSeriesInst >= 0 )  
            {
                //  The end of a channel instance?
                if( PQDIF_IsEqualGUID( s_arrayTags[ level ], tagOneChannelInst ) )
                {
                    //  Count how many series instances we found for this channel.
                    s_observation.Get_channel( s_idxChannelInst )->nSeries = s_idxSeriesInst + 1;
                }
            }
        }
    }   
}
            
BOOL acceptScalar( const GUID& tag, INT1 typePhysical, void *pdata, int level )
{
	Valid_Scalar( s_arrayTags, level, tag, typePhysical, pdata );

    //  CONTAINER RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagContainer ) )
    {
        if( typePhysical == ID_PHYS_TYPE_TIMESTAMPPQDIF )
        {
            if( PQDIF_IsEqualGUID( tag, tagCreation ) )
			{
                s_container.tsCreation = *( (ts *) pdata );
			}
            if( PQDIF_IsEqualGUID( tag, tagLastSaved ) )
			{
                s_container.tsLastSaved = *( (ts *) pdata );
			}
        }
		if ( typePhysical == ID_PHYS_TYPE_UNS_INTEGER4 )
		{
			if( PQDIF_IsEqualGUID( tag, tagTimesSaved ) )
			{
				s_container.nTimesSaved = (INT4) *( (UINT4 *) pdata );
			}
			else if ( PQDIF_IsEqualGUID (tag, tagCompressionStyleID) )
			{
				s_container.compStyleRecordLevel = (INT4) *( (UINT4 *) pdata );
			}
			else if ( PQDIF_IsEqualGUID (tag, tagCompressionAlgorithmID) )
			{
				s_container.compAlgZlig = (INT4) *( (UINT4 *) pdata );
			}
			else
			{

			}
		}
    }

    //  DATA SOURCE RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecDataSource ) )
    {
        switch( typePhysical )
        {
            case ID_PHYS_TYPE_UNS_INTEGER4:
            {
                UINT4 valueUINT4 = *( (UINT4 *) pdata );

                if( s_idxChannelDefn >= 0 )
                {
                    if( PQDIF_IsEqualGUID( tag, tagPhaseID ) )
                    {
                        s_datasource.Get_channel( s_idxChannelDefn )->idPhase = valueUINT4;
                    }
					else if ( PQDIF_IsEqualGUID ( tag, tagQuantityMeasuredID ) )
					{
						s_datasource.Get_channel( s_idxChannelDefn )->idQuantityMeasured = valueUINT4;
					}
                }

                if( s_idxChannelDefn >= 0 && s_idxSeriesDefn >= 0 )
                {
                    if( PQDIF_IsEqualGUID( tag, tagQuantityUnitsID ) )
                    { 
                        s_datasource.Get_channel( s_idxChannelDefn)->Get_series( s_idxSeriesDefn)->idQuantityUnits = valueUINT4;
                    }
                    else if( PQDIF_IsEqualGUID( tag, tagStorageMethodID ) )
                    {
						if (!(valueUINT4 & ID_SERIES_METHOD_VALUES))//周宏军 20200318 增加错误打印信息
						{
							channel_defn *pChannelDefn = s_datasource.Get_channel( s_idxChannelDefn);
							series_defn *pSeriesDefn = s_datasource.Get_channel( s_idxChannelDefn)->Get_series( s_idxSeriesDefn);

 							if( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, ID_SERIES_VALUE_TYPE_TIME ))
 							{
 								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES(ID_SERIES_VALUE_TYPE_TIME)"),pChannelDefn->szChannelName);
 							}
 							else if( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, ID_SERIES_VALUE_TYPE_MAX ))
 							{
 								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES(ID_SERIES_VALUE_TYPE_MAX)"),pChannelDefn->szChannelName);
 							}
 							else if( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, ID_SERIES_VALUE_TYPE_MIN ))
 							{
 								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES(ID_SERIES_VALUE_TYPE_MIN)"),pChannelDefn->szChannelName);
 							}
 							else if( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, ID_SERIES_VALUE_TYPE_AVG ))
 							{
 								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES(ID_SERIES_VALUE_TYPE_AVG)"),pChannelDefn->szChannelName);
 							}
 							else if( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, ID_SERIES_VALUE_TYPE_P95 ))
 							{
 								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES(ID_SERIES_VALUE_TYPE_P95)"),pChannelDefn->szChannelName);
 							}
 							else if( PQDIF_IsEqualGUID( pSeriesDefn->idValueType, ID_SERIES_VALUE_TYPE_BINID ))
 							{
 								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES(ID_SERIES_VALUE_TYPE_BINID)"),pChannelDefn->szChannelName);
 							}
 							else
							{
								CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("通道(%s)下的tagStorageMethodID不包含ID_SERIES_METHOD_VALUES,其tagValueTypeID=[0x%lx-0x%x-0x%x]"),pChannelDefn->szChannelName
									,pSeriesDefn->idValueType.Data1,pSeriesDefn->idValueType.Data2,pSeriesDefn->idValueType.Data3);
							}

//							valueUINT4 = 1;
						}

                        s_datasource.Get_channel( s_idxChannelDefn)->Get_series( s_idxSeriesDefn)->idMethod = valueUINT4;
                    }
                    else if( PQDIF_IsEqualGUID( tag, tagHintGreekPrefixID ) )
                    {
                        s_datasource.Get_channel( s_idxChannelDefn)->Get_series( s_idxSeriesDefn)->idGreekPrefix = valueUINT4;
                    }
                }
            }
            break;

            case ID_PHYS_TYPE_TIMESTAMPPQDIF:
                break;

            case ID_PHYS_TYPE_GUID:
            {
                GUID    valueGUID = *((GUID *) pdata );

                if( PQDIF_IsEqualGUID( tag, tagDataSourceTypeID ) )
                {
                    s_datasource.idType = valueGUID;
                }
                else if( PQDIF_IsEqualGUID( tag, tagVendorID ) )
                {
                    s_datasource.idVendorID = valueGUID;
                }
                else if( PQDIF_IsEqualGUID( tag, tagEquipmentID ) )
                {
                    s_datasource.idEquipID = valueGUID;
                }
                
                if( s_idxChannelDefn >= 0 )
                {
                    if( PQDIF_IsEqualGUID( tag, tagQuantityTypeID ) )
                    {
                        s_datasource.Get_channel( s_idxChannelDefn)->idQuantityType = valueGUID;
                    }
                }

                if( s_idxChannelDefn >= 0 && s_idxSeriesDefn >= 0 )
                {
                    if( PQDIF_IsEqualGUID( tag, tagValueTypeID ) )
                    {
                        s_datasource.Get_channel( s_idxChannelDefn)->Get_series( s_idxSeriesDefn)->idValueType = valueGUID;
                    }
                    //  NOTE: THIS TAG IS NEW IN PQDIF VERSION 1.5
                    else if( PQDIF_IsEqualGUID( tag, tagQuantityCharacteristicID ) )
                    {
                        s_datasource.Get_channel( s_idxChannelDefn)->Get_series( s_idxSeriesDefn)->idCharacteristicType = valueGUID;
                    }
                }
            }
            break;
        } // end of switch
    } // end of data source

    //  MONITOR SETTINGS RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecMonitorSettings ) )
    {
        switch( typePhysical )
        {
            case ID_PHYS_TYPE_TIMESTAMPPQDIF:
            {
                TIMESTAMPPQDIF   valueDT = *( (TIMESTAMPPQDIF *) pdata );

                if( PQDIF_IsEqualGUID( tag, tagEffective ) )
                    s_monsett.tsEffective = valueDT;
                if( PQDIF_IsEqualGUID( tag, tagTimeInstalled ) )
                    s_monsett.tsInstalled = valueDT;
            }
            break;

            case ID_PHYS_TYPE_BOOLEAN4:
            {
                BOOL4   valueBOOL4 = *( (BOOL4 *) pdata );

                if( PQDIF_IsEqualGUID( tag, tagUseCalibration ) )
                    s_monsett.bUseCalibration = valueBOOL4;
                if( PQDIF_IsEqualGUID( tag, tagUseTransducer ) )
                    s_monsett.bUseTransducer = valueBOOL4;
            }
            break;

            case ID_PHYS_TYPE_UNS_INTEGER4:
            {
            }
            break;
            case ID_PHYS_TYPE_REAL8:
            {
                REAL8   valueREAL8 = *( (REAL8 *) pdata );
            }
            break;
            case ID_PHYS_TYPE_GUID:
            {
            }
            break;
        }
    }

    //  OBSERVATION RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecObservation ) )
    {
        switch( typePhysical )
        {

			case ID_PHYS_TYPE_INTEGER2: // 某些文件用groupID代表频率通道
			{
				INT2 valueINT2 = *( (INT2*)pdata );

				if( s_idxChannelInst >= 0 ) 
				{
					if ( PQDIF_IsEqualGUID ( tag, tagChannelGroupID ) )
					{
						s_observation.Get_channel( s_idxChannelInst )->channelFreq = valueINT2;
					}
				}
			}
			break;

            case ID_PHYS_TYPE_UNS_INTEGER4:
            {
                UINT4   valueUINT4 = *( (UINT4 *) pdata );
                
                if( PQDIF_IsEqualGUID( tag, tagTriggerMethodID ) )
                {
                    s_observation.iTriggered = valueUINT4;
                }

				if( s_idxChannelInst >= 0 ) 
				{
					if ( PQDIF_IsEqualGUID ( tag, tagChannelGroupID ) ) // 某些文件用groupID代表频率通道
					{
						s_observation.Get_channel( s_idxChannelInst )->channelFreq = valueUINT4;
					}
				}

                if( s_idxChannelInst >= 0 ) 
                {
                    if( PQDIF_IsEqualGUID( tag, tagTriggerMethodID ) )
                    {
                        s_observation.Get_channel( s_idxChannelInst )->idxChannel = valueUINT4;
                    }
                    else if( PQDIF_IsEqualGUID( tag, tagChannelDefnIdx ) )
                    {
                        s_observation.Get_channel( s_idxChannelInst )->idxChannelDefn = valueUINT4;
                    }
					/* // 不支持共享通道
                    if( s_idxSeriesInst  >= 0 )
                    {
                        if( PQDIF_IsEqualGUID( tag, tagSeriesShareChannelIdx ) )
                        {
                            s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->shared = TRUE;
                            s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->idxSharedChannel = valueUINT4;
                        }
                        else if( PQDIF_IsEqualGUID( tag, tagSeriesShareSeriesIdx ) )
                        {
                            s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->shared = TRUE;
                            s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->idxSharedSeries = valueUINT4;
                        }
                    }*/
                }
            }
            break;

            case ID_PHYS_TYPE_REAL8:
            {
                REAL8   valueREAL8 = *( (REAL8 *) pdata );

                if( s_idxChannelInst >= 0 ) 
                {
					if ( PQDIF_IsEqualGUID ( tag, tagChannelFrequency ))
					{
						s_observation.Get_channel( s_idxChannelInst )->channelFreq = valueREAL8;
					}

                    if( s_idxSeriesInst  >= 0 ) 
                    {
                        if( PQDIF_IsEqualGUID( tag, tagSeriesScale ) )
                        {
                            s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->dScale = valueREAL8;
                        }
                        else if( PQDIF_IsEqualGUID( tag, tagSeriesOffset ) )
                        {
                            s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->dOffset = valueREAL8;
                        }
                    }
                }
            }
            break;

            case ID_PHYS_TYPE_TIMESTAMPPQDIF:
            {
                TIMESTAMPPQDIF valueTS = *((TIMESTAMPPQDIF *) pdata );
                
                if( PQDIF_IsEqualGUID( tag, tagTimeCreate ) )
                {
                    s_observation.tsCreate = valueTS;
                }
                else if( PQDIF_IsEqualGUID( tag, tagTimeStart ) )
                {
                    // s_observation.tsStart = valueTS;
					s_observation.tsStart = CPQDTimeToLocalTime ( &valueTS );
                }
                else if( PQDIF_IsEqualGUID( tag, tagTimeTriggered ) )
                {
                    s_observation.tsTrigger = valueTS;
                }
            }
            break;

            case ID_PHYS_TYPE_GUID:
            {
                GUID    valueGUID = *((GUID *) pdata );
            }
            break;
        }
    }

    return TRUE;
}


BOOL acceptVector( const GUID& tag, INT1 typePhysical, c_vector *pvector, void *pdata, int level )
{
	Valid_Vector( s_arrayTags, level, tag, typePhysical, pvector );

    //  CONTAINER RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagContainer ) )
    {
        if( typePhysical == ID_PHYS_TYPE_UNS_INTEGER4 )
        {
            UINT4 * arrayVersion = (UINT4 *) pdata;

            if( PQDIF_IsEqualGUID( tag, tagVersionInfo ) )
            {
                s_container.iFormatVersionMajor = arrayVersion[ 0 ];
                s_container.iFormatVersionMinor = arrayVersion[ 1 ];
            }
        }

        if( typePhysical == ID_PHYS_TYPE_CHAR1 )
        {
            char *  pstring = (char *) pdata;
			long    countPoints = pvector->count; // 数组中数据的个数

			if ( PQDIF_IsEqualGUID ( tag, tagFileName ) )
			{
				memcpy ( s_container.szFileName, pstring, countPoints );
			}
			if ( PQDIF_IsEqualGUID ( tag, tagLanguage ) )
			{
				memcpy ( s_container.szLanguage, pstring, countPoints );
			}
        }
    }

    //  DATA SOURCE RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecDataSource ) )
    {
        switch( typePhysical )
        {
            case ID_PHYS_TYPE_CHAR1:
		    {
                //  Channel defn info?
                if( s_idxChannelDefn >= 0 )
                {
                    if( PQDIF_IsEqualGUID( tag, tagChannelName ) )
                    {
                       // strcpy( s_datasource.Get_channel( s_idxChannelDefn)->szChannelName, (char *) pdata );
						s_datasource.Get_channel( s_idxChannelDefn)->szChannelName = (char *) pdata;
                    }
                }

                //  Series defn info?
                if( s_idxChannelDefn >= 0 && s_idxSeriesDefn >= 0 )
                {
                }
			}
            break;
        } // end of switch()
    } // end of if()

    //  MONITOR SETTINGS RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecMonitorSettings ) )
    {
        switch( typePhysical )
        {
            case ID_PHYS_TYPE_REAL8:
            {
            }
            break;
        }
    }

    //  OBSERVATION RECORD
    if( PQDIF_IsEqualGUID( s_arrayTags[ 0 ], tagRecObservation ) )
    {
        //  First, call out the series values
        if( PQDIF_IsEqualGUID( tag, tagSeriesValues ) )
        {
            if( s_idxChannelInst >= 0 && s_idxSeriesInst  >= 0 )
            {
                long    countPoints = pvector->count; // 数组中数据的个数
                long    countPointsResolved = pvector->count;
                long    idxObservChannelDefn = s_observation.Get_channel( s_idxChannelInst )->idxChannelDefn; // index in data_source
                
                if( countPoints > 0 )
                {
                    s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->paData =  // double *
                            _NewResolvedSeries( s_idxChannelInst, s_idxSeriesInst, idxObservChannelDefn, countPoints, pdata, typePhysical, countPointsResolved );

                    s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->typePhysical = typePhysical;
                    //s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->nValues = countPoints;

					if (countPoints < 0)
					{
						countPoints = countPoints;
					}

                    s_observation.Get_channel( s_idxChannelInst )->Get_series( s_idxSeriesInst )->nTotalValues = countPoints;
                }
            }
        }

        //  Then check for everything else
        switch( typePhysical )
        {
            case ID_PHYS_TYPE_CHAR1:
            {
                char * valueString = (char *) pdata;

                if( PQDIF_IsEqualGUID( tag, tagObservationName ) )
                {
                    //strcpy( s_observation.szName, valueString );
					s_observation.szName = valueString;
                }
            }
            break;
            
            case ID_PHYS_TYPE_UNS_INTEGER4:
            {
                UINT4 * valuesUINT4 = (UINT4 *) pdata;

                if( PQDIF_IsEqualGUID( tag, tagObservationName ) && pvector->count > 0 )
                {
                    s_observation.idxTriggerChannel = valuesUINT4[ 0 ];
                }
            }
            break;
        }
    } // end of if()

    return TRUE;
}

double * _NewResolvedSeries
(
	long    idxChannel,
    long    idxSeries,
    long    idxChannelDefn,     //  If ptr is NULL, this is ignored // index in data_source
    long    countRawPoints,     //  If ptr is NULL, this is ignored // 数组中数据的个数
    void *  pvectSeriesArray,   //  Can be NULL                     // *pdata
    INT1    idPhysicalType,     //  If ptr is NULL, this is ignored
    long&   countPoints         //  ?
)
{
    double * raValues = NULL;

    //  If the vector pointer is NULL, then the data is being shared from another series.
    if( pvectSeriesArray )
    {
        //  Not shared ...  Get channel definition information
        if( idxChannelDefn >= 0 && idxChannelDefn < s_datasource.nChannel )
        {
            if( idxSeries >= 0 && idxSeries < s_datasource.Get_channel( idxChannelDefn)->nSeries )
            {
                UINT4   idStorageMethod;
                double  rScale;
                double  rOffset;

                //  Get info from series defn
                idStorageMethod = s_datasource.Get_channel( idxChannelDefn)->Get_series( idxSeries )->idMethod; // 全部都是ID_SERIES_METHOD_VALUES  The data in tagSeriesValues are a straight array of data points.

                //  Get channel instance information
				series_instance *p_Find_series_instance = s_observation.Get_channel( idxChannel )->Get_series( idxSeries );
				ASSERT (p_Find_series_instance != NULL);
                rScale  = p_Find_series_instance->dScale;
                rOffset = p_Find_series_instance->dOffset;

                //  Immediately resolve the series.
                raValues = _GenerateSeriesData( idStorageMethod, idPhysicalType, rScale, rOffset, countRawPoints, pvectSeriesArray, countPoints );
            }
        }
    }
    else // 通道数据共享 : 把共享数通道的数据拷贝到当前通道
    {
        //  Must be shared... find out which one to share from
        long    idxSharedChannel = s_observation.Get_channel( idxChannel )->Get_series( idxSeries )->idxSharedChannel;
        long    idxSharedSeries  = s_observation.Get_channel( idxChannel )->Get_series( idxSeries )->idxSharedSeries;
    
        //  See if we can make a copy of the data...
        if( idxSharedChannel >= 0 && idxSharedChannel < s_observation.nChannels &&
            idxSharedSeries >= 0  && idxSharedSeries  < s_observation.Get_channel( idxSharedChannel)->nSeries )
        {
            if( s_observation.Get_channel( idxSharedChannel )->Get_series( idxSharedSeries )->paData )
            {
                //  Copy it!
                countPoints = s_observation.Get_channel( idxSharedChannel )->Get_series( idxSharedSeries )->nTotalValues;
                raValues = new double[ countPoints ];
                memcpy( raValues, s_observation.Get_channel( idxSharedChannel )->Get_series( idxSharedSeries )->paData, countPoints * sizeof( double ) );
            }
        }
    }

    return raValues;
}

double * _GenerateSeriesData
( 
	UINT4   idStorageMethod, 
	INT1    idPhysicalType,
	double  rScale, 
	double  rOffset, 
	long    countRawPoints,
	void *  pvectSeriesArray,
	long&   countPoints
)
{
    double *    arValues = NULL;
    double *    prTempValues;
    long        idxPoint;
    // long        idxRaw;

    // countPoints = _GenerateSeriesCount( idStorageMethod, idPhysicalType, countRawPoints, pvectSeriesArray ); 
	// countPoints = countRawPoints;

    if( idStorageMethod & ID_SERIES_METHOD_VALUES )
    {
        if( countPoints > 0 && countPoints == countRawPoints )
        {
            arValues = new double[ countPoints ]; // why double ?
            prTempValues = arValues;

            for( idxPoint = 0; idxPoint < countPoints; idxPoint++, prTempValues++ )
            {
                _VectorArrayGetValue( pvectSeriesArray, idPhysicalType, idxPoint, *prTempValues ); // 从读取的文件缓冲区中读取数字，并放入结构体数组中
            }
        }
    }
    else // 去除了 ID_SERIES_METHOD_INCREMENT 的情况，目前没有使用
    {
        arValues = NULL;
    }

    //  使用了 Scale 和 offset 的情况 
    if( idStorageMethod & ID_SERIES_METHOD_SCALED )
    {
        if( arValues && countPoints > 0 )
        {
            prTempValues = arValues;
            for( idxPoint = 0; idxPoint < countPoints; idxPoint++, prTempValues++ )
            {
                *prTempValues *= rScale;
                *prTempValues += rOffset;
            } 
        }
    }

    return arValues;
}

BOOL _VectorArrayGetValue ( void *pdata, INT1 typePhysical, int idx, double& value )
{
    BOOL status = TRUE;

    if( pdata )
    {
        switch( typePhysical )
        {
			case ID_PHYS_TYPE_BOOLEAN1:
			{
				BOOL1 * pvalues = (BOOL1 *) pdata;
                value = (double) pvalues[ idx ];
			}
			break;
			case ID_PHYS_TYPE_BOOLEAN2:
			{
				BOOL2 * pvalues = (BOOL2 *) pdata;
                value = (double) pvalues[ idx ];
			}
			break;
			case ID_PHYS_TYPE_BOOLEAN4:
			{
				BOOL4 * pvalues = (BOOL4 *) pdata;
                value = (double) pvalues[ idx ];
			}
			break;

			case ID_PHYS_TYPE_CHAR1:
            {
                CHAR1 * pvalues = (CHAR1 *) pdata;
                value = (double) pvalues[ idx ];
            }
			break;
			case ID_PHYS_TYPE_CHAR2:
            {
                CHAR2 * pvalues = (CHAR2 *) pdata;
                value = (double) pvalues[ idx ];
            }
			break;

            case ID_PHYS_TYPE_INTEGER1:
            {
				// 从数组pdata中取出一个数，强制转成double，并放入结构体数组中
                INT1 * pvalues = (INT1 *) pdata;
                value = (double) pvalues[ idx ];
            }
            break;
            case ID_PHYS_TYPE_INTEGER2:
            {
                INT2 * pvalues = (INT2 *) pdata;
                value = (double) pvalues[ idx ];
            }
            break;
            case ID_PHYS_TYPE_INTEGER4: 
            {
                INT4 * pvalues = (INT4 *) pdata;
                value = (double) pvalues[ idx ];
            }
            break;

			case ID_PHYS_TYPE_UNS_INTEGER1:
			{
				UINT1 * pvalues = (UINT1 *) pdata;
                value = (double) pvalues[ idx ];
			}
			break;
			case ID_PHYS_TYPE_UNS_INTEGER2:
			{
				UINT2 * pvalues = (UINT2 *) pdata;
                value = (double) pvalues[ idx ];
			}
			break;
			case ID_PHYS_TYPE_UNS_INTEGER4:
			{
				//UINT4 * pvalues = (UINT4 *) pdata;
                value = (double)( ((UINT4 *)pdata)[idx]);
			}
			break;

            case ID_PHYS_TYPE_REAL4:
            {
                REAL4 * pvalues = (REAL4 *) pdata;
                value = (double) pvalues[ idx ];
            }
            break;

            case ID_PHYS_TYPE_REAL8: // max min avg cp95
            {
                REAL8 * pvalues = (REAL8 *) pdata;
                value = (double) pvalues[ idx ];
            }
            break;

            default:
                status = FALSE;
            break;
        }
    }
    else
    {
        status = FALSE;
    }

    return status;
}

/*
long _GenerateSeriesCount
( 
	UINT4   idStorageMethod,
	INT1    idPhysicalType,
	long    countRawPoints,
	void *  pvectSeriesArray
)
{
    long    countPoints = 0;

    if( idStorageMethod & ID_SERIES_METHOD_VALUES )
    {
        countPoints = countRawPoints;
    }
    else // 去除了 ID_SERIES_METHOD_INCREMENT 的情况，目前没有使用
    {
    }

    return countPoints;
} */

