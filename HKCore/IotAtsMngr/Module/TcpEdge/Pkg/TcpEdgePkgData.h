//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData.h  CTcpEdgePkgData

#pragma once

#include "TcpEdgePkgGlobal.h"

class CTcpEdgePkgData : public CExBaseList
{
public:
	CString m_arrayNotMust[64];//����ע�����Ϊ��ı����ֶ�
	QString m_strErrorInfo;	//���Ĵ���
	QString m_strNecessityLack;//�����ֶ�ȱʧ
	QString m_strNecessityErr;//�����ֶδ���
	QString m_strRangeOut;//����
	QString m_strReturnFalse;//ִ��ʧ�ܷ��ش�����

	CTcpEdgePkgData();
	virtual ~CTcpEdgePkgData();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKGDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgDataKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgDataKey();     }

	static CDvmData* AddNewData(CDvmDataset* pDataset, const CString &strID, DWORD dwMust = 1, CString strNote = "");
	static void AddNewData(CDvmDataset* pDataset, CDvmDataset* pObject, DWORD dwMust = 1);
	static void AddNewDatas(CDvmDataset* pDataset, const CString &strID, DWORD dwMust = 1);
	static void AddNewDatas(CDvmDataset* pDataset, CDvmDataset* pObject, const CString &strID, DWORD dwMust = 1);
	static void SetDataFormat(CDvmData* pData, CString strFormat, long nParams = 0, ...);

public:
	virtual CDvmDataset* ToDataset();
	virtual BOOL NewData(CDvmDatasetGroup* pArray);

	//virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal);

	static CTcpEdgePkgData* GetPrcdrDataByID(const CString& strPrcdrID);

	//�ж������Ƿ�Ϸ�,��ʽ�Ƿ���ȷ
	virtual QString CheckTimeFormat(CString strID, CString strNodeID, CString strTime);
	virtual QString CheckDateLegal(CString strID, CString strNodeID, long year, long month, long day, long nHour, long nMinute, long nSecond, long nMillisecond);

	//�жϰٷֱ���Ĳ�����ʽ�ͷ�Χ�Ƿ���ȷ
	virtual QString CheckRangePer(CString strID, CString strNodeID, CString strNode);

};

