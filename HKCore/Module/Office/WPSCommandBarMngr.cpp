// CmdBarButton.cpp: implementation of the CWordCommandBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WPSCommandBarMngr.h"
#include "..\Api\GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////

CWPSCommandBarMngr::CWPSCommandBarMngr()
{
}

CWPSCommandBarMngr::~CWPSCommandBarMngr()
{

}

void CWPSCommandBarMngr::InitWordCommandBarMngr(KSO::_CommandBars cmdbars, BOOL bHide)
{
	try
	{
		long nCount = cmdbars.get_Count();
		long nIndex = 1;
		CWordCommandBar *pCmdBar = NULL;

		for(nIndex=1;nIndex<=nCount;nIndex++)
		{
			KSO::CommandBar cmdbar = cmdbars.get_Item(COleVariant(nIndex));
			pCmdBar = new CWordCommandBar;
			pCmdBar->m_strName = cmdbar.get_Name();
			pCmdBar->m_bEnable = cmdbar.get_Enabled();
			pCmdBar->m_bVisible = cmdbar.get_Visible();
			pCmdBar->m_nIndex = cmdbar.get_Index();

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

void CWPSCommandBarMngr::RestoreWordCommandBars(KSO::_CommandBars cmdbars)
{
	//ª÷∏¥
	KSO::CommandBar cmdbar = NULL;
	
	try
	{
		long nCount = cmdbars.get_Count();
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
					cmdbar = cmdbars.get_Item(COleVariant(pCmdBar->m_nIndex));
				}
				catch (...) 
				{
					TRACE("catch error-----");
					try
					{
						cmdbar = cmdbars.get_Item(COleVariant(pCmdBar->m_strName));
					}
					catch (...) 
					{
						TRACE("catch error-----");
					}
				}

				if (cmdbar != NULL)
				{
					cmdbar.put_Enabled(pCmdBar->m_bEnable);
					cmdbar.put_Visible(pCmdBar->m_bVisible);
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

BOOL CWPSCommandBarMngr::LoadWordCommandBarMngr(KSO::_CommandBars cmdbars)
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
