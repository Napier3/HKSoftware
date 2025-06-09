//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData.h  CTcpEdgePkgData

#pragma once

#include "TcpEdgePkgGlobal.h"

class CTcpEdgePkgData : public CExBaseList
{
public:
	CString m_arrayNotMust[64];//用以注册可以为否的报文字段
	QString m_strErrorInfo;	//报文错误
	QString m_strNecessityLack;//必需字段缺失
	QString m_strNecessityErr;//必需字段错误
	QString m_strRangeOut;//超限
	QString m_strReturnFalse;//执行失败返回错误报文

	CTcpEdgePkgData();
	virtual ~CTcpEdgePkgData();


//重载函数
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

	//判断日期是否合法,格式是否正确
	virtual QString CheckTimeFormat(CString strID, CString strNodeID, CString strTime);
	virtual QString CheckDateLegal(CString strID, CString strNodeID, long year, long month, long day, long nHour, long nMinute, long nSecond, long nMillisecond);

	//判断百分比类的参数格式和范围是否正确
	virtual QString CheckRangePer(CString strID, CString strNodeID, CString strNode);

};

