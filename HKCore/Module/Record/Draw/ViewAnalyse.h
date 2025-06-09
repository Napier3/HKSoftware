#if !defined(AFX_UIWNDANALYSE_H__BDBAA802_027D_48DB_800A_5DCC44066E64__INCLUDED_)
#define AFX_UIWNDANALYSE_H__BDBAA802_027D_48DB_800A_5DCC44066E64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewAnalyse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewAnalyse window
#include "../../BaseClass/MemBufferDC.H"
#include "RecordTestDrawBase.h"
#include "../RecordGlobalDefine.h"
#include "ParaSort.h"

#include "../MR1200BaseApp.h"
// #include "../RecordTest/RecordTest.h"
// #include "../Comtrade/ComtradeMngr.h"
#define MIN_PELS 40                     //����Ŵ����С��Χ
#define ZOOMBMP_TO_CURSOR 2

#define RECORDBUFFERTYPE_RECORDBUFFER    0
#define RECORDBUFFERTYPE_MAPFILEBUFFER   1

//������ͨ��¼������
class CViewAnalyse :public CRecordTestDrawBase
{
// Construction
public:
	CViewAnalyse();
	virtual ~CViewAnalyse();

	//CMemBufferDC m_oMemDC;
	//��ʱû����
	//long m_nShowContent;//��ʾ���ݣ�0-ʵ�����ݣ�1-���ļ�������

	//ԭ��Ƶ�Ŀ���ǿ��Խ���ͬ��ͨ�����ڲ�ͬ��page��
	//CDrawBaseObjectList m_listDrawPages;  
	//CDrawVariablesMngr* m_pCurrentPageVariables;//��ǰҳ���ͨ��
	
	//¼�����ݵĳ���
	double m_dOscillographTimeLong;
	MrDraw::DRAWMEMBUFFERPOS m_oOscillographBufferPos;

	BOOL m_bRecordPageChanged;
	double m_dAxisMinTimeBack;
	double m_dAxisMaxTimeBack;

	BOOL m_bWaveAnalyse;
	
// Attributes
public:
// 	//�ؼ���
	long m_nPostSysOptr;
	long m_nPostSysTimer;
	long m_nRecordBufferType;   //¼�����ݵ�����0=RecordBuffer��1=RecordMapFile

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewAnalyse)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual void InitDrawBeginEndTime();
	virtual void InitDrawPoints();		

	//��CDrawMr1200RecordBase�̳еĺ���
	virtual void InitDrawBufferPos();
	virtual void SelectNextChannel();
	virtual void SelectPrevChannel();
	virtual void MoveChanDown();
	virtual void MoveChanUp();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void ArrowLeft();
	virtual void ArrowRight();
	virtual void ArrowUp();
	virtual void ArrowDown();
	virtual void ZoomInTime(long nMode = 0);
	virtual void ZoomOutTime(long nMode = 0);
	virtual void ZoomInChan();
	virtual void ZoomOutChan();

	//��CUIWindowBase������
	virtual void Enable(long nEnable, BOOL bEnableWindow);
	virtual BOOL UICreate(CWnd *pParent);
	virtual long InitAttributes();
	virtual long OnSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount);
	virtual CBaseObject* CreateNewAttributeChild(long nClassID);
	virtual CBaseObject* CreateNewAttributeChild(LPCTSTR pszClassID);
	//virtual long SerializeOwn(CBinarySerializeBuffer &oBinaryBuffer);
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual UINT GetClassID() {        return CMTRDCLASSID_WNDWAVEANALYSE;                               }

	//����
	//void CreateVariablesFromComtradeFile(int& nAnalogChanAmount, int& nBinaryChanAmount,long nDataPoints);
	void GetSaveDataPos(long nMode,long& nBegin1,long& nLen1,long& nBegin2,long& nLen2);	
//	void SetCurrentShowContent(long nSet)	{	m_nShowContent = nSet;	}//��ʱû����

	//virtual BOOL CalCurrentDataPosEx(MrDraw::DRAWMEMBUFFERPOS &oDrawBufferPos, long nSampleRate, double dMax,double dMin);
	virtual BOOL CalCurrentDataPos(double dMax,double dMin);
	virtual long CalCurrentDataPosEx(double dMax,double dMin
		, CRecordTest *pRecordTest
		, CMemBufferInterface *pRefBuffer
		, MrDraw::DRAWMEMBUFFERPOS &oDrawBufferPos
		, MrDraw::DRAWMEMBUFFERPOS &oOscillographBufferPos);


	virtual void InitFromComtrade();
	virtual void InitFromRecordTest(long nDataLen, long nSamRateForDraw);

	void InitFromRecordTest();
	void CalXPosByTimeAxis(double dMax=-1, double dMin=-1);
	void InitDrawVariablesByRecordTest();
	void CreateMemDC();				//������ͼ����
	virtual void InitTimeAxis();  //2022-4-24  lijunqing ��ʼ��ʱ�����꣬�ɱ��������ø��Ի�
	
	void SetTimeMoveCursor(HCURSOR hCursor) {	m_pTimeCursorDraw->SetMoveCursor(hCursor);	}

	//������ʾ������
	void CalParaRect();
	void DrawPara(CDC* pDC);
	void InitByBorder();
	void AdjustAllDrawObjectsPos();
	void DrawAnalyse();
	void OnDraw(CDC *pDC);
	
	static UINT  DrawAnalyseThread(LPVOID pParam);
	static UINT  ReadOnlineDataThread(LPVOID pParam);
	static UINT  ReadComtradeFileThread(LPVOID pParam);
	BOOL m_bInDrawAnalyseThread;

protected:
	void XOnMouseMove(UINT nFlags, CPoint point);
	void XOnLButtonDown(UINT nFlags, CPoint point);
	void XOnLButtonUp(UINT nFlags, CPoint point);
	void XOnRButtonDown(UINT nFlags, CPoint point);
	void XOnRButtonUp(UINT nFlags, CPoint point);
// 	afx_msg void OnPaint();
	void XOnLButtonDblClk(UINT nFlags, CPoint point);
	void XOnRButtonDblClk(UINT nFlags, CPoint point);
	void OnSizeEx(UINT nType, int cx, int cy);

	LRESULT XOnInvalidateVertRangeStateAxis(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariableSizeChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariablePositionChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariableSelectChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeAxisChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeCursorPositionChange(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeCursorSelectChange(WPARAM wParam, LPARAM lParam);
	LRESULT XOnSaveComtradeFile(WPARAM wParam, LPARAM lParam);
	LRESULT XOnTimeCursorMessage(WPARAM wParam, LPARAM lParam);
	//LRESULT XOnDrawVariableShowChanged(WPARAM wParam, LPARAM lParam);
	//LRESULT XOnSetVariableAxisRange(WPARAM wParam, LPARAM lParam);
	LRESULT XOnVariableShow(WPARAM wParam, LPARAM lParam);
	LRESULT XOnAnalyseRecordViewMapChanged(WPARAM wParam, LPARAM lParam);
	LRESULT XOnOnlineRecordWriteFinished(WPARAM wParam, LPARAM lParam);
	LRESULT XOnOnlineRecordDataCopy(WPARAM wParam, LPARAM lParam);
	LRESULT XOnDrawSetChanged(WPARAM wParam, LPARAM lParam);

protected:
// 	BOOL m_bByRecordTest;
	BOOL m_bCanChanged;//����ʹ�����Ȧ������Ŵ�
	//MR1200SYSANALYSEMNGR m_oDrawVarsOld;//����ԭ����¼�����ã����˳���ʱ��ָ�ԭ��������,fdp add 2010.7.7
	void LoadZoomBmp();

	//fdp add 2010.6.4
	long m_nAttrSpyState[MAX_MR1200_CHANNELS][MAX_MR1200_VARIABLE_ATTR_BUFFERS];//�������״̬�ı���
	long m_nVariableSpyState[MAX_MR1200_CHANNELS];
//	void SaveLastSpyState(); //�������״̬
//	void ReSetSpyState();    //������ͨ��������������ļ���״̬�ص�ԭ����״̬
//	void InitBackUpSpyState(); //��ʼ��m_nAttrSpyState��m_nVariableSpyState����
//	void SetVariableRect();
//	BOOL CalCurrentDataPosByOpenFile(double dMax,double dMin);
//	void CalPara(long nBeginPos);
	virtual void InitCurrDrawPageVariables();//chenling ��Ҫ�ı�m_nTextHeight�ĸ߶� �ĳ��麯��
	void AttachCurrentVariable();

	//�������Ƶ�����ͨ������������ֻ�������right��ֵ
	void InitDrawRectByDrawStruct();
	void ReSetBorder(const CRect &rect);
	void ReSetMainRect(const CRect &rect);

	CDrawVariable* FindDrawVariableBySelIndex(long nIndex);
	void InitViewAnalyse();

	//fdp add 2010.7.7
	void InitDrawVarRect();
	void SetBorder();
	
	//�������л�ͼ�����Parent����
	void SetAllObjParentWnd();

private:
	BOOL IsUseRecorBuffer()      {    return (m_nRecordBufferType == RECORDBUFFERTYPE_RECORDBUFFER);    }
	BOOL IsUseMapFileBuffer()    {    return (m_nRecordBufferType == RECORDBUFFERTYPE_MAPFILEBUFFER);   }

//////////////////////////////////////////////////////////////////////////
//ʹ��ӳ���ļ�����ش���
private:
#define DRAW_HEIGHT   20
#define WAIT_DRAW_POS   10
#define ONLINE_WITE_DRAW_POS   -30
#define CALTHREAD_DRAW_POS   -50

	void MapRecorBuffer(double dBeginTime, double dTimeLong);
	void DrawWait();
	void DrawInWritingState();
	void DrawCalThreadState();
	void DrawRecordDataBufferState(long nTotal, long nIndex);
	void DrawSaveComtradeFileState(long nTotal, long nIndex);
	
	long GetAnalogVariableCount();
	BOOL m_bHasUICreated;

public:
	virtual void SetInRecordProcessThreadState(BOOL bInState = TRUE);
	void FireTimeAxisChangedSysOptr();

	void WaveAnalyse();
	void CalValues();
	BOOL CalValues(long nTimeCursorPos);

	void WriteAttrFile(long nAttrID);
};


extern BOOL g_bWriteAttrFileWhenWaveAnalyse;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UIWNDANALYSE_H__BDBAA802_027D_48DB_800A_5DCC44066E64__INCLUDED_)
