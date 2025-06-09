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
#include "XScdDrawCtrl_SclSvInAll.h"
#include "XScdDrawCtrl_SclGsOut.h"
#include "XScdDrawCtrl_SclGsIn.h"
#include "XScdDrawCtrl_SclGsInAll.h"

#include "XScdDrawIedBase.h"


class CXScdDrawIedSclDetail : public CXScdDrawIedBase
{
public:
	CXScdDrawIedSclDetail();
	virtual ~CXScdDrawIedSclDetail();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_SCL;   }
	CString m_strIP;
	CString m_strManufacturer;

//˽�г�Ա����
private:

public:

public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);

	CXScdDrawCtrlBase* XCreateCtrl_SvIn_Scl(CSclCtrlsSmvIn *pSclCtrls, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsIn_Scl(CSclCtrlsGsIn *pSclCtrls, CWnd *pParentWnd);
	
	void XCreateCtrl_SvOut_Scl(CSclCtrlsSmvOut *pSclCtrls, CWnd *pParentWnd);
	void XCreateCtrl_GsOut_Scl(CSclCtrlsGsOut   *pSclCtrls, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_SvOut_Scl(CSclCtrlSmvOut  *pSclCtrl, CWnd *pParentWnd);
	CXScdDrawCtrlBase* XCreateCtrl_GsOut_Scl(CSclCtrlGsOut    *pSclCtrl, CWnd *pParentWnd);

//��ͼ��غ�������
public:
	//virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	void DrawLines(CDC *pDC, double fZoomRatio,const CPoint &ptOffset);

public:
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);
};

