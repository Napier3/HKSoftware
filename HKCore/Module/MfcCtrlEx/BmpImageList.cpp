// SplashWndBase.cpp
//

#include "stdafx.h"
#include "BmpImageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////

CBmpImageList::CBmpImageList()  
{  
	m_pBitmap = NULL;
	m_hBitmap = NULL;
}  

CBmpImageList::~CBmpImageList()  
{  
	delete m_pBitmap;
}  

void CBmpImageList::FreeBmp()
{
	if (m_pBitmap != NULL)
	{
		m_pBitmap->Detach();
	}

	if (m_hBitmap != NULL)
	{
		::DeleteObject(m_hBitmap);
	}
}

BOOL CBmpImageList::LoadBmpFile(const CString &strFile, long nCount, COLORREF crMask)
{
	Create(16,16,ILC_COLOR32 | ILC_COLORDDB | ILC_MASK, nCount, 1);

	if (m_pBitmap == NULL)
	{
		m_pBitmap = new CBitmap; 
	}
	else
	{
		FreeBmp();
	}

	m_hBitmap = (HBITMAP)LoadImage(NULL, strFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if ( NULL != m_hBitmap ) 
	{ 
		m_pBitmap->Attach(m_hBitmap);  
		Add(m_pBitmap, crMask); 
		return TRUE;
	} 

	return FALSE;
}


