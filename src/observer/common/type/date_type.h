/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/sys/rc.h"
#include "common/type/data_type.h"

/**
 * @brief 日期类型
 * @ingroup DataType
 */
class DateType : public DataType
{
public:
  DateType() : DataType(AttrType::CHARS) {}

  virtual ~DateType() = default;

  int compare(const Value &left, const Value &right) const override;

  RC cast_to(const Value &val, AttrType type, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  int cast_cost(AttrType type) override;

  RC to_string(const Value &val, string &result) const override;

  static bool is_valid_date_format(const char *str,int& year,int& month,int& day) {
    if (str == nullptr || strlen(str) != 10) {
        return false;
    }
  
    if (sscanf(str, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return false;
    }
  
    // 检查格式固定位置是否是 '-'
    if (str[4] != '-' || str[7] != '-') {
        return false;
    }
  
    // 简单的合法性检查（可扩展）
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
  
    // 更精确检查每月天数（包括闰年）
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[1] = 29;  // 闰年二月
    }
  
    if (day > days_in_month[month - 1]) {
        return false;
    }
  
    return true;
  }
};
