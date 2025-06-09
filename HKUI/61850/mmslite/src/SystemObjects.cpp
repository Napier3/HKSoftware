/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,	*/
/*		2001, All Rights Reserved				*/
/*									*/
/* MODULE NAME : SystemObjects.cpp					*/
/* PRODUCT(S)  : 							*/
/*									*/
/* MODULE DESCRIPTION : 						*/
/* Implementation of wrapper classes for system objects			*/
/*									*/
/* GLOBAL FUNCTIONS DEFINED IN THIS MODULE :				*/
/*									*/
/* MODIFICATION LOG :							*/
/*  Date     Who   Rev			Comments			*/
/* --------  ---  ------   -------------------------------------------	*/
/* 11/07/06  DSF     27    Cleaned up compile warnings			*/
/* 08/14/06  DSF     26    Added Thread2::Start ()			*/
/* 06/13/05  DSF     25    Protected access to Thread::Start and	*/
/*			   Terminate					*/
/* 03/18/05  DSF     24    Use _SASSERTE				*/
/* 07/26/04  DSF     23    Tread::Wait () asserts on deadlock		*/
/*			   Termination Event should be manual		*/
/* 07/23/04  DSF     22    Thread::Start () now waits until the thread	*/
/*			   starts running				*/
/* 05/10/04  DSF     21    Added better DLL Termination handling	*/
/* 05/05/04  DSF     20    If terminating DLL, wait 1 sec for thread to	*/
/*			   terminate					*/
/* 02/11/04  DSF     19    Added ThreadTermCallback (can only be used on*/
/*			   Windows for now)				*/
/* 11/19/03  DSF     18    Undo change 15				*/
/* 09/11/03  DSF     17    Must save thread handle for self terminating */
/*			   threads					*/
/* 06/10/03  DSF     16    If thread is already running, don't start	*/
/*			   another instance				*/
/* 05/13/03  DSF     15    Added a way to automatically clean up timers	*/
/* 03/21/03  DSF     14    Added SISCO namespace			*/
/* 09/25/02  DSF     13    Allowed threads to be restarted		*/
/* 08/01/02  DSF     12    Added SetThreadName				*/
/* 07/19/02  DSF     11    Added Events.WaitAll ()			*/
/* 06/29/02  DSF     10    Added Block method				*/
/* 06/24/02  DSF     06    Fixed a memory leak				*/
/* 11/12/01  DSF     05    Events now holds a vector of Event pointers	*/
/* 11/12/01  DSF     04    Thread Terminate () fixes			*/
/* 11/09/01  DSF     03    delete m_pTermEvent in Thread dtor		*/
/* 11/02/01  EJV     02    Thread::Wait: added call to gs_close_thread.	*/
/* 08/08/01  DSF     01    Module created				*/
/************************************************************************/

static char *thisFileName = __FILE__;

#include "SystemObjects.h"


#if defined (DEBUG_NEW_MFC)
#define new DEBUG_NEW
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif

namespace SISCO
{

namespace SystemObjects
{

/************************************************************************/
/************************************************************************/
/*			Events Class implementation			*/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/*				Wait					*/
/************************************************************************/

Event::WaitReturn Events::Wait (long timeout)
  {
Event::WaitReturn waitRet;
ST_EVENT_SEM esTable[128];
ST_BOOLEAN activity[128];
int i;
  
  if (m_events.size () == 0)
    return Event::waitFailed;
    
  vector<Event *>::iterator iter;
  for (iter = m_events.begin (), i = 0; iter != m_events.end (); iter++, i++)
    esTable[i] = (*iter)->GetEvent ();
    
  ST_RET ret = gs_wait_mult_event_sem (m_events.size (), esTable, 
                                       activity, timeout);
  if (ret == SD_TIMEOUT)
    waitRet = Event::waitTimeout;
  else if (ret == SD_FAILURE)
    waitRet = Event::waitFailed;
  else
    {
    for (i = 0; i < (int) m_events.size (); i++)
      {
      if (activity[i])
        return static_cast<Event::WaitReturn> (i);
      }
    }
    
  return waitRet;
  }
  
/************************************************************************/
/*				WaitAll					*/
/************************************************************************/

Event::WaitReturn Events::WaitAll (long timeout)
  {
Event::WaitReturn waitRet;
ST_EVENT_SEM esTable[128];
ST_BOOLEAN activity[128];
bool allActivity[128];
int i;
  
  if (m_events.size () == 0)
    return Event::waitFailed;

  if (m_events.size () == 1)
    return Events::Wait (timeout);
    
  memset (allActivity, 0, sizeof (allActivity));
  
  vector<Event *>::iterator iter;
  for (iter = m_events.begin (), i = 0; iter != m_events.end (); iter++, i++)
    esTable[i] = (*iter)->GetEvent ();
  
  ST_DOUBLE startWait, endWait;
  long newTimeout = timeout;
  long timeoutAdjust;
  bool done = false;
  while (!done)
    {
    startWait = sGetMsTime ();
    ST_RET ret = gs_wait_mult_event_sem (m_events.size (), esTable, 
                                         activity, newTimeout);
    endWait = sGetMsTime ();
    
    done = true;	
    if (ret == SD_TIMEOUT)
      waitRet = Event::waitTimeout;
    else if (ret == SD_FAILURE)
      waitRet = Event::waitFailed;
    else
      {
      for (i = 0; i < (int) m_events.size (); i++)
        {
        if (activity[i])
          allActivity[i] = true;
        }

      for (i = 0; i < (int) m_events.size (); i++)
        {
        if (allActivity[i] == false)
	  {
	  done = false;
	  break;
	  }
        }
	
      if (done)
        waitRet = Event::waitSuccess;
      else
        {
	timeoutAdjust = (long) (endWait - startWait);
	newTimeout -= timeoutAdjust;
	}
      }
    }
    
  return waitRet;
  }
  

/************************************************************************/
/************************************************************************/
/*			Thread Class implementation			*/
/************************************************************************/
/************************************************************************/

#if defined (_WIN32)
DWORD Thread::m_tlsIndex = TLS_OUT_OF_INDEXES;
#endif

/************************************************************************/
/*				Thread::Thread				*/
/************************************************************************/

Thread::Thread () : m_h (0), m_id (0), m_terminating (false), m_terminated (false), 
	m_pTermEvent (new Event (true)), m_pStartEvent (new Event),
  	m_destroyOnExit (false), m_pTermCallback (NULL)
  {
  
  }

/************************************************************************/
/*				Thread::Start				*/
/************************************************************************/

bool Thread::Start ()
  {

  Lock<> guard (m_mutex);  
  if (m_h)
    return true;
    
  if (m_pStartEvent == NULL)
    m_pStartEvent = new Event;
  if (m_pTermEvent == NULL)
    m_pTermEvent = new Event;

  m_terminated = false;    
  VERIFY (gs_start_thread (entryPoint, (ST_THREAD_ARG) this, 
			   &m_h, &m_id) == SD_SUCCESS);
  m_pStartEvent->Wait ();
  return true;			   
  }

/************************************************************************/
/*				Thread2::Start				*/
/************************************************************************/

bool Thread2::Start ()
  {

  Lock<> guard (m_mutex);  
  if (m_h)
    return true;
    
  if (m_pStartEvent == NULL)
    m_pStartEvent = new Event;
  if (m_pTermEvent == NULL)
    m_pTermEvent = new Event;

  m_terminated = false;    
  VERIFY (gs_start_thread (entryPoint, (ST_THREAD_ARG) this, 
			   &m_h, &m_id) == SD_SUCCESS);
  m_pStartEvent->Wait ();
  return true;			   
  }


/************************************************************************/
/*				Thread::Terminate			*/
/************************************************************************/

bool Thread::Terminate ()
  {
  
  Lock<> guard (m_mutex);
  if (m_h == 0)
    {
    delete m_pStartEvent;
    m_pStartEvent = NULL;
    delete m_pTermEvent;
    m_pTermEvent = NULL;
    return true;
    }

  m_terminating = true;    
  SetTermEvent ();
  long timeout = -1;
#if defined (_WIN32) && defined (_DLL)
  if (IsDLLTerminating ())
    timeout = 1000;
#endif
  Wait (timeout);
  delete m_pStartEvent;
  m_pStartEvent = NULL;
  delete m_pTermEvent;
  m_pTermEvent = NULL;
  
  m_h = 0;
  m_id = 0;
  m_terminating = false;
  m_terminated = true;    
  
  return true;
  }

/************************************************************************/
/*				Thread::Wait				*/
/************************************************************************/

bool Thread::Wait (long timeout)
  {
  
  if (m_h == 0)
    return true;

  _SASSERTE (GET_THREAD_ID () != m_id);
    
  ST_THREAD_HANDLE handle = m_h; 
  ST_RET ret = gs_wait_thread (m_h, m_id, timeout);
  
  if (ret == SD_SUCCESS)
    {
    ret = gs_close_thread (handle);
    m_h = 0;
    m_id = 0;
    return true;
    }
  else
    return false;
  }

/************************************************************************/
/*			Thread::InstallThreadName			*/
/************************************************************************/

void Thread::InstallThreadName ()
  {
  
#if defined (_WIN32)
  if (!m_name.empty ()) 
    gs_set_thread_name (m_id, (char *) m_name.c_str ());
#endif
  }

/************************************************************************/
/************************************************************************/
/*			Global Functions				*/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/*			Block						*/
/************************************************************************/

//void SISCO::SystemObjects::Block (long period)
void Block (long period)
  {
  static Event dummy;
  
  dummy.Wait (period);
  return;
  }
  
#if defined (_WIN32) && defined (_DLL)

static bool isDllTerminating = false;

/************************************************************************/
/*			DllTerminating					*/
/************************************************************************/

void DLLTerminating ()
  {
  
  isDllTerminating = true;
  }
  
/************************************************************************/
/*			IsDllTerminating				*/
/************************************************************************/

bool IsDLLTerminating ()
  {
  
  return isDllTerminating;
  }

#endif

}
}  
