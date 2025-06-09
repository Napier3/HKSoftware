#pragma once


// CWzdCmdTreeCtrl 视图

class CWzdCmdTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNCREATE(CWzdCmdTreeCtrl)

public:
	CWzdCmdTreeCtrl();           // 动态创建所使用的受保护的构造函数
	virtual ~CWzdCmdTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()
};


