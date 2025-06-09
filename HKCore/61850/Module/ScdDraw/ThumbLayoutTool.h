//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.h  CXScdDrawIed

#pragma once

#include "XScdDrawIedThumbnail.h"
#include "..\..\..\Module\BaseClass\BaseList.h"

#define ThumbLayoutElement_pos_None  0x00FFFFFF

class CThumbLayoutElement : public CExBaseObject
{
public:
	CThumbLayoutElement();
	virtual ~CThumbLayoutElement();
	
	CXScdDrawIedThumbnail *m_pIedRef;
	long m_nPos;
	long m_nPosBackup;
	
	BOOL HasLayout()	{	return m_nPos != ThumbLayoutElement_pos_None;	}
	void ResetLayout()	{	m_nPos = ThumbLayoutElement_pos_None;	}

	void BackupPos();
	void RestorePos();

};


class CThumbLayoutGroup : public CExBaseList
{
public:
	CThumbLayoutGroup();
	virtual ~CThumbLayoutGroup();

	//主Element
	CThumbLayoutElement *m_pMainElement;

	//已经排布的Element
	CExBaseList m_listHasLayoutElement;

	//需要排布的Element
	CExBaseList m_listNeedLayoutElement;

	long m_nLinkCount;
	long m_nLength;

public:
	void InitGroup(CThumbLayoutElement *pIedElement);
	long CalTotalLength();

	void InitGroupLements();
	void LayoutElements(long nBeginIndex, long nFlag);
	void ResetLayout();
	void CalMainElementPos();
	void BackupPos();
	void RestorePos();

protected:
	long GetMinPos(CExBaseList *pList, long &nValue);
	long GetMaxPos(CExBaseList *pList, long &nValue);

	void BackupPos(CExBaseList *pList);
	void RestorePos(CExBaseList *pList);

};

class CThumbLayoutTool : public CExBaseList
{
private:
	CThumbLayoutTool();
	virtual ~CThumbLayoutTool();

	static CThumbLayoutTool* g_pThumbLayoutTool;
	static long g_nThumbLayoutToolRef;

	CExBaseList m_listProtIedElement;
	CExBaseList m_listMeasIedElement;
	CExBaseList m_listMuStIedElement;

	CExBaseList m_listProtGroup;
	CExBaseList m_listMeasGroup;

	CExBaseList m_listProtLayout;
	CExBaseList m_listMeasLayout;

public:
	static CThumbLayoutTool* Create();
	static void Release();

	static CThumbLayoutElement* FindElement(CXScdDrawIedThumbnail *pIed);
	static CThumbLayoutElement* FindProtElement(CXScdDrawIedThumbnail *pIed);
	static CThumbLayoutElement* FindMeasElement(CXScdDrawIedThumbnail *pIed);
	static CThumbLayoutElement* FindMuStElement(CXScdDrawIedThumbnail *pIed);
	static void InitProtElement(CExBaseList *pListIed);
	static void InitMeasElement(CExBaseList *pListIed);
	static void InitMuStElement(CExBaseList *pListIed);
	static void InitProtGroup();
	static void InitMeasGroup();

	static void LayoutProtElement();
	static void LayoutMeasElement();

protected:
	CThumbLayoutElement* FindElement(CXScdDrawIedThumbnail *pIed, CExBaseList *pList);

	void _LayoutProtElement();
	void _LayoutMeasElement();

	void _SortProtGroup(CExBaseList *pList);
	void _AddGroup(CThumbLayoutGroup *pGroup, CExBaseList *pDestList);
	long _CalLayoutValue(CThumbLayoutGroup *pGroup, CExBaseList *pDestList, long nPos);

	void BackupPos(CExBaseList *pList);
	void RestorePos(CExBaseList *pList);

};

