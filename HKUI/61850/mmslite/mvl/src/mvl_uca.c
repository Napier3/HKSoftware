/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	       1998-2005, All Rights Reserved.		        */
/*									*/
/*		    PROPRIETARY AND CONFIDENTIAL			*/
/*									*/
/* MODULE NAME : mvl_uca.c						*/
/* PRODUCT(S)  : MMSEASE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*	Special read/write processing functions for UCA and		*/
/*	IEC 61850 objects.						*/
/*									*/
/* NOTE: define MVL61850_CTL_DISABLE to avoid calling user functions	*/
/*	(u_mvl61850_ctl_oper_*) if 61850 Controls not needed.		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/07/07  JRB     57    Add mvlu_get_leaf_val_int_any.		*/
/* 11/21/06  JRB     56    Send LastApplError if write of Oper, etc fails.*/
/* 10/30/06  JRB     55    Use new mvl_vmd_* object handling functions.	*/
/*			   mvlu_find_base_va: add args.			*/
/*			   u_mvl_get_va_aa: add args.			*/
/*			   u_gnl_ind_*: add net_info arg to		*/
/*			   elim use of global var "_mvl_curr_net_info".	*/
/*			   u_mvl_get_va_aa: do not set va->usr_ind_ctrl	*/
/*			    (done by calling functions).		*/
/* 10/26/06  JRB     54    Del unused local vars.			*/
/* 09/27/06  MDE     53	   Added MMSOP_RDWR_USR_HANDLED for IOS		*/
/* 09/13/06  JRB     52    mvlu_find_comp_type: allow non-dynamic types.*/
/* 08/09/06  JRB     51    Del u_mvl_get_nvl, u_mvl_free_nvl functions	*/
/*			   (not needed with new improved Foundry).	*/
/*			   Use "mvl_var_create/destroy" so all variables*/
/*			   created/destroyed in one place.		*/
/* 07/24/06  JRB     50    Chg some common ERR logs to FLOW.		*/
/* 03/27/06  JRB     49    Add more mvlu_get_leaf_* functions.		*/
/* 07/29/05  MDE     48    Fixed static data use for write handling	*/
/* 07/11/05  JRB     47    Call user fcts (u_mvl61850_ctl_oper_*) if	*/
/*			   !defined (MVL61850_CTL_DISABLE).		*/
/* 01/19/05  JRB     46	   u_gnl_ind_* return (-1) on error.		*/
/* 12/09/04  JRB     45    init_prim_info_recursive: fix ARR_END handling.*/
/*			   init_prim_info_arr: simplify & ret ST_VOID.	*/
/*			   Add mvlu_find_comp_type, mvlu_get_leaf_val*.	*/
/*			   Chg trim_branch_name to global mvlu_trim_..	*/
/*			   & simplify it using strrchr.			*/
/* 09/20/04  JRB     44    startElWrites: if writing "Oper" or "Cancel"	*/
/*			   struct, check SBO state.			*/
/*			   mvlu_wr_prim_done call mvlu_sbo_ctrl_free.	*/
/* 06/29/04  JRB     43    Del global var mvluUseStaticData, instead use*/
/*			   use_static_data flag in MVL_VAR_ASSOC for Read.*/
/*			   NEVER use static data for Write.		*/
/*			   startElReads, etc: add prim_info arg.	*/
/*			   Del elmntOffset, use prim_info->prim_offset.	*/
/* 11/24/03  JRB     42    getGnlVarNames: fix prefix len by using	*/
/*			   MAX_IDENT_LEN, chk overflow BEFORE writing,	*/
/*			   & add logging & asserts.			*/
/* 09/18/03  JRB     41    Allow alt acc on array of "nested" structures*/
/*			   Add some debug logging & extra comments.	*/
/* 05/02/03  JRB     40    switch(rt->el_tag): Use default for most cases*/
/* 04/04/03  JRB     39    Fix integrity/GI scan code so multiple	*/
/*			   concurrent scans don't corrupt one another.	*/
/* 12/20/02  JRB     38    Moved mvlu_set_leaf_param to mvluleaf.c	*/
/* 12/12/02  JRB     37    Use usr_resp_fun ptr to call scan done funcs.*/
/* 12/09/02  MDE     36    Made mvlu_find_uca_var global		*/
/* 11/27/02  MDE     35    Addded leaf indication handlers		*/
/* 			   Addded mvlu_find_rt_leaf			*/
/* 			   Addded mvlu_set_leaf_param 			*/
/* 11/29/01  MDE     34    Added GOOSE function pointer			*/
/* 11/14/01  EJV     33    Added support for new MMS type UtcTime:  	*/
/* 11/13/01  MDE     32    Added GOOSE scan support			*/
/* 05/21/01  MDE     31    Cleaned up memory allocation for SMEM	*/
/* 10/25/00  JRB     30    Del u_mvl & u_gnl funct ptrs. Call directly.	*/
/*			   Del mvlu_install (no longer needed).		*/
/* 08/18/00  JRB     29    Don't clear va_to_free. Need value later.	*/
/*			   mvlu_free_nvl free va->va_to_free only if	*/
/*			   it was allocated by mvlu_get_nvl.		*/
/* 08/18/00  RKR     28    Added rt fields to MVLU_ typedefs		*/
/* 07/13/00  JRB     27    Cleanup ms_comp_na.. chg for MVL_XNAME.	*/
/* 07/13/00  JRB     26    Use new ms_comp_name_find to get comp names.	*/
/* 07/13/00  JRB     25	   Move these functs to mvl_type.c:		*/
/*			     mvlu_add_rt_type, mvlu_free_rt_type.	*/
/* 06/21/00  MDE     24    Now copy base VA user_info to new VA		*/
/* 05/15/00  MDE     23    Now filder out too-long variable names	*/
/* 04/14/00  JRB     22    Lint cleanup.				*/
/* 04/05/00  RKR     21    Made MVL_XNAME a compile time option		*/
/* 04/03/00  RKR     20    Added the xName to UCA Rd and Wr Ind funs	*/
/* 03/30/00  RKR     19    Passed the expanded UCA var name to ind fun  */
/* 01/21/00  MDE     18    Now use MEM_SMEM for dynamic memory		*/
/* 12/20/99  MDE     17    Fix getArrAARtType to return SUCCESS/FAIL	*/
/* 11/03/99  JRB     16    Fix GetNameList if CA name = base var name.	*/ 
/* 09/30/99  EJV     15    Added slog macro to mvlu_rd_prim_done 	*/
/* 09/13/99  MDE     14    Added SD_CONST modifiers			*/
/* 09/07/99  MDE     13    Revised and enhanced the UCA report system	*/
/* 06/04/99  MDE     12    Now allow arrays as base VA type, other	*/
/* 			   minor changes to VA processing		*/
/* 06/04/99  MDE     11    Fixed memory leak for nested array alt acc	*/
/* 04/07/99  MDE     10    Logging improvements (fixed wrong AA log too)*/
/* 03/09/99  JRB     12    Fix illegal free of gnlNameBuf.		*/
/* 02/22/99  JRB     11    BUG FIX: Always start with clean "arrCtrl".	*/
/* 01/08/99  JRB     10    Use new "bsearch" object model. Don't use	*/
/*			   "_UCA_" prefix on va and nvl names.		*/
/* 12/11/98  MDE     09    Removed scope references from VA		*/
/* 11/17/98  MDE     08    Made mvlu_get_va_aa alloc space for name	*/
/* 11/16/98  MDE     07    Renamed internal functions (prefix '_')	*/
/* 09/21/98  MDE     06    Uninitialized ptr fix, Minor lint cleanup	*/
/* 08/11/98  MDE     05    Added UCA variable array support		*/
/* 07/13/98  MDE     04    Mixed scope NVL fixes, data alignment fix	*/
/* 06/29/98  MDE     03    Added report function pointers 		*/
/* 06/15/98  MDE     02    Changes to allow compile under C++		*/
/* 01/02/98  MDE     01    New						*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "glbsem.h"
#include "mmsdefs.h"
#include "mms_pvar.h"
#include "mms_vvar.h"
#include "mvl_uca.h"
#include "mvl_log.h"

#if defined(MVL_UCA)	/* This entire module is only valid for UCA.	*/


/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/* PRIM_INFO struct:  extra info about primitive.	*/
typedef struct
  {
  ST_UINT prim_num;		/* index to data			*/
  ST_UINT prim_offset;		/* mem offset from start of var		*/
  ST_UINT prim_offset_base;	/* mem offset from start of "base" var	*/
  } PRIM_INFO;			/* extra info about primitive	*/

/************************************************************************/

static ST_VOID mvluDefGetVaDataBufFun (ST_INT service, MVL_VAR_ASSOC *va, 
				       ST_INT size);
static ST_VOID mvluDefFreeVaDataBufFun (ST_INT service, MVL_VAR_ASSOC *va);

/************************************************************************/
/* Read/Write leaf indication override handlers */

ST_VOID (*u_mvlu_leaf_rd_ind_fun)(MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID (*u_mvlu_leaf_wr_ind_fun)(MVLU_WR_VA_CTRL *mvluWrVaCtrl);

/************************************************************************/
/* STATIC VARIABLES, LOCAL DEFINES					*/

/* GNL Variables */
static ST_CHAR *gnlNameBuf;
static ST_CHAR *currGnlNamePos;

#define _OBJ_NAME_CLONE_NAME_SIZE (65)
#define _OBJ_NAME_CLONE_SIZE (sizeof(OBJECT_NAME)+(2 * _OBJ_NAME_CLONE_NAME_SIZE))

/************************************************************************/
/* STATIC FUNCTIONS							*/

static ST_RET mvlu_find_struct_comp (ST_CHAR *compName,
			     RUNTIME_TYPE **rtIo, ST_INT *numRtIo);

static ST_VOID mvlu_handle_alt_acc (OBJECT_NAME *obj, ALT_ACCESS *alt_acc, 
				    MVL_ARR_CTRL *arrCtrl);
static ST_RET getArrAARtType (MVL_ARR_CTRL *arrCtrl, 
			RUNTIME_TYPE **pRt, ST_INT *pNumRt);
static ST_VOID cloneArrAA (ALT_ACC_EL *arrAa,  ALT_ACCESS *dest);

static ST_VOID mvlu_find_base_va (MVL_VMD_CTRL *vmd_ctrl, OBJECT_NAME *obj, MVL_NET_INFO *net_info, MVL_VAR_ASSOC **vaOut);

ST_VOID getGnlVarNames (MVL_VAR_ASSOC *va, ST_CHAR *caPtr, 
			ST_CHAR **dest, ST_INT maxNames, 
			ST_INT *numNames, ST_BOOLEAN *moreFollowsOut);
static ST_VOID mvlu_clone_objname (ST_CHAR *dest, OBJECT_NAME *src);

static ST_VOID startArrRds (MVL_IND_PEND *indCtrl, MVLAS_READ_CTRL *rdCtrl,
		     MVLAS_RD_VA_CTRL *rdVaCtrl, RUNTIME_TYPE *rt, PRIM_INFO *prim_info);
static ST_VOID startElReads (MVL_IND_PEND *indCtrl, MVLAS_READ_CTRL *rdCtrl,
		     MVLAS_RD_VA_CTRL *rdVaCtrl, 
		     RUNTIME_TYPE *rt, ST_INT rt_num, PRIM_INFO *prim_info);
static ST_VOID startArrWrs (MVL_IND_PEND *indCtrl, MVLAS_WRITE_CTRL *wrCtrl,
		     MVLAS_WR_VA_CTRL *wrVaCtrl, RUNTIME_TYPE *rt, PRIM_INFO *prim_info);
static ST_VOID startElWrites (MVL_IND_PEND *indCtrl, MVLAS_WRITE_CTRL *wrCtrl,
	  	      MVLAS_WR_VA_CTRL *wrVaCtrl, 
		      RUNTIME_TYPE *rt, ST_INT rt_num, PRIM_INFO *prim_info);
static ST_INT countPrimEl (MVL_VAR_ASSOC *va, RUNTIME_TYPE *rt, ST_INT rt_num);


ST_RET init_prim_info_recursive (PRIM_INFO *prim_info, RUNTIME_TYPE *rt_first, ST_INT rt_num, ST_UINT first_offset_base);
/************************************************************************/
/*			init_prim_info_arr				*/
/* Updates prim_info->prim_num.					*/
/* Must never find match within an array, because impossible to specify	*/
/* IEC/UCA flattened name for array element, so just ignore returns	*/
/* from init_prim_info_recursive, and finish loop anyway.		*/
/* Errors will be detected when this function returns.			*/
/************************************************************************/
ST_VOID init_prim_info_arr (PRIM_INFO *prim_info,
	RUNTIME_TYPE *rt_first,
	ST_UINT first_offset_base)	/* mem offset from start of "base" var*/
					/* for "first" prim of this var	*/
  {
ST_RTINT rt_num;
ST_RTINT num_arr_elements;	/* num of elements in array	*/
ST_RTINT j;

  assert (rt_first->el_tag == RT_ARR_START);  /* confirm this.	*/

  rt_num = rt_first->u.arr.num_rt_blks;	/* num RUNTIME_TYPE to define one element of array*/
  num_arr_elements = rt_first->u.arr.num_elmnts;
  assert (num_arr_elements > 0);

  /* Call "init_prim_info_recursive" once for each array element.	*/
  for (j = 0; j < num_arr_elements; ++j)
    {
    init_prim_info_recursive (prim_info, rt_first+1, rt_num, first_offset_base);
    }
  return;
  }
/************************************************************************/
/*			init_prim_info_recursive			*/
/* Updates prim_info->prim_num.					*/
/* NOTE: when called recursively by init_prim_info_arr, this will	*/
/*       often fail. That is to be expected.				*/
/* RETURNS:	SD_FAILURE	if NOT found yet.			*/
/*		SD_SUCCESS	if found.				*/
/************************************************************************/
ST_RET init_prim_info_recursive (PRIM_INFO *prim_info,
	RUNTIME_TYPE *rt_first,
	ST_INT rt_num,
	ST_UINT first_offset_base)	/* mem offset from start of "base" var*/
					/* for "first" prim of this var	*/
  {
RUNTIME_TYPE *rt_type;
ST_INT j;
ST_RET retcode = SD_FAILURE;

  for (j = 0, rt_type = rt_first; j < rt_num; j++, rt_type++)
    {
    /* NOTE: Usually el_size=0 for non-primitives (RT_STR_START/END,	*/
    /* RT_ARR_START/END) but sometimes el_size!=0 for padding.		*/
    prim_info->prim_offset_base += rt_type->el_size;

    switch (rt_type->el_tag)
      {
      case RT_STR_START:
      case RT_STR_END:
      case RT_ARR_END:
        break;	/* do nothing	*/
      case RT_ARR_START:
        init_prim_info_arr (prim_info, rt_type, first_offset_base);
	/* CRITICAL: Index to just before RT_ARR_END. Don't skip over it*/
        /* or its rt_type->el_size will not be added to prim_offset_base.*/
        rt_type += rt_type->u.arr.num_rt_blks;
        j += rt_type->u.arr.num_rt_blks;
        break;
      default:			/* Primitive	*/
        prim_info->prim_num++;
        break;  
      }	/* end "switch"	*/

    if (prim_info->prim_offset_base == first_offset_base)
      {
      retcode = SD_SUCCESS;	/* this is only way SD_SUCCESS returned	*/
      break;			/* break out of main loop & return	*/
      }
    if (prim_info->prim_offset_base > first_offset_base)
      {	/* Will NEVER find it. This is a SERIOUS error.	*/
      /* NOTE: this error may occur more than once if it occurs in recursive call.*/
      /*       Don't log error here. Log in init_prim_info if this funct fails.*/ 
      break;	/* stop trying	*/
      }
    }
  return (retcode);	/* SD_FAILURE if NOT found, SD_SUCCESS if found	*/
  }
  
/************************************************************************/
/*			init_prim_info					*/
/* Initializes prim_info struct. This is the main function. It calls	*/
/* init_prim_info_recursive & init_prim_info_arr recursively.		*/
/* NOTE: prim_info->prim_offset set = 0, never changed by this function.*/
/************************************************************************/
ST_RET init_prim_info (MVL_VAR_ASSOC *va, PRIM_INFO *prim_info)
  {
ST_RET retcode = SD_SUCCESS;
MVL_TYPE_CTRL *type_ctrl;

  /* Set initial values in prim_info. If this is top level var,
   * these values will be used.
   */
  prim_info->prim_num = 0;
  prim_info->prim_offset_base = 0;
  prim_info->prim_offset = 0;	/* NOTE: never changed by this function	*/

  /* If NOT top level var, must call init_prim_info_recursive to fix
   * prim_info->prim_num.
   */
  if (va->offset_from_base)
    {
    type_ctrl = mvl_type_ctrl_find (va->base_va->type_id);
    retcode = init_prim_info_recursive (prim_info,
         type_ctrl->rt,
         type_ctrl->num_rt,
         va->offset_from_base);
    if (retcode != SD_SUCCESS)
      MVL_LOG_ERR3 ("No component in variable '%s' at offset=%d. Nearest is at offset=%d",
                    va->base_va->name, va->offset_from_base, prim_info->prim_offset_base);
    }

  assert (prim_info->prim_offset == 0);	/* verify this was NOT changed	*/
  return (retcode);
  }

/************************************************************************/
/************************************************************************/
/* MANUFACTURED VARIABLE RESOLUTION FUNCTIONS				*/
/************************************************************************/
/*			u_mvl_get_va_aa					*/
/************************************************************************/
/* This function is called from MVL when it is unable to find a 	*/
/* configured MMS server variable for a READ, WRITE, or GET VARIABLE 	*/
/* ACCESS ATTRIBUTES indication. 					*/

MVL_VAR_ASSOC *u_mvl_get_va_aa (MVL_VMD_CTRL *vmd_ctrl, ST_INT service, OBJECT_NAME *obj, 
			   MVL_NET_INFO *netInfo,
		      	   ST_BOOLEAN alt_access_pres,
		      	   ALT_ACCESS *alt_acc,
		      	   ST_BOOLEAN *alt_access_done_out)
  {
ST_CHAR *name;
MVL_VAR_ASSOC *va;
MVL_VAR_ASSOC *baseVa;
ST_RET rc;
OBJECT_NAME *objClone; 
ST_CHAR objNameBuf[_OBJ_NAME_CLONE_SIZE]; 
RUNTIME_TYPE *baseRt;
ST_INT numBaseRt;
RUNTIME_TYPE *ucaRt;
ST_INT numUcaRt;
ST_CHAR *subStart;
ST_INT subTypeId;
MVL_ARR_CTRL arrCtrl;

/* Make a working copy of the variable name (mvlu_handle_alt_acc may change it)	*/
  objClone = (OBJECT_NAME *) objNameBuf;
  mvlu_clone_objname (objNameBuf, obj);

/* We will handle any alternate access here, by creating the UCA from 	*/
/* variable name.							*/
  memset (&arrCtrl, 0, sizeof (MVL_ARR_CTRL));	/* start with clean "arrCtrl"*/
  if (alt_access_pres)
    {
    mvlu_handle_alt_acc (objClone, alt_acc, &arrCtrl);
    *alt_access_done_out = SD_TRUE;
    }

/* We need to find the base type for this variable 			*/
  mvlu_find_base_va (vmd_ctrl, objClone, netInfo, &baseVa);
  if (baseVa == NULL)
    {
    MVL_LOG_NERR1 ("Could not resolve UCA variable '%s'", objClone->obj_name.vmd_spec);
    return (NULL);
    }

/* Now resolve this variable's type given it's name and the base	*/
/* type.								*/
  rc = mvl_get_runtime (baseVa->type_id, &baseRt, &numBaseRt);
  if (rc != SD_SUCCESS)
    {
    MVL_LOG_NERR1 ("Could not get RT type for type id %d", baseVa->type_id);
    return (NULL);
    }
  ucaRt = baseRt;
  numUcaRt = numBaseRt;

/* Check to see if this is for base var... name has no embedded '$'	*/
/* If is a derived variable we need to create from the variable name	*/
/* 'path' and runtime type.						*/
  name = objClone->obj_name.vmd_spec;	/* We know this is a union ...	*/
  subStart = strstr (name,"$");		/* Skip the outer (base) name 	*/
  if (subStart)
    {
  /* This is a derived variable, and we have the base UCA variable	*/
  /* Using the base runtime table and the variable name, we can get the	*/
  /* subset type for this variable					*/

    ++subStart;
    rc = mvlu_find_uca_var (&ucaRt, &numUcaRt, subStart);
    if (rc != SD_SUCCESS)
      {
      MVL_LOG_NERR1 ("Error - could not find subcomponent '%s'", subStart);
      return (NULL);
      }
    }


/* If this is an alternate access on an array, we need to copy the	*/
/* RT type so we can modify the number of elements and total size	*/
  if (arrCtrl.arrAltAccPres == SD_TRUE)
    {
    rc = getArrAARtType (&arrCtrl, &ucaRt, &numUcaRt);
    if (rc != SD_SUCCESS)
      {
      M_FREE (MSMEM_MVLU_AA, arrCtrl.alt_acc.aa);
      return (NULL);
      }
    }

/* OK, now we have the sub-runtime type, go ahead and create a temp 	*/
/* RT type and variable association.					*/
  rc = mvlu_add_rt_type (ucaRt, numUcaRt, &subTypeId);
  if (rc != SD_SUCCESS)
    {
    MVL_LOG_NERR0 ("Error - could not add temp RT type");
    return (NULL);
    }

/* Create the variable association for this variable			*/
/* CRITICAL: Must use "mvl_var_create", not "mvl_var_add" because	*/
/*   this var must not be added to list (i.e. it will not be sent in	*/
/*   GetNameList responses).						*/
  va = mvl_var_create (objClone, subTypeId,
            NULL,	/* data (set later by mvluDefGet..)	*/
            NULL,	/* (MVL_VAR_PROC *) not needed	*/
            SD_TRUE);	/* copy var name	*/
/* Set special "va" elements not set by mvl_var_create.	*/
  va->base_va = baseVa;
  va->user_info = baseVa->user_info;

  va->offset_from_base = ucaRt->mvluTypeInfo.offSet;

/* If the user elected to use offset, data or proc initialization, 	*/
/* take care of	it here.						*/

#if defined(MVLU_USE_REF)
  va->ref = ucaRt->mvluTypeInfo.ref;
#endif

/* Copy the array AA information */
  memcpy (&va->arrCtrl, &arrCtrl, sizeof (MVL_ARR_CTRL));
  va->arrCtrl.curr_index = arrCtrl.low_index;

  /* Get the data buffer */
  /* This function sets "va->data".	*/
  mvluDefGetVaDataBufFun (service, va, ucaRt->offset_to_last);

/* Good work, we are done here.	*/
  return (va);
  }

/************************************************************************/
/*			getArrAARtType					*/
/************************************************************************/

static ST_RET getArrAARtType (MVL_ARR_CTRL *arrCtrl, 
			RUNTIME_TYPE **pRt, ST_INT *pNumRt)
    {
ST_INT numRt;
ST_INT i, j;
RUNTIME_TYPE *rt;
RUNTIME_TYPE *endRt;
RUNTIME_TYPE *newRt;
ALT_ACCESS *alt_acc;
ALT_ACC_EL *alt_acc_el;	/* ptr to current entry in alt acc array	*/
ST_INT nest_level = 0;

  rt = *pRt;
  numRt = *pNumRt;

/* Check to see if further nesting with this AA selection ...	*/
  if (arrCtrl->nested == SD_FALSE)
    {
  /* If just one element, need to lose the outer array */
    if (arrCtrl->num_elmnts == 1)
      {
      numRt -= 2;
      ++rt;
      }
    }
  else	/* Further nesting is requested, let's do it!	*/
    {
  /* We only support a single drill down AA	*/
    if (arrCtrl->num_elmnts > 1)
      {
      MVL_LOG_NERR0 ("AA resolution problem - multiple elements and nested");
      return (SD_FAILURE);
      }
    numRt -= 2;
    ++rt;

  /* OK, we now need to find the type of the component ... */  
    alt_acc = &arrCtrl->alt_acc;
    /* Only support AA_COMP and AA_COMP_NEST for now.		*/
    /* If AA_COMP_NEST is used, this is recursive process.	*/
    for (j=0; j < alt_acc->num_aa; j++)
      {
      alt_acc_el = &alt_acc->aa[j];
      if (alt_acc_el->sel_type == AA_COMP || alt_acc_el->sel_type == AA_COMP_NEST)
        {
        if (alt_acc_el->sel_type == AA_COMP_NEST)
          nest_level++;
        /* find this component name within the current RUNTIME_TYPE array*/
        for (i = 0; i < numRt; ++i, ++rt)
          {
          if (!strcmp (alt_acc_el->u.component, ms_comp_name_find (rt)))
            break;
          }
        if (i >= numRt)
          {
          MVL_LOG_NERR1 ("AA resolution problem - could not find component '%s'", 
					alt_acc_el->u.component);
          return (SD_FAILURE);
	  }
        if (rt->el_tag == RT_STR_START)
          numRt = rt->u.str.num_rt_blks+2;
        else if (rt->el_tag == RT_ARR_START)
          numRt = rt->u.arr.num_rt_blks+2;
        else
          numRt = 1;
        }
      else if (alt_acc_el->sel_type == AA_END_NEST)
        nest_level--;
      else
        {
        MVL_LOG_NERR0 ("AA resolution problem - complex nested AA on array");
        return (SD_FAILURE);
        }
      }		/* end "for" loop	*/
    if (nest_level != 0)
      {
      MVL_LOG_NERR0 ("AA resolution problem - invalid nesting");
      return (SD_FAILURE);
      }
    }

/* OK, now copy the runtime type elements into a new one so we can fool	*/
/* with it.								*/
  newRt = (RUNTIME_TYPE *) M_MALLOC (MSMEM_DYN_RT, numRt * sizeof (RUNTIME_TYPE));
  memcpy (newRt, rt, numRt * sizeof (RUNTIME_TYPE));

/* Adjust the total size of the type, using scaling 			*/
  if (arrCtrl->num_elmnts > 1)
    {
    newRt->offset_to_last = rt[1].offset_to_last * arrCtrl->num_elmnts;

/* Now set the number of elements as desired				*/
    newRt->u.arr.num_elmnts = arrCtrl->num_elmnts;
    endRt = newRt + (newRt->u.arr.num_rt_blks + 1);
    endRt->u.arr.num_elmnts = arrCtrl->num_elmnts;

/* We don't want end of array padding */
    endRt->el_size = 0;
    }

  *pRt = newRt;
  *pNumRt = numRt;
  return (SD_SUCCESS);
  }

/************************************************************************/
/*                       mvlu_handle_alt_acc				*/
/************************************************************************/
/* Here we deal with an alternate access. We will simply add the 	*/
/* sub-name components to the base name to create a fully qualified UCA */
/* sub-var name								*/
/* Of course, this only handles the most simple form of alternate	*/
/* access correctly ...							*/

static ST_VOID mvlu_handle_alt_acc (OBJECT_NAME *obj, ALT_ACCESS *alt_acc,
				    MVL_ARR_CTRL *arrCtrl)
  {
ST_INT i;
ST_CHAR *name;
ST_BOOLEAN done;

  name = obj->obj_name.vmd_spec;	/* We know this is a union ...	*/
  arrCtrl->nested = SD_FALSE;
  done = SD_FALSE;
  for (i = 0; i < alt_acc->num_aa && !done; ++i)
    {
    switch (alt_acc->aa[i].sel_type)
      {
      case AA_COMP :
      case AA_COMP_NEST :
        strcat (name, "$");
        strcat (name, alt_acc->aa[i].u.component);
      break;

      case AA_INDEX_NEST :
        arrCtrl->nested = SD_TRUE;
	cloneArrAA (&alt_acc->aa[i],  &arrCtrl->alt_acc);
	/* Lets fall through into common code ... */
      case AA_INDEX :
        arrCtrl->arrAltAccPres = SD_TRUE;
        arrCtrl->low_index = (ST_RTINT) alt_acc->aa[i].u.index;
        arrCtrl->num_elmnts = 1;
        done = SD_TRUE;
      break;

      case AA_INDEX_RANGE_NEST :
        arrCtrl->nested = SD_TRUE;
	cloneArrAA (&alt_acc->aa[i],  &arrCtrl->alt_acc);
	/* Lets fall through into common code ... */
      case AA_INDEX_RANGE :
        arrCtrl->arrAltAccPres = SD_TRUE;
        arrCtrl->low_index = (ST_RTINT) alt_acc->aa[i].u.ir.low_index;
        arrCtrl->num_elmnts = (ST_RTINT) alt_acc->aa[i].u.ir.num_elmnts;
        done = SD_TRUE;
      break;

      case AA_ALL:
      case AA_ALL_NEST :
        arrCtrl->nested = SD_TRUE;
	cloneArrAA (&alt_acc->aa[i],  &arrCtrl->alt_acc);
        arrCtrl->arrAltAccPres = SD_TRUE;
        arrCtrl->low_index = 0;
        arrCtrl->num_elmnts = 0;	/* 'all' flag */
        done = SD_TRUE;
      break;

      case AA_END_NEST :
        done = SD_TRUE;
      break;

      default:
        MVL_LOG_NERR1 ("Error: Invalid alt access sel_type", 
					alt_acc->aa[i].sel_type);
      break;
      }
    }
  }

/************************************************************************/
/*				cloneArrAA				*/
/************************************************************************/

static ST_VOID cloneArrAA (ALT_ACC_EL *arrAa,  ALT_ACCESS *dest)
  {
ST_INT elCount;
ST_INT nestLevel;
ALT_ACC_EL *aaEl;

/* First let's count how many we need */
  nestLevel = 0;
  elCount = 0;
  aaEl = arrAa + 1;
  while (SD_TRUE)
    {
    if (nestLevel == 0 && aaEl->sel_type == AA_END_NEST)
      break;

    ++elCount;
    if (aaEl->sel_type == AA_COMP_NEST ||
        aaEl->sel_type == AA_INDEX_NEST ||
        aaEl->sel_type == AA_INDEX_RANGE_NEST ||
        aaEl->sel_type == AA_ALL_NEST)
      {
      ++nestLevel;
      } 
    if (aaEl->sel_type == AA_END_NEST)
      {
      --nestLevel;
      } 
    ++aaEl;
    } 

/* OK, now just calloc and copy the nested alternate access */
  if (elCount)
    {
    dest->num_aa = elCount;
    dest->aa = (ALT_ACC_EL *) M_MALLOC (MSMEM_MVLU_AA, elCount * sizeof (ALT_ACC_EL));
    memcpy (dest->aa, arrAa+1, elCount * sizeof (ALT_ACC_EL));
    }
  else
    {
    MVL_LOG_NERR0 ("Nested AA construction problem");
    }
  }

/************************************************************************/
/*                       mvlu_find_base_va				*/
/************************************************************************/
/* This function takes a MMS variable name and determines the type ID	*/
/* for the base type for the variable. This is done here by 		*/
/* extracting the name root then looking for a configured variable	*/
/* of that name.							*/

static ST_VOID mvlu_find_base_va (MVL_VMD_CTRL *vmd_ctrl, OBJECT_NAME *obj, MVL_NET_INFO *net_info, MVL_VAR_ASSOC **vaOut)
  {
MVL_VAR_ASSOC *va;
ST_CHAR *p;
ST_CHAR *name;
OBJECT_NAME *objClone; 
ST_CHAR objNameBuf[_OBJ_NAME_CLONE_SIZE]; 

  objClone = (OBJECT_NAME *) objNameBuf;
  mvlu_clone_objname (objNameBuf, obj);
  name = objClone->obj_name.vmd_spec;	/* We know this is a union ...	*/

/* See if this variable name has embedded '$', and if so wack it so	*/
/* that we have the base name to work with.				*/
  p = strstr (name,"$");
  if (p)
    *p = 0;

  va = mvl_vmd_find_var (vmd_ctrl, objClone, net_info);
  if (va && (va->flags & MVL_VAR_FLAG_UCA) == 0)
    va = NULL;	/* Found va but not UCA variable, so don't return it.	*/
  *vaOut = va;
  }

/************************************************************************/
/*                       mvlu_find_uca_var				*/
/************************************************************************/
/* This function searches a runtime type for the given UCA variable 	*/
/* name. It does this by breaking the UCA name into its components	*/
/* and then finding the name in the current level of the runtime type.	*/

ST_RET mvlu_find_uca_var (RUNTIME_TYPE **rtIo, ST_INT *numRtIo, 
				 ST_CHAR *varName)
  {
ST_CHAR nameBuf[MAX_IDENT_LEN+1];
ST_CHAR *nameToFind;
ST_CHAR *compEnd;
ST_BOOLEAN nameDone;
ST_RET ret;

/* Note that varName does not have the base name prefix */
  strcpy (nameBuf, varName);	
  nameToFind = nameBuf;
  nameDone = SD_FALSE;
  while (nameDone == SD_FALSE)
    {
  /* Isolate the component name for this level, removing subcomp names	*/
    compEnd = strstr (nameToFind, "$");
    if (compEnd != NULL)
      *compEnd = 0;
    else			/* This is the last nest level		*/
      nameDone = SD_TRUE;

  /* Find the component name in the current runtime type nest level	*/
    ret = mvlu_find_struct_comp (nameToFind, rtIo, numRtIo);
    if (ret == SD_FAILURE)
      {
      /* Many things can cause this so just use FLOW Logging.	*/
      MVLU_LOG_FLOW2 ("Could not find name component %s from name %s",
				nameToFind, varName);
      return (SD_FAILURE);
      }

  /* OK, we now have found the component in the runtime type, and our	*/
  /* runtime pointer and numRt reflect the sub-runtime type.		*/
  /* next component.							*/

  /* Prepare to find the next level component name			*/
    nameToFind = compEnd+1;
    }
  return (SD_SUCCESS);
  }

/************************************************************************/
/*                       mvlu_find_struct_comp				*/
/************************************************************************/
/* This function searches a structure runtime type for the given  	*/
/* component name at the outer level.					*/

static ST_RET mvlu_find_struct_comp (ST_CHAR *compName,
			     RUNTIME_TYPE **rtIo, ST_INT *numRtIo) 
  {
RUNTIME_TYPE *rt;
RUNTIME_TYPE *endRt;
ST_BOOLEAN foundRt;

  foundRt = SD_FALSE;
  rt = *rtIo;
  endRt = rt + *numRtIo;
  if (rt->el_tag != RT_STR_START)
    {
    MVL_LOG_NERR0 ("Find struct comp: First RT is not structure start");
    return (SD_FAILURE);
    }
  ++rt;		/* Skip the structure start */

  while (rt < endRt)
    {
    if (!strcmp (compName, ms_comp_name_find (rt)))
      {
      *rtIo = rt;
      foundRt = SD_TRUE;
      }
    switch (rt->el_tag)
      {
      case RT_STR_START :
	if (foundRt == SD_TRUE)
          {
	  *numRtIo = rt->u.str.num_rt_blks+2;
          return (SD_SUCCESS);
          }
        rt += rt->u.str.num_rt_blks+2;	/* Skip the structure contents	*/
      break;

      case RT_ARR_START :
	if (foundRt == SD_TRUE)
          {
	  *numRtIo = rt->u.arr.num_rt_blks+2;
          return (SD_SUCCESS);
          }
        rt += rt->u.arr.num_rt_blks+1; /* Skip the array contents	*/
      break;

      case RT_STR_END :
      case RT_ARR_END :
        ++rt;
      break;

      default:
	if (foundRt == SD_TRUE)
          {
	  *numRtIo = 1;
          return (SD_SUCCESS);
          }
        ++rt;
      break;
      }
    }
  return (SD_FAILURE);
  }

/************************************************************************/
/*				u_mvl_free_va				*/
/************************************************************************/
/* MVL calls this function when it is through with it. We will free	*/
/* the data buffer, and then the VA (unless it was a base VA).		*/

ST_VOID u_mvl_free_va (ST_INT service, MVL_VAR_ASSOC *va, 
			    MVL_NET_INFO *netInfo)
  {
RUNTIME_TYPE *ucaRt;
ST_INT numUcaRt;
ST_RET rc;

/* We always 'allocate' the data buffer */
   mvluDefFreeVaDataBufFun(service, va);

/* If this was not a 'base' VA, free the derived type */
  if ( (va->flags & MVL_VAR_FLAG_UCA) == 0)
    {

  /* See if we allocated the runtime type ... */
    if (va->arrCtrl.arrAltAccPres == SD_TRUE)
      {
      rc = mvl_get_runtime (va->type_id, &ucaRt, &numUcaRt);
      if (rc == SD_SUCCESS)
        M_FREE (MSMEM_DYN_RT, ucaRt);
      else
        {
        MVL_LOG_NERR0 ("Error: internal error");
        }
      if (va->arrCtrl.nested == SD_TRUE)
        M_FREE (MSMEM_MVLU_AA, va->arrCtrl.alt_acc.aa);
      }

    mvlu_free_rt_type (va->type_id);
    mvl_var_destroy (va);
    }
  }

/************************************************************************/
/************************************************************************/
/* MANUFACTURED VARIABLE_LIST RESOLUTION FUNCTIONS			*/
/************************************************************************/
/* u_mvl_get_nvl, u_mvl_free_nvl functions deleted (no longer needed).	*/
/* They were only needed because Foundry could not find the variables	*/
/* for the NVL to set "vl->entries". But new improved Foundry		*/
/* generates code like the following (only done once at startup,	*/
/* so it is much more efficient):					*/
/*
 *  varObjName.obj_name.vmd_spec = "DI$Name";
 *  varObjName.object_tag = DOM_SPEC;
 *  varObjName.domain_id = mvl_vmd.dom_tbl[6]->name;
 *  vl->entries [0] = u_mvl_get_va_aa (MMSOP_INFO_RPT, &varObjName, NULL, SD_FALSE, NULL, NULL);
 */

/************************************************************************/
/************************************************************************/
/* GET NAMELIST HELPER FUNCTIONS					*/
/* These functions are necessary because MVL does not know about our	*/
/* manufactured variables and variable lists. We will fill in part of 	*/
/* the namelist response data structure.				*/
/************************************************************************/
/************************************************************************/
/*			u_gnl_ind_vars					*/
/************************************************************************/

ST_INT u_gnl_ind_vars (MVL_NET_INFO *net_info, NAMELIST_REQ_INFO *req_info, 
			     ST_CHAR **ptr, ST_BOOLEAN *moreFollowsOut, 
			     ST_INT maxNames)
  {
ST_INT i;
ST_INT numRespNames;
ST_CHAR caBuf[100];
ST_CHAR *caPtr;
ST_CHAR *p;
ST_INT numVa;
ST_INT v;
MVL_VAR_ASSOC **va;
MVL_AA_OBJ_CTRL *aa;
MVL_DOM_CTRL *domCtrl;


  gnlNameBuf = (ST_CHAR *) M_CALLOC (MSMEM_MVLU_GNL, 1, maxNames * (MAX_IDENT_LEN +1));

/* Start by finding the VA that we should start with 			*/
/* Get the variable associations in the selected scope			*/
  numVa = 0;
  if (req_info->objscope == VMD_SPEC)
    {
    numVa = mvl_vmd.num_var_assoc;
    va = mvl_vmd.var_assoc_tbl;
    }
  else if (req_info->objscope == DOM_SPEC)
    {
    domCtrl = mvl_vmd_find_dom (&mvl_vmd, req_info->dname);
    if (domCtrl)
      {
      numVa = domCtrl->num_var_assoc;
      va = domCtrl->var_assoc_tbl;
      }
    else
      {
      MVL_LOG_NERR1 ("GetNameList variables: Domain '%s' not found", req_info->dname);
      *moreFollowsOut = SD_FALSE;
      return (-1);	/* error. This triggers error response	*/
      }
    }
  else  /* AA_SPEC */
    {
    aa = (MVL_AA_OBJ_CTRL *) net_info->aa_objs;
    if (aa)
      {
      numVa = aa->num_var_assoc;
      va = aa->var_assoc_tbl;
      }
    else
      {
      *moreFollowsOut = SD_FALSE;
      return (-1);	/* error. This triggers error response	*/
      }
    }

/* Take care of the 'continue after' business as necessary. Note that 	*/
/* we will only look at the base name.					*/
  i = 0;
  if (req_info->cont_after_pres)
    {
    caPtr = req_info->continue_after;
    strcpy (caBuf, req_info->continue_after);
    p = strstr (caBuf,"$");
    if (p)
      *p = 0;

    while (i < numVa)
      {
      p = va[i]->name;
      v = strcmp (caBuf, p);
      if (v == 0)	  	/* Exact match				*/
        break;

      if (v < 0) 		/* CA is less than real VA name		*/
        {
        if (i > 0)		/* Start with the previous VA		*/
          --i;
        break;
        }
      ++i;			/* We have not found our place yet ...	*/
      }
    }
  else
    caPtr = NULL;

  *moreFollowsOut = SD_FALSE;

  currGnlNamePos = gnlNameBuf;

/* OK, va[i] is where we start putting together our names		*/
  for (numRespNames = 0; numRespNames < maxNames && i < numVa; ++i)
    {
    ST_INT j;
    ST_INT numRespNamesStart = numRespNames;	/* save count modified by fct*/
    getGnlVarNames (va[i], caPtr, &ptr[numRespNames], 
		  maxNames, &numRespNames, moreFollowsOut);

    MVLU_LOG_DEBUG0 ("Names returned from getGnlVarNames");
    for (j = numRespNamesStart; j<numRespNames; j++)
      MVLU_LOG_CDEBUG2 ("[%d]%s", j, ptr[j]);

    caPtr = NULL;
    }
  if (i < numVa)
    *moreFollowsOut = SD_TRUE;
    
  return (numRespNames);
  }

/************************************************************************/
/*			getGnlVarNames					*/
/************************************************************************/

/* GNL Variables defines */
#define MAX_NEST_LEVEL	10

ST_VOID getGnlVarNames (MVL_VAR_ASSOC *va, ST_CHAR *caPtr, 
			ST_CHAR **dest, ST_INT maxNames, 
			ST_INT *numNames, ST_BOOLEAN *moreFollowsOut)
  {
RUNTIME_TYPE *ucaRt;
ST_INT numUcaRt;
ST_INT i;
ST_CHAR nameBuf[MAX_IDENT_LEN+1];
ST_INT nameCount;
ST_INT maxSortedNum;
ST_INT sortedNum;
ST_INT startSortedNum;
ST_CHAR *subStart;
ST_RET rc;
ST_INT baseIndexOffset;
ST_INT maxRetNames;
/* prefix len should never reach MAX_IDENT_LEN but could get very close*/
ST_CHAR namePrefix[MAX_NEST_LEVEL][MAX_IDENT_LEN+1];
ST_INT nestLevel;
ST_INT strLen;
ST_INT get;
ST_INT put;
ST_INT numNewNames;
ST_BOOLEAN compress;
ST_CHAR *comp_name;		/* component name	*/

  if ( (va->flags & MVL_VAR_FLAG_UCA) == 0)
    {  
    ++(*numNames);
    dest[0] = va->name;
    return;
    }

  memset (namePrefix, 0, sizeof(namePrefix));
  strcpy (namePrefix[0], va->name);

/* First we need to find the starting 'sortedNum', based on the CA name	*/
  nameCount = *numNames;
  startSortedNum = 1;
  if (caPtr != NULL)
    {
    baseIndexOffset = 0;
    /* CA name could be base name, or derived name.			*/
    if (strcmp (caPtr, va->name) == 0)
      {	/* CA name equals base name. Start with next name AFTER base.	*/
      startSortedNum = 1;
      }
    else if ((subStart = strstr (caPtr,"$")) == NULL)	/* Skip the base name*/
      {
      MVL_LOG_ERR1 ("Problem finding sub-type in '%s'", caPtr);
      return;
      }
    else
      {
      rc = mvl_get_runtime (va->type_id, &ucaRt, &numUcaRt);
      ++subStart; 
      rc = mvlu_find_uca_var (&ucaRt, &numUcaRt, subStart);
      if (rc == SD_SUCCESS)
        startSortedNum = ucaRt->mvluTypeInfo.sortedNum + 1;
      }
    }
  else	/* No continue after, we need to include the base name */
    {
    dest[0] = va->name;
    ++nameCount;
    baseIndexOffset = 1;
    --maxNames;
    }
  maxRetNames = maxNames - *numNames;
  maxSortedNum = startSortedNum + maxRetNames - 1;

/* OK, now we start doing the real thing. Derive names for this 	*/
/* type, put them into the dest array.					*/
/* We will save those elements with 'sortedNum' between 		*/
/* 'startSortedNum' and 'maxSortedNum'					*/

  compress = SD_FALSE;
  rc = mvl_get_runtime (va->type_id, &ucaRt, &numUcaRt);

  /* This code assumes all UCA vars are structs, so first tag must be RT_STR_START*/
  /* DEBUG: change this to "assert"?					*/
  if (ucaRt->el_tag != RT_STR_START)
    MVL_LOG_ERR1 ("IEC/UCA type (type_id=%d) is not a struct. Cannot derive variable names for GetNameList response.",
                  va->type_id);

  nestLevel = 0;
  for (i = 0; i < numUcaRt; ++i, ++ucaRt)
    {
    sortedNum = ucaRt->mvluTypeInfo.sortedNum;
    comp_name = ms_comp_name_find (ucaRt);
    if (strlen (comp_name)  &&
        sortedNum >= startSortedNum && sortedNum <= maxSortedNum)
      {
      /* Chk len is legal BEFORE writing (need room for 2 strings + '$'.*/
      if (strlen (namePrefix[nestLevel]) + strlen (comp_name) + 1 <= MAX_IDENT_LEN)
        {
        sprintf (nameBuf, "%s$%s", namePrefix[nestLevel], comp_name);
        strLen = strlen (nameBuf);
        assert (strLen <= MAX_IDENT_LEN);	/* if this fails, len chk in "if" is wrong*/
        dest[sortedNum-startSortedNum+baseIndexOffset] = currGnlNamePos;
        strcpy (currGnlNamePos, nameBuf);
        currGnlNamePos += strLen +1;
        ++nameCount;
        }
      else
        {
        MVL_LOG_NERR2 ("Derived variable name '%s$%s' too long to access",
                       namePrefix[nestLevel], comp_name);
        compress = SD_TRUE;
        }
      }

    if (ucaRt->el_tag == RT_STR_START)
      {
      comp_name = ms_comp_name_find (ucaRt);
      if (strlen (comp_name))
        {
        ++nestLevel;
        assert (nestLevel < MAX_NEST_LEVEL);
        assert (nestLevel > 0);
        strcpy (namePrefix[nestLevel], namePrefix[nestLevel-1]);
        strcat (namePrefix[nestLevel], "$");
        strcat (namePrefix[nestLevel], comp_name);
        }
      }
    else if (ucaRt->el_tag == RT_STR_END)
       --nestLevel;
    else if (ucaRt->el_tag == RT_ARR_START)
      {					     /* Skip the array elements	*/
      /* There is no way to create UCA names for objects inside an	*/
      /* array, so skip over the array.					*/
      i += (ucaRt->u.arr.num_rt_blks + 1);
      ucaRt += (ucaRt->u.arr.num_rt_blks + 1);
      }

    if (sortedNum > maxSortedNum)
      *moreFollowsOut = SD_TRUE;

    }

  /* DEBUG: at this point loop, 'nestLevel' should equal (-1). This may	*/
  /* sound strange, but nestLevel NOT incremented on first RT_STR_START,*/
  /* so last RT_STR_END makes it -1. Add assert here?			*/

  /* If we had to skip one or more names, we need to eliminate the	*/
  /* holes in the name pointer table.					*/
  if (compress == SD_TRUE)
    {
    get = 0;
    put = 0;
    numNewNames = nameCount - *numNames;
    while (put < numNewNames)
      {
      if (dest[get] != NULL)
        dest[put++] = dest[get];
      ++get;
      }
    }

  *numNames = nameCount;
  }

/************************************************************************/
/*                       u_gnl_done					*/
/************************************************************************/
/* This function is called after MVL has send the MMS response to a 	*/
/* GET_NAME_LIST indication. We will clean up memory resources.		*/

ST_VOID u_gnl_done (ST_INT16 mms_class,
			      NAMELIST_RESP_INFO *resp_info)
  {
  if (mms_class == MMS_CLASS_VAR)
    M_FREE (MSMEM_MVLU_GNL, gnlNameBuf);
  }

/************************************************************************/
/************************************************************************/
/*			u_gnl_ind_nvls					*/
/************************************************************************/

ST_INT u_gnl_ind_nvls (MVL_NET_INFO *net_info, NAMELIST_REQ_INFO *req_info, 
			     ST_CHAR **ptr, ST_BOOLEAN *moreFollowsOut, 
			     ST_INT maxNames)
  {
ST_INT v;
ST_INT i;
ST_INT num_obj;
MVL_AA_OBJ_CTRL *aa;
MVL_NVLIST_CTRL **vl;
MVL_DOM_CTRL *domCtrl;
ST_INT startIndex;
ST_INT numObjLeft;
ST_INT numRetNames;
ST_CHAR *name;

/* First get the number of objects and pointer to the object table	*/
  num_obj = 0;
  if (req_info->objscope == VMD_SPEC)
    {
    num_obj = mvl_vmd.num_nvlist;
    vl = mvl_vmd.nvlist_tbl;
    }
  else if (req_info->objscope == DOM_SPEC)
    {
    domCtrl = mvl_vmd_find_dom (&mvl_vmd, req_info->dname);
    if (domCtrl)
      {
      num_obj = domCtrl->num_nvlist;
      vl = domCtrl->nvlist_tbl;
      }
    else
      {
      MVL_LOG_NERR1 ("GetNameList NVL: Domain '%s' not found", req_info->dname);
      *moreFollowsOut = SD_FALSE;
      return (-1);	/* error. This triggers error response	*/
      }
    }
  else  /* AA_SPEC */
    {
    aa = (MVL_AA_OBJ_CTRL *) net_info->aa_objs;
    if (aa)
      {
      num_obj = aa->num_nvlist;
      vl = aa->nvlist_tbl;
      }
    else
      {
      *moreFollowsOut = SD_FALSE;
      return (-1);	/* error. This triggers error response	*/
      }
    }

  if (num_obj)
    {
  /* Take care of the 'continue after' business if necessary */
    startIndex = 0;
    if (req_info->cont_after_pres)
      {
      while (startIndex < num_obj)
        {
        name = vl[startIndex]->name;
        v = strcmp (req_info->continue_after, name);
        if (v == 0)
          {
          ++startIndex;		/* Index to the next one		*/
          break;
          }
        if (v < 0) 
          break;
  
        ++startIndex;		/* We have not found our place yet ...	*/
        }
      }

    numObjLeft = num_obj-startIndex;
    numRetNames = min(numObjLeft, maxNames);
    if (numRetNames < numObjLeft)
      *moreFollowsOut = SD_TRUE;

  /* Now make the list for the response */
    for (i = 0; i < numRetNames; ++i, ++ptr)
      *ptr = vl[startIndex+i]->name;
  
    return (numRetNames);
    }
  return (0);
  }

/************************************************************************/
/************************************************************************/
/*                       mvlu_clone_objname				*/
/************************************************************************/
/* This function 'clones' a MMS OBJECT_NAME structure, which means that	*/
/* it must allocate the various storage elements as required. Note	*/
/* that the name storage allocation is 65, to give calling routines	*/
/* room to work.							*/ 

static ST_VOID mvlu_clone_objname (ST_CHAR *dest, OBJECT_NAME *src)
  {
OBJECT_NAME *objClone;

  objClone = (OBJECT_NAME *) dest;
  memset (dest, 0, _OBJ_NAME_CLONE_SIZE);
  objClone->object_tag = src->object_tag;
  objClone->obj_name.vmd_spec = (ST_CHAR *) (objClone + 1);
  strcpy (objClone->obj_name.vmd_spec, src->obj_name.vmd_spec);
  if (src->object_tag == DOM_SPEC)
    {
    objClone->domain_id = objClone->obj_name.vmd_spec + _OBJ_NAME_CLONE_NAME_SIZE;
    strcpy (objClone->domain_id, src->domain_id);
    }
  }

/************************************************************************/
/************************************************************************/
/* MVLU READ/WRITE HANDLERS						*/
/************************************************************************/

static ST_VOID mvluDefAsyncWrIndFun (struct mvlu_wr_va_ctrl *mvluWrVaCtrl);
static ST_VOID mvluDefAsyncRdIndFun (struct mvlu_rd_va_ctrl *mvluRdVaCtrl); 

/* Function pointers for non-UCA variable handling */
ST_VOID(*mvluAsyncRdIndFun)(struct mvlu_rd_va_ctrl *mvluRdVaCtrl) = 
				mvluDefAsyncRdIndFun;
ST_VOID(*mvluAsyncWrIndFun)(struct mvlu_wr_va_ctrl *mvluWrVaCtrl) =
				mvluDefAsyncWrIndFun;

/************************************************************************/
/************************************************************************/
/************************************************************************/
/*			mvl_read_ind					*/
/************************************************************************/

ST_VOID u_mvl_read_ind (MVL_IND_PEND *indCtrl)
  {
MVLAS_READ_CTRL *rdCtrl;
MVLAS_RD_VA_CTRL *rdVaCtrl;
MVL_VAR_ASSOC *va;
MVLU_RD_VA_CTRL *mvluRdVaCtrl;
ST_INT i;
ST_INT numVar;
RUNTIME_TYPE *rt;
ST_INT numRt;
PRIM_INFO prim_info;

  rdCtrl = &indCtrl->u.rd;
  numVar = rdCtrl->numVar;

/* First we will go through each variable being read and count the	*/
/* primitive elelemts.							*/

  rdVaCtrl = rdCtrl->vaCtrlTbl;
  for (i = 0; i < numVar; ++i, ++rdVaCtrl)
    {
    va = rdVaCtrl->va;
    if (va)	  /* VA was resolved, we can deal with it		*/
      {
      mvl_get_runtime (va->type_id, &rt, &numRt);
      rdVaCtrl->acc_rslt_tag = ACC_RSLT_SUCCESS;
      rdVaCtrl->numPrimDataDone = 0;
      if (va->base_va != NULL)	/* UCA variable handling ... */
        {
        rdVaCtrl->numPrimData = countPrimEl (va, rt, numRt); 
        }
      else
        rdVaCtrl->numPrimData = 1;
      }
    else
      rdVaCtrl->numPrimData = 1;
    }

/* Now we will go through each var being read and invoke the rdInd	*/
/* function for it.							*/

  rdVaCtrl = rdCtrl->vaCtrlTbl;
  for (i = 0; i < numVar; ++i, ++rdVaCtrl)
    {
    va = rdVaCtrl->va;
    if (va)	  /* VA was resolved, we can deal with it		*/
      {

    /* The VA's data pointer is valid, as is the type ID. 		*/
    /* We want to call the handlers for all primitive level functions 	*/
    /* for this data type						*/

      if (va->base_va != NULL)	/* UCA variable handling ... */
        {
        mvl_get_runtime (va->type_id, &rt, &numRt);

        /* Initialize prim_info struct.	*/
        if (init_prim_info (va, &prim_info))
          {	/* Failed. Can't process this var. Skip to next var in list*/
          MVL_LOG_ERR1 ("init_prim_info failed for 'Read' of variable '%s'", va->name);
          rdVaCtrl->acc_rslt_tag = ACC_RSLT_FAILURE;
          continue;	/* skip to next variable	*/
          }

#if defined (IEC_61850_SERVER_OPC_CLIENT)
        /* OPC Client code runs in a separate thread and writes data to
         * the static data buffer (i.e. va->base_va->data). Need this
         * semaphore to protect access to the static data buffer.
         * CRITICAL: OPC Client must use the same semaphore.
         */
        S_LOCK_COMMON_RESOURCES ();
#endif
        startElReads (indCtrl, rdCtrl, rdVaCtrl, rt, numRt, &prim_info); 
#if defined (IEC_61850_SERVER_OPC_CLIENT)
        S_UNLOCK_COMMON_RESOURCES ();
#endif
        }
      else		/* Non-UCA variable handling ... */
        {
        mvluRdVaCtrl = (MVLU_RD_VA_CTRL *) M_CALLOC (MSMEM_MVLU_VA_CTRL, 1, 
					sizeof (MVLU_RD_VA_CTRL));
        mvluRdVaCtrl->primData = (ST_CHAR *) va->data;
        mvluRdVaCtrl->indCtrl = indCtrl;
        mvluRdVaCtrl->rdVaCtrl = rdVaCtrl;
        (*mvluAsyncRdIndFun)(mvluRdVaCtrl);
        }
      }
    else		/* VA not found, let it be done */
      {
      mvluRdVaCtrl = (MVLU_RD_VA_CTRL *) M_CALLOC (MSMEM_MVLU_VA_CTRL, 1, 
					sizeof (MVLU_RD_VA_CTRL));
      mvluRdVaCtrl->indCtrl = indCtrl;
      mvluRdVaCtrl->rdVaCtrl = rdVaCtrl;
      mvlu_rd_prim_done (mvluRdVaCtrl, SD_SUCCESS);
      }
    }
  }

/************************************************************************/
/*			mvlu_trim_branch_name				*/
/* Find last '$' in name and replace it with NULL.			*/
/************************************************************************/

ST_VOID mvlu_trim_branch_name (ST_CHAR *branch_name)
  {
ST_CHAR *ptr;
  if ((ptr = strrchr (branch_name, '$')) != NULL)	/* find last '$'*/
    *ptr = 0;	/* replace '$' with NULL	*/
  return;
  }

/************************************************************************/
/*			startElReads					*/
/************************************************************************/

static ST_VOID startElReads (MVL_IND_PEND *indCtrl, MVLAS_READ_CTRL *rdCtrl,
		     MVLAS_RD_VA_CTRL *rdVaCtrl, 
		     RUNTIME_TYPE *rt, ST_INT rt_num, PRIM_INFO *prim_info)
  {
ST_INT i;
MVLU_RD_VA_CTRL *mvluRdVaCtrl;
ST_RTINT rdIndFunIndex;
ST_UCHAR el_tag;
ST_RTINT el_size;
ST_RTINT num_rt_blks;
#if defined(MVL_XNAME)
ST_CHAR element_name[MAX_IDENT_LEN+1];  
ST_CHAR branch_name[MAX_IDENT_LEN+1];  
MVL_VAR_ASSOC *va;
ST_CHAR *comp_name;
#endif

#if defined(MVL_XNAME)
  va = rdVaCtrl->va;
  element_name[0]=0;
  strcpy (branch_name,va->name);

/* if this is a substructure we need to trim back one level of the name */
/* because the first rt element will be the name of the component 	*/
/* already part of the va->name						*/

  if ((rt_num > 1) && (strstr (branch_name,"$")))
    {
    mvlu_trim_branch_name (branch_name);
    }
#endif

  for (i = 0; i < rt_num; ++i, ++rt)
    {

#if defined(MVL_XNAME)
    if (rt_num > 1)
      {
      comp_name = ms_comp_name_find (rt);
      if (strlen (comp_name))
        {
        if ((rt->el_tag == RT_STR_START))
          {
          strcat (branch_name, "$");
          strcat (branch_name, comp_name);
          strcpy (element_name, branch_name);
          }
        else
          {
	  element_name[0]=0;
	  strcat (element_name, branch_name);
	  strcat (element_name, "$");
	  strcat (element_name, comp_name);
	  }
        }

      if (rt->el_tag == RT_STR_END)
        {
        strcpy (element_name, branch_name);
        mvlu_trim_branch_name (branch_name);
        }
      }
    else
      {   /* only one element in the RT table assume it's a primitive	*/
      strcpy (element_name, branch_name);
      }
#endif

    el_tag = rt->el_tag;
    num_rt_blks = rt->u.arr.num_rt_blks;
    el_size = rt->el_size;

    if (ms_is_rt_prim (rt) == SD_TRUE)
      {
      rdIndFunIndex = rt->mvluTypeInfo.rdIndFunIndex;
      if (u_mvlu_leaf_rd_ind_fun != NULL || 
          (rdIndFunIndex >= 0 && rdIndFunIndex < mvluNumRdFunEntries))
        {
        mvluRdVaCtrl = (MVLU_RD_VA_CTRL *) M_CALLOC (MSMEM_MVLU_VA_CTRL, 1, 
					     sizeof (MVLU_RD_VA_CTRL));
        mvluRdVaCtrl->rt = rt;
#if defined(MVL_XNAME)
    	strcpy (mvluRdVaCtrl->xName, element_name);
#endif
        mvluRdVaCtrl->primData = (ST_CHAR *) rdVaCtrl->va->data + 
      		   			     prim_info->prim_offset;
        mvluRdVaCtrl->indCtrl = indCtrl;
        mvluRdVaCtrl->rdVaCtrl = rdVaCtrl;
#if defined(MVLU_USE_REF)
        mvluRdVaCtrl->primRef = rt->mvluTypeInfo.ref;
#endif
        mvluRdVaCtrl->prim_num = prim_info->prim_num;
        mvluRdVaCtrl->prim_offset_base = prim_info->prim_offset_base;
        if (u_mvlu_leaf_rd_ind_fun == NULL)
          (*mvluRdFunInfoTbl[rdIndFunIndex].fun_ptr)(mvluRdVaCtrl);
	else
          (*u_mvlu_leaf_rd_ind_fun)(mvluRdVaCtrl);
        }
      else
        rdVaCtrl->acc_rslt_tag = ACC_RSLT_FAILURE;
      prim_info->prim_num++;
      }

    if (el_tag == RT_ARR_START)
      {
      startArrRds (indCtrl, rdCtrl, rdVaCtrl, rt, prim_info);
      i += (num_rt_blks + 1);
      rt += (num_rt_blks + 1);
      }
    else
      {
      prim_info->prim_offset      += el_size;
      prim_info->prim_offset_base += el_size;
      }
    }
  }

/************************************************************************/
/*  				startArrRds				*/
/************************************************************************/

static ST_VOID startArrRds (MVL_IND_PEND *indCtrl, MVLAS_READ_CTRL *rdCtrl,
		     MVLAS_RD_VA_CTRL *rdVaCtrl, RUNTIME_TYPE *rt, PRIM_INFO *prim_info)
  {
ST_RTINT i;
MVL_VAR_ASSOC *va;
ST_INT numRt;
ST_RTINT low_index;
ST_RTINT num_elmnts;

  numRt = rt->u.arr.num_rt_blks+2;
  va = rdVaCtrl->va;

  if (va->arrCtrl.arrAltAccPres == SD_TRUE)
    {
    low_index = va->arrCtrl.low_index;
    num_elmnts = va->arrCtrl.num_elmnts;
    }
  else
    {
    low_index = 0;
    num_elmnts = rt->u.arr.num_elmnts;
    }

/* Let's check to see if the client is selecting a sub-object ... 	*/
  prim_info->prim_offset      += rt->el_size;
  prim_info->prim_offset_base += rt->el_size;
  for (i = 0; i < num_elmnts; ++i)
    {
    va->arrCtrl.curr_index = low_index + i;
    startElReads (indCtrl, rdCtrl, rdVaCtrl, rt+1, numRt-2, prim_info);
    }
  prim_info->prim_offset      += (rt+numRt-1)->el_size;
  prim_info->prim_offset_base += (rt+numRt-1)->el_size;
  }

/************************************************************************/
/*			mvlu_rd_prim_done				*/
/************************************************************************/
/* The user calls this function acynchronously when the primitive data	*/
/* has been put in the 'primData' buffer.				*/

ST_VOID mvlu_rd_prim_done (MVLU_RD_VA_CTRL *mvluRdVaCtrl, ST_RET rc)
  {
MVL_IND_PEND *indCtrl;
MVLAS_READ_CTRL *rdCtrl;
MVLAS_RD_VA_CTRL *rdVaCtrl;
ST_INT i;

  rdVaCtrl = mvluRdVaCtrl->rdVaCtrl;

  if (rc != SD_SUCCESS)
    {
/* DEBUG LIZ: added logging why read failed */
    MVL_LOG_NERR2 ("Read failed for UCA variable '%s' rc=%d",
      rdVaCtrl->va->name, rc);
    rdVaCtrl->acc_rslt_tag = ACC_RSLT_FAILURE;
    }
    
  ++rdVaCtrl->numPrimDataDone;
  if (rdVaCtrl->numPrimDataDone == rdVaCtrl->numPrimData)
    {
    /* All primitives for "one" variable are complete.		*/
    indCtrl = mvluRdVaCtrl->indCtrl;

    if (indCtrl->scan_va_done_fun)
      (*indCtrl->scan_va_done_fun)(indCtrl, rdVaCtrl->va);

  /* If all primitives for all variables are complete, respond now */
    rdCtrl = &indCtrl->u.rd;
    rdVaCtrl = rdCtrl->vaCtrlTbl;
    for (i = 0; i < rdCtrl->numVar; ++i, ++rdVaCtrl)
      {
      if (rdVaCtrl->numPrimDataDone != rdVaCtrl->numPrimData)
        break;
      }
    if (i == rdCtrl->numVar)
      {
      if (indCtrl->op != MMSOP_READ)
        {	/* Not normal read. Do special processing.	*/
        if (indCtrl->usr_resp_fun)
          {	/* If user set custom resp fun, call it.	*/
          (*indCtrl->usr_resp_fun) (indCtrl);
          }
        }
      else
        mvlas_read_resp (indCtrl);
      }
    }
  M_FREE (MSMEM_MVLU_VA_CTRL, mvluRdVaCtrl);
  }

/************************************************************************/
/*			mvluDefAsyncRdIndFun				*/
/************************************************************************/

static ST_VOID mvluDefAsyncRdIndFun (struct mvlu_rd_va_ctrl *mvluRdVaCtrl)
  {
  mvlu_rd_prim_done (mvluRdVaCtrl, SD_SUCCESS);
  }

/************************************************************************/
/************************************************************************/
/*			mvlu_write_ind					*/
/************************************************************************/

ST_VOID u_mvl_write_ind (MVL_IND_PEND *indCtrl)
  {
MVLAS_WRITE_CTRL *wrCtrl;
MVLAS_WR_VA_CTRL *wrVaCtrl;
MVL_VAR_ASSOC *va;
MVLU_WR_VA_CTRL *mvluWrVaCtrl;
ST_INT i;
ST_INT numVar;
RUNTIME_TYPE *rt;
ST_INT numRt;
PRIM_INFO prim_info;

  wrCtrl = &indCtrl->u.wr;
  numVar = wrCtrl->numVar;

/* First we will go through each variable being written and count the	*/
/* primitive elelemts.							*/
  wrVaCtrl = wrCtrl->vaCtrlTbl;

  for (i = 0; i < numVar; ++i, ++wrVaCtrl)
    {
    va = wrVaCtrl->va;
    if (va)		/* VA was resolved, we can look it over		*/
      {
      mvl_get_runtime (va->type_id, &rt, &numRt);
      wrVaCtrl->resp_tag = WR_RSLT_SUCCESS;
      wrVaCtrl->numPrimDataDone = 0;
      if (va->base_va != NULL)	/* UCA variable handling ... */
        wrVaCtrl->numPrimData = countPrimEl (va, rt, numRt);
      else
        wrVaCtrl->numPrimData = 1;
      }
    else
      wrVaCtrl->numPrimData = 1;
    }

/* Now we will go through each var being written and invoke the wrInd	*/
/* function for it.							*/

  wrVaCtrl = wrCtrl->vaCtrlTbl;
  for (i = 0; i < numVar; ++i, ++wrVaCtrl)
    {
    va = wrVaCtrl->va;
    if (va)		/* VA was resolved, we can look it over		*/
      {
    /* The VA's data pointer is valid, as is the type ID. 		*/
    /* We want to call the handlers for all primitive level functions 	*/
    /* for this data type						*/
      if (va->base_va != NULL)	/* UCA variable handling ... */
        {
        mvl_get_runtime (va->type_id, &rt, &numRt);

        /* Initialize prim_info struct.	*/
        if (init_prim_info (va, &prim_info))
          {	/* Failed. Can't process this var. Skip to next var in list*/
          MVL_LOG_ERR1 ("init_prim_info failed for 'Write' of variable '%s'", va->name);
          wrVaCtrl->resp_tag = WR_RSLT_FAILURE;
          continue;	/* skip to next variable	*/
          }
        startElWrites (indCtrl, wrCtrl,wrVaCtrl, rt, numRt, &prim_info); 
        }
      else		/* Non-UCA variable handling ... */
        {
        mvluWrVaCtrl = (MVLU_WR_VA_CTRL *) M_CALLOC (MSMEM_MVLU_VA_CTRL, 1, 
					sizeof (MVLU_WR_VA_CTRL));
        mvluWrVaCtrl->primData = (ST_CHAR *) va->data;
        mvluWrVaCtrl->indCtrl = indCtrl;
        mvluWrVaCtrl->wrVaCtrl = wrVaCtrl;
        (*mvluAsyncWrIndFun)(mvluWrVaCtrl);
        }
      }
    else 	
      { 
      mvluWrVaCtrl = (MVLU_WR_VA_CTRL *) M_CALLOC (MSMEM_MVLU_VA_CTRL, 1, 
					sizeof (MVLU_WR_VA_CTRL));
      mvluWrVaCtrl->indCtrl = indCtrl;
      mvluWrVaCtrl->wrVaCtrl = wrVaCtrl;
      mvlu_wr_prim_done (mvluWrVaCtrl, SD_SUCCESS);
      }
    }
  }

/************************************************************************/
/*			startElWrites					*/
/************************************************************************/

static ST_VOID startElWrites (MVL_IND_PEND *indCtrl, MVLAS_WRITE_CTRL *wrCtrl,
	  	      MVLAS_WR_VA_CTRL *wrVaCtrl, 
		      RUNTIME_TYPE *rt, ST_INT rt_num, PRIM_INFO *prim_info)
  {
ST_INT i;
MVLU_WR_VA_CTRL *mvluWrVaCtrl;
ST_RTINT wrIndFunIndex;
ST_UCHAR el_tag;
ST_RTINT el_size;
ST_RTINT num_rt_blks;
#if defined(MVL_XNAME)
ST_CHAR element_name[MAX_IDENT_LEN+1];  
ST_CHAR branch_name[MAX_IDENT_LEN+1];  
MVL_VAR_ASSOC *va;
ST_CHAR *comp_name;
#endif
ST_CHAR sboName[MAX_SBO_NAME_SIZE+1];

#if !defined(MVL61850_CTL_DISABLE)
  ST_INT oper_nest_level = 0;
  MVL_NET_INFO *save_net_info = indCtrl->event->net_info;	/* save to use after indCtrl free*/
  MVL_VAR_ASSOC *base_var = wrVaCtrl->va->base_va;
#endif

#if defined(MVL_XNAME)
  va = wrVaCtrl->va;
  element_name[0]=0;
  strcpy (branch_name,va->name);

/* if this is a substructure we need to trim back one level of the name */
/* because the first rt element will be the name of the component 	*/
/* already part of the va->name		    				*/

  if ((rt_num > 1) && (strstr (branch_name, "$")))
    {
    mvlu_trim_branch_name (branch_name);
    }
#endif

  for (i = 0; i < rt_num; ++i, ++rt)
    {
#if defined(MVL_XNAME)
    if (rt_num > 1)  /* is this a collection of elements? */
      {
      comp_name = ms_comp_name_find (rt);
      if (strlen (comp_name))
        {
        if ((rt->el_tag == RT_STR_START))
          {
          strcat (branch_name, "$");
          strcat (branch_name, comp_name);
          strcpy (element_name, branch_name);
          }
        else
          {
	  element_name[0]=0;
	  strcat (element_name, branch_name);
	  strcat (element_name, "$");
	  strcat (element_name, comp_name);
	  }
        }

      if (rt->el_tag == RT_STR_END)
        {
        strcpy (element_name, branch_name);
        mvlu_trim_branch_name (branch_name);
        }
      }
    else
      {   /* only one element in the RT table assume it's a primitive */
      strcpy (element_name, branch_name);
      }
#endif

    el_tag = rt->el_tag;
    num_rt_blks = rt->u.arr.num_rt_blks;
    el_size = rt->el_size;

    /* Do some special stuff for IEC 61850 SBO controls.		*/
    /* If this comp is start of struct & comp name is "Oper" or "Cancel",*/
    /* check SBO state.							*/
    if (rt->el_tag == RT_STR_START  &&  
        (strcmp (ms_comp_name_find(rt), "Oper") == 0  ||  strcmp (ms_comp_name_find(rt), "Cancel") == 0))
      {
      /* Check "Select" timeouts for ALL SBO controls.	*/
      mvlu_sbo_chk_timers ();
      /* Chk SBO state. Save in wrVaCtrl->sboCtrl (NULL if "Select" not done).*/
      mvl61850_sbo_create_sboname (wrVaCtrl->va, &wrVaCtrl->va_scope, sboName);
      wrVaCtrl->sboCtrl = mvlu_sbo_chk_state (sboName, indCtrl->event->net_info);
      }

#if !defined(MVL61850_CTL_DISABLE)
    if (rt->el_tag == RT_STR_START)
      {
      /* only increment this if this is "Oper" or already inside "Oper".	*/
      if (oper_nest_level>0)
        oper_nest_level++;
      else if (strcmp (ms_comp_name_find(rt), "Oper") == 0)
        {
        u_mvl61850_ctl_oper_begin (sboName);
        oper_nest_level++;
        }
      }
    if (rt->el_tag == RT_STR_END)
      {
      if (oper_nest_level>0)
        {
        if (--oper_nest_level==0)
          {
          /* All leaf functs have been called for "Oper" struct.*/
          /* CRITICAL: use save_net_info because indCtrl may have been freed.*/
          u_mvl61850_ctl_oper_end (save_net_info, sboName, base_var);
          }
        }
      }
#endif	/* !defined(MVL61850_CTL_DISABLE)	*/

    if (ms_is_rt_prim (rt) == SD_TRUE)
      {
      wrIndFunIndex = rt->mvluTypeInfo.wrIndFunIndex;
      if (u_mvlu_leaf_wr_ind_fun != NULL || 
          (wrIndFunIndex >= 0 && wrIndFunIndex < mvluNumWrFunEntries))
        {
        mvluWrVaCtrl = (MVLU_WR_VA_CTRL *) M_CALLOC (MSMEM_MVLU_VA_CTRL, 1,
                                             sizeof (MVLU_WR_VA_CTRL));
#if defined(MVL_XNAME)
    	strcpy (mvluWrVaCtrl->xName, element_name);
#endif
        mvluWrVaCtrl->primData = (ST_CHAR *) wrVaCtrl->va->data + 
      		   			     prim_info->prim_offset;
        mvluWrVaCtrl->indCtrl = indCtrl;
        mvluWrVaCtrl->wrVaCtrl = wrVaCtrl;
        mvluWrVaCtrl->rt = rt;
#if defined(MVLU_USE_REF)
        mvluWrVaCtrl->primRef = rt->mvluTypeInfo.ref;
#endif
        mvluWrVaCtrl->prim_num = prim_info->prim_num;
        mvluWrVaCtrl->prim_offset_base = prim_info->prim_offset_base;
        if (u_mvlu_leaf_wr_ind_fun == NULL)
          (*mvluWrFunInfoTbl[wrIndFunIndex].fun_ptr)(mvluWrVaCtrl);
	else
          (*u_mvlu_leaf_wr_ind_fun)(mvluWrVaCtrl);
        }
      else
        wrVaCtrl->resp_tag = WR_RSLT_FAILURE;
      prim_info->prim_num++;
      }

    if (el_tag == RT_ARR_START)
      {
      startArrWrs (indCtrl, wrCtrl, wrVaCtrl, rt, prim_info);
      i += (num_rt_blks + 1);
      rt += (num_rt_blks + 1);
      }
    else
      {
      prim_info->prim_offset      += el_size;
      prim_info->prim_offset_base += el_size;
      }
    }
  }

/************************************************************************/
/* 			startArrWrs					*/
/************************************************************************/

static ST_VOID startArrWrs (MVL_IND_PEND *indCtrl, MVLAS_WRITE_CTRL *wrCtrl,
		     MVLAS_WR_VA_CTRL *wrVaCtrl, RUNTIME_TYPE *rt, PRIM_INFO *prim_info)
  {
ST_RTINT i;
MVL_VAR_ASSOC *va;
ST_INT numRt;
ST_RTINT low_index;
ST_RTINT num_elmnts;

  numRt = rt->u.arr.num_rt_blks+2;
  va = wrVaCtrl->va;

  if (va->arrCtrl.arrAltAccPres == SD_TRUE)
    {
    low_index = va->arrCtrl.low_index;
    num_elmnts = va->arrCtrl.num_elmnts;
    }
  else
    {
    low_index = 0;
    num_elmnts = rt->u.arr.num_elmnts;
    }

/* Let's check to see if the client is selecting a sub-object ... 	*/
  prim_info->prim_offset      += rt->el_size;
  prim_info->prim_offset_base += rt->el_size;
  for (i = 0; i < num_elmnts; ++i)
    {
    va->arrCtrl.curr_index = low_index + i;
    startElWrites (indCtrl, wrCtrl, wrVaCtrl, rt+1, numRt-2, prim_info);
    }
  prim_info->prim_offset      += (rt+numRt-1)->el_size;
  prim_info->prim_offset_base += (rt+numRt-1)->el_size;
  }

/************************************************************************/
/*			 mvlu_wr_prim_done				*/
/************************************************************************/
/* The user calls this function acynchronously when the primitive data	*/
/* has been put in the 'primData' buffer.				*/

ST_VOID mvlu_wr_prim_done (MVLU_WR_VA_CTRL *mvluWrVaCtrl, ST_RET rc)
  {
MVL_IND_PEND *indCtrl;
MVLAS_WRITE_CTRL *wrCtrl;
MVLAS_WR_VA_CTRL *wrVaCtrl;
ST_INT i;

  wrVaCtrl = mvluWrVaCtrl->wrVaCtrl;
  if (rc != SD_SUCCESS)
    wrVaCtrl->resp_tag = WR_RSLT_FAILURE;
    
  ++wrVaCtrl->numPrimDataDone;
  if (wrVaCtrl->numPrimDataDone == wrVaCtrl->numPrimData)
    {
    indCtrl = mvluWrVaCtrl->indCtrl;
    wrCtrl = &indCtrl->u.wr;

  /* If all primitives for all variables are complete, respond now */
    wrVaCtrl = wrCtrl->vaCtrlTbl;
    for (i = 0; i < wrCtrl->numVar; ++i, ++wrVaCtrl)
      {
      if (wrVaCtrl->numPrimDataDone != wrVaCtrl->numPrimData)
        break;
      else
        {				/* Done writing this var.	*/
        /* Do special cleanup for IEC 61850 SBO controls.		*/
        /* If wrVaCtrl->sboCtrl != NULL, this var is SBO Oper or Cancel	*/
        /* (see startElWrites), so do SBO cleanup.			*/
        if (wrVaCtrl->sboCtrl)
          {
          mvlu_sbo_ctrl_free (wrVaCtrl->sboCtrl);
          wrVaCtrl->sboCtrl = NULL;	/* reset this so free not done twice.*/
          }
       
#if !defined(MVL61850_CTL_DISABLE)
        /* If Write failed, and Var is IEC 61850 Oper, Cancel, or SBOw,	*/
        /* must also send InformationReport containing LastApplError.	*/
        if (wrVaCtrl->resp_tag == WR_RSLT_FAILURE && wrVaCtrl->va != NULL)	/* var might not be found*/
          {
          ST_CHAR *lastdollar = strrchr (wrVaCtrl->va->name, '$');	/* find last '$'*/
          /* lastdollar should ALWAYS be valid*/
          /* If var name ends in Oper, etc, call user funct to send LastApplError.*/
          if (strcmp (lastdollar+1, "Oper") == 0 ||
              strcmp (lastdollar+1, "Cancel") == 0 ||
              strcmp (lastdollar+1, "SBOw") == 0)
	    {
            /* Construct & send LastApplError info report.*/
            ST_CHAR *ptr;	/* ptr into CntrlObj string	*/

            /* Fill in "LastApplError" structure.	*/
            /* Construct CntrlObj from var->name. Other members	(Error,	*/
            /* AddCause, Origin, ctlNum) already set by leaf functions.	*/
            strcpy (wrVaCtrl->LastApplError.CntrlObj, wrVaCtrl->va->name);
            ptr = strrchr (wrVaCtrl->LastApplError.CntrlObj, '$');	/* find last '$'*/
            strcpy (ptr+1, "Oper");	/* replace last component name with "Oper"*/
            mvl61850_ctl_lastapplerror_send (indCtrl->event->net_info, &wrVaCtrl->LastApplError);
            }
          }
#endif	/* !defined(MVL61850_CTL_DISABLE)	*/
        }
      }
    if (i == wrCtrl->numVar)
      {
      mvlas_write_resp (indCtrl);
      }
    }
  M_FREE (MSMEM_MVLU_VA_CTRL, mvluWrVaCtrl);
  }


/************************************************************************/
/*			mvluDefAsyncWrIndFun				*/
/************************************************************************/

static ST_VOID mvluDefAsyncWrIndFun (struct mvlu_wr_va_ctrl *mvluWrVaCtrl)
  {
  mvlu_wr_prim_done (mvluWrVaCtrl, SD_SUCCESS);
  }

/************************************************************************/
/************************************************************************/
/*			countPrimEl					*/
/************************************************************************/

static ST_INT countPrimEl (MVL_VAR_ASSOC *va, RUNTIME_TYPE *rt, ST_INT rt_num)
  {
ST_INT i;
ST_INT num_elmnts;
ST_INT numPrimData;
ST_INT subElCount;

  numPrimData = 0;
  for (i = 0; i < rt_num; ++i, ++rt)
    {
    if (ms_is_rt_prim (rt) == SD_TRUE)
      ++numPrimData;
    if (rt->el_tag == RT_ARR_START)
      {
      subElCount = countPrimEl (va, rt+1, rt->u.arr.num_rt_blks);

      if (va->arrCtrl.arrAltAccPres == SD_FALSE)
        num_elmnts = rt->u.arr.num_elmnts;
      else
        num_elmnts = va->arrCtrl.num_elmnts;

      numPrimData += (subElCount * num_elmnts);

      i += (rt->u.arr.num_rt_blks + 1);
      rt += (rt->u.arr.num_rt_blks + 1);
      }
    }
  return (numPrimData);
  }

/************************************************************************/
/*			mvluDefGetVaDataBufFun				*/
/************************************************************************/

static ST_VOID mvluDefGetVaDataBufFun (ST_INT service, 
				       MVL_VAR_ASSOC *va, ST_INT size)
  {
  if (service == MMSOP_READ || service == MMSOP_WRITE || 
      service == MMSOP_INFO_RPT || service == MMSOP_RDWR_USR_HANDLED)
    {
    /* If static data used, va->data points within base_va.	*/
    if (!va->base_va->use_static_data)
      va->data = M_MALLOC (MSMEM_MVLU_VA_DATA, size);
    else
      va->data = (((ST_CHAR *) va->base_va->data) + va->offset_from_base);
    }
  else if (service == MMSOP_MVLU_RPT_VA)
    {
    }
  }

/************************************************************************/
/*			mvluDefFreeVaDataBufFun				*/
/************************************************************************/

static ST_VOID mvluDefFreeVaDataBufFun (ST_INT service, MVL_VAR_ASSOC *va)
  {
  if (service == MMSOP_READ || service == MMSOP_WRITE ||
      service == MMSOP_INFO_RPT || service == MMSOP_RDWR_USR_HANDLED)
    {
		if(!va->base_va)//hejian add on 2010-4-2
		{
    if (!va->base_va->use_static_data)
      M_FREE (MSMEM_MVLU_VA_DATA, va->data);
    }
	}
  else if (service == MMSOP_MVLU_RPT_VA)
    {
    }
  }


/************************************************************************/
/*			mvlu_find_rt_leaf				*/
/************************************************************************/

RUNTIME_TYPE *mvlu_find_rt_leaf (ST_INT type_id, ST_CHAR *leafName)
  {
RUNTIME_TYPE *rt;
ST_INT numRt; 
ST_RET ret;

  ret = mvl_get_runtime (type_id, &rt, &numRt);
  if (ret != SD_SUCCESS)
    {
    MVL_LOG_NERR1 ("Could not get RT type for type id %d", type_id);
    return (NULL);
    }

  ret = mvlu_find_uca_var (&rt, &numRt, leafName);
  if (ret != SD_SUCCESS)
    {
    MVL_LOG_NERR1 ("Could not find leaf '%s'", leafName);
    return (NULL);
    }

  if (numRt != 1)
    {	/* See if this is an array with a single primitive element */
    if (rt->el_tag == RT_ARR_START && numRt == 3) 
      return (rt+1);

    MVL_LOG_NERR1 ("'%s' is a branch, not a leaf", leafName);
    return (NULL);
    }


  return (rt);
  }

/************************************************************************/
/*			mvlu_find_comp_type				*/
/* Arguments:								*/
/*  base_type_id	type ID for top level variable			*/
/*  flatname		flattened component name with top level var	*/
/*			name (Logical Node) stripped off.		*/
/*  sub_rt_type		Ptr to (RUNTIME_TYPE *) to be filled in.	*/
/*  sub_rt_num		Ptr to "count" to be filled in.			*/
/************************************************************************/
ST_RET mvlu_find_comp_type (ST_INT base_type_id, ST_CHAR *flatname,
			RUNTIME_TYPE **sub_rt_type,		/* out	*/
			ST_INT *sub_rt_num)			/* out	*/
  {
MVL_TYPE_CTRL *base_type_ctrl;
ST_RET ret;

  base_type_ctrl = mvl_type_ctrl_find (base_type_id);
  if (base_type_ctrl)
    {
    *sub_rt_type = base_type_ctrl->rt;
    *sub_rt_num = base_type_ctrl->num_rt;
    ret = mvlu_find_uca_var (sub_rt_type, sub_rt_num, flatname);
    }
  else
    ret = SD_FAILURE;

  /* NOTE: don't log error here. Caller may often pass invalid names.	*/
  return (ret);
  }

/************************************************************************/
/*			mvlu_get_leaf_val_int8			*/
/* Get leaf data value for type ST_INT8.				*/ 
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   data	ptr to data written by this function			*/
/* RETURNS:	SD_SUCCESS or SD_FAILURE				*/
/************************************************************************/
ST_RET mvlu_get_leaf_val_int8 (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_INT8 *data)
  {
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_RET ret = SD_FAILURE;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
           flatname,	/* flattened name	*/
	   &comp_rt_type,	/* ptr to val set by function	*/
	   &comp_rt_num)	/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    if (comp_rt_type->el_tag == RT_INTEGER && comp_rt_type->u.p.el_len == 1)
      {	/* must be INT8	*/
      *data = *(ST_INT8 *)((ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet);
      ret = SD_SUCCESS;
      }
    else
      MVL_LOG_ERR1 ("Invalid type for '%s' attribute. Cannot use it.", flatname);
    }
  else
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
                  flatname, base_va->name);
  return (ret);
  }
/************************************************************************/
/*			mvlu_get_leaf_val_int32			*/
/* Get leaf data value for type ST_INT32.				*/ 
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   data	ptr to data written by this function			*/
/* RETURNS:	SD_SUCCESS or SD_FAILURE				*/
/************************************************************************/
ST_RET mvlu_get_leaf_val_int32 (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_INT32 *data)
  {
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_RET ret = SD_FAILURE;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
           flatname,	/* flattened name	*/
	   &comp_rt_type,	/* ptr to val set by function	*/
	   &comp_rt_num)	/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    if (comp_rt_type->el_tag == RT_INTEGER && comp_rt_type->u.p.el_len == 4)
      {	/* must be INT32	*/
      *data = *(ST_INT32 *)((ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet);
      ret = SD_SUCCESS;
      }
    else
      MVL_LOG_ERR1 ("Invalid type for '%s' attribute. Cannot use it.", flatname);
    }
  else
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
                  flatname, base_va->name);
  return (ret);
  }
/************************************************************************/
/*			mvlu_get_leaf_val_int_any			*/
/* Get leaf value for any signed integer. Cast value to ST_INT32.	*/
/************************************************************************/
ST_RET mvlu_get_leaf_val_int_any (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_INT32 *data)
  {  
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_CHAR *raw_data;	/* ptr to data. May be any integer size	*/
ST_INT8 tmp_int8;	/* Used to get val as INT8, then cast to INT32	*/
ST_INT16 tmp_int16;	/* Used to get val as INT16, then cast to INT32	*/
ST_RET retcode = SD_SUCCESS;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
          flatname,		/* flattened name	*/
          &comp_rt_type,	/* ptr to val set by function	*/
          &comp_rt_num)		/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    raw_data = (ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet;
    if (comp_rt_type->el_tag == RT_INTEGER)
      {
      if (comp_rt_type->u.p.el_len == 1)	/* INT8	*/
        {
        tmp_int8 = *(ST_INT8 *) raw_data;
        *data = (ST_INT32) tmp_int8;
        }
      else if (comp_rt_type->u.p.el_len == 2)	/* INT16	*/
        {
        tmp_int16 = *(ST_INT16 *) raw_data;
        *data = (ST_INT32) tmp_int16;
        }
      else if (comp_rt_type->u.p.el_len == 4)	/* INT32	*/
        {
        *data = *(ST_INT32 *) raw_data;
        }
      else
        {  
        MVL_LOG_ERR2 ("Unsupported integer size for '%s' attribute in variable '%s'",
                  flatname, base_va->name);
        retcode = SD_FAILURE;
        }
      }
    else
      {  
      MVL_LOG_ERR2 ("Invalid type for '%s' attribute in variable '%s'. Cannot get value.",
                  flatname, base_va->name);
      retcode = SD_FAILURE;
      }
    }
  else
    {  
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in variable '%s'",
                  flatname, base_va->name);
    retcode = SD_FAILURE;
    }
  return (retcode);
  }
/************************************************************************/
/*			mvlu_get_leaf_val_uint32			*/
/* Get leaf data value for type ST_UINT32.				*/ 
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   data	ptr to data written by this function			*/
/* RETURNS:	SD_SUCCESS or SD_FAILURE				*/
/************************************************************************/
ST_RET mvlu_get_leaf_val_uint32 (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_UINT32 *data)
  {
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_RET ret = SD_FAILURE;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
           flatname,		/* flattened name	*/
	   &comp_rt_type,	/* ptr to val set by function	*/
	   &comp_rt_num)	/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    if (comp_rt_type->el_tag == RT_UNSIGNED && comp_rt_type->u.p.el_len == 4)
      {	/* must be UINT32	*/
      *data = *(ST_UINT32 *)((ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet);
      ret = SD_SUCCESS;
      }
    else
      MVL_LOG_ERR1 ("Invalid type for '%s' attribute. Cannot use it.", flatname);
    }
  else
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
                  flatname, base_va->name);
  return (ret);
  }
/************************************************************************/
/*			mvlu_get_leaf_val_boolean			*/
/* Get leaf data value for type ST_BOOLEAN.				*/ 
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   data	ptr to data written by this function			*/
/* RETURNS:	SD_SUCCESS or SD_FAILURE				*/
/************************************************************************/
ST_RET mvlu_get_leaf_val_boolean (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, ST_BOOLEAN *data)
  {
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_RET ret = SD_FAILURE;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
           flatname,	/* flattened name	*/
	   &comp_rt_type,	/* ptr to val set by function	*/
	   &comp_rt_num)	/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    if (comp_rt_type->el_tag == RT_BOOL)
      {	/* must be BOOLEAN	*/
      *data = *(ST_BOOLEAN *)((ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet);
      ret = SD_SUCCESS;
      }
    else
      MVL_LOG_ERR1 ("Invalid type for '%s' attribute. Cannot use it.", flatname);
    }
  else
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
                  flatname, base_va->name);
  return (ret);
  }
/************************************************************************/
/*			mvlu_get_leaf_val_bvstring			*/
/* Get leaf data value for type MMS_BVSTRING.				*/ 
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   data	ptr to data written by this function			*/
/* RETURNS:	SD_SUCCESS or SD_FAILURE				*/
/************************************************************************/
ST_RET mvlu_get_leaf_val_bvstring (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname,
                                   MMS_BVSTRING *data, ST_INT max_num_bits)
  {
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_RET ret = SD_FAILURE;
ST_INT num_bytes;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
           flatname,	/* flattened name	*/
	   &comp_rt_type,	/* ptr to val set by function	*/
	   &comp_rt_num)	/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    /* NOTE: for Bvstring, el_len is negative.	*/
    if (comp_rt_type->el_tag == RT_BIT_STRING && comp_rt_type->u.p.el_len < 0
        && abs (comp_rt_type->u.p.el_len) <= max_num_bits)
      {
      num_bytes = 2 + (abs (comp_rt_type->u.p.el_len) + 7)/8;
      memcpy (data, (ST_CHAR *)base_va->data + comp_rt_type->mvluTypeInfo.offSet, num_bytes);
      ret = SD_SUCCESS;
      }
    else
      MVL_LOG_ERR1 ("Invalid type for '%s' attribute. Cannot use it.", flatname);
    }
  else
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
                  flatname, base_va->name);
  return (ret);
  }
/************************************************************************/
/*			mvlu_get_leaf_data_ptr				*/
/* Get leaf data pointer (for any type of leaf).			*/
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   rt_type	ptr to ptr to type (function sets "*rt_type")		*/
/* RETURNS:	pointer to leaf data (NULL on error)			*/
/************************************************************************/
ST_VOID *mvlu_get_leaf_data_ptr (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, RUNTIME_TYPE **rt_type)
  {
RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
ST_INT comp_rt_num;		/* num of rt_types in component	*/
ST_VOID *data;

  /* Find the attribute type.	*/
  if (mvlu_find_comp_type (base_va->type_id,
           flatname,	/* flattened name	*/
	   &comp_rt_type,	/* ptr to val set by function	*/
	   &comp_rt_num)	/* ptr to val set by function	*/
      == SD_SUCCESS)
    {
    data = ((ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet);
    *rt_type = comp_rt_type;
    }
  else
    {
    data = NULL;
    MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
                  flatname, base_va->name);
    }
  return (data);
  }

/************************************************************************/
/*			mvlu_get_leaf_data_ptr_mydefine				*/
/* Get leaf data pointer (for any type of leaf).			*/
/* Arguments:								*/
/*   base_va	base variable (i.e. logical node)			*/
/*   flatname	flattened leaf name (e.g. ST$Mod$stVal)			*/
/*   rt_type	ptr to ptr to type (function sets "*rt_type")		*/
/* RETURNS:	pointer to leaf data (NULL on error)			*/
/************************************************************************/
ST_VOID *mvlu_get_leaf_data_ptr_mydefine (MVL_VAR_ASSOC *base_va, ST_CHAR *flatname, 
										  RUNTIME_TYPE **rt_type, ST_INT *rt_num)
{
	RUNTIME_TYPE *comp_rt_type;	/* first rt_type of component	*/
	ST_INT comp_rt_num;		/* num of rt_types in component	*/
	ST_VOID *data;

	/* Find the attribute type.	*/
	if (mvlu_find_comp_type (base_va->type_id,
		flatname,	/* flattened name	*/
		&comp_rt_type,	/* ptr to val set by function	*/
		&comp_rt_num)	/* ptr to val set by function	*/
		== SD_SUCCESS)
	{
		data = ((ST_CHAR *) base_va->data + comp_rt_type->mvluTypeInfo.offSet);
		*rt_type = comp_rt_type;
		*rt_num = comp_rt_num;
	}
	else
	{
		data = NULL;
		MVLU_LOG_FLOW2 ("Cannot find '%s' attribute in this variable '%s'",
			flatname, base_va->name);
	}
	return (data);
}
/************************************************************************/
#endif	/* defined(MVL_UCA)	*/
/************************************************************************/
