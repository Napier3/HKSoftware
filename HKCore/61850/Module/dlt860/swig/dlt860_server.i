%module(directors="1") dlt860_server

%{
#include "libdlt860_define.h"
#include "dlt860_model.h"
#include "gsp_mms_server.h"
#include "gsp_mms_value.h"
#include "mms_mapping.h"
#include "ied_server_private.h"
#include "dlt860_server_interface.h"
#include "modelgenerator.h"
#include "dlt860_server.h"
#include "mms_server_libinternal.h"
#include "mms_server_internal.h"
#include "dlt860_common.h"
#include "mms_service_table.h"
#include "mms_server_func.h"

%} 

%feature("director") ConnectionCallBackWrapper;
%feature("director") DataCallBackWrapper;


%inline %{
struct ConnectionCallBackWrapper
{
public:
    virtual void handle(GspIedServer self, GspClientConnection connection, bool connected, void* parameter) = 0;
    virtual ~ConnectionCallBackWrapper() {}
};  
struct DataCallBackWrapper
{
public:
    virtual void handle(const char *addr, const char *data, int type) = 0;
    virtual ~DataCallBackWrapper() {}
};   
%}

%{
static ConnectionCallBackWrapper *connect_ptr = NULL;
static DataCallBackWrapper *datacb_ptr = NULL;

static void connect_helper(GspIedServer self, GspClientConnection connection, bool connected, void* parameter)
{
    connect_ptr->handle(self, connection, connected, parameter);
}

static void data_helper(const char *addr, const char *data, int type)
{
    datacb_ptr->handle(addr, data, type);
}
%} 
 
%inline %{
void iedserver_reg_conn_cb(GspIedServer self, ConnectionCallBackWrapper *handler, void *param)
{
    connect_ptr = handler;
    GspIedServer_setConnectionIndicationHandler(self, connect_helper, param);
}    
void iedserver_reg_data_cb(GspIedServer self, DataCallBackWrapper *handler)
{
    datacb_ptr = handler;
    setDataDumpHandler(data_helper);
}    
%}

%feature("director") ConnectionCallBackWrapper;

%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "stdint.i"
using std::string;
using std::vector;
using std::map;

%include "libdlt860_define.h"
%include "dlt860_model.h"

namespace std {
    %template(ModelVector) vector<GspIedModel *>;
    %template(StrVector) vector<string>;
    %template(str_data_map) map<string, Data_t *>;
    %template(str_data_map_vec) vector<map<string, Data_t *> >;
    %template(str_data_pair_vec) vector<pair<string, Data_t *> >;
} 

%{
namespace swig{
    template <> struct traits<Data>
    {
        typedef pointer_category category;
        static const char* type_name()
        {
            return "Data";
        }
    }; 
}
%}
 
%include "gsp_mms_server.h"
%include "gsp_mms_value.h"
%include "mms_mapping.h"
%include "ied_server_private.h"
%include "dlt860_server_interface.h"
%include "modelgenerator.h" 
%include "dlt860_server.h" 
%include "dlt860_common.h" 
%include "mms_server_libinternal.h"
%include "mms_server_internal.h"
%include "mms_service_table.h"
%include "mms_server_func.h"
%define %dlt860_pointer_cast(TYPE1,TYPE2,NAME)
%inline %{
TYPE2 NAME(TYPE1 x) {
    return (TYPE2)x;
}  
  
%}
%enddef

%dlt860_pointer_cast(sGspModelNode*, sGspDataAttribute *, gmn_to_gda);
%dlt860_pointer_cast(sGspModelNode*, sGspLogicalDevice*, gmn_to_gld);
%inline %{
GspIedModel *modelss_get(GspIedModel **modelss, int i)
{
    return modelss[i];
} 
 
GspIedModel **modelss_get_ptr(vector<GspIedModel*> *modelss)
{
    if(modelss)
        return modelss->data();
    else
    {
        return NULL;
    }
}
%} 

