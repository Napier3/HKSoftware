#include "stdafx.h"
#include "DvmXmlRpcValue.h"

#include "..\XmlRpcApi_MFC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

class CDvmXmlRpcValue
{
public:
	CDvmXmlRpcValue();
	virtual ~CDvmXmlRpcValue();
public:
	
#ifdef _USE_XMLRPC_ShareMem	
protected:
	CShareMemSerialize m_oXmlRpcWriteSmBuf;

public:	
	virtual void InitAtsSmBuffer(CString strSmFile);
	CShareMemSerialize* GetXmlRpcWriteSmBuf()	{	return &m_oXmlRpcWriteSmBuf;	}
#endif

public:
	void Dvm_To_XmlRpcValue(CDvmData *pData,XmlRpc::XmlRpcValue &oValue);
	void Dvm_To_XmlRpcValue(CDvmDataset *pDataset,XmlRpc::XmlRpcValue &oValue);
	void Dvm_To_XmlRpcValue(CDataGroup *pGroup,XmlRpc::XmlRpcValue &oValue);
	void Dvm_To_XmlRpcValue(CDvmLogicDevice *pLogicDevice,XmlRpc::XmlRpcValue &oValue);
}g_oDvmXmlRpcValue;


CDvmXmlRpcValue::CDvmXmlRpcValue()
{

}

CDvmXmlRpcValue::~CDvmXmlRpcValue()
{
#ifdef _USE_XMLRPC_ShareMem
	m_oXmlRpcWriteSmBuf.SerializeFree();
#endif
}

#ifdef _USE_XMLRPC_ShareMem
void CDvmXmlRpcValue::InitAtsSmBuffer(CString strSmFile)
{	
	ASSERT(strSmFile.IsEmpty() == FALSE);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += strSmFile;
	m_oXmlRpcWriteSmBuf.CreateFileEx(strFile, 128);
}
#endif	
													
void CDvmXmlRpcValue::Dvm_To_XmlRpcValue(CDvmData *pData,XmlRpc::XmlRpcValue &oValue)
{
	ASSERT(pData != NULL);

	long nLen = 0;
	char *pBuffer = NULL;

#ifdef _USE_XMLRPC_ShareMem
	CShareMemSerialize *pSmBuffer = GetXmlRpcWriteSmBuf();
	dvm_SerializeWrite(pData,pSmBuffer);
	pSmBuffer->GetBuffer(&pBuffer, &nLen);
#else
	CBinarySerialBuffer oBuffer;
	dvm_SerializeWrite(pData,oBuffer);
	oBuffer.GetBuffer(&pBuffer, &nLen);
#endif

	Buffer_To_XmlRpcValue(pBuffer, nLen, oValue);
}

void CDvmXmlRpcValue::Dvm_To_XmlRpcValue(CDvmDataset *pDataset,XmlRpc::XmlRpcValue &oValue)
{
	ASSERT(pDataset != NULL);

	long nLen = 0;
	char *pBuffer = NULL;

#ifdef _USE_XMLRPC_ShareMem
	CShareMemSerialize *pSmBuffer = GetXmlRpcWriteSmBuf();
	dvm_SerializeWrite(pDataset,pSmBuffer);
	pSmBuffer->GetBuffer(&pBuffer, &nLen);
#else
	CBinarySerialBuffer oBuffer;
	dvm_SerializeWrite(pDataset,oBuffer);
	oBuffer.GetBuffer(&pBuffer, &nLen);
#endif

	Buffer_To_XmlRpcValue(pBuffer, nLen, oValue);
}

void CDvmXmlRpcValue::Dvm_To_XmlRpcValue(CDataGroup *pGroup,XmlRpc::XmlRpcValue &oValue)
{
	ASSERT(pGroup != NULL);

	long nLen = 0;
	char *pBuffer = NULL;

#ifdef _USE_XMLRPC_ShareMem
	CShareMemSerialize *pSmBuffer = GetXmlRpcWriteSmBuf();
	dvm_SerializeWrite(pGroup,pSmBuffer);
	pSmBuffer->GetBuffer(&pBuffer, &nLen);
#else
	CBinarySerialBuffer oBuffer;
	dvm_SerializeWrite(pGroup,oBuffer);
	oBuffer.GetBuffer(&pBuffer, &nLen);
#endif

	Buffer_To_XmlRpcValue(pBuffer, nLen, oValue);
}

void CDvmXmlRpcValue::Dvm_To_XmlRpcValue(CDvmLogicDevice *pLogicDevice,XmlRpc::XmlRpcValue &oValue)
{
	ASSERT(pLogicDevice != NULL);

	long nLen = 0;
	char *pBuffer = NULL;

#ifdef _USE_XMLRPC_ShareMem
	CShareMemSerialize *pSmBuffer = GetXmlRpcWriteSmBuf();
	dvm_SerializeWrite(pLogicDevice,pSmBuffer);
	pSmBuffer->GetBuffer(&pBuffer, &nLen);
#else
	CBinarySerialBuffer oBuffer;
	dvm_SerializeWrite(pLogicDevice,oBuffer);
	oBuffer.GetBuffer(&pBuffer, &nLen);
#endif

	Buffer_To_XmlRpcValue(pBuffer, nLen, oValue);
}


////////////////////////////////////////////////

void InitAtsSmBuffer(CString strSmFile)
{
#ifdef _USE_XMLRPC_ShareMem
	g_oDvmXmlRpcValue.InitAtsSmBuffer(strSmFile);
#endif
}

void Dvm_To_XmlRpcValue(CDvmData *pData,XmlRpc::XmlRpcValue &oValue)
{
	g_oDvmXmlRpcValue.Dvm_To_XmlRpcValue(pData, oValue);
}

void Dvm_To_XmlRpcValue(CDvmDataset *pDataset,XmlRpc::XmlRpcValue &oValue)
{
	g_oDvmXmlRpcValue.Dvm_To_XmlRpcValue(pDataset, oValue);
}

void Dvm_To_XmlRpcValue(CDataGroup *pGroup,XmlRpc::XmlRpcValue &oValue)
{
	g_oDvmXmlRpcValue.Dvm_To_XmlRpcValue(pGroup, oValue);
}

void Dvm_To_XmlRpcValue(CDvmLogicDevice *pLogicDevice,XmlRpc::XmlRpcValue &oValue)
{
	g_oDvmXmlRpcValue.Dvm_To_XmlRpcValue(pLogicDevice, oValue);
}

void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDvmData &oData)
{
	char *pRptBuffer = NULL;
	long nLen = 0;

	XmlRpcValue_To_Buffer(oValue, &pRptBuffer, nLen);
	dvm_SerializeRead(&oData,pRptBuffer,nLen);
}

void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDvmDataset &oDataset)
{
	char *pRptBuffer = NULL;
	long nLen = 0;

	XmlRpcValue_To_Buffer(oValue, &pRptBuffer, nLen);
	dvm_SerializeRead(&oDataset,pRptBuffer,nLen);
}

void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDataGroup &oGroup)
{
	char *pRptBuffer = NULL;
	long nLen = 0;

	XmlRpcValue_To_Buffer(oValue, &pRptBuffer, nLen);
	dvm_SerializeRead(&oGroup,pRptBuffer,nLen);
}

void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDvmLogicDevice &oLogicDevice)
{
	char *pRptBuffer = NULL;
	long nLen = 0;

	XmlRpcValue_To_Buffer(oValue, &pRptBuffer, nLen);
	dvm_SerializeRead(&oLogicDevice,pRptBuffer,nLen);
}