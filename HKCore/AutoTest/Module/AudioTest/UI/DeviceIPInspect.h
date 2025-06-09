#pragma once
#include "../../../AudioTest/resource.h"
#include "AudioDlgBase.h"
// CDeviceIPInspect 对话框
class CDeviceIPInspect : /*public CDialog,*/public CAudioDlgBase
{
	DECLARE_DYNAMIC(CDeviceIPInspect)

public:
	CDeviceIPInspect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceIPInspect();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
// 对话框数据
	enum { IDD = IDD_DIALOG_DEVEICEIPINSPECT };
public:
	virtual void FindSelectAnswer(CString strResult);
	virtual bool DealAnswer(CString strResult);
	virtual CString GetCurrentResult();

	

protected:
	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	CStatic m_static;
	CString m_strIP;
};
