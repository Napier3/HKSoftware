#include "stdafx.h"
#include "TcpEdgePrcdr_File.h"
#include "TcpEdgeGlobalDef.h"
#include "TcpEdgeServer.h"
#include "TcpEdgeProtocol.h"
#include "Pkg/TcpEdgePkg.h"
#include "Pkg/TcpEdgePkgData_FileGet.h"
#include "Pkg/TcpEdgePkgData_FileGetResp.h"
#include "Pkg/TcpEdgePkgData_FileDataTrans.h"
#include "Pkg/TcpEdgePkgData_FileDataTransResp.h"
#include "Pkg/TcpEdgePkgData_FileSendResp.h"
#include "Pkg/TcpEdgePkgData_FileSend.h"
#include "Pkg/TcpEdgePkgData_DeviceGetLogResp.h"
#include "Pkg/TcpEdgePkgData_ContGetLogReq.h"
#include "Pkg/TcpEdgePkgData_DeviceGetLogReq.h"
#include "Pkg/TcpEdgePkgData_ContGetLogResp.h"
#include "Pkg/TcpEdgePkgData_AppGetLogReq.h"
#include "Pkg/TcpEdgePkgData_GetModel.h"
#include "Pkg/TcpEdgePkgData_GetTopoFile.h"
#include "Pkg/TcpEdgePkgData_GetMessage.h"
#include "Pkg/TcpEdgePkgData_AppGetCfgFileResp.h"
#include "Pkg/TcpEdgePkgData_AppSetCfgFileResp.h"
#include "Pkg/TcpEdgePkgData_AppSetCfgFileReq.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateResp.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateStatusReq.h"
#include "Pkg/TcpEdgePkgData_AppInstallResp.h"
#include "Pkg/TcpEdgePkgData_AppInstallStatusReq.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateStatusResp.h"
#include "Pkg/TcpEdgePkgData_AppInstallResult.h"
#include "Pkg/TcpEdgePkgData_AppInstallStatusResp.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateResult.h"
#include "Pkg/TcpEdgePkgData_AppGetLogResp.h"
#include "Pkg/TcpEdgePkgData_AppInstallReq.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateReq.h"
#include "../../../Module/API/Base64.h"
#include "../../../Module/API/GlobalConfigApi.h"

#include <QFileInfo>
#include <QDir>

//CRC32
unsigned long CRC32_Table[256] = {
	0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL,
	0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
	0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L,
	0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
	0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
	0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
	0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
	0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
	0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L,
	0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
	0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L,
	0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
	0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L,
	0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
	0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
	0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
	0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL,
	0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
	0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L,
	0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
	0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
	0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
	0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL,
	0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
	0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
	0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
	0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L,
	0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
	0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L,
	0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
	0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L,
	0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
	0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL,
	0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
	0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
	0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
	0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL,
	0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
	0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL,
	0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
	0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L,
	0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
	0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L,
	0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
	0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
	0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
	0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L,
	0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
	0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
	0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
	0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L,
	0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
	0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL,
	0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
	0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
	0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
	0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L,
	0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
	0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L,
	0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
	0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L,
	0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
	0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
	0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};

CTcpEdgePrcdr_File::CTcpEdgePrcdr_File()
{
	m_nFileSegNo = 1;
	m_nFileGetType = 0;
	m_bRecAppSetCfgFileResp = FALSE;
	m_nMaxFileSize = 0;
	m_nCurFileSize = 0;

}

CTcpEdgePrcdr_File::~CTcpEdgePrcdr_File()
{

}

long CTcpEdgePrcdr_File::GetFileSize(const CString& strFilePath)
{
	long nSize = 0;
	FILE *fp = NULL;
	fopen_s(&fp, strFilePath.GetString(), "r");
	if(fp == NULL)
	{
		return nSize;
	}
	fseek(fp, 0L, SEEK_END);
	nSize = ftell(fp);
	fclose(fp);
	return nSize;
}

BOOL CTcpEdgePrcdr_File::Base64ToFile(const CString& strFilePath, long& nFileLength)
{
	int nLen = 0;
	char* strBase64 = base64_decode(m_strBase64.GetString(), m_strBase64.GetLength(), nLen);

	FILE* fp = NULL;
	fopen_s(&fp, strFilePath.GetString(), "ab");
	if(!fp)
	{
		QString strLog = QString("从设备获取文件失败!").arg(m_strDeviceID);
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		return FALSE;
	}

	long nWrite = fwrite(strBase64, 1, nLen, fp);
	fclose(fp);
	nFileLength = nLen;
	return TRUE;
}

CString CTcpEdgePrcdr_File::FileToBase64(const CString& strFilePath)
{
	long nSize = GetFileSize(strFilePath);
	if(!nSize)
	{
		QString strLog = QString("向设备发送文件失败!");
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		return "";
	}

	FILE* fp = NULL;
	fopen_s(&fp, strFilePath.GetString(), "rb");
	BYTE* pBuffer = new BYTE[nSize];
	long nRead = fread(pBuffer, 1, nSize, fp);
	CString strBase64 = base64_encode((char*)pBuffer, nSize);
	fclose(fp);
	delete pBuffer;
	return strBase64;
}

BOOL CTcpEdgePrcdr_File::RunStepNull()
{
	//根据数据集、参数列表，拼报文发送
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
// 	if(m_strID.Find("Req") != -1
// 		|| m_strID == PkgData_FileGet)
// 	{
// 		pPkg->m_pPkgHead = ProduceHead(m_strID, PkgData_Value_CotReq);
// 	}
// 	else
// 	{
// 		pPkg->m_pPkgHead = ProduceHead(m_strID, PkgData_Value_CotResp);
// 	}
	pPkg->m_pPkgHead = ProduceHead(m_strID);
	pPkg->m_pPkgData = ProduceData(m_strID);
	if (m_strID == PkgData_AppInstallReq)
	{
		CTcpEdgePkgData_AppInstallReq* pAppInstallReq = (CTcpEdgePkgData_AppInstallReq*)pPkg->m_pPkgData;
		m_strJobId = pAppInstallReq->m_strJobId;
	}
	if (m_strID == PkgData_DeviceUpdateReq)
	{
		CTcpEdgePkgData_DeviceUpdateReq* pDeviceUpdateReq = (CTcpEdgePkgData_DeviceUpdateReq*)pPkg->m_pPkgData;
		m_strJobId = pDeviceUpdateReq->m_strJobId;
	}
	if(pPkg->m_pPkgData)
	{	
		if(pPkg->m_pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCFGFILEREQ)
		{
			//应用配置文件下装只有用户输入处可以获取下装文件信息
			CTcpEdgePkgData_AppSetCfgFileReq* pTemp = (CTcpEdgePkgData_AppSetCfgFileReq*)pPkg->m_pPkgData;
			m_strFilePath = pTemp->GetTcpEdgePkgFile()->m_strPath;
		}
		else if (pPkg->m_pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILEGET)
		{
			CTcpEdgePkgData_FileGet* pTemp = (CTcpEdgePkgData_FileGet*)pPkg->m_pPkgData;
			m_strFilePath = pTemp->m_strFullPathFileName;
			if(m_strFilePath.ReverseFind('\\') != -1)
			{
				m_strFileName = m_strFilePath.Mid(m_strFilePath.ReverseFind('\\') + 1);
			}
			else
			{
				m_strFileName = m_strFilePath.Mid(m_strFilePath.ReverseFind('/') + 1);
			}
		}

		QByteMap map;
		QByteMap mapASDU = Produce(pPkg, map);
		UpdateDataset(m_strID, mapASDU);
		Send(map, m_strID, m_nPort);
	}
	else
	{
		delete pPkg;
	}

	SetProcedureState(PrcdrState_Step_1);
	//重新设置超时
	ResetTimer();
	m_nOverTimeLong = 180000;//文件传输超时时间3分钟
	return FALSE;
}

void CTcpEdgePrcdr_File::SetFileGetType(const QString& strID)
{
	if(strID == "FileModelGet")
	{
		m_nFileGetType = 1;
	}
	else if(strID == "FileTopoGet")
	{
		m_nFileGetType = 2;
	}
	else if(strID == "FileMessageGet")
	{
		m_nFileGetType = 3;
	}
}

BOOL CTcpEdgePrcdr_File::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	if(pPkg->m_nPort == m_nPort)
	{
		BOOL bRet = FALSE;

		if((pPkgDetail->m_strCmdID == PkgData_FileGet && m_strID == PkgData_DeviceUpdateReq )
			|| (pPkgDetail->m_strCmdID == PkgData_FileDataTransResp && m_strID == PkgData_DeviceUpdateReq)    //设备升级
			|| (pPkgDetail->m_strCmdID == PkgData_FileGet && m_strID == PkgData_AppInstallReq )
			|| (pPkgDetail->m_strCmdID == PkgData_FileDataTransResp && m_strID == PkgData_AppInstallReq))     //应用安装
		{
			ProcessFileGetResp(pPkgDetail);
		}
		else if((pPkgDetail->m_strCmdID == PkgData_DeviceUpdateResp && m_strID == PkgData_DeviceUpdateReq)
			|| (pPkgDetail->m_strCmdID == PkgData_AppInstallResp && m_strID == PkgData_AppInstallReq))
		{
			QString strLog = QString("接收到应答消息[%1]...").arg(pPkgDetail->m_strCmdID);
			emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_PKG_RSLT);
		}
		else if((pPkgDetail->m_strCmdID == PkgData_DeviceUpdateResult && m_strID == PkgData_DeviceUpdateReq)//设备升级
			|| (pPkgDetail->m_strCmdID == PkgData_AppInstallResult && m_strID == PkgData_AppInstallReq) //应用安装
			|| (pPkgDetail->m_strCmdID == PkgData_DeviceUpdateStatusResp && m_strID == PkgData_DeviceUpdateStatusReq)//设备升级进度查询
			|| (pPkgDetail->m_strCmdID == PkgData_AppInstallStatusResp && m_strID == PkgData_AppInstallStatusReq))//应用安装进度查询       
		{
			//报文是查询回应,结束该过程
			ProcessPackageFinished(pPkgDetail);
			QString strLog = QString("[%1]测试结束...").arg(m_strID);
			emit sig_updateViewPkg(m_strIP, strLog, 0);
			return TRUE;
		}		
		//日志召回
		else if(m_strID == PkgData_DeviceGetLogReq
			|| m_strID == PkgData_ContGetLogReq
			|| m_strID == PkgData_AppGetLogReq)
		{
			if(pPkg->m_strCmdID == PkgData_DeviceGetLogResp)
			{
				bRet = ProcessDeviceGetLogReq(pPkgDetail);
			}
			else if(pPkg->m_strCmdID == PkgData_ContGetLogResp)
			{
				bRet = ProcessContGetLogReq(pPkgDetail);
			}
			else if(pPkg->m_strCmdID == PkgData_AppGetLogResp)
			{
				bRet = ProcessAppGetLogReq(pPkgDetail);
			}
			else if(pPkg->m_strCmdID == PkgData_FileGetResp
				|| pPkg->m_strCmdID == PkgData_FileDataTrans)
			{
				bRet = ProcessFileGet(pPkgDetail);
			}
		}
		else if (m_strID == PkgData_FileGet
			|| m_strID == PkgData_FileDataTrans)
		{
			bRet = ProcessFileGet(pPkgDetail);
		}
// 		else if (m_strID == PkgData_FileSend
// 			|| m_strID == PkgData_FileDataTransResp)
// 		{
// 			bRet = ProcessFileSend(pPkgDetail);
// 		}
		else if(m_strID == PkgData_AppGetCfgFileReq)
		{
			if(pPkg->m_strCmdID == PkgData_AppGetCfgFileResp)
			{
				bRet = ProcessAppGetCfgFileReq(pPkgDetail);
			}
			else if(pPkg->m_strCmdID == PkgData_FileGetResp
				|| pPkg->m_strCmdID == PkgData_FileDataTrans)
			{
				bRet = ProcessFileGet(pPkgDetail);
			}
		}
		else if((m_strID == PkgData_AppSetCfgFileReq && pPkg->m_strCmdID == PkgData_AppSetCfgFileResp))
		{
			m_bRecAppSetCfgFileResp = TRUE;
		}
		else if((pPkgDetail->m_strCmdID == PkgData_FileGet && m_strID == PkgData_AppSetCfgFileReq )
			|| (pPkgDetail->m_strCmdID == PkgData_FileDataTransResp && m_strID == PkgData_AppSetCfgFileReq))
		{
			//bRet = ProcessAppSetCfgFileReq(pPkgDetail);
			if(m_bRecAppSetCfgFileResp)
			{
				bRet = ProcessFileGetResp(pPkgDetail);
			}
		}
		else
		{
			//不属于该过程的报文
			return FALSE;
		}

		if(bRet)
		{
			ProcessPackageFinished(pPkgDetail);
			QString strLog = QString("[%1]测试结束...").arg(m_strID);
			emit sig_updateViewPkg(m_strIP, strLog, 0);
			if(m_nFileGetType == 1)
			{
				m_pTcpProtocolRef->OnModelFileGet(m_strFileName);
			}
			return TRUE;
		}

		pPkgDetail->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	}

	SetProcedureState(PrcdrState_Step_1);
	return FALSE;
}

BOOL CTcpEdgePrcdr_File::ProduceData_FileGetResp(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* tmpPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_FileGet* pFileGetData = (CTcpEdgePkgData_FileGet*)tmpPkg->m_pPkgData;

	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	CTcpEdgePkgHead* pHead = ProduceHead(PkgData_FileGetResp, PkgData_Value_CotReq);
	CTcpEdgePkgData_FileGetResp* pData = new CTcpEdgePkgData_FileGetResp;
	pData->m_strID = PkgData_Node_Data;
	pData->m_strCmdId = pFileGetData->m_strCmdId;
	m_strCmdId = pFileGetData->m_strCmdId;
	m_strFilePath = pFileGetData->m_strFullPathFileName;
	QFileInfo find(pFileGetData->m_strFullPathFileName);
	m_bFileFind = find.exists();

	if(m_bFileFind)
	{
		CFile tempFile;
		bool bRet;
		bRet = tempFile.Open(pFileGetData->m_strFullPathFileName, CFile::modeReadWrite);
		pData->m_strStatus = "0";	
		pData->m_strFileSize.Format(_T("%d"), find.size());
		QDateTime date = find.lastModified();
		pData->m_strModifyTime = date.toString("yyyy-MM-dd_hh:mm:ss");
		tempFile.Close();
		pData->m_strFileCrc = CRC32(pFileGetData->m_strFullPathFileName, find.size());
		
	}
	else
	{
		pData->m_strStatus = _T("1");
		pData->m_strErrorCode = _T("404");
		pData->m_strNote = _T("文件不存在, 文件获取失败");
	}

	pPkg->AddNewChild(pHead);
	pPkg->AddNewChild(pData);
	pPkg->m_pPkgHead = (CTcpEdgePkgHead*)pHead->CloneEx(TRUE, TRUE);
	pPkg->m_pPkgData = (CTcpEdgePkgData*)pData->CloneEx(TRUE, TRUE);

	//创建对应的Dataset以进行必需项目分析
	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = new CDvmDataset;

	CreateDataset(pHead);

	CDvmDataset* pDataDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_CmdId);
	pDvmData->m_strValue = pData->m_strCmdId;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_Status);
	pDvmData->m_strValue = pData->m_strStatus;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_ErrorCode);
	pDvmData->m_strValue = pData->m_strErrorCode;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_Note);
	pDvmData->m_strValue = pData->m_strNote;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_FileCrc);
	pDvmData->m_strValue = pData->m_strFileCrc;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_FileSize);
	pDvmData->m_strValue = pData->m_strFileSize;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_ModifyTime);
	pDvmData->m_strValue = pData->m_strModifyTime;
	m_pDvmDataset->AddNewChild(pDataDataset);
	long nRet = Send(pPkg, PkgData_FileGetResp, m_nPort);
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_FileGet);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_FileGet, m_strASDU);

	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;

	return nRet;
}

BOOL CTcpEdgePrcdr_File::ProcessFileGetResp(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	if(pPkg->m_strCmdID == PkgData_FileGet)
	{
		ProduceData_FileGetResp(pPkgDetail);
		if (m_bFileFind)
		{
			ProduceData_FileTransReq();
		}
		else
		{
			return FALSE;
		}
		
	}
	else if(pPkg->m_strCmdID == PkgData_FileDataTransResp)
	{
		CTcpEdgePkgData_FileDataTransResp* pData = (CTcpEdgePkgData_FileDataTransResp*)pPkg->m_pPkgData;
		if(pData->m_strStatus == "1")
		{
			//失败
			QString strLog = QString("向设备发送文件执行失败!");
			emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_ERR);
			return TRUE;
		}
		else
		{
			if(m_strContinue == "1")
			{
				ProduceData_FileTransReq();
			}
			else
			{
				QString strLog = QString("向设备发送文件成功...");
				emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_PKG_RSLT);
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CTcpEdgePrcdr_File::ProduceData_FileGet()
{
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	CTcpEdgePkgHead* pHead = ProduceHead(PkgData_FileGet, PkgData_Value_CotReq);
	CTcpEdgePkgData_FileGet* pData = new CTcpEdgePkgData_FileGet;
	pData->m_strCmdId = GetValueFromDataset(PkgData_Node_CmdId);
	pData->m_strFullPathFileName = GetValueFromDataset(PkgData_Node_FullPathFileName);
	pData->m_strStartByte = GetValueFromDataset(PkgData_Node_StartByte);
	if(!pData->m_strFullPathFileName.GetLength())
	{
		pData->m_strFullPathFileName = m_strFilePath;
		if(pData->m_strFullPathFileName.GetLength())
		{
			//并非用户主动发起,而是自动发起的文件召唤
			pData->m_strCmdId = "1000";
			pData->m_strStartByte = "1";

			//支持断点续传
			//文件传输
			CString strFilePath = GetDevice()->m_strRecvFilePath;
			QDir dirFile(strFilePath);
			if (!dirFile.exists())
			{
				dirFile.mkpath(strFilePath);
			}
			strFilePath += m_strFileName;
			QFileInfo find(strFilePath);
			if(find.exists())
			{
				QFile::remove(strFilePath);
			}
		}
	}

	pPkg->AddNewChild(pHead);
	pPkg->AddNewChild(pData);
	pPkg->m_pPkgHead = (CTcpEdgePkgHead*)pHead->CloneEx(TRUE, TRUE);
	pPkg->m_pPkgData = (CTcpEdgePkgData*)pData->CloneEx(TRUE, TRUE);

	//创建对应的Dataset以进行必需项目分析
	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = new CDvmDataset;

	CreateDataset(pHead);

	CDvmDataset* pDataDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_CmdId);
	pDvmData->m_strValue = pData->m_strCmdId;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_FullPathFileName);
	pDvmData->m_strValue = pData->m_strFullPathFileName;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_StartByte);
	pDvmData->m_strValue = pData->m_strStartByte;
	m_pDvmDataset->AddNewChild(pDataDataset);
	long nRet = Send(pPkg, PkgData_FileGet, m_nPort);
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_FileGet);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_FileGet, m_strASDU);
	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;
	 
	return nRet;
}

BOOL CTcpEdgePrcdr_File::ProduceData_FileTransResp(const CString& strCmdId, const CString& strFileSegNo,
												   CString strStatus, CString strErrorCode, CString strNote)
{
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	CTcpEdgePkgHead* pHead = ProduceHead(PkgData_FileDataTransResp, PkgData_Value_CotResp);
	CTcpEdgePkgData_FileDataTransResp* pData = new CTcpEdgePkgData_FileDataTransResp;
	pData->m_strCmdId = strCmdId;
	pData->m_strFileSegNo = strFileSegNo;
	pData->m_strStatus = strStatus;
	pData->m_strErrorCode = strErrorCode;
	pData->m_strNote = strNote;

	pPkg->AddNewChild(pHead);
	pPkg->AddNewChild(pData);
	pPkg->m_pPkgHead = (CTcpEdgePkgHead*)pHead->CloneEx(TRUE, TRUE);
	pPkg->m_pPkgData = (CTcpEdgePkgData*)pData->CloneEx(TRUE, TRUE);

	//创建对应的Dataset以进行必需项目分析
	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = new CDvmDataset;

	CreateDataset(pHead);

	CDvmDataset* pDataDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_CmdId);
	pDvmData->m_strValue = pData->m_strCmdId;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_FileSegNo);
	pDvmData->m_strValue = pData->m_strFileSegNo;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_Status);
	pDvmData->m_strValue = pData->m_strStatus;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_ErrorCode);
	pDvmData->m_strValue = pData->m_strErrorCode;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_Note);
	pDvmData->m_strValue = pData->m_strNote;
	m_pDvmDataset->AddNewChild(pDataDataset);
	long nRet = Send(pPkg, PkgData_FileDataTransResp, m_nPort);
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_FileGet);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_FileDataTransResp, m_strASDU);
	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;

	return nRet;
}

// BOOL CTcpEdgePrcdr_File::ProduceData_FileSend(SOCKET hSocket)
// {
// 	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
// 	pPkg->m_pPkgHead = ProduceHead(PkgData_FileSend, PkgData_Value_CotReq);
// 	CTcpEdgePkgData_FileSend* pData = new CTcpEdgePkgData_FileSend;
// 	pData->m_strCmdId = GetValueFromDataset(PkgData_Node_CmdId);
// 	m_strCmdId = pData->m_strCmdId;
// 	pData->m_strFullPathFileName = GetValueFromDataset(PkgData_Node_FullPathFileName);
// 	pData->m_strFileCrc = GetValueFromDataset(PkgData_Node_FileCrc);
// 	pData->m_strFileSize = GetValueFromDataset(PkgData_Node_FileSize);
// 	pData->m_strModifyTime = GetValueFromDataset(PkgData_Node_ModifyTime);
// 	if(!pData->m_strFullPathFileName.GetLength())
// 	{
// 		pData->m_strFullPathFileName = m_strFilePath;
// 		if(pData->m_strFullPathFileName.GetLength())
// 		{
// 			//并非用户主动发起,而是自动发起的文件发送
// 			pData->m_strCmdId = "1000";
// 
// 			QFileInfo find(m_strFilePath);
// 			pData->m_strFileSize.Format("%lld", find.size());
// 			QDateTime date = find.lastModified();
// 			pData->m_strModifyTime = date.toString("yyyy-MM-dd_hh:mm:ss");
// 			pData->m_strFileCrc = CRC32(m_strFilePath, find.size());
// 		}
// 	}
// 	else
// 	{
// 		m_strFileName = pData->m_strFullPathFileName.Mid(pData->m_strFullPathFileName.ReverseFind('\\') + 1);
// 		m_strFilePath = pData->m_strFullPathFileName;
// 	}
// 	pPkg->m_pPkgData = pData;
// 
// 	CDvmDataset* pTempDataset = m_pDvmDataset;
// 	m_pDvmDataset = pData->ToDataset();
// 	CDvmData* pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_CmdId);
// 	pDvmData->m_strValue = pData->m_strCmdId;
// 	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_FullPathFileName);
// 	pDvmData->m_strValue = pData->m_strFullPathFileName;
// 	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_FileCrc);
// 	pDvmData->m_strValue = pData->m_strFileCrc;
// 	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_FileSize);
// 	pDvmData->m_strValue = pData->m_strFileSize;
// 	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_ModifyTime);
// 	pDvmData->m_strValue = pData->m_strModifyTime;
// 	long nRet = Send(hSocket, pPkg);
// 	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_FileSend);
// 	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_FileSend, m_strASDU);
// 	delete m_pDvmDataset;
// 	m_pDvmDataset = pTempDataset;
// 
// 	return nRet;
// }

BOOL CTcpEdgePrcdr_File::ProduceData_FileTransReq()
{
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	CTcpEdgePkgHead* pHead = ProduceHead(PkgData_FileDataTrans, PkgData_Value_CotReq);
	pHead->m_strMid = "1";
	CTcpEdgePkgData_FileDataTrans* pData = new CTcpEdgePkgData_FileDataTrans;
	pData->m_strCmdId = m_strCmdId;
	pData->m_strFileSegNo.Format("%d", m_nFileSegNo);

	if(!m_strBase64.GetLength())
	{
		m_strBase64 = FileToBase64(m_strFilePath);
	}
	
	//由于ASDU报文最大是65535,这里给base64留下65000,超过则分段发
	if(m_strBase64.GetLength() > 65000)
	{
		pData->m_strContent = m_strBase64.Mid(0, 65000);
		pData->m_strContinue = "1";
		m_strContinue = "1";
		m_strBase64 = m_strBase64.Mid(65000);
		m_nFileSegNo++;
	}
	else
	{
		pData->m_strContent = m_strBase64;
		pData->m_strContinue = "0";
		m_strContinue = "0";
		m_strBase64 = "";
	}

	pPkg->AddNewChild(pHead);
	pPkg->AddNewChild(pData);
	pPkg->m_pPkgHead = (CTcpEdgePkgHead*)pHead->CloneEx(TRUE, TRUE);
	pPkg->m_pPkgData = (CTcpEdgePkgData*)pData->CloneEx(TRUE, TRUE);

	//创建对应的Dataset以进行必需项目分析
	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = new CDvmDataset;

	CreateDataset(pHead);

	CDvmDataset* pDataDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_CmdId);
	pDvmData->m_strValue = pData->m_strCmdId;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_FileSegNo);
	pDvmData->m_strValue = pData->m_strFileSegNo;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_Content);
	pDvmData->m_strValue = pData->m_strContent;
	pDvmData = (CDvmData*)pDataDataset->FindByID(PkgData_Node_Continue);
	pDvmData->m_strValue = pData->m_strContinue;
	m_pDvmDataset->AddNewChild(pDataDataset);
	long nRet = Send(pPkg, PkgData_FileDataTrans, m_nPort);
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_FileGet);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_FileDataTrans, m_strASDU);
	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;

	return nRet;
}

BOOL CTcpEdgePrcdr_File::ProcessFileGet(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	if(pPkg->m_strCmdID == PkgData_FileGetResp)
	{
		CTcpEdgePkgData_FileGetResp* pData = (CTcpEdgePkgData_FileGetResp*)pPkg->m_pPkgData;
		m_nMaxFileSize = CString_To_long(pData->m_strFileSize);
		QString strLog = QString("从设备获取文件,总大小:%1(kb)").arg(m_nMaxFileSize);
		//emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		m_strRecvCrc32 = pData->m_strFileCrc;
		if(pData->m_strStatus == "1")
		{
			//失败
			m_nMaxFileSize = m_nCurFileSize = 0;
			emit sig_updateViewPkg(m_strIP, "从设备获取文件执行失败!", XLOGLEVEL_EDGE_INFO);
			return TRUE;
		}
	}
	else if(pPkg->m_strCmdID == PkgData_FileDataTrans)
	{
		CTcpEdgePkgData_FileDataTrans* pData = (CTcpEdgePkgData_FileDataTrans*)pPkg->m_pPkgData;
		m_strBase64 += pData->m_strContent;

		m_strMid = pPkg->m_pPkgHead->m_strMid;
		if(pData->m_strContinue == "0")
		{
			int nTempLen = 0;
			char* strBase64Temp = base64_decode(m_strBase64.GetString(), m_strBase64.GetLength(), nTempLen);
			m_nCurFileSize = nTempLen;
			if(m_nMaxFileSize == 0)
			{
				m_nMaxFileSize = m_nCurFileSize;
			}
			QString strLog = QString("获取文件进度: %1/%2 (kb)").arg(m_nMaxFileSize).arg(m_nMaxFileSize);
			//emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);

			//文件传输
			CString strFilePath = GetDevice()->m_strRecvFilePath;
			QDir dirFile(strFilePath);
			if (!dirFile.exists())
			{
				dirFile.mkpath(strFilePath);
			}
			strFilePath += m_strFileName;

			QFileInfo find(strFilePath);
			if(find.exists())
			{
				QFile::remove(strFilePath);
			}

			//保存文件
			long nLen = 0;
			BOOL bRet = Base64ToFile(strFilePath, nLen);

			m_strBase64 = "";
			if(bRet)
			{
				//CRC文件传输校验还有问题
// 				CString strFileCrc32 = CRC32(strFilePath, nLen);
// 				if(strFileCrc32 == m_strRecvCrc32)
// 				{
					ProduceData_FileTransResp(pData->m_strCmdId, pData->m_strFileSegNo, "0", TCPEDGE_ERROR_ID_NO_ERROR, TCPEDGE_ERROR_NO_ERROR);
// 				}
// 				else
// 				{
// 					ProduceData_FileTransResp(pData->m_strCmdId, pData->m_strFileSegNo, "1", TCPEDGE_ERROR_CRC, TCPEDGE_ERROR_CRC);
// 					return TRUE;
// 				}
			}
			else
			{
				int nTempLen = 0;
				char* strBase64Temp = base64_decode(m_strBase64.GetString(), m_strBase64.GetLength(), nTempLen);
				m_nCurFileSize = nTempLen;
				QString strLog = QString("获取文件进度: %1/%2 (kb)").arg(m_nCurFileSize).arg(m_nMaxFileSize);
				//emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);

				ProduceData_FileTransResp(pData->m_strCmdId, pData->m_strFileSegNo, "1", TCPEDGE_ERROR_ID_FILE_NO_EXIST, TCPEDGE_ERROR_FILE_NO_EXIST);
				return TRUE;
			}

			m_nMaxFileSize = m_nCurFileSize = 0;
			emit sig_updateViewPkg(m_strIP, "从设备获取文件成功...", XLOGLEVEL_EDGE_PKG_RSLT);
			return TRUE;
		}
		else
		{
			ProduceData_FileTransResp(pData->m_strCmdId, pData->m_strFileSegNo, "0", TCPEDGE_ERROR_ID_NO_ERROR, TCPEDGE_ERROR_NO_ERROR);
		}
	}

	return FALSE;
}

// BOOL CTcpEdgePrcdr_File::ProcessFileSend(CPxPkgBase *pPkgDetail)
// {
// 	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
// 	if(pPkg->m_strCmdID == PkgData_FileSendResp)
// 	{
// 		CTcpEdgePkgData_FileSendResp* pData = (CTcpEdgePkgData_FileSendResp*)pPkg->m_pPkgData;
// 		if(pData->m_strStatus == "1")
// 		{
// 			//失败
// // 			CLogPrint::LogFormatString(XLOGLEVEL_EDGE_ERR, "向设备[%s]发送文件执行失败!", m_strDeviceID);
// 			QString strLog = QString("向设备发送文件执行失败");
// 			g_pTcpEdgeServer->UpdateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
// 			return TRUE;
// 		}
// 		else
// 		{
// 			ProduceData_FileTransReq(pPkg->m_hSocket);
// 		}
// 	}
// 	else if(pPkg->m_strCmdID == PkgData_FileDataTransResp)
// 	{
// 		CTcpEdgePkgData_FileDataTransResp* pData = (CTcpEdgePkgData_FileDataTransResp*)pPkg->m_pPkgData;
// 		if(pData->m_strStatus == "1")
// 		{
// 			//失败
// // 			CLogPrint::LogFormatString(XLOGLEVEL_EDGE_ERR, "向设备[%s]发送文件执行失败!", m_strDeviceID);
// 			QString strLog = QString("向设备发送文件执行失败");
// 			g_pTcpEdgeServer->UpdateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
// 			return TRUE;
// 		}
// 		else
// 		{
// 			if(m_strContinue == "1")
// 			{
// 				ProduceData_FileTransReq(pPkg->m_hSocket);
// 			}
// 			else
// 			{
// 				QString strLog = QString("向设备发送文件成功...");
// 				g_pTcpEdgeServer->UpdateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_PKG_RSLT);
// 				return TRUE;
// 			}
// 		}
// 	}
// 
// 	return FALSE;
// }

CString CTcpEdgePrcdr_File::GetValueFromDataset(const CString& strDataID)
{
	if(m_pDvmDataset)
	{
		CDvmData* pData = (CDvmData*)m_pDvmDataset->FindByID(strDataID);
		if(pData)
		{
			return pData->m_strValue;
		}
	}
	return "";
}

BOOL CTcpEdgePrcdr_File::ProcessDeviceGetLogReq(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_DeviceGetLogResp* pData = (CTcpEdgePkgData_DeviceGetLogResp*)pPkg->m_pPkgData;
	if(pData->m_strStatus == "1")
	{
		//失败
		QString strLog = QString("从设备召回设备日志失败!");
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		return TRUE;
	}

	/*File结构规范
	"File":{
		"Name":"deviceLog",
		"FileType":"tar.gz",
		"Path":"/tmp/deviceLog.tar.gz",
		"Size":"284590"}
	*/
	m_strFilePath = pData->GetTcpEdgePkgFile()->m_strPath;
	m_strFileName = pData->GetTcpEdgePkgFile()->m_strName + "." + pData->GetTcpEdgePkgFile()->m_strFileType;
	ProduceData_FileGet();
	return FALSE;
}

BOOL CTcpEdgePrcdr_File::ProcessContGetLogReq(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_ContGetLogResp* pData = (CTcpEdgePkgData_ContGetLogResp*)pPkg->m_pPkgData;
	if(pData->m_strStatus == "1")
	{
		//失败
		QString strLog = QString("从设备召回容器日志失败!");
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		return TRUE;
	}

	m_strFilePath = pData->GetTcpEdgePkgFile()->m_strPath;
	m_strFileName = pData->GetTcpEdgePkgFile()->m_strName + "." + pData->GetTcpEdgePkgFile()->m_strFileType;
	ProduceData_FileGet();
	return FALSE;
}

BOOL CTcpEdgePrcdr_File::ProcessAppGetLogReq(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_DeviceGetLogResp* pData = (CTcpEdgePkgData_DeviceGetLogResp*)pPkg->m_pPkgData;
	if(pData->m_strStatus == "1")
	{
		//失败
		QString strLog = QString("从设备召回应用日志失败!");
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		return TRUE;
	}

	m_strFilePath = pData->GetTcpEdgePkgFile()->m_strPath;
	m_strFileName = pData->GetTcpEdgePkgFile()->m_strName + "." + pData->GetTcpEdgePkgFile()->m_strFileType;
	ProduceData_FileGet();
	return FALSE;
}

BOOL CTcpEdgePrcdr_File::ProcessAppGetCfgFileReq(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_AppGetCfgFileResp* pData = (CTcpEdgePkgData_AppGetCfgFileResp*)pPkg->m_pPkgData;
	if(pData->m_strStatus == "1")
	{
		//失败
		QString strLog = QString("从设备召回应用配置文件失败!");
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		QString strErr = QString("从设备召回应用配置文件失败! 错误代码: [%1]; Note: [%2]").arg(pData->m_strErrorCode).arg(pData->m_strNote);
		emit sig_updateViewPkg(m_strIP, strErr, XERRTYPE_RETURNFALSE);
		return TRUE;
	}

	CTcpEdgePkgFile* pFile = pData->GetTcpEdgePkgFile();
	m_strFilePath = pFile->m_strPath;
	m_strFileName = pData->GetTcpEdgePkgFile()->m_strName + "." + pData->GetTcpEdgePkgFile()->m_strFileType;

	ProduceData_FileGet();
	return FALSE;
}

//BOOL CTcpEdgePrcdr_File::ProcessAppSetCfgFileReq(CPxPkgBase *pPkgDetail)
//{
//	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
//	CTcpEdgePkgData_AppSetCfgFileResp* pData = (CTcpEdgePkgData_AppSetCfgFileResp*)pPkg->m_pPkgData;
//	if(pData->m_strStatus == "1")
//	{
//		//失败
//		CLogPrint::LogFormatString(XLOGLEVEL_EDGE_ERR, "设备[%s]下载应用配置文件失败!错误代码: [%s]; Note: [%s]", m_strDeviceID, pData->m_strErrorCode, pData->m_strNote);
//		return TRUE;
//	}
//
//	ProduceData_FileSend(pPkg->m_hSocket);
//	return FALSE;
//}

unsigned long ssh_crc32(unsigned char *buf, unsigned long size)
{
	unsigned long i, crc;

	crc = 0xFFFFFFFF;
	for (i = 0; i < size; i++)
		crc = CRC32_Table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
	return crc^0xFFFFFFFF;
}

CString CTcpEdgePrcdr_File::CRC32(CString strFilePath, long nFileLength)
{
	CFile fp;
	if(!(fp.Open(strFilePath, CFile::modeRead))) 
	{
		return "";
	}

	fp.SeekToBegin();
	char* pBuffer = new char[nFileLength];
	if(fp.Read(pBuffer, nFileLength) < 1)
	{
		fp.Close();
		return "";
	}
	fp.Close();
    
	unsigned long nCRC32 = 0xFFFFFFFF;
	for (int i = 0; i < nFileLength; i++)
	{
		nCRC32 = CRC32_Table[(nCRC32 ^ pBuffer[i]) & 0xFF] ^ (nCRC32 >> 8);
	}
	nCRC32 = nCRC32^0xFFFFFFFF;

	CString strCRC32;
	strCRC32.Format("0x%.8X", nCRC32);

	return strCRC32;
}

void CTcpEdgePrcdr_File::CreateDataset(CTcpEdgePkgHead* pHead)
{
	CDvmDataset* pHeadDataset = pHead->ToDataset();
	CDvmData* pDvmData = (CDvmData*)pHeadDataset->FindByID(PkgData_Node_FunName);
	pDvmData->m_strValue = pHead->m_strFunName;
	pDvmData = (CDvmData*)pHeadDataset->FindByID(PkgData_Node_Cot);
	pDvmData->m_strValue = pHead->m_strCot;
	pDvmData = (CDvmData*)pHeadDataset->FindByID(PkgData_Node_Timestamp);
	pDvmData->m_strValue = pHead->m_strTimestamp;
	pDvmData = (CDvmData*)pHeadDataset->FindByID(PkgData_Node_Mid);
	pDvmData->m_strValue = pHead->m_strMid;
	m_pDvmDataset->AddNewChild(pHeadDataset);
}

BOOL CTcpEdgePrcdr_File::ProcessDeviceUpdateStatusReq(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* tmpPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_DeviceUpdateResp* pDeviceUpdateRespData = (CTcpEdgePkgData_DeviceUpdateResp*)tmpPkg->m_pPkgData;

	CTcpEdgePkg* pPkg = new CTcpEdgePkg;

	if(m_strID.Find("Req") != -1)
	{
		pPkg->m_pPkgHead = ProduceHead(PkgData_DeviceUpdateStatusReq, PkgData_Value_CotReq);
	}
	else
	{
		pPkg->m_pPkgHead = ProduceHead(PkgData_DeviceUpdateStatusReq, PkgData_Value_CotResp);
	}

	CTcpEdgePkgData_DeviceUpdateStatusReq* pData = new CTcpEdgePkgData_DeviceUpdateStatusReq;
	pData->m_strJobId = pDeviceUpdateRespData->m_strJobId;
	pPkg->m_pPkgData = pData;

	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_JobId);
	pDvmData->m_strValue = pData->m_strJobId;

	QByteMap map;
	Produce(pPkg, map);
	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_DeviceUpdateReq);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_DeviceUpdateStatusReq, m_strASDU);
	Send(map, PkgData_DeviceUpdateStatusReq);
	delete pPkg;
	return TRUE;
}

BOOL CTcpEdgePrcdr_File::ProcessAppInstallStateReq(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* tmpPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_AppInstallResp* pAppInstallRespData = (CTcpEdgePkgData_AppInstallResp*)tmpPkg->m_pPkgData;

	CTcpEdgePkg* pPkg = new CTcpEdgePkg;

	if(m_strID.Find("Req") != -1)
	{
		pPkg->m_pPkgHead = ProduceHead(PkgData_AppInstallStatusReq, PkgData_Value_CotReq);
	}
	else
	{
		pPkg->m_pPkgHead = ProduceHead(PkgData_AppInstallStatusReq, PkgData_Value_CotResp);
	}

	CTcpEdgePkgData_AppInstallStatusReq* pData = new CTcpEdgePkgData_AppInstallStatusReq;
	pData->m_strJobId = m_strJobId;
	pPkg->m_pPkgData = pData;

	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_JobId);
	pDvmData->m_strValue = pData->m_strJobId;

	QByteMap map;
	Produce(pPkg, map);
	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_AppInstallReq);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_AppInstallStatusReq, m_strASDU);
	Send(map, PkgData_AppInstallStatusReq);
	delete pPkg;
	return TRUE;
}

void CTcpEdgePrcdr_File::FailErrorInfo(CPxPkgBase *pPkgDetail, CString strID)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;

	CTcpEdgePkgData* pData = pPkg->m_pPkgData;
	CString strTemp;

	if(pPkgDetail->m_strCmdID == PkgData_FileGetResp)       
	{
		CTcpEdgePkgData_FileGetResp* pDataResp = (CTcpEdgePkgData_FileGetResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_FileGetResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_FileGetResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_FileGetResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_FileDataTransResp)       
	{
		CTcpEdgePkgData_FileDataTransResp* pDataResp = (CTcpEdgePkgData_FileDataTransResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_FileDataTransResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_FileDataTransResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_FileDataTransResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DeviceUpdateResp)       
	{
		CTcpEdgePkgData_DeviceUpdateResp* pDataResp = (CTcpEdgePkgData_DeviceUpdateResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceUpdateResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceUpdateResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceUpdateResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DeviceUpdateStatusResp)       
	{
		CTcpEdgePkgData_DeviceUpdateStatusResp* pDataResp = (CTcpEdgePkgData_DeviceUpdateStatusResp*)pPkg->m_pPkgData;
		if(pDataResp->m_strState == _T("0"))
		{
			strTemp = QString(_T("【执行失败】[%1]报文, 当前设备升级任务不存在; \n")).arg(PkgData_DeviceUpdateStatusResp);
		}
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += strTemp;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DeviceUpdateResult)       
	{
		CTcpEdgePkgData_DeviceUpdateResult* pDataResp = (CTcpEdgePkgData_DeviceUpdateResult*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceUpdateResult);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceUpdateResult);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceUpdateResult);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppInstallResp)       
	{
		CTcpEdgePkgData_AppInstallResp* pDataResp = (CTcpEdgePkgData_AppInstallResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppInstallResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppInstallResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppInstallResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppInstallStatusResp)       
	{
		CTcpEdgePkgData_AppInstallStatusResp* pDataResp = (CTcpEdgePkgData_AppInstallStatusResp*)pPkg->m_pPkgData;
		if(pDataResp->m_strState == _T("0"))
		{
			strTemp = QString(_T("【执行失败】[%1]报文, 当前应用安装任务不存在; \n")).arg( PkgData_AppInstallStatusResp);
		}
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += strTemp;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppInstallResult)       
	{
		CTcpEdgePkgData_AppInstallResult* pDataResp = (CTcpEdgePkgData_AppInstallResult*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppInstallResult);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppInstallResult);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppInstallResult);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DeviceGetLogResp)       
	{
		CTcpEdgePkgData_DeviceGetLogResp* pDataResp = (CTcpEdgePkgData_DeviceGetLogResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceGetLogResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceGetLogResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceGetLogResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ContGetLogResp)       
	{
		CTcpEdgePkgData_ContGetLogResp* pDataResp = (CTcpEdgePkgData_ContGetLogResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ContGetLogResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ContGetLogResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ContGetLogResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppGetLogResp)       
	{
		CTcpEdgePkgData_AppGetLogResp* pDataResp = (CTcpEdgePkgData_AppGetLogResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppGetLogResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppGetLogResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppGetLogResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppGetCfgFileResp)       
	{
		CTcpEdgePkgData_AppGetCfgFileResp* pDataResp = (CTcpEdgePkgData_AppGetCfgFileResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppGetCfgFileResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppGetCfgFileResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppGetCfgFileResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppSetCfgFileResp)       
	{
		CTcpEdgePkgData_AppSetCfgFileResp* pDataResp = (CTcpEdgePkgData_AppSetCfgFileResp*)pPkg->m_pPkgData;
		strTemp = FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetCfgFileResp);
		pDataResp->m_strErrorInfo += strTemp;
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetCfgFileResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetCfgFileResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		strTemp = pDataResp->m_strErrorInfo;
	}
	else
	{
		return;
	}

	//更新到模型
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(strID);
	CDvmData *pDvmData = (CDvmData *)pDataset->GetTail();
	pDvmData->m_strValue = strTemp;
}

QString CTcpEdgePrcdr_File::FailErrorInfo(CString strStatus, CString strErrorCode, CString strNote, CString strPkgID)
{
	QString strTemp;
	if(strStatus != "0")
	{
		if(strStatus == "1")
		{
			//失败
			strTemp = QString(_T("【执行失败】[%1]报文, 错误代码: [%2]; Note: [%3]; \n")).arg(strPkgID).arg(strErrorCode).arg(strNote);
		}
		else
		{
			strTemp = QString(_T("【错误】【超过范围】[%1]报文字段Status超出范围, 无法判断执行状态;\n")).arg(strPkgID);
		}
	}
	return strTemp;
}

QString CTcpEdgePrcdr_File::ReurnFalseInfo(CString strStatus, CString strErrorCode, CString strNote, CString strPkgID)
{
	QString strTemp;
	if(strStatus != "0")
	{
		if(strStatus == "1")
		{
			//失败
			strTemp = QString(_T("【执行失败】[%1]报文, 错误代码: [%2]; Note: [%3]; \n")).arg(strPkgID).arg(strErrorCode).arg(strNote);
		}
	}
	return strTemp;
}

QString CTcpEdgePrcdr_File::RangeOutInfo(CString strStatus, CString strErrorCode, CString strNote, CString strPkgID)
{
	QString strTemp;
	if(strStatus != "0")
	{
		if(strStatus != "1")
		{
			strTemp = QString(_T("【错误】【超过范围】[%1]报文字段Status超出范围, 无法判断执行状态;\n")).arg(strPkgID);
		}
	}
	return strTemp;
}

void CTcpEdgePrcdr_File::UpdateErrInfo(QString strNecessityLack, QString strNecessityErr, QString strRangeOut, QString strReturnFalse)
{
	if (strNecessityLack != "")
	{
		emit sig_updateViewPkg(m_strIP, strNecessityLack,XERRTYPE_LACKNECESSITY);
	}
	if (strNecessityErr != "")
	{
		emit sig_updateViewPkg(m_strIP, strNecessityErr, XERRTYPE_NECESSITYERR);

	}
	if (strReturnFalse != "")
	{
		emit sig_updateViewPkg(m_strIP, strReturnFalse, XERRTYPE_RETURNFALSE);
	}
	if (strRangeOut != "")
	{	
		emit sig_updateViewPkg(m_strIP,strRangeOut,XERRTYPE_RANGEOUT);
	}
}