//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

	CSclCtrlBase *m_pSclCtrl;	//������SCL���ƿ�
	CIecCfgDataBase *m_pCfgData;  //������CFG����

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
//���غ���
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowTitle(CExBaseObject *pData) = 0;

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);

	//��ͼ��غ�������
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
//���غ���
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void UpdateDatas();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL ChIsUsed_BeginObj(CExBaseObject *pObj); 
	BOOL ChIsUsed_EndObj(CExBaseObject *pObj);

// 	virtual void  Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc=NULL);
// 	static void EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//��ͼ��غ�������
public:

};
