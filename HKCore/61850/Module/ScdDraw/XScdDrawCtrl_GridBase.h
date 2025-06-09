//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_CfgGridChs.h  CXScdDrawCtrl_CfgGridChs

#pragma once

#include "XScdDrawGlobal.h"
#include "..\..\..\Module\GridBase\ExBaseListXGridCtrlBase.h"
#include "XScdDrawLineBase.h"

class CXScdDrawCtrl_CfgGridBase : public CExBaseListXGridCtrlBase
{
public:
	CXScdDrawCtrl_CfgGridBase();
	virtual ~CXScdDrawCtrl_CfgGridBase();

	CSclCtrlBase *m_pSclCtrl;	//关联的SCL控制块
	CIecCfgDataBase *m_pCfgData;  //关联的CFG配置

public:
	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridTitleBase : public CXScdDrawCtrl_CfgGridBase
{
public:
	CXScdDrawCtrl_CfgGridTitleBase();
	virtual ~CXScdDrawCtrl_CfgGridTitleBase();


	CXScdDrawCtrl_CfgGridBase *m_pCtrlChsGrid;
//重载函数
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowTitle(CExBaseObject *pData) = 0;

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);

	//绘图相关函数定义
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridChsBase : public CXScdDrawCtrl_CfgGridBase
{
public:
	CXScdDrawCtrl_CfgGridChsBase();
	virtual ~CXScdDrawCtrl_CfgGridChsBase();

	CXScdDrawCtrl_CfgGridBase *m_pCtrlTitleGrid;
	CXScdDrawLines *m_pXscdLines;
//重载函数
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void UpdateDatas();

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL ChIsUsed_BeginObj(CExBaseObject *pObj); 
	BOOL ChIsUsed_EndObj(CExBaseObject *pObj);

// 	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);
// 	static void EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//绘图相关函数定义
public:

};
