// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// IecConfigDoc.h : CIecConfigDoc 类的接口
//


#pragma once


class CIecConfigDoc : public CDocument
{
protected: // 仅从序列化创建
	CIecConfigDoc();
	DECLARE_DYNCREATE(CIecConfigDoc)

// 属性
public:
	CIecCfgFile *m_pIecCfgFile;

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);


// 实现
public:
	virtual ~CIecConfigDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);

	afx_msg void OnFileSaveAT02D();//周宏军 20200616  增加AT02配置
	afx_msg void OnUpdateFileSaveAT02D(CCmdUI *pCmdUI);
	afx_msg void OnFileSaveAsAT02D();
	afx_msg void OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI);
};


