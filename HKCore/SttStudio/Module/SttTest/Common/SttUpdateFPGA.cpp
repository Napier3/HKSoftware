#include "stdafx.h"
#include "tmt_common_def.h"
#include "SttUpdateFPGA.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#include "../../Engine/SttTestServerBase.h"
#include <fstream>
#include "QDebug"
#endif

CString CSttUpdateFPGA::m_strMacroName = "ģ��̼���������";
CString CSttUpdateFPGA::m_strMacroID = STT_MACRO_ID_UpdateFPGA;

CSttUpdateFPGA::CSttUpdateFPGA()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_nModuleIndex = -1;
    m_strFileName = _T("");
    m_pChar = new char[20*1024*1024];
}

CSttUpdateFPGA::~CSttUpdateFPGA(void)
{
    if(m_pChar != NULL)
    {
        delete[] m_pChar;
    }
}

void CSttUpdateFPGA::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    m_nModuleIndex = -1;
    m_strFileName = _T("");
    m_nUpdateIndex = 0;
	pXmlSerialize->xml_serialize("ͨ��λ��", "ModuleIndex", "", "", m_nModuleIndex);
	pXmlSerialize->xml_serialize("�ļ�����", "FileName", "", "", m_strFileName);
}

void CSttUpdateFPGA::StartTest()
{
#ifdef _PSX_QT_LINUX_
    if(m_nModuleIndex > -1 && m_nModuleIndex < 8)
    {
        CString strPath = _P_GetSystemPath();
        if(m_nModuleIndex == 0)
        {
            strPath += "FPGA/BOOT.bin";
            QFile ofile(strPath);
            if(ofile.exists())
            {
                system("rm /mnt/BOOT.bin");
                system("sync");
                CString strCmd;
                strCmd.Format(_T("mv %s /mnt/BOOT.bin"),strPath.GetString());
                qDebug()<<strCmd;
                system(strCmd.toUtf8());
                system("sync");
                m_nUpdateIndex = 100;
                SendUpdateIndex();
                CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("������ɣ���ϵ������豸"));
            }
        }
        else
        {
            strPath += "FPGA/";
            strPath += m_strFileName;

            std::ifstream file;
            file.open(strPath.toLatin1().data(),std::ios::binary|std::ios::ate);
            if(file.is_open())
            {
				if(!CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting)
				{
					CSttDeviceBase::g_pSttDeviceBase->m_bTestStarting = TRUE;
					pthread_mutex_unlock(&g_oTestResultMutex);
				}

                int nSize = file.tellg(); //ͨ����־ate�õ��ļ���С��
                file.seekg(0,std::ios::beg); //�Ѷ�ȡλ������д���ļ���ͷ��
                if(m_pChar != NULL)
                {
                    file.read(m_pChar,nSize);
                    file.close();

                    m_nUpdateIndex = 0;
                    SendUpdateIndex();
					g_bUpdateFPGA = TRUE;
					g_bNeedReadDeviceStatatus = FALSE;

                    CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("FPGA�洢����ʼ�����Ԥ��ʱ��40��"));
                    m_nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
					
					g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
                    ioctl(m_nfd,0x30f,1<<(m_nModuleIndex - 1));
                    write(m_nfd,m_pChar,nSize);
					g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

                    SetTestStarting(TRUE);
                }
            }
        }
    }
#endif
}

BOOL CSttUpdateFPGA::EventProcessEx()
{
    m_nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	int nFlag = 0;
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nFlag = ioctl(m_nfd,0x502,0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    if(nFlag == SPI_FLAG_EREASE_FINISH)
    {
        //"FPGA�洢�������"
        CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("FPGA�洢������ɹ�"));
    }
    else if(nFlag == SPI_FLAG_EREASE_FAILED)
    {
        //"FPGA�洢�����ʧ��"
        CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("FPGA�洢�����ʧ��"));
    }
    else if(nFlag == SPI_FLAG_IN_WRITING)
    {
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
        m_nUpdateIndex = ioctl(m_nfd,0x505,0);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
        SendUpdateIndex();
    }
    else if(nFlag == SPI_FLAG_IN_WRITING_FAILED)
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("���¹����쳣�ж�"));
    }
    else if(nFlag == SPI_FLAG_WRITE_FINISH)
    {
        m_nUpdateIndex = 100;
        SendUpdateIndex();
        CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("������ɣ���ϵ������豸"));
    }
    return FALSE;
}

void CSttUpdateFPGA::SendUpdateIndex()
{
    CSttTestServerBase *pSttTestServerBase = CSttTestServerBase::GetServerEngine();
    if(pSttTestServerBase == NULL)
	{
        return;
	}
    CSttTestClientUserMngr *pSttTestClientUserMngr = pSttTestServerBase->GetTestClientUserMngr();
    if(pSttTestClientUserMngr == NULL)
	{
        return;
	}

    CSttSysState oSysState;
    CSttTestCmd *pTempCmd = (CSttTestCmd*)pSttTestServerBase->m_oSttTestCmd.CloneEx();
    pTempCmd->m_strID = _T("");

    oSysState.SetRetType(SYS_STATE_RETTYPE_EVENT);
    oSysState.UpdateSysStateHead(pTempCmd);
    CSttParas *pParas = oSysState.GetSttParas();
    pParas->AddNewData("CurrStateIndex","CurrStateIndex",m_nUpdateIndex);

    CSttTestClientUser *pUser = NULL;
    POS pos = pSttTestClientUserMngr->GetHeadPosition();
    while(pos != NULL)
    {
        pUser = (CSttTestClientUser *)pSttTestClientUserMngr->GetNext(pos);
        if(pUser != NULL)
        {
			if(pUser->m_pRefSttSckt != NULL)
            {
                pUser->m_pRefSttSckt->SendSysState(&oSysState);
            }
        }
    }
}
