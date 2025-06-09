#pragma once

#include "ExBaseList.h"

template <class T> 
class CFactoryBase : public CExBaseList
{
public:
	typedef T* (PFCREATE)();

protected:
	class CCreatorBase : public CExBaseObject
	{
	public:
		UINT m_nClassID; //

		CCreatorBase(const CString &strName,const CString &strID, PFCREATE* pFunCreate)
		{
			m_strName = strName;
			m_strID = strID;
			m_pFunCreate = pFunCreate;
			m_nClassID = 0;
		}

		CCreatorBase(const CString &strName,UINT nClassID, PFCREATE* pFunCreate)
		{
			m_strName = strName;
			m_nClassID = nClassID;
			m_pFunCreate = pFunCreate;
		}

		virtual ~CCreatorBase(void){};

		T* Create()
		{
			T *pNew = m_pFunCreate();
			return pNew;
		}

		T* CreateEx()
		{
			T *pNew = m_pFunCreate();
			pNew->m_strName = m_strName;
			pNew->m_strID = m_strID;
			return pNew;
		}

	private:
		PFCREATE* m_pFunCreate;

	};

public:
	CFactoryBase(void){};
	virtual ~CFactoryBase(void)
	{
		DeleteAll();
	};

protected:
	virtual CCreatorBase* FindByID2(UINT nClassID)
	{
		POS pos = GetHeadPosition();
		CCreatorBase *p = NULL;
		CCreatorBase *pFind = NULL;

		while (pos != NULL)
		{
			p = (CCreatorBase *)GetNext(pos);

			if (p->m_nClassID == nClassID)
			{
				pFind = p;
				break;
			}
		}

		return pFind;
	}

	virtual CCreatorBase* RegisterCreator(const CString &strName,const CString &strID, PFCREATE* pFunCreate)
	{
		CCreatorBase *pFind = (CCreatorBase*)FindByID(strID);
		ASSERT (pFind == NULL);

		pFind = new CCreatorBase(strName, strID, pFunCreate);
		AddNewChild(pFind);
		return pFind;
	}

	virtual CCreatorBase* RegisterCreator(const CString &strName, UINT nClassID, PFCREATE* pFunCreate)
	{
		CCreatorBase *pFind = (CCreatorBase*)FindByID2(nClassID);
		ASSERT (pFind == NULL);

		pFind = new CCreatorBase(strName, nClassID, pFunCreate);
		AddNewChild(pFind);
		return pFind;
	}

	T* Create(const CString &strID)
	{
		T *pNew = NULL;
		CCreatorBase *pCreator = (CCreatorBase*)FindByID(strID);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pNew = pCreator->Create();

		return pNew;
	}

	T* Create(UINT nClassID)
	{
		T *pNew = NULL;
		CCreatorBase *pCreator = (CCreatorBase*)FindByID2(nClassID);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pNew = pCreator->Create();

		return pNew;
	}

	T* CreateByName(const CString &strName)
	{
		T *pNew = NULL;
		CCreatorBase *pCreator = (CCreatorBase*)FindByName(strName);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pNew = pCreator->Create();

		return pNew;
	}

	T* CreateEx(const CString &strID)
	{
		T *pNew = NULL;
		CCreatorBase *pCreator = (CCreatorBase*)FindByID(strID);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pNew = pCreator->CreateEx();

		return pNew;
	}

	T* CreateEx(UINT nClassID)
	{
		T *pNew = NULL;
		CCreatorBase *pCreator = (CCreatorBase*)FindByID2(nClassID);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pNew = pCreator->CreateEx();

		return pNew;
	}

	T* CreateExByName(const CString &strName)
	{
		T *pNew = NULL;
		CCreatorBase *pCreator = (CCreatorBase*)FindByName(strName);

		if (pCreator == NULL)
		{
			return NULL;
		}

		pNew = pCreator->CreateEx();

		return pNew;
	}
};

