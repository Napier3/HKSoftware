// RecordDrawMngrBase.h: interface for the CRecordDrawMngrBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RecordDrawMngrBase_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
#define AFX_RecordDrawMngrBase_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBaseMngr.h"
#include "DrawSysTime.h"
#include "ParaSort.h"
#define VER_MOVE_ONCE 1  //ͨ����ֱһ���ƶ�5������
#define TIME_MOVE_ONCE 1 //ʱ����һ���ƶ�һ��ʱ��
#define TIME_ZOOM_RATE 2 //ʱ��Ŵ���ʣ���С���䵹��
#define VER_ZOOM_RATE 1.5 //ͨ���Ŵ����
#define OUT_RANGE 5.0 //�ɼ����������ֵ

class CRecordDrawMngrBase : public CDrawBaseMngr  
{
public:
	CRecordDrawMngrBase();
	virtual ~CRecordDrawMngrBase();

public:
	CRect m_rcTimeandProgress;
	CDrawVariablesMngr  m_oVariableMngr;    //ͨ������  
// 	static long g_snWaveDrawAreaGap;
// 	static long g_snBottomRectHeight;
// 	static long g_snTimeandProgressRectHeight;
	double m_dRecordDataTimeLength;    //��ǰ¼�����ݵ��ܵ�ʱ�䳤�ȣ���λΪs
	double m_dMinTimeInOneSreen;       //��ǰ��Ļ�ܹ���ʾ����Сʱ�䳤�� ,��λΪ��
	double m_dMaxTimeInOneSreen;       //��ǰ��Ļ�ܹ���ʾ�����ʱ�䳤�� ,��λΪ��
	CDrawSysTime m_oDrawSysTime;       //ϵͳʱ�����
	CRect m_rcWaveDrawEx;              //���λ�ͼ�������չ

	//��ͼ�������ݵ����ʼ����ֹλ��
	double m_dDrawBeginTime;
	double m_dDrawEndTime;

public:
	virtual void InitDrawBeginEndTime();
	void SetRecordDataTimeLength(double dTime) {     m_dRecordDataTimeLength = dTime;   }

	//�̳еķ���
	UINT GetClassID()	{	return 0;	}
	virtual void Init();
	virtual void SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void SetParentWnd(CWnd* pParentWnd);
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	//����ķ���
	void SetMaxShowOneSreen(double dMaxShowOneSreen){		m_dMaxTimeInOneSreen	= dMaxShowOneSreen;	}
	void SelectNextChannel(CDrawBase *pChannel);
	void SelectPrevChannel(CDrawBase *pChannel);
	void AdjustChanState(); 
	void SelectChannel(CDrawVariable *pVariable);

	//������Ϣ
	virtual void SelectNextChannel();
	virtual void SelectPrevChannel();
	virtual void MoveChanDown();
	virtual void MoveChanUp();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void ArrowLeft();
	virtual void ArrowRight();
	virtual void ArrowDown();
	virtual void ArrowUp();
	virtual void ZoomInTime(long nMode = 0);//nMode = 0��ʾ�Բ��δ������Ľ������ţ�nMode = 1��ʾ�����������֮��Ĳ��Σ�nMode = 2��ʾ��������������
	virtual void ZoomOutTime(long nMode = 0);//nMode = 0��ʾ�Բ��δ������Ľ������ţ�nMode = 1��ʾ�����������֮��Ĳ��Σ�nMode = 2��ʾ��������������
	virtual void ZoomInChan();
	virtual void ZoomOutChan();

	virtual void DrawMainBack(CDC *pDC);
	virtual void DrawMain(CDC *pDC);


	virtual void ZoomOutTime_GetTimeCenter();//�Բ��δ������Ľ�������
	virtual void ZoomOutTime_GetTimeCursorXA();//��������������
	virtual void ZoomOutTime_GetTimeCursorXAXB();//�����������֮��Ĳ���
	virtual void ZoomInTime_GetTimeCursorXA();//���������зŴ�
	virtual void ZoomInTime_GetTimeCenter();//�Բ��δ������Ľ��зŴ�
	virtual void ZoomInTime_GetTimeCursorXAXB();//�Ŵ��������֮��Ĳ���

protected:
	void DrawWaveAreaBorder(CDC *pDC);
	void DrawGrid(CDC *pDC);
};

#endif // !defined(AFX_RecordDrawMngrBase_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
