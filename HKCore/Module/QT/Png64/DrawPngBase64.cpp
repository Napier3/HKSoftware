#include "DrawPngBase64.h"

CDrawPngBase64::CDrawPngBase64()
{
	m_pImage = NULL;
	m_pBuffer = NULL;
}

CDrawPngBase64::~CDrawPngBase64()
{
	ReleasePngDraw();
}

void CDrawPngBase64::CreatePngDraw(long nWidth, long nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	QString format("png");
	m_pBuffer = new QBuffer(&m_ba);
	m_pBuffer->open(QIODevice::WriteOnly);
	m_pImage = new QImage(nWidth, nHeight, QImage::Format_RGB32);
}

void CDrawPngBase64::FillBack(unsigned long cr)
{
	CDC oDC;
	oDC.begin(m_pImage);

	CBrush cBrush(cr);
	CRect rc(0, 0, m_nWidth, m_nHeight);
	oDC.FillRect(&rc, &cBrush);

	oDC.end();
}

void CDrawPngBase64::GetPngBase64()
{
	m_pImage->save(m_pBuffer, "png", -1);
	m_strPngBase64 = m_ba.toBase64();
}

void CDrawPngBase64::ClearPngCache()
{
	m_strPngBase64 = "";
	m_ba.clear();
}

void CDrawPngBase64::PngDrawDemo()
{
	CDC oDC;
	oDC.begin(m_pImage);
	
	CBrush cBrush(RGB(255, 255, 255));
	oDC.SelectObject(&cBrush);

	CRect rc(10, 10, m_nWidth-20, m_nHeight - 20);
	oDC.Rectangle(rc);
	oDC.Ellipse(rc);
	oDC.MoveTo(10, 10);
	oDC.LineTo(m_nWidth-20, m_nHeight - 20);
	
	oDC.end();
}

void CDrawPngBase64::ReleasePngDraw()
{
	if (m_pImage == NULL)
	{
		return;
	}

	delete m_pImage;
	delete m_pBuffer;
	m_pImage = NULL;
	m_pBuffer = NULL;
}

