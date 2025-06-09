#if !defined(AFX_LOGARITHMAXISDLG_H__606182BD_F3DA_456F_AA89_7DD510177763__INCLUDED_)
#define AFX_LOGARITHMAXISDLG_H__606182BD_F3DA_456F_AA89_7DD510177763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogarithmAxisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxisDlg dialog

class CLogarithmAxisDlg : public CDialog
{
// Construction
public:
	CLogarithmAxisDlg(CWnd* pParent = NULL);   // standard constructor

	ILogarithmAxisInterface  *m_ILogarithmAxis;
	void InitLogarithmAxis();
	void ChangeDrawStype(BOOL bSet,long nStyle);

	//��������ϵͳ�����ߡ����Ե����ɫ��Ϣ

	float	m_fMaxTimeVal;		//��������ʱ����ֵ
	float	m_fMaxCurrVal;		//�������������ֵ
	CRect	m_rectAxis;			//����ϵ��λ��
	float	m_fAxisValue[4];		//��������ķ�Χ	0-3���ѿ������ꣻ4-7��������
	int		m_iAxisGridLineType;		//���������ߵ�����
	
	void	OnAxisColorChanged();			//��������ɫ��Ϣ�ı�
//	void	ResetAxisVal();		//������������������Сֵ
	void	InitAxisValue();	//��ʼ����������ķ�Χ	
	void    ResetNormalAxis();

	
	//��ʼ������ķ�Χ
	void ResetLogAxisDataDef();				//��ʼ������λ��
	

//	void OnAxiscolorset();
	void InitAxisAttr();
	int FloatValToInt(double f,BOOL bCaryy=1);
	
	//������Ŀ����غ���
	int	m_iCurrTestItem;					//��ǰ������Ŀ
	


// Dialog Data
	//{{AFX_DATA(CLogarithmAxisDlg)
	enum { IDD = IDD_DIALOG_LOGARITHM };
	CStatic	m_stcFrame;
	BOOL	m_bAxisBorder;
	BOOL	m_bAxisCenter;
	BOOL	m_bWorkArea;
	BOOL	m_bXAxisLine;
	BOOL	m_bXHalfScale;
	BOOL	m_bXScaleText;
	BOOL	m_bXTenthScale;
	BOOL	m_bYAxisLine;
	BOOL	m_bYHalfScale;
	BOOL	m_bYScaleText;
	BOOL	m_bYTenthScale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogarithmAxisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogarithmAxisDlg)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnWorkarea();
	afx_msg void OnAxiscenter();
	afx_msg void OnAxisborder();
	afx_msg void OnXaxisline();
	afx_msg void OnXscaletext();
	afx_msg void OnXtenthscale();
	afx_msg void OnXhalfscale();
	afx_msg void OnYaxisline();
	afx_msg void OnYscaletext();
	afx_msg void OnYtenthscale();
	afx_msg void OnYhalfscale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGARITHMAXISDLG_H__606182BD_F3DA_456F_AA89_7DD510177763__INCLUDED_)
