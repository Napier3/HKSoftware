//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//配置窗体改变消息
#define WM_CFGDATAWNDS_CHANGED  (WM_USER + 908)  
#define WM_CFGDATAWND_DELETE    (WM_USER + 909)  
#define WM_CFGDATAWND_SETCFGDATAVALUE    (WM_USER + 910)  


class CStCfgDataWndBase : public CStBaseObject//, public CDialogEx
{
public:
	CStCfgDataWndBase();
	virtual ~CStCfgDataWndBase();

	CStCfgDataBase *m_pCfgData;			 //对应的配置数据对象
	CWnd *m_pCfgDataWnd; 				 //配置窗体指针  具体的窗体引用
	DWORD m_dwCfgDataWndState;
	long m_yPos;

//重载函数
public: 
	//用于在界面初始化时显示相关的数据
	virtual BOOL UICreate(CWnd *pParentWnd);
	virtual BOOL UICreateOwn(CWnd *pParentWnd);
	virtual BOOL UICreateChildren(CWnd *pParentWnd)	{	return FALSE;	}
	
	//显示
	virtual void ShowStCfgData(CStCfgDataBase *pCfgData = NULL);
	virtual void ShowStCfgDataOwn(CStCfgDataBase *pCfgData = NULL, DWORD dwPara=0) = 0;
	virtual void ShowStCfgDataChildren(CStCfgDataBase *pCfgData = NULL)	{		};
	virtual CString GetTitle() = 0;
	virtual void ShowTitle();
	
	//保存
	virtual void SaveStCfgData();
	virtual void SaveStCfgDataOwn() = 0;
	virtual void SaveStCfgDataChildren()	{	}

	//窗口操作
	virtual void ActiveWnd() = 0;
	virtual void OnDeleteWnd() = 0;

	virtual CSize GetDataWndSize();
	virtual void SetDataWndPos(long &nLeft, long &nTop);
	virtual void MoveDataWndPos(long &nLeft, long &nTop);

	virtual void ShowCfgDataWnd();
	virtual void HideCfgDataWnd();
  
//私有成员变量
protected:
	CWnd *m_pCfgDataParentWnd;
	CSize m_szOrigin;   //原始大小
	CSize m_szMin;
	
	CBitmapButton m_btnMin;
	CBitmapButton m_btnMax;
	CBitmapButton m_btnClose;
	CEdit m_edtInfor;
	BOOL m_bHasTitleButtons;

	void AdjustCfgDataWndCtrls();
	CDWordArray m_adwCtrls;

	void PostDataWndMsg(UINT nMsg, WPARAM wPara, LPARAM lPara);


//私有成员变量访问方法
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
