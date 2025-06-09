#ifndef SCL_INCLUDED
#define SCL_INCLUDED
/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2004-2004 All Rights Reserved					*/
/*									*/
/* MODULE NAME : scl.h							*/
/* PRODUCT(S)  : MMS-EASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	SCL main header file.						*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 10/30/06  JRB    12     scl2_datatype_create_all: all args changed.	*/
/*			   scl2_ld_create_all: add vmd_ctrl, is_client args.*/
/*			   Add type_id to SCL_LN, SCL_LNTYPE.		*/
/*			   Chg SCL2_BTYPE.				*/
/* 08/04/06  MDE    11     Added scl_debug_mode, scl2_add_btype, etc.	*/
/* 07/26/06  JRB    10     Add structs,functs for parsing Communication.*/
/* 04/19/06  JRB    09	   Add maxClient to SCL_RCB for "RptEnabled max".*/
/* 03/16/06  JRB    08	   Add SCL_SVCB struct & scl_svcb_add proto.	*/
/* 03/15/06  JRB    07     Chg almost all function prototypes.		*/
/*			   Del scl_dotype_add_da_val,			*/
/*			    scl_datype_add_bda_val, scl_header_save.	*/
/*			   Add sGroup to SCL_DAI.			*/
/*			   Chg desc to ptr (allocated during parse).	*/
/*			   Increase MAX_CDC_LEN for user-defined CDCs.	*/
/* 07/25/05  JRB    12     scl2_ld_create_all: Add brcb_bufsize arg.	*/
/*			   SCL_INFO: add brcb_bufsize element.		*/
/* 06/28/05  JRB    11     Del scl2_ld_destroy_all. Use mvl_vmd_destroy.*/
/* 06/24/05  JRB    10     Chg "ord" from unsigned to signed value.	*/
/* 05/27/05  CRM    09	   Add scl_info_destroy & scl2_ld_destroy_all.	*/
/* 03/22/05  JRB    08     Add ifdef __cplusplus to work with C++ code.	*/
/* 02/15/05  JRB    07     Add iedName to SCL_INFO.			*/
/*			   Add domName to SCL_LD & SCL_FCDA.		*/
/*			   Add varName to SCL_LN.			*/
/*			   Define SCL_HEADER struct & add it to SCL_INFO.*/
/*			   Add scl_header_save.				*/
/* 08/06/04  JRB    06     Add scl_parse.				*/
/*			   Move mapping functions to user header.	*/
/* 07/19/04  JRB    05     Add out_filename arg to datamap_cfg_read.	*/
/*			   Add any_cfg_count proto.			*/
/* 07/15/04  JRB    04     Clean up SCL_GCB, scl_gcb_add.		*/
/* 07/09/04  JRB    03     scl2_ld_create_all: add reportScanRate arg.	*/
/* 07/02/04  JRB    02     Add SCL_LCB, SCL_GCB, scl_lcb_add, scl_gcb_add.*/
/* 06/08/04  JRB    01     Initial Revision.				*/
/************************************************************************/
#include "gen_list.h"
#include "mms_def2.h"		/* need MAX_IDENT_LEN	*/
#include "mvl_defs.h"		/* need MVL_VAR_ASSOC, etc.	*/

#define SCL_USE_MMS_STRING_

#ifdef SCL_USE_MMS_STRING_
#include "mms_string.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_VALKIND_LEN	4	/* Spec, Conf, RO, or Set		*/
#define MAX_CDC_LEN	50	/* SPS, DPS, etc. (CURVE is longest	*/
				/* predefined CDC but user may define others)*/
#define MAX_FC_LEN	2	/* ST, MX, etc.				*/

/* These defines used in SCL_DA struct to differentiate between structs	*/
/* containing DA info and structs containing SDO info.			*/
#define SCL_OBJTYPE_DA	0
#define SCL_OBJTYPE_SDO	1


/* This def used for flattened leaf names (longer to allow array indices)*/
#define MAX_FLAT_LEN	(MAX_IDENT_LEN*2)

/************************************************************************/
/* Structures to contain information from "Header" section of SCL.	*/
/************************************************************************/
typedef struct
  {
  /* NOTE: only required elements included here. Add optional elements as needed.*/
#ifdef SCL_USE_MMS_STRING_
	  MMS_MEM_STRING id;
#else
  ST_CHAR id        [MAX_IDENT_LEN+1];
#endif

  /* Defined values for "nameStructure" attribute	*/
  #define SCL_NAMESTRUCTURE_IEDNAME	0	/* value="IEDName"	*/
  #define SCL_NAMESTRUCTURE_FUNCNAME	1	/* value="FuncName"	*/
  ST_INT nameStructure;
  } SCL_HEADER;

/************************************************************************/
/* Structures to contain information from "Communications" section of SCL.*/
/************************************************************************/
/* Data from "GSE" element (inside "ConnectedAP" element)	*/
typedef struct scl_gse
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_gse *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_gse *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING ldInst;
  MMS_MEM_STRING cbName;
#else
  ST_CHAR ldInst[MAX_IDENT_LEN+1];
  ST_CHAR cbName[MAX_IDENT_LEN+1];
#endif  
  ST_CHAR MAC[CLNP_MAX_LEN_MAC];	/* Multicast MAC address	*/
		ST_UINT VLANID;				//hejian add on 2010-7-28
		ST_UINT APPID;
  ST_UINT VLANPRI;
		ST_UINT MinTime;					//hejian add on 2010-7-28
		ST_UINT MaxTime;					//hejian add on 2010-7-28
  } SCL_GSE;

/* Data from "SMV" element (inside "ConnectedAP" element)	*/
typedef struct scl_smv
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_smv *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_smv *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING ldInst;
  MMS_MEM_STRING cbName;
#else
  ST_CHAR ldInst[MAX_IDENT_LEN+1];
  ST_CHAR cbName[MAX_IDENT_LEN+1];
#endif

  ST_CHAR MAC[CLNP_MAX_LEN_MAC];	/* Multicast MAC address	*/
		ST_UINT VLANID;
		ST_UINT APPID;
  ST_UINT VLANPRI;
  } SCL_SMV;


typedef struct scl_address
{
	/* CRITICAL: First 2 parameters used to add this struct to linked	*/
	/* lists using list_add_last, etc.					*/
	struct scl_address *next;		/* CRITICAL: DON'T MOVE.	*/
	struct scl_address *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
	MMS_MEM_STRING address_ip;
	MMS_MEM_STRING address_ip_subnet;
	MMS_MEM_STRING address_ip_gateway;
#else
	ST_CHAR address_ip[MAX_IDENT_LEN+1];
	ST_CHAR address_ip_subnet[MAX_IDENT_LEN+1];
	ST_CHAR address_ip_gateway[MAX_IDENT_LEN+1];
#endif

} SCL_ADDRESS;


/* Data from "ConnectedAP" element	*/
typedef struct scl_cap
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_cap *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_cap *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING iedName;
#else
  ST_CHAR iedName[MAX_IDENT_LEN+1];
#endif

  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING apName;
#else
  ST_CHAR apName[MAX_IDENT_LEN+1];
#endif

  SCL_ADDRESS *addressHead;
  SCL_GSE *gseHead;      /* head of list of GSE defs	*/
  SCL_SMV *smvHead;      /* head of list of SMV defs	*/
  } SCL_CAP;

typedef struct scl_bay
{

	struct scl_bay *next;	
	struct scl_bay *prev;	
	ST_CHAR *name;
	ST_CHAR *desc;		
	//SCL_BAY  *bayHead; 		
	//SCL_IED *iedHead;

} SCL_BAY;




typedef struct scl_vollevel
{

	struct scl_vollevel *next;	
	struct scl_vollevel *prev;	
	ST_CHAR *name;
	ST_CHAR *desc;		
	SCL_BAY  *bayHead; 		
	//SCL_IED *iedHead;


} SCL_VOLLEVEL;

typedef struct scl_substation
{
	/* CRITICAL: First 2 parameters used to add this struct to linked	*/
	/* lists using list_add_last, etc.					*/
	struct scl_substation *next;		/* CRITICAL: DON'T MOVE.	*/
	struct scl_substation *prev;		/* CRITICAL: DON'T MOVE.	*/
	ST_CHAR *name;
	ST_CHAR *desc;		/* description (optional)*/
	/* may be long so allocate if present*/
	SCL_VOLLEVEL *vollevelHead;		/* head of list of ConnectedAP defs	*/
} SCL_SUBSTATION;



/* Data from "Subnetwork" element	*/
typedef struct scl_subnet
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_subnet *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_subnet *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;
#else
  ST_CHAR name[MAX_IDENT_LEN+1];
#endif

  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/
  ST_CHAR type[MAX_IDENT_LEN+1];
  SCL_CAP *capHead;		/* head of list of ConnectedAP defs	*/
  } SCL_SUBNET;

/************************************************************************/
/* Structures to contain information from "AccessPoint" section of SCL.*/
/************************************************************************/

/* "scl_fcda_add" allocates this struct, fills it in,		*/
/* and adds it to the linked list "fcdaHead" in SCL_DATASET.		*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING domName;	/* domain name (constructed)	*/
  MMS_MEM_STRING ldInst;
  MMS_MEM_STRING prefix;
  MMS_MEM_STRING lnInst;
  MMS_MEM_STRING lnClass;
  MMS_MEM_STRING doName;
  MMS_MEM_STRING daName;
  MMS_MEM_STRING fc;	/* ST, MX, etc.			*/

		//hejian add on 2011-3-29
		MMS_MEM_STRING lndesc;
		MMS_MEM_STRING dodesc;
		//hejian add on 2010-11-11
		MMS_MEM_STRING desc;
		MMS_MEM_STRING type;

 		MMS_MEM_STRING DOType;//zhow:2017.08.01 增加SMV中对DOType和对应cdc的记录
 		MMS_MEM_STRING cdc;//zhow:2017.08.01 增加SMV中对DOType和对应cdc的记录

		//ST_CHAR value	[MAX_IDENT_LEN+1];
		MMS_MEM_STRING map;
#else
  ST_CHAR domName[MAX_IDENT_LEN+1];	/* domain name (constructed)	*/
  ST_CHAR ldInst  [MAX_IDENT_LEN+1];
  ST_CHAR prefix  [MAX_IDENT_LEN+1];
  ST_CHAR lnInst  [MAX_IDENT_LEN+1];
  ST_CHAR lnClass [MAX_IDENT_LEN+1];
  ST_CHAR doName  [MAX_IDENT_LEN+1];
  ST_CHAR daName  [MAX_IDENT_LEN+1];
  ST_CHAR fc      [MAX_FC_LEN+1];	/* ST, MX, etc.			*/

		//hejian add on 2011-3-29
		ST_CHAR lndesc	[MAX_IDENT_LEN+1];
		ST_CHAR dodesc	[MAX_IDENT_LEN+1];
		//hejian add on 2010-11-11
		ST_CHAR desc	[MAX_IDENT_LEN+1];
		ST_CHAR type	[MAX_TYPE_LEN+1];

 		ST_CHAR DOType	[MAX_IDENT_LEN+1];//zhow:2017.08.01 增加SMV中对DOType和对应cdc的记录
 		ST_CHAR cdc	[MAX_CDC_LEN+1];//zhow:2017.08.01 增加SMV中对DOType和对应cdc的记录

		//ST_CHAR value	[MAX_IDENT_LEN+1];
		ST_CHAR map		[MAX_IDENT_LEN+1];
#endif

  } SCL_FCDA;

/* "scl_dai_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "daiHead" in SCL_LN.			*/
/* The "flattened" name must be constructed from the "name" & "ix"	*/
/* attribute of the DOI and DAI and possibly the intervening SDI,	*/
/* where "ix" is an array index (we'll need some new flattened name	*/
/* syntax to handle the array index).					*/
/* The "accessControl" attr of DOI is ignored (don't know what it means).*/
/* The "desc" attr of DOI, SDI, & DAI are ignored (not useful).		*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING flattened;	/* flattened attribute name	*/
#else
  ST_CHAR flattened[MAX_FLAT_LEN+1];	/* flattened attribute name	*/
#endif
					/* constructed from "name" & "ix"*/
					/* from DOI, SDI, & DAI		*/
  ST_CHAR *Val;				/* attribute value text		*/
					/* allocate appropriate size buffer*/
  ST_UINT sGroup;			/* optional Setting Group Number*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING sAddr;	/* from DAI			*/
#else
  ST_CHAR sAddr[MAX_IDENT_LEN+1];	/* from DAI			*/
#endif

  ST_CHAR valKind[MAX_VALKIND_LEN+1];	/* from DAI			*/
  } SCL_DAI;

/* "scl_dataset_add" allocates this struct,			*/
/* and adds it to the linked list "datasetHead" in SCL_LN.	*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;	/* dataset name		*/
#else
  ST_CHAR name[MAX_IDENT_LEN+1];	/* dataset name		*/
#endif

  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/
  SCL_FCDA *fcdaHead;			/* head of list of FCDA	*/
  } SCL_DATASET;

/* "scl_rcb_add" allocates this struct, fills it in,		*/
/* and adds it to the linked list "rcbHead" in SCL_LN.		*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;
#else
  ST_CHAR name[MAX_IDENT_LEN+1];
#endif

  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING datSet;
#else
  ST_CHAR datSet[MAX_IDENT_LEN+1];
#endif

  ST_UINT intgPd;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING rptID;
#else
  ST_CHAR rptID[MAX_IDENT_LEN+1];
#endif

  ST_UINT confRev;
  ST_BOOLEAN buffered;		/* TRUE if this is buffered RCB	*/
  ST_UINT bufTime;
  ST_UINT8 TrgOps [1];		/* 8-bit bitstring			*/
				/* Boolean vals from SCL file		*/
				/* (dchg, qchg, dupd, & period)		*/
				/* used to set bits in TrgOps bitstring	*/
  ST_UINT8 OptFlds [2];		/* 9-bit bitstring			*/
				/* Boolean vals from SCL file		*/
				/* (seqNum, timeStamp, dataSet,		*/
				/* reasonCode, dataRef, bufOvfl,	*/
				/* entryID, configRef)			*/
				/* segmentation boolean is ignored	*/
				/* used to set bits in OptFlds bitstring*/
  ST_UINT maxClient;		/* value of "RptEnabled max" attr.	*/
  } SCL_RCB;			/* Report Control Block	*/

typedef struct
  {
  /* Counters of different types of BRCB.	*/
  ST_UINT brcb_count_complex;
  ST_UINT brcb_count_ST;
  ST_UINT brcb_count_MX;
  ST_UINT brcb_count_CO;
  ST_UINT brcb_count_SP;
  ST_UINT brcb_count_SG;
  ST_UINT brcb_count_SE;
  ST_UINT brcb_count_SV;
  ST_UINT brcb_count_CF;
  ST_UINT brcb_count_DC;
  ST_UINT brcb_count_EX;

  /* Counters of different types of URCB.	*/
  ST_UINT urcb_count_complex;
  ST_UINT urcb_count_ST;
  ST_UINT urcb_count_MX;
  ST_UINT urcb_count_CO;
  ST_UINT urcb_count_SP;
  ST_UINT urcb_count_SG;
  ST_UINT urcb_count_SE;
  ST_UINT urcb_count_SV;
  ST_UINT urcb_count_CF;
  ST_UINT urcb_count_DC;
  ST_UINT urcb_count_EX;
  } SCL_RCB_COUNTERS;

/************************************************************************/
/*			LOG Control Block				*/
/* "scl_lcb_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "lcbHead" in SCL_LN.			*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;
#else
  ST_CHAR name[MAX_IDENT_LEN+1];
#endif

  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING datSet;
#else
  ST_CHAR datSet[MAX_IDENT_LEN+1];
#endif

  ST_UINT intgPd;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING logName;
#else
  ST_CHAR logName[MAX_IDENT_LEN+1];
#endif

  ST_BOOLEAN logEna;
  ST_BOOLEAN reasonCode;
  ST_UINT8 TrgOps [1];		/* 8-bit bitstring			*/
				/* Boolean vals from SCL file		*/
				/* (dchg, qchg, dupd, & period)		*/
				/* used to set bits in TrgOps bitstring	*/
  } SCL_LCB;


/************************************************************************/
/*			Setting Control Block				*/
/* "scl_sgcb_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "lcbHead" in SCL_LN.			*/
//zhouhj 20181206
typedef struct
{
	DBL_LNK l;
	ST_UINT numOfSGs;
	ST_UINT actSG;
} SCL_SGCB;

/************************************************************************/
	/*			GOOSE/Sampled ExtRef	hejian add on 2010-11-2			*/
	/* "scl_extref_add" allocates this struct, fills it in,			*/
	/* and adds it to the linked list "inputsHead" in SCL_LN.			*/
	typedef struct
	{
		DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
		MMS_MEM_STRING inAddr;
		MMS_MEM_STRING domName;	/* domain name (constructed)	*/
		MMS_MEM_STRING ldInst ;
		MMS_MEM_STRING prefix ;
		MMS_MEM_STRING lnInst;
		MMS_MEM_STRING lnClass;
		MMS_MEM_STRING doName;
		MMS_MEM_STRING daName;

		//hejian add on 2011-3-29
		MMS_MEM_STRING lndesc;
		MMS_MEM_STRING dodesc;
		//hejian add on 2010-11-11
		MMS_MEM_STRING desc;

		MMS_MEM_STRING type;//zhow:2017.08.02
		MMS_MEM_STRING cdc;//zhow:2017.08.02
#else
		ST_CHAR inAddr  [MAX_IDENT_LEN+1];
		ST_CHAR domName [MAX_IDENT_LEN+1];	/* domain name (constructed)	*/
		ST_CHAR ldInst  [MAX_IDENT_LEN+1];
		ST_CHAR prefix  [MAX_IDENT_LEN+1];
		ST_CHAR lnInst  [MAX_IDENT_LEN+1];
		ST_CHAR lnClass [MAX_IDENT_LEN+1];
		ST_CHAR doName  [MAX_IDENT_LEN+1];
		ST_CHAR daName  [MAX_IDENT_LEN+1];

		//hejian add on 2011-3-29
		ST_CHAR lndesc	[MAX_IDENT_LEN+1];
		ST_CHAR dodesc	[MAX_IDENT_LEN+1];
		//hejian add on 2010-11-11
		ST_CHAR desc	[MAX_IDENT_LEN+1];

		ST_CHAR type	[MAX_IDENT_LEN+1];//zhow:2017.08.02
		ST_CHAR cdc  	[MAX_IDENT_LEN+1];//zhow:2017.08.02
#endif


		ST_INT  index;
	} SCL_EXTREF;

	/************************************************************************/
	/*			GOOSE/Sampled Value Inputs	hejian add on 2010-11-2			*/
	/* "scl_inputs_add" allocates this struct, fills it in,			*/
	/* and adds it to the linked list "inputsHead" in SCL_LN.			*/
	typedef struct
	{
		DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
		MMS_MEM_STRING name;
#else
		ST_CHAR name[MAX_IDENT_LEN+1];
#endif

		ST_CHAR *desc;			/* description (optional)*/
		SCL_EXTREF *extrefHead;
	} SCL_INPUTS;

	/************************************************************************/
/*			GOOSE Control Block				*/
/* "scl_gcb_add" allocates this struct, fills it in,			*/
/* and adds it to the linked list "gcbHead" in SCL_LN.			*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;
#else
  ST_CHAR name[MAX_IDENT_LEN+1];
#endif

  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING datSet;	/* for GOOSE only	*/
#else
  ST_CHAR datSet[MAX_IDENT_LEN+1];	/* for GOOSE only	*/
#endif

  ST_UINT confRev;			/* for GOOSE only	*/
  ST_BOOLEAN isGoose;	/* SD_TRUE if "GOOSE", SD_FALSE if "GSSE"*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING appID;	/* for GOOSE only	*/
#else
  ST_CHAR appID[MAX_IDENT_LEN+1];	/* for GOOSE only	*/
#endif

  /* The SCL file may also contain one or more "IEDName" elements to	*/
  /* indicate IEDs that should subscribe for GOOSE data. We have no	*/
  /* way to use this information, so it is ignored.			*/
  } SCL_GCB;

/************************************************************************/
/*			Sampled Value Control Block			*/
/* "scl_parse" allocates this struct and fills it in.			*/
/* "scl_svcb_add" adds it to the linked list "svcbHead" in SCL_LN.	*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;
#else
  ST_CHAR name[MAX_IDENT_LEN+1];
#endif

  ST_CHAR *desc;		/* description (optional)*/
				/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING datSet;
  MMS_MEM_STRING smvID;
#else
  ST_CHAR datSet[MAX_IDENT_LEN+1];
  ST_CHAR smvID[MAX_IDENT_LEN+1];
#endif

  ST_UINT smpRate;
  ST_UINT nofASDU;
  ST_UINT confRev;
  ST_BOOLEAN multicast;		/* TRUE if this is MsvCB		*/
  ST_UINT8 OptFlds [1];		/* 8-bit bitstring			*/
				/* Boolean vals from "SmvOpts" in SCL	*/
				/* (sampleRate, etc.)			*/
				/* used to set bits in this bitstring	*/
  ST_BOOLEAN securityPres;	/* SmvOpts security flag	*/
  ST_BOOLEAN dataRefPres;	/* SmvOpts dataRef flag		*/
  } SCL_SVCB;			/* Sampled Value Control Block	*/

/* "scl_ln_add" allocates this struct, fills it in,		*/
/* and adds it to the linked list "lnHead" in SCL_LD.		*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING varName;	/* variable name (constructed)	*/
#else
  ST_CHAR varName[MAX_IDENT_LEN+1];	/* variable name (constructed)	*/
#endif

  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING lnType;	/* LN Type name		*/
  MMS_MEM_STRING lnClass;	/* LN Class name	*/
					/* for LN0, must be "LLN0"	*/
  MMS_MEM_STRING inst;	/* LN inst name			*/
					/* for LN0, must be "" (empty string)*/
  MMS_MEM_STRING prefix;	/* LN prefix name	*/
					/* for LNO, ignored	*/
#else
  ST_CHAR lnType[MAX_IDENT_LEN+1];	/* LN Type name		*/
  ST_CHAR lnClass[MAX_IDENT_LEN+1];	/* LN Class name	*/
					/* for LN0, must be "LLN0"	*/
  ST_CHAR inst[MAX_IDENT_LEN+1];	/* LN inst name			*/
					/* for LN0, must be "" (empty string)*/
  ST_CHAR prefix[MAX_IDENT_LEN+1];	/* LN prefix name	*/
#endif

  SCL_DAI     *daiHead;		/* head of list of DAI	*/
  SCL_DATASET *datasetHead;	/* head of list of DataSet	*/
  SCL_RCB     *rcbHead;		/* head of list of RCB (Report Control)	*/
  SCL_LCB     *lcbHead;		/* head of list of LCB (Log Control)	*/
  SCL_GCB     *gcbHead;		/* head of list of GCB (GOOSE Control)	*/
  SCL_SVCB    *svcbHead;	/* head of list of SVCB (Sampled Value Control)*/
		SCL_INPUTS  *inputsHead;  /* head of list of inputs*/ //hejian add on 2010-11-2
		SCL_SGCB    *sgcbHead;   //zhouhj 20181206

  /* NOTE: In LN or LN0: Inputs ignored		*/
  /* NOTE: In LN0: SampledValueControl, SettingControl, SCLControl ignored*/

  ST_INT type_id;		/* Initialized by "scl2_datatype_create_all"*/
  MVL_VAR_ASSOC *mvl_var_assoc;	/* MVL Variable Association created from LN info*/
  } SCL_LN;			/* Logical Node (LN or LN0 in SCL)	*/

/* "scl_ld_create" allocates this struct			*/
/* and adds it to the linked list "ldHead" in SCL_INFO.		*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING domName;	/* domain name (constructed)	*/
#else
  ST_CHAR domName[MAX_IDENT_LEN+1];	/* domain name (constructed)	*/
#endif

  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING inst;	/* LD inst name		*/
  MMS_MEM_STRING ldName;	/* LD inst name		*/
#else
  ST_CHAR inst[MAX_IDENT_LEN+1];	/* LD inst name		*/
  ST_CHAR ldName[MAX_IDENT_LEN+1];	/* LD inst name		*/
#endif

  SCL_LN *lnHead;			/* head of list of LN	*/
  /* NOTE: AccessControl in LDevice is ignored	*/
  } SCL_LD;			/* Logical Device (LDevice in SCL)*/

	typedef struct //hejian add on 2010-11-5
	{
		DBL_LNK l;
		ST_CHAR *desc;			/* description (optional)*/

#ifdef SCL_USE_MMS_STRING_
		MMS_MEM_STRING name;
#else
		ST_CHAR name[MAX_IDENT_LEN+1];
#endif

		SCL_LD *ldHead;			/* head of list of LD	*/
		/* NOTE: AccessControl in LDevice is ignored	*/
	} SCL_AP;			/* Access Point (AccessPoint in SCL)*/

	typedef struct //hejian add on 2010-11-5
	{
		DBL_LNK l;
		ST_CHAR *desc;			/* description (optional)*/

#ifdef SCL_USE_MMS_STRING_
		MMS_MEM_STRING name;
		MMS_MEM_STRING type;
		MMS_MEM_STRING configVersion;
		MMS_MEM_STRING manufacturer;
#else
		ST_CHAR name[MAX_IDENT_LEN+1];
		ST_CHAR type[MAX_IDENT_LEN+1];
		ST_CHAR configVersion[MAX_IDENT_LEN+1];
		ST_CHAR manufacturer[MAX_IDENT_LEN+1];
#endif

		SCL_AP *apHead;			/* head of list of LD	*/
		/* NOTE: AccessControl in LDevice is ignored	*/
	} SCL_IED;			/* Access Point (AccessPoint in SCL)*/

/************************************************************************/
/* Structures to contain information from "DataTypeTemplates" section of SCL.*/
/************************************************************************/
/* This structure should be allocated and filled in by the function	*/
/* "scl_lntype_add_do".							*/
typedef struct scl_do
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_do *next;			/* CRITICAL: DON'T MOVE.	*/
  struct scl_do *prev;			/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;	/* data object name		*/
  MMS_MEM_STRING type;	/* data object type		*/
#else
  ST_CHAR name[MAX_IDENT_LEN+1];	/* data object name		*/
  ST_CHAR type[MAX_IDENT_LEN+1];	/* data object type		*/
#endif

  } SCL_DO;

typedef struct scl_lntype
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_lntype *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_lntype *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING id;			/* name used to reference this LN Type*/
  MMS_MEM_STRING lnClass;		/* logical node class		*/
#else
  ST_CHAR id[MAX_IDENT_LEN+1];			/* name used to reference this LN Type*/
  ST_CHAR lnClass[MAX_IDENT_LEN+1];		/* logical node class		*/
#endif

  SCL_DO *doHead;		/* head of list of DO	*/
				/* scl_lntype_add_do adds to list	*/
  ST_INT type_id;		/* Initialized by "scl2_datatype_create_all"*/
  } SCL_LNTYPE;


/* This structure should be allocated and filled in by the function	*/
/* "scl_dotype_add_da" OR "scl_dotype_add_sdo", and possibly modified by the optional	*/
/* function "scl_dotype_add_da_val".					*/
/* NOTE: the same structure must be used for DA or SDO because each must	*/
/* be put on the same linked list in the order they are read from the SCL file.*/
/* Most of the parameters are relevant only for DA elements. They are	*/
/* ignored if this is an SDO (i.e. objtype=SCL_OBJTYPE_SDO).		*/
typedef struct
  {
  DBL_LNK l;
  ST_INT objtype;			/* SCL_OBJTYPE_DA or SCL_OBJTYPE_SDO	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;	/* DA or SDO name		*/
#else
  ST_CHAR name[MAX_IDENT_LEN+1];	/* DA or SDO name		*/
#endif

  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING sAddr;	/* for DA only: DA sAddr	*/
  MMS_MEM_STRING bType;	/* for DA only: DA bType	*/
#else
  ST_CHAR sAddr[MAX_IDENT_LEN+1];	/* for DA only: DA sAddr	*/
  ST_CHAR bType[MAX_IDENT_LEN+1];	/* for DA only: DA bType	*/
#endif

  ST_CHAR valKind[MAX_VALKIND_LEN+1];	/* for DA only: Spec, Conf, RO, or Set	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING type;	/* for DA: needed if bType="Struct" or "Enum"*/
#else
  ST_CHAR type[MAX_IDENT_LEN+1];	/* for DA: needed if bType="Struct" or "Enum"*/
#endif
					/* for SDO: required		*/
  ST_UINT count;			/* for DA only: num array entries*/
  ST_CHAR fc[MAX_FC_LEN+1];		/* for DA only: functional constraint	*/
  ST_BOOLEAN dchg;			/* for DA only: TrgOp (data change)	*/
  ST_BOOLEAN qchg;			/* for DA only: TrgOp (quality change)	*/
  ST_BOOLEAN dupd;			/* for DA only: TrgOp (data update)	*/

  /* The "Val" and "sGroup" parameters are only set if the SCL file contains the
   * optional "Val" element, in which case "scl_dotype_add_da_val" is called.
   */
  ST_CHAR *Val;				/* for DA only: attribute value text	*/
					/* allocate appropriate size buffer*/
  ST_UINT sGroup;			/* for DA only: optional Setting Group Number*/
  } SCL_DA;

typedef struct scl_dotype
  {
  /* CRITICAL: First 2 parameters used to add this struct to linked	*/
  /* lists using list_add_last, etc.					*/
  struct scl_dotype *next;		/* CRITICAL: DON'T MOVE.	*/
  struct scl_dotype *prev;		/* CRITICAL: DON'T MOVE.	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING id;	/* name used to reference this DO Type	*/
  MMS_MEM_STRING cdc;	/* CDC name				*/
#else
  ST_CHAR id[MAX_IDENT_LEN+1];	/* name used to reference this DO Type	*/
  ST_CHAR cdc[MAX_CDC_LEN+1];	/* CDC name				*/
#endif

  SCL_DA *daHead;		/* head of list of DA or SDO		*/
				/* scl_dotype_add_da OR			*/
				/* scl_dotype_add_sdo adds to list	*/
  } SCL_DOTYPE;

/* This structure should be allocated and filled in by the function	*/
/* "scl_datype_add_bda".						*/
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING name;		/* data attribute name		*/
#else
  ST_CHAR name[MAX_IDENT_LEN+1];		/* data attribute name		*/
#endif

  ST_CHAR *desc;			/* description (optional)*/
					/* may be long so allocate if present*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING sAddr;		/* for DA only: DA sAddr	*/
  MMS_MEM_STRING bType;		/* data attribute type		*/
#else
  ST_CHAR sAddr[MAX_IDENT_LEN+1];		/* for DA only: DA sAddr	*/
  ST_CHAR bType[MAX_IDENT_LEN+1];		/* data attribute type		*/
#endif

  ST_CHAR valKind[MAX_VALKIND_LEN+1];		/* Spec, Conf, RO, or Set	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING type;		/* only used if btype="Struct" or "Enum"*/
#else
  ST_CHAR type[MAX_IDENT_LEN+1];		/* only used if btype="Struct" or "Enum"*/
#endif

  ST_UINT count;	/* for DA only: num array entries*/

  /* The "Val" and "sGroup" parameters are only set if the SCL file contains the
   * optional "Val" element, in which case "scl_datype_add_bda_val" is called.
   */
  ST_CHAR *Val;				/* attribute value text		*/
					/* allocate appropriate size buffer*/
  ST_UINT sGroup;			/* optional Setting Group Number*/
  } SCL_BDA;			/* Basic Data Attribute		*/


typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING id;			/* name used to reference this DA Type*/
#else
  ST_CHAR id[MAX_IDENT_LEN+1];			/* name used to reference this DA Type*/
#endif

  SCL_BDA *bdaHead;		/* head of list of BDA	*/
				/* scl_datype_add_bda adds to list	*/
  } SCL_DATYPE;


/* This structure should be allocated and filled in by the function	*/
/* "scl_enumtype_add_enumval".						*/
typedef struct
  {
  DBL_LNK l;
  ST_INT ord;				/* ord attribute	*/

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING EnumVal;	/* EnumVal element		*/
#else
  ST_CHAR EnumVal[MAX_IDENT_LEN+1];	/* EnumVal element		*/
#endif

					/* TRUNCATED if longer than buffer	*/
  } SCL_ENUMVAL;
typedef struct
  {
  DBL_LNK l;

#ifdef SCL_USE_MMS_STRING_
  MMS_MEM_STRING id;			/* name used to reference this DA Type*/
#else
  ST_CHAR id[MAX_IDENT_LEN+1];			/* name used to reference this DA Type*/
#endif

  SCL_ENUMVAL *enumvalHead;	/* head of list of EnumVal	*/
				/* scl_enumtype_add_enumval adds to list*/
  } SCL_ENUMTYPE;

/************************************************************************/
/*			SCL_INFO					*/
/* This structure contains all information extracted from the SCL file	*/
/* to be used for MMS-EASE Lite initialization.				*/
/************************************************************************/
typedef struct
  {
		//hejian del on 2010-11-5
		//ST_CHAR iedName [MAX_IDENT_LEN+1];	/* passed to scl_parse		*/

  SCL_HEADER Header;		/* Info from "Header" section of SCL file*/

    SCL_SUBSTATION *substationHead;//cgl Bay Infomation

  /* SubNetwork definitions from (from Communication section)		*/
  SCL_SUBNET *subnetHead;	/* head of list of SubNetwork defs	*/

  /* Logical Node Type definitions (from DataTypeTemplates section)	*/
  SCL_LNTYPE *lnTypeHead;	/* head of list	of LNodeType defs	*/
  SCL_DOTYPE *doTypeHead;	/* head of list of DOType defs		*/
  SCL_DATYPE *daTypeHead;	/* head of list of DAType defs		*/
  SCL_ENUMTYPE *enumTypeHead;	/* head of list of EnumType defs	*/

  /* Logical Device (MMS Domain) definitions (from AccessPoint section)	*/
		//hejian del on 2010-11-5
		//SCL_LD *ldHead;		/* head of list of LDevice defs		*/
		SCL_IED	*iedHead;

  ST_INT brcb_bufsize;		/* BRCB buffer size			*/
				/* scl2_ld_create_all uses arg to set it*/
  ST_BOOLEAN datatype_create_done;	/* flag set by scl2_datatype_create_all*/
  ST_BOOLEAN ld_create_done;	/* flag set by scl2_ld_create_all*/
  } SCL_INFO;


/************************************************************************/
/************************************************************************/
/* FUNCTIONS to store SCL info in "SCL_INFO" structure.			*/
/************************************************************************/
/************************************************************************/

SCL_LNTYPE *scl_lntype_create (
	SCL_INFO *scl_info);

SCL_DO *scl_lntype_add_do (
	SCL_INFO *scl_info);

SCL_DOTYPE *scl_dotype_create (
	SCL_INFO *scl_info);

SCL_DA *scl_dotype_add_da (
	SCL_INFO *scl_info);

SCL_DA *scl_dotype_add_sdo (
	SCL_INFO *scl_info);

SCL_DATYPE *scl_datype_create (
	SCL_INFO *scl_info);

SCL_BDA *scl_datype_add_bda (
	SCL_INFO *scl_info);

SCL_ENUMTYPE *scl_enumtype_create (
	SCL_INFO *scl_info);

SCL_ENUMVAL *scl_enumtype_add_enumval (
	SCL_INFO *scl_info);

SCL_FCDA *scl_fcda_add (
	SCL_INFO *scl_info);

SCL_DAI *scl_dai_add (
	SCL_INFO *scl_info);

SCL_DATASET *scl_dataset_add (
	SCL_INFO *scl_info);

SCL_RCB *scl_rcb_add (
	SCL_INFO *scl_info);

SCL_LCB *scl_lcb_add (
	SCL_INFO *scl_info);

SCL_SGCB *scl_sgcb_add (//zhouhj 20181206
	SCL_INFO *scl_info);

SCL_GCB *scl_gcb_add (
	SCL_INFO *scl_info);

	SCL_INPUTS *scl_inputs_add (
		SCL_INFO *scl_info);//hejian add on 2010-11-2

	SCL_EXTREF *scl_extref_add (
		SCL_INFO *scl_info);//hejian add on 2010-11-2

SCL_SVCB *scl_svcb_add (
	SCL_INFO *scl_info);

SCL_LN *scl_ln_add (
	SCL_INFO *scl_info);

SCL_LD *scl_ld_create (
	SCL_INFO *scl_info);

	SCL_AP *scl_ap_create (
		SCL_INFO *scl_info);

	SCL_IED *scl_ied_create (
		SCL_INFO *scl_info);

SCL_SUBNET *scl_subnet_add (
	SCL_INFO *scl_info);

SCL_CAP *scl_cap_add (
	SCL_INFO *scl_info);

SCL_GSE *scl_gse_add (
	SCL_INFO *scl_info);

SCL_SMV *scl_smv_add (
	SCL_INFO *scl_info);

SCL_ADDRESS *scl_address_add (
					  SCL_INFO *scl_info);


SCL_SUBSTATION *scl_substation_create (
									SCL_INFO *scl_info);

SCL_VOLLEVEL *scl_vollevel_add (
								SCL_INFO *scl_info);

SCL_BAY *scl_bay_add (
					  SCL_INFO *scl_info);

/************************************************************************/
/*			scl_parse					*/
/* Parses SCL file and stores extracted info in SCL_INFO structure.	*/
/************************************************************************/
	ST_RET scl_parse (ST_CHAR *xmlFileName, SCL_INFO *sclInfo);
ST_VOID scl_log_all (SCL_INFO *scl_info);

/************************************************************************/
/*			scl_info_destroy				*/
/* Destroy all info stored in the SCL_INFO structure by "scl_parse".	*/
/************************************************************************/
ST_VOID scl_info_destroy (SCL_INFO *scl_info);

/************************************************************************/
/*			scl2_datatype_create_all			*/
/* Create MMS Data types for all Logical Node Types (LNodeType)		*/
/* defined in SCL.							*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET scl2_datatype_create_all (
	MVL_VMD_CTRL *vmd_ctrl,	/* VMD in which to add types.		*/
	SCL_INFO *sclInfo,	/* main struct where all SCL info stored*/
	ST_INT max_rt_num,	/* max num of RUNTIME_TYPE for each LNodeType*/
	ST_BOOLEAN use_names,	/* if SD_TRUE, generate a name for each type*/
	ST_CHAR *name_prefix);	/* unique prefix to add to each type name*/
				/* only used if "use_names==SD_TRUE".	*/

/************************************************************************/
/*			scl2_ld_create_all			*/
/* Create all Logical Devices from SCL info saved in "sclInfo".		*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET scl2_ld_create_all (
	MVL_VMD_CTRL *vmd_ctrl,	/* VMD in which to add Logical Devices.	*/
	SCL_INFO *sclInfo,	/* main struct where all SCL info stored*/
	ST_UINT reportScanRate,	/* report scan rate (millisec)	*/
	ST_INT brcb_bufsize,	/* BRCB buffer size			*/
	ST_BOOLEAN is_client);	/* If this flag is set, Client model is	*/
				/* created (i.e. Control Blocks NOT created).*/

/************************************************************************/
/*			u_set_all_leaf_functions			*/
/* User customizable function to set all leaf functions for a data type.*/
/************************************************************************/
ST_RET u_set_all_leaf_functions (RUNTIME_CTRL *rt_ctrl);


/************************************************************************/
/************************************************************************/

extern ST_BOOLEAN scl_debug_mode;
extern ST_INT scl_debug_mode_error_count;

typedef struct
  {
  DBL_LNK l;
  ST_CHAR *btype;
  RUNTIME_CTRL *rt_ctrl;
  } SCL2_BTYPE;
extern SCL2_BTYPE *scl2_btype_list;
SCL2_BTYPE *scl2_add_btype (ST_CHAR *btype, ST_CHAR *tdl);



typedef struct
  {
  SCL_INFO *scl_info;
  SCL_LD *scl_ld;
  SCL_LN *scl_ln;
  ST_CHAR *valText;
  ST_CHAR *attrib;
  ST_VOID *dest;
  ST_INT numRt;
  SD_CONST RUNTIME_TYPE *rtHead;
  } SCL2_IV_TRANSLATE_CTRL;

ST_RET u_mvl_scl_set_initial_value (SCL2_IV_TRANSLATE_CTRL *sclXlateIv);

#ifdef __cplusplus
}
#endif

#endif	/* !SCL_INCLUDED	*/
