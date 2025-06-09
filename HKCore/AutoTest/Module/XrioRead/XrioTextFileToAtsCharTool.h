#pragma once

#include "XrioTextFile.h"

#include "../Characteristic/Characteristics.h"
#include "../../../Module/FilterText/FilterTextMngr.h"

#define RIO_KEY_DISTANCE   _T("DISTANCE")
#define RIO_KEY_OVERCURRENT   _T("OVERCURRENT")
#define RIO_KEY_SYNCHRO   _T("SYNCHRO")
#define RIO_KEY_DIFFERENTIAL   _T("DIFFERENTIAL")

#define RIO_KEY_ZONE   _T("ZONE")
#define RIO_KEY_DIFFBIAS   _T("DIFFBIAS")
#define RIO_KEY_DIFF   _T("DIFF")
#define RIO_KEY_BIAS   _T("BIAS")

//////////////////////////////////////////////////////////////////////////
//曲线相关的关键字
#define RIO_KEY_TRIPCHAR   _T("TRIPCHAR ")
#define RIO_KEY_TRIPCHAR_EARTH   _T("TRIPCHAR-EARTH")
#define RIO_KEY_LENSTOMATOSHAPE   _T("LENSTOMATOSHAPE")
#define RIO_KEY_MHOSHAPE   _T("MHOSHAPE")
#define RIO_KEY_SHAPE   _T("SHAPE")
//绘图元素
#define RIO_KEY_ARCP   _T("ARCP")
#define RIO_KEY_ARC   _T("ARC")
#define RIO_KEY_LINEP   _T("LINEP")
#define RIO_KEY_AUTOCLOSE   _T("AUTOCLOSE")
#define RIO_KEY_INVERT   _T("INVERT")
#define RIO_KEY_ANGLE   _T("ANGLE")
#define RIO_KEY_OFFSET   _T("OFFSET")
#define RIO_KEY_REACH   _T("REACH")
#define RIO_KEY_WIDTH   _T("WIDTH")
#define RIO_KEY_START   _T("START ")
#define RIO_KEY_LINE   _T("LINE")
#define RIO_KEY_STOP   _T("STOP")
#define RIO_KEY_CLOSE   _T("CLOSE")

#define RIO_KEY_LABEL   _T("LABEL")
#define RIO_KEY_NAME   _T("NAME")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")

#define RIO_KEY_YES   _T("YES")
#define RIO_KEY_NO   _T("NO")
// #define RIO_KEY_   _T("")
// #define RIO_KEY_   _T("")

inline long rio_get_key_value_yes_no(const CString &strValue)
{
	if (strValue == RIO_KEY_YES)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

class CXrioTextFileToAtsCharTool
{
public:
	CXrioTextFileToAtsCharTool();
	virtual ~CXrioTextFileToAtsCharTool();

protected:
	//打开的rio历史记录文件
	CFilterTextMngr m_oRioFileHis;

	CCharacteristics *m_pCharacteristicsRef;
	
public:
	void AttatchCharacteristics(CCharacteristics *pCharacteristics)	{	m_pCharacteristicsRef = pCharacteristics;	}
	BOOL ImportCharsFromRioFile(const CString &strRioFile);
	BOOL ImportCharsFromRioFile(CCharacteristics *pChars, const CString &strRioFile);
	BOOL ImportCharFromRioGroup(CCharacteristic *pChar, CXrioGroup *pGroup);

protected:
	void ParseGroup(CXrioGroup *pGroup);

	void AddChar_Zone(CXrioGroup *pGroup);
	void InitChar_Zone(CXrioGroup *pGroup, CCharacteristic *pChar);
	void InitChar_ZoneAttrs(CXrioData *pData, CCharacteristic *pChar, CDvmData *pCharAttrs);
	void AddChar_Zone_Group(CXrioGroup *pGroup, CCharacteristic *pChar);
	void AddChar_Zone_Shape(CXrioGroup *pGroup, CCharacteristic *pChar);
	void AddChar_Zone_Mho(CXrioGroup *pGroup, CCharacteristic *pChar);
	void AddChar_Zone_Lens(CXrioGroup *pGroup, CCharacteristic *pChar);
	void AddChar_Zone_TripChar(CXrioGroup *pGroup, CCharacteristic *pChar);

	CCharElement* AddChar_Element_Line(CXrioData *pData, CCharacterArea *pArea);
	CCharElementLined* AddChar_Element_Line(CXrioData *pData, CCharacterArea *pArea, CCharElementLined *pLinedPrev);
	CCharElement* AddChar_Element_Linep(CXrioData *pData, CCharacterArea *pArea);
	CCharElement* AddChar_Element_Arc(CXrioData *pData, CCharacterArea *pArea);
	CCharElement* AddChar_Element_Arcp(CXrioData *pData, CCharacterArea *pArea);
	CCharElementLined* AddChar_Element_Start(CXrioData *pData, CCharacterArea *pArea);
	CCharElementLined* AddChar_Element_Stop(CXrioData *pData, CCharacterArea *pArea, CCharElementLined *pLinedPrev);

	void AddChar_DiffBias(CXrioGroup *pGroup);
	void InitChar_DiffBias(CXrioGroup *pGroup, CCharacteristic *pChar);

};
