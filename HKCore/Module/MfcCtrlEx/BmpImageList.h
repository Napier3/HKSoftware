#if !defined(_BmpImageList_h__)
#define _BmpImageList_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpImageList.h : header file
//

class CBmpImageList : public CImageList  
{  
public:  
	CBmpImageList();  
	virtual ~CBmpImageList();  

public:  
	BOOL LoadBmpFile(const CString &strFile, long nCount, COLORREF crMask);
	BOOL ValidImageList()	{	return (m_hBitmap != NULL);	}
	
protected:
	CBitmap *m_pBitmap;
	HBITMAP m_hBitmap;

	void FreeBmp();
};  

#endif // !defined(_BmpImageList_h__)
