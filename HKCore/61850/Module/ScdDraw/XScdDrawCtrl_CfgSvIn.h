//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_CfgSvIn.h  CXScdDrawCtrl_CfgSvIn

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"


//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_CfgGridTitleSvIn : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_CfgGridTitleSvIn();
	virtual ~CXScdDrawCtrl_CfgGridTitleSvIn();

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
class CXScdDrawCtrl_CfgGridChsSvIn : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_CfgGridChsSvIn();
	virtual ~CXScdDrawCtrl_CfgGridChsSvIn();

	CIecCfgDataBase *m_pIecfgData;

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
//CXScdDrawCtrl_CfgSvIn
class CXScdDrawCtrl_CfgSvIn : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_CfgSvIn();
	virtual ~CXScdDrawCtrl_CfgSvIn();

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
