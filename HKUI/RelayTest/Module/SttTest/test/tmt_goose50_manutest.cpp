#include "stdafx.h"
#include "tmt_goose50_manutest.h"

void stt_init_paras(tmt_Goose50Paras *pParas)
{
    memset(&pParas, 0, sizeof(tmt_Goose50Paras));
    pParas->init();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///


void stt_xml_serialize(tmt_Goose50Paras *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        CSttXmlSerializeBase *pGOOSEPubXml = pXmlSierialize->xml_serialize("", "GOOSEPubs", "GOOSEPubs", stt_ParaGroupKey());

        if(pGOOSEPubXml != NULL)
        {
            for(int nIndex = 0; nIndex < 50; nIndex++)
            {
                CSttXmlSerializeBase *pGooseSerialize = pGOOSEPubXml->xml_serialize("GOOSE发布控制块", "GOOSEPub", nIndex + 1, "GOOSEPub", stt_ParaGroupKey());

                if(pGooseSerialize)
                {
                    pParas->m_oGoosePub[nIndex].m_bUseFlag = TRUE;
                    CString strVal = _T("GooseChannel");
                    CString strChannelID;

                    for(int nChanIndex = 0; nChanIndex < 20; nChanIndex++)
                    {
                        strChannelID.Format(_T("%d"), nChanIndex + 1);
                        strChannelID = strVal + strChannelID;
                        pGooseSerialize->xml_serialize("GOOSE通道", strChannelID.GetString(), " ", "string", pParas->m_oGoosePub[nIndex].m_strChannel[nChanIndex]);
                    }
                }
            }
        }
    }
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"

