#pragma once

#include "ExBaseList.h"

//2019-4-20   ���
//���еĺ�������ǰ׺��Optr_������Ϊ����֮ǰ�Ѿ�����õ�ExBase*�ؼ�����ĺ������֣������ͻ
// class CExBaseCtrlOptrInterface
// {
// public:
// 	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
// 	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
// 	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE) = 0;
// 	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
// 
// 	virtual void Optr_UpdateDataIndex()	{	};
// };
#include "ExBaseCtrlOptrInterface.h"

class CExBaseDataOptrBaseApp
{
public:
	virtual BOOL Optr_InsertData(CExBaseList &oList) = 0;
	virtual BOOL Optr_DeleteData(CExBaseList &oList, int nExtFlag) = 0;
	virtual BOOL Optr_UpdateData(CExBaseList &oList) = 0;
	virtual BOOL Optr_UploadFile(const CString &strRemoteFile, const CString &strLocalFile,BOOL bSend=TRUE) = 0;
	virtual BOOL Optr_DownLoadFile(const CString &strRemoteFile, const CString &strLocalFile,BOOL bSend=TRUE) = 0;

};

extern CExBaseDataOptrBaseApp *g_pExBaseDataOptrBaseApp;


//2021-9-2  lijunqing  ����QT/Windows����Ϣ����
class CExBaseXMsgRcvInterface
{
public:
	virtual void OnXMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam) = 0;
	virtual void OnXTimer(unsigned int nIDEvent) = 0;

};

