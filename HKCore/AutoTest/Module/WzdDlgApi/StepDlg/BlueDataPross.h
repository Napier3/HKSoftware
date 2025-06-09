#pragma once

#include "../../BlueTooth/Module/BlueTooth/BtSmartTestEventInterface.h"
#include "../../BlueTooth/Module/BlueTooth/BlueToothService.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../SttStudio/Module/SttCmd/SttParas.h"
#include "../../../AutoTest/Module/XSmartTestClient.h"
#include "../../../Module/xml/json/CJSON.h"

class CBlueDataPross :
	public CBlueToothService
{
public:
	CBlueDataPross(void);
	~CBlueDataPross(void);

public:
	virtual CString GetClassID() {    return BTMNGRCLASSID_JINANXINGLONG;   }

	void OpenBlueToothServer();
	void CloseBlueToothServer();

	void HandleClientCommand(BYTE *strCmmd);

private:
	CString     m_strFileListName;
	long        m_lSeekPos;//当前游标位置，每次从头开始移动
	long		m_nFileLength;
	CFile		m_oFile;

	CDataGroup m_oTemplateMap;
	CDataGroup m_oDeviceInfo;
	CSttParas *m_pParas;

	void ProssRecv0x81Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x85Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x87Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x90Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x91Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x92Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x94Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x97Data(BYTE *strCmmd, int nDataLen);
	void ProssRecv0x98Data(BYTE *strCmmd, int nDataLen);
};
