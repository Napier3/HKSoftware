#pragma once

#include "EpDevBaseList.h"
#include "..\BaseClass\FactoryBase.h"

class CEpDevWndFactory : public CFactoryBase<CEpDevBase>
{
public:
	static CEpDevBase* CreateDevWnd(CExBaseObject* pData,CWnd* pParentWnd);
	static CEpDevBase* CreateDevWnd(UINT nDataClassID,CWnd* pParentWnd,CExBaseObject* pData);
	static CEpDevBase* CreateDevWnd(CExBaseObject* pData,CWnd* pParentWnd,CEpDevBaseList* pDevParent);

	static CEpDevWndFactory *g_pEpDevWndFactory;

	virtual void RegisterAllCreator()	{		ASSERT (FALSE);	}

protected:
	static long m_nEpDevWndFactoryRef;
	
	CEpDevWndFactory();
	virtual ~CEpDevWndFactory();

// 	virtual CCreatorBase* RegisterCreator(const CString &strName,const CString &strID, PFCREATE* pFunCreate)
// 	{
// 		return CFactoryBase::RegisterCreator(strName, strID, pFunCreate);
// 	}


};

