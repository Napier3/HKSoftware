#include "stdafx.h"
#include "SttRemoteRegMngr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRemoteRegMngr::CSttRemoteRegMngr()
{
	//初始化属性
	m_strName = _T("远程控制服务");

	m_pMsgWnd = NULL;
	//初始化成员变量
}

CSttRemoteRegMngr::~CSttRemoteRegMngr()
{

}
