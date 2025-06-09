#ifndef _CDrawPngBase_H__
#define _CDrawPngBase_H__

#include "../../XDrawBase/XDrawGlobal.h"

#include <qbuffer.h>
#include <qpainter.h>

class CDrawPngBase64
{
public:
	CDrawPngBase64();
	virtual ~CDrawPngBase64();

	QByteArray m_ba;
	QString m_strPngBase64;
	
	QImage *m_pImage;
	QBuffer* m_pBuffer;
	long m_nWidth;
	long m_nHeight;
	
public:
	void CreatePngDraw(long nWidth, long nHeight);
	void FillBack(unsigned long cr);
	void GetPngBase64();
	void PngDrawDemo();
	void ReleasePngDraw();
	void ClearPngCache();
};

#endif//!_CDrawPngBase_H__