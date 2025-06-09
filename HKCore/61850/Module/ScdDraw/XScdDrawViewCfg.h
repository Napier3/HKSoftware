//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawViewIedCfg.h  CXScdDrawViewIedCfg

#pragma once

#include "XScdDrawViewBase.h"
#include "..\CfgDataMngr\IecCfgDevice.h"
#include "XScdDrawIedCfg.h"

extern int  g_nCount_LeftIeds; //��������߱�IED�ĸ���������Ϊȫ�ֱ���
extern int  g_nCount_RightIeds; //�������ұ�IED�ĸ���������Ϊȫ�ֱ���

class CXScdDrawViewCfg : public CXScdDrawViewBase
{
public:
	CXScdDrawViewCfg();
	virtual ~CXScdDrawViewCfg();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_VIEW_CFG;   }

//˽�г�Ա����
private:
	CXScdDrawIedCfg *m_pMainIed;
	CExBaseList m_listIedGroup;
	CXScdIedGroup *m_pLeft;
	CXScdIedGroup *m_pRight;

//˽�г�Ա�������ʷ���
public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

protected:
	void InitXScdDrawView(CIecCfgDatasMngr *pCfgDatasMngr, CWnd *pParentWnd);
	void InitXScdDrawView(CIecCfgDatasSMV *pIecCfgDatasSMV, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd);
	void InitXScdDrawView(CIecCfgGinDatas *pIecCfgGinDatas, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd);
	void InitXScdDrawView(CIecCfgGoutDatas *pIecCfgGoutDatas, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd);
//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
// 	virtual void Pick(const CPoint &point, CExBaseList &oList);

public:
	virtual CSize Layout(CPoint &ptTopLeft);
	virtual CSize CalLayout(CSize &szDraw);
// 	virtual CSize CalLayoutOwn(CSize &szDraw);
// 	virtual CSize CalLayoutChildren(CSize &szDraw);

protected:
	CSize CalLayoutOtherIed();
	CSize CalLayoutOtherIed(CSize szSplit);

};

