//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_SclGsIn.h  CXScdDrawCtrl_SclGsIn

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_SclGridTitleGsIn : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_SclGridTitleGsIn();
	virtual ~CXScdDrawCtrl_SclGridTitleGsIn();

	//���غ���
public:
	virtual void ShowTitle(CExBaseObject *pData);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_SclGridChsGsIn : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_SclGridChsGsIn();
	virtual ~CXScdDrawCtrl_SclGridChsGsIn();

	//���غ���
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_ChDataType_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:

};

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_SclGsIn
class CXScdDrawCtrl_SclGsIn : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_SclGsIn();
	virtual ~CXScdDrawCtrl_SclGsIn();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVIN;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);

};

