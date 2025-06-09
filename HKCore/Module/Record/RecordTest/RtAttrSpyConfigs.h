// RtAttrSpyConfigs.h: interface for the CRtAttrSpyConfigs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTATTRSPYCONFIGS_H__AAAEB939_307F_440B_AC0F_73689DB88EBC__INCLUDED_)
#define AFX_RTATTRSPYCONFIGS_H__AAAEB939_307F_440B_AC0F_73689DB88EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MODULE/BASECLASS/ExBaseList.h"
#include "RtAttrSpyConfig.h"
#include "RecordTestClassDef.h"
#define Max_Harm_CalCount 2

//����ͨ������ı����ӣ�������ÿ��ͨ�����е����Բ����ļ���״̬
class CRtAttrSpyConfigs : public CExBaseList  
{
public:
	static CRtAttrSpyConfigs *g_pRtAttrSpyConfigs;
	static CRtAttrSpyConfigs* CreategRtAttrSpyConfigs();
	static long  g_nRtAttrSpyConfigsCount;
	static long  Release();	
	
private:
	CRtAttrSpyConfigs();
	virtual ~CRtAttrSpyConfigs();
public:
	virtual UINT GetClassID()				{	return RTCLASSID_ATTRSPYCONFIG;		}
// 	virtual CExBaseObject* CreateNewChild()	{	return NULL;		}
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID) {	return NULL;		}
	virtual CExBaseObject* CreateNewChild(long nClassID);

	CRtAttrSpyConfig *FindByAttrID(CString strAttrID);
	void InitAttrSpyConfigs();
	
	//����ͨ��������ӵ����Ը������ֵ
	void SetVariableSpyGridMaxColums(long nMaxColum)		{	 m_nVariableSpyGridMaxColums = nMaxColum;   }

	//��ȡ��ǰ���ӵ������ܸ���
	long GetCurrSpyAttrCount();

	//�ж��Ƿ���Ըı����Լ��ӵĸ���
	BOOL CanChangeAttrSpyCount();

	//�ж��Ƿ�������Ӽ���г������
	BOOL CanAddHarmAttrSpy();

private:
	long m_nVariableSpyGridMaxColums;
};

#endif // !defined(AFX_RTATTRSPYCONFIGS_H__AAAEB939_307F_440B_AC0F_73689DB88EBC__INCLUDED_)
