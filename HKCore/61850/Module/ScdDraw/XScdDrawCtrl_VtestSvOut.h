//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_VtestSvOut.h  CXScdDrawCtrl_VtestSvOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_VtestGridTitleSvOut : public CXScdDrawCtrl_VtestGridTitleBase
{
public:
	CXScdDrawCtrl_VtestGridTitleSvOut();
	virtual ~CXScdDrawCtrl_VtestGridTitleSvOut();

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
class CXScdDrawCtrl_VtestGridChsSvOut : public CXScdDrawCtrl_VtestGridChsBase
{
public:
	CXScdDrawCtrl_VtestGridChsSvOut();
	virtual ~CXScdDrawCtrl_VtestGridChsSvOut();

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

class CXScdDrawCtrl_VtestSvOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_VtestSvOut();
	virtual ~CXScdDrawCtrl_VtestSvOut();

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

public:

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);

};

