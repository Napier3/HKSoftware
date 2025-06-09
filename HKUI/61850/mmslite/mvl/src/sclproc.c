/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2004-2006 All Rights Reserved					*/
/*									*/
/* MODULE NAME : sclproc.c						*/
/* PRODUCT(S)  : MMS-EASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Functions to "post-proccess" information parsed from SCL file.	*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*			scl2_datatype_create_all			*/
/*			scl2_ld_create_all				*/
/*									*/
/* NOTE: FC must be "ST" "MX" "CO" "SP" "SG" "SE" "SV" "CF" "DC" or "EX"*/
/*									*/
/* NOTE: scl2_datatype_create_all allocates an array of RESERVED_INFO	*/
/*   structures to save extra SCL data for each datatype created.	*/
/*   The array pointer is saved in the reserved_1 member of		*/
/*   RUNTIME_CTRL, to be used later by scl2_ld_create_all,		*/
/*   which then frees it (see reserved_free_all).			*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 03/06/07  JRB    31     Fix LogRef initial value (ObjectReference).	*/
/* 02/13/07  JRB    30	   Use RptEnabled max attribute for BRCB too.	*/
/*			   Save rpt scan rate in rpt_ctrl->scan_rate.	*/
/* 10/30/06  JRB    29     scl2_datatype_create_all: all args changed.	*/
/*			   scl2_ld_create_all: add vmd_ctrl, is_client args.*/
/*			   Use <Val> element of <DA> or <BDA> to init	*/
/*			   all variables containing the attribute.	*/
/*			   Instead of creating TDL, create RUNTIME_TYPE	*/
/*			   array directly (allows saving extra type info).*/
/*			   Don't need type names anymore. Only use names*/
/*			   if caller requests it.			*/
/*			   Allow bType="Check", "VisString???".		*/
/* 08/21/06  MDE    28     Added more scl_debug_mode			*/
/* 08/09/06  JRB    27     Create multiple RCBs for each URCB configured.*/
/*			   Add 01, 02, etc suffixes to all RCB names.	*/
/*			   Allow scl_rcb->datSet="" (i.e. datSet not	*/
/*			    present in ReportControl element of SCL file).*/
/*			   Allow datSet write with mvl61850_datset_wr_ind.*/
/*			   Chg DatSet in BRCB, URCB, GCB, LCB, MSVCB,	*/
/*			    and USVCB to Vstring129.			*/
/*			   Chg LogRef in LCB to Vstring129.		*/
/*			   Del mvlu_rpt_create_scan_ctrl2 call		*/
/*			    (new mvl61850_rpt_service automatically scans).*/
/* 08/04/06  MDE    26     Tweaked logging				*/
/* 08/04/06  MDE    25     Added scl_debug_mode, scl2_add_btype, etc.	*/
/* 06/22/06  RKR    24     Added Vstring129				*/
/* 03/20/06  JRB    23     Add code for Sampled Value config (see svcb).*/
/*			   Del unused scl_rcb_counters.			*/
/* 12/14/05  JRB    22     Fix init val of DatSet in LCB or GCB		*/
/*			   (must be ObjectReference).			*/
/* 11/22/05  JRB    21     Fix spelling of "BufTm" in brcb, urcb.	*/
/*			   (Only UCA uses the spelling "BufTim").	*/
/* 09/15/05  JRB    20     Fix spelling.				*/
/* 07/27/05  JRB    19     Don't set OptFlds len=9 (default=10 is good).*/
/*			   Don't set OptFlds bits bufovfl, entryID for URCB.*/
/* 07/25/05  JRB    18     scl2_ld_create_all: Add brcb_bufsize arg.	*/
/* 07/21/05  JRB    17     Set initial vals for LCB, GCB, SCB.		*/
/* 07/11/05  JRB    16     scl2_ld_create_all: Call			*/
/*			   mvl61850_ctl_lastapplerror_create.		*/
/* 06/27/05  JRB    15     Use mvl_nvl_add (mvlu_rpt_nvl_add is obsolete).*/
/* 05/27/05  JRB    14     Construct NVL name from LN & DataSet name	*/
/*			   as 61850-8-1 requires.			*/
/* 05/25/05  JRB    13     Del all code to generate RCB name & just use	*/
/*			   name configured in SCL file (scl_rcb->name).	*/
/*			   Add errflag so if one call to tdladd_string	*/
/*			   fails, subsequent calls fail too.		*/
/* 05/09/05  JRB    12     Chg leaf write functions for SqNum (in BRCB	*/
/*			   & URCB) to u_no_write_allowed.		*/
/* 04/05/05  MDE    11     Supress invalid log messages			*/
/* 03/18/05  JRB    10     Use mvl_max_dyn when creating domains.	*/
/* 02/15/05  JRB    09     Use new generated scl_ld->domName, not	*/
/*			   scl_ld->inst as domain name.			*/
/*			   Use new generated scl_fcda->domName, not	*/
/*			   scl_fcda->ldInst as domain name.		*/
/*			   Use new scl_ln->varName, generated once,	*/
/*			   instead of generating ln_name repeatedly.	*/
/*			   Compute max_num_var for mvl_dom_add call.	*/
/* 01/19/05  JRB    08     Add scl2_dai_set_value_all & use it to init	*/
/*			    data from DOI/SDI/DAI entries in SCL file.	*/
/*			   Fix len on all strncat calls.		*/
/*			   scl2_rcb_create_all: init ln_name just once.	*/
/*			   Improve some logging.			*/
/* 09/01/04  JRB    07     Map Octet64 to OVstring64 (to match 61850-8-1)*/
/* 08/29/04  JRB    06     Chg Quality type back to BVstring13 because	*/
/*			   final IEC-61850-8-1 changed back.		*/
/* 08/19/04  JRB    05     Init return value in scl2_ld_create_all.	*/
/* 07/19/04  JRB    04     Add tdladd_lg, tdladd_go_or_gs.		*/
/* 07/14/04  JRB    03     Chg Quality type to BVstring14.		*/
/* 07/09/04  JRB    02     scl2_ld_create_all: add reportScanRate arg	*/
/*			   to this and lower level functions.		*/
/* 07/02/04  JRB    01     Initial Revision.				*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "scl.h"
#include "sx_log.h"
#include "mvl_defs.h"
#include "mvl_uca.h"
#include "mvl_log.h"
#include "str_util.h"	/* for strn..._safe	protos	*/
#include "sx_arb.h"	/* for sxaText.... proto	*/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/* RESERVED_INFO: structure for extra type related info that is not	*/
/* contained in RUNTIME_TYPE or RUNTIME_CTRL. Allocate array of these.	*/
typedef struct
{
	SCL_ENUMTYPE *scl_enumtype;	/* SCL enumtype def for this type	*/
	ST_CHAR *Val;			/* SCL initial value for this type	*/
} RESERVED_INFO;

/* CRITICAL: this struct must be compatible with RUNTIME_TYPE.	*/
/* If either one changes, the other must change to match.	*/
typedef struct
{
	ST_UINT8 LogEna;		/* Bool	*/
	ST_CHAR LogRef[MVL61850_MAX_OBJREF_LEN+1];	/* Vstring129 (ObjectReference)	*/
	ST_CHAR DatSet[MVL61850_MAX_OBJREF_LEN+1];	/* Vstring129 (ObjectReference)	*/
	MMS_BTIME6 OldEntrTim;	/* Btime6	*/
	MMS_BTIME6 NewEntrTim;	/* Btime6	*/
	ST_UINT8 OldEntr[8];		/* Ostring8	*/
	ST_UINT8 NewEntr[8];		/* Ostring8	*/
	MMS_BVSTRING TrgOps;	/* BVstring6 - struct includes 1 byte data. Enough.*/
	ST_UINT32 IntgPd;		/* Ulong	*/
} MVL61850_LCB_DATA;	/* struct to store data for LCB (IEC Log Control Block)	*/

/* CRITICAL: this struct must be compatible with RUNTIME_TYPE.	*/
/* If either one changes, the other must change to match.	*/
typedef struct
{
	ST_BOOLEAN GoEna;
	ST_CHAR GoID[66];
	ST_CHAR DatSet[MVL61850_MAX_OBJREF_LEN+1];	/* Vstring129 (ObjectReference)*/
	ST_UINT32 ConfRev;
	ST_BOOLEAN NdsCom;
	struct
	{
		ST_UCHAR Addr[6];
		ST_UINT8 PRIORITY;
		ST_UINT16 VID;
		ST_UCHAR APPID[5];
	} DstAddress;
} MVL61850_GCB_DATA;	/* struct to store data for GCB (GOOSE Control Block)	*/

/* CRITICAL: this struct must be compatible with RUNTIME_TYPE.	*/
/* If either one changes, the other must change to match.	*/
typedef struct
{
	ST_BOOLEAN GsEna;
	ST_CHAR GsID[66];
	ST_CHAR DNALabels[32][66];
	ST_CHAR UserSTLabels[128][66];
	struct
	{
		ST_CHAR GsID[66];
		MMS_BTIME6 t;
		ST_UINT32 SqNum;
		ST_UINT32 StNum;
		ST_UINT32 TAL;
		ST_UINT32 usec;
		ST_UINT16 PhsID;
		ST_UCHAR DNA[8];
		ST_UCHAR UserST[32];
	} LSentData;
} MVL61850_SCB_DATA;	/* struct to store data for SCB (GSSE Control Block)	*/

typedef struct
{
	ST_UINT8 SvEna;		/* Bool	*/
	ST_CHAR MsvID[MVL61850_MAX_RPTID_LEN+1];		/* Vstring65	*/
	ST_CHAR DatSet[MVL61850_MAX_OBJREF_LEN+1];	/* Vstring129 (ObjectReference)	*/
	ST_UINT32 ConfRev;		/* Ulong	*/
	ST_UINT32 SmpRate;		/* Ulong	*/
	MMS_BVSTRING OptFlds;	/* BVstring3 - struct includes 1 byte data. Enough.*/
} MVL61850_MSVCB_DATA;	/* struct to store data for MSVCB	*/

typedef struct
{
	ST_UINT8 SvEna;		/* Bool	*/
	ST_UINT8 Resv;		/* Bool	*/
	ST_CHAR UsvID[MVL61850_MAX_RPTID_LEN+1];		/* Vstring65	*/
	ST_CHAR DatSet[MVL61850_MAX_OBJREF_LEN+1];	/* Vstring129 (ObjectReference)	*/
	ST_UINT32 ConfRev;		/* Ulong	*/
	ST_UINT32 SmpRate;		/* Ulong	*/
	MMS_BVSTRING OptFlds;	/* BVstring3 - struct includes 1 byte data. Enough.*/
} MVL61850_USVCB_DATA;	/* struct to store data for USVCB	*/

// hejian add on 2010-7-30
SCL_SMV *scl_smv_find (SCL_INFO *scl_info, SCL_LD *scl_ld, SCL_SVCB *scl_svcb)
{
	SCL_SUBNET *scl_subnet;
	SCL_CAP *scl_cap;
	SCL_SMV *scl_smv;

	for (scl_subnet = (SCL_SUBNET *) list_find_last ((DBL_LNK *) scl_info->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *) list_find_prev ((DBL_LNK *) scl_info->subnetHead, (DBL_LNK *) scl_subnet))
	{
		for (scl_cap = (SCL_CAP *) list_find_last ((DBL_LNK *) scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *) list_find_prev ((DBL_LNK *) scl_subnet->capHead, (DBL_LNK *) scl_cap))
		{
			//hejian del on 2010-11-5
			//if (strcmp (scl_info->iedName, scl_cap->iedName) == 0)
			{	/* found matching iedName	*/
				for (scl_smv = (SCL_SMV *) list_find_last ((DBL_LNK *) scl_cap->smvHead);
					scl_smv != NULL;
					scl_smv = (SCL_SMV *) list_find_prev ((DBL_LNK *) scl_cap->smvHead, (DBL_LNK *) scl_smv))
				{
					if (strcmp (scl_ld->inst, scl_smv->ldInst) == 0
						&& (strcmp (scl_svcb->name, scl_smv->cbName) == 0))
					{	/* Found it. Too many loops to break out of, so just return.*/
						return (scl_smv);
					}
				}	/* end scl_gse loop	*/
			}	
		}		/* end scl_cap loop	*/
	}		/* end scl_subnet loop	*/

	return (NULL);	/* Not found	*/
}

// hhzhen add 0112
SCL_GSE *scl_gse_find (SCL_INFO *scl_info, SCL_LD *scl_ld, SCL_GCB *scl_gcb)
{
	SCL_SUBNET *scl_subnet;
	SCL_CAP *scl_cap;
	SCL_GSE *scl_gse;

	for (scl_subnet = (SCL_SUBNET *) list_find_last ((DBL_LNK *) scl_info->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *) list_find_prev ((DBL_LNK *) scl_info->subnetHead, (DBL_LNK *) scl_subnet))
	{
		for (scl_cap = (SCL_CAP *) list_find_last ((DBL_LNK *) scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *) list_find_prev ((DBL_LNK *) scl_subnet->capHead, (DBL_LNK *) scl_cap))
		{
			//hejian del on 2010-11-5
//			if (strcmp (scl_info->iedName, scl_cap->iedName) == 0)
			{	/* found matching iedName	*/
				for (scl_gse = (SCL_GSE *) list_find_last ((DBL_LNK *) scl_cap->gseHead);
					scl_gse != NULL;
					scl_gse = (SCL_GSE *) list_find_prev ((DBL_LNK *) scl_cap->gseHead, (DBL_LNK *) scl_gse))
				{
					if ((strcmp (scl_ld->inst, scl_gse->ldInst) == 0)
						&& (strcmp (scl_gcb->name, scl_gse->cbName) == 0))
					{	/* Found it. Too many loops to break out of, so just return.*/
						return (scl_gse);
					}
				}	/* end scl_gse loop	*/
			}	
		}		/* end scl_cap loop	*/
	}		/* end scl_subnet loop	*/

	return (NULL);	/* Not found	*/
}


/************************************************************************/
/* STATIC FUNCTION PROTOTYPES						*/
/* Need prototypes for these static functions because rtadd_da_struct	*/
/* calls rtadd_da_or_bda and vice versa.				*/
/* Other static functions are just defined in the order they are needed	*/
/* so prototypes are not needed.					*/
/************************************************************************/
static ST_RET rtadd_da_struct (
							   RUNTIME_BUILD_CTXT *ctxt,
							   SCL_INFO *scl_info,
							   ST_CHAR *type_id,
							   ST_CHAR *comp_name);
static ST_RET rtadd_da_or_bda (
							   RUNTIME_BUILD_CTXT *ctxt,
							   SCL_INFO *scl_info,
							   ST_CHAR *name,		/* DA or BDA name	*/
							   ST_CHAR *bType,		/* DA or BDA bType	*/
							   ST_CHAR *type,		/* DA or BDA type	*/
							   ST_UINT count,		/* DA or BDA count	*/
							   ST_CHAR *Val);		/* DA or BDA Val	*/

/************************************************************************/
/************************************************************************/
ST_BOOLEAN scl_debug_mode;
ST_INT scl_debug_mode_error_count;
SCL2_BTYPE *scl2_btype_list;

/************************************************************************/
/* Add a "custom" basic type to the RUNTIME_TYPE array.			*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_custom_btype (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *btype, ST_CHAR *comp_name)
{
	SCL2_BTYPE *sclBtype;
	sclBtype = scl2_btype_list;
	while (sclBtype != NULL)
	{
		if (!strcmp (sclBtype->btype, btype))
		{      /* already checked that this is simple type, so just use ...rt_first*/
			return (ms_rt_bld_add_special (ctxt, comp_name, sclBtype->rt_ctrl->rt_first));
		}
		sclBtype = list_get_next (scl2_btype_list, sclBtype);
	}
	SXLOG_ERR1 ("bType='%s' is not recognized", btype);
	return (SD_FAILURE);
}
/************************************************************************/
/* Add a basic type to the RUNTIME_TYPE array.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_btype (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *btype, ST_CHAR *comp_name)
{
	//hejian add on 2010-4-7
	char typebuf[64];

	strcpy(typebuf, btype);
	strupr(typebuf);

	/* First check for any of the PredefinedBasicTypes.	*/
	if (strcmp (typebuf, "BOOLEAN") == 0)
		return (ms_rt_bld_add_bool (ctxt, comp_name));
	if (strcmp (typebuf, "INT8") == 0)
		return (ms_rt_bld_add_int (ctxt, comp_name, 1));
	if (strcmp (typebuf, "INT16") == 0)
		return (ms_rt_bld_add_int (ctxt, comp_name, 2));
	if (strcmp (typebuf, "INT32") == 0)
		return (ms_rt_bld_add_int (ctxt, comp_name, 4));

	///////////hejian add on 2010-3-25////////////////
	if (strcmp (typebuf, "INT64") == 0)
		return (ms_rt_bld_add_int (ctxt, comp_name, 8));
	if (strcmp (typebuf, "INT128") == 0)
		return (ms_rt_bld_add_int (ctxt, comp_name, 16));
	///////////////////////////////////////////////////

	if (strcmp (typebuf, "INT8U") == 0)
		return (ms_rt_bld_add_uint (ctxt, comp_name, 1));
	if (strcmp (typebuf, "INT16U") == 0)
		return (ms_rt_bld_add_uint (ctxt, comp_name, 2));
	if (strcmp (typebuf, "INT32U") == 0)
		return (ms_rt_bld_add_uint (ctxt, comp_name, 4));
	if (strcmp (typebuf, "FLOAT32") == 0)
		return (ms_rt_bld_add_float (ctxt, comp_name, 4));
	if (strcmp (typebuf, "FLOAT64") == 0)
		return (ms_rt_bld_add_float (ctxt, comp_name, 8));
	if (strcmp (typebuf, "DBPOS") == 0
		|| strcmp (typebuf, "TCMD") == 0
		|| strcmp (typebuf, "CHECK") == 0)
		return (ms_rt_bld_add_bstring (ctxt, comp_name, 2));	/* 2 bits*/
	if (strcmp (typebuf, "QUALITY") == 0)
		return (ms_rt_bld_add_bvstring (ctxt, comp_name, 13));	/* max 13 bits*/
	if (strcmp (typebuf, "TIMESTAMP") == 0)
		return (ms_rt_bld_add_utctime (ctxt, comp_name));

	///////////hejian add on 2010-4-7////////////////
	if (strcmp (typebuf, "BITSTRING8") == 0)
		return (ms_rt_bld_add_bstring (ctxt, comp_name, 1));
	if (strcmp (typebuf, "BITSTRING16") == 0)
		return (ms_rt_bld_add_bstring (ctxt, comp_name, 2));
	if (strcmp (typebuf, "BITSTRING32") == 0)
		return (ms_rt_bld_add_bstring (ctxt, comp_name, 4));
	if (strcmp (typebuf, "BITSTRING64") == 0)
		return (ms_rt_bld_add_bstring (ctxt, comp_name, 8));
	///////////////////////////////////////////////////

	if (strcmp (typebuf, "VISSTRING32") == 0)
		return (ms_rt_bld_add_vstring (ctxt, comp_name, 32));	/* max 32 char*/
	if (strcmp (typebuf, "VISSTRING64") == 0)
		return (ms_rt_bld_add_vstring (ctxt, comp_name, 64));	/* max 64 char*/
	if (strcmp (typebuf, "VISSTRING65") == 0)
		return (ms_rt_bld_add_vstring (ctxt, comp_name, 65));	/* max 65 char*/
	if (strcmp (typebuf, "VISSTRING128") == 0)
		return (ms_rt_bld_add_vstring (ctxt, comp_name, 128));	/* max 128 char*/
	if (strcmp (typebuf, "VISSTRING129") == 0)
		return (ms_rt_bld_add_vstring (ctxt, comp_name, 129));	/* max 129 char*/
	if (strcmp (typebuf, "VISSTRING255") == 0)
		return (ms_rt_bld_add_vstring (ctxt, comp_name, 255));	/* max 255 char*/
	if (strcmp (typebuf, "OCTET64") == 0)
		/* 61850-8-1 says all octet strings are variable length*/
		return (ms_rt_bld_add_ovstring (ctxt, comp_name, 64));	/* max 64 bytes*/
	if (strcmp (typebuf, "ENTRYTIME") == 0)
		return (ms_rt_bld_add_btime6 (ctxt, comp_name));
	if (strcmp (typebuf, "UNICODE255") == 0)
		return (ms_rt_bld_add_utf8vstring (ctxt, comp_name, 255));	/* max 255 char*/
	/* If the "typebuf" does not match any PredefinedBasicTypes,		*/
	/* see if it matches a "custom" type (i.e. a type created earlier by	*/
	/* calling scl2_add_btype).			*/
	return (ms_rt_bld_61850_add_custom_btype (ctxt, btype, comp_name));
}

/************************************************************************/
/*			ms_rt_bld_61850_add_brcb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_brcb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_vstring   (ctxt, "RptID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_bool      (ctxt, "RptEna");
	ms_rt_bld_add_vstring   (ctxt, "DatSet", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_uint      (ctxt, "ConfRev", 4);
	ms_rt_bld_add_bvstring  (ctxt, "OptFlds", 10);
	ms_rt_bld_add_uint      (ctxt, "BufTm", 4);
	ms_rt_bld_add_uint      (ctxt, "SqNum", 2);
	ms_rt_bld_add_bvstring  (ctxt, "TrgOps", 6);
	ms_rt_bld_add_uint      (ctxt, "IntgPd", 4);
	ms_rt_bld_add_bool      (ctxt, "GI");
	ms_rt_bld_add_bool      (ctxt, "PurgeBuf");
	ms_rt_bld_add_ostring   (ctxt, "EntryID", 8);
	ms_rt_bld_add_btime6    (ctxt, "TimeofEntry");
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			ms_rt_bld_61850_add_urcb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_urcb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_vstring   (ctxt, "RptID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_bool      (ctxt, "RptEna");
	ms_rt_bld_add_bool      (ctxt, "Resv");
	ms_rt_bld_add_vstring   (ctxt, "DatSet", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_uint      (ctxt, "ConfRev", 4);
	ms_rt_bld_add_bvstring  (ctxt, "OptFlds", 10);
	ms_rt_bld_add_uint      (ctxt, "BufTm", 4);
	ms_rt_bld_add_uint      (ctxt, "SqNum", 1);
	ms_rt_bld_add_bvstring  (ctxt, "TrgOps", 6);
	ms_rt_bld_add_uint      (ctxt, "IntgPd", 4);
	ms_rt_bld_add_bool      (ctxt, "GI");
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			ms_rt_bld_61850_add_lcb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_lcb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_bool      (ctxt, "LogEna");
	ms_rt_bld_add_vstring   (ctxt, "LogRef", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_vstring   (ctxt, "DatSet", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_btime6    (ctxt, "OldEntrTim");
	ms_rt_bld_add_btime6    (ctxt, "NewEntrTim");
	ms_rt_bld_add_ostring   (ctxt, "OldEntr", 8);
	ms_rt_bld_add_ostring   (ctxt, "NewEntr", 8);
	ms_rt_bld_add_bvstring  (ctxt, "TrgOps", 6);
	ms_rt_bld_add_uint      (ctxt, "IntgPd", 4);
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			ms_rt_bld_61850_add_gcb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_gcb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_bool      (ctxt, "GoEna");
	ms_rt_bld_add_vstring   (ctxt, "GoID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_vstring   (ctxt, "DatSet", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_uint      (ctxt, "ConfRev", 4);
	ms_rt_bld_add_bool      (ctxt, "NdsCom");
	ms_rt_bld_add_str_start (ctxt, "DstAddress");
	ms_rt_bld_add_ostring   (ctxt, "Addr", 6);
	ms_rt_bld_add_uint      (ctxt, "PRIORITY", 1);
	ms_rt_bld_add_uint      (ctxt, "VID", 2);
	//ms_rt_bld_add_uint      (ctxt, "APPID", 2);
	ms_rt_bld_add_ostring   (ctxt, "APPID", 5); //hejian alter on 2010-9-4
	ms_rt_bld_add_str_end   (ctxt);
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			ms_rt_bld_61850_add_scb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_scb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_bool      (ctxt, "GsEna");
	ms_rt_bld_add_vstring   (ctxt, "GsID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_arr_start (ctxt, "DNALabels", 32);
	ms_rt_bld_add_vstring   (ctxt, "DNALabels", 65);
	ms_rt_bld_add_arr_end   (ctxt);
	ms_rt_bld_add_arr_start (ctxt, "UserSTLabels", 128);
	ms_rt_bld_add_vstring   (ctxt, "DNALabels", 65);
	ms_rt_bld_add_arr_end   (ctxt);
	ms_rt_bld_add_str_start (ctxt, "LSentData");
	ms_rt_bld_add_vstring   (ctxt, "GsID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_btime6    (ctxt, "t");
	ms_rt_bld_add_uint      (ctxt, "SqNum", 4);
	ms_rt_bld_add_uint      (ctxt, "StNum", 4);
	ms_rt_bld_add_uint      (ctxt, "TAL", 4);
	ms_rt_bld_add_uint      (ctxt, "usec", 4);
	ms_rt_bld_add_uint      (ctxt, "PhsID", 2);
	ms_rt_bld_add_bstring   (ctxt, "DNA", 64);
	ms_rt_bld_add_bstring   (ctxt, "UserST", 256);
	ms_rt_bld_add_str_end   (ctxt);
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			ms_rt_bld_61850_add_msvcb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_msvcb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_bool      (ctxt, "SvEna");
	ms_rt_bld_add_vstring   (ctxt, "MsvID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_vstring   (ctxt, "DatSet", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_uint      (ctxt, "ConfRev", 4);
	ms_rt_bld_add_uint      (ctxt, "SmpRate", 4);
	ms_rt_bld_add_bvstring  (ctxt, "OptFlds", 3);
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			ms_rt_bld_61850_add_usvcb				*/
/* NOTE: check only last return code. If one "ms_rt_bld_add_*" call fails,	*/
/*       subsequent calls will fail too.				*/
/************************************************************************/
static ST_RET ms_rt_bld_61850_add_usvcb (RUNTIME_BUILD_CTXT *ctxt, ST_CHAR *comp_name)
{
	ST_RET retcode;
	ms_rt_bld_add_str_start (ctxt, comp_name);
	ms_rt_bld_add_bool      (ctxt, "SvEna");
	ms_rt_bld_add_bool      (ctxt, "Resv");
	ms_rt_bld_add_vstring   (ctxt, "UsvID", MVL61850_MAX_RPTID_LEN);
	ms_rt_bld_add_vstring   (ctxt, "DatSet", MVL61850_MAX_OBJREF_LEN);
	ms_rt_bld_add_uint      (ctxt, "ConfRev", 4);
	ms_rt_bld_add_uint      (ctxt, "SmpRate", 4);
	ms_rt_bld_add_bvstring  (ctxt, "OptFlds", 3);
	retcode = ms_rt_bld_add_str_end   (ctxt);
	return (retcode);
}
/************************************************************************/
/*			reserved_free_all				*/
/* Find all types used by this VMD. If rt_ctrl->reserved_1 is not NULL,	*/
/* we must have allocated it in "scl2_datatype_create", so free it and	*/
/* set it to NULL.							*/
/************************************************************************/
static ST_VOID reserved_free_all (MVL_VMD_CTRL *vmd_ctrl)

{
	ST_INT type_id;
	MVL_TYPE_CTRL *type_ctrl;
	RUNTIME_CTRL *rt_ctrl;
	/* This only works for "dynamic" types so start with first dynamic type.*/
	for (type_id = mvl_num_types - mvl_max_dyn.types; type_id < mvl_num_types; type_id++)
	{
		type_ctrl = mvl_vmd_type_ctrl_find (vmd_ctrl, type_id);
		if (type_ctrl)		/* type found in this VMD	*/
		{
			rt_ctrl = type_ctrl->rt_ctrl;		/* always valid	*/
			if (rt_ctrl->reserved_1 != NULL)
			{
				chk_free (rt_ctrl->reserved_1);
				rt_ctrl->reserved_1 = NULL;
			}
		}
	}
}
/************************************************************************/
/*			scl_make_objref					*/
/* Construct ObjectReference from SCL info.				*/
/************************************************************************/
static ST_RET scl_make_objref (
							   SCL_LD *scl_ld,
							   SCL_LN *scl_ln,
							   ST_CHAR *objName,	/* Object (DataSet, Data) name		*/
							   ST_CHAR *objRef,	/* ptr to resulting ObjRef string	*/
							   ST_UINT max_len)	/* max len of resulting ObjRef string	*/
{
	ST_RET retcode;
	if (strlen (scl_ld->domName) +
		strlen (scl_ln->prefix) + strlen (scl_ln->lnClass) + strlen (scl_ln->inst) +
		strlen (objName) + 2 > max_len)	/* 2 added for '/' and '$'	*/
	{
		SXLOG_ERR1 ("Constructed ObjectReference would be too long for '%s'.", objName);
		retcode = SD_FAILURE;
	}
	else
	{
		sprintf (objRef, "%s/%s%s%s$%s", scl_ld->domName, scl_ln->prefix,
			scl_ln->lnClass, scl_ln->inst, objName);
		retcode = SD_SUCCESS;
	}
	return (retcode);
}

/************************************************************************/
/*			scl_make_objref2				*/
/* Construct ObjectReference from SCL info (LN Name not included).	*/
/* Similar to scl_make_objref, but does not include LN name.		*/
/************************************************************************/
static ST_RET scl_make_objref2 (
								SCL_LD *scl_ld,
								ST_CHAR *objName,	/* Object name				*/
								ST_CHAR *objRef,	/* ptr to resulting ObjRef string	*/
								ST_UINT max_len)	/* max len of resulting ObjRef string	*/
{
	ST_RET retcode;
	if (strlen (scl_ld->domName) +
		strlen (objName) + 2 > max_len)	/* 2 added for '/' and '$'	*/
	{
		SXLOG_ERR1 ("Constructed ObjectReference would be too long for '%s'.", objName);
		retcode = SD_FAILURE;
	}
	else
	{
		sprintf (objRef, "%s/%s", scl_ld->domName, objName);
		retcode = SD_SUCCESS;
	}
	return (retcode);
}

/************************************************************************/
/*			special_type_name				*/
/* Create type name for a special LN (one that includes RCB, LCB, etc.).*/
/* NOTE: do not use '$'. This will confuse "mvlu_set_leaf_param".	*/
/************************************************************************/
ST_RET special_type_name (ST_CHAR *prefix, SCL_LD *scl_ld, SCL_LN *scl_ln,
						  ST_CHAR *type_name, size_t type_name_size)
{	/* Create unique type name for this LN.	*/
	size_t len = 0;
	ST_RET retcode;
	if (prefix)	/* NOTE: if prefix is not NULL, add prefix.	*/
		len += strlen (prefix);
	len += strlen (scl_ld->inst);
	len += strlen (scl_ln->prefix);
	len += strlen (scl_ln->lnClass);
	len += strlen (scl_ln->inst);

	type_name [0] = '\0';		/* start with empty string	*/
	if (len < type_name_size)
	{				/* name will fit, so write it	*/
		if (prefix)
			strcat (type_name, prefix);
		strcat (type_name, scl_ld->inst);
		strcat (type_name, scl_ln->prefix);
		strcat (type_name, scl_ln->lnClass);
		strcat (type_name, scl_ln->inst);
		retcode = SD_SUCCESS;
	}
	else
		retcode = SD_FAILURE;	/* name would be too long	*/
	return (retcode);
}

/************************************************************************/
/*			simple_type_name				*/
/* Create type name for a simple type.					*/
/* NOTE: do not use '$'. This will confuse "mvlu_set_leaf_param".	*/
/************************************************************************/
ST_RET simple_type_name (ST_CHAR *prefix, SCL_LNTYPE *scl_lntype,
						 ST_CHAR *type_name, size_t type_name_size)
{	/* Create unique type name for this LN.	*/
	size_t len = 0;
	ST_RET retcode;

	if (prefix)	/* NOTE: if prefix is not NULL, add prefix.	*/
		len += strlen (prefix);
	len += strlen (scl_lntype->id);

	type_name [0] = '\0';		/* start with empty string	*/
	if (len < type_name_size)
	{				/* name will fit, so write it	*/
		if (prefix)
			strcat (type_name, prefix);
		strcat (type_name, scl_lntype->id);
		retcode = SD_SUCCESS;
	}
	else
		retcode = SD_FAILURE;	/* name would be too long	*/
	return (retcode);
}

/************************************************************************/
/*			scl_find_dotype					*/
/************************************************************************/
static SCL_DOTYPE *scl_find_dotype (
									SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									ST_CHAR *type_id)
{
	SCL_DOTYPE *scl_dotype;

	for (scl_dotype = (SCL_DOTYPE *) list_find_last ((DBL_LNK *) scl_info->doTypeHead);
		scl_dotype != NULL;
		scl_dotype = (SCL_DOTYPE *) list_find_prev ((DBL_LNK *) scl_info->doTypeHead, (DBL_LNK *) scl_dotype))
	{
		if (strcmp (scl_dotype->id, type_id) ==0)
			return (scl_dotype);
	}
	return (NULL);	/* match not found	*/
}
/************************************************************************/
/*			scl_find_datype					*/
/************************************************************************/
static SCL_DATYPE *scl_find_datype (
									SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									ST_CHAR *type_id)
{
	SCL_DATYPE *scl_datype;

	for (scl_datype = (SCL_DATYPE *) list_find_last ((DBL_LNK *) scl_info->daTypeHead);
		scl_datype != NULL;
		scl_datype = (SCL_DATYPE *) list_find_prev ((DBL_LNK *) scl_info->daTypeHead, (DBL_LNK *) scl_datype))
	{
		if (strcmp (scl_datype->id, type_id) ==0)
			return (scl_datype);
	}
	return (NULL);	/* match not found	*/
}
/************************************************************************/
/************************************************************************/
static SCL_DATASET *scl_find_dataset (
									  SCL_LN *scl_ln,
									  ST_CHAR *dataset_name)
{
	SCL_DATASET *scl_dataset;

	for (scl_dataset = (SCL_DATASET *) list_find_last ((DBL_LNK *) scl_ln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *) list_find_prev ((DBL_LNK *) scl_ln->datasetHead, (DBL_LNK *) scl_dataset))
	{
		if (strcmp (scl_dataset->name, dataset_name) ==0)
			return (scl_dataset);
	}
	return (NULL);	/* match not found	*/
}

/************************************************************************/
/*			scl2_find_enumtype				*/
/************************************************************************/
SCL_ENUMTYPE *scl2_find_enumtype (SCL_INFO *scl_info, ST_CHAR *name)
{
	SCL_ENUMTYPE *scl_enumtype;
	for (scl_enumtype = (SCL_ENUMTYPE *) list_find_last ((DBL_LNK *) scl_info->enumTypeHead);
		scl_enumtype != NULL;
		scl_enumtype = (SCL_ENUMTYPE *) list_find_prev ((DBL_LNK *) scl_info->enumTypeHead, (DBL_LNK *) scl_enumtype))
	{
		if (strcmp (scl_enumtype->id, name) == 0)
			break;	/* found a match	*/
	}
	return (scl_enumtype);
}

/************************************************************************/
/*			scl2_add_btype					*/
/************************************************************************/
SCL2_BTYPE *scl2_add_btype (ST_CHAR *btype, ST_CHAR *tdl)
{
	SCL2_BTYPE *sclBtype;
	RUNTIME_CTRL *rt_ctrl;
	ST_UCHAR asn1_buf [200];	/* simple types only, so this should be big enough*/

	sclBtype = NULL;	/* assume failure for now	*/
	rt_ctrl = ms_tdl_to_runtime (tdl, asn1_buf, sizeof(asn1_buf));
	if (rt_ctrl)
	{
		if (rt_ctrl->rt_num == 1)	/* must be simple type	*/
		{
			sclBtype = chk_calloc (1, sizeof (SCL2_BTYPE) + strlen (btype) + 1);
			sclBtype->btype = (ST_CHAR *) (sclBtype + 1);	/* point after struct*/
			strcpy (sclBtype->btype, btype);
			sclBtype->rt_ctrl = rt_ctrl;	/* rt_ctrl allocated, just save ptr*/
			list_add_last (&scl2_btype_list, sclBtype);
		}
		else
		{	/* Complex type not allowed, so destroy it now. Err return already set*/
			ms_runtime_destroy (rt_ctrl);
		}
	}
	return (sclBtype);
}

/************************************************************************/
/*			rtadd_sdo					*/
/* NOTE: if (error) returned, caller should break out of loop.		*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET rtadd_sdo (
						 RUNTIME_BUILD_CTXT *rt_ctxt,
						 SCL_INFO *scl_info,
						 ST_CHAR *FC,		/* FC to match	*/
						 ST_CHAR *name,		/* SDO name	*/
						 ST_CHAR *type)		/* SDO type	*/
{
	SCL_DOTYPE *scl_dotype;
	SCL_DA *scl_da;
	ST_RET retcode;
	ST_INT rt_num_after_str_start;	/* index after str_start added	*/

	/* First add SDO name (passed to this funct). May need rollback later	*/
	if (ms_rt_bld_add_str_start (rt_ctxt, name)!=SD_SUCCESS)
		return (SD_FAILURE);	/* error (already logged)	*/

	/* Save current index. Use later to check if any types added.	*/
	rt_num_after_str_start = rt_ctxt->rt_ctrl->rt_num;

	/* Find DOType whose "id" matches the SDO "type".	*/
	scl_dotype = scl_find_dotype (scl_info, type);
	if (scl_dotype)
	{
		/* Find all DA or SDO in this DO that match the FC	*/
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_da = (SCL_DA *) list_find_last ((DBL_LNK *) scl_dotype->daHead);
			scl_da != NULL;
			scl_da = (SCL_DA *) list_find_prev ((DBL_LNK *) scl_dotype->daHead, (DBL_LNK *) scl_da))
		{
			if (scl_da->objtype == SCL_OBJTYPE_SDO)
			{		/* ERROR: just break & ret NULL	*/
				SXLOG_ERR1 ("SDO named '%s' defined inside another SDO: not supported.", scl_da->name);
				return (SD_FAILURE);	/* error	*/
			}
			else
			{	/* objtype must be SCL_OBJTYPE_DA	*/
				if (strcmp (scl_da->fc, FC) == 0)	/* FC of this DA matches FC	*/
				{
					retcode = rtadd_da_or_bda (rt_ctxt, scl_info, scl_da->name, scl_da->bType,
						scl_da->type, scl_da->count, scl_da->Val);
					if (retcode != SD_SUCCESS)	/* error (already logged)	*/
						return (retcode);			/* error	*/
				}
			}
		}	/* end "for (scl_da...)" loop	*/

	}
	else
	{
		SXLOG_ERR1 ("SDO type '%s' cannot be found", type);
		return (SD_FAILURE);	/* error	*/
	}

	/* Check if any types were added after start of struct	*/
	if (rt_ctxt->rt_ctrl->rt_num > rt_num_after_str_start)
	{			/* types were added, so finish struct now	*/
		if (ms_rt_bld_add_str_end (rt_ctxt) != SD_SUCCESS)
			return (SD_FAILURE);	/* error (already logged)	*/
	}
	else
	{			/* types NOT added so remove start of struct	*/
		ms_rt_bld_remove_last (rt_ctxt);
	}
	return (SD_SUCCESS);	/* only successful return	*/
}
/************************************************************************/
/*			rtadd_da_or_bda				*/
/* NOTE: if (error) returned, caller should break out of loop.	*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET rtadd_da_or_bda (
							   RUNTIME_BUILD_CTXT *rt_ctxt,
							   SCL_INFO *scl_info,
							   ST_CHAR *name,		/* DA or BDA name	*/
							   ST_CHAR *bType,		/* DA or BDA bType	*/
							   ST_CHAR *type,		/* DA or BDA type	*/
							   ST_UINT count,		/* DA or BDA count	*/
							   ST_CHAR *Val)		/* DA or BDA Val (may be NULL)	*/
{
	ST_RET retcode;
	RESERVED_INFO *reserved_info;	/* ptr to array of extra type info.	*/

	/* Cast "reserved_1" pointer to the type we allocated.	*/
	reserved_info = (RESERVED_INFO *) rt_ctxt->rt_ctrl->reserved_1;

	/* If count!=0, this is array.	*/
	if (count)
	{
		/* NOTE: comp_name stored on arr_start AND on first element of array.*/
		if (ms_rt_bld_add_arr_start (rt_ctxt, name, count))
			return (SD_FAILURE);	/* error (already logged)	*/
	}

	/* Add different text depending on "bType" (Struct, Enum, or BasicType).	*/
	if (strcmp (bType, "Struct") == 0)
	{
		/* NOTE: this may cause recursion		*/
		/* (i.e. rtadd_da_struct may call rtadd_da_or_bda).*/
		retcode = rtadd_da_struct (rt_ctxt, scl_info, type, name);
		if (retcode != SD_SUCCESS)
		{
			SXLOG_ERR1 ("SCL ERROR: Can't add type definition for BDA Struct type=%s", type);
			return (retcode);
		}
	}
	else if (strcmp (bType, "Enum") == 0)
	{
		SCL_ENUMTYPE *scl_enumtype;
		if ((scl_enumtype = scl2_find_enumtype (scl_info, type))==NULL)
		{
			SXLOG_ERR1 ("EnumType '%s' could not be found", type);
			return (SD_FAILURE);
		}
		else
		{
			/* DEBUG: for now assume all enums are 8-bit	*/
			/* Someday may need to chk for maximum "EnumVal ord" to determine # of bits	*/
			/* Save the scl_enumtype pointer in reserved_info array.		*/
			/* CRITICAL: Do this BEFORE calling "ms_rt_bld_add_*" so that		*/
			/*           scl_enumtype is saved in the current array entry.	*/
			reserved_info[rt_ctxt->rt_ctrl->rt_num].scl_enumtype = scl_enumtype;
			if (ms_rt_bld_add_int (rt_ctxt, name, 1) != SD_SUCCESS)
				return (SD_FAILURE);	/* error (already logged)	*/
		}
	}
	else
	{				/* must be BasicType		*/
		/* Save initial value of this component, if present.	*/
		if (Val != NULL)
		{
			SXLOG_FLOW2 ("Saving Val='%s' for DA or BDA='%s'", Val, name);
			/* Can't process Val now. Save Val ptr in reserved_info array.	*/
			/* CRITICAL: Do this BEFORE calling "ms_rt_bld_add_*" so that		*/
			/*           "Val" is saved in the current array entry.		*/
			reserved_info[rt_ctxt->rt_ctrl->rt_num].Val = Val;
		}
		if (ms_rt_bld_61850_add_btype (rt_ctxt, bType, name))
			return (SD_FAILURE);	/* error (already logged)	*/
	}

	/* If count!=0, this is array.	*/
	if (count)
	{				/* this BDA is array	*/
		if (ms_rt_bld_add_arr_end (rt_ctxt))
			return (SD_FAILURE);	/* error (already logged)	*/
	}

	return (SD_SUCCESS);	/* only successful return	*/
}
/************************************************************************/
/*			rtadd_da_struct				*/
/* Add the RUNTIME_TYPE definitions for a DA that is "Struct".		*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET rtadd_da_struct (
							   RUNTIME_BUILD_CTXT *rt_ctxt,
							   SCL_INFO *scl_info,
							   ST_CHAR *type_id,
							   ST_CHAR *comp_name)
{
	SCL_DATYPE *scl_datype;
	SCL_BDA *scl_bda;
	ST_RET retcode;

	scl_datype = scl_find_datype (scl_info, type_id);
	if (scl_datype)
	{
		if (ms_rt_bld_add_str_start (rt_ctxt, comp_name)!=SD_SUCCESS)
			return (SD_FAILURE);	/* error (already logged)	*/

		/* Add info for all BDA in this DAType.	*/
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_bda = (SCL_BDA *) list_find_last ((DBL_LNK *) scl_datype->bdaHead);
			scl_bda != NULL;
			scl_bda = (SCL_BDA *) list_find_prev ((DBL_LNK *) scl_datype->bdaHead, (DBL_LNK *) scl_bda))
		{
			retcode = rtadd_da_or_bda (rt_ctxt, scl_info, scl_bda->name, scl_bda->bType,
				scl_bda->type, scl_bda->count, scl_bda->Val);
			if (retcode != SD_SUCCESS)	/* error (already logged)	*/
				return (retcode);			/* error	*/
		}	/* end "for (scl_bda...)" loop	*/

		if (ms_rt_bld_add_str_end (rt_ctxt)!=SD_SUCCESS)
			return (SD_FAILURE);	/* error (already logged)	*/
	}
	else
	{
		SXLOG_ERR1 ("SCL ERROR: DAType id=%s not found", type_id);
		return (SD_FAILURE);	/* error	*/
	}

	return (SD_SUCCESS);	/* only successful return	*/
}
/************************************************************************/
/*			rtadd_do					*/
/* Add the RUNTIME_TYPE definitions for one DO.				*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET rtadd_do (
						RUNTIME_BUILD_CTXT *rt_ctxt,
						char *FC,
						SCL_INFO *scl_info,
						ST_CHAR *do_name,
						SCL_DOTYPE *scl_dotype)
{
	SCL_DA *scl_da;
	ST_RET retcode;
	ST_INT rt_num_after_str_start;	/* index after str_start added	*/

	if (ms_rt_bld_add_str_start (rt_ctxt, do_name)!=SD_SUCCESS)
		return (SD_FAILURE);	/* error (already logged)	*/

	/* Save current index. Use later to check if any types added.	*/
	rt_num_after_str_start = rt_ctxt->rt_ctrl->rt_num;

	/* Find all DA or SDO in this DO that match the FC	*/
	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*     so get off list in reverse order.				*/
	for (scl_da = (SCL_DA *) list_find_last ((DBL_LNK *) scl_dotype->daHead);
		scl_da != NULL;
		scl_da = (SCL_DA *) list_find_prev ((DBL_LNK *) scl_dotype->daHead, (DBL_LNK *) scl_da))
	{
		if (scl_da->objtype == SCL_OBJTYPE_SDO)
		{
			/* Only "name" and "type" used for SDO.	*/
			retcode = rtadd_sdo (rt_ctxt, scl_info, FC, scl_da->name, scl_da->type);
			if (retcode != SD_SUCCESS)		/* error (already logged)	*/
				return (retcode);			/* error	*/
		}
		else
		{	/* objtype must be SCL_OBJTYPE_DA	*/
			if (strcmp (scl_da->fc, FC) == 0)	/* FC of this DA matches FC	*/
			{
				retcode = rtadd_da_or_bda (rt_ctxt, scl_info, scl_da->name, scl_da->bType,
					scl_da->type, scl_da->count, scl_da->Val);
				if (retcode != SD_SUCCESS)	/* error (already logged)	*/
					return (retcode);			/* error	*/
			}
		}
	}	/* end "for (scl_da...)" loop	*/

	/* Check if any types were added after start of struct	*/
	if (rt_ctxt->rt_ctrl->rt_num > rt_num_after_str_start)
	{			/* types were added, so finish struct now	*/
		if (ms_rt_bld_add_str_end (rt_ctxt) != SD_SUCCESS)
			return (SD_FAILURE);	/* error (already logged)	*/
	}
	else
	{			/* types NOT added so remove start of struct	*/
		ms_rt_bld_remove_last (rt_ctxt);
	}
	return (SD_SUCCESS);	/* only successful return	*/
}
/************************************************************************/
/*			rtadd_fc					*/
/* RETURNS:	SD_SUCCESS or error code				*/
/* Add the types for one FC to the RUNTIME_BUILD_CTXT.			*/
/************************************************************************/
static ST_RET rtadd_fc (
						RUNTIME_BUILD_CTXT *rt_ctxt,
						ST_CHAR *FC,
						SCL_INFO *scl_info,
						SCL_LNTYPE *scl_lntype)
{
	SCL_DO *scl_do;
	SCL_DOTYPE *scl_dotype;
	ST_RET retcode;
	ST_INT rt_num_after_str_start;	/* index after str_start added	*/

	/* Add start of struct for this FC. Remove later if no DA's found.*/
	if (ms_rt_bld_add_str_start (rt_ctxt, FC)!=SD_SUCCESS)
		return (SD_FAILURE);

	/* Save current index. Use later to check if any types added.	*/
	rt_num_after_str_start = rt_ctxt->rt_ctrl->rt_num;  

	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*     so get off list in reverse order.				*/
	for (scl_do = (SCL_DO *) list_find_last ((DBL_LNK *) scl_lntype->doHead);
		scl_do != NULL;
		scl_do = (SCL_DO *) list_find_prev ((DBL_LNK *) scl_lntype->doHead, (DBL_LNK *) scl_do))
	{
		/* Find DOType for this DO.	*/
		scl_dotype = scl_find_dotype (scl_info, scl_do->type);
		if (scl_dotype)	/* found DOType	*/
		{
			retcode = rtadd_do (rt_ctxt, FC, scl_info, scl_do->name, scl_dotype);
			if (retcode != SD_SUCCESS)
			{
				SXLOG_ERR1 ("ERROR adding type definitions for DO='%s'", scl_do->name);
				return (retcode);
			}
		}
		else
		{	/* can't find DOType for this DO. Cannot continue.	*/
			SXLOG_ERR2 ("Cannot find DOType='%s' for DO='%s'.",
				scl_do->type, scl_do->name);
			return (SD_FAILURE);
		}
	}	/* end "for (scl_do...)" loop	*/

	/* Check if any types were added after start of struct	*/
	if (rt_ctxt->rt_ctrl->rt_num > rt_num_after_str_start)
	{			/* types were added, so finish struct now	*/
		if (ms_rt_bld_add_str_end (rt_ctxt) != SD_SUCCESS)
			return (SD_FAILURE);	/* error (already logged)	*/
	}
	else
	{			/* types NOT added so remove start of struct	*/
		ms_rt_bld_remove_last (rt_ctxt);
	}
	return (SD_SUCCESS);		/* this is only "good" return	*/
}
/************************************************************************/
/*			rtadd_rp_or_br					*/
/* RETURNS:	SD_SUCCESS or error code				*/
/* Add runtime type definition for special FC=RP or FC=BR.		*/
/* CRITICAL: Last arg "buffered" must be SD_TRUE or SD_FALSE (other	*/
/*           non-zero values NOT treated the same as SD_TRUE).		*/
/************************************************************************/
static ST_RET rtadd_rp_or_br (
							  RUNTIME_BUILD_CTXT *rt_ctxt,
							  SCL_INFO *scl_info,
							  SCL_LNTYPE *scl_lntype,
							  SCL_LN *scl_ln,
							  ST_BOOLEAN buffered)	/* SD_TRUE to add "buffered" reports	*/
							  /* SD_FALSE to add "unbuffered" reports	*/
							  /* CRITICAL: no other values allowed	*/
{
	SCL_RCB *scl_rcb;
	ST_INT count = 0;
	ST_RET retcode = SD_SUCCESS;
	ST_INT index, maxClient;

	for (scl_rcb = (SCL_RCB *) list_find_last ((DBL_LNK *) scl_ln->rcbHead);
		scl_rcb != NULL;
		scl_rcb = (SCL_RCB *) list_find_prev ((DBL_LNK *) scl_ln->rcbHead, (DBL_LNK *) scl_rcb))
	{
		/* If RCB doesn't match the kind we're looking for, ignore it.	*/
		if (scl_rcb->buffered != buffered)
			continue;

		/* NOTE: if NOT the type we're looking for, never get here (see 'continue' above)*/
		/* NOTE: don't chk every rtadd.. return. If one call fails, subsequent calls fail too.*/
		if (buffered)	/* looking for buffered & this is buffered	*/
		{
			if (count==0)
				ms_rt_bld_add_str_start (rt_ctxt, "BR");
		}
		else		/* looking for unbuffered & this is unbuffered	*/
		{
			if (count==0)
				ms_rt_bld_add_str_start (rt_ctxt, "RP");
		}

		maxClient = scl_rcb->maxClient;	/* use value of "RptEnabled max" in SCL*/

		/* Add type definitions for each RCB in a loop.	*/
		for (index = 1; index<=maxClient; index++)
		{
			ST_CHAR rcb_name [MAX_IDENT_LEN + 1];
			if (strlen (scl_rcb->name) <= MAX_IDENT_LEN - 2)	/* make sure there's room*/
			{
				sprintf (rcb_name, "%s%02d", scl_rcb->name, index);	/* construct RCB name*/
				if (buffered)	/* looking for buffered & this is buffered	*/
					retcode = ms_rt_bld_61850_add_brcb (rt_ctxt, rcb_name);
				else		/* looking for unbuffered & this is unbuffered	*/
					retcode = ms_rt_bld_61850_add_urcb (rt_ctxt, rcb_name);
			}
			else
				retcode = SD_FAILURE;	/* name too long. Should NEVER get this error*/
		}

		if (retcode)		/* if error, stop	*/
			return (retcode);

		count++;	/* increment count of rcb	*/
	}	/* end loop	*/

	/* If any found, add ending text.	*/
	if (count>0)
		retcode = ms_rt_bld_add_str_end (rt_ctxt);

	return (retcode);	/* NOTE: may have returned sooner on some errors*/
}	/* end rtadd_rp_or_br	*/

/************************************************************************/
/*			rtadd_lg					*/
/* RETURNS:	SD_SUCCESS or error code				*/
/* Add runtime type definition for special FC=LG.			*/
/* NOTE: OptFlds in 61850-7-2 not mapped to MMS.			*/
/************************************************************************/
static ST_RET rtadd_lg (
						RUNTIME_BUILD_CTXT *rt_ctxt,
						SCL_INFO *scl_info,
						SCL_LNTYPE *scl_lntype,
						SCL_LN *scl_ln)
{
	SCL_LCB *scl_lcb;
	ST_INT count = 0;
	SCL_DATASET *scl_dataset;
	ST_RET retcode = SD_SUCCESS;

	for (scl_lcb = (SCL_LCB *) list_find_last ((DBL_LNK *) scl_ln->lcbHead);
		scl_lcb != NULL;
		scl_lcb = (SCL_LCB *) list_find_prev ((DBL_LNK *) scl_ln->lcbHead, (DBL_LNK *) scl_lcb))
	{
		scl_dataset = scl_find_dataset (scl_ln, scl_lcb->datSet);
		if (scl_dataset == NULL)
		{
			SXLOG_ERR1 ("rtadd_lg: datSet='%s' not found", scl_lcb->datSet);
			return (SD_FAILURE);
		}

		if (count==0)
			retcode = ms_rt_bld_add_str_start (rt_ctxt, "LG");	/* first one needs (LG)	*/

		if (retcode)		/* if error, stop	*/
			return (retcode);

		/* Add lcb name as component name.*/
		if (ms_rt_bld_61850_add_lcb (rt_ctxt, scl_lcb->name))
			return (SD_FAILURE);	/* error (already logged)	*/

		if (retcode)		/* if error, stop	*/
			return (retcode);

		count++;	/* increment count of lcb	*/
	}	/* end loop	*/

	/* If any found, add ending text.	*/
	if (count>0)
		retcode = ms_rt_bld_add_str_end (rt_ctxt);

	return (retcode);	/* NOTE: may have returned sooner on some errors*/
}	/* end rtadd_lg	*/

/************************************************************************/
/*			rtadd_go_or_gs					*/
/* RETURNS:	SD_SUCCESS or error code				*/
/* Add runtime type definition for special FC=GO or FC=GS.		*/
/************************************************************************/
static ST_RET rtadd_go_or_gs (
							  RUNTIME_BUILD_CTXT *rt_ctxt,
							  SCL_INFO *scl_info,
							  SCL_LNTYPE *scl_lntype,
							  SCL_LN *scl_ln,
							  ST_BOOLEAN isGoose)	/* SD_TRUE to add GOOSE (FC=GO)		*/
							  /* SD_FALSE to add GSSE (FC=GS)		*/
							  /* CRITICAL: no other values allowed	*/
{
	SCL_GCB *scl_gcb;
	ST_INT count = 0;
	SCL_DATASET *scl_dataset;
	ST_RET retcode = SD_SUCCESS;

	for (scl_gcb = (SCL_GCB *) list_find_last ((DBL_LNK *) scl_ln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *) list_find_prev ((DBL_LNK *) scl_ln->gcbHead, (DBL_LNK *) scl_gcb))
	{
		/* If GCB doesn't match the kind we're looking for, ignore it.	*/
		if (scl_gcb->isGoose != isGoose)
			continue;

		/* NOTE: if NOT the type we're looking for, never get here (see 'continue' above)*/
		if (scl_gcb->isGoose)
		{
			/* GOOSE needs dataset. Find it now.	*/
			scl_dataset = scl_find_dataset (scl_ln, scl_gcb->datSet);
			if (scl_dataset == NULL)
			{
				SXLOG_ERR1 ("rtadd_go_or_gs: datSet='%s' not found", scl_gcb->datSet);
				return (SD_FAILURE);
			}

			if (count==0)
				ms_rt_bld_add_str_start (rt_ctxt, "GO");	/* first one needs "GO"	*/
		}
		else
		{
			if (count==0)
				ms_rt_bld_add_str_start (rt_ctxt, "GS");	/* first one needs "GS"	*/
		}

		if (retcode)		/* if error, stop	*/
			return (retcode);

		if (scl_gcb->isGoose)	/* looking for GOOSE & this is GOOSE	*/
			retcode = ms_rt_bld_61850_add_gcb (rt_ctxt, scl_gcb->name);
		else			/* looking for GSSE & this is GSSE	*/
			retcode = ms_rt_bld_61850_add_scb (rt_ctxt, scl_gcb->name);

		if (retcode)		/* if error, stop	*/
			return (retcode);

		count++;	/* increment count of gcb	*/
	}	/* end loop	*/

	/* If any found, add ending text.	*/
	if (count>0)
		retcode = ms_rt_bld_add_str_end (rt_ctxt);

	return (retcode);	/* NOTE: may have returned sooner on some errors*/
}	/* end rtadd_go_or_gs	*/

/************************************************************************/
/*			rtadd_ms_or_us					*/
/* RETURNS:	SD_SUCCESS or error code				*/
/* Add runtime type definition for FC=MS or FC=US.			*/
/* CRITICAL: Last arg "multicast" must be SD_TRUE or SD_FALSE (other	*/
/*           non-zero values NOT treated the same as SD_TRUE).		*/
/************************************************************************/
static ST_RET rtadd_ms_or_us (
							  RUNTIME_BUILD_CTXT *rt_ctxt,
							  SCL_INFO *scl_info,
							  SCL_LNTYPE *scl_lntype,
							  SCL_LN *scl_ln,
							  ST_BOOLEAN multicast)	/* SD_TRUE  to add all MSVCB (FC=MS)	*/
							  /* SD_FALSE to add all USVCB (FC=US)	*/
							  /* CRITICAL: no other values allowed	*/
{
	SCL_SVCB *scl_svcb;
	ST_INT count = 0;
	SCL_DATASET *scl_dataset;
	ST_RET retcode = SD_SUCCESS;

	for (scl_svcb = (SCL_SVCB *) list_find_last ((DBL_LNK *) scl_ln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *) list_find_prev ((DBL_LNK *) scl_ln->svcbHead, (DBL_LNK *) scl_svcb))
	{
		/* If svcb doesn't match the kind we're looking for, ignore it.	*/
		if (scl_svcb->multicast != multicast)
			continue;

		scl_dataset = scl_find_dataset (scl_ln, scl_svcb->datSet);
		if (scl_dataset == NULL)
		{
			SXLOG_ERR1 ("rtadd_ms_or_us: datSet='%s' not found", scl_svcb->datSet);
			return (SD_FAILURE);
		}

		/* NOTE: if NOT the type we're looking for, never get here (see 'continue' above)*/
		/* NOTE: don't chk every rtadd.. return. If one call fails, subsequent calls fail too.*/
		if (multicast)	/* looking for multicast & this is multicast	*/
		{
			if (count==0)
				ms_rt_bld_add_str_start (rt_ctxt, "MS");	/* first one needs (MS)	*/
		}
		else		/* looking for unicast & this is unicast	*/
		{
			if (count==0)
				ms_rt_bld_add_str_start (rt_ctxt, "US");	/* first one needs (US)	*/
		}


		/* NOTE: if NOT the type we're looking for, never get here (see 'continue' above)*/
		if (multicast)	/* looking for multicast & this is multicast	*/
			retcode = ms_rt_bld_61850_add_msvcb (rt_ctxt, scl_svcb->name);
		else		/* looking for unicast & this is unicast	*/
			retcode = ms_rt_bld_61850_add_usvcb (rt_ctxt, scl_svcb->name);

		if (retcode)		/* if error, stop	*/
			return (retcode);

		count++;	/* increment count of svcb	*/
	}	/* end loop	*/

	/* If any found, add ending text.	*/
	if (count>0)
		retcode = ms_rt_bld_add_str_end (rt_ctxt);

	return (retcode);	/* NOTE: may have returned sooner on some errors*/
}	/* end rtadd_ms_or_us	*/

/************************************************************************/
/*			scl2_datatype_create				*/
/* Create MMS Data type for one Logical Node Type (LNodeType)		*/
/* defined in SCL.							*/
/* RETURNS:	type_id (-1 on error)					*/
/************************************************************************/
static ST_INT scl2_datatype_create (
									MVL_VMD_CTRL *vmd_ctrl,	/* VMD in which to add this type	*/
									SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									SCL_LNTYPE *scl_lntype,	/* info for this LNType			*/
									ST_INT max_rt_num,	/* max num of RUNTIME_TYPE for this LNodeType*/
									ST_BOOLEAN use_names,	/* If set, use type names.		*/
									ST_CHAR *name_prefix,	/* unique prefix to add to each type name*/
									/* only used if "use_names==SD_TRUE".	*/
									SCL_LD *scl_ld_special,	/* LD containing LN with "special stuff"*/
									/* (i.e. ReportControl, LogControl, etc)*/
									/* NULL if nothing special in LN.	*/
									SCL_LN *scl_ln_special)	/* LN with "special stuff"		*/
									/* NULL if nothing special in LN.	*/
{
	ST_RET retcode;
	ST_INT type_id = -1;			/* assumes failure.		*/
	RUNTIME_BUILD_CTXT rt_ctxt;
	MVL_TYPE_CTRL *type_ctrl;
	ST_CHAR type_name[MAX_IDENT_LEN+1];

	if (use_names)
	{
		/* Generate type_name.	*/
		if (scl_ln_special)
		{	/* Create unique type name for this LN.	*/
			retcode = special_type_name (name_prefix, scl_ld_special, scl_ln_special, type_name, sizeof(type_name));
		}
		else
			retcode = simple_type_name (name_prefix, scl_lntype, type_name, sizeof(type_name));
		if (retcode)
		{
			SXLOG_ERR1 ("Error generating type name for LNodeType id='%s'", scl_lntype->id);
			return (-1);	/* return type_id of (-1) to indicate error	*/
		}
	}

	/* Begin constructing the data type in rt_ctxt.	*/
	ms_rt_bld_start (&rt_ctxt, max_rt_num);
	/* Allocate extra array of structs. Free this when all SCL processing*/
	/* done (see end of scl2_ld_create_all).				*/
	rt_ctxt.rt_ctrl->reserved_1 = (ST_VOID *) chk_calloc (max_rt_num, sizeof (RESERVED_INFO));	/* array of ptrs*/

	/* Go through all linked lists and create COMPLETE type definition.	*/
	/* NOTE: order of FC specified in 61850-8-1 (section 6.1.3).	*/

	/* NOTE: SCL only allows "ST" "MX" "CO" "SP" "SG" "SE" "SV" "CF" "DC" "EX".*/
	/*       "RP", "LG", and "BR" are special cases.			*/
	do
	{	/* "do-while" loop: only needed so we can break on first error.	*/
		/* if any rtadd_* call fails, break and return error.	*/
		if ((retcode = ms_rt_bld_add_str_start (&rt_ctxt, NULL)) != SD_SUCCESS)	/* no comp name*/
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "MX", scl_info, scl_lntype)) != SD_SUCCESS)  //Add the types for one FC to the RUNTIME_BUILD_CTXT
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "ST", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "CO", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "CF", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "DC", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "SP", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "SG", scl_info, scl_lntype)) != SD_SUCCESS)
			break;

		/* FC=RP is special case. Call special function.	*/
		if (scl_ln_special)
		{		/* special type for LN containing RCBs	*/
			if ((retcode = rtadd_rp_or_br (&rt_ctxt, scl_info, scl_lntype, scl_ln_special, SD_FALSE)) != SD_SUCCESS)
				break;
		}

		/* FC=LG is special case. Call special function.	*/
		if (scl_ln_special)
		{
			if ((retcode = rtadd_lg (&rt_ctxt, scl_info, scl_lntype, scl_ln_special)) != SD_SUCCESS)
				break;
		}

		/* FC=BR is special case. Call special function.	*/
		if (scl_ln_special)
		{		/* special type for LN containing RCBs	*/
			if ((retcode = rtadd_rp_or_br (&rt_ctxt, scl_info, scl_lntype, scl_ln_special, SD_TRUE)) != SD_SUCCESS)
				break;
		}

		if (scl_ln_special)
		{
			/* FC=GO is special case. Call special function (last arg SD_TRUE).	*/
			if ((retcode = rtadd_go_or_gs (&rt_ctxt, scl_info, scl_lntype, scl_ln_special, SD_TRUE)) != SD_SUCCESS)
				break;
			/* FC=GS is special case. Call special function (last arg SD_FALSE).	*/
			if ((retcode = rtadd_go_or_gs (&rt_ctxt, scl_info, scl_lntype, scl_ln_special, SD_FALSE)) != SD_SUCCESS)
				break;
		}

		if ((retcode = rtadd_fc (&rt_ctxt, "SV", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = rtadd_fc (&rt_ctxt, "SE", scl_info, scl_lntype)) != SD_SUCCESS)
			break;

		/* Add types for "MS" and "US" (sampled value control blocks).	*/
		if (scl_ln_special)
		{
			/* FC=MS: This funct with arg = SD_TRUE  adds types for FC=MS.	*/
			if ((retcode = rtadd_ms_or_us (&rt_ctxt, scl_info, scl_lntype, scl_ln_special, SD_TRUE)) != SD_SUCCESS)
				break;
			/* FC=US: This funct with arg = SD_FALSE adds types for FC=US.	*/
			if ((retcode = rtadd_ms_or_us (&rt_ctxt, scl_info, scl_lntype, scl_ln_special, SD_FALSE)) != SD_SUCCESS)
				break;
		}

		if ((retcode = rtadd_fc (&rt_ctxt, "EX", scl_info, scl_lntype)) != SD_SUCCESS)
			break;
		if ((retcode = ms_rt_bld_add_str_end (&rt_ctxt)) != SD_SUCCESS)
			break;
	} while (0);	/* end of "do-while" loop: only needed so we can break on first error.	*/

	/* If retcode==SD_SUCCESS, ALL "rtadd_fc" calls were successful, so create type here	*/
	if (retcode == SD_SUCCESS)
	{
		ms_rt_bld_finish (&rt_ctxt);

		/* Create the type now.	*/
		if (use_names)
			type_id = mvl_vmd_type_id_create (vmd_ctrl, type_name, rt_ctxt.rt_ctrl);
		else
			type_id = mvl_vmd_type_id_create (vmd_ctrl, NULL, rt_ctxt.rt_ctrl);
	}
	else
	{	/* build failed, so cleanup now	*/
		chk_free (rt_ctxt.rt_ctrl->reserved_1);
		ms_rt_bld_cancel (&rt_ctxt);
	}

	if (type_id >= 0)
	{						/* type successfully created	*/
		type_ctrl = mvl_type_ctrl_find (type_id);
		if (mms_debug_sel & MMS_LOG_RT)
		{
			MLOG_ALWAYS1 ("RUNTIME_TYPE definition for LNodeType id='%s':", scl_lntype->id);
			ms_log_runtime (type_ctrl->rt_ctrl->rt_first, type_ctrl->rt_ctrl->rt_num);
		}

		/* CRITICAL: we want the same leaf function for every leaf, so	*/
		/* set leaf functions now in every RUNTIME_TYPE element.		*/
		/* NOTE: leaf functions never used for RT_STR_START, RT_ARR_START,*/
		/*       etc. but they're set anyway because it's easier to set all.*/
		/* NOTE: this function may be customized for each application.	*/
		/*       It should be placed in a "user" module.			*/

		if (u_set_all_leaf_functions (type_ctrl->rt_ctrl) != SD_SUCCESS)
		{
			SXLOG_ERR1 ("Error setting leaf functions for LNodeType id=%s", scl_lntype->id);
			mvl_type_id_destroy (type_id);	/* destroy type just created	*/
			type_id = -1;	/* set invalid type_id to indicate error	*/
		}
	}

	if (type_id < 0)
		SXLOG_ERR1 ("scl2_datatype_create FAILED for LNodeType id=%s", scl_lntype->id);
	else
		SXLOG_FLOW1 ("scl2_datatype_create SUCCESSFUL for LNodeType id=%s", scl_lntype->id);

	return (type_id);
}
/************************************************************************/
/*			find_scl_lntype					*/
/* Search for lntype by name.						*/
/************************************************************************/
SCL_LNTYPE *find_scl_lntype (SCL_INFO *scl_info, ST_CHAR *name)
{
	SCL_LNTYPE *scl_lntype;
	for (scl_lntype = (SCL_LNTYPE *) list_find_last ((DBL_LNK *) scl_info->lnTypeHead);
		scl_lntype != NULL;
		scl_lntype = (SCL_LNTYPE *) list_find_prev ((DBL_LNK *) scl_info->lnTypeHead, (DBL_LNK *) scl_lntype))
	{
		if (strcmp (name, scl_lntype->id) == 0)	/* type name matches*/
			return (scl_lntype);
	}
	return (NULL);	/* lntype not found*/
}
/************************************************************************/
/*			scl2_datatype_create_all			*/
/* Create MMS Data types for all Logical Node Types (LNodeType)		*/
/* defined in SCL.							*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET scl2_datatype_create_all (
								 MVL_VMD_CTRL *vmd_ctrl,	/* VMD in which to add types.		*/
								 SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
								 ST_INT max_rt_num,	/* max num of RUNTIME_TYPE for each LNodeType*/
								 ST_BOOLEAN use_names,	/* if SD_TRUE, generate a name for each type*/
								 ST_CHAR *name_prefix)	/* unique prefix to add to each type name*/
								 /* only used if "use_names==SD_TRUE".	*/
{
	ST_RET retcode;
	SCL_LNTYPE *scl_lntype;
//	SCL_LD *scl_ld;
//	SCL_LN *scl_ln;

	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*     so get off list in reverse order.				*/
	retcode = SD_SUCCESS;

	/* CRITICAL: Don't allow this to be called again for the same SCL_INFO struct.*/
	/* That would cause types to be created twice, and the "type_id" saved*/
	/* in each SCL_LN and SCL_LNTYPE would be overwritten.		*/
	if (scl_info->datatype_create_done)
	{
		SXLOG_ERR0 ("Data types already created for this SCL file. Cannot create again.");
		return (SD_FAILURE);
	}
	else
		scl_info->datatype_create_done = SD_TRUE;	/* Set flag now	*/

	/* Loop through all scl_lntype structs. For each one, create type & save type_id in scl_lntype->type_id.*/
	for (scl_lntype = (SCL_LNTYPE *) list_find_last ((DBL_LNK *) scl_info->lnTypeHead);
		scl_lntype != NULL;
		scl_lntype = (SCL_LNTYPE *) list_find_prev ((DBL_LNK *) scl_info->lnTypeHead, (DBL_LNK *) scl_lntype))
	{
		scl_lntype->type_id = scl2_datatype_create (vmd_ctrl, scl_info, scl_lntype,
			max_rt_num, use_names, name_prefix, NULL, NULL);
		/* NOTE: could fail (type_id < 0). OK for now. Might not be used by any LN.*/
	}

	/* Loop through all Logical Nodes. If a Locical Node
	* contains "special stuff" (i.e. ReportControl, LogControl, GSEControl),
	* create a special type that includes the "special stuff".
	* If not, use the appropriate type created by the above loop (scl_lntype->type_id).
	* Must check all Logical Nodes (scl_ln) in all Logical Devices (scl_ld).
	*/
	//hejian del on 2010-11-5
	//for (scl_ld = (SCL_LD *) list_find_last ((DBL_LNK *) scl_info->ldHead);
	//	scl_ld != NULL;
	//	scl_ld = (SCL_LD *) list_find_prev ((DBL_LNK *) scl_info->ldHead, (DBL_LNK *) scl_ld))
	//{
	//	for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
	//		scl_ln != NULL;
	//		scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
	//	{
	//		scl_lntype = find_scl_lntype (scl_info, scl_ln->lnType);	/* search for lntype by name*/
	//		if (scl_lntype)
	//		{
	//			assert (scl_ln->type_id == 0);	/* already set. Something's wrong*/
	//			/* If rcbHead!=NULL, this LN contains ReportControl.		*/
	//			/* If lcbHead!=NULL, this LN contains LogControl.		*/
	//			/* If gcbHead!=NULL, this LN contains GSEControl.		*/
	//			/* If svcbHead!=NULL, this LN contains SampledValueControl	*/
	//			/* NOTE: do nothing if it fails. Detected later when rcb created.*/
	//			if (scl_ln->rcbHead || scl_ln->lcbHead || scl_ln->gcbHead || scl_ln->svcbHead)
	//			{		/* "Special" LN. Create special type just for this LN.	*/
	//				/* Last 2 args point to LD & LN containing special info (rcb, gcb, etc.).*/
	//				scl_ln->type_id = scl2_datatype_create (vmd_ctrl, scl_info, scl_lntype,
	//					max_rt_num, use_names, name_prefix, scl_ld, scl_ln);
	//			}
	//			else
	//			{          /* "Normal" LN. Save type_id created by first loop.	*/
	//				scl_ln->type_id = scl_lntype->type_id;
	//			}
	//		}
	//		else
	//		{	/* type not found. Set invalid type_id. Error logged below.*/
	//			scl_ln->type_id = -1;
	//		}
	//		if (scl_ln->type_id < 0)
	//		{
	//			SXLOG_ERR2 ("Could not find or create lnType '%s' for LN '%s'",
	//				scl_ln->lnType, scl_ln->varName);
	//			retcode = SD_FAILURE;	/* create failed for this LN, return error.*/
	//			/* NOTE: function fails, but continue looping to log other errors too.*/
	//		}
	//	}
	//}
	if (retcode)
	{
		/* If anything failed, reserved_1 member of every			*/
		/* RUNTIME_CTRL should no longer be needed.				*/
		reserved_free_all (vmd_ctrl);
	}
	return (retcode);
}

/************************************************************************/
/*			scl2_ln_init_lcb_vals				*/
/* Use mvlu_find_comp_type to find the data offset of each LCB in the LN.*/
/* Then write the SCL data there.					*/
/************************************************************************/
static ST_VOID scl2_ln_init_lcb_vals (
									  SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									  SCL_LD *scl_ld,
									  SCL_LN *scl_ln)
{
	ST_CHAR flatname [MAX_IDENT_LEN +1];
	SCL_LCB *scl_lcb;
	MVL61850_LCB_DATA *lcb_data;
	RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
	ST_INT comp_rt_num;		/* num of rt_types in component	*/
	ST_RET retcode = SD_SUCCESS;

	for (scl_lcb = (SCL_LCB *) list_find_last ((DBL_LNK *) scl_ln->lcbHead);
		scl_lcb != NULL;
		scl_lcb = (SCL_LCB *) list_find_prev ((DBL_LNK *) scl_ln->lcbHead, (DBL_LNK *) scl_lcb))
	{
		/* NOTE: mvlu_find_comp_type uses flattened name without LN prefix.	*/
		sprintf (flatname, "LG$%s", scl_lcb->name);
		retcode = mvlu_find_comp_type (scl_ln->mvl_var_assoc->type_id,
			flatname, &comp_rt_type, &comp_rt_num);
		if (retcode!=SD_SUCCESS)
		{
			SXLOG_ERR2 ("Cannot find component '%s' in var '%s'. Initial values not set.",
				flatname, scl_ln->mvl_var_assoc->name);
		}
		else
		{
			lcb_data = (MVL61850_LCB_DATA *)((ST_CHAR *) scl_ln->mvl_var_assoc->data + comp_rt_type->mvluTypeInfo.offSet);
			/* Use SCL info to initialize LCB data.	*/
			/* Construct ObjectReference for lcb_data->DatSet.	*/
			scl_make_objref (scl_ld, scl_ln, scl_lcb->datSet,
				lcb_data->DatSet, sizeof (lcb_data->DatSet) - 1);
			lcb_data->IntgPd = (ST_UINT32) scl_lcb->intgPd;
			/* Construct ObjectReference for lcb_data->LogRef.	*/
			scl_make_objref2 (scl_ld, scl_lcb->logName,
				lcb_data->LogRef, sizeof (lcb_data->LogRef) - 1);
			lcb_data->LogEna = scl_lcb->logEna;
			/* NOTE: "scl_lcb->reasonCode" may be read from SCL file, but it	*/
			/* is not in LCB (according to 61850-8-1) so just ignore it.	*/
			lcb_data->TrgOps.len = 6;		/* Var len 6-bit bitstring	*/
			lcb_data->TrgOps.data[0] = scl_lcb->TrgOps[0];	/* 1 byte of data	*/
		}
	}	/* end loop	*/
}
/************************************************************************/
/*			scl2_ln_init_gcb_vals				*/
/* Use mvlu_find_comp_type to find the data offset of each GCB in the LN.*/
/* Then write the SCL data there.					*/
/************************************************************************/
static ST_VOID scl2_ln_init_gcb_vals (
									  SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									  SCL_LD *scl_ld,
									  SCL_LN *scl_ln)
{
	ST_INT i = 0;
	ST_CHAR flatname [MAX_IDENT_LEN +1];
	SCL_GCB *scl_gcb;
	MVL61850_GCB_DATA *gcb_data;	/* GOOSE Control Block data	*/
	MVL61850_SCB_DATA *scb_data;	/* GSSE Control Block data	*/
	RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
	ST_INT comp_rt_num;		/* num of rt_types in component	*/
	ST_RET retcode = SD_SUCCESS;
	ST_CHAR *dataptr;
	SCL_GSE *scl_gse;	/* GOOSE addressing info	 hhzhen 0112 */

	for (scl_gcb = (SCL_GCB *) list_find_last ((DBL_LNK *) scl_ln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *) list_find_prev ((DBL_LNK *) scl_ln->gcbHead, (DBL_LNK *) scl_gcb))
	{
		/* NOTE: mvlu_find_comp_type uses flattened name without LN prefix.	*/
		if (scl_gcb->isGoose)	/* GOOSE	*/
			sprintf (flatname, "GO$%s", scl_gcb->name);
		else			/* GSSE		*/
			sprintf (flatname, "GS$%s", scl_gcb->name);
		retcode = mvlu_find_comp_type (scl_ln->mvl_var_assoc->type_id,
			flatname, &comp_rt_type, &comp_rt_num);
		if (retcode!=SD_SUCCESS)
		{
			SXLOG_ERR2 ("Cannot find component '%s' in var '%s'. Initial values not set.",
				flatname, scl_ln->mvl_var_assoc->name);
		}
		else
		{
			dataptr = (ST_CHAR *) scl_ln->mvl_var_assoc->data
				+ comp_rt_type->mvluTypeInfo.offSet;
			/* Use SCL info to initialize GCB data.	*/
			if (scl_gcb->isGoose)
			{			/* GOOSE	*/
				gcb_data = (MVL61850_GCB_DATA *) dataptr;
				/* Construct ObjectReference for gcb_data->DatSet.	*/
				scl_make_objref (scl_ld, scl_ln, scl_gcb->datSet,
					gcb_data->DatSet, sizeof (gcb_data->DatSet) - 1);
				gcb_data->ConfRev = (ST_UINT32) scl_gcb->confRev;
				/* 61850-8-1 maps appID to GoID	*/
				strcpy (gcb_data->GoID, scl_gcb->appID);
				// HHZHEN ADD 0112
				if ((scl_gse = scl_gse_find (scl_info, scl_ld, scl_gcb)) == NULL)
				{
					//hejian del on 2010-11-5
//					SLOGALWAYS3 ("ERROR: unable to find addressing information for GSEControl '%s' in ldInst '%s' in IED '%s'",
//						scl_gcb->name, scl_ld->inst, scl_info->iedName);
					return ;
				}
				memcpy (gcb_data->DstAddress.Addr, scl_gse->MAC, sizeof(scl_gse->MAC)); 

				//hejian alter on 2010-9-4
				memcpy(gcb_data->DstAddress.APPID, scl_gse->APPID, 5);
				gcb_data->DstAddress.PRIORITY = scl_gse->VLANPRI;
				//if(scl_gse->)
				gcb_data->DstAddress.VID = 0; //SCL_GSE 结构里边无该数值

				//HHZHEN ADD 0112
			}
			else
			{			/* GSSE		*/
				scb_data = (MVL61850_SCB_DATA *) dataptr;
				/* datSet, confRev ignored for GSSE.	*/
				/* 61850-8-1 maps appID to GsID	*/
				strcpy (scb_data->GsID, scl_gcb->appID);
			}
		}
	}	/* end loop	*/
}
/************************************************************************/
/*			scl2_ln_init_svcb_vals				*/
/* Use mvlu_find_comp_type to find the data offset of each SVCB in the LN.*/
/* Then write the SCL data there.					*/
/************************************************************************/
static ST_VOID scl2_ln_init_svcb_vals (
									   SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									   SCL_LD *scl_ld,
									   SCL_LN *scl_ln)
{
	ST_CHAR flatname [MAX_IDENT_LEN +1];
	SCL_SVCB *scl_svcb;
	RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
	ST_INT comp_rt_num;		/* num of rt_types in component	*/
	ST_RET retcode = SD_SUCCESS;
	ST_CHAR *dataptr;

	for (scl_svcb = (SCL_SVCB *) list_find_last ((DBL_LNK *) scl_ln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *) list_find_prev ((DBL_LNK *) scl_ln->svcbHead, (DBL_LNK *) scl_svcb))
	{
		/* NOTE: mvlu_find_comp_type uses flattened name without LN prefix.	*/
		if (scl_svcb->multicast)
			sprintf (flatname, "MS$%s", scl_svcb->name);
		else
			sprintf (flatname, "US$%s", scl_svcb->name);
		retcode = mvlu_find_comp_type (scl_ln->mvl_var_assoc->type_id,
			flatname, &comp_rt_type, &comp_rt_num);
		if (retcode!=SD_SUCCESS)
		{
			SXLOG_ERR2 ("Cannot find component '%s' in var '%s'. Initial values not set.",
				flatname, scl_ln->mvl_var_assoc->name);
		}
		else
		{
			dataptr = (ST_CHAR *) scl_ln->mvl_var_assoc->data
				+ comp_rt_type->mvluTypeInfo.offSet;
			/* Use SCL info to initialize SVCB data.	*/
			if (scl_svcb->multicast)
			{			/* MSVCB	*/
				MVL61850_MSVCB_DATA *msvcb_data = (MVL61850_MSVCB_DATA *) dataptr;
				msvcb_data->SvEna = SD_FALSE;	/* can't be configured. Init to FALSE*/
				strcpy (msvcb_data->MsvID, scl_svcb->smvID);
				/* Construct ObjectReference to initialize msvcb_data->DatSet.	*/
				scl_make_objref (scl_ld, scl_ln, scl_svcb->datSet,
					msvcb_data->DatSet, sizeof (msvcb_data->DatSet) - 1);
				msvcb_data->ConfRev =  scl_svcb->confRev;
				msvcb_data->SmpRate =  scl_svcb->smpRate;
				msvcb_data->OptFlds.len = 3;	/* Var len 3-bit bitstring	*/
				msvcb_data->OptFlds.data[0] = scl_svcb->OptFlds[0];	/* 1 byte of data*/
			}
			else
			{			/* USVCB	*/
				MVL61850_USVCB_DATA *usvcb_data = (MVL61850_USVCB_DATA *) dataptr;
				usvcb_data->SvEna = SD_FALSE;	/* can't be configured. Init to FALSE*/
				usvcb_data->Resv = SD_FALSE;	/* can't be configured. Init to FALSE*/
				strcpy (usvcb_data->UsvID, scl_svcb->smvID);
				/* Construct ObjectReference to initialize usvcb_data->DatSet.	*/
				scl_make_objref (scl_ld, scl_ln, scl_svcb->datSet,
					usvcb_data->DatSet, sizeof (usvcb_data->DatSet) - 1);
				usvcb_data->ConfRev =  scl_svcb->confRev;
				usvcb_data->SmpRate =  scl_svcb->smpRate;
				usvcb_data->OptFlds.len = 3;	/* Var len 3-bit bitstring	*/
				usvcb_data->OptFlds.data[0] = scl_svcb->OptFlds[0];	/* 1 byte of data*/
			}
		}
	}	/* end loop	*/
}
/************************************************************************/
/*			scl2_ln_create			*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_ln_create (
							  MVL_VMD_CTRL *vmd_ctrl,
							  SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
							  SCL_LD *scl_ld,
							  SCL_LN *scl_ln)
{
	ST_INT type_id;
	MVL_VAR_ASSOC *var_assoc;
	OBJECT_NAME object_name;
	ST_VOID *data;		/* buffer to store logical node data. Allocated here.*/
	MVL_TYPE_CTRL *type_ctrl;
	ST_RET retcode;

	retcode = SD_FAILURE;	/* assume failure	*/

	type_id = scl_ln->type_id;
	if (type_id < 0)
		SXLOG_ERR2 ("Cannot find type='%s' for logical node='%s'", scl_ln->lnType, scl_ln->varName);
	else
	{
		/* CRITICAL: alloc buffer to store "data". All data for this LN stored here.*/
		/* This data buffer constitutes the "Data Cache" described in Design Doc.	*/
		/* NOTE: type_ctrl->data_size==type_ctrl->rt_ctrl->rt_first->offset_to_last*/
		type_ctrl = mvl_type_ctrl_find (type_id);
		data = chk_calloc (1, type_ctrl->data_size);

		/* Construct object name from LD & LN info.		*/
		object_name.object_tag = DOM_SPEC;	/* ALWAYS Domain specific	*/
		object_name.domain_id = scl_ld->domName;
		object_name.obj_name.vmd_spec = scl_ln->varName;

		/* Create the MMS variable (Logical Node).	*/
		var_assoc = mvl_vmd_var_add (vmd_ctrl, &object_name,
			NULL,	/* MVL_NET_INFO *	*/
			type_id,
			data,
			NULL,	/* MVL_VAR_PROC *	*/
			SD_TRUE);	/* ALWAYS copy name to var_assoc	*/
		if (var_assoc == NULL)
			SXLOG_ERR2 ("Cannot create LN='%s' in LD='%s'", scl_ln->varName, scl_ld->domName);
		else
		{
			var_assoc->flags = MVL_VAR_FLAG_UCA;	/* CRITICAL: must make it a UCA variable*/
			/* NOTE: var_assoc->use_static_data flag is automatically set	*/
			/*       by mvl_vmd_var_add because data is never NULL.		*/
			scl_ln->mvl_var_assoc = var_assoc;	/* save var_assoc for later*/
			retcode = SD_SUCCESS;
		}
	}
	if (retcode == SD_SUCCESS)
	{
		/* Set initial vals for LCB, GCB, & SCB (i.e. GSSE control block).	*/
		scl2_ln_init_lcb_vals (scl_info, scl_ld, scl_ln);
		scl2_ln_init_gcb_vals (scl_info, scl_ld, scl_ln);
		scl2_ln_init_svcb_vals (scl_info, scl_ld, scl_ln);
	}
	return (retcode);
}
/************************************************************************/
/*			scl2_dataset_create				*/
/* Create one DataSet (SCL_DATASET) for this Logical Node (SCL_LN).	*/
/* A DataSet maps to a MMS NamedVariableList (NVL).			*/
/* The MMS NVL name follows the form "LogicalNodeName$DataSetName".	*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_dataset_create (
								   MVL_VMD_CTRL *vmd_ctrl,
								   SCL_LD *scl_ld,
								   SCL_LN *scl_ln,
								   SCL_DATASET *scl_dataset)
{
	OBJECT_NAME nvl_obj;
	MVL_NVLIST_CTRL *nvlist_ctrl;
	ST_INT num_var = 0;
	OBJECT_NAME *var_obj;	/* array of var names	*/
	SCL_FCDA *scl_fcda;
	ST_RET ret;
	/* allow extra char in var_name so strncat can go beyond limit. If it does, return error.*/
	ST_CHAR *var_name_buf;	/* one buf allocated to hold all var names	*/
	ST_CHAR *var_name;	/* ptr to current name being constructed	*/
	ST_CHAR *dot_ptr;			/* ptr to '.' within var_name	*/
	ST_CHAR nvl_name [MAX_IDENT_LEN+1];	/* one extra byte for NULL	*/

	ret = SD_SUCCESS;	/* assume success	*/

	/* Construct NVL object name from LD, LN, and DataSet info.		*/
	if (strlen (scl_ln->prefix) + strlen (scl_ln->lnClass) + strlen (scl_ln->inst)
		+ strlen (scl_dataset->name) + 1 > MAX_IDENT_LEN)
	{
		SXLOG_ERR1 ("Constructed NVL name would be too long for dataset '%s'.", scl_dataset->name);
		return (SD_FAILURE);
	}
	sprintf (nvl_name, "%s%s%s$%s", scl_ln->prefix, scl_ln->lnClass, scl_ln->inst, scl_dataset->name);
	nvl_obj.object_tag = DOM_SPEC;	/* ALWAYS Domain specific	*/
	nvl_obj.domain_id = scl_ld->domName;
	nvl_obj.obj_name.vmd_spec = nvl_name;	/* use constructed NVL name	*/

	/* Go through list once just to count number of variables.		*/
	for (scl_fcda = (SCL_FCDA *) list_find_last ((DBL_LNK *) scl_dataset->fcdaHead);
		scl_fcda != NULL;
		scl_fcda = (SCL_FCDA *) list_find_prev ((DBL_LNK *) scl_dataset->fcdaHead, (DBL_LNK *) scl_fcda))
	{
		num_var++;
	}
	/* Allocate var_obj array.	*/
	var_obj = chk_calloc (num_var, sizeof (OBJECT_NAME));

	/* NOTE: this is a bit tricky. OBJECT_NAME struct contains only a ptr
	*     to name, no storage. Need to allocate storage for names. Here we
	*     allocate one big buffer for all names. In the loop below,
	*     we use part of this buffer for each name.
	*/
	var_name_buf = chk_calloc (num_var, MAX_IDENT_LEN+2);	/* Note +2 for NULL plus extra char*/

	/* Go through list again to fill in var_obj array.	*/
	num_var = 0;
	for (scl_fcda = (SCL_FCDA *) list_find_last ((DBL_LNK *) scl_dataset->fcdaHead);
		scl_fcda != NULL;
		scl_fcda = (SCL_FCDA *) list_find_prev ((DBL_LNK *) scl_dataset->fcdaHead, (DBL_LNK *) scl_fcda))
	{
		/* Set "var_name" pointing to proper section of big buffer.	*/
		var_name = var_name_buf + num_var*(MAX_IDENT_LEN+2);
		/* Fill in "var_name".	*/
		strncpy (var_name, scl_fcda->prefix, MAX_IDENT_LEN+1);
		strncat (var_name, scl_fcda->lnClass, MAX_IDENT_LEN+1-strlen(var_name));
		strncat (var_name, scl_fcda->lnInst,  MAX_IDENT_LEN+1-strlen(var_name));
		strncat (var_name, "$",               MAX_IDENT_LEN+1-strlen(var_name));
		strncat (var_name, scl_fcda->fc,      MAX_IDENT_LEN+1-strlen(var_name));
		if (strlen (scl_fcda->doName))
		{
			strncat (var_name, "$",              MAX_IDENT_LEN+1-strlen(var_name));
			strncat (var_name, scl_fcda->doName, MAX_IDENT_LEN+1-strlen(var_name));
		}
		if (strlen (scl_fcda->daName))
		{
			strncat (var_name, "$",              MAX_IDENT_LEN+1-strlen(var_name));
			strncat (var_name, scl_fcda->daName, MAX_IDENT_LEN+1-strlen(var_name));
		}
		/* doName or daName may contain '.'. Each '.' must be replaced with '$'.*/
		dot_ptr = var_name;
		while ((dot_ptr = strchr (dot_ptr, '.')) != NULL)
			*dot_ptr++ = '$';
		if (strlen (var_name) > MAX_IDENT_LEN)
		{
			SXLOG_ERR1 ("Variable name generated from FCDA info too long '%s'", var_name);
			ret = SD_FAILURE;
			break;	/* stop looping	*/
		}

		/* var_name generated, now fill in this "var_obj".	*/
		var_obj[num_var].object_tag = DOM_SPEC;	/* ALWAYS Domain specific	*/
		var_obj[num_var].domain_id = scl_fcda->domName;
		var_obj[num_var].obj_name.vmd_spec = var_name;
		num_var++;
	}

	if (ret == SD_SUCCESS)
	{
		nvlist_ctrl = mvl_vmd_nvl_add (vmd_ctrl, &nvl_obj, NULL, num_var, var_obj, SD_TRUE);
		if (nvlist_ctrl)
			ret = SD_SUCCESS;
		else
			ret = SD_FAILURE;
	}
	/* NOTE: can free these now because mvl_vmd_nvl_add copied this info.*/
	chk_free (var_obj);
	chk_free (var_name_buf);
	return (ret);
}
/************************************************************************/
/*			scl2_dataset_create_all				*/
/* Create all DataSets (SCL_DATASET) for this Logical Node (SCL_LN).	*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_dataset_create_all (
									   MVL_VMD_CTRL *vmd_ctrl,
									   SCL_LD *scl_ld,
									   SCL_LN *scl_ln)
{
	SCL_DATASET *scl_dataset;
	ST_RET ret;

	ret = SD_SUCCESS;	/* assume success	*/

	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*       so get off list in reverse order.				*/
	for (scl_dataset = (SCL_DATASET *) list_find_last ((DBL_LNK *) scl_ln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *) list_find_prev ((DBL_LNK *) scl_ln->datasetHead, (DBL_LNK *) scl_dataset))
	{
		ST_UINT32 mvl_debug_sel_save;

		mvl_debug_sel_save = mvl_debug_sel;
		mvl_debug_sel &= ~MVLLOG_NERR;
		ret = scl2_dataset_create (vmd_ctrl, scl_ld, scl_ln, scl_dataset);
		mvl_debug_sel = mvl_debug_sel_save;
		if (ret)
		{
			//hejian alter on 2010-4-7
			if (!scl_debug_mode)
				//  break;	/* if one fails, stop processing	*/

				++scl_debug_mode_error_count;
		}
		else
		{
			SXLOG_FLOW3 ("scl2_dataset_create DONE for '%s' (LD=%s LN=%s)",
				scl_dataset->name, scl_ld->domName, scl_ln->varName);
		}
	}
	return (ret);
}
/************************************************************************/
/*			init_basrcb_data				*/
/* Use other info in scl_rcb to initialize data in basrcb.		*/
/************************************************************************/
static ST_VOID init_basrcb_data (
								 MVLU_RPT_CTRL *rpt_ctrl,
								 SCL_RCB *scl_rcb)
{
	MVLU_BASRCB *basrcb;

	basrcb = &rpt_ctrl->only_client.basrcb;

	/* If RptID configured in SCL, overwrite default RptID generated by mvlu_create_rpt_ctrl	*/
	if (strlen (scl_rcb->rptID))
		strncpy_safe (basrcb->RptID, scl_rcb->rptID, sizeof (basrcb->RptID)-1);
	/* Use other info in scl_rcb to initialize data in basrcb		*/
	/* NOTE: scl_rcb->name, scl_rcb->desc not used.			*/
	basrcb->IntgPd = scl_rcb->intgPd;
	basrcb->BufTim = scl_rcb->bufTime;

	basrcb->TrgOps.len = 6;	/* BVstring. Assume max len*/
	basrcb->TrgOps.data [0] = scl_rcb->TrgOps [0];

	basrcb->OptFlds.data_1 [0] = scl_rcb->OptFlds [0];
	basrcb->OptFlds.data_1 [1] = scl_rcb->OptFlds [1];
	if (!scl_rcb->buffered)
	{	/* For URCB, 61850-8-1 says to ignore buffer-overflow, entryID bits, so clear them*/
		BSTR_BIT_SET_OFF (basrcb->OptFlds.data_1, OPTFLD_BITNUM_BUFOVFL);
		BSTR_BIT_SET_OFF (basrcb->OptFlds.data_1, OPTFLD_BITNUM_ENTRYID);
	}
}
/************************************************************************/
/*			init_rpt_ctrl					*/
/* Used only by loop in "scl2_rcb_create".				*/
/************************************************************************/
ST_RET init_rpt_ctrl (
					  SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
					  SCL_RCB *scl_rcb,
					  MVL_NVLIST_CTRL *nvl,
					  MVL_VAR_ASSOC *base_va,
					  ST_CHAR *basrcb_var_namexx,
					  ST_CHAR *basrcb_type_namexx,
					  ST_UINT reportScanRate)	/* report scan rate (millisec)	*/
{
	ST_INT buftim_action;
	ST_INT set_flags;	/* flags for mvlu_set_leaf_param_name	*/
	ST_RET ret;
	ST_CHAR leaf_name [MAX_IDENT_LEN + 1];
	MVLU_RPT_CTRL *rpt_ctrl;

	/* DEBUG: nothing in SCL to set buftim_action. Is there another way to get this info?	*/
	buftim_action = MVLU_RPT_BUFTIM_SEND_NOW;

	/* Set all leaf functions required to implement RCB.
	* NOTE: these leaf functions replace the default leaf functions
	*       set by "u_set_all_leaf_functions" when the datatype was created.
	*/

	/* Use same flags for all leafs	*/
	set_flags = MVLU_SET_RD_FUN | MVLU_SET_WR_FUN | MVLU_SET_REF;

	/* Start with good return value & OR all returns together. If ANY call
	* to mvlu_set_leaf_param_name fails, this function will fail.
	*/
	ret = SD_SUCCESS;
	/* CRITICAL: len of basrcb_type_name chked above, so none of these "sprintf"s
	* will cause leaf_name to be exceeded.
	*/
	sprintf (leaf_name, "%s$RptID", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_rptid_rd_ind_fun",
		"mvlu_rptid_wr_ind_fun",
		"");
	sprintf (leaf_name, "%s$RptEna", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_rptena_rd_ind_fun",
		"mvlu_rptena_wr_ind_fun",
		"");
	if (!scl_rcb->buffered)	/* "Resv" only for Unbuffered	*/
	{
		sprintf (leaf_name, "%s$Resv", basrcb_type_namexx);
		ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
			leaf_name,
			"mvlu_resv_rd_ind_fun",
			"mvlu_resv_wr_ind_fun",
			"");
	}
	sprintf (leaf_name, "%s$DatSet", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_datsetna_rd_ind_fun",
		"mvl61850_datset_wr_ind",
		"");
	sprintf (leaf_name, "%s$ConfRev", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_confrev_rd_ind",
		"u_no_write_allowed",		/* NOT writable	*/
		"");
	sprintf (leaf_name, "%s$OptFlds", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_optflds_rd_ind_fun",
		"mvlu_optflds_wr_ind_fun",
		"");
	sprintf (leaf_name, "%s$BufTm", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_buftim_rd_ind_fun",
		"mvlu_buftim_wr_ind_fun",
		"");
	sprintf (leaf_name, "%s$SqNum", basrcb_type_namexx);
	if (scl_rcb->buffered)
	{	/* Buffered uses INT16U for SqNum	*/
		ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
			leaf_name,
			"mvlu_sqnum_int16u_rd_ind_fun",
			"u_no_write_allowed",
			"");
	}
	else
	{	/* Unbuffered uses INT8U for SqNum	*/
		ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
			leaf_name,
			"mvlu_sqnum_rd_ind_fun",
			"u_no_write_allowed",
			"");
	}
	sprintf (leaf_name, "%s$TrgOps", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_trgops_rd_ind_fun",
		"mvlu_trgops_wr_ind_fun",
		"");
	sprintf (leaf_name, "%s$IntgPd", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_intgpd_rd_ind_fun",
		"mvlu_intgpd_wr_ind_fun",
		"");
	sprintf (leaf_name, "%s$GI", basrcb_type_namexx);
	ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
		leaf_name,
		"mvlu_gi_rd_ind",
		"mvlu_gi_wr_ind",
		"");
	if (scl_rcb->buffered)	/* only for Buffered	*/
	{
		sprintf (leaf_name, "%s$PurgeBuf", basrcb_type_namexx);
		ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
			leaf_name,
			"mvlu_purgebuf_rd_ind",
			"mvlu_purgebuf_wr_ind",
			"");
		sprintf (leaf_name, "%s$EntryID", basrcb_type_namexx);
		ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
			leaf_name,
			"mvlu_entryid_rd_ind",
			"mvlu_entryid_wr_ind",
			"");
		sprintf (leaf_name, "%s$TimeofEntry", basrcb_type_namexx);
		ret |= mvlu_set_leaf_param_name2 (base_va->type_id, set_flags,
			leaf_name,
			"mvlu_timeofentry_rd_ind",
			"u_no_write_allowed",		/* NOT writable	*/
			"");
	}	/* only for Buffered	*/

	if (ret)
	{
		SXLOG_ERR1 ("At least one leaf function could not be found for RCB '%s'", basrcb_var_namexx);
		if (scl_debug_mode)
		{
			++scl_debug_mode_error_count;
			return (SD_SUCCESS);	/* Don't let this stop us for now ...	*/
		}
		return (ret);
	}

	/* NOTE: nvl may be NULL. If so, it must be set later when client writes DatSet.*/
	rpt_ctrl = mvl61850_create_rpt_ctrl (basrcb_var_namexx, nvl,
		base_va,
		(scl_rcb->buffered ? RCB_TYPE_IEC_BRCB : RCB_TYPE_IEC_URCB),
		buftim_action,
		scl_info->brcb_bufsize,	/* BRCB bufsize	*/
		scl_rcb->confRev);	/* ConfRev	*/
	if (rpt_ctrl)
	{
		init_basrcb_data (rpt_ctrl, scl_rcb);	/* use scl_rcb to init data*/
		rpt_ctrl->scan_rate = (ST_DOUBLE) reportScanRate;	/* init scan rate*/
		ret = SD_SUCCESS;
	}
	else
		ret = SD_FAILURE;
	return (ret);
}
/************************************************************************/
/*			scl2_rcb_create					*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_rcb_create (
							   MVL_VMD_CTRL *vmd_ctrl,
							   SCL_INFO *scl_info,
							   SCL_LD *scl_ld,
							   SCL_LN *scl_ln,
							   SCL_RCB *scl_rcb,
							   ST_UINT reportScanRate)	/* report scan rate (millisec)	*/
{
	ST_RET ret;
	ST_CHAR basrcb_var_name [MAX_IDENT_LEN + 1];
	ST_CHAR basrcb_type_name [MAX_IDENT_LEN + 1];	/* for setting leaf functions*/
	ST_CHAR basrcb_var_namexx [MAX_IDENT_LEN + 1];	/* name plus 2 char index*/
	ST_CHAR basrcb_type_namexx [MAX_IDENT_LEN + 1];	/* name plus 2 char index*/
	MVL_VAR_ASSOC *base_va;
	OBJECT_NAME base_var_oname;
	OBJECT_NAME nvl_oname;
	MVL_NVLIST_CTRL *nvl;
	SCL_DATASET *scl_dataset;
	ST_CHAR nvl_name [MAX_IDENT_LEN+1];
	ST_INT index, maxClient;

	/* Initialize basrcb_type_name. Add $BR.. or $RP.. later.	*/
	/* First part of name shouldn't matter now that init_rpt_ctrl uses	*/
	/* mvlu_set_leaf_param_name2 to set leaf params. Use simple name.	*/
	strcpy (basrcb_type_name, "b");

	/* Generate basrcb_var_name from SCL info. The code below should generate a unique
	* basrcb_var_name for every RCB in this LN.
	*/
	strcpy (basrcb_var_name, scl_ln->varName);	/* never too long	*/
	if (scl_rcb->buffered)
	{
		strncat_safe (basrcb_var_name,  "$BR$", MAX_IDENT_LEN-strlen(basrcb_var_name));
		strncat_safe (basrcb_type_name, "$BR$", MAX_IDENT_LEN-strlen(basrcb_type_name));
	}
	else
	{
		strncat_safe (basrcb_var_name,  "$RP$", MAX_IDENT_LEN-strlen(basrcb_var_name));
		strncat_safe (basrcb_type_name, "$RP$", MAX_IDENT_LEN-strlen(basrcb_type_name));
	}
	/* Add RCB name (read from SCL file).	*/
	strncat_safe (basrcb_var_name,  scl_rcb->name, MAX_IDENT_LEN-strlen(basrcb_var_name));
	strncat_safe (basrcb_type_name, scl_rcb->name, MAX_IDENT_LEN-strlen(basrcb_type_name));

	/* Make sure there's room for 2 char "index" plus longest suffix	*/
	if (strlen (basrcb_var_name) + 2 + sizeof("$TimeOfEntry") > MAX_IDENT_LEN)
	{
		SXLOG_ERR1 ("BasRCB variable name '%s' too long", basrcb_var_name);
		return (SD_FAILURE);
	}
	if (strlen (basrcb_type_name) + 2 + sizeof("$TimeOfEntry") > MAX_IDENT_LEN)
	{
		SXLOG_ERR1 ("BasRCB type name '%s' too long", basrcb_type_name);
		return (SD_FAILURE);
	}

	/* If "datSet" is not NULL, try to find it.	*/
	if (scl_rcb->datSet[0] != '\0')
	{
		scl_dataset = scl_find_dataset (scl_ln, scl_rcb->datSet);
		if (scl_dataset == NULL)
		{
			SXLOG_ERR1 ("scl2_rcb_create: datSet='%s' not found", scl_rcb->datSet);
			return (SD_FAILURE);
		}
		/* Construct NVL object name from LD, LN, and DataSet info.		*/
		if (strlen (scl_ln->prefix) + strlen (scl_ln->lnClass) + strlen (scl_ln->inst)
			+ strlen (scl_rcb->datSet) + 1 > MAX_IDENT_LEN)
		{
			SXLOG_ERR1 ("Constructed NVL name would be too long for dataset '%s'.", scl_rcb->datSet);
			return (SD_FAILURE);
		}
		sprintf (nvl_name, "%s%s%s$%s", scl_ln->prefix, scl_ln->lnClass, scl_ln->inst, scl_rcb->datSet);
		nvl_oname.object_tag = DOM_SPEC;
		nvl_oname.domain_id = scl_ld->domName;	/* domain name	*/
		nvl_oname.obj_name.item_id = nvl_name;	/* use constructed NVL name	*/
		nvl = mvl_vmd_find_nvl (vmd_ctrl, &nvl_oname,
			NULL);	/* DOM_SPEC so net_info doesn't matter*/
		if (nvl == NULL)
		{
			SXLOG_ERR3 ("Cannot find NVL '%s' in domain '%s' to create RCB '%s'",
				nvl_oname.obj_name.item_id,
				nvl_oname.domain_id,
				basrcb_var_name);
			return (SD_FAILURE);
		}
	}
	else
		nvl = NULL;	/* datSet="" so can't find NVL	*/

	/* Find the "base_va". Needed as arg to mvlu_create_rpt_ctrl.	*/
	base_var_oname.object_tag = DOM_SPEC;
	base_var_oname.domain_id = scl_ld->domName;

	base_var_oname.obj_name.item_id = scl_ln->varName;
	base_va = mvl_vmd_find_var (vmd_ctrl, &base_var_oname,
		NULL);	/* DOM_SPEC so net_info doesn't matter*/
	if (base_va == NULL)
	{
		SXLOG_ERR1 ("Cannot find base variable='%s' for RCB", scl_ln->varName);
		return (SD_FAILURE);
	}

	assert (scl_rcb->maxClient > 0 && scl_rcb->maxClient <= 99);	/* was checked during parsing	*/

	maxClient = scl_rcb->maxClient;	/* use value of "RptEnabled max" in SCL*/

	/* Create "maxClient" RCBs, each with "index" as a suffix.	*/
	for (index = 1; index <= maxClient; index++)
	{
		/* Add "index" suffix to var and type name.	*/
		sprintf (basrcb_var_namexx, "%s%02d", basrcb_var_name, index);
		sprintf (basrcb_type_namexx, "%s%02d", basrcb_type_name, index);

		ret = init_rpt_ctrl (scl_info, scl_rcb, nvl, base_va,
			basrcb_var_namexx, basrcb_type_namexx, reportScanRate);
		if (ret)
			break;	/* stop looping on any error.	*/
	}	/* end of loop	*/
	return (ret);
}
/************************************************************************/
/*			scl2_rcb_create_all			*/
/* Create all Report Control Blocks (SCL_RCB) for this Logical Node (SCL_LN).*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_rcb_create_all (
								   MVL_VMD_CTRL *vmd_ctrl,
								   SCL_INFO *scl_info,
								   SCL_LD *scl_ld,
								   SCL_LN *scl_ln,
								   ST_UINT reportScanRate)	/* report scan rate (millisec)	*/
{
	SCL_RCB *scl_rcb;
	ST_RET ret;

	ret = SD_SUCCESS;	/* assume success	*/

	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*       so get off list in reverse order.				*/
	for (scl_rcb = (SCL_RCB *) list_find_last ((DBL_LNK *) scl_ln->rcbHead);
		scl_rcb != NULL;
		scl_rcb = (SCL_RCB *) list_find_prev ((DBL_LNK *) scl_ln->rcbHead, (DBL_LNK *) scl_rcb))
	{
		ret = scl2_rcb_create (vmd_ctrl, scl_info, scl_ld, scl_ln, scl_rcb,
			reportScanRate);
		if (ret)
			break;	/* if one fails, stop processing	*/
		else
			SXLOG_FLOW3 ("scl2_rcb_create DONE for '%s' (LD=%s LN=%s)",
			scl_rcb->name, scl_ld->domName, scl_ln->varName);
	}
	return (ret);
}
/************************************************************************/
/*			convert_initial_value				*/
/* NOTE: This function does special conversion for "Enum" and "Boolean"	*/
/*       values. For all other types, it just calls sxaTextToLocal.	*/
/************************************************************************/
ST_RET convert_initial_value (SCL_INFO *scl_info,
							  SCL_LD *scl_ld,
							  SCL_LN *scl_ln,
							  ST_CHAR *flattened_name,	/* flattened variable name	*/
							  RUNTIME_CTRL *rt_ctrl,
							  ST_INT comp_rt_index,	/* index to this comp in array	*/
							  ST_VOID *data,		/* Pointer to converted data	*/
							  ST_CHAR *valstring)	/* string to be converted.	*/
{
	ST_RET ret = SD_SUCCESS;
	RUNTIME_TYPE *comp_rt_type;
	SCL_ENUMTYPE *scl_enumtype;
	RESERVED_INFO *reserved_info;	/* ptr to array of extra type info.	*/

	/* Cast "reserved_1" pointer to the type we allocated.	*/
	reserved_info = (RESERVED_INFO *) rt_ctrl->reserved_1;

	comp_rt_type = rt_ctrl->rt_first + comp_rt_index;
	scl_enumtype = reserved_info[comp_rt_index].scl_enumtype;	/* may be NULL*/

	/* Component must be primitive.	*/
	assert (ms_is_rt_prim (comp_rt_type));
	if (comp_rt_type->el_tag == RT_INTEGER && scl_enumtype)	/* must be Enum	*/
	{
		//hejian alter on 2010-11-11  isalpha(valstring[0])
		if ((valstring[0] >= 'a' && valstring[0] <= 'z')
			|| (valstring[0] >= 'A' && valstring[0] <= 'Z')) 
		{
			/* If first char of valstring is alphabetic, try to match text with EnumType definition.*/
			SCL_ENUMVAL *scl_enumval;
			ST_BOOLEAN found = SD_FALSE;
			for (scl_enumval = (SCL_ENUMVAL *) list_find_last ((DBL_LNK *) scl_enumtype->enumvalHead);
				scl_enumval != NULL;
				scl_enumval = (SCL_ENUMVAL *) list_find_prev ((DBL_LNK *) scl_enumtype->enumvalHead, (DBL_LNK *) scl_enumval))
			{
				if (strcmp (scl_enumval->EnumVal, valstring) == 0)
				{
					*(ST_INT8*)data = scl_enumval->ord;
					found = SD_TRUE;
					break;
				}
			}
			if (!found)
				ret = SD_FAILURE;
		}
		else
			/* First char of Val is numeric. Use "sxaText.." to convert.*/
		{
			ret = sxaTextToLocal (valstring, data, 1,	/* rt_num always 1 (primitive)	*/
				comp_rt_type);
			//hejian add on 2010-7-25
			*(ST_INT8*)data = atoi(valstring);
		}
	}
	else if (comp_rt_type->el_tag == RT_BOOL)
	{		/* convert boolean (may be "0", "1", "true", or "false")	*/
		if (strcmp (valstring, "true") == 0 || strcmp (valstring, "1") == 0)
			*(ST_INT8 *)data = 1;
		else if (strcmp (valstring, "false") == 0 || strcmp (valstring, "0") == 0)
			*(ST_INT8 *)data = 0;
		else
			ret = SD_FAILURE;
	}
	/* Do special checking for visible strings.		*/
	else if (comp_rt_type->el_tag == RT_VISIBLE_STRING)
	{
		ST_CHAR *ptr;
		/* Visible string must not contain any control chars.	*/
		for (ptr = valstring; *ptr!=0; ptr++)
		{
			if (*ptr < ' ')     /* Check that character is not a control char.  */
			{
				SXLOG_ERR1 ("Illegal character (0x%02x) in visible string",
					(ST_UINT)(ST_UCHAR) *ptr);	/* 2 casts to avoid sign extension*/
				ret = SD_FAILURE;
				break;	/* stop on first error	*/
			}
		}
		if (ret == SD_SUCCESS)
		{
			if (comp_rt_type->u.p.el_len < 0	/* variable len	*/
				&& strlen (valstring) > (size_t) abs (comp_rt_type->u.p.el_len))
			{
				SXLOG_ERR2 ("String '%s' exceeds max len '%d'",
					valstring, abs (comp_rt_type->u.p.el_len));
				ret = SD_FAILURE;
			}
			else if (comp_rt_type->u.p.el_len >= 0	/* fixed len	*/
				&& strlen (valstring) != (size_t) comp_rt_type->u.p.el_len)
			{
				/* Shouldn't get here because no fixed len in SCL, but just in case..*/
				SXLOG_ERR2 ("String '%s' does not match fixed len '%d'",
					valstring, comp_rt_type->u.p.el_len);
				ret = SD_FAILURE;
			}
			else
				strcpy (data, valstring);	/* all is ok, so copy string*/
		}
	}	/* end RT_VISIBLE_STRING	*/
	else
	{	/* handle all other element types	*/
		ret = sxaTextToLocal (valstring, data, 1,	/* rt_num always 1 (primitive)	*/
			comp_rt_type);
		//hejian add on 2010-7-25
		strcpy(data, valstring);
	}

	if (ret)
	{	/* Our conversion code failed. Let the user try.	*/
		SCL2_IV_TRANSLATE_CTRL translate_ctrl;
		memset (&translate_ctrl, 0, sizeof (SCL2_IV_TRANSLATE_CTRL));

		translate_ctrl.scl_info = scl_info;
		translate_ctrl.scl_ld   = scl_ld;
		translate_ctrl.scl_ln   = scl_ln;
		translate_ctrl.valText  = valstring;
		translate_ctrl.attrib   = flattened_name;
		translate_ctrl.dest     = data;
		translate_ctrl.numRt    = 1;	/* always 1 (primitive)	*/
		translate_ctrl.rtHead   = comp_rt_type;

		ret = u_mvl_scl_set_initial_value (&translate_ctrl);/* call user funct*/
	}
	return (ret);
}

/************************************************************************/
/*			scl2_dai_set_value				*/
/* Set initial data value from DAI input from SCL file.			*/
/* Use sxaTextToLocal to convert the text to data.			*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_dai_set_value (SCL_INFO *scl_info,
								  SCL_LD *scl_ld,
								  SCL_LN *scl_ln,
								  SCL_DAI *scl_dai)
{
	ST_CHAR fixed_name [MAX_IDENT_LEN +1];
	ST_RET ret = SD_FAILURE;
	MVL_VAR_ASSOC *var;	/* MVL Variable Association created from LN info*/
	RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
	ST_INT comp_rt_num;		/* num of rt_types in component	*/
	ST_UINT32 mvl_debug_sel_save;
	MVL_TYPE_CTRL *type_ctrl;

	var = scl_ln->mvl_var_assoc;

	if (strlen (scl_dai->flattened) <= (MAX_IDENT_LEN-3))
	{
		/* Turn off false NERR log messages */
		mvl_debug_sel_save = mvl_debug_sel;
		mvl_debug_sel &= ~MVLLOG_NERR;

		/* Find the attribute type. Don't know the FC, so try all possible	*/
		/* FC (i.e."ST" "MX" "CO" "SP" "SG" "SE" "SV" "CF" "DC" or "EX").	*/
		do		/* use "do-while" loop only so we can break out on success*/
		{
			strcpy (fixed_name, "ST$");    /* Try "ST" first.		*/
			strcat (fixed_name, scl_dai->flattened);
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "MX", 2);	/* replace FC prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "CO", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "SP", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "SG", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "SE", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "SV", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "CF", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "DC", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/

			strncpy (fixed_name, "EX", 2);	/* replace prefix*/
			if ((ret = mvlu_find_comp_type (var->type_id, fixed_name, &comp_rt_type, &comp_rt_num)) == SD_SUCCESS)
				break;	/* found it. done	*/
		} while (0);	/* end of do-while loop	*/

		/* Restore MVL log mask settings */
		mvl_debug_sel = mvl_debug_sel_save;
	}

	/* Tried all possible FC. Did we find a match.	*/
	if (ret != SD_SUCCESS)
	{
		SXLOG_ERR2 ("scl2_dai_set_value: Attribute '%s' in '%s' not found.",
			scl_dai->flattened, scl_ln->varName);
		if (strchr (scl_dai->flattened, '[') != NULL)
			SXLOG_CERR0 ("Initialization of array elements not yet supported.");
	}
	else if (comp_rt_num !=1)
	{
		SXLOG_ERR2 ("scl2_dai_set_value: Attribute '%s' in '%s' not a primitive type.",
			scl_dai->flattened, scl_ln->varName);
		ret = SD_FAILURE;
	}

	if (ret == SD_SUCCESS && scl_dai->Val == NULL)
	{
		SXLOG_ERR2 ("scl2_dai_set_value: Attribute '%s' in '%s' does not have Val",
			scl_dai->flattened, scl_ln->varName);
		//   ret = SD_FAILURE;  //hhzhen del 0111
	}

	// if (ret == SD_SUCCESS)   // hhzhen del 0111
	if(ret==SD_SUCCESS && scl_dai->Val!=NULL) // hhzhen add 0111
	{
		type_ctrl = mvl_type_ctrl_find (var->type_id);
		ret = convert_initial_value (scl_info, scl_ld, scl_ln, fixed_name,
			type_ctrl->rt_ctrl,
			comp_rt_type - type_ctrl->rt_ctrl->rt_first,	/* index to this comp*/
			(ST_INT8*)(var->data)+comp_rt_type->mvluTypeInfo.offSet,
			scl_dai->Val);
	}

	if (ret == SD_SUCCESS)
		SXLOG_FLOW3 ("scl2_dai_set_value: Val '%s' conversion for '%s$%s' SUCCESSFUL",
		scl_dai->Val, scl_ln->varName, fixed_name);
	else
		SXLOG_ERR3 ("scl2_dai_set_value: Val '%s' conversion for '%s$%s' FAILED",
		scl_dai->Val, scl_ln->varName, fixed_name);

	if (scl_debug_mode)
	{
		if (ret != SD_SUCCESS)
			++scl_debug_mode_error_count;

		return (SD_SUCCESS);	/* Don't let this stop us for now ...	*/
	}
	return (ret);
}

/************************************************************************/
/*			scl2_da_or_bda_set_value_all			*/
/* NOTE: the same Val text might get converted many times by this	*/
/* function, but not enough info available to do conversion before now.	*/
/************************************************************************/
static ST_RET scl2_da_or_bda_set_value_all (SCL_INFO *scl_info,
											SCL_LD *scl_ld,
											SCL_LN *scl_ln)
{
	ST_RET ret;
	MVL_TYPE_CTRL *type_ctrl;
	RUNTIME_TYPE *rt_type;
	ST_INT rt_idx;	/* index into RUNTIME_TYPE array.	*/
	RESERVED_INFO *reserved_info;	/* ptr to array of extra type info.	*/

	ret = SD_SUCCESS;	/* assume success	*/

	type_ctrl = mvl_type_ctrl_find (scl_ln->mvl_var_assoc->type_id);
	assert (type_ctrl);
	/* Cast "reserved_1" pointer to the type we allocated.	*/
	reserved_info = (RESERVED_INFO *) type_ctrl->rt_ctrl->reserved_1;

	/* Loop through all elements of RUNTIME_TYPE array	*/
	for (rt_idx = 0, rt_type = type_ctrl->rt_ctrl->rt_first;
		rt_idx < type_ctrl->rt_ctrl->rt_num;
		rt_idx++, rt_type++)
	{
		ST_CHAR *Val = reserved_info[rt_idx].Val;

		if (Val)	/* string to convert*/
		{
			/* Convert text to value & store in Variable.	*/
			ret = convert_initial_value (scl_info, scl_ld, scl_ln,
				NULL,	/* don't know flattened_name in this case.	*/
				type_ctrl->rt_ctrl,
				rt_idx,
				(ST_INT8*)(scl_ln->mvl_var_assoc->data) + rt_type->mvluTypeInfo.offSet,
				Val);	/* string to convert*/
			if (ret != SD_SUCCESS)
			{
				SXLOG_ERR2 ("Cannot convert DA or BDA Val='%s' to data for '%s' attribute.",
					Val, ms_comp_name_find(rt_type));
				break;	/* stop now	*/
			}
		}
	}
	return (ret);
}
/************************************************************************/
/*			scl2_dai_set_value_all			*/
/* Initialize data for all DAI in this logical node.			*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_dai_set_value_all (SCL_INFO *scl_info,
									  SCL_LD *scl_ld,
									  SCL_LN *scl_ln)
{
	SCL_DAI *scl_dai;
	ST_RET ret;

	ret = SD_SUCCESS;	/* assume success	*/

	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*       so get off list in reverse order.				*/
	for (scl_dai = (SCL_DAI *) list_find_last ((DBL_LNK *) scl_ln->daiHead);
		scl_dai != NULL;
		scl_dai = (SCL_DAI *) list_find_prev ((DBL_LNK *) scl_ln->daiHead, (DBL_LNK *) scl_dai))
	{
		ret = scl2_dai_set_value (scl_info, scl_ld, scl_ln, scl_dai);
		if (ret)
		{
			SXLOG_ERR3 ("scl2_dai_set_value FAILED for '%s' (LD=%s LN=%s)",
				scl_dai->flattened, scl_ld->domName, scl_ln->varName);
			// break;	/* if one fails, stop processing	*/
			//////hejian alter on 2010-3-29/////////
		}
		else
			SXLOG_FLOW3 ("scl2_dai_set_value DONE for '%s' (LD=%s LN=%s)",
			scl_dai->flattened, scl_ld->domName, scl_ln->varName);
	}
	return (SD_SUCCESS);
}
/************************************************************************/
/*			scl2_ld_create_part1			*/
/* Create Domain and all variables in it.				*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_ld_create_part1 (
									MVL_VMD_CTRL *vmd_ctrl,
									SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									SCL_LD *scl_ld)
{
	ST_RET ret = SD_SUCCESS;	/* Assume success	*/
	MVL_DOM_CTRL *dom_ctrl;
	ST_INT max_num_var;	/* compute from scl_ld info	*/
	ST_INT max_num_nvl;
	ST_INT max_num_jou;
	SCL_LN *scl_ln;

	/* Make sure there's room for all Logical Nodes (variables) defined in SCL.*/
	/* plus room for the configured maximum number of dynamic variables.	*/
	max_num_var = list_get_sizeof (scl_ld->lnHead) + mvl_max_dyn.dom_vars;
	max_num_nvl = mvl_max_dyn.dom_nvls;
	max_num_jou = mvl_max_dyn.journals;

	/* First create MMS domain	*/
	dom_ctrl = mvl_vmd_dom_add (vmd_ctrl,
		scl_ld->domName,	/* domain name	*/
		max_num_var,
		max_num_nvl,
		max_num_jou,
		SD_TRUE);	/* always copy name to dom_ctrl	*/
	if (!dom_ctrl)
		ret = SD_FAILURE;

	/* If MMS domain created successfully, create all MMS variables (logical nodes).	*/
	if (ret == SD_SUCCESS)
	{
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
		{
			ret = scl2_ln_create (vmd_ctrl, scl_info, scl_ld, scl_ln);
			if (ret)
			{
				SXLOG_ERR1 ("scl2_ln_create FAILED for %s", scl_ln->varName);
				break;	/* if one fails, stop processing	*/
			}
			else
				SXLOG_FLOW1 ("scl2_ln_create for %s SUCCESSFUL", scl_ln->varName);
		}
	}

	return (ret);
}

/************************************************************************/
/*			scl2_ld_create_part2			*/
/* Create all NVLs and RCBs in this domain.				*/
/* NOTE: this cannot be done in "scl2_ld_create_part1" because NVL	*/
/* may include VAR from another Domain that was not defined yet.	*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
static ST_RET scl2_ld_create_part2 (
									MVL_VMD_CTRL *vmd_ctrl,
									SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
									SCL_LD *scl_ld,
									ST_UINT reportScanRate,	/* report scan rate (millisec)	*/
									ST_BOOLEAN is_client)	/* see description in scl2_ld_create_all*/
{
	ST_RET ret = SD_SUCCESS;	/* Assume success	*/
	SCL_LN *scl_ln;

	/* Create all MMS NVLs (DataSets).
	* IEC 61850 defines a DataSet "inside" a Logical Node.
	* This should seem a little strange, because
	* a Logical Node maps to a MMS Variable, and a DataSet maps to a
	* MMS Named Variable List, and of course, a Named Variable List CANNOT
	* be "inside" of a Variable.
	* This is resolved by simply creating a normal Named Variable List, and just
	* adding it to the same Domain as the Variable.
	* CRITICAL: THIS IS DONE AFTER ALL VARIABLES (LOGICAL NODES) CREATED BECAUSE
	*           DATASET MAY REFERENCE OTHER LOGICAL NODES.
	*/
	if (ret == SD_SUCCESS)
	{
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
		{
			ret = scl2_dataset_create_all (vmd_ctrl, scl_ld, scl_ln);
			if (ret)
			{
				break;	/* if one fails, stop processing (error already logged)	*/
			}
		}
	}

	if (is_client)
	{
		SXLOG_FLOW0 ("Client configuration. Control blocks not created.");
		return (ret);	/* Stop now. Do NOT create RCB, LCB, etc.	*/
	}

	/* If all successful up to here, create all RCBs.	*/
	//if (ret == SD_SUCCESS)
	{
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
		{
			ret = scl2_rcb_create_all (vmd_ctrl, scl_info, scl_ld, scl_ln, reportScanRate);
			if (ret)
			{
				break;	/* if one fails, stop processing (error already logged)	*/
			}
		}
	}

	/* If all successful up to here, set initial values from DA & BDA.	*/
	//if (ret == SD_SUCCESS)
	{
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
		{
			ret = scl2_da_or_bda_set_value_all (scl_info, scl_ld, scl_ln);
			if (ret)
			{
				break;	/* if one fails, stop processing (error already logged)	*/
			}
		}
	}

	/* If all successful up to here, set initial data values from		*/
	/* DOI/SDI/DAI entries found in the SCL file.				*/
	//if (ret == SD_SUCCESS)
	{
		/* NOTE: linked list is in reverse order from data in SCL file,	*/
		/*     so get off list in reverse order.				*/
		for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
		{
			ret = scl2_dai_set_value_all (scl_info, scl_ld, scl_ln);
			if (ret)
			{
				break;	/* if one fails, stop processing (error already logged)	*/
			}
		}
	}

	return (ret);
}
/************************************************************************/
/*			scl2_ld_create_all				*/
/* Create all Logical Devices from SCL info saved in "scl_info".	*/
/* NOTE: must be done in 2 parts, because NVLs created in part2, may	*/
/* reference Vars from different domains created in part1.		*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET scl2_ld_create_all (
						   MVL_VMD_CTRL *vmd_ctrl,	/* VMD in which to add Logical Devices.	*/
						   SCL_INFO *scl_info,	/* main struct where all SCL info stored*/
						   ST_UINT reportScanRate,	/* report scan rate (millisec)	*/
						   ST_INT brcb_bufsize,	/* BRCB buffer size			*/
						   ST_BOOLEAN is_client)	/* If this flag is set, Client model is	*/
						   /* created (i.e. Control Blocks NOT created).*/
{
	ST_RET ret;
	//SCL_LD *scl_ld;

	/* CRITICAL: Don't allow this to be called again for the same SCL_INFO struct.*/
	/* That would cause duplicate objects.				*/
	if (scl_info->ld_create_done)
	{
		SXLOG_ERR0 ("Logical Devices already created for this SCL file. Cannot create again.");
		return (SD_FAILURE);
	}
	else
		scl_info->ld_create_done = SD_TRUE;	/* Set flag now	*/

	/* Save BRCB buffer size in scl_info so lower functions can access it.*/
	scl_info->brcb_bufsize = brcb_bufsize;

	ret = SD_SUCCESS;	/* default ret val: returned if LD linked list empty.*/

	/* NOTE: linked list is in reverse order from data in SCL file,	*/
	/*     so get off list in reverse order.				*/
	//hejian del on 2010-11-5
	//for (scl_ld = (SCL_LD *) list_find_last ((DBL_LNK *) scl_info->ldHead);
	//	scl_ld != NULL;
	//	scl_ld = (SCL_LD *) list_find_prev ((DBL_LNK *) scl_info->ldHead, (DBL_LNK *) scl_ld))
	//{
	//	ret = scl2_ld_create_part1 (vmd_ctrl, scl_info, scl_ld);
	//	if (ret)
	//	{
	//		SXLOG_ERR1 ("scl2_ld_create_part1 for '%s' FAILED", scl_ld->domName);
	//		break;	/* if one fails, stop processing	*/
	//	}
	//	else
	//	{
	//		SXLOG_FLOW1 ("scl2_ld_create_part1 for '%s' SUCCESSFUL", scl_ld->domName);
	//	}
	//}
	///* NOTE: linked list is in reverse order from data in SCL file,	*/
	///*     so get off list in reverse order.				*/
	//for (scl_ld = (SCL_LD *) list_find_last ((DBL_LNK *) scl_info->ldHead);
	//	scl_ld != NULL;
	//	scl_ld = (SCL_LD *) list_find_prev ((DBL_LNK *) scl_info->ldHead, (DBL_LNK *) scl_ld))
	//{
	//	ret = scl2_ld_create_part2 (vmd_ctrl, scl_info, scl_ld, reportScanRate, is_client);
	//	if (ret)
	//	{
	//		SXLOG_ERR1 ("scl2_ld_create_part2 for '%s' FAILED", scl_ld->domName);
	//		if (!scl_debug_mode)
	//			break;	/* if one fails, stop processing	*/

	//		++scl_debug_mode_error_count;
	//	}
	//	else
	//	{
	//		SXLOG_FLOW1 ("scl2_ld_create_part2 for '%s' SUCCESSFUL", scl_ld->domName);
	//	}
	//}
	/* Create "LastApplError" variable (required if "Control with		*/
	/* enhanced security" supported).					*/
	if (ret == SD_SUCCESS)
		ret = mvl61850_ctl_lastapplerror_create ();

	/* The reserved_1 member of every RUNTIME_CTRL is must now be freed.	*/
	reserved_free_all (vmd_ctrl);
	return (ret);
}
