#pragma once

#include "../../BaseClass/TLinkList.h"
#include "CJSON.h"

class CJsonBaseList : public CTLinkList<CJSON>
{
public:
	CJsonBaseList();
	virtual ~CJsonBaseList();

	void FreeAll();
	void AttachJsonSrc(CJSON *pJson)	{	m_pJsonSrc = pJson;	}
	void SetMaxItemCount(long nCount)	{	m_nMaxItemCount = nCount;	}
	void add_to_json(CJSON* item);
	void ClearList();

private:
	CJSON* m_pJsonSrc;
	CJSON* m_pJsonDest;
	long m_nCurrCount;
	long m_nMaxItemCount;


	void add_to_json(CJsonBaseList &listPath);
	CJSON* add_to_json(CJSON *pCurr, CJSON *pParent);
	BOOL get_json_all_path(CJSON* itemFind, CJSON* itemSrc,  CJsonBaseList &listPath);
};
