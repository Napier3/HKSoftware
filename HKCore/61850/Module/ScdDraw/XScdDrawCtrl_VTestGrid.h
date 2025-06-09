//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_VTestGridChs.h  CXScdDrawCtrl_VTestGridChs

#pragma once

#include "XScdDrawCtrlBase.h"
#include "..\..\..\Module\GridBase\ExBaseListXGridCtrlBase.h"


//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_VTestGridTitleBase : public CExBaseListXGridCtrlBase
{
public:
	CXScdDrawCtrl_VTestGridTitleBase();
	virtual ~CXScdDrawCtrl_VTestGridTitleBase();

	//重载函数
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowTitle(CExBaseObject *pData) = 0;
	virtual CDataType* FindDataType(const CString &strDataType);

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	//绘图相关函数定义
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_VTestGridChsBase : public CExBaseListXGridCtrlBase
{
public:
	CXScdDrawCtrl_VTestGridChsBase();
	virtual ~CXScdDrawCtrl_VTestGridChsBase();

//重载函数
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

// 	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);
// 	static void EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//绘图相关函数定义
public:

};
