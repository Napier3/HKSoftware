#pragma once

#include "..\..\..\Module\BaseClass\ExBaseListListCtrl.h"
#include "GbWzdCmd.h"
// CWzdCmdListCtrl

class CWzdCmdListCtrl : public CExBaseListListCtrl
{
	DECLARE_DYNAMIC(CWzdCmdListCtrl)

public:
	CWzdCmdListCtrl();
	virtual ~CWzdCmdListCtrl();
	void InitColumns();
	CGbWzdCmd* GetCurrCmd();
	void UpdateIndex();

protected:
	DECLARE_MESSAGE_MAP()
};


