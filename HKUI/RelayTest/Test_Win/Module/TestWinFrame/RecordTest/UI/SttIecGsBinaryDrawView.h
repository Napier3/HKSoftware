//SttIecGsBinaryDraw.h  CSttIecGsBinaryDraw

#pragma once

#include "../../BinaryDraw/XBinaryDrawView.h"
#include "../../../../Module/SmartCap/61850Cap/ProtocolBase/ProtocolGlobalDef.h" 

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinaryDraw
class CSttIecGsBinaryDrawView : public CXBinaryDrawView
{
public:
	CSttIecGsBinaryDrawView();
	virtual ~CSttIecGsBinaryDrawView();

	EPCAPPARSEDATAS *m_pDatas;

//构建函数
public:
	virtual DWORD XCreateElement(long nCount, EPCAPPARSEDATAS *pDatas, CWnd *pParentWnd);
	
	void OnSize(long cx, long cy);
};
