/*
** $Id: lua.h,v 1.218.1.5 2008/08/06 13:30:12 roberto Exp $
** Lua - An Extensible Extension Language
** Lua.org, PUC-Rio, Brazil (http://www.lua.org)
** See Copyright Notice at the end of this file
*/


#ifndef luac_h
#define luac_h

#include <stdarg.h>
#include <stddef.h>

#include "lua.h"

LUA_API int (luaL_compilestring) (lua_State *L, const char *s);



#endif
