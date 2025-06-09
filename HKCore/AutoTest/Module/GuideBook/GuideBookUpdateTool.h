#pragma once

#include "..\..\..\Module\BaseClass\ExBaseListUpdateToolBase.h"

#define GBUPDATE_TYPE_REPORTMAP    0X00000001

class CGuideBookUpdateTool : public CExBaseListUpdateToolBase
{
public:
	CGuideBookUpdateTool();
	virtual ~CGuideBookUpdateTool();

protected:
	DWORD m_dwGbUpdateTypeMask;

protected:
	virtual BOOL Update_Own(CExBaseObject *pSrc, CExBaseObject *pDest);
	virtual BOOL Update_Own_ReportMap(CExBaseObject *pSrc, CExBaseObject *pDest);

public:
	void Update_ReportMap(CExBaseObject *pSrc, CExBaseObject *pDest);
	void Update_ReportMap(CExBaseObject *pGuideBook);
};


