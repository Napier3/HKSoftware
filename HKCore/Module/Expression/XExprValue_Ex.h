//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValueRslt.h  
//CXExprValueRslt,CXExprValue1,CXExprValue2,CXExprValueMin,CXExprValueMax,CXExprValueStd,CXExprValueError

#pragma once

#include "XExprValue.h"

//CXExprValueRslt
class CXExprValueRslt : public CXExprValue
{
public:
	CXExprValueRslt();
	virtual ~CXExprValueRslt();

//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUERSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueRsltKey();     }
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValue1
class CXExprValue1 : public CXExprValue
{
public:
	CXExprValue1();
	virtual ~CXExprValue1();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUE1;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValue1Key();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValue2
class CXExprValue2 : public CXExprValue
{
public:
	CXExprValue2();
	virtual ~CXExprValue2();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUE2;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValue2Key();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueMax
class CXExprValueMax : public CXExprValue
{
public:
	CXExprValueMax();
	virtual ~CXExprValueMax();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEMAX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueMaxKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueMin
class CXExprValueMin : public CXExprValue
{
public:
	CXExprValueMin();
	virtual ~CXExprValueMin();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEMIN;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueMinKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueStd
class CXExprValueStd : public CXExprValue
{
public:
	CXExprValueStd();
	virtual ~CXExprValueStd();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUESTD;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueStdKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueError   ������ݶ�������ޣ�
class CXExprValueError : public CXExprValue
{
public:
	CXExprValueError();
	virtual ~CXExprValueError();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERROR;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRel   ���������ݶ����������ޣ�
class CXExprValueErrorRel : public CXExprValue
{
public:
	CXExprValueErrorRel();
	virtual ~CXExprValueErrorRel();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORREL;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorRelKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorAbs   ����������ݶ��󣨾�������ޣ�
class CXExprValueErrorAbs : public CXExprValue
{
public:
	CXExprValueErrorAbs();
	virtual ~CXExprValueErrorAbs();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORABS;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorAbsKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRslt   ��������� = ����õ������ֵ
class CXExprValueErrorRslt : public CXExprValue
{
public:
	CXExprValueErrorRslt();
	virtual ~CXExprValueErrorRslt();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorRsltKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRelRslt   ������������ = ����õ���������ֵ
class CXExprValueErrorRelRslt : public CXExprValue
{
public:
	CXExprValueErrorRelRslt();
	virtual ~CXExprValueErrorRelRslt();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORRELRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorRelRsltKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorAbsRslt   ������������� = ����õ��ľ������ֵ
class CXExprValueErrorAbsRslt : public CXExprValue
{
public:
	CXExprValueErrorAbsRslt();
	virtual ~CXExprValueErrorAbsRslt();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORABSRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorAbsRsltKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

//CXExprValueCalRslt   ���������������������ݶ������������㣨+��-��*���£��Ľ������
class CXExprValueCalRslt : public CXExprValue
{
public:
	CXExprValueCalRslt();
	virtual ~CXExprValueCalRslt();

	//���غ���
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUECALRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueCalRsltKey();     }
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};