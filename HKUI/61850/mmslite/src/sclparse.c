/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*	2004-2006, All Rights Reserved					*/
/*                                                                      */
/* MODULE NAME : sclparse.c                                             */
/* PRODUCT(S)  :                                                        */
/*                                                                      */
/* MODULE DESCRIPTION : This routine parses XML files conforming to the */
/*                      SCL object model.			        */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev          Comments                                */
/* --------  ---  ------   -------------------------------------------  */
/* 09/08/06  JRB    17     Fix dstlen type in convert_mac.		*/
/* 07/26/06 LWP/JRB 16     Parse & save GOOSE & SMV addressing info from*/
/*			   "Communication" section.			*/
/* 04/19/06  JRB    15     Make datSet in ReportControl "optional".	*/
/* 04/19/06  JRB    14     Parse & save "RptEnabled" info.		*/
/* 04/04/06  JRB    13     Parse & save "SampledValueControl" info.	*/
/* 03/25/06  JRB    12     Change order of operations: call create/add	*/
/*			   functions first, then copy data directly to	*/
/*			   SCL structs (eliminates intermediate copy).	*/
/*			   Repl scl_get_attr (could overflow caller buf)*/
/*			   with scl_get_attr_ptr & scl_get_attr_copy.	*/
/*			   Replace CONTROL_BLOCK with SCL_RCB & SCL_LCB,*/
/*			   Fix _DA_SEFun setting of dchg, qchg, & dupd.	*/
/*			   Fix sx_get_string calls to prevent overflow.	*/
/*			   Fix "*_Val_*" functions.			*/
/*			   Chg desc to ptr (allocated during parse).	*/
/* 07/25/05  JRB    11     Make nameStructure optional, default=IEDName.*/
/* 06/24/05  JRB    10     Call sx_parseExx_mt (faster).		*/
/*			   Chg "ord" from unsigned to signed value.	*/
/* 05/17/05  DWL    09     Use sx_push instead of SX_PUSH, and force	*/
/*			   user code to call sx_pop.  Eliminated some	*/
/*			   unnecessary debug logging.			*/
/* 05/17/05  JRB    08     Avoid allocating struct in scl_parse.	*/
/* 02/15/05  JRB    07     Save iedName in scl_info.			*/
/*			   Parse Header & save in scl_info.		*/
/*			   Fix some log messages.			*/
/* 12/07/04  JRB    06     Del unneeded memsets after callocs.		*/
/* 08/23/04  JRB    05     Ret err if iedName or accessPoint.. not found*/
/* 08/06/04  JRB    04     Del "sclparse.h", use "scl.h".		*/
/* 07/23/04  JRB    03     Del unused static functions.			*/
/* 07/15/04  DWL    02     Added LogControl & GSEControl elements	*/
/*			   Handle LN and LN0 differently.		*/
/* 06/10/04  DWL    01     Created					*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "sx_defs.h"
#include "sx_log.h"
#include "str_util.h"
#include "slog.h"
#include "scl.h"	/* SCL file processing structs & functions	*/
#include "mvl_uca.h"
#include "smpval.h"

/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of      */
/* __FILE__ strings.                                                    */

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

#define SCL_ATTR_OPTIONAL 	0	/* attribute is optional	*/
#define SCL_ATTR_REQUIRED 	1	/* attribute is required	*/

typedef struct scl_dec_ctrl
{
	ST_CHAR *iedName;
	ST_CHAR *accessPointName;
	ST_BOOLEAN accessPointFound;	/* SD_TRUE if IED and AccessPoint found	*/
	ST_BOOLEAN iedNameMatched;	
	ST_BOOLEAN accessPointMatched;
	SCL_INFO *sclInfo;
	SCL_SUBSTATION *scl_substation;
	SCL_VOLLEVEL *scl_vollevel;
	SCL_BAY *scl_bay;
	SCL_GSE *scl_gse;	/* Used for "GSE" in "Communication" section	*/
	SCL_SMV *scl_smv;	/* Used for "SMV" in "Communication" section	*/

	SCL_ADDRESS *scl_address;

	SCL_LD *scl_ld;	/* Used for "LDevice"				*/
	SCL_LN *scl_ln;	/* Used for "LN" (Logical Node)			*/
	SCL_RCB *scl_rcb;	/* alloc to store ReportControl info		*/
	SCL_LCB *scl_lcb;	/* alloc to store LogControl info		*/
	SCL_SGCB *scl_sgcb;	/* alloc to store SettingControl info		*/ // zhouhj20181206
	ST_UINT8 TrgOps[1];	/* Used for ReportControl or LogControl.	*/
	/* Copied to SCL_RCB or SCL_LCB.		*/
	SCL_SVCB *scl_svcb;	/* Used for "SampledValueControl".	*/
	SCL_ENUMVAL *scl_enumval;	/* Used for "EnumVal".			*/
	SCL_DAI *scl_dai;	/* Used for "DAI".				*/
	SCL_DA *scl_da;	/* Used for "DA".				*/
	SCL_BDA *scl_bda;	/* Used for "BDA".				*/
	ST_CHAR flattened[MAX_FLAT_LEN + 1];	/* Created by concatenating values*/
	/* from DOI, SDI, and DAI elements*/
} SCL_DEC_CTRL;

/************************************************************************/
static ST_VOID _SCL_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _Header_SFun (SX_DEC_CTRL *sxDecCtrl);

static ST_VOID _Communication_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SubNetwork_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _ConnectedAP_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _GSE_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _GSE_Address_SEFun (SX_DEC_CTRL *sxDecCtrl);

static ST_VOID _Address_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _Address_P_SEFun (SX_DEC_CTRL *sxDecCtrl);



//hejian add on 2010-7-28
static ST_VOID _GSE_MinTime_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _GSE_MaxTime_SEFun (SX_DEC_CTRL *sxDecCtrl);

static ST_VOID _GSE_Address_P_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SMV_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SMV_Address_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SMV_Address_P_SEFun (SX_DEC_CTRL *sxDecCtrl);

static ST_VOID _IED_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _AccessPoint_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _Server_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _LDevice_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _LN_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DataSet_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _FCDA_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _ReportControl_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _LogControl_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _GSEControl_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _Inputs_SFun (SX_DEC_CTRL *sxDecCtrl);	//hejian add on 2010-11-2
static ST_VOID _ExtRef_SFun (SX_DEC_CTRL *sxDecCtrl);	//hejian add on 2010-11-2
static ST_VOID _SettingControl_SFun (SX_DEC_CTRL *sxDecCtrl);	//周宏军 add on 2018-12-6
static ST_VOID _TrgOps_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _OptFlds_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _RptEnabled_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DOI_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SDI_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DAI_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DAI_Val_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DataTypeTemplates_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _LNodeType_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DO_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DOType_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DA_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SDO_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DAType_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _DA_Val_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _BDA_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _BDA_Val_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _EnumType_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _EnumVal_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_RET _scl_unknown_el_start (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag);
static ST_RET _scl_unknown_el_end (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag);
static ST_VOID _SampledValueControl_SEFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SampledValueControl_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SampledValueControl_EFun (SX_DEC_CTRL *sxDecCtrl);
static ST_VOID _SmvOpts_SFun (SX_DEC_CTRL *sxDecCtrl);
static ST_INT _hex_to_uint(char *str);


static ST_VOID _SubStation_SEFun (SX_DEC_CTRL *sxDecCtrl);

static ST_VOID _VoltageLevel_SEFun (SX_DEC_CTRL *sxDecCtrl);

static ST_VOID _Bay_SEFun (SX_DEC_CTRL *sxDecCtrl);

/************************************************************************/
/************************************************************************/
/* Only the elements we need to extract are listed here.		*/
/* The rest are handled by "unknown" element handler.			*/
SX_ELEMENT sclStartElements[] = 
{
	{"SCL", 		SX_ELF_CSTARTEND,		_SCL_SEFun, NULL, 0}
};

SX_ELEMENT SCLElements[] = 
{
	{"Header",           	SX_ELF_CSTART|SX_ELF_OPT, 	_Header_SFun, NULL, 0},
	{"Substation",    	SX_ELF_CSTARTEND|SX_ELF_OPT, 	_SubStation_SEFun, NULL, 0},
	{"Communication",    	SX_ELF_CSTARTEND|SX_ELF_OPT, 	_Communication_SEFun, NULL, 0},
	{"IED",            	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_IED_SEFun, NULL, 0},
	{"DataTypeTemplates", SX_ELF_CSTARTEND|SX_ELF_OPT, 	_DataTypeTemplates_SEFun, NULL, 0}
};

/************************************************************************/
/* Tables for mapping "Communication" elements.				*/
/************************************************************************/
SX_ELEMENT CommunicationElements[] = 
{
	{"SubNetwork",      	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SubNetwork_SEFun, NULL, 0}
};

SX_ELEMENT SubNetworkElements[] = 
{
	/* NOTE: "bitRate" and "Text" elements ignored.	*/
	{"ConnectedAP",      	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_ConnectedAP_SEFun, NULL, 0}
};

SX_ELEMENT ConnectedAPElements[] = 
{
	/* DEBUG: add "Address". Ignore "PhyConn".	*/
	{"GSE",	      	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_GSE_SEFun, NULL, 0},
	{"SMV",	      	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SMV_SEFun, NULL, 0},
	{"Address",	      	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_Address_SEFun, NULL, 0}
};

SX_ELEMENT AddressElements[] = 
{
	{"P",      		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_Address_P_SEFun, NULL, 0}
};

SX_ELEMENT GSEElements[] = 
{
	{"Address",      	SX_ELF_CSTARTEND|SX_ELF_OPT, 	_GSE_Address_SEFun, NULL, 0},

	//hejian add on 2010-7-28
	{"MinTime",      	SX_ELF_CSTARTEND|SX_ELF_OPT, 	_GSE_MinTime_SEFun, NULL, 0},
	{"MaxTime",      	SX_ELF_CSTARTEND|SX_ELF_OPT, 	_GSE_MaxTime_SEFun, NULL, 0}
};

SX_ELEMENT GSEAddressElements[] = 
{
	{"P",      		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_GSE_Address_P_SEFun, NULL, 0}
};

SX_ELEMENT SMVElements[] = 
{
	{"Address",      	SX_ELF_CSTARTEND|SX_ELF_OPT, 	_SMV_Address_SEFun, NULL, 0}
};

SX_ELEMENT SMVAddressElements[] = 
{
	{"P",      		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SMV_Address_P_SEFun, NULL, 0}
};
/************************************************************************/
/* Tables for mapping "IED" elements.					*/
/************************************************************************/
SX_ELEMENT IEDElements[] = 
{
	{"AccessPoint",      	SX_ELF_CSTARTEND|SX_ELF_RPT, 	_AccessPoint_SEFun, NULL, 0}
};

SX_ELEMENT AccessPointElements[] = 
{
	{"Server",      	SX_ELF_CSTARTEND, 		_Server_SEFun, NULL, 0}
};

SX_ELEMENT ServerElements[] = 
{
	{"LDevice",      	SX_ELF_CSTARTEND|SX_ELF_RPT,	_LDevice_SEFun, NULL, 0}
};

SX_ELEMENT LDeviceElements[] = 
{
	{"LN0",      		SX_ELF_CSTARTEND,		_LN_SEFun, NULL, 0},
	{"LN",      		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_LN_SEFun, NULL, 0}
};

SX_ELEMENT LN0Elements[] = 
{
	{"DataSet",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DataSet_SEFun, NULL, 0},
	{"ReportControl",	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_ReportControl_SEFun, NULL, 0},
	{"DOI",			SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DOI_SEFun, NULL, 0}, 
	{"SampledValueControl",	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SampledValueControl_SEFun, NULL, 0},
	{"LogControl",	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_LogControl_SEFun, NULL, 0},
	{"GSEControl",	SX_ELF_CSTART|SX_ELF_OPTRPT,	_GSEControl_SFun, NULL, 0},
	{"Inputs",		SX_ELF_CSTARTEND|SX_ELF_OPT,	_Inputs_SFun, NULL, 0},	//hejian add on 2010-11-2
	{"SettingControl",		SX_ELF_CSTARTEND|SX_ELF_OPT,	_SettingControl_SFun, NULL, 0}//zhouhj 增加用于定值控制块 20181206
};

SX_ELEMENT LNElements[] = 
{
	{"DataSet",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DataSet_SEFun, NULL, 0},
	{"ReportControl",	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_ReportControl_SEFun, NULL, 0},
	{"DOI",		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DOI_SEFun, NULL, 0}, 
	{"SampledValueControl",	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SampledValueControl_SEFun, NULL, 0},
	{"LogControl",	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_LogControl_SEFun, NULL, 0}
};

SX_ELEMENT DataSetElements[] = 
{
	{"FCDA",  		SX_ELF_CSTART|SX_ELF_RPT,	_FCDA_SFun, NULL, 0}
};

SX_ELEMENT ReportControlElements[] = 
{
	{"TrgOps",  		SX_ELF_CSTART|SX_ELF_OPT,	_TrgOps_SFun, NULL, 0},
	{"OptFields",		SX_ELF_CSTART,			_OptFlds_SFun, NULL, 0},
	{"RptEnabled",	SX_ELF_CSTART|SX_ELF_OPT,	_RptEnabled_SFun, NULL, 0}
};

SX_ELEMENT LogControlElements[] = 
{
	{"TrgOps",  		SX_ELF_CSTART|SX_ELF_OPT,	_TrgOps_SFun, NULL, 0}
};

SX_ELEMENT SampledValueControlElements[] = 
{
	{"SmvOpts",  		SX_ELF_CSTART,			_SmvOpts_SFun, NULL, 0}
};

SX_ELEMENT DOIElements[] = 
{
	{"SDI",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SDI_SEFun, NULL, 0},
	{"DAI",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DAI_SEFun, NULL, 0}
};

SX_ELEMENT INPUTSElements[] =		//hejian add on 2010-11-2
{
	{"ExtRef",	SX_ELF_CSTART|SX_ELF_OPTRPT, _ExtRef_SFun, NULL, 0}
};

/* SDI can be nested under itself indefinitely */
SX_ELEMENT SDIElements[] = 
{
	{"SDI",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_SDI_SEFun, NULL, 0},
	{"DAI",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DAI_SEFun, NULL, 0}
};

SX_ELEMENT DAIElements[] = 
{
	{"Val",  		SX_ELF_CSTARTEND|SX_ELF_OPT,	_DAI_Val_SEFun, NULL, 0}
};

/************************************************************************/
/* Tables for mapping "DataTypeTemplates" elements.			*/
/************************************************************************/
SX_ELEMENT DataTypeTemplatesElements[] = 
{
	{"LNodeType",  	SX_ELF_CSTARTEND|SX_ELF_RPT,	_LNodeType_SEFun, NULL, 0},
	{"DOType",  		SX_ELF_CSTARTEND|SX_ELF_RPT,	_DOType_SEFun, NULL, 0},
	{"DAType",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DAType_SEFun, NULL, 0},
	{"EnumType", 		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_EnumType_SEFun, NULL, 0}
};

SX_ELEMENT LNodeTypeElements[] = 
{
	{"DO",  		SX_ELF_CSTART|SX_ELF_RPT,	_DO_SFun, NULL, 0}
};

SX_ELEMENT DOTypeElements[] = 
{
	{"DA",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DA_SEFun, NULL, 0},
	{"SDO",  		SX_ELF_CSTART|SX_ELF_OPTRPT,	_SDO_SFun, NULL, 0}
};

SX_ELEMENT DAElements[] = 
{
	{"Val",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_DA_Val_SEFun, NULL, 0}
};

SX_ELEMENT DATypeElements[] = 
{
	{"BDA",  		SX_ELF_CSTARTEND|SX_ELF_RPT,	_BDA_SEFun, NULL, 0}
};

SX_ELEMENT BDAElements[] = 
{
	{"Val",  		SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_BDA_Val_SEFun, NULL, 0}
};

SX_ELEMENT EnumTypeElements[] = 
{
	{"EnumVal",  		SX_ELF_CSTARTEND|SX_ELF_RPT,	_EnumVal_SEFun, NULL, 0}
};

//2014-10-27
static ST_INT _hex_to_uint(char *str)
{
	ST_INT val = 0;
	char *p = str;

	while (*p != 0)
	{
		val = val * 16;
		
		if ('0' <= *p && *p <= '9')
		{
			val += *p - '0';
		}
		else if ('A' <= *p && *p <= 'F')
		{
			val += *p - 'A' + 10;
		}
		else if ('a' <= *p && *p <= 'f')
		{
			val += *p - 'a' + 10;
		}

		p++;
	}

	return val;
}

SX_ELEMENT SubstationElements[] = 
{
	{"VoltageLevel",   SX_ELF_CSTARTEND|SX_ELF_OPTRPT,		_VoltageLevel_SEFun, NULL, 0}
};



SX_ELEMENT VoltageLevelElements[] = 
{
	/* NOTE: "bitRate" and "Text" elements ignored.	*/
	{"Bay",  	SX_ELF_CSTARTEND|SX_ELF_OPTRPT,	_Bay_SEFun, NULL, 0}
};



/************************************************************************/
/*			convert_mac					*/
/* Converts MAC string read from SCL file (like 01-02-03-04-05-06)	*/
/* to 6 byte hex MAC address.						*/
/************************************************************************/
#define MAX_MAC_STRING_LEN	60

static ST_RET _is_mac_char(ST_CHAR ch)
{
	if ('0' <= ch && ch <= '9')
	{
		return SD_SUCCESS;
	}

	if ('a' <= ch && ch <= 'f')
	{
		return SD_SUCCESS;
	}

	if ('A' <= ch && ch <= 'F')
	{
		return SD_SUCCESS;
	}

	return SD_FAILURE;
}

static ST_RET convert_mac (ST_UCHAR *dst, ST_CHAR *src)
{
	ST_RET retcode;
	ST_CHAR tmpbuf [MAX_MAC_STRING_LEN+1];
	ST_CHAR *tmpptr;
	ST_UINT dstlen;
	ST_UINT maclen;//

	/* Input string may include extra blanks, so allow for fairly long string.*/
	if (strlen (src) > MAX_MAC_STRING_LEN)
		retcode = SD_FAILURE;
	else
	{
		/* Just replace each '-' with ' '. Then use ascii_to_hex_str to convert.*/
		tmpptr = tmpbuf;
		maclen = 0;//
		/* Copy until NULL terminator but ignore '-' and spaces.	*/
		for ( ;  *src;  src++)
		{
			if (SD_SUCCESS == _is_mac_char(*src))//*src != '-' && (!isspace(*src)))
			{
				maclen++;//
				*tmpptr = *src;
				tmpptr++;
			}
			else
			{
				//hejian add on 2010-8-4
				if (maclen == 1)
				{
					*tmpptr = '0';//*(tmpptr - 1);
					//*(tmpptr - 1) = '0';
					tmpptr++;
				}
				maclen = 0;
			}
		}

		//hejian add on 2010-8-4
		if (maclen == 1)
		{
			*tmpptr = '0';
			tmpptr++;
		}

		*tmpptr = '\0';	/* NULL terminate temp buffer	*/
		retcode = ascii_to_hex_str (dst, &dstlen, 6, tmpbuf);
		//if (retcode == SD_SUCCESS && dstlen != 6)
		//	retcode = SD_FAILURE; 
	}
	return (retcode);
}

/************************************************************************/
/*			log_notfound_attr				*/
/************************************************************************/

static ST_VOID log_notfound_attr (ST_CHAR *attrName)
{
	SXLOG_ERR1 ("SCL PARSE: Required attribute '%s' not found.", 
		attrName);
}

/************************************************************************/
/*			log_attr_str					*/
/************************************************************************/

static ST_VOID log_attr_str (ST_CHAR *name, ST_CHAR *value)
{
	SXLOG_DEC2 ("SCL PARSE: Found attribute '%s', value is '%s'", name, value);
}

/************************************************************************/
/*			log_attr_int					*/
/************************************************************************/

static ST_VOID log_attr_int (ST_CHAR *name, ST_INT value)
{
	SXLOG_DEC2 ("SCL PARSE: Found attribute '%s', value is '%d'", name, value);
}

/************************************************************************/
/*			log_attr_uint					*/
/************************************************************************/

static ST_VOID log_attr_uint (ST_CHAR *name, ST_UINT value)
{
	SXLOG_DEC2 ("SCL PARSE: Found attribute '%s', value is '%u'", name, value);
}

/************************************************************************/
/*			log_returned_failure				*/
/************************************************************************/

static ST_VOID log_returned_failure (ST_CHAR *funcName, ST_LONG ret)
{
	SXLOG_ERR2 ("SCL PARSE: %s returned failure, err=%ld", funcName, ret);
}

/************************************************************************/
/*			scl_stop_parsing				*/
/************************************************************************/

static ST_VOID scl_stop_parsing (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *offender,
								 ST_RET errCode)
{
	sxDecCtrl->errCode = errCode;
	sxDecCtrl->termFlag = SD_TRUE;
	if (errCode == SX_REQUIRED_TAG_NOT_FOUND)
	{
		log_notfound_attr (offender);
	}
	else /* SX_USER_ERROR */
	{
		log_returned_failure (offender, errCode);
	}
}

/************************************************************************/
/*			scl_get_attr_ptr				*/
/* Get a pointer to an attr string stored in SX_DEC_CTRL.		*/
/* If attr found, SD_SUCCESS returned & "*value" points to string.	*/
/* NOTE: The pointer returned in "*value" might not be valid later	*/
/*	when parsing continues.						*/
/************************************************************************/

static ST_RET scl_get_attr_ptr (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *name,
								ST_CHAR **value, ST_BOOLEAN required)
{
	ST_RET ret;

	ret = sx_get_attr_ptr (sxDecCtrl, value, name);
	if (ret != SD_SUCCESS)
	{
		*value = NULL;	/* make sure ptr is NULL on error (better than garbage)*/
		if (required)
			scl_stop_parsing (sxDecCtrl, name, SX_REQUIRED_TAG_NOT_FOUND);
	}
	else
		log_attr_str (name, *value);

	return (ret);
}

/************************************************************************/
/*			scl_get_attr_copy				*/
/* Get a pointer to an attr string stored in SX_DEC_CTRL.		*/
/* If strlen <= maxValueLen, copy string, else return error.		*/
/************************************************************************/

// static ST_RET scl_get_attr_copy (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *name,
// 								 ST_CHAR *value, ST_UINT maxValueLen, ST_BOOLEAN required)
// {
// 	ST_RET ret;
// 	ST_CHAR *pValue;
// 
// 	ret = scl_get_attr_ptr (sxDecCtrl, name, &pValue, required);
// 	if (ret == SD_SUCCESS)
// 	{
// 		if (strlen (pValue) <= maxValueLen)
// 		{
// 			//在此添加创建的代码
// 			strcpy (value, pValue);	/* copy string to caller's buffer	*/
// 		}
// 		else
// 		{
// 			if (0 == strcmp(name,"sAddr"))   //zhow20180307 南瑞继保 部分压板的短地址值长度大于100 导致SCD解析失败
// 			{
// 				strcpy (value, "属性值太长未拷贝");
// 				return (ret);
// 			}
// 			else
// 			{
// 				SXLOG_ERR3 ("Attribute Value='%s' exceeds max len '%d' for attribute '%s'", pValue, maxValueLen, name);
// 				scl_stop_parsing (sxDecCtrl, name, SX_USER_ERROR);
// 				ret = SD_FAILURE;
// 			}
// 		}
// 	}
// 
// 	return (ret);
// }

#ifdef SCL_USE_MMS_STRING_
static ST_RET scl_get_attr_copy_mms_str (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *name,
								 MMS_MEM_STRING *pMms_Value, ST_BOOLEAN required)
{
	ST_RET ret;
	ST_CHAR *pValue;

	ret = scl_get_attr_ptr (sxDecCtrl, name, &pValue, required);
	if (ret == SD_SUCCESS)
	{
		mms_str_set(pMms_Value,pValue);
	}

	return (ret);
}
#endif

static ST_RET scl_get_attr_copy (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *name,
								 ST_CHAR *value, ST_UINT maxValueLen, ST_BOOLEAN required)
{
	ST_RET ret;
	ST_CHAR *pValue;

	ret = scl_get_attr_ptr (sxDecCtrl, name, &pValue, required);
	if (ret == SD_SUCCESS)
	{
		if (strlen (pValue) <= maxValueLen)
		{
			//在此添加创建的代码
			strcpy (value, pValue);	/* copy string to caller's buffer	*/
		}
		else
		{
			if (strcmp(name,"sAddr") == 0)//zhow20180307 南瑞继保 部分压板的短地址值长度大于100 导致SCD解析失败
			{
				//strcpy (value, "属性值太长未拷贝");
				memcpy(value, pValue, maxValueLen);
				//alue[maxValueLen] = 0;
				return (ret);
			}
			else
			{
				SXLOG_ERR3 ("Attribute Value='%s' exceeds max len '%d' for attribute '%s'", pValue, maxValueLen, name);
				scl_stop_parsing (sxDecCtrl, name, SX_USER_ERROR);
				ret = SD_FAILURE;
			}
		}
	}

	return (ret);
}

/************************************************************************/
/*			scl_get_int_attr				*/
/************************************************************************/

static ST_RET scl_get_int_attr (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *name,
								ST_INT *value, ST_BOOLEAN required)
{
	ST_RET ret;

	ret = sx_get_int_attr (sxDecCtrl, name, value);
	if (ret != SD_SUCCESS)
	{
		if (required)
			scl_stop_parsing (sxDecCtrl, name, SX_REQUIRED_TAG_NOT_FOUND);
	}
	else
		log_attr_int (name, *value);

	return (ret);
}

/************************************************************************/
/*			scl_get_uint_attr				*/
/************************************************************************/

static ST_RET scl_get_uint_attr (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *name,
								 ST_UINT *value, ST_BOOLEAN required)
{
	ST_RET ret;

	ret = sx_get_uint_attr (sxDecCtrl, name, value);
	if (ret != SD_SUCCESS)
	{
		if (required)
			scl_stop_parsing (sxDecCtrl, name, SX_REQUIRED_TAG_NOT_FOUND);
	}
	else
		log_attr_uint (name, *value);

	return (ret);
}

/************************************************************************/
/*			 construct_flattened				*/
/* Construct a flattened variable name from DOI, SDI, DAI names.	*/
/************************************************************************/
ST_RET construct_flattened (ST_CHAR *flattened, size_t maxlen, ST_CHAR *name, ST_CHAR *ix)
{
	size_t ixlen;
	ST_RET retCode;

	/* Calc space needed for optional [ix]	*/
	if (ix)
		ixlen = strlen(ix)+2;	/* string plus brackets	*/
	else
		ixlen = 0;
	/* Make sure there is room for [ix] and "$"	*/
	if (strlen (flattened) + strlen(name) + ixlen + 1 <= maxlen)
	{
		/* If flattened is now empty, just copy name, else add "$" then name.*/
		if (strlen(flattened) == 0)
			strcpy (flattened, name);
		else
		{
			strcat (flattened, "$");
			strcat (flattened, name);
		}
		//if (ix) hejian del on 2010-11-11
		//{      /* Add 'ix' to flattened if necessary.	*/
		//	strcat (flattened, "[");
		//	strcat (flattened, ix);
		//	strcat (flattened, "]");
		//}
		retCode = SD_SUCCESS;
	}
	else
	{	/* flattened is big, so this error should never occur with normal SCL.*/
		SXLOG_ERR2 ("ERROR: not enough space to add name '%s' to flattened name '%s'", name, flattened);
		retCode = SD_FAILURE;
	}
	return (retCode);
}

/************************************************************************/
/*			scl_parse					*/
/************************************************************************/

ST_RET scl_parse (ST_CHAR *xmlFileName, SCL_INFO *sclInfo)
{
	ST_RET ret;
	SCL_DEC_CTRL sclDecCtrl = {0};	/* start with clean struct.	*/

	memset (sclInfo, 0, sizeof (SCL_INFO));    /* CRITICAL: start with clean struct*/

	sclDecCtrl.iedName = "";
	sclDecCtrl.accessPointName = "";
	sclDecCtrl.accessPointFound = SD_FALSE;
	sclDecCtrl.sclInfo = sclInfo;

	ret = sx_parseExx_mt (xmlFileName, 
		sizeof (sclStartElements)/sizeof(SX_ELEMENT), sclStartElements,
		&sclDecCtrl, _scl_unknown_el_start, _scl_unknown_el_end);

	/* NOTE: sx_parseEx_mt doesn't log error if file open fails, so log here*/
	/* It may not log some other errors, so log any other error here too.	*/
	if (ret == SX_FILE_NOT_FOUND)
		SXLOG_ERR1 ("XML File (%s) Open Error",xmlFileName);
	else if (ret != SD_SUCCESS)
		SXLOG_ERR2 ("Error 0x%X parsing SCL file (%s)", ret, xmlFileName);

	return (ret);
}

/************************************************************************/
/************************************************************************/
/*			SCL_SEFun					*/
/************************************************************************/

static ST_VOID _SCL_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
		sx_push (sxDecCtrl, sizeof(SCLElements)/sizeof(SX_ELEMENT), SCLElements, SD_FALSE);

	else
	{
		while (sxDecCtrl->itemStackLevel > 0)
			sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_Header_SFun					*/
/************************************************************************/

static ST_VOID _Header_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *nameStructure;
	ST_RET ret;
	SCL_INFO *sclInfo;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	sclInfo = sclDecCtrl->sclInfo;

	/* Get required attributes	*/

#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str(sxDecCtrl, "id", &sclInfo->Header.id, SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#else
	ret = scl_get_attr_copy (sxDecCtrl, "id", sclInfo->Header.id,
		(sizeof(sclInfo->Header.id)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#endif
	if (ret != SD_SUCCESS)
		return;	/* At least one required attr not found. Stop now.	*/

	/* Handle optional "nameStructure".	*/
	if (scl_get_attr_ptr (sxDecCtrl, "nameStructure", &nameStructure, SCL_ATTR_OPTIONAL) == SD_SUCCESS)
	{
		if (strcmp (nameStructure, "IEDName") != 0)
			SXLOG_ERR1 ("Header attribute nameStructure='%s' not allowed. Assuming nameStructure='IEDName' (i.e. 'Product Naming')", nameStructure);
	}
	/* Always assume nameStructure="IEDName" (i.e. "Product Naming")	*/
	sclInfo->Header.nameStructure = SCL_NAMESTRUCTURE_IEDNAME;
}

/************************************************************************/
/*			_Communication_SEFun				*/
/************************************************************************/
static ST_VOID _Communication_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sx_push (sxDecCtrl, sizeof(CommunicationElements)/sizeof(SX_ELEMENT), 
			CommunicationElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}
/************************************************************************/
/*			_SubNetwork_SEFun				*/
/************************************************************************/
static ST_VOID _SubNetwork_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_SUBNET *scl_subnet;
		scl_subnet = scl_subnet_add (sclDecCtrl->sclInfo);
		if (scl_subnet == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_subnet_add", SX_USER_ERROR);
			return;
		}
		/* Get required attributes.	*/

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_subnet->name, SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_subnet->name, (sizeof(scl_subnet->name)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#endif
		//if (ret)
		//{
		//	scl_stop_parsing (sxDecCtrl, "SubNetwork", SX_USER_ERROR);
		//	return;
		//}
		/* Get optional attributes.	*/
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_subnet->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
		ret = scl_get_attr_copy (sxDecCtrl, "type", scl_subnet->type, (sizeof(scl_subnet->type)-1), SCL_ATTR_OPTIONAL);

		sx_push (sxDecCtrl, sizeof(SubNetworkElements)/sizeof(SX_ELEMENT), 
			SubNetworkElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}
/************************************************************************/
/*			_ConnectedAP_SEFun				*/
/************************************************************************/
static ST_VOID _ConnectedAP_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_CAP *scl_cap;
		scl_cap = scl_cap_add (sclDecCtrl->sclInfo);
		if (scl_cap == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_cap_add", SX_USER_ERROR);
			return;
		}
		/* Get required attributes	*/
#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "iedName", (&scl_cap->iedName), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "apName", (&scl_cap->apName), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);

#else
		ret = scl_get_attr_copy (sxDecCtrl, "iedName", scl_cap->iedName, (sizeof(scl_cap->iedName)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
		ret |= scl_get_attr_copy (sxDecCtrl, "apName", scl_cap->apName, (sizeof(scl_cap->apName)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#endif
		//if (ret)
		//{
		//	scl_stop_parsing (sxDecCtrl, "ConnectedAP", SX_USER_ERROR);
		//	return;
		//}
		/* Get optional attributes.	*/
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_cap->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

		sx_push (sxDecCtrl, sizeof(ConnectedAPElements)/sizeof(SX_ELEMENT), 
			ConnectedAPElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}
/************************************************************************/
/*			_GSE_SEFun					*/
/************************************************************************/
static ST_VOID _GSE_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* NOTE: save ptr in sclDecCtrl->scl_gse to use later in parsing.	*/
		sclDecCtrl->scl_gse = scl_gse_add (sclDecCtrl->sclInfo);
		if (sclDecCtrl->scl_gse == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_gse_add", SX_USER_ERROR);
			return;
		}

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "ldInst", (&sclDecCtrl->scl_gse->ldInst) , SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);    
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "cbName", (&sclDecCtrl->scl_gse->cbName), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);  
#else
		ret = scl_get_attr_copy (sxDecCtrl, "ldInst", sclDecCtrl->scl_gse->ldInst , (sizeof(sclDecCtrl->scl_gse->ldInst)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);    
		ret |= scl_get_attr_copy (sxDecCtrl, "cbName", sclDecCtrl->scl_gse->cbName, (sizeof(sclDecCtrl->scl_gse->cbName)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);  
#endif
		//if (ret)
		//{
		//	scl_stop_parsing (sxDecCtrl, "GSE", SX_USER_ERROR);
		//	return;
		//}
		//else
			sx_push (sxDecCtrl, sizeof(GSEElements)/sizeof(SX_ELEMENT), 
			GSEElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}
/************************************************************************/
/*			_GSE_Address_SEFun				*/
/************************************************************************/
static ST_VOID _GSE_Address_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sx_push (sxDecCtrl, sizeof(GSEAddressElements)/sizeof(SX_ELEMENT), 
			GSEAddressElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}

static ST_VOID _Address_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
	//	/* NOTE: save ptr in sclDecCtrl->scl_gse to use later in parsing.	*/
	     sclDecCtrl->scl_address = scl_address_add(sclDecCtrl->sclInfo);
		if (sclDecCtrl->scl_address == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_address_add", SX_USER_ERROR);
			return;
		}
	//	//ret |= scl_get_attr_copy (sxDecCtrl, "IP", sclDecCtrl->scl_address->address_ip, (sizeof( sclDecCtrl->scl_address->address_ip)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
	//	//ret |= scl_get_attr_copy (sxDecCtrl, "IP-SUBNET",  sclDecCtrl->scl_address->address_ip_subnet, (sizeof( sclDecCtrl->scl_address->address_ip_subnet)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
	//	//ret |= scl_get_attr_copy (sxDecCtrl, "IP-ATEWAY",  sclDecCtrl->scl_address->address_ip_gateway, (sizeof(  sclDecCtrl->scl_address->address_ip_gateway)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/); 

	//	sx_push (sxDecCtrl, sizeof(ConnectedAPElements)/sizeof(SX_ELEMENT), 
	//		ConnectedAPElements, SD_FALSE);
			sx_push (sxDecCtrl, sizeof(AddressElements)/sizeof(SX_ELEMENT), 
				AddressElements, SD_FALSE);
	}


	//if (sxDecCtrl->reason == SX_ELEMENT_START)
	//{
	//	sx_push (sxDecCtrl, sizeof(AddressElements)/sizeof(SX_ELEMENT), 
	//		AddressElements, SD_FALSE);
	//}
	else
	{
		sx_pop (sxDecCtrl);
	}
}


static ST_VOID _Address_P_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_CHAR *str;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *strOut;
	ST_INT strLen;

	if (sxDecCtrl->reason == SX_ELEMENT_END)
	{
		ret = scl_get_attr_ptr (sxDecCtrl, "type", &str, required);
	
		 if (!strcmpi(str,"IP"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{	
#ifdef SCL_USE_MMS_STRING_
				mms_str_set(&sclDecCtrl->scl_address->address_ip,strOut);
#else
				strcpy(sclDecCtrl->scl_address->address_ip,strOut);
#endif

			}
		}

		 else if (!strcmpi(str,"IP-SUBNET"))
		 {
			 ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			 if (ret == SD_SUCCESS)
			 {		       
#ifdef SCL_USE_MMS_STRING_				 
				 mms_str_set(&sclDecCtrl->scl_address->address_ip_subnet,strOut);
#else
				 strcpy(sclDecCtrl->scl_address->address_ip_subnet,strOut);
#endif
			 }
		 }

		 else if (!strcmpi(str,"IP-GATEWAY"))
		 {
			 ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			 if (ret == SD_SUCCESS)
			 {		       
#ifdef SCL_USE_MMS_STRING_				 
				 mms_str_set(&sclDecCtrl->scl_address->address_ip_gateway,strOut);
#else
				 strcpy(sclDecCtrl->scl_address->address_ip_gateway,strOut);
#endif
			 }
		 }
	}
}
/************************************************************************/
/*			_GSE_MinTime_SEFun		hejian add on 2010-7-28		*/
/************************************************************************/
static ST_VOID _GSE_MinTime_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *strOut;
	ST_INT strLen;

	if (sxDecCtrl->reason == SX_ELEMENT_END)
	{
		ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
		if (ret == SD_SUCCESS)
		{
			sclDecCtrl->scl_gse->MinTime = atoi(strOut);
		}
	}
}
/************************************************************************/
/*			_GSE_MaxTime_SEFun		hejian add on 2010-7-28				*/
/************************************************************************/
static ST_VOID _GSE_MaxTime_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *strOut;
	ST_INT strLen;

	if (sxDecCtrl->reason == SX_ELEMENT_END)
	{
		ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
		if (ret == SD_SUCCESS)
		{
			sclDecCtrl->scl_gse->MaxTime = atoi(strOut);
		}
	}
}
/************************************************************************/
/*			_GSE_Address_P_SEFun				*/
/************************************************************************/
static ST_VOID _GSE_Address_P_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_CHAR *str;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *strOut;
	ST_INT strLen;

	if (sxDecCtrl->reason == SX_ELEMENT_END)
	{
		ret = scl_get_attr_ptr (sxDecCtrl, "type", &str, required);
		if (!strcmpi(str,"MAC-Address"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{
				if (convert_mac (sclDecCtrl->scl_gse->MAC,strOut))
				{
					SXLOG_ERR1 ("Illegal MAC Address '%s'", strOut);
					scl_stop_parsing (sxDecCtrl, "_GSE_Address_P_SEFun", SX_USER_ERROR);
				}
			}
		}
		else if (!strcmpi(str,"VLAN-ID"))
		{//hejian add on 2010-7-28
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{
				sclDecCtrl->scl_gse->VLANID = atoi(strOut);
			}
		}
		else if (!strcmpi(str,"APPID"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{//hejian alter on 2010-9-4
				sclDecCtrl->scl_gse->APPID = _hex_to_uint(strOut);//atoi(strOut);  //lijq - 2014/10/27
			}
		}
		else if (!strcmpi(str,"VLAN-PRIORITY"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
				sclDecCtrl->scl_gse->VLANPRI = atoi(strOut);
		}
	}
}
/************************************************************************/
/*			_SMV_SEFun					*/
/************************************************************************/
static ST_VOID _SMV_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* NOTE: save ptr in sclDecCtrl->scl_smv to use later in parsing.	*/
		sclDecCtrl->scl_smv = scl_smv_add (sclDecCtrl->sclInfo);
		if (sclDecCtrl->scl_smv == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_smv_add", SX_USER_ERROR);
			return;
		}

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "ldInst", (&sclDecCtrl->scl_smv->ldInst), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);    
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "cbName", (&sclDecCtrl->scl_smv->cbName), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);  
#else
		ret = scl_get_attr_copy (sxDecCtrl, "ldInst", sclDecCtrl->scl_smv->ldInst, (sizeof(sclDecCtrl->scl_smv->ldInst)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);    
		ret |= scl_get_attr_copy (sxDecCtrl, "cbName", sclDecCtrl->scl_smv->cbName, (sizeof(sclDecCtrl->scl_smv->cbName)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);  
#endif

		//if (ret)
		//{
		//	scl_stop_parsing (sxDecCtrl, "SMV", SX_USER_ERROR);
		//	return;
		//}
		//else
			sx_push (sxDecCtrl, sizeof(SMVElements)/sizeof(SX_ELEMENT), 
			SMVElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}
/************************************************************************/
/*			_SMV_Address_SEFun				*/
/************************************************************************/
static ST_VOID _SMV_Address_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sx_push (sxDecCtrl, sizeof(SMVAddressElements)/sizeof(SX_ELEMENT), 
			SMVAddressElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}
/************************************************************************/
/*			_SMV_Address_P_SEFun				*/
/************************************************************************/
static ST_VOID _SMV_Address_P_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_CHAR *str;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *strOut;
	ST_INT strLen;

	if (sxDecCtrl->reason == SX_ELEMENT_END)
	{
		ret = scl_get_attr_ptr (sxDecCtrl, "type", &str, required);
		if (!strcmpi(str,"MAC-Address"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{
				if (convert_mac (sclDecCtrl->scl_smv->MAC,strOut))
				{
					SXLOG_ERR1 ("Illegal MAC Address '%s'", strOut);
					scl_stop_parsing (sxDecCtrl, "_SMV_Address_P_SEFun", SX_USER_ERROR);
				}
			}
		}
		else if (!strcmpi(str,"VLAN-ID"))
		{//hejian add on 2010-7-28
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{
				//sclDecCtrl->scl_gse->VLANID = atoi(strOut);
				sclDecCtrl->scl_smv->VLANID = atoi(strOut);  //lijq  2014-10-23
			}
		}
		else if (!strcmpi(str,"APPID"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
			{
				//sclDecCtrl->scl_gse->APPID = atoi(strOut);
				sclDecCtrl->scl_smv->APPID = _hex_to_uint(strOut);//lijq - 2014/10/27   atoi(strOut);//lijq  2014-10-23
			}
		}
		else if (!strcmpi(str,"VLAN-PRIORITY"))
		{
			ret = sx_get_string_ptr (sxDecCtrl, &strOut, &strLen);
			if (ret == SD_SUCCESS)
				sclDecCtrl->scl_smv->VLANPRI = atoi(strOut);
		}
	}
}
/************************************************************************/
/*			IED_SEFun					*/
/************************************************************************/

static ST_VOID _IED_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	SCL_IED *scl_ied;
	ST_CHAR *desc;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		scl_ied  = scl_ied_create (sclDecCtrl->sclInfo);
		if (scl_ied == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_ied_create", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		required = SD_FALSE;
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_ied->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
		/* end optional attributes */		

#ifdef SCL_USE_MMS_STRING_
		scl_get_attr_copy_mms_str (sxDecCtrl, "type", &scl_ied->type, required);
		scl_get_attr_copy_mms_str (sxDecCtrl, "configVersion", &scl_ied->configVersion,  required);
		scl_get_attr_copy_mms_str (sxDecCtrl, "manufacturer", &scl_ied->manufacturer, required);
		//required = SD_TRUE;
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_ied->name, required);
#else
		scl_get_attr_copy (sxDecCtrl, "type", scl_ied->type, (sizeof(scl_ied->type)-1), required);
		scl_get_attr_copy (sxDecCtrl, "configVersion", scl_ied->configVersion, (sizeof(scl_ied->configVersion)-1), required);
		scl_get_attr_copy (sxDecCtrl, "manufacturer", scl_ied->manufacturer, (sizeof(scl_ied->manufacturer)-1), required);
		//required = SD_TRUE;
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_ied->name, (sizeof(scl_ied->name)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//	return;	/* At least one required attr not found. Stop now.	*/

		sx_push (sxDecCtrl, sizeof(IEDElements)/sizeof(SX_ELEMENT), IEDElements, SD_FALSE);

		//hejian del on 2010-11-5
		//if (strcmp(str, sclDecCtrl->iedName) == 0)
		//{
		//	SXLOG_CDEC1 ("SCL PARSE: IED 'name' match found: %s", str);
		//	sclDecCtrl->iedNameMatched = SD_TRUE;
		//	sx_push (sxDecCtrl, sizeof(IEDElements)/sizeof(SX_ELEMENT), IEDElements, SD_FALSE);
		//}
		//else
		//{
		//	SXLOG_CDEC1 ("SCL PARSE: IED 'name' found (%s), not a match", str);
		//}
		/* end required attributes */
	}
	else
	{
		//if (sclDecCtrl->iedNameMatched == SD_TRUE)
		//{
		//	sclDecCtrl->iedNameMatched = SD_FALSE;
		//	sx_pop (sxDecCtrl);
		//}

		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_AccessPoint_SEFun				*/
/************************************************************************/

static ST_VOID _AccessPoint_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	SCL_AP *scl_ap;
	ST_CHAR *desc;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		scl_ap = scl_ap_create (sclDecCtrl->sclInfo);
		if (scl_ap == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_ap_create", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		required = SD_FALSE;
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_ap->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;
#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_ap->name, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_ap->name, (sizeof(scl_ap->name)-1), required);
#endif
		//if (ret != SD_SUCCESS)
		//	return;	/* At least one required attr not found. Stop now.	*/
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(AccessPointElements)/sizeof(SX_ELEMENT), AccessPointElements, SD_FALSE);

		//hejian del on 2010-11-5
		//if (strcmp(str, sclDecCtrl->accessPointName) == 0)
		//{
		//	SXLOG_CDEC1 ("SCL PARSE: AccessPoint 'name' match found: %s", str);
		//	sclDecCtrl->accessPointFound = SD_TRUE;	/*NOTE: only get here if IED also found*/
		//	sclDecCtrl->accessPointMatched = SD_TRUE;
		//	sx_push (sxDecCtrl, sizeof(AccessPointElements)/sizeof(SX_ELEMENT), AccessPointElements, SD_FALSE);
		//}
		//else
		//{
		//	SXLOG_CDEC1 ("SCL PARSE: AccessPoint 'name' found (%s), not a match", str);
		//}
		/* end required attributes */
	}
	else
	{
		//if (sclDecCtrl->accessPointMatched == SD_TRUE)
		//{
		//	sclDecCtrl->accessPointMatched = SD_FALSE;
		//	sx_pop (sxDecCtrl);
		//}

		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_Server_SEFun					*/
/************************************************************************/

static ST_VOID _Server_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sx_push (sxDecCtrl, sizeof(ServerElements)/sizeof(SX_ELEMENT), ServerElements, SD_FALSE);
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_LDevice_SEFun					*/
/************************************************************************/
static ST_VOID _LDevice_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_INFO *scl_info;
	SCL_LD *scl_ld;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_ld = sclDecCtrl->scl_ld = scl_ld_create (sclDecCtrl->sclInfo);
		if (scl_ld == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_ld_create", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_ld->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "inst", (&scl_ld->inst), required);
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "ldName", (&scl_ld->ldName), required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "inst", scl_ld->inst, (sizeof(scl_ld->inst)-1), required);
		ret = scl_get_attr_copy (sxDecCtrl, "ldName", scl_ld->ldName, (sizeof(scl_ld->ldName)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//	return;	/* At least one required attr not found. Stop now.	*/
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(LDeviceElements)/sizeof(SX_ELEMENT), LDeviceElements, SD_FALSE);
	}
	else
	{		/* reason == SX_ELEMENT_END	*/
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		scl_info = sclDecCtrl->sclInfo;
		scl_ld = sclDecCtrl->scl_ld;
		/* Construct MMS Domain name from scl info.	*/
		/* ASSUME nameStructure="IEDName" (domain name = IED name + LDevice inst)*/
		/* nameStructure="FuncName" is OBSOLETE.				*/

		//hejian del on 2010-11-5
		//if (strlen(scl_info->iedName) + strlen(scl_ld->inst) <= MAX_IDENT_LEN)
		//{
		//	strcpy (scl_ld->domName, scl_info->iedName);	/* construct domain name*/
		//	strcat (scl_ld->domName, scl_ld->inst);
		//}
		//else
		//{
		//	SXLOG_ERR0 ("Cannot create LD: constructed domain name too long");
		//	scl_stop_parsing (sxDecCtrl, "_LDevice_SEFun", SX_USER_ERROR);
		//}
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_LN_SEFun					*/
/************************************************************************/

static ST_VOID _LN_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_LN *scl_ln;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_ln = sclDecCtrl->scl_ln = scl_ln_add (sclDecCtrl->sclInfo);
		if (scl_ln == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_ln_add", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_ln->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "prefix", (&scl_ln->prefix), required);
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "lnType", (&scl_ln->lnType), required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "inst", (&scl_ln->inst), required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "lnClass", (&scl_ln->lnClass), required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "prefix", scl_ln->prefix, (sizeof(scl_ln->prefix)-1), required);
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;
		ret = scl_get_attr_copy (sxDecCtrl, "lnType", scl_ln->lnType, (sizeof(scl_ln->lnType)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "inst", scl_ln->inst, (sizeof(scl_ln->inst)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "lnClass", scl_ln->lnClass, (sizeof(scl_ln->lnClass)-1), required);
#endif

		//hejian alter on 2010-9-29
		/*if (ret != SD_SUCCESS)
		return;*/

		if (stricmp(sxDecCtrl->sxDecElInfo.tag, "LN0") == 0 

#ifdef SCL_USE_MMS_STRING_
			&& stricmp(mms_string(&scl_ln->lnClass), "LLN0") != 0)
#else
			&& stricmp(scl_ln->lnClass, "LLN0") != 0)
#endif

		{
			//hejian alter on 2010-9-29
			sxDecCtrl->errCode = SD_SUCCESS;
			sxDecCtrl->termFlag = SD_FALSE;

#ifdef SCL_USE_MMS_STRING_
			mms_str_set(&scl_ln->lnClass, "LLN0");
#else
			strcpy(scl_ln->lnClass, "LLN0");
#endif

			//sxDecCtrl->errCode = SX_USER_ERROR;
			//sxDecCtrl->termFlag = SD_TRUE;
			// SXLOG_ERR0 ("SCL PARSE: Attribute 'lnClass' of element 'LN0' has a value other then 'LLN0' (schema violation).");
			//	  return;
		}
		/* end required attributes */

		if (stricmp(sxDecCtrl->sxDecElInfo.tag, "LN0") == 0)
			sx_push (sxDecCtrl, sizeof(LN0Elements)/sizeof(SX_ELEMENT), LN0Elements, SD_FALSE);
		else
			sx_push (sxDecCtrl, sizeof(LNElements)/sizeof(SX_ELEMENT), LNElements, SD_FALSE);
	}
	else
	{		/* reason == SX_ELEMENT_END	*/
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		scl_ln = sclDecCtrl->scl_ln;
		/* Construct MMS Variable name from scl info.	*/

#ifdef SCL_USE_MMS_STRING_
//		if (mms_str_length(&scl_ln->prefix) + mms_str_length(&scl_ln->lnClass) + mms_str_length(&scl_ln->inst) <= MAX_IDENT_LEN)
		{
			mms_str_set(&scl_ln->varName, mms_string(&scl_ln->prefix));
			mms_str_cat(&scl_ln->varName, mms_string(&scl_ln->lnClass));
			mms_str_cat(&scl_ln->varName, mms_string(&scl_ln->inst));
		}
#else
		if (strlen(scl_ln->prefix) + strlen(scl_ln->lnClass) + strlen(scl_ln->inst) <= MAX_IDENT_LEN)
		{
			strcpy (scl_ln->varName, scl_ln->prefix);
			strcat (scl_ln->varName, scl_ln->lnClass);
			strcat (scl_ln->varName, scl_ln->inst);
		}
		else
		{
			SXLOG_ERR0 ("Cannot add LN: constructed variable name too long");
			scl_stop_parsing (sxDecCtrl, "_LN_SEFun", SX_USER_ERROR);
		}
#endif
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_DataSet_SEFun					*/
/************************************************************************/

static ST_VOID _DataSet_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_DATASET *scl_dataset;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_dataset = scl_dataset_add (sclDecCtrl->sclInfo);
		if (scl_dataset == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_dataset_add", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_dataset->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;
#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", (&scl_dataset->name), required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_dataset->name, (sizeof(scl_dataset->name)-1), required);
#endif
		//if (ret != SD_SUCCESS)
		//	return;
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(DataSetElements)/sizeof(SX_ELEMENT), DataSetElements, SD_FALSE);
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_FCDA_SFun					*/
/************************************************************************/

static ST_VOID _FCDA_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_INFO *scl_info;
	SCL_FCDA *scl_fcda;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	scl_info = sclDecCtrl->sclInfo;

	scl_fcda = scl_fcda_add (scl_info);
	if (scl_fcda == NULL)
	{
		scl_stop_parsing (sxDecCtrl, "scl_fcda_add", SX_USER_ERROR);
		return;
	}

	/* start optional attributes */

#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "ldInst",  (&scl_fcda->ldInst),  required);
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "prefix",  (&scl_fcda->prefix),  required);
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "lnInst",  (&scl_fcda->lnInst),  required);
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "lnClass", (&scl_fcda->lnClass), required);
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "doName",  (&scl_fcda->doName),  required);
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "daName",  (&scl_fcda->daName),  required);
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "fc", (&scl_fcda->fc), required);
#else
	ret = scl_get_attr_copy (sxDecCtrl, "ldInst",  scl_fcda->ldInst,  (sizeof(scl_fcda->ldInst)-1), required);
	ret = scl_get_attr_copy (sxDecCtrl, "prefix",  scl_fcda->prefix,  (sizeof(scl_fcda->prefix)-1), required);
	ret = scl_get_attr_copy (sxDecCtrl, "lnInst",  scl_fcda->lnInst,  (sizeof(scl_fcda->lnInst)-1), required);
	ret = scl_get_attr_copy (sxDecCtrl, "lnClass", scl_fcda->lnClass, (sizeof(scl_fcda->lnClass)-1), required);
	ret = scl_get_attr_copy (sxDecCtrl, "doName",  scl_fcda->doName,  (sizeof(scl_fcda->doName)-1), required);
	ret = scl_get_attr_copy (sxDecCtrl, "daName",  scl_fcda->daName,  (sizeof(scl_fcda->daName)-1), required);

	/* end optional attributes */

	/* start required attributes */
	//required = SD_TRUE;
	ret = scl_get_attr_copy (sxDecCtrl, "fc", scl_fcda->fc, (sizeof(scl_fcda->fc)-1), required);
#endif
	//if (ret != SD_SUCCESS)
	//	return;
	/* end required attributes */

	/* Construct domain name from SCL info	*/
	/* ASSUME nameStructure="IEDName" (domain name = IED name + LDevice inst)*/
	/* nameStructure="FuncName" is OBSOLETE.*/
	
	//hejian del on 2010-11-5
	//if (strlen(scl_info->iedName) + strlen(scl_fcda->ldInst) <= MAX_IDENT_LEN)
	//{
	//	strcpy (scl_fcda->domName, scl_info->iedName);
	//	strcat (scl_fcda->domName, scl_fcda->ldInst);
	//}
	//else
	//{
	//	SXLOG_ERR0 ("Cannot add FCDA: constructed domain name too long");
	//	scl_stop_parsing (sxDecCtrl, "_FCDA_SFun", SX_USER_ERROR);
	//}
}

/************************************************************************/
/*			_ReportControl_SEFun				*/
/************************************************************************/

static ST_VOID _ReportControl_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *str;	/* ptr set by scl_get_attr_ptr	*/
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *desc;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* Alloc struct, save ptr in sclDecCtrl, & set local ptr to it.	*/
		SCL_RCB *scl_rcb = sclDecCtrl->scl_rcb = scl_rcb_add (sclDecCtrl->sclInfo);
		if (scl_rcb == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_rcb_add", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_rcb->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "datSet", (&scl_rcb->datSet),  required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "datSet", scl_rcb->datSet, (sizeof(scl_rcb->datSet)-1), required);
#endif

		ret = scl_get_uint_attr (sxDecCtrl, "intgPd", &scl_rcb->intgPd, required);
		ret = scl_get_uint_attr (sxDecCtrl, "bufTime", &scl_rcb->bufTime, required);
		ret = scl_get_attr_ptr (sxDecCtrl, "buffered", &str, required);

		scl_rcb->buffered = SD_FALSE;  /* default */
		if (ret == SD_SUCCESS)
		{
			if (stricmp(str, "true") == 0)
				scl_rcb->buffered = SD_TRUE;
		}
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", (&scl_rcb->name),  required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "rptID", (&scl_rcb->rptID),  required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_rcb->name, (sizeof(scl_rcb->name)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "rptID", scl_rcb->rptID, (sizeof(scl_rcb->rptID)-1), required);
#endif

		ret |= scl_get_uint_attr (sxDecCtrl, "confRev", &scl_rcb->confRev, required);
		//if (ret != SD_SUCCESS)
		//	return;
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(ReportControlElements)/sizeof(SX_ELEMENT), ReportControlElements, SD_FALSE);
	}
	else /* reason = SX_ELEMENT_END */
	{
		/* CRITICAL: Copy TrgOps to scl_rcb.	*/
		sclDecCtrl->scl_rcb->TrgOps[0] = sclDecCtrl->TrgOps[0];
		/* If "RptEnabled max" not configured, set default value*/
		if (sclDecCtrl->scl_rcb->maxClient == 0)
			sclDecCtrl->scl_rcb->maxClient = 1;	/* default	*/
		/* NOTE: scl_rcb is all filled in now	*/
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_LogControl_SEFun				*/
/************************************************************************/

static ST_VOID _LogControl_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *str;	/* ptr set by scl_get_attr_ptr	*/
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *desc;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* Alloc struct, save ptr in sclDecCtrl, & set local ptr to it.	*/
		SCL_LCB *scl_lcb = sclDecCtrl->scl_lcb = scl_lcb_add (sclDecCtrl->sclInfo);
		if (scl_lcb == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_lcb_add", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_lcb->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
		ret = scl_get_uint_attr (sxDecCtrl, "intgPd", &scl_lcb->intgPd, required);
		ret = scl_get_attr_ptr (sxDecCtrl, "logEna", &str, required);
		scl_lcb->logEna = SD_FALSE;  /* default */
		if (ret == SD_SUCCESS)
		{
			if (stricmp(str, "true") == 0)
				scl_lcb->logEna = SD_TRUE;
		}
		else//zhouhj 20181206 将默认值置为true
		{
			scl_lcb->logEna = SD_TRUE;
		}

		ret = scl_get_attr_ptr (sxDecCtrl, "reasonCode", &str, required);
		scl_lcb->reasonCode = SD_FALSE;  /* default */
		if (ret == SD_SUCCESS)
		{
			if (stricmp(str, "true") == 0)
				scl_lcb->reasonCode = SD_TRUE;
		}
		else//zhouhj 20181206 将默认值置为true
		{
			scl_lcb->reasonCode = SD_TRUE;
		}
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", (&scl_lcb->name), required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "datSet", (&scl_lcb->datSet), required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "logName", (&scl_lcb->logName), required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_lcb->name, (sizeof(scl_lcb->name)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "datSet", scl_lcb->datSet, (sizeof(scl_lcb->datSet)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "logName", scl_lcb->logName, (sizeof(scl_lcb->logName)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//	return;
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(LogControlElements)/sizeof(SX_ELEMENT), LogControlElements, SD_FALSE);
	}
	else /* reason = SX_ELEMENT_END */
	{
		/* CRITICAL: Copy TrgOps to scl_lcb.	*/
		sclDecCtrl->scl_lcb->TrgOps[0] = sclDecCtrl->TrgOps[0];
		/* NOTE: scl_lcb is all filled in now	*/
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_SettingControl_SFun				*/
/************************************************************************/

static ST_VOID _SettingControl_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* Alloc struct, save ptr in sclDecCtrl, & set local ptr to it.	*/
		SCL_SGCB *scl_sgcb = sclDecCtrl->scl_sgcb = scl_sgcb_add (sclDecCtrl->sclInfo);
		if (scl_sgcb == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_sgcb_add", SX_USER_ERROR);
			return;
		}

		ret = scl_get_uint_attr (sxDecCtrl, "numOfSGs", &scl_sgcb->numOfSGs, required);
		ret = scl_get_uint_attr (sxDecCtrl, "actSG", &scl_sgcb->actSG, required);
	}
	else /* reason = SX_ELEMENT_END */
	{
		/* NOTE: scl_lcb is all filled in now	*/
//		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_GSEControl_SFun				*/ 
/************************************************************************/

static ST_VOID _GSEControl_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	ST_CHAR *type;	/* ptr set by scl_get_attr_ptr	*/
	SCL_GCB *scl_gcb;
	ST_CHAR *desc;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	scl_gcb = scl_gcb_add (sclDecCtrl->sclInfo);
	if (scl_gcb == NULL)
	{
		scl_stop_parsing (sxDecCtrl, "scl_gcb_add", SX_USER_ERROR);
		return;
	}

	/* start optional attributes */
	ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
	if (ret == SD_SUCCESS)
		scl_gcb->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
	ret = scl_get_uint_attr (sxDecCtrl, "confRev", &scl_gcb->confRev, required);
	ret = scl_get_attr_ptr (sxDecCtrl, "type", &type, required);
	if (ret == SD_SUCCESS && strcmp(type, "GSSE") == 0)
		scl_gcb->isGoose = SD_FALSE;
	else
		scl_gcb->isGoose = SD_TRUE;
	/* end optional attributes */

	/* start required attributes */
	//required = SD_TRUE;
#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str  (sxDecCtrl, "name",   (&scl_gcb->name),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "datSet", (&scl_gcb->datSet),required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "appID",  (&scl_gcb->appID), required);
#else
	ret = scl_get_attr_copy  (sxDecCtrl, "name",   scl_gcb->name,   (sizeof(scl_gcb->name)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "datSet", scl_gcb->datSet, (sizeof(scl_gcb->datSet)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "appID",  scl_gcb->appID,  (sizeof(scl_gcb->appID)-1), required);
#endif

	//if (ret != SD_SUCCESS)
	//	return;
	/* end required attributes */
}

/************************************************************************/
/*			_Inputs_SFun	hejian add on 2010-11-2			*/
/************************************************************************/

static ST_VOID _Inputs_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	SCL_INPUTS *scl_inputs;
	ST_CHAR *desc;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		scl_inputs = scl_inputs_add (sclDecCtrl->sclInfo);
		if (scl_inputs == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_inputs_add", SX_USER_ERROR);
			return;
		}

		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_inputs->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

#ifdef SCL_USE_MMS_STRING_
		scl_get_attr_copy_mms_str (sxDecCtrl, "name", (&scl_inputs->name), required);
#else
		scl_get_attr_copy (sxDecCtrl, "name", scl_inputs->name, (sizeof(scl_inputs->name)-1), required);
#endif

		sx_push (sxDecCtrl, sizeof(INPUTSElements)/sizeof(SX_ELEMENT), INPUTSElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_ExtRef_SFun	hejian add on 2010-11-2			*/
/************************************************************************/

static ST_VOID _ExtRef_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	SCL_EXTREF *scl_extref;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	scl_extref = scl_extref_add (sclDecCtrl->sclInfo);
	if (scl_extref == NULL)
	{
		scl_stop_parsing (sxDecCtrl, "scl_extref_add", SX_USER_ERROR);
		return;
	}

#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str  (sxDecCtrl, "prefix",  (&scl_extref->prefix),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "intAddr", (&scl_extref->inAddr),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "doName",  (&scl_extref->doName),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "lnInst",  (&scl_extref->lnInst),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "iedName", (&scl_extref->domName), required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "daName",  (&scl_extref->daName),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "ldInst",  (&scl_extref->ldInst),  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "lnClass", (&scl_extref->lnClass), required);
#else
	ret = scl_get_attr_copy  (sxDecCtrl, "prefix",  scl_extref->prefix,  (sizeof(scl_extref->prefix)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "intAddr", scl_extref->inAddr,  (sizeof(scl_extref->inAddr)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "doName",  scl_extref->doName,  (sizeof(scl_extref->doName)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "lnInst",  scl_extref->lnInst,  (sizeof(scl_extref->lnInst)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "iedName", scl_extref->domName, (sizeof(scl_extref->domName)-1),required);
	ret |= scl_get_attr_copy (sxDecCtrl, "daName",  scl_extref->daName,  (sizeof(scl_extref->daName)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "ldInst",  scl_extref->ldInst,  (sizeof(scl_extref->ldInst)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "lnClass", scl_extref->lnClass, (sizeof(scl_extref->lnClass)-1),required);
#endif

	//if (ret != SD_SUCCESS)
	//	return;
}

/************************************************************************/
/*			_TrgOps_SFun					*/
/* Save all TrgOps bits in sclDecCtrl->TrgOps.				*/
/************************************************************************/

static ST_VOID _TrgOps_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *str;	/* ptr set by scl_get_attr_ptr	*/
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	sclDecCtrl->TrgOps[0] = 0;	/* Start with all bits=0	*/

	/* start optional attributes */
	ret = scl_get_attr_ptr (sxDecCtrl, "dchg", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(sclDecCtrl->TrgOps, TRGOPS_BITNUM_DATA_CHANGE);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "qchg", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(sclDecCtrl->TrgOps, TRGOPS_BITNUM_QUALITY_CHANGE);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "dupd", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(sclDecCtrl->TrgOps, TRGOPS_BITNUM_DATA_UPDATE);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "period", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(sclDecCtrl->TrgOps, TRGOPS_BITNUM_INTEGRITY);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "gi", &str, required);//zhouhj 按开源库的方式增加
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(sclDecCtrl->TrgOps, TRGOPS_BITNUM_GENERAL_INTERROGATION);
		}
	}
	else
	{
		BSTR_BIT_SET_ON(sclDecCtrl->TrgOps, TRGOPS_BITNUM_GENERAL_INTERROGATION);
	}
	/* end optional attributes */
}

/************************************************************************/
/*			_OptFlds_SFun					*/
/* Save all OptFlds bits in sclDecCtrl->scl_rcb->OptFlds.		*/
/************************************************************************/

static ST_VOID _OptFlds_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *str;	/* ptr set by scl_get_attr_ptr	*/
	ST_RET ret;
	SCL_RCB *scl_rcb;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	scl_rcb = sclDecCtrl->scl_rcb;

	/* start optional attributes */
	ret = scl_get_attr_ptr (sxDecCtrl, "seqNum", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_SQNUM);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "timeStamp", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_TIMESTAMP);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "dataSet", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_DATSETNAME);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "reasonCode", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_REASON);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "dataRef", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_DATAREF);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "bufOvfl", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_BUFOVFL);
		}
	}
	else//zhouhj 20181206按照开源库增加
	{
		BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_BUFOVFL);
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "entryID", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_ENTRYID);
		}
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "configRef", &str, required);
	if (ret == SD_SUCCESS)
	{
		if (stricmp(str, "true") == 0)
		{
			BSTR_BIT_SET_ON(scl_rcb->OptFlds, OPTFLD_BITNUM_CONFREV);
		}
	}
	/* end optional attributes */
}

/************************************************************************/
/*			_RptEnabled_SFun				*/
/* Save RptEnabled info in sclDecCtrl->scl_rcb.				*/
/************************************************************************/
static ST_VOID _RptEnabled_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;
	SCL_RCB *scl_rcb;

	assert (sxDecCtrl->reason == SX_ELEMENT_START);
	scl_rcb = sclDecCtrl->scl_rcb;

	/* start optional attributes */
	ret = scl_get_uint_attr (sxDecCtrl, "max", &scl_rcb->maxClient, SCL_ATTR_OPTIONAL);
	/* If configured, check for legal value.	*/
	if (ret == SD_SUCCESS)
	{
		if (scl_rcb->maxClient <= 0 || scl_rcb->maxClient > 99)
		{
			SXLOG_ERR1 ("RptEnabled max=%d is not valid. Must be value between 1 and 99", scl_rcb->maxClient);
			scl_stop_parsing (sxDecCtrl, "RptEnabled", SX_USER_ERROR);
			scl_rcb->maxClient = 1;	/* set to default just in case user ignores error*/
		}
	}
}

/************************************************************************/
/*			_DOI_SEFun					*/
/************************************************************************/

static ST_VOID _DOI_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *ix;
	ST_CHAR *name;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_DAI *scl_dai;
	ST_CHAR *desc;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* start required attributes */
		//required = SD_TRUE;
		ret = scl_get_attr_ptr (sxDecCtrl, "name", &name, required);
		if (ret != SD_SUCCESS)
		{
			return;
		}
		/* end required attributes */

		/* start optional attributes */
		required = SD_FALSE;
		//hejian add on 2010-12-6  add doi desc to dai
		if ((scl_dai = scl_dai_add (sclDecCtrl->sclInfo)) != NULL)
		{
#ifdef SCL_USE_MMS_STRING_
			mms_str_set(&scl_dai->flattened, name);
			mms_str_cat(&scl_dai->flattened, "$desc");
#else
			strcpy(scl_dai->flattened, name);
			strcat(scl_dai->flattened, "$desc");
#endif

			ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
			if (ret == SD_SUCCESS)
			{
				scl_dai->Val = chk_strdup (desc);	/* alloc & store Val*/
			}	
		}

		ret = scl_get_attr_ptr (sxDecCtrl, "ix", &ix, required);
		if (ret)
			ix = NULL;
		/* end optional attributes */

		/* Start creation of flattened name */
		sclDecCtrl->flattened[0] = '\0';	/* CRITICAL: start with empty flatname*/
		if (construct_flattened (sclDecCtrl->flattened, sizeof(sclDecCtrl->flattened), name, ix)
			!= SD_SUCCESS)
		{	/* error already logged.	*/
			scl_stop_parsing (sxDecCtrl, "_DOI_SEFun", SX_USER_ERROR);
			return;
		}

		SXLOG_CDEC1 ("SCL PARSE: Created flattened variable: '%s'", sclDecCtrl->flattened);

		sx_push (sxDecCtrl, sizeof(DOIElements)/sizeof(SX_ELEMENT), DOIElements, SD_FALSE);    
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_SDI_SEFun					*/
/************************************************************************/

static ST_VOID _SDI_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *ix;
	ST_CHAR *name;
	ST_RET ret;
	ST_CHAR *p;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "ix", &ix, required);
		if (ret)
			ix = NULL;
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;
		ret = scl_get_attr_ptr (sxDecCtrl, "name", &name, required);
		if (ret != SD_SUCCESS)
		{
			return;
		}
		/* end required attributes */

		/* Continue creation of flattened name */
		if (construct_flattened (sclDecCtrl->flattened, sizeof(sclDecCtrl->flattened), name, ix)
			!= SD_SUCCESS)
		{	/* error already logged.	*/
			scl_stop_parsing (sxDecCtrl, "_SDI_SEFun", SX_USER_ERROR);
			return;
		}

		SXLOG_CDEC1 ("SCL PARSE: Appended to flattened variable: '%s'", sclDecCtrl->flattened);

		sx_push (sxDecCtrl, sizeof(SDIElements)/sizeof(SX_ELEMENT), SDIElements, SD_FALSE);    
	}
	else /* reason = SX_ELEMENT_END */
	{
		/* Remove the last item from the flattened string */
		p = strrchr(sclDecCtrl->flattened, '$');
		if (p != NULL)
			*p = 0;
		SXLOG_CDEC1 ("SCL PARSE: Removed last item from flattened variable: '%s'", sclDecCtrl->flattened);
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_DAI_SEFun					*/
/************************************************************************/

static ST_VOID _DAI_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *ix;
	ST_CHAR *name;
	ST_RET ret;
	ST_CHAR *p;
	ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_DAI *scl_dai;
		if ((scl_dai = sclDecCtrl->scl_dai = scl_dai_add (sclDecCtrl->sclInfo)) == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_enumtype_create", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "ix", &ix, required);
		if (ret)
			ix = NULL;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "sAddr", (&scl_dai->sAddr), required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "sAddr", scl_dai->sAddr, (sizeof(scl_dai->sAddr)-1), required);
#endif

		ret = scl_get_attr_copy (sxDecCtrl, "valKind", scl_dai->valKind, (sizeof(scl_dai->valKind)-1), required);
		if (ret)
			strcpy (scl_dai->valKind, "Set"); /* default */
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;
		ret = scl_get_attr_ptr (sxDecCtrl, "name", &name, required);
		if (ret != SD_SUCCESS)
		{
			return;
		}
		/* end required attributes */

		/* Continue creation of flattened name */
		if (construct_flattened (sclDecCtrl->flattened, sizeof(sclDecCtrl->flattened), name, ix)
			!= SD_SUCCESS)
		{	/* error already logged.	*/
			scl_stop_parsing (sxDecCtrl, "_DAI_SEFun", SX_USER_ERROR);
			return;
		}

		SXLOG_CDEC1 ("SCL PARSE: Appended to flattened variable: '%s'", sclDecCtrl->flattened);

#ifdef SCL_USE_MMS_STRING_
		mms_str_set(&scl_dai->flattened, sclDecCtrl->flattened);
#else
		strcpy (scl_dai->flattened, sclDecCtrl->flattened);
#endif

		sx_push (sxDecCtrl, sizeof(DAIElements)/sizeof(SX_ELEMENT), DAIElements, SD_FALSE);    
	}
	else /* reason = SX_ELEMENT_END */
	{
		/* Remove the last item from the flattened string */
		p = strrchr(sclDecCtrl->flattened, '$');
		if (p != NULL)
			*p = 0;
		SXLOG_CDEC1 ("SCL PARSE: Removed last item from flattened variable: '%s'", sclDecCtrl->flattened);
		sx_pop (sxDecCtrl);
	}
}

/************************************************************************/
/*			_DAI_Val_SEFun					*/
/* Sets "sGroup" and "Val" in sclDecCtrl->scl_dai.			*/
/************************************************************************/

static ST_VOID _DAI_Val_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		/* start optional attributes (don't care about return)	*/
		scl_get_uint_attr (sxDecCtrl, "sGroup", &sclDecCtrl->scl_dai->sGroup, SCL_ATTR_OPTIONAL);
		/* end optional attributes */
	}
	else /* reason = SX_ELEMENT_END */
	{
		SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		ST_RET ret;
		ST_INT strLen;
		ST_CHAR *Val;
		ret = sx_get_string_ptr (sxDecCtrl, &Val, &strLen);
		if (ret==SD_SUCCESS)
			sclDecCtrl->scl_dai->Val = chk_strdup (Val);	/* alloc & store Val*/
		else
			scl_stop_parsing (sxDecCtrl, "DAI Val", SX_USER_ERROR);
	}
}

/************************************************************************/
/*			_DataTypeTemplates_SEFun			*/
/************************************************************************/

static ST_VOID _DataTypeTemplates_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
		sx_push (sxDecCtrl, sizeof(DataTypeTemplatesElements)/sizeof(SX_ELEMENT), DataTypeTemplatesElements, SD_FALSE);    
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_LNodeType_SEFun				*/
/************************************************************************/

static ST_VOID _LNodeType_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_LNTYPE *scl_lntype;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_lntype = scl_lntype_create (sclDecCtrl->sclInfo);
		if (scl_lntype == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_lntype_create", SX_USER_ERROR);
			return;
		}

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "id", &scl_lntype->id, required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "lnClass", &scl_lntype->lnClass, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "id", scl_lntype->id, (sizeof(scl_lntype->id)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "lnClass", scl_lntype->lnClass, (sizeof(scl_lntype->lnClass)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//{
			//hejian alter on 2010-9-29
		//	sxDecCtrl->errCode = SD_SUCCESS;
		//	sxDecCtrl->termFlag = SD_FALSE;

			//return;
		//}
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(LNodeTypeElements)/sizeof(SX_ELEMENT), LNodeTypeElements, SD_FALSE);    
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_DO_SFun					*/
/************************************************************************/

static ST_VOID _DO_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_DO *scl_do;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	scl_do = scl_lntype_add_do (sclDecCtrl->sclInfo);
	if (scl_do == NULL)
	{
		scl_stop_parsing (sxDecCtrl, "scl_lntype_add_do", SX_USER_ERROR);
		return;
	}

	/* start required attributes */
	//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_do->name,  required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "type", &scl_do->type, required);
#else
	ret = scl_get_attr_copy (sxDecCtrl, "name", scl_do->name, (sizeof(scl_do->name)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "type", scl_do->type, (sizeof(scl_do->type)-1), required);
#endif

	//if (ret != SD_SUCCESS)
	//{
	//	return;
	//}
	/* end required attributes */
}

/************************************************************************/
/*			_DOType_SEFun					*/
/************************************************************************/

static ST_VOID _DOType_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_DOTYPE *scl_dotype;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_dotype = scl_dotype_create (sclDecCtrl->sclInfo);
		if (scl_dotype == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_dotype_create", SX_USER_ERROR);
			return;
		}

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "id", &scl_dotype->id, required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "cdc", &scl_dotype->cdc, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "id", scl_dotype->id, (sizeof(scl_dotype->id)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "cdc", scl_dotype->cdc, (sizeof(scl_dotype->cdc)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//{
		//	return;
		//}
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(DOTypeElements)/sizeof(SX_ELEMENT), DOTypeElements, SD_FALSE);    
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_DA_SEFun					*/
/************************************************************************/

static ST_VOID _DA_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_DEC_CTRL *sclDecCtrl;
		ST_CHAR *str;	/* use for dchg, qchg, dupd	*/
		ST_BOOLEAN bDchg = SD_FALSE;
		ST_BOOLEAN bQchg = SD_FALSE;
		ST_BOOLEAN bDupd = SD_FALSE;
		ST_RET ret;
		ST_BOOLEAN required = SD_FALSE;
		SCL_DA *scl_da;
		ST_CHAR *desc;

		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_da = sclDecCtrl->scl_da = scl_dotype_add_da (sclDecCtrl->sclInfo);
		if (scl_da == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_dotype_add_da", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_da->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "sAddr", &scl_da->sAddr, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "sAddr", scl_da->sAddr, (sizeof(scl_da->sAddr)-1), required);
#endif

		ret = scl_get_attr_copy (sxDecCtrl, "valKind", scl_da->valKind, (sizeof(scl_da->valKind)-1), required);
		if (ret)
			strcpy (scl_da->valKind, "Set"); /* default */

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "type", &scl_da->type, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "type", scl_da->type, (sizeof(scl_da->type)-1), required);
#endif

		ret = scl_get_uint_attr (sxDecCtrl, "count", &scl_da->count, required);
		ret = scl_get_attr_ptr (sxDecCtrl, "dchg", &str, required);
		if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
			bDchg = SD_TRUE;

		ret = scl_get_attr_ptr (sxDecCtrl, "qchg", &str, required);
		if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
			bQchg = SD_TRUE;

		ret = scl_get_attr_ptr (sxDecCtrl, "dupd", &str, required);
		if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
			bDupd = SD_TRUE;

		scl_da->dchg = bDchg;//zhouhj 20181204
		scl_da->qchg = bQchg;
		scl_da->dupd = bDupd;
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_da->name, required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "bType", &scl_da->bType, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_da->name, (sizeof(scl_da->name)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "bType", scl_da->bType, (sizeof(scl_da->bType)-1), required);
#endif

		ret |= scl_get_attr_copy (sxDecCtrl, "fc", scl_da->fc, (sizeof(scl_da->fc)-1), required);
		//if (ret != SD_SUCCESS)
		//{
		//	return;
		//}
		/* end required attributes */
		sx_push (sxDecCtrl, sizeof(DAElements)/sizeof(SX_ELEMENT), DAElements, SD_FALSE);
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_SDO_SFun					*/
/************************************************************************/

static ST_VOID _SDO_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_DA *scl_da;
	ST_CHAR *desc;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	scl_da = scl_dotype_add_sdo (sclDecCtrl->sclInfo);
	if (scl_da == NULL)
	{
		scl_stop_parsing (sxDecCtrl, "scl_dotype_add_sdo", SX_USER_ERROR);
		return;
	}

	/* start optional attributes */
	ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
	if (ret == SD_SUCCESS)
		scl_da->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
	/* end optional attributes */

	/* start required attributes */
	//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_da->name, required);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "type", &scl_da->type, required);
#else
	ret = scl_get_attr_copy (sxDecCtrl, "name", scl_da->name, (sizeof(scl_da->name)-1), required);
	ret |= scl_get_attr_copy (sxDecCtrl, "type", scl_da->type, (sizeof(scl_da->type)-1), required);
#endif

	//if (ret != SD_SUCCESS)
	//{
	//	return;
	//}
	/* end required attributes */
}

/************************************************************************/
/*			_DA_Val_SEFun					*/
/************************************************************************/

static ST_VOID _DA_Val_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		/* start optional attributes (don't care about return)	*/
		scl_get_uint_attr (sxDecCtrl, "sGroup", &sclDecCtrl->scl_da->sGroup, SCL_ATTR_OPTIONAL);
		/* end optional attributes */
	}
	else /* reason = SX_ELEMENT_END */
	{
		SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		ST_RET ret;
		ST_INT strLen;
		ST_CHAR *Val;
		ret = sx_get_string_ptr (sxDecCtrl, &Val, &strLen);
		if (ret==SD_SUCCESS)
			sclDecCtrl->scl_da->Val = chk_strdup (Val);	/* alloc & store Val*/
		else
			scl_stop_parsing (sxDecCtrl, "DA Val", SX_USER_ERROR);
	}
}

/************************************************************************/
/*			_DAType_SEFun					*/
/************************************************************************/

static ST_VOID _DAType_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_DATYPE *scl_datype;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_datype = scl_datype_create (sclDecCtrl->sclInfo);
		if (scl_datype == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_datype_create", SX_USER_ERROR);
			return;
		}

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "id", &scl_datype->id, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "id", scl_datype->id, (sizeof(scl_datype->id)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//{
		//	return;
		//}
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(DATypeElements)/sizeof(SX_ELEMENT), DATypeElements, SD_FALSE);    
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_BDA_SEFun					*/
/************************************************************************/

static ST_VOID _BDA_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_DEC_CTRL *sclDecCtrl;
		ST_RET ret;
		ST_BOOLEAN required = SD_FALSE;
		SCL_BDA *scl_bda;
		ST_CHAR *desc;

		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		scl_bda = sclDecCtrl->scl_bda = scl_datype_add_bda (sclDecCtrl->sclInfo);
		if (scl_bda == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_datype_add_bda", SX_USER_ERROR);
			return;
		}

		/* start optional attributes */
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, required);
		if (ret == SD_SUCCESS)
			scl_bda->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "sAddr", &scl_bda->sAddr,  required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "sAddr", scl_bda->sAddr, (sizeof(scl_bda->sAddr)-1), required);
#endif

		ret = scl_get_attr_copy (sxDecCtrl, "valKind", scl_bda->valKind, (sizeof(scl_bda->valKind)-1), required);
		if (ret)
			strcpy (scl_bda->valKind, "Set"); /* default */

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "type", &scl_bda->type, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "type", scl_bda->type, (sizeof(scl_bda->type)-1), required);
#endif

		ret = scl_get_uint_attr (sxDecCtrl, "count", &scl_bda->count, required);
		/* end optional attributes */

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", &scl_bda->name, required);
		ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "bType", &scl_bda->bType, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_bda->name, (sizeof(scl_bda->name)-1), required);
		ret |= scl_get_attr_copy (sxDecCtrl, "bType", scl_bda->bType, (sizeof(scl_bda->bType)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//{
			//hejian alter on 2010-9-29
		//	sxDecCtrl->errCode = SD_SUCCESS;
		//	sxDecCtrl->termFlag = SD_FALSE;
			//return;
		//}
		/* end required attributes */
		sx_push (sxDecCtrl, sizeof(BDAElements)/sizeof(SX_ELEMENT), BDAElements, SD_FALSE);
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_BDA_Val_SEFun					*/
/************************************************************************/

static ST_VOID _BDA_Val_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		/* start optional attributes (don't care about return)	*/
		scl_get_uint_attr (sxDecCtrl, "sGroup", &sclDecCtrl->scl_bda->sGroup, SCL_ATTR_OPTIONAL);
		/* end optional attributes */
	}
	else /* reason = SX_ELEMENT_END */
	{
		SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
		ST_RET ret;
		ST_INT strLen;
		ST_CHAR *Val;
		ret = sx_get_string_ptr (sxDecCtrl, &Val, &strLen);
		if (ret==SD_SUCCESS)
			sclDecCtrl->scl_bda->Val = chk_strdup (Val);	/* alloc & store Val*/
		else
			scl_stop_parsing (sxDecCtrl, "BDA Val", SX_USER_ERROR);
	}
}

/************************************************************************/
/*			_EnumType_SEFun					*/
/************************************************************************/

static ST_VOID _EnumType_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_BOOLEAN required = SD_FALSE;
	SCL_ENUMTYPE *scl_enumtype;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

		if ((scl_enumtype = scl_enumtype_create (sclDecCtrl->sclInfo)) == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_enumtype_create", SX_USER_ERROR);
			return;
		}

		/* start required attributes */
		//required = SD_TRUE;

#ifdef SCL_USE_MMS_STRING_
		ret = scl_get_attr_copy_mms_str(sxDecCtrl, "id", &scl_enumtype->id, required);
#else
		ret = scl_get_attr_copy (sxDecCtrl, "id", scl_enumtype->id, (sizeof(scl_enumtype->id)-1), required);
#endif

		//if (ret != SD_SUCCESS)
		//{
		//	return;
		//}
		/* end required attributes */

		sx_push (sxDecCtrl, sizeof(EnumTypeElements)/sizeof(SX_ELEMENT), EnumTypeElements, SD_FALSE);    
	}
	else
		sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_EnumVal_SEFun					*/
/************************************************************************/

static ST_VOID _EnumVal_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	ST_INT strLen;
	ST_BOOLEAN required = SD_FALSE;
	SCL_ENUMVAL *scl_enumval;
	char *pszMms_str = NULL;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		if ((scl_enumval = sclDecCtrl->scl_enumval = scl_enumtype_add_enumval (sclDecCtrl->sclInfo)) == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_enumtype_add_enumval", SX_USER_ERROR);
			return;
		}

		/* start required attributes */
		//required = SD_TRUE;
		ret = scl_get_int_attr (sxDecCtrl, "ord", &scl_enumval->ord, required);
		//if (ret != SD_SUCCESS)
		//{
		//	return;
		//}
		/* end required attributes */
	}
	else /* reason = SX_ELEMENT_END */
	{
		scl_enumval = sclDecCtrl->scl_enumval;
		/* CRITICAL: Init strLen = max len. After sx_get_string, strLen = actual len*/
		strLen = sizeof(scl_enumval->EnumVal)-1;

#ifdef SCL_USE_MMS_STRING_
		pszMms_str = malloc(MAX_IDENT_LEN*2);
		memset(pszMms_str,0,MAX_IDENT_LEN*2);
		ret = sx_get_string (sxDecCtrl,pszMms_str , &strLen);
		mms_str_set(&scl_enumval->EnumVal ,pszMms_str);
		free(pszMms_str);
#else
		ret = sx_get_string (sxDecCtrl, scl_enumval->EnumVal, &strLen);
#endif

		if (ret != SD_SUCCESS)
			scl_stop_parsing (sxDecCtrl, "_EnumVal_SEFun", SX_USER_ERROR);
	}
}

/************************************************************************/
/*			_scl_unknown_el_start				*/
/************************************************************************/

static ST_RET _scl_unknown_el_start (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag)
{
	SXLOG_DEC1 ("SCL PARSE: Unneeded or unknown element '%s'", tag);
	return (SD_SUCCESS);
}

/************************************************************************/
/*			_scl_unknown_el_end				*/
/************************************************************************/

static ST_RET _scl_unknown_el_end (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag)
{
	return (SD_SUCCESS);
}

/************************************************************************/
/*			_SampledValueControl_SEFun			*/
/* DEBUG: if parser called separate start and end functions, the lower	*/
/*   functs could be called directly & this funct would not be needed.	*/
/************************************************************************/
static ST_VOID _SampledValueControl_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	if (sxDecCtrl->reason == SX_ELEMENT_START)
		_SampledValueControl_SFun (sxDecCtrl);
	else
		_SampledValueControl_EFun (sxDecCtrl);
}
/************************************************************************/
/*			_SampledValueControl_SFun			*/
/* Handle Start tag							*/
/************************************************************************/
static ST_VOID _SampledValueControl_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *str;		/* ptr set by scl_get_attr_ptr	*/
	ST_RET ret;
	SCL_SVCB *scl_svcb;
	ST_CHAR *desc;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	/* Alloc struct, save in sclDecCtrl, & set local ptr to it.	*/
	scl_svcb = sclDecCtrl->scl_svcb = scl_svcb_add (sclDecCtrl->sclInfo);
	if (scl_svcb == NULL)
	{
		scl_stop_parsing (sxDecCtrl, "scl_svcb_add", SX_USER_ERROR);
		return;
	}

	/* start required attributes */
#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "name", (&scl_svcb->name), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
	ret |= scl_get_attr_copy_mms_str (sxDecCtrl, "smvID", (&scl_svcb->smvID), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#else
	ret = scl_get_attr_copy (sxDecCtrl, "name", scl_svcb->name, (sizeof(scl_svcb->name)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
	ret |= scl_get_attr_copy (sxDecCtrl, "smvID", scl_svcb->smvID, (sizeof(scl_svcb->smvID)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
#endif

	ret |= scl_get_uint_attr (sxDecCtrl, "smpRate", &scl_svcb->smpRate, SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
	ret |= scl_get_uint_attr (sxDecCtrl, "nofASDU", &scl_svcb->nofASDU, SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
	//if (ret != SD_SUCCESS)
	//	return;	/* At least one required attr not found. Stop now.	*/
	/* end required attributes */

	/* start optional attributes */
	ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
	if (ret == SD_SUCCESS)
		scl_svcb->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

#ifdef SCL_USE_MMS_STRING_
	ret = scl_get_attr_copy_mms_str (sxDecCtrl, "datSet", (&scl_svcb->datSet), SCL_ATTR_OPTIONAL);
#else
	ret = scl_get_attr_copy (sxDecCtrl, "datSet", scl_svcb->datSet, (sizeof(scl_svcb->datSet)-1), SCL_ATTR_OPTIONAL);
#endif

	ret = scl_get_uint_attr (sxDecCtrl, "confRev", &scl_svcb->confRev, SCL_ATTR_OPTIONAL);
	ret = scl_get_attr_ptr (sxDecCtrl, "multicast", &str, SCL_ATTR_OPTIONAL);	/* chk "str" below*/
	if (ret == SD_SUCCESS  &&  stricmp(str, "false") == 0)
		scl_svcb->multicast = SD_FALSE;
	else
		scl_svcb->multicast = SD_TRUE;  /* default value */
	/* end optional attributes */

	sx_push (sxDecCtrl, sizeof(SampledValueControlElements)/sizeof(SX_ELEMENT), SampledValueControlElements, SD_FALSE);
}
/************************************************************************/
/*			_SampledValueControl_EFun			*/
/* Handle End tag							*/
/************************************************************************/
static ST_VOID _SampledValueControl_EFun (SX_DEC_CTRL *sxDecCtrl)
{
	sx_pop (sxDecCtrl);
}

/************************************************************************/
/*			_SmvOpts_SFun					*/
/************************************************************************/
static ST_VOID _SmvOpts_SFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_CHAR *str;		/* ptr set by scl_get_attr_ptr	*/
	ST_RET ret;
	SCL_SVCB *scl_svcb;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	scl_svcb = sclDecCtrl->scl_svcb;

	/* start optional attributes */
	ret = scl_get_attr_ptr (sxDecCtrl, "sampleRate", &str, SCL_ATTR_OPTIONAL);
	if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
	{
		BSTR_BIT_SET_ON(scl_svcb->OptFlds, SVOPT_BITNUM_SMPRATE);
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "refreshTime", &str, SCL_ATTR_OPTIONAL);
	if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
	{
		BSTR_BIT_SET_ON(scl_svcb->OptFlds, SVOPT_BITNUM_REFRTM);
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "sampleSynchronized", &str, SCL_ATTR_OPTIONAL);
	if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
	{
		BSTR_BIT_SET_ON(scl_svcb->OptFlds, SVOPT_BITNUM_SMPSYNCH);
	}

	ret = scl_get_attr_ptr (sxDecCtrl, "security", &str, SCL_ATTR_OPTIONAL);
	if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
		scl_svcb->securityPres = SD_TRUE;	/* scl_svcb calloced so init val is FALSE*/

	/* NOTE: SCL calls this "dataRef", but 7-2 & 9-2 call it "DatSet".	*/
	ret = scl_get_attr_ptr (sxDecCtrl, "dataRef", &str, SCL_ATTR_OPTIONAL);
	if (ret == SD_SUCCESS  &&  stricmp(str, "true") == 0)
		scl_svcb->dataRefPres = SD_TRUE;	/* scl_svcb calloced so init val is FALSE*/
	/* end optional attributes */
}


/************************************************************************/
/*			_SubStation_SEFun				*/
/************************************************************************/

static ST_VOID _SubStation_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl;
	ST_RET ret;
	SCL_SUBSTATION *scl_substation;
	ST_CHAR *name;
	ST_CHAR *desc;
    //ST_BOOLEAN required = SD_FALSE;

	sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		scl_substation  = scl_substation_create (sclDecCtrl->sclInfo);
		if (scl_substation == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_substation_create", SX_USER_ERROR);
			return;
		}

		//ret = scl_get_attr_copy (sxDecCtrl, "Name", scl_substation->name, (sizeof(scl_substation->name)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);

		ret = scl_get_attr_ptr (sxDecCtrl, "name", &name, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_substation->name= chk_strdup (name);	
		
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_substation->desc = chk_strdup (desc);	

		sx_push (sxDecCtrl, sizeof(SubstationElements)/sizeof(SX_ELEMENT), 
			SubstationElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static ST_VOID _SubStation_SEFun(SX_DEC_CTRL *sxDecCtrl)
//{
//
//	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
//
//		SCL_SUBSTATION *scl_substation;
//		scl_subnet = scl_subnet_add (sclDecCtrl->sclInfo);
//
//	ST_RET ret;
//	ST_CHAR *desc;
//
//	if (sxDecCtrl->reason == SX_ELEMENT_START)
//	{		
//		ret = scl_get_attr_copy (sxDecCtrl, "name", scl_substation->name, (sizeof(scl_substation->name)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
//		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
//		if (ret == SD_SUCCESS)
//			scl_substation->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/
//
//		sx_push (sxDecCtrl, sizeof(SubstationElements)/sizeof(SX_ELEMENT), 
//			SubstationElements, SD_FALSE);
//	}
//	else
//	{
//		sx_pop (sxDecCtrl);
//	}
//}

/************************************************************************/
/*			_VoltageLevel_SEFun				*/
/************************************************************************/




static ST_VOID _VoltageLevel_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;
	ST_CHAR *name;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_VOLLEVEL *scl_vollevel;
		scl_vollevel = scl_vollevel_add(sclDecCtrl->sclInfo);
		if (scl_vollevel == NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_vollevel_add", SX_USER_ERROR);
			return;
		}
		/* Get required attributes	*/
		//ret = scl_get_attr_copy (sxDecCtrl, "vollevelName", scl_vollevel->name, (sizeof(scl_vollevel->name)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
		ret = scl_get_attr_ptr (sxDecCtrl, "name", &name, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_vollevel->name= chk_strdup (name);	/* Alloc & copy desc string	*/
		//ret |= scl_get_attr_copy (sxDecCtrl, "apName", scl_cap->apName, (sizeof(scl_cap->apName)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
		//if (ret)
		//{
		//	scl_stop_parsing (sxDecCtrl, "ConnectedAP", SX_USER_ERROR);
		//	return;
		//}
		/* Get optional attributes.	*/
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_vollevel->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

		sx_push (sxDecCtrl, sizeof(VoltageLevelElements)/sizeof(SX_ELEMENT), 
			VoltageLevelElements, SD_FALSE);
	}
	else
	{
		sx_pop (sxDecCtrl);
	}
}


/************************************************************************/
/*			_GSE_SEFun					*/
/************************************************************************/
static ST_VOID _Bay_SEFun (SX_DEC_CTRL *sxDecCtrl)
{
	SCL_DEC_CTRL *sclDecCtrl = (SCL_DEC_CTRL *) sxDecCtrl->usr;
	ST_RET ret;

    ST_CHAR *name;
	ST_CHAR *desc;

	if (sxDecCtrl->reason == SX_ELEMENT_START)
	{
		SCL_BAY *scl_bay;
		scl_bay = scl_bay_add(sclDecCtrl->sclInfo);
		if (scl_bay== NULL)
		{
			scl_stop_parsing (sxDecCtrl, "scl_bay_add", SX_USER_ERROR);
			return;
		}
		/* Get required attributes	*/
	//	ret = scl_get_attr_copy (sxDecCtrl, "iedName", scl_bay->Name, (sizeof(scl_bay->Name)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
        ret = scl_get_attr_ptr (sxDecCtrl, "name", &name, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_bay->name= chk_strdup (name);	/* Alloc & copy desc string	*/
		//ret |= scl_get_attr_copy (sxDecCtrl, "apName", scl_cap->apName, (sizeof(scl_cap->apName)-1), SCL_ATTR_OPTIONAL/*SCL_ATTR_REQUIRED*/);
		//if (ret)
		//{
		//	scl_stop_parsing (sxDecCtrl, "ConnectedAP", SX_USER_ERROR);
		//	return;
		//}
		/* Get optional attributes.	*/
		ret = scl_get_attr_ptr (sxDecCtrl, "desc", &desc, SCL_ATTR_OPTIONAL);
		if (ret == SD_SUCCESS)
			scl_bay->desc = chk_strdup (desc);	/* Alloc & copy desc string	*/

	}
	//else
	//{
	//	sx_pop (sxDecCtrl);
	//}
}
