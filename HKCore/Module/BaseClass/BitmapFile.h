// BitmapFile.h

#ifndef __BITMAPFILE_H__
#define __BITMAPFILE_H__

class CBitmapFile : public CBitmap
{

public:
	CBitmapFile();
	~CBitmapFile();
	
	BOOL LoadFile(const CString &strFile);
	BOOL Load(const CString &strFile)	{	return LoadFile(strFile);	}

	BOOL Draw( CDC *, int nX = 0, int nY = 0,int nWidth = -1, int nHeight = -1,
		unsigned long unsrc=SRCCOPY );

	void SetTransparent(BOOL bTrans)	{	m_bTransparent = bTrans;	}
	void SetMaskColor(COLORREF cr)		{	m_crMask = cr;				}

private:
	BOOL m_bFirst;
	BOOL m_bTransparent;
	COLORREF m_crMask;
};

#endif
