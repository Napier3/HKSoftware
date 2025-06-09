
#ifndef _XYun_File_Api_h__
#define _XYun_File_Api_h__

#include "XYunFileApi_Global.h"

long Yun_Search(CXFolder *pParentFolder, CExBaseList &listPostfix, BOOL bTraveSubFolder);

long Yun_SetBatchOperMode(BOOL bBatchMode, HWND hWnd, UINT nMsg=YUN_OPER_RSLT_MSG);
long Yun_BatchOper();

long Yun_DownLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles);
long Yun_UpLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles);
long Yun_Delete(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles);

long Yun_DownLoadFile(const CString &strFile);
long Yun_UpLoadFile(const CString &strFile);
long Yun_DeleteFile(const CString &strFile);

long Yun_DownLoadFolder(const CString &strFolder);
long Yun_UpLoadFolder(const CString &strFolder);
long Yun_DeleteFolder(const CString &strFolder);

void Yun_Init();
void Yun_Free();

void Yun_Login();
void Yun_Logout();

BOOL Yun_IsLoginSucc();

//XTestDB
void Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg);
CString Yun_GetTasksXml(const CString &strPara);
void Yun_SetTasksXml(CString &strXml);
void Yun_PopTasksSelWnd(const CString &strPara, long nPara);

#endif



