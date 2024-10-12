#include "leptjson.h"
#include <assert.h> /* assert() */
#include <stdlib.h> /* NULL */

#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)

typedef struct{
    const char* json;
}lept_context;

// 跳过空白字符
static void lept_parse_whitespace(lept_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

// null = "null" 解析null
static int lept_parse_null(lept_context *c, lept_value *v)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;  
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

// true = "true" 解析true
static int lept_parse_true(lept_context *c, lept_value *v)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}
static int lept_parse_false(lept_context *c, lept_value *v)
{
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

// 解析值
static int lept_parse_value(lept_context *c, lept_value *v)
{
    switch (*c->json)
    {
    case 't':
        return lept_parse_true(c, v);
    case 'f':
        return lept_parse_false(c, v);
    case 'n':
        return lept_parse_null(c, v);
    case '\0':
        return LEPT_PARSE_EXPECT_VALUE;
    default:
        return LEPT_PARSE_INVALID_VALUE;
    }
}

// 解析结果 v:解析结果 json:待解析字符串
int lept_parse(lept_value *v, const char *json)
{
    lept_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);

    if((ret = lept_parse_value(&c,v)) == LEPT_PARSE_OK)
    {
        lept_parse_whitespace(&c);
        if(*c.json != '\0')
        {
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}

// 获取数据类型
lept_type lept_get_type(const lept_value *v)
{
    assert(v != NULL);
    return v->type;
}
