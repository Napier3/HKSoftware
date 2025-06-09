/*****************************************************************************/
/* SISCO SOFTWARE MODULE HEADER **********************************************/
/*****************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,            */
/*            2006 All Rights Reserved                                       */
/*                                                                           */
/* MODULE NAME : sfile.c                                                     */
/* PRODUCT(S)  : USPS support                                                */
/*                                                                           */
/* MODULE DESCRIPTION:                                                       */
/*   USPS directory access functions                                         */
/*                                                                           */
/* MODIFICATION LOG:                                                         */
/*   Date    Who  Rev  Comments                                              */
/* --------  ---  ---  ----------------------------------------------------- */
/* 10/13/06  RLH   01  Created                                               */
/*****************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "sfile.h"
#include <string.h>
#include <ctype.h>

#define S_FILE_DIR_CHAR_IS_SLASH(x)     (((x) == '/') || ((x) == '\\'))

#define S_FILE_DIR_CHAR_FAKE_SLASH_C    '<'
#define S_FILE_DIR_CHAR_FAKE_SLASH_S    "<"

#ifdef _WIN32
#define S_FILE_DIR_CHAR_NATIVE_SLASH_C  '\\'
#define S_FILE_DIR_CHAR_NATIVE_SLASH_S  "\\"

#define S_FILE_DIR_CHAR_OTHER_SLASH_C   '/'
#define S_FILE_DIR_CHAR_OTHER_SLASH_S   "/"

#else /* unix */
#define S_FILE_DIR_CHAR_NATIVE_SLASH_C  '/'
#define S_FILE_DIR_CHAR_NATIVE_SLASH_S  "/"

#define S_FILE_DIR_CHAR_OTHER_SLASH_C   '\\'
#define S_FILE_DIR_CHAR_OTHER_SLASH_S   "\\"

#endif

/* indicator to "highlight" a name as being a directory */
#define S_FILE_DIR_SLASH_SUFFIX         "/"


#ifdef __cplusplus
#define S_FILE_MEMORY_NEW(T)            new T
#define S_FILE_MEMORY_NEW_ARRAY(T,n)    new T[n]

#define S_FILE_MEMORY_DELETE(x)         {if (x != NULL) delete x; x = NULL;}
#define S_FILE_MEMORY_DELETE_ARRAY(x)   {if (x != NULL) delete[] x; x = NULL;}

#else

#define S_FILE_MEMORY_NEW(T)            (T *) malloc (sizeof (T))
#define S_FILE_MEMORY_NEW_ARRAY(T,n)    (T *) malloc (n * sizeof (T))

#define S_FILE_MEMORY_DELETE(x)         {if (x != NULL) free (x); x = NULL;}
#define S_FILE_MEMORY_DELETE_ARRAY(x)   {if (x != NULL) free (x); x = NULL;}

#endif


typedef struct
  {
  ST_CHAR                   searchPath [S_FILE_DIR_NAME_MAXLEN+1];
  ST_CHAR                   searchName [S_FILE_DIR_NAME_MAXLEN+1];
  ST_CHAR                   fileName   [S_FILE_DIR_NAME_MAXLEN+1];
  S_FILE_DIR_RESOURCE       resource;
  ST_BOOLEAN                firstDirReadDone;
  ST_BOOLEAN                isDir;
  ST_BOOLEAN                keepFileName;
  S_FILE_CONTEXT *          sFileContext;
  } S_FILE_DIR_REQ;


/*-***************************************************************************/
/*              fileTimeToTimeT                                              */
/*  used to convert FILETIME of files from FindFirstFile/FindNextFile to     */
/*  a time_t value.  Window only.                                            */
/*****************************************************************************/

#ifdef _WIN32

static time_t               fileTimeToTimeT (
  FILETIME                  gmt_ft)
  {
  FILETIME                  loc_ft;
  SYSTEMTIME                loc_st;
  struct tm                 loc_tm;
  time_t                    gmt_tm;


  FileTimeToLocalFileTime   (&gmt_ft, &loc_ft);
  FileTimeToSystemTime      (&loc_ft, &loc_st);

  loc_tm.tm_yday            = 0;
  loc_tm.tm_wday            = (int) loc_st.wDayOfWeek;
  loc_tm.tm_isdst           = -1;

  loc_tm.tm_year            = (int) loc_st.wYear  - 1900;
  loc_tm.tm_mon             = (int) loc_st.wMonth - 1;
  loc_tm.tm_mday            = (int) loc_st.wDay;
  loc_tm.tm_hour            = (int) loc_st.wHour;
  loc_tm.tm_min             = (int) loc_st.wMinute;
  loc_tm.tm_sec             = (int) loc_st.wSecond;

  gmt_tm = mktime (&loc_tm);

  return gmt_tm;

  } /* fileTimeToTimeT */

#endif


/*-***************************************************************************/
/*              sFileStrDup2                                                 */
/*  platform-neutral string duplicate                                        */
/*****************************************************************************/

static ST_CHAR *            sFileStrDup2 (
  const ST_CHAR *           str1,
  const ST_CHAR *           str2)
  {
  ST_CHAR *                 result;
  ST_ULONG                  len;

  if ((str1 == NULL) || (str2 == NULL))
    {
    /* error: null argument */
    return NULL;
    }

  len = strlen (str1) + strlen (str2) + 1;

  result = S_FILE_MEMORY_NEW_ARRAY (ST_CHAR, len);

  if (result == NULL)
    {
    /* error: allocation failure */
    return NULL;
    }

  strcpy (result, str1);
  strcat (result, str2);

  return result;

  } /* sFileStrDup2 */


/*-***************************************************************************/
/*              sFileStrDup                                                  */
/*  platform-neutral string duplicate                                        */
/*****************************************************************************/

static ST_CHAR *            sFileStrDup (
  const ST_CHAR *           str)
  {
  return sFileStrDup2 (str, "");

  } /* sFileStrDup */


/*-***************************************************************************/
/*              wildmatch                                                    */
/*  forward declaration                                                      */
/*****************************************************************************/


static ST_BOOLEAN           wildmatch (
  const ST_CHAR *           name,
  const ST_CHAR *           wild);


static ST_BOOLEAN           window_wild_tail (
  const ST_CHAR *           wild)
  {
  /* if a string consists only of *, ? and . return true */

  if (wild == NULL)
    {
    return SD_FALSE;
    }

  if (*wild == 0)
    {
    return SD_FALSE;
    }

  for (; *wild; wild++)
    {
    if ((*wild != '*') && (*wild != '?') && (*wild != '.'))
      {
      return SD_FALSE;
      }
    }

  return SD_TRUE;

  } /* window_wild_tail */


static ST_BOOLEAN           wildmatch_char (
  const ST_CHAR *           name,
  const ST_CHAR *           wild)
  {
  /* nothing matches against NULL */

  if ((name == NULL) || (wild == NULL))
    {
    return SD_FALSE;
    }

  if ((*name == 0) && (*wild == 0))
    {
    /* reached end of both strings - match found */
    return SD_TRUE;
    }

  /* if the name and pattern differ only by a trailing dot */
  /* then treat them as if equal.  example: */
  /* abc. == abc  and  abc == abc. */
  /* cases where there is an exact match are handled elsewhere */

  if ((*name == 0) && (wild[0] == '.') && (wild[1] == 0))
    {
    /* wild == name + '.' --> treat as match */
    return SD_TRUE;
    }

  if ((*wild == 0) && (name[0] == '.') && (name[1] == 0))
    {
    /* name == wild + '.' --> treat as match */
    return SD_TRUE;
    }

  if (*wild == '*')
    {

    /* if pattern ends in '*.*' or similar, treat like it's just '*' */

    if (window_wild_tail (wild+1))
      {
      return wildmatch_char (name, "*");
      }

    /* matching of '*' done as follows: */

    /*  skip over '*' in wild                                 */
    /*  attempt to match tail of wild with tail of name       */
    /*  if match found, return true                           */
    /*  if match not found, skip one char of name, and retry  */

    for (wild++; ; name++)
      {
      /* perform recursive match */
      if (wildmatch_char (name, wild))
        {
        return SD_TRUE;
        }

      if (*name == 0)         /* nothing to match against */
        {
        return SD_FALSE;
        }
      } /* for */

    } /* if '*' */

  if (*wild == '?')
    {
    /* '?' matches one char, which may not be the end of the string */

    if (*name == 0)         /* nothing to match against */
      {
      return SD_FALSE;
      }

    return wildmatch_char (name+1, wild+1);
    }

  /* if we have an explicit match on a dot, use it */

  if ((*name == '.') && (*wild == '.'))
    {
    return wildmatch_char (name+1, wild+1);
    }

  /* if pattern ends in '.*' or similar, treat like it's just '*' */

  if ((*wild == '.') && (window_wild_tail (wild+1)))
    {
    return wildmatch_char (name, "*");
    }

  /* if we have an explicit match on a non-wild char, continue match */

#ifdef _WIN32
  /* Win32 is case-insensitive for filename matches */
  if (toupper(*name) == toupper(*wild))
    {
    return wildmatch_char (name+1, wild+1);
    }

#else
  /* Unix/Linux is case-sensitive for filename matches */
  if (*name == *wild)
    {
    return wildmatch_char (name+1, wild+1);
    }
#endif

  /* name does not match wildcard pattern */
  return SD_FALSE;
  }


/*-***************************************************************************/
/*              wildmatch                                                    */
/*  a front-end to recursive wildcard match function wildmatch_char.         */
/*****************************************************************************/


static ST_BOOLEAN           wildmatch (
  const ST_CHAR *           name,
  const ST_CHAR *           wild)
  {
  return wildmatch_char (name, wild);

  } /* wildmatch */


/*-***************************************************************************/
/*              sFileIsDir                                                   */
/*  if name contains a wildcard pattern, return SD_TRUE, else SD_FALSE       */
/*****************************************************************************/


static ST_BOOLEAN           sFileIsDir (
  ST_CHAR *                 name)
  {
#ifdef _WIN32
#define STAT_NAME           _stat
#define STAT_DIR_FLAG       _S_IFDIR

#else
#define STAT_NAME           stat
#define STAT_DIR_FLAG       S_IFDIR

#endif

  struct STAT_NAME          buf;
  ST_CHAR                   workName   [S_FILE_DIR_NAME_MAXLEN+1];
  int                       len;


  if (name == NULL)
    {
    return SD_FALSE;        /* should not happen, just being careful */
    }

  strncpy (workName, name, S_FILE_DIR_NAME_MAXLEN);
  workName[S_FILE_DIR_NAME_MAXLEN] = 0;

  /* remove trailing slash if any, because stat may not like it */
  /* c:\ab\xy\# */
  /* 0123456789 */

  len = strlen(workName);

  if ( (len > 1)
  &&   (S_FILE_DIR_CHAR_IS_SLASH (workName[len-1])) )
    {
    workName[len-1] = 0;
    }

  if (STAT_NAME (workName, &buf) != 0)
    {
    /* cannot get attribute for name */
    return SD_FALSE;        /* assume stat failure == not a directory */
    }


  if (buf.st_mode & STAT_DIR_FLAG)
    {
    return SD_TRUE;         /* name is a directory */
    }

  return SD_FALSE;          /* name is not a directory */

#undef STAT_NAME
#undef STAT_DIR_FLAG

  } /* wildmatch */


/*-***************************************************************************/
/*              sFileHasPattern                                              */
/*  if name contains a wildcard pattern, return SD_TRUE, else SD_FALSE       */
/*****************************************************************************/


static ST_BOOLEAN           sFileHasPattern (
  ST_CHAR *                 name)
  {
  if (name == NULL)
    {
    return SD_FALSE;        /* should not happen, just being careful */
    }

  for (; *name; name++)
    {
    if ((*name == '*') || (*name == '?'))
      {
      return SD_TRUE;       /* name has a wildcard pattern */
      }

    } /* for */

  return SD_FALSE;          /* no pattern chars found */

  } /* sFileHasPattern */


/*-***************************************************************************/
/*              sNormalizeFileName                                           */
/*  convert filename delimitors to host default values                       */
/*****************************************************************************/


static ST_VOID              sNormalizeFileName (
  ST_CHAR *                 name)
  {
  if (name == NULL)
    {
    return;     /* should not happen, just being careful */
    }

  for (; *name; name++)
    {
    if (*name == S_FILE_DIR_CHAR_OTHER_SLASH_C)
      {
      *name = S_FILE_DIR_CHAR_NATIVE_SLASH_C;
      }

    } /* for */

  } /* sNormalizeFileName */


/*-***************************************************************************/
/*              sFileAllocContext                                            */
/*  return a pointer to an allocated S_FILE_CONTEXT, or NULL on failure      */
/*****************************************************************************/


S_FILE_CONTEXT *            sFileAllocContext ()
  {
  S_FILE_CONTEXT *          result;

  result = S_FILE_MEMORY_NEW (S_FILE_CONTEXT);

  if (result == NULL)
    {
    /* error: S_FILE_CONTEXT allocation failed */
    return NULL;
    }

  result->numDirs             = 0;
  result->numFiles            = 0;
  result->totalFileSize       = 0;
  result->numEntries          = 0;
  result->seekFileMatch       = 0;

  result->prevFileMatchName   = NULL;
  result->sFileDirEntryList   = NULL;
  result->sFileDirEntrySorted = NULL;
  result->lastEntryReturned   = NULL;

  result->sortedByName        = SD_FALSE;

  return result;

  } /* sFileAllocContext */


/*-***************************************************************************/
/*              sFileCloseDir                                                */
/*  close a directory resource, if currently allocated.                      */
/*****************************************************************************/


static ST_VOID              sFileCloseDir  (
  S_FILE_DIR_RESOURCE *     /*O*/ resource)
  {
  if (resource == NULL)
    {
    return;     /* should not happen, just being careful */
    }

  if (*resource != (S_FILE_DIR_RESOURCE) 0)
    {

#ifdef _WIN32
    if (FindClose (*resource) == 0)
      {
      /* error: FindClose API failed */
      }

#else
    if (closedir (*resource) != 0)
      {
      /* error: closedir API failed */
      }
#endif

    }

  *resource = (S_FILE_DIR_RESOURCE) 0;

  } /* sFileCloseDir */


/*-***************************************************************************/
/*              sFileFreeDirEntry                                            */
/*  free an allocated S_FILE_DIR_ENTRY struct. if the supplied pointer is    */
/*  NULL, omit the free operation for efficiency sake.                       */
/*****************************************************************************/


ST_VOID                     sFileFreeDirEntry (
  S_FILE_DIR_ENTRY *        /*O*/ sFileDirEntry)
  {
  if (sFileDirEntry != NULL)
    {
    /* if there is a filename string allocated, free it first */
    S_FILE_MEMORY_DELETE_ARRAY (sFileDirEntry->fileName);

    S_FILE_MEMORY_DELETE (sFileDirEntry);
    }

  } /* sFileFreeDirEntry */


/*-***************************************************************************/
/*              sFileFreeContext                                             */
/*  free an allocated S_FILE_CONTEXT struct.  if the supplied pointer is     */
/*  NULL, omit the free operation for efficiency sake.                       */
/*  if non-NULL pointers for sFileDirEntryList and/or sFileDirEntrySorted    */
/*  exist, free up the memory they occupy.                                   */
/*****************************************************************************/


ST_VOID                     sFileFreeContext (
  S_FILE_CONTEXT *          /*O*/ sFileContext)
  {
  if (sFileContext != NULL)
    {
    S_FILE_DIR_ENTRY *      curr;
    S_FILE_DIR_ENTRY *      next;

    curr = sFileContext->sFileDirEntryList;

    while (curr != NULL)
      {
      /* delete the list of allocated S_FILE_DIR_ENTRY structs */

      /* save next, since curr struct will be deleted */
      next = (S_FILE_DIR_ENTRY *)curr->l.next;

      sFileFreeDirEntry (curr);
      curr = next;
      }

    /* delete the array of S_FILE_DIR_ENTRY pointers */
    S_FILE_MEMORY_DELETE_ARRAY (sFileContext->sFileDirEntrySorted);

    S_FILE_MEMORY_DELETE (sFileContext);
    }

  } /* sFileFreeContext */


/*-***************************************************************************/
/*              sFileAllocDirEntry                                           */
/*  return a pointer to an allocated S_FILE_DIR_ENTRY, or NULL on failure    */
/*****************************************************************************/


S_FILE_DIR_ENTRY *          sFileAllocDirEntry ()
  {
  S_FILE_DIR_ENTRY *        result;


  result = S_FILE_MEMORY_NEW (S_FILE_DIR_ENTRY);

  if (result == NULL)
    {
    /* error: S_FILE_DIR_ENTRY allocation failed */
    return NULL;
    }

  result->l.prev              = NULL;
  result->l.next              = NULL;
  result->fileName            = NULL;
  result->fileTime            = 0;
  result->st_size             = 0;
  result->next                = NULL;

  return result;

  } /* sFileAllocDirEntry */


/*-***************************************************************************/
/*              sFileDirPathIsRoot                                           */
/*  determine if dirPath represent a Windows root directory                  */
/*  for unix systems, the function always returns SD_FALSE                   */
/*****************************************************************************/


static ST_BOOLEAN           sFileDirPathIsRoot (
  ST_CHAR *                 dirPath)
  {
#ifdef _WIN32
  if (dirPath == NULL)
    {
    return SD_FALSE;
    }

 /* a lone '.' will probably not work on Windows without an '*' pattern */
 /* we will treat '.' as if it were a root directory */
 /* we will get the same results as we would if '.' were accepted, */
 /* so this choice won't hurt anything */

 /* similar comments apply to '..' */

 if ((dirPath[0] == '.') && (dirPath[1] == 0))
    {
    return SD_TRUE;
    }

 if ((dirPath[0] == '.') && (dirPath[1] == '.') && (dirPath[2] == 0))
    {
    return SD_TRUE;
    }

  /* look for paths of the form C:\ */
  /*                            0123 */

  if ( (isalpha (dirPath[0]))
  &&   (dirPath[1] == ':')
  &&   (S_FILE_DIR_CHAR_IS_SLASH (dirPath[2]))
  &&   (dirPath[3] == 0) )
    {
    return SD_TRUE;
    }

  /* look for UNC names of the form \\machineName\shareName */

  if ( (S_FILE_DIR_CHAR_IS_SLASH (dirPath[0]))
  &&   (S_FILE_DIR_CHAR_IS_SLASH (dirPath[1])) )
    {
    /* dirPath might be a UNC name */

    ST_CHAR *               scan;
    ST_BOOLEAN              found;

    scan = dirPath+2;

    if (*scan == 0)
      {
      /* malformed UNC */
      return SD_FALSE;
      }

    if (S_FILE_DIR_CHAR_IS_SLASH (*scan))
      {
      /* malformed UNC */
      return SD_FALSE;
      }

    /* find end of machineName */

    found = SD_FALSE;

    for (; *scan; scan++)
      {
      if (*scan == 0)
        {
        /* malformed UNC */
        return SD_FALSE;
        }

      if (S_FILE_DIR_CHAR_IS_SLASH (*scan))
        {
        if (scan[1] == 0)
          {
          /* malformed UNC - looks like \\machineName\ with nothing after it */
          return SD_FALSE;
          }

        found = SD_TRUE;
        break;
        }

      } /* for */

    if (! found)
      {
      /* malformed UNC - no separator between machineName and shareName */
      return SD_FALSE;
      }

    /* find end of shareName */
    /* search above left 'scan' pointing to separator, need to skip over it */

    for (scan++; ; scan++)
      {
      if (*scan == 0)
        {
        /* end of string without another separator - must be a root name */
        return SD_TRUE;
        }

      if (S_FILE_DIR_CHAR_IS_SLASH (*scan))
        {
        break;
        }
      } /* for */

    if (scan[1] == 0)
      {
      /* if char after slash is nul, the path is a root */
      return SD_TRUE;
      }

    /* otherwise,  there is something following the sharename, */
    /* so is not a root */

    } /* if dirPath might be a UNC name */

  /* at this point, path does not look like a root */

  return SD_FALSE;

#else /* unix */
  /* unix is not bothered by root requests */
  return SD_FALSE;

#endif
  } /* sFileDirPathIsRoot */


/*-***************************************************************************/
/*              sFileDirSplitPath                                            */
/*  break apart a dirPath into a path prefix and a name.                     */
/*  if any parameter is NULL, or dirPath malformed, return SD_FAILURE.       */
/*  path and name sizes are assumed to be at least S_FILE_DIR_NAME_MAXLEN+1  */
/*****************************************************************************/


static ST_RET               sFileDirSplitPath (
  ST_CHAR *                 dirPath,
  ST_CHAR *                 path,
  ST_CHAR *                 name)
  {
  ST_LONG                   len;
  ST_LONG                   currlen;
  ST_LONG                   pathlen;
  ST_LONG                   wild;
  ST_CHAR *                 scan;


  if ((dirPath == NULL) || (path == NULL) || (name == NULL))
    {
    /* error: NULL argument[s] supplied */
    return SD_FAILURE;
    }

  path[0] = 0;
  name[0] = 0;

  len = strlen (dirPath);

  if ((len == 0) || (len > S_FILE_DIR_NAME_MAXLEN))
    {
    /* error: dirPath empty or too long */
    return SD_FAILURE;
    }


#ifdef _WIN32
  /* a lone drive letter like "C:" means "C:.\*" */
  /* in terms of FindFirstFile arguments */
  /* this is different from a "root" since we have to add "." to it */

  if ( (isalpha (dirPath[0]))
  &&   (dirPath[1] == ':')
  &&   (dirPath[2] == 0) )
    {
    strcpy (path, dirPath);
    strcat (path, ".");
    strcpy (name, "*");
    return SD_SUCCESS;
    }
#endif


  /* find last subdirectory separator char */
  /* if a wildcard char appears before a separator, the path is invalid */

  wild = 0;
  pathlen = -1;             /* default if path has no sep characters at all */

  for (scan = dirPath, currlen = 0;
      *scan;
       scan++,         currlen++)
    {
    if (S_FILE_DIR_CHAR_IS_SLASH (*scan))
      {
      pathlen = currlen;    /* len of path up to and including last sep */

      if (wild > 0)
        {
        /* error: wildcard char in dirPath is not supported     */

        /* example: in \abc*\def.* the * after 'abc' is invalid */
        /* that would imply searching multiple subdirectories,  */
        /* which cannot be easily supported in a portable way.  */

        return SD_FAILURE;
        }
      }

    else if ((*scan == '*') || (*scan == '?'))
      {
      wild++;
      }

    } /* for */

  if (pathlen == -1)
    {
    /* there were no file separator chars at all */

    /* if no separators but a ':' is present, we have a Windows name */
    /* like "C:abc.*" which is relative to the current directory on C: */
    /* this is the same as "C:.\abc.*".  we don't need to check for a */
    /* bare drive like "C:", since this was done earlier */

#ifdef _WIN32
    if (dirPath[1] == ':')
      {
      path[0] = dirPath[0];
      strcpy (path+1, ":.");
      strcpy (name, dirPath+2);
      return SD_SUCCESS;
      }
#endif

    /* the "path" is a simple filename or filename pattern, with no drive */
    /* letter.  we assume the path is '.' the current directory. */
    /* for Windows, we also assume the current drive, but we */
    /* don't have to specify anything to get that part of it. */

    strcpy (path, ".");         /* path is current directory */
    strcpy (name, dirPath);     /* entire dirPath is the name */
    return SD_SUCCESS;

    } /* if pathlen == -1 */

  /* dirPath contains one or more slashes */
  /* recall that pathlen is the index to where the last slash is */

  /* if dirPath is a lone slash, we have to convert to '\ *' or '/ *' */
  /* since logic elsewhere will put a slash between the path and name, */
  /* we will have to skip that part for lone-slash paths */
  /* we denote this condition by putting a "fake" root path of '<' */

  /* we later convert '<' to slash but don't put a slash between them */
  /* ---------------------------------------------------------------- */

  if ((len == 0) && (pathlen == 0))
    {
    path[0] = S_FILE_DIR_CHAR_FAKE_SLASH_C;
    path[1] = 0;
    strcpy (name, "*");
    return SD_SUCCESS;
    }

  /* if there were no wildcards, and path does not end in slash, */
  /* and name is a directory, we need to add an implied * for the name */

  if ( (wild == 0)
  &&   (dirPath[pathlen+1] != 0)
  &&   (sFileIsDir (dirPath)) )
    {
    strcpy (path, dirPath);
    strcpy (name, "*");
    return SD_SUCCESS;
    }

  if (pathlen == 0)
    {
    /* similar issue if dirPath one and only one slash at start of name */

    path[0] = S_FILE_DIR_CHAR_FAKE_SLASH_C;
    path[1] = 0;
    return SD_SUCCESS;
    }

  /* if it is a "root" name, we have to generate a default '*' pattern */

  if (sFileDirPathIsRoot (dirPath))
    {
    strncpy (path, dirPath, pathlen);
    path [pathlen] = 0;
    strcpy (name, "*");
    }

  /* if there were no wildcards, and path does end in slash, */
  /* and name is a directory, we need to add an implied * for the name */
  /* and chop off the trailing slash */

  if ( (wild == 0)
  &&   (dirPath[pathlen+1] == 0)
  &&   (sFileIsDir (dirPath)) )
    {
    strcpy (path, dirPath);
    path [pathlen] = 0;
    strcpy (name, "*");
    return SD_SUCCESS;
    }

  else
    {
    strncpy (path, dirPath, pathlen);
    path [pathlen] = 0;
    strcpy (name, dirPath + pathlen + 1);
    }

  return SD_SUCCESS;

  } /* sFileDirSplitPath */


/*-***************************************************************************/
/*              sFileSetDefaultDirPath                                       */
/*  if dirPath is NULL or only contains spaces, treat as equivalent to       */
/*  an '*' pattern, otherwise use as-is.                                     */
/*****************************************************************************/


static ST_CHAR *            sFileSetDefaultDirPath (
  ST_CHAR *                 /*I*/  dirPath)
  {
  ST_CHAR *                 scan;

  if (dirPath == NULL)
    {
    return "*";
    }

  for (scan = dirPath; *scan; scan++)
    {
    if (! isspace (*scan))
      {
      /* dirPath contains a non-blank char, so use it as-is */

      return dirPath;
      }
    }

  /* dirPath contains only whitespace */

  return "*";

  } /* sFileSetDefaultDirPath */


/*-***************************************************************************/
/*              sFileDirGetInit                                              */
/*  initialize a S_FILE_DIR_REQ to prepare for reading a directory.          */
/*  on NULL parameters or malformed arguments, return SD_FAILURE.            */
/*****************************************************************************/


static ST_RET               sFileDirGetInit (
  S_FILE_CONTEXT *          /*IO*/ sFileContext,
  ST_CHAR *                 /*I*/  dirPath,
  S_FILE_DIR_REQ *          /*IO*/ dirReq)
  {

  if ((sFileContext == NULL) || (dirPath == NULL) || (dirReq == NULL))
    {
    /* error: NULL parameters supplied */
    return SD_FAILURE;
    }

  /* ensure current dir resource is closed before opening another one */
  sFileCloseDir (&dirReq->resource);

  dirReq->searchPath[0] = 0;
  dirReq->searchName[0] = 0;
  dirReq->fileName[0]   = 0;
  dirReq->firstDirReadDone = SD_FALSE;
  dirReq->sFileContext  = sFileContext;

  if (sFileDirSplitPath (
        dirPath, dirReq->searchPath, dirReq->searchName) != SD_SUCCESS)
    {
    /* error: dirPath is NULL or invalid */
    return SD_FAILURE;
    }

  /* fix slashes if needed */
  sNormalizeFileName (dirReq->searchPath);
  sNormalizeFileName (dirReq->searchName);

  return SD_SUCCESS;

  } /* sFileDirGetInit */


/*-***************************************************************************/
/*              sFileDirGetNext                                              */
/*  based on an initialized S_FILE_DIR_REQ struct, get the next file name    */
/*  in the directory.  return SD_TRUE if successful, else SD_FALSE.          */
/*  when read is successful, fill in the S_FILE_DIR_ENTRY.                   */
/*****************************************************************************/


static ST_BOOLEAN           sFileDirGetNext (
  S_FILE_DIR_REQ *          /*IO*/ dirReq,
  S_FILE_DIR_ENTRY *        /*O*/  dirEntry)
  {
  ST_CHAR                   fullPath [S_FILE_DIR_NAME_MAXLEN+2];
  S_FILE_DIR_RESOURCE       resource;

#ifdef _WIN32
  WIN32_FIND_DATA           winFindData;
#else
  struct dirent *           unixDirEnt;
  struct stat               unixStatBuf;
#endif

  if ((dirReq == NULL) || (dirEntry == NULL))
    {
    /* error: dirReq or dirEntry argument is NULL*/
    return SD_FALSE;        /* should not occur, just being careful */
    }

#ifdef _WIN32 /* windows FindFirstFile / FindNextFile */

  for (;;)  /* retry may be needed to skip '.' and '..' entries */
    {
    if (dirReq->firstDirReadDone == SD_FALSE)
      {
      /* first time reading from directory */

      /* create the fullPath. the dirPath has already been properly split */
      /* and dummy * names created if needed.  we now have to glue it all */
      /* together, and if we have a path of S_FILE_DIR_CHAR_FAKE_SLASH_C, */
      /* there is an initial backslash, but no backslash between them.  */

      if (dirReq->searchPath[0] == S_FILE_DIR_CHAR_FAKE_SLASH_C)
        {
        strcpy (fullPath, S_FILE_DIR_CHAR_NATIVE_SLASH_S);
        }

      else
        {
        strcpy (fullPath, dirReq->searchPath);
        strcat (fullPath, S_FILE_DIR_CHAR_NATIVE_SLASH_S);
        }

      strcat (fullPath, dirReq->searchName);

      resource = FindFirstFile (fullPath, &winFindData);

      if (resource == INVALID_HANDLE_VALUE)
        {
        return SD_FALSE;      /* error, or more likely, no files in directory */
        }

      dirReq->resource = resource;  /* save handle for next */

      } /* first time  reading from directory */

    else
      {
      /* subsequent time reading from directory */

      /* assume that the dirReq is valid from the initial read */

      if (! FindNextFile (dirReq->resource, &winFindData))
        {
        /* error, or more likely, reached the end of the directory */
        /* assuming at end of directory, close the resource */

        sFileCloseDir (&dirReq->resource);
        return SD_FALSE;
        }

      } /* subsequent time reading from directory */

    dirReq->firstDirReadDone = SD_TRUE;   /* call FindNextFile next time */

    /* hidden or system files are not of interest to us */

    if (winFindData.dwFileAttributes &
          (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM))
      {
      continue;
      }

    /* the windows FindFirstFile/FindNextFile API integrates wildcard */
    /* matching.  if we got a successful return, the file in question */
    /* matches the filename pattern. */

    /* fill in the dirEntry from winFindData. */

    /* create a copy of the file name if the request asked for it */
    /* otherwise set to NULL.  this is done mainly for the sake of */
    /* retrieving stats, when the name is not needed. */

    /* winFindData.cFileName is the file name, not the full path name */
    /* if the file name is '.' or '..', reject it */

    if ( (strcmp (winFindData.cFileName, ".")  == 0)
    ||   (strcmp (winFindData.cFileName, "..") == 0) )
      {
      dirReq->firstDirReadDone = SD_TRUE;   /* call FindNextFile next time */
      continue;     /* ignore '.'  and '..' names */
      }

    dirEntry->fileTime = fileTimeToTimeT (winFindData.ftLastWriteTime);

    /* for directory entries, set isDir in dirReq.  in case file is very */
    /* large, set to max int size of 0x7FFFFFFF, otherwise store true size. */

    if (winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
      dirReq->isDir = SD_TRUE;
      dirEntry->st_size = 0;
      }

    else /* not directory */
      {
      dirReq->isDir = SD_FALSE;

      if ( (winFindData.nFileSizeHigh != 0)
      ||   ((ST_LONG) winFindData.nFileSizeLow < 0) )
        {
        /* file is big; cannot store true size, so we will fake it */
        dirEntry->st_size = 0x7FFFFFFF;
        }

      else
        {
        /* store true size */
        dirEntry->st_size = (ST_LONG) winFindData.nFileSizeLow;
        }

      } /* not directory */

    if (dirReq->keepFileName)
      {
      if (dirReq->isDir)
        {
        /* add slash as suffix to directory name */
        dirEntry->fileName =
            sFileStrDup2 (winFindData.cFileName, S_FILE_DIR_SLASH_SUFFIX);
        }

      else
        {
        dirEntry->fileName = sFileStrDup (winFindData.cFileName);
        }
      }

    else
      {
      dirEntry->fileName = NULL;
      }

    return SD_TRUE;

    } /* for */

#else /* unix readdir() */

  if (dirReq->firstDirReadDone == SD_FALSE)
    {
    /* first time reading from directory */
    /* on unix, we must read from the directory and do our own wildcard */
    /* matching. opendir references the directory but not the file name. */

    resource = opendir (dirReq->searchPath);

    if (resource == NULL)
      {
      return SD_FALSE;      /* error, or more likely, no files in directory */
      }

    dirReq->resource = resource;  /* save handle for next */

    } /* first time  reading from directory */

  dirReq->firstDirReadDone = SD_TRUE;

  /* because we do our own wildcard matching, we have to reject file names */
  /* that do not match.  we also reject "." and ".." file names, which the */
  /* unix API returns. */

  for (;;)
    {
    /* assume that the dirReq is valid from the initial read */

    unixDirEnt = readdir (dirReq->resource);

    if (unixDirEnt == NULL)
      {
      /* error, or more likely, reached the end of the directory */
      /* assuming at end of directory, close the resource */

      sFileCloseDir (&dirReq->resource);
      return SD_FALSE;
      }

    if ( (strcmp (unixDirEnt->d_name, "." ) == 0)
    ||   (strcmp (unixDirEnt->d_name, "..") == 0) )
      {
      /* reject . and .. entries */
      continue;
      }

    if (! wildmatch (unixDirEnt->d_name, dirReq->searchName))
      {
      /* not the file we are looking for */
      continue;
      }

    /* to get a fully-qualified name, we have to concatenate the */
    /* directory and returned file name, with a slash between. */

    strcpy (fullPath, dirReq->searchPath);
    strcat (fullPath, S_FILE_DIR_CHAR_NATIVE_SLASH_S);
    strcat (fullPath, unixDirEnt->d_name);

    /* readdir only gives us the name, so we have to */
    /* get attributes from stat(). */

    if (stat (fullPath, &unixStatBuf) != 0)
      {
      /* cannot get attribute for current file - skip this one */
      continue;
      }

    break;      /* accept current file name */

    } /* for */

  /* fill in the dirEntry */

  dirEntry->fileTime = unixStatBuf.st_mtime;

  if (unixStatBuf.st_mode & S_IFDIR)
    {
    dirReq->isDir = SD_TRUE;
    dirEntry->st_size = 0;
    }

  else /* not directory */
    {
    dirReq->isDir = SD_FALSE;
    dirEntry->st_size  = unixStatBuf.st_size;
    }

  /* create a copy of the file name if the request asked for it */
  /* otherwise set to NULL.  this is done mainly for the sake of */
  /* retrieving stats, when the name is not needed. */

  if (dirReq->keepFileName)
    {
    if (dirReq->isDir)
      {
      /* add slash as suffix to directory name */
      dirEntry->fileName =
          sFileStrDup2 (unixDirEnt->d_name, S_FILE_DIR_SLASH_SUFFIX);
      }

    else
      {
      dirEntry->fileName = sFileStrDup (unixDirEnt->d_name);
      }
    }

  else
    {
    dirEntry->fileName = NULL;
    }

  return SD_TRUE;

#endif

  } /* sFileDirGetInit */


/*-***************************************************************************/
/*              sFileDirGetStats                                             */
/*  obtain statistics for the given directory path and store in the supplied */
/*  context.  when statistics are successfully fetched, return SD_SUCCESS,   */
/*  even if the number of files found is 0.                                  */
/*  on NULL parameters or malformed dirPath, return SD_FAILURE.              */
/*****************************************************************************/


ST_RET                      sFileDirGetStats (
  S_FILE_CONTEXT *          /*O*/ sFileContext,
  ST_CHAR *                 /*I*/ dirPath)
  {
  S_FILE_DIR_REQ            dirReq   = {0};
  S_FILE_DIR_ENTRY          dirEntry = {0};


  /* check for NULL or blank dirPath */
  dirPath = sFileSetDefaultDirPath (dirPath);

  if (sFileDirGetInit (sFileContext, dirPath, &dirReq) == SD_FAILURE)
    {
    /* error: bad parameters, or unable to initiate directory request */
    return SD_FAILURE;
    }

  sFileContext->numDirs       = 0;
  sFileContext->numFiles      = 0;
  sFileContext->totalFileSize = 0;

  /* don't alloc memory for returned filenames, because we don't need them */
  dirReq.keepFileName = SD_FALSE;

  while (sFileDirGetNext (&dirReq, &dirEntry))
    {
    if (dirReq.isDir)
      {
      sFileContext->numDirs++;
      }

    else
      {
      sFileContext->numFiles++;
      sFileContext->totalFileSize += dirEntry.st_size;
      }
    }

  return SD_SUCCESS;

  } /* sFileDirGetStats */


/*-***************************************************************************/
/*              sFileGetDirList                                              */
/*  obtain a list of file names, and store into a linked list of             */
/*  S_FILE_DIR_ENTRY nodes.  we also compute the stats.                      */
/*****************************************************************************/


ST_RET                      sFileGetDirList (
  S_FILE_CONTEXT *          /*O*/ sFileContext,
  ST_CHAR *                 /*I*/ dirPath)
  {
  S_FILE_DIR_REQ            dirReq   = {0};
  S_FILE_DIR_ENTRY          dirEntry = {0};
  S_FILE_DIR_ENTRY *        currDirEntry = NULL;
  S_FILE_DIR_ENTRY *        nextDirEntry = NULL;


  /* check for NULL or blank dirPath */
  dirPath = sFileSetDefaultDirPath (dirPath);

  if (sFileDirGetInit (sFileContext, dirPath, &dirReq) == SD_FAILURE)
    {
    /* error: bad parameters, or unable to initiate directory request */
    return SD_FAILURE;
    }

  sFileContext->numDirs       = 0;
  sFileContext->numFiles      = 0;
  sFileContext->totalFileSize = 0;
  sFileContext->numEntries    = 0;

  /* alloc and return filename strings */
  dirReq.keepFileName = SD_TRUE;

  while (sFileDirGetNext (&dirReq, &dirEntry))
    {
    sFileContext->numEntries++;

    /* accumulate stats */
    if (dirReq.isDir)
      {
      sFileContext->numDirs++;
      }

    else
      {
      sFileContext->numFiles++;
      sFileContext->totalFileSize += dirEntry.st_size;
      }

    /* add directory to list */
    /* reuse any existing S_FILE_DIR_ENTRY nodes in the chain. */
    /* allocate more if needed, and discard extra ones at the end */
    /* if sFileDirEntryList is NULL, we create an initial S_FILE_DIR_ENTRY */

    if (sFileContext->sFileDirEntryList == NULL)
      {
      sFileContext->sFileDirEntryList = sFileAllocDirEntry ();

      if (sFileContext->sFileDirEntryList == NULL)
        {
        /* error: could not allocate initial S_FILE_DIR_ENTRY */
        return SD_FAILURE;
        }

      } /* sFileDirEntryList is NULL */

    /* first time through, use first (or only) S_FILE_DIR_ENTRY node */
    /* pointed-to by the context.  on subsequent passes, get 'next' node */
    /* if any, otherwise allocate a new one. */

    if (currDirEntry == NULL)
      {
      currDirEntry = sFileContext->sFileDirEntryList;
      nextDirEntry = (S_FILE_DIR_ENTRY *) currDirEntry->l.next;
      }

    else
      {
      /* not first file; find next node from curr one */
      nextDirEntry = (S_FILE_DIR_ENTRY *) currDirEntry->l.next;

      if (nextDirEntry == NULL)
        {
        /* there is no 'next' node, so allocate a new one */

        nextDirEntry = sFileAllocDirEntry ();

        if (nextDirEntry == NULL)
          {
          /* error: could not allocate subsequent S_FILE_DIR_ENTRY */
          return SD_FAILURE;
          }

        /* link the new node to the old one */

        currDirEntry->l.next = (DBL_LNK *) nextDirEntry;
        nextDirEntry->l.prev = (DBL_LNK *) currDirEntry;

        /* the newly allocated node is now the 'current' one */

        currDirEntry = nextDirEntry;

        /* currDirEntry is 'last' one, so there is no 'next' node */
        nextDirEntry = NULL;

        } /* nextDirEntry == NULL */


      else /* nextDirEntry != NULL */
        {
        /* 'next' node from prior iteration becomes the new 'curr' node */
        currDirEntry = nextDirEntry;
        nextDirEntry = (S_FILE_DIR_ENTRY *) currDirEntry->l.next;
        }

      } /* not first file */

    /* copy S_FILE_DIR_ENTRY values from local struct to the allocated node */

    currDirEntry->fileName = dirEntry.fileName;
    currDirEntry->fileTime = dirEntry.fileTime;
    currDirEntry->st_size  = dirEntry.st_size;

    } /* while */

  /* after all names were returned, chop off the last node */
  /* we only do this if there were any nodes in the first place */
  /* there will be no nodes at all if sFileDirGetNext() returned nothing */

  if (currDirEntry != NULL)
    {
    currDirEntry->l.next = NULL;
    }

  /* delete any trailing nodes */
  /* if sFileDirGetNext() returned nothing, then nextDirEntry = NULL */
  /* and the for loop will not execute */

  for (currDirEntry = nextDirEntry;
       currDirEntry != NULL;
       currDirEntry = nextDirEntry)
    {
    /* save 'next' pointer, since 'curr' node will be deleted */
    nextDirEntry = (S_FILE_DIR_ENTRY *) currDirEntry->l.next;

    sFileFreeDirEntry (currDirEntry);
    }

  return SD_SUCCESS;

  } /* sFileGetDirList */


/*-***************************************************************************/
/*              sFileNameCompare                                             */
/*  compare the fileName's within S_FILE_DIR_ENTRY nodes.                    */
/*  on Windows, compare using _stricmp, else strcmp                          */
/*****************************************************************************/


static ST_INT               sFileNameCompare (
  const S_FILE_DIR_ENTRY ** /*I*/ one,
  const S_FILE_DIR_ENTRY ** /*I*/ two)
  {
  ST_INT                    result;
  ST_CHAR *                 p_one;
  ST_CHAR *                 p_two;
  ST_CHAR                   c_one;
  ST_CHAR                   c_two;


  /* to handle cases of NULL pointers, treat as equal compare */

  if ((one == NULL) || (two == NULL))
    {
    return 0;
    }

  if ((*one == NULL) || (*two == NULL))
    {
    return 0;
    }

  p_one = (*one)->fileName;
  p_two = (*two)->fileName;

  for (;; p_one++, p_two++)
    {
#ifdef _WIN32
    c_one = tolower (*p_one);
    c_two = tolower (*p_two);
#else
    c_one = *p_one;
    c_two = *p_two;
#endif

    if ( (S_FILE_DIR_CHAR_IS_SLASH (c_one))
    &&   (p_one[1] == 0) )
      {
      /* string one ends in a slash */
      c_one = 0;
      }

    if ( (S_FILE_DIR_CHAR_IS_SLASH (c_two))
    &&   (p_two[1] == 0) )
      {
      /* string two ends in a slash */
      c_two = 0;
      }

    if (c_one == c_two)
      {
      if (c_one != 0) continue; /* more to compare */
      return 0;                 /* strings are identical */
      }

    result = c_one - c_two;     /* form comparison value */
    break;

    } /* for */

  return result;

  } /* sFileNameCompare */


/*-***************************************************************************/
/*              sFileSortByName                                              */
/*  create a sort-table of pointers to S_FILE_DIR_ENTRY's based on filename. */
/*  use the sort-table to thread the S_FILE_DIR_ENTRY's in sorted order.     */
/*  case sensitivity of the sort is platform dependent.                      */
/*  no sort table is created if number of files is 0 or 1.                   */
/*  return SD_SUCCESS or SD_FAILURE depending on outcome.                    */
/*****************************************************************************/


ST_RET                      sFileSortByName (
  S_FILE_CONTEXT *          /*O*/ sFileContext)
  {
  ST_LONG                   n;
  ST_LONG                   numEntries = 0;
  S_FILE_DIR_ENTRY *        curr_entry;
  S_FILE_DIR_ENTRY *        next_entry;

  if (sFileContext == NULL)
    {
    /* error: null parameter */
    return SD_FAILURE;
    }

  /* success of sort is uncertain at first; a sort-table may not be created */

  sFileContext->sortedByName = SD_FALSE;

  /* a (possible) change in sort order invalidates any prior seek point */
  sFileContext->seekFileMatch = 0;
  S_FILE_MEMORY_DELETE_ARRAY (sFileContext->prevFileMatchName);

  /* delete any prior sort-table */
  S_FILE_MEMORY_DELETE_ARRAY (sFileContext->sFileDirEntrySorted);

  /* re-establish numEntries, and clear out any old sorted-next pointers */

  for (curr_entry = sFileContext->sFileDirEntryList;
       curr_entry != NULL;
       curr_entry = (S_FILE_DIR_ENTRY *) curr_entry->l.next)
    {
    curr_entry->next = NULL;
    numEntries++;
    }

  sFileContext->numEntries = numEntries;

  if (numEntries < 1)
    {
    /* it is not an error to request a sort of 0 entries */
    return SD_SUCCESS;
    }

  /* allocate new sort table */

  sFileContext->sFileDirEntrySorted =
    S_FILE_MEMORY_NEW_ARRAY (P_S_FILE_DIR_ENTRY, numEntries);
  /* fill-in sort-table by traversing the list a second time */

  n = 0;

  for (curr_entry = sFileContext->sFileDirEntryList;
       curr_entry != NULL;
       curr_entry = (S_FILE_DIR_ENTRY *) curr_entry->l.next)
    {
    if (n >= numEntries)
      {
      /* error: mismatch in first vs. second pass on list, should not occur */
      return SD_FAILURE;
      }

    sFileContext->sFileDirEntrySorted[n++] = curr_entry;
    }

  /* there is no need to sort a list of length 1 */
  /* but if there is only one, leave the 1 item in the list and exit */

  if (numEntries == 1)
    {
    return SD_SUCCESS;
    }

  /* sort the sort-table */

  qsort (
    sFileContext->sFileDirEntrySorted,      /* void *base */
    (size_t) numEntries,                    /* size_t num */
    sizeof (P_S_FILE_DIR_ENTRY),            /* size_t width */
    (int (*) (const void*, const void*)) sFileNameCompare);

  /* chain together the sorted links in the dir entries, so a user can */
  /* traverse the entries in sorted order without needing the sort table */

  for (n = 0; n < numEntries-1; n++)
    {
    curr_entry = sFileContext->sFileDirEntrySorted[n];
    next_entry = sFileContext->sFileDirEntrySorted[n+1];

    curr_entry->next = next_entry;
    next_entry->next = NULL;    /* ensure final entry's next is NULL */
    }

  sFileContext->sortedByName = SD_TRUE;

  return SD_SUCCESS;

  } /* sFileSortByName */


/*-***************************************************************************/
/*              sFileFindDirEntry                                            */
/*  if fileName is a wildcard pattern, and seekFileMatch > 0, return the     */
/*  n'th file which matches the pattern, where n = seekFileMatch.  if the    */
/*  value of seekFileMatch is <= 0, the first matching name is returned.     */
/*  if fileName is not a wildcard pattern, return the first matching entry.  */
/*  if the same pattern is                                                   */
/*                                                                           */
/*  in either case, if no match is found (or possible) return NULL.          */
/*  if the list has been sorted, it is searched in sorted order, else in     */
/*  unsorted order.  if the list has been sorted and the name in question    */
/*  is not a wildcard, use bsearch to find it faster.                        */
/*                                                                           */
/*  if fileName is fully-qualified, only use the base (unqualified name).    */
/*  it is an error to provide a fileName ending in a slash, and this will    */
/*  result in a NULL return value.                                           */
/*                                                                           */
/*****************************************************************************/


S_FILE_DIR_ENTRY *          sFileFindDirEntry (
  S_FILE_CONTEXT *          /*I*/ sFileContext,
  ST_CHAR *                 /*I*/ qualFileName)
  {
  ST_BOOLEAN                hasPattern;
  ST_BOOLEAN                sortTableExists = SD_FALSE;
  ST_LONG                   currFileMatch = 0;
  ST_LONG                   seekFileMatch = 0;
  ST_LONG                   fileNameOffset = 0;
  ST_LONG                   i;
  S_FILE_DIR_ENTRY *        curr_entry;
  S_FILE_DIR_ENTRY *        next_entry;
  S_FILE_DIR_ENTRY          work_entry = {0};
  S_FILE_DIR_ENTRY *        p_work_entry;
  S_FILE_DIR_ENTRY **       pp_dir_entry;
  ST_CHAR *                 fileName;   /* unqualified file name */


  sFileContext->lastEntryReturned = NULL;

  if ((sFileContext == NULL)
  ||  (qualFileName == NULL))
    {
    /* error: null parameters */
    return NULL;
    }

  if ((sFileContext->numEntries == 0)
  ||  (sFileContext->sFileDirEntryList == NULL))
    {
    /* normal: no data found */
    return NULL;
    }

  /* if qualFileName is qualified, find offset to unqualified part */
  /* the unqualified part is after the last slash.  if the name has */
  /* a trailing slash, it is a directory name */

  for (i = 0; qualFileName[i]; i++)
    {
    if (S_FILE_DIR_CHAR_IS_SLASH (qualFileName[i]))
      {
      if (qualFileName[i+1] == 0)
        {
        /* allow a trailing slash for a directory name */
        break;
        }

      fileNameOffset = i + 1;
      }
    }

  fileName = qualFileName + fileNameOffset;

  if ( (sFileContext->sortedByName)
  &&   (sFileContext->numEntries > 0) )
    {
    if ((sFileContext->sFileDirEntrySorted) != NULL)
      {
      /* a sort-table exists */

      if (*(sFileContext->sFileDirEntrySorted) != NULL)
        {
        /* first entry of sort-table is valid */
        sortTableExists = SD_TRUE;
        }
      }
    }

  hasPattern = sFileHasPattern (fileName + fileNameOffset);

  /* if the supplied file name is a pattern, and the context contains a */
  /* positive seekFileMatch, we are looking for a specific name in the */
  /* list, otherwise we are looking for the first match. */

  /* if no pattern is supplied, the seekFileMatch is ignored. */
  /* if there was a prior sort of the list, use bsearch to find the name */

  if (! hasPattern)
    {
    /* a prior pattern match is ended by a non-pattern match */
    sFileContext->seekFileMatch = 0;
    S_FILE_MEMORY_DELETE_ARRAY (sFileContext->prevFileMatchName);

    if (sortTableExists)
      {
      /* use bsearch to find the name thru the sort table */
      /* recall the sort table is a table of node ptrs, not string ptrs */
      /* since the compare routine takes S_FILE_DIR_ENTRY values, we */
      /* have to store the fileName in a dummy S_FILE_DIR_ENTRY struct */
      /* so the compare will work properly. */

      work_entry.fileName = fileName;
      p_work_entry = &work_entry;

      pp_dir_entry = (S_FILE_DIR_ENTRY **) bsearch (
          &p_work_entry,                          /* key */
          sFileContext->sFileDirEntrySorted,      /* void *base */
          (size_t) sFileContext->numEntries,      /* size_t num */
          sizeof (P_S_FILE_DIR_ENTRY),            /* size_t width */
          (int (*) (const void*, const void*)) sFileNameCompare);

      if (pp_dir_entry == NULL)
        {
        return NULL;            /* fileName not found */
        }

      return *pp_dir_entry;     /* pointer to an S_FILE_DIR_ENTRY */
      }
    }

  /* note that this support for "successive matching" is done ONLY if the */
  /* sFileContext->seekFileMatch > 0, which is its default value.  the user */
  /* has to set this field, otherwise we always return the first match. */

  if (hasPattern && (sFileContext->seekFileMatch > 0))
    {
    /* if there was a prior pattern match, but the pattern changed, */
    /* the match sequence starts over */
    /* in order to resume the search, the pattern must match exactly */
    /* even on Windows with case-insensitive names */

    if (sFileContext->prevFileMatchName != NULL)
      {
      if (strcmp (fileName, sFileContext->prevFileMatchName) != 0)
        {
        /* names don't match - fileName starts a new match */
        /* we will start by looking for the 1st match */

        sFileContext->seekFileMatch = 1;
        S_FILE_MEMORY_DELETE_ARRAY (sFileContext->prevFileMatchName);
        sFileContext->prevFileMatchName = sFileStrDup (fileName);
        }
      }

    /* seekFileMatch holds the n'th "match", not the n'th file */
    seekFileMatch = sFileContext->seekFileMatch;
    }

  else
    {
    /* a prior pattern match is ended by a non-pattern match */
    sFileContext->seekFileMatch = 0;
    S_FILE_MEMORY_DELETE_ARRAY (sFileContext->prevFileMatchName);
    }

  /* if it appears we can follow a sorted list of directory entry links, */
  /* use them, otherwise we follow the unsorted link */

  curr_entry = sFileContext->sFileDirEntryList;

  if (sortTableExists)
    {
    curr_entry = *(sFileContext->sFileDirEntrySorted);
    }

  for (next_entry = NULL;               /* precautionary assignment */
       curr_entry != NULL;
       curr_entry = next_entry)
    {
    /* choose 'next' link to follow */

    if (sortTableExists)
      {
      next_entry = curr_entry->next;    /* sorted link */
      }

    else
      {
      /* get next physical (unsorted) link */
      next_entry = (S_FILE_DIR_ENTRY *) curr_entry->l.next;
      }

    if (wildmatch (curr_entry->fileName, fileName))
      {
      /* the file name matched.  if we are not looking for a specific */
      /* match, return this one, otherwise return this one if it's the */
      /* n'th one we want. */

      currFileMatch++;                  /* count number of matches */

      if (seekFileMatch == 0)
        {
        sFileContext->lastEntryReturned = curr_entry;
        return curr_entry;
        }

      if ((seekFileMatch > 0)
      &&  (seekFileMatch == currFileMatch))
        {
        /* update the context's seekFileMatch, so we can get the next */
        /* one (if one exists) the next time this function is called */

        sFileContext->seekFileMatch = seekFileMatch + 1;
        sFileContext->lastEntryReturned = curr_entry;

        /* if this is the first time we got a match, store a copy of the */
        /* search name */

        if ( hasPattern
        &&   (sFileContext->seekFileMatch > 0)
        &&   (sFileContext->seekFileMatch > 0)
        &&   (sFileContext->prevFileMatchName == NULL) )
          {
          sFileContext->prevFileMatchName = sFileStrDup (fileName);
          }

        return curr_entry;
        }
      }

      /* if no match, keep looking */

    } /* for */

  return NULL;  /* no match found */

  } /* sFileFindDirEntry */

