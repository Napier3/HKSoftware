/*
**  File name:          $Workfile: validate.cpp $
**  Last modified:      $Modtime: 3/23/99 12:10p $
**  Last modified by:   $Author: Erich $
**
**  VCS archive path:   $Archive: /PQDIF/Native15/PQDIFr/validate.cpp $
**  VCS revision:       $Revision: 11 $ 
*/
#include "stdafx.h"
#include "pqdifr.h"

#include <vector>

using namespace std;

//  Local declarations
enum which_kind
{
	wk_Element,
	wk_Physical,
	wk_Required
};

//  Data structure to hold the logical information
#define MAX_LEVELS  10

typedef struct
{
	//  Static information
	char *      nameTag;        //  Allocated by strdup() -- use free() to destroy
	UINT4       typeElement;
	UINT4       typePhysical;
	UINT4       countExpected;  //  0 = no specific number
	BOOL4       required;

	//  State (dynamic) information
	int         countFound;
} LOGICAL;

typedef LOGICAL LOGICALBLOCK[ MAX_LEVELS ];

//typedef vector<LOGICAL> LOGICALBLOCK;

//typedef vector<LOGICALBLOCK *> CLogInfo;
typedef vector<LOGICAL *> CLogInfo;

static CLogInfo m_alogInfo;

//  Logical structure data
//static  LOGICALBLOCK *  m_alogInfo = NULL;
static  int             m_countInfo = 0;

//  Comment
// #define  _use_comment_
#ifdef _use_comment_
static  char    comment[ 512 ];
#endif

//  Actual data gleaned from the records
static  UINT4   styleCompression  = ID_COMP_STYLE_NONE;
static  UINT4   algCompression    = ID_COMP_ALG_NONE;
static  UINT4   checksumTotalFile = 0;


//  Local functions
static  int _Valid_FindTag( const GUID *arrayTags, int  level, const GUID&tag, BOOL reverse = FALSE );

static  int _Valid_FindOneTag
(
 const   GUID&       tag,
 int&        level
 );

static UINT4 _Valid_TransKind
( 
 const   char *      pSegment, 
 which_kind  whichKind
 );

static BOOL _Valid_ElementType
( 
 int     idxLine, 
 int     idxLevel,
 UINT1   typeElement
 );
static BOOL _Valid_PhysicalType
( 
 int     idxLine, 
 int     idxLevel,
 UINT1   typePhysical 
 );


//  Begins validation of a collection
//  against the logical information.
//
//  These functions return TRUE if everything is okay;
//  if they return FALSE, a comment has been generated.
//  (In this case, use _GetComment() to retrieve it.)
//
BOOL Valid_BeginCollection( const GUID * arrayTags, int level )
{
	BOOL    status = TRUE;

	int     idxLine;
	int     idxFirst;
	int     idxLast;

	idxFirst = _Valid_FindTag( arrayTags, level, arrayTags[ level ] );
	idxLast  = _Valid_FindTag( arrayTags, level, arrayTags[ level ], TRUE );

	if( idxFirst >= 0 && idxLast >= 0 )
	{
		//  Found it. Check the type.
		if( !_Valid_ElementType( idxFirst, level, ID_ELEMENT_TYPE_COLLECTION ) )
			status = FALSE;

		//  Reset the counts of the elements inside
		for( idxLine = idxFirst; idxLine <= idxLast; idxLine++ )
		{
			m_alogInfo[ idxLine ][ level + 1 ].countFound = 0;
		}
	}
	else
	{
		//  Did not find it -- use the default comment
		status = FALSE;
	}

	return status;
}


//  Finishes up validation of a collection;
//  notes any required tags which are missing.
//
BOOL Valid_EndCollection( const   GUID *  arrayTags, int level )
{
	BOOL    status = TRUE;
	BOOL    requiresWarning = FALSE;

	int     idxLine;
	int     idxFirst;
	int     idxLast;
	int     idxLevelToCheck;

	//  Special case: sharing series data
	int     idxShareChannel;
	int     idxShareSeries;
	int     levelChannel;
	int     levelSeries;

	static char *  namePrevTag = "";


	//  Check through all the items in this level of the collection and see
	//  that all required tags have been included.
	idxFirst = _Valid_FindTag( arrayTags, level, arrayTags[ level ] );
	idxLast  = _Valid_FindTag( arrayTags, level, arrayTags[ level ], TRUE );

	if( idxFirst >= 0 && idxLast >= 0 )
	{
		//  Check the required flag for each line
		//  Check the next hierarchy level 
		idxLevelToCheck = level + 1;

		for( idxLine = idxFirst; idxLine <= idxLast; idxLine++ )
		{
			//  Have the required contents of the collection been found?
			if( m_alogInfo[ idxLine ][ idxLevelToCheck ].required 
				&& strcmp( m_alogInfo[ idxLine ][ idxLevelToCheck ].nameTag, namePrevTag ) != 0 )
			{
				if( m_alogInfo[ idxLine ][ idxLevelToCheck ].countFound < 1 )
				{
					requiresWarning = TRUE;

					//  SPECIAL CASES
					//  ... things we should not complain about
					if( strcmp( m_alogInfo[ idxLine ][ idxLevelToCheck ].nameTag, "tagSeriesValues" ) == 0 )
					{
						//  Did we get tags for shared data series?
						idxShareChannel = _Valid_FindOneTag( tagSeriesShareChannelIdx, levelChannel );
						idxShareSeries  = _Valid_FindOneTag( tagSeriesShareSeriesIdx, levelSeries );

						if( idxShareChannel >= 0 && idxShareSeries >= 0 )
						{
							if( m_alogInfo[ idxShareChannel ][ levelChannel ].countFound > 0 &&
								m_alogInfo[ idxShareSeries ][ levelSeries ].countFound > 0 )
							{
								//  This is okay. No warnings necessary.
								requiresWarning = FALSE;
							}
						}
					}

					if( requiresWarning )
					{
						//
						//
						//  I had to increase the size of comment to 512 to
						//  fix a hard to find bug.  While I was at it, I
						//  changed strcat to strncat.
						//
						status = FALSE;

						//  Remember this tag and don't complain about it again
						namePrevTag = m_alogInfo[ idxLine ][ idxLevelToCheck ].nameTag;
					}
				}
			}

			//  Mark this collection as being found...
			m_alogInfo[ idxLine ][ level ].countFound++;
		}
	}

	return status;
}


BOOL Valid_Scalar( const GUID *arrayTags, int level, const GUID&tag,  INT1 typePhysical, void * pdata )
{
	BOOL    status = TRUE;
	int     idxLine;

#ifdef _use_comment_
	strcpy( comment, "" );
#endif

	idxLine = _Valid_FindTag( arrayTags, level + 1, tag );

	if( idxLine >= 0 )
	{
		//  Found it!
		//  Are the element & physical types correct?
		if( !_Valid_ElementType( idxLine, level + 1, ID_ELEMENT_TYPE_SCALAR ) )
			status = FALSE;

		if( !_Valid_PhysicalType( idxLine, level + 1, typePhysical ) )
			status = FALSE;

		if( status )
			m_alogInfo[ idxLine ][ level + 1 ].countFound++;

		//  Is this something we need to keep?
		if( status )
		{
			//  Compression?
			if( PQDIF_IsEqualGUID( tag, tagCompressionStyleID ) )
			{
				styleCompression = *( (UINT4 *) pdata );
			}
			if( PQDIF_IsEqualGUID( tag, tagCompressionAlgorithmID ) )
			{
				algCompression = *( (UINT4 *) pdata );
			}
			if( PQDIF_IsEqualGUID( tag, tagCompressionChecksum ) )
			{
				checksumTotalFile = *( (UINT4 *) pdata );
			}
		}
	}
	else
	{
		//  Did not find it -- use the default comment
		status = FALSE;
	}

	return status;
}


BOOL Valid_Vector
(
 const   GUID *      arrayTags,
 int         level,
 const   GUID&       tag, 
 INT1        typePhysical,
 c_vector *  pvector
 )
{
	BOOL    status = TRUE;
	int     idxLine;

	//  Init
#ifdef _use_comment_
	strcpy( comment, "" );
#endif

	pvector = NULL; //  This parameter is currently unused

	idxLine = _Valid_FindTag( arrayTags, level + 1, tag );

	if( idxLine >= 0 )
	{
		//  Found it!
		//  Are the element & physical types correct?
		if( !_Valid_ElementType( idxLine, level + 1, ID_ELEMENT_TYPE_VECTOR ) )
			status = FALSE;

		if( !_Valid_PhysicalType( idxLine, level + 1, typePhysical ) )
			status = FALSE;

		if( status )
			m_alogInfo[ idxLine ][ level + 1 ].countFound++;
	}
	else
	{
		//  Did not find it -- use the default comment
		status = FALSE;
	}

	return status;
}


char * Valid_GetComment( void )
{
#ifdef _use_comment_
	return comment;
#else
	return NULL;
#endif
}


BOOL Valid_GetCompressionInfo( UINT4& style, UINT4& alg )
{
	style = styleCompression;
	alg = algCompression;

	return TRUE;
}

UINT4 Valid_GetTotalFileChecksum( void )
{
	return checksumTotalFile;
}


//  INIT/DESTROY
//  ============
//  Reads the logical structure file
//

//  Logical structure file info
const   char    fnameLogical[] = "logical.txt";
const   char    sepLogical[] = "\t";

//  Fields from file:
//  =================
enum field_idx
{
	fi_NameTag = 0,
	fi_ElementKindID,
	fi_PhysicalKindID,
	fi_RequiredKindID,
	fi_CountExpected,

	fi_TotalColumns
};
/* 说白了，就是把logical.txt中的表示结构字符串的字符串，全部存储到一个结构体里边，并且这些字符串的逻辑关系不变 */
BOOL Valid_Init( const char * pathMain )
{
	BOOL    status = FALSE;
	static  char    pathLogicalSpecification[ _MAX_PATH ];
	static  char    buffLine[ 1024 ];
	FILE *  pfile;

	int         idxLine;
	int         idxLevel;
	field_idx   idxField;

	//  Parsing
	int     idxCol;
	char *  pSegment;

	//  Open file
	memset ( pathLogicalSpecification, 0, sizeof(pathLogicalSpecification) );
	strcpy( pathLogicalSpecification, pathMain );
	strcat( pathLogicalSpecification, fnameLogical );
	pfile = fopen( pathLogicalSpecification, "rt" ); /* 只读打开一个文本文件 */

	if( pfile )
	{
		//  Init
		idxLine = 0;
		//        m_alogInfo[idxLine] = (LOGICALBLOCK *) calloc( 1, sizeof( LOGICALBLOCK ) );
		//        m_alogInfo.push_back(lb);
		//        m_alogInfo = (LOGICALBLOCK *) calloc( idxLine + 1, sizeof( LOGICALBLOCK ) );

		//  Read through the lines in the text file
		while( fgets( buffLine, sizeof( buffLine ), pfile ) ) /* 读取一行 */
		{
			LOGICAL * p = (LOGICAL *) calloc( MAX_LEVELS, sizeof( LOGICAL ) ); /* 此内存原先没有被释放，导致了内存泄露 */
			m_alogInfo.push_back(p);

			//  Parse through each line
			idxCol = 0;
			pSegment = strtok( buffLine, sepLogical );
			while( pSegment )
			{
				//  Use this column?
				idxLevel = idxCol / fi_TotalColumns;
				idxField = (field_idx)( idxCol % fi_TotalColumns );
				switch( idxField )
				{
				case fi_NameTag:
					m_alogInfo[ idxLine ][ idxLevel ].nameTag = strdup( pSegment ); /* 动态申请的字符串,需用free释放 */
					break;

				case fi_ElementKindID:
					m_alogInfo[ idxLine ][ idxLevel ].typeElement = _Valid_TransKind( pSegment, wk_Element );
					break;

				case fi_PhysicalKindID:
					m_alogInfo[ idxLine ][ idxLevel ].typePhysical = _Valid_TransKind( pSegment, wk_Physical );
					break;

				case fi_RequiredKindID:
					m_alogInfo[ idxLine ][ idxLevel ].required = (BOOL4) _Valid_TransKind( pSegment, wk_Required );
					break;

				case fi_CountExpected:
					m_alogInfo[ idxLine ][ idxLevel ].countExpected = atoi( pSegment );
					break;
				}

				//  Next segment
				pSegment = strtok( NULL, sepLogical );
				idxCol++;
			}   //  while( pSegment )

			//  Try to get the next line
			idxLine++;
			//            m_alogInfo = (LOGICALBLOCK *) realloc( m_alogInfo, ( idxLine + 1 ) * sizeof( LOGICALBLOCK ) );
			//            memset( &( m_alogInfo[ idxLine ] ), 0, sizeof( m_alogInfo[ 0 ] ) );
		}   //  while( fgets... )

		//  This should be the final count
		m_countInfo = idxLine;
		fclose( pfile );

		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "Read %d lines from file 'logical.txt'\n", (int) m_countInfo );

		status = TRUE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "*** Could not open file 'logical.txt'\n" );
	}

	return status;
}


void Valid_Destroy( void )
{
	//if( m_alogInfo )
	{
		for( int idxLine = 0; idxLine < m_countInfo; idxLine++ )
		{
			for( int idxLevel = 0; idxLevel < MAX_LEVELS; idxLevel++ )
			{
				if( m_alogInfo[ idxLine ][ idxLevel ].nameTag )
				{
					free( m_alogInfo[ idxLine ][ idxLevel ].nameTag );
				}
			}

			/* 程序中原先缺少了这一行，没有被释放，导致了内存泄露 */
			free ( m_alogInfo[idxLine] ); /* add by yp.w */
		}

		//free( m_alogInfo );
	}
}


static  int _Valid_FindTag( const GUID *arrayTags, int  level, const GUID& tag, BOOL  reverse)
{
	int     idxRet = -1;

	BOOL    matched;

	int     idxLine;

	int     idxLevel;
	char *  nameThisTag;
	char *  nameHierarchTag;

	//  What's the name of this tag?
	nameThisTag = GetNameOfTag( tag );
	//    if( nameThisTag && m_alogInfo )

	if( nameThisTag)
	{
		if( reverse )
			idxLine = m_countInfo - 1;
		else
			idxLine = 0;

		for(;;)
		{
			//  Check if we should continue the loop
			if( reverse )
			{
				if( idxLine < 0 )
					break;
			}
			else
			{
				if( idxLine >= m_countInfo )
					break;
			}

			//  Check the hierarchy first.
			//  Let's assume it will match them all...
			matched = TRUE;

			for( idxLevel = 0; idxLevel < level; idxLevel++ )
			{
				//  Check this level of the hierarchy...
				nameHierarchTag = GetNameOfTag( arrayTags[ idxLevel ] );

				if( nameHierarchTag && m_alogInfo[ idxLine ][ idxLevel ].nameTag )
				{
					if( strcmp( m_alogInfo[ idxLine ][ idxLevel ].nameTag, nameHierarchTag ) == 0 )
					{
						//  It matched! (But we assumed it would.)
					}
					else
					{
						//  It didn't match...
						matched = FALSE;
					}
				}
				else
				{
					//  One of the strings not available.
				}
			}

			//  Did all the levels match?
			if( matched )
			{
				//  Did the tag itself match?
				if( nameThisTag && m_alogInfo[ idxLine ][ level ].nameTag )
				{
					if( strcmp( m_alogInfo[ idxLine ][ level ].nameTag, nameThisTag ) == 0 )
					{
						//  Yup! Everything matched.
						idxRet = idxLine;
						break;
					}
				}
				else
				{
					//  One of the strings not available.
				}
			}

			//  Inc/dec
			if( reverse )
			{
				idxLine--;
			}
			else
			{
				idxLine++;
			}
		}

		//  Did we match it?
		if( idxRet < 0 )
		{
			//  Nope ...
#ifdef _use_comment_
			sprintf( comment, "The tag %s could not be matched. ", nameThisTag );
#endif
		}
	}
	else
	{
#ifdef _use_comment_
		strcat( comment, "No logical structure information found. Unable to validate. " );
#endif
	}

	return idxRet;
}


static  int _Valid_FindOneTag( const   GUID&       tag, int&        level )
{
	int     idxRet = -1;

	int     idxLine;
	int     idxLevel;
	int     countLevels = MAX_LEVELS;
	char *  nameThisTag;

	//  What's the name of this tag?
	nameThisTag = GetNameOfTag( tag );

	if( nameThisTag )
//    if( nameThisTag && m_alogInfo )
	{
		//  Yup, we recognize it ...
		//  See if we can find it in the list.
		for( idxLine = 0; idxLine < m_countInfo; idxLine++ )
		{
			for( idxLevel = 0; idxLevel < countLevels; idxLevel++ )
			{
				//  Check this level of the hierarchy...
				if( m_alogInfo[ idxLine ][ idxLevel ].nameTag )
				{
					if( strcmp( m_alogInfo[ idxLine ][ idxLevel ].nameTag, nameThisTag ) == 0 )
					{
						idxRet = idxLine;
						level = idxLevel;
						break;
					}
				}
			}
		}
	}

	return idxRet;
}



//  KIND/TYPE TRANSLATION
//  =====================

typedef struct
{
	which_kind  wk;
	UINT1       from;
	UINT1       to;
}   KTTRANS;

static  KTTRANS     infoTransKT[] = 
{
	//  ELEMENT
	{   wk_Element, 1,  ID_ELEMENT_TYPE_COLLECTION  } ,
	{   wk_Element, 2,  ID_ELEMENT_TYPE_SCALAR      } ,
	{   wk_Element, 3,  ID_ELEMENT_TYPE_VECTOR      } ,

	//  PHYSICAL
	{   wk_Physical, 1,  ID_PHYS_TYPE_BOOLEAN1        } ,
	{   wk_Physical, 2,  ID_PHYS_TYPE_BOOLEAN2        } ,
	{   wk_Physical, 3,  ID_PHYS_TYPE_BOOLEAN4        } ,

	{   wk_Physical, 4,  ID_PHYS_TYPE_CHAR1           } ,
	{   wk_Physical, 5,  ID_PHYS_TYPE_CHAR2           } ,

	{   wk_Physical, 6,  ID_PHYS_TYPE_INTEGER1        } ,
	{   wk_Physical, 7,  ID_PHYS_TYPE_INTEGER2        } ,
	{   wk_Physical, 8,  ID_PHYS_TYPE_INTEGER4        } ,

	{   wk_Physical, 9,  ID_PHYS_TYPE_UNS_INTEGER1    } ,
	{   wk_Physical, 10, ID_PHYS_TYPE_UNS_INTEGER2    } ,
	{   wk_Physical, 11, ID_PHYS_TYPE_UNS_INTEGER4    } ,

	{   wk_Physical, 12, ID_PHYS_TYPE_REAL4           } ,
	{   wk_Physical, 13, ID_PHYS_TYPE_REAL8           } ,
	{   wk_Physical, 14, ID_PHYS_TYPE_COMPLEX8        } ,
	{   wk_Physical, 15, ID_PHYS_TYPE_COMPLEX16       } ,

	{   wk_Physical, 16, ID_PHYS_TYPE_TIMESTAMPPQDIF  } ,

	{   wk_Physical, 17, ID_PHYS_TYPE_GUID            } ,

	//  REQUIRED
	{   wk_Required, 1,  TRUE       } ,
	{   wk_Required, 2,  FALSE      } ,
};
const   int countTransKT = ( sizeof( infoTransKT ) / sizeof( infoTransKT[ 0 ] ) );


static UINT4 _Valid_TransKind
( 
 const   char *      pSegment, 
 which_kind  whichKind
 )
{
	UINT4   rc = 0;
	UINT1   fromSegment = (UINT1) atoi( pSegment );

	int     idx;

	for( idx = 0; idx < countTransKT; idx++ )
	{
		if(    infoTransKT[ idx ].wk   == whichKind
			&& infoTransKT[ idx ].from == fromSegment )
		{
			//  Got it!
			rc = (UINT4) infoTransKT[ idx ].to;
		}
	}

	return rc;
}


//  TYPE CHECKS
//  ===========
static BOOL _Valid_ElementType
( 
 int     idxLine, 
 int     idxLevel,
 UINT1   typeElement
 )
{
	BOOL    status = FALSE;

	//  Match?
	if( m_alogInfo[ idxLine ][ idxLevel ].typeElement == typeElement )
		status = TRUE;

	//  Generate comment if necessary
	if( !status )
	{
#ifdef _use_comment_
		strcat( comment, "Incorrect element type found: " );
		strcat( comment, GetNameOfElementType( typeElement ) );
		strcat( comment, " (expected " );
		strcat( comment, GetNameOfElementType( m_alogInfo[ idxLine ][ idxLevel ].typeElement ) );
		strcat( comment, "). " );
#endif
	}

	return status;
}


static BOOL _Valid_PhysicalType
( 
 int     idxLine, 
 int     idxLevel,
 UINT1   typePhysical 
 )
{
	BOOL    status = FALSE;

	//  Should we skip the match entirely?
	if( m_alogInfo[ idxLine ][ idxLevel ].typePhysical == 0 )
	{
		//  In some cases, the physical type does not need to be matched.
		status = TRUE;
	}
	else
	{
		//  Match?
		if( m_alogInfo[ idxLine ][ idxLevel ].typePhysical == typePhysical )
			status = TRUE;

		//  Generate comment if necessary
		if( !status )
		{
#ifdef _use_comment_
			strcat( comment, "Incorrect physical type found: " );
			strcat( comment, GetNameOfPhysType( typePhysical ) );
			strcat( comment, " (expected " );
			strcat( comment, GetNameOfPhysType( m_alogInfo[ idxLine ][ idxLevel ].typePhysical ) );
			strcat( comment, "). " );
#endif
		}
	}

	return status;
}

