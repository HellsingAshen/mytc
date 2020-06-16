#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define null NULL

int get_field_int(const char* filename, const char* fieldname, const char* fieldkey){
    lua_State       *L              = lua_open();
    int             ret             = 0;

    luaL_openlibs(L);

    if (luaL_loadfile(L, filename) 
        || (lua_pcall(L, 0, 0, 0)))
        error("canot run config file : [%s].\n", lua_tostring(L, -1));
    
    lua_getglobal(L, fieldname);
    
    lua_pushstring(L, fieldkey);

    lua_gettable(L, -2);

    if (!lua_isnumber(L, -1))
        error("lua_isnumber check failed. filed is [%s] index is [%d].\n", fieldname, fieldkey);

    ret = lua_tonumber(L, -1);
    
    lua_pop(L, 1);

	lua_close(L);
    return ret;
}

char* get_field_string(const char* filename, const char* fieldname, const char* fieldkey){
    lua_State       *L              = lua_open();
    const char*     fieldvalue      = null;
    char*           retvalue        = null;

    luaL_openlibs(L);

    if (luaL_loadfile(L, filename) 
        || (lua_pcall(L, 0, 0, 0)))
        error("canot run config file : [%s].", lua_tostring(L, -1));

    
    lua_getglobal(L, fieldname);
    
    lua_pushstring(L, fieldkey);

    lua_gettable(L, -2);

    if (!lua_isstring(L, -1))
        error("lua_isnumber check failed. filed is [%s] index is [%d].\n", fieldname, fieldkey);

    fieldvalue = lua_tostring(L, -1);

    retvalue = malloc(strlen(fieldvalue) + 1);
    assert(retvalue != null);

    memset(retvalue, 0, strlen(fieldvalue) + 1);
    strcpy(retvalue, fieldvalue);
    
    lua_pop(L, 1);
	lua_close(L);

    return retvalue;
}

int main(){
    printf("test lua cfg.\n");
    int             iAge                = 0;
    char*           pcName              = null; 
    
    iAge = get_field_int("./cfg.lua", "People", "age");    
    printf("age is [%d].\n", iAge);

    pcName = get_field_string("./cfg.lua", "People", "name");    
    printf("name is [%s].\n", pcName);

    return 0;
}
