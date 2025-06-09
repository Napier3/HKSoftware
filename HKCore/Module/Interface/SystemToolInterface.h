//////////////////////////////////////////////////////////////////////////
//SystemToolInterface.h
//SystemTool组件的接口定义和扩展文件

#ifndef _SYSTEMTOOL_INTERFACE_H__
#define _SYSTEMTOOL_INTERFACE_H__

#import "SystemTool.tlb"

inline void BinarySerializeAddBufferLen(CBinarySerialBuffer &oBinaryBuffer, long nLen) 
{
	oBinaryBuffer->AddBufferLength(nLen);
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const CString &strVal) 
{
	oBinaryBuffer->AddBufferLength((strVal.GetLength()+1)*2);
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, BSTR strVal) 
{
	oBinaryBuffer->AddBufferLength((wcslen(strVal)+1)*2);
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, wchar_t* strVal) 
{
	oBinaryBuffer->AddBufferLength((wcslen(strVal)+1)*2);
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const long &nVal) 
{
	oBinaryBuffer->AddBufferLength(sizeof(long));
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const double &dVal) 
{
	oBinaryBuffer->AddBufferLength(sizeof(double));
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const float &fVal) 
{
	oBinaryBuffer->AddBufferLength(sizeof(float));
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const CString &strVal)
{
	oBinaryBuffer->PutString(_bstr_t(strVal));
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, BSTR strVal)
{
	oBinaryBuffer->PutString(strVal);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const long &nVal)
{
	oBinaryBuffer->PutLong(nVal);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const double &dVal)
{
	oBinaryBuffer->PutDouble(dVal);
}

inline void BinarySerialWrite(CBinarySerialBuffer &oBinaryBuffer, const float &fVal)
{
	oBinaryBuffer->PutFloat(fVal);
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, CString &strVal)
{
	strVal = (TCHAR*)oBinaryBuffer->GetString();
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, BSTR strVal)
{
	ASSERT (FALSE);
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, long &nVal)
{
	nVal = oBinaryBuffer->GetLong();
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, double &dVal)
{
	dVal = oBinaryBuffer->GetDouble();
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, float &fVal)
{
	fVal = oBinaryBuffer->GetFloat();
}

#endif
