//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowShapes.h  CVFlowShapes

#pragma once

#include "LogicShapeMngrGlobal.h"

#include "VFlowShapesBase.h"

#include "VFlowShapeLine.h"
#include "VFlowShape_Data.h"
#include "VFlowShape_Logic.h"
#include "VFlowShape_Expression.h"
#include "VFlowShape_Branch.h"
#include "VFlowShape_Threshold.h"

class CVFlowShapes : public CVFlowShapesBase
{
public:
	CVFlowShapes();
	virtual ~CVFlowShapes();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWSHAPES;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowShapesKey();     }
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
	void InitShapes();//��ʼ��Shape�е��㷨����ʹ�õı�ʶΪ0
	void GetAllResultShapes(CVFlowShapes *pResultRefShapes);//��ȡȫ��û�����,ֻ�������Shape�������Shape
};

