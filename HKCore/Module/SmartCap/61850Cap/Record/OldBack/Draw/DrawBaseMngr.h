// DrawBaseMngr.h: interface for the CDrawBaseMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DrawBaseMngr_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_)
#define AFX_DrawBaseMngr_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBaseList.h"
#include "DrawBinaryVariable.h"
#include "DrawAnalogVariable.h"
#include "DrawTimeAxis.h"
#include "DrawTimeCursor.h"
#include "DrawVariablesMngr.h"
#include "DrawBinaryVariableGroup.h"
// #include "DrawAttrSpy.h"
//#include "DrawAnalogComplexVariable.h"
#include "NameSort.h"
#include "DrawGlobalDef.h"
#include "..\RecordDefine.h"
#include "..\RecordGlobalDefine.h"

#include "..\..\..\..\..\Module\BaseClass\MemBufferDC.H"

//˵����m_listChild���е�ֻ��ͨ������
#define BINRAR_TO_BOTTOM 5
#define ANALOG_GAP 8
#define WAVE_BORDER_TO_RIGHT 5 
#define MAX_DRAWGAP1 100   //ʾ�����ĵȼ��ȡ����Gap
#define MAX_DRAWGAP2 200   //�����ȼ��ȡ����Gap
#define AnalyseWnd_MaxDrawlength 60000 //���������ÿ�������Ƶĳ��ȣ����ʮ����

class CDrawBaseMngr : public CDrawBaseList  
{
public:
	CDrawBase       *m_pCurrDrawObj;        //��ǰѡ�еĻ�ͼ����
	CDrawVariable   *m_pCurrDrawVariable;   //��ǰͨ������
	CDrawTimeCursor *m_pTimeCursorDraw;     //ʱ����
	CDrawTimeAxis   m_oTimeAxisDraw;        //ʱ����	
	CDrawRangeStateAxis *m_pRangeStateAxis; //ʱ��������

	//����������
	CMemBuffer_CPoint* m_pPointBuffer;//CPoint
	CMemBufferInterface* m_pRefBuffer;
	//CMemBuffer_Float*  m_pfAttrBuffer;
	MrDraw::DRAWMEMBUFFERPOS m_oDrawBufferPos;
	//��������
	CRect m_rcNameAndRangeAxis;
	CRect m_rcTimeAxis;
	CRect m_rcWaveDraw;
	CMemBufferDC m_oDrawMemDC;

	long m_nMaxGapValue;
	UINT m_nSamRateForDraw;//������

	//����ɫ

public:
	//�̳еķ���
	virtual void SetBorder(const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void CreateDrawMemDC(CDC *pDC, const CRect &rcClient);				//������ͼ����
	virtual void SetParentWnd(CWnd* pParentWnd);
	
	virtual LONG MouseMove(UINT nFlags, CPoint point);
	virtual LONG LButtonDown(UINT nFlags, CPoint point); 
	virtual LONG LButtonUp(UINT nFlags, CPoint point);
	virtual LONG RButtonDown(UINT nFlags, CPoint point);
	virtual LONG RButtonUp(UINT nFlags, CPoint point);
	virtual void Draw(CDC* pDC);
	virtual void Init();
	virtual UINT GetClassID()			{	return 0;	}
	virtual void SetCurrentShowTimeRange(double dMax, double dMin);
	virtual void GetCurrentShowTimeRange(double& dMax, double& dMin);
	virtual void SetTimeRange(double dMax, double dMin);
	virtual void GetTimeRange(double& dMax, double& dMin);

	//����ķ���
	void MoveChannel(CDrawBase *pChannel, double dOffset);
	void ZoomChannel(CDrawBase *pChannel, double dRate);
	void MoveTimeAxis(double dOffset =0);
	void ZoomTimeAxis(double dRate);
	void MoveTimerCursor(double dOffset);
	virtual BOOL CalCurrentDataPos(double dMax, double dMin);
	virtual void CalXPos(long nTotalPoints);
	void AdjustDrawVariablePosition(BOOL bUseClipRect = TRUE);

	void OnTimeAxisPositionchanged();
	double DecivePointToLogicPointTime(long x);

	void AdjustDrawNameRect();
	BOOL ReCompositor();
	BOOL ReCompositorEx();
	
	BOOL InitShowDrawVariables(CDrawVariablesMngr &oVariableMngr);

    void SetDrawDataRange(long nBeginPos1,long nEndPos1,long nBeginPos2 = -1,long nEndPos2 = -1)
	{
		m_oDrawBufferPos.nBuf1BeginPos  = nBeginPos1;
		m_oDrawBufferPos.nBuf1EndPos	= nEndPos1;
		m_oDrawBufferPos.nBuf2BeginPos  = nBeginPos2;
		m_oDrawBufferPos.nBuf2EndPos	= nEndPos2;

		if (nBeginPos2 >= 0)
		{
			m_oDrawBufferPos.nBufLength = nEndPos1 - nBeginPos1 + nEndPos2 - nBeginPos2 + 2;
		} 
		else
		{
			m_oDrawBufferPos.nBufLength = nEndPos1 - nBeginPos1 + 1;
		}
	}
public:
	CDrawBaseMngr();
	virtual ~CDrawBaseMngr();
	void FreeAll()
	{
		DeleteAll();
		m_pCurrDrawObj = NULL;
		m_pCurrDrawVariable = NULL;
		m_pRefBuffer = NULL;
		m_pRangeStateAxis->DettachVariable();
	}

	void SetVariableMoveCursor(HCURSOR hCursor);
	void SetVariableZoomCursor(HCURSOR hCursor);
	void SetVariableProhibitCursor(HCURSOR hCursor);
	void SetTimeAxisMoveCursor(HCURSOR hCursor);
	void SetTimeAxisZoomCursor(HCURSOR hCursor);
	void SetTimeAxisProhibitCursor(HCURSOR hCursor);
	CDrawRangeStateAxis* GetChannelRangeStateAxis()       {    return m_pRangeStateAxis;                               }
	CDrawRangeStateAxis* GetTimeAxisRangeStateAxis()      {    return &(m_oTimeAxisDraw.m_oRangeAxis.m_oRangeState);   }

	virtual void DrawMain(CDC *pDC);
	virtual void DrawSubject(CDC *pDC);
	CDrawVariable* FindVariable(CMemBuffer_Long *pBuffer);
	void AddVariableByIndex(CDrawVariable *pVariable);
	void InitParaRectByNameRect();

private:
	void AttachRangeStateAxisVariable();
};

#endif // !defined(AFX_DrawBaseMngr_H__64430395_E132_4498_8453_FF07ECA0AEB7__INCLUDED_)
