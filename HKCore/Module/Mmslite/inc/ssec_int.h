/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*      (c) Copyright Systems Integration Specialists Company, Inc.,    */
/*      	 2003 - 2007, All Rights Reserved                       */
/*                                                                      */
/* MODULE NAME : ssec_int.h	                                        */
/* PRODUCT(S)  :                                                        */
/*                                                                      */
/* MODULE DESCRIPTION :                                                 */
/*	This module contains internal security functions, defines,...	*/
/*	that are not exposed to user.					*/
/*	It also contains function that are passing GEN_SOCK parameter.	*/
/*	Having these protos in ssec.h caused compile conflicts in	*/
/*	project using old gensock.h					*/
/*                                                                      */
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :                            */
/*                                                                      */
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev     Comments                                     */
/* --------  ---  ------   -------------------------------------------  */
/* 11/06/07  EJV    02     Chg sSecGetCertId param to ST_UINT32.	*/
/*			   Added few prototypes.			*/
/* 08/25/03  EJV    01     Moved protos with GEN_SOCK from ssec.h	*/
/************************************************************************/

#ifndef SSEC_INT_INCLUDED
#define SSEC_INT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "gensock2.h"


/* internal functions for secure socket interface */
ST_RET setGenSockSSL (GEN_SOCK_CONFIG *sockCfg);
ST_RET sSecGetCipherSuite (GEN_SOCK *pSock, ST_INT *cipherSuiteOut);
ST_RET sSecGetCertId (GEN_SOCK *pSock, ST_UINT32 *cfgIdOut);
ST_RET sSecGetCertCtrl (GEN_SOCK *pSock, S_CERT_CTRL **certCtrlOut);

ST_RET _secManGetCfg (S_SEC_CONFIG **secCfgOut);

ST_INT       sslGetCipherSuite (GEN_SOCK *pSock);
S_CERT_INFO *sslGetPeerCert    (GEN_SOCK *pSock);
ST_VOID      sslFreePeerCert   (S_CERT_INFO *remCert);


/************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* SSEC_INT_INCLUDED */
/************************************************************************/
