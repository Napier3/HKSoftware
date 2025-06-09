#pragma once

class CMouseHook
{ 
private:
	CMouseHook()	{	}

public: 
	CMouseHook(HINSTANCE hInstance); 
	~CMouseHook(); 
	
	//安装钩子函数 
	BOOL StartHook(); 

	//卸载钩子函数 
	BOOL StopHook(); 

public:
	static HHOOK g_hHook;    //安装的鼠标钩子句柄

private:
	HINSTANCE m_hInstance;    //DLL实例句柄 
}; 

