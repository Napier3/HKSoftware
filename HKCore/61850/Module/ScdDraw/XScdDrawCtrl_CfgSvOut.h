//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_CfgSvOut.h  CXScdDrawCtrl_CfgSvOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridTitleSvOut : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_CfgGridTitleSvOut();
	virtual ~CXScdDrawCtrl_CfgGridTitleSvOut();

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
class CXScdDrawCtrl_CfgGridChsSvOut : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_CfgGridChsSvOut();
	virtual ~CXScdDrawCtrl_CfgGridChsSvOut();

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

class CXScdDrawCtrl_CfgSvOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_CfgSvOut();
	virtual ~CXScdDrawCtrl_CfgSvOut();

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

public:

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);
};
