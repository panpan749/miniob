#include "null_type.h"
#include <cassert>
#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/integer_type.h"
#include "common/value.h"
int NullType::compare(const Value &left, const Value &right) const
{
	return -1; // null type should not be compared
}

RC NullType::add(const Value &left, const Value &right, Value &result) const
{
	result.set_null();
	return RC::SUCCESS;
}

RC NullType::subtract(const Value &left, const Value &right, Value &result) const
{
	result.set_null();
	return RC::SUCCESS;
}

RC NullType::multiply(const Value &left, const Value &right, Value &result) const
{
	result.set_null();
	return RC::SUCCESS;
}

RC NullType::negative(const Value &val, Value &result) const
{
	result.set_null();
	return RC::SUCCESS;
}

RC NullType::to_string(const Value &val, string &result) const
{
	result = "NULL";
	return RC::SUCCESS;
}
