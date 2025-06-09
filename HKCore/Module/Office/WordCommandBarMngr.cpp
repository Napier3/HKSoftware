// CmdBarButton.cpp: implementation of the CWordCommandBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WordCommandBarMngr.h"
#include "..\Api\GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CWordCommandBarMngr::CWordCommandBarMngr()
{
}

CWordCommandBarMngr::~CWordCommandBarMngr()
{
	
}

void CWordCommandBarMngr::InitWordCommandBarMngr(MSO9::_CommandBars cmdbars, BOOL bHide)
{
	try
	{
		long nCount = cmdbars.GetCount();
		long nIndex = 1;
		CWordCommandBar *pCmdBar = NULL;

		for(nIndex=1;nIndex<=nCount;nIndex++)
		{
			MSO9::CommandBar cmdbar = cmdbars.GetItem(COleVariant(nIndex));
			pCmdBar = new CWordCommandBar;
			pCmdBar->m_strName = cmdbar.GetName();
			pCmdBar->m_bEnable = cmdbar.GetEnabled();
			pCmdBar->m_bVisible = cmdbar.GetVisible();
			pCmdBar->m_nIndex = cmdbar.GetIndex();

			if (pCmdBar->m_bEnable && pCmdBar->m_bVisible)
			{ 
				AddTail(pCmdBar);
			}
			else
			{
				delete pCmdBar;
			}
		}
	}
	catch (...)
	{
		TRACE("catch error-----");
	}	

	SaveWordCommandBarMngr();
}

void CWordCommandBarMngr::RestoreWordCommandBars(MSO9::_CommandBars cmdbars)
{
	//ª÷∏¥
	MSO9::CommandBar cmdbar = NULL;
	
	try
	{
		long nCount = cmdbars.GetCount();
		long nIndex = 1;
		CWordCommandBar *pCmdBar = NULL;
		POS pos = NULL;
		pos = GetHeadPosition();
		while (pos != NULL)
		{
			pCmdBar = (CWordCommandBar*)GetNext(pos);

			if (pCmdBar->m_bEnable && pCmdBar->m_bVisible)
			{
				cmdbar = NULL;
				try
				{
					cmdbar = cmdbars.GetItem(COleVariant(pCmdBar->m_nIndex));
				}
				catch (...) 
				{
					TRACE("catch error-----");
					try
					{
						cmdbar = cmdbars.GetItem(COleVariant(pCmdBar->m_strName));
					}
					catch (...) 
					{
						TRACE("catch error-----");
					}
				}

				if (cmdbar != NULL)
				{
					cmdbar.SetEnabled(pCmdBar->m_bEnable);
					cmdbar.SetVisible(pCmdBar->m_bVisible);
				}
			}
		}
	}	
	catch( ... )
	{
	}

	//…æ≥˝¡Ÿ ±≈‰÷√Œƒº˛
	try
	{
		CFile::Remove( m_strCmdBarsCfgFile );
	}
	catch( ... )
	{
	}

	EndIt();
}

BOOL CWordCommandBarMngr::LoadWordCommandBarMngr(MSO9::_CommandBars cmdbars)
{
	CBinarySerialBuffer oBuff;

	if (oBuff.OpenFromFile(m_strCmdBarsCfgFile) )
	{
		oBuff.SetReadMode();
		Serialize(oBuff);
		RestoreWordCommandBars(cmdbars);
	}

	return FALSE;
}
