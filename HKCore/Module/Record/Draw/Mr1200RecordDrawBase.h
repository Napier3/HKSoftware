// Mr1200RecordDrawBase.h: interface for the CDrawMr1200RecordBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MR1200RECORDDRAWBASE_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
#define AFX_MR1200RECORDDRAWBASE_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XRecordDrawBase.h"
#include "..\RecordTest\RecordTest.h"
#include "..\DRAW\DrawSysTime.h"

#define VER_MOVE_ONCE 1  //ͨ����ֱһ���ƶ�5������
#define TIME_MOVE_ONCE 1 //ʱ����һ���ƶ�һ��ʱ��
#define TIME_ZOOM_RATE 2 //ʱ��Ŵ���ʣ���С���䵹��
#define VER_ZOOM_RATE 1.5 //ͨ���Ŵ����
#define OUT_RANGE 5.0 //�ɼ����������ֵ


class CDrawMr1200RecordBase : public CXRecordDrawBase  
{
public:
	CDrawMr1200RecordBase();
	virtual ~CDrawMr1200RecordBase();

public:
	CRect m_rcTimeandProgress;
	CExBaseList  m_oVariableMngr;    //ͨ������  
	double m_dRecordDataTimeLength;    //��ǰ¼�����ݵ��ܵ�ʱ�䳤�ȣ���λΪs
	double m_dMinTimeInOneSreen;       //��ǰ��Ļ�ܹ���ʾ����Сʱ�䳤�� ,��λΪ��
	double m_dMaxTimeInOneSreen;       //��ǰ��Ļ�ܹ���ʾ�����ʱ�䳤�� ,��λΪ��
	CDrawSysTime m_oDrawSysTime;       //ϵͳʱ�����
	//CRect m_rcWaveDrawEx;              //���λ�ͼ�������չ

	//��ͼ�������ݵ����ʼ����ֹλ��
	double m_dDrawBeginTime;
	double m_dDrawEndTime;

	CRecordTest *m_pRecordTest;

public:
	//�ۺ����Ի�ͼ
	void AddAttrsDraw();
	
	//�õ���������λ��
	long GetCalAttrBeginPos(long nTimeCursorPos);

	virtual void InitDrawBeginEndTime();
	virtual void SetRecordDataTimeLength(double dTime) {     m_dRecordDataTimeLength = dTime;   }

	//�̳еķ���
	UINT GetClassID()	{	return 0;	}
	virtual void Init();
	//virtual void SetBorder(CDC *pDC, const CRect &rect, BOOL bUseClipRect=TRUE);
	virtual void SetParentWnd(CWnd* pParentWnd);
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	//����ķ���
	virtual void SetMaxShowOneSreen(double dMaxShowOneSreen){		m_dMaxTimeInOneSreen	= dMaxShowOneSreen;	}
	void SelectNextChannel(CDrawBase *pChannel);
	void SelectPrevChannel(CDrawBase *pChannel);
	void AdjustChanState(); 
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

// 	virtual void DrawMainBack(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
// 	virtual void DrawMain(double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
// 	virtual void DrawMain_Wave(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);


	virtual void ZoomOutTime_GetTimeCenter();//�Բ��δ������Ľ�������
	virtual void ZoomOutTime_GetTimeCursorXA();//��������������
	virtual void ZoomOutTime_GetTimeCursorXAXB();//�����������֮��Ĳ���
	virtual void ZoomInTime_GetTimeCursorXA();//���������зŴ�
	virtual void ZoomInTime_GetTimeCenter();//�Բ��δ������Ľ��зŴ�
	virtual void ZoomInTime_GetTimeCursorXAXB();//�Ŵ��������֮��Ĳ���

	virtual void SaveRecordDrawObjectControl();
	virtual void InitRecordDrawObjectPosByControl();

// protected:
// 	void DrawWaveAreaBorder(CDC *pDC);
// 	void DrawGrid(CDC *pDC);
// 	void DrawMainEx(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);


public:
	//COMTRADEFILE����
	static UINT  SaveComtradeFileThread(LPVOID pParam);
	virtual void SetInRecordProcessThreadState(BOOL bInState);
	virtual void GetComtradeSaveDataPos(long nMode,long& nBegin1,long& nLen1,long& nBegin2,long& nLen2);
	virtual void DrawSaveComtradeFileState(CDC *pDC, CRect rcBorder, long nTotal, long nIndex);
	virtual void InitComtradeChannels(CRcdComtradeFile *pComtradeFile);

protected:
// 	double m_dDeltaT;
// 	double m_dTa;
// 	double m_dTb;

	virtual void FireTimeAxisChangedSysOptr(double dTOffset);
	CDrawVariable* GetNextVariable(CDrawVariable *pCurr);
	CDrawVariable* GetPrevVariable(CDrawVariable *pCurr);


};

extern double g_dCursorTime[3];

#endif // !defined(AFX_MR1200RECORDDRAWBASE_H__4BF6353F_793C_4EA6_9EDD_54F2BA25F364__INCLUDED_)
