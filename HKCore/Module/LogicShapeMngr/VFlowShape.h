//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShape.h  CVFlowShape

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShapeBase.h"
#include "VFlowShapeLines.h"


class CVFlowShape : public CVFlowShapeBase
{
public:
	CVFlowShape();
	virtual ~CVFlowShape();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPE;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapeKey();     }
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
	BOOL m_bHasAttachCalc;//�ж��Ƿ�������㷨������

//���Ա������ʷ���
public:
	virtual void UpdateLineType_Color();//����Shape�������͡���ɫ
	virtual void InitDataTypeUnit();//��ʼ��Shape�����������󡢼������line����������ͼ�����

	CVFlowShapeLines m_oInLines;//�������������
	CVFlowShapeLines m_oOutLines;//�������������
};

