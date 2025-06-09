#pragma once
#include "ByteBlocks.h"
#include "ProtocolXmlRWKeys.h"
#include "DataByteBlock.h"
#include "PpDataBinds.h"

class CDvmData;
class CPpTag;

/*
数据定义对象，组成规则为：字节块集+数据字节块+字节块集+数据绑定，数据字节块为DataByteBlock
*/
class CBbData:	public CByteBlocks
{
public:
	CBbData(void);
	virtual ~CBbData(void);

public:
	CBbVariables		*m_pVariables;				//Data对象的变量，不作为子对象出现，派生类具体实现
	CDataByteBlock		*m_pDataByteBlock;		//数据定义字节块，派生类具体实现
	CPpDataBinds		*m_pDataBinds;
	CString m_strMaxCount;

	//实际解析的时候使用，暂时注释掉
	//long m_nMaxCount;

public:
	virtual UINT GetClassID()				{        return PPCLASSID_BBDATA;													}
	virtual BSTR GetXmlElementKey()	{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataKey;		}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

public:
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//字节块的制造
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	{		return PpParseError();		};

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	virtual CExBaseObject* QueryByBind(BOOL bQueryDataNode);
	CDvmData* GetDeviceNodeDataByBind();
	virtual CExBaseObject* BindItemIndex(long nItemIndex);
	long GetBindItemIndex();

private:
	CExBaseObject* QueryByBindStack(void **ppDataQueryBindStatck, BOOL bQueryDataNode);
	void InitQueryBindStack(void **ppDataQueryBindStatck);

};
