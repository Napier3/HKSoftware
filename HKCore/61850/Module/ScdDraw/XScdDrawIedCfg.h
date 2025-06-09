//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawGlobal.h"

#include "XScdDrawCtrl_CfgSvOut.h"
#include "XScdDrawCtrl_CfgSvIn.h"
#include "XScdDrawCtrl_CfgGsOut.h"
#include "XScdDrawCtrl_CfgGsIn.h"

#include "XScdDrawCtrl_SclSvOut.h"
#include "XScdDrawCtrl_SclSvIn.h"
#include "XScdDrawCtrl_SclGsOut.h"
#include "XScdDrawCtrl_SclGsIn.h"

#include "XScdDrawIedBase.h"


class CXScdDrawIedCfg : public CXScdDrawIedBase
{
public:
	CXScdDrawIedCfg();
	virtual ~CXScdDrawIedCfg();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_CFG;   }
	CString m_strIP;
	CString m_strManufacturer;

//˽�г�Ա����
private:

	 BOOL m_Symble_MainIed;//����һ������IED�ı�־���������ֵ�һ��IED�ͺ����IED

public:
	void SetSymbleMainIed(BOOL pSymble_MainIed) {m_Symble_MainIed=pSymble_MainIed; }
	BOOL GetSymbleMainIed() {return m_Symble_MainIed;}


	 //˽�г�Ա�������ʷ���
public:
	CXScdDrawCtrlBase* XCreateCtrl_SvIn_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_SvOut_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsIn_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsOut_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);

	CXScdDrawCtrlBase* XCreateCtrl_SvIn_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_SvOut_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsIn_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsOut_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd);

//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	void DrawLines(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

public:
	CSize CalLayout(CSize &szDraw);

	virtual CSize Layout(CPoint &ptTopLeft);

};

