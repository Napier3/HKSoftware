/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2004-2005 All Rights Reserved					*/
/*									*/
/* MODULE NAME : userleaf.c						*/
/* PRODUCT(S)  : MMS-EASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	User customized "leaf" functions.				*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*			u_set_all_leaf_functions			*/
/*			u_custom_rd_ind					*/
/*			u_custom_wr_ind					*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 02/21/07  RKR    11     more work on u_custom_rd                     */
/* 02/13/07  RKR    10     changed u_custom_rd_ind to emulate data chngs*/
/* 11/22/06  JRB    09     Fill in LastApplError struct if control fails*/
/* 08/17/06  JRB    08     Add set_rpt_reason to detect data, quality	*/
/*			   changes for reports.				*/
/* 09/20/05  JRB    07     Del assert in u_custom_wr_ind, doesn't work now.*/
/* 09/13/05  JRB    06     Add u_ctl_sbow_comp_wr_ind for writing "SBOw".*/		
/*			   Simplify ..nest_level computation.		*/
/*			   Del unneeded memcpy in "wr_ind" functs.	*/
/* 06/03/05  JRB    05     Add chk for (map_head_sorted == NULL).	*/
/* 11/04/04  JRB    04     Replace u_sbo*, u_direct* with u_ctl_oper_*	*/
/*			   functs that check "Loc$stVal" & "ctlModel" vals.*/
/*			   Del unneeded found_sbo flag.			*/
/* 			   Add u_ctl_sbo_rd_ind leaf function to replace*/
/*			   mvl61850_sbo_select_rd_ind deleted from lib.	*/
/* 09/20/04  JRB    03     Add SBO, Oper, Cancel leaf functions.	*/
/* 08/05/04  JRB    02     Use new user header file.			*/
/* 06/08/04  JRB    01     Initial Revision.				*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "usermap.h"	/* for DATA_MAP, etc.	*/
#include "slog.h"
#include "mvl_defs.h"
#include "mvl_uca.h"
#include "mvl_log.h"
#include "stdtime.h"
#include "stdtime_mms_utctime.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/************************************************************************/
/*			TRACK2_INFO structure				*/
/* Simplified version of TRACK_INFO in "usermap.h".			*/ 
/************************************************************************/
typedef struct
  {
  ST_INT str_nest;			/* current struct nest level	*/
  /* rt_type of start of structs containing this leaf. First entry is 	*/
  /* top level struct, next is lower level struct, etc.			*/
  RUNTIME_TYPE *rt_type_str_start [MAX_NEST_LEVEL];
  } TRACK2_INFO;

/************************************************************************/
/*			u_set_all_leaf_functions			*/
/* User customizable function to set all leaf functions for a data type.*/
/* NOTE: leaf functions never used for RT_STR_START, RT_ARR_START,	*/
/*       etc. but they're set anyway because it's easier to set all.	*/
/* NOTE: this function may be customized for each application.		*/
/*       It should be placed in a "user" module.			*/
/************************************************************************/
ST_RET u_set_all_leaf_functions (RUNTIME_CTRL *rt_ctrl)
  {
RUNTIME_TYPE *rt_type;
/* These are indices into the arrays of Read & Write leaf function pointers.*/
ST_RTINT idx_u_custom_rd_ind;
ST_RTINT idx_u_custom_wr_ind;
ST_RTINT idx_u_ctl_sbo_rd_ind;	/* index for SBO Select Read ind funct.	*/
ST_RTINT idx_u_no_write_allowed;	/* index for Write not allowed ind funct.*/
ST_RTINT idx_u_ctl_oper_ctlval_wr_ind;
ST_RTINT idx_u_ctl_oper_other_wr_ind;
ST_RTINT idx_u_cancel_comp_wr_ind;
ST_RTINT idx_u_ctl_sbow_comp_wr_ind;
ST_RTINT idx_mvl61850_beh_stval_rd_ind;
ST_INT j;
ST_RET retcode = SD_SUCCESS;
ST_CHAR *comp_name;
ST_INT oper_nest_level = 0;	/* > 0 if inside "Oper" struct	*/
ST_INT cancel_nest_level = 0;	/* > 0 if inside "Cancel" struct	*/
ST_INT sbow_nest_level = 0;	/* > 0 if inside "SBOw" struct	*/
TRACK2_INFO track_info;
ST_CHAR *lowest_struct_name;	/* name of lowest level struct	*/
  memset (&track_info, 0, sizeof (track_info));	/* CRITICAL: initialize track_info*/

  /* Find the customized rd and wr leaf functions to use for this application.*/
  idx_u_custom_rd_ind = mvlu_find_rd_ind_fun_index ("u_custom_rd_ind");
  idx_u_custom_wr_ind = mvlu_find_wr_ind_fun_index ("u_custom_wr_ind");

  idx_u_ctl_sbo_rd_ind = mvlu_find_rd_ind_fun_index ("u_ctl_sbo_rd_ind");
  idx_u_no_write_allowed = mvlu_find_wr_ind_fun_index ("u_no_write_allowed");

  idx_u_ctl_oper_ctlval_wr_ind = mvlu_find_wr_ind_fun_index ("u_ctl_oper_ctlval_wr_ind");
  idx_u_ctl_oper_other_wr_ind = mvlu_find_wr_ind_fun_index ("u_ctl_oper_other_wr_ind");

  idx_u_cancel_comp_wr_ind = mvlu_find_wr_ind_fun_index ("u_cancel_comp_wr_ind");

  idx_mvl61850_beh_stval_rd_ind = mvlu_find_rd_ind_fun_index ("mvl61850_beh_stval_rd_ind");

  idx_u_ctl_sbow_comp_wr_ind = mvlu_find_wr_ind_fun_index ("u_ctl_sbow_comp_wr_ind");

  /* Do not continue unless ALL necessary leaf functions are found.	*/
  if (   idx_u_custom_rd_ind >= 0
      && idx_u_custom_wr_ind >= 0
      && idx_u_ctl_sbo_rd_ind >= 0
      && idx_u_no_write_allowed >= 0
      && idx_u_ctl_oper_ctlval_wr_ind >= 0
      && idx_u_ctl_oper_other_wr_ind >= 0
      && idx_u_cancel_comp_wr_ind >= 0
      && idx_u_ctl_sbow_comp_wr_ind >= 0
      )
    {
    /* Set the leaf function index for every leaf.		*/
    for (j = 0, rt_type = rt_ctrl->rt_first;
         j < rt_ctrl->rt_num;
         j++, rt_type++)
      {
      /* Save struct names in track_info.	*/
      if (rt_type->el_tag == RT_STR_START)
        track_info.rt_type_str_start[track_info.str_nest++] = rt_type;	/* save this ptr (lowest level struct found)*/
      if (rt_type->el_tag == RT_STR_END)
        track_info.rt_type_str_start[--track_info.str_nest] = NULL;	/* clear ptr*/
      if (track_info.str_nest > 0)
        lowest_struct_name = ms_comp_name_find (track_info.rt_type_str_start[track_info.str_nest - 1]);

      comp_name = ms_comp_name_find(rt_type);
      if (strcmp (comp_name, "SBO") == 0)
        {
        rt_type->mvluTypeInfo.rdIndFunIndex = idx_u_ctl_sbo_rd_ind;
        rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_no_write_allowed;
        }
      else if (strcmp (comp_name, "Oper") == 0)
        {
        if (rt_type->el_tag == RT_STR_START)	/* "Oper" must be struct*/
          {
          oper_nest_level++;
          }
        else
          {
          MVL_LOG_ERR1 ("Attribute '%s' is not a struct. Data type is NOT a valid IEC-61850 type.", comp_name);
          retcode = SD_FAILURE;
          break;
          }
        }
      else if (strcmp (comp_name, "Cancel") == 0)
        {
        if (rt_type->el_tag == RT_STR_START)	/* "Cancel" must be struct*/
          {
          cancel_nest_level++;
          }
        else
          {
          MVL_LOG_ERR1 ("Attribute '%s' is not a struct. Data type is NOT a valid IEC-61850 type.", comp_name);
          retcode = SD_FAILURE;
          break;
          }
        }
      else if (strcmp (comp_name, "SBOw") == 0)
        {
        if (rt_type->el_tag == RT_STR_START)	/* "SBOw" must be struct*/
          {
          sbow_nest_level++;
          }
        else
          {
          MVL_LOG_ERR1 ("Attribute '%s' is not a struct. Data type is NOT a valid IEC-61850 type.", comp_name);
          retcode = SD_FAILURE;
          break;
          }
        }
      else if (strcmp (comp_name, "ctlModel") == 0)
        {
        rt_type->mvluTypeInfo.rdIndFunIndex = idx_u_custom_rd_ind;	/* use default rd leaf function*/
        rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_no_write_allowed;
        }
      else if (strcmp (comp_name, "sboClass") == 0)
        {
        rt_type->mvluTypeInfo.rdIndFunIndex = idx_u_custom_rd_ind;	/* use default rd leaf function*/
        rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_no_write_allowed;
        }
      else if (strcmp (comp_name, "stVal") == 0 && strcmp (lowest_struct_name, "Beh") == 0)
        {
        rt_type->mvluTypeInfo.rdIndFunIndex = idx_mvl61850_beh_stval_rd_ind;	/* special rd for Beh$stVal*/
        rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_no_write_allowed;
        }
      else
        {
        rt_type->mvluTypeInfo.rdIndFunIndex = idx_u_custom_rd_ind;	/* use default rd leaf function*/
        if (oper_nest_level > 0)
          {	/* inside "Oper" structure	*/
          if (rt_type->el_tag == RT_STR_START)
            oper_nest_level++;
          else if (rt_type->el_tag == RT_STR_END)
            oper_nest_level--;
          else if (strcmp (comp_name, "ctlVal") == 0 || strcmp (comp_name, "setMag") == 0)
            {
            rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_ctl_oper_ctlval_wr_ind;
            }
          else
            {
            rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_ctl_oper_other_wr_ind;
            }
          }
        else if (cancel_nest_level > 0)
          {	/* inside "Cancel" structure	*/
          if (rt_type->el_tag == RT_STR_START)
            cancel_nest_level++;
          else if (rt_type->el_tag == RT_STR_END)
            cancel_nest_level--;
          else
            rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_cancel_comp_wr_ind;
          }
        else if (sbow_nest_level > 0)
          {	/* inside "SBOw" structure	*/
          if (rt_type->el_tag == RT_STR_START)
            sbow_nest_level++;
          else if (rt_type->el_tag == RT_STR_END)
            sbow_nest_level--;
          else
            rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_ctl_sbow_comp_wr_ind;
          }
        else
          {	/* NOT inside struct: use default wr leaf function	*/
          rt_type->mvluTypeInfo.wrIndFunIndex = idx_u_custom_wr_ind;
          }
        }
      }	/* end "for" loop	*/
    }
  else
    {
    MVL_LOG_ERR0 ("u_set_all_leaf_functions: cannot find one or more read or write leaf functions");
    retcode = SD_FAILURE;
    }

  /* Make sure nesting counters came back to 0.	*/
  assert (oper_nest_level == 0);
  assert (cancel_nest_level == 0);
  assert (sbow_nest_level == 0);
  return (retcode);
  }

/************************************************************************/
/*			set_rpt_reason					*/
/* Check if this leaf is part of a scan for Report changes.		*/
/* If so, check for data-change, quality-change, etc & set rpt_reason.	*/
/* CRITICAL: this function should be modified to use the best available	*/
/*   change detection for each device.					*/
/************************************************************************/
ST_VOID set_rpt_reason (MVLU_RD_VA_CTRL *mvluRdVaCtrl)
  {
MVL_VAR_ASSOC *va;
ST_INT prim_offset;
ST_CHAR *old_data;
ST_CHAR *new_data;

  /* If scan_va_done_fun is set, this read is part of a RPT scan	*/
  /* so check for changes & set "rpt_reason".				*/
  /* NOTE: checking scan_va_done_fun is not critical, but it helps avoid*/
  /*   wasting time checking for changes on non-report data.		*/
  if (mvluRdVaCtrl->indCtrl->scan_va_done_fun)
    {
    va = mvluRdVaCtrl->rdVaCtrl->va;
    /* Need offset to find this leaf's data in "last_data" buffer.	*/
    prim_offset = mvluRdVaCtrl->primData - (ST_CHAR *) va->data;
    old_data = (ST_CHAR *) va->last_data + prim_offset;
    new_data = mvluRdVaCtrl->primData;
    if (memcmp (new_data, old_data, mvluRdVaCtrl->rt->el_size) != 0)
      {
      if (strcmp (ms_comp_name_find(mvluRdVaCtrl->rt), "q") == 0)
        {	/* set quality-change bit in rpt_reason	*/
        va->rpt_reason |= MVLU_TRGOPS_QUALITY;		/* quality-change*/
        }
      else
        {	/* set data-change bit in rpt_reason	*/
        va->rpt_reason |= MVLU_TRGOPS_DATA;		/* data-change	*/
        }
      }
    }
  }
    
/************************************************************************/
/*			u_custom_rd_ind					*/
/************************************************************************/
ST_VOID u_custom_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl)
  {
MVL_VAR_ASSOC *base_var;
DATA_MAP_HEAD *map_head_sorted;	/* head of array of (DATA_MAP *) for this var.*/
DATA_MAP *map_entry;		/* DATA_MAP for this bit of data.	*/
ST_RET retcode = SD_SUCCESS;
#if 1 /* pointers and counters for emulating data changes */
ST_INT8  *i8ptr;
ST_INT16 *i16ptr;
ST_INT32  *i32ptr;
static ST_INT8  i8 =1;
static ST_INT16 i16 =1;
static ST_INT32  i32= 1;
ST_UINT8  *u8ptr;
ST_UINT16 *u16ptr;
ST_UINT32  *u32ptr;
MMS_UTC_TIME *destutc;
static ST_UINT8  u8 =1;
static ST_UINT16 u16 =1;
static ST_UINT32  u32= 1;
ST_FLOAT  *f4ptr;
ST_DOUBLE *f8ptr;
static ST_FLOAT  f4=(ST_FLOAT)1.00;
static ST_DOUBLE f8 =(ST_DOUBLE)1.00;
STDTIME	st= {0};
#endif


  /* Use new "prim_num" to find (DATA_MAP *).	*/
  base_var = mvluRdVaCtrl->rdVaCtrl->va->base_va;

  assert (base_var->use_static_data);	/* funct only works in this mode*/

  map_head_sorted = (DATA_MAP_HEAD *) base_var->user_info;	/* it was saved here*/
  if (map_head_sorted == NULL)
    {		/* THIS IS A SERIOUS ERROR	*/
    MVL_LOG_ERR1 ("DATA mapping error: variable '%s' not mapped", base_var->name);
    retcode = SD_FAILURE;
    }
  else if (mvluRdVaCtrl->prim_num >= map_head_sorted->map_count)
    {		/* THIS IS A SERIOUS ERROR	*/
    MVL_LOG_ERR1 ("DATA mapping error: prim_num=%d exceeds limit", mvluRdVaCtrl->prim_num);
    retcode = SD_FAILURE;
    }
  else
    {
    map_entry = map_head_sorted->map_arr [mvluRdVaCtrl->prim_num];

    /* CRITICAL: "map_entry" may be NULL (i.e. this leaf not mapped).	*/
    if (map_entry)
      {
      /* CRITICAL: this chks that all mapping was correct.	*/
      if (map_entry->dataPtr != mvluRdVaCtrl->primData)
        {		/* THIS IS A SERIOUS ERROR	*/
        MVL_LOG_ERR2 ("DATA mapping error: map_entry->dataPtr=0x%X mvluRdVaCtrl->primData=0x%X",
                  map_entry->dataPtr, mvluRdVaCtrl->primData);
        retcode = SD_FAILURE;
        }
      }
    }

#if 1 /* This code randomizes values read from Integer, Unsigned, and Float leafs */
      /* It is only for testing reports and we dont't want to randomize data for  */
      /* ctlModel or sboTimeout          */
  if ((strcmp (ms_comp_name_find(mvluRdVaCtrl->rt), "i") == 0)||
      (strcmp (ms_comp_name_find(mvluRdVaCtrl->rt), "f") == 0))
    {  
      switch (mvluRdVaCtrl->rt->el_tag)
      {
      case RT_INTEGER:
        switch (mvluRdVaCtrl->rt->u.p.el_len)
  	  {
	  case 1:
	    i8ptr = (ST_INT8 *) mvluRdVaCtrl->primData;
            *i8ptr = i8++;
	    break;
	  case 2:
	    i16ptr = (ST_INT16 *) mvluRdVaCtrl->primData;
            *i16ptr = i16++;
	    break;
	  case 4:
	    i32ptr = (ST_INT32 *) mvluRdVaCtrl->primData;
            *i32ptr = i32++;
	    break;

	  }
        break;

      case RT_UNSIGNED:
        switch (mvluRdVaCtrl->rt->u.p.el_len)
	  {
	  case 1:
	    u8ptr = (ST_UINT8 *) mvluRdVaCtrl->primData;
            *u8ptr = u8++;
	    break;
	  case 2:
	    u16ptr = (ST_UINT16 *) mvluRdVaCtrl->primData;
            *u16ptr = u16++;
	    break;
	  case 4:
	    u32ptr = (ST_UINT32 *) mvluRdVaCtrl->primData;
            *u32ptr = u32++;
	    break;
	  }
        break;

      case RT_FLOATING_POINT:
         switch (mvluRdVaCtrl->rt->u.p.el_len)
	  {
	  case 4:
	    f4ptr = (ST_FLOAT *) mvluRdVaCtrl->primData;
            *f4ptr = f4;
	    f4+=(ST_FLOAT)1.375;
	    break;

	  case 8:
	    f8ptr = (ST_DOUBLE *) mvluRdVaCtrl->primData;
            *f8ptr = f8;
	    f8+=(ST_DOUBLE)1.675;
	    break;
	  }
        break;

      case RT_UTC_TIME:
        destutc = (MMS_UTC_TIME *) mvluRdVaCtrl->primData;
        GetStdTime (&st);
        StdTimeToMmsUtcTime (&st, destutc);
        break;

      default :
        break;
      }
    }/* end-if */

#endif

  /* NOTE: Data is already in static buffer. Nothing else to do.
   * Notice the 2 possible mapping errors above. If one of these errors
   * occurred, retcode==SD_FAILURE. If not, retcode==SD_SUCCESS, and
   * the data in the static buffer is sent in the read response.
   */

  if (retcode==SD_SUCCESS)
    set_rpt_reason (mvluRdVaCtrl);	/* set va->rpt_reason if necessary.*/

  mvlu_rd_prim_done (mvluRdVaCtrl, retcode);
  }

/************************************************************************/
/*			u_custom_wr_ind					*/
/************************************************************************/
ST_VOID u_custom_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
MVL_VAR_ASSOC *base_var;
DATA_MAP_HEAD *map_head_sorted;	/* head of array of (DATA_MAP *) for this var.*/
DATA_MAP *map_entry;		/* DATA_MAP for this bit of data.	*/
ST_RET retcode = SD_SUCCESS;

  /* Use new "prim_num" to find (DATA_MAP *).	*/
  base_var = mvluWrVaCtrl->wrVaCtrl->va->base_va;

  assert (base_var->use_static_data);	/* funct only works in this mode*/

  map_head_sorted = (DATA_MAP_HEAD *) base_var->user_info;	/* it was saved here*/
  if (map_head_sorted == NULL)
    {		/* THIS IS A SERIOUS ERROR	*/
    MVL_LOG_ERR1 ("DATA mapping error: variable '%s' not mapped", base_var->name);
    retcode = SD_FAILURE;
    }
  else if (mvluWrVaCtrl->prim_num >= map_head_sorted->map_count)
    {		/* THIS IS A SERIOUS ERROR	*/
    MVL_LOG_ERR1 ("DATA mapping error: prim_num=%d exceeds limit", mvluWrVaCtrl->prim_num);
    retcode = SD_FAILURE;
    }
  else
    {
    /* NOTE: this example not actually using the map_entry, but real leaf
     * function should use map_entry (especially map_entry->usr_data_info)
     * to determine how/where to write the data.
     */
    map_entry = map_head_sorted->map_arr [mvluWrVaCtrl->prim_num];
    }

  /* NOTE: the data for this leaf has already been copied to the variable.*/
  /*       To get a ptr to the data, use (mvluWrVaCtrl->primData) OR	*/
  /*       ((ST_CHAR *) base_var->data + mvluWrVaCtrl->prim_offset_base)*/

  /* retcode is always SD_SUCCESS, unless mapping error detected.*/
  mvlu_wr_prim_done (mvluWrVaCtrl, retcode);
  }

/************************************************************************/
/*			fillLastApplError				*/
/* Fill in LastApplError members just in case write fails.		*/
/************************************************************************/
static ST_VOID fillLastApplError (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
ST_CHAR *comp_name;
  comp_name = ms_comp_name_find (mvluWrVaCtrl->rt);

  if (strcmp (comp_name, "ctlNum") == 0)
    mvluWrVaCtrl->wrVaCtrl->LastApplError.ctlNum = *(ST_UINT8 *) mvluWrVaCtrl->primData;
  else if (strcmp (comp_name, "orCat") == 0)
    mvluWrVaCtrl->wrVaCtrl->LastApplError.Origin.orCat = *(ST_INT8 *) mvluWrVaCtrl->primData;
  else if (strcmp (comp_name, "orIdent") == 0)
    /* NOTE: copying el_size bytes works for any data type.		*/
    memcpy (&mvluWrVaCtrl->wrVaCtrl->LastApplError.Origin.orIdent,
        mvluWrVaCtrl->primData,
        mvluWrVaCtrl->rt->el_size);
  }
/************************************************************************/
/*			u_ctl_oper_ctlval_wr_ind			*/
/* For "controlled" component of "Oper" (ctlVal or setMag).		*/
/* Chk value of "Loc$stVal" to determine if remote control allowed.	*/
/* Chk value of "ctlModel" to determine type of control.		*/
/************************************************************************/
ST_VOID u_ctl_oper_ctlval_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
ST_RET retcode;

  /* Check ctlModel, etc. to determine if control is right type & in right state.*/
  retcode = mvl61850_ctl_chk_state (mvluWrVaCtrl);

  /* Many ways to fail. retcode==SD_FAILURE if "local" mode (Loc$stVal==FALSE)
   * if ctlModel is not appropriate,
   * if SBO Select never done or timed out,
   * if NOT writing whole "Oper" structure, etc.
   */

  /* If write failed, must set Error, AddCause members of LastApplError.*/
  /* ctlNum, Origin of LastApplError set by fillLastApplError calls.	*/
  if (retcode)
    {
    /* DEBUG: these values should be modified if specific error is known.*/
    mvluWrVaCtrl->wrVaCtrl->LastApplError.Error = 1;	/* Unknown	*/
    mvluWrVaCtrl->wrVaCtrl->LastApplError.AddCause = 0;	/* Unknown	*/
    }
    
  mvlu_wr_prim_done (mvluWrVaCtrl, retcode);
  return;      
  }
/************************************************************************/
/*			u_ctl_oper_other_wr_ind				*/
/* For "other" components of "Oper" (origin, ctlNum, etc.).		*/ 
/* Chk value of "Loc$stVal" to determine if remote control allowed.	*/
/* Chk value of "ctlModel" to determine type of control.		*/
/************************************************************************/
ST_VOID u_ctl_oper_other_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
  /* Fill in LastApplError members just in case write fails.	*/
  fillLastApplError (mvluWrVaCtrl);

  /* For this example, do exactly same as for "controlled" component.	*/
  /* In some applications, may want to just ignore this data, or	*/
  /* do something slightly different.					*/
  u_ctl_oper_ctlval_wr_ind (mvluWrVaCtrl);
  }

/************************************************************************/
/*			u_cancel_comp_wr_ind				*/
/* Write a component of the "Cancel" structure (to cancel SBO control).	*/
/* NOTE: this function just writes the data. The actual operation of	*/
/*	cancelling the SBO Select, is done automatically in		*/
/*	mvlu_wr_prim_done.						*/
/************************************************************************/
ST_VOID u_cancel_comp_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
  /* Fill in LastApplError members just in case write fails.	*/
  fillLastApplError (mvluWrVaCtrl);

  /* Chk sboCtrl (set by startElWrites if client writing "Cancel").	*/
  if (mvluWrVaCtrl->wrVaCtrl->sboCtrl)
    {
    mvlu_wr_prim_done (mvluWrVaCtrl, SD_SUCCESS);
    }
  else	/* SBO Select never done or timed out. DO NOT cancel control	*/
    mvlu_wr_prim_done (mvluWrVaCtrl, SD_FAILURE);

  return;      
  }

/************************************************************************/
/*			u_ctl_sbo_rd_ind				*/
/* If "Select" allowed, send ObjectReference of control in response.	*/
/* If "Select" NOT allowed, send "empty string" in response.		*/
/************************************************************************/
ST_VOID u_ctl_sbo_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl)
  {
MVL_SBO_CTRL *sboCtrl;

  /* This library function does all the "required" SBO checks.	*/
  sboCtrl = mvl61850_ctl_chk_sbo (mvluRdVaCtrl);
  if (sboCtrl)
    strcpy (mvluRdVaCtrl->primData, sboCtrl->sbo_var);	/* 'positive' resp*/
  else
    mvluRdVaCtrl->primData [0] = '\0';	/* 'negative' resp (empty string)*/

#if 0	/* enable this code & add additional checks if necessary	*/
  if (sboCtrl)
    {	/* SISCO checks OK.	*/
    ST_BOOLEAN user_detected_error = SD_FALSE;

    /* Add code here to perform additional checks. Set "user_detected_error = SD_TRUE" if problem found.*/

    if (user_detected_error)
      {		/* user found problem, so cleanup.	*/
      mvluRdVaCtrl->primData [0] = '\0';	/* 'negative' resp (empty string)*/
      mvlu_sbo_ctrl_free (sboCtrl);
      }
    }
#endif

  /* Always return SUCCESS. Data is 'empty string' if select not allowed.*/
  mvlu_rd_prim_done (mvluRdVaCtrl, SD_SUCCESS);
  }

/************************************************************************/
/*			u_ctl_sbow_comp_wr_ind				*/
/* Write a component of the "SBOw" structure.				*/
/* Writing the complete "SBOw" structure performs the "Select" service	*/
/* if the control model is "sbo-with-enhanced-security".		*/
/************************************************************************/
ST_VOID u_ctl_sbow_comp_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl)
  {
ST_RET retcode;	/* SD_SUCCESS or SD_FAILURE	*/
ST_CHAR *comp_name;	/* name of this component	*/
MVL_SBO_CTRL *sboCtrl;

  /* Fill in LastApplError members just in case write fails.	*/
  fillLastApplError (mvluWrVaCtrl);

  /* This function is called for each leaf of "SBOw". To avoid repeating*/
  /* SBO checks, only perform SBO checks for one "mandatory" leaf	*/
  /* within "SBOw" struct (here we look for "Check" attribute).		*/
  comp_name = ms_comp_name_find (mvluWrVaCtrl->rt);
  if (strcmp (comp_name, "Check") == 0)
    {	/* This is "Check" attribute, so do SBO checks.	*/
    /* This library function does all the "required" SBO checks.	*/
    sboCtrl = mvl61850_ctl_chk_sbow (mvluWrVaCtrl);
    if (sboCtrl)
      retcode = SD_SUCCESS;	/* 'positive' resp*/
    else
      retcode = SD_FAILURE;	/* 'negative' resp*/

#if 0	/* enable this code & add additional checks if necessary	*/
    if (sboCtrl)
      {	/* SISCO checks OK.	*/
      ST_BOOLEAN user_detected_error = SD_FALSE;

      /* Add code here to perform additional checks. Set "user_detected_error = SD_TRUE" if problem found.*/

      if (user_detected_error)
        {		/* user found problem, so cleanup.	*/
        retcode = SD_FAILURE;	/* 'negative' resp*/
        mvlu_sbo_ctrl_free (sboCtrl);
        }
      }
#endif
    }
  else
    {	/* this is NOT "Check" attribute, so skip SBO checks.	*/
    retcode = SD_SUCCESS;	/* allow the write	*/
    }

  /* If write failed, must set Error, AddCause members of LastApplError.*/
  /* ctlNum, Origin of LastApplError set by fillLastApplError calls.	*/
  if (retcode)
    {
    /* DEBUG: these values should be modified if specific error is known.*/
    mvluWrVaCtrl->wrVaCtrl->LastApplError.Error = 1;	/* Unknown	*/
    mvluWrVaCtrl->wrVaCtrl->LastApplError.AddCause = 0;	/* Unknown	*/
    }
    
  mvlu_wr_prim_done (mvluWrVaCtrl, retcode);

  return;      
  }
