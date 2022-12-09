#include "chi_runtime.h"
#include "chi_log.h"
#include "ChiConsole/chi_console.h"
#include "DFEMDiffusionSolver/lua/lua_utils.h"

#include "ChiMacros/lua_register_macro.h"

// #include "ChiMath/PETScUtils/petsc_utils.h"
// #include "ChiPhysics/FieldFunction2/fieldfunction2.h"

int main(int argc, char* argv[])
{
  chi::Initialize(argc,argv);

  chi::log.Log() << "\n------------------------\nDFEM Diffusion main code!\n------------------------\n";

  // Adding lua function that requires console
  auto& console = chi_objects::ChiConsole::GetInstance();
  auto L = console.consoleState;
  RegisterFunction(chiDFEMDiffusionSolverCreate);
  RegisterFunction(chiDFEMDiffusionSetBCProperty);

  chi::RunBatch(argc, argv);

  // Adding rest of the code here
  chi::log.Log() << "Coding Tutorial DFEM";
  chi::Finalize();
  return 0;

}