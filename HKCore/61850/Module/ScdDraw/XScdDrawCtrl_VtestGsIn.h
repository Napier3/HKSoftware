//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_VtestGsIn.h  CXScdDrawCtrl_VtestGsIn

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_VtestGridTitleGsIn : public CXScdDrawCtrl_VtestGridTitleBase
{
public:
	CXScdDrawCtrl_VtestGridTitleGsIn();
	virtual ~CXScdDrawCtrl_VtestGridTitleGsIn();

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
class CXScdDrawCtrl_VtestGridChsGsIn : public CXScdDrawCtrl_VtestGridChsBase
{
public:
	CXScdDrawCtrl_VtestGridChsGsIn();
	virtual ~CXScdDrawCtrl_VtestGridChsGsIn();

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
//CXScdDrawCtrl_VtestGsIn
class CXScdDrawCtrl_VtestGsIn : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_VtestGsIn();
	virtual ~CXScdDrawCtrl_VtestGsIn();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVIN;   }

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

