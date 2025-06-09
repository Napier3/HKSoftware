//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttChMaps.cpp  CSttChMaps


#include "stdafx.h"
#include "SttChMaps.h"
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"
#include "../SttTest/Common/tmt_test_paras_head.h"
#include "../XLangResource_Native.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttChMaps::CSttChMaps()
{
	//��ʼ������

	//��ʼ����Ա����

	//20240923 huangliang �������뿪����Ĭ��ֵ�����ö�����ʱ�������ڹ��캯���д���Ĭ��ֵ
//	CreateDefaultBinBoutMaps();
}

CSttChMaps::~CSttChMaps()
{
}

long CSttChMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttChMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	//20240919 huangliang ����ʱ��Ҫ�ѿ��뿪�����浽xml��
	CExBaseList olistBinary;	
	CreateBinToList(&olistBinary);
	CreateBinExToList(&olistBinary);
	CreateBoutToList(&olistBinary);
	CreateBoutExToList(&olistBinary);
	olistBinary.XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CSttChMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CSttChMaps::InitAfterRead()
{
	//20240919 huangliang �ֱ��¼ģ���������롢����
	int iBinIndex = 0, iBinExIndex = 0, iBoutIndex = 0, iBoutExIndex = 0;
	POS pos = GetHeadPosition();
	CSttChMap *pChMap = NULL;
	while (pos != NULL)
	{
		pChMap = (CSttChMap *)GetNext(pos);	
		CString sID = pChMap->m_strID;
		CString sName = pChMap->m_strName;
		if (sID.Find(MAPS_BINARY_ID_BINEX) != -1)
		{
			m_szBinExDesc[iBinExIndex] = sName;
			iBinExIndex++;
		}
		else if (sID.Find(MAPS_BINARY_ID_BIN) != -1)
		{
			m_szBinDesc[iBinIndex] = sName;
			iBinIndex++;
		}
		else if (sID.Find(MAPS_BINARY_ID_BOUTEX) != -1)
		{
			m_szBoutExDesc[iBoutExIndex] = sName;
			iBoutExIndex++;
		}
		else if (sID.Find(MAPS_BINARY_ID_BOUT) != -1)
		{
			m_szBoutDesc[iBoutIndex] = sName;
			iBoutIndex++;
		}
	}

	//ɾ�������еĿ��뿪��
	ClearBinBoutMaps();
}

BOOL CSttChMaps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttChMaps *p = (CSttChMaps*)pObj;

	return TRUE;
}

BOOL CSttChMaps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttChMaps *p = (CSttChMaps*)pDest;

	//20240919 huangliang ���뿪��Ҳ��Ҫ����
	CopyBinBout(p);

	return TRUE;
}

CBaseObject* CSttChMaps::Clone()
{
	CSttChMaps *p = new CSttChMaps();
	Copy(p);
	return p;
}

CBaseObject* CSttChMaps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttChMaps *p = new CSttChMaps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttChMaps::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTCHMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttChMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttChMapKey)
	{
		pNew = new CSttChMap();
	}

	return pNew;
}

CExBaseObject* CSttChMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTCHMAP)
	{
		pNew = new CSttChMap();
	}

	return pNew;
}


CSttChMap* CSttChMaps::FindByHdCh(long nType, const CString &strChID)
{
	char *pszType = stt_get_module_id_by_type(nType);
	CString strType;
	strType = pszType;

	return FindByHdCh(strType, strChID);
}

CSttChMap* CSttChMaps::FindByHdCh(const CString &strType, const CString &strChID)
{
	POS pos = GetHeadPosition();
	CSttChMap *pChMap = NULL;
	CSttChMap *pChMapFind = NULL;
	CSttHdCh *pHdCh = NULL;

	while (pos != NULL)
	{
		pChMap = (CSttChMap *)GetNext(pos);

		if (pChMap->HasHdCh(strType, strChID))
		{
			pChMapFind = pChMap;
			break;
		}
	}

	return pChMapFind;
}

CSttChMap* CSttChMaps::FindByHdCh(const CString &strType, const CString &strChID,float &fHdChCoef)
{
	POS pos = GetHeadPosition();
	CSttChMap *pChMap = NULL;
	CSttChMap *pChMapFind = NULL;
	CSttHdCh *pHdCh = NULL;

	while (pos != NULL)
	{
		pChMap = (CSttChMap *)GetNext(pos);
		pHdCh = pChMap->FindHdCh(strType, strChID);

		if (pHdCh != NULL)
		{
			pChMapFind = pChMap;
			fHdChCoef = pHdCh->m_fCoef;
			break;
		}
	}

	return pChMapFind;
}

CSttChMap* CSttChMaps::GetChMap(const CString &strSoftRsID)
{
	CSttChMap* pChild = (CSttChMap*)FindByID(strSoftRsID);
	return pChild;
}

CSttChMap* CSttChMaps::AddChMap(const CString &strSoftRsName,const CString &strSoftRsID)
{
	CSttChMap* pChild = new CSttChMap;
	pChild->m_strName = strSoftRsName;
	pChild->m_strAlias = strSoftRsName;
	pChild->m_strID = strSoftRsID;
	pChild->GetRsIndexFromID();
	AddNewChild(pChild);
	return pChild;
}

CSttChMap* CSttChMaps::AddChMap_FindByID(const CString &strSoftRsName,const CString &strSoftRsID)
{
	CSttChMap* pChild = (CSttChMap*)FindByID(strSoftRsID);

	if (pChild == NULL)
	{
		pChild = new CSttChMap;
		AddNewChild(pChild);
	}

	pChild->m_strName = strSoftRsName;
	pChild->m_strAlias = strSoftRsName;
	pChild->m_strID = strSoftRsID;
	pChild->GetRsIndexFromID();
	return pChild;
}

void CSttChMaps::SetChCountU(long nChNum)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nChIndex = 0;
	CString strTmp;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.GetAt(0) == 'U')
		{
			strTmp = pSttChMap->m_strID.Mid(1);
			nChIndex = CString_To_long(strTmp);

			if (nChIndex>nChNum)
			{
				Delete(pSttChMap);
			}
		}
	}
}

void CSttChMaps::SetChCountI(long nChNum)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nChIndex = 0;
	CString strTmp;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.GetAt(0) == 'I')
		{
			strTmp = pSttChMap->m_strID.Mid(1);
			nChIndex = CString_To_long(strTmp);

			if (nChIndex>nChNum)
			{
				Delete(pSttChMap);
			}
		}
	}
}

BOOL CSttChMaps::OpenChMapsFile(const CString &strChMapsPath)
{
	DeleteAll();
	return OpenXmlFile(strChMapsPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

BOOL CSttChMaps::SaveChMapsFile(const CString &strChMapsPath)
{
	return SaveXmlFile(strChMapsPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

// 20250311 suyang add   ��������ͨ��ӳ���ļ�
void CSttChMaps::SaveSyncChMapsFile(const CString &strChMapsPath)
{
	CString str6u6iFile,str4u3iFile;	

	//��չ���滻
	str4u3iFile = ChangeFilePostfix(strChMapsPath,"4u3i");
	str6u6iFile = ChangeFilePostfix(strChMapsPath,"6u6i");

	CSttChMaps *o4u3iChDatas = new CSttChMaps();
	CSttChMaps *o6u6iChDatas = new CSttChMaps();
	CSttChMaps *oChMaps = new CSttChMaps();//������ʱ�����洢���ݣ��������ҪDeleteAll
	
	CSttChMap *oChMapData = NULL,*oChMap2 = NULL;

	if (IsFileExist(str4u3iFile))//�жϸ��ļ��Ƿ����
	{
		o4u3iChDatas->OpenXmlFile(str4u3iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);//��4U3Iͨ��ӳ���ļ�
	}

	if(IsFileExist(str6u6iFile))
	{
		o6u6iChDatas->OpenXmlFile(str6u6iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);//��6U6Iͨ��ӳ���ļ�
	}

	POS pos = o4u3iChDatas->GetHeadPosition();
	while(pos)
	{
		oChMapData = (CSttChMap *)o4u3iChDatas->GetNext(pos);//������ǰsync�ļ��е�ͨ�����ݣ�����4U3I��ID

		if (oChMapData != NULL)
		{
			oChMap2 =(CSttChMap *) FindByID(oChMapData->m_strID);//����4u3i��ͨ���뵱ǰͨ�������Ƿ����

			//������ֵ��sync����,sync�ļ������ݱ�4u3i�٣�ֱ�Ӹ�ֵ�ͺ���
			if (oChMap2 != NULL)
			{
				/*ΪʲôҪ��¡��oChMap2�Ǵӵ�ǰ��������ȡ��������ӵ�oChMaps���棬���oChMaps��DeleteAll����ʱ��ǰ���ݵĽ���Ѿ������ı�;
				*����һ����new��������ʱ�����ṹҲ�ᷢ���ı䣬�Ӷ���deleteʱ���±���
				*/
				oChMapData =(CSttChMap *) oChMap2->Clone();
				//���ݴ��ڣ�����ӵ���ʱ������
				oChMaps->AddNewChild(oChMapData);
			}
			else
			{
				//û���ڵ�ǰͨ�������в�ѯ����Ӧ����֮ǰ����
				oChMaps->AddNewChild((CExBaseObject *)oChMapData->Clone());
				
			}
			
		}
	}

	oChMaps->Copy(o4u3iChDatas);

	oChMaps->RemoveAll();

	POS pos2 = o6u6iChDatas->GetHeadPosition();

	while(pos2)
	{
		oChMapData = (CSttChMap *)o6u6iChDatas->GetNext(pos2);

		if (oChMapData != NULL)
		{
			oChMap2 = (CSttChMap *)FindByID(oChMapData->m_strID);//����4u3i��ͨ���뵱ǰͨ�������Ƿ����

			//ֱ�ӽ�sync�����ݴ��ڵĸ�ֵ��6u6i��ȷʵ��new
			if (oChMap2 != NULL)
			{
				oChMapData = (CSttChMap *)oChMap2->Clone();//
				oChMaps->AddNewChild(oChMapData);
			}
			else
			{
				//û���ڵ�ǰͨ�������в�ѯ����Ӧ����֮ǰ����
				oChMaps->AddNewChild((CExBaseObject *)oChMapData->Clone());
			}	

		}
	}

	oChMaps->Copy(o6u6iChDatas);

	o4u3iChDatas->SaveXmlFile(str4u3iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	o6u6iChDatas->SaveXmlFile(str6u6iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);


	oChMaps->DeleteAll();
	o4u3iChDatas->DeleteAll();
	o6u6iChDatas->DeleteAll();
}

void CSttChMaps::Save4U3IChMapsFile(const CString &strChMapsPath)
{
	CString str6u6iFile,strFileName;

	strFileName = ChangeFilePostfix(strChMapsPath,"sync");
	str6u6iFile = ChangeFilePostfix(strChMapsPath,"6u6i");

	CSttChMaps *oSyncChData = new CSttChMaps();
	CSttChMaps *o6u6iChDatas = new CSttChMaps();
	CSttChMaps *oChMaps = new CSttChMaps();

	if (IsFileExist(strFileName))//�жϸ��ļ��Ƿ����
	{
		oSyncChData->OpenXmlFile(strFileName,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	}
	if (IsFileExist(str6u6iFile))//�жϸ��ļ��Ƿ����
	{
		o6u6iChDatas->OpenXmlFile(str6u6iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	}
	
	POS pos = oSyncChData->GetHeadPosition();

	CSttChMap *oChMapData = NULL,*oChMap2 = NULL;

	while(pos)
	{
		oChMapData = (CSttChMap *)oSyncChData->GetNext(pos);//����sync�е�ͨ��
		
		if (oChMapData != NULL)
		{
			oChMap2 =(CSttChMap *) FindByID(oChMapData->m_strID);//����sync��ͨ���뵱ǰͨ�������Ƿ����

			//������ֵ��sync����,sync�ļ������ݱ�4u3i�٣�ֱ�Ӹ�ֵ�ͺ���
			if (oChMap2 != NULL)
			{
				oChMapData = (CSttChMap *) oChMap2->Clone();
				oChMaps->AddNewChild(oChMapData);
			}
			else
			{
				//û���ڵ�ǰͨ�������в�ѯ����Ӧ����֮ǰ����
				oChMaps->AddNewChild((CExBaseObject *)oChMapData->Clone());
			}
		}
	}
	
	oChMaps->Copy(oSyncChData);

	oChMaps->RemoveAll();

	POS pos2 = o6u6iChDatas->GetHeadPosition();

	while(pos2)
	{
		oChMapData = (CSttChMap *)o6u6iChDatas->GetNext(pos2);

		if (oChMapData != NULL)
		{
			oChMap2 = (CSttChMap *)FindByID(oChMapData->m_strID);//����4u3i��ͨ���뵱ǰͨ�������Ƿ����

			//ֱ�ӽ�4u3i�����ݴ��ڵĸ�ֵ��6u6i��ȷʵ��new
			if (oChMap2 != NULL)
			{
				oChMapData = (CSttChMap *) oChMap2->Clone();
				oChMaps->AddNewChild(oChMapData);
			}
			else
			{
				//û���ڵ�ǰͨ�������в�ѯ����Ӧ����֮ǰ����
				oChMaps->AddNewChild((CExBaseObject *)oChMapData->Clone());
			}
			
		}
	}

	oChMaps->Copy(o6u6iChDatas);

	oSyncChData->SaveXmlFile(strFileName,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	o6u6iChDatas->SaveXmlFile(str6u6iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oChMaps->DeleteAll();
	oSyncChData->DeleteAll();
	o6u6iChDatas->DeleteAll();

}

void CSttChMaps::Save6U6IChMapsFile(const CString &strChMapsPath)
{
	CString str4u3iFile,strFileName;

	strFileName = ChangeFilePostfix(strChMapsPath,"sync");
	str4u3iFile = ChangeFilePostfix(strChMapsPath,"4u3i");

	CSttChMaps *oSyncChData = new CSttChMaps();
	CSttChMaps *o4u3iChDatas = new CSttChMaps();
	CSttChMaps *oChMaps = new CSttChMaps();

	if (IsFileExist(strFileName))//�жϸ��ļ��Ƿ����
	{
		oSyncChData->OpenXmlFile(strFileName,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	}

	if (IsFileExist(str4u3iFile))//�жϸ��ļ��Ƿ����
	{
		o4u3iChDatas->OpenXmlFile(str4u3iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	}

	POS pos = oSyncChData->GetHeadPosition();


	CSttChMap *oChMapData = NULL,*oChMap2 = NULL;
	while(pos)
	{
		oChMapData = (CSttChMap *)oSyncChData->GetNext(pos);//����sync�е�ͨ��

		if (oChMapData != NULL)
		{
			oChMap2 =(CSttChMap *) FindByID(oChMapData->m_strID);//����sync��ͨ���뵱ǰͨ�������Ƿ����

			//������ֵ��sync����,sync�ļ������ݱ�6u6i�٣�ֱ�Ӹ�ֵ�ͺ���
			if (oChMap2 != NULL)
			{
				oChMapData =(CSttChMap *) oChMap2->Clone();
				oChMaps->AddNewChild(oChMapData);
			}
			else
			{
				//û���ڵ�ǰͨ�������в�ѯ����Ӧ����֮ǰ����
				oChMaps->AddNewChild((CExBaseObject *)oChMapData->Clone());
			}
		}
	}

	oChMaps->Copy(oSyncChData);

	oChMaps->RemoveAll();


	POS pos2 = o4u3iChDatas->GetHeadPosition();

	while(pos2)
	{
		oChMapData = (CSttChMap *)o4u3iChDatas->GetNext(pos2);

		if (oChMapData != NULL)
		{
			oChMap2 = (CSttChMap *)FindByID(oChMapData->m_strID);//����4u3i��ͨ���뵱ǰͨ�������Ƿ����

			//ֱ�ӽ�6u6i�����ݴ��ڵĸ�ֵ��4u3i
			if (oChMap2 != NULL)
			{
				oChMapData =(CSttChMap *) oChMap2->Clone();
				oChMaps->AddNewChild(oChMapData);
			}
			else
			{
				//û���ڵ�ǰͨ�������в�ѯ����Ӧ����֮ǰ����
				oChMaps->AddNewChild((CExBaseObject *)oChMapData->Clone());
			}
		}
	}

	oChMaps->Copy(o4u3iChDatas);

	oSyncChData->SaveXmlFile(strFileName,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	o4u3iChDatas->SaveXmlFile(str4u3iFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oChMaps->DeleteAll();
	oSyncChData->DeleteAll();
	o4u3iChDatas->DeleteAll();

}

BOOL CSttChMaps::HasAnalogCurrModuleHdCh(long nModuleIndex)
{
	return Global_HasAnalogCurrModuleHdCh(this, nModuleIndex);
	// 	POS pos = GetHeadPosition();
	// 	CSttChMap *pSttChMap = NULL;
	// 	long nChIndex = 0;
	// 	CString strTmp;
	// 
	// 	while(pos)
	// 	{
	// 		pSttChMap = (CSttChMap *)GetNext(pos);
	// 
	// 		if (pSttChMap->m_strID.GetAt(0) == 'I')
	// 		{
	// 			if (pSttChMap->HasAnalogCurrModuleHdCh(nModuleIndex))
	// 			{
	// 				return TRUE;
	// 			}
	// 		}
	// 	}
	// 
	// 	return FALSE;
}

void CSttChMaps::SortByRsIndex()
{
	POS pos1 = GetHeadPosition();
	POS pos2 = pos1;
	CSttChMap *p1 = NULL, *p2 = NULL;
	BOOL bNeedChangePos = FALSE;

	while (pos1 != NULL)
	{
		p1 = (CSttChMap*)GetAt(pos1);
		pos2 = pos1;
		GetNext(pos2);//�ӵ�ǰͨ���������

		while (pos2 != NULL)
		{
			p2  = (CSttChMap*)GetAt(pos2);
			bNeedChangePos = FALSE;

			if (p1->m_strID.GetAt(0) == p2->m_strID.GetAt(0))//���ͨ��������ͬ
			{
				if (p1->m_nRsIndex > p2->m_nRsIndex)//��һ����RsIndex���ڵڶ���,����Ҫ����
				{
					bNeedChangePos = TRUE;
				}
			}
			else if (p1->IsCurrentCh())//��ͨ�����Ͳ�ͬ�������,���p1Ϊ����ͨ��,��Ҳ��Ҫ����λ��
			{
				bNeedChangePos = TRUE;
			}

			if (bNeedChangePos)//�����Ҫ����λ�ã������λ�ý���
			{
				SetAt(pos1, p2);
				SetAt(pos2, p1);
				p1 = p2;
			}

			GetNext(pos2);//�����ƶ�һ������֤��ǰ�����е�Moduleλ��Ϊ��С��
		}

		GetNext(pos1);
	}
}

BOOL CSttChMaps::HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek)
{
	CSttChMap *pSttChMap = NULL;
	CExBaseObject *pCurrObj = NULL;
	BOOL bHasFind = FALSE;
	POS pos = GetHeadPosition();

	while (pos)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
		{
			continue;
		}

		pSttChMap = (CSttChMap *)pCurrObj;

		if (pSttChMap->HasMapHdResource(nHasAnalog, nHasDigital, nHasWeek))
		{
			return TRUE;
		}
	}

	return FALSE;

	//	return Global_HasMapHdResource(this, nHasAnalog, nHasDigital, nHasWeek);
	// 	POS pos = GetHeadPosition();
	// 	CSttChMap *pSttChMap = NULL;
	// 	BOOL bHasFind = FALSE;
	// 
	// 	while(pos)
	// 	{
	// 		pSttChMap = (CSttChMap *)GetNext(pos);
	// 
	// 		if (pSttChMap->HasMapHdResource(nHasAnalog,nHasDigital,nHasWeek))
	// 		{
	// 			return TRUE;
	// 		}
	// 	}
	// 
	// 	return FALSE;
}

BOOL CSttChMaps::HasMapHdResource(const CString &strHdChsID)
{
	CSttChMap *pSttChMap = NULL;
	CExBaseObject *pCurrObj = NULL;
	BOOL bHasFind = FALSE;
	POS pos = GetHeadPosition();

	while (pos)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
	{
			continue;
		}

		pSttChMap = (CSttChMap *)pCurrObj;

		if (pSttChMap->HasMapHdResource(strHdChsID))
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSttChMaps::GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	BOOL bHasSet = FALSE;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->GetMaxValue_WeekRates(dMaxVol,dMaxCur))
		{
			bHasSet = TRUE;
		}
	}

	return bHasSet;
}

BOOL CSttChMaps::SetChMapsString(const CString &strChMaps)
{
	DeleteAll();
	return SetXml(strChMaps, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

long CSttChMaps::GetChNum(const CString &strChID)
{
	return Global_GetChNum(this, strChID);
	// 	POS pos = GetHeadPosition();
	// 	CSttChMap *pSttChMap = NULL;
	// 	long nNum = 0;
	// 
	// 	while(pos)
	// 	{
	// 		pSttChMap = (CSttChMap *)GetNext(pos);
	// 
	// 		if (pSttChMap->m_strID.Find(strChID) == 0)
	// 		{
	// 			nNum++;
	// 		}
	// 	}
	// 
	// 	return nNum;
}

void CSttChMaps::UpdateWeekRateValue()
{
	Global_UpdateWeekRateValue(this);
	// 	POS pos = GetHeadPosition();
	// 	CSttChMap *pSttChMap = NULL;
	// 
	// 	while(pos)
	// 	{
	// 		pSttChMap = (CSttChMap *)GetNext(pos);
	// 		pSttChMap->UpdateWeekRateValue();
	// 	}
}

void CSttChMaps::UpdateAliasByName()
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);
		pSttChMap->m_strAlias = pSttChMap->m_strName;
	}
}

//20240919 huangliang ����Ĭ��ֵ
void CSttChMaps::CreateDefaultBinBoutMaps()	
{
	CString sName, str;

	int i = 0;
	for (i = 0; i < MAPS_MAX_BINARYIN_COUNT; i++)
		{
		str.Format("%c", (char)(65 + i));
		sName = g_sLangTxt_InputValue.GetString()+ str;
		m_szBinDesc[i] = sName;
		//m_szBinDesc[i].Format("%c", (char)(65 + i));
		}
	for (i = 0; i < MAPS_MAX_ExBINARY_COUNT; i++)
	{
		m_szBinExDesc[i].Format("%s%d", MAPS_BINARY_ID_BINEX, i + 1);
	}
	for (i = 0; i < MAPS_MAX_BINARYOUT_COUNT; i++)
	{
		str.Format(_T("%d"), i + 1);
		sName = g_sLangTxt_OutputValue.GetString() + str;

		m_szBoutDesc[i] = sName;
		//m_szBoutDesc[i].Format("%d", i + 1);
	}
	for (i = 0; i < MAPS_MAX_ExBINARY_COUNT; i++)
	{
		m_szBoutExDesc[i].Format("%s%d", MAPS_BINARY_ID_BOUTEX, i + 1);
	}
}

//20240904 huangliang ɾ������������������
void CSttChMaps::ClearBinBoutMaps()	
{
	POS pos = GetHeadPosition();
	CSttChMap *pChMap = NULL;
	while (pos != NULL)
	{
		pChMap = (CSttChMap *)GetNext(pos);
		CString sID = pChMap->m_strID;
		if (sID.Find(MAPS_BINARY_ID_BINEX) != -1)
		{
			this->Delete(pChMap);
		}
		else if (sID.Find(MAPS_BINARY_ID_BIN) != -1)
		{
			this->Delete(pChMap);
		}
		else if (sID.Find(MAPS_BINARY_ID_BOUTEX) != -1)
		{
			this->Delete(pChMap);
		}
		else if (sID.Find(MAPS_BINARY_ID_BOUT) != -1)
		{
			this->Delete(pChMap);
		}
	}
}

//20240919 huangliang ȡ�����뿪��������
CString CSttChMaps::GetBinBoutNameForIndex(int iBin, int nIndex)	
{
	if (nIndex < 0)
		return "";
	switch (iBin)
	{
	case MAPS_BINARY_TYPE_BIN:
		if (nIndex >= MAPS_MAX_BINARYIN_COUNT)
			return "";
		return m_szBinDesc[nIndex];
	case MAPS_BINARY_TYPE_EXBIN:
		if (nIndex >= MAPS_MAX_ExBINARY_COUNT)
			return "";
		return m_szBinExDesc[nIndex];
	case MAPS_BINARY_TYPE_BOUT:
		if (nIndex >= MAPS_MAX_BINARYOUT_COUNT)
			return "";
		return m_szBoutDesc[nIndex];
	case MAPS_BINARY_TYPE_EXBOUT:
		if (nIndex >= MAPS_MAX_ExBINARY_COUNT)
			return "";
		return m_szBoutExDesc[nIndex];
	}
	return "";
}

//20240904 huangliang �������뿪��
void CSttChMaps::CopyBinBout(CBaseObject* pDest)
{
	CSttChMaps *p = (CSttChMaps*)pDest;

	int i = 0;
	for (i = 0; i < MAPS_MAX_BINARYIN_COUNT; i++)
	{
		p->m_szBinDesc[i] = m_szBinDesc[i];
	}
	for (i = 0; i < MAPS_MAX_ExBINARY_COUNT; i++)
	{
		p->m_szBinExDesc[i] = m_szBinExDesc[i];
	}
	for (i = 0; i < MAPS_MAX_BINARYOUT_COUNT; i++)
	{
		p->m_szBoutDesc[i] = m_szBoutDesc[i];
	}
	for (i = 0; i < MAPS_MAX_ExBINARY_COUNT; i++)
	{
		p->m_szBoutExDesc[i] = m_szBoutExDesc[i];
	}
}
void CSttChMaps::CreateBinToList(CExBaseList *plistBin)
{
	CString strID;
	int i = 0;
	for (i = 0; i < g_nBinCount; i++)
	{
		strID.Format("%s%d", MAPS_BINARY_ID_BIN, i + 1);
		CSttChMap *pBinMap = new CSttChMap();
		pBinMap->m_strID = strID;
		pBinMap->m_strName = m_szBinDesc[i];
		pBinMap->m_strAlias = pBinMap->m_strName;
		plistBin->AddTail(pBinMap);
	}
}
void CSttChMaps::CreateBinExToList(CExBaseList *plistBin)
{
	CString strID;
	int i = 0;
	for (i = 0; i < g_nBinExCount; i++)
	{
		strID.Format("%s%d", MAPS_BINARY_ID_BINEX, i + 1);
		CSttChMap *pBinMap = new CSttChMap();
		pBinMap->m_strID = strID;
		pBinMap->m_strName = m_szBinExDesc[i];
		pBinMap->m_strAlias = pBinMap->m_strName;
		plistBin->AddTail(pBinMap);
	}
}
void CSttChMaps::CreateBoutToList(CExBaseList *plistBout)
{
	CString strID;
	int i = 0;
	for (i = 0; i < g_nBoutCount; i++)
	{
		strID.Format("%s%d", MAPS_BINARY_ID_BOUT, i + 1);
		CSttChMap *pBinMap = new CSttChMap();
		pBinMap->m_strID = strID;
		pBinMap->m_strName = m_szBoutDesc[i];
		pBinMap->m_strAlias = pBinMap->m_strName;
		plistBout->AddTail(pBinMap);
	}
}
void CSttChMaps::CreateBoutExToList(CExBaseList *plistBout)
{
	CString strID;
	int i = 0;
	for (i = 0; i < g_nBoutExCount; i++)
	{
		strID.Format("%s%d", MAPS_BINARY_ID_BOUTEX, i + 1);
		CSttChMap *pBinMap = new CSttChMap();
		pBinMap->m_strID = strID;
		pBinMap->m_strName = m_szBoutExDesc[i];
		pBinMap->m_strAlias = pBinMap->m_strName;
		plistBout->AddTail(pBinMap);
	}
}

void CSttChMaps::ReadListToBin(CExBaseList *plistBin)
{
	if (plistBin == NULL)
		return;

	int i = 0;
	for (i = 0; i < MAPS_MAX_BINARYIN_COUNT; i++)
	{
		CSttChMap *pBinMap = (CSttChMap *)plistBin->GetAtIndex(i);
		if (pBinMap == NULL)
			break;
		m_szBinDesc[i] = pBinMap->m_strName;
	}
}
void CSttChMaps::ReadListToBinEx(CExBaseList *plistBin)
{
	if (plistBin == NULL)
		return;

	int i = 0;
	for (i = 0; i < MAPS_MAX_ExBINARY_COUNT; i++)
		{
		CSttChMap *pBinMap = (CSttChMap *)plistBin->GetAtIndex(i);
		if (pBinMap == NULL)
			break;
		m_szBinExDesc[i] = pBinMap->m_strName;
		}
}
void CSttChMaps::ReadListToBout(CExBaseList *plistBout)
{
	if (plistBout == NULL)
		return;

	int i = 0;
	for (i = 0; i < MAPS_MAX_BINARYOUT_COUNT; i++)
	{
		CSttChMap *pBoutMap = (CSttChMap *)plistBout->GetAtIndex(i);
		if (pBoutMap == NULL)
			break;
		m_szBoutDesc[i] = pBoutMap->m_strName;
	}
}
void CSttChMaps::ReadListToBoutEx(CExBaseList *plistBout)
{
	if (plistBout == NULL)
		return;

	int i = 0;
	for (i = 0; i < MAPS_MAX_ExBINARY_COUNT; i++)
	{
		CSttChMap *pBoutMap = (CSttChMap *)plistBout->GetAtIndex(i);
		if (pBoutMap == NULL)
			break;
		m_szBoutExDesc[i] = pBoutMap->m_strName;
	}
}

void Global_UpdateWeekRateValue(CExBaseList *pAnalogChMapList)
{
	if (pAnalogChMapList == NULL)
	{
		return;
	}

	POS pos = pAnalogChMapList->GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	CExBaseObject *pCurrObj = NULL;

	while (pos)
	{
		pCurrObj = pAnalogChMapList->GetNext(pos);

		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
	{
			continue;
		}

		pSttChMap = (CSttChMap *)pCurrObj;
		pSttChMap->UpdateWeekRateValue();
	}
}

//BOOL Global_HasMapHdResource(CExBaseList *pAnalogChMapList, long nHasAnalog, long nHasDigital, long nHasWeek)
//{
//	if (pAnalogChMapList == NULL)
//	{
//		return FALSE;
//	}
//
//	POS pos = pAnalogChMapList->GetHeadPosition();
//	CSttChMap *pSttChMap = NULL;
//	CExBaseObject *pCurrObj = NULL;
//	BOOL bHasFind = FALSE;
//
//	while (pos)
//	{
//		pCurrObj = pAnalogChMapList->GetNext(pos);
//
//		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
//		{
//			continue;
//		}
//
//		pSttChMap = (CSttChMap *)pCurrObj;
//
//		if (pSttChMap->HasMapHdResource(nHasAnalog, nHasDigital, nHasWeek))
//		{
//			return TRUE;
//		}
//	}
//
//	return FALSE;
//}

BOOL Global_GetMaxValue_WeekRates(CExBaseList *pAnalogChMapList, double &dMaxVol, double &dMaxCur)
{
	if (pAnalogChMapList == NULL)
	{
		return FALSE;
	}

	POS pos = pAnalogChMapList->GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	CExBaseObject *pCurrObj = NULL;
	BOOL bHasSet = FALSE;

	while (pos)
	{
		pCurrObj = pAnalogChMapList->GetNext(pos);

		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
		{
			continue;
		}

		pSttChMap = (CSttChMap *)pCurrObj;
		//		pSttChMap = (CSttChMap *)pAnalogChMapList->GetNext(pos);

		if (pSttChMap->GetMaxValue_WeekRates(dMaxVol, dMaxCur))
		{
			bHasSet = TRUE;
		}
	}

	return bHasSet;
}

BOOL Global_HasAnalogCurrModuleHdCh(CExBaseList *pAnalogChMapList, long nModuleIndex)
{
	if (pAnalogChMapList == NULL)
	{
		return FALSE;
	}

	POS pos = pAnalogChMapList->GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	CExBaseObject *pCurrObj = NULL;
	long nChIndex = 0;
	CString strTmp;

	while (pos)
	{
		pCurrObj = pAnalogChMapList->GetNext(pos);

		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
		{
			continue;
	}

		pSttChMap = (CSttChMap *)pCurrObj;
		//		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.GetAt(0) == 'I')
		{
			if (pSttChMap->HasAnalogCurrModuleHdCh(nModuleIndex))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

long Global_GetChNum(CExBaseList *pAnalogChMapList, const CString &strChID)
{
	if (pAnalogChMapList == NULL)
	{
		return 0;
	}

	POS pos = pAnalogChMapList->GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	CExBaseObject *pCurrObj = NULL;
	long nNum = 0;

	while (pos)
	{
		pCurrObj = pAnalogChMapList->GetNext(pos);

		if (pCurrObj->GetClassID() != STTCMDCLASSID_CSTTCHMAP)
		{
			continue;
		}

		pSttChMap = (CSttChMap *)pCurrObj;
		//		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.Find(strChID) == 0)
	{
			nNum++;
		}
	}

	return nNum;
}