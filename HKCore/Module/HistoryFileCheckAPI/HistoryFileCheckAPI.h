#pragma once
#include "..\..\..\Module\MemBuffer\BufferBase.h"

CString GetEncodingValueFromXML(const CString &strBuff);
BOOL find_child_puginode(pugi::xml_node &oRoot,pugi::xml_node &oChildNode,CString strChildNodeName,CString strChildAttrName1,CString strChildAttrName2);
BOOL find_pugiattr(pugi::xml_node &oNode,pugi::xml_attribute &oAttr,CString strAttrName,CString strAttrValue);
BOOL check_decimal_format(const CString &strDecimal);
BOOL check_hex_format(const CString &strHex);
BOOL check_decimal_DoublePoint_format(const CString &strDecimal);
BOOL check_binary_format(const CString &strDecimal);
BOOL check_XML_SOE_date_format(const CString &strDate);
BOOL check_soe_msg_date(const CString &strDate);
void get_line_from_filebuf(CBufferBase *pFileBuf ,CString &strLineMsg);
BOOL check_soe_msg_header(const CString &strLineMsg,CString &strTmp1,CString &strTmp2,CString &strTmp3);
BOOL check_soe_msg_deviceID(const CString &strLineMsg,CString &strTmp1,CString &strTmp2,CString &strTmp3);
BOOL check_soe_msg_body(const CString &strLineMsg,CString &strTmp1,CString &strTmp2,CString &strTmp3,CString &strTmp4);