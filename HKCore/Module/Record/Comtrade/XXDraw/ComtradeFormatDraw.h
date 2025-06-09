// ComtradeFormatDraw.h: interface for the CComtradeFormatDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined COMTRADEFORMATDRAW_H_
#define COMTRADEFORMATDRAW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComtradeAnalogDraw.h"
#include "ComtradeBinaryDraw.h"
#include "..\ComtradeMngr.h"
#include "..\..\MemBuffer\TMemBuffer.h"

#include "..\..\XDrawBase\XDrawViewBase.h"

#define ANALOG_DRAW_MODE_GROUP   0
#define ANALOG_DRAW_MODE_SIGLE    1

class CComtradeFormatDraw : public CXDrawViewBase  
{
public:
	CComtradeFormatDraw();
	virtual ~CComtradeFormatDraw();

protected:
	CComtradeMngr	*m_pCmtrdInterface;	//ͬ��ͼ��󶨵Ľӿ�����
	CMemBuffer_CPoint	*m_pMemBuf_Point;		//��ͼ�ĵ�����ݻ������ռ䣬����ʱ��������

	int		m_iTitleMaxLen;						////����ͨ���������󳤶�
	CMemBuffer_float	*m_pTimeDataBuff;

public:
	//�����������Ա����Ϊ��ͼ�ı�־
	BOOL	m_bShowTagBar;			//��Ϣ��ǩ
	BOOL	m_bShowUsedOnly;		//�Ƿ�ֻ��ʾʹ�õ�ģ��ͨ��
	int		m_nAnalogDrawMode;		//ģ��ͨ���Ļ�ͼģʽ 0��ͬ��ģ����һ����ƣ�1��ÿ��ģ����һ��ͼ��

// 	CPDBaseObjectList listDrawElement;	//��ͼͼԪ������

protected://ע���ͼ��
	void	RegisterComtradeDrawClass();
	void	UnRegisterComtradeDrawClass();

public:
	CComtradeDrawBaseClass*GetComtradeDrawClassByName(CString strType);
	BOOL IsAnalogDrawModeSingle()	{	return m_nAnalogDrawMode == ANALOG_DRAW_MODE_SIGLE;	}
	BOOL IsAnalogDrawModeGroup()	{	return m_nAnalogDrawMode == ANALOG_DRAW_MODE_GROUP;	}

public:
	void	InitIt();
	void	EndIt();

	//################################################################
	//����ͼ�ӿ�����ָ��ͬ��ͼ���
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	//void	BindComtradeInterface(CComtradeMngr*pInterface);

	//����������ͼ��־���ɻ�ͼͼԪ����
	void	InitDrawListByFlags(CDC*pDC);

protected:
	void XCreateElement_Group(CWnd *pParentWnd);
	void XCreateElement_Single(CWnd *pParentWnd);
	void XCreateElement_Binary(CWnd *pParentWnd);

private:
	//���ݻ�ͼ�ı�־����ͨ���ĵ�λ���ָ�ͨ��ԭ���ĵ�λ
	void	MakeCHUnitTheSame(CComtradeDrawBaseClass*pElement);
	void	ResumeCHUnit(CComtradeDrawBaseClass*pElement);
	//�ٽ����е�ͨ�������ͼͼԪ��֮�󣬱�����������Ŀ̶ȷ�Χ
	void	SetElementAxisRange();
	//�����ǻ�ͼģʽ�ı�Ľӿں���
	
protected:
	void	GetCHTitleMaxLength();						//��ø�ͨ���������󳤶�
	void	TypeSetAllElement(CSize size,long &lDrift);	//�Ի�ͼԪ�б�����Ű�
	void	TypeSetAllElementAgain(CSize size,long &lDrift);	//�����Ű�
	void	InitCHTitlePosAfterTypeset();						//�Ű���ͨ�����ݵı���λ�ý��г�ʼ��
	void	InitDrawElementAxis();				//��ʼ������ϵ
public:
	//��ʼ����ͼ�Ľӿں���
	void	InitDrawElement(CSize size,long &lDrift);	//�����ͼ����Ĵ�С�����ø���ͼͼԪ��λ��
public:
	//��ͼ�ӿں���
	void	DrawTheGraph(CDC*pDC);			//�ܵĻ�ͼ����
	void	DrawTheGraphCurve(CDC*pDC);
	void	DrawComtrade(CDC*pDC);			//���ƻ�ͼͼԪ�е�ͼ��
private:
	int		m_iBeginIndex,m_iEndIndex;		//��ͼ����ʼ����ֹ��
	void	SetDrawBeginEndIndex(int iBeginIndex,int iEndIndex);
	void	DrawTheComtradeCurve(CComtradeDrawBaseClass*pElement,int iActiveCHIndex=-1);

//###################################################################
//ͼ�β�����ͨ�ú���
private:
	void SetElementAxisXRange();
	void FindBeginEndIndex(float fBT,float fET);
	void HalfSearchIndex(float fTime,int &iTimeIndex);
	void GetElementAxisUnit(float &fAxisUnit);
public:
	int  FindTimeIndex(float fTime);
//����ͼ�εĲ���������ͼ�εķŴ���С���ƶ�
public:
	void OnCmtrdGrphOP_Zoomout();		//ͼ�ηŴ�
	void OnCmtrdGrphOP_Resume();		//ͼ�θ�ԭ
	void OnCmtrdGrphOP_Zoomin();		//ͼ�ε���С
	void OnCmtrdGrphOP_Moveleft();		//�����ƶ�
	void OnCmtrdGrphOP_Moveright();		//�����ƶ�

	void OnCmtrdGrphOP_RangeZoomout(int iXL,int iXR);	//ͼ������Ŵ�
	void OnCmtrdGrphOP_RangeZoomout(float fTime1,float fTime2);	//ͼ������Ŵ�

	void GetTimeByCursorPos(int iXL,int iXR,float &fTime1,float &fTime2);
	void GetXPosByTimeVal(float fTime1,int &iXPos);
//���������Ķ���ӿں���
public:
	//�������ͼԪ�Ļ�ͼ�ľ��ε�λ��
	CRect* GetAllElementRectPos();
	int  GetTotalElement();

	//�������ѡ�л��ͼԪ�е�ͨ�����Ƶ���س�Ա�ͺ���
private:
	CComtradeDrawBaseClass*	m_pNowActElement;

public:
	BOOL	OnLButtonDown(CPoint point);
	BOOL	OnLButtonDown(CPoint point,CDC*pDC);
	BOOL	OnLButtonDown(CPoint point,CWnd*pParent);
	CComtradeDrawBaseClass*GetNowActiveElement(CPoint point);
	CComtradeDrawBaseClass*GetNowActiveElement();
	int		GetNowActCHIndex();
	void	SetNowActiveElement(CComtradeDrawBaseClass*pElement);
};

#endif // !defined(COMTRADEFORMATDRAW_H_)
