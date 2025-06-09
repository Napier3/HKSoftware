//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShape_Branch.h  CVFlowShape_Branch

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShape.h"


class CVFlowShape_Branch : public CVFlowShape
{
public:
	CVFlowShape_Branch();
	virtual ~CVFlowShape_Branch();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPE_BRANCH;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShape_BranchKey();     }
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
	virtual void InitDataTypeUnit();//��ʼ��Shape�����������󡢼������line����������ͼ�����
	CVFlowShape* GetBeginShape_Connected(); //��ȡ��÷�֧�ڵ��������׶�Shape���׶˱���Ψһ���ұ�����
};

