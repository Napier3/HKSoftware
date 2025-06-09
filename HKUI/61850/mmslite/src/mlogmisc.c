/***********************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*                  1986 - 2006 All Rights Reserved                     */
/*                                                                      */
/* MODULE NAME : mlogmisc.c                                             */
/* PRODUCT(S)  : MMS-EASE                                               */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*      This module contains user defined logging functions for         */
/*      u_misc.c functions that require logging.                        */
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev                  Comments                        */
/* --------  ---  ------   -------------------------------------------  */
/* 03/03/06  EJV     12    Use strncpy_safe. Added str_util.h		*/
/* 03/11/04  GLB     11    Remove "thisFileName"                    	*/
/* 10/14/03  JRB     10    Del unnecessary casts.			*/
/* 09/13/99  MDE     09    Added SD_CONST modifiers			*/
/* 11/04/98  DSF     08    Added m_get_mms_rej_text ()			*/
/* 11/04/98  DSF     07    Fixed spelling				*/
/* 10/05/98  EJV     06    Don't need "suicacse.h" (if def MAP30_ACSE)	*/
/* 03/20/98  JRB     05    Don't need mmsop_en.h anymore.		*/
/* 12/09/97  DSF     04    Fixed spelling				*/
/* 08/05/97  MDE     03    Made 'no log' functions non-static		*/
/* 08/04/97  MDE     02    Removed DEBUG_SISCO code, added err, more	*/
/* 06/09/97  MDE     01    Added MMS-LITE ifdefs			*/
/* 04/02/97  DTL   7.00    MMSEASE 7.0 release. See MODL70.DOC for	*/
/*			   history.					*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "str_util.h"

#ifndef MMS_LITE
#include "mms_usr.h"		/* to access MMS fucntions, variables   */
#else
#include "mmsdefs.h"
#endif

#include "mms_pevn.h"		/* to access modifiers			*/
#include "asn1defs.h"           /* to access ASN.1 variables            */
#include "mem_chk.h"
#include "slog.h"

#include "mloguser.h"

/************************************************************************/
/*                      m_log_external                                  */
/* This function is used to log the contents of the extern_info         */
/* structure that has been filled in by a parse routine                 */
/************************************************************************/

ST_VOID m_log_external (EXTERN_INFO *info)
  {
struct mms_obj_id *obj;
ST_INT i;

  if (info->dir_ref_pres)
    {
    obj = &(info->dir_ref);
    for (i = 0; i < obj->num_comps; ++i)
      {
      MLOG_CALWAYS1 ("Direct Reference : %d",obj->comps[i]);
      }
    }
  else
    {
    MLOG_CALWAYS0 ("Direct Reference : Not Present");
    }

  if (info->indir_ref_pres)
    {
    MLOG_CALWAYS1 ("Indirect Reference : %ld",info->indir_ref);
    }
  else
    {
    MLOG_CALWAYS0 ("Indirect Reference : Not Present");
    }

  if (info->dv_descr_pres)
    {
    MLOG_CALWAYS0 ("Data Value Descripter :");
    MLOG_ALWAYSH (info->dv_descr_len,info->dv_descr);
    }
  else
    {
    MLOG_CALWAYS0 ("Data Value Descripter : Not Present");
    }

  MLOG_CALWAYS1 ("Encoding Tag : %d",info->encoding_tag);

  if (info->encoding_tag == 2)
    {
    MLOG_CALWAYS1 ("Data Length = %d bits",info->num_bits);
    }
  else
    {
    MLOG_CALWAYS1 ("Data Length = %d octects",info->data_len);
    }

  MLOG_CALWAYS0 ("Data : ");
  MLOG_ALWAYSH (info->data_len,info->data_ptr);
  }


/************************************************************************/
/************************************************************************/
/************************************************************************/
/*			m_log_objname					*/
/* This routine is used here in variable access management and in	*/
/* semaphore management, to print an object name.			*/
/************************************************************************/

ST_VOID m_log_objname (OBJECT_NAME *info)
  {
  switch (info->object_tag)
    {
    case 0  :
      MLOG_CALWAYS1 ("VMD-Specific Name : %s",info->obj_name.vmd_spec);
      break;

    case 1  :
      MLOG_CALWAYS1 ("DOM-Specific Domain Id: %s",info->domain_id);
      MLOG_CALWAYS1 ("Item Id: %s",info->obj_name.item_id);
      break;

    case 2  :
      MLOG_CALWAYS1 ("AA -Specific Name : %s",info->obj_name.aa_spec);
      break;

    default   :
      MLOG_CALWAYS1 ("Invalid Object Tag : %d ",info->object_tag);
      break;
    }
  }

/************************************************************************/
/*			m_log_modifier					*/
/* This routine is used to slog a modifier.	 			*/
/************************************************************************/

ST_VOID m_log_modifier (MODIFIER *info)
  {
  switch (info->modifier_tag)
    {
    case (0)  :
      MLOG_CALWAYS0 ("Attach to Event Condition");

      MLOG_CALWAYS0 ("Event Enrollment Name Follows:");
      m_log_objname (&(info->mod.atec.evenroll_name));

      MLOG_CALWAYS0 ("Event Condition Name Follows:");
      m_log_objname (&(info->mod.atec.evcon_name));

      MLOG_CALWAYS1 ("Causing Transitions : %02x",
      				info->mod.atec.causing_transitions);

      if (info->mod.atec.causing_transitions & 0x01)
        {
        MLOG_CALWAYS0 ("Idle to Disabled : Set");
        }
      else
        {
        MLOG_CALWAYS0 ("Idle to Disabled : Not Set");	        
        }

      if (info->mod.atec.causing_transitions & 0x02)
        {
        MLOG_CALWAYS0 ("Active to Disabled : Set");
        }
      else 
        {
        MLOG_CALWAYS0 ("Active to Disabled : Not Set");
        }

      if (info->mod.atec.causing_transitions & 0x04)
        {
        MLOG_CALWAYS0 ("Disabled to Idle : Set");
        }
      else
        {
        MLOG_CALWAYS0 ("Disabled to Idle : Not Set");
        }

      if (info->mod.atec.causing_transitions & 0x08)
        {
        MLOG_CALWAYS0 ("Active to Idle : Set");
        }
      else
        {
        MLOG_CALWAYS0 ("Active to Idle : Not Set");
        }

      if (info->mod.atec.causing_transitions & 0x10)
        {
        MLOG_CALWAYS0 ("Disabled to Active : Set");
        }
      else
        {
        MLOG_CALWAYS0 ("Disabled to Active : Not Set");
        }

      if (info->mod.atec.causing_transitions & 0x20)
        {
        MLOG_CALWAYS0 ("Idle to Active : Set");
        }
      else
        {
        MLOG_CALWAYS0 ("Idle to Active : Not Set");
        }

      if (info->mod.atec.causing_transitions & 0x40)
        {
        MLOG_CALWAYS0 ("Any to Deleted : Set");
        }
      else
        {
        MLOG_CALWAYS0 ("Any to Deleted : Not Set");
        }

      if (info->mod.atec.acc_delay_pres)
        {
        MLOG_CALWAYS1 ("Acceptable Delay : %ld",info->mod.atec.acc_delay);
        }
      else
        {
        MLOG_CALWAYS0 ("Acceptable Delay : Not Present ");
        }
      break;

    case (1)  :
      MLOG_CALWAYS0 ("Attach to Semaphore");
      MLOG_CALWAYS0 ("Semaphore Name Follows:");
      m_log_objname (&(info->mod.atsem.sem_name));

      if (info->mod.atsem.named_token_pres)
        {
        MLOG_CALWAYS1 ("Named Token : %s",info->mod.atsem.named_token);
        }
      else
        {
        MLOG_CALWAYS0 ("Named Token : ot Present");
        }

      MLOG_CALWAYS1 ("Priority : %u",info->mod.atsem.priority);
      if (info->mod.atsem.acc_delay_pres)
        {
        MLOG_CALWAYS1 ("Acceptable Delay : %ld",info->mod.atsem.acc_delay);
        }
      else
        {
        MLOG_CALWAYS0 ("Acceptable Delay : Not Present");
        }

      if (info->mod.atsem.ctrl_timeout_pres)
        {
        MLOG_CALWAYS1 ("Control Timeout : %ld",info->mod.atsem.ctrl_timeout);
        }
      else
        {
        MLOG_CALWAYS0 ("Control Timeout : Not Present");
        }

      if (info->mod.atsem.abrt_on_timeout_pres)
        {
	if (info->mod.atsem.abrt_on_timeout)
          {
          MLOG_CALWAYS0 ("Abort On Timeout : Yes");
          }
	else
          {
          MLOG_CALWAYS0 ("Abort On Timeout : No");
          }
	}
      else
        {
        MLOG_CALWAYS0 ("Abort On Timeout : Not Present ");
        }

      if (info->mod.atsem.rel_conn_lost)
        {
        MLOG_CALWAYS0 ("Relinquish if Conn Lost : Yes");
        }
      else
        {
        MLOG_CALWAYS0 ("Relinquish if Conn Lost : No");
        }
      break;

    default   :
      MLOG_CALWAYS1 ("Invalid Tag : %d",info->modifier_tag);
      break;
    }
  }


/************************************************************************/
/************************************************************************/
/************************************************************************/
/************************************************************************/

static ST_CHAR *err_class_msg[] = 
  {									
  "VMD State",				/* Class = 0			*/
  "Application Reference",		/* Class = 1			*/
  "Definition",				/* Class = 2			*/
  "Resource",				/* Class = 3			*/
  "Service",				/* Class = 4			*/
  "Service Preempt",			/* Class = 5			*/
  "Time Resolution",			/* Class = 6			*/
  "Access",				/* Class = 7			*/
  "Initiate",				/* Class = 8			*/
  "Conclude",				/* Class = 9			*/
  "Cancel",				/* Class = 10			*/
  "File"				/* Class = 11			*/
  };

static ST_CHAR *vmd_err_code_msg[] = 
  {
  "Other",
  "State Conflict",
  "Operational Problem",
  "Domain transfer Problem",
  "State Machine ID Invalid"
  };

static ST_CHAR *def_err_code_msg[] = 
  {
  "Other",
  "Object Undefined",
  "Invalid Address",
  "Type Unsupported",
  "Type Inconsistent",
  "Object Exists",
  "Attribute Inconsistent"
  };

static ST_CHAR *res_err_code_msg[] = 
  {
  "Other",
  "Memory",
  "Processor",
  "Mass Storage",
  "Capability Unavailable",
  "Capability Unknown"
  };

static ST_CHAR *ser_err_code_msg[] = 
  {
  "Other",
  "Primitive Sequence",
  "State Conflict",
  "PDU Size",
  "Continuation",
  "Constraint Conflict"
  };

static ST_CHAR *acc_err_code_msg[] = 
  {
  "Other",
  "Access Unsupported",
  "Nonexistent",
  "Access Denied",
  "Invalidated"
  };

static ST_CHAR *init_err_code_msg[] = 
  {
  "Other",
  "Version",
  "Max Segment",
  "Oustanding Calling",
  "Oustanding Called",
  "Service CBB",
  "Parameter CBB",
  "Nesting"
  };

static ST_CHAR *concl_err_code_msg[] = 
  {
  "Other",
  "Further Communication Req'd"
  };

static ST_CHAR *file_err_code_msg[] = 
  {
  "Other",
  "FileName Ambiguous",
  "File Busy",
  "FileName Syntax",
  "Content Type",
  "Position",
  "Access Denied",
  "Non-Existent"
  };

/************************************************************************/


static ST_CHAR *rej_class_msg[] = 
  {
  "",
  "Request PDU",
  "Response PDU",
  "Error PDU",
  "Unconfirmed PDU",
  "PDU Error",
  "Cancel Request",
  "Cancel Response",
  "Cancel Error",
  "Conclude Request",
  "Conclude Response",
  "Conclude Error"
  };

static ST_CHAR *class1_rej_code_msg[] = 
  {
  "Other",
  "Unrecognized Service",
  "Modifier",
  "Invalid Invoke ID",
  "Argument",
  "Modifier",
  "Max Outstanding Exceeded",
  "Reserved",
  "Max Recursion Exceeded",
  "Value Out Of Range"
  };	

static ST_CHAR *class2_rej_code_msg[] = 
  {
  "Other",
  "Unrecognized Service",
  "Invalid Invoke ID",
  "Result",
  "Reserved",
  "Recursion",
  "Value Out Of Range"
  };
static ST_CHAR *class3_rej_code_msg[] = 
  {
  "Other",
  "Unrecognized Service",
  "Invalid Invoke ID",
  "Invalid Error",
  "Value"
  };
static ST_CHAR *class5_rej_code_msg[] = 
  {
  "Unknown PDU Type",
  "Invalid PDU",
  "Illegal ACSE Mapping"
  };
static ST_CHAR *class9_rej_code_msg[] = 
  {
  "Other",
  "Argument"
  };
static ST_CHAR *class10_rej_code_msg[] = 
  {
  "Other",
  "Result"
  };
static ST_CHAR *class11_rej_code_msg[] = 
  {
  "Other",
  "Invalid Error",
  "Value"
  };

/************************************************************************/
/************************************************************************/
/*			m_log_error_info 				*/
/************************************************************************/
/* Called to log an 'err_info' structure				*/

ST_VOID m_log_error_info (ERR_INFO *err_ptr)
  {
  if (err_ptr->adtnl.mod_pos_pres)
    {
    MLOG_CALWAYS1 ("  Modifier position : %ld", err_ptr->adtnl.mod_pos);
    }

  MLOG_CALWAYS1 ("  Problem Type : %d", err_ptr->eclass);
  MLOG_CALWAYS1 ("  Problem Code : %d", err_ptr->code);
  if (err_ptr->adtnl.info_pres)
    {
    MLOG_CALWAYS0 ("  Additional Information : ");
    if (err_ptr->adtnl.code_pres)
      {
      MLOG_CALWAYS1 ("    Code : %ld", err_ptr->adtnl.code);
      }
    if (err_ptr->adtnl.descr_pres)
      {
      MLOG_CALWAYS1 ("    Description : %s", err_ptr->adtnl.descr);
      }
    if (err_ptr->adtnl.ssi_pres)
      {
      MLOG_CALWAYS0 ("    Additional Service Specific Information Follows.");
      MLOG_CALWAYS1 ("    Service : %d", err_ptr->adtnl.service);
      if (err_ptr->adtnl.service == 10)
        {
        MLOG_CALWAYS0("    Additional Error Data Follows in HEX:");
        MLOG_ALWAYSH (err_ptr->adtnl.ss_error_len, 
                      err_ptr->adtnl.ss_error_data); 
        }
      else
        {
        MLOG_CALWAYS1 ("    Error : %d", err_ptr->adtnl.ss_error_val);
        }
      }
    }
  }

/************************************************************************/
/************************************************************************/

ST_VOID m_get_mms_err_text (ST_INT eclass, ST_INT code, 
	ST_CHAR *dest, ST_INT dest_len)
  {
ST_CHAR buf[200];
ST_CHAR buf2[100];
ST_CHAR **msg_tbl;

  if (eclass > 11 || eclass < 0)
    {
    strncpy_safe (dest, "Bad Error Class", dest_len-1);
    return;
    }  

  sprintf (buf,"%s, ", err_class_msg[eclass]);
  switch (eclass)
    {
    case 0 :
      msg_tbl = vmd_err_code_msg; 
    break;

    case 2 :
      msg_tbl = def_err_code_msg; 
    break;

    case 3 :
      msg_tbl = res_err_code_msg; 
    break;

    case 4 :
      msg_tbl = ser_err_code_msg; 
    break;

    case 7 :
      msg_tbl = acc_err_code_msg; 
    break;

    case 8 :
      msg_tbl = init_err_code_msg; 
    break;

    case 9 :
      msg_tbl = concl_err_code_msg; 
    break;

    case 11 :
      msg_tbl = file_err_code_msg; 
    break;

    default :
      sprintf (buf2,"Code %d",code);
      strcat (buf,buf2);
      msg_tbl = NULL; 
    }
  if (msg_tbl)
    strcat (buf,msg_tbl[code]);

  strncpy_safe (dest, buf, dest_len-1);
  }

/************************************************************************/
/************************************************************************/

ST_VOID m_get_mms_rej_text (ST_INT rclass, ST_INT code, 
	ST_CHAR *dest, ST_INT dest_len)
  {
ST_CHAR buf[200];
ST_CHAR buf2[100];
ST_CHAR **msg_tbl;

  if (rclass > 11 || rclass < 1)
    {
    strncpy_safe (dest, "Bad Reject Class", dest_len-1);
    return;
    }  

  sprintf (buf,"%s, ", rej_class_msg[rclass]);
  switch (rclass)
    {
    case 1 :
      msg_tbl = class1_rej_code_msg; 
    break;

    case 2 :
      msg_tbl = class2_rej_code_msg;
    break;

    case 3 :
      msg_tbl = class3_rej_code_msg;
    break;

    case 5 :
      msg_tbl = class5_rej_code_msg;
    break;

    case 9 :
      msg_tbl = class9_rej_code_msg;
    break;

    case 10 :
      msg_tbl = class10_rej_code_msg;
    break;

    case 11 :
      msg_tbl = class11_rej_code_msg;
    break;

    default :
      sprintf (buf2,"Code %d",code);
      strcat (buf,buf2);
      msg_tbl = NULL; 
    }
  if (msg_tbl)
    strcat (buf,msg_tbl[code]);

  strncpy_safe (dest, buf, dest_len-1);
  }

/************************************************************************/
/************************************************************************/

ST_VOID m_log_reject_info (REJECT_RESP_INFO *rej_ptr)
  {
ST_CHAR **msg_tbl;
ST_CHAR *rej_msg;

  if (rej_ptr->detected_here)
    {
    MLOG_CALWAYS0 ("Reject Detected Here.");
    }
  else
    {
    MLOG_CALWAYS0 ("Reject Detected At Peer.");
    }
  if (rej_ptr->invoke_known)
    {
    MLOG_CALWAYS1 ("Invoke ID : %lu", rej_ptr->invoke);
    }
  else
    {
    MLOG_CALWAYS0 ("Invoke ID NOT KNOWN");
    }
  MLOG_CALWAYS1 ("Reject Class : %d", rej_ptr->rej_class);
  MLOG_CALWAYS1 ("Reject Code : %d", rej_ptr->rej_code);
  
  rej_msg = rej_class_msg[rej_ptr->rej_class];
  switch (rej_ptr->rej_class)
    {
    case 1 :
      msg_tbl = class1_rej_code_msg; 
    break;
  
    case 2 :
      msg_tbl = class2_rej_code_msg; 
    break;
  
    case 3 :
      msg_tbl = class3_rej_code_msg; 
    break;
  
    case 5 :
      msg_tbl = class5_rej_code_msg; 
    break;
  
    case 9 :
      msg_tbl = class9_rej_code_msg; 
    break;
  
    case 10 :
      msg_tbl = class10_rej_code_msg; 
    break;
  
    case 11 :
      msg_tbl = class11_rej_code_msg; 
    break;
  
    default :
      MLOG_CALWAYS2 ("Rejected : Class = %d, Code %d",
  				rej_ptr->rej_class, rej_ptr->rej_code);
      msg_tbl = NULL; 
    }
  if (msg_tbl)
    {
    MLOG_CALWAYS2 ("Rejected : %s, %s", 
  			rej_msg, msg_tbl[rej_ptr->rej_code]);
    }
  }

/************************************************************************/
/************************************************************************/

ST_VOID m_no_log_resp (ST_VOID *resp)
  {
  }

ST_VOID m_no_log_req  (ST_VOID *req)
  {
  }



