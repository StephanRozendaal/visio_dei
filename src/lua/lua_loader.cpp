/*
 * lua_loader.cpp
 *
 *  Created on: Nov 21, 2011
 *      Author: stephan
 */
#include "lua.h"

lua_loader::lua_loader() {
	L = lua_open();
	luaL_openlibs(L);
	this->bind();
}

lua_loader::~lua_loader() {
	lua_close(L);
}

void lua_loader::bind() {
	using namespace luabind;

	open(L);
	/**
	 * lua functies
	 */
	module(L)
		[
		def("change_color_space", &alg::change_color_space), 
		def("threshold", &alg::segmentation::threshold),
		class_<image_resource>("image_resource")
			.def(constructor<cv::Mat&>())
			.def(constructor<const char*, int>())
			];

}
void lua_loader::execute(const char* script) {
	luaL_loadfile(L, script);
}
