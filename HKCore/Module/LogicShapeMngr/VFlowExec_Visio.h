//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//VFlowExec_Visio.h  CVFlowExec_Visio

#pragma once

#include "LogicShapeMngrGlobal.h"


#include "VFlowShapeLines.h"
#include "VFlowShapes.h"

#include "../Visio/VisioReadWrite.h"
#include "../DataMngr/DvmDataset.h"


/*
��һ������Visioͼ�ļ����� OpenVisioFile
�ڶ���������Visio�е�ǰҳ��Index��name���õ�ǰ�����Sheetҳ  ����InitFlowShapesFromPage�������ڸú�������ɶԵ�ǰ����sheetҲ������ͼ����״�������Ĵ��������ֹ��ܳ�ʼ��
����������Ҫ�ⲿģ�齫�������ݵ��������ͺ͵�λ����m_oOrigDataDataset�����У�ֻ������ԭʼ������Ҫ���ⲿ��ȡ�������ͣ����������޷��жϾ�����������
���Ĳ�������UpdataDataTypeUnit_AllOrigDatas������ɶ�������ԭʼ���ݣ��������ͺ͵�λ�ķ�ֵ
���岽������UpdataValue_AllOrigDatas������ɶ�����ԭʼ���ݵĸ�ֵ
������������UpdateAllShapes���������µ�ǰ�������

��;����ͼ����ʾ���裺
��һ�����ⲿģ�����m_oOrigDataDataset������ֵ�����Ӹ��µ�DvmData��m_nIndex����Ϊ1
�ڶ���������UpdataValue_AllOrigDatas������ɶ�����ԭʼ���ݵĸ�ֵ(����������)
������������UpdateAllShapes���������µ�ǰ�������(����������)

*/




class CVFlowExec_Visio : public CExBaseList
{
public:
	CVFlowExec_Visio();
	virtual ~CVFlowExec_Visio();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWEXEC_VISIO;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowExec_VisioKey();     }
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
	BOOL OpenVisioFile(const CString &strVisioFilePath, BOOL bVisible = TRUE);//�򿪵�ǰVisioͼ
	BOOL SaveVisioFile(); //���浱ǰVisioͼ
	void CloseFile();  //�رյ�ǰ�ĵ�
	void QuitApp();
	BOOL InitFlowShapesFromPage(const CString &strPageName);//����Page���ƣ����Ҷ�Ӧ��page��������ҳ����Ϊ��ǰҳ���õ�ǰҳ��������״��ʼ����������
	BOOL InitFlowShapesFromPage(long nPageIndex);//����Page��ʶ�����Ҷ�Ӧ��page��������ҳ����Ϊ��ǰҳ���õ�ǰҳ��������״��ʼ����������,��1��ʼ����

	BOOL UpdataValue_AllOrigDatas();//�������е�ԭʼ����ֵ
	BOOL UpdataDataTypeUnit_AllOrigDatas();//�������е�ԭʼ���ݶ�Ӧ���������ͼ���λ
	BOOL UpdateAllShapes();//���ݵ�ǰֵ,����ȫ��Shape��Line

	BOOL SetOrigDataValue(const CString &strOrigDataRef,const CString &strValue);//���µ���ԭʼ����,ֻ��������ֵ,�����½���,�������������ݹ̶�����Visio����
	BOOL GetOrigDataValue(const CString &strOrigDataRef,CString &strValue);//��ȡ����ԭʼ����,ֻ���ڴ��ȡ,����ʵ�ʽ����ȡ
	BOOL SetOrigDataValue_UI(const CString &strOrigDataRef,const CString &strValue);//���µ���ԭʼ����,ֻ��������ֵ,ͬʱ���½���
	BOOL GetOrigDataValue_UI(const CString &strOrigDataRef,CString &strValue);//��ȡ����ԭʼ����,�ӽ����ȡ

	BOOL SetShapeValueByID(const CString &strShapeID,const CString &strValue);//������״ֵ��������״��ID
	BOOL GetShapeValueByID(const CString &strShapeID,CString &strValue);//��ȡ��״ֵ��������״��ID

	CVFlowShape* FindShapeByID(const CString &strShapeID);
	CVisioReadWrite* GetVisioReadWrite()	{	return &m_oVisioReadWrite;	}
	CExBaseList* GetPagesList()	{	return m_oVisioReadWrite.GetPageList();	}
	void ActivePage(const CString &strPage); //�������ƣ�����ҳ��


	CDvmDataset m_oOrigDataDataset;//�����ݼ��е����ݶ���CDvmData������ԭʼ���ݵ���Ϣ,����m_strIDΪԭʼ����ID��m_strNameΪԭʼ����·��;
	//m_strDataType��m_strUnit��m_strValue���ⲿ��ȡ,������ݵ�ʵ���������͡���λ��ֵһ�£�m_nIndex��ʶ�������Ƿ��޸�,���²����󣬽���ֵ����Ϊ0
protected:
	void DeleteAllCalcShapes();//ɾ��������������������ļ��϶���,�ö���������е���״��m_oShapes��m_oLines�У���ֹ�ظ�ɾ��
	BOOL CreateAllShapesLines();//��ȡȫ��Shape��Line������������Ӧ��Ա����������
	BOOL CreateAllPropertys(); //������������,Shapes��������״�����ԣ��ݲ�����line
// 	BOOL AttachAllShapeLineInOut();//����������״�����롢����ڵ�
// 	BOOL AttachShapesInOut();//����Shapes�����е����롢����ڵ�
	BOOL AttachLinesInOut();//����Lines�����е����롢����ڵ�
	void InitOrigDataShapesPropertys();//��ʼ��ԭʼ����Shapes��Propertys����
	void AttachLineInOut(CVFlowShapeLine *pShapeLineData,const long &nBeginShapeID,const long &nEndShapeID);//�������������������������
	BOOL CreateCalcFlowShapes();//�����㷨�����õ�Shapes
	void CreateCalcFlowShapes(CVFlowShapes *pSrcCalcShapes);//�����㷨�����õ�Shapes
	void GetAllInShapes(CVFlowShapes *pSrcShapes,CVFlowShapes *pDstShapesRef);//��ȡȫ���������������Shape

	CVFlowShape m_oOrigDataPropertysRef;//ȫ����������������(����Ҫ���µ�ԭʼ��������)
	CVFlowShapes m_oOrigDataShapesRef;//ȫ������������ԭʼ���ݽڵ�(Ӧ��������ԭʼ���ݶ�Ӧ�ô�������·��)

	CVFlowShapes m_oShapes;//ȫ����Shape�ڵ�
	CVFlowShapeLines m_oLines;//ȫ����Line�ڵ�

private:
	CVisioReadWrite m_oVisioReadWrite;
};

