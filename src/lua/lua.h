/*
 * lua.h
 *
 *  Created on: Nov 21, 2011
 *      Author: stephan
 */

#ifndef LUA_H_
#define LUA_H_

/**
 * externe libraries
 */
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/class.hpp>
#include <luabind/function.hpp>
#include <luabind/object.hpp>
#include <iostream>

/**
 * eigen libraries
 */
#include "../library/library.h"

class lua_loader {
public:
	lua_loader();
	~lua_loader();
	void bind();
	void execute(const char*);
private:
	lua_State* L;
protected:
};

#endif /* LUA_H_ */
