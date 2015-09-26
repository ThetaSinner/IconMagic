cmake_minimum_required(VERSION 3.3)
project(iconmagic)

############ BEGIN: BUILD SETTINGS ############
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/App")
############ NEBIG: BUILD SETTINGS ############

############ BEGIN: LIST ALL SOURCE FILES ############
set(SOURCE_DIRECTORY "Source")
set(MAIN "main")
set(TEST "test")
set(MAIN_FILES
    ${SOURCE_DIRECTORY}/main.cpp
    ${SOURCE_DIRECTORY}/${MAIN}/IconMagic.hpp
    ${SOURCE_DIRECTORY}/${MAIN}/IconMagic.cpp

    ${SOURCE_DIRECTORY}/main/Registry/Manager.hpp
    ${SOURCE_DIRECTORY}/main/Registry/Manager.cpp

    # Common
    ${SOURCE_DIRECTORY}/main/Registry/Common/KeyPath.hpp
    ${SOURCE_DIRECTORY}/main/Registry/Common/KeyPath.cpp
    ${SOURCE_DIRECTORY}/main/Registry/Common/KeyService.hpp
    ${SOURCE_DIRECTORY}/main/Registry/Common/KeyService.cpp

    # Data Access
    ${SOURCE_DIRECTORY}/main/Registry/DataAccess/DirectRegistryAccess.hpp
    ${SOURCE_DIRECTORY}/main/Registry/DataAccess/DirectRegistryAccess.cpp
    ${SOURCE_DIRECTORY}/main/Registry/DataAccess/RegistryAccessException.hpp
    ${SOURCE_DIRECTORY}/main/Registry/DataAccess/RegistryAccessException.cpp
	${SOURCE_DIRECTORY}/main/Registry/DataAccess/SimpleRegistryAccess.hpp
	${SOURCE_DIRECTORY}/main/Registry/DataAccess/SimpleRegistryAccess.cpp

    # History
    ${SOURCE_DIRECTORY}/main/Registry/History/RegistryHistory.hpp
    ${SOURCE_DIRECTORY}/main/Registry/History/RegistryHistory.cpp
    ${SOURCE_DIRECTORY}/main/Registry/History/ExtensionHistory.hpp
    ${SOURCE_DIRECTORY}/main/Registry/History/ExtensionHistory.cpp
    ${SOURCE_DIRECTORY}/main/Registry/History/ImageEntry.hpp
    ${SOURCE_DIRECTORY}/main/Registry/History/ImageEntry.cpp

    # Scanner
    ${SOURCE_DIRECTORY}/main/Registry/Scanner/RegistryScanner.hpp
    ${SOURCE_DIRECTORY}/main/Registry/Scanner/RegistryScanner.cpp
    ${SOURCE_DIRECTORY}/main/Registry/Scanner/ScanTool.hpp
    ${SOURCE_DIRECTORY}/main/Registry/Scanner/ScanTool.cpp

    ${SOURCE_DIRECTORY}/main/Menu/Menu.hpp
    ${SOURCE_DIRECTORY}/main/Menu/Menu.cpp
    ${SOURCE_DIRECTORY}/main/Menu/MenuManager.hpp
    ${SOURCE_DIRECTORY}/main/Menu/MenuManager.cpp

    ${SOURCE_DIRECTORY}/main/Util.hpp
    ${SOURCE_DIRECTORY}/main/Util.cpp

    ${SOURCE_DIRECTORY}/${MAIN}/SystemValidation.hpp
    ${SOURCE_DIRECTORY}/${MAIN}/SystemValidation.cpp
    ${SOURCE_DIRECTORY}/${MAIN}/TextUI.hpp
    ${SOURCE_DIRECTORY}/${MAIN}/TextUI.cpp
    ${SOURCE_DIRECTORY}/${MAIN}/WindowsToolbox.hpp
    ${SOURCE_DIRECTORY}/${MAIN}/WindowsToolbox.cpp)
set(TEST_FILES
    ${SOURCE_DIRECTORY}/${TEST}/framework.hpp
    ${SOURCE_DIRECTORY}/${TEST}/framework.cpp
    ${SOURCE_DIRECTORY}/${TEST}/RegistryHistoryTest.hpp
    ${SOURCE_DIRECTORY}/${TEST}/RegistryHistoryTest.cpp)
set (SOURCE_FILES ${MAIN_FILES})
############ NEBIG: LIST ALL SOURCE FILES ############

####### BEGIN : CREATE THE EXECUTABLE ############
add_executable(IconMagic ${SOURCE_FILES})
####### NIBEG : CREATE THE EXECUTABLE ############
