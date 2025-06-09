
#ifndef _PQ_READ_H_
#define _PQ_READ_H_

#include "pqdexamp.h"

//  This keeps track of where we are in the PQDIF hierarchy.
//  This particularly array allows up to 16 levels of hierarchy, but a standard PQDIF file has only 6 levels.
extern  GUID  s_arrayTags[];

//  Example "proprietary" structures for reading data into.
extern   container_example       s_container;
extern   datasource_example      s_datasource;
extern   monitorsettings_example s_monsett;
extern   observation_example     s_observation;

//  Current channel/series defn indices (used if we are reading a data source record).
extern  long    s_idxChannelDefn;
extern  long    s_idxSeriesDefn;

//  Current channel settings index (used if we are reading a monitor settings record).
extern  long    s_idxChannelSett;

//  Current channel/series instance indices (used if we are reading an observation record).
extern  long    s_idxChannelInst;
extern  long    s_idxSeriesInst;


extern void acceptNewRecord( long pos, const GUID& tag );

extern int endOfRecord( void );

extern BOOL acceptCollection( const GUID& tag, int level );

extern void endOfCollection( int level );

extern BOOL acceptScalar( const GUID& tag, INT1 typePhysical, void *pdata, int level );

extern BOOL acceptVector( const GUID& tag, INT1 typePhysical, c_vector *pvector, void *pdata, int level );


#endif // _PQ_READ_H_