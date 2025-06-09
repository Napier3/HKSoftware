//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_ThumbBase.h  XScdDrawCtrl_ThumbBase

#pragma once

#include "XScdDrawCtrlBase.h"

class CXScdDrawCtrl_ThumbBase : public CXDrawElements
{
public:
	CXScdDrawCtrl_ThumbBase();
	virtual ~CXScdDrawCtrl_ThumbBase();
	CString m_strCtrlText;

	static BOOL g_bNeedCreateCtrlLines;

	CXScdDrawLine_ToBus *m_pLineCtrlBus;

public:
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual void CreateCtrlLines(){};
	virtual void CreateCtrlBusLines();
	virtual CXScdDrawLineBase* FindLineByBeginRef(CExBaseObject *pBeginRef);

	virtual void GetAllLines(CXDrawElements &oScdLines);

	CXScdDrawLine_Bus* GetSvBus();
	CXScdDrawLine_Bus* GetGooseBus();
};
