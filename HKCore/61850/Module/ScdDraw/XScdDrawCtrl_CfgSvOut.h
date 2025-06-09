//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_CfgSvOut.h  CXScdDrawCtrl_CfgSvOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridTitleSvOut : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_CfgGridTitleSvOut();
	virtual ~CXScdDrawCtrl_CfgGridTitleSvOut();

//重载函数
public:
	virtual void ShowTitle(CExBaseObject *pData);

//私有成员变量
private:

//私有成员变量访问方法
public:

//绘图相关函数定义
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridChsSvOut : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_CfgGridChsSvOut();
	virtual ~CXScdDrawCtrl_CfgGridChsSvOut();

//重载函数
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//绘图相关函数定义
public:

};

class CXScdDrawCtrl_CfgSvOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_CfgSvOut();
	virtual ~CXScdDrawCtrl_CfgSvOut();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVOUT;   }

//私有成员变量
private:

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

public:

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);
};
