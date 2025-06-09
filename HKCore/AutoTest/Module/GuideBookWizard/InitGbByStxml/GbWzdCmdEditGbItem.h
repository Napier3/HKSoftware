#pragma once

#include "..\GbWzdCmd.h"


class CGbWzdCmdEditGbItem : public CGbWzdCmd
{
public:
	CGbWzdCmdEditGbItem();
	virtual ~CGbWzdCmdEditGbItem();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_STXML_EDITGBITEM;	} 
public:
	CExBaseObject *m_pGbItem;

public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish();
	virtual void GetCmdInfor(CString &strText);
};