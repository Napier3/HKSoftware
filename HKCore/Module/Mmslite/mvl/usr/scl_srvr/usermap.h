#ifndef USERMAP_INCLUDED
#define USERMAP_INCLUDED
/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2004-2005 All Rights Reserved					*/
/*									*/
/* MODULE NAME : usermap.h						*/
/* PRODUCT(S)  : MMS-EASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Data mapping structures and functions used by SCL Server	*/
/*	sample application.						*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 04/08/08  JRB    10     Chg () to (ST_VOID) in prototype.		*/
/* 07/10/07  CRM    09     Added opcInitialValue to DATA_MAP typedef	*/
/* 04/16/07  CRM    08     Added "writable" flag to DATA_MAP typedef.	*/
/* 03/05/07  JRB    07     Chg opcItemName from array to ptr.		*/
/* 03/20/06  JRB    06     Del all_obj_create/destroy (now in scl_srvr.c)*/
/* 09/22/05  JRB    05     Del opc protos & opcServerInfoHead.		*/
/* 07/13/05  JRB    04     Chg datamap_cfg_read args.			*/
/*			   Add datamap_cfg_destroy.			*/
/*			   Add all_obj_create/destroy.			*/
/*			   Add datamap_user_oper, datamap_user_leaf.	*/
/* 03/17/05  JRB    03     Add ifdef __cplusplus to work with C++ code.	*/
/*			   Cleanup IEC_61850_SER.. sections.		*/
/* 01/18/05  JRB    02     Add opcGroup for IEC_61850_SER..		*/
/*			   Add TRACK_INFO & datamap_leaf_opc_client.	*/
/* 08/05/04  JRB    01     Initial Revision.				*/
/************************************************************************/
#include "scl.h"	/* need SCL_INFO	*/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(IEC_61850_SERVER_OPC_CLIENT)
#include "opcmap.h"	/* need OPC_GROUP, OPC_SERVER, etc.	*/
#endif

/************************************************************************/
/*			DATA_MAP structure				*/
/* This structure is used to store each entry from a data mapping	*/
/* configuration file.							*/
/* Each structure represents 1 line from the file.			*/
/************************************************************************/
typedef struct
  {
  ST_CHAR ldevice [MAX_IDENT_LEN+1];	/* Logical Device name	*/
  ST_CHAR leaf [MAX_IDENT_LEN+1];	/* "leaf" name		*/
  /* This is a user-defined parameter to help the user to map MMS data	*/
  /* to real user data.  This may be replaced with any			*/
  /* parameter that may be useful for mapping data.			*/
  /* In this example it is just a string read from the mapping file.	*/
  ST_CHAR usr_data_info [MAX_IDENT_LEN+1];

  ST_VOID *dataPtr;	/* Pointer to data storage for this	*/
			/* leaf. Also used as unique handle	*/
			/* for sorting/finding			*/
  RUNTIME_TYPE *dataType;	/* data type of this leaf	*/

#if defined(IEC_61850_SERVER_OPC_CLIENT)
  ST_CHAR opcServerName [MAX_IDENT_LEN+1];
  ST_CHAR *opcItemName;	/* may be long so just point to appropriate buf	*/
  ST_CHAR opcGroupName [MAX_IDENT_LEN+1];	/* OPC Group Name	*/
						/* Use "IOClass" name	*/
						/* from "opcmap.cfg"	*/
  ST_CHAR *opcInitialValue; /* may be long so just point to appropriate buf */
  ST_VOID *qualityPtr;		/* Pointer to nearest Quality		*/
				/* attribute for this leaf		*/
  ST_VOID *timePtr;		/* Pointer to nearest Timestamp	*/
				/* attribute for this leaf		*/
  HANDLE opcItemHandle;	/* handle returned from opcClientGroupAdd	*/
  OPC_GROUP *opcGroup;
  ST_BOOLEAN writable;	/* y = SD_TRUE, n = SD_FALSE	*/
#endif
  } DATA_MAP;

/************************************************************************/
/*			DATA_MAP_HEAD structure				*/
/************************************************************************/
typedef struct
  {
  DATA_MAP **map_arr;	/* Array of ptrs to DATA_MAP structures	*/
			/* allocated and initialized when cfg file read	*/
  ST_UINT map_count;	/* num of entries in array		*/
  } DATA_MAP_HEAD;

#define MAX_NEST_LEVEL	50

/************************************************************************/
/*			TRACK_INFO structure				*/
/************************************************************************/
typedef struct
  {
  ST_UINT primdata_num;	/* # of primitive data elements in variable	*/
			/* must account for arrays of structs.	*/
  ST_INT data_offset;
  ST_INT str_nest;			/* current struct nest level	*/
  /* rt_type of start of structs containing this leaf. First entry is 	*/
  /* top level struct, next is lower level struct, etc.			*/
  RUNTIME_TYPE *rt_type_str_start [MAX_NEST_LEVEL];
  ST_INT data_offset_str_start [MAX_NEST_LEVEL];
  } TRACK_INFO;

/************************************************************************/
/*			datamap_cfg_read				*/
/* Reads data mapping configuration file & maps the data for all	*/
/* variables in the global VMD "mvl_vmd".				*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET datamap_cfg_read (
	ST_CHAR *in_filename,		/* input cfg file name	*/
	ST_CHAR *out_filename);		/* output cfg file name	*/

/************************************************************************/
/*			datamap_cfg_destroy				*/
/* Unmap all data mapped by datamap_cfg_read and free associated buffers.*/
/* CRITITAL: must be called BEFORE variables removed, or it will be	*/
/*   impossible to remove the mapping.					*/
/************************************************************************/
ST_VOID datamap_cfg_destroy (ST_VOID);

/************************************************************************/
/*			any_cfg_count					*/
/* Count the number of "useful" lines in a CFG file.			*/
/* NOTE: Ignore empty lines or lines beginning with '#'.		*/
/************************************************************************/
ST_INT any_cfg_count (ST_CHAR *in_filename);


#if defined(IEC_61850_SERVER_OPC_CLIENT)	/* extra for this app	*/
/************************************************************************/
/*			datamap_leaf_opc_client				*/
/* Perform extra mapping for "IEC 61850 Server to OPC Client interface"	*/
/* application.								*/
/* Not used by MMS-Lite sample applications.				*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET datamap_leaf_opc_client (
	DATA_MAP *map_entry,	/* map entry for this leaf	*/
	MVL_VAR_ASSOC *var,	/* Variable (Logical Node) info		*/
	ST_CHAR *comp_name,
	TRACK_INFO *track_info);

#endif	/* IEC_61850_SERVER_OPC_CLIENT	*/


/************************************************************************/
/* If usermap.c is compiled with DATAMAP_USER_ENABLED defined, these	*/
/* user functions are called to do extra mapping or initialization.	*/
/************************************************************************/
ST_VOID datamap_user_oper (ST_CHAR *dom_name, ST_CHAR *oper_name);
ST_VOID datamap_user_leaf (DATA_MAP *map_entry);

#ifdef __cplusplus
}
#endif

#endif	/* !USERMAP_INCLUDED	*/
