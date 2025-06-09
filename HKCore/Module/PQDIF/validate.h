
#ifndef _VALIDATE_H_
#define _VALIDATE_H_

// ��������������Щ�����ķ�������

extern BOOL Valid_Init( const char * pathMain );
extern void Valid_Destroy( void );

extern BOOL Valid_BeginCollection
        ( 
        const   GUID *  arrayTags,
        int             level
        );
extern BOOL Valid_EndCollection
        (
        const   GUID *  arrayTags,
        int             level
        );
extern BOOL Valid_Scalar
        (
        const   GUID *      arrayTags,
                int         level,
        const   GUID&       tag, 
                INT1        typePhysical,
                void *      pdata
        );
extern BOOL Valid_Vector
        (
        const   GUID *      arrayTags,
                int         level,
        const   GUID&       tag, 
                INT1        typePhysical,
                c_vector *  pvector
        );
extern char * Valid_GetComment( void );

//  Gather information from the actual contents of the records
extern BOOL Valid_GetCompressionInfo( UINT4& style, UINT4& alg );
extern UINT4 Valid_GetTotalFileChecksum( void );



#endif // _VALIDATE_H_