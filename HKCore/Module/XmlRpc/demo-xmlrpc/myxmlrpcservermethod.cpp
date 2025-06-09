#include "stdafx.h"

#include "myxmlrpcservermethod.h"
// #include "../singleton/qtestcontrolmngr.h"
// #include<QDebug>
// #include"../protobuf/hqyPUDPara.pb.h"
// #include"../protobuf/hqyBinaryInSetting.pb.h"
// #include"../singleton/singleton.h"
// #include"../singleton/fpgadirectoper.h"
// #include"../protobuf/hqySetting.pb.h"
// #include"../protobuf/TesterOutputPara.pb.h"
// #include"../singleton/device.h"
// #include"../protobuf/CompensationPara.pb.h"
// #include "../testcontrol/qmanualtestcontrol.h"
// #include "../singleton/driveroper.h"
// #include"../testcontrol/define.h"
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <string.h>
// #include <qmath.h>

using namespace std;


Start::Start(XmlRpcServer* s):myXmlRpcServerMethod("Start", s)
{

}

void Start::execute(XmlRpcValue & params, XmlRpcValue& result,const XmlRpc::XmlRpcServerConnection* context)
{
//    int n = params.getType();
//    qDebug()<<"n yp"<<n;
    int bStart = params[0];
//    qDebug()<<"bStart----------"<<bStart;

    if(bStart==1||bStart==2){
        //QTestControlMngr::g_pTestControlMngr->Start();
    }
    else if(bStart == 0){
 //       qDebug()<<"Stop--------------";
       // QTestControlMngr::g_pTestControlMngr->Stop();
    }
    else if(bStart == 3){
        //QTestControlMngr::g_pTestControlMngr->StateNext();
    }

    XmlRpc::XmlRpcValue re(true);
    result = re;
}



TestItem::TestItem(XmlRpcServer* s):myXmlRpcServerMethod("PQTTestMethod", s)
{
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("PQTTestMethod"));
}

static long g_nCurrValue = 0;
void TestItem::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
{
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("TestItem::execute"));
    int fd = context->getfd();
    struct sockaddr_in name;
    int namelen = sizeof(name);

    if(!getpeername(fd, (struct sockaddr *)&name, &namelen))
    {
//        char buf[64];
//        inet_ntop(AF_INET,&name.sin_addr, buf,64);
//         hqyComPackage::ComSetting oComSetting;
//         oComSetting.set_strip(buf,64);
//         oComSetting.set_nport(8085);
//         Device::g_Device->setComSetting(&oComSetting);
    }

	//XmlRpcValue::BinaryData ovalue = params[0];
	std::string content =  params[0];
// 	result[0] = 3;
// 	result[1] = content;
// 	result[2] = content+content;
// 	char *pBuffer = NULL;
// 	long nLen = 0;
// 	CFile file;
// 	
// 	if (file.Open(_T("D:\\0\\XmlRpc.txt"), CFile::modeRead))
// 	{
// 		result = content;
// 		nLen = file.GetLength();
// 		 std::string* pstring = result.get_string();//._value.asString;
// 		 pstring->resize(nLen);
// 		 char *pBuffer = (char*)pstring->data();
// 		file.Read(pBuffer, nLen);
// 		file.Close();
// 	}
// 	else
	{
		char pszMaxBuff[100];
		sprintf(pszMaxBuff, "xmlrpc:[%d]", g_nCurrValue);
		g_nCurrValue++;
		result = pszMaxBuff;
	}

}

TestParaSet::TestParaSet(XmlRpcServer* s):myXmlRpcServerMethod("TestParaSet", s)
{
   CLogPrint::LogString(LOGLEVEL_TRACE, _T("TestParaSet"));
}

void TestParaSet::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
{
//     int fd = context->getfd();
//     struct sockaddr_in name;
//     size_t namelen = sizeof(name);
//     if(!getpeername(fd, (struct sockaddr *)&name, &namelen))
//     {
//         char   buf[64];
//         inet_ntop(AF_INET,&name.sin_addr, buf,64);
//         qDebug()<<"ip is "<<buf;
//         hqyComPackage::ComSetting oComSetting;
//         oComSetting.set_strip(buf,64);
//         oComSetting.set_nport(8085);
//         Device::g_Device->setComSetting(&oComSetting);
//     }
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
// //    QTestControlMngr::g_pTestControlMngr->Setpara(pChar,ovalue.size());
//     XmlRpc::XmlRpcValue re(true);
//     result = re;
//     free(pChar);
}
// 
// SetBinaryInSetting::SetBinaryInSetting(XmlRpcServer* s):myXmlRpcServerMethod("SetBinaryInSetting", s)
// {
//  //    qDebug()<<"SetBinaryInSetting\n";
// }
// 
// void SetBinaryInSetting::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     std::string strPara = params[0];
//     hqyBinaryInPackage::BinaryinSetting oSetting ;
//     if(oSetting.ParseFromString(strPara))
//   //      qDebug()<<"true";
// //    else
//   //      qDebug()<<"false";              ;
//     singleton::g_singleton->setBinaryInSetting(oSetting);
//     FpgaDirectOper::g_FpgsDirectOper->SetbinarySetting(&oSetting);
// 
//     XmlRpcValue re("success");
//     result = re;
// }
// 
// SetSetting::SetSetting(XmlRpcServer* s):myXmlRpcServerMethod("SetSetting", s)
// {
//  //    qDebug()<<"SetBinaryInSetting\n";
// }
// 
// void SetSetting::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     std::string strPara = params[0];
//     hqySettingPackage::Setting osetting;
//     osetting.ParseFromString(strPara);
//    int nType = osetting.ntype();
// //    qDebug()<<"type="<<nType;
// 
//     switch (nType) {
//     case hqySettingPackage::ST_BinarySetting :
//     {
// //        hqyBinaryInPackage::BinaryinSetting oBSetting = osetting.obinaryinsetting();
// //        singleton::g_singleton->setBinaryInSetting(oBSetting);
//   //      FpgaDirectOper::g_FpgsDirectOper->SetbinarySetting(&oBSetting);
//     }
// 
//         break;
//     case hqySettingPackage::ST_ComSetting :
//     {
//  //       hqyComPackage::ComSetting oComSetting = osetting.ocomsetting();
//   //      Device::g_Device->setComSetting(&oComSetting);
// 
//    //     qDebug()<<"ip"<<oComSetting.strip().data();
//   //      qDebug()<<"ip"<<oComSetting.nport();
//         break;
//     }
//     default:
//         break;
//     }
// 
//     qDebug()<<"this is int the SetSetting";
// 
//     XmlRpcValue re("success");
//     result = re;
// }
// 
// LockerDispel::LockerDispel(XmlRpcServer* s):myXmlRpcServerMethod("LockerDisp", s)
// {
//     qDebug()<<"LockerDispel\n";
// }
// 
// void LockerDispel::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
//     DriverOper::g_pDriverOper->setDcPowerValue(pChar);
//     XmlRpcValue re("success");
//     result = re;
//     free(pChar);
// }
// 
// DeviceInnerParaSet::DeviceInnerParaSet(XmlRpcServer* s):myXmlRpcServerMethod("DeviceinnerparaSet", s)
// {
// 
// }
// 
// void DeviceInnerParaSet::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
// 
//     qDebug()<<"in DeviceInterPara";
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
// 
//     DeviceInnerPara::DeviceInnerSetting oSetting;
//     bool bRet = oSetting.ParsePartialFromArray(pChar,ovalue.size());
//     if(!bRet){
//         qDebug()<<"parse failed!";
//         return;
//     }
//      FpgaDirectOper::g_FpgsDirectOper->SetDeviceInnerParaSet(&oSetting);
//      free(pChar);
// 
// }
// Read::Read(XmlRpcServer* s):myXmlRpcServerMethod("Read", s)
// {
// 
// }
// 
// void Read::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
// 
// }
// Write::Write(XmlRpcServer* s):myXmlRpcServerMethod("Write", s)
// {
// 
// }
// 
// void Write::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
//     free(pChar);
// 
// }
// 
// DeviceInnerParaRead::DeviceInnerParaRead(XmlRpcServer* s):myXmlRpcServerMethod("DeviceInnerParaRead", s)
// {
// 
// }
// 
// void DeviceInnerParaRead::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     char buffer[10] = {0};
//     DriverOper::g_pDriverOper->readDeviceInnerPara(buffer);
// }
// 
// ReadCompensation::ReadCompensation(XmlRpcServer* s):myXmlRpcServerMethod("ReadCompensation", s)
// {
// 
// }
// 
// void ReadCompensation::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     int nLen = Device::g_Device->getCompensationSettingSize();
//     //char* pBuffer = (char *)malloc(nLen);
//     char* pBuffer;
//     Device::g_Device->getCompensationSettingArray(pBuffer);
//     XmlRpcValue setting(pBuffer,nLen);
// 
// 
//     result = setting;
// 
// }
// 
// WriteCompensation::WriteCompensation(XmlRpcServer* s):myXmlRpcServerMethod("WriteCompensation", s)
// {
// 
// }
// 
// void WriteCompensation::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
// 
//     CmpensationConfig oSetting;
//     memcpy(&oSetting,pChar,ovalue.size());
// 
//     free(pChar);
// 
//     Device::g_Device->SetCompensationSetting(oSetting);
// }
// 
// 
// TestParaOutput::TestParaOutput(XmlRpcServer* s):myXmlRpcServerMethod("TestParaOutput", s)
// {
// 
// }
// 
// void TestParaOutput::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
// 
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
//     TesterOutputPara::AC6U6I oAc;
//     bool bRet = oAc.ParsePartialFromArray(pChar,ovalue.size());
//     if(!bRet){
//         return;
//     }
//     free(pChar);
//     TesterOutputPara::ChanelMode oChanel = oAc.ochanel();
//     hqyPudPara::TestItem oPara;
//     oPara.set_otesttype(hqyPudPara::manual_type);
//     hqyPudPara::manualpara *pManual = oPara.mutable_omanual();
//     pManual->set_sendzeroafterstop(true);
//     pManual->set_ndelaytime(30);
//     pManual->set_nisstopbichanged(0);
// 
//     hqyPudPara::acpara* pACPara =  pManual->mutable_oacpara();
//     hqyPudPara::acanalogpara* pAC = pACPara->mutable_oacanlogpara();
//     for(int i=0;i<6;i++)
//     {
//         hqyPudPara::chanelpara* p =  pAC->add_analogcurrentchanelvalue();
//         TesterOutputPara::ChanelPara oPara =  oChanel.ocurchanel(i);
//         p->set_famptitude(oPara.famptitude());
//         p->set_fphase(oPara.fphase());
//         p->set_ffre(oPara.ffre());
// 
//      }
//     for(int i=0;i<6;i++)
//     {
//         hqyPudPara::chanelpara* p =  pAC->add_analogvoltchangelvalue();
//         TesterOutputPara::ChanelPara oPara =  oChanel.ovolchanel(i);
//         p->set_famptitude(oPara.famptitude());
//         p->set_fphase(oPara.fphase());
//         p->set_ffre(oPara.ffre());
// 
//     }
//     pACPara->set_nbinaryout(0);
//     int size = oPara.ByteSize();
//     char *pchar = (char *)malloc(sizeof(char)*size);
//     oPara.SerializePartialToArray(pchar,size);
// 
//     QTestControlMngr::g_pTestControlMngr->Setpara(pchar,size,manual_type);
//     XmlRpc::XmlRpcValue re(true);
//     result = re;
//     free(pchar);
// }
// 
// PSUDifferTest::PSUDifferTest(XmlRpcServer* s):myXmlRpcServerMethod("PSUDifferTest", s)
// {
// 
// }
// 
// void PSUDifferTest::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     int fd = context->getfd();
//     struct sockaddr_in name;
//     size_t namelen = sizeof(name);
//     if(!getpeername(fd, (struct sockaddr *)&name, &namelen))
//     {
//         char buf[64];
//         inet_ntop(AF_INET,&name.sin_addr, buf,64);
//         hqyComPackage::ComSetting oComSetting;
//         oComSetting.set_strip(buf,64);
//         oComSetting.set_nport(8085);
//         Device::g_Device->setComSetting(&oComSetting);
//     }
// 
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
//     QTestControlMngr::g_pTestControlMngr->Setpara(pChar,ovalue.size(),differ_type);
//     free(pChar);
// }
// PSUDistanceTest::PSUDistanceTest(XmlRpcServer* s):myXmlRpcServerMethod("PSUDistanceTest", s)
// {
// 
// }
// 
// void PSUDistanceTest::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     int fd = context->getfd();
//     struct sockaddr_in name;
//     size_t namelen = sizeof(name);
//     if(!getpeername(fd, (struct sockaddr *)&name, &namelen))
//     {
//         char buf[64];
//         inet_ntop(AF_INET,&name.sin_addr, buf,64);
//         hqyComPackage::ComSetting oComSetting;
//         oComSetting.set_strip(buf,64);
//         oComSetting.set_nport(8085);
//         Device::g_Device->setComSetting(&oComSetting);
//     }
// 
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
//     QTestControlMngr::g_pTestControlMngr->Setpara(pChar,ovalue.size(),distance_type);
//     free(pChar);
// }
// 
// PSUSearchZBorderTest::PSUSearchZBorderTest(XmlRpcServer* s):myXmlRpcServerMethod("PSUSearchZBorderTest", s)
// {
// 
// }
// 
// void PSUSearchZBorderTest::execute(XmlRpcValue & params, XmlRpcValue& result, const XmlRpc::XmlRpcServerConnection* context)
// {
//     int fd = context->getfd();
//     struct sockaddr_in name;
//     size_t namelen = sizeof(name);
//     if(!getpeername(fd, (struct sockaddr *)&name, &namelen))
//     {
//         char buf[64];
//         inet_ntop(AF_INET,&name.sin_addr, buf,64);
//         hqyComPackage::ComSetting oComSetting;
//         oComSetting.set_strip(buf,64);
//         oComSetting.set_nport(8085);
//         Device::g_Device->setComSetting(&oComSetting);
//     }
// 
//     XmlRpcValue::BinaryData ovalue = params[0];
//     char* pChar =(char *)malloc(sizeof(char)*ovalue.size());
// 
//     for(int i=0;i<ovalue.size();i++)
//     {
//         pChar[i]= ovalue.at(i);
//     }
//     QTestControlMngr::g_pTestControlMngr->Setpara(pChar,ovalue.size(),searchzborder_type);
//     free(pChar);
// }
// 
