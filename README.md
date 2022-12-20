# chi-ip
IP for DFEM diffusion in chi-tech


## Step-0:

1. Create empty repo on github
2. git clone with token
3. Open new project in CLion and point to repo that was jsut cloned

## Step-1:
Follow the instructions in the developper's manual (```Using Chi-Tech as a library```)

Specifically,
- create the CMakeLists.txt file and populate
- create the main .cc file and populate
- Go to CLion's Cmake setting and add the ENV variable for where the amin chi-tech sources are (for me, ```CHI_TECH_DIR=/Users/jean.ragusa/repo/chi-tech```)
   - however, this was not sufficient when I compile from a terminal outside of CLion. I had to export that env variable also in that terminal
- check in the CMake terminal that everything went fine (that Downstream.cmake was found, that MPI was found, ...)
- The instructions require to create a ```build``` directory. I called it ```chi_build``` instead.
## Step-2:

Start adding source files.
- I created a new folder (```DFEMDIffusionSolver```), added source code there.
- I had to update the ```CMakeLists.txt``` file at the upper level by adding ```add_subdirectory("${PROJECT_SOURCE_DIR}/DFEMDiffusionSolver/")```
- I created a new ```CMakeLists.txt``` file in the new folder and included the following lines:
   ```bash
   file (GLOB_RECURSE MORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")
   set(SOURCES ${SOURCES} ${MORE_SOURCES} PARENT_SCOPE) 
   ```

## Step-3:

- I developed new code in the new folder ```DFEMDIffusionSolver```.
- I add a subfolder there, called ```lua``` where the lua wrappers are found. The wrappers allow to call the functions from the lua console (i.e., the input file)
  - ```create_solver.cc```, the solver itself
  - ```setBCproperty.cc```, the BC conditions
  - ```lua_utils.h```, the header
- the main code file, ```testIP.cc```, needs to register the lua functions

Later, when the code gets folded into the main chi-tech, a few changes will need to take place. We describe those later.

## Step-4:

I wanted to create a simulation test that uses the new solver, but also contains a new function (the L2 error norm) that I do not want to be in the main solver.

- I created a new folder structure that mimics the chi-tech simulation test folder structure: ```ChiTech\LuaTest\ ```
- There, I added ```sim_IP_MMS_L2error.cc```, that basically calls my original solver, but also contains the L2 error computation. This file is actually the lua wrapper, same functionality as above.
- I also added a header file, ```unit_tests.h```.
- A ```CmakeLists.txt``` file needs to be added there
  ```bash
  file (GLOB_RECURSE MORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")
  set(SOURCES ${SOURCES} ${MORE_SOURCES} PARENT_SCOPE)
   ```
- In the main code test, ```testIP.cc```, the new lua function needs to be registered.
- In the main ```CmakeLists.txt``` file, the new subfolder needs to be added ```add_subdirectory("${PROJECT_SOURCE_DIR}/ChiTech/LuaTest/") ```


## Step-5:

When bringing the code into the main chi-tech repository, 
the following changes need to happen:
- The folder ```DFEMDIffusionSolver``` gets placed in 
  ```ChiModules``` and the ```lua_utils.h``` in that subfolder 
  receives an update: we add ```RegisterLuaEntities()``` inside a namespace
- We add 
  - this line ```#include "DFEMDiffusion/lua/ip_lua_utils.h" ``` 
  - and this line ```dfem_diffusion::dfem_diffusion_lua_utils::RegisterLuaEntities(L)```
 
  in ```ChiModule\lua\chi_modules_lua.cc```
- Add the proper subfolder in the ```CMakeLists.txt``` file 
located in ```ChiModules``` (i.e., add this line ```add_subdirectory("DFEMDiffusion")```)
- Update ```lua_test.cc``` to register the sim test
