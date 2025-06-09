//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_SclSvInAll.h  CXScdDrawCtrl_SclSvInAll

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"


//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_GridTitleSclSvInAll : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_GridTitleSclSvInAll();
	virtual ~CXScdDrawCtrl_GridTitleSclSvInAll();

	//重载函数
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowTitle(CExBaseObject *pData);

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	//绘图相关函数定义
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_GridChsSclSvInAll : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_GridChsSclSvInAll();
	virtual ~CXScdDrawCtrl_GridChsSclSvInAll();


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

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclSvInAll
class CXScdDrawCtrl_SclSvInAll : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_SclSvInAll();
	virtual ~CXScdDrawCtrl_SclSvInAll();

//重载函数
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVIN;   }

//私有成员变量
private:
	CExBaseList m_listAllCh;

//私有成员变量访问方法
public:

//绘图相关函数定义
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);
	virtual void CreateCtrlLines();

};

