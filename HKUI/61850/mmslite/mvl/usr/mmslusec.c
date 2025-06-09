/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	      2003 - 2005, All Rights Reserved.		        */
/*									*/
/* MODULE NAME : mmslusec.c						*/
/* PRODUCT(S)  : MMS-EASE Lite with LITESECURE				*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/* 		This file contains Security related user functions.	*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 09/06/05  EJV     06    Rpl suicacse.h with lean_a.h.		*/
/* 08/02/05  EJV     05    Added suicacse.h (not in MMS H file anymore)	*/
/* 02/25/05  MDE     04    Now match remote AE Title on confirm		*/
/* 01/20/04  EJV     03    ulFreeAssocSecurity: del cc param; reworked.	*/
/* 01/07/04  EJV     02    Merged with  MMS-EASE mms_usec.c.		*/
/* 07/08/03  EJV     01    Adopted from MMS-EASE mms_usec.c.		*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "mem_chk.h"
#include "mvl_defs.h"
#include "mvl_acse.h"
#include "mmslusec.h"
#include "lean_a.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

#if defined(S_SEC_ENABLED)

/************************************************************************/
/*			ulSetSecurityCalling				*/
/*----------------------------------------------------------------------*/
/* This function prepares the calling connection security info based on	*/
/* information in the Security Configuration (secManCfg.xml).		*/
/* It is to be be called just before the initiate request is called.	*/
/* Parameters:								*/
/*  ST_CHAR    *locArName	ptr to local AR Name for the connection	*/
/*  ST_CHAR    *remArName	ptr to remote AR Name for the connection*/
/*  S_SEC_LOC_AR **locArSecOut	addr where local AR Security ptr is ret	*/
/*  S_SEC_REM_AR **remArSecOut	addr where remote AR Security ptr is ret*/
/*  ACSE_AUTH_INFO     *locAuthInfo	ptr to Authenication Info to set*/
/*  S_SEC_ENCRYPT_CTRL *encryptCtrl	ptr to Encryption Ctrl to set	*/
/* Returns:								*/
/*    SD_SUCCESS		if setting security info for calling	*/
/*				connection successful,			*/
/*    SD_FAILURE		otherwise.				*/
/************************************************************************/
ST_RET ulSetSecurityCalling (ST_CHAR            *locArName,
			     ST_CHAR            *remArName,
			     S_SEC_LOC_AR      **locArSecOut,
			     S_SEC_REM_AR      **remArSecOut,
                             ACSE_AUTH_INFO     *locAuthInfo,
                             S_SEC_ENCRYPT_CTRL *encryptCtrl)
{
ST_RET         ret;
S_SEC_CONFIG  *pSecCfg;			/* pointer to security cfg	*/
S_SEC_LOC_AR  *locArSec;		/* Local AR Security  		*/
S_SEC_REM_AR  *remArSec;		/* Remote AR Security 		*/

  /* access the security configuration */
  ret = secManAccessCfg (&pSecCfg);
  if (ret != SD_SUCCESS)
    {
    SECLOG_ERR1 ("Could not access security configuration (ret=%d)", ret);
    return (SD_FAILURE);
    }

  if (pSecCfg->secureModeEnabled)
    {
    /* Retrieve the AR security configuration for local AR Name 	*/
    ret = sSecLocArNameToArSec (locArName, &locArSec);
    if (ret != SD_SUCCESS)
      {
      secManReleaseCfg ();
      SECLOG_NERR1 ("Local AR Security for '%s' not found", locArName);
      return (SD_FAILURE);
      }
  
    /* Retrieve the AR security configuration for remote AR Name 	*/
    ret = sSecRemArNameToArSec (remArName, &remArSec);
    if (ret != SD_SUCCESS)
      {
      secManReleaseCfg ();
      SECLOG_NERR1 ("Remote AR Security for '%s' not found", remArName);
      return (SD_FAILURE);
      }
  
    /* See if we are to use MACE with this remote node */
    if (remArSec->arAuthMode == S_AR_AUTH_MODE_MACE)
      {
      if (locArSec->maceCert == NULL)
        {
        secManReleaseCfg ();
        SECLOG_NERR1 ("Local AR '%s' does not have MACE certificate", locArName);
        return (SD_FAILURE);
	}

      /* Create MACE Authentication information 				*/
      /* Note that the MACE ASN.1 Buffer will be free'd by MVL as appropriate	*/
      ret = sSecMaceAuthInfoCreate (&locArSec->maceCert->certId, locAuthInfo);
      if (ret != SD_SUCCESS)
        {
        secManReleaseCfg ();
        SECLOG_NERR1 ("Could not create MACE Authentication Information (ret=%d)", ret);
        return (SD_FAILURE);
        }
      }
    else	/* Not using MACE */
      locAuthInfo->auth_pres = SD_FALSE;
  
    /* Now set encryption for this connection					*/
    encryptCtrl->encryptMode = remArSec->encryptMode;
    encryptCtrl->u.ssl.port = remArSec->sslPort;

    *locArSecOut = locArSec;
    *remArSecOut = remArSec;
    }
  else
    {
    /* non-secured connection */
    locAuthInfo->auth_pres = SD_FALSE;
    encryptCtrl->encryptMode = S_SEC_ENCRYPT_NONE;
    *locArSecOut = NULL;
    *remArSecOut = NULL;
    }

  secManReleaseCfg ();
  return (SD_SUCCESS);
}

/************************************************************************/
/*			ulCheckSecureAssocConf				*/
/*----------------------------------------------------------------------*/
/* This function is to be called when a successful associate confirm is	*/
/* received. It verifies that the appropriate security settings are in	*/
/* effect.								*/
/* It should be called from 'u_mvl_connect_cnf_ex', and the connection 	*/
/* should only be accepted for a return value of ACSE_AUTH_SUCCESS	*/
/* Parameters:								*/
/*   MVL_NET_INFO   *cc		ptr to connection info			*/
/* Return:								*/
/*   ACSE_AUTH_SUCCESS		if security check successful		*/
/*   ACSE_DIAG_...		otherwise diagnostics code as defined	*/
/*				in acseauth.h				*/
/************************************************************************/
ST_RET ulCheckSecureAssocConf (MVL_NET_INFO *cc)
{
ST_RET              ret;
S_SEC_CONFIG       *pSecCfg;		/* pointer to security configuration	*/
S_SEC_AUTHCHK_RSLT  secChk;

  /* access the security configuration */
  ret = secManAccessCfg (&pSecCfg);
  if (ret != SD_SUCCESS)
    {
    SECLOG_ERR1 ("Could not access security configuration (ret=%d)", ret);
    return (ACSE_DIAG_AUTH_FAILURE);
    }

  if (pSecCfg->secureModeEnabled)
    {
    /* Check to make sure appropriate security settings are in place */
    memset(&secChk, 0, sizeof (S_SEC_AUTHCHK_RSLT));

    ret = sSecAssocConfChkEx (cc, &pSecCfg->dibMatch, cc->rem_ar_sec, &secChk);
    if (ret != SD_SUCCESS)
      {
      SECLOG_NERR1 ("Security settings for '%s' not acceptable", cc->rem_ar_sec->arName);
      return (ACSE_DIAG_AUTH_FAILURE);
      }
    }

  secManReleaseCfg ();
  return (ACSE_AUTH_SUCCESS);
}

/************************************************************************/
/*			ulCheckSecureAssocInd				*/
/*----------------------------------------------------------------------*/
/* This function checks if the received association indication can	*/
/* be accepted. 							*/
/* It should be called from 'u_mvl_connect_ind_ex', and the connection 	*/
/* should only be accepted for a return value of ACSE_AUTH_SUCCESS	*/
/*   MVL_NET_INFO    *cc	  ptr to connection info		*/
/*   ACSE_AUTH_INFO  *rspAuthInfo ptr to athorization info for response	*/
/* Returns:								*/
/*  ACSE_AUTH_SUCCESS		if security check successful		*/
/*   ACSE_DIAG_...		otherwise diagnostics code as defined	*/
/*				in acseauth.h				*/
/************************************************************************/
ST_RET ulCheckSecureAssocInd (MVL_NET_INFO *cc, ACSE_AUTH_INFO *rspAuthInfo)
{
ST_RET              ret;
S_SEC_CONFIG       *pSecCfg;		/* ptr to security configuration*/
S_SEC_REM_AR       *remArSec = NULL;	/* Local AR Security  		*/
S_SEC_LOC_AR       *locArSec = NULL;	/* Remote AR Security 		*/
S_SEC_AUTHCHK_RSLT  secChk;
DIB_MATCH_CTRL      dibMatch;
DIB_ENTRY          *remDe;

  /* access the security configuration */
  ret = secManAccessCfg (&pSecCfg);
  if (ret != SD_SUCCESS)
    {
    SECLOG_ERR1 ("Could not access security configuration (ret=%d)", ret);
    return (ACSE_DIAG_AUTH_FAILURE);
    }

  rspAuthInfo->auth_pres = SD_FALSE;	/* assume no response authentication	*/

  if (pSecCfg->secureModeEnabled)
    {
    /* Find out who the remote node is based on configured Remote AR Security	*/
    memset(&secChk, 0, sizeof (S_SEC_AUTHCHK_RSLT));
    ret = sSecAssocIndChk (cc, &pSecCfg->dibMatch, &remArSec, &secChk);
    if (ret != SD_SUCCESS)
      {
      secManReleaseCfg ();
      SECLOG_NERR1 ("Security settings for indication not acceptable (ret=%d)", ret);
      return (ACSE_DIAG_AUTH_REQUIRED);  	    /* Reject the connection 	*/
      }
    cc->rem_ar_sec = remArSec;		/* save the remote AR security		*/

    /* We know who the remote is, and configured security elements are in use	*/
    /* If we are using MACE for this remote, get it ready to send		*/
    if (remArSec->arAuthMode == S_AR_AUTH_MODE_MACE)
      {
      /* Retrieve the AR security configuration for the Local AR Name		*/
      ret = sSecLocArNameToArSec (cc->bind_ctrl->ar_name, &locArSec);
      if (ret != SD_SUCCESS)
        {
        secManReleaseCfg ();
        SECLOG_NERR1 ("Local AR Security for '%s' not found", cc->bind_ctrl->ar_name);
        return (ACSE_DIAG_AUTH_REQUIRED); 	    /* Reject the connection 	*/
	}
      cc->loc_ar_sec = locArSec;	/* save the local AR security		*/

      if (locArSec->maceCert == NULL)
        {
        secManReleaseCfg ();
        SECLOG_NERR1 ("Local AR '%s' does not have MACE certificate", cc->bind_ctrl->ar_name);
        return (ACSE_DIAG_AUTH_REQUIRED); 	    /* Reject the connection 	*/
	}

      /* Now create the MACE auth_info structure for response.			*/
      ret = sSecMaceAuthInfoCreate (&locArSec->maceCert->certId, rspAuthInfo);
      if (ret != SD_SUCCESS)
        {
        secManReleaseCfg ();
        SECLOG_NERR1 ("Could not create MACE Authentication Information (ret=%d)", ret);
        return (ACSE_DIAG_AUTH_REQUIRED);	/* Reject the connection 	*/
	}
      }
    else	/* Not using MACE */
      rspAuthInfo->auth_pres = SD_FALSE;
    }
  else
    {
    /* check if we can find calling node's AR Name in Stack's Configuration	*/
    /* Use the AE Title information for matching				*/
    memset (&dibMatch, 0, sizeof (DIB_MATCH_CTRL));
    dibMatch.match_ap_title = SD_TRUE;
    dibMatch.match_ae_qualifier = SD_TRUE;
    ret = mvl_match_remote_ar (&dibMatch, cc, &remDe);
    if (ret == SD_SUCCESS)
      {
      /* We know the remote AR Name, but in this sample do not take action 	*/
      /* based on that information.						*/
      }
    }

  secManReleaseCfg ();
  return (ACSE_AUTH_SUCCESS);		/* Accept the connection 	*/
}

/************************************************************************/
/*			ulFreeAssocSecurity				*/
/*----------------------------------------------------------------------*/
/* This function releases authentication info.				*/
/* Parameters:								*/
/*   ACSE_AUTH_INFO	*authInfo	ptr to authtentication info	*/
/* Returns:								*/
/*	SD_SUCCESS		if function successful			*/
/*	SD_FAILURE		otherwise.				*/
/************************************************************************/
ST_RET ulFreeAssocSecurity (ACSE_AUTH_INFO *authInfo)
{
ST_RET ret = SD_SUCCESS;

  /* Clean authentication information */
  if (authInfo && authInfo->auth_pres)
    {
    ret = sSecFreeSecParam (authInfo);
    if (ret != SD_SUCCESS)
      SECLOG_NERR1 ("Could not free Authentication Info (ret=%d)", ret);
    }

  return (ret);
}

/************************************************************************/
/*			ulCheckSecurityConfiguration			*/
/*----------------------------------------------------------------------*/
/* This function can be called to check to see if the security 		*/
/* configuration has changed, and to reload it if so.			*/
/* Parameters:								*/
/*    none								*/
/* Return:								*/
/*    SD_SUCCESS		if checked/reloaded security config	*/
/*    SD_FAILURE or error code 	otherwise				*/
/************************************************************************/

ST_RET ulCheckSecurityConfiguration (ST_VOID)
  {
ST_RET        ret;
S_SEC_CONFIG *pSecCfg;
S_SEC_CONFIG  secCfgNew;

/* need to check if secureModeEnabled is set before proceeding */
  ret = secManAccessCfg (&pSecCfg);
  if (ret != SD_SUCCESS)
    {
    SECLOG_ERR1 ("Could not access security configuration (ret=%d)", ret);
    return (SD_FAILURE);
    }
  if (!pSecCfg->secureModeEnabled)
    {
    secManReleaseCfg ();
    return (SD_SUCCESS);
    }
  secManReleaseCfg ();

/* Let's see if the security configuration has been changed		*/
  if (secManChkNewCfgAvail())
    {

   /* Security Configuration has changed, load the new configutaion 	*/
    ret = secManLoadCfg (&secCfgNew);
    if (ret != SD_SUCCESS)
      {
      SECLOG_NERR1 ("Could not load new security configuration (ret=%d)", ret);
      return (ret);
      }
  
  /* Access the current security configuration */
    ret = secManAccessCfg (&pSecCfg);
    if (ret != SD_SUCCESS)
      {
      secManFreeCfg (&secCfgNew);
      SECLOG_ERR1 ("Could not access security configuration (ret=%d)", ret);
      return (SD_FAILURE);
      }

  /* Update the new configuration, then free the new copy		*/
    ret = sSecUpdate (pSecCfg, &secCfgNew);
    if (ret != SD_SUCCESS)
      SECLOG_NERR1 ("Could not put new configuration into effect (ret=%d)", ret);

    secManFreeCfg (&secCfgNew);
    secManReleaseCfg ();
    return (ret);
    }

  return (SD_SUCCESS);
  }

#endif /* defined(S_SEC_ENABLED) */
