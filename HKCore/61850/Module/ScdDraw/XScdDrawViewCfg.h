//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIedCfg.h  CXScdDrawViewIedCfg

#pragma once

#include "XScdDrawViewBase.h"
#include "..\CfgDataMngr\IecCfgDevice.h"
#include "XScdDrawIedCfg.h"

extern int  g_nCount_LeftIeds; //界面上左边标IED的个数，设置为全局变量
extern int  g_nCount_RightIeds; //界面上右边IED的个数，设置为全局变量

class CXScdDrawViewCfg : public CXScdDrawViewBase
{
public:
	CXScdDrawViewCfg();
	virtual ~CXScdDrawViewCfg();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_CFG;   }

//私有成员变量
private:
	CXScdDrawIedCfg *m_pMainIed;
	CExBaseList m_listIedGroup;
	CXScdIedGroup *m_pLeft;
	CXScdIedGroup *m_pRight;

//私有成员变量访问方法
public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

protected:
	void InitXScdDrawView(CIecCfgDatasMngr *pCfgDatasMngr, CWnd *pParentWnd);
	void InitXScdDrawView(CIecCfgDatasSMV *pIecCfgDatasSMV, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd);
	void InitXScdDrawView(CIecCfgGinDatas *pIecCfgGinDatas, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd);
	void InitXScdDrawView(CIecCfgGoutDatas *pIecCfgGoutDatas, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd);
//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
// 	virtual void Pick(const CPoint &point, CExBaseList &oList);

public:
	virtual CSize Layout(CPoint &ptTopLeft);
	virtual CSize CalLayout(CSize &szDraw);
// 	virtual CSize CalLayoutOwn(CSize &szDraw);
// 	virtual CSize CalLayoutChildren(CSize &szDraw);

protected:
	CSize CalLayoutOtherIed();
	CSize CalLayoutOtherIed(CSize szSplit);

};

