//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_SclSvInAll.h  CXScdDrawCtrl_SclSvInAll

#pragma once

#include "XScdDrawCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"


//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_GridTitleSclSvInAll : public CXScdDrawCtrl_CfgGridTitleBase
{
public:
	CXScdDrawCtrl_GridTitleSclSvInAll();
	virtual ~CXScdDrawCtrl_GridTitleSclSvInAll();

	//���غ���
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowTitle(CExBaseObject *pData);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:


};

//////////////////////////////////////////////////////////////////////////
class CXScdDrawCtrl_GridChsSclSvInAll : public CXScdDrawCtrl_CfgGridChsBase
{
public:
	CXScdDrawCtrl_GridChsSclSvInAll();
	virtual ~CXScdDrawCtrl_GridChsSclSvInAll();


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
//CXScdDrawCtrl_SclSvInAll
class CXScdDrawCtrl_SclSvInAll : public CXScdDrawCtrlBase
{
public:
	CXScdDrawCtrl_SclSvInAll();
	virtual ~CXScdDrawCtrl_SclSvInAll();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_CTRL_CFG_SVIN;   }

//˽�г�Ա����
private:
	CExBaseList m_listAllCh;

//˽�г�Ա�������ʷ���
public:

//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);
	virtual void CreateCtrlLines();

};

