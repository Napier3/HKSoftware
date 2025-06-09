/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2004-2005 All Rights Reserved					*/
/*									*/
/* MODULE NAME : usermap.c						*/
/* PRODUCT(S)  : MMS-EASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Functions to map from MMS "leafs" to user data.			*/
/*									*/
/* NOTE: code within "#ifdef IEC_61850_SERVER_OPC_CLIENT" customized	*/
/*       for the "IEC-61850 Server to OPC Client interface" application.*/
/*									*/
/* NOTE: compile with "DATAMAP_USER_ENABLE" defined to cause extra user	*/
/*       functions to be called.					*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*			datamap_cfg_read				*/
/*			datamap_cfg_destroy				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 10/29/07  JRB    21     strncat_safe obsolete, use strncat_maxstrlen.*/
/* 08/06/07  JRB    20     Allow only comma or tab as delimiters.	*/
/*			   Check for empty tokens.			*/
/* 07/20/07  JRB    19     Generate opcInitialValue if missing in input.*/
/* 07/12/07  CRM    18     opcItemName parameter MUST be present	*/
/*			   (if not known, must enter "").		*/
/* 07/10/07  CRM    17     Added opcInitialValue to input/output.	*/
/*			   Column 7 (type) now required in input.	*/
/* 06/19/07  JRB    16     Ignore illegal mappings in input.		*/
/* 04/30/07  JRB    15     Fix to work with RUNTIME_TYPE change.	*/
/* 03/29/07  CRM    14     Added quotes to opcmapout.cfg dummy entries. */
/* 03/05/07  JRB    13     Allow longer lines in input.			*/
/*			   Don't map Beh$stVal to data, it is computed.	*/
/*			   Chg opcItemName to ptr, alloc before using.	*/
/* 09/09/05  JRB    12     Don't assert (just log) if any var is not struct.*/
/* 07/22/05  JRB    11     Recognize RCB leafs by looking for $RP$ or	*/
/*			   $BR$ (looking for RP$urcb, BR$brcb didn't work).*/
/* 07/13/05  JRB    10     If DATAMAP_USER_ENABLE defined, call user fcts*/
/*			   datamap_user_leaf, datamap_user_oper.	*/
/* 07/13/05  JRB    09     datamap_cfg_read: Del (SCL_INFO *) arg	*/
/*			    (allows mapping vars NOT configured by SCL);*/
/*			    del (DATA_MAP_HEAD *) arg & use local var.	*/
/*			   Add datamap_cfg_destroy funct.		*/
/*			   Alloc and copy DATA_MAP structs so unneeded	*/
/*			    structs can be freed in datamap_cfg_read.	*/
/* 03/30/05  JRB    08     Chg ERR log to FLOW log if leaf not mapped.	*/
/* 03/15/05  JRB    07     Replace strtok with get_next_string to handle*/
/*			   extra delimiters and quoted strings.		*/
/*			   Add quotes around strings in output cfg file.*/
/*			   Add "type" column in output cfg file.	*/
/* 02/15/05  JRB    06     Use new generated scl_ld->domName, not	*/
/*			   scl_ld->inst as domain name.			*/
/* 01/19/05  JRB    05     Move most IEC_61850_SERVER_OPC_CLIENT code	*/
/*			    to new module, call datamap_leaf_opc_client.*/
/*			   For IEC_61850_SER.., allow missing "ItemName"*/
/*			   Move TRACK_INFO to usermap.h.		*/
/*			   Chg rt_type_str_start & data_offset_str_start*/
/*			    in TRACK_INFO to arrays to save multiple	*/
/*			    nesting levels.				*/
/*			   Use mvlu_trim_branch_name from mvl_uca.c	*/
/*			   Fix data_offset calc, do all in datamap_loop.*/
/* 08/05/04  JRB    04     Use new user header file.			*/
/* 07/23/04  JRB    03     Fixed logs. Shortened static function names.	*/
/* 07/21/04  JRB    02     Add out_filename arg to datamap_cfg_read.	*/
/*			   Add #if (IEC_61850_SERVER_OPC_CLIENT)	*/
/* 06/08/04  JRB    01     Initial Revision.				*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "scl.h"	/* for SCL_INFO, SCL_LD, etc.	*/
#include "usermap.h"	/* for DATA_MAP, etc.	*/
#include "sx_log.h"
#include "mvl_defs.h"
#include "mvl_uca.h"
#include "str_util.h"	/* for strn..._safe	protos	*/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

#define LINE_BUF_LEN	1024	/* max len of line read from file.	*/

#if 0
/************************************************************************/
/* DEBUG: if special user mapping is required, DATAMAP_USER_ENABLED	*/
/* must be defined and the user must write the functions		*/
/* "datamap_user_leaf" and "datamap_user_oper" to do user mapping.	*/
/* These functions may be placed here or in any other module.		*/
/************************************************************************/
#define DATAMAP_USER_ENABLE
/* Example of "datamap_user_leaf" function (does nothing).	*/
ST_VOID datamap_user_leaf (DATA_MAP *map_entry)
  {
  }
/* Example of "datamap_user_oper" function (does nothing).	*/
ST_VOID datamap_user_oper (ST_CHAR *dom_name, ST_CHAR *oper_name)
  {
  }
#endif

/* CRITICAL: the "primdata_num" element of the TRACK_INFO struct
 * is used in this module as the index into the array of (DATA_MAP *).
 * The same value must also be passed to the leaf functions so they can
 * find the right (DATA_MAP *).
 * NOTE: dataPtr passed to the leaf function should ALWAYS 
 *       match the dataPtr in the DATA_MAP struct.
 */

/************************************************************************/
/* Need these prototypes because of recursion.				*/
/************************************************************************/
static ST_RET datamap_loop (
	DATA_MAP_HEAD *map_head_cfg,
	ST_CHAR *dom_name,	/* Name of domain (Logical Device)	*/
				/* containing this variable (Logical Node)*/
	MVL_VAR_ASSOC *var,	/* Variable (Logical Node) info		*/
	RUNTIME_TYPE *rt_first,	
	ST_INT rt_num,
	RUNTIME_TYPE *rt_type_last,	/* to make sure don't go past end of RUNTIME_TYPE arr*/
	TRACK_INFO *track_info,
	ST_CHAR *branch_name,
	ST_BOOLEAN array_flag,	/* SD_TRUE if this type is in array	*/
	FILE *fp_out_map);
static ST_VOID datamap_loop_count_prim (
	RUNTIME_TYPE *rt_first,	
	ST_INT rt_num,
	TRACK_INFO *track_info);

/************************************************************************/
/*			any_cfg_count					*/
/* Count the number of "useful" lines in a CFG file.			*/
/* NOTE: Ignore empty lines or lines beginning with '#'.		*/
/* RETURN: number of lines (-1 on error)				*/
/************************************************************************/
ST_INT any_cfg_count (ST_CHAR *in_filename)
  {
FILE *in_fp;
ST_CHAR in_buf[LINE_BUF_LEN];	/* buffer for one line read from file	*/
ST_CHAR token_buf[LINE_BUF_LEN];	/* copy of "in_buf". Modified by get_next_string.*/
ST_CHAR *curptr;		/* ptr to current position in token_buf	*/
char seps[] = ",\t\n";
ST_CHAR *ldevice;		/* first token on line	*/
ST_INT entry_num;		/* index to cur entry in array	*/

  entry_num = 0;
  in_fp = fopen (in_filename, "r");
  if (in_fp == NULL)
    SXLOG_ERR1 ("Error opening input file '%s'", in_filename);
  else
    {
    /* Read one line at a time from the input file	*/
    while (fgets (in_buf, sizeof(in_buf) - 1, in_fp) != NULL)
      {
      /* If string is too close to max len, we probably did not read	*/
      /* complete line. DO NOT allow that.				*/
      if (strlen (in_buf) > (sizeof (in_buf) - 3))
        {
        /* If this happens, increase value of LINE_BUF_LEN.		*/
        SXLOG_ERR2 ("Line exceeds maximum length '%d' in '%s'. Cannot parse.",
                    LINE_BUF_LEN, in_filename);
        entry_num = -1;	/* ERROR. Cannot parse this file.	*/
        break;
        }
      /* Make a copy of input buffer to be used with "get_next_string", which will
       * modify the copied buffer (token_buf). Keep input buffer (in_buf)
       * intact.
       * NOTE: use same function (get_next_string) here as in datamap_cfg_rd2
       *       (i.e. on 2nd parse) so, for any input, it will always return
       *       the same value here as it does in datamap_cfg_rd2.
       */
      strcpy (token_buf, in_buf);
      curptr = token_buf;	/* init "curptr"	*/
      ldevice = get_next_string(&curptr, seps);	/* "curptr" adjusted by this funct	*/

      /* If NULL, this is empty line. If first char is '#', this is comment line.*/
      if (ldevice == NULL || ldevice[0] == '#')
        continue;		/* Ignore empty lines & comment lines	*/
      if (ldevice [0] == '\0')
        continue;	/* First token is empty. This is probably empty line. Ignore it.*/

      /* If we got this far, assume line contains good stuff. Make room in array.*/
      entry_num++;
      }	/* end "while (fgets..)"	*/
    fclose (in_fp);
    }
  return (entry_num);
  }

/************************************************************************/
/*			datamap_cfg_rd2					*/
/* Read each line in the "Mapping Cfg" file. Copy data from one line	*/
/* to one entry in the (DATA_MAP *) array referenced by 'map_head_cfg'.	*/
/* NOTE: Ignore empty lines or lines beginning with '#'.		*/
/************************************************************************/
static ST_RET datamap_cfg_rd2 (ST_CHAR *datamap_cfg_filename, DATA_MAP_HEAD *map_head_cfg)
  {
FILE *in_fp;
ST_CHAR in_buf[LINE_BUF_LEN];	/* buffer for one line read from file	*/
ST_CHAR token_buf[LINE_BUF_LEN];	/* copy of "in_buf". Modified by get_next_string.*/
ST_CHAR *curptr;		/* ptr to current position in token_buf	*/
char seps[] = ",\t\n";
DATA_MAP *map_entry;
ST_INT line_num;		/* number of lines in file	*/
ST_UINT entry_num;		/* number of valid entries in file	*/
ST_RET retcode = SD_SUCCESS;
ST_CHAR *ldevice;		/* first token on line	*/
ST_CHAR *leaf;			/* 2nd token	*/
ST_CHAR *token3;		/* 3rd token	*/
ST_CHAR *token4;		/* 4th token	*/
ST_CHAR *token5;		/* 5th token	*/
ST_CHAR *token6;		/* 6th token	*/
ST_CHAR *token7;		/* 7th token	*/


  in_fp = fopen (datamap_cfg_filename, "r");
  if (in_fp == NULL)
    {
    SXLOG_ERR1 ("Error opening input file '%s'", datamap_cfg_filename);
    return (SD_FAILURE);
    }

  /* Read one line at a time from the input file	*/
  /* NOTE: length of every line checked in "any_cfg_count", so no need to recheck here.*/
  entry_num = 0;	
  line_num = 0;
  while (fgets (in_buf, sizeof(in_buf) - 1, in_fp) != NULL)
    {
    line_num++;
    map_entry = map_head_cfg->map_arr[entry_num];

    /* Make a copy of input buffer to be used by "get_next_string", which will
     * modify the copied buffer (token_buf). Keep input buffer (in_buf)
     * intact.
     * NOTE: could use "strtok" here, but it doesn't nicely handle extra
     *       delimiters or quoted strings. 
     */
    strcpy (token_buf, in_buf);
    curptr = token_buf;	/* init "curptr"	*/
    ldevice = get_next_string(&curptr, seps);	/* "curptr" adjusted by this funct	*/

    /* If NULL, this is empty line. If first char is '#', this is comment line.*/
    if (ldevice == NULL || ldevice[0] == '#')
      continue;		/* Ignore empty lines & comment lines	*/
    if (ldevice [0] == '\0')
      {
      /* First token is empty. This is probably empty line.	*/
      /* Ignore this line, but log error if more tokens found. 	*/
      if ((leaf = get_next_string (&curptr, seps)) != NULL)
        SXLOG_ERR3 ("Input ignored because first token is empty at line %d in '%s'. Second token='%s'",
                    line_num, datamap_cfg_filename, leaf);
      continue;
      }

    /* First token must be "ldevice". Save it.	*/
    strncpy_safe (map_entry->ldevice, ldevice, MAX_IDENT_LEN);

    /* NOTE: if one get_next_string returns NULL, subsequent calls should also.*/
    leaf   = get_next_string (&curptr, seps);
    token3 = get_next_string (&curptr, seps);
    token4 = get_next_string (&curptr, seps);
    token5 = get_next_string (&curptr, seps);
    token6 = get_next_string (&curptr, seps);
    token7 = get_next_string (&curptr, seps);

#if defined (IEC_61850_SERVER_OPC_CLIENT)		/* customized	*/
    if (token5)
      {	/* if token5 valid, all previous tokens must be valid too*/
      strncpy_safe (map_entry->leaf,          leaf,   MAX_IDENT_LEN);
      strncpy_safe (map_entry->opcServerName, token3, MAX_IDENT_LEN);
      map_entry->opcItemName = chk_malloc (strlen (token4)+1);
      strcpy (map_entry->opcItemName, token4);
      strncpy_safe (map_entry->opcGroupName,  token5, MAX_IDENT_LEN);

      if (token7)
        {	/* token7 is present, so token6 is opcInitialValue */
        map_entry->opcInitialValue = chk_malloc (strlen (token6)+1);
        strcpy (map_entry->opcInitialValue, token6);
        }
      else
        {	/* token7 NOT present, so assume opcInitialValue missing*/
        /* Old file might have 5 or 6 parameters.	*/
        SXLOG_ERR2 ("Parameter missing at line %d in '%s'. Expecting 6 parameters and a type.", line_num, datamap_cfg_filename);\
        SXLOG_CERR1 ("%s", in_buf);
        SXLOG_CERR0 ("Assuming 'Initial Value' missing and generating correct entry in output file.");
        map_entry->opcInitialValue = chk_calloc (1, 1);  /* create an empty string */
        }
      }
    else
      {
      SXLOG_ERR2 ("Invalid input at line %d in '%s'. Must contain 6 parameters and a type.", line_num, datamap_cfg_filename);
      SXLOG_CERR1 ("%s", in_buf);
      retcode = SD_FAILURE;
      }
#else	/* !IEC_61850_SERVER_OPC_CLIENT	*/
    /* NOTE: token4 & token5 not used here, but may be used later.	*/
    if (leaf && token3)
      {
      strncpy_safe (map_entry->leaf,          leaf,   MAX_IDENT_LEN);
      strncpy_safe (map_entry->usr_data_info, token3, MAX_IDENT_LEN);
      }
    else
      {
      SXLOG_ERR2 ("Invalid input at line %d in '%s'. Must contain 3 parameters.", line_num, datamap_cfg_filename);
      SXLOG_CERR1 ("%s", in_buf);
      retcode = SD_FAILURE;
      }
#endif	/* !IEC_61850_SERVER_OPC_CLIENT	*/

    /* If ANYTHING failed so far, stop looping.	*/
    if (retcode)
      break;	/* get out of loop	*/
    entry_num++;
    }	/* end main "while" loop	*/

  /* If no errors, num entries must match.	*/
  if (retcode == SD_SUCCESS)
    {
    assert (entry_num == map_head_cfg->map_count);
    }

  fclose (in_fp);
  return (retcode);
  }
/************************************************************************/
/*			datamap_find_leaf				*/
/* Skip any leaf with comp_name=="q" or "t". They MUST NOT be mapped.	*/
/* If they are mapped, the mapping is ignored.				*/
/************************************************************************/
DATA_MAP *datamap_find_leaf (
	DATA_MAP_HEAD *map_head_cfg,
	ST_CHAR *dom_name,	/* Name of domain (Logical Device)	*/
				/* containing this variable (Logical Node)*/
	ST_CHAR *leaf_name,	/* "Flattened" leaf name		*/
	ST_CHAR *comp_name)	/* Name of this component		*/
  {
ST_UINT j;
DATA_MAP *map_entry = NULL;

  assert (comp_name != NULL);

#if defined (IEC_61850_SERVER_OPC_CLIENT)		/* customized	*/
  /* Don't bother searching if comp_name=="q" or "t". These must never be mapped.*/
  if (strcmp (comp_name, "q") == 0  || strcmp (comp_name, "t") == 0)
    return (NULL);
#endif

  for (j = 0; j<map_head_cfg->map_count; j++)
    {
    if (strcmp (map_head_cfg->map_arr [j]->ldevice, dom_name) == 0
        && strcmp (map_head_cfg->map_arr [j]->leaf, leaf_name) == 0)
      {
      map_entry = map_head_cfg->map_arr [j];
      break;	/* found it, so stop looping	*/
      }
    }
  return (map_entry);
  }
/************************************************************************/
/*			datamap_leaf					*/
/* Sets the "dataPtr", "dataType"					*/
/* parameters in JUST ONE entry of the "map_head_cfg->map_arr".		*/ 
/* RETURNS:	SD_SUCCESS or SD_FAILURE				*/
/************************************************************************/
static ST_RET datamap_leaf (
	DATA_MAP_HEAD *map_head_cfg,
	MVL_VAR_ASSOC *var,	/* Variable (Logical Node) info		*/
	ST_CHAR *dom_name,	/* Name of domain (Logical Device)	*/
				/* containing this variable (Logical Node)*/
	ST_CHAR *branch_name,
	ST_CHAR *comp_name,
	RUNTIME_TYPE *rt_type,	/* type of this "leaf"			*/
	TRACK_INFO *track_info,
	FILE *fp_out_map)
  {
DATA_MAP_HEAD *map_head_sorted;	/* head of array of (DATA_MAP *) for this var.*/
DATA_MAP *map_entry;	/* map entry for this leaf	*/
/* Allow extra char in leaf_name so strncat can go one byte past limit.*/
/* If it does, return error.						*/
ST_CHAR leaf_name[MAX_FLAT_LEN+2];	/* build flattened leaf name here*/
ST_CHAR tdl_buf[80];			/* TDL for type of this leaf	*/
ST_INT  tdl_len;			/* len of TDL			*/
RUNTIME_TYPE tmp_rt_type;

  assert (comp_name);	/* assume "comp_name" is NEVER NULL	*/
  if (strlen (comp_name))
    {	/* not empty, so append to branch name	*/
    strcpy (leaf_name, branch_name);
    /* Allow extra char in these strncat_maxstrlen calls. If used, return error.*/
    strncat_maxstrlen (leaf_name, "$",       MAX_FLAT_LEN + 1);
    strncat_maxstrlen (leaf_name, comp_name, MAX_FLAT_LEN + 1);
    if (strlen (leaf_name) > MAX_FLAT_LEN)
      {
      SXLOG_ERR1 ("flattened name '%s' too long", leaf_name);
      return (SD_FAILURE);
      }
    }
  else
    {   /* comp_name is empty, so don't append to branch_name	*/
    strcpy (leaf_name, branch_name);
    }

  /* Get TDL for this type for writing to output file.
   * Don't want component name in the TDL, so just copy rt_type to temp struct
   * and set comp_name_ptr = NULL.
   * Always simple type so 2nd arg to "ms_runtime_to_tdl" is always 1.
   */ 
  memcpy (&tmp_rt_type, rt_type, sizeof (RUNTIME_TYPE));
  tmp_rt_type.comp_name_ptr = NULL;
  tdl_len = ms_runtime_to_tdl (&tmp_rt_type, 1, tdl_buf, sizeof(tdl_buf)-1);
  if (tdl_len == 0)	/* make sure tdl_buf set if error occurred	*/
    sprintf (tdl_buf, "UNKNOWN_TYPE(tag=%d, len=%d)",rt_type->el_tag, rt_type->u.p.el_len);

  map_head_sorted = (DATA_MAP_HEAD *) var->user_info;

  /* Use dom_name, leaf_name to find the map_entry.		*/
  map_entry = datamap_find_leaf (map_head_cfg, dom_name, leaf_name, comp_name);
  if (map_entry != NULL)
    {				/* this leaf is mapped	*/
#if defined (IEC_61850_SERVER_OPC_CLIENT)		/* customized	*/
    /* Perform extra mapping for "IEC 61850 Server to OPC Client interface"*/
    /* application. Ignore return code (most leafs fail).		*/
    datamap_leaf_opc_client (map_entry, var, comp_name, track_info);
#endif	/* IEC_61850_SERVER_OPC_CLIENT	*/

    /* Set pointer to data storage for this leaf.	*/
    map_entry->dataPtr = (ST_CHAR *) var->data + track_info->data_offset;
    map_entry->dataType = rt_type;	/* Save type	*/

    /* NOTE: map_entry is completely filled in now.
     * Save map_entry to appropriate array entry.
     * Use primdata_num as index into array.
     * NOTE: array initialized to all NULL, so only need to save if map_entry!=NULL.
     * CRITICAL: the value of "primdata_num" used here as index to array
     * must be passed to "leaf" function. The "leaf" function needs it
     * to find this map_entry.
     * CRITICAL: The DATA_MAP struct is allocated and copied so that the DATA_MAP_HEAD
     *   struct filled in when file is read (i.e. map_head_cfg) can be destroyed when
     *   config is complete (see datamap_cleanup), but the sorted DATA_MAP_HEAD
     *   struct created here (i.e. map_head_sorted) is still valid and usable.
     */
    map_head_sorted->map_arr [track_info->primdata_num] = chk_malloc (sizeof (DATA_MAP));
    memcpy (map_head_sorted->map_arr [track_info->primdata_num], map_entry, sizeof (DATA_MAP));

#if defined(DATAMAP_USER_ENABLE)
    /* Call extra user function to perform special mapping or initialization.*/
    datamap_user_leaf (map_entry);
#endif
    
    /* Copy "Mapping Cfg" entry to output file.	*/
    assert (strcmp (map_entry->ldevice, dom_name) == 0);
    assert (strcmp (map_entry->leaf, leaf_name) == 0);

    if (fp_out_map)
      {
#if defined (IEC_61850_SERVER_OPC_CLIENT)		/* customized	*/
      /* Ignore if comp_name=="q" or "t" or leaf_name contains "$Beh$stVal", "$RP$" or "$BR$".
       * These should NEVER be mapped to OPC Items.
       * Otherwise add to output cfg file.
       */
      if (strcmp (comp_name, "q") != 0			/* not "q"	*/
          &&  strcmp (comp_name, "t") != 0		/* not "t"	*/
          &&  strstr (leaf_name, "$Beh$stVal") == NULL	/* does not contain "$Beh$stVal"*/
          &&  strstr (leaf_name, "$RP$") == NULL	/* does not contain "$RP$"*/
          &&  strstr (leaf_name, "$BR$") == NULL)	/* does not contain "$BR$"*/
        {
        fprintf (fp_out_map, "%s\t%s\t\"%s\"\t\"%s\"\t\"%s\"\t\"%s\"\ttype=%s\n", 
               map_entry->ldevice,
               map_entry->leaf,
               map_entry->opcServerName,
               map_entry->opcItemName,
               map_entry->opcGroupName,
               map_entry->opcInitialValue,
               tdl_buf);
        }
      else
        SXLOG_ERR1 ("Leaf name '%s' may not be mapped. Ignored.", leaf_name);
#else	/* !IEC_61850_SERVER_OPC_CLIENT	*/
      /* Ignore if leaf_name contains "$Beh$stVal", "$RP$" or "$BR$".
       * These should NEVER be mapped.
       * Otherwise add to output cfg file.
       */
      if (strstr (leaf_name, "$Beh$stVal") == NULL	/* does not contain "$Beh$stVal"*/
          &&  strstr (leaf_name, "$RP$") == NULL	/* does not contain "$RP$"*/
          &&  strstr (leaf_name, "$BR$") == NULL)	/* does not contain "$BR$"*/
        {
        fprintf (fp_out_map, "%s\t%s\t\"%s\"\ttype=%s\n", 
               map_entry->ldevice,
               map_entry->leaf,
               map_entry->usr_data_info,
               tdl_buf);
        }
      else
        SXLOG_ERR1 ("Leaf name '%s' may not be mapped. Ignored.", leaf_name);
#endif	/* !IEC_61850_SERVER_OPC_CLIENT	*/
      }
    }	/* end "if (map_entry != NULL)"	*/
  else
    {	/* map_entry == NULL (i.e. not mapped).	*/
#if defined (IEC_61850_SERVER_OPC_CLIENT)		/* customized	*/
    /* OK if comp_name=="q" or "t" or leaf_name contains "$Beh$stVal", "$RP$" or "$BR$".
     * These should NEVER be mapped to OPC Items.
     * Otherwise log & add to output cfg file.
     */
    if (strcmp (comp_name, "q") != 0			/* not "q"	*/
        &&  strcmp (comp_name, "t") != 0		/* not "t"	*/
        &&  strstr (leaf_name, "$Beh$stVal") == NULL	/* does not contain "$Beh$stVal"*/
        &&  strstr (leaf_name, "$RP$") == NULL	/* does not contain "$RP$"*/
        &&  strstr (leaf_name, "$BR$") == NULL)	/* does not contain "$BR$"*/
      {
      SXLOG_FLOW2 ("Leaf name '%s' in domain '%s' not found in OPCMAP configuration file",
                 leaf_name, dom_name);
      /* Write dummy "opcmap.cfg" entry to output file "opcmapout.cfg".	*/
      if (fp_out_map)
        fprintf (fp_out_map, "%s\t%s\t\"dummy_opcserver\"\t\"dummy_opcitem\"\t\"dummy_ioclass\"\t\"\"\ttype=%s\n",
                 dom_name, leaf_name, tdl_buf);
      }
#else	/* !IEC_61850_SERVER_OPC_CLIENT	*/
    /* OK if leaf_name contains "$Beh$stVal", "$RP$" or "$BR$".
     * These should NEVER be mapped.
     * Otherwise log & add to output cfg file.
     */
    if (strstr (leaf_name, "$Beh$stVal") == NULL	/* does not contain "$Beh$stVal"*/
        &&  strstr (leaf_name, "$RP$") == NULL	/* does not contain "$RP$"*/
        &&  strstr (leaf_name, "$BR$") == NULL)	/* does not contain "$BR$"*/
      {
      SXLOG_FLOW2 ("Leaf name '%s' in domain '%s' not found in data mapping configuration file",
                 leaf_name, dom_name);
      /* Write dummy "Mapping Cfg" entry to output file.	*/
      if (fp_out_map)
        fprintf (fp_out_map, "%s\t%s\t%s\ttype=%s\n", 
		dom_name, leaf_name, "dummy_data_mapping_string",
                tdl_buf);
      }
#endif	/* !IEC_61850_SERVER_OPC_CLIENT	*/
    }

  /* CRITICAL: update primdata_num (ONLY here).	*/
  track_info->primdata_num++;
  return (SD_SUCCESS);
  }
/************************************************************************/
/*  				datamap_array				*/
/* WARNING: datamap_array & datamap_loop may call each other		*/
/*	recursively.							*/
/* Add text for array, like "...$array[0]$etc".				*/
/* NOTE: because array index is included in mapping text, there is no	*/
/* need for "var->arrCtrl".						*/
/************************************************************************/
static ST_RET datamap_array (
	DATA_MAP_HEAD *map_head_cfg,
	ST_CHAR *dom_name,	/* Name of domain (Logical Device)	*/
				/* containing this variable (Logical Node)*/
	MVL_VAR_ASSOC *var,	/* Variable (Logical Node) info		*/
	RUNTIME_TYPE *rt_type,
	RUNTIME_TYPE *rt_type_last,	/* to make sure don't go past end of RUNTIME_TYPE arr*/
	TRACK_INFO *track_info,
	ST_CHAR *branch_name,	/* array name without index		*/
	FILE *fp_out_map)
  {
ST_INT j;
ST_INT rt_num;
ST_INT num_arr_elements;
ST_CHAR tmp_branch_name[MAX_FLAT_LEN+1];	/* copy branch_name here & add index*/
ST_RET retcode = SD_FAILURE;
ST_CHAR *comp_name;

  comp_name = ms_comp_name_find (rt_type);
  /* ifdef USE_RT_TYPE_2, ms_comp_name_find macro NEVER returns NULL.	*/
  assert (comp_name != NULL);

  rt_num = rt_type->u.arr.num_rt_blks;	/* num RUNTIME_TYPE to define one element of array*/

  num_arr_elements = rt_type->u.arr.num_elmnts;	/* num of elements in array		*/

  assert (rt_type->el_tag == RT_ARR_START);

  /* Make sure room for 10 digit integer value in sprintf of tmp_branch_name.*/
  if (strlen(branch_name) > (MAX_FLAT_LEN-12))
    {
    SXLOG_ERR1 ("flattened name too long to add more: %s", branch_name);
    /* retcode already set = SD_FAILURE	*/
    }
  else
    {
    for (j = 0; j < num_arr_elements; ++j)
      {
      /* Create temporary branch_name for this array element.	*/
      sprintf (tmp_branch_name, "%s[%d]", branch_name, j);
      assert (strlen(tmp_branch_name) <= MAX_FLAT_LEN);	/* should never fail with chk above*/
      /* Recursive call to "datamap_loop".	*/
      retcode = datamap_loop (map_head_cfg, dom_name, var, rt_type+1, rt_num,
                  rt_type_last, track_info, tmp_branch_name, SD_TRUE, fp_out_map);
      if (retcode)
        break;	/* error, stop looping	*/
      }
    }

  /* NOTE: don't do anything for RT_ARR_END here. Handled in datamap_loop.*/

  return (retcode);
  }
/************************************************************************/
/*			datamap_loop					*/
/* WARNING: datamap_array & datamap_loop may call each other		*/
/*	recursively.							*/
/* RETURNS:	SD_SUCCESS or error code				*/
/* NOTE: usually (track_info->data_offset == rt_type->mvluTypeInfo.offSet)*/
/*       but not when inside an array.					*/
/************************************************************************/
static ST_RET datamap_loop (
	DATA_MAP_HEAD *map_head_cfg,
	ST_CHAR *dom_name,	/* Name of domain (Logical Device)	*/
				/* containing this variable (Logical Node)*/
	MVL_VAR_ASSOC *var,	/* Variable (Logical Node) info		*/
	RUNTIME_TYPE *rt_first,	
	ST_INT rt_num,
	RUNTIME_TYPE *rt_type_last,	/* to make sure don't go past end of RUNTIME_TYPE arr*/
	TRACK_INFO *track_info,
	ST_CHAR *branch_name,
	ST_BOOLEAN array_flag,	/* SD_TRUE if this type is in array	*/
	FILE *fp_out_map)
  {
ST_RTINT num_rt_blks;
ST_CHAR *comp_name;
RUNTIME_TYPE *rt_type;		/* ptr to current array entry.	*/
ST_INT rt_index;		/* index into array of RUNTIME_TYPE	*/
ST_RET retcode = SD_SUCCESS;

  /* Loop through array of RUNTIME_TYPE structs.			*/
  /* NOTE: On RT_ARR_START, rt_index & rt_type get extra incrementing.	*/
  for (rt_index = 0, rt_type = rt_first; rt_index < rt_num; ++rt_index, ++rt_type)
    {
    assert (rt_type < rt_type_last);

    if (!array_flag)
      {	/* must have been called from "datamap_ln" (not datamap_array)	*/
      /* Make sure data_offset computed correctly	*/
      if (track_info->data_offset != rt_type->mvluTypeInfo.offSet)
        {
        SXLOG_ERR2 ("data_offset=%d does not match expected (%d)",
                    track_info->data_offset, rt_type->mvluTypeInfo.offSet);
        retcode = SD_FAILURE;	/* give up	*/
        break;
        }
      }

    comp_name = ms_comp_name_find (rt_type);
    /* ifdef USE_RT_TYPE_2, ms_comp_name_find macro NEVER returns NULL.	*/
    assert (comp_name != NULL);
    
    switch (rt_type->el_tag)
      {
      case RT_STR_START:
        if (track_info->str_nest >= MAX_NEST_LEVEL)
          {
          SXLOG_ERR1 ("Structure nesting exceeds max %d. Can't continue processing.", MAX_NEST_LEVEL);
          retcode = SD_FAILURE;	/* give up	*/
          break;
          }
        track_info->rt_type_str_start[track_info->str_nest] = rt_type;	/* save this ptr (lowest level struct found)*/
        track_info->data_offset_str_start[track_info->str_nest] = track_info->data_offset;
        track_info->str_nest++;

        if (strlen (comp_name))
          {
          if (array_flag && rt_index == 0)
            {	/* this struct is first elem of array. DO NOT add comp_name*/
            }
          else
            {
            strncat_maxstrlen (branch_name, "$", MAX_FLAT_LEN);
            strncat_maxstrlen (branch_name, comp_name, MAX_FLAT_LEN);
            }
          }
#if defined(DATAMAP_USER_ENABLE)
        /* If this struct is "Oper", call extra user function to perform special mapping or initialization.*/
        if (strcmp (comp_name, "Oper") == 0) 
          datamap_user_oper (dom_name, branch_name);	/* user function	*/
#endif
        break;
      case RT_STR_END:
        track_info->str_nest--;		/* decrement nest level	*/
        track_info->rt_type_str_start[track_info->str_nest] = NULL;	/* clear ptr*/
        track_info->data_offset_str_start[track_info->str_nest] = 0;	/* clear offset*/

        assert (strlen(comp_name)==0);	/* Shound NEVER have component name*/
        mvlu_trim_branch_name (branch_name);
        break;
      case RT_ARR_END:
        assert (0);		/* should never get here. Code below for*/
				/* RT_ARR_START skips past this RUNTIME_TYPE.	*/
        break;
      case RT_ARR_START:
        assert (strlen(comp_name));	/* MUST have component name*/
        strncat_maxstrlen (branch_name, "$", MAX_FLAT_LEN);
        strncat_maxstrlen (branch_name, comp_name, MAX_FLAT_LEN);
        /* Recursive call to "datamap_array".	*/
        datamap_array (map_head_cfg, dom_name, var, rt_type,
                         rt_type_last, track_info, branch_name, fp_out_map);
        mvlu_trim_branch_name (branch_name);	/* remove comp_name just added	*/

        track_info->data_offset += rt_type->el_size;	/* SPECIAL CASE: do this before incrementing rt_type*/

        /* Increment to point at RT_ARR_END	*/
        num_rt_blks = rt_type->u.arr.num_rt_blks;
        rt_index += (num_rt_blks + 1);
        rt_type += (num_rt_blks + 1);
        assert (rt_type->el_tag==RT_ARR_END);
        break;
      default:			/* Primitive	*/
        if (rt_num == 1)
          {   /* this prim is only element in the RT table.	*/
          /* don't want datamap_leaf to add comp_name, so overwrite	*/
          /* it with empty string.					*/
          comp_name = "";
          }
        retcode = datamap_leaf (
                  map_head_cfg,
                  var,
                  dom_name,		/* Name of domain (Logical Device)	*/
					/* containing this variable (Logical Node)*/
                  branch_name,
                  comp_name,
                  rt_type,		/* type of this "leaf"			*/
                  track_info,
                  fp_out_map);
        /* NOTE: if this fails, retcode chk below will break out of "for" loop.*/
        break;
      }	/* end "switch"	*/
    if (retcode)
      break;		/* error so stop looping	*/

    /* Update data_offset for any rt_type. Notice the SPECIAL CASE for	*/
    /* RT_ARR_START where data_offset also updated before incrementing rt_type.*/
    track_info->data_offset += rt_type->el_size;
    }	/* end "for" loop	*/

  if (!array_flag)
    {	/* must have been called from "datamap_ln" (not datamap_array)	*/
    /* rt_type should be pointing at last struct in RUNTIME_TYPE array.	*/
    assert (rt_type == rt_type_last);
    }
  return (retcode);
  }
/************************************************************************/
/*  				datamap_array_count_prim		*/
/* WARNING: datamap_array_count_prim & datamap_loop_count_prim may	*/
/*	call each other	recursively.					*/
/* Add text for array, like "...$array[0]$etc".				*/
/* RETURNS:	ST_VOID		Cannot fail				*/
/************************************************************************/
static ST_VOID datamap_array_count_prim (
	RUNTIME_TYPE *rt_type,
	TRACK_INFO *track_info)
  {
ST_INT j;
ST_INT rt_num;		/* num RUNTIME_TYPE to define one element of array*/
ST_INT num_arr_elements;	/* num elements in array*/

  rt_num = rt_type->u.arr.num_rt_blks;
  num_arr_elements = rt_type->u.arr.num_elmnts;	/* num elements in array*/

  for (j = 0; j < num_arr_elements; ++j)
    {
    /* Recursive call to "datamap_loop_count_prim".	*/
    datamap_loop_count_prim (rt_type+1, rt_num, track_info);
    }
  return;
  }
/************************************************************************/
/*			datamap_loop_count_prim				*/
/* WARNING: datamap_array_count_prim & datamap_loop_count_prim may	*/
/*	call each other	recursively.					*/
/* RETURNS:	ST_VOID		Cannot fail				*/
/************************************************************************/
static ST_VOID datamap_loop_count_prim (
	RUNTIME_TYPE *rt_first,	
	ST_INT rt_num,
	TRACK_INFO *track_info)
  {
ST_RTINT num_rt_blks;
RUNTIME_TYPE *rt_type;		/* ptr to current array entry.	*/
ST_INT rt_index;		/* index into array of RUNTIME_TYPE	*/

  for (rt_index = 0, rt_type = rt_first; rt_index < rt_num; ++rt_index, ++rt_type)
    {
    switch (rt_type->el_tag)
      {
      case RT_STR_START:
      case RT_STR_END:
      case RT_ARR_END:
        break;			/* Do nothing	*/
      case RT_ARR_START:
        /* Recursive call to "datamap_array_count_prim".	*/
        datamap_array_count_prim (rt_type, track_info);
        num_rt_blks = rt_type->u.arr.num_rt_blks;
        rt_index += (num_rt_blks + 1);
        rt_type += (num_rt_blks + 1);
        break;
      default:	/* Must be primitive	*/
        track_info->primdata_num++;	/* CRITICAL: increment ONLY here.*/
        break;
      }	/* end "switch"	*/
    }	/* end "for" loop	*/

  return;
  }
/************************************************************************/
/*			datamap_ln					*/
/* Sets the "dataPtr" and "dataType"					*/
/* parameters in EVERY entry of the "map_head_cfg->map_arr".		*/
/* This function allocates an array of (DATA_MAP *), one for each	*/
/* primitive data element. It would be easier to alloc one (DATA_MAP *)	*/
/* for each element of RUNTIME_CTRL, but that would not work if the type*/
/* contains arrays. This approach allows a unique (DATA_MAP *) for each	*/
/* element of an array.							*/ 
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET datamap_ln (
	DATA_MAP_HEAD *map_head_cfg,
	ST_CHAR *dom_name,	/* Name of domain (Logical Device)	*/
				/* containing this variable (Logical Node)*/
	MVL_VAR_ASSOC *var,	/* Variable (Logical Node) info		*/
	FILE *fp_out_map)
  {
ST_CHAR branch_name[MAX_FLAT_LEN+1];	/* allow extra space for array indices	*/
RUNTIME_CTRL *rt_ctrl;
MVL_TYPE_CTRL *type_ctrl;
ST_RET retcode;
TRACK_INFO track_info;
DATA_MAP_HEAD *map_head_sorted;
RUNTIME_TYPE *rt_type_last;	/* to make sure don't go past end of RUNTIME_TYPE arr*/

  if ((strstr (var->name,"$")))
    {
    assert (0);	/* should always be top level var. No '$' in name	*/
    }

  /* "var" is top-level var. Should never be alternate access.*/
  assert (var->arrCtrl.arrAltAccPres == SD_FALSE);

  /* Find runtime type (RUNTIME_CTRL) for this Variable (Logical Node).	*/
  if ((type_ctrl = mvl_type_ctrl_find (var->type_id)) != NULL)
    rt_ctrl = type_ctrl->rt_ctrl;
  else
    {
    SXLOG_ERR2 ("Invalid type_id=%d for Variable '%s'", var->type_id, var->name);
    return (SD_FAILURE);
    }

  /* Assuming Logical Node is always a struct.	*/
  if (rt_ctrl->rt_first->el_tag != RT_STR_START)
    {
    SXLOG_ERR1 ("Variable '%s' is not a structure. Cannot be mapped using datamap_cfg_read", var->name);
    return (SD_FAILURE);
    }

  memset (&track_info, 0, sizeof (TRACK_INFO));	/* CRITICAL: initialize track_info*/
  strcpy (branch_name,var->name);

  rt_type_last = rt_ctrl->rt_first + rt_ctrl->rt_num;

  /* Process var once to find number of primitive data elements using "track_info->primdata_num".*/
  datamap_loop_count_prim (rt_ctrl->rt_first, rt_ctrl->rt_num, &track_info);

  /* Allocate DATA_MAP_HEAD struct plus array of (DATA_MAP *).	*/
  /* Save allocated ptr in "var->user_info".			*/
  map_head_sorted = chk_calloc (1, sizeof (DATA_MAP_HEAD) + track_info.primdata_num * sizeof (DATA_MAP *));
  map_head_sorted->map_arr = (DATA_MAP **)(map_head_sorted + 1);
  map_head_sorted->map_count = track_info.primdata_num;

  assert (var->user_info == NULL);	/* CRITICAL: user_info must not be used for something else*/
  /* If assert fails, then all code in this module may need to avoid	*/
  /* using "user_info". Perhaps a new element could be added to "var".	*/
  var->user_info = map_head_sorted;

  /* Process var again to complete mapping.	*/
  memset (&track_info, 0, sizeof (TRACK_INFO));	/* CRITICAL: re-init track_info*/
  retcode =  datamap_loop (map_head_cfg, dom_name, var,
                              rt_ctrl->rt_first, rt_ctrl->rt_num, rt_type_last,
                              &track_info, branch_name, SD_FALSE, fp_out_map);
  if (retcode == SD_SUCCESS)
    {
    assert (track_info.str_nest == 0);	/* finished processing top level struct*/
    /* CRITICAL: must get same count as datamap_loop_count_prim (saved in map_count)*/
    assert (track_info.primdata_num == map_head_sorted->map_count);
    /* Make sure data_offset was computed right.	*/
    /* Log before assert so easier to debug if assertion ever fails.	*/
    if (track_info.data_offset != rt_ctrl->rt_first->offset_to_last)
      SXLOG_ERR2 ("track_info.data_offset = %d  rt_ctrl->rt_first->offset_to_last = %d",
            track_info.data_offset, rt_ctrl->rt_first->offset_to_last);
    assert (track_info.data_offset == rt_ctrl->rt_first->offset_to_last);
    SXLOG_FLOW2 ("Number of primitive data elements in LN '%s' = %d", var->name, track_info.primdata_num);
    }
  return (retcode);
  }
/************************************************************************/
/*			datamap_cleanup					*/
/* Free up unnecessary mapping info.					*/
/* NOTE: this function does not free the DATA_MAP_HEAD struct saved in	*/
/*   the "user_info" member of MVL_VAR_ASSOC (i.e. "sorted" entries).	*/
/*   See "datamap_cfg_var_cleanup" for MVL_VAR_ASSOC cleanup.		*/
/************************************************************************/
static ST_VOID datamap_cleanup (DATA_MAP_HEAD *map_head_cfg)
  {
ST_UINT j;

  /* Free up DATA_MAP ptrs (in reverse order).	*/
  if (map_head_cfg->map_count)	/* this "if" helps if already called	*/
    {
    for (j = 0; j < map_head_cfg->map_count; j++)
      chk_free (map_head_cfg->map_arr [j]);
    chk_free (map_head_cfg->map_arr);
    map_head_cfg->map_count = 0;	/* CRITICAL: so code doesn't try to access freed entries*/
    }
  }
/************************************************************************/
/*			datamap_cfg_read				*/
/* Reads data mapping configuration file & maps the data for all	*/
/* variables in the global VMD object "mvl_vmd".			*/
/* RETURNS:	SD_SUCCESS or error code				*/
/************************************************************************/
ST_RET datamap_cfg_read (
	ST_CHAR *in_filename,		/* input cfg file name	*/
	ST_CHAR *out_filename)		/* output cfg file name	*/
  {
ST_RET retcode = SD_SUCCESS;	/* assume SUCCESS	*/
ST_UINT j;
FILE *fp_out_map;
/* Use local "map_head_cfg" struct to store all info read from the cfg file.*/
DATA_MAP_HEAD map_head_cfg = {0};	/* start with clean struct	*/
MVL_DOM_CTRL *dom;
MVL_VAR_ASSOC *var;
ST_INT didx, vidx;	/* indices to domain & variable arrays	*/
ST_INT line_count;

  /* Read "Mapping Cfg" file to count number of entries.			*/
  line_count = any_cfg_count (in_filename);
  if (line_count < 0)
    return (SD_FAILURE);	/* ERROR already logged. Give up now.	*/

  /* If "any_cfg_count" successful, save returned count.	*/
  map_head_cfg.map_count = line_count;

  /* if map_count > 0, allocate array of pointers to DATA_MAP structs,	*/
  /* and re-read file							*/
  if (map_head_cfg.map_count > 0)
    {
    /* Alloc array of ptrs to DATA_MAP structures, then alloc each struct.*/
    map_head_cfg.map_arr = chk_calloc (map_head_cfg.map_count, sizeof (DATA_MAP *));
    for (j = 0; j < map_head_cfg.map_count; j++)
      map_head_cfg.map_arr [j] = chk_calloc (1, sizeof (DATA_MAP));

    /* Read "Mapping Cfg" again and fill in "DATA_MAP_HEAD *map_head_cfg".*/
    if (datamap_cfg_rd2 (in_filename, &map_head_cfg) != SD_SUCCESS)
      {		/* ERROR already logged	*/
      datamap_cleanup (&map_head_cfg);	/* frees DATA_MAP ptrs just allocated*/
      return (SD_FAILURE);	/* Give up now.	*/
      }
    }

  fp_out_map = fopen (out_filename, "w");
  if (fp_out_map == NULL)
    SXLOG_ERR1 ("WARNING: could not open output file '%s'", out_filename);

  /* Loop through all "Logical Devices" (domains).	*/
  for (didx = 0; didx < mvl_vmd.num_dom; didx++)
    {
    dom = mvl_vmd.dom_tbl [didx];
    /* Loop through all "Logical Nodes" (variables).	*/
    for (vidx = 0; vidx < dom->num_var_assoc; vidx++)
      {
      var = dom->var_assoc_tbl[vidx];
      retcode = datamap_ln (&map_head_cfg, dom->name, var, fp_out_map);
      if (retcode)
        break;		/* stop on first error	*/
      }
    if (retcode)
      break;		/* stop on first error	*/
    }
  if (fp_out_map)
    fclose (fp_out_map);

  /* Free up unnecessary buffers. All necessary information has already	*/
  /* been copied to appropriate objects.				*/
  datamap_cleanup (&map_head_cfg);
  return (retcode);
  }

/************************************************************************/
/*			datamap_cfg_var_cleanup				*/
/* Clean up data mapping info in this var.				*/
/************************************************************************/

static ST_VOID datamap_cfg_var_cleanup (MVL_VAR_ASSOC *var)
  {
DATA_MAP_HEAD *map_head_sorted;
ST_UINT j;

  /* var->user_info points to DATA_MAP_HEAD struct	*/
  map_head_sorted = var->user_info;
  if (map_head_sorted)
    {
    for (j = 0; j < map_head_sorted->map_count; j++)
      {	/* map_arr has many NULL entries for non-primitive elements*/
      if (map_head_sorted->map_arr [j] != NULL)
        chk_free (map_head_sorted->map_arr [j]);
      }
    chk_free (map_head_sorted);
    var->user_info = NULL;
    }
  }

/************************************************************************/
/*			datamap_cfg_destroy				*/
/* Unmap all data mapped by datamap_cfg_read and free associated buffers.*/
/* CRITITAL: must be called BEFORE variables removed, or it will be	*/
/*   impossible to remove the mapping.					*/
/************************************************************************/
ST_VOID datamap_cfg_destroy ()
  {
ST_INT didx, vidx;	/* indices to domain & variable arrays	*/
MVL_DOM_CTRL *dom;
MVL_VAR_ASSOC *var;

  for (didx = 0; didx < mvl_vmd.num_dom; didx++)
    {
    dom = mvl_vmd.dom_tbl [didx];
    for (vidx = 0; vidx < dom->num_var_assoc; vidx++)
      {
      var = dom->var_assoc_tbl[vidx];
      /* Clean up data mapping info in this var.	*/
      datamap_cfg_var_cleanup (var);
      }
    }
  }
