#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int Add(lua_State* L)
{
    double dD1 = luaL_checknumber(L, 1);
    double dD2 = luaL_checknumber(L, 2);

    lua_pushnumber(L, dD1 + dD2);

    return 1;
}

static luaL_Reg afTestFunc[] = {
    {"add", Add},
    {NULL, NULL},
};

extern int luaopen_testlua(lua_State* L)
{
    luaL_newlib(L, afTestFunc);
    return 1;
}
