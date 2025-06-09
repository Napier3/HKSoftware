//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMatchObject.h  CXMatchObject

#pragma once

#include "KeyDbGlobal.h"

#include "XKeyDB.h"
#include "../BaseClass/ThreadProgressInterface.h"

class CXMatchObjectRatio : public CExBaseObject
{
public:
	CXMatchObjectRatio(CExBaseObject *pRefObject, long nMatchRatio)
	{	
		m_nMatchRatio = nMatchRatio;
		m_pRefObject = pRefObject;
	}

	virtual ~CXMatchObjectRatio(){}

	long m_nMatchRatio;
	CExBaseObject *m_pRefObject;	//��ƥ������ݶ�������

public:
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0)
	{
		CString strText;
                strText.Format(_T("��%d%%��%s"), m_nMatchRatio, m_pRefObject->m_strName.GetString());
		m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strText, 0, 0, htiParent);
		pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
	}
};

class CXMatchObject : public CExBaseList
{
public:
	CXMatchObject();
	CXMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb);
	virtual ~CXMatchObject();

	CExBaseObject *m_pRefObject;	//��ƥ������ݶ�������
	//CExBaseList m_listMatchXKeys;	//���ö���ƥ��Ĺؼ���
	CXKeyMatchRefList m_listMatchXKeys;	//���ö���ƥ��Ĺؼ���
	CExBaseList m_listMacthRefObject;	//ƥ��ɹ������ݶ���
	CExBaseList m_listMacthObjectRatio;	//ƥ��ɹ������ݶ���
	BOOL m_bFullMatchString;            //�����ַ���ƥ��

	static long g_bNumberKeyMatchRatioAdd;
//���غ���
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXMATCHOBJECT;   }
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual void FreeMatch();
	BOOL XMatch(CXKeyMatchRefList *pSrcXKeys, CXKeyMatchRefList *pDstXKeys, long &nMatchRatio); //2022-5-9 lijunqing ���ŵĽӿ�
	void XAddXMatchRatioObject(long nRatio, CExBaseObject *pRefObj);

//˽�г�Ա����
private:
	//virtual BOOL Match(CExBaseList *pSrcXKeys, CExBaseList *pDstXKeys, long &nMatchRatio);
	//virtual BOOL IsSubKeys(CExBaseList *pSrcXKeys, CExBaseList *pDstXKeys, long &nMatchRatio);
	//virtual BOOL IsSubKey(CExBaseList *pXKeys, CExBaseObject *pXKey, long &nImportance);
	virtual BOOL Match(CXKeyMatchRefList *pSrcXKeys, CXKeyMatchRefList *pDstXKeys, long &nMatchRatio);
	virtual BOOL IsSubKeys(CXKeyMatchRefList *pSrcXKeys, CXKeyMatchRefList *pDstXKeys, long &nMatchRatio);
	virtual BOOL IsSubKey(CXKeyMatchRefList *pXKeys, CXKeyMatchRef *pXKey, long &nImportance);
	virtual void Match(CXMatchObject *pMatchObj, BOOL bUseFullMatchString);
	
	virtual void AddXMatchRatioObject(long nRatio, CExBaseObject *pRefObj)
	{
		CXMatchObjectRatio *pNew = new CXMatchObjectRatio(pRefObj, nRatio);
		m_listMacthObjectRatio.AddTail(pNew);
	}

//˽�г�Ա�������ʷ���
public:
	virtual void Match(CExBaseList *pMachList, BOOL bFreeMatchList, BOOL bUseFullMatchString);
	virtual void Init(CExBaseObject *pRefObj, CXKeyDB *pKeyDb);
	virtual long GetMatchRefCount()	{	return m_listMacthRefObject.GetCount();	}
	virtual CExBaseObject* GetMatchRef();
	virtual BOOL HasRefObj(CExBaseObject *pRefObj);
	virtual void FilterMatch(CExBaseObject *pRefObj);
	virtual void FilterMatch(CXMatchObject *pMatchObj);
	virtual void FilterMatchRatio(long nRatioMin=20);
	virtual void FilterSortByRatio();
	virtual void SetMacthRefObj(CExBaseObject *pRefObj, BOOL bClear=TRUE)
	{
		if (bClear)
		{
			m_listMacthRefObject.RemoveAll();
		}

		if (pRefObj != NULL)
		{
			m_listMacthRefObject.AddTail(pRefObj);
		}
	}

	void GetXMatchsString(CString &strText, BOOL bGetID, long nMaxCount);
	void SelFirstMatch();
	BOOL ValidateMatch();
};

