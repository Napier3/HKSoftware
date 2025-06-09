#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"


class CSttBaseInterface : public CExBaseList
{
public:
	CSttBaseInterface(){}
	virtual ~CSttBaseInterface(){}

	virtual void Release()
	{
        CExBaseList *pParent = (CExBaseList*)GetParent();
		
		if (pParent != NULL)
		{
			pParent->Delete(this);
		}
		else
		{
			delete this;
		}
	}


	CSttBaseInterface* SttFindByID(const CString &strID)
	{
		CSttBaseInterface* pTemp = NULL;
		CSttBaseInterface* pFind = NULL;

		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pTemp = (CSttBaseInterface*)GetNext(pos);

			if (pTemp->m_strID == strID)
			{
				pFind = pTemp;
				break;
			}
		}

		return pFind;
	}
};
