#include "stdafx.h"
#include "SttRemoteRegMngr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRemoteRegMngr::CSttRemoteRegMngr()
{
	//��ʼ������
	m_strName = _T("Զ�̿��Ʒ���");

	m_pMsgWnd = NULL;
	//��ʼ����Ա����
}

CSttRemoteRegMngr::~CSttRemoteRegMngr()
{

}
