//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_SclSvOut.h  CXScdDrawCtrl_SclSvOut

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_SclGridTitleSvOut : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_SclGridTitleSvOut();
	virtual ~CXScdDrawCtrl_SclGridTitleSvOut();

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
class CXScdDrawCtrl_SclGridChsSvOut : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_SclGridChsSvOut();
	virtual ~CXScdDrawCtrl_SclGridChsSvOut();

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

class CXScdDrawCtrl_SclSvOut : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_SclSvOut();
	virtual ~CXScdDrawCtrl_SclSvOut();

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

