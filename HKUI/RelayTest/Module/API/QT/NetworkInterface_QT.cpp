#include "stdafx.h"
#include "../NetworkInterface.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "QNetworkInterface"
#include "../../SttTestBase/SttXmlSerialize.h"

long stt_file_save_deviceip(const CString &strIP, const CString &strMask)
{
    CString strCmd;

    strCmd.Format(_T("ifconfig %s %s netmask %s up \n"), g_str_Net_DeviceName.GetString(), strIP.GetString(), strMask.GetString());
    QFile fileIp("/mnt/setip.sh");
    if(fileIp.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate))
    {
        fileIp.write(strCmd.toUtf8());
        fileIp.flush();
        fileIp.close();
		system("sync");
        return 0;
    }

    return 1;
}

long stt_file_save_subips(const CStringArray &astrIP, const CStringArray &astrMask, const CStringArray &astrGW, long *pMetric,long nBeginIndex)
{
    if(astrIP.GetCount() <= nBeginIndex || astrMask.GetCount() <= nBeginIndex)
        return 1;

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SubIP.xml");

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pParas = oSttXmlSerializeTool.CreateXmlSerializeWrite();

	long nCount = astrIP.GetCount();
	CString strIP, strMask, strGW, strID;

	for (int i=0; i<nCount; i++)
	{
		if((i+nBeginIndex) < nCount)
		{
			strIP = astrIP.GetAt(i+nBeginIndex);
			strMask = astrMask.GetAt(i+nBeginIndex);
			strGW = astrGW.GetAt(i+nBeginIndex);
			strID.Format("SubIP%d",i+1);

			CSttXmlSerializeBase *pGroupSerialize = pParas->xml_serialize("", strID.GetString(), "SubIP", stt_ParaGroupKey());

			if (pGroupSerialize == NULL)
			{
				continue;
			}

			pGroupSerialize->xml_serialize("", "IP", "", "string",  strIP);
			pGroupSerialize->xml_serialize("", "Mask", "", "string",  strMask);
			pGroupSerialize->xml_serialize("", "GateWay", "", "string",  strGW);
			pGroupSerialize->xml_serialize("", "Metric", "", "long",  pMetric[i+nBeginIndex]);
		}
	}

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
	system("sync");

    return 1;
}

void stt_file_get_subips(CStringArray &astrIP, CStringArray &astrMask, CStringArray &astrGateWay,long* nMetric)
{
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SubIP.xml");

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pParas = oSttXmlSerializeTool.CreateXmlSerializeRead(strXMLPath);
	if(pParas == NULL)
	{
		return;
	}

	CString strIP, strMask, strGW, strID;

	for(int i = 0;i < 100;i++)
	{
		strID.Format("SubIP%d",i+1);
		CSttXmlSerializeBase *pGroupSerialize = pParas->xml_serialize("", strID.GetString(), "SubIP", stt_ParaGroupKey());

		if (pGroupSerialize == NULL)
		{
			return;
		}

		pGroupSerialize->xml_serialize("", "IP", "", "string",  strIP);
		pGroupSerialize->xml_serialize("", "Mask", "", "string",  strMask);
		pGroupSerialize->xml_serialize("", "GateWay", "", "string",  strGW);
		pGroupSerialize->xml_serialize("", "Metric", "", "long",  nMetric[i]);

		astrIP.Add(strIP);
		astrMask.Add(strMask);
		astrGateWay.Add(strGW);
	}
}

long stt_net_set_ip(long nIndex, const CString &strIP, const CString &strMask)
{
    //CString strCmd=CString("ifconfig eth0:1 %1 netmask %2 up").arg(strIP).arg(strMask);
    CString strCmd;
	
    strCmd.Format(_T("ifconfig %s:%d %s netmask %s up"),g_str_Net_DeviceName.GetString(), nIndex, strIP.GetString(), strMask.GetString());
    system(strCmd.GetString());//system(strCmd.toUtf8());

	CLogPrint::LogString(XLOGLEVEL_TRACE,strCmd);
    return 1;
}

long stt_net_set_gateway(const CString &strGateWay,long nMetric)
{
    //nMetric 值范围 1-100
    CString strCmd;
    strCmd.Format(_T("route add default gw %s metric %d dev %s"),strGateWay.GetString(),nMetric,g_str_Net_DeviceName.GetString());
    system(strCmd.GetString());//system(strCmd.toUtf8());

	CLogPrint::LogString(XLOGLEVEL_TRACE,strCmd);
    return 1;
}

#include <QNetworkInterface>

void stt_net_get_deviceip_ex(CString &strIP, CString &strMask)
{
    strIP=_T("");
    strMask=_T("");

    QList<QNetworkInterface> listInterface = QNetworkInterface::allInterfaces();
    QNetworkInterface oInterface;
    long nCount = listInterface.size();
    long k = 0;

    for (k=0; k<nCount; k++)
    {
        oInterface = listInterface.at(k);

        strIP=oInterface.addressEntries().at(0).ip().toString();
        strMask=oInterface.addressEntries().at(0).netmask().toString();

        if (strIP != "127.0.0.1")
        {
            break;
        }
    }
}

void stt_file_get_deviceip(CString &strIP, CString &strMask)
{
    QFile fileIp("/mnt/setip.sh");
    BOOL bFind = FALSE;

    if(fileIp.exists())
    {
        if(fileIp.open(QIODevice::Text | QIODevice::ReadOnly)) //|QIODevice::Truncate
        {
            char pszBuf[1024];
            int nfileSize;
            while(!fileIp.atEnd())
            {
                nfileSize = fileIp.readLine(pszBuf,1024);
                if(nfileSize > 0)
                {
                    CString strData(pszBuf);
                    if(strData.contains("ifconfig") && strData.contains("netmask"))
                    {
                        QList<QString> oList = strData.split(" ");
                        strIP = oList.at(2);
                        strMask = oList.at(4);
                        bFind = TRUE;
                        break;
                    }
                }
            }

            fileIp.close();
        }
    }

    if(!bFind)
    {
        stt_net_get_deviceip(strIP, strMask);
    }
}

void stt_net_get_deviceip(CString &strIP, CString &strMask)
{
	strIP=_T("");
	strMask=_T("");
    CString strName;

    QList<QNetworkInterface> listInterface = QNetworkInterface::allInterfaces();
    QNetworkInterface oInterface;
    long nCount = listInterface.size();
    long k = 0;

    for (k=0; k<nCount; k++)
    {
        oInterface = listInterface.at(k);
        strName=oInterface.name();

        if(g_str_Net_DeviceName == strName)
        {
            if(oInterface.addressEntries().count() > 0)
            {
                strIP=oInterface.addressEntries().at(0).ip().toString();
                strMask=oInterface.addressEntries().at(0).netmask().toString();
                return;
            }
        }

    }

    //2020-12-04  lijunqing   如果没找到对应的IP，则默认使用第一个设置的IP
    stt_net_get_deviceip_ex(strIP, strMask);
}

long stt_net_get_ip(CStringArray &astrIP, CStringArray &astrMask)
{
    CString strIP, strMask, strName;

    QList<QNetworkInterface> listInterface = QNetworkInterface::allInterfaces();
    QNetworkInterface oInterface;
    long nInterfaceCount = listInterface.size();
    long k = 0;

    for (k=0; k<nInterfaceCount; k++)
    {
        oInterface = listInterface.at(k);
        strName=oInterface.name();

        if(g_str_Net_DeviceName == strName)
        {
            long nCount = oInterface.addressEntries().count();

            for (long i=0; i<nCount; i++)
            {
                strIP = oInterface.addressEntries().at(i).ip().toString();
                strMask = oInterface.addressEntries().at(i).netmask().toString();
                astrIP.Add(strIP);
                astrMask.Add(strMask);
            }
        }
    }

    return astrIP.GetCount();
}

long stt_net_set_subips(CStringArray &astrIP, CStringArray &astrMask, long nIPBeginIndex)
{
    if(nIPBeginIndex < 2)
    {
        nIPBeginIndex = 2; // '1'预留给DHCP，强制从'2'开始
    }
    long i = 0;
    long nCount = astrIP.GetCount();
    CString strIP, strMask;

	for (i=0; i<nCount; i++)
    {
        strIP = astrIP.GetAt(i);
        strMask = astrMask.GetAt(i);
        stt_net_set_ip(nIPBeginIndex, strIP, strMask);
        nIPBeginIndex++;
    }

    return 0;
}

long stt_net_set_gateway(const CStringArray &astrGateWay,long* nMetric)
{
    long i = 0;
    long nCount = astrGateWay.GetCount();
    CString strGateWay;

    for (i=0; i<nCount; i++)
    {
        strGateWay = astrGateWay.GetAt(i);
		if(strGateWay == "0.0.0.0")
		{
			continue;
		}

        if(nMetric[i] < 0)
            nMetric[i] = 100;//20220526 zhoulei 优先级默认100		
        stt_net_set_gateway(strGateWay, nMetric[i]);//连外网的优先级的nMetric数值一定要是最小的
    }
    return 0;
}

void stt_net_dhcp()
{
    CString strCmd;

    strCmd.Format(_T("udhcpc -i %s:1 -s %sdefault.script -n"),g_str_Net_DeviceName.GetString(), _P_GetBinPath());
    system(strCmd.GetString());//20220526 zhoulei 由路由器动态分配IP地址
}


#ifdef _PSX_IDE_QT_
long stt_net_get_ip(QStringList &astrIP, QStringList &astrMask)
{
    QString  strIP, strMask, strName;

    QList<QNetworkInterface> listInterface = QNetworkInterface::allInterfaces();
    QNetworkInterface oInterface;
    long nInterfaceCount = listInterface.size();
    long k = 0;

    for (k=0; k<nInterfaceCount; k++)
    {
        oInterface = listInterface.at(k);
        strName=oInterface.name();

        if(g_str_Net_DeviceName == strName)
        {
            long nCount = oInterface.addressEntries().count();

            for (long i=0; i<nCount; i++)
            {
                strIP=oInterface.addressEntries().at(k).ip().toString();
                strMask=oInterface.addressEntries().at(k).netmask().toString();
                astrIP.append(strIP);
                astrMask.append(strMask);
            }
        }
    }

    return astrIP.size();
}

long stt_net_set_ip(QStringList &astrIP, QStringList &astrMask, long nIPBeginIndex)
{
    if(nIPBeginIndex < 2)
    {
        nIPBeginIndex = 2; // '1'预留给DHCP，强制从'2'开始
    }
    long i = 0;
    long nCount = astrIP.size();
    QString strIP, strMask;

	for (i=0; i<nCount; i++)
    {
        strIP = astrIP.at(i);
        strMask = astrMask.at(i);
        stt_net_set_ip(nIPBeginIndex, strIP, strMask);
        nIPBeginIndex++;
    }

    return 0;
}

#endif
