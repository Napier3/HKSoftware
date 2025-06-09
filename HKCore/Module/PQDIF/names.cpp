/*
**  File name:          $Workfile: names.cpp $
**  Last modified:      $Modtime: 5/31/01 2:00p $
**  Last modified by:   $Author: Jack $
**
**  VCS archive path:   $Archive: /PQDIF/Document/Version15/GenerateCode/names.cpp $
**  VCS revision:       $Revision: 12 $ 
*/

#ifndef _NOSAMPLEI
//    #include "samplei_main.h"
#endif

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>


#include "pqdif_ph.h"
#include "pqdif_lg.h"
#include "pqdif_id.h"

#include "names.h"


//  Arrays and stuff to hold lists
#define MAX_TAG_NAMES       512
#define MAX_INTID_NAMES     512
#define MAX_TYPE_NAMES      32

struct TagName
{
	GUID    tag;
	char    name[ 64 ];
	unsigned long  DataID;
};

static  TagName     nameOfTags[ MAX_TAG_NAMES ];
static  int         countNames;


struct IntegerName
{
	INT4    value;
	GUID    tag;
	char    name[ 64 ];
	char    owner[ 64 ];
};

//  Physical value
static  IntegerName nameOfTypes[ MAX_TYPE_NAMES ];
static  int         countTypes;

//  Integer IDs
static  IntegerName nameOfIntID[ MAX_INTID_NAMES ];
static  int         countInstID;


//  Macros to add the tags to a GUID list
#define ADD_TAG_ENTRY( tagTHING )\
	nameOfTags[ countNames ].tag = tagTHING; \
	strcpy( nameOfTags[ countNames++ ].name , #tagTHING ); \
	assert( countNames < MAX_TAG_NAMES )

//  Macro to add the GUID IDs to the *same list*
#define ADD_ID_GUID_ENTRY( thing1, thing2 ) ADD_TAG_ENTRY( thing1 )

//  Macro to add integer ID to a list
#define ADD_ID_UINT4_ENTRY( thing1, thing2 ) \
	nameOfIntID[ countInstID ].value = thing1; \
	nameOfIntID[ countInstID ].tag = thing2; \
	strcpy( nameOfIntID[ countInstID ].name , #thing1 ); \
	strcpy( nameOfIntID[ countInstID++ ].owner, #thing2 );

//  Macro to add physical types to a list
#define ADD_PHYSTYPE_ENTRY( thing ) \
	nameOfTypes[ countTypes ].value = ID_PHYS_TYPE_##thing; \
	strcpy( nameOfTypes[ countTypes++ ].name , #thing );



int  GetTagCount( void )
{
	return countNames;
}


char * GetTagInfo( int index, GUID& tag )
{
	if( index >= 0 && index < countNames )
	{
		tag = nameOfTags[ index ].tag;
		return GetNameOfTag( tag );
	}

	return NULL;
}


char * GetNameOfTag( const GUID& tag )
{
	static  char * nothing = "< Unrecognized tag >";
	unsigned long nDataID = tag.Data1;

	for( int idx = 0; idx < countNames; idx++ )
	{
		//if( PQDIF_IsEqualGUID( tag, nameOfTags[ idx ].tag ) )
		//	return nameOfTags[ idx ].name;

		if (nDataID == nameOfTags[ idx ].tag.Data1)
		{
			return nameOfTags[ idx ].name;
		}
	}

	return nothing;
}


char * GetNameOfElementType( INT4 type )
{
	static  char *  nothing = "< Unrecognized element type >";
	static  char *  nameCollection = "Collection";
	static  char *  nameScalar     = "Scalar";
	static  char *  nameVector     = "Vector";

	switch( type )
	{
	case ID_ELEMENT_TYPE_COLLECTION:
		return nameCollection;

	case ID_ELEMENT_TYPE_SCALAR    :
		return nameScalar;

	case ID_ELEMENT_TYPE_VECTOR    :
		return nameVector;

	default:
		return nothing;
	}
}


char * GetNameOfPhysType( INT4 type )
{
	static  char * nothing = "< Unrecognized physical type >";

	for( int idx = 0; idx < countTypes; idx++ )
	{
		if( nameOfTypes[ idx ].value == type )
			return nameOfTypes[ idx ].name;
	}

	return nothing;
}


long GetNumBytesOfType(long idType)
{
	long    rc = 1L;

	switch (idType)
	{
	case ID_PHYS_TYPE_BOOLEAN1:
	case ID_PHYS_TYPE_CHAR1:
	case ID_PHYS_TYPE_INTEGER1:
	case ID_PHYS_TYPE_UNS_INTEGER1:
		rc = 1;
		break;

	case ID_PHYS_TYPE_INTEGER2:
	case ID_PHYS_TYPE_UNS_INTEGER2:
		rc = 2;
		break;

	case ID_PHYS_TYPE_INTEGER4:
	case ID_PHYS_TYPE_UNS_INTEGER4:
	case ID_PHYS_TYPE_REAL4:
		rc = 4;
		break;

	case ID_PHYS_TYPE_REAL8:
	case ID_PHYS_TYPE_COMPLEX8:
		rc = 8;
		break;

	case ID_PHYS_TYPE_COMPLEX16:
		rc = 16;
		break;

	case ID_PHYS_TYPE_TIMESTAMPPQDIF:
		rc = 12;
		assert( rc == sizeof( TIMESTAMPPQDIF ) );
		break;

	case ID_PHYS_TYPE_GUID:
		rc = 16;
		assert( rc == sizeof( GUID ) );
		break;

	default:
		rc = 1;
		break;
	}

	return rc;
}


SIZE4 padSizeTo4Bytes( SIZE4 sizeOrig )
{
	SIZE4   remainder;

	remainder = ( sizeOrig % 4 );

	if( remainder == 0 ) //  Already multiple of 4?
		return sizeOrig;

	return sizeOrig + ( 4 - remainder ); //  Pad it
}


int GetIntegerIDCount( void )
{
	return countInstID;
}


char * GetIntegerIDInfo( int index, int& value )
{
	static  char * nothing = NULL;

	if( index >= 0 && index < countInstID )
	{
		value = nameOfIntID[ index ].value;
		return nameOfIntID[ index ].name;
	}

	return nothing;
}

char * GetIntegerIDInfo2( int index, int& value, GUID& tag )
{
	static  char * nothing = NULL;

	if( index >= 0 && index < countInstID )
	{
		value = nameOfIntID[ index ].value;
		tag   = nameOfIntID[ index ].tag;
		return nameOfIntID[ index ].name;
	}

	return nothing;
}

char * GetIntegerIDOwner( int index )
{
	static  char * nothing = NULL;

	if( index >= 0 && index < countInstID )
	{
		return nameOfIntID[ index ].owner;
	}

	return nothing;
}

char * GetIntegerIDInfoFromTag( const GUID& tag, INT4 valueID )
{
	static char szConcat[256];
	//  Get owner tag name
	char * name = NULL;
	char * owner = GetNameOfTag( tag );

	bool bFirst = true;
	bool bConcat = false;

	szConcat[0] = 0;

	if( owner )
	{

		for( int index = 0; index < countInstID; index++ )
		{
			if ( strcmp( owner, nameOfIntID[ index ].owner ) == 0 )
			{
				//
				//
				//  Handle storage method tag specially
				//
				if( PQDIF_IsEqualGUID( tag, tagStorageMethodID ) )
				{
					if( valueID & nameOfIntID[ index ].value )
					{
						name = nameOfIntID[ index ].name;

						if (bFirst)
						{
							strcpy(szConcat, name);
							bFirst = false;
						}
						else
						{
							strcat(szConcat, " | ");
							strcat(szConcat, name);
						}
						name = szConcat;
					}
				}
				else
				{
					if( valueID == nameOfIntID[ index ].value )
					{
						//  Yup - return name of ID
						name = nameOfIntID[ index ].name;
						break;
					}
				} // if (tag == tagStorageMethodID) else
			} // if ( strcmp( owner, nameOfIntID[ index ].owner ) == 0 )
		} // for( int index = 0; index < countInstID; index++ )
	} // if( owner )

	return name;
}


void InitNames( void )
{
	//  Init
	countNames = 0;
	countTypes = 0;
	countInstID = 0;

	//  GUID names
	//  ----------
	//  Any record
	nameOfTags[ countNames ].tag = tagBlank       ;
	strcpy( nameOfTags[ countNames++ ].name , "< Blank >" );

	//  Get the tag names from an automatically-generated include file
#include "name_tag.inc"

	//  Get the ID (GUID and integer) names from an automatically-generated include file
#include "name_id.inc"

	//  Physical type names
	//  -------------------
	ADD_PHYSTYPE_ENTRY( BOOLEAN1 );
	ADD_PHYSTYPE_ENTRY( BOOLEAN2 );
	ADD_PHYSTYPE_ENTRY( BOOLEAN4 );
	ADD_PHYSTYPE_ENTRY( CHAR1 );
	ADD_PHYSTYPE_ENTRY( CHAR2 );
	ADD_PHYSTYPE_ENTRY( INTEGER1 );
	ADD_PHYSTYPE_ENTRY( INTEGER2 );
	ADD_PHYSTYPE_ENTRY( INTEGER4 );
	ADD_PHYSTYPE_ENTRY( UNS_INTEGER1 );
	ADD_PHYSTYPE_ENTRY( UNS_INTEGER2 );
	ADD_PHYSTYPE_ENTRY( UNS_INTEGER4 );
	ADD_PHYSTYPE_ENTRY( REAL4 );
	ADD_PHYSTYPE_ENTRY( REAL8 );
	ADD_PHYSTYPE_ENTRY( COMPLEX8 );
	ADD_PHYSTYPE_ENTRY( COMPLEX16 );
	ADD_PHYSTYPE_ENTRY( TIMESTAMPPQDIF );
	ADD_PHYSTYPE_ENTRY( GUID );


	long nIndex = 0;

	for (nIndex=0; nIndex<countNames; nIndex++)
	{
		nameOfTags[nIndex].DataID = nameOfTags[nIndex].tag.Data1;
	}


	return;
}


