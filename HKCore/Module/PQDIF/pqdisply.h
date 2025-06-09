
#ifndef _PQ_DISPLY_
#define _PQ_DISPLY_

extern void printNewFile( const char * description );

extern void printNewRecord( long pos );
extern void printNewRecord( long    pos, c_record_mainheader *p);

extern BOOL printStartCollection
        ( 
        const   GUID&   tag,
        const   GUID *  arrayTags,
                int     level
        );

extern void printEndCollection
        (
        const   GUID *  arrayTags,
                int     level
        );

extern BOOL printScalar
        ( 
                const GUID&     tag,
                //c_scalar *      pscalar,
                INT1            typePhysical,
                void *          pdata,
        const   GUID *          arrayTags,
                int             level
        );

extern BOOL printVector
        ( 
                const GUID&     tag, 
                INT1            typePhysical,
                c_vector *      pvector,
                void *          pdata,
        const   GUID *          arrayTags,
                int             level
        );

extern void printTimeStamp
        (
        TIMESTAMPPQDIF *    pts
        );

extern BOOL formatTimeStamp
        ( 
        char *              buffer, 
        TIMESTAMPPQDIF *    pts
        );

extern void printGUID
        (
        GUID *  pguid
        );

extern void printIndent( int levelCurrent, BOOL plus = FALSE );


#endif // _PQ_DISPLY_