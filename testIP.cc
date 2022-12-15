#include "chi_runtime.h"
#include "chi_log.h"
#include "ChiConsole/chi_console.h"
// #include "./DFEMDiffusionSolver/lua/lua_utils.h"

#include "ChiMacros/lua_register_macro.h"
#include "./ChiTech/LuaTest/unit_tests.h"

int main(int argc, char* argv[])
{
  chi::Initialize(argc,argv);

  chi::log.Log() << "\n------------------------\nDFEM Diffusion main code!\n------------------------\n";

  // Adding lua function that requires console
  auto& console = chi_objects::ChiConsole::GetInstance();
  auto L = console.consoleState;
  RegisterFunction(chiDFEMDiffusionSolverCreate);
  RegisterFunction(chiDFEMDiffusionSetBCProperty);
  lua_register(L, "chiSimTest_IP_MMS_L2error", chi_unit_sim_tests::chiSimTest_IP_MMS_L2error);

  chi::RunBatch(argc, argv);

  // Adding rest of the code here
  chi::log.Log() << "Coding Tutorial DFEM";
  chi::Finalize();
  return 0;

}