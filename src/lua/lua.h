/*
 * lua.h
 *
 *  Created on: Nov 21, 2011
 *      Author: stephan
 */

#ifndef LUA_H_
#define LUA_H_

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <iostream>

class lua_loader {
public:
	lua_loader();
	~lua_loader();
private:
	lua_State* L;
protected:
};

#endif /* LUA_H_ */
