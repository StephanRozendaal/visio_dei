/*
 * lua_loader.cpp
 *
 *  Created on: Nov 21, 2011
 *      Author: stephan
 */
#include "lua.h"

lua_loader::lua_loader() {
	luabind::open(L);

}

lua_loader::~lua_loader() {

}
