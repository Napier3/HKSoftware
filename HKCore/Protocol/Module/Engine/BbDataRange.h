#pragma once
#include "../../../module/baseclass/ExBaseObject.h"

#include "ProtocolXmlRWKeys.h"


class CBbDataRange :	public CExBaseObject
{
public:
	CBbDataRange(void);
	virtual ~CBbDataRange(void);

public:
	CString m_strType;
	CString m_strValue;

public:
		virtual void InitAfterRead();
 
	    virtual UINT GetClassID(){ return PPCLASSID_BBDATARANGE; };
		virtual BSTR GetXmlElementKey()  {  return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRangeKey;   };
		/*virtual long IsEqual(CExBaseObject* pObj)
		virtual long Copy(CExBaseObject* pDesObj)
		virtual CExBaseObject* Clone()
		virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)*/
		virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
		virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	BYTE* GetValueBuffer(long &nLen);
	void InitValueBuffer();

private:
	//BYTE m_pValueBuffer[60];
	BYTE *m_pValueBuffer;
	long m_nValueBufferLength;


	BYTE HexToByte(BYTE *p)
	{
		if ('0' <= *p && *p <= '9')
		{
			return *p - '0';
		}

		if ('a' <= *p && *p <= 'f')
		{
			return *p - 'a' + 10;
		}

		if ('A' <= *p && *p <= 'F')
		{
			return *p - 'A' + 10;
		}

		return 0;
	}

	void HexToByte(BYTE *pSrc, BYTE *pDest)
	{
		*pDest = HexToByte(pSrc) * 16 + HexToByte( pSrc+1 );
	}

	void FreeValBuffer()
	{
		if (m_pValueBuffer != NULL)
		{
			delete m_pValueBuffer;
			m_pValueBuffer = NULL;
		}
	}
};
