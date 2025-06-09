#pragma once

class CMouseHook
{ 
private:
	CMouseHook()	{	}

public: 
	CMouseHook(HINSTANCE hInstance); 
	~CMouseHook(); 
	
	//��װ���Ӻ��� 
	BOOL StartHook(); 

	//ж�ع��Ӻ��� 
	BOOL StopHook(); 

public:
	static HHOOK g_hHook;    //��װ����깳�Ӿ��

private:
	HINSTANCE m_hInstance;    //DLLʵ����� 
}; 

