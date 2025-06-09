/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*      	1994 - 1996, All Rights Reserved		        */
/*									*/
/* MODULE NAME : s_fdir.c    						*/
/* PRODUCT(S)  : MMSEASE-LITE						*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*	_mvl_process_fdir_ind						*/
/*	mplas_fdir_resp							*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 03/09/05  CRM     12    Added mvlas_fdir_resp, convertFileTime, and	*/
/*                         fileFdirEnt functions for WIN32 defined	*/
/* 09/21/01  JRB     11    Alloc global bufs only once at startup.	*/
/* 03/30/01  MDE     10    Changed MSMEM_ENC_INFO to MSMEM_ENC_OS_INFO	*/
/* 09/13/00  JRB     09    Compute resp_info size (don't use const).	*/
/* 01/21/00  MDE     08    Now use MEM_SMEM for dynamic memory		*/
/* 09/13/99  MDE     07    Added SD_CONST modifiers			*/
/* 04/01/99  MDE     06    Changes to decode buffer allocation scheme   */
/* 11/16/98  MDE     05    Renamed internal functions (prefix '_')	*/
/* 09/21/98  MDE     04    Minor lint cleanup				*/
/* 06/15/98  MDE     03    Changes to allow compile under C++		*/
/* 05/14/98  JRB     02    Use MVL_IND_PEND. Add mvlas resp function.	*/
/* 09/10/97  MDE     01    MMS-LITE V4.0 Release			*/
/************************************************************************/

#include "glbtypes.h"
#include "sysincs.h"
#include "mmsdefs.h"
#include "mms_pfil.h"
#include "mvl_defs.h"
#include "mvl_log.h"

/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 	*/
/* __FILE__ strings.							*/
/************************************************************************/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

/*-----------------------------------------*/
/* Global definitions used by all systems  */
/*-----------------------------------------*/
#define SERVICE_OVRHD    20
#define DIR_ENTRY_OVRHD  32

/************************************************************************/
/************************************************************************/
/*			_mvl_process_fdir_ind				*/
/* A fdir indication has been received, process it and respond	*/
/************************************************************************/

ST_VOID _mvl_process_fdir_ind (MVL_IND_PEND *indCtrl)
  {
FDIR_REQ_INFO *req_info;
FILE_NAME *fs_fname;	/* ptr to array of FILE_NAME for "fs"	*/
FILE_NAME *ca_fname;	/* ptr to array of FILE_NAME for "ca"	*/
MVLAS_FDIR_CTRL *fdir;

  fdir = &indCtrl->u.fdir;

  req_info = (FDIR_REQ_INFO *) indCtrl->event->u.mms.dec_rslt.data_ptr;

  /* fs_fname array is right after req_info			*/
  fs_fname = (FILE_NAME *)(req_info + 1);
  /* ca_fname array is right after fs_fname array		*/
  ca_fname = fs_fname + req_info->num_of_fs_fname;

  if (req_info->filespec_pres)
    {
    if (_mvl_concat_filename (fdir->fs_filename, req_info->num_of_fs_fname, 
                      fs_fname, sizeof (fdir->fs_filename)))
      {
      _mplas_err_resp (indCtrl,11,3);	/* File name syntax error	*/
      return;
      }
    }
  else
    fdir->fs_filename[0] = 0;

  if (req_info->cont_after_pres)
    {
    if (_mvl_concat_filename (fdir->ca_filename, req_info->num_of_ca_fname, 
                      ca_fname, sizeof (fdir->ca_filename)))
      {
      _mplas_err_resp (indCtrl,11,3);	/* File name syntax error	*/
      return;
      }
    }
  else
    fdir->ca_filename[0] = 0;

  u_mvl_fdir_ind (indCtrl);
  }

/************************************************************************/
/*			mplas_fdir_resp				*/
/************************************************************************/
ST_VOID mplas_fdir_resp (MVL_IND_PEND *indCtrl)
  {
ST_RET rc;
FDIR_RESP_INFO *resp_info;
ST_UINT resp_size;	/* size of "resp_info"	*/
FDIR_DIR_ENT *fdir_entry;
FILE_NAME *fname;
ST_INT j;
MVL_FDIR_RESP_INFO *mvl_resp_info;


  mvl_resp_info = indCtrl->u.fdir.resp_info;

/* Compute size needed for "resp_info".					*/
/* NOTE: num_of_fname is always 1, so total_num_of_fname = num_dir_ent.	*/
  resp_size = sizeof (FDIR_RESP_INFO)
	        + (mvl_resp_info->num_dir_ent * sizeof (FDIR_DIR_ENT))
		+ (mvl_resp_info->num_dir_ent * sizeof (FILE_NAME));
  resp_info = (FDIR_RESP_INFO *) M_CALLOC (MSMEM_ENC_OS_INFO, 1, resp_size);
     
  resp_info->num_dir_ent = mvl_resp_info->num_dir_ent;
  resp_info->more_follows = mvl_resp_info->more_follows;
  for (j = 0,  fdir_entry = (FDIR_DIR_ENT *) (resp_info + 1);
       j < resp_info->num_dir_ent;  j++)
    {
    fdir_entry->fsize = mvl_resp_info->dir_ent[j].fsize;
    fdir_entry->mtimpres = mvl_resp_info->dir_ent[j].mtimpres;
    fdir_entry->mtime = mvl_resp_info->dir_ent[j].mtime;
    fdir_entry->num_of_fname = 1;	/* we always use 1	*/

    fname = (FILE_NAME *) (fdir_entry + 1);
    fname->fn_len = strlen (mvl_resp_info->dir_ent[j].filename);
    fname->fname = mvl_resp_info->dir_ent[j].filename;

    /* always 1 fname, so point after it to get to next fdir_entry.	*/
    fdir_entry = (FDIR_DIR_ENT *) (fname + 1);
    }

  /* Build a File Directory response 					*/
  rc = mpl_fdir_resp (indCtrl->event->u.mms.dec_rslt.id, resp_info);
  _mvl_send_resp_i (indCtrl, rc);

  M_FREE (MSMEM_ENC_OS_INFO, resp_info);
  }


#if defined(_WIN32)
/************************************************************************/
/*                      convertFileTime                                 */
/* convert FILETIME to time_t                                           */
/************************************************************************/

static time_t convertFileTime (FILETIME *pstFileTime)
  {
WORD wFatDate, wFatTime;
struct tm stTm;
time_t retTime;
FILETIME stLocalTime;

  FileTimeToLocalFileTime (pstFileTime, &stLocalTime);
  
  if (FileTimeToDosDateTime (&stLocalTime, &wFatDate, &wFatTime))
    {
    stTm.tm_sec  = (wFatTime & 0x001F) * 2;       // bits 0-4
    stTm.tm_min  = (wFatTime & 0x07E0) >> 5;      // bits 5-10
    stTm.tm_hour = (wFatTime & 0xF800) >> 11;     // bits 11-15
 
    stTm.tm_mday = wFatDate & 0x001F;             // bits 0-4
    stTm.tm_mon  = ((wFatDate & 0x01E0)>>5) - 1;  // bits 5-8
    stTm.tm_year = ((wFatDate & 0xFE00)>>9) + 80; // bits 9-15

    stTm.tm_isdst = -1; // let someone else figure out DST
    retTime = mktime (&stTm);
    }
  else
    retTime = -1;

  return retTime;
  }

/************************************************************************/
/*			fileFdirEnt					*/
/* fill up the FDIR_DIR_ENT struct, FILE_NAME struct, and nameBuffer	*/
/* from the WIN32_FIND_DATA struct.					*/
/************************************************************************/
static ST_VOID fillFdirEnt (WIN32_FIND_DATA *pstFindData, FDIR_DIR_ENT *pstFdirEnt,
		FILE_NAME *pstFileName, ST_CHAR *nameBuffer)
  {
time_t theTime;

  /* Fill in the FDIR_DIR_ENT struct.	*/
  pstFdirEnt->fsize = (pstFindData->nFileSizeHigh * MAXDWORD) + pstFindData->nFileSizeLow;
  
  theTime = convertFileTime (&pstFindData->ftLastWriteTime);
  
  if (theTime == -1)
    pstFdirEnt->mtimpres = SD_FALSE;
  else
    {
    pstFdirEnt->mtimpres = SD_TRUE;
    pstFdirEnt->mtime = (ST_INT32) theTime;
    }
  
  pstFdirEnt->num_of_fname = 1;

  /* Fill in nameBuffer.	*/
  strcpy (nameBuffer, pstFindData->cFileName);

  if (pstFindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    strcat (nameBuffer, "\\");
  
  /* Fill in the FILE_NAME struct.	*/
  pstFileName->fname = nameBuffer;
  pstFileName->fn_len = strlen (nameBuffer);
  }

/************************************************************************/
/*			 mvlas_fdir_resp				*/
/************************************************************************/

ST_VOID mvlas_fdir_resp (MVL_IND_PEND *indCtrl)
  {
ST_INT   status;
ST_CHAR  fs_name [MAX_FILE_NAME+1];
ST_CHAR  ca_name [MAX_FILE_NAME+1];
ST_INT   ca_len;
FDIR_RESP_INFO *rsp_ptr;
FDIR_DIR_ENT   *dir_ptr;
ST_INT rsp_size;
ST_CHAR    *name_ptr;
ST_INT  total_len, doMore;
FILE_NAME  *fname_ptr;
ST_UCHAR   found_ca = SD_FALSE;
ST_CHAR    *data_buf;
WIN32_FIND_DATA stFindData;
HANDLE  hFind;
MVLAS_FDIR_CTRL *fdir_ctrl;
ST_INT  negotiatedPduSize;
ST_INT  max_dir_ents;
ST_RET  rc;


  /* calculate the maximum message size and number of directory entries */
  negotiatedPduSize = (ST_INT) indCtrl->event->net_info->max_pdu_size;
  max_dir_ents = (negotiatedPduSize - SERVICE_OVRHD) / DIR_ENTRY_OVRHD;

  /* set the number of directory entries and allocate memory for response info */
  fdir_ctrl = &indCtrl->u.fdir;

  strcpy (fs_name, fdir_ctrl->fs_filename);
  strcpy (ca_name, fdir_ctrl->ca_filename);

  /* check if ca_filename is present */
  if ((ca_len = strlen (ca_name)) > 0)
    {
    /* strip off any '\' character at the end of file name */
    if (ca_len && ca_name[ca_len-1] == '\\')
      {
      ca_len--;                        
      ca_name[ca_len] = '\0';
      }
    }
  else
    found_ca = SD_TRUE;                   
  
  /*---------------------------------------------------------*/
  /* Find maximum response buffer size, calloc space for it, */
  /* and initialize the response structure variables.        */
  /*---------------------------------------------------------*/
  rsp_size = sizeof (FDIR_RESP_INFO) 
                + ( max_dir_ents * sizeof (FDIR_DIR_ENT) )
                + ( max_dir_ents * sizeof (FILE_NAME) );
  rsp_ptr  = (FDIR_RESP_INFO *) chk_calloc (1,rsp_size);

  /* Allocate buffer to hold just names. Will NEVER use whole buffer	*/
  /* because names plus overhead must be less than mms_max_msgsze.	*/
  data_buf = chk_malloc (negotiatedPduSize);

  rsp_ptr->num_dir_ent  = 0;
  rsp_ptr->more_follows = SD_FALSE;                        /* set default value    */

  /*---------------------------------*/
  /* Initialize some other variables */
  /*---------------------------------*/

  name_ptr = data_buf;
  total_len = 0;
  status = SD_SUCCESS;
  fname_ptr = ( FILE_NAME * )( fdir_ctrl + 1 );

  /* traverse the directory and stash output in the resp struct         */
  if ( status == SD_SUCCESS )
    {
    hFind = FindFirstFile (fs_name, &stFindData);
    
    if (hFind != INVALID_HANDLE_VALUE)
      {
      dir_ptr   = (FDIR_DIR_ENT *)(rsp_ptr + 1);
      fname_ptr = (FILE_NAME *)(dir_ptr + 1);
      doMore = SD_TRUE;
      
      while ( doMore )
        {
        if (!found_ca && (!stricmp (stFindData.cFileName, ca_name)) )
          found_ca = SD_TRUE;

        if (found_ca && (stricmp (stFindData.cFileName, ca_name)) )
          {
          /* Discard the . and .. entries                               */
          if (!strcmp (stFindData.cFileName, ".") || 
              !strcmp (stFindData.cFileName, ".."))
            {
            doMore = FindNextFile (hFind, &stFindData);
            continue;
            }

          /* see how big it would be and if it fits - keep it           */
          total_len += ( strlen(stFindData.cFileName) + DIR_ENTRY_OVRHD ); 
          
	  if (total_len < (negotiatedPduSize - SERVICE_OVRHD) ) 
            {
            rsp_ptr->num_dir_ent++;     
            fillFdirEnt (&stFindData, dir_ptr, fname_ptr, name_ptr);
            name_ptr += fname_ptr->fn_len + 1; /* check for end of buffer */
            dir_ptr =  (FDIR_DIR_ENT *) ((FILE_NAME *) (dir_ptr + 1) + 1);
            fname_ptr = (FILE_NAME *)(dir_ptr + 1);
              
            doMore = FindNextFile (hFind, &stFindData);
            }
          else                          /* message size limit           */
            {
            rsp_ptr->more_follows = SD_TRUE;
            doMore = SD_FALSE;
            }
          }
        else
          doMore = FindNextFile (hFind, &stFindData);
        }
      FindClose (hFind);
      }
    }

  if (status == SD_SUCCESS)                /* directory was successful     */
    {
    /* Build a File Directory response 					*/
    rc = mpl_fdir_resp (indCtrl->event->u.mms.dec_rslt.id, rsp_ptr);
    _mvl_send_resp_i (indCtrl, rc);
    }
/*------------------------*/
/* Free allocated storage */
/*------------------------*/

  chk_free (rsp_ptr);
  chk_free (data_buf);
  }

#endif /* if defined(_WIN32) */
