//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FuncResults.h  CFuncResults

#pragma once

#include "DllCallGlobal.h"

#include "..\..\..\Module\DataMngr\DvmData.h"


class CFuncResults : public CDvmData
{
public:
	CFuncResults();
	virtual ~CFuncResults();


//重载函数
public:
	virtual UINT GetClassID() {    return DLCLCLASSID_CFUNCRESULTS;   }
	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CFuncResultsKey();     }
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

