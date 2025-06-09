/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2004-2005, All Rights Reserved.					*/
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : mvl61850_ctl.c						*/
/* PRODUCT(S)  : MMSEASE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*	IEC 61850 Control Model Server functions.			*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*			mvl61850_sbo_create_sboname			*/
/*			mvl61850_ctl_chk_sbo				*/
/*			mvl61850_ctl_chk_sbow				*/
/*			mvl61850_ctl_chk_state				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 02/26/07  JRB     10    initSboCtrl: add use_ms_timer arg.		*/
/* 02/21/07  JRB     09    Fix comment.					*/
/* 11/21/06  JRB     08    Add mvl61850_ctl_lastapplerror_send.		*/
/* 10/30/06  JRB     07    Use new mvl_vmd_* object handling functions.	*/
/*			   Fix check that ALL of Oper and ONLY Oper is	*/
/*			   being written.				*/
/* 04/17/06  JRB     06    Do NOT create LastApplError var at startup,	*/
/*			   but create temporary var only when needed.	*/
/* 09/12/05  JRB     05    Add mvl61850_ctl_chk_sbow.			*/
/*			   Add NERR log if Loc$stVal==TRUE.		*/
/*			   Chk ctlModel before SBO read or SBOw write.	*/
/* 07/11/05  JRB     04    Add mvl61850_ctl_command_termination.	*/
/*			   Add mvl61850_ctl_lastapplerror_create.	*/
/* 03/28/05  JRB     03    Don't allow SBO read if Loc$stVal==TRUE.	*/
/* 01/27/05  JRB     02    Del unused variable.				*/
/* 12/10/04  JRB     01    New. Moved 61850 Control code from mvlu_sbo.c*/
/*			   to this module.				*/
/*			   Add mvl61850_ctl_chk_sbo, mvl61850_ctl_chk_state.*/
/*			   Del leaf funct mvl61850_sbo_select_rd_ind.	*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "glbsem.h"
#include "mmsdefs.h"
#include "mvl_uca.h"
#include "mvl_log.h"

/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/
/*			mvl61850_sbo_create_sboname			*/
/* Creates a name to return when an IEC 61850 SBO attribute is read.	*/
/* NOTE: this name may also be passed to "mvlu_sbo_chk_state"		*/
/*	to find the correct MVL_SBO_CTRL struct.			*/
/************************************************************************/
ST_VOID mvl61850_sbo_create_sboname (MVL_VAR_ASSOC *va, MVL_SCOPE *va_scope, 
		      ST_CHAR *sboName)
  {
ST_CHAR *tmp_ptr;	/* use to find last '$' in var name	*/

/* if primRef is NULL, then don't perform the string table lookup	*/
  switch (va_scope->scope)
    {
    case VMD_SPEC: 
      strcpy (sboName, "/");
    break;

    case DOM_SPEC: 
      strcpy (sboName, va_scope->dom->name);
      strcat (sboName, "/");
    break;

    case AA_SPEC:  
      strcpy (sboName,"@/");
    break;
    }

/* Scope in place, now append the name of variable 			*/
  strcat (sboName, va->name);

/* Replace end of var name with name of protected element (Oper).	*/
/* Var name may end with Oper, SBO, Cancel, etc. Replace with "Oper".	*/
/* This is a waste if it already ends with "Oper", but it takes more	*/
/* code to check.							*/
  if ((tmp_ptr = strrchr (sboName, '$')) != NULL)	/* find last '$'*/
    strcpy (tmp_ptr+1, "Oper");	/* Write name of protected element (Oper) AFTER it.*/
  else
    MVL_LOG_ERR1 ("SBO name generated '%s' is invalid", sboName);
    /* DEBUG: should this function return SD_FAILURE in this case?	*/
  }

/************************************************************************/
/*			mvl61850_mkname_ctlmodel			*/
/* Generate the "flattened" name of the "ctlModel" attribute that	*/
/* corresponds to the attribute passed as "var_name" arg.		*/
/* The var_name arg should always be of the following form:		*/
/*	LNodeName$CO$yyy$Oper						*/
/*	LNodeName$CO$yyy$SBO, etc.					*/
/* This funct generates a name like this ("LNodeName$" stripped off):	*/
/*	CF$yyy$ctlModel							*/
/************************************************************************/
ST_RET mvl61850_mkname_ctlmodel (ST_CHAR *var_name, ST_CHAR *flatname, size_t flatname_len)
  {
ST_RET retcode = SD_FAILURE;
ST_CHAR *firstdollar;	/* ptr to first '$' in var name	*/
ST_CHAR *lastdollar;	/* ptr to last '$' in var name	*/
ST_INT prefixlen;	/* len of first half of generated string	*/
ST_CHAR *suffix = "ctlModel";

  firstdollar = strchr (var_name, '$');		/* find first '$'	*/
  lastdollar = strrchr (var_name, '$');		/* find last '$'	*/
  if (firstdollar && lastdollar)
    {
    prefixlen = lastdollar - firstdollar;
    if (prefixlen + strlen (suffix) <= flatname_len)
      {
      strcpy (flatname, firstdollar+1);	/* Copy text after first '$'*/
      strncpy (flatname, "CF", 2);	/* Replace CO at start with CF	*/
      strcpy (flatname + prefixlen, suffix);	/* Write new suffix after last '$'*/
      retcode = SD_SUCCESS;
      }
    }
  return (retcode);
  }

/************************************************************************/
/*			mvl61850_mkname_sbotimeout			*/
/* Generate the "flattened" name of the "sboTimeout" attribute that	*/
/* corresponds to the attribute passed as "var_name" arg.		*/
/* The var_name arg should always be of the following form:		*/
/*	LNodeName$CO$yyy$SBO						*/
/* This funct generates a name like this ("LNodeName$" stripped off):	*/
/*	CF$yyy$sboTimeout						*/
/************************************************************************/
ST_RET mvl61850_mkname_sbotimeout (ST_CHAR *var_name, ST_CHAR *flatname, size_t flatname_len)
  {
ST_CHAR *firstdollar;	/* ptr to first '$' in var name	*/
ST_CHAR *lastdollar;	/* ptr to last '$' in var name	*/
ST_INT prefixlen;	/* len of first half of generated string	*/
ST_CHAR *suffix = "sboTimeout";	/* replacement text to put after last '$'*/
ST_RET retcode = SD_FAILURE;

  firstdollar = strchr (var_name, '$');		/* find first '$'	*/
  lastdollar = strrchr (var_name, '$');		/* find last '$'	*/
  if (firstdollar && lastdollar)
    {
    prefixlen = lastdollar - firstdollar;
    if (prefixlen + strlen (suffix) <= flatname_len)	/* room to replace*/
      {
      strcpy (flatname, firstdollar+1);	/* Copy text after first '$'*/
      strncpy (flatname, "CF", 2);	/* Replace CO at start with CF	*/
      strcpy (flatname + prefixlen, suffix);	/* Write new suffix after last '$'*/
      retcode = SD_SUCCESS;
      }
    }
  return (retcode);
  }

/************************************************************************/
/*			mvl61850_ctl_chk_sbo				*/
/* This function should be called from "leaf" function when IEC 61850	*/
/* "SBO" attribute is being read (i.e. performing Control Model 'Select'*/
/* Service). It checks if client is allowed to perform 'Select'.	*/
/* If 'Select' allowed, it reserves a MVL_SBO_CTRL struct and returns	*/
/* a ptr to it.								*/
/* RETURNS:  ptr to struct if successful (sbo_var member of struct	*/
/*           contains name to send in read response).			*/
/*	     NULL if failed.						*/
/* CRITICAL: if return is NOT NULL & caller decides not to allow	*/
/*           'Select', must pass this ptr to mvlu_sbo_ctrl_free.	*/
/************************************************************************/
MVL_SBO_CTRL *mvl61850_ctl_chk_sbo (MVLU_RD_VA_CTRL *mvluRdVaCtrl)
  {
MVL_VAR_ASSOC *va;
ST_CHAR sboName[MAX_SBO_NAME_SIZE+1];
MVL_SBO_CTRL *sboCtrl = NULL;
ST_CHAR *lastdollar;	/* ptr to last '$' in var name	*/
/* Init sboTimeout=0. If ..$CF$..$sboTimeout==0, or not found, set to default val.*/
ST_UINT32 sboTimeout = 0;	/* SBO timeout value.	*/
ST_CHAR sboTimeoutName [MAX_IDENT_LEN+1];	/* "CF$...$sboTimeout"	*/
ST_BOOLEAN loc_stval;

/* First take care of timeout housekeeping  			*/
  mvlu_sbo_chk_timers ();

/* find the name of the attribute being selected		*/
  va = mvluRdVaCtrl->rdVaCtrl->va;

/* Check value of "ST$Loc$stVal".	*/
  if (mvlu_get_leaf_val_boolean (va->base_va, "ST$Loc$stVal", &loc_stval)!=SD_SUCCESS)
    loc_stval = SD_FALSE;	/* if can't read ST$Loc$stVal, assume FALSE*/
  if (loc_stval)
    {
    MVL_LOG_NERR1 ("Reading of '%s' not allowed: Local mode is set.", va->name);
    return (NULL);	/* error return	*/
    }

/* Only perform "Select" if SBO is ONLY attribute being read.	*/
/* Check this by seeing if variable name ends with "$SBO".	*/
/* Point to where "$SBO" should be, then see if it's there.	*/
  lastdollar = strrchr (va->name, '$');		/* find last '$'	*/
  if (lastdollar != NULL && strcmp (lastdollar+1, "SBO") == 0)
    {
    ST_INT8 ctlModel;
    ST_CHAR flatname [MAX_IDENT_LEN + 1];	/* attribute to find	*/

    /* Generate "ctlModel" leaf name and try to read its value.	*/
    /* CRITICAL: this only works if va->name checked first (i.e. it ends in "$SBO")*/
    if (mvl61850_mkname_ctlmodel (va->name, flatname, MAX_IDENT_LEN) != SD_SUCCESS
        || mvlu_get_leaf_val_int8 (va->base_va, flatname, &ctlModel) != SD_SUCCESS)
      ctlModel = MVL61850_CTLMODEL_STATUS_ONLY;	/* can't read ctlModel. assume status-only*/

    if (ctlModel != MVL61850_CTLMODEL_SBO_NORMAL)
      {
      MVL_LOG_NERR3 ("Reading of '%s' not allowed: ctlModel=%d, expected ctlModel=%d (sbo-with-normal-security)",
                     va->name, ctlModel, MVL61850_CTLMODEL_SBO_NORMAL);
      return (NULL);	/* error return	*/
      }

/* Create sboName from var name.	*/
    mvl61850_sbo_create_sboname (va, &mvluRdVaCtrl->rdVaCtrl->va_scope, sboName);

/* Find "sboTimeout" value.	*/
  if (mvl61850_mkname_sbotimeout (va->name, sboTimeoutName, MAX_IDENT_LEN) != SD_SUCCESS ||
      mvlu_get_leaf_val_uint32 (va->base_va, sboTimeoutName, &sboTimeout) != SD_SUCCESS ||
      sboTimeout==0)		/* ..$CF$..$sboTimeout==0, or not found	*/
    sboTimeout = SBO_SELECT_TIMEOUT;	/* set timeout to default val	*/

/* Get a SBO control element */
    sboCtrl = initSboCtrl (mvluRdVaCtrl->indCtrl->event->net_info,sboName,
              sboTimeout, SD_TRUE);	/* timeout in milliseconds*/
    }

  return (sboCtrl);
  }

/************************************************************************/
/*			mvl61850_ctl_chk_sbow				*/
/* This function should be called from "leaf" function when IEC 61850	*/
/* an attribute inside the "SBOw" structure is being written		*/
/* (i.e. performing Control Model 'Select' Service for			*/
/* sbo-with-enhanced-security).						*/
/* It checks if client is allowed to perform 'Select'.			*/
/* If 'Select' allowed, it reserves a MVL_SBO_CTRL struct and returns	*/
/* a ptr to it.								*/
/* RETURNS:  ptr to struct if successful (sbo_var member of struct	*/
/*           contains name to send in read response).			*/
/*	     NULL if failed.						*/
/* CRITICAL: if return is NOT NULL & caller decides not to allow	*/
/*           'Select', caller must pass this ptr to mvlu_sbo_ctrl_free.	*/
/* NOTE: this is very similar to mvl61850_ctl_chk_sbo, but it is used	*/
/*       when writing "SBOw" instead of when reading "SBO".		*/
/************************************************************************/
MVL_SBO_CTRL *mvl61850_ctl_chk_sbow (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
MVL_VAR_ASSOC *va;
ST_CHAR sboName[MAX_SBO_NAME_SIZE+1];
MVL_SBO_CTRL *sboCtrl = NULL;
ST_CHAR *lastdollar;	/* ptr to last '$' in var name	*/
/* Init sboTimeout=0. If ..$CF$..$sboTimeout==0, or not found, set to default val.*/
ST_UINT32 sboTimeout = 0;	/* SBO timeout value.	*/
ST_CHAR sboTimeoutName [MAX_IDENT_LEN+1];	/* "CF$...$sboTimeout"	*/
ST_BOOLEAN loc_stval;

/* First take care of timeout housekeeping  			*/
  mvlu_sbo_chk_timers ();

  va = mvluWrVaCtrl->wrVaCtrl->va;

/* Check value of "ST$Loc$stVal".	*/
  if (mvlu_get_leaf_val_boolean (va->base_va, "ST$Loc$stVal", &loc_stval)!=SD_SUCCESS)
    loc_stval = SD_FALSE;	/* if can't read ST$Loc$stVal, assume FALSE*/
  if (loc_stval)
    {
    MVL_LOG_NERR1 ("Reading of '%s' not allowed: Local mode is set.", va->name);
    return (NULL);	/* error return	*/
    }

/* Only perform "Select" if entire SBOw is written & nothing else.*/
/* Check this by seeing if variable name ends with "$SBOw".	*/
/* Point to where "$SBOw" should be, then see if it's there.	*/
  lastdollar = strrchr (va->name, '$');		/* find last '$'	*/
  if (lastdollar != NULL && strcmp (lastdollar+1, "SBOw") == 0)
    {
    ST_INT8 ctlModel;
    ST_CHAR flatname [MAX_IDENT_LEN + 1];	/* attribute to find	*/

    /* Generate "ctlModel" leaf name and try to read its value.		*/
    /* CRITICAL: this only works if va->name checked first (i.e. it ends in "$SBOw")*/
    if (mvl61850_mkname_ctlmodel (va->name, flatname, MAX_IDENT_LEN) != SD_SUCCESS
        || mvlu_get_leaf_val_int8 (va->base_va, flatname, &ctlModel) != SD_SUCCESS)
      ctlModel = MVL61850_CTLMODEL_STATUS_ONLY;	/* can't read ctlModel. assume status-only*/

    if (ctlModel != MVL61850_CTLMODEL_SBO_ENHANCED)
      {
      MVL_LOG_NERR3 ("Writing of '%s' not allowed: ctlModel=%d, expected ctlModel=%d (sbo-with-enhanced-security)",
                     va->name, ctlModel, MVL61850_CTLMODEL_SBO_ENHANCED);
      return (NULL);
      }

    /* Create sboName from var name.	*/
    /* NOTE: the sboName is not really used for "SBOw", but the "initSboCtrl"*/
    /*   function (originally written only for "SBO") needs it.		*/
    mvl61850_sbo_create_sboname (va, &mvluWrVaCtrl->wrVaCtrl->va_scope, sboName);

    /* Find "sboTimeout" value.	*/
    if (mvl61850_mkname_sbotimeout (va->name, sboTimeoutName, MAX_IDENT_LEN) != SD_SUCCESS ||
        mvlu_get_leaf_val_uint32 (va->base_va, sboTimeoutName, &sboTimeout) != SD_SUCCESS ||
        sboTimeout==0)		/* ..$CF$..$sboTimeout==0, or not found	*/
      sboTimeout = SBO_SELECT_TIMEOUT;	/* set timeout to default val	*/

    /* Get a SBO control element */
    sboCtrl = initSboCtrl (mvluWrVaCtrl->indCtrl->event->net_info, sboName, 
              sboTimeout, SD_TRUE);	/* timeout in milliseconds*/
    }

  return (sboCtrl);
  }

/************************************************************************/
/*			mvl61850_ctl_chk_state				*/
/* Check ctlModel, etc. to determine if control is right type &		*/
/* in right state.							*/
/************************************************************************/
ST_RET mvl61850_ctl_chk_state (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
MVL_VAR_ASSOC *base_var = mvluWrVaCtrl->wrVaCtrl->va->base_va;
ST_INT8 ctlModel;
ST_BOOLEAN loc_stval;
ST_RET retcode = SD_FAILURE;	/* many reasons to fail so assume failure*/
ST_CHAR flatname [MAX_IDENT_LEN + 1];	/* attribute to find	*/
ST_CHAR *lastdollar;	/* ptr to last '$' in var name	*/

  /* Only allow "Operate" if writing ALL of "Oper" and ONLY "Oper".	*/
  /* Check this by seeing if variable name ends with "$Oper".		*/
  /* Point to where "$Oper" should be, then see if it's there.		*/
  lastdollar = strrchr (mvluWrVaCtrl->wrVaCtrl->va->name, '$');	/* find last '$'*/
  if (lastdollar == NULL || strcmp (lastdollar+1, "Oper") != 0)
    return (retcode);	/* ERROR: not writing ALL of Oper and ONLY Oper.*/

  /* Check value of "ST$Loc$stVal".	*/
  if (mvlu_get_leaf_val_boolean (base_var, "ST$Loc$stVal", &loc_stval)!=SD_SUCCESS)
    loc_stval = SD_FALSE;	/* if can't read ST$Loc$stVal, assume FALSE*/
  if (loc_stval == SD_FALSE)
    {
    /* Generate "ctlModel" leaf name and try to read its value.	*/	
    if (mvl61850_mkname_ctlmodel (mvluWrVaCtrl->wrVaCtrl->va->name, flatname, MAX_IDENT_LEN) != SD_SUCCESS
        || mvlu_get_leaf_val_int8 (base_var, flatname, &ctlModel) != SD_SUCCESS)
      ctlModel = MVL61850_CTLMODEL_STATUS_ONLY;	/* can't read ctlModel. assume status-only*/

    if (ctlModel == MVL61850_CTLMODEL_DIRECT_NORMAL  ||
        ctlModel == MVL61850_CTLMODEL_DIRECT_ENHANCED)
      {	/* This is Direct control.	*/
      retcode = SD_SUCCESS;	/* OK to write data later	*/
      }
    else if (ctlModel == MVL61850_CTLMODEL_SBO_NORMAL  ||
             ctlModel == MVL61850_CTLMODEL_SBO_ENHANCED)
      {	/* This is SBO control.	*/
      /* Chk sboCtrl (set by startElWrites if client writing "Oper").	*/
      if (mvluWrVaCtrl->wrVaCtrl->sboCtrl)
        retcode = SD_SUCCESS;	/* OK to write data later	*/
      }
    else
      {
      /* ctlModel="status-only" or invalid. Do nothing (already set retcode=SD_FAILURE)*/
      }
    }	/* end "if (loc_stval == SD_FALSE)"  (i.e. "remote" mode)	*/
  return (retcode);
  }

/************************************************************************/
/*			mvl61850_ctl_command_termination		*/
/* Called by user to send "Command Termination" request for controls	*/
/* with "Enhanced Security".						*/
/************************************************************************/
ST_RET mvl61850_ctl_command_termination (MVL_NET_INFO *net_info, ST_CHAR *oper_ref,
            ST_RET status, MVL61850_LAST_APPL_ERROR *last_appl_error)
  {
OBJECT_NAME nvl_obj;	/* NVL object name	*/
MVL_NVLIST_CTRL *nvlist_ctrl;
ST_INT num_var;
OBJECT_NAME var_obj[2];	/* array of var object names (1 or 2 depending on status)*/
MVL_VAR_ASSOC *last_appl_var = NULL;	/* var assoc for "LastApplError"*/
ST_RET ret;
ST_CHAR oper_ref_local[MAX_IDENT_LEN+1];	/* local copy of oper_ref arg	*/

  ret = SD_SUCCESS;	/* assume success	*/

  /* Create tmp NVL used only for building this rpt.	*/
  nvl_obj.object_tag = VMD_SPEC;
  nvl_obj.obj_name.vmd_spec = "tmp_nvl_for_rpt";

  /* Fill in var_obj array.	*/
  num_var = 0;
  if (status != SD_SUCCESS)
    {			/* On error, include "LastApplError" in report.	*/
    ST_INT type_id;
    /* Create temporary VMD_SPEC "LastApplError" variable.	*/
    /* If this fails, mvl_vmd_nvl_add will also fail later.	*/ 
    type_id = mvl_typename_to_typeid ("LastApplErrorType");
    if (type_id >= 0)
      {
      var_obj[num_var].object_tag = VMD_SPEC;
      var_obj[num_var].obj_name.vmd_spec = "LastApplError";
      /* NOTE: last_appl_error points to temporary data. This var must be deleted before returning*/
      last_appl_var = mvl_vmd_var_add (&mvl_vmd, &var_obj[num_var],
            NULL,	/* (MVL_NET_INFO *)	*/
            type_id,
            last_appl_error,	/* data ptr (saved in var->data)	*/
            NULL,	/* (MVL_VAR_PROC *)	*/
            SD_FALSE);	/* DO NOT copy the var name	*/
      }
    num_var++;
    }
  /* Add this control object (LN$FC$xxx$Oper) to "var_obj".	*/
  var_obj[num_var].object_tag = DOM_SPEC;	/* ALWAYS Domain specific*/
  /* strtok modifies input buffer, so copy oper_ref to local buffer first.	*/
  strcpy (oper_ref_local, oper_ref);
  var_obj[num_var].domain_id = strtok (oper_ref_local, "/");	/*extract dom name*/
  var_obj[num_var].obj_name.vmd_spec = strtok (NULL, "");
  if (var_obj[num_var].obj_name.vmd_spec == NULL)
    {
    MVL_LOG_ERR1 ("Invalid ControlObjectReference '%s', cannot send CommandTermination", oper_ref);
    ret = SD_FAILURE;
    }
  else
    {
    num_var++;

    nvlist_ctrl = mvl_vmd_nvl_add (&mvl_vmd, &nvl_obj, NULL,	/* net_info: not needed*/
                   num_var, var_obj, SD_TRUE);	/* copy name	*/

    /* Now send report	*/
    if (nvlist_ctrl)
      {
      ret = mvl_info_variables (net_info, nvlist_ctrl, SD_TRUE);	/* listOfVariables*/
      mvl_vmd_nvl_remove (&mvl_vmd, &nvl_obj, NULL);	/* done with tmp NVL	*/
      }
    else
      ret = SD_FAILURE;
    }
  /* If temporary "LastApplError" var created, destroy it now.	*/
  if (last_appl_var)
    mvl_vmd_var_remove (&mvl_vmd, &var_obj[0], NULL);	/* always first in "var_obj" array*/
    
  return (ret);
  }

/************************************************************************/
/*			mvl61850_ctl_lastapplerror_create		*/
/* Create type to use later when "temporary" LastApplError var created.	*/
/************************************************************************/
ST_RET mvl61850_ctl_lastapplerror_create ()
  {
ST_RET retcode = SD_SUCCESS;
ST_CHAR *LastApplErrorTdl = "{\
    (CntrlObj)Vstring65,\
    (Error)Byte,\
    (Origin){(orCat)Byte,(orIdent)OVstring64},\
    (ctlNum)Ubyte,\
    (AddCause)Byte}";

  /* Maybe this type was already created. If it does NOT exist, create it.*/
  if (mvl_typename_to_typeid ("LastApplErrorType") < 0)
    {
    if (mvl_type_id_create_from_tdl ("LastApplErrorType",LastApplErrorTdl) < 0)
      retcode = SD_FAILURE;	/* create failed	*/
    }
  return (retcode);
  }

/************************************************************************/
/*			mvl61850_ctl_lastapplerror_send			*/
/* Called by user to send "LastApplError" information report.		*/
/************************************************************************/
ST_RET mvl61850_ctl_lastapplerror_send (MVL_NET_INFO *net_info,
	MVL61850_LAST_APPL_ERROR *last_appl_error)
  {
OBJECT_NAME nvl_obj;	/* NVL object name	*/
MVL_NVLIST_CTRL *nvlist_ctrl;
ST_INT num_var;
OBJECT_NAME var_obj;			/* temporary var object name	*/
MVL_VAR_ASSOC *last_appl_var = NULL;	/* var assoc for "LastApplError"*/
ST_RET ret;
ST_INT type_id;

  ret = SD_SUCCESS;	/* assume success	*/

  /* Create tmp NVL used only for building this rpt.	*/
  nvl_obj.object_tag = VMD_SPEC;
  nvl_obj.obj_name.vmd_spec = "tmp_nvl_for_rpt";

  /* Fill in var_obj.	*/
  num_var = 1;
  /* Create temporary VMD_SPEC "LastApplError" variable.	*/
  /* If this fails, mvl_vmd_nvl_add will also fail later.		*/ 
  type_id = mvl_typename_to_typeid ("LastApplErrorType");
  if (type_id >= 0)
    {
    var_obj.object_tag = VMD_SPEC;
    var_obj.obj_name.vmd_spec = "LastApplError";
    /* NOTE: last_appl_error points to temporary data. This var must be deleted before returning*/
    last_appl_var = mvl_vmd_var_add (&mvl_vmd, &var_obj,
            NULL,	/* (MVL_NET_INFO *)	*/
            type_id,
            last_appl_error,	/* data ptr (saved in var->data)	*/
            NULL,	/* (MVL_VAR_PROC *)	*/
            SD_FALSE);	/* DO NOT copy the var name	*/

    nvlist_ctrl = mvl_vmd_nvl_add (&mvl_vmd, &nvl_obj, NULL,	/* net_info: not needed*/
                   num_var, &var_obj, SD_TRUE);	/* copy name	*/

    /* Now send report	*/
    if (nvlist_ctrl)
      {
      ret = mvl_info_variables (net_info, nvlist_ctrl, SD_TRUE);	/* listOfVariables*/
      mvl_vmd_nvl_remove (&mvl_vmd, &nvl_obj, NULL);	/* done with tmp NVL	*/
      }
    else
      ret = SD_FAILURE;
    }
  else
    ret = SD_FAILURE;

  /* If temporary "LastApplError" var created, destroy it now.	*/
  if (last_appl_var)
    mvl_vmd_var_remove (&mvl_vmd, &var_obj, NULL);
    
  if (ret != SD_SUCCESS)
    MVL_LOG_ERR0 ("Error sending LastApplError");
  return (ret);
  }
