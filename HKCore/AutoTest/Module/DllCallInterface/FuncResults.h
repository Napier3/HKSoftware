//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FuncResults.h  CFuncResults

#pragma once

#include "DllCallGlobal.h"

#include "..\..\..\Module\DataMngr\DvmData.h"


class CFuncResults : public CDvmData
{
public:
	CFuncResults();
	virtual ~CFuncResults();


//���غ���
public:
	virtual UINT GetClassID() {    return DLCLCLASSID_CFUNCRESULTS;   }
	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CFuncResultsKey();     }
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

