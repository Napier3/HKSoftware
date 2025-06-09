//////////////////////////////////////////////////////////////////////////
//BinarySerialInterface.h

#ifndef _BINARYSERIALIZE_INTERFACE_H__
#define _BINARYSERIALIZE_INTERFACE_H__

#include "BinarySerialBuffer.h"

#ifndef _PSX_IDE_QT_
#include "ShareMemSerialize.h"
#endif

inline void BinarySerializeAddBufferLen(CBinarySerialBuffer &oBinaryBuffer, long nLen) 
{
	oBinaryBuffer.AddBufferLength(nLen);
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const CString &strVal) 
{
#ifdef _UNICODE
	oBinaryBuffer.AddBufferLength((strVal.GetLength()+1)*2);
#else
	oBinaryBuffer.AddBufferLength(strVal.GetLength()+1);
#endif
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, BSTR strVal) 
{
	oBinaryBuffer.AddBufferLength((wcslen(strVal)+1)*2);
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const long &nVal) 
{
	oBinaryBuffer.AddBufferLength(sizeof(nVal));
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const COLORREF &nVal) 
{
	oBinaryBuffer.AddBufferLength(sizeof(nVal));
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const double &dVal) 
{
	oBinaryBuffer.AddBufferLength(sizeof(dVal));
}

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const float &fVal) 
{
	oBinaryBuffer.AddBufferLength(sizeof(fVal));
}

#ifndef _PSX_IDE_QT_
inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, const SYSTEMTIME &tm)
{
	oBinaryBuffer.AddBufferLength(sizeof(tm));
}
#endif

inline void BinarySerializeCalLen(CBinarySerialBuffer &oBinaryBuffer, char *pszString)
{
	oBinaryBuffer.AddBufferLength(strlen(pszString) + 1);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const CString &strVal)
{
	oBinaryBuffer.PutString(strVal);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const long &nVal)
{
	oBinaryBuffer.PutLong(nVal);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const COLORREF &nVal)
{
	oBinaryBuffer.PutLong(nVal);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const double &dVal)
{
	oBinaryBuffer.PutDouble(dVal);
}

inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const float &fVal)
{
	oBinaryBuffer.PutFloat(fVal);
}

//#ifndef _PSX_IDE_QT_
inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, const SYSTEMTIME &tm)
{
	oBinaryBuffer.PutSystemtime(tm);
}
//#endif

//2020-12-27  lijunqing
inline void BinarySerializeWrite(CBinarySerialBuffer &oBinaryBuffer, char *pszString)
{
	oBinaryBuffer.WriteString(pszString);
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, CString &strVal)
{
	//strVal = oBinaryBuffer.GetString();
	oBinaryBuffer.GetString(strVal);
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, long &nVal)
{
	nVal = oBinaryBuffer.GetLong();
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, COLORREF &nVal)
{
	nVal = oBinaryBuffer.GetLong();
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, double &dVal)
{
	dVal = oBinaryBuffer.GetDouble();
}

inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, float &fVal)
{
	fVal = oBinaryBuffer.GetFloat();
}

//#ifndef _PSX_IDE_QT_
inline void BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, SYSTEMTIME &tm)
{
	tm = oBinaryBuffer.GetSystemtime();
}
//#endif

//2020-12-27  lijunqing
inline long BinarySerializeRead(CBinarySerialBuffer &oBinaryBuffer, char *pszString)
{
	return oBinaryBuffer.ReadString(pszString);
}

#endif
