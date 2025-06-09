#pragma once

#include "../../../Module/BaseClass/BaseObject.h"
#include "../../../Module/DataMngr/DataTypes.h"

#define SCLCLASSID_BASECLASS                   (CLASSID_BASECLASS + 0X10050000)

#define SCLCLASSID_CSCLFILEROOT             (SCLCLASSID_BASECLASS + 0X00000000)
#define SCLCLASSID_CSCLFILETEMPLATES        (SCLCLASSID_BASECLASS + 0X00000001)
#define SCLCLASSID_CSCLFILELNODETYPET       (SCLCLASSID_BASECLASS + 0X00000002)
#define SCLCLASSID_CSCLFILEDOTYPE           (SCLCLASSID_BASECLASS + 0X00000003)
#define SCLCLASSID_CSCLFILEDATYPE           (SCLCLASSID_BASECLASS + 0X00000004)
#define SCLCLASSID_CSCLFILEENUMTYPE         (SCLCLASSID_BASECLASS + 0X00000005)

#define SCLCLASSID_CSCLFILE_DODETAIL        (SCLCLASSID_BASECLASS + 0X00000006)
#define SCLCLASSID_CSCLFILE_DADETAIL        (SCLCLASSID_BASECLASS + 0X00000007)
#define SCLCLASSID_CSCLFILE_SDODETAIL       (SCLCLASSID_BASECLASS + 0X00000008)
#define SCLCLASSID_CSCLFILE_BDADETAIL       (SCLCLASSID_BASECLASS + 0X00000009)
#define SCLCLASSID_CSCLFILE_ENUMDETAIL      (SCLCLASSID_BASECLASS + 0X0000000A)

#define SCLCLASSID_CSCLFILE_LDEVICE         (SCLCLASSID_BASECLASS + 0X0000000B)
#define SCLCLASSID_CSCLFILE_DATASET         (SCLCLASSID_BASECLASS + 0X0000000C) 
#define SCLCLASSID_CSCLFILE_CDC             (SCLCLASSID_BASECLASS + 0X0000000D)
#define SCLCLASSID_CSCLFILELNODETYPE        (SCLCLASSID_BASECLASS + 0X0000000E)
#define SCLCLASSID_CSCLFILE_DOTVALUE        (SCLCLASSID_BASECLASS + 0X0000000F)

#define SCLCLASSID_CCHECKOBJECTSSET             (SCLCLASSID_BASECLASS + 0X00000010)
#define SCLCLASSID_CSCHEMACHECKS                (SCLCLASSID_BASECLASS + 0X00000011)
#define SCLCLASSID_CCHECKOBJECT                 (SCLCLASSID_BASECLASS + 0X00000012)
#define SCLCLASSID_CDLT860MODELCHECKS           (SCLCLASSID_BASECLASS + 0X00000013)
#define SCLCLASSID_CPROJAPPMODELCHECKS          (SCLCLASSID_BASECLASS + 0X00000014)
#define SCLCLASSID_CVIRLOOPCHECKS               (SCLCLASSID_BASECLASS + 0X00000015)
#define SCLCLASSID_SCHEMACCHECKOBJECT           (SCLCLASSID_BASECLASS + 0X00000016)
#define SCLCLASSID_CCHECKPATHS                  (SCLCLASSID_BASECLASS + 0X00000017)
#define SCLCLASSID_SINGLEPATH                   (SCLCLASSID_BASECLASS + 0X00000018)

#define SCLCLASSID_ADDTEMPLATESFILES            (SCLCLASSID_BASECLASS + 0X00000019)
#define SCLCLASSID_ADDTEMPLATESDATATYPES        (SCLCLASSID_BASECLASS + 0X0000001A)
#define SCLCLASSID_ADDTEMPLATESELEMENT          (SCLCLASSID_BASECLASS + 0X0000001B)
#define SCLCLASSID_ADDTEMPLATESFILE             (SCLCLASSID_BASECLASS + 0X0000001C)


class CSclCheckMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CSclCheckMngrXmlRWKeys();
	virtual ~CSclCheckMngrXmlRWKeys();
	static long g_nDataTypeTemRef;

public:
	static CSclCheckMngrXmlRWKeys* g_pXmlKeys;
	static CSclCheckMngrXmlRWKeys* Create();
	static void Release();
public:
	BSTR m_strCSCLKey; //SCL
	BSTR m_strCDataTypeTmpsKey; //DataTypeTemplates
	BSTR m_strCLNodeTypeTKey; //LNodeTypeT
	BSTR m_strCLNodeTypeKey; //LNodeType
	BSTR m_strCDOTypeKey; //DOType
	BSTR m_strCDATypeKey; //DAType
	BSTR m_strCEnumTypeKey; //EnumType

	BSTR m_strCDOValueKey; //DO
	BSTR m_strCDOTValueKey; //DOt
	BSTR m_strCDAValueKey; //DA
	BSTR m_strCSDOValueKey; //SDO
	BSTR m_strCBDAValueKey; //BDA
	BSTR m_strCEnumValKey; //EnumVal

	BSTR m_strLnClassKey; //lnClass
	BSTR m_strCDCKey; //cdc

	BSTR m_strMopKey; //mop

	BSTR m_strDchgKey; //dchg
	BSTR m_strBTypeKey; //bType
	BSTR m_strFCKey; //fc
	BSTR m_strQchgKey; //qchg

	BSTR m_strOrdKey; //ord
	BSTR m_strTypeKey; //type
	BSTR m_strValueKey; //Val
	BSTR m_strVertionKey; //vertion
	BSTR m_strMethodKey; //method

	BSTR m_strCLDeviceKey; //LDevice
	BSTR m_strCDataSetKey; //DataSet
	BSTR m_strCCDCKey; //CDC
	BSTR m_strDescKey; //desc  
	BSTR m_strBrcbnameKey; //brcbname 
	BSTR m_strLcbnameKey; //lcbname 
	BSTR m_strTransientKey; //transient 

	BSTR m_strPrivateMSGKey; //privateMSG

	BSTR m_strCSclCheckObjectsSetKey; //all-checks
	BSTR m_strCSchemaChecksKey; //schema-checks
	BSTR m_strCDLT860ModelChecksKey; //DLT860Modol-checks
	BSTR m_strCProjAppModelChecksKey; //ProjAppModel-checks
	BSTR m_strCVirLoopChecksKey; //virloop-checks
	BSTR m_strCCheckObjectKey; //check-object
	BSTR m_strCSchemaObjectKey; //schema-object

	BSTR m_strChoseKey; //chose
	BSTR m_strPathKey; //path

	BSTR m_strCCheckPathsKey;//check-paths
	BSTR m_strCSinglePathKey;//single-path

public:
	static BSTR CSCLKey()  {   return g_pXmlKeys->m_strCSCLKey;  }
	static BSTR CDataTypeTmpsKey()  {   return g_pXmlKeys->m_strCDataTypeTmpsKey;  }

	static BSTR CLNodeTypeTKey()  {   return g_pXmlKeys->m_strCLNodeTypeTKey;  }
	static BSTR CLNodeTypeKey()  {   return g_pXmlKeys->m_strCLNodeTypeKey;  }
	static BSTR CDOTypeKey()  {   return g_pXmlKeys->m_strCDOTypeKey;  }
	static BSTR CDATypeKey()  {   return g_pXmlKeys->m_strCDATypeKey;  }
	static BSTR CEnumTypeKey()  {   return g_pXmlKeys->m_strCEnumTypeKey;  }

	static BSTR CDOValueKey()  {   return g_pXmlKeys->m_strCDOValueKey;  }
	static BSTR CDOTValueKey()  {   return g_pXmlKeys->m_strCDOTValueKey;  }
	static BSTR CSDOValueKey()  {   return g_pXmlKeys->m_strCSDOValueKey;  }
	static BSTR CDADValueKey()  {   return g_pXmlKeys->m_strCDAValueKey;  }
	static BSTR CBDAValueKey()  {   return g_pXmlKeys->m_strCBDAValueKey;  }
	static BSTR CEnumValKey()  {   return g_pXmlKeys->m_strCEnumValKey;  }

	static BSTR CLDeviceKey()  {   return g_pXmlKeys->m_strCLDeviceKey;  }
	static BSTR CDataSetKey()  {   return g_pXmlKeys->m_strCDataSetKey;  }
	static BSTR CCDCKey()  {   return g_pXmlKeys->m_strCCDCKey;  }

	static BSTR CSclCheckObjectsSetKey()  {   return g_pXmlKeys->m_strCSclCheckObjectsSetKey;  }
	static BSTR CSchemaChecksKey()  {   return g_pXmlKeys->m_strCSchemaChecksKey;  }
	static BSTR CDLT860ModelChecksKey()  {   return g_pXmlKeys->m_strCDLT860ModelChecksKey;  }
	static BSTR CProjAppModelChecksKey()  {   return g_pXmlKeys->m_strCProjAppModelChecksKey;  }
	static BSTR CVirLoopChecksKey()  {   return g_pXmlKeys->m_strCVirLoopChecksKey;  }
	static BSTR CCheckObjectKey()  {   return g_pXmlKeys->m_strCCheckObjectKey;  }
	static BSTR CSchemaObjectKey()  {   return g_pXmlKeys->m_strCSchemaObjectKey;  }

	static BSTR CCheckPathsKey()  {   return g_pXmlKeys->m_strCCheckPathsKey;  }
	static BSTR CSinglePathKey()  {   return g_pXmlKeys->m_strCSinglePathKey;  }
};

class CSclCheckMngrConstGlobal
{
private:
	CSclCheckMngrConstGlobal();
	virtual ~CSclCheckMngrConstGlobal();

public:
	static CSclCheckMngrConstGlobal* Create();
	static void Release();

	static CDataType* FindIecRtdDataType(const  CString &strDataTypeID);

private:
	static long g_nGlobalRef;
	static CSclCheckMngrConstGlobal *g_pGlobal;

	void InitGlobal();
	CDataTypes m_oIecRtdDataTypes;

private:
	void Init_checkObjectSetDataType();  //_T("checkObjectSetDataType");
	void Init_schemaCheckObjectSetDataType();  //_T("schemaCheckVertionType");
	void Init_schemaCheckMethodType();  //_T("schemaCheckMethodType");
};

