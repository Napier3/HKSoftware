#include "stdafx.h"
#include "../NetworkInterface.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "QNetworkInterface"

long stt_net_set_deviceip(const CString &strIP, const CString &strMask)
{
	CString strCmd;

	strCmd.Format(_T("ifconfig %s %s netmask %s up \n"), g_str_Net_DeviceName.GetString(), strIP.GetString(), strMask.GetString());
	QFile fileIp("/mnt/setip.sh");
    if(fileIp.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate))
    {
        fileIp.write(strCmd.toUtf8());
        fileIp.flush();
        fileIp.close();
        return 0;
    }

	return 1;
}

long stt_net_set_subips(const CStringArray &astrIP, const CStringArray &astrMask,long nBeginIndex)
{
    if(astrIP.GetCount() <= nBeginIndex || astrMask.GetCount() <= nBeginIndex)
        return 1;

    QFile fileIp("/mnt/setip.sh");
    if(fileIp.exists())
    {
        if(fileIp.open(QIODevice::Text|QIODevice::ReadWrite))
        {
            char pszBuf[4096];
            int nfileSize;
            nfileSize=fileIp.read(pszBuf,4096);
            CString strData(pszBuf);
            int nPos=strData.Find('\n');

            if(nPos > 0)
            {
                fileIp.seek(nPos+1);
                CString strCmd;

                long nCount = astrIP.GetCount();
                CString strIP, strMask;

                for (int i=0; i<nCount; i++)
                {
                    if((i+nBeginIndex) < nCount)
                    {
                        strIP = astrIP.GetAt(i+nBeginIndex);
                        strMask = astrMask.GetAt(i+nBeginIndex);
                        strCmd.Format(_T("ifconfig %s:%d %s netmask %s up \n"),
                                      g_str_Net_DeviceName.GetString(), i+2, strIP.GetString(), strMask.GetString());

                        fileIp.write(strCmd.toUtf8());
                    }
                }

                fileIp.flush();
                fileIp.close();
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }

    return 1;
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

void stt_net_get_deviceip_ex(CString &strIP, CString &strMask)
{
    strIP=_T("");
    strMask=_T("");

    foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
    {
        if(interface.addressEntries().size()>0)
        {
            strIP=interface.addressEntries().at(0).ip().toString();
            strMask=interface.addressEntries().at(0).netmask().toString();

            if (strIP != "127.0.0.1")
            {
                break;
            }
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

	foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
	{
        strName=interface.name();

        if(g_str_Net_DeviceName == strName)
		{
			if(interface.addressEntries().count() > 0)
			{
			strIP=interface.addressEntries().at(0).ip().toString();
			strMask=interface.addressEntries().at(0).netmask().toString();
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

	foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
	{
		strName=interface.name();
	
        if(g_str_Net_DeviceName == strName)
		{
			long nCount = interface.addressEntries().count();
		
			for (long k=0; k<nCount; k++)
			{
				strIP=interface.addressEntries().at(k).ip().toString();
				strMask=interface.addressEntries().at(k).netmask().toString();
				astrIP.Add(strIP);
//				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%d %s"),k,strIP.GetString());
				astrMask.Add(strMask);
			}
		}
	}

	return astrIP.GetCount();
}

void stt_net_get_ip(CString *IP)
{
    CString strIP, strName;

    foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
    {
        strName=interface.name();
        //CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ipname = %s"),strName.GetString());

        if(NET_DEVICENAME != strName)
        {
            if(interface.addressEntries().count() > 0)
            {
                strIP=interface.addressEntries().at(0).ip().toString();
                //CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ip = %s"),strIP.GetString());
                *IP = strIP;
                return ;
            }
        }
    }
    *IP = "127.0.0.1";
}

long stt_net_set_ip(CStringArray &astrIP, CStringArray &astrMask, long nIPBeginIndex)
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
		QString strCmd, strIP, strMask, strName;

	foreach(QNetworkInterface interface,QNetworkInterface::allInterfaces())
	{
		strName=interface.name();
	
        if(g_str_Net_DeviceName == strName)
		{
			long nCount = interface.addressEntries().count();
		
			for (long k=0; k<nCount; k++)
			{
				strIP=interface.addressEntries().at(k).ip().toString();
				strMask=interface.addressEntries().at(k).netmask().toString();
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
