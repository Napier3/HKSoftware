#include "SttIecRecord.h"
#ifdef _PSX_IDE_QT_
    #include "../../../SttDevice/SttDeviceBase.h"
    #include "../../../SttDevice/Module/Driver466/IEC_GlobalDefine.h"
#endif

CString CSttIecRecord::m_strMacroName = "数字报文采集测试";
CString CSttIecRecord::m_strMacroID = STT_MACRO_ID_IecRecord;
CString CSttIecRecord::m_strFilePostFix = "stttst";
CString CSttIecRecord::m_strMacroVer = "1.0";

CSttIecRecord::CSttIecRecord()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
}

CSttIecRecord::~CSttIecRecord()
{
}

void CSttIecRecord::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    IECRecordItems oIECRecordItems;
    oIECRecordItems.bEnable = FALSE;
    oIECRecordItems.bHasSmv = FALSE;
    oIECRecordItems.nCount6044 = 0;
    oIECRecordItems.nCount61850 = 0;
    BOOL bOk;
    BOOL bIs6044 = FALSE;
    pXmlSerialize->xml_serialize("", "Enable", "", "", oIECRecordItems.bEnable);

    if(oIECRecordItems.bEnable)
    {
        CString strVaule;
        CString strType;
        CString strPort;
        int nCount6044;
        int nCount61850;
        float fBaudRate;

        for(int nIndex = 0; nIndex < 16; nIndex++)
        {
            CSttXmlSerializeBase *pSubBlock = pXmlSerialize->xml_serialize(stt_ParaGroupKey(), nIndex, "", "Subscribe", "Subscribe");

            if(pSubBlock == NULL)
            {
                break;
            }

            pSubBlock->xml_serialize("", XPARA_ID_Port, "", "", strPort);
            bIs6044 = pSubBlock->xml_serialize("", XPARA_ID_BaudRate, "", "", strVaule);

            if(bIs6044)
            {
                oIECRecordItems.bHasSmv = TRUE;
                nCount6044 = oIECRecordItems.nCount6044;
                IECRecordItem_6044 &oItem_6044 = oIECRecordItems.item6044[nCount6044];
                oIECRecordItems.nCount6044++;
                pSubBlock->xml_serialize("", XPARA_ID_BaudRate, "", "", fBaudRate);
                pSubBlock->xml_serialize("", XPARA_ID_OnePkgLen, "", "", oItem_6044.nPkgLen);
                oItem_6044.nPort = strPort.toInt();
                fBaudRate = fBaudRate * 2;
                oItem_6044.nBaudRate = 200 / fBaudRate;
            }
            else
            {
                nCount61850 = oIECRecordItems.nCount61850;
                IECRecordItem_61850 &oItem_61850 = oIECRecordItems.item61850[nCount61850];
                oIECRecordItems.nCount61850++;
                int nSubMode = 0;
                pSubBlock->xml_serialize("", XPARA_ID_Type, "", "", strType);

                if(strType == XPARA_ID_TYPE_SMV92)
                {
                    oIECRecordItems.bHasSmv = TRUE;
                }

                BOOL bRet = pSubBlock->xml_serialize("", XPARA_ID_CRC, "", "", strVaule);

                if(bRet)
                {
                    if(strVaule.length() >= 3)
                    {
                        nSubMode = 1;
                    }
                }

                if(nSubMode == 1)
                {
                    strVaule = strVaule.replace("0x", "");
                    oItem_61850.nFilterVal = strVaule.toInt(&bOk, 16);
                }
                else
                {
                    CString strDestMac;
                    CString strAppID;
                    pSubBlock->xml_serialize("", XPARA_ID_DestMac, "", "", strDestMac);
                    pSubBlock->xml_serialize("", XPARA_ID_APPID, "", "", strAppID);
                    strAppID = strAppID.replace("0x", "");
                    int nType = 2;

                    if(strType == XPARA_ID_TYPE_SMV92)
                    {
                        nType = 1;
                    }

                    oItem_61850.nFilterVal =
                        CalCRC(strAppID, strDestMac, strPort.toInt(), nType);
                }
            }
        }
    }

    CSttDeviceBase::g_pSttDeviceBase->SetIecFilter(&oIECRecordItems);
#endif
}

void CSttIecRecord::StartTest()
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttIecRecord::StartTest >>>>>>");

	ReturnTestStateEvent_TestStart(0, 0, FALSE);
#ifdef _PSX_QT_LINUX_
	Sleep(50);
#endif
	//时间标识置为0,自动测试处理此消息
	ReturnTestStateEvent_TestFinish(0, 0, FALSE);
}
