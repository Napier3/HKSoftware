//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgAnalogCh.h  CIecCfgAnalogCh

#pragma once

#include "IecCfgDataMngrGlobal.h"
#include "IecCfgDataChBase.h"


class CIecCfgAnalogCh : public CIecCfgDataChBase
{
public:
	CIecCfgAnalogCh();
	virtual ~CIecCfgAnalogCh();


	float  m_fPrimNom;
	float  m_fSecNom;
	float  m_fValue;
	float  m_fCoef;
	long  m_nOutput;
	long  m_nOffset;
	CString m_strUnit;
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGANALOGCH;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgAnalogChKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
// 	virtual void GetChFlagHcn(long &nFlag, long &nHcn);
//	virtual DWORD CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset);
	virtual void InitForSclRead(long &nUChIndex, long &nIChIndex);
// 	virtual DWORD InitArtAmpDigdata(CArtAmpDigdata *pData);

	BOOL Is_U_CH()
	{
		return (m_strAppChID.Left(1) == _T("U"));
	}
	BOOL Is_I_CH()
	{
		return (m_strAppChID.Left(1) == _T("I"));
	}
	BOOL Is_None_CH()
	{
		if (Is_U_CH())
		{
			return FALSE;
		}

		if (Is_I_CH())
		{
			return FALSE;
		}

		return TRUE;
	}

	void InitUnit()
	{
		if (Is_U_CH())
		{
			m_strUnit = _T("V");
		}
		else if (Is_I_CH())
		{
			m_strUnit = _T("A");
		}
		else
		{
			m_strUnit = _T("");
		}
	}
};

