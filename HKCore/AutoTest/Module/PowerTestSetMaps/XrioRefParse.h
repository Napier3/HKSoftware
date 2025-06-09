#pragma once

#include "PowerTestSetMaps.h"
#include "..\..\..\Module\MemBuffer\EquationBuffer.h"
#include "..\XrioRead\XrioCustom.h"
#include "..\GuideBook\Cpus.h"

class CXrioRefParse
{
public:
	CXrioRefParse(void);
	virtual  ~CXrioRefParse(void);

public:
 	BOOL ReadFromRefFile(CPowerTestSetMaps *pPtMaps,const CString &strFile);
//	CDvmDevice *TransXrioRefToDevModel(CXrioCustom *pXrioCustom);
//	
//	BOOL TransRefPathToFullPath(CXrioCustom *pXrioCustom);

protected:
	CBufferBase m_oBuffer;
	long m_nCurrParsePos;

protected:
	BOOL GetRootBlockID(CPowerTestSetMaps *pPtMaps);
	void Offset();
	BOOL Parse_Xrio_Ref(CPowerTestSetMaps *pPtMaps,char *_pTplBuff, long nLen);
	BOOL GetCurLineMapObj(CPowerTestSetMaps *pPtMaps);
	BOOL GetForeignId(CStringA &strForeignId);
	BOOL GetSettingName(CStringA &strName);
};

