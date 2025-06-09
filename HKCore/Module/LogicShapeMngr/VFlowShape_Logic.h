//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShape_Logic.h  CVFlowShape_Logic

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShape.h"


class CVFlowShape_Logic : public CVFlowShape
{
public:
	CVFlowShape_Logic();
	virtual ~CVFlowShape_Logic();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPE_LOGIC;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShape_LogicKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	virtual void UpdateLineType_Color();

protected:
	long CalcLogicValue();
	long CalcLogicValue_AND();
	long CalcLogicValue_OR();
	long CalcLogicValue_NOT();
};

