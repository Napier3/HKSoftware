//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangFile.h  CXLangFile

#pragma once


#include "..\XLanguage.h"

class CXLangFile : public CExBaseList
{
public:
	CXLangFile();
	virtual ~CXLangFile();

	CXLanguage m_oXLanguage;

//���غ���
public:
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	void SetRefXLanguage(BOOL b)	{	m_bRefXLanguage = b;	}
	void FreeXLanguage();

//˽�г�Ա����
private:
	BOOL m_bRefXLanguage;

//˽�г�Ա�������ʷ���
public:
	BOOL OpenXLangFile();
	BOOL HasXLangFileOpen();
};


//�����ַ�����Դ�������
class CXLangItemDev : public CExBaseList
{
public:
	CXLangItemDev();
	virtual ~CXLangItemDev();

	CXLangItem* FindXLangItem(long nXLangIndex);
	BOOL HasError();
	void DeleteXLang();
	void CopyXLang(CExBaseList &listAllFiles);
	void OverWriteID(CExBaseList &listAllFiles);
	void OverWriteSrcText(CExBaseList &listAllFiles);
	void MatchTransText(CExBaseList &listAllFiles);

public:
	CXLangItem *m_pRefItem;
	long  m_nRefCount;
};

class CXLangFileRsItemMngr : public CExBaseList
{
public:
	CXLangFileRsItemMngr();
	virtual ~CXLangFileRsItemMngr();

	CExBaseList m_listFiles;
	BOOL m_bModifiedFlag;

public:
	void AddFile(CXLangFile *pFile);
	void AddFile(CXLangFile *pFile, long nXLangIndex);
	long FindXLangItemIndex(CXLangItem *pItem);
	void UpdateRefCount(long nCount);
	void DeleteRsItem(CXLangItemDev *pXLangItemDev);
	void CopyRsItem(CXLangItemDev *pXLangItemDev, CXLangItem *pItem);
	void SaveXLangFiles();
	BOOL CopyXLangItems(CExBaseList &listItems);
	BOOL OverWriteID(CExBaseList &listItems);
	BOOL OverWriteSrcText(CExBaseList &listItems);
	BOOL MatchTransText(CExBaseList &listItems);
	CXLangItemDev* FindXBy_Item(CXLangItem *pItem, long nXLangIndex);

protected:
	void AddXLangItem(CXLangItem *pItem);
	void AddXLangItem(CXLangItem *pItem, long nXLangIndex);
	CXLangItemDev* FindXBy_Id_SrcText(CXLangItem *pItem, long nXLangIndex);
	CXLangItemDev* FindXBy_SrcText(CXLangItem *pItem, long nXLangIndex);
	CXLangItemDev* FindXBy_Id(CXLangItem *pItem, long nXLangIndex);

};