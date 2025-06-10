#include "stdafx.h"
#include "tmt_pic200d_iotest.h"
#include "../../../../Module/API/StringApi.h"

void stt_xml_serialize(tmt_Pic200dIoTest *pPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strID;

    for(int nIndex=0;nIndex<8;nIndex++)
    {
        strID.Format(_T("1_IO%d"),nIndex+1);
        pXmlSierialize->xml_serialize("",strID.GetString(),"","long",pPara->m_nIO1[nIndex]);
    }
    for(int nIndex=0;nIndex<8;nIndex++)
    {
        strID.Format(_T("3_IO%d"),nIndex+1);
        pXmlSierialize->xml_serialize("",strID.GetString(),"","long",pPara->m_nIO3[nIndex]);
    }
    for(int nIndex=0;nIndex<16;nIndex++)
    {
        strID.Format(_T("2_IO%d"),nIndex+1);
        pXmlSierialize->xml_serialize("",strID.GetString(),"","long",pPara->m_nIO2[nIndex]);
    }
}

#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"

