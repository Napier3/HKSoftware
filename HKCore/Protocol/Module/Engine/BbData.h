#pragma once
#include "ByteBlocks.h"
#include "ProtocolXmlRWKeys.h"
#include "DataByteBlock.h"
#include "PpDataBinds.h"

class CDvmData;
class CPpTag;

/*
���ݶ��������ɹ���Ϊ���ֽڿ鼯+�����ֽڿ�+�ֽڿ鼯+���ݰ󶨣������ֽڿ�ΪDataByteBlock
*/
class CBbData:	public CByteBlocks
{
public:
	CBbData(void);
	virtual ~CBbData(void);

public:
	CBbVariables		*m_pVariables;				//Data����ı���������Ϊ�Ӷ�����֣����������ʵ��
	CDataByteBlock		*m_pDataByteBlock;		//���ݶ����ֽڿ飬���������ʵ��
	CPpDataBinds		*m_pDataBinds;
	CString m_strMaxCount;

	//ʵ�ʽ�����ʱ��ʹ�ã���ʱע�͵�
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
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//�ֽڿ������
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
