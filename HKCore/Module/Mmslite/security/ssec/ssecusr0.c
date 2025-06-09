/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*			2003 - 2008, All Rights Reserved		*/
/*									*/
/* MODULE NAME : ssecusr0.c 						*/
/* PRODUCT(S)  :							*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	This file contains Security Manager NUL functions called	*/
/*	from an MMS or MMS-Lite application.    			*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 07/07/08  EJV    19     Chg sSecGetCertId param to ST_UINT32.	*/
/* 10/04/07  MDE    18     Tweaked LOGCFG_VALUE_GROUP/LOGCFGX_VALUE_MAP	*/
/* 08/12/05  MDE    17     Added sslLogMaskMapCtrl			*/
/* 08/01/05  MDE    16     Added secLogMaskMapCtrl			*/
/* 02/25/05  MDE    15     Added sSecAssocConfChkEx			*/
/* 08/10/04  EJV    14     secManCfgXmlFile: all lowcase "secmancfg.xml"*/
/* 02/04/04  EJV    13	   Moved maceMechId to acse2dec.c and marb_tx.c	*/
/*			   Added secManCfgChange.			*/
/* 10/23/03  EJV    12     Del sSecFreeSecParam, sSecFreePartSecParam.	*/
/*			   Added params to sSecUpdate, sSecUsrEnd.	*/
/* 10/15/03  EJV    11     MMS_LITE: added glb var secManCfgXmlFile.	*/
/* 09/05/03  EJV    10     Changed defines SECLOG..._ to SEC_LOG_...	*/
/*			   Added ssle_debug_sel.			*/
/*			   sSecUpdate returns SD_SUCCESS.		*/
/*			   Added few more secman.c, genssl.c NUL funcs	*/
/* 08/25/03  EJV    09     Merged with recent code changes.		*/
/* 08/25/03  EJV    08     Added MMS_LITE code.				*/
/*			   Added sSecUpdate. Removed dupl sSecUsrStart.	*/
/*			   Added maceMechId.				*/
/*			   Added usr funcs from ssec.c			*/
/* 08/05/03  ASK    07     sSecFreeSecParam: chg param to ACSE_AUTH_INFO*/
/* 07/14/03  EJV    06     Added secman functions.			*/
/* 06/20/03  EJV    05     sSecAssocConfChk added parameters.		*/
/*			   sSecAssocIndChk added matchCtrl parameter.	*/
/* 05/27/03  EJV    04     sSecAssocIndChk added srcChkDest parameter.	*/
/* 05/21/03  EJV    03     Added sSecUsrStart.				*/
/* 05/08/03  EJV    02     Chg params according to ne ssec.h		*/
/* 04/22/03  EJV    01     Created from ssecusr.c			*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "ssec.h"
#include "ssec_int.h"
#include "sslelog.h"


/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/
/************************************************************************/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif


/************************************************************************/
/* Logging */

/* Log type strings */
SD_CONST ST_CHAR *SD_CONST _sec_err_logstr  = "SEC_LOG_ERR";
SD_CONST ST_CHAR *SD_CONST _sec_nerr_logstr = "SEC_LOG_NERR";
SD_CONST ST_CHAR *SD_CONST _sec_flow_logstr = "SEC_LOG_FLOW";
SD_CONST ST_CHAR *SD_CONST _sec_data_logstr = "SEC_LOG_DATA";
SD_CONST ST_CHAR *SD_CONST _sec_debug_logstr = "SEC_LOG_DEBUG";

ST_UINT       sec_debug_sel = SEC_LOG_ERR;
ST_UINT       ssle_debug_sel = SSLE_LOG_ERR;
S_SEC_CONFIG _dummySecCfg; 

LOGCFG_VALUE_GROUP secLogMaskMapCtrl =
  {
  {NULL,NULL},
  "SecurityLogMasks",  /* Parent Tag */
  0,
  NULL
  };

LOGCFG_VALUE_GROUP ssleLogMaskMapCtrl =
  {
  {NULL,NULL},
  "SecurityLogMasks",  /* Parent Tag */
  0,
  NULL
  };


#if defined(MMS_LITE) && !defined(MAP30_ACSE)
ST_CHAR *secManCfgXmlFile = "secmancfg.xml";
#endif  /* MMS_LITE over LEAN-T */

/************************************************************************/
/*			sSecUsrStart					*/
/************************************************************************/

ST_RET sSecUsrStart (S_SEC_CONFIG **secCfgOut)
  {
  _dummySecCfg.secureModeEnabled = SD_FALSE;
  *secCfgOut = &_dummySecCfg;
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			secManAccessCfg					*/
/************************************************************************/

ST_RET secManAccessCfg (S_SEC_CONFIG **secCfgOut)
  {
  _dummySecCfg.secureModeEnabled = SD_FALSE;
  *secCfgOut = &_dummySecCfg;
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			secManReleaseCfg				*/
/************************************************************************/

ST_RET secManReleaseCfg ()
  {
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			     sSecUpdate  				*/
/************************************************************************/

ST_RET sSecUpdate(S_SEC_CONFIG *currCfg, S_SEC_CONFIG *newCfg)
  {
  return (SD_SUCCESS);
  }

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* Set/Get/Free Authentication Info & Encrypt Control	*/
	/* in stack.						*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined(MMS_LITE) || defined(MAP30_ACSE)
/************************************************************************/
/*			sSecSetSecParam					*/
/*----------------------------------------------------------------------*/
/* Copies the local authentication info and encryption control into the */
/* channel info. This function must be called before MMS connection	*/
/* request.								*/
/* After connection terminated call the s_free_security_info() to free	*/
/* the user allocated auth_value buf and cleanup the channel info.	*/
/* Parameters:								*/
/*  ST_INT		 chan		channel to set security info	*/
/*  S_SEC_PARAMS        *secParams	ptr to security parameters	*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if set operation succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/

ST_RET sSecSetSecParam (ST_INT chan, S_SEC_SPARAMS *secParams)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecGetSecParam					*/
/*----------------------------------------------------------------------*/
/* Returns pointers to encryption control and partner's authentication	*/
/* info	from the specified channel info. This functions should be called*/
/* after connection indication was received to retrieve the security	*/
/* informations.							*/
/* After the connection terminates call the s_free_part_security_info()	*/
/* to free the allocated auth_value buf and cleanup the channel info.	*/
/* Parameters:								*/
/*  ST_INT	         chan		 channel to get security info	*/
/*  S_SEC_PARAMS        *secParams	 ptr where to return sec params	*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	 if get operation succeeded	*/
/*			SD_FAILURE 	 or other error.		*/
/************************************************************************/

ST_RET sSecGetSecParam (ST_INT chan, S_SEC_SPARAMS *secParams)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

#else /* defined(MMS_LITE) */

/************************************************************************/
/*			sSecGetSecParam					*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if get operation succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/

ST_RET sSecGetSecParam (struct mvl_net_info *cc, S_SEC_SPARAMS *secParams) 
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecFreeSecParam			       	*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if free operation succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/
ST_RET sSecFreeSecParam (ACSE_AUTH_INFO *authInfo)
{
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
} 

/************************************************************************/
/*			sSecFreePartSecParam			   	*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if free operation succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/
ST_RET sSecFreePartSecParam (struct mvl_net_info *cc)
{
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
} 

/************************************************************************/
/*			secManCfgChange       				*/
/************************************************************************/

ST_VOID secManCfgChange(ST_VOID)
  {
  }
#endif /* defined(MMS_LITE) */

/************************************************************************/
/*			    sSecUsrEnd					*/
/*----------------------------------------------------------------------*/
/* Called by a MACE application to free any resources allocated by the 	*/
/* secman and sslEngine DLLs. This function should be called before the */
/* application terminates to ensure that all sensitive memory has been	*/
/* overwritten.								*/
/*	      								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if shutdown was successfull	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/
ST_RET sSecUsrEnd (ST_VOID)
  {
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			sSecAuthChk					*/
/*----------------------------------------------------------------------*/
/* Perform security checks on a received ACSE_AUTH_INFO			*/
/* 	1. Get the Cipher Suite being used for the connection		*/
/* 	2. Decode the certificate and time seal				*/
/* 	3. Verify the time seal						*/
/* 	4. Check the Certificate validity time				*/
/* 	5. Verify the issuer is acceptable per secCfg			*/
/* 	6. Match the subject to a AR Name per secCfg			*/
/* Parameters:								*/
/*  ST_INT		chan		conection channel 		*/
/*  S_SEC_AUTHCHK_RSLT *srcChkDest	pointer to authentication check	*/
/*					result.				*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Authentication check succeeded	*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

#if !defined(MMS_LITE)
ST_RET sSecAuthChk (ST_INT chan, S_SEC_AUTHCHK_RSLT *srcChkDest)
#else
ST_RET sSecAuthChk (struct mvl_net_info *cc, S_SEC_AUTHCHK_RSLT *srcChkDest)
#endif
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* MACE Authentication 					*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

/************************************************************************/
/*			sSecMaceAuthInfoCreate				*/
/*----------------------------------------------------------------------*/
/* Create a 'ready-to-go' ACSE_AUTH_INFO for the specified local AR	*/
/* Note that the returned struct is to be free'd using			*/
/* sSecMaceAuthInfoFree.						*/
/* Parameters:								*/
/*  S_CERT_ID		*certId		pointer to Certificate Id	*/
/*  ACSE_AUTH_INFO	*authInfo	pointer to Authentication Info	*/
/*					to be created.			*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if authInfo created		*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/

ST_RET sSecMaceAuthInfoCreate (S_CERT_ID *certId, ACSE_AUTH_INFO *authInfo)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecMaceAuthInfoFree				*/
/*----------------------------------------------------------------------*/
/* Free ACSE_AUTH_INFO fields.						*/
/* Parameters:								*/
/* ACSE_AUTH_INFO	*auth_info	pointer to Authentication Info	*/
/*					to free				*/
/* Return:								*/
/*	none								*/
/************************************************************************/

ST_VOID sSecMaceAuthInfoFree (ACSE_AUTH_INFO *auth_info)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  }


/************************************************************************/
/*			sSecMaceAsn1Enc					*/
/*----------------------------------------------------------------------*/
/* Encode a ASN.1 MACE ACSE_AUTH_INFO 					*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if MACE encoding succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/

ST_RET sSecMaceAsn1Enc (S_MACE_INFO *maceInfo, 
                        ST_CHAR *asn1Buf, ST_INT asn1BufLen,
                        ST_CHAR **maceAsn1Out, ST_INT *maceAsn1LenOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }


/************************************************************************/
/*			sSecMaceAuthInfoDec				*/
/*----------------------------------------------------------------------*/
/* Decode an ACSE_AUTH_INFO into time seal and certificate info 	*/
/* Note that the maceInfo is to be free'd using chk_free, and the 	*/
/* certInfo by sSecFreeCertInfo						*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if MACE decoding succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/

ST_RET sSecMaceAuthInfoDec (ACSE_AUTH_INFO *authInfo, 
			    S_MACE_INFO **maceInfoOut, 
			    S_CERT_INFO **certInfoOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecFreeCertInfo				*/
/*----------------------------------------------------------------------*/
/* Free Certificate Info.						*/
/*	S_CERT_INFO 	*certInfo	pointer to Certificate to free	*/
/* Parameters:								*/
/* Return:								*/
/*	none								*/
/************************************************************************/

ST_VOID sSecFreeCertInfo (S_CERT_INFO *certInfo)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  }

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* AR Security Configuration 				*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

/************************************************************************/
/*			sSecLocArNameToArSec				*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if conversion successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecLocArNameToArSec (ST_CHAR *arName, S_SEC_LOC_AR **arSecOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecRemArNameToArSec				*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if conversion successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecRemArNameToArSec (ST_CHAR *arName, S_SEC_REM_AR **arSecOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecAssocConfChk				*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Assoc Confirm check successful	*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

#if defined(MMS_LITE)
ST_RET sSecAssocConfChkEx (struct mvl_net_info *cc, DIB_MATCH_CTRL *matchCtrl,
			   S_SEC_REM_AR *remArSec, S_SEC_AUTHCHK_RSLT *srcChkDest)
#else
ST_RET sSecAssocConfChkEx (ST_INT chan, DIB_MATCH_CTRL *matchCtrl,
			   S_SEC_REM_AR *remArSec, S_SEC_AUTHCHK_RSLT *srcChkDest)
#endif
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecAssocIndChk					*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Assoc Indication check successful	*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

#if defined(MMS_LITE)
ST_RET sSecAssocIndChk (struct mvl_net_info *cc, DIB_MATCH_CTRL *matchCtrl, 
			S_SEC_REM_AR **arSecOut, S_SEC_AUTHCHK_RSLT *srcChkDest)
#else
ST_RET sSecAssocIndChk (ST_INT chan, DIB_MATCH_CTRL *matchCtrl, 
			S_SEC_REM_AR **arSecOut, S_SEC_AUTHCHK_RSLT *srcChkDest)
#endif
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }


	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* Finding things in the Security Configuration		*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

/************************************************************************/
/*			sSecCertNameToLocCertCtrl	 		*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if conversion successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/
/* Get the configured certCtrl for the selected Cert Name		*/

ST_RET sSecCertNameToLocCertCtrl (ST_CHAR *certName, S_CERT_CTRL **certCtrlOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecCertNameToRemCertCtrl    	 		*/
/*----------------------------------------------------------------------*/
/* Get the configured certCtrl for the selected Cert Name		*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if conversion successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecCertNameToRemCertCtrl (ST_CHAR *certName, S_CERT_CTRL **certCtrlOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecCertIdToRemCertCtrl				*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if conversion successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecCertIdToRemCertCtrl (S_CERT_ID *certId, S_CERT_CTRL **certCtrlOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*		  sSecCertCfgIdToRemCertCtrl				*/
/*----------------------------------------------------------------------*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if conversion successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecCertCfgIdToRemCertCtrl (ST_INT cfgId, S_CERT_CTRL **certCtrlOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* Remote Certificate Validity Checking			*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

/************************************************************************/
/*			sSecChkIssuer					*/
/*----------------------------------------------------------------------*/
/* Verify that the issuer of the certificate has been configured as OK	*/ 
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Issuer check successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecChkIssuer (S_CERT_INFO *certInfo)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecChkValidityTimes				*/
/*----------------------------------------------------------------------*/
/* Verify the certificate validity times are OK				*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if check Validity Times successful	*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecChkValidityTimes (S_CERT_INFO *certInfo)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecChkTimeSeal					*/
/*----------------------------------------------------------------------*/
/* This function performs time seal checks, which are an anti-replay 	*/
/* where:								*/
/*  	1. The signedTimeT must match local time within 		*/
/*	   pSecCfg->timeSigWindow seconds				*/
/* 	2. The signedTime has not have been received within 		*/
/*	   pSecCfg->timeSigWindow seconds				*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Time Seal check successful		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecChkTimeSeal (S_CERT_INFO *remCert, 
			time_t signedTimeT, 
			ST_UCHAR *clearTime,
			S_SIGNED_TIME *signedTime)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }


	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/*	Certificate Blob Handling 		     	*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

/************************************************************************/
/*			sSecGetLocalCert				*/
/*----------------------------------------------------------------------*/
/* Retrieve local Certificate Blob from Certificate Store for the 	*/
/* sprecified CName. 							*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if get Local Cert succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/


ST_RET sSecGetLocalCert (S_CERT_ID *certId, S_CERT_BLOB *certBlob)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecCertDec					*/
/*----------------------------------------------------------------------*/
/* Decode an Certificate Blob into certificate info 			*/
/* Note that the certInfo is to be free'd using sSecFreeCertInfo 	*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET		SD_SUCCESS	if Cert decode succeeded	*/
/*			SD_FAILURE      otherwise.			*/
/************************************************************************/

ST_RET sSecCertDec (S_CERT_BLOB *certData, S_CERT_INFO **certInfoOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */
	/* Signed Time Handling 				*/
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - */

/************************************************************************/
/*			sSecSignedTimeDec				*/
/*----------------------------------------------------------------------*/
/* Decode an SignedTime into time_t					*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Signed Time decode succeeded		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecSignedTimeDec (S_CERT_INFO *remCert, S_SIGNED_TIME *signedTime, time_t *timeOut)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }

/************************************************************************/
/*			sSecSignedTimeEnc				*/
/*----------------------------------------------------------------------*/
/* Encoding a Signed Time						*/
/* Parameters:								*/
/* Return:								*/
/*  ST_RET	SD_SUCCESS	if Signed Time encode succeeded		*/
/*		SD_FAILURE      otherwise.				*/
/************************************************************************/

ST_RET sSecSignedTimeEnc (S_CERT_ID *localCert, time_t timeToSign, S_SIGNED_TIME *signedTime)
  {
  SECLOG_NERR0 ("Security functions not supported.");
  return (SD_FAILURE);
  }



	/*------------------------------------------------------*/
	/*							*/
	/*	ssec.c NULL functions needed for MMS_LITE	*/
	/*							*/
	/*------------------------------------------------------*/

/************************************************************************/
/*			sSecStart					*/
/************************************************************************/
ST_RET sSecStart (S_SEC_CONFIG **secCfgOut)
  {
  _dummySecCfg.secureModeEnabled = SD_FALSE;
  *secCfgOut = &_dummySecCfg;
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			sSecEnd  					*/
/************************************************************************/

ST_RET sSecEnd (ST_VOID)
  {
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			  sSecGetCertId					*/
/************************************************************************/
/* Retrieve the remote certificate ID on a given socket			*/
ST_RET sSecGetCertId (GEN_SOCK *pSock, ST_UINT32 *cfgIdOut)
  {
  return (SD_FAILURE);
  }

/************************************************************************/
/*			  sSecGetCertCtrl 				*/
/************************************************************************/
/* Retrieve a ptr to the remote certificate control on a given socket   */
ST_RET sSecGetCertCtrl (GEN_SOCK *pSock, S_CERT_CTRL **certCtrlOut)
  {
  return (SD_FAILURE);
  }


/************************************************************************/
/*			sSecGetCipherSuite				*/
/************************************************************************/
/* Retrieve the cipher suite in use on a given socket			*/
ST_RET sSecGetCipherSuite (GEN_SOCK *pSock, ST_INT *cipherSuiteOut)
  {
  return (SD_FAILURE);
  }

/************************************************************************/
/*			setGenSockSSL					*/
/************************************************************************/
/* Sets the security control and callback functions on a given socket.  */
/* Called by SNAP; always returns SD_SUCCESS. 				*/

ST_RET setGenSockSSL (GEN_SOCK_CONFIG *sockCfg)
  {
  return (SD_FAILURE);
  }


	/*------------------------------------------------------*/
	/*							*/
	/*	secman.c NULL functions needed for MMS_LITE	*/
	/*							*/
	/*------------------------------------------------------*/

/************************************************************************/
/*			secManChkNewCfgAvail        			*/
/************************************************************************/

ST_BOOLEAN secManChkNewCfgAvail()
  {
  return (SD_FALSE);
  }

/************************************************************************/
/*			secManLoadCfg    	    			*/
/************************************************************************/

ST_RET secManLoadCfg(S_SEC_CONFIG *secCfgOut)
  {
  _dummySecCfg.secureModeEnabled = SD_FALSE;
  *secCfgOut = _dummySecCfg;

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			secManUpdateCfg    	    			*/
/************************************************************************/

ST_RET secManUpdateCfg(S_SEC_CONFIG *currCfg, S_SEC_CONFIG *newCfg)
  {
  return (SD_SUCCESS);
  }

/************************************************************************/
/*			secManFreeCfg    	    			*/
/************************************************************************/

ST_RET secManFreeCfg(S_SEC_CONFIG *secCfg)
  {
  return (SD_SUCCESS);
  }


	/*------------------------------------------------------*/
	/*							*/
	/*	genssl.c NULL functions needed for MMS_LITE	*/
	/*							*/
	/*------------------------------------------------------*/


/************************************************************************/
/*			     sslUpdate  				*/
/************************************************************************/

ST_RET sslUpdate()
  {
  return (SD_SUCCESS);
  }
