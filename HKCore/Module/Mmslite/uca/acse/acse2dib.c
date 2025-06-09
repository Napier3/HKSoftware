/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	2003 - 2003, All Rights Reserved		        */
/*									*/
/* MODULE NAME : acse2dib.c    						*/
/* PRODUCT(S)  : MMS-LITE						*/
/*									*/
/* MODULE DESCRIPTION : Address matching functions.			*/
/*									*/
/*	NOTE: !!! If changes are made to this file the same changes	*/
/*		  have to be made in the marb_dib.c (MMS-EASE).		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/28/05  JRB     03    Del suicacse header.				*/
/* 06/16/03  EJV     02    Renamed m_match.c to acse2dib.c		*/
/* 06/02/03  MDE     01    Created					*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"

#include "acse2.h"


/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/
/************************************************************************/

#ifdef DEBUG_SISCO
static ST_CHAR *thisFileName = __FILE__;
#endif


/************************************************************************/
/* Internal Functions */

static ST_VOID _dib_match_ap_title (DIB_MATCH_CTRL *matchCtrl, 
		      ST_INT *matchLevel,
		      ST_BOOLEAN ind_pres, MMS_OBJ_ID *ind_apTitle, 
		      ST_BOOLEAN dib_pres, MMS_OBJ_ID *dib_apTitle);
static ST_VOID _dib_match_ae_int (DIB_MATCH_CTRL *matchCtrl,
		      ST_INT *matchLevel,
		      ST_BOOLEAN ind_pres, ST_INT32 ind_val, 
		      ST_BOOLEAN dib_pres, ST_INT32 dib_val, 
		      ST_CHAR *itemText);
static ST_VOID _dib_match_mem (ST_INT *matchLevel,
		      ST_INT ind_sel_len, ST_UCHAR *ind_sel, 
		      ST_INT dib_sel_len, ST_UCHAR *dib_sel, 
		      ST_CHAR *sel_text);
static ST_VOID _dib_match_ae_present_flag (DIB_MATCH_CTRL *matchCtrl,
				       ST_INT *matchLevelIo,
				       ST_CHAR *aeElText,
				       ST_BOOLEAN dibPres, 
				       ST_BOOLEAN remotePres,
				       ST_BOOLEAN *doCompareOut);

/************************************************************************/
/*			ml_match_remote_ar				*/
/************************************************************************/

ST_RET dib_match_remote_ar (DIB_MATCH_CTRL *matchCtrl, 
			    AARQ_APDU *aarq, DIB_ENTRY **dib_entry_out)
  {
ST_INT i;
DIB_ENTRY *de;
DIB_ENTRY *closeDe;
ST_INT remMatch;

  ACSELOG_DIB0 ("Matching Remote AR");
  closeDe = NULL;
  for (i = 0; i < num_rem_dib_entries; ++i)
    {
    de = &rem_dib_table[i];
    ACSELOG_DIB1C ("      Remote AR '%s'", de->name);
    remMatch = dib_cmp_remote_addr (matchCtrl, aarq, de);
    if (remMatch == DIB_MATCH_EXACT)
      {
      *dib_entry_out = de;
      ACSELOG_DIB1C ("Exact Match: '%s'", de->name);
      return (SD_SUCCESS);
      }
    if (remMatch == DIB_MATCH_CLOSE && closeDe == NULL)
      closeDe = de;
    }

  if (closeDe != NULL)
    {
    *dib_entry_out = closeDe;
    ACSELOG_DIB1C ("Close Match: '%s'", closeDe->name);
    return (SD_SUCCESS);
    }
  
  return (SD_FAILURE);
  }

/************************************************************************/
/*			dib_match_local_ar				*/
/************************************************************************/

ST_RET dib_match_local_ar (DIB_MATCH_CTRL *matchCtrl, 
			   AARQ_APDU *aarq, DIB_ENTRY **dib_entry_out)
  {
ST_INT i;
DIB_ENTRY *de;
DIB_ENTRY *closeDe;
ST_INT locMatch;

  ACSELOG_DIB0 ("Matching Local AR");
  closeDe = NULL;
  for (i = 0; i < num_loc_dib_entries; ++i)
    {
    de = &loc_dib_table[i];
    ACSELOG_DIB1C ("      Local AR '%s'", de->name);
    locMatch = dib_cmp_local_addr (matchCtrl,aarq, de);
    if (locMatch == DIB_MATCH_EXACT)
      {
      ACSELOG_DIB1C ("Exact Match: '%s'", de->name);
      *dib_entry_out = de;
      return (SD_SUCCESS);
      }

    if (locMatch == DIB_MATCH_CLOSE && closeDe == NULL)
      closeDe = de;
    }

  if (closeDe != NULL)
    {
    ACSELOG_DIB1C ("Close Match: '%s'", de->name);
    *dib_entry_out = closeDe;
    return (SD_SUCCESS);
    }
  
  return (SD_FAILURE);
  }


/************************************************************************/
/************************************************************************/
/*                 dib_cmp_local_addr                                 	*/
/************************************************************************/

ST_INT dib_cmp_local_addr (DIB_MATCH_CTRL *matchCtrl, 
			   AARQ_APDU *aarq, DIB_ENTRY *dib_entry)
  {
ST_INT matchLevel;

/* The best we can do ... */
  matchLevel = DIB_MATCH_EXACT;

/* Compare local network address with dib entry */
#if 0
  if (matchCtrl->match_net_addr)
    {
    if (aarq->transport == TCP)
      {
      _dib_match_mem (&matchLevel, 
      		   strlen (aarq->ip_addr), aarq->ip_addr, 
  		   strlen (dib_entry->ip_addr), dib_entry->ip_addr, 
  		   "Local IP Address");
      if (matchLevel == DIB_MATCH_NOT)
        return (DIB_MATCH_NOT);
      }
    else if (aarq->transport == TP4)
      {
      _dib_match_mem (&matchLevel,
      		   aarq->net_addr_len,aarq->net_addr, 
  		   dib_entry->net_addr_len, dib_entry->net_addr, 
  		   "Local Network Address");
      if (matchLevel == DIB_MATCH_NOT)
        return (DIB_MATCH_NOT);
      }
    else
      {
      ACSELOG_ERR1 ("Transport type problem: %d", aarq->transport);
      return (DIB_MATCH_NOT);
      }
    }
#endif


/* Compare selectors with dib entry */
  /* PSEL */
  if (matchCtrl->match_psel)
    {
    _dib_match_mem (&matchLevel, aarq->called_paddr.psel_len, aarq->called_paddr.psel, 
    		 dib_entry->pres_addr.psel_len, dib_entry->pres_addr.psel, 
      		 "PSEL");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* SSEL */
  if (matchCtrl->match_ssel)
    {
    _dib_match_mem (&matchLevel, aarq->called_paddr.ssel_len, aarq->called_paddr.ssel, 
		 dib_entry->pres_addr.ssel_len, dib_entry->pres_addr.ssel,
		 "SSEL");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* TSEL */
  if (matchCtrl->match_tsel)
    {
    _dib_match_mem (&matchLevel, aarq->called_paddr.tsel_len, aarq->called_paddr.tsel, 
		 dib_entry->pres_addr.tsel_len, dib_entry->pres_addr.tsel,
		 "TSEL");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

/* Now compare AE Titles */
  /* AP Title */
  if (matchCtrl->match_ap_title)
    {
    _dib_match_ap_title (matchCtrl,&matchLevel,
		    aarq->called_ae_title.AP_title_pres, &aarq->called_ae_title.AP_title, 
		    dib_entry->AP_title_pres, &dib_entry->AP_title);
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* AE Qualifier */
  if (matchCtrl->match_ae_qualifier)
    {
    _dib_match_ae_int (matchCtrl, &matchLevel,
		    aarq->called_ae_title.AE_qual_pres, aarq->called_ae_title.AE_qual, 
		    dib_entry->AE_qual_pres, dib_entry->AE_qual, 
		    "AE Qualifier");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* AP Invoke ID */
  if (matchCtrl->match_ap_invoke)
    {
    _dib_match_ae_int (matchCtrl, &matchLevel,
		    aarq->called_ae_title.AP_inv_id_pres, aarq->called_ae_title.AP_inv_id, 
		    dib_entry->AP_inv_id_pres, dib_entry->AP_invoke_id, 
		    "AP invoke ID");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* AE Invoke ID */  
  if (matchCtrl->match_ae_invoke)
    {
    _dib_match_ae_int (matchCtrl, &matchLevel,
		    aarq->called_ae_title.AE_inv_id_pres, aarq->called_ae_title.AE_inv_id, 
		    dib_entry->AE_inv_id_pres, dib_entry->AE_invoke_id, 
		    "AE invoke ID");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }
  return (matchLevel);	/* exact */
  }


/************************************************************************/
/*			dib_cmp_remote_addr				*/
/************************************************************************/

ST_INT dib_cmp_remote_addr (DIB_MATCH_CTRL *matchCtrl, 
			    AARQ_APDU *aarq, DIB_ENTRY *dib_entry)
  {
ST_INT matchLevel;

/* The best we can do ... */
  matchLevel = DIB_MATCH_EXACT;

/* Compare partner network address with dib entry */
#if 0
  if (matchCtrl->match_net_addr)
    {
    if (aarq->transport == TCP)
      {
      _dib_match_mem (&matchLevel, 
      		   strlen (aarq->part_ip_addr), aarq->part_ip_addr, 
  		   strlen (dib_entry->ip_addr), dib_entry->ip_addr, 
  		   "Remote IP Address");
      if (matchLevel == DIB_MATCH_NOT)
        return (DIB_MATCH_NOT);
      }
    else if (aarq->transport == TP4)
      {
      _dib_match_mem (&matchLevel,
      		   aarq->part_net_addr_len,aarq->part_net_addr, 
  		   dib_entry->net_addr_len, dib_entry->net_addr, 
  		   "Remote Network Address");
      if (matchLevel == DIB_MATCH_NOT)
        return (DIB_MATCH_NOT);
      }
    else
      {
      ACSELOG_ERR1 ("Transport type problem: %d", aarq->transport);
      return (DIB_MATCH_NOT);
      }
    }
#endif

/* Compare selectors with dib entry */
  /* PSEL */
  if (matchCtrl->match_psel)
    {
    _dib_match_mem (&matchLevel, aarq->calling_paddr.psel_len, aarq->calling_paddr.psel, 
		 dib_entry->pres_addr.psel_len, dib_entry->pres_addr.psel, 
		 "PSEL");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* SSEL */
  if (matchCtrl->match_ssel)
    {
    _dib_match_mem (&matchLevel, aarq->calling_paddr.ssel_len, aarq->calling_paddr.ssel, 
		 dib_entry->pres_addr.ssel_len, dib_entry->pres_addr.ssel,
		 "SSEL");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* TSEL */
  if (matchCtrl->match_tsel)
    {
    _dib_match_mem (&matchLevel, aarq->calling_paddr.tsel_len, aarq->calling_paddr.tsel, 
		 dib_entry->pres_addr.tsel_len, dib_entry->pres_addr.tsel,
		 "TSEL");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    } 
      
/* Now compare AE Titles */
/* AP Title */
  if (matchCtrl->match_ap_title)
    {
    _dib_match_ap_title (matchCtrl, &matchLevel,
		    aarq->calling_ae_title.AP_title_pres, &aarq->calling_ae_title.AP_title, 
		    dib_entry->AP_title_pres, &dib_entry->AP_title);
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* AE Qualifier */
  if (matchCtrl->match_ae_qualifier)
    {
    _dib_match_ae_int (matchCtrl, &matchLevel,
		    aarq->calling_ae_title.AE_qual_pres, aarq->calling_ae_title.AE_qual, 
		    dib_entry->AE_qual_pres, dib_entry->AE_qual, 
		    "AE Qualifier");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* AP Invoke ID */
  if (matchCtrl->match_ap_invoke)
    {
    _dib_match_ae_int (matchCtrl, &matchLevel,
		    aarq->calling_ae_title.AP_inv_id_pres, aarq->calling_ae_title.AP_inv_id, 
		    dib_entry->AP_inv_id_pres, dib_entry->AP_invoke_id, 
		    "AP invoke ID");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  /* AE Invoke ID */  
  if (matchCtrl->match_ae_invoke)
    {
    _dib_match_ae_int (matchCtrl, &matchLevel,
		    aarq->calling_ae_title.AE_inv_id_pres, aarq->calling_ae_title.AE_inv_id, 
		    dib_entry->AE_inv_id_pres, dib_entry->AE_invoke_id, 
		    "AE invoke ID");
    if (matchLevel == DIB_MATCH_NOT)
      return (DIB_MATCH_NOT);
    }

  return (matchLevel);
  }

/************************************************************************/
/*			_dib_match_ap_title				*/
/************************************************************************/

/* Set match level to DIB_MATCH_NOT, or leave alone	*/

static ST_VOID _dib_match_ap_title (DIB_MATCH_CTRL *matchCtrl, 
		      ST_INT *matchLevel,
		      ST_BOOLEAN ind_pres, MMS_OBJ_ID *ind_apTitle, 
		      ST_BOOLEAN dib_pres, MMS_OBJ_ID *dib_apTitle)
  {
ST_CHAR *itemText = "AP Title";
ST_BOOLEAN doCompare;

  _dib_match_ae_present_flag (matchCtrl, matchLevel, itemText, dib_pres, 
  				ind_pres, &doCompare);
/* See if we need to compare	*/
  if (doCompare)
    {
    if (asn1_objidcmp (ind_apTitle, dib_apTitle))
      {
      ACSELOG_DIB1C ("        %s mismatch", itemText);
      *matchLevel = DIB_MATCH_NOT;
      return;
      }
    }
  }

/************************************************************************/
/*			_dib_match_ae_int					*/
/************************************************************************/

/* Set match level to DIB_MATCH_NOT, or leave alone	*/

static ST_VOID _dib_match_ae_int (DIB_MATCH_CTRL *matchCtrl, ST_INT *matchLevel,
		      ST_BOOLEAN ind_pres, ST_INT32 ind_val, 
		      ST_BOOLEAN dib_pres, ST_INT32 dib_val, 
		      ST_CHAR *itemText)
  {
ST_BOOLEAN doCompare;

  _dib_match_ae_present_flag (matchCtrl, matchLevel, itemText, dib_pres, 
  				ind_pres, &doCompare);

/* OK, we matched, see if we need to compare	*/
  if (doCompare)
    {
    if (ind_val != dib_val)
      {
      ACSELOG_DIB1C ("        %s mismatch", itemText);
      *matchLevel = DIB_MATCH_NOT;
      return;
      }
    }
  }

/************************************************************************/
/*			_dib_match_mem					*/
/************************************************************************/

/* Set match level to DIB_MATCH_NOT, or leave alone	*/

static ST_VOID _dib_match_mem (ST_INT *matchLevel,
		      ST_INT ind_sel_len, ST_UCHAR *ind_sel, 
		      ST_INT dib_sel_len, ST_UCHAR *dib_sel, 
		      ST_CHAR *sel_text)
  {
/* See if the selectors match */
  if (ind_sel_len == dib_sel_len &&
      !memcmp (ind_sel, dib_sel, ind_sel_len))
    {
    return;
    }

  ACSELOG_DIB1C ("        %s mismatch", sel_text);
  *matchLevel = DIB_MATCH_NOT;
  return;
  }

/************************************************************************/
/*			_dib_match_ae_present_flag				*/
/************************************************************************/

/* Set match level to DIB_MATCH_CLOSE or DIB_MATCH_NOT, or leave alone	*/

static ST_VOID _dib_match_ae_present_flag (DIB_MATCH_CTRL *matchCtrl, 
				       ST_INT *matchLevelIo,
				       ST_CHAR *aeElText,
				       ST_BOOLEAN dibPres, 
				       ST_BOOLEAN remotePres,
				       ST_BOOLEAN *doCompareOut)
  {

/* If the remote sent the parameter and it is in the DIB, SUCCESS	*/
  if (dibPres == remotePres)
    {
    *doCompareOut = dibPres;  /* If it is present, then compare it	*/
    return;
    }
  *doCompareOut = SD_FALSE;	/* Can't compare */

/* OK, this is more complicated. We need to find out what the mismatch	*/
/* is and what the user wants to do about it.				*/

  if (!remotePres)
    {
    if (matchCtrl->match_allow_missing_ae_elements)
      {
      ACSELOG_DIB1C ("        Remote did not send: %s, ignoring", aeElText);
      if (*matchLevelIo == DIB_MATCH_EXACT)
        *matchLevelIo = DIB_MATCH_CLOSE;
      }
    else
      {
      ACSELOG_DIB1C ("        Remote did not send required: %s", aeElText);
      *matchLevelIo = DIB_MATCH_NOT;
      }
    }

  if (remotePres)
    {
    if (matchCtrl->match_allow_extra_ae_elements)
      {
      ACSELOG_DIB1C ("        Remote sent unexpected: %s, ignoring", aeElText);
      if (*matchLevelIo == DIB_MATCH_EXACT)
        *matchLevelIo = DIB_MATCH_CLOSE;
      }
    else
      {
      ACSELOG_DIB1C ("        Remote sent unexpected: %s", aeElText);
      *matchLevelIo = DIB_MATCH_NOT;
      }
    }
  }



