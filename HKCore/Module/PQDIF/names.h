
#ifndef _NAMES_H_
#define _NAMES_H_

extern void InitNames( void );
extern int  GetTagCount( void );
extern char * GetTagInfo( int index, GUID& tag );
extern char * GetNameOfTag( const GUID& tag );
extern char * GetNameOfElementType( INT4 type );
extern char * GetNameOfPhysType( INT4 type );
extern long GetNumBytesOfType(long idType);
extern SIZE4 padSizeTo4Bytes( SIZE4 sizeOrig );

extern int GetIntegerIDCount( void );
extern char * GetIntegerIDInfo( int index, int& value );
extern char * GetIntegerIDInfo2( int index, int& value, GUID& tag );
extern char * GetIntegerIDOwner( int index );
extern char * GetIntegerIDInfoFromTag( const GUID& tag, INT4 valueID );


#endif // _NAMES_H_