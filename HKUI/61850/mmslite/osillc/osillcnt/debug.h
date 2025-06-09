/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		1996, All Rights Reserved				*/
/*									*/
/* MODULE NAME : debug.h						*/
/* PRODUCT(S)  : OSI LLC NDIS 3.0 Device Driver for NT 			*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 10/24/02  EJV    04     DBG defined causes fre compile error 2000,XP	*/
/* 05/28/98  DSF    03     DBG always defined				*/
/* 08/06/96  DSF    02     Added WriteErrorLogEntry support		*/
/* 05/22/96  DSF    01     Initial Release				*/
/*									*/
/************************************************************************/

extern ULONG OsillcDebugFlag;
extern ULONG ErrorCodes[];

/* #define DBG	1 */

#if DBG

#define DEBUGERROR0(a)			{if (OsillcDebugFlag > 0) DbgPrint ("OSILLC: %s %d " a "\n",__FILE__,__LINE__);}
#define DEBUGERROR1(a,b) 		{if (OsillcDebugFlag > 0) DbgPrint ("OSILLC: %s %d " a "\n",__FILE__,__LINE__,b);}
#define DEBUGERROR2(a,b,c) 		{if (OsillcDebugFlag > 0) DbgPrint ("OSILLC: %s %d " a "\n",__FILE__,__LINE__,b,c);}
#define DEBUGTRACE0(a)			{if (OsillcDebugFlag > 1) DbgPrint ("OSILLC: %s %d " a "\n",__FILE__,__LINE__);}
#define DEBUGTRACE1(a,b) 		{if (OsillcDebugFlag > 1) DbgPrint ("OSILLC: %s %d " a "\n",__FILE__,__LINE__,b);}
#define DEBUGTRACE2(a,b,c)		{if (OsillcDebugFlag > 1) DbgPrint ("OSILLC: %s %d " a "\n",__FILE__,__LINE__,b,c);}

#else

#define DEBUGERROR0(a)			{}
#define DEBUGERROR1(a,b)		{}
#define DEBUGERROR2(a,b,c)		{}
#define DEBUGTRACE0(a)			{}
#define DEBUGTRACE1(a,b)		{}
#define DEBUGTRACE2(a,b,c)		{}

#endif
