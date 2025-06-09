//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"

#include "XScdDrawCtrl_CfgSvOut.h"
#include "XScdDrawCtrl_CfgSvIn.h"
#include "XScdDrawCtrl_CfgGsOut.h"
#include "XScdDrawCtrl_CfgGsIn.h"

#include "XScdDrawCtrl_SclSvOut.h"
#include "XScdDrawCtrl_SclSvIn.h"
#include "XScdDrawCtrl_SclGsOut.h"
#include "XScdDrawCtrl_SclGsIn.h"

#include "XScdDrawIedBase.h"


class CXScdDrawIedCfg : public CXScdDrawIedBase
{
public:
	CXScdDrawIedCfg();
	virtual ~CXScdDrawIedCfg();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_CFG;   }
	CString m_strIP;
	CString m_strManufacturer;

//私有成员变量
private:

	 BOOL m_Symble_MainIed;//设置一个被测IED的标志，用于区分第一个IED和后面的IED

public:
	void SetSymbleMainIed(BOOL pSymble_MainIed) {m_Symble_MainIed=pSymble_MainIed; }
	BOOL GetSymbleMainIed() {return m_Symble_MainIed;}


	 //私有成员变量访问方法
public:
	CXScdDrawCtrlBase* XCreateCtrl_SvIn_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_SvOut_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsIn_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsOut_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);

	CXScdDrawCtrlBase* XCreateCtrl_SvIn_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_SvOut_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsIn_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsOut_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);

//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	void DrawLines(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

public:
	CSize CalLayout(CSize &szDraw);

	virtual CSize Layout(CPoint &ptTopLeft);

};

