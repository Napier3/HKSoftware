/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*          2000 - 2006, All Rights Reserved                            */
/*                                                                      */
/* MODULE NAME : logcfgx.c                                              */
/* PRODUCT(S)  :                                                        */
/*                                                                      */
/* MODULE DESCRIPTION :    This module processes each value parsed in   */
/*                         the logcfg.xml file .  The logcfg.xml file   */
/*                         assigns Log File Attributes and              */
/*                         Miscellaneous Control Flags as well as       */
/*                         Memory Use Logging and various Log Masks     */
/*                         to enable specific logging required.         */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev          Comments                                */
/* --------  ---  ------  --------------------------------------------  */
/* 01/03/09  MDE    42    Added SSEAL parameters    			*/
/* 11/07/08  MDE    41    Added 'Get Log Masks' feature support		*/
/* 09/09/08  MDE    40    Fixed problems with NULL destLogCtrl		*/
/* 08/11/08  MDE    39    Added set 'initialized' 			*/
/* 08/04/08  MDE    38    Now call slogIpcEventEx			*/
/* 07/25/08  MDE    37    Moved slogIpcCtx into LOG_CTRL		*/
/* 04/24/08  MDE    36    In fopen, removed 't' (not ANSI)		*/
/* 05/12/08  RKR    35    Fixed slog_ipc_std_cmd_service arg list,      */
/* 			  Added clone, reset, remote log message 	*/
/* 04/24/08  MDE    34    In slog_ipc_std_cmd_service, use text mode	*/
/* 04/07/08  MDE    33    Changed slog_ipc_std_cmd_service to reconnect	*/
/* 03/10/08  MDE    32    Added slog_ipc_std_cmd_service		*/
/* 03/05/08  JRB    31    Put #ifdef DEBUG_SISCO around entire file.	*/
/* 02/25/08  MDE    30    Rearranged table entries 			*/
/* 12/19/07  MDE    29    Fixed duplicate LOGCFGX_TAG_VAL on reload	*/
/* 10/29/07  JRB    28    strncat_safe obsolete, use strncat_maxstrlen.	*/
/* 10/23/07  MDE    27    Added ElapsedTime option 			*/
/* 10/10/07  MDE    26    Turn on timestamps by default, add tag	*/
/* 10/04/07  MDE    25    Fixed up preferred tag handling, etc.. 	*/
/* 05/30/07  MDE    24    Save tag values better			*/
/* 03/12/07  MDE    23    Added 'LogIpcEditLogCfg' 			*/
/* 07/28/06  MDE    22    Fixed logCfgClearTagVals			*/
/* 07/17/06  EJV    21    Add logCfgCallbackFunTYPE to avoid warnings.	*/
/* 04/03/06  RKR    20    Declare "tagVal" specific to DEBUT_SISCO      */
/* 03/21/06  GLB    19    Modify LOGCFGX_STATE_.. values         	*/
/* 03/03/06  EJV    18    AVOID using constants (use sizeof instead).	*/
/* 03/02/06  MDE    17    Fixed case where logCtrl == NULL		*/
/* 02/06/06  MDE    16    Added logcfg_exx, tagPath, etc.		*/
/* 02/02/06  EJV    15    _logcfg_data_end: corr _LOGCFG_DATATYPE_DOUBLE*/
/*			    Separated handling for signed and unsigned.	*/
/* 10/31/05  EJV    14    sx_get_... can fail, check for return.	*/
/*			  Use sx_parseExx_mt instead of sx_parseEx_mt.	*/
/*			  Chg sx_debug_sel_save.Revised _logcfg_data_end*/
/* 08/10/05  MDE    13    Added logCfgRemoveAllMaskGroups		*/
/* 06/21/05  EJV    12    Deleted obsolete logcfgx function.		*/
/* 05/23/05  EJV    11    Moved xxxLogMaskMapCtrl to respective C files.*/
/*			  Del m_track_prev_free (not used anymore).	*/
/*			  Force user to use logcfgx_ex insted of logcfgx*/
/* 04/25/05  MDE    10    Added MMS_LOG_CLIENT & MMS_LOG_SERVER		*/
/* 03/31/05  MDE    09    Put suicacse.h back, for MAP30_ACSE		*/
/* 03/28/05  JRB    08    Del suicacse header.              		*/
/* 02/10/05  MDE    07    Changed MILOG_ to MI_LOG_			*/
/* 02/10/05  MDE    06    Added new DATATYPE's				*/
/* 01/27/05  MDE    05    DEBUG_SISCO #ifdefs, LINUX warning cleanup	*/
/* 01/20/05  MDE    04    Lot's more work ...				*/
/* 12/10/04  ASK    03    Added Slog IPC params, added 			*/
/*		          case _LOGCFG_DATATYPE_UINT32_MASK		*/
/*			  Modify params to use 'R'everse data type	*/
/*                        Update copyright year                         */
/* 11/16/04  MDE    02    Fixed to compile with MAP30_ACSE		*/
/* 10/12/04  MDE    01    Complete rewrite to work with SX changes,     */
/*                        make extendable				*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "gen_list.h"
#include "str_util.h"
#include "glbsem.h"
#include "slog.h"

#include "sx_defs.h"
#include "sx_log.h"
#if defined(DEBUG_SISCO)  /*code in this file needed only if this defined*/

/************************************************************************/

/* For debug version, use a static pointer to avoid duplication of      */
/* __FILE__ strings.                                                    */

#if defined(DEBUG_SISCO)
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/

LOGCFG_VALUE_GROUP *logCfgLogCtrlGroupList;
LOGCFG_VALUE_GROUP *logCfgLogMaskGroupList;
static LOGCFGX_TAG_VAL *_tagValList;

/************************************************************************/
#if defined(DEBUG_SISCO)
static LOG_CTRL tmp_sLogCtrl;

ST_UINT logcfg_debug_sel;

/* Log type strings */
SD_CONST ST_CHAR *SD_CONST _logcfg_log_err_logstr 	= "LOGCFG_ERR";
SD_CONST ST_CHAR *SD_CONST _logcfg_log_nerr_logstr	= "LOGCFG_NERR";
SD_CONST ST_CHAR *SD_CONST _logcfg_log_flow_logstr	= "LOGCFG_FLOW";

LOGCFGX_VALUE_MAP logcfgMaskMaps[] =
  {
    {"LOGCFG_ERR",	LOGCFG_ERR,	&logcfg_debug_sel, _LOGCFG_DATATYPE_UINT_MASK, NULL, "Error"},
    {"LOGCFG_NERR",	LOGCFG_NERR,	&logcfg_debug_sel, _LOGCFG_DATATYPE_UINT_MASK, NULL, "Notice"},
    {"LOGCFG_FLOW",	LOGCFG_FLOW,	&logcfg_debug_sel, _LOGCFG_DATATYPE_UINT_MASK, NULL, "Flow"}
  };

LOGCFG_VALUE_GROUP logcfgMaskMapCtrl =
  {
  {NULL,NULL},
  "LOGCFG",
  sizeof(logcfgMaskMaps)/sizeof(LOGCFGX_VALUE_MAP),
  logcfgMaskMaps
  };

/************************************************************************/
/************************************************************************/

LOGCFGX_VALUE_MAP logCfgLogMaskMaps[] =
  {
/* Common Log Message Formmatting Related */
    {"LogElapsedTime", 		LOG_ELAPSEDTIME_EN, 	&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_UINT32_MASK},
  /* Not frequently used */
    {"HeaderLogTime", 		LOG_TIME_EN, 		&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_RUINT32_MASK},
    {"HeaderCr", 		LOG_NO_HEADER_CR, 	&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_RUINT32_MASK},
    {"HeaderFilename", 		LOG_FILENAME_SUPPRESS, 	&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_RUINT32_MASK},
    {"HeaderLogType", 		LOG_LOGTYPE_SUPPRESS, 	&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_RUINT32_MASK},

/* File Logging Related */
    {"LogFileEnable", 		LOG_FILE_EN, 		&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_UINT32_MASK},
    {"LogFileSize",    		0, 			&tmp_sLogCtrl.fc.maxSize, 	_LOGCFG_DATATYPE_ULONG},
    {"LogFileName",    		0, 			&tmp_sLogCtrl.fc.fileName, 	_LOGCFG_DATATYPE_FILENAME},
    {"DestroyOldFile", 		FIL_CTRL_NO_APPEND, 	&tmp_sLogCtrl.fc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},
    {"HardFlush", 		FIL_CTRL_HARD_FLUSH, 	&tmp_sLogCtrl.fc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},
  /* Not frequently used */
    {"Setbuf", 			FIL_CTRL_SETBUF_EN, 	&tmp_sLogCtrl.fc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},
    {"MsgHeader", 		FIL_CTRL_MSG_HDR_EN, 	&tmp_sLogCtrl.fc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},
    {"Wipe", 			FIL_CTRL_WIPE_EN, 	&tmp_sLogCtrl.fc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},
    {"Wrap", 			FIL_CTRL_WRAP_EN, 	&tmp_sLogCtrl.fc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},

/* IPC Logging Related */
    {"LogIpcAppId", 	        0, 			&tmp_sLogCtrl.ipc.appId, 	_LOGCFG_DATATYPE_STRING},
    {"LogIpcSmartMode", 	LOG_IPC_SMART, 	        &tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_UINT32_MASK},
    {"LogIpcEditLogCfg", 	LOG_IPC_EDIT_LOGCFG,    &tmp_sLogCtrl.ipc.options,	_LOGCFG_DATATYPE_UINT32_MASK},
    {"LogIpcMaxQueCount",       0, 			&tmp_sLogCtrl.ipc.maxQueCnt, 	_LOGCFG_DATATYPE_UINT},
    {"LogIpcSealMode",          0, 			&tmp_sLogCtrl.ipc.sealMode, 	_LOGCFG_DATATYPE_INT},
    {"LogIpcSealTimeWindow",    0, 			&tmp_sLogCtrl.ipc.sealTimeWindow, _LOGCFG_DATATYPE_INT},

  /* Listen */
    {"LogIpcListenEnable", 	LOG_IPC_LISTEN_EN, 	&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_UINT32_MASK},
    {"LogIpcListenPort",        0, 			&tmp_sLogCtrl.ipc.port, 	_LOGCFG_DATATYPE_UINT16},
    {"LogIpcNumListenPorts",    0, 			&tmp_sLogCtrl.ipc.portCnt, 	_LOGCFG_DATATYPE_UINT16},
    {"LogIpcMaxListenConn",     0, 			&tmp_sLogCtrl.ipc.maxConns, 	_LOGCFG_DATATYPE_UINT},

  /* Calling */
    {"LogIpcCallEnable", 	LOG_IPC_CALL_EN, 	&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_UINT32_MASK},
    {"LogIpcCallingPort",       0, 			&tmp_sLogCtrl.ipc.callingPort, 	_LOGCFG_DATATYPE_UINT16},
    {"LogIpcCallingIp",         0, 			&tmp_sLogCtrl.ipc.callingIp, 	_LOGCFG_DATATYPE_STRING},
    {"LogIpcCallingBackoff",    0, 			&tmp_sLogCtrl.ipc.callingBackoff,_LOGCFG_DATATYPE_ULONG},

/* Memory Logging Related */
    {"LogMemoryEnable", 	LOG_MEM_EN, 		&tmp_sLogCtrl.logCtrl, 		_LOGCFG_DATATYPE_UINT32_MASK},
    {"MemoryFileDump", 		MEM_CTRL_AUTODUMP_EN, 	&tmp_sLogCtrl.mc.ctrl, 		_LOGCFG_DATATYPE_UINT_MASK},
    {"LogMemoryItems", 		0, 			&tmp_sLogCtrl.mc.maxItems, 	_LOGCFG_DATATYPE_ULONG},
    {"MemoryFileName", 		0, 			&tmp_sLogCtrl.mc.dumpFileName,	_LOGCFG_DATATYPE_FILENAME},
  };

LOGCFG_VALUE_GROUP logCfgLogCtrlMapCtrl =
  {
  {NULL,NULL},
  "",
  sizeof(logCfgLogMaskMaps)/sizeof(LOGCFGX_VALUE_MAP),
  logCfgLogMaskMaps
  };
#endif /* defined(DEBUG_SISCO) */


/************************************************************************/
/************************************************************************/

static ST_RET _logcfg_data_start (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag);
static ST_RET _logcfg_data_end (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag);

static ST_VOID _logcfg_proc_value_map (SX_DEC_CTRL *sxDecCtrl, 
				       LOGCFG_VALUE_GROUP *slogMaskGroup,
			               LOGCFGX_VALUE_MAP *slogValueMap, 
			               LOGCFGX_TAG_VAL *tagVal);

/************************************************************************/
/*			logCfgAddMaskGroup 				*/
/************************************************************************/

ST_VOID logCfgAddMaskGroup (LOGCFG_VALUE_GROUP *logMaskGroup)
  {
  if (list_find_node (logCfgLogMaskGroupList, logMaskGroup) != SD_SUCCESS)
    list_add_last (&logCfgLogMaskGroupList, logMaskGroup);
  }

/************************************************************************/
/*			logCfgRemoveMaskGroup 				*/
/************************************************************************/

ST_VOID logCfgRemoveMaskGroup (LOGCFG_VALUE_GROUP *logMaskGroup)
  {
  if (list_find_node (logCfgLogMaskGroupList, logMaskGroup) == SD_SUCCESS)
    list_unlink (&logCfgLogMaskGroupList, logMaskGroup);
  }

/************************************************************************/
/*			logCfgRemoveAllMaskGroups			*/
/************************************************************************/

ST_VOID logCfgRemoveAllMaskGroups ()
  {
  logCfgLogMaskGroupList = NULL;
  }

/************************************************************************/
/* 		_logcfg_save_logmasks					*/
/************************************************************************/

ST_RET _logcfg_save_logmasks (ST_CHAR *destFile)
  {
FILE *fp;
ST_INT xmlSize;
ST_CHAR *xmlBuf;
ST_RET rc;
ST_INT bytesWritten;

  xmlSize = _logcfg_get_logmasks_size ();
  xmlSize += SX_ENC_BUFFER_OH;
  xmlBuf = chk_malloc (xmlSize);

  rc = _logcfg_get_logmasks (xmlBuf, &xmlSize);
  if (rc == SD_SUCCESS)
    {
    fp = fopen (destFile, "w");
    if (fp != NULL)
      {
      bytesWritten = fwrite (xmlBuf, 1, xmlSize, fp);
      fclose (fp);
      }
    else
      rc = SD_FAILURE;
    }

  chk_free (xmlBuf);
  return (rc);
  }

/************************************************************************/
/*			_logcfg_get_logmasks				*/
/************************************************************************/

ST_RET _logcfg_get_logmasks (ST_CHAR *xmlBuf, ST_INT *xmlSizeIo)
  {
LOGCFG_VALUE_GROUP *slogMaskGroup;
LOGCFGX_VALUE_MAP  *slogValueMap;
SX_ENC_CTRL         sxEncCtrl;
SXE_ATTR_PAIR       attr[1];
ST_INT              i;
ST_CHAR *v;

  sx_init_encode (&sxEncCtrl, xmlBuf, *xmlSizeIo - SX_ENC_BUFFER_OH);
  sxEncCtrl.bUseFormatting = SD_TRUE;
  sx_start_element (&sxEncCtrl, "LogMasks", 0, NULL);

  slogMaskGroup = logCfgLogMaskGroupList;
  while (slogMaskGroup)
    {
    if ((slogMaskGroup != &memDebugMapCtrl) && 
        (slogMaskGroup != &logcfgMaskMapCtrl))
      {
      sx_start_element (&sxEncCtrl, slogMaskGroup->name, 0, NULL);
      for (i = 0; i < slogMaskGroup->numMaskMap; ++i)
        {
        slogValueMap = &slogMaskGroup->maskMapTbl[i];

      /* Masks with "_ERR" or "_NERR" in them will be On, others Off */       
        v = "Off";
	if ((strstr (slogValueMap->tag, "_ERR") != NULL) ||
	    (strstr (slogValueMap->tag, "_NERR") != NULL))
	  {
          v = "On";
	  }

        if (slogValueMap->preferredTag)
	  {
          attr[0].name  = "desc";
          attr[0].value = slogValueMap->preferredTag;
          sx_wrx_string_el (&sxEncCtrl, slogValueMap->tag, v, 1, attr);
	  }
        else
          sx_wr_string_el (&sxEncCtrl, slogValueMap->tag, v);
        }
      sx_end_element (&sxEncCtrl);
      }
    slogMaskGroup = list_get_next (logCfgLogMaskGroupList, slogMaskGroup);
    }

  sx_end_element (&sxEncCtrl);
  *xmlSizeIo = SX_ENC_LEN (&sxEncCtrl);
  return (sxEncCtrl.errCode);
  }

/************************************************************************/
/*
<LogMasks>n</LogMasks>n
*/
#define _LOGCFG_XML_OH	23

/*
t<>nt</>n
*/
#define _LOGCFG_GROUP_OH 	9

/*
tt<>ntt</>n
*/
#define _LOGCFG_TAG_OH		11

/*
 desc=""
*/
#define _LOGCFG_DESC_OH		8


ST_INT _logcfg_get_logmasks_size ()
  {
ST_INT xmlSize;
LOGCFG_VALUE_GROUP *slogMaskGroup;
LOGCFGX_VALUE_MAP *slogValueMap;
ST_INT i;

  xmlSize = _LOGCFG_XML_OH;
  slogMaskGroup = logCfgLogMaskGroupList;
  while (slogMaskGroup)
    {
    if ((slogMaskGroup != &memDebugMapCtrl) && 
        (slogMaskGroup != &logcfgMaskMapCtrl))
      {
      xmlSize += _LOGCFG_GROUP_OH;
      xmlSize += (2 * strlen (slogMaskGroup->name));
      for (i = 0; i < slogMaskGroup->numMaskMap; ++i)
        {
        slogValueMap = &slogMaskGroup->maskMapTbl[i];
        xmlSize += (_LOGCFG_TAG_OH + (2 * strlen (slogValueMap->tag)));

        if (slogValueMap->preferredTag)
          xmlSize += (_LOGCFG_DESC_OH + strlen (slogValueMap->preferredTag));
        }
      }
    slogMaskGroup = list_get_next (logCfgLogMaskGroupList, slogMaskGroup);
    }
  return (xmlSize);
  }

/************************************************************************/
/************************************************************************/
/*			logCfgFindTagVal				*/
/************************************************************************/

LOGCFGX_TAG_VAL *logCfgFindTagValPath (ST_CHAR *tag)
  {
LOGCFGX_TAG_VAL *tagVal;

  tagVal = _tagValList;
  while (tagVal != NULL)
    {
    if (!strcmp (tag, tagVal->tagPath))
      return (tagVal);

    tagVal = list_get_next (_tagValList, tagVal);
    }
  return (NULL);
  }

/************************************************************************/

LOGCFGX_TAG_VAL *logCfgFindTagVal (ST_CHAR *tag)
  {
LOGCFGX_TAG_VAL *tagVal;

/* First try using the tag path */
  tagVal = logCfgFindTagValPath (tag);
  if (tagVal)
    return (tagVal);

/* No luck, just use the terminal tag */
  tagVal = _tagValList;
  while (tagVal != NULL)
    {
    if (!strcmp (tag, tagVal->tag))
      return (tagVal);

    tagVal = list_get_next (_tagValList, tagVal);
    }
  return (NULL);
  }


/************************************************************************/
/*			logCfgClearTagVals				*/
/************************************************************************/

ST_VOID logCfgClearTagVals ()
  {
LOGCFGX_TAG_VAL *tagVal;

  while (_tagValList)
    {
    tagVal = _tagValList;
    list_unlink (&_tagValList, _tagValList);
    if (tagVal->dataType == _LOGCFG_DATATYPE_STRING || 
        tagVal->dataType == _LOGCFG_DATATYPE_FILENAME)
      {
      chk_free (tagVal->u.str);
      }
    chk_free (tagVal);
    }
  }

/************************************************************************/
/************************************************************************/
/*                                logcfgx_exx                           */
/* User must call logCfgAddMaskGroup for each group of log masks to be	*/
/* configured BEFORE calling this function to parse the file.		*/
/************************************************************************/

#define _LOGCFG_MAX_NAME_LEVEL	10

#define LOGCFGX_STATE_NONE      	0
#define LOGCFGX_STATE_UNKNOWN		1
#define LOGCFGX_STATE_LOGCTRL		2
#define LOGCFGX_STATE_LOOK_COMPNAME	3
#define LOGCFGX_STATE_LOGMASKS		4

typedef struct
  {
  LOG_CTRL *destLogCtrl;
  ST_INT     state;
  ST_CHAR   *logFileName; 
  ST_CHAR   *fileNamePrefix;
  ST_BOOLEAN masksOnly;
  ST_BOOLEAN saveTagVals;
  ST_CHAR   *compName;

  ST_INT    logMaskNestLevel;
  ST_CHAR   logMaskNameStack[_LOGCFG_MAX_NAME_LEVEL][SX_MAX_TAG_LEN+1];
  } LOGCFGX_CTRL;


ST_RET logcfgx_ex (LOG_CTRL *destLogCtrl, ST_CHAR *logFileName, ST_CHAR *fileNamePrefix, 
		   ST_BOOLEAN masksOnly, ST_BOOLEAN saveTagVals)
  {
  return (logcfgx_exx (destLogCtrl, logFileName, fileNamePrefix, 
		       masksOnly, saveTagVals, NULL));
  }		     


ST_RET logcfgx_exx (LOG_CTRL *destLogCtrl, ST_CHAR *logFileName, ST_CHAR *fileNamePrefix, 
		    ST_BOOLEAN masksOnly, ST_BOOLEAN saveTagVals, ST_CHAR *compName)

  {
LOGCFGX_CTRL logCfgxCtrl;
ST_RET rc;
#if defined(DEBUG_SISCO)
LOGCFGX_TAG_VAL *tagVal;
ST_CHAR *savedFileName;
#endif

  logCfgxCtrl.destLogCtrl     = destLogCtrl;
  logCfgxCtrl.logFileName     =	logFileName; 
  if (fileNamePrefix != NULL) 
    logCfgxCtrl.fileNamePrefix  = fileNamePrefix; 
  else
    logCfgxCtrl.fileNamePrefix  =  ""; 

  logCfgxCtrl.masksOnly       =	masksOnly;
  logCfgxCtrl.saveTagVals     =	saveTagVals;
  logCfgxCtrl.compName        =	compName;
  logCfgxCtrl.logMaskNestLevel = 0;
  logCfgxCtrl.state = LOGCFGX_STATE_NONE;   

#if defined(DEBUG_SISCO)
  logcfg_debug_sel |= LOGCFG_ERR;
  logcfg_debug_sel |= LOGCFG_NERR;
  sx_debug_sel     |= SX_LOG_ERR;
  sx_debug_sel     |= SX_LOG_NERR;

  if (logCfgLogCtrlGroupList == NULL)
    list_add_last (&logCfgLogCtrlGroupList, &logCfgLogCtrlMapCtrl);

/* Always allow LOGCFG & SX logging ... */
  logCfgAddMaskGroup (&logcfgMaskMapCtrl);
  logCfgAddMaskGroup (&sxLogMaskMapCtrl);

  if (destLogCtrl != NULL)
    {
    savedFileName = destLogCtrl->fc.fileName;

  /* Copy original "destLogCtrl" to temporary struct which may be modified */
  /* by the configuration.                                              */
  /* This prevents logging control changes while there may be logging.  */

    memcpy (&tmp_sLogCtrl, destLogCtrl, sizeof (LOG_CTRL));
    }

#endif  /* defined(DEBUG_SISCO) */

  if (destLogCtrl != NULL)
    {
  /* Set reasonable default values */
    tmp_sLogCtrl.logCtrl |= LOG_TIME_EN;
    tmp_sLogCtrl.logCtrl |= LOG_IPC_SMART;
    tmp_sLogCtrl.fc.ctrl |= FIL_CTRL_MSG_HDR_EN;
    tmp_sLogCtrl.fc.ctrl |= FIL_CTRL_WIPE_EN;
    tmp_sLogCtrl.fc.ctrl |= FIL_CTRL_WRAP_EN;
    }

  rc = sx_parseExx_mt (logFileName, 0, NULL, &logCfgxCtrl, _logcfg_data_start, _logcfg_data_end);
#if defined(DEBUG_SISCO)
  if (rc != SD_SUCCESS)
    {
    /* Config failed: Do not modify "destLogCtrl".                         */
    /* Turn on cfg logging and parse file again.                        */
    if (destLogCtrl != NULL)
      destLogCtrl->logCtrl |= LOG_FILE_EN;

    sx_debug_sel |= SX_LOG_DEC | SX_LOG_DEBUG | SX_LOG_FLOW;
    logcfg_debug_sel |= LOGCFG_ERR | LOGCFG_NERR | LOGCFG_FLOW;
    LOGCFG_ERR0 ("ERROR Parsing Logging Configuration File: Trying again w/debug on ... ");
    rc = sx_parseExx_mt (logFileName, 0,NULL,&logCfgxCtrl, _logcfg_data_start, _logcfg_data_end);
    }
  else    /* rc == SD_SUCCESS */
    {
    LOGCFG_CFLOW0 ("");
    LOGCFG_CFLOW0 ("Log Control");
    if (destLogCtrl != NULL)
      {
      destLogCtrl->initialized = SD_TRUE;
      LOGCFG_CFLOW1 ("  File Logging           : %s",  destLogCtrl->logCtrl & LOG_FILE_EN ? "On" : "Off");
      if (destLogCtrl->logCtrl & LOG_FILE_EN)
        {
        LOGCFG_CFLOW1 ("    File name            : '%s'", destLogCtrl->fc.fileName);
        LOGCFG_CFLOW1 ("    File size            : %ld", destLogCtrl->fc.maxSize);
        LOGCFG_CFLOW1 ("    Timestamps           : %s",  destLogCtrl->logCtrl & LOG_TIME_EN       ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Wipe                 : %s",  destLogCtrl->fc.ctrl & FIL_CTRL_WIPE_EN    ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Wrap                 : %s",  destLogCtrl->fc.ctrl & FIL_CTRL_WRAP_EN    ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Header               : %s",  destLogCtrl->fc.ctrl & FIL_CTRL_MSG_HDR_EN ? "On" : "Off");
        LOGCFG_CFLOW1 ("    No Append            : %s",  destLogCtrl->fc.ctrl & FIL_CTRL_NO_APPEND  ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Hard Flush           : %s",  destLogCtrl->fc.ctrl & FIL_CTRL_HARD_FLUSH ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Setbuf               : %s",  destLogCtrl->fc.ctrl & FIL_CTRL_SETBUF_EN  ? "On" : "Off");
        }
      					    
      LOGCFG_CFLOW1 ("  Mem Logging            : %s",  destLogCtrl->logCtrl & LOG_MEM_EN        ? "On" : "Off");
      if (destLogCtrl->logCtrl & LOG_MEM_EN)
        {
        LOGCFG_CFLOW1 ("    Mem max items        : %d",  destLogCtrl->mc.maxItems);
        LOGCFG_CFLOW1 ("    Mem auto dump        : %s",  destLogCtrl->mc.ctrl & MEM_CTRL_AUTODUMP_EN ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Mem dump file name   : '%s'",  destLogCtrl->mc.dumpFileName);
        }

      LOGCFG_CFLOW1 ("  IPC Logging            : %s",  destLogCtrl->logCtrl & LOG_IPC_EN        ? "On" : "Off");
      if (destLogCtrl->logCtrl & LOG_IPC_EN)
        {
        LOGCFG_CFLOW1 ("    App ID               : '%s'", destLogCtrl->ipc.appId);
        LOGCFG_CFLOW1 ("    Smart                : %s",  destLogCtrl->logCtrl & LOG_IPC_SMART     ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Edit LogCfg          : %s",  destLogCtrl->ipc.options & LOG_IPC_EDIT_LOGCFG ? "On" : "Off");
        LOGCFG_CFLOW1 ("    Max que              : %d",  destLogCtrl->ipc.maxQueCnt);
        LOGCFG_CFLOW1 ("    Listen               : %s",  destLogCtrl->logCtrl & LOG_IPC_LISTEN_EN ? "On" : "Off");
        if (destLogCtrl->logCtrl & LOG_IPC_LISTEN_EN)
          {
          LOGCFG_CFLOW1 ("      Port               : %d",  (int) destLogCtrl->ipc.port);
          LOGCFG_CFLOW1 ("      Port Count         : %d",  destLogCtrl->ipc.portCnt);
          LOGCFG_CFLOW1 ("      Max Conns          : %d",  destLogCtrl->ipc.maxConns);
      	  }
        LOGCFG_CFLOW1 ("    Calling              : %s",  destLogCtrl->logCtrl & LOG_IPC_CALL_EN   ? "On" : "Off");
        if (destLogCtrl->logCtrl & LOG_IPC_CALL_EN)
          {
          LOGCFG_CFLOW1 ("      IP                 : %s",  destLogCtrl->ipc.callingIp);
          LOGCFG_CFLOW1 ("      Port               : %d",  (int) destLogCtrl->ipc.callingPort);
	  }
        }
      }

    tagVal = _tagValList;
    if (tagVal != NULL)
      {
      LOGCFG_CFLOW0 ("");
      LOGCFG_CFLOW0 ("Tag Values");
      while (tagVal != NULL)
        {
        LOGCFG_CFLOW2 ("  %-32.32s\t(%s)",  tagVal->tag, tagVal->tagPath );
        tagVal = list_get_next (_tagValList, tagVal);
        }
      }
    LOGCFG_FLOW0 ("Logging configuration complete");
    }
#endif  /* defined(DEBUG_SISCO) */

  /* store the SX masks now  (saved during parsing) */
  sx_debug_sel = sx_debug_sel_cfg;
  return (rc);
  }

/************************************************************************/
/************************************************************************/
/*			_logcfg_data_start				*/
/************************************************************************/

static ST_RET _logcfg_data_start (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag)
  {
LOGCFGX_CTRL *logCfgxCtrl;

  logCfgxCtrl = sxDecCtrl->usr;

/* See if we are starting the LogControl section */
  if (!strcmp (tag, "LogControl"))
    {
    logCfgxCtrl->state = LOGCFGX_STATE_LOGCTRL;
    return (SD_SUCCESS);
    }

/* See if we are starting the LogMasks section */
  if (!strcmp (tag, "LogMasks"))
    {
    if (logCfgxCtrl->compName)
      logCfgxCtrl->state = LOGCFGX_STATE_LOOK_COMPNAME;
    else
      {
      logCfgxCtrl->state = LOGCFGX_STATE_LOGMASKS;
      logCfgxCtrl->logMaskNestLevel = 0;
      }
    return (SD_SUCCESS);
    }

/* See if we are looking for our component tag */
  if (logCfgxCtrl->state == LOGCFGX_STATE_LOOK_COMPNAME)
    {
    if (!strcmp (tag, logCfgxCtrl->compName))
      {
      logCfgxCtrl->state = LOGCFGX_STATE_LOGMASKS;
      logCfgxCtrl->logMaskNestLevel = 0;
      }
    return (SD_SUCCESS);
    }


/* If we are in the logmasks state, record the tag stack for use below */
  if (logCfgxCtrl->state == LOGCFGX_STATE_LOGMASKS)
    {
    strcpy (logCfgxCtrl->logMaskNameStack[logCfgxCtrl->logMaskNestLevel], tag);
    ++logCfgxCtrl->logMaskNestLevel;
    return (SD_SUCCESS);
    }

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			_logcfg_data_end				*/
/************************************************************************/

#define _MAX_TAGPATH	200

static ST_RET _logcfg_data_end (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag)
  {
LOGCFGX_CTRL *logCfgxCtrl;
LOGCFG_VALUE_GROUP *slogMaskGroup;
LOGCFGX_VALUE_MAP *slogValueMap;
LOG_CTRL *destLogCtrl;
LOGCFGX_TAG_VAL *tagVal;
SX_DEC_ELEMENT_INFO *sxDecElInfo; 
ST_CHAR *str;
ST_INT i;
ST_INT strLen;
#if defined(DEBUG_SISCO)
ST_CHAR *oldFileName;
ST_BOOLEAN logFileChanged;
#endif
ST_BOOLEAN found;
ST_CHAR *p;
ST_CHAR *parentTag;
ST_CHAR tagPath[_MAX_TAGPATH+1];

  logCfgxCtrl = sxDecCtrl->usr;

/* See if this is the End of the LogMasks section */
  if (!strcmp (tag, "LogMasks"))
    {
    logCfgxCtrl->state = LOGCFGX_STATE_NONE;
    return (SD_SUCCESS);
    }

/* See if this is the End of the file */
  if (!strcmp (tag, "LOG_CFG"))
    return (SD_SUCCESS);


  destLogCtrl = logCfgxCtrl->destLogCtrl;
  sxDecElInfo = &sxDecCtrl->sxDecElInfo; 

/* See if this is the End of the LogControl section */
  if (!strcmp (tag, "LogControl"))
    {
#if defined(DEBUG_SISCO)
    logFileChanged = SD_FALSE;
    if (logCfgxCtrl->masksOnly == SD_FALSE)
      {
      /* If the log file name has changed and the log file is open, 	*/
      /* close the log file and clear state.				*/
      
      if (destLogCtrl->fc.state & FIL_STATE_OPEN)
        {                 
        oldFileName = destLogCtrl->fc.fileName;
#ifdef _WIN32   /* Filenames NOT case sensitive on Windows  */
        if (stricmp (tmp_sLogCtrl.fc.fileName, oldFileName) != 0)
#else
        if (strcmp (tmp_sLogCtrl.fc.fileName, oldFileName) != 0)
#endif
          {   /* NEW log file name different from OLD.    */
          fclose (destLogCtrl->fc.fp);           /* close it */
          destLogCtrl->fc.state &= ~(FIL_STATE_OPEN);    /* clear state  */
          logFileChanged = SD_TRUE;
          }
        }
      if (tmp_sLogCtrl.fc.ctrl & FIL_CTRL_MSG_HDR_EN)
        tmp_sLogCtrl.mc.ctrl |= MEM_CTRL_MSG_HDR_EN;
      else
        tmp_sLogCtrl.mc.ctrl &= ~MEM_CTRL_MSG_HDR_EN;
  
      destLogCtrl->logCtrl         = tmp_sLogCtrl.logCtrl;
      destLogCtrl->fc.ctrl         = tmp_sLogCtrl.fc.ctrl;
      destLogCtrl->fc.fileName     = tmp_sLogCtrl.fc.fileName;
      destLogCtrl->fc.maxSize      = tmp_sLogCtrl.fc.maxSize;
      destLogCtrl->mc.ctrl         = tmp_sLogCtrl.mc.ctrl;
      destLogCtrl->mc.dumpFileName = tmp_sLogCtrl.mc.dumpFileName;
      destLogCtrl->mc.maxItems     = tmp_sLogCtrl.mc.maxItems;
      destLogCtrl->ipc.appId 	   = tmp_sLogCtrl.ipc.appId; 	
      destLogCtrl->ipc.options	   = tmp_sLogCtrl.ipc.options; 	
      destLogCtrl->ipc.port 	   = tmp_sLogCtrl.ipc.port; 	
      destLogCtrl->ipc.portCnt     = tmp_sLogCtrl.ipc.portCnt; 	
      destLogCtrl->ipc.maxConns    = tmp_sLogCtrl.ipc.maxConns; 	
      destLogCtrl->ipc.callingIp   = tmp_sLogCtrl.ipc.callingIp; 
      destLogCtrl->ipc.callingPort = tmp_sLogCtrl.ipc.callingPort;
      destLogCtrl->ipc.maxQueCnt   = tmp_sLogCtrl.ipc.maxQueCnt; 
      destLogCtrl->ipc.sealMode    = tmp_sLogCtrl.ipc.sealMode; 
      destLogCtrl->ipc.sealTimeWindow = tmp_sLogCtrl.ipc.sealTimeWindow; 
      }
    LOGCFG_FLOW2 ("LogCfg loading file %s, prefix %s", 
		      logCfgxCtrl->logFileName, logCfgxCtrl->fileNamePrefix);

    if (logFileChanged)
      {
      _slog (destLogCtrl,_logcfg_log_flow_logstr, thisFileName,__LINE__, 
        	"See the file '%s' for messages logged before or during Logging config",
                  oldFileName);
      }
#endif  /* defined(DEBUG_SISCO) */
    logCfgxCtrl->state = LOGCFGX_STATE_NONE;
    return (SD_SUCCESS);
    } /* end of <LogCtrl> handling */


/* See if we are in the LogCtrl section */
  if (logCfgxCtrl->state == LOGCFGX_STATE_LOGCTRL)
    {
  /* See if we can find it in the selected table set ... */
  /* First try to use the group name/preferredTag to find the value map */
    found = SD_FALSE;
    if (logCfgxCtrl->logMaskNestLevel > 1)  
      {
      parentTag = logCfgxCtrl->logMaskNameStack[logCfgxCtrl->logMaskNestLevel-2];
      slogMaskGroup = logCfgLogCtrlGroupList;
      while (slogMaskGroup)
        {
        if (!strcmp (slogMaskGroup->name, parentTag))
          {
        /* OK, found the right group */
          for (i = 0; !found && (i < slogMaskGroup->numMaskMap); ++i)
            {
	    slogValueMap = &slogMaskGroup->maskMapTbl[i];
          /* Accept either the preferred tag or the tag */
            if (slogValueMap->preferredTag && !strcmp (tag, slogValueMap->preferredTag))
              found = SD_TRUE;
            else if (!strcmp (tag, slogValueMap->tag))
              found = SD_TRUE;
	    }
	  }
        if (found)
          break;

        slogMaskGroup = list_get_next (logCfgLogCtrlGroupList, slogMaskGroup);
        }
      }

  /* If that did not work, look for the unqualified tag */
    if (!found)
      {
      slogMaskGroup = logCfgLogCtrlGroupList;
      while (slogMaskGroup)
        {
        for (i = 0; !found && (i < slogMaskGroup->numMaskMap); ++i)
          {
	  slogValueMap = &slogMaskGroup->maskMapTbl[i];
          if (!strcmp (tag, slogValueMap->tag))
            found = SD_TRUE;
	  }
        if (found)
          break;

        slogMaskGroup = list_get_next (logCfgLogCtrlGroupList, slogMaskGroup);
        }
      }

  /* If we found the tag, process it appropriately */
    if (found)
      _logcfg_proc_value_map (sxDecCtrl, slogMaskGroup, slogValueMap, NULL);

    return (SD_SUCCESS);
    }

/* logCfgxCtrl->state != LOGCFGX_STATE_LOGCTRL		   */
/* This might be an Log Mask or other value of interest */
  if (logCfgxCtrl->state == LOGCFGX_STATE_LOGMASKS || 
      logCfgxCtrl->state == LOGCFGX_STATE_NONE)
    {
  /* If we are to save tag values for LogMasks, do it now */
    if (logCfgxCtrl->saveTagVals && logCfgxCtrl->logMaskNestLevel > 0)
      {
    /* Assemble the path */
      tagPath[0] = 0;
      for (i = 0; i < logCfgxCtrl->logMaskNestLevel; ++i)
        {
        if (i > 0)
          strncat_maxstrlen (tagPath, "/", _MAX_TAGPATH);

        strncat_maxstrlen (tagPath, logCfgxCtrl->logMaskNameStack[i], _MAX_TAGPATH);
        }

    /* See if the TagVal already is in our list, and free it if so */
      tagVal = logCfgFindTagValPath (tagPath);
      if (tagVal)
        {
        list_unlink (&_tagValList, tagVal);
        if (tagVal->dataType == _LOGCFG_DATATYPE_STRING || 
            tagVal->dataType == _LOGCFG_DATATYPE_FILENAME)
          {
          chk_free (tagVal->u.str);
          }
        chk_free (tagVal);
        }

    /* OK, allocate the new one */
      tagVal = chk_calloc (1, sizeof (LOGCFGX_TAG_VAL) + 
      			      (strlen (tag) + 1) + 
      			      (strlen (tagPath) + 1)) ;

      p = (ST_CHAR *) (tagVal + 1);
      tagVal->tag = p;
      strcpy (p, tag);
      p = (ST_CHAR *) (p + (strlen (tag) + 1));
      tagVal->tagPath = p;
      strcpy (p, tagPath);
      list_add_last (&_tagValList, tagVal);
      }
    else
      tagVal = NULL;

/* Now see if we can find it in the selected tag set ... */
/* First try to use the GroupName/preferredTag or GroupName/Tag to find the value map */
    found = SD_FALSE;
    if (logCfgxCtrl->logMaskNestLevel > 1)  
      {
      parentTag = logCfgxCtrl->logMaskNameStack[logCfgxCtrl->logMaskNestLevel-2];
      slogMaskGroup = logCfgLogMaskGroupList;
      while (slogMaskGroup)
        {
        if (!strcmp (slogMaskGroup->name, parentTag))
          {
        /* OK, found the right group */
          for (i = 0; !found && (i < slogMaskGroup->numMaskMap); ++i)
            {
          /* Accept either the preferred tag or the tag */
	    slogValueMap = &slogMaskGroup->maskMapTbl[i];
            if (slogValueMap->preferredTag && !strcmp (tag, slogValueMap->preferredTag))
              found = SD_TRUE;
	    else if (!strcmp (tag, slogValueMap->tag))
              found = SD_TRUE;
  	    }
          }
        if (found)
          break;

        slogMaskGroup = list_get_next (logCfgLogMaskGroupList, slogMaskGroup);
        }
      }

  /* If that did not work, settle for the unqualified tag */
    if (!found)
      {
      slogMaskGroup = logCfgLogMaskGroupList;
      while (slogMaskGroup)
        {
        for (i = 0; !found && (i < slogMaskGroup->numMaskMap); ++i)
          {
	  slogValueMap = &slogMaskGroup->maskMapTbl[i];
          if (!strcmp (tag, slogValueMap->tag))
            found = SD_TRUE;
	  }
        if (found)
          break;

        slogMaskGroup = list_get_next (logCfgLogMaskGroupList, slogMaskGroup);
        }
      }

  /* If we found the tag, process it appropriately */
    if (found)
      {
      if (tagVal != NULL)
        tagVal->dataType = slogValueMap->dataType;

      _logcfg_proc_value_map (sxDecCtrl, slogMaskGroup, slogValueMap, tagVal);
      }
    else 
      {
    /* We did not find this tag */
      if (tagVal != NULL)
        {
        strLen = 0;
        if (sx_get_string_ptr (sxDecCtrl, &str, &strLen) == SD_SUCCESS)
          {
          if (!stricmp (str, "On"))
            {
            LOGCFG_CFLOW1 ("Saving  log mask %-20s  ON  (ignored)", tag);
            tagVal->u.b = SD_TRUE;
            tagVal->dataType = _LOGCFG_DATATYPE_BOOLEAN;
            }
          else if (!stricmp (str, "Off"))
            {
            LOGCFG_CFLOW1 ("Saving  log mask %-20s  OFF (ignored)", tag);
            tagVal->u.b = SD_FALSE;
            tagVal->dataType = _LOGCFG_DATATYPE_BOOLEAN;
            }
          else
            {
            /* DEBUG: currently str may be unusable if the tag is an end of a XML subsection */
            /* LOGCFG_CFLOW2 ("Saving           %-20s  '%s'", tag, str); */
            tagVal->u.str = chk_strdup (str);
            tagVal->dataType = _LOGCFG_DATATYPE_STRING;
            }
          }
        }
      else /* We are not saving log mask values */
        {
        /* log only tags that could be log masks */
        if (strstr (tag, "LOG_"))
          LOGCFG_CFLOW1 ("        log mask %-20s  ignored", tag);
        }
      }

  /* If this was the end of the selected component, switch states */
    if (logCfgxCtrl->compName && !strcmp (tag, logCfgxCtrl->compName))
      logCfgxCtrl->state = LOGCFGX_STATE_LOOK_COMPNAME;

    --logCfgxCtrl->logMaskNestLevel;
    } /* End of 'if logCfgxCtrl->state == LOGCFGX_STATE_LOGMASKS */

  return (SD_SUCCESS);
  }

/************************************************************************/
/************************************************************************/
/*			_logcfg_proc_value_map				*/
/************************************************************************/

static ST_VOID _logcfg_proc_value_map (SX_DEC_CTRL *sxDecCtrl, 
				       LOGCFG_VALUE_GROUP *slogMaskGroup,
			               LOGCFGX_VALUE_MAP *slogValueMap, 
			               LOGCFGX_TAG_VAL *tagVal)
  {
LOGCFGX_CTRL *logCfgxCtrl;
typedef ST_VOID (*logCfgCallbackFunTYPE) (SX_DEC_CTRL *sxDecCtrl, ST_CHAR *tag,
					  LOGCFGX_VALUE_MAP *valMap);
logCfgCallbackFunTYPE logCfgCallbackFun;
ST_CHAR *str;
ST_BOOLEAN b;
ST_INT strLen;
ST_CHAR *p;
ST_CHAR paramName[200];

  sprintf (paramName, "%s/%s (%s)", 
  	slogMaskGroup->name != NULL ? slogMaskGroup->name: "",
	slogValueMap->tag,
	slogValueMap->preferredTag ? slogValueMap->preferredTag : "");

  logCfgxCtrl = sxDecCtrl->usr;
  switch (slogValueMap->dataType)
    {
    case _LOGCFG_DATATYPE_UINT_MASK:
      {
      ST_UINT *up;
      up = slogValueMap->addr;
      if (sx_get_string_OnOff_bool (sxDecCtrl, &b, SX_ERR_CONVERT) != SD_SUCCESS)
        break;
      if (b)
        *up |= slogValueMap->mask; /* Set the bit */
      else
        *up &= ~slogValueMap->mask; /* Clear the bit */
  
      LOGCFG_CFLOW2 ("Setting log mask %-50.50s  %s", paramName, b ? "ON" : "OFF");

      if (tagVal != NULL)
        tagVal->u.b = b;
      }
    break;

    case _LOGCFG_DATATYPE_UINT32_MASK:
      {
      ST_UINT32 *u32p;
      u32p = slogValueMap->addr;
      if (sx_get_string_OnOff_bool (sxDecCtrl, &b, SX_ERR_CONVERT) != SD_SUCCESS)
        break;
      if (b)
        *u32p |= slogValueMap->mask; /* Set the bit */
      else
        *u32p &= ~slogValueMap->mask; /* Clear the bit */
    
      LOGCFG_CFLOW2 ("Setting log mask %-50.50s  %s", paramName, b ? "ON" : "OFF");
      if (tagVal != NULL)
        tagVal->u.b = b;
      }
    break;
    
    /* 'R'everse mask settings */
    case _LOGCFG_DATATYPE_RUINT32_MASK:
      {
      ST_UINT *up;
      up = slogValueMap->addr;
      if (sx_get_string_OnOff_bool (sxDecCtrl, &b, SX_ERR_CONVERT) != SD_SUCCESS)
        break;
      if (b)
        *up &= ~slogValueMap->mask; /* Clear the bit */
      else
        *up |= slogValueMap->mask; /* Set the bit */
    
      LOGCFG_CFLOW2 ("Setting log mask %-50.50s  %s", paramName, b ? "ON" : "OFF");
      if (tagVal != NULL)
        tagVal->u.b = b;
      }
    break;
    
    case _LOGCFG_DATATYPE_BOOLEAN:
      {
      ST_BOOLEAN *bp;
      bp = (ST_BOOLEAN *) slogValueMap->addr;
      if (sx_get_string_OnOff_bool (sxDecCtrl, bp, SX_ERR_CONVERT) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting boolean  %-50.50s  %s", paramName, *bp ? "ON" : "OFF");
      if (tagVal != NULL)
        tagVal->u.b = *bp;
      }
    break;
    
    case _LOGCFG_DATATYPE_INT:
      {
      ST_INT *sp;
      sp = slogValueMap->addr;
      if (sx_get_int (sxDecCtrl, sp) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %d", paramName, *sp);
      if (tagVal != NULL)
        tagVal->u.sInt = *sp;
      }
    break;
    
    case _LOGCFG_DATATYPE_UINT:
      {
      ST_UINT *up;
      up = slogValueMap->addr;
      if (sx_get_uint (sxDecCtrl, up) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %u", paramName, *up);
      if (tagVal != NULL)
        tagVal->u.uInt = *up;
      }
    break;
    
    case _LOGCFG_DATATYPE_LONG:
      {
      ST_LONG *slp;
      slp = slogValueMap->addr;
      if (sx_get_long (sxDecCtrl, slp) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %ld", paramName, *slp);
      if (tagVal != NULL)
        tagVal->u.sLong = *slp;
      }
    break;
    
    case _LOGCFG_DATATYPE_ULONG:
      {
      ST_ULONG *ulp;
      ulp = slogValueMap->addr;
      if (sx_get_ulong (sxDecCtrl, ulp) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %lu", paramName, *ulp);
      if (tagVal != NULL)
        tagVal->u.uLong = *ulp;
      }
    break;
    
    case _LOGCFG_DATATYPE_INT16:
      {
      ST_INT16 *s16p;
      s16p = slogValueMap->addr;
      if (sx_get_int16 (sxDecCtrl, s16p) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %d", paramName, (ST_INT) *s16p);
      if (tagVal != NULL)
        tagVal->u.sInt16 = *s16p;
      }
    break;
    
    case _LOGCFG_DATATYPE_UINT16:
      {
      ST_UINT16 *u16p;
      u16p = slogValueMap->addr;
      if (sx_get_uint16 (sxDecCtrl, u16p) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %u", paramName, (ST_UINT) *u16p);
      if (tagVal != NULL)
        tagVal->u.uInt16 = *u16p;
      }
    break;
    
    case _LOGCFG_DATATYPE_INT32:
      {
      ST_INT32 *s32p;
      s32p = slogValueMap->addr;
      if (sx_get_int32 (sxDecCtrl, s32p) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %ld", paramName, (ST_LONG) *s32p);
      if (tagVal != NULL)
        tagVal->u.sInt32 = *s32p;
      }
    break;
    
    case _LOGCFG_DATATYPE_UINT32:
      {
      ST_UINT32 *u32p;
      u32p = slogValueMap->addr;
      if (sx_get_uint32 (sxDecCtrl, u32p) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %lu", paramName, (ST_ULONG) *u32p);
      if (tagVal != NULL)
        tagVal->u.uInt32 = *u32p;
      }
    break;
    
    case _LOGCFG_DATATYPE_DOUBLE:
      {
      ST_DOUBLE *dp;
      dp = slogValueMap->addr;
      if (sx_get_double (sxDecCtrl, dp) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  %.4f", paramName, *dp);
      if (tagVal != NULL)
        tagVal->u.dbl = *dp;
      }
    break;
    
    case _LOGCFG_DATATYPE_STRING:
      {
      ST_CHAR **cpp;
      cpp = slogValueMap->addr;
      if (sx_get_alloc_string (sxDecCtrl, cpp) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  '%s'", paramName, *cpp);
      if (tagVal != NULL)
        tagVal->u.str = *cpp;
      }
    break;
    
    case _LOGCFG_DATATYPE_STRINGBUF:
      {
      ST_CHAR *cp;
      cp = slogValueMap->addr;
      strLen = 0;
      if (sx_get_string_ptr (sxDecCtrl, &str, &strLen) != SD_SUCCESS)
        break;
      LOGCFG_CFLOW2 ("Setting          %-50.50s  '%s'", paramName, str);
      cp = slogValueMap->addr;
      strncpy_safe (cp, str, slogValueMap->mask);
    
      if (tagVal != NULL)
        tagVal->u.str = cp;
      }
    break;
    
    case _LOGCFG_DATATYPE_FILENAME:
      {
      ST_CHAR **cpp;
      cpp = slogValueMap->addr;
    
    /* The user might want a prefix for this file name */
      strLen = 0;
      if (sx_get_string_ptr (sxDecCtrl, &str, &strLen) != SD_SUCCESS)
        break;
      if (logCfgxCtrl->fileNamePrefix)
        strLen += strlen (logCfgxCtrl->fileNamePrefix);
      p = chk_malloc (strLen+1);
      *cpp = p;
      if (logCfgxCtrl->fileNamePrefix)
        strcpy (p, logCfgxCtrl->fileNamePrefix);
      else
        *p = 0;
      strcat (p, str);

      LOGCFG_CFLOW2 ("Setting          %-50.50s  '%s'", paramName, p);
      if (tagVal != NULL)
        tagVal->u.str = p;
      }
    break;

    case _LOGCFG_DATATYPE_CALLBACK:
      logCfgCallbackFun = (logCfgCallbackFunTYPE) slogValueMap->addr;
      if (logCfgCallbackFun != NULL)
        (*logCfgCallbackFun) (sxDecCtrl, sxDecCtrl->sxDecElInfo.tag, slogValueMap);
    break;
    }
  }

/************************************************************************/
/*			slog_ipc_std_cmd_service			*/
/*			slog_ipc_std_cmd_service_ex			*/
/************************************************************************/

ST_VOID slog_ipc_std_cmd_service (ST_CHAR *logCfgFile, 
				  ST_CHAR *fileNamePrefix,
                                  ST_CHAR *cName,
                                  ST_BOOLEAN callingEnable,
				  ST_RET (*logReloadHandler) (ST_VOID),
				  ST_RET (*extendedCmdHandler) (SLOGIPC_CMD *slogIpcCmd))
  {
  slog_ipc_std_cmd_service_ex (sLogCtrl, logCfgFile, fileNamePrefix,
                                  cName, callingEnable,logReloadHandler, extendedCmdHandler);
  }


ST_VOID slog_ipc_std_cmd_service_ex (LOG_CTRL *lc, ST_CHAR *logCfgFile, 
				  ST_CHAR *fileNamePrefix,
                                  ST_CHAR *cName,
                                  ST_BOOLEAN callingEnable,
				  ST_RET (*logReloadHandler) (ST_VOID),
				  ST_RET (*extendedCmdHandler) (SLOGIPC_CMD *slogIpcCmd))
  {
SLOGIPC_CMD *slogIpcCmd;
ST_ULONG msgRespType;
ST_LONG fileSize;
ST_LONG bytesRead;
ST_LONG bytesWritten;
ST_CHAR *cfgData;
ST_RET  rc;
struct stat buf;
int result;
FILE *fp;
ST_INT xmlSize;
ST_CHAR *xmlBuf;

  slogIpcEventEx (lc);	/* required for IPC Logging if gensock2.c is	*/
    			/* not compiled with GENSOCK_THREAD_SUPPORT	*/

  slogIpcCallingEnableEx (lc, callingEnable);

/* Any pending SLOG IPC Commands ? */
  if (slogIpcCmdList == NULL)
    return;

  S_LOCK_UTIL_RESOURCES ();
  slogIpcCmd = slogIpcCmdList;
  list_unlink (&slogIpcCmdList, slogIpcCmd);
  S_UNLOCK_UTIL_RESOURCES ();

/* Assume the worst ... */
  msgRespType = SLOGIPC_MSG_TYPE_RESP_FAILURE;

  switch (slogIpcCmd->msgType)
    {
    case SLOGIPC_MSG_TYPE_READ_LOGCFG:
    /* Get the size of the file */
      bytesRead = 0;
      cfgData = NULL;
      fp = fopen (logCfgFile, "r");
      if (fp != NULL)
        {
        result = fstat (fileno (fp), &buf);
        if (result == 0)
          {  
        /* Allocate a buffer and read all into memory */
          fileSize = buf.st_size;
          cfgData = (ST_CHAR *) chk_malloc (fileSize);
          bytesRead = fread (cfgData, 1, fileSize, fp);
          fclose (fp);
          if (bytesRead > 0)
            msgRespType = SLOGIPC_MSG_TYPE_RESP_SUCCESS;
          }
        }
      slogIpcSendData (slogIpcCmd->pSock, msgRespType, bytesRead, (ST_UCHAR *)cfgData);
      if (cfgData != NULL)
        chk_free (cfgData);
    break;

    case SLOGIPC_MSG_TYPE_WRITE_LOGCFG:
      fp = fopen (logCfgFile, "w");
      if (fp != NULL)
        {
        bytesWritten = fwrite (slogIpcCmd->msgData, 1, slogIpcCmd->msgDataLen, fp);
        fclose (fp);
        if (bytesWritten == slogIpcCmd->msgDataLen)
          {  
          if (logReloadHandler != NULL)
	    rc = (*logReloadHandler)();
          else
            rc = logcfgx_exx (lc, logCfgFile, fileNamePrefix, SD_TRUE, SD_TRUE, cName);

          if (rc == SD_SUCCESS)
            msgRespType = SLOGIPC_MSG_TYPE_RESP_SUCCESS;
	  }
        }
      slogIpcSendData (slogIpcCmd->pSock, msgRespType, 0, NULL);
    break;

    case SLOGIPC_MSG_TYPE_CLONE_LOG:
      slogIpcCmd->msgData[slogIpcCmd->msgDataLen] = 0;
      slogCloneFile (lc, slogIpcCmd->msgData);
      slogIpcSendData (slogIpcCmd->pSock, SLOGIPC_MSG_TYPE_RESP_SUCCESS, 0, NULL);
    break;

    case SLOGIPC_MSG_TYPE_RESET_LOG:
      slogDeleteFile (lc);
      slogIpcSendData (slogIpcCmd->pSock, SLOGIPC_MSG_TYPE_RESP_SUCCESS, 0, NULL);
    break;
	
    case SLOGIPC_MSG_TYPE_WRITE_MSGDATA:
      SLOGALWAYS0 (slogIpcCmd->msgData);
      slogIpcSendData (slogIpcCmd->pSock, SLOGIPC_MSG_TYPE_RESP_SUCCESS, 0, NULL);
    break;

    case SLOGIPC_MSG_TYPE_GET_LOGMASKS:
      xmlSize = _logcfg_get_logmasks_size ();
      xmlSize += SX_ENC_BUFFER_OH;
      xmlBuf = chk_malloc (xmlSize);

      rc = _logcfg_get_logmasks (xmlBuf, &xmlSize);
      if (rc == SD_SUCCESS)
        msgRespType = SLOGIPC_MSG_TYPE_RESP_SUCCESS;
      else
        xmlSize = 0;
      slogIpcSendData (slogIpcCmd->pSock, msgRespType, xmlSize, (ST_UCHAR *) xmlBuf);
      chk_free (xmlBuf);
    break;

    default:
      if (extendedCmdHandler != NULL)
        rc = (*extendedCmdHandler) (slogIpcCmd);
      else
        slogIpcSendData (slogIpcCmd->pSock, msgRespType, 0, NULL);
    break;
    }

/* Normally would use 'slogIpc_uDataBufFree' for sockData, but it is static ... */
  chk_free (slogIpcCmd->sockData);
  chk_free (slogIpcCmd);
  return;
  }
#endif	/* defined(DEBUG_SISCO)	*/




