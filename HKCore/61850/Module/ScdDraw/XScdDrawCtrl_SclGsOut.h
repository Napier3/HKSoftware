//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_SclGsOut.h  CXScdDrawCtrl_SclGsOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_SclGridTitleGsOut : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_SclGridTitleGsOut();
	virtual ~CXScdDrawCtrl_SclGridTitleGsOut();

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
class CXScdDrawCtrl_SclGridChsGsOut : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_SclGridChsGsOut();
	virtual ~CXScdDrawCtrl_SclGridChsGsOut();

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
//CXScdDrawCtrl_SclGsOut
class CXScdDrawCtrl_SclGsOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_SclGsOut();
	virtual ~CXScdDrawCtrl_SclGsOut();

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

