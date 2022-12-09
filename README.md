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


