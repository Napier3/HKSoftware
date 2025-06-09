#pragma once

#define _use_safenet_dog

#ifdef _use_safenet_dog

#include "..\..\Module\Sentinel LDK\SentinelLDKInterface.h"
#include "..\..\Module\Sentinel LDK\XSafenetLogin.h"

#else

#include "..\Encrypt\EncryptTool.h"
#include "..\Encrypt\Safenet\EncryptSafeNet.h"
BOOL Encrypt_IsEncrypt_Demo();
BOOL Encrypt_IsEncrypt_Test();

#endif

typedef LONG (__cdecl *EP_GETEPOTOSTRING)(long nStringID, char *pString, long &nStringLen);
// extern EP_GETEPOTOSTRING 								Pp_GetEpotoString;

BOOL HasLoadEpotoLib();
void ReleaseEpotoLib();
BOOL LoadEpotoLib(const CString &strPath);

BOOL Encrypt_IsEncrypt_Devlop(UINT nFetureID, BOOL bShowHaspMsg=TRUE);
BOOL Encrypt_IsEncrypt_CanUseAutoTest();
BOOL Encrypt_IsEncrypt(UINT nFetureID, BOOL bShowHaspMsg=TRUE);


#define FETUREID_AUTOTEST     100
#define FETUREID_RPTDEV       101
#define FETUREID_GBDEV        102
#define FETUREID_STXML        103
#define FETUREID_PPDEV        104
#define FETUREID_PPENGINE     105
#define FETUREID_MMSENGINE    106
#define FETUREID_ATSREGISTER  107
#define FETUREID_SERVER       108


// ���ֻ����վ��վ����	1
#define AUTHORITY_TEST_STATIONTEST  1

// ��װ�ö��Լ����	2
#define AUTHORITY_TEST_SDVMPP          2

// ��װ�õ���Լ����	3
#define AUTHORITY_TEST_MDVSPP         3

// ��װ�ö������	4
#define AUTHORITY_TEST_DMVMGRP      4

// ģ��ӳ�乤��DvmMap	5
#define AUTHORITY_TEST_DVMMAP        5

// ģ�Ͳ��Թ���DvmTest	6
#define AUTHORITY_TEST_DVMTEST      6

// ���������ù���XLangDev	7
#define AUTHORITY_TEST_XLANGDEV    7

// ����ģ�����	8
#define AUTHORITY_TEST_TEMPLATEMNGR          8

// ����ģ����Ȩ	9
#define AUTHORITY_TEST_TEMPLATEAUTHORITY  9

// �����������	10
#define AUTHORITY_TEST_TASKTEST  10



LONG GetEpotoString(long nStringID, char *pString, long &nStringLen);

#define Pp_GetEpotoString    GetEpotoString
#define EPOTO_STRING_ID_EPOTO     0X00F00000
#define EPOTO_STRING_ID_DEV       0X00F00001
#define EPOTO_STRING_ID_COMPANY   0X00F00002
#define EPOTO_STRING_ID_USER      0X00F00003
#define EPOTO_STRING_ID_TITLE     0X00F00004
#define EPOTO_STRING_ID_MAIL      0X00F00005
#define EPOTO_STRING_ID_TEL       0X00F00006
#define EPOTO_STRING_ID_QQ        0X00F00007
#define EPOTO_STRING_ID_AUTHORITY 0X00F00008


