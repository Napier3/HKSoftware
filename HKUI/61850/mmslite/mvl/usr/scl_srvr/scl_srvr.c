/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	1986 - 2005, All Rights Reserved		        */
/*									*/
/* MODULE NAME : scl_srvr.c    						*/
/* PRODUCT(S)  : MMSEASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	NONE								*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/15/07  JRB    21     Del mvlu_rpt_service call (for UCA only).	*/
/* 02/13/07  RKR    20     added ms res to WIN32 u_mvlu_rpt_time_get    */
/* 01/10/07  JRB    19     Del unused local vars.			*/
/* 12/04/06  JRB    18     Fix mvl_vmd_destroy call (new arg).		*/
/*			   Add call to mvl61850_rpt_ctrl_destroy_all.	*/
/* 11/13/06  JRB    17     Use new mvl_vmd_* object handling functions.	*/
/* 10/30/06  JRB    16     Chg args to "scl2_*_create_all" functions.	*/
/*			   u_mvl_scl_set_initial_value: return error.	*/
/*			   Del slog_max_msg_size_set call, see slog_start*/
/* 08/17/06  JRB    15     Add call to mvl61850_rpt_service (61850 rpt	*/
/*			   servicing is now separate from UCA).		*/
/*			   Shorten wait_any_event delay.		*/
/* 08/09/06  JRB    14	   Add u_mvl_scl_set_initial_value callback.	*/
/* 03/27/06  JRB    13     Add SMPVAL test code (see SMPVAL_SUPPORT).	*/
/*			   all_obj_create do not call scl_info_free	*/
/*			   (let user call it if scl_info not needed).	*/
/* 10/25/05  EJV    12     S_SEC_ENABLED: added identify_response_info.	*/
/*			   Call slog_start, slog_end, slogIpcEvent.	*/
/* 09/09/05  JRB    11     Don't print BUILD_NUM.			*/
/* 09/06/05  EJV    10     Added more code for S_SEC_ENABLED.		*/
/* 07/25/05  JRB    09     scl2_ld_create_all: Add brcb_bufsize arg.	*/
/* 07/13/05  JRB    08     Add sample "u_mvl61850_ctl_oper_*" functs.	*/
/* 07/13/05  JRB    07     Chg datamap_cfg_read args.			*/
/*			   Don't exit on err in SCL or DATAMAP config.	*/
/*			   Init all objs before ACSE (see mvl_init_mms_objs)*/
/*			   Call scl_info_destroy when no longer needed.	*/
/*			   Use new all_obj_create to parse SCL & create	*/
/*			   objects.					*/
/*			   Use new all_obj_destroy to cleanup on exit.	*/
/*			   Don't print "Check log file". May not be one.*/
/*			   Set "failure" code in u_no_write_allowed.	*/
/*			   Use new slog_max_msg_size_set.		*/
/* 06/07/05  EJV    06     Set gsLogMaskMapCtrl if S_MT_SUPPORT defined	*/
/* 06/01/05  GLB    05     Removed secLogMaskMapCtrl & usrLogMaskMapCtrl*/
/* 05/24/05  EJV    04     Added logCfgAddMaskGroup (&xxxLogMaskMapCtrl)*/
/*			   Use logcfgx_ex to parse logging config file.	*/
/* 08/10/04  EJV    03     u_mvl_connect_ind_ex: typecasted ret		*/
/* 08/06/04  JRB    02     Del "sclparse.h", use "scl.h".		*/
/*			   Use new user header file.			*/
/* 07/19/04  JRB    01     New app using SCL parser.			*/
/************************************************************************/

#if 0
  #define HARD_CODED_CFG		/* move outside #if to enable	*/
  #define ACSE_AUTH_ENABLED		/* for password authentication	*/
					/* without security		*/
/*  S_SEC_ENABLED		for certificate based authentication &	*/
/*				SSL encryption, put this define in	*/
/*				application's DSP/MAK file 		*/
#endif



/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include <signal.h>

#include "mmsdefs.h"
#include "mms_pvar.h"
#include "mms_vvar.h"
#include "mms_pvmd.h"
#include "mms_err.h"
#include "mms_pcon.h"
#include "asn1defs.h"
#include "stime.h"

#include "mvl_acse.h"
#include "mvl_uca.h"	/* UCA/IEC defs	*/
#include "mvl_log.h"
#include "uca_obj.h"
#include "tp4api.h"

#include "stdtime.h"
#include "stdtime_mms_btime.h"
#include "uca_srvr.h"

#if defined (MVL_GOOSE_SUPPORT)
#include "goose.h"
#include "glbsem.h"
#include <process.h>
#endif

#ifdef SMEM_ENABLE
#include "smem.h"
#endif
#include "scl.h"	/* SCL file processing structs & functions	*/
#include "startup.h"	/* struct & function to parse "startup.cfg"	*/
#include "usermap.h"	/* for DATA_MAP_HEAD, datamap_cfg_read, etc.	*/
#include "sx_arb.h"			/* for sxaTextToLocal		*/

/*----------------------------------------------------------------------*/
/* NOTE: The MMS-EASE Lite Secured applications (Client, Server) 	*/
/*	 are designed to work with Security Toolkit for MMS-EASE Lite	*/
/*	 (MMS-LITE-SECURE-80x-001).						*/
/*       The S_SEC_ENABLED delimits the security related code.		*/
/*----------------------------------------------------------------------*/
#if defined(S_SEC_ENABLED) && defined(ACSE_AUTH_ENABLED)
#error Only one S_SEC_ENABLED or ACSE_AUTH_ENABLED may be defined
#endif

#if defined(S_SEC_ENABLED)
#include "mmslusec.h"
#endif

#include "smpval.h"


ST_RET all_obj_create (ST_CHAR *startup_cfg_filename,
	ST_CHAR *datamap_cfg_filename,
	ST_CHAR *datamap_cfg_out_filename,
	SCL_INFO *scl_info);
ST_RET all_obj_destroy ();

/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/
/************************************************************************/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

ST_INT32 SampleData [16];	/* Data to demonstrate SMPVAL messages	*/

/************************************************************************/
/************************************************************************/
/* MMS IDENTIFY AND STATUS RESPONSE INFORMATION				*/

/* Identify server information						*/
#if defined(S_SEC_ENABLED)
IDENT_RESP_INFO identify_response_info =
  {
  "SISCO",  				/* Vendor 	*/
  S_SEC_LITESECURE_NAME,  		/* Model  	*/
  S_SEC_LITESECURE_VERSION_STR	,  0,	/* Version 	*/
  };
#else
static IDENT_RESP_INFO identify_response_info =
  {
  "SISCO",  		/* Vendor 	*/
  MMSLITE_NAME,  	/* Model  	*/
  MMSLITE_VERSION,  0,	/* Version 	*/
  };
#endif

/* Status server information						*/
static STATUS_RESP_INFO status_resp_info =
  {
  0,		/* logical_stat 	*/
  0, 		/* physical_stat 	*/
  0, 		/* local_detail_pres 	*/
  };

/************************************************************************/
/************************************************************************/
/* Functions in this module						*/

/* Initialization */
static ST_VOID init_acse (ST_VOID);
static ST_VOID init_log_cfg (ST_VOID);
static ST_VOID init_mem (ST_VOID);

/* Connection Management */
static ST_INT connect_ind_fun (MVL_NET_INFO *cc, INIT_INFO *init_info);
static ST_VOID disc_ind_fun (MVL_NET_INFO *cc, ST_INT discType);

/* Misc. */
ST_VOID ctrlCfun (int);

/************************************************************************/

/* General program control variables */
static ST_BOOLEAN doIt = SD_TRUE;

#ifdef SMPVAL_SUPPORT
/************************************************************************/
/*			scl_svcb_find					*/
/************************************************************************/
SCL_SVCB *scl_svcb_find (SCL_INFO *scl_info, ST_CHAR *svcb_name, SCL_LD **scl_ld_out, SCL_LN **scl_ln_out)
  {
SCL_LD *scl_ld;
SCL_LN *scl_ln;
SCL_SVCB *scl_svcb;

  for (scl_ld = (SCL_LD *) list_find_last ((DBL_LNK *) scl_info->ldHead);
       scl_ld != NULL;
       scl_ld = (SCL_LD *) list_find_prev ((DBL_LNK *) scl_info->ldHead, (DBL_LNK *) scl_ld))
    {
    for (scl_ln = (SCL_LN *) list_find_last ((DBL_LNK *) scl_ld->lnHead);
         scl_ln != NULL;
         scl_ln = (SCL_LN *) list_find_prev ((DBL_LNK *) scl_ld->lnHead, (DBL_LNK *) scl_ln))
      {
      for (scl_svcb = (SCL_SVCB *) list_find_last ((DBL_LNK *) scl_ln->svcbHead);
           scl_svcb != NULL;
           scl_svcb = (SCL_SVCB *) list_find_prev ((DBL_LNK *) scl_ln->svcbHead, (DBL_LNK *) scl_svcb))
        {
        if (strcmp (scl_svcb->name, svcb_name) == 0)
          {
          *scl_ld_out = scl_ld;
          *scl_ln_out = scl_ln;
          return (scl_svcb);	/* too hard to break out of 3 loops	*/
          }
        }
      }
    }

  return (NULL);	/* not found	*/
  }
/************************************************************************/
/*			test_smpval_msg_send				*/
/************************************************************************/
ST_RET test_smpval_msg_send (SMPVAL_MSG *smpvalMsg, SCL_SVCB *scl_svcb,
                      ST_INT *SmpCntPtr, ETYPE_INFO *etypeInfo)
  {
MMS_UTC_TIME utcTime;
ST_UINT asduIdx;
ST_UCHAR dstMac [] = {1,1,1,1,1,1};
#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
ST_INT32 SampleDataConverted [16];	/* SMPVAL Data converted to BigEndian*/
#endif
ST_BOOLEAN SmpRatePres;		/* extracted from OptFlds	*/
ST_BOOLEAN RefrTmPres;		/* extracted from OptFlds	*/
ST_BOOLEAN SmpSynch;		/* extracted from OptFlds	*/
ST_RET retcode;

  utcTime.secs = (ST_UINT32) time(NULL);	/* just set seconds in UTC time.	*/
  if (scl_svcb)
    {
    SmpRatePres  = BSTR_BIT_GET (scl_svcb->OptFlds, SVOPT_BITNUM_SMPRATE);
    RefrTmPres   = BSTR_BIT_GET (scl_svcb->OptFlds, SVOPT_BITNUM_REFRTM);
    SmpSynch = BSTR_BIT_GET (scl_svcb->OptFlds, SVOPT_BITNUM_SMPSYNCH);

    /* For this sample, put same data in each ASDU, but increment "SmpCnt".*/
    for (asduIdx = 0; asduIdx < smpvalMsg->numASDU; asduIdx++)
      {
      (*SmpCntPtr)++;
      retcode = smpval_asdu_data_update (smpvalMsg,
          asduIdx,
#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
          (ST_UINT8 *) SampleDataConverted,
#else
          (ST_UINT8 *) SampleData,	/* for BigEndian, use original unconverted data	*/
#endif
          sizeof (SampleData),
          scl_svcb->smvID,
          *SmpCntPtr,
          scl_svcb->dataRefPres,	/* DatSetPres flag	*/
          scl_svcb->datSet,		/* ST_CHAR *DatSet	*/
          scl_svcb->confRev,		/* ST_UINT32 ConfRev	*/
          SmpSynch,			/* ST_BOOLEAN SmpSynch	*/
          RefrTmPres,			/* RefrTmPres flag	*/
          &utcTime,			/* MMS_UTC_TIME *RefrTm	*/
          SmpRatePres,			/* SmpRatePres flag	*/
          (ST_UINT16)scl_svcb->smpRate);/* ST_UINT16 SmpRate	*/
      if (retcode)
        {
        printf ("smpval_asdu_data_update error\n");
        break;
        }
      }	/* end loop	*/
    }
  if (retcode == SD_SUCCESS)
    {
#if 0	/* DEBUG: enable this to test "security" encode/decode in SMPVAL msg.*/
    /* WARNING: do not exceed max len of securityBuf.	*/
    strcpy (smpvalMsg->securityBuf, "test_security");
    smpvalMsg->securityLen = strlen ("test_security");
#endif

    retcode = smpval_msg_send (smpvalMsg, etypeInfo, dstMac);
    printf ("SampledValue message sent, numASDU = %d, smpCnt values:", smpvalMsg->numASDU);
    for (asduIdx = 0; asduIdx < smpvalMsg->numASDU; asduIdx++)
      printf (" %d", smpvalMsg->asduArray[asduIdx].SmpCnt);
    printf ("\n  securityLen = %u\n", smpvalMsg->securityLen);
    }
  return (retcode);
}
#endif	/* SMPVAL_SUPPORT	*/

/************************************************************************/
/************************************************************************/
/*                       main						*/
/************************************************************************/

int main ()
  {
ST_RET ret;
SCL_INFO scl_info;

#ifdef SMPVAL_SUPPORT
SCL_LD *scl_ld;
SCL_LN *scl_ln;
SCL_SVCB *scl_svcb;
ST_UINT nofASDU;	/* Num of ASDU concatenated into one APDU.	*/
			/* Get from SCL configuration.			*/
ST_DOUBLE currTime;
ST_DOUBLE lastTime = 0;
SMPVAL_MSG *smpvalMsg;
ETYPE_INFO etypeInfo;
ST_INT SmpCnt = 0;	/* incremented with each entry	*/
ST_BOOLEAN *SvEnaPtr;	/* Ptr to SvEna leaf data.	*/
RUNTIME_TYPE *SvEnaRtType;
#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
ST_INT32 SampleDataConverted [16];	/* SMPVAL Data converted to BigEndian*/
#endif
MVL_VAR_ASSOC *var_with_ms;	/* var containing FC=MS	*/
OBJECT_NAME baseVarName;

  /* Initialize SMPVAL data with dummy values.	*/
  SampleData [0]  = 256;
  SampleData [1]  = 0x0000f0f0;	/* Quality in first 2 bytes (low bytes on INTEL)*/
  SampleData [2]  = 257;
  SampleData [3]  = 0x00000f0f;
  SampleData [4]  = 258;
  SampleData [5]  = 0x0000f0f0;
  SampleData [6]  = 259;
  SampleData [7]  = 0x0000f0f0;
  SampleData [8]  = 260;
  SampleData [9]  = 0x0000f0f0;
  SampleData [10] = 261;
  SampleData [11] = 0x0000f0f0;
  SampleData [12] = 262;
  SampleData [13] = 0x0000f0f0;
  SampleData [14] = 263;
  SampleData [15] = 0x0000f0f0;
#endif	/* SMPVAL_SUPPORT	*/

  setbuf (stdout, NULL);    /* do not buffer the output to stdout   */
  setbuf (stderr, NULL);    /* do not buffer the output to stderr   */

  printf ("%s Version %s\n", MMSLITE_NAME, MMSLITE_VERSION);
#if defined(S_SEC_ENABLED)
  printf ("%s Version %s\n", S_SEC_LITESECURE_NAME, S_SEC_LITESECURE_VERSION_STR);
#endif
  puts (MMSLITE_COPYRIGHT);

#if defined(NO_GLB_VAR_INIT)
  mvl_init_glb_vars ();
#endif
  init_mem ();		/* Set up memory allocation tools 		*/
  init_log_cfg ();	/* Set up logging subsystem			*/

  SLOGALWAYS2 ("%s Version %s", MMSLITE_NAME, MMSLITE_VERSION);

  SLOGALWAYS0 ("Initializing ...");
  mvlu_install ();	/* Install UCA object handler			*/

  /* Must set "mvl_max_dyn" members BEFORE mvl_init_mms_objs to		*/
  /* override default maximum values.					*/
  mvl_max_dyn.types = 5000;
  mvl_max_dyn.dom_vars = 200;
   mvl_max_dyn.dom_nvls = 500;

  /* mvl_init_mms_objs must be called before any dynamic object creation*/
  /* It is called automatically by mvl_start_acse, but it may often be	*/
  /* better to init all objects before mvl_start_acse.			*/
  mvl_init_mms_objs ();

  /* Read all object config files (especially SCL) and create all objects.*/
  ret = all_obj_create ("startup.cfg", "datamap.cfg", "datamapout.cfg", &scl_info);
  if (ret != SD_SUCCESS)
    printf ("\n ERROR: Something in SCL or DATAMAP configuration FAILED.");

  /* NOTE: if data in scl_info is not needed, scl_info_destroy may be	*/
  /*   called now to free up resources.					*/

#if defined(S_SEC_ENABLED)
  /* set security configuration file name, MUST be before mvl_start_acse*/
  secManCfgXmlFile = "secmancfg.xml";
#endif  /* defined(S_SEC_ENABLED) */

  init_acse ();		/* Start the lower layer subsystem		*/
  SLOGALWAYS0 ("Initialization complete, entering service loop");

#ifdef SMPVAL_SUPPORT
  /* MSVCB "Volt" configured in sample scl.xml. Try to find it. */
  /* Then find the "SvEna" attribute to use later.		*/
  SvEnaPtr = NULL;	/* NULL indicates "SvEna" not found	*/
  scl_svcb = scl_svcb_find (&scl_info, "Volt", &scl_ld, &scl_ln);
  if (scl_svcb == NULL)
    {
    printf ("Can't find SVCB in SCL configuration. SampledValue messages will not be sent.\n");
    var_with_ms = NULL;
    }
  else
    {
    baseVarName.object_tag = DOM_SPEC;
    baseVarName.domain_id = scl_ld->domName;
    baseVarName.obj_name.item_id = scl_ln->varName;
    var_with_ms = mvl_vmd_find_var (&mvl_vmd, &baseVarName, NULL);
    if (var_with_ms == NULL)
      {
      printf ("Can't find var '%s' containing SVCB. SampledValue messages will not be sent.\n", scl_ln->varName);
      /* NOTE: main loop chks var_with_ms before sending SampledValue msgs.*/
      }
    else
      SvEnaPtr = mvlu_get_leaf_data_ptr (var_with_ms, "MS$Volt$SvEna", &SvEnaRtType);
    }
  /* Automatically enable the the SampledValueControlBlock.	*/
  /* Client may disable it by writing to "SvEna" attribute.	*/
  if (SvEnaPtr)
    *SvEnaPtr = 1;

  etypeInfo.tci     = ETYPE_TCI_SV;
  etypeInfo.etypeID = ETYPE_TYPE_SV;
  /* according to 61850-9-2, APPID must be between 0x4000 and 0x7FFF	*/
  /* Default value if not configured is 0x4000.				*/
  etypeInfo.appID   = 0x4000;	/* use default value	*/
  if (scl_svcb)
    nofASDU = scl_svcb->nofASDU;
  else
    nofASDU = 1;	/* couldn't find configured num, so assume 1	*/
  smpvalMsg = smpval_msg_create (nofASDU);

#if (SD_BYTE_ORDER==SD_LITTLE_ENDIAN)
  {
  ST_INT j;
  for (j = 0; j < 16; j++)
    {	/* Odd entries are Quality. No need to reverse bytes.	*/
    if (j % 2)
      SampleDataConverted [j] = SampleData [j];	/* Quality	*/
    else
      reverse_bytes ((ST_UINT8 *) &SampleDataConverted[j],
                     (ST_UINT8 *) &SampleData[j], 4);
    }
  }
#endif
#endif	/* SMPVAL_SUPPORT	*/

/* Set the ^c catcher */
  signal (SIGINT, ctrlCfun);

/* We are all initialized, just service communications			*/
  chk_malloc (1);	/* Marker					*/
  printf ("\n Entering 'server' mode, hit ^c to exit ... \n");

  dyn_mem_ptr_status ();	/* Log memory allocation usage		*/

  /* We want to know about connection activity */
  u_mvl_disc_ind_fun = disc_ind_fun;

  while (doIt)
    {
    wait_any_event (100);	/* keep this short so reporting is fast	*/
    while (mvl_comm_serve ())	/* Perform communications service	*/
      {
      }
    mvl61850_rpt_service ();	/* process IEC 61850 reports	*/

#ifdef SMPVAL_SUPPORT
    /* If enabled (i.e. SvEna=TRUE), send SMPVAL message when smpRate expires.*/
    /* NOTE: lastTime started at 0, so first msg sent immediately.	*/
    /* NOTE: timing will not exactly match smpRate because of wait_any_event.*/

    if (SvEnaPtr && *SvEnaPtr != 0)	/* got data ptr earlier. Just chk value*/
      {
      currTime = sGetMsTime();
      if (currTime > lastTime + scl_svcb->smpRate)
        {
        lastTime = currTime;
        test_smpval_msg_send (smpvalMsg, scl_svcb, &SmpCnt, &etypeInfo);
        }
      }
#endif	/* SMPVAL_SUPPORT	*/

#if defined(S_SEC_ENABLED)
    /* check for security configuration updates */
    if (ulCheckSecurityConfiguration () != SD_SUCCESS)
      printf("\n Security Reconfiguration failed\n");
#endif /* defined(S_SEC_ENABLED) */

#if defined(DEBUG_SISCO)
    if (sLogCtrl->logCtrl & LOG_IPC_EN)
      slogIpcEvent ();	/* required for IPC Logging if gensock2.c is	*/
    			/* not compiled with GENSOCK_THREAD_SUPPORT	*/
#endif
    }

#ifdef SMPVAL_SUPPORT
  smpval_msg_destroy (smpvalMsg);
#endif

  ret = mvl_end_acse ();	/* Stop the lower layer subsystem	*/

  scl_info_destroy (&scl_info);	/* Destroy all stored SCL info		*/
				/* could be done earlier if SCL info not needed*/

  all_obj_destroy ();		/* Destroy all MMS objects.		*/

  /* If cleanup worked, number of types logged here should be 0.	*/
  SLOGALWAYS1 ("DEBUG: Number of types in use after cleanup=%d", mvl_type_count ());

  dyn_mem_ptr_status ();	/* Log memory allocation usage		*/

#if defined(DEBUG_SISCO)
  /* terminate logging services and save current log file position */
  slog_end (sLogCtrl);
#endif

  printf ("\n\n");

  return (0);
  }

/************************************************************************/
/************************************************************************/
/* INDICATION HANDLING FUNCTIONS					*/
/************************************************************************/
/*			u_mvl_ident_ind					*/
/************************************************************************/

ST_VOID u_mvl_ident_ind (MVL_IND_PEND *indCtrl)
  {
  indCtrl->u.ident.resp_info = &identify_response_info;
  mplas_ident_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_status_ind				*/
/************************************************************************/

ST_VOID u_mvl_status_ind (MVL_IND_PEND *indCtrl)
  {
  indCtrl->u.status.resp_info = &status_resp_info;
  mplas_status_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_getdom_ind				*/
/************************************************************************/

ST_VOID u_mvl_getdom_ind (MVL_IND_PEND *indCtrl)
  {
  mvlas_getdom_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_getvlist_ind				*/
/************************************************************************/

ST_VOID u_mvl_getvlist_ind (MVL_IND_PEND *indCtrl)
  {
  mvlas_getvlist_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_getvar_ind				*/
/************************************************************************/

ST_VOID u_mvl_getvar_ind (MVL_IND_PEND *indCtrl)
  {
  mvlas_getvar_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_namelist_ind				*/
/************************************************************************/

ST_VOID u_mvl_namelist_ind (MVL_IND_PEND *indCtrl)
  {
  mvlas_namelist_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_defvlist_ind				*/
/************************************************************************/

ST_VOID u_mvl_defvlist_ind (MVL_IND_PEND *indCtrl)
  {
  mvlas_defvlist_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_delvlist_ind				*/
/************************************************************************/
ST_VOID u_mvl_delvlist_ind (MVL_IND_PEND *indCtrl)
  {
  mvlas_delvlist_resp (indCtrl);
  }

/************************************************************************/
/*			u_mvl_getcl_ind					*/
/************************************************************************/
ST_VOID u_mvl_getcl_ind (MVL_IND_PEND *ind)
  {
ST_INT16 num_of_capab;
GETCL_RESP_INFO *info;	/* Same as "ind->u.getcl.resp_info".	*/
			/* Only used to simpify filling it in.	*/
ST_CHAR **capab_list;

  num_of_capab = 4;
  /* Allocate space for Resp struct AND array of pointers to capabilities.*/
  info = ind->u.getcl.resp_info = chk_malloc (sizeof(GETCL_RESP_INFO) +
                                         num_of_capab * sizeof(ST_CHAR *));

  /* Fill in response structure.		*/
  info->more_follows = SD_FALSE;
  info->num_of_capab = num_of_capab;

  /* Fill in array of ptrs to capabilities.	*/
  capab_list = (ST_CHAR **) (info + 1);	/* Point after struct.	*/
  if (num_of_capab > 0)
    capab_list [0] = "SampleCapability_0";
  if (num_of_capab > 1)
    capab_list [1] = "SampleCapability_1";
  if (num_of_capab > 2)
    capab_list [2] = "SampleCapability_2";
  if (num_of_capab > 3)
    capab_list [3] = "SampleCapability_3";

  mplas_getcl_resp (ind);	/* Primitive		*/
  chk_free (info);		/* Done with struct, so free it.	*/
  }

/************************************************************************/
/*			u_mvl_concl_ind					*/
/************************************************************************/
ST_VOID u_mvl_concl_ind (MVL_COMM_EVENT *event)
  {
  /* This function should do all appropriate cleanup before sending the	*/
  /* Conclude response.							*/
  mplas_concl_resp (event);	/* Send response.	*/
  }

/************************************************************************/
/************************************************************************/
/* CONNECTION MANAGEMENT FUNCTIONS					*/
/************************************************************************/
/*			connect_ind_fun					*/
/************************************************************************/
/* This function is called when a remote node has connected to us. We	*/
/* can look at the assReqInfo to see who it is (assuming that the 	*/
/* AE-Titles are used), or at the cc->rem_init_info to see initiate 	*/
/* request parameters.							*/

static ST_INT  connect_ind_fun (MVL_NET_INFO *cc, INIT_INFO *init_info)
  {
static INIT_INFO initRespInfo;

  initRespInfo.mms_p_context_pres = SD_TRUE;
  initRespInfo.max_segsize_pres = SD_TRUE;
  initRespInfo.max_segsize = mvl_cfg_info->max_msg_size;
  initRespInfo.maxreq_calling = 1;
  initRespInfo.maxreq_called = 3;
  initRespInfo.max_nest_pres = SD_TRUE;
  initRespInfo.max_nest = 5;
  initRespInfo.mms_detail_pres = SD_TRUE;
  initRespInfo.version = 1;
  initRespInfo.num_cs_init = 0;
  initRespInfo.core_position = 0;
  initRespInfo.param_supp[0] = m_param[0];
  initRespInfo.param_supp[1] = m_param[1];
  memcpy (initRespInfo.serv_supp, m_service_resp,11);

  mvl_init_resp_info = &initRespInfo;
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			u_mvl_connect_ind_ex				*/
/************************************************************************/
/* This function is called when a remote node has connected to us and	*/
/* requires us to look at the authentication info sent to us in the	*/
/* req_auth_info pointer. After we have verified ACSE authentication, we*/
/* can fill out an authentication structure of our own to send to our   */
/* partner and continue processing the connection normally.		*/

ST_ACSE_AUTH u_mvl_connect_ind_ex (MVL_NET_INFO *cc, INIT_INFO *init_info,
            ACSE_AUTH_INFO *req_auth_info, ACSE_AUTH_INFO *rsp_auth_info)
  {
ST_RET ret;

#if defined(S_SEC_ENABLED)
  ret = ulCheckSecureAssocInd (cc, rsp_auth_info);
  if (ret != ACSE_AUTH_SUCCESS)
    {
    printf ("\n Connection not authenticated");
    return ((ST_ACSE_AUTH) ret);
    }
#elif defined(ACSE_AUTH_ENABLED)
  if(req_auth_info->auth_pres == SD_TRUE)
    {
    /* Looks like we have some authentication to look at, simply print  */
    /* the password and continue as normal.				*/
    if(req_auth_info->mech_type == ACSE_AUTH_MECH_PASSWORD)
      {
      printf("\nPassword received from peer: %s\n", req_auth_info->u.pw_auth.password);
      }
    /* We were sent a mechanism we don't support, let's reject the 	*/
    /* the connection with the appropriate diagnostic.			*/
    else
      {
      return ACSE_DIAG_AUTH_MECH_NAME_NOT_RECOGNIZED;
      }
    }
  else
    {
    /* Hmm... looks like we weren't sent any authentication even though */
    /* we require it. Let's reject with the appropriate diagnostic.	*/
    return ACSE_DIAG_AUTH_REQUIRED;
    }
  
  /* Fill out a response authentication structure, must use the pointer */
  /* provided to us here.						*/
  rsp_auth_info->auth_pres = SD_TRUE;
  rsp_auth_info->mech_type = ACSE_AUTH_MECH_PASSWORD;
  /* this is the password */
  strcpy(rsp_auth_info->u.pw_auth.password, "secret");
#endif /* defined(ACSE_AUTH_ENABLED) */
  
  /* Now proceed processing the connection as normal */   
  ret = connect_ind_fun(cc, init_info);
  
  if (ret == SD_SUCCESS)
    return ACSE_AUTH_SUCCESS;
  else
    return ACSE_DIAG_NO_REASON;
  }

/************************************************************************/
/*			disc_ind_fun					*/
/************************************************************************/
/* This function is called when connection is terminated.		*/

static ST_VOID disc_ind_fun (MVL_NET_INFO *cc, ST_INT discType)
  {
  printf ("disconnect indication received.\n");
  mvlu_clr_pend_sbo (cc);
  }

/************************************************************************/
/************************************************************************/
/* INITIALIZATION FUNCTIONS 						*/
/************************************************************************/

/************************************************************************/
/*				init_acse				*/
/************************************************************************/

static ST_VOID init_acse ()
  {
ST_RET ret;
MVL_CFG_INFO mvlCfg;

/* We want to know about connection activity				*/
  u_mvl_disc_ind_fun     = disc_ind_fun;
  
#if defined(HARD_CODED_CFG)
  num_loc_dib_entries = sizeof(localDibTable)/sizeof(DIB_ENTRY);
  loc_dib_table = localDibTable;
  num_rem_dib_entries = 0;

/* Only call config functions necessary for stack being used.	*/
#error Please remove this line when you have selected your configuration functions below.
#if 0
  adlcConfigure();	/* TRIM-7(over ADLC)/REDUCED STACK	*/
  tp4_config();		/* OSI/RFC1006/TRIM-7			*/
  clnp_config();	/* OSI/TRIM-7				*/
#endif
  /* Fill in mvlCfg.	*/
  mvlCfg.num_calling = 0;
  mvlCfg.num_called = 4;
  mvlCfg.max_msg_size = 8000;
  strcpy (mvlCfg.local_ar_name, "local1");
#else
  ret = osicfgx ("osicfg.xml", &mvlCfg);	/* This fills in mvlCfg	*/
  if (ret != SD_SUCCESS)
    {
    printf ("Stack configuration failed, err = 0x%X. Check configuration.\n", ret );
    exit (1);
    }
#endif  /* end #if defined(HARD_CODED_CFG) */


  ret = mvl_start_acse (&mvlCfg);	/* MAKE SURE mvlCfg is filled in*/
  if (ret != SD_SUCCESS)
    {
    printf ("mvl_start_acse () failed, err = %d.\n", ret );
    exit (1);
    }
  }

/************************************************************************/
/*			init_log_cfg					*/
/************************************************************************/
static ST_VOID init_log_cfg (ST_VOID)
  {
#ifdef DEBUG_SISCO

#if defined (HARD_CODED_CFG)
/* Use File logging							*/
  sLogCtrl->logCtrl = LOG_FILE_EN;

/* Use time/date time log						*/
  sLogCtrl->logCtrl |= LOG_TIME_EN;
  sLogCtrl->logCtrl |= LOG_DIFFTIME_EN;

/* File Logging Control defaults 					*/
  sLogCtrl->fc.fileName = "uca_srvr.log";
  sLogCtrl->fc.maxSize = 1000000L;
  sLogCtrl->fc.ctrl = (FIL_CTRL_WIPE_EN | 
                 FIL_CTRL_WRAP_EN | 
		 FIL_CTRL_NO_APPEND |
                 FIL_CTRL_MSG_HDR_EN);

  asn1_debug_sel |= ASN1_LOG_ERR;
  asn1_debug_sel |= ASN1_LOG_NERR;
#if 0
  asn1_debug_sel |= ASN1_LOG_DEC;
  asn1_debug_sel |= ASN1_LOG_ENC;
#endif

  mms_debug_sel |= MMS_LOG_NERR;
#if 0
  mms_debug_sel |= MMS_LOG_PDU;
  mms_debug_sel |= MMS_LOG_USR_CONF;
  mms_debug_sel |= MMS_LOG_USR_IND;
#endif

  mvl_debug_sel |= MVLLOG_ERR;
  mvl_debug_sel |= MVLLOG_NERR;
#if 0
  mvl_debug_sel |= MVLLOG_TIMING;
  mvl_debug_sel |= MVLLOG_ACSE;
  mvl_debug_sel |= MVLLOG_ACSEDATA;
  mvl_debug_sel |= MVLULOG_FLOW;
#endif

  acse_debug_sel |= ACSE_LOG_ERR;
#if 0
  acse_debug_sel |= ACSE_LOG_ENC;
  acse_debug_sel |= ACSE_LOG_DEC;
  acse_debug_sel |= COPP_LOG_ERR;
  acse_debug_sel |= COPP_LOG_DEC;
  acse_debug_sel |= COPP_LOG_DEC_HEX;
  acse_debug_sel |= COPP_LOG_ENC;
  acse_debug_sel |= COPP_LOG_ENC_HEX;
  acse_debug_sel |= COSP_LOG_ERR;
  acse_debug_sel |= COSP_LOG_DEC;
  acse_debug_sel |= COSP_LOG_DEC_HEX;
  acse_debug_sel |= COSP_LOG_ENC;
  acse_debug_sel |= COSP_LOG_ENC_HEX;
#endif


  tp4_debug_sel |= TP4_LOG_ERR;
#if 0
  tp4_debug_sel |= TP4_LOG_FLOWUP;
  tp4_debug_sel |= TP4_LOG_FLOWDOWN;
#endif

#if 0
  clnp_debug_sel |= CLNP_LOG_ERR;
  clnp_debug_sel |= CLNP_LOG_NERR;
  clnp_debug_sel |= CLNP_LOG_REQ;
  clnp_debug_sel |= CLNP_LOG_IND;
  clnp_debug_sel |= CLNP_LOG_ENC_DEC;
  clnp_debug_sel |= CLNP_LOG_LLC_ENC_DEC;
  clnp_debug_sel |= CLSNS_LOG_REQ;
  clnp_debug_sel |= CLSNS_LOG_IND;
#endif

#if defined(UCA_SMP)
  smp_debug_sel |= SMP_LOG_ERR;
  smp_debug_sel |= SMP_LOG_IND;
  smp_debug_sel |= SMP_LOG_REQ;
#endif

  chk_debug_en |= MEM_LOG_ERR;

#if 0
  chk_debug_en |= MEM_LOG_CALLOC;
  chk_debug_en |= MEM_LOG_MALLOC;
  chk_debug_en |= MEM_LOG_REALLOC;
  chk_debug_en |= MEM_LOG_FREE;
#endif

#else	/* !defined (HARD_CODED_CFG)	*/
#if defined(S_SEC_ENABLED)
  logCfgAddMaskGroup (&secLogMaskMapCtrl);
  logCfgAddMaskGroup (&ssleLogMaskMapCtrl);
#endif
  logCfgAddMaskGroup (&mvlLogMaskMapCtrl);
  logCfgAddMaskGroup (&mmsLogMaskMapCtrl);
  logCfgAddMaskGroup (&acseLogMaskMapCtrl);
  logCfgAddMaskGroup (&tp4LogMaskMapCtrl);
  logCfgAddMaskGroup (&clnpLogMaskMapCtrl);
  logCfgAddMaskGroup (&asn1LogMaskMapCtrl);
  logCfgAddMaskGroup (&sxLogMaskMapCtrl);
#if defined(S_MT_SUPPORT)
  logCfgAddMaskGroup (&gsLogMaskMapCtrl);
#endif
  logCfgAddMaskGroup (&sockLogMaskMapCtrl);
  logCfgAddMaskGroup (&memLogMaskMapCtrl);
  logCfgAddMaskGroup (&memDebugMapCtrl);

  if (logcfgx_ex (sLogCtrl, "logcfg.xml", NULL, SD_FALSE, SD_FALSE) != SD_SUCCESS)
    {
    printf ("\n Parsing of 'logging' configuration file failed.");
    if (sLogCtrl->fc.fileName)
      printf ("\n Check log file '%s'.", sLogCtrl->fc.fileName);
    exit (5);
    }
#endif	/* !defined (HARD_CODED_CFG)	*/

  slog_start (sLogCtrl, MAX_LOG_SIZE);  /* call after logging parameters are configured	*/

#endif  /* DEBUG_SISCO */
  }


/************************************************************************/
/************************************************************************/
/*				init_mem				*/
/************************************************************************/

static ST_VOID mem_chk_error_detected (ST_VOID);
static ST_VOID *my_malloc_err (ST_UINT size);
static ST_VOID *my_calloc_err (ST_UINT num, ST_UINT size);
static ST_VOID *my_realloc_err (ST_VOID *old, ST_UINT size);

static ST_CHAR *spareMem;

static ST_VOID init_mem ()
  {

/* Allocate spare memory to allow logging/printing memory errors	*/
  spareMem = malloc (500);

/* trap mem_chk errors							*/
  mem_chk_err = mem_chk_error_detected;
  m_memerr_fun = my_malloc_err;
  c_memerr_fun = my_calloc_err;
  r_memerr_fun = my_realloc_err;

#if 0
  m_heap_check_enable = SD_TRUE;
  m_check_list_enable = SD_TRUE;
  m_no_realloc_smaller = SD_TRUE;
  m_fill_en = SD_TRUE;
#endif
  m_mem_debug = SD_TRUE;

  }

/************************************************************************/
/* This function is called from the DEBUG version of the mem library	*/
/* when an error of any type is detected.				*/
/************************************************************************/

static ST_INT memErrDetected;

static ST_VOID mem_chk_error_detected (ST_VOID)
  {
  if (!memErrDetected)
    {
    free (spareMem);
    memErrDetected = SD_TRUE;
    printf ("\n Memory Error Detected!");
    dyn_mem_ptr_status ();
    }
  }

/************************************************************************/
/* Memory Allocation Error Handling Functions.				*/
/* These functions are called from mem_chk when it is unable to 	*/
/* perform the requested operation. These functions must either return 	*/
/* a valid buffer or not return at all.					*/
/************************************************************************/

static ST_VOID *my_malloc_err (ST_UINT size)
  {
  mem_chk_error_detected ();
  printf ("\n Malloc");
  exit (2);
  return (NULL);   
  }

static ST_VOID *my_calloc_err (ST_UINT num, ST_UINT size)
  {
  mem_chk_error_detected ();
  exit (3);
  return (NULL);   
  }

static ST_VOID *my_realloc_err (ST_VOID *old, ST_UINT size)
  {
  mem_chk_error_detected ();
  exit (4);
  return (NULL);   
  }

/************************************************************************/
/* MISC. FUNCTIONS							*/
/************************************************************************/
/************************************************************************/
/*				ctrlCfun				*/
/************************************************************************/
/* This function handles the ^c, and allows us to cleanup on exit	*/

ST_VOID ctrlCfun (int i)
  {
  doIt = SD_FALSE;
  }

/************************************************************************/
/************************************************************************/
#if defined MVLU_LEAF_FUN_LOOKUP_ENABLE
/************************************************************************/
/* DYNAMIC LEAF ACCESS PARAMETER MANIPULATION				*/
/************************************************************************/
/*			u_mvlu_resolve_leaf_ref				*/
/************************************************************************/
/* This callback function is invoked from within the MVLU LAP file	*/
/* load function mvlu_load_xml_leaf_file from mvlu_set_leaf_param_name.	*/

/* We are to provide the leaf reference value for the named leaf via	*/
/* the outparameter refOut, nominally by looking at the reference text	*/
/* that is passed to us.						*/

/* The bit masked input/output parameter setFlagsIo tells us whether	*/
/* the reference text was present in the LAP file, and we can set or	*/
/* clear the bit to control whether the reference value is written.	*/

ST_RET u_mvlu_resolve_leaf_ref (ST_CHAR *leafName, ST_INT *setFlagsIo, 
				ST_CHAR *refText, ST_RTREF *refOut)
  {
ST_CHAR *p;

/* Note: In this example  we won't really set the reference, because 	*/
/* the references we need are already set in the leaf at compile time 	*/
/* by the Foundry LAP input file					*/

/* First let's see if the reference text was provided 			*/
  if (*setFlagsIo & MVLU_SET_REF)
    {
  /* The refText text was provided in the LAP file.			*/
  /* We need to check for a special PREFIX (used especially for SBO).	*/
    if (!strncmp (refText, MVLU_STRING_REF_PREFIX, strlen (MVLU_STRING_REF_PREFIX)))
      {		/* Write everything after PREFIX as quoted string.	*/
      p = refText + strlen(MVLU_STRING_REF_PREFIX);
      *refOut = (ST_RTREF) chk_strdup (p);
      }
    else	/* If no PREFIX, we don't handle it.			*/
      *setFlagsIo &= ~MVLU_SET_REF;
    }
  else
    {
  /* The refText text was NOT provided in the LAP file.			*/
  /* If we wanted, we could still provide a reference to be used ...	*/
#if 0
    *refOut = (ST_RTREF) 0;
    *setFlagsIo |= MVLU_SET_REF;
#endif
    }

/* We always return success, otherwise the LAP will not be set		*/
  return (SD_SUCCESS);
  }
#endif

/************************************************************************/
/*			u_mvlu_rpt_time_get				*/
/* UCA/IEC reporting callback function to get accurate rpt time.	*/
/* If UCA/IEC Reports are enabled, user must provide this function.	*/
/************************************************************************/
ST_VOID u_mvlu_rpt_time_get (MMS_BTIME6 *TimeOfEntry)
  {
#if 1	/* This is a very simple example using the standard "time" fct.	*/
STDTIME                  stdTime;   

/* This should be GMT time.  61850 now says all Btime6 values must be   */
/* based on GMT.                                                        */

   GetStdTime (&stdTime);          /* if GMT time needed  */
   StdTimeToMmsTimeOfDay6 (&stdTime, TimeOfEntry);  

#else	/* This is simplest possible code if user doesn't care about time.*/
  TimeOfEntry->ms = 0;
  TimeOfEntry->day = 0;
#endif
  return;
  }

/* NOTE: these leaf functions copied from rdwrind.c. Can't use whole file.*/

/************************************************************************/
/* 		'NO WRITE ALLOWED' WRITE HANDLER			*/
/************************************************************************/
ST_VOID u_no_write_allowed (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
  mvluWrVaCtrl->wrVaCtrl->failure = ARE_OBJ_ACCESS_DENIED;	/* send in rsp*/
  mvlu_wr_prim_done (mvluWrVaCtrl, SD_FAILURE);
  }
/************************************************************************/
/*			u_mvl_sbo_operate				*/
/************************************************************************/
ST_VOID  u_mvl_sbo_operate (MVL_SBO_CTRL *sboSelect, 
			    MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
MVL_VAR_ASSOC *va;
ST_CHAR *src;

  /* The select is in place, go ahead and operate ... 			*/
  va = mvluWrVaCtrl->wrVaCtrl->va;
  src = mvluWrVaCtrl->primData;

  mvlu_wr_prim_done (mvluWrVaCtrl, SD_SUCCESS);
  }

/************************************************************************/
/*			all_obj_create					*/
/* Read all object configuration files (especially SCL) and create all	*/
/* objects.								*/
/************************************************************************/
ST_RET all_obj_create (ST_CHAR *startup_cfg_filename,
	ST_CHAR *datamap_cfg_filename,
	ST_CHAR *datamap_cfg_out_filename,
	SCL_INFO *scl_info)
  {
ST_RET ret;
STARTUP_CFG startup_cfg;	/* info from "startup.cfg" file		*/
ST_INT brcb_bufsize=1000000;	/* DEBUG: add to "startup.cfg"?		*/
ST_DOUBLE mstime;

  ret = startup_cfg_read (startup_cfg_filename, &startup_cfg);

  mstime =sGetMsTime ();
  if (ret == SD_SUCCESS)
    ret = scl_parse (startup_cfg.scl_filename,
         startup_cfg.ied_name,			/* IED name	*/
         startup_cfg.access_point_name,		/* AccessPoint	*/
         scl_info);
  printf ("scl_parse time = %f\n", sGetMsTime() - mstime);

  /* Create types only if everything successful up to now.	*/
  if (ret == SD_SUCCESS)
    {
    /* CRITICAL: This saves the type_id in each SCL_LN struct.	*/
    /*           Must not call again with same "scl_info".	*/
    ret = scl2_datatype_create_all (&mvl_vmd, scl_info, 14000,
               SD_FALSE,	/* type names not generated	*/
               NULL);		/* type name prefix (not used)	*/
    }

  /* Create variables only if everything successful up to now.	*/
  if (ret == SD_SUCCESS)
    ret = scl2_ld_create_all (&mvl_vmd, scl_info, startup_cfg.report_scan_rate, brcb_bufsize,
              SD_FALSE);	/* create "server" model	*/

  /* Map MMS data to user data by reading user data mapping file.	*/
  if (ret == SD_SUCCESS)
    ret = datamap_cfg_read (datamap_cfg_filename, datamap_cfg_out_filename);

  return (ret);
  }

/************************************************************************/
/*			all_obj_destroy					*/
/* Destroy all objects created by all_obj_create.			*/
/************************************************************************/
ST_RET all_obj_destroy ()
  {
ST_RET ret;
  /* CRITICAL: datamap_cfg_destroy must be called BEFORE mvl_vmd_destroy*/
  /*           if datamap_cfg_read was called at startup.		*/
  datamap_cfg_destroy ();
  mvl61850_rpt_ctrl_destroy_all ();	/* destroy rpt_ctrls before VMD	*/
  ret = mvl_vmd_destroy (&mvl_vmd);	/* destroy global VMD	*/
  return (ret);
  }


/************************************************************************/
/*			u_mvl61850_ctl_oper_begin			*/
/* Sample user callback function.					*/
/************************************************************************/
ST_VOID u_mvl61850_ctl_oper_begin (ST_CHAR *oper_ref)
  {
  }
/************************************************************************/
/*			u_mvl61850_ctl_oper_end				*/
/* Sample user callback function.					*/
/* This sample simply sends a "CommandTermination" if "ctlModel"	*/
/* indicates "enhanced security".					*/
/* NOTE: a real application should not send the CommandTermination until*/
/*	the control operation completes.				*/
/************************************************************************/
ST_VOID u_mvl61850_ctl_oper_end (MVL_NET_INFO *net_info, ST_CHAR *oper_ref, MVL_VAR_ASSOC *base_var)
  {
ST_RET retcode;
MVL61850_LAST_APPL_ERROR last_appl_error;
ST_CHAR ctlmodel_name [MAX_IDENT_LEN + 1];
ST_INT8 ctlModel;
/* DEBUG: use statics here so value can be changed on each call*/
static ST_RET completion_status = SD_SUCCESS;
static ST_INT8 dummyError = 0;
static ST_INT8 dummyAddCause = 10;

  if (mvl61850_mkname_ctlmodel (oper_ref, ctlmodel_name, MAX_IDENT_LEN) == SD_SUCCESS
      && mvlu_get_leaf_val_int8 (base_var, ctlmodel_name, &ctlModel) == SD_SUCCESS)
    {
    if (ctlModel == MVL61850_CTLMODEL_DIRECT_ENHANCED
        || ctlModel == MVL61850_CTLMODEL_SBO_ENHANCED)
      {
      /* DEBUG: For testing purposes only, change status for each CommandTermination.*/
      completion_status = (completion_status == SD_SUCCESS) ? SD_FAILURE : SD_SUCCESS;

      if (completion_status!=SD_SUCCESS)
        {
        /* last_appl_error must contain valid data. Set appropriate values here.*/
        memset (&last_appl_error, 0, sizeof (MVL61850_LAST_APPL_ERROR));
        strcpy (last_appl_error.CntrlObj, oper_ref);
        last_appl_error.Error = dummyError++;	/* DEBUG: For testing, chg on each call*/
        last_appl_error.AddCause = dummyAddCause++;
        }

      retcode = mvl61850_ctl_command_termination (net_info, oper_ref,
              completion_status,
              &last_appl_error);
      }
    }
  }

/************************************************************************/
/*			u_mvl_scl_set_initial_value			*/
/* Called during SCL processing to convert initial value text to data.	*/
/* NOTE: only called if MVL library conversion fails.			*/
/************************************************************************/
ST_RET u_mvl_scl_set_initial_value (SCL2_IV_TRANSLATE_CTRL *translate)
  {
#if 0
  /* The MVL library already calls sxaTextToLocal for most data.	*/
  /* If that fails, user might want to try different conversion		*/
  /* function, but the call might be similar to this.			*/
  return (sxaTextToLocal (translate->valText, translate->dest,
          translate->numRt, translate->rtHead));
#else
  SLOGALWAYS1 ("Error converting Val '%s' from SCL file to data.", translate->valText);
  return (SD_FAILURE);	/* this will cause SCL processing to stop	*/
#endif
  }
