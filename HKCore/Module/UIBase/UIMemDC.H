#if !defined(_UIMEMDC_H__)
#define _UIMEMDC_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UIMemDC.h : header file
//

#include "..\API\GloblaDrawFunctions.h"

class CUIMemDC
{
public:

	BOOL Create(CDC* pDC, CRect &rc)
	{
		if (m_rect != rc)
		{
			m_bSizeChanged = FALSE;
			ASSERT(pDC != NULL);
			Release();
			m_rect = rc;
			m_pBitmap = new CBitmap();
			m_pOldBitmap = NULL;
			m_pDC = new CDC();
			m_pDC->CreateCompatibleDC(pDC);
			m_pBitmap->CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
			m_pOldBitmap = m_pDC->SelectObject(m_pBitmap);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

    // constructor sets up the memory DC
    CUIMemDC()
	{
		m_bSizeChanged = TRUE;
		m_pOldBitmap = NULL;
		m_pBitmap = NULL;
		m_pDC = NULL;
	}
	
	CUIMemDC(CDC* pDC, CRect &rc)
   {
		m_bSizeChanged = TRUE;
		m_pOldBitmap = NULL;
		m_pBitmap = NULL;
		m_pDC = NULL;
		Create(pDC, rc);
    }
	
	void Draw(CDC *pDC)
	{
		pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
			m_pDC, m_rect.left, m_rect.top, SRCCOPY);
	}
    
	void DrawTransparent(CDC *pDC, COLORREF rgbMask)
	{
		DrawTransparentBitmap(pDC, m_pBitmap,m_rect, rgbMask, TRUE);
	}

	void Release()
	{
		if (m_pOldBitmap != NULL)
		{
			m_pDC->SelectObject(m_pOldBitmap);
			m_pOldBitmap = NULL;
		}

		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}

		if (m_pDC != NULL)
		{
			delete m_pDC;
			m_pDC = NULL;
		}
		m_rect.left = 0;
		m_rect.top = 0;
		m_rect.right = 0;
		m_rect.bottom = 0;
	}
    // Destructor copies the contents of the mem DC to the original DC
    ~CUIMemDC()
    {
		Release();
    }

    // Allow usage as a pointer
    CUIMemDC* operator->() {return this;}
        
    // Allow usage as a pointer
    operator CUIMemDC*() {return this;}

	CDC* GetDC()  {   return m_pDC;    }
	void SetSizeChanged()  {   m_bSizeChanged = TRUE;	}
	BOOL IsSizeChanged()   {   return m_bSizeChanged;	}

private:
    CBitmap  *m_pBitmap;      // Offscreen bitmap
    CBitmap  *m_pOldBitmap;  // bitmap originally found in CUIMemDC
    CRect    m_rect;        // Rectangle of drawing area.
	CDC      *m_pDC;
	BOOL     m_bSizeChanged;
};

#endif // !defined(_UIMEMDC_H__)
