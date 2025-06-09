#pragma once

#include <cmath> //Èý½Ç¼ÆËãcosX£¬ sinX
#include "SttParaObjects.h"
#include "SttParaObjectsGroup.h"

#define TMCLASSID_SttTestBase		(CLASSID_EXLISTCLASS + 0x00700000)

class CSttTestBaseInterface : public CExBaseList
{
public:
	CSttTestBaseInterface()	{}
	virtual ~CSttTestBaseInterface()	{}

public:
	virtual void RegisterFaultParas(CSttParaObjects *pParas) = 0;
	virtual void RegisterFaultParasEx(CSttParaObjectsGroup *pParas) = 0;
	virtual void RegisterSysParas(CSttParaObjects *pParas) = 0;
	virtual void RegisterResults(CSttParaObjects *pParas) = 0;
	virtual void RegisterSearchResults(CSttParaObjects *pParas) = 0;
	virtual void InitParas() = 0;
	virtual void RegisterSpyParas() = 0;
	virtual void RegisterResultsCommon(CSttParaObjects *pParas) = 0;
	virtual void OnSetParaValue(CSttParaObject *pPara)	 = 0;
	virtual void RegisterResultsEx(CSttParaObjectsGroup *pParas)	 = 0;

};