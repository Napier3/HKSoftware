//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "..\..\..\Module\XDrawBase\XDrawElements.h"
#include "XScdDrawGlobal.h"
#include "XScdDrawIedBase.h"

#include "XScdDrawCtrl_ThumbSvOut.h"
#include "XScdDrawCtrl_ThumbSvIn.h"
#include "XScdDrawCtrl_ThumbGsOut.h"
#include "XScdDrawCtrl_ThumbGsIn.h"
#include "XScdDrawLineBase.h"
#include "XScdDrawLine_Ctrls.h"

#define IEDTHUMBNAILTYPE_PROCMEAS 1
#define IEDTHUMBNAILTYPE_MUCTRL 2
#define IEDTHUMBNAILTYPE_PROCMEAS2 3



class CXScdDrawIedThumbnail : public CXScdDrawIedBase
{
public:
	CXScdDrawIedThumbnail();
	virtual ~CXScdDrawIedThumbnail();

//���غ���
public:
 	virtual UINT GetClassID() {    return XSCDDRAW_IED_THUMBNAIL;   }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
	CSclIed *m_pRefIed;
	int m_b_ProtMeas_MuCtrl;

//˽�г�Ա�������ʷ���
public:
	void SetRefIed(CSclIed *pRefIed) {m_pRefIed=pRefIed;}
	CSclIed* GetRefIed() {return m_pRefIed;}

	void SetSymbel (int b_ProtMeas_MuCtrl) {m_b_ProtMeas_MuCtrl = b_ProtMeas_MuCtrl;}
	int GetSymbel() {return m_b_ProtMeas_MuCtrl;}

	BOOL IsIed_RPIT_MU()	{	return m_pRefIed->IsIed_RPIT_MU();	}
	BOOL IsIed_MU()			{	return m_pRefIed->IsIed_MU();	}
	BOOL IsIed_RPIT()		{	return m_pRefIed->IsIed_RPIT();	}
	BOOL IsIed_Prot_Meas()	{	return m_pRefIed->IsIed_Prot_Meas();	}
	BOOL IsIed_Prot()		{	return m_pRefIed->IsIed_Prot();	}
	BOOL IsIed_Meas()		{	return m_pRefIed->IsIed_Meas();	}

	//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

	CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);

	virtual void  XCreateCtrl(CSclIed *pIedData, CWnd *pParentWnd);
	virtual void  XCreateCtrl(CWnd *pParentWnd);
	virtual void GetAllLines(CXDrawElements &oScdLines);
	virtual void CreateCtrlLines();
	void FilterAllLines(CXDrawElements &oScdLines);//�����е��߽����жϣ��Ƿ�Ϊ�������װ��֮������ߣ����Ǳ������װ����ϲ���Ԫ�����ն�֮�������


	CXScdDrawCtrl_ThumbSvOut* GetCtrl_ThumbSvOut();
	CXScdDrawCtrl_ThumbSvIn* GetCtrl_ThumbSvIn();
	CXScdDrawCtrl_ThumbGsOut* GetCtrl_ThumbGsOut();
	CXScdDrawCtrl_ThumbGsIn* GetCtrl_ThumbGsIn();

	virtual void CreateCtrlBusLines();

};

