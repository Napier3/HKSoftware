#pragma once


//XKeyDBUiGlobal.h
#include "..\XKeyDB.h"
#include "..\..\DialogBase\DynDialogEx.h"



#define XIDC_EDIT_NAME                       1001
#define XIDC_EDIT_ID                         1002
#define XIDC_LIST_MULTIKEY                   1003
#define XIDC_EDIT_BASEKEYNAME                1004
#define XIDC_BTN_SAVE                        1005
#define XIDC_BTN_INSERT                      1006
#define XIDC_BTN_DELETE                      1007
#define XIDC_STATIC_NAME                     1008
#define XIDC_STATIC_ID                       1009
#define XIDC_BTN_CANCLE                      1010
#define XIDC_BTN_BASEKEYNEW                  1011
#define XIDC_BTN_MULTIKEYNEW                 1012
#define XIDC_BTN_KEYDELETE                   1013
#define XIDC_BTN_FILTER                      1014
#define XIDC_LIST_KEYDB                      1015
#define XIDC_BTN_XKEYDB_VALIDATE                  1016
#define XIDC_BTN_INKEYDB                     1017
#define XIDC_EDIT_ANALYZE                    1018
#define XIDC_BTN_ANALYZE                     1019
#define XIDC_COMB_FILTER                     1020
#define XIDC_EDIT_BASEKEY_NAME               1021
#define XIDC_EDIT_BASEKEY_ID                 1022


#define STYLE_LISTCTRL_LIST  (WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | LVS_LIST | LVS_SHOWSELALWAYS)

#define XKEYEDITDLG_MODE_NONE  0
#define XKEYEDITDLG_MODE_NEW   1
#define XKEYEDITDLG_MODE_EDIT  2

class CXKeyEditDlgBase : public CDynDialogEx
{
public:
	CXKeyEditDlgBase(CWnd *pParent);
	virtual ~CXKeyEditDlgBase();

	UINT m_nXKeyEditDlgMode;

	CExBaseObject *m_pXKey;

public:
	BOOL IsModeNew()	{	return m_nXKeyEditDlgMode == XKEYEDITDLG_MODE_NEW;	}
	BOOL IsModeEdit()	{	return m_nXKeyEditDlgMode == XKEYEDITDLG_MODE_EDIT;	}

	virtual int NewKey(CExBaseObject *pKey);
	virtual int EditKey(CExBaseObject *pKey);

protected:
	CExBaseList *m_pKeyParent;
	CExBaseObject *m_pXKeySrc;

	virtual BOOL ValidateKey(const CString &strName, const CString &strID);
};
