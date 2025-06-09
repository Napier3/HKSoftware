#ifndef SQLITE_SG_STORAGE
#define SQLITE_SG_STORAGE

#include "sgstorage.h"
#include "sqlite3.h"
#include "sqlite_orm/sqlite_orm.h"

using namespace sqlite_orm;


inline auto make_storage_query(const string &dbName)
{
    return make_storage(dbName,
                        make_table("sgcb",
                                   make_column("id", &Sgcb::id, autoincrement(), primary_key()),
                                   make_column("ldname", &Sgcb::ldName, unique()),
                                   make_column("actsg", &Sgcb::actSg),
                                   make_column("editsg", &Sgcb::editSg),
                                   make_column("sgnumber", &Sgcb::sgNumber),
                                   make_column("latime", &Sgcb::laTime)),
                        make_table("sgrawvalue",
                                   make_column("id", &SgRawValue::id, autoincrement(), primary_key()),
                                   make_column("ldname", &SgRawValue::ldName),
                                   make_column("reference", &SgRawValue::reference),
                                   make_column("valuetype", &SgRawValue::valueType),
                                   make_column("value", &SgRawValue::value),
                                   make_column("sgnumber", &SgRawValue::sgNumber)));
}

class SqliteSgStorage : public SgStorage
{
public:
    SqliteSgStorage(const string &filePath);

    virtual void selectActiveSg(const string &ldName, uint8_t actSg, uint64_t laTime) override;
    virtual bool insertSgcb(const string &ldName, uint8_t actSg, uint8_t editSg, uint8_t sgNumber, uint64_t laTime) override;
    virtual void getAllSgcbValues(vector<Sgcb> &sgcbs) override;
    virtual void getSgValues(const string &ldName, uint8_t editSg, SgValueVec &valueVec) override;
    virtual void selectEditSg(const string &ldName, uint8_t editSg) override;
    virtual void setEditSgValue(const SgValue &value) override;
    virtual void getSgValues(const string &ldName, uint8_t editSg, vector<GspMmsValue *> &values) override;
    virtual void setEditSgValues(const string &ldName, uint8_t editSg, const SgValueVec &valueVec) override;

private:
    sqlite3 *_db = nullptr;
    sqlite3_stmt *_insertSgcbStmt = nullptr;
    sqlite3_stmt *_updateActSgStmt = nullptr;

    decltype (make_storage_query(std::declval<const string &>())) _storage;
};

#endif
