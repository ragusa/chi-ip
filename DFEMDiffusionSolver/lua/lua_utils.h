#ifndef DFEM_DIFFUSION_LUA_UTILS_H
#define DFEM_DIFFUSION_LUA_UTILS_H

#include"ChiLua/chi_lua.h"

int chiDFEMDiffusionSolverCreate(lua_State *L);
int chiDFEMDiffusionSetBCProperty(lua_State *L);


#endif //DFEM_DIFFUSION_LUA_UTILS_H