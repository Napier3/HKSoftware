#include "SttIecDetect.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#include "../../../SttDevice/Module/Driver466/IEC61850CfgMngr.h"
#endif

CString CSttIecDetect::m_strMacroName = "数字报文探测测试";
CString CSttIecDetect::m_strMacroID = STT_MACRO_ID_IecDetect;
CString CSttIecDetect::m_strFilePostFix = "stttst";
CString CSttIecDetect::m_strMacroVer ="1.0";

CSttIecDetect::CSttIecDetect()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttIecDetect::~CSttIecDetect()
{

}

void CSttIecDetect::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    BOOL bEnable;
	long nType = 0;
	pXmlSerialize->xml_serialize("","Enable","","long",bEnable);	

#ifdef _PSX_QT_LINUX_
	if(bEnable)
	{
		pXmlSerialize->xml_serialize("","Ft3_CRCType","","long",nType);
		Ft3SubCrcs oSubCrcs;
		memset(&oSubCrcs,0,sizeof(Ft3SubCrcs));
		oSubCrcs.nCrcType = nType;

		Drv_IECConfigFt3 *pIECConfigFt3 = CSttDeviceBase::g_pSttDeviceBase->m_pIECConfigFt3;

		oSubCrcs.nModuleCnt = pIECConfigFt3->mdCnt;
		for(int i = 0; i < pIECConfigFt3->mdCnt && i < 4; i++)
		{
			if(pIECConfigFt3->item[i].nSTRecvBeginIdx > -1)
			{
				oSubCrcs.ft3SubCrc[i].nModule = pIECConfigFt3->item[i].module;
			}

			oSubCrcs.ft3SubCrc[i].nCnt = pIECConfigFt3->item[i].nSTRecvEndIdx
					- pIECConfigFt3->item[i].nSTRecvBeginIdx + 1;
		}

		if(nType == 1)
		{
			unsigned int nLenTotal[16];
			memset(nLenTotal,0,16*4);
			CString strID;
			for(int i = 0; i < 16; i++)
			{
				strID.Format("Ft3_PkgLength%d",i+1);
				//报文通道字节总和，不含0564和CRC
				pXmlSerialize->xml_serialize("",strID.GetString(),"","long",nLenTotal[i]);
			}

			for(int i = 0; i < 16; i++)
			{
				int nBoard = -1;

				for(int j = 0; j < pIECConfigFt3->mdCnt; j++)
				{
					if(i >= pIECConfigFt3->item[j].nSTRecvBeginIdx
							&& i <= pIECConfigFt3->item[j].nSTRecvEndIdx)
					{
						nBoard = j;
						break;
					}
				}

				if((nBoard >= 0) && (nBoard < 4))
				{
					if(nLenTotal[i] > 0)
					{
						int nIndex = i - pIECConfigFt3->item[nBoard].nSTRecvBeginIdx;
						oSubCrcs.ft3SubCrc[nBoard].nPkgLen[nIndex] = nLenTotal[i] + 4;
					}
				}
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->SetFT3SubCRC((char *)&oSubCrcs);
	}

	nType = 0;
	pXmlSerialize->xml_serialize("","IecType","","long",nType);
	switch(nType)
	{
	case 0://All
	case 1://SMV
	case 2://GOOSE
	case 3://FT3
		break;
	default:
		nType = 0;
	}

	CSttDeviceBase::g_pSttDeviceBase->SetIecDetect(bEnable, nType);
#endif
}
