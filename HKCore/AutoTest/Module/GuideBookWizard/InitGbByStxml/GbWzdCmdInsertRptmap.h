#pragma once

#include "..\GbWzdCmd.h"


class CGbWzdCmdInsertRptmap : public CGbWzdCmd
{
public:
	CGbWzdCmdInsertRptmap();
	virtual ~CGbWzdCmdInsertRptmap();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_STXML_EDITGBITEM;	} 
public:
	CExBaseObject *m_pGbItem;

public:
	virtual BOOL Execute();
	virtual BOOL IsCmdFinish();
	virtual void GetCmdInfor(CString &strText);
};