/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*	(c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*	1999 All Rights Reserved					*/
/*									*/
/* MODULE NAME : clnp_thr.c						*/
/* PRODUCT(S)  : Lean-T Stack						*/
/*									*/
/* MODULE DESCRIPTION :							*/
/*	Functions to allow multithreading CLNP. It allows reading	*/
/*	from multiple threads and/or writing from multiple threads.	*/
/*	   For reading, the user must call "clnp_read_thread_start"	*/
/*	which creates a thread that calls "clnp_read" to get packets,	*/
/*	and then puts them on 2 linked lists. The upper layers then	*/
/*	call "clnp_read_main" or "clnp_read_goose" to get the packets	*/
/*	from the appropriate linked list.				*/
/*	   For writing, the user doesn't need to do anything. However,	*/
/*	it is essential that "clnp_usr.c" is compiled with S_MT_SUPPORT	*/
/*	defined. This causes "clnp_write" to get the mutex semaphore.	*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*			clnp_read_thread_start				*/
/*			clnp_read_main					*/
/*			clnp_read_goose					*/
/*									*/
/* WARNING: If this module is used, the "s_log" library must be		*/
/*	compiled with "S_MT_SUPPORT" defined, because it causes		*/
/*	logging from multiple threads.					*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev     Comments					*/
/* --------  ---  ------   -------------------------------------------  */
/* 02/28/02  JRB    08     Don't use DWORD. Chg INFINITE to LONG_MAX.	*/
/*			   Skip gs_init call (not needed for event sems)*/
/* 12/13/00  DWL    07     Added SD_FALSE param to gs_get_event_sem	*/
/* 04/06/00  JRB    06     Use WaitFor..Ex for WIN32. CRITICAL.		*/
/* 08/05/99  JRB    05     Del "clnp...running". Use funct ptrs instead.*/
/* 08/02/99  JRB    04     Check for empty linked list.			*/
/* 08/02/99  JRB    03     Move some globals to clnp_usr.c		*/
/* 08/02/99  JRB    02     Use glbsem functs so this module is portable.*/
/* 07/30/99  JRB    01     Created.					*/
/************************************************************************/
#include "glbtypes.h"
#include "sysincs.h"
#include "gen_list.h"
#include "acse2usr.h"	/* for clpp_event (called from goose thread)	*/
#include "clnp_usr.h"
#include "clnp_sne.h"
#include "clnp.h"
#include "clnp_log.h"
#include "glbsem.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;  /* Define for SLOG mechanism    */
#endif

static N_UNITDATA *main_list = NULL;	/* Linked list	*/
static N_UNITDATA *goose_list = NULL;	/* Linked list	*/
ST_EVENT_SEM hGooseEvent;

void clnp_read_thread (void *param);
void goose_read_thread (void *param);
static ST_VOID put_main_pdu (N_UNITDATA *n_unitdata);
static ST_VOID put_goose_pdu (N_UNITDATA *n_unitdata);

/************************************************************************/
/*			clnp_read_thread_start				*/
/* This function starts a new thread that repeatedly calls "clnp_read".	*/
/* It also sets parameters so the following things happen automatically:*/
/*   1. "Main" thread waits for "hMainEvent" instead of "hMMSEvent".	*/
/*   2. "Main" thread calls "clnp_read_main" instead of "clnp_read".	*/
/*   3. "Goose" thread calls "clnp_read_goose" instead of "clnp_read".	*/
/************************************************************************/
ST_RET clnp_read_thread_start ()
  {
  /* Create "Main" and "Goose" event semaphores.		*/
  /* Use "gs_get_event_sem" which creates "auto-reset" events.		*/
  if (!(hMainEvent = gs_get_event_sem (SD_FALSE)))
    {
    CLNP_LOG_ERR0 ("Error creating Main Event Semaphore.");
    return (SD_FAILURE);
    }
  /* IMPORTANT: this is called BEFORE starting "goose_read_thread"	*/
  /*            because the thread needs to wait on this event.		*/
  if (!(hGooseEvent = gs_get_event_sem (SD_FALSE)))
    {
    CLNP_LOG_ERR0 ("Error creating GOOSE Event Semaphore.");
    return (SD_FAILURE);
    }

  /* Start "CLNP Read" thread to read packets from ethernet driver.	*/
  if (gs_start_thread ((ST_VOID *)clnp_read_thread,	/* funct ptr	*/
               0, NULL, NULL))	/* arg = 0, no thr handle, no thr id	*/
    {
    CLNP_LOG_ERR0 ("Can't create 'CLNP Read' Thread");
    return (SD_FAILURE);
    }

  /* Start "GOOSE Read" thread to read packets from the linked list	*/
  /* instead of calling "clnp_read" directly.				*/
  /* IMPORTANT: this is called AFTER "hGooseEvent" created, because it	*/
  /*            needs to wait on this event.				*/
  if (gs_start_thread ((ST_VOID *)goose_read_thread,	/* funct ptr	*/
               0, NULL, NULL))	/* arg = 0, no thr handle, no thr id	*/
    {
    CLNP_LOG_ERR0 ("Can't create 'Goose Read' Thread");
    return (SD_FAILURE);
    }

  /* CRITICAL: set function pointer so CLPP calls "clnp_read_goose"	*/
  /* instead of "clnp_read".						*/
  clnp_read_fun_cl = clnp_read_goose;

  /* CRITICAL: set function pointer so TP4 calls "clnp_read_main"	*/
  /* instead of "clnp_read".						*/
  clnp_read_fun_co = clnp_read_main;

  return (SD_SUCCESS);
  }

/************************************************************************/
/*			clnp_read_thread					*/
/* This is the "CLNP Read" thread. It reads and decodes packets from	*/
/* the ethernet driver, saves them on 2 linked lists, then signals the	*/
/* other threads using gs_signal_event_sem.					*/
/* This thread is spawned from the main thread only once.		*/
/************************************************************************/
void clnp_read_thread (void *param)
  {
ST_RET rc;
N_UNITDATA *n_unitdata;

  /* Don't do anything until driver creates "Network" event semaphore.	*/
  while (hMMSEvent == NULL)
    {
    }

  while (1)
    {
    /* Wait for "Network" event semaphore.	*/
#if defined(_WIN32)
    /* CRITICAL: must use "Wait...Ex" so Read Completion functions in	*/
    /*           Ethernet interface code get called.			*/
    WaitForSingleObjectEx (hMMSEvent, INFINITE, TRUE);
    rc = SD_SUCCESS;	/* Don't care what is returned from "Wait.."	*/
#else
    rc = gs_wait_event_sem (hMMSEvent, LONG_MAX);
#endif

    if (rc)		/* Error.	*/
      {
      CLNP_LOG_ERR0 ("Wait For 'Network' Event failed");
      }
    else
      {
      /* Loop until no more packets. This helps if events missed.	*/
      while ((n_unitdata = clnp_read ()) != NULL)
        {
	if (clnp_snet_check_mac (n_unitdata->loc_mac) == CLNP_MAC_GOOSE)
          put_goose_pdu (n_unitdata);	/* put on "Goose" linked list	*/
        else
          put_main_pdu (n_unitdata);	/* put on "main" linked list.	*/
        }	/* end inner "while"	*/
      }
    }	/* end "while"	*/
  }

/************************************************************************/
/*			goose_read_thread					*/
/* This is the the recommended version of "goose_read_thread" that	*/
/* waits for a GOOSE Event and then processes it.			*/
/* The user is free to replace this thread with their own version to	*/
/* meet their own GOOSE performance needs.				*/
/************************************************************************/
void goose_read_thread (void *param)
  {
ST_RET rc;

  /* Don't do anything until main thread creates "GOOSE" event semaphore.*/
  /* This is done before starting this thread, but just to be sure....	*/
  while (hGooseEvent == NULL)
    {
    }

  while (1)
    {
    /* Wait for "Goose" event.	*/
    rc = gs_wait_event_sem (hGooseEvent, LONG_MAX);

    if (rc)		/* Error.	*/
      {
      CLNP_LOG_ERR0 ("Wait For Goose Event failed");
      }
    else
      {
      /* Loop until no more packets. This helps if events missed.	*/
      /* This function calls "clnp_read_goose" to get the packet,	*/
      /* decodes it, and if the decoding is successful, calls the ACSE	*/
      /* user function "u_a_unit_data_ind" to give the data to the user.*/
      while (clpp_event ())
        {
        /* All processing done within "clpp_event". Do nothing here.	*/
        }
      }
    }	/* end "while"	*/
  }

/************************************************************************/
/************************************************************************/
static ST_VOID put_main_pdu (N_UNITDATA *n_unitdata)
  {
  gs_get_sem ();

  /* WARNING: WARNING: multiple threads accessing this list.		*/
  /* Must be protected by some kind of mutex semaphore.			*/
  list_add_last ((void**) &main_list, n_unitdata);

  gs_free_sem ();

  gs_signal_event_sem (hMainEvent);	/* Wake up main thread.		*/
  }

/************************************************************************/
/************************************************************************/
static ST_VOID put_goose_pdu (N_UNITDATA *n_unitdata)
  {
  gs_get_sem ();

  /* WARNING: WARNING: multiple threads accessing this list.		*/
  /* Must be protected by some kind of mutex semaphore.			*/
  list_add_last ((void**) &goose_list, n_unitdata);

  gs_free_sem ();

  gs_signal_event_sem (hGooseEvent);	/* Wake up Goose thread.		*/
  }

/************************************************************************/
/*			clnp_read_main					*/
/* Called by CLNP user to read "main" (not GOOSE) NPDU			*/
/* For efficiency, the "main" thread should wait for the event		*/
/* "hMainEvent" before calling this function. See the function		*/
/* "wait_any_event" for an example of how to do this.			*/
/************************************************************************/
N_UNITDATA *clnp_read_main (ST_VOID)
  {
N_UNITDATA *n_unitdata;
  gs_get_sem ();

  /* WARNING: WARNING: multiple threads accessing this list.		*/
  /* Must be protected by some kind of mutex semaphore.			*/
  if (main_list)
    n_unitdata = (N_UNITDATA *) list_get_first ((ST_VOID **) &main_list);
  else
    n_unitdata = (N_UNITDATA *) NULL;

  gs_free_sem ();
  return (n_unitdata);
  }

/************************************************************************/
/*			clnp_read_goose					*/
/* Called by CLNP user to read "GOOSE" NPDU.				*/
/* For efficiency, the "goose" thread should wait for the event		*/
/* "hGooseEvent" before calling this function.				*/
/************************************************************************/
N_UNITDATA *clnp_read_goose (ST_VOID)
  {
N_UNITDATA *n_unitdata;
  gs_get_sem ();

  /* WARNING: WARNING: multiple threads accessing this list.		*/
  /* Must be protected by some kind of mutex semaphore.			*/
  if (goose_list)
    n_unitdata = (N_UNITDATA *) list_get_first ((ST_VOID **) &goose_list);
  else
    n_unitdata = (N_UNITDATA *) NULL;

  gs_free_sem ();
  return (n_unitdata);
  }
