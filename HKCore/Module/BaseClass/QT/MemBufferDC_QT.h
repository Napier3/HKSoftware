#if !defined(_MemBufferDC_QT_h__)
#define _MemBufferDC_QT_h__

#ifndef _USE_NO_GUI_
#include "../../OSInterface/QT/CXDraw_QT.h"
#else
#include "../../OSInterface/QT/CXDraw_QT_NOGUI.h"
#endif

class CMemBufferDC
{
public:
	
        inline BOOL Create(CDC* pDC, const CRect &rc)
	{
		if (m_rect != rc)
		{
			m_bSizeChanged = FALSE;
			ASSERT(pDC != NULL);
			Release();
			m_rect = rc;
                        m_pBitmap = new CBitmap(rc.Width(), rc.Height());
                        m_pDC = pDC;
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		m_bIsBegin = FALSE; //2021-9-20  lijunqing
	}
	
    // constructor sets up the memory DC
    inline CMemBufferDC()
	{
		m_bIsBegin = FALSE; //2021-9-20  lijunqing
		m_bSizeChanged = TRUE;
		m_pBitmap = NULL;
		m_pDC = NULL;
		m_rect.left = -1;
		m_rect.top = -1;
		m_rect.right = -1;
		m_rect.bottom = -1;
	}
	
        inline CMemBufferDC(CDC* pDC, CRect &rc)
	{
		m_bIsBegin = FALSE; //2021-9-20  lijunqing
		m_rect.left = -1;
		m_rect.top = -1;
		m_rect.right = -1;
		m_rect.bottom = -1;
		m_bSizeChanged = TRUE;
		m_pBitmap = NULL;
		m_pDC = NULL;
		Create(pDC, rc);
    }
	
        inline void Draw(CDC *pDC)
	{
#ifndef _USE_NO_GUI_
	    pDC->drawImage(0, 0, *m_pBitmap);
#endif
	}

        inline void FillSolidRect(COLORREF crColor)
	{
		if (m_pDC != NULL)
		{
			m_pDC->FillSolidRect(&m_rect, crColor);
		}
	}
    
        inline void Release()
	{
		EndDC();

		if (m_pBitmap != NULL)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
		
                m_pDC = NULL;
		m_rect.left = -1;
		m_rect.top = -1;
		m_rect.right = -1;
		m_rect.bottom = -1;
                m_bSizeChanged = 1;
		m_bIsBegin = FALSE; //2021-9-20  lijunqing
	}
    // Destructor copies the contents of the mem DC to the original DC
    virtual ~CMemBufferDC()
    {
		Release();
    }
	
    // Allow usage as a pointer
    inline CMemBufferDC* operator->() {return this;}
	
    // Allow usage as a pointer
    inline operator CMemBufferDC*() {return this;}
	
	inline CDC* GetDC()
	{
#ifndef _USE_NO_GUI_
		if (!m_bIsBegin)
		{
			m_pDC = new CDC();
			m_bIsBegin = TRUE; //2021-9-20  lijunqing
			m_pDC->begin(m_pBitmap);
		}
#endif
	    return m_pDC;
	}

	inline void EndDC()
	{
#ifndef _USE_NO_GUI_
		m_bIsBegin = FALSE; //2021-9-20  lijunqing

		if (m_pDC != NULL)
		{
			m_pDC->end();
			delete m_pDC;
			m_pDC = NULL;
		}
#endif
	}

        inline void SetSizeChanged()  {   m_bSizeChanged = TRUE;	}
        inline BOOL IsSizeChanged()   {   return m_bSizeChanged;	}
        inline CRect GetRect()        {   return m_rect;           }
        inline CBitmap* GetBitmap()	{	return m_pBitmap;	}
	
        inline void BitBlt(int x,int y,int nWidth,int nHeight,
                               CDC* pSrcDC, int xSrc,int ySrc,DWORD dwRop)
        {
#ifndef _USE_NO_GUI_
	    pSrcDC->drawImage(x, y, *m_pBitmap);
#endif
	}

private:
    CBitmap  *m_pBitmap;      // Offscreen bitmap
    CRect    m_rect;        // Rectangle of drawing area.
	CDC      *m_pDC;
	BOOL     m_bSizeChanged;

	//2021-9-20  lijunqing
	BOOL m_bIsBegin;
};

#endif // !defined(_MemBufferDC_QT_h__)
