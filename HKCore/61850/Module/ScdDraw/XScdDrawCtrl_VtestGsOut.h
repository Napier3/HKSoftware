//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_VtestGsOut.h  CXScdDrawCtrl_VtestGsOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_VtestGridTitleGsOut : public CXScdDrawCtrl_VtestGridTitleBase
{
public:
	CXScdDrawCtrl_VtestGridTitleGsOut();
	virtual ~CXScdDrawCtrl_VtestGridTitleGsOut();

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
class CXScdDrawCtrl_VtestGridChsGsOut : public CXScdDrawCtrl_VtestGridChsBase
{
public:
	CXScdDrawCtrl_VtestGridChsGsOut();
	virtual ~CXScdDrawCtrl_VtestGridChsGsOut();

	//���غ���
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:

};

//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VtestGsOut
class CXScdDrawCtrl_VtestGsOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_VtestGsOut();
	virtual ~CXScdDrawCtrl_VtestGsOut();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVOUT;   }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);

};

