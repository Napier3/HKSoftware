// XpoRptFillFactory.h : header file

#pragma once

#include "../../../Module/OSInterface/OSInterface.h"

class XpoRptFillBase
{
public:
    virtual void Xpo_RptFill(const CString &strXmlFile, const CString &strOutFile) = 0;
    virtual ~XpoRptFillBase(){}

};

class XpoRptFillFactory
{
public:
    XpoRptFillBase* CreateXpoRpt(long &strRptId);
    virtual ~XpoRptFillFactory(){}
};
