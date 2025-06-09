#include "stdafx.h"

#include "pqdifr.h"

//  Limit how many items we actually display from an array (these
//  can get pretty big...)
#define MAX_ARRAY_PRINT     512


void printNewFile( const char * description )
{
#ifdef _LOG_PQDIF_

    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  description );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n" );
#endif
}

void printNewRecord( long pos )
{
    //CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n============================== New record (offset %ld)\n\n", (long) pos );
}

void printNewRecord( long pos, c_record_mainheader *p)
{   
#ifdef _LOG_PQDIF_

	char szType[64];

    strcpy(szType, "Unknown");

    //  Which type of record is it?
    //
    //  DATA SOURCE RECORD
    //  ==================
    if( PQDIF_IsEqualGUID( p->tagRecordType, tagRecDataSource ) )
    {
        strcpy(szType, "Data Source");
    }

    //  MONITOR SETTINGS RECORD
    //  =======================
    if( PQDIF_IsEqualGUID( p->tagRecordType, tagRecMonitorSettings ) )
    {
        strcpy(szType, "Monitor Settings");
    }

    //  OBSERVATION RECORD
    //  ==================
    if( PQDIF_IsEqualGUID( p->tagRecordType, tagRecObservation ) )
    {
        strcpy(szType, "Observation");
    }
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n============================== New %16s record (offset %ld)\n", szType, (long) pos );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,    "    sizeHeader: %d (%X)\n", p->sizeHeader    , p->sizeHeader    );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,    "      sizeData: %d (%X)\n", p->sizeData      , p->sizeData      );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,    "linkNextRecord: %d (%X)\n", p->linkNextRecord, p->linkNextRecord);
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,    "      checksum: %d (%X)\n", p->checksum      , p->checksum      );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,    "auiReserved[4]: %d, %d, %d, %d\n", p->auiReserved[0],p->auiReserved[1],p->auiReserved[2],p->auiReserved[3]);
#endif
}

BOOL printStartCollection( const GUID& tag, const GUID *arrayTags, int level)
{
#ifdef _LOG_PQDIF_

	printIndent( level, TRUE );

    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "-Collection -- tag: %s (level %d)\n", GetNameOfTag( tag ), level );
#endif

    if( !Valid_BeginCollection( arrayTags, level ) )
    {
#ifdef _LOG_PQDIF_
        printIndent( level );
        CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   | *** %s\n", Valid_GetComment() );
#endif
    }

    return TRUE;
}

void printEndCollection ( const GUID *arrayTags, int level )
{
    if( !Valid_EndCollection( arrayTags, level ) )
    {
#ifdef _LOG_PQDIF_
       printIndent( level );
        CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   +---- Problems were found in the above collection\n" );
        printIndent( level );
        CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   | *** %s\n", Valid_GetComment() );
#endif
    }

#ifdef _LOG_PQDIF_
    printIndent( level );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   +-(End of collection)\n" );
#endif
}

/* 在acceptScalar函数中被调用 */
BOOL printScalar( const GUID& tag, INT1 typePhysical, void *pdata, const GUID *arrayTags, int level )
{
#ifdef _LOG_PQDIF_
    printIndent( level );

    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   +-Scalar -- tag: %s", GetNameOfTag( tag ) );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " (type: %s)", GetNameOfPhysType( typePhysical ) );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n" );

    //  Just display the information

    switch( typePhysical )
    {
        case ID_PHYS_TYPE_CHAR1:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: '%c'\n", *( (char *) pdata ) );
            break;

        case ID_PHYS_TYPE_BOOLEAN4:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: '%s'\n",  *( (BOOL4 *) pdata ) != 0 ? "TRUE" : "FALSE" );
            break;

        case ID_PHYS_TYPE_INTEGER4:
            {
            char * psz = GetIntegerIDInfoFromTag(tag, *( (INT4 *) pdata ));

            printIndent( level );

            if (psz)
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: %ld - %s\n", *( (INT4 *) pdata ), psz );
            else
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: %ld\n", *( (INT4 *) pdata ) );
            }
            break;

        case ID_PHYS_TYPE_UNS_INTEGER4:
            {
            char * psz = GetIntegerIDInfoFromTag(tag, *( (UINT4 *) pdata ));

            printIndent( level );

            if (psz)
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: %lu - %s\n", *( (UINT4 *) pdata ), psz );
            else
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: %lu\n", *( (UINT4 *) pdata ) );
            }
            break;

        case ID_PHYS_TYPE_REAL8:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: %f\n", (double) *( (REAL8 *) pdata ) );
            break;

        case ID_PHYS_TYPE_REAL4:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: %f\n", (double) *( (REAL4 *) pdata ) );
            break;

        case ID_PHYS_TYPE_TIMESTAMPPQDIF:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: " );
            printTimeStamp( (TIMESTAMPPQDIF *) pdata );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n" );
            break;

        case ID_PHYS_TYPE_GUID:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: " );
            printGUID( (GUID *) pdata );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n");
            break;

        default:
            break;
    }
#endif

	/* Valid_Scalar似乎不应该放在打印函数中，如果打印函数被注释掉， Valid_Scalar函数也将不起作用 */
    //  Validate the scalar
    if( ! Valid_Scalar( arrayTags, level, tag, typePhysical, pdata ) )
    {
#ifdef _LOG_PQDIF_
        printIndent( level );
        CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   | *** %s\n", Valid_GetComment() );
#endif
    }

    return TRUE;
}

BOOL printVector
            ( 
                    const GUID&     tag, 
                    INT1            typePhysical,
                    c_vector *      pvector,
                    void *          pdata,
            const   GUID *          arrayTags,
                    int             level
            )
{
    INT4    idxValue;
#ifdef _LOG_PQDIF_

    printIndent( level );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   +-Vector -- tag: %s", GetNameOfTag( tag ) );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " (type: %s)", GetNameOfPhysType( typePhysical ) );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " [ %ld ]", pvector->count );
    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n" );

    switch( typePhysical )
        {
        case ID_PHYS_TYPE_CHAR1:
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  value: '%s'\n", (char *) pdata );
            break;

        case ID_PHYS_TYPE_INTEGER1:
            {
            INT1 *  ar;
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  values: " );
            ar = (INT1 *) pdata;
            for( idxValue = 0; idxValue < pvector->count; idxValue++ )
                {
                if( idxValue != 0 )
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  ", " );
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "%d", (short) ar[ idxValue ] );
                if( idxValue > MAX_ARRAY_PRINT )
                    {
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " ... " );
                    break;
                    }
                }
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n");
            }
            break;

        case ID_PHYS_TYPE_INTEGER4:
            {
            INT4 *  ar;
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  values: " );
            ar = (INT4 *) pdata;
            for( idxValue = 0; idxValue < pvector->count; idxValue++ )
                {
                if( idxValue != 0 )
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  ", " );
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "%ld", ar[ idxValue ] );
                if( idxValue > MAX_ARRAY_PRINT )
                    {
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " ... " );
                    break;
                    }
                }
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n");
            }
            break;

        case ID_PHYS_TYPE_UNS_INTEGER4:
            {
            UINT4 * ar;
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  values: " );
            ar = (UINT4 *) pdata;
            for( idxValue = 0; idxValue < pvector->count; idxValue++ )
                {
                if( idxValue != 0 )
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  ", " );
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "%lu", ar[ idxValue ] );
                if( idxValue > MAX_ARRAY_PRINT )
                    {
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " ... " );
                    break;
                    }
                }
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n");
            }
            break;

        case ID_PHYS_TYPE_REAL8:
            {
            REAL8 * ar;
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  values: " );
            ar = (REAL8 *) pdata;
            for( idxValue = 0; idxValue < pvector->count; idxValue++ )
                {
                if( idxValue != 0 )
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  ", " );
                CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "%f", ar[ idxValue ] );
                if( idxValue > MAX_ARRAY_PRINT )
                    {
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " ... " );
                    break;
                    }
                }
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n");
            }
            break;

        case ID_PHYS_TYPE_GUID:
            {
            GUID * ar;
            printIndent( level );
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |  values: " );
            ar = (GUID *) pdata;
            for( idxValue = 0; idxValue < pvector->count; idxValue++ )
                {
                if( idxValue != 0 )
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  ", " );
                printGUID( &( ar[ idxValue ] ) );
                if( idxValue > MAX_ARRAY_PRINT )
                    {
                    CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " ... " );
                    break;
                    }
                }
            CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "\n");
            }
            break;

        default:
            break;
        }
#endif

	//  Validate the vector
	if( ! Valid_Vector( arrayTags, level, tag, typePhysical, pvector ) )
	{
#ifdef _LOG_PQDIF_
		printIndent( level );
		CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   | *** %s\n", Valid_GetComment() );
#endif
	}

    return TRUE;
 }


 void printIndent( int levelCurrent, BOOL plus )
 {
#ifdef _LOG_PQDIF_
	 for( int idxLevel = 0; idxLevel < levelCurrent; idxLevel++ )
	 {
		 if( plus && idxLevel == ( levelCurrent - 1) )
			 CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   +" );
		 else
			 CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "   |" );
	 }
#endif
 }


void printTimeStamp        (TIMESTAMPPQDIF *    pts)
{
#ifdef _LOG_PQDIF_
	static  char    buffer[ 128 ];

	formatTimeStamp( buffer, pts );
	CLogPrint::LogFormatString(LOGLEVEL_TRACE,  buffer );
#endif
}


BOOL formatTimeStamp
        ( 
        char *              buffer, 
        TIMESTAMPPQDIF *    pts
        )
    {
    //  Translate to a CTime
    struct tm   tmTrans;
    time_t      ttTrans;
    long        daysSince1970;
	
            long    seconds;
            long    picoSeconds;
    const   double  oneSecPico = 1000000000.0;    //  Picoseconds (LONG_MAX=2147483647)
    const   double  roundHalfPico = 0.0000000005;    //  Picoseconds (LONG_MAX=2147483647)

    memset( &tmTrans, 0, sizeof( tmTrans ) );

    //  Fields in tm structure
    //      int tm_sec;     /* seconds after the minute - [0,59] */
    //      int tm_min;     /* minutes after the hour - [0,59] */
    //      int tm_hour;    /* hours since midnight - [0,23] */
    //      int tm_mday;    /* day of the month - [1,31] */
    //      int tm_mon;     /* months since January - [0,11] */
    //      int tm_year;    /* years since 1900 */
    //      int tm_wday;    /* days since Sunday - [0,6] */
    //      int tm_yday;    /* days since January 1 - [0,365] */
    //      int tm_isdst;   /* daylight savings time flag */

    daysSince1970 = pts->day - EXCEL_DAYCOUNT_ADJUST;
    ttTrans = ( daysSince1970 ) * SECONDS_PER_DAY;
    seconds = (long) pts->sec;
    ttTrans += seconds;
    
    //tmTrans = *localtime( &ttTrans );
    tmTrans = *gmtime( &ttTrans );

    //  Display the fractional seconds in picoseconds
    double fracSeconds = ( pts->sec - (double) seconds ) + roundHalfPico;
    picoSeconds = (long) ( fracSeconds * oneSecPico );

    //  Format the whole shebang
    sprintf( buffer, "%d/%d/%d %d:%d:%d.%09.9d", 
        tmTrans.tm_mon + 1,
        tmTrans.tm_mday,
        tmTrans.tm_year + 1900,
        tmTrans.tm_hour,
        tmTrans.tm_min,
        tmTrans.tm_sec,
        (int) picoSeconds );

    return TRUE;
    }


void printGUID (        GUID *  pguid        )
{
#ifdef _LOG_PQDIF_
	CLogPrint::LogFormatString(LOGLEVEL_TRACE,  "{%08.8lx-%04.4x-%04.4x-%02.2x%02.2x%02.2x%02.2x}",
		pguid->Data1,
		pguid->Data2,
		pguid->Data3,
		(short) pguid->Data4[ 0 ],
		(short) pguid->Data4[ 1 ],
		(short) pguid->Data4[ 2 ],
		(short) pguid->Data4[ 3 ]
	);

	char *  name = GetNameOfTag( *pguid );
	if( name )
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE,  " - %s", name );
	}
#endif
}

