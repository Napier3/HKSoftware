//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_CfgGsOut.h  CXScdDrawCtrl_CfgGsOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridTitleGsOut : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_CfgGridTitleGsOut();
	virtual ~CXScdDrawCtrl_CfgGridTitleGsOut();

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
class CXScdDrawCtrl_CfgGridChsGsOut : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_CfgGridChsGsOut();
	virtual ~CXScdDrawCtrl_CfgGridChsGsOut();

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
//CXScdDrawCtrl_CfgGsOut
class CXScdDrawCtrl_CfgGsOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_CfgGsOut();
	virtual ~CXScdDrawCtrl_CfgGsOut();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVOUT;   }

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
