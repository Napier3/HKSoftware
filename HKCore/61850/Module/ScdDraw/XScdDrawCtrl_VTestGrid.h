//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

	//���غ���
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowTitle(CExBaseObject *pData) = 0;
	virtual CDataType* FindDataType(const CString &strDataType);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_VTestGridChsBase : public CExBaseListXGridCtrlBase
{
public:
	CXScdDrawCtrl_VTestGridChsBase();
	virtual ~CXScdDrawCtrl_VTestGridChsBase();

//���غ���
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

// 	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);
// 	static void EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//��ͼ��غ�������
public:

};
