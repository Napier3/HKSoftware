//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "..\..\..\Module\XDrawBase\XDrawElements.h"
#include "XScdDrawGlobal.h"
#include "XScdDrawIedBase.h"

#include "XScdDrawCtrl_ThumbSvOut.h"
#include "XScdDrawCtrl_ThumbSvIn.h"
#include "XScdDrawCtrl_ThumbGsOut.h"
#include "XScdDrawCtrl_ThumbGsIn.h"
#include "XScdDrawLineBase.h"
#include "XScdDrawLine_Ctrls.h"

#define IEDTHUMBNAILTYPE_PROCMEAS 1
#define IEDTHUMBNAILTYPE_MUCTRL 2
#define IEDTHUMBNAILTYPE_PROCMEAS2 3



class CXScdDrawIedThumbnail : public CXScdDrawIedBase
{
public:
	CXScdDrawIedThumbnail();
	virtual ~CXScdDrawIedThumbnail();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_THUMBNAIL;   }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	CSclIed *m_pRefIed;
	int m_b_ProtMeas_MuCtrl;

//私有成员变量访问方法
public:
	void SetRefIed(CSclIed *pRefIed) {m_pRefIed=pRefIed;}
	CSclIed* GetRefIed() {return m_pRefIed;}

	void SetSymbel (int b_ProtMeas_MuCtrl) {m_b_ProtMeas_MuCtrl = b_ProtMeas_MuCtrl;}
	int GetSymbel() {return m_b_ProtMeas_MuCtrl;}

	BOOL IsIed_RPIT_MU()	{	return m_pRefIed->IsIed_RPIT_MU();	}
	BOOL IsIed_MU()			{	return m_pRefIed->IsIed_MU();	}
	BOOL IsIed_RPIT()		{	return m_pRefIed->IsIed_RPIT();	}
	BOOL IsIed_Prot_Meas()	{	return m_pRefIed->IsIed_Prot_Meas();	}
	BOOL IsIed_Prot()		{	return m_pRefIed->IsIed_Prot();	}
	BOOL IsIed_Meas()		{	return m_pRefIed->IsIed_Meas();	}

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

	CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual void  XCreateCtrl(CSclIed *pIedData, CWnd *pParentWnd);
	virtual void  XCreateCtrl(CWnd *pParentWnd);
	virtual void GetAllLines(CXDrawElements &oScdLines);
	virtual void CreateCtrlLines();
	void FilterAllLines(CXDrawElements &oScdLines);//对所有的线进行判断，是否为保护测控装置之间的连线，还是保护测控装置与合并单元智能终端之间的连线


	CXScdDrawCtrl_ThumbSvOut* GetCtrl_ThumbSvOut();
	CXScdDrawCtrl_ThumbSvIn* GetCtrl_ThumbSvIn();
	CXScdDrawCtrl_ThumbGsOut* GetCtrl_ThumbGsOut();
	CXScdDrawCtrl_ThumbGsIn* GetCtrl_ThumbGsIn();

	virtual void CreateCtrlBusLines();

};

