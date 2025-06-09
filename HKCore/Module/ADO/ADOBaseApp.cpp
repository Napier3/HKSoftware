// ADOBaseApp.cpp: implementation of the CADOBaseApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOBaseApp.h"
#include "VariantApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


////////////////CXDbRecordset///////////////////////////

CXDbRecordset::CXDbRecordset(void)
	:CXDbRecordsetBase()
{
	m_pRecordset = NULL;
}

CXDbRecordset::CXDbRecordset(ADODB::_RecordsetPtr pRecordset)
	:CXDbRecordsetBase()
{
	m_pRecordset = pRecordset;
}

CXDbRecordset::~CXDbRecordset()
{
	Free();
}

BOOL CXDbRecordset::Open(ADODB::_ConnectionPtr &pConnection, const CString &strSQL)
{
	Free();
	m_pRecordset.CreateInstance("ADODB.Recordset");
	BOOL bRet = TRUE;
	
	try
	{
		m_pRecordset->Open(_variant_t (strSQL), 
			pConnection.GetInterfacePtr( ), 
			ADODB::adOpenDynamic, 
			ADODB::adLockOptimistic,                                              
			ADODB::adCmdText);
	}
	catch(_com_error &e) 
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,  (LPCTSTR)e.Description());
		bRet = FALSE;
	}

	return bRet;
}

BOOL CXDbRecordset::GetFieldBaseValue(long nFieldIndex,_variant_t &vt)
{
	ASSERT(m_pRecordset);

	try
	{
		vt= m_pRecordset->GetCollect(nFieldIndex);
	}
	catch(_com_error &e) 
	{ 
		CString str = (LPCTSTR)e.Description();
		return FALSE; 
	} 

	return TRUE;
}

BOOL CXDbRecordset::GetFieldBaseValue(const CString &strID,_variant_t &vt)
{
	ASSERT(m_pRecordset);

	try
	{
		vt= m_pRecordset->GetCollect((_variant_t)strID);
	}
	catch(_com_error &e) 
	{ 
		CString str = (LPCTSTR)e.Description();
		return FALSE; 
	} 

	return TRUE;
}

//��ȡ��ǰ��¼ֵ
BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, CString &strValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	return VariantToCString(vt,strValue);
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, long &nValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	return VariantToLong(vt, nValue);
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, double &fValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	return VariantToDouble(vt, fValue);	
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, float &fValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	return VariantToFloat(vt, fValue);
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, DWORD &dwValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	return VariantToDWord(vt, dwValue);
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, __int64 &n64Value)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	return VariantToInt64(vt, n64Value);
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(nFieldIndex, vt))
	{
		return FALSE;
	}

	
	return VariantToSystemTime(vt, tmValue);
}

BOOL CXDbRecordset::GetFieldValue(long nFieldIndex, char **blobData, long &nLen)
{
// 	*blobData = Item(nFieldIndex);
// 	if(!(*blobData))
// 	{
// 		return FALSE;
// 	} 
//	nLen = nCurFieldDataLen;
	return TRUE;
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, CString &strValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToCString(vt,strValue);
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, long &nValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToLong(vt, nValue);
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, double &fValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToDouble(vt, fValue);	
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, float &fValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToFloat(vt, fValue);	
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, DWORD &dwValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToDWord(vt, dwValue);
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, __int64 &n64Value)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToInt64(vt, n64Value);
}

BOOL CXDbRecordset::GetFieldValue(const CString &strID, SYSTEMTIME &tmValue)
{
	_variant_t vt;

	if (!GetFieldBaseValue(strID, vt))
	{
		return FALSE;
	}

	return VariantToSystemTime(vt,tmValue);
}


BOOL CXDbRecordset::GetFieldValue(const CString &strID, char **blobData, long &nLen)
{
// 	*blobData = Item(strID);
// 	if(!(*blobData))
// 	{
// 		return FALSE;
// 	}
//	nLen = nCurFieldDataLen; 

	return TRUE;
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, CString &strValue)
{
	return GetFieldValue((const CString)strID,strValue);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, long &nValue)
{
	return GetFieldValue((const CString)strID,nValue);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, double &fValue)
{
	return GetFieldValue((const CString)strID,fValue);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, float &fValue)
{
	return GetFieldValue((const CString)strID,fValue);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, DWORD &dwValue)
{
	return GetFieldValue((const CString)strID,dwValue);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, __int64 &n64Value)
{
	return GetFieldValue((const CString)strID,n64Value);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, SYSTEMTIME &tmValue)
{
	return GetFieldValue((const CString)strID,tmValue);
}

BOOL CXDbRecordset::GetFieldValue(BSTR strID, char **blobData, long &nLen)
{
	return GetFieldValue((const CString)strID,blobData,nLen);
}

//���õ�ǰ��¼ֵ
void CXDbRecordset::SetFieldValue(long nFieldIndex, const CString &strValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect(nFieldIndex,(_variant_t)strValue);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, long &nValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect(nFieldIndex,nValue);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, double &fValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect(nFieldIndex,fValue);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, float &fValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect(nFieldIndex,fValue);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, DWORD &dwValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect(nFieldIndex,dwValue);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, __int64 &n64Value)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect(nFieldIndex,n64Value);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, SYSTEMTIME &tmValue)
{
	ASSERT(m_pRecordset);
	CString strValue;      
	strValue.Format(_T("%4d-%2d-%2d %2d:%2d:%2d")
		,tmValue.wYear,tmValue.wMonth,tmValue.wDay
		,tmValue.wHour,tmValue.wMinute,tmValue.wSecond);

	m_pRecordset->PutCollect(nFieldIndex,(_variant_t)strValue);
}

void CXDbRecordset::SetFieldValue(long nFieldIndex, char **blobData, long &nLen)
{

}


void CXDbRecordset::SetFieldValue(const CString &strID, const CString &strValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect((_variant_t)strID,(_variant_t)strValue);
}

void CXDbRecordset::SetFieldValue(const CString &strID, long &nValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect((_variant_t)strID,nValue);
}

void CXDbRecordset::SetFieldValue(const CString &strID, double &fValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect((_variant_t)strID,fValue);
}

void CXDbRecordset::SetFieldValue(const CString &strID, float &fValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect((_variant_t)strID,fValue);
}

void CXDbRecordset::SetFieldValue(const CString &strID, DWORD &dwValue)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect((_variant_t)strID,dwValue);
}

void CXDbRecordset::SetFieldValue(const CString &strID, __int64 &n64Value)
{
	ASSERT(m_pRecordset);
	m_pRecordset->PutCollect((_variant_t)strID,n64Value);
}

void CXDbRecordset::SetFieldValue(const CString &strID, SYSTEMTIME &tmValue)
{
	ASSERT(m_pRecordset);
	CString strValue;      
	strValue.Format(_T("%4d-%2d-%2d %2d:%2d:%2d")
		,tmValue.wYear,tmValue.wMonth,tmValue.wDay
		,tmValue.wHour,tmValue.wMinute,tmValue.wSecond);

	m_pRecordset->PutCollect((_variant_t)strID,(_variant_t)strValue);
}


void CXDbRecordset::SetFieldValue(const CString &strID, char **blobData, long &nLen)
{
// 	CXDbSQLFieldObject *pFind = (CXDbSQLFieldObject *)FindByID(strID);
// 
// 	if (pFind == NULL)
// 	{
// 		pFind = new CXDbSQLFieldObject(strID, nLen, *blobData);
// 		AddNewChild(pFind);
// 	}
// 	else
// 	{
// 		pFind->SetValue(nLen, *blobData);
// 	}
}

void CXDbRecordset::SetFieldValue(BSTR strID, const CString &strValue)
{
	SetFieldValue((const CString)strID, strValue);
}

void CXDbRecordset::SetFieldValue(BSTR strID, long &nValue)
{
	SetFieldValue((const CString)strID, nValue);
}

void CXDbRecordset::SetFieldValue(BSTR strID, double &fValue)
{
	SetFieldValue((const CString)strID, fValue);
}

void CXDbRecordset::SetFieldValue(BSTR strID, float &fValue)
{
	SetFieldValue((const CString)strID, fValue);
}

void CXDbRecordset::SetFieldValue(BSTR strID, DWORD &dwValue)
{
	SetFieldValue((const CString)strID, dwValue);
}

void CXDbRecordset::SetFieldValue(BSTR strID, __int64 &n64Value)
{
	SetFieldValue((const CString)strID, n64Value);
}

void CXDbRecordset::SetFieldValue(BSTR strID, SYSTEMTIME &tmValue)
{
	SetFieldValue((const CString)strID, tmValue);
}

void CXDbRecordset::SetFieldValue(BSTR strID, char **blobData, long &nLen)
{
	SetFieldValue((const CString)strID, blobData, nLen);
}

CXDbBaseLib* CXDbRecordset::GetXDbBaseLib()
{
	return NULL;/*m_pMySqlBaseApp*/;
}

// ��ȡ��ѯ���������	
long CXDbRecordset::GetQueryNumCols(void)	
{
	ASSERT(m_pRecordset);
	return m_pRecordset->GetFields()->Count;
}

// �ͷŲ�ѯ����ռ�
void CXDbRecordset::Free(void)
{
	if(m_pRecordset)
	{
		try
		{
			//�رռ�¼��
			m_pRecordset->Close();
		}
		catch(_com_error &e) 
		{ 
			CLogPrint::LogString(XLOGLEVEL_TRACE,  (LPCTSTR)e.Description());
		} 
	}

	m_pRecordset = NULL;
}

//���ü�¼���α�
void CXDbRecordset::MoveNext()
{
	ASSERT(m_pRecordset);

	if (!IsEof())
	{
		m_pRecordset->MoveNext();
	}
}

void CXDbRecordset::MovePrev()
{
	ASSERT(m_pRecordset);

	if(!IsBof())
	{
		m_pRecordset->MovePrevious();
	}
}

void CXDbRecordset::MoveFirst()
{
	ASSERT(m_pRecordset);

	m_pRecordset->MoveFirst();
}

void CXDbRecordset::MoveLast()
{
	ASSERT(m_pRecordset);

	m_pRecordset->MoveLast();
}

BOOL CXDbRecordset::IsBof()
{
	ASSERT(m_pRecordset);

	return m_pRecordset->adoBOF;
}

BOOL CXDbRecordset::IsEof()
{
	ASSERT(m_pRecordset);

	if (m_pRecordset == NULL)
	{
		return TRUE;
	}

	return m_pRecordset->adoEOF;
}

//ˢ�µ�ǰ��¼
BOOL CXDbRecordset::Update(BSTR bstrPrimaryKey, BOOL bInsert)
{
	ASSERT(m_pRecordset);

	m_pRecordset->Update();	
	return TRUE;
// 	CString strPK;
// 	strPK = bstrPrimaryKey;
// 	m_bPKAutoIncreaceFlg = InitPrimaryState(strPK);
// 
// 	if(bInsert)
// 	{
// 		return DB_Insert();
// 	}
// 	else
// 	{
// 		return DB_Update();
// 	}
}

//ˢ�¼�¼��
void CXDbRecordset::UpdateAll()
{
	ASSERT(m_pRecordset);

	m_pRecordset->Update(ADODB::adAffectAll);
}

void CXDbRecordset::AddNew()
{
	ASSERT(m_pRecordset);

	m_pRecordset->AddNew();
}

//ɾ����¼
void CXDbRecordset::Delete()
{
	ASSERT(m_pRecordset);

	m_pRecordset->Delete(ADODB::adAffectCurrent);///ɾ����ǰ��¼
}

//ɾ����¼
void CXDbRecordset::DeleteAll()
{
	MoveFirst();

	while(!IsEof())
	{
		Delete();
		MoveNext();///�Ƶ���һ����¼
	}
}

/////////////////////////////////////////////////////////////////////////


////////////////////////CADOBaseApp////////////////////////////////////////
CADOBaseApp * g_ptheADOApp;

CADOBaseApp::CADOBaseApp(void)
{
	g_ptheADOApp = this;
	m_pConnection = NULL;	
	m_bConnectStatus = FALSE;
}

CADOBaseApp::~CADOBaseApp(void)
{
	DisconnectDB();
}

//�������ݿ�
BOOL CADOBaseApp::ConnectDB(CDBServerInfoBase &oDBServerInfo)
{
	if(! oDBServerInfo.IsValid_ADO())
	{
		return FALSE;
	}

	//�Ͽ�����
	DisconnectDB();

	CString strSql;
	strSql.Format(_T("DSN=%s;server=%s;database=%s"),
		oDBServerInfo.m_strDSN,
		oDBServerInfo.m_strHostIp,
		oDBServerInfo.m_strDbName);
	
	try
	{
		m_pConnection.CreateInstance(_T("ADODB.Connection"));
		m_pConnection->ConnectionTimeout = 5; 		//��������ʱ�� 
		//�����ݿ����� 
		HRESULT hr = m_pConnection->Open((_bstr_t)strSql,(_bstr_t)oDBServerInfo.m_strUserName,(_bstr_t)oDBServerInfo.m_strPasswd,ADODB::adModeUnknown); 
	}
	catch(_com_error &e) 
	{ 
		CLogPrint::LogString(XLOGLEVEL_TRACE,  (LPCTSTR)e.Description());
		m_pConnection = NULL;
		return FALSE; 
	} 

	m_bConnectStatus = TRUE;

	return TRUE;
}

//�Ͽ����ݿ�����
void CADOBaseApp::DisconnectDB(void)
{
	if(m_pConnection)
	{
		//�ر�����
		m_pConnection->Close( );              
		m_pConnection=NULL;
	}

	m_bConnectStatus = FALSE;
}

//ִ�в���
CXDbRecordsetBase* CADOBaseApp::ExecuteQuery(CString &strQuery)
{
	CXDbRecordset* pXDbRecordset = NULL;

	if (!m_bConnectStatus || strQuery.IsEmpty())
	{
		return NULL;
	}
	
	pXDbRecordset = new CXDbRecordset;

	if(!pXDbRecordset->Open(m_pConnection, strQuery))
	{
		delete pXDbRecordset;
		pXDbRecordset = NULL;
	}

	return pXDbRecordset;	
}

//ִ������
BOOL CADOBaseApp::ExecuteCmd(const CString &strCmd)
{
	if (!m_bConnectStatus || strCmd.IsEmpty())
	{
		return FALSE;
	}

	_variant_t varr; 

	try
	{
		m_pConnection->Execute((_bstr_t)strCmd,&varr, ADODB::adCmdText);
	}
	catch(_com_error &e) 
	{ 
		CLogPrint::LogString(XLOGLEVEL_TRACE,  (LPCTSTR)e.Description());
		return FALSE; 
	}
	
	return TRUE;
}

BOOL CADOBaseApp::DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,long lCondition)
{
	CString strSQL;
	strSQL.Format(_T("delete * from %s where %s=%d"),strTableName,strConditionName,lCondition);
	_bstr_t bstr(strSQL);
	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;///����Ϊ�޲���

	try
	{
		ADODB::_CommandPtr pCommand;
		pCommand.CreateInstance(__uuidof(ADODB::Command));
		pCommand->CommandText=bstr;
		pCommand->ActiveConnection = g_ptheADOApp->m_pConnection;///�ǳ��ؼ���һ�䣬�����������Ӹ�ֵ����
		pCommand->Execute(&vNULL,&vNULL,ADODB::adCmdText);
	}
	catch (_com_error &e)//�쳣����
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,  (LPCTSTR)e.Description());
	}

	return TRUE;
}

BOOL CADOBaseApp::DeleteDataFromDB(const CString &strTableName,const CString &strConditionName,const CString &strCondition)
{
	//�����ݿ�ɾ����������
	CString strSQL;
	strSQL.Format(_T("delete * from %s where %s=\'%s\'"),strTableName,strConditionName,strCondition);
	_bstr_t bstr(strSQL);
	_variant_t vNULL;
	vNULL.vt = VT_ERROR;
	vNULL.scode = DISP_E_PARAMNOTFOUND;///����Ϊ�޲���

	try
	{
		ADODB::_CommandPtr pCommand;
		pCommand.CreateInstance(__uuidof(ADODB::Command));
		pCommand->CommandText=bstr;
		pCommand->ActiveConnection = g_ptheADOApp->m_pConnection;///�ǳ��ؼ���һ�䣬�����������Ӹ�ֵ����
		pCommand->Execute(&vNULL,&vNULL,ADODB::adCmdText);
	}
	catch (_com_error &e)//�쳣����
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,  (LPCTSTR)e.Description());
	}

	return TRUE;
}


//#################  ###############################
//�����ݿ��ȡ����������ݵĺ���
BOOL ADO_GetChunk(ADODB::_RecordsetPtr pRecordset,CString strTableField,CString &strData)
{
	_variant_t vTable(strTableField);
	long lDataSize = pRecordset->GetFields()->GetItem(vTable)->ActualSize;

	if(lDataSize > 0) 
	{
		_variant_t varBLOB;
		varBLOB = pRecordset->GetFields()->GetItem(vTable)->GetChunk(lDataSize);
		if(varBLOB.vt == (VT_ARRAY | VT_UI1)) ///�ж����������Ƿ���ȷ
		{
			BSTR HUGEP *pbstr;
			SafeArrayAccessData(varBLOB.parray,(void **)&pbstr); 
			///�õ�ָ�����ݵ�ָ�� /*****���������ǿ��Զ�pBuf�е����ݽ��д���*****/
			strData = *pbstr;	
			SafeArrayUnaccessData (varBLOB.parray);
		}
		else
			strData="";
	} 
	else
		strData="";
	return TRUE;
}

//�����ݿ�д�����������
BOOL ADO_AppendChunk(ADODB::_RecordsetPtr pRecordset,CString strTableField,CString strData)
{
	_variant_t vTable(strTableField);
	char *pBuff=NULL;
	long lLength=strData.GetLength()+1;
	pBuff=new char [lLength+2];
	CString_to_char(strData, pBuff);
	VARIANT varBLOB;
	SAFEARRAY *psa; 
	SAFEARRAYBOUND rgsabound[1];

	char *p=pBuff;
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = lLength;
	psa = SafeArrayCreate(VT_UI1, 1,rgsabound);		///����SAFEARRAY����
	for(long i = 0; i < (long)lLength; i++)			
		SafeArrayPutElement (psa,&i,p++);			///��pBufָ��Ķ��������ݱ��浽SAFEARRAY����psa��
	varBLOB.vt = VT_ARRAY | VT_UI1;					///��varBLOB����������ΪBYTE���͵�����
	varBLOB.parray = psa; 							///ΪvarBLOB������ֵ 
	pRecordset->GetFields()->GetItem(vTable)->AppendChunk(varBLOB); 	///����BLOB���͵�����

	delete pBuff;

	return TRUE;
}
