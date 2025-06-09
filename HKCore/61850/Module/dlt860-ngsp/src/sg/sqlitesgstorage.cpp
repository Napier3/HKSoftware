#include "sqlitesgstorage.h"
#include "nlogging.h"
#include <stdexcept>
#include <cstring>
#include <string>
#include "sqlite_orm/sqlite_orm.h"
#include "gspMmsValue.h"

using namespace gsp;

using namespace std;

inline void checkRc(int rc, int expire = SQLITE_OK, const char *msg = "")
{
    if(rc != expire)
        throw runtime_error(msg);
}

SqliteSgStorage::SqliteSgStorage(const string &filePath) : SgStorage(filePath)
  , _storage(make_storage_query(filePath.c_str()))
{
    _storage.sync_schema(true);
}

void SqliteSgStorage::selectActiveSg(const string &ldName, uint8_t actSg, uint64_t laTime)
{
    _storage.update_all(sqlite_orm::set(c(&Sgcb::actSg) = actSg,
                            c(&Sgcb::laTime) = laTime),
                        where(c(&Sgcb::ldName) == ldName));
}

bool SqliteSgStorage::insertSgcb(const string &ldName, uint8_t actSg, uint8_t editSg, uint8_t sgNumber, uint64_t laTime)
{
    auto ret = _storage.get_all_pointer<Sgcb>(where(c(&Sgcb::ldName) == ldName));
    if(ret.empty())
    {
        //NLOG_DEBUG("初始化定值数据, {}, actsg {}, editsg {}, sgnumber {}, latime {}", ldName, actSg, editSg, sgNumber, laTime);
        Sgcb sgcb{-1, ldName, actSg, editSg, sgNumber, laTime};
        _storage.insert(sgcb);
        return true;
    }
    return false;
}

void SqliteSgStorage::getAllSgcbValues(vector<Sgcb> &sgcbs)
{
    sgcbs = _storage.get_all<Sgcb>();
}

void SqliteSgStorage::getSgValues(const string &ldName, uint8_t editSg, SgValueVec &valueVec)
{
    auto ret = _storage.get_all_pointer<SgRawValue>(where(c(&SgRawValue::sgNumber) == editSg and c(&SgRawValue::ldName) == ldName));
    if(ret.empty())
    {
        NLOG_DEBUG("获取{}，{}定值数据为空!", ldName, editSg);
    }
    else
    {
        for(auto &item : ret)
        {
            SgValue value;
            value.reference = item->reference;
            value.value = Value::unserialize(item->value);
            valueVec.push_back(value);
        }
    }
}

void SqliteSgStorage::selectEditSg(const string &ldName, uint8_t editSg)
{
    _storage.update_all(sqlite_orm::set(c(&Sgcb::editSg) = editSg),
                        where(c(&Sgcb::ldName) == ldName));
}

void SqliteSgStorage::setEditSgValue(const SgValue &value)
{
    CharVec rawData;
    Value::serialize(value.value, rawData);
    _storage.update_all(sqlite_orm::set(c(&SgRawValue::value) = rawData),
                        where(c(&SgRawValue::reference) == value.reference));
}

void SqliteSgStorage::getSgValues(const string &ldName, uint8_t editSg, vector<GspMmsValue *> &values)
{

}

void SqliteSgStorage::setEditSgValues(const string &ldName, uint8_t editSg, const SgValueVec &valueVec)
{
    _storage.begin_transaction();

    for(auto &item : valueVec)
    {
        CharVec bin;
        SgRawValue value{-1, ldName, item.reference, 0, {} , editSg};
        Value::serialize(item.value, value.value);
        auto ret = _storage.get_all_pointer<SgRawValue>(
            where(c(&SgRawValue::sgNumber) == editSg 
                and c(&SgRawValue::ldName) == ldName
                and c(&SgRawValue::reference) == item.reference));
        if(ret.empty())
        {
            NLOG_DEBUG("获取{}，{}定值数据为空!", ldName, editSg);
            _storage.insert(value);
        }
        else
        {
            value.id = ret.at(0).get()->id;
            _storage.update(value);
        }
    }
    _storage.commit();
}
