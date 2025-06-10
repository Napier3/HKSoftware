#include "SttDevice.h"
#include "math.h"
#include "../../Engine/SttServerTestCtrlCntr.h"

CSttDevice *CSttDevice::g_pSttDevice=NULL;
long CSttDevice::g_nSttDeviceRef = 0;

static int g_nVChannel[6] = {4,5,0,1,3,2};
static int g_nIChannel[6] = {3,5,0,2,1,4};
ConverStruct ts;
CSttDevice::CSttDevice(QObject *parent) : QObject(parent)
{
	m_nSampPoints=4000;
	//    m_nEDVolt = V;
	//    m_nEDCurrent = A; 额定电流和电压
	m_nEDFre = 50;//50 Hz 额定频率
	CSttDriverOper::Stop();
	m_bStartTest_UserParameter=FALSE;
	otmt_Paras.init();
}

void CSttDevice::Create()
{
	g_nSttDeviceRef++;

	if (g_nSttDeviceRef == 1)
	{
		g_pSttDevice=new CSttDevice;
		g_pSttDevice->InitDevice();
		g_pSttDeviceBase=(CSttDeviceBase*)g_pSttDevice;
	}
}

void CSttDevice::Release()
{
	g_nSttDeviceRef--;

	if (g_nSttDeviceRef == 0)
	{
		delete g_pSttDevice;
		g_pSttDevice = NULL;
	}
}

void CSttDevice::InitDevice()
{
	m_fIDa = 2.5;
	InitDApara();
	m_pBianryInSetting = new hqyBinaryInPackage::BinaryinSetting;
	InitBinaryInSetting();
	SetbinarySetting(m_pBianryInSetting);
	ReadCompensation();
}

void CSttDevice::InitDApara()
{
	QFile f("/mnt/dafile.txt");
	if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return ;
	}

	QTextStream txtInput(&f);
	float vda[4];
	float ida[4];
	int i=0;
	int j=0;
	while(!txtInput.atEnd())
	{
		QString lineStr = txtInput.readLine();
		QString strTemp = lineStr.left(3);
		if(!strTemp.compare("uda"))
		{
			int nPos = lineStr.lastIndexOf("=");
			QString strValue = lineStr.right(lineStr.length()-nPos-1);
			vda[i]= strValue.toFloat();
			i++;
		}
		if(!strTemp.compare("ida"))
		{
			int nPos = lineStr.lastIndexOf("=");
			QString strValue = lineStr.right(lineStr.length()-nPos-1);
			ida[j]= strValue.toFloat();
			j++;
		}
	}
	f.close();
	uchar nByte = 0;
	DeviceDAPara oDAPara;
	oDAPara.nvolt = 0;
	oDAPara.ncurrent = 0;
	for(int i=0;i<4;i++)
	{
		nByte = vda[i]/3.3*255;
		oDAPara.nvolt |= ((uint)nByte)<<(i*8);
		qDebug()<<"volt da value"<<vda[i];
	}


	for(int i=0;i<4;i++)
	{
		nByte = ida[i]/3.3*255;
		oDAPara.ncurrent |= ((uint)nByte)<<(i*8);
		qDebug()<<"current da value"<<ida[i];
	}

	qDebug()<<QString::number(oDAPara.ncurrent,16)<<QString::number(oDAPara.nvolt,16);
	CSttDriverOper::setDeviceDaPara((char*)&oDAPara,sizeof(DeviceDAPara));
}

void CSttDevice::UpdateDApara(double params[])
{
	double fValue[4];
	for(int i =0;i<4;i++)
	{
		fValue[i] = params[i];
	}
	if(fValue[0] < 0)
	{
		ReadCompensation();
	}
	else
	{
		uchar nByte = 0;
		float vda[4] = {0,0,0,0};
		float ida[4] = {0,0,0,0};
		vda[1] = (fValue[0]*1.414-163)/82;
		ida[1] = (fValue[1]*1.414+0.6)/3.4;
		vda[0] = (fValue[2]-142)/48;

		setCurrentDa(fValue[1]);
		DeviceDAPara oDAPara;
		oDAPara.nvolt = 0;
		oDAPara.ncurrent = 0;
		for(int i=0;i<4;i++)
		{
			nByte = vda[i]/3.3*255;
			oDAPara.nvolt |= ((uint)nByte)<<(i*8);
		}

		for(int i=0;i<4;i++)
		{
			nByte = ida[i]/3.3*255;
			oDAPara.ncurrent |= ((uint)nByte)<<(i*8);
		}
		CSttDriverOper::setDeviceDaPara((char*)&oDAPara,sizeof(DeviceDAPara));
		CSttDriverOper::setInputShake(fValue[3]*10000);
	}
}

void CSttDevice::ReadCompensation()
{
	QFile f("/mnt/compensation.txt");
	if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return ;
	}

	QTextStream txtInput(&f);
	while(!txtInput.atEnd())
	{
		QString strLine = txtInput.readLine();
		QString strName = strLine.section(",",0,0);
		if(strName.contains("ua"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<4;i++)
				{
					m_fVamp[0][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fVphe[0][0] = strLine.section(",",1,1).toFloat();
				m_fVphe[0][1] = strLine.section(",",2,2).toFloat();
				m_fVphe[0][2] = strLine.section(",",3,3).toFloat();
				m_fVphe[0][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fVzero[0][0] = strLine.section(",",1,1).toFloat();
				m_fVzero[0][1] = strLine.section(",",2,2).toFloat();
				m_fVzero[0][2] = strLine.section(",",3,3).toFloat();
				m_fVzero[0][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fVampMeas[0][0] = strLine.section(",",1,1).toFloat();
				m_fVampMeas[0][1] = strLine.section(",",2,2).toFloat();
				m_fVampMeas[0][2] = strLine.section(",",3,3).toFloat();
				m_fVampMeas[0][3] = strLine.section(",",4,4).toFloat();
				m_fVampMeas[0][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fVpheMeas[0][0] = strLine.section(",",1,1).toFloat();
				m_fVpheMeas[0][1] = strLine.section(",",2,2).toFloat();
				m_fVpheMeas[0][2] = strLine.section(",",3,3).toFloat();
				m_fVpheMeas[0][3] = strLine.section(",",4,4).toFloat();
				m_fVpheMeas[0][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fVzeroMeas[0][0] = strLine.section(",",1,1).toFloat();
				m_fVzeroMeas[0][1] = strLine.section(",",2,2).toFloat();
				m_fVzeroMeas[0][2] = strLine.section(",",3,3).toFloat();
				m_fVzeroMeas[0][3] = strLine.section(",",4,4).toFloat();
				m_fVzeroMeas[0][4] = strLine.section(",",5,5).toFloat();
			}
		}
		else if(strName.contains("ub"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<4;i++)
				{
					m_fVamp[1][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fVphe[1][0] = strLine.section(",",1,1).toFloat();
				m_fVphe[1][1] = strLine.section(",",2,2).toFloat();
				m_fVphe[1][2] = strLine.section(",",3,3).toFloat();
				m_fVphe[1][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fVzero[1][0] = strLine.section(",",1,1).toFloat();
				m_fVzero[1][1] = strLine.section(",",2,2).toFloat();
				m_fVzero[1][2] = strLine.section(",",3,3).toFloat();
				m_fVzero[1][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fVampMeas[1][0] = strLine.section(",",1,1).toFloat();
				m_fVampMeas[1][1] = strLine.section(",",2,2).toFloat();
				m_fVampMeas[1][2] = strLine.section(",",3,3).toFloat();
				m_fVampMeas[1][3] = strLine.section(",",4,4).toFloat();
				m_fVampMeas[1][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fVpheMeas[1][0] = strLine.section(",",1,1).toFloat();
				m_fVpheMeas[1][1] = strLine.section(",",2,2).toFloat();
				m_fVpheMeas[1][2] = strLine.section(",",3,3).toFloat();
				m_fVpheMeas[1][3] = strLine.section(",",4,4).toFloat();
				m_fVpheMeas[1][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fVzeroMeas[1][0] = strLine.section(",",1,1).toFloat();
				m_fVzeroMeas[1][1] = strLine.section(",",2,2).toFloat();
				m_fVzeroMeas[1][2] = strLine.section(",",3,3).toFloat();
				m_fVzeroMeas[1][3] = strLine.section(",",4,4).toFloat();
				m_fVzeroMeas[1][4] = strLine.section(",",5,5).toFloat();
			}
		}
		else if(strName.contains("uc"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<4;i++)
				{
					m_fVamp[2][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fVphe[2][0] = strLine.section(",",1,1).toFloat();
				m_fVphe[2][1] = strLine.section(",",2,2).toFloat();
				m_fVphe[2][2] = strLine.section(",",3,3).toFloat();
				m_fVphe[2][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fVzero[2][0] = strLine.section(",",1,1).toFloat();
				m_fVzero[2][1] = strLine.section(",",2,2).toFloat();
				m_fVzero[2][2] = strLine.section(",",3,3).toFloat();
				m_fVzero[2][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fVampMeas[2][0] = strLine.section(",",1,1).toFloat();
				m_fVampMeas[2][1] = strLine.section(",",2,2).toFloat();
				m_fVampMeas[2][2] = strLine.section(",",3,3).toFloat();
				m_fVampMeas[2][3] = strLine.section(",",4,4).toFloat();
				m_fVampMeas[2][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fVpheMeas[2][0] = strLine.section(",",1,1).toFloat();
				m_fVpheMeas[2][1] = strLine.section(",",2,2).toFloat();
				m_fVpheMeas[2][2] = strLine.section(",",3,3).toFloat();
				m_fVpheMeas[2][3] = strLine.section(",",4,4).toFloat();
				m_fVpheMeas[2][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fVzeroMeas[2][0] = strLine.section(",",1,1).toFloat();
				m_fVzeroMeas[2][1] = strLine.section(",",2,2).toFloat();
				m_fVzeroMeas[2][2] = strLine.section(",",3,3).toFloat();
				m_fVzeroMeas[2][3] = strLine.section(",",4,4).toFloat();
				m_fVzeroMeas[2][4] = strLine.section(",",5,5).toFloat();
			}
		}
		else if(strName.contains("u0"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<4;i++)
				{
					m_fVamp[3][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fVphe[3][0] = strLine.section(",",1,1).toFloat();
				m_fVphe[3][1] = strLine.section(",",2,2).toFloat();
				m_fVphe[3][2] = strLine.section(",",3,3).toFloat();
				m_fVphe[3][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fVzero[3][0] = strLine.section(",",1,1).toFloat();
				m_fVzero[3][1] = strLine.section(",",2,2).toFloat();
				m_fVzero[3][2] = strLine.section(",",3,3).toFloat();
				m_fVzero[3][3] = strLine.section(",",4,4).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fVampMeas[3][0] = strLine.section(",",1,1).toFloat();
				m_fVampMeas[3][1] = strLine.section(",",2,2).toFloat();
				m_fVampMeas[3][2] = strLine.section(",",3,3).toFloat();
				m_fVampMeas[3][3] = strLine.section(",",4,4).toFloat();
				m_fVampMeas[3][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fVpheMeas[3][0] = strLine.section(",",1,1).toFloat();
				m_fVpheMeas[3][1] = strLine.section(",",2,2).toFloat();
				m_fVpheMeas[3][2] = strLine.section(",",3,3).toFloat();
				m_fVpheMeas[3][3] = strLine.section(",",4,4).toFloat();
				m_fVpheMeas[3][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fVzeroMeas[3][0] = strLine.section(",",1,1).toFloat();
				m_fVzeroMeas[3][1] = strLine.section(",",2,2).toFloat();
				m_fVzeroMeas[3][2] = strLine.section(",",3,3).toFloat();
				m_fVzeroMeas[3][3] = strLine.section(",",4,4).toFloat();
				m_fVzeroMeas[3][4] = strLine.section(",",5,5).toFloat();
			}
		}
		else if(strName.contains("ia"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp[0][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fIphe[0][0] = strLine.section(",",1,1).toFloat();
				m_fIphe[0][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fIzero[0][0] = strLine.section(",",1,1).toFloat();
				m_fIzero[0][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fIampMeas[0][0] = strLine.section(",",1,1).toFloat();
				m_fIampMeas[0][1] = strLine.section(",",2,2).toFloat();
				m_fIampMeas[0][2] = strLine.section(",",3,3).toFloat();
				m_fIampMeas[0][3] = strLine.section(",",4,4).toFloat();
				m_fIampMeas[0][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fIpheMeas[0][0] = strLine.section(",",1,1).toFloat();
				m_fIpheMeas[0][1] = strLine.section(",",2,2).toFloat();
				m_fIpheMeas[0][2] = strLine.section(",",3,3).toFloat();
				m_fIpheMeas[0][3] = strLine.section(",",4,4).toFloat();
				m_fIpheMeas[0][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fIzeroMeas[0][0] = strLine.section(",",1,1).toFloat();
				m_fIzeroMeas[0][1] = strLine.section(",",2,2).toFloat();
				m_fIzeroMeas[0][2] = strLine.section(",",3,3).toFloat();
				m_fIzeroMeas[0][3] = strLine.section(",",4,4).toFloat();
				m_fIzeroMeas[0][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("a1mp") )
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp1[0][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("p1he"))
			{
				m_fIphe1[0][0] = strLine.section(",",1,1).toFloat();
				m_fIphe1[0][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("z1ero"))
			{
				m_fIzero1[0][0] = strLine.section(",",1,1).toFloat();
				m_fIzero1[0][1] = strLine.section(",",2,2).toFloat();
			}
		}
		else if(strName.contains("ib"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp[1][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fIphe[1][0] = strLine.section(",",1,1).toFloat();
				m_fIphe[1][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fIzero[1][0] = strLine.section(",",1,1).toFloat();
				m_fIzero[1][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fIampMeas[1][0] = strLine.section(",",1,1).toFloat();
				m_fIampMeas[1][1] = strLine.section(",",2,2).toFloat();
				m_fIampMeas[1][2] = strLine.section(",",3,3).toFloat();
				m_fIampMeas[1][3] = strLine.section(",",4,4).toFloat();
				m_fIampMeas[1][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fIpheMeas[1][0] = strLine.section(",",1,1).toFloat();
				m_fIpheMeas[1][1] = strLine.section(",",2,2).toFloat();
				m_fIpheMeas[1][2] = strLine.section(",",3,3).toFloat();
				m_fIpheMeas[1][3] = strLine.section(",",4,4).toFloat();
				m_fIpheMeas[1][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fIzeroMeas[1][0] = strLine.section(",",1,1).toFloat();
				m_fIzeroMeas[1][1] = strLine.section(",",2,2).toFloat();
				m_fIzeroMeas[1][2] = strLine.section(",",3,3).toFloat();
				m_fIzeroMeas[1][3] = strLine.section(",",4,4).toFloat();
				m_fIzeroMeas[1][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("a1mp") )
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp1[1][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("p1he"))
			{
				m_fIphe1[1][0] = strLine.section(",",1,1).toFloat();
				m_fIphe1[1][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("z1ero"))
			{
				m_fIzero1[1][0] = strLine.section(",",1,1).toFloat();
				m_fIzero1[1][1] = strLine.section(",",2,2).toFloat();
			}
		}
		else if(strName.contains("ic"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp[2][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fIphe[2][0] = strLine.section(",",1,1).toFloat();
				m_fIphe[2][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fIzero[2][0] = strLine.section(",",1,1).toFloat();
				m_fIzero[2][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fIampMeas[2][0] = strLine.section(",",1,1).toFloat();
				m_fIampMeas[2][1] = strLine.section(",",2,2).toFloat();
				m_fIampMeas[2][2] = strLine.section(",",3,3).toFloat();
				m_fIampMeas[2][3] = strLine.section(",",4,4).toFloat();
				m_fIampMeas[2][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fIpheMeas[2][0] = strLine.section(",",1,1).toFloat();
				m_fIpheMeas[2][1] = strLine.section(",",2,2).toFloat();
				m_fIpheMeas[2][2] = strLine.section(",",3,3).toFloat();
				m_fIpheMeas[2][3] = strLine.section(",",4,4).toFloat();
				m_fIpheMeas[2][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fIzeroMeas[2][0] = strLine.section(",",1,1).toFloat();
				m_fIzeroMeas[2][1] = strLine.section(",",2,2).toFloat();
				m_fIzeroMeas[2][2] = strLine.section(",",3,3).toFloat();
				m_fIzeroMeas[2][3] = strLine.section(",",4,4).toFloat();
				m_fIzeroMeas[2][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("a1mp") )
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp1[2][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("p1he"))
			{
				m_fIphe1[2][0] = strLine.section(",",1,1).toFloat();
				m_fIphe1[2][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("z1ero"))
			{
				m_fIzero1[2][0] = strLine.section(",",1,1).toFloat();
				m_fIzero1[2][1] = strLine.section(",",2,2).toFloat();
			}
		}
		else if(strName.contains("i0"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp[3][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fIphe[3][0] = strLine.section(",",1,1).toFloat();
				m_fIphe[3][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fIzero[3][0] = strLine.section(",",1,1).toFloat();
				m_fIzero[3][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fIampMeas[3][0] = strLine.section(",",1,1).toFloat();
				m_fIampMeas[3][1] = strLine.section(",",2,2).toFloat();
				m_fIampMeas[3][2] = strLine.section(",",3,3).toFloat();
				m_fIampMeas[3][3] = strLine.section(",",4,4).toFloat();
				m_fIampMeas[3][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fIpheMeas[3][0] = strLine.section(",",1,1).toFloat();
				m_fIpheMeas[3][1] = strLine.section(",",2,2).toFloat();
				m_fIpheMeas[3][2] = strLine.section(",",3,3).toFloat();
				m_fIpheMeas[3][3] = strLine.section(",",4,4).toFloat();
				m_fIpheMeas[3][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fIzeroMeas[3][0] = strLine.section(",",1,1).toFloat();
				m_fIzeroMeas[3][1] = strLine.section(",",2,2).toFloat();
				m_fIzeroMeas[3][2] = strLine.section(",",3,3).toFloat();
				m_fIzeroMeas[3][3] = strLine.section(",",4,4).toFloat();
				m_fIzeroMeas[3][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("a1mp") )
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp1[3][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("p1he"))
			{
				m_fIphe1[3][0] = strLine.section(",",1,1).toFloat();
				m_fIphe1[3][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("z1ero"))
			{
				m_fIzero1[3][0] = strLine.section(",",1,1).toFloat();
				m_fIzero1[3][1] = strLine.section(",",2,2).toFloat();
			}
		}
		else if(strName.contains("is"))
		{
			if(strName.contains("amp") && !strName.contains("meas"))
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp[4][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("phe") && !strName.contains("meas"))
			{
				m_fIphe[4][0] = strLine.section(",",1,1).toFloat();
				m_fIphe[4][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("zero") && !strName.contains("meas"))
			{
				m_fIzero[4][0] = strLine.section(",",1,1).toFloat();
				m_fIzero[4][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("amp") && strName.contains("meas"))
			{
				m_fIampMeas[4][0] = strLine.section(",",1,1).toFloat();
				m_fIampMeas[4][1] = strLine.section(",",2,2).toFloat();
				m_fIampMeas[4][2] = strLine.section(",",3,3).toFloat();
				m_fIampMeas[4][3] = strLine.section(",",4,4).toFloat();
				m_fIampMeas[4][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("phe") && strName.contains("meas"))
			{
				m_fIpheMeas[4][0] = strLine.section(",",1,1).toFloat();
				m_fIpheMeas[4][1] = strLine.section(",",2,2).toFloat();
				m_fIpheMeas[4][2] = strLine.section(",",3,3).toFloat();
				m_fIpheMeas[4][3] = strLine.section(",",4,4).toFloat();
				m_fIpheMeas[4][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("zero") && strName.contains("meas"))
			{
				m_fIzeroMeas[4][0] = strLine.section(",",1,1).toFloat();
				m_fIzeroMeas[4][1] = strLine.section(",",2,2).toFloat();
				m_fIzeroMeas[4][2] = strLine.section(",",3,3).toFloat();
				m_fIzeroMeas[4][3] = strLine.section(",",4,4).toFloat();
				m_fIzeroMeas[4][4] = strLine.section(",",5,5).toFloat();
			}
			else if(strName.contains("a1mp") )
			{
				int nFre = strName.right(strName.size()-5).toInt();
				for(int i=0;i<2;i++)
				{
					m_fIamp1[4][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if(strName.contains("p1he"))
			{
				m_fIphe1[4][0] = strLine.section(",",1,1).toFloat();
				m_fIphe1[4][1] = strLine.section(",",2,2).toFloat();
			}
			else if(strName.contains("z1ero"))
			{
				m_fIzero1[4][0] = strLine.section(",",1,1).toFloat();
				m_fIzero1[4][1] = strLine.section(",",2,2).toFloat();
			}
		}
		else if(QString::compare("uDCooutput",strName) == 0)
		{
			m_fVDcoutput[0] = strLine.section(",",1,1).toFloat();
			m_fVDcoutput[1] = strLine.section(",",2,2).toFloat();
			m_fVDcoutput[2] = strLine.section(",",3,3).toFloat();
			m_fVDcoutput[3] = strLine.section(",",4,4).toFloat();
		}
		else if(QString::compare("uDCooutputzero",strName) == 0)
		{
			m_fVDcoutputzero[0] = strLine.section(",",1,1).toFloat();
			m_fVDcoutputzero[1] = strLine.section(",",2,2).toFloat();
			m_fVDcoutputzero[2] = strLine.section(",",3,3).toFloat();
			m_fVDcoutputzero[3] = strLine.section(",",4,4).toFloat();
		}
		else if(QString::compare("iDcinput",strName) == 0)
		{
			m_fIDcinput[0] = strLine.section(",",1,1).toFloat();
			m_fIDcinput[1] = strLine.section(",",2,2).toFloat();
			m_fIDcinput[2] = strLine.section(",",3,3).toFloat();
			m_fIDcinput[3] = strLine.section(",",4,4).toFloat();
			m_fIDcinput[4] = strLine.section(",",5,5).toFloat();
			m_fIDcinput[5] = strLine.section(",",6,6).toFloat();
			m_fIDcinput[6] = strLine.section(",",7,7).toFloat();
			m_fIDcinput[7] = strLine.section(",",8,8).toFloat();
		}
		else if(QString::compare("idcinputzero",strName) == 0)
		{
			m_fIDcinputzero[0] = strLine.section(",",1,1).toFloat();
			m_fIDcinputzero[1] = strLine.section(",",2,2).toFloat();
			m_fIDcinputzero[2] = strLine.section(",",3,3).toFloat();
			m_fIDcinputzero[3] = strLine.section(",",4,4).toFloat();
			m_fIDcinputzero[4] = strLine.section(",",5,5).toFloat();
			m_fIDcinputzero[5] = strLine.section(",",6,6).toFloat();
			m_fIDcinputzero[6] = strLine.section(",",7,7).toFloat();
			m_fIDcinputzero[7] = strLine.section(",",8,8).toFloat();
		}
		else if(QString::compare("udcinput",strName) == 0)
		{
			m_fVDcinput[0] = strLine.section(",",1,1).toFloat();
			m_fVDcinput[1] = strLine.section(",",2,2).toFloat();
			m_fVDcinput[2] = strLine.section(",",3,3).toFloat();
			m_fVDcinput[3] = strLine.section(",",4,4).toFloat();
		}
		else if(QString::compare("m_fIbig",strName) == 0)
		{
			m_fILarge[0] = strLine.section(",",1,1).toFloat();
			m_fILarge[1] = strLine.section(",",2,2).toFloat();
			m_fILarge[2] = strLine.section(",",3,3).toFloat();
			m_fILarge[3] = strLine.section(",",4,4).toFloat();
			m_fILarge[4] = strLine.section(",",5,5).toFloat();

		}
		else if(QString::compare("iDCoutput",strName) == 0)
		{
			m_fIDcoutput[0] = strLine.section(",",1,1).toFloat();
			m_fIDcoutput[1] = strLine.section(",",2,2).toFloat();
		}
		else if(QString::compare("iDCoutputzero",strName) == 0)
		{
			m_fIDcoutputzero[0] = strLine.section(",",1,1).toFloat();
			m_fIDcoutputzero[1] = strLine.section(",",2,2).toFloat();
		}
		else if (strName.contains("small"))
		{
			if (QString::compare("smallphe",strName) == 0)
			{
				for (int i =0;i<8;i++)
				{
					m_fSmallOutphe[i] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else if (QString::compare("smallzero",strName) == 0)
			{
				for (int i =0;i<8;i++)
				{
					m_fSmallOutzero[i] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
			else
			{
				int nFre = strName.right(strName.size()-7).toInt();
				int nChannel = strName.mid(5,1).toInt();
				for(int i=0;i<3;i++)
				{
					m_fSmallOut[nChannel-1][i][nFre-1] = strLine.section(",",i+1,i+1).toFloat();
				}
			}
		}
	}
	f.close();
}

//////////////////////////////////////////////////
//2020-03-26 zhoulei

hqyBinaryInPackage::BinaryInFD CSttDevice::getBinaryInFD(float fThreadHold)
{
	if(fThreadHold>600){
		return hqyBinaryInPackage::BFD_B_600V;
	}
	else if(fThreadHold>100){
		return hqyBinaryInPackage::BFD_B_600V;
	}
	else if(fThreadHold>10){
		return hqyBinaryInPackage::BFD_B_100V;
	}
	else if(fThreadHold>1){
		return hqyBinaryInPackage::BFD_B_10V;
	}
	else if(fThreadHold>0.1)
	{
		return hqyBinaryInPackage::BFD_B_1V;
	}
	else{
		return hqyBinaryInPackage::BFD_B_01V;
	}
}

int CSttDevice::getBinaryFDCode(hqyBinaryInPackage::BinaryInFD nFD)
{
	m_vBinarySetting.insert(hqyBinaryInPackage::BFD_B_10V,0x0B);
	m_vBinarySetting.insert(hqyBinaryInPackage::BFD_B_1V,0x07);
	m_vBinarySetting.insert(hqyBinaryInPackage::BFD_B_01V,0x0F);
	m_vBinarySetting.insert(hqyBinaryInPackage::BFD_B_100V,0x0D);
	m_vBinarySetting.insert(hqyBinaryInPackage::BFD_B_600V,0x0E);

	QMap<hqyBinaryInPackage::BinaryInFD,int>::iterator oter = m_vBinarySetting.find(nFD);
	if(oter != m_vBinarySetting.end()){
		return oter.value();
	}
	else
	{
		return 0x0B;
	}

}

void CSttDevice::SetbinarySetting(hqyBinaryInPackage::BinaryinSetting* pSetting)
{
	hqyBinaryInPackage::BinaryInInfo* pInfo = NULL;
	if(pSetting->obinaryinfolist_size() != 10){
		//qDebug()<<"binaryIn count is err!";
		return;
	}
	uint nFD1 = 0;
	uint nFD2 = 0;
	long lTemp1 = 0;
	unsigned short nthreadHold = 0;
	unsigned short vthreadhold[10] = {0};
	unsigned long nMode = 0;

	for(int i=0;i<pSetting->obinaryinfolist_size();i++)
	{
		pInfo = pSetting->mutable_obinaryinfolist(i);
		float fThreadHold = pInfo->fthreshold();
		hqyBinaryInPackage::BinaryInFD nBDF = getBinaryInFD(fThreadHold) ;

		int nBinaryInType = pInfo->ntype();
		switch(nBinaryInType)
		{
		case hqyBinaryInPackage::BT_EmptyMode:
		{
			nMode |= 1<<i;
			vthreadhold[i] = 0xB480;
			int nBDFCode = getBinaryFDCode(hqyBinaryInPackage::BFD_B_10V);
			if(i<8){
				nFD1 |= nBDFCode<<(i*4);
			}
			else
			{
				nFD2 |= nBDFCode<<((i-8)*4);
			}
			break;
		}
		case hqyBinaryInPackage::BT_SampleMode:
		{
			int nBDFCode = getBinaryFDCode(nBDF);

			if(i<8){
				nFD1 |= nBDFCode<<(i*4);
			}
			else
			{
				nFD2 |= nBDFCode<<((i-8)*4);
			}

			switch (nBDF) {
			case hqyBinaryInPackage::BFD_B_600V:
			{
				lTemp1 = (long)(fThreadHold / 505.1 * 0.9995002 / 2.048);
				break;
			}
			case hqyBinaryInPackage::BFD_B_100V:
			{
				lTemp1 = (long)(fThreadHold / 505.1 * 6.7540723 / 2.048);
				break;
			}
			case hqyBinaryInPackage::BFD_B_10V:
			{
				lTemp1 = (long)(fThreadHold / 505.1 * 72.2891566 / 2.048);
				break;
			}
			case hqyBinaryInPackage::BFD_B_1V:
			{
				lTemp1 = (long)(fThreadHold / 505.1 * 666.6666667 / 2.048);
				break;
			}
			case hqyBinaryInPackage::BFD_B_01V:
			{
				lTemp1 = (long)(fThreadHold / 505.1 * 2000 / 2.048);
				break;
			}
			default:
				break;
			}
			break;

			lTemp1 = (lTemp1 * 32767) + 32768;
			nthreadHold = (unsigned short)lTemp1;
			vthreadhold[i] = nthreadHold;

		}
		default:
			break;
		}

	}

	//threadhold setting
	int i=0;
	unsigned short nth = vthreadhold[i++];
	unsigned short nth2 = vthreadhold[i++];
	unsigned long ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);
	CSttDriverOper::WriteFPGAData(0x70004068,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);
	CSttDriverOper::WriteFPGAData(0x7000406C,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);
	CSttDriverOper::WriteFPGAData(0x70005068,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);
	CSttDriverOper::WriteFPGAData(0x7000506C,ns);

	nth = vthreadhold[i++];
	nth2 = vthreadhold[i++];
	ns = ((nth<<16)&0xFFFF0000)|(nth2&0xFFFF);
	CSttDriverOper::WriteFPGAData(0x70005070,ns);

	//write fd
	//sample mode
	CSttDriverOper::IoCtrl(0x108,nMode);

	//Sample gear
	CSttDriverOper::IoCtrl(0x109,nFD1);
	CSttDriverOper::IoCtrl(0x10A,nFD2);
}

void CSttDevice::InitBinaryInSetting()
{
	for(int i=0;i<10;i++)
	{
		hqyBinaryInPackage::BinaryInInfo* pInfo =  m_pBianryInSetting->add_obinaryinfolist();
		pInfo->set_ntype(hqyBinaryInPackage::BT_EmptyMode);
	}
}

void CSttDevice::SetDeviceInnerParaSet(float *fValue)
{
	uchar nByte = 0;
	float vda[4] = {0,0,0,0};
	float ida[4] = {0,0,0,0};

	vda[1] = (fValue[0]*1.414-163)/82;
	ida[1] = (fValue[1]*1.414+0.6)/3.4;
	vda[0] = (fValue[2]-142)/48;

	DeviceDAPara oDAPara;
	oDAPara.nvolt = 0;
	oDAPara.ncurrent = 0;
	for(int i=0;i<4;i++)
	{
		nByte = vda[i]/3.3*255;
		oDAPara.nvolt |= ((uint)nByte)<<(i*8);
		qDebug()<<"volt da value"<<vda[i];

		nByte = ida[i]/3.3*255;
		oDAPara.ncurrent |= ((uint)nByte)<<(i*8);
		qDebug()<<"current da value"<<ida[i];
	}

	CSttDriverOper::setDeviceDaPara((char*)&oDAPara,sizeof(DeviceDAPara));
}

void CSttDevice::TranslateACVoltBuffer(float fAmp,float fPh,float fFre,int nChanIndex, long* pBuff,int nHarmIndex)
{
	float fVoltMax=getAnalogVoltMax()*1.2;
	long nAmp,nPh,nFre;

	int nFrenum = fFre/50;
	if(nFrenum <= 1)
		nFrenum = 1;

	if(fAmp <= 70)
	{
		fAmp = fAmp*m_fVamp[nChanIndex][3][nFrenum-1];
		fPh = fPh+m_fVphe[nChanIndex][3];
	}
	else if(fAmp <= 120 && fAmp>70)
	{
		fAmp = fAmp*m_fVamp[nChanIndex][2][nFrenum-1];
		fPh = fPh+m_fVphe[nChanIndex][2];
	}
	else if(fAmp <= 300 && fAmp>120)
	{
		fAmp = fAmp*m_fVamp[nChanIndex][1][nFrenum-1];
		fPh = fPh+m_fVphe[nChanIndex][1];
	}
	else if(fAmp>300)
	{
		fAmp = fAmp*m_fVamp[nChanIndex][0][nFrenum-1]*m_fVamp[nChanIndex][1][nFrenum-1];
		fPh = fPh+m_fVphe[nChanIndex][0];
		fVoltMax = 440*1.2;
	}

	long nH = fAmp*MaxNum/fVoltMax;
	double fH = fAmp*MaxNum/fVoltMax;
	long nL = (fH - nH)*65536;
	nAmp  = ((nH<<16)&0xFFFF0000)+nL;
	nPh = fPh*MaxNum/360;
	nPh = nPh<<16;
	nH = (long)fFre*MaxNum/400000.0;
	fH = fFre*MaxNum/400000.0;
	nL = (fH - nH)*65536;
	nFre  =((nH<<16)&0xFFFF0000)+nL;

	pBuff[nHarmIndex*18+g_nVChannel[nChanIndex]*3] = nPh;
	pBuff[nHarmIndex*18+g_nVChannel[nChanIndex]*3+1] = nFre;
	pBuff[nHarmIndex*18+g_nVChannel[nChanIndex]*3+2] = nAmp;
}

void CSttDevice::TranslateACVoltBufferDC(float fAmp,int nChanIndex,long* pBuff)
{
	long nAmp = 0;
	float fVoltMax = getAnalogVoltMax()*1.2;

	if(fAmp <= 70)
	{
		fAmp = m_fVzero[nChanIndex][3]/3000;
	}
	else if(fAmp <= 120 && fAmp>70)
	{
		fAmp = m_fVzero[nChanIndex][2]/3000;
	}
	else if(fAmp <= 264 && fAmp>120)
	{
		fAmp = m_fVzero[nChanIndex][1]/3000;
	}
	else if(fAmp>264)
	{
		fAmp = m_fVzero[nChanIndex][0]/3000;
		fVoltMax = 440*1.2;
	}

	long nH = fAmp*MaxNum/fVoltMax;
	double fH = fAmp*MaxNum/fVoltMax;
	long nL = (fH - nH)*65536;
	nAmp  = ((nH<<16)&0xFFFF0000)+nL;
	pBuff[g_nVChannel[nChanIndex]] = nAmp;
}

void CSttDevice::TranslateACCurrentBuffer(float fAmp,float fPh,float fFre,int nChanIndex, long* pBuff,int nHarmIndex)
{
	float fCurrentMax =  getAnalogCurrentMax()*1.2;
	long nAmp,nPh,nFre;
	fFre = fFre;
	int nFrenum = fFre/50;
	if(nFrenum <=1)
		nFrenum = 1;

	if(fAmp <= 1.2)
	{
		fAmp = fAmp*m_fIamp[nChanIndex][1][nFrenum-1];
		fPh = fPh+180+m_fIphe[nChanIndex][1];
	}
	else if(fAmp>1.2 && fAmp<= 5)
	{
		fAmp = fAmp*m_fIamp[nChanIndex][0][nFrenum-1];
		fPh = fPh+180+m_fIphe[nChanIndex][0];
	}
	else if(fAmp>5)
	{
		fAmp = fAmp*m_fIamp[nChanIndex][0][nFrenum-1]-fAmp*m_fIamp[nChanIndex][0][nFrenum-1]*qPow(fAmp-5,2)*(m_fILarge[nChanIndex]-1)/25;
		fPh = fPh+180+m_fIphe[nChanIndex][0];
	}

	if(fPh>=360)
	{
		fPh=fPh-360;
	}

	long nH = fAmp*MaxNum/fCurrentMax;
	double fH = fAmp*MaxNum/fCurrentMax;
	long nL = (fH - nH)*65536;
	nAmp  = ((nH<<16)&0xFFFF0000)+nL;
	nPh = fPh*MaxNum/360;
	nPh = nPh<<16;
	nH = (long)fFre*MaxNum/400000.0;
	fH = fFre*MaxNum/400000.0;
	nL = (fH - nH)*65536;
	nFre  =((nH<<16)&0xFFFF0000)+nL;

	pBuff[nHarmIndex*18+g_nIChannel[nChanIndex]*3] = nPh;
	pBuff[nHarmIndex*18+g_nIChannel[nChanIndex]*3+1] = nFre;
	pBuff[nHarmIndex*18+g_nIChannel[nChanIndex]*3+2] = nAmp;
}

void CSttDevice::TranslateACCurrentBufferDC(float fAmp,int nChanIndex,long* pBuff)
{
	float fCurrentMax =  getAnalogCurrentMax()*1.2;
	long nAmp = 0;
	if(fAmp <= 1.2)
	{
		fAmp = m_fIzero[nChanIndex][1]/3000;
	}
	else if(fAmp>1.2 && fAmp<= 5)
	{
		fAmp = m_fIzero[nChanIndex][0]/3000;
	}
	else if(fAmp>5)
	{
		fAmp = m_fIzero[nChanIndex][0]/3000;
	}

	long nH = fAmp*MaxNum/fCurrentMax;
	double fH = fAmp*MaxNum/fCurrentMax;
	long nL = (fH - nH)*65536;
	nAmp  = ((nH<<16)&0xFFFF0000)+nL;
	pBuff[g_nIChannel[nChanIndex]] = nAmp;
}

long CSttDevice::TRanslateDcVolt(float fVDc)
{
	long fTemp = fVDc*1000000;
	if(fTemp<=120000)
	{
		float fTmp = (fVDc*m_fVDcoutput[3]-m_fVDcoutputzero[3])/-0.12;
		float fValue = qPow(2,31)*fTmp;
		long nValue = fValue;
		CSttDriverOper::setDCoutput(nValue);
	}
	else if(fTemp <= 1200000 && fTemp > 120000)
	{
		float fTmp = (fVDc*m_fVDcoutput[2]-m_fVDcoutputzero[2])/-1.2;
		float fValue = qPow(2,31)*fTmp;
		long nValue = fValue;
		CSttDriverOper::setDCoutput(nValue);
	}
	else if(fTemp <= 12000000 && fTemp >1200000)
	{
		float fTmp = (fVDc*m_fVDcoutput[1]-m_fVDcoutputzero[1])/-12;
		float fValue = qPow(2,31)*fTmp;
		long nValue = fValue;
		CSttDriverOper::setDCoutput(nValue);
	}
	else if(fTemp > 12000000)
	{
		float fTmp = (fVDc*m_fVDcoutput[0]-m_fVDcoutputzero[0])/300;
		float fValue = qPow(2,31)*fTmp;
		long nValue = fValue;
		CSttDriverOper::setDCoutput(nValue);
	}
}

void CSttDevice::TranslateDCCurrent(float fCurrent,long* pBuff)
{
	if(fCurrent<1.2)
	{
		float fTmp = (fCurrent*m_fIDcoutput[1]+m_fIDcoutputzero[1])/(2.3*1.2*1.2);
		int fValue = 0x100000000*fTmp;
		pBuff[3] = fValue;
	}
	else
	{
		float fTmp = (fCurrent*m_fIDcoutput[0]+m_fIDcoutputzero[0])/(20*1.2*1.7);
		int fValue = 0x100000000*fTmp;
		pBuff[3] = fValue;
	}
}

BOOL CSttDevice::SetParameter(CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize(&otmt_Paras,pXmlSierialize);

	//设置电源功率
	if(otmt_Paras.m_bLargeCurrent)
		setCurrentDa(7.5);
	else
		setCurrentDa(2.5);

	float fDAValue[3]  ={300,0,300};
	fDAValue[1] = getCurrentDa();
	SetDeviceInnerParaSet(fDAValue);

	int nTap=0x180;
	int nDCTap=0;
	long nTemp = fabs(otmt_Paras.m_fVolAux)*1000000;
	if(nTemp<=120000)
	{
		nDCTap =1<<4;
	}
	else if(nTemp<=1200000 && nTemp>120000)
	{
		nDCTap=1<<5;
	}
	else if(nTemp<=12000000 && nTemp>1200000)
	{

	}
	else if(nTemp>12000000)
	{
		nDCTap=1<<6;
	}
	nTap|=nDCTap;
	CSttDriverOper::setOutPutTap(nTap);

	TRanslateDcVolt(fabs(otmt_Paras.m_fVolAux));
	m_bStartTest_UserParameter=otmt_Paras.m_bKeepLoad;

	if(m_bStartTest_UserParameter)
	{
		memset(&m_oDrvManuPara,0,sizeof(Drv_ManuPara));
		m_oDrvManuPara.moduleCount = 2;
		Drv_ManuAnalogPara Voltanal,Curanal;
		memset(&Voltanal,0,sizeof(Drv_ManuAnalogPara));
		Voltanal.module = 0;
		memset(&Curanal,0,sizeof(Drv_ManuAnalogPara));
		Curanal.module = 1;

		float fre=otmt_Paras.m_uiVOL[0].Harm[1].fFreq;

		for(int i=0;i<4;i++)
		{
			if(otmt_Paras.m_uiVOL[i].Harm[1].fAmp>300)
				otmt_Paras.m_uiVOL[i].Harm[1].fAmp=300;

			if(otmt_Paras.m_uiCUR[i].Harm[1].fAmp>20)
				otmt_Paras.m_uiCUR[i].Harm[1].fAmp=20;

			TranslateACVoltBuffer(otmt_Paras.m_uiVOL[i].Harm[1].fAmp
					,otmt_Paras.m_uiVOL[i].Harm[1].fAngle,otmt_Paras.m_uiVOL[i].Harm[1].fFreq,
					i,Voltanal.dat+6);

			TranslateACCurrentBuffer(otmt_Paras.m_uiCUR[i].Harm[1].fAmp
					,otmt_Paras.m_uiCUR[i].Harm[1].fAngle,otmt_Paras.m_uiCUR[i].Harm[1].fFreq,
					i,Curanal.dat+6);

			//TranslateACVoltBufferDC(otmt_Paras.m_uiVOL[i].Harm[1].fAmp,i,Voltanal.nDc);
			//TranslateACCurrentBufferDC(otmt_Paras.m_uiCUR[i].Harm[1].fAmp,i,Curanal.nDc);
			TranslateACVoltBufferDC(otmt_Paras.m_uiVOL[i].Harm[1].fAmp,i,Voltanal.dat);
			TranslateACCurrentBufferDC(otmt_Paras.m_uiCUR[i].Harm[1].fAmp,i,Curanal.dat);

			fre=qMin(fre,otmt_Paras.m_uiVOL[i].Harm[1].fFreq);
			fre=qMin(fre,otmt_Paras.m_uiCUR[i].Harm[1].fFreq);
		}

		if(fre==0)
			fre=50;

		m_oDrvManuPara.sample = 40000/fre;

		CSttDriverOper::setMeasTap(4);
		int nBo=0;
		for (int i=0; i<8; i++)//bo
		{
			nBo += ((otmt_Paras.m_binOut[i].nState)<<i);
		}
		CSttDriverOper::setOutPutStatue(nBo);

		setTap();

		m_oDrvManuPara.stAlg[0] = Voltanal;
		m_oDrvManuPara.waveCount[0] = 6+3*6*31;
		m_oDrvManuPara.stAlg[1] = Curanal;
		m_oDrvManuPara.waveCount[1] = 6+3*6*31;

		StartTest_UserParameter();
	}
	else
	{
		CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
		if(pCurrTest==NULL||pCurrTest->IsTestFinished(0))
			CSttDriverOper::Stop();
	}
}

BOOL CSttDevice::IsStartTest_UserParameter()
{
	return m_bStartTest_UserParameter;
}

void CSttDevice::StartTest_UserParameter()
{
	CSttDriverOper::setManualAcAnalogPara((char*)&m_oDrvManuPara,sizeof(Drv_ManuPara));
	float fDAValue[3]  ={300,0,300};
	fDAValue[1] = getCurrentDa();
	SetDeviceInnerParaSet(fDAValue);
	setTap();
	CSttDriverOper::Start(1);
}

void CSttDevice::setTap()
{
	int nTap = 0;
	int nUtap = 0;

	for(int i=0;i<4;i++)
	{
		if(otmt_Paras.m_uiVOL[i].Harm[1].fAmp > 300)
			nUtap |= 1<<i;
	}
	int nItap = 128;
	int nDCTap=0x100;

	long nTemp = otmt_Paras.m_fVolAux*1000000;
	if(nTemp<=120000)
	{
		nDCTap =1<<4;
	}
	else if(nTemp<=1200000 && nTemp>120000)
	{
		nDCTap=1<<5;
	}
	else if(nTemp<=12000000 && nTemp>1200000)
	{

	}
	else if(nTemp>12000000)
	{
		nDCTap=1<<6;
	}

	nTap |= nUtap;
	nTap |= nItap;
	nTap |= nDCTap;

	CSttDriverOper::setOutPutTap(nTap);
}

void CSttDevice::CloseDevice()
{
	TRanslateDcVolt(0);
	CSttDriverOper::Stop();
}
