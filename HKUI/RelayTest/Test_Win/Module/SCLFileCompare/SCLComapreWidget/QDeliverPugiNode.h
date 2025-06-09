#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/xml/PugiXML/pugixml.hpp"


class QDeliverPugiNode :public CExBaseList
{
public:
	QDeliverPugiNode(void);
	~QDeliverPugiNode(void);

	pugi::xml_node_struct* m_pSourNode;
	pugi::xml_node_struct* m_pCompNode;
	long m_nType;// 0 标识相同  ；2 标识删除 ； 4 标识新增 ；  6 标识修改 ；
};
