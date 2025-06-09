#ifndef _DvmXmlRpcValue_h
#define _DvmXmlRpcValue_h

#include "..\..\DataMngr\DataGroup.h"
#include "..\..\DataMngr\DvmLogicDevice.h"
#include "..\XmlRpc.h"

void InitAtsSmBuffer(CString strSmFile);

void Dvm_To_XmlRpcValue(CDvmData *pData,XmlRpc::XmlRpcValue &oValue);
void Dvm_To_XmlRpcValue(CDvmDataset *pDataset,XmlRpc::XmlRpcValue &oValue);
void Dvm_To_XmlRpcValue(CDataGroup *pGroup,XmlRpc::XmlRpcValue &oValue);
void Dvm_To_XmlRpcValue(CDvmLogicDevice *pLogicDevice,XmlRpc::XmlRpcValue &oValue);

void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDvmData &oData);
void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDvmDataset &oDataset);
void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDataGroup &oGroup);
void XmlRpcValue_To_Dvm(XmlRpc::XmlRpcValue &oValue, CDvmLogicDevice &oLogicDevice);

#endif