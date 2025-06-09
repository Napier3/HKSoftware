/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	2002-2005, All Rights Reserved					*/
/*									*/
/* MODULE NAME : iec_rx.c					    	*/
/* PRODUCT(S)  : MMSEASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*	  Module contains sample code for  receiving IEC GOOSE		*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	NONE								*/						
/*									*/
/* NOTE: The GSE_IEC_CTRL structure (created by gse_iec_control_create)	*/
/*  was originally intended to be used only for sending GOOSE (not	*/
/*  receiving). However, the structure contains data that is convenient	*/
/*  to be used also when receiving GOOSE, so it is used in several	*/
/*  functions in this module.						*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments		  	*/
/* --------  ---  ------   -------------------------------------------	*/
/* 08/09/06  JRB     13    Add clnp_snet_free call to fix memory leak.	*/
/*			   Fix StNum, SqNum log msg.			*/
/*			   Fix "DataEntry" log msg.			*/
/*			   Check return from set_multicast_filters.	*/
/* 07/27/05  JRB     12    Add GSE_IEC_CTRL NOTE in module header.	*/
/* 07/25/05  JRB     11    log_iec_goose_msg: del unused local vars.	*/
/* 02/08/05  JRB     10    Chg all Subscriber functions to use new	*/
/*			    IEC_GOOSE_RX_USER_INFO instead of		*/
/*			    IEC_GOOSE_SEND_USER_INFO, MAC_TO_GOOSE.	*/
/*			   Add iecGooseSubscribe2.			*/
/*			   Fix "chk_for_goose_msg" to work with new	*/
/*			    clnp_snet_read, etype_hdr_decode & fix ret val.*/
/*			   add_rxd_goose/delete_rxd..: move here & add	*/
/*			    args to init all needed params		*/
/*			   Del globals mac_to_goose_lookup_table &	*/
/*			    number_of_sub_macs.				*/
/*			   Don't init retrans_timeout (leave it =0) so	*/
/*			    timer won't start until after first GOOSE rcvd.*/
/*			   Reset timeToLive when GOOSE received, not in	*/
/*			    iecGooseDecode (decode may be done much later).*/
/*			   Del add_gsse_goose_multicast_filter.		*/
/*			   Del add_multicast_filter, remove_multicast_filter*/
/*			   Semaphores not safe, redo completely.	*/
/*			   iecGooseDecode, check_sub_mac_list: overhaul.*/
/*			   When decode done, call gse_iec_decode_done	*/
/*			    (CRITICAL for freeing memory).		*/
/* 09/01/04  JRB     09    Del unused extern.				*/
/* 05/19/04  JRB     08    Use gs_mutex.. only if USE_FRAMEWORK.. defined*/ 
/* 11/07/03  JRB     07    Fix logging of GOOSE data by calling m_log_data.*/
/*			   If (hdr==NULL), don't try to log hdr info.	*/
/*			   Simplify "out-of-sequence" chk.		*/
/* 06/20/03  JRB     06    Use SLOGCALWAYS*.				*/
/* 04/17/03  JRB     05    Cleanup unneeded code/comments.		*/
/* 01/10/03  JRB     04    Del all refs to dataRef, elementId struct	*/
/*			   members & related code.			*/
/*			   Del unneeded args from iecGooseSubscribe.	*/
/*			   Del unneeded args from gse_iec_data_init.	*/
/*			   Make function & flag names more consistent.	*/
/*			   Fix use of decode_buf in iecGooseLastRxDecode*/
/* 12/10/02  ASK     03    Ethertype additions, misc cleanup.		*/
/* 02/20/01  JRB     02    Fix format.					*/
/* 02/14/02  HSF     01    Created					*/
/************************************************************************/
#include "iec_demo.h"
#include "glbsem.h"
#include "sx_defs.h"
#include "ethertyp.h"
#include "mloguser.h"
#include "clnp_sne.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__; 
#endif

#define MAX_WAIT_FOR_TRANS 120000L

static ST_VOID log_iec_goose_msg (ST_UCHAR *loc_mac, ST_UCHAR *rem_mac, ST_INT pdu_len, ST_CHAR *pdu, GSE_IEC_HDR *hdr, ETYPE_INFO *etype);

/**********************************************************/
/*		add_rxd_goose()						*/
/**********************************************************/

static IEC_GOOSE_RX_USER_INFO *add_rxd_goose(GSE_IEC_CTRL *gptr,
	ST_UCHAR *dst_mac,
	ST_INT decode_mode,
	ST_VOID (*usr_fun)(IEC_GOOSE_RX_USER_INFO *info,
		GSE_IEC_CTRL *gptr,
		ST_VOID *usr,
		ST_UINT16 reason))	/* callback function	*/
  {
  IEC_GOOSE_RX_USER_INFO *user_info= NULL;

  user_info = chk_calloc (1, sizeof (IEC_GOOSE_RX_USER_INFO));
  user_info->gptr = gptr;
  user_info->num_rxd = 0;
  memcpy (user_info->dst_mac,dst_mac,MAC_ADDR_SIZE);
  user_info->decode_mode = decode_mode;
  user_info->usr_fun = usr_fun;	/*set the callback function	*/
  /* user_info->retrans_timeout=0 from calloc. OK.		*/
  list_add_last (&sub_ctrl.sub_list, user_info);

  return(user_info);
  }


/**********************************************************/
/*		delete_rxd_goose()					*/
/**********************************************************/
static ST_RET delete_rxd_goose (IEC_GOOSE_RX_USER_INFO *user_info)
  {
  ST_RET ret = SD_SUCCESS;	/* for now, always success	*/
	  
  /* Remove it from list & free it.	*/
  list_unlink (&sub_ctrl.sub_list, user_info);
  chk_free (user_info);
  return (ret);
  }

/****************************************************/
/*				set_multicast_filters				*/
/*  this sets a list of multicast addresses			*/
/*  this function must be modified to include		*/
/*  UCA GOOSE subscriptions and ES/IS addresses		*/
/*  if there is a combined stack					*/
/****************************************************/
ST_RET set_multicast_filters(ST_VOID)
{
ST_RET ret;
ST_INT j=0;
ST_UCHAR mac_list[MAX_RXD_GOOSE][MAC_ADDR_SIZE];
ST_UCHAR ETHE_ALL_ES [ETHE_MAC_LEN] = {0x09,0x00,0x2B,0x00,0x00,0x04};
ST_UCHAR ETHE_ALL_IS [ETHE_MAC_LEN] = {0x09,0x00,0x2B,0x00,0x00,0x05};
IEC_GOOSE_RX_USER_INFO *goosehandle;

  /* always add ES/IS	*/
  memcpy(mac_list[j++],ETHE_ALL_ES,MAC_ADDR_SIZE);
  memcpy(mac_list[j++],ETHE_ALL_IS,MAC_ADDR_SIZE);

#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_get(&sub_ctrl.sub_mutex);
#endif
  /* DEBUG: This loop may need changes to avoid duplicates	*/
  /* (i.e. 2 subscribers using the same MAC).			*/
  for (goosehandle = sub_ctrl.sub_list;
       goosehandle != NULL;
       goosehandle = (IEC_GOOSE_RX_USER_INFO *) list_get_next (sub_ctrl.sub_list, goosehandle))
    {
    if (j < MAX_RXD_GOOSE)	/* only copy if there's room in mac_list*/
      memcpy(mac_list[j],goosehandle->dst_mac,MAC_ADDR_SIZE);
    j++;
    }
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_free(&sub_ctrl.sub_mutex);
#endif

  if(j <= MAX_RXD_GOOSE)
    ret = gse_set_multicast_filter((ST_UCHAR *)mac_list,j);
  else
    ret = SD_FAILURE;
  return(ret);
}


/**********************************************************/
/*		chk_iec_goose_timeout()					*/
/* Check for retrans timeout on each subscriber.			*/
/**********************************************************/
ST_VOID chk_iec_goose_timeout( ST_INT32 elapsed_msec)
{
IEC_GOOSE_RX_USER_INFO *user_info;

  /* Check for retrans timeout on each subscriber.	*/
  for (user_info = sub_ctrl.sub_list;
       user_info != NULL;
       user_info = (IEC_GOOSE_RX_USER_INFO *) list_get_next (sub_ctrl.sub_list, user_info))
    {
    if (user_info->retrans_timeout > 0) 
      {
      /*check for timeoout and issue timeout callback if needed	*/
      if(((user_info->retrans_timeout -= elapsed_msec)<=0) && (user_info->usr_fun!=NULL))
        (*user_info->usr_fun)(user_info, user_info->gptr, user_info->usr, GOOSE_CALLBACK_REASON_TIMEALLOWED_TO_LIVE_TIMEOUT);
      } 
    }
}



/****************************************************/
/*				iecGooseSubscribe					*/
/*  this sets a list of multicast addresses			*/
/*  this function must be modified to include		*/
/*  UCA GOOSE subscriptions and ES/IS addresses		*/
/*  if there is a combined stack					*/
/****************************************************/

IEC_GOOSE_RX_USER_INFO *iecGooseSubscribe( ST_UCHAR *DstAddress,
          		 ST_CHAR *GooseRef,
          		 ST_CHAR *DataSetRef,
          		 ST_CHAR *AppID,
          		 ST_INT32 ConfRevNum,		/*initial configuration number expected		*/
          		 ST_INT numDataEntries,		/*number of entries expecting			*/
          		 RT_TYPE_ARRAY *rt_array_in,
          		 ST_VOID (*usr_fun)(IEC_GOOSE_RX_USER_INFO *info,
  						 GSE_IEC_CTRL *gptr,
      						 ST_VOID *usr,
      						 ST_UINT16 reason),	/*callback function		*/
          		 ST_INT mode_of_decode		/* GOOSE_DEC_MODE_..*/
          		 )
{
  GSE_IEC_CTRL *gptr;
  IEC_GOOSE_RX_USER_INFO *goosehandle = NULL;
  ST_INT i;
  RT_TYPE_ARRAY *rt_array;


  /*create the gse_control	*/

  rt_array = rt_array_in;


  /*check to make sure that everything that is absolutely needed is given	*/

  if(	(GooseRef==NULL) || (DataSetRef == NULL) || (AppID == NULL) ||
    (numDataEntries ==0) || (rt_array == NULL) || (usr_fun==NULL))
    return(goosehandle);

  if((gptr = gse_iec_control_create (GooseRef, DataSetRef, AppID, numDataEntries))!=NULL)
    {
    gptr->confRev =ConfRevNum;
    goosehandle = add_rxd_goose(gptr, DstAddress, mode_of_decode, usr_fun);
 
    /*have a good control block, time to add data entries	*/

    for(i=0;i<numDataEntries;i++, rt_array++)
      {
      gse_iec_data_init(gptr, i, rt_array->rt, rt_array->num_rts);
      /*the decoded data will appear in the Gptr->dataEntries[i].dataBuf	*/
      /*allocated by the gse_iec_data_init call	*/
      }

    /* Update list of multicast addresses in the driver.	*/
    set_multicast_filters ();
    }
  return(goosehandle);
}

/************************************************************************/
/*	iecGooseUnSubscribe						*/
/* this function is intended to free any allocated resources by the	*/
/*Subscribe function							*/
/************************************************************************/
ST_RET iecGooseUnSubscribe( IEC_GOOSE_RX_USER_INFO *goosehandle)
{
ST_RET ret = SD_SUCCESS;

  /* do this first because delete_rxd_goose frees goosehandle*/
  gse_iec_control_destroy(goosehandle->gptr);

  if (delete_rxd_goose(goosehandle) != SD_SUCCESS)
    SLOGALWAYS0("delete_rxd_goose failed");

  /*reset multicast filters	*/
  set_multicast_filters();

  return(ret);
}

/************************************************************************/
/* 	check_sub_mac_list						*/
/* Check to see if there is a subscription for this MAC and gcRef.	*/
/* DEBUG: other GSE_IEC_HDR params could also be checked.		*/
/************************************************************************/
static IEC_GOOSE_RX_USER_INFO *check_sub_mac_list(ST_UCHAR *loc_mac, GSE_IEC_HDR *hdr)
{
IEC_GOOSE_RX_USER_INFO *goosehandle = NULL;

#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_get(&sub_ctrl.sub_mutex);
#endif
  /* Check for retrans timeout on each subscriber.	*/
  for (goosehandle = sub_ctrl.sub_list;
       goosehandle != NULL;
       goosehandle = (IEC_GOOSE_RX_USER_INFO *) list_get_next (sub_ctrl.sub_list, goosehandle))
    {
    if (memcmp (goosehandle->dst_mac, loc_mac, MAC_ADDR_SIZE) == 0 &&
        strcmp (goosehandle->gptr->gcRef,hdr->gcRef)==0)
      {
      /* Found a match on "MAC" and "gcRef". Return ptr to this entry.	*/
      break;
      }
    }
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_free(&sub_ctrl.sub_mutex);
#endif

return(goosehandle);
}	

    

/************************************************************************/
/*		iecGooseLastRxSave					*/
/* This function saves the last received IEC GOOSE for each DST MAC	*/
/* to be decoded later.							*/
/* User app must call "iecGooseLastRxDecode" to decode these GOOSEs.	*/
/************************************************************************/
static ST_VOID iecGooseLastRxSave( IEC_GOOSE_RX_USER_INFO *lookup_ptr, 
				      ST_INT pdu_len, 
				      ST_CHAR *pdu ,
				      ST_CHAR *src_mac, 
				      ETYPE_INFO *info)
{
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_get(&sub_ctrl.sub_mutex);
#endif
   if(lookup_ptr->goose_pdu==NULL)		/*then need to allocate	*/
     lookup_ptr->goose_pdu = chk_malloc(MAX_IEC_GOOSE_ENCODE_BUF);

   memcpy(lookup_ptr->goose_pdu,pdu,pdu_len);
   lookup_ptr->goose_pdu_len=pdu_len;
   memcpy(lookup_ptr->src_mac,src_mac,MAC_ADDR_SIZE);
   memcpy(&lookup_ptr->etype_info, info, sizeof((*info)));
   lookup_ptr->decode_needed=SD_TRUE;
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_free(&sub_ctrl.sub_mutex);
#endif
}


/************************************************************************/
/*				iecGooseDecode				*/
/* Decode the IEC GOOSE msg.						*/
/* NOTE: header already decoded (see goosehandle->gse_iec_hdr).		*/
/************************************************************************/
static ST_VOID iecGooseDecode (IEC_GOOSE_RX_USER_INFO *goosehandle, ETYPE_INFO *info)
{
GSE_IEC_CTRL *gptr;
ST_UINT16 reason = 0x0;
ST_INT i;
GSE_IEC_DATA_ENTRY *found_deptr=NULL;
GSE_IEC_HDR *hdr;

  IEC_GOOSE_LOG_FLOW0 ("IEC 61850 GOOSE decode begins");
 
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_get(&sub_ctrl.sub_mutex);
#endif
  /* Header decoded earlier and dst MAC and gcRef matched, "goosehandle"*/
  /* points to "matched" info.						*/
  hdr = goosehandle->gse_iec_hdr;

  goosehandle->num_rxd++;			/*increment number of received	*/

  gptr = goosehandle->gptr;

  /*check the configuration revision number and other gcRef, appid, datset	*/
  /*depending on how "fussy" the end application is	*/
  /*some of these checks may be removed.	*/

  if(hdr->confRev != gptr->confRev)				/*then there is a configuration problem	*/
    reason |= GOOSE_CALLBACK_REASON_CONFREV_MISMATCH;
  if(strcmp( hdr->appID ,gptr->appID) )
    reason |= GOOSE_CALLBACK_REASON_APPID_MISMATCH;
  if(strcmp ( hdr->dataSetRef, gptr->dataSetRef) )
    reason |= GOOSE_CALLBACK_REASON_DATSET_MISMATCH;
  if(strcmp ( hdr->gcRef , gptr->gcRef) )
    reason |= GOOSE_CALLBACK_REASON_GCREF_MISMATCH;

  if(!reason)	/*if there are no errors in configuration	*/
    {
    if(hdr->stNum != gptr->stNum)			/*we must decode the data then	*/
      {
      IEC_GOOSE_LOG_CFLOW2("StNumber change detected Old[%04x] New[%04x]",
        gptr->stNum, hdr->stNum);
      /*mark the data unchanged	*/
      for(i=0;i<gptr->numDataEntries;++i)
        gptr->dataEntries[i].userInfo = NULL;	/* userInfo=NULL indicates dataEntry not valid*/

      if (hdr->numDataEntries == gptr->numDataEntries)
        {	/* num entries received MUST match expected	*/
        reason |= GOOSE_CALLBACK_REASON_STATECHANGE_DATA_UPDATED;
        for(i=0;i<gptr->numDataEntries;++i)
          {
          found_deptr = &gptr->dataEntries [i];
          assert (found_deptr);	/* must always be valid	*/
          if ( ( ms_asn1_to_local(	found_deptr-> runtimeTypeHead,
				found_deptr->numRuntimeTypes,
				hdr->dataEntries[i].asn1Ptr,
				hdr->dataEntries[i].asn1Len,
				found_deptr->dataBuf)) == SD_SUCCESS )
            {
            /*mark the user info so the application can determine which	*/
            /*elements have been updated	*/
            found_deptr->userInfo = (ST_VOID *)1;	/* userInfo!=NULL indicates dataEntry valid*/
            }
          else
            SLOGALWAYS2 ("ERROR: Conversion of data from ASN.1 to local failed for GOOSE DataSet '%s', entry #%d. Possible type inconsistency.",
                           hdr->dataSetRef, i);
          }
        }
      else
        {
        SLOGALWAYS2 ("ERROR: num entries received (%d) does not match expected (%d). Data ignored.",
                     hdr->numDataEntries, gptr->numDataEntries);
        /* DEBUG: this reason also used when dataSetRef doesn't match. Should we make new reason?*/
        reason |= GOOSE_CALLBACK_REASON_DATSET_MISMATCH;
        }
      }
    }


  
  /* gptr->sqNum contains "next expected" value of sqNum.	*/
  /* First sqNum is always 0 but 0 is skipped on rollover.	*/
  /* NOTE: if decode mode is GOOSE_DEC_MODE_LAST_RX, get lots of these	*/
  /*   errors because last PDU may be decoded many times with same sqNum.*/
  /* When stNum changes, sqNum goes back to 0, so don't check sqNum in that case*/
  if (hdr->stNum == gptr->stNum && hdr->sqNum != gptr->sqNum)  
    reason |=GOOSE_CALLBACK_REASON_OUT_OF_SEQUENCE_DETECTED;

  if(hdr->needsCommissioning)
    reason |= GOOSE_CALLBACK_REASON_NEED_COMMISSIONING;
  if(hdr->test)
    reason |= GOOSE_CALLBACK_REASON_TEST_MODE;

  /* Update stored values in "gptr".	*/
  gptr->stNum = hdr->stNum;
  gptr->sqNum = hdr->sqNum + 1;	/* this gets us back in sync with sender (if we were out of sync)*/
  /* Handle rollover, skip 0 (next expected sqNum=1)	*/
  if (gptr->sqNum == 0)
    gptr->sqNum++;
  gptr->needsCommissioning = hdr->needsCommissioning;
  gptr->test = hdr->test;

  /* Add the Ethertype info */
  goosehandle->etype_tci   = info->tci;
  goosehandle->etype_id	   = info->etypeID;
  goosehandle->etype_appID = info->appID;

  IEC_GOOSE_LOG_CFLOW1 ("IEC 61850 GOOSE decode ends. reason = %d", reason);
  /* Call user callback function ONLY if reason != 0	*/
  if (reason!=0)
    {
    IEC_GOOSE_LOG_CFLOW0 ("Calling user callback function");
    (*goosehandle->usr_fun)(goosehandle, gptr, goosehandle->usr,reason);
    }
  else
    IEC_GOOSE_LOG_CFLOW0 ("NOT calling user callback function because reason=0");
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_free(&sub_ctrl.sub_mutex);
#endif
  return;
}


/********************************************************************/
/*				iecGooseLastRxDecode			*/
/* This function decodes the last received IEC GOOSE for each DST MAC.	*/
/********************************************************************/
ST_RET iecGooseLastRxDecode(ST_VOID)
{
IEC_GOOSE_RX_USER_INFO *goosehandle = NULL;
ST_RET ret = SD_FAILURE;

#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_get(&sub_ctrl.sub_mutex);
#endif
  for (goosehandle = sub_ctrl.sub_list;
       goosehandle != NULL;
       goosehandle = (IEC_GOOSE_RX_USER_INFO *) list_get_next (sub_ctrl.sub_list, goosehandle))
    {
    if(goosehandle->decode_mode == GOOSE_DEC_MODE_LAST_RX &&
      (goosehandle->decode_needed == SD_TRUE)  )
      {
      IEC_GOOSE_LOG_FLOW0("Decoding last received GOOSE for this Subscriber");
      iecGooseDecode(goosehandle, &goosehandle->etype_info);
      ret = SD_SUCCESS;
      }
    }
#if defined(USE_FRAMEWORK_THREADS)
  gs_mutex_free(&sub_ctrl.sub_mutex);
#endif
return(ret);
}



/********************************************************************/
/*				chk_for_goose_msg									*/
/*function used to chk for goose messages.  This may be called		*/
/*after polling the subnet interface or be called from within that	*/
/*interface directly												*/
/* CRITICAL: if this message is GOOSE, this function decodes the header	*/
/*   and saves it. Sometime later when all decoding is done (or when	*/
/*   error is detected), gse_iec_decode_done must be called to free mem.*/
/********************************************************************/
ST_RET chk_for_goose_msg (SN_UNITDATA *sn_req)
{
IEC_GOOSE_RX_USER_INFO *goosehandle;
ST_RET ret= SD_FAILURE;
ETYPE_INFO etype;
ST_UCHAR *apdu;
ST_INT apdu_len;
GSE_IEC_HDR *gse_iec_hdr;

/********************************************
An Ethertype frame consists of [loc_mac][rem_mac][VLAN][Ethertype][data]

The size of the _mac(s) is 6 octets

The size of the VLAN is 2 octets, The size of the Ethertype is 10 octets

The pdu_len MUST be the length of the bytes within the lpdu minus the MACs,
VLAN, and Ethertype.

The pointer to the pdu is a pointer to [VLAN][Ethertype][data],
it should be passed to etype_hdr_decode(...) to retrieve the [data].

*********************************************/

  /*this is the section where the framework will be extended to		  */
  /*receive other link level PDUs besides IEC_GOOSE.			  */
  /*In order to extend, add the ETYPE_TYPE_... definition from ethertyp.h */
  /* NOTE: "sn_req->lpdu_len" represents "type", not "length" in this case.*/

  /* Check if this is an IEC 61850 GOOSE message	*/
  if(sn_req->lpdu_len == ETYPE_TYPE_GOOSE)
    {				/* it is a GOOSE	*/
    /* Returns a ptr to the data */
    apdu = etype_hdr_decode(sn_req, &etype, &apdu_len);
      	
    /* If GOOSE, must decode header & use header info to decide what next.*/
    if(etype.etypeID == ETYPE_TYPE_GOOSE &&
       (gse_iec_hdr = gse_iec_hdr_decode(apdu, apdu_len))!=NULL)
      {
      ret= SD_SUCCESS;
      if(iec_goose_usr_debug & IEC_GOOSE_LOG_RX)  /*logged received IEC GOOSE	*/
        {	/* No LOG_RX macros, so use SLOGALWAYS	*/
        log_iec_goose_msg (sn_req->loc_mac, sn_req->rem_mac, apdu_len, apdu, gse_iec_hdr, &etype);
        }

      /*see if it is a GOOSE that needs to be decoded later	*/

#if defined(USE_FRAMEWORK_THREADS)
      gs_mutex_get(&sub_ctrl.sub_mutex);
#endif
      if ( (goosehandle= check_sub_mac_list(sn_req->loc_mac, gse_iec_hdr))!=NULL)
        {        /* Match found.	*/
        /* Reset timeToLive now, not in iecGooseDecode. Decode may not be done until later.*/
        goosehandle->retrans_timeout= goosehandle->gptr->timeToLive = gse_iec_hdr->timeToLive;		

        /* For GOOSE_DEC_MODE_LAST_RX, free old hdr first.	*/
        /* DEBUG: most recent hdr never gets freed. Perhaps that could be done before exit.*/
        if(goosehandle->decode_mode == GOOSE_DEC_MODE_LAST_RX && goosehandle->gse_iec_hdr)
          gse_iec_decode_done (goosehandle->gse_iec_hdr);	/* done with "previous" GOOSE*/

        /* Save new gse_iec_hdr for use later in decode, etc.*/
        goosehandle->gse_iec_hdr = gse_iec_hdr;
        
        IEC_GOOSE_LOG_CFLOW0("*** subscribed message rxd'd");
        if(goosehandle->decode_mode == GOOSE_DEC_MODE_LAST_RX)
          {
          IEC_GOOSE_LOG_CFLOW0("*** message being saved for later decode");
          iecGooseLastRxSave(goosehandle,apdu_len,apdu,sn_req->rem_mac, &etype);
          }
        else if	(goosehandle->decode_mode == GOOSE_DEC_MODE_IMMEDIATE)
          {
          IEC_GOOSE_LOG_CFLOW0("*** message being immediately decoded");
          iecGooseDecode(goosehandle, &etype);
          gse_iec_decode_done (gse_iec_hdr);	/* done with this GOOSE*/
          }
        }
      else
        {
        IEC_GOOSE_LOG_CFLOW1("*** subscription not found for gcRef='%s'. Message ignored", gse_iec_hdr->gcRef);
        gse_iec_decode_done (gse_iec_hdr);	/* done with this GOOSE*/
        }
#if defined(USE_FRAMEWORK_THREADS)
      gs_mutex_free(&sub_ctrl.sub_mutex);
#endif
      }
    }
  return(ret);
}


/********************************************************************/
/*		get_goose_messages					*/
/*function used to read messages from the SISCO subnet interface	*/
/********************************************************************/
ST_RET get_goose_messages(ST_VOID)
{
ST_RET ret= SD_FAILURE;
SN_UNITDATA sn_req;

  if( (ret = clnp_snet_read  (&sn_req)) == SD_SUCCESS)
    {
    ret = chk_for_goose_msg (&sn_req);
    clnp_snet_free (&sn_req);	/* CRITICAL: free resources	*/
    }
  return(ret);
}

/************************************************************************/
/*		convert_mac_to_string					*/
/************************************************************************/
static ST_VOID convert_mac_to_string(ST_CHAR *dest,ST_UCHAR *mac)
{
ST_CHAR temp_store[65];
ST_INT i;
ST_CHAR ret_string[65];

  ret_string[0]=0x0;
  for(i=0;i<6;++i)
    {
    sprintf(temp_store,"%02x",mac[i]);
    if(i!=5)
      strcat(temp_store,":");
    strcat(ret_string,temp_store);
    }

  strcpy(dest,ret_string);

}

/*******************************************************************	*/
/*	log_iec_goose_msg						*/
/*******************************************************************	*/
static ST_VOID log_iec_goose_msg (ST_UCHAR *loc_mac, ST_UCHAR *rem_mac,
			ST_INT pdu_len, ST_CHAR *pdu, GSE_IEC_HDR *hdr, ETYPE_INFO *etype)
{
ST_CHAR debug[800];
ST_INT i;
ST_INT numDataEntries;		
GSE_IEC_DATA_ENTRY_RX *DataEntry;

  /* Only get in this function if IEC_GOOSE_LOG_RX is set, so just use SLOGALWAYS (faster).*/
  SLOGALWAYS0 ("IEC 61850 GOOSE message received");
      
  SLOGCALWAYS1 ("Ethertype TCI: 0x%04X", etype->tci);
  SLOGCALWAYS1 ("Ethertype Type ID: 0x%04X", etype->etypeID);
  SLOGCALWAYS1 ("Ethertype APP ID: 0x%04X", etype->appID);
  SLOGALWAYSH(pdu_len,pdu);	/*log the hex pdu	*/

  convert_mac_to_string(debug,loc_mac);

  SLOGCALWAYS0("Ethernet Header:");
  SLOGCALWAYS1("\tDestMac: %s",debug);

  convert_mac_to_string(debug,rem_mac);
  SLOGCALWAYS1("\tSrcMac: %s",debug);
  SLOGCALWAYS0("\tLPDU:");



  SLOGCALWAYS0("\t\tIEC GOOSE INFORMATION:");
  SLOGCALWAYS3 ("\t\t\tGCREF: %s, DatSet %s, AppID %s",
        	hdr->gcRef,hdr->dataSetRef,hdr->appID);
  SLOGCALWAYS3 ("\t\t\tConRev: %d, NeedsCommissiong: %02x, test: %02x",
        	hdr->confRev,hdr->needsCommissioning, hdr->test);
  SLOGCALWAYS2 ("\t\t\tStNum: %lu, SqNum: %lu",
        	hdr->stNum, hdr->sqNum);

  SLOGCALWAYS1 ("\t\t\tNum of dataEntries: %d", hdr->numDataEntries);

  /*prepare to display the entries and data	*/
  numDataEntries = hdr->numDataEntries;
  DataEntry = hdr->dataEntries;
  for(i=0;i<numDataEntries; ++i)
    {
    SLOGCALWAYS1("\t\t\tDataEntry [%04d]:", i) ;

    /* Convert ASN.1 data to local format and log it.	*/
    m_rt_type_limit = 500;	/* CRITICAL: default limit is not big enough	*/
    m_log_data (DataEntry->asn1Len, DataEntry->asn1Ptr);

    ++DataEntry;
    }
}


/************************************************************************/
/*			iecGooseSubscribe2				*/
/* Same as iecGooseSubscribe but uses typeid_array instead of (RT_TYPE_ARRAY *).*/
/************************************************************************/
IEC_GOOSE_RX_USER_INFO *iecGooseSubscribe2 (
	ST_UCHAR *DstAddress,
	ST_CHAR *GooseRef,
	ST_CHAR *DataSetRef,
	ST_CHAR *AppID,
	ST_INT32 confRev,	/* initial configuration number expected*/
	ST_INT numDataEntries,	/* number of DataSet entries expected	*/
	ST_INT *typeid_array,
	ST_VOID (*usr_fun)(IEC_GOOSE_RX_USER_INFO *info,
		GSE_IEC_CTRL *gptr,
		ST_VOID *usr,
		ST_UINT16 reason),	/* callback function	*/
	ST_INT mode_of_decode		/* GOOSE_DEC_MODE_..	*/
	)
  {
  GSE_IEC_CTRL *gptr;
  IEC_GOOSE_RX_USER_INFO *goosehandle = NULL;
  ST_INT j;
  RUNTIME_TYPE *rt_type;	/* ptr to RUNTIME_TYPE array for one DataSet entry	*/
  ST_INT rt_num;		/* num of RUNTIME_TYPE in array for one DataSet entry	*/

  /*check to make sure that everything that is absolutely needed is given	*/

  if((GooseRef==NULL) || (DataSetRef==NULL) || (AppID==NULL) ||
     (numDataEntries==0) || (typeid_array == NULL) || (usr_fun==NULL))
    return (NULL);

  /* Create a GOOSE control block	*/
  if((gptr = gse_iec_control_create (GooseRef, DataSetRef, AppID, numDataEntries))!=NULL)
    {
    gptr->confRev = confRev;	/* gse_iec_control_create doesn't set confRev, so do it now.*/

    /* Add data entries to the GOOSE control block.	*/
    for(j=0; j<numDataEntries; j++)
      {
      if (mvl_get_runtime (typeid_array [j], &rt_type, &rt_num) != SD_SUCCESS)
        {
        SLOGALWAYS1 ("Cannot find runtime type for type id=%d", typeid_array[j]);
        return (NULL);	/* error: can't continue	*/
        }
      if (gse_iec_data_init (gptr, j, rt_type, rt_num) != SD_SUCCESS)
        {
        SLOGALWAYS1 ("gse_iec_data_init failed for type id=%d", typeid_array[j]);
        return (NULL);	/* error: can't continue	*/
        }
      /* The decoded data will appear in the gptr->dataEntries[i].dataBuf*/
      /* allocated by gse_iec_data_init.				*/
      }

    goosehandle = add_rxd_goose (gptr, DstAddress, mode_of_decode, usr_fun);

    /* Update list of multicast addresses in the driver.	*/
    if (set_multicast_filters () != SD_SUCCESS)
      {	/* DEBUG: should never happen, but if so, probably need more cleanup here.*/
      SLOGALWAYS0 ("Error setting multicast filters. Cannot complete Subscription.");
      goosehandle = NULL;
      }
    }
  return(goosehandle);
  }
