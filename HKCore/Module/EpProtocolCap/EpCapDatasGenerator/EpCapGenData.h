//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenData.h  CEpCapGenData

#pragma once

#include "EpCapDatasGeneratorGlobal.h"

#include "..\..\Module\MemBuffer\CycleMemBuffer.h"

class CEpCapGenData : public CExBaseObject
{
public:
	CEpCapGenData();
	virtual ~CEpCapGenData();


	long  m_dwCapID;
	long  m_dwCapTime;
	long  m_dwCapMs;
	long  m_dwAddrSrc;
	long  m_dwAddrDst;
	long  m_dwType;
	CString m_strFrameData;
//重载函数
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenDataKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	CCycleMemBuffer m_oBuffer;

//私有成员变量访问方法
public:
	BYTE* GetBuffer()		{	return m_oBuffer.GetBuffer();		}
	long GetDataLength()	{	return m_oBuffer.GetDataLength();	}
	CCycleMemBuffer* GetCycleMemBuffer()	{	return &m_oBuffer;	}
	void GetFrameDataBuffer(BYTE **ppBufer, long *pnLength);
};

