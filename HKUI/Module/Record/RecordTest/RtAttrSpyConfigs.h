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

//用于通道级别的表格监视，管理了每个通道所有的属性参数的监视状态
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
    virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID)
    {
#ifdef _PSX_IDE_QT_
        (void)pszClassID;
#endif
        return NULL;
    }
	virtual CExBaseObject* CreateNewChild(long nClassID);

	CRtAttrSpyConfig *FindByAttrID(CString strAttrID);
	void InitAttrSpyConfigs();
	
	//设置通道级别监视的属性个数最大值
	void SetVariableSpyGridMaxColums(long nMaxColum)		{	 m_nVariableSpyGridMaxColums = nMaxColum;   }

	//获取当前监视的属性总个数
	long GetCurrSpyAttrCount();

	//判断是否可以改变属性监视的个数
	BOOL CanChangeAttrSpyCount();

	//判断是否可以增加监视谐波属性
	BOOL CanAddHarmAttrSpy();

private:
	long m_nVariableSpyGridMaxColums;
};

#endif // !defined(AFX_RTATTRSPYCONFIGS_H__AAAEB939_307F_440B_AC0F_73689DB88EBC__INCLUDED_)
