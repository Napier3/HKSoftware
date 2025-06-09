//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//StCfgDataWndBase.h  CStCfgDataWndBase

#pragma once

#include "..\CfgDataMngr\StCfgDataBase.h"

#define ID_CFGDATA_BTN_MIN   0X06001
#define ID_CFGDATA_BTN_MAX   0X06002
#define ID_CFGDATA_BTN_CLOSE 0X06003
#define ID_CFGDATA_BTN_INFOR 0X06004

#define CFGDATAWND_STATE_MIN   0
#define CFGDATAWND_STATE_MAX   1

#define STCFGDATAWND_TITLEBAR_WIDTH       24
#define STCFGDATAWND_TITLEBAR_CTRL_HEIGHT 19
#define STCFGDATAWND_TITLEBAR_HEIGHT      24
#define STCFGDATAWND_TITLEBAR_GAP         3

//���ô���ı���Ϣ
#define WM_CFGDATAWNDS_CHANGED  (WM_USER + 908)  
#define WM_CFGDATAWND_DELETE    (WM_USER + 909)  
#define WM_CFGDATAWND_SETCFGDATAVALUE    (WM_USER + 910)  


class CStCfgDataWndBase : public CStBaseObject//, public CDialogEx
{
public:
	CStCfgDataWndBase();
	virtual ~CStCfgDataWndBase();

	CStCfgDataBase *m_pCfgData;			 //��Ӧ���������ݶ���
	CWnd *m_pCfgDataWnd; 				 //���ô���ָ��  ����Ĵ�������
	DWORD m_dwCfgDataWndState;
	long m_yPos;

//���غ���
public: 
	//�����ڽ����ʼ��ʱ��ʾ��ص�����
	virtual BOOL UICreate(CWnd *pParentWnd);
	virtual BOOL UICreateOwn(CWnd *pParentWnd);
	virtual BOOL UICreateChildren(CWnd *pParentWnd)	{	return FALSE;	}
	
	//��ʾ
	virtual void ShowStCfgData(CStCfgDataBase *pCfgData = NULL);
	virtual void ShowStCfgDataOwn(CStCfgDataBase *pCfgData = NULL, DWORD dwPara=0) = 0;
	virtual void ShowStCfgDataChildren(CStCfgDataBase *pCfgData = NULL)	{		};
	virtual CString GetTitle() = 0;
	virtual void ShowTitle();
	
	//����
	virtual void SaveStCfgData();
	virtual void SaveStCfgDataOwn() = 0;
	virtual void SaveStCfgDataChildren()	{	}

	//���ڲ���
	virtual void ActiveWnd() = 0;
	virtual void OnDeleteWnd() = 0;

	virtual CSize GetDataWndSize();
	virtual void SetDataWndPos(long &nLeft, long &nTop);
	virtual void MoveDataWndPos(long &nLeft, long &nTop);

	virtual void ShowCfgDataWnd();
	virtual void HideCfgDataWnd();
  
//˽�г�Ա����
protected:
	CWnd *m_pCfgDataParentWnd;
	CSize m_szOrigin;   //ԭʼ��С
	CSize m_szMin;
	
	CBitmapButton m_btnMin;
	CBitmapButton m_btnMax;
	CBitmapButton m_btnClose;
	CEdit m_edtInfor;
	BOOL m_bHasTitleButtons;

	void AdjustCfgDataWndCtrls();
	CDWordArray m_adwCtrls;

	void PostDataWndMsg(UINT nMsg, WPARAM wPara, LPARAM lPara);


//˽�г�Ա�������ʷ���
public:
	BOOL IsMinSize()	{	return m_dwCfgDataWndState == CFGDATAWND_STATE_MIN;	}
	BOOL IsMaxSize()	{	return m_dwCfgDataWndState == CFGDATAWND_STATE_MAX;	}

	BOOL InitMinBtnBitmaps(UINT nIDBitmapResource,UINT nIDBitmapResourceSel = 0,UINT nIDBitmapResourceFocus = 0,UINT nIDBitmapResourceDisabled = 0);
	BOOL InitMaxBtnBitmaps(UINT nIDBitmapResource,UINT nIDBitmapResourceSel = 0,UINT nIDBitmapResourceFocus = 0,UINT nIDBitmapResourceDisabled = 0);
	BOOL InitCloseBtnBitmaps(UINT nIDBitmapResource,UINT nIDBitmapResourceSel = 0,UINT nIDBitmapResourceFocus = 0,UINT nIDBitmapResourceDisabled = 0);
	afx_msg void _OnClose();
	afx_msg void _OnMin();
	afx_msg void _OnMax();

	virtual void SetCfgDataValue(long nDataID, float dValue);


};

inline void st_ValidateMiMax(long &Value, long Min, long Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}


inline void st_ValidateMiMax(double &Value, double Min, double Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}


inline void st_ValidateMiMax(float &Value, float Min, float Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}


inline void st_ValidateMiMax(DWORD &Value, DWORD Min, DWORD Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}
