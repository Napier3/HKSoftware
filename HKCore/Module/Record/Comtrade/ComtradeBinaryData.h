// ComtradeBinaryData.h: interface for the CComtradeBinaryData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTRADEBINARYDATA_H__F33EE038_AC74_423D_9CA1_E655840770C0__INCLUDED_)
#define AFX_COMTRADEBINARYDATA_H__F33EE038_AC74_423D_9CA1_E655840770C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComtradeDataBase.h"
#include "ComtradeFileGlobal.h"

class CComtradeBinaryData : public CComtradeDataBase  
{
public:
	long m_nNormalState;//y这个属性
	int m_nDataIndex; // 数据在一个WORD中的哪一位
	//CString m_strSttDataFile;//该通道对应的data文件中的值

	virtual void GetChanInfor(CString* pstrParse,long nOffSet = 0);
	virtual void SaveChanInfo(CString& strInfor);
	virtual BOOL IsAnalogData()		{	return FALSE;	}
	long GetChIndex();//2024-02-27 wuxinyi 获取当前通道的顺序

	virtual BOOL InsertBySampleRate(float* pdSrcSamRate,long* pnSrcDataPoints,long nSrcSamAmount, double dDstSmpRate,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime);//zhouhj 20200914

	//zhouhj 2024.2.4 增加用于插入稳态波形
	void InsertNormalCyclePoints(long nInsertPoints,long nDataFileType);
protected:
	virtual BOOL InsertBySampleRate(const long &nSrcBeginPoint,const long &nSrcEndPoint ,long &nDstBeginPoint,
		double &dSrcBeginPointTime,const double &dSrcGap,const double &dDstGap,CComtradeDataBase *pDstData,const double &dDstBeginOffsetTime);//zhouhj 20200914

public:
	CComtradeBinaryData();
	virtual ~CComtradeBinaryData();

public:
	virtual UINT GetClassID() {    return CMTRDCLASSID_BINARY;   }
	//xupf
public:
//	virtual UINT GetClassID() {    return GLOBALCLASSID_CCOMTRADEBINARYDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CComtradeFileXmlRWKeys::CComtradeBinaryDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual BOOL CopyOwn(CBaseObject* pDest);
};

#endif // !defined(AFX_COMTRADEBINARYDATA_H__F33EE038_AC74_423D_9CA1_E655840770C0__INCLUDED_)
