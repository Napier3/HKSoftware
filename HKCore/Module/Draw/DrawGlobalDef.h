// DrawGlobalDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWGLOBALDEF_H__)
#define _DRAWGLOBALDEF_H__
//��ID
#define DRAWCLASSID_BASEOBJECT				0x00010000					//��ͼ�������
#define DRAWCLASSID_BASELIST				0x00110000					//����������
#define DRAWCLASSID_BINARYVARIABLE			DRAWCLASSID_BASEOBJECT + 0x00000001	//��������
#define DRAWCLASSID_ANALOGVARIABLE			DRAWCLASSID_BASEOBJECT + 0x00000002	//ģ������
#define DRAWCLASSID_TIMEAXIS				DRAWCLASSID_BASEOBJECT + 0x00000003	//ʱ������
#define DRAWCLASSID_TIMECURSOR				DRAWCLASSID_BASEOBJECT + 0x00000004	//ʱ������
#define DRAWCLASSID_TRIGCURSOR				DRAWCLASSID_BASEOBJECT + 0x00000005	//���������
#define DRAWCLASSID_VARIABLESMNGR			DRAWCLASSID_BASELIST   + 0x00000006	//ͨ��������
#define DRAWCLASSID_BINARYVARIABLEGROUP     DRAWCLASSID_BASELIST   + 0x00000007	//������Ⱥ������
#define DRAWCLASSID_ATTRSPYVARIABLE			DRAWCLASSID_BASEOBJECT + 0x00000008	//���Լ�������
#define DRAWCLASSID_RANGESTATEAXIS			DRAWCLASSID_BASEOBJECT + 0x00000009	//
#define DRAWCLASSID_COMPLEXVARIABLE			DRAWCLASSID_BASEOBJECT + 0x0000000A	//ģ����������

extern HCURSOR g_hMoveCursor;
extern CBitmap g_bmpZoom;

namespace MrDraw
{	
#define VARIABLE_NAME_MIN_LENGTH			40
#define VARIABLE_MIN_DEFAULT_HEIGHT			50
#define DRAW_HAS_OBJECT_SELECTED            1
#define DRAW_NONE_OBJECT_SELECTED           0
	
#define WM_RECORD_TIMER_DRAW                (WM_USER + 89)
#define WM_DRAW								(WM_USER + 90)
#define WM_INVALIDATE_RANGESTATEAXIS        (WM_USER + 91)
#define WM_VARIABLE_SIZE_CHANGED		    (WM_USER + 92)
#define WM_VARIABLE_POS_CHANGED				(WM_USER + 93)
#define WM_VARIABLE_SELECT_CHANGED			(WM_USER + 94)
#define WM_TIMEAXIS_CHANGED					(WM_USER + 95)
#define WM_TIMECURSOR_POS_CHANGE			(WM_USER + 96)
#define WM_TIMECURSOR_SELECT_CHANGE			(WM_USER + 97)
#define WM_TIME_CHANGED						(WM_USER + 98)
	
	//��ͼʱ����ʾ���ε����ݷ�Χ
	typedef struct  
	{
		long nBufLength;
		long nBuf1BeginPos;
		long nBuf1EndPos;
		long nBuf2BeginPos;
		long nBuf2EndPos;
		long nGap;
	}DRAWMEMBUFFERPOS, *PDRAWMEMBUFFERPOS;
		
	extern LOGFONT g_lfDrawVariableName;
	extern LOGFONT g_lfDrawVaraibleAxisScale;
	extern LOGFONT g_lfDrawPara;
	extern long g_nVariableNameLength;
	
	inline BOOL PointInRect(const CPoint &pt, const CRect &rcRect)
	{
		return (rcRect.left <= pt.x && pt.x <= rcRect.right
			&& rcRect.top <= pt.y && pt.y <= rcRect.bottom);
	}
	
	inline BOOL PointInRect(const CRect &rcRect, const CPoint &pt)
	{
		return (rcRect.left <= pt.x && pt.x <= rcRect.right
			&& rcRect.top <= pt.y && pt.y <= rcRect.bottom);
	}
}

#endif // !defined(_DRAWGLOBALDEF_H__)
