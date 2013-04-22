#pragma once


#include <libpq-fe.h>


#define DBTRACE_ERROR(sqlDatabase,...) sqlDatabase->SetErrorInfo(__VA_ARGS__);

NS_CH_BEG

class PgRecordField;
class PgRecord;
class PgRecordSet;
class PgRecordTable;
class PgSqlDatabase;

NS_CH_END

#include "TableParse.h"

#include "PgSql/PgRecordField.h"
#include "PgSql/PgRecord.h"
#include "PgSql/PgRecordSet.h"
#include "PgSql/PgRecordTable.h"
#include "PgSql/PgSqlDatabase.h"

//common

