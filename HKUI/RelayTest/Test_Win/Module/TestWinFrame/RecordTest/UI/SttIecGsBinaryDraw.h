//SttIecGsBinaryDraw.h  CSttIecGsBinaryDraw

#pragma once

#include "../../BinaryDraw/XBinaryDrawBase.h"

#include "../../../../Module/SmartCap/61850Cap/ProtocolBase/ProtocolGlobalDef.h" 

#define BINARY_NOT_BINARY_COLOR   RGB(255, 255, 255)
#define BINARY_COLOR_0X84_0    RGB(255, 255, 0)
#define BINARY_COLOR_0X84_1    RGB(0,250,154)
#define BINARY_COLOR_0X84_2    RGB(255, 0, 0)
#define BINARY_COLOR_0X84_3    RGB(0,255,255)

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinaryDraw
class CSttIecGsBinaryDraw : public CXBinaryDrawBase
{
public:
	CSttIecGsBinaryDraw();
	virtual ~CSttIecGsBinaryDraw();

	EPCAPPARSEDATAS *m_pDatas;

//构建函数
public:
	virtual void CreateBinaryDraw(long nIndex, EPCAPPARSEDATAS *pDatas);
	virtual long GetBinaryBitVal();
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag);

};

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinarysDraw
class CSttIecGsBinarysDraw : public CXBinarysDrawBase
{
public:
	CSttIecGsBinarysDraw();
	virtual ~CSttIecGsBinarysDraw();

	EPCAPPARSEDATAS *m_pDatas;

//构建函数
public:
	virtual void CreateBinarysDraw(long nCount, EPCAPPARSEDATAS *pDatas, CWnd *pMsgRcvWnd);
};

