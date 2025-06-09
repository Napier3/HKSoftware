//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenerator.h  CUibGenerator

#pragma once

#include "UIBGeneratorGlobal.h"
#include "UibGenState.h"

#include "..\Comtrade\ComtradeMngr.h"

class CUibGenerator : public CExBaseList
{
public:
	CUibGenerator();
	virtual ~CUibGenerator();

	CRcdComtradeFile *m_pRcdComtradeFile;
	CString m_strUibGenFile;

	float  m_fFreq;
	long  m_nSampRate;
	long  m_nUchCount;
	long  m_nIchCount;
	long  m_nBchCount;

	static const CString g_strUibGenFilePostfix;
	static const CString g_strUibGenFileFilter;
	static const CString g_strUibGenFileTitle;
//重载函数
public:
	virtual UINT GetClassID() {    return UIBGCLASSID_CUIBGENERATOR;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBGeneratorXmlRWKeys::CUibGeneratorKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	long m_nTotalPoints;

//私有成员变量访问方法
public:
	BOOL OpenUibGeneratorFile(CWnd *pParentWnd);
	BOOL OpenUibGeneratorFile(const CString &strFile);

	void InitUIBGenerate();
	void UIBGenerate();

protected:
	void InitGenerate();
	void GetAnalogs(CExBaseList &listAnalogs);
	void GetBinarys(CExBaseList &listBinarys);
	float CalTimeLong();
};

//////////////////////////////////////////////////////////////////////////
//CUibGeneratorMngr
class CUibGeneratorMngr : public CExBaseList
{
private:
	CUibGeneratorMngr();
	virtual ~CUibGeneratorMngr();

	static CUibGeneratorMngr *g_pUibGeneratorMngr;
	static long g_nUibGeneratorMngr;

public:
	static CUibGeneratorMngr* Create();
	static void Release();

	static BOOL PopOpenUibGenerator(CString &strFile);
	static CUibGenerator* OpenUibGenerator();
	static CUibGenerator* OpenUibGenerator(const CString &strFile);
	static CUibGenerator* FindUibGenerator(const CString &strFile);
	static CUibGenerator* GetUibGenerator(long nIndex);
	static BOOL CloseUibGenerator(const CString &strFile);
	static BOOL CloseUibGenerator(CUibGenerator *pUibGenerator);
	static BOOL CloseComtradeFile(CRcdComtradeFile *pComtradeFile);
	static CUibGenerator* FindByComtradeFile(CRcdComtradeFile *pComtradeFile);
	static long GetUibGeneratorCount();
};