#include "stdafx.h"
#include "SttAppWndAssistInterface.h"

//��ʾ/����һ���Ӵ���
void CSttWndAssistInterface::ast_Show(const CString &strWndIdPath, bool bShow)
{

}

//������ʽ
void CSttWndAssistInterface::ast_SetStyle(const CString &strWndIDPath, const CString &strStyle)
{

}

CString CSttWndAssistInterface::ast_GetStyle(const CString &strWndIDPath)
{
	CString strStyle;

	return strStyle;
}

//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
CSttWndAssistInterface* CSttWndAssistInterface::ast_FindWnd(const CString &strWndID)
{
	return NULL;
}

//��ȡ����λ�� �ҵ����ڷ���true�����򷵻�false
bool CSttWndAssistInterface::ast_GetWndPos(const CString &strWndIdPath, CRect &rcWndPos)
{
	return false;
}

