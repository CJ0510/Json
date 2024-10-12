#ifndef LEPTJSON_H__
#define LEPTJSON_H__

// JSON数据类型
typedef enum
{
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

// JSON数据结构
typedef struct
{
    lept_type type;
} lept_value;

enum
{
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

// 解析结果 v:解析结果 json:待解析字符串
int lept_parse(lept_value *v, const char *json);

// 获取数据类型
lept_type lept_get_type(const lept_value *v);

#endif /* LEPTJSON_H__ */