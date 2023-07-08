cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(NAME NutshellEngine-Application)
project(${NAME} VERSION 0.0.1 LANGUAGES C CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NTSHENGN_DEFINES "")
set(NTSHENGN_LIBRARIES "")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list(APPEND NTSHENGN_LIBRARIES ${CMAKE_DL_LIBS})
endif()

set(NTSHENGN_CORE_PATH "NtshEngn_Core_NOTFOUND" CACHE PATH "The directory containing NutshellEngine's core.")
if(NOT ${NTSHENGN_CORE_PATH} STREQUAL "NtshEngn_Core_NOTFOUND" AND EXISTS ${NTSHENGN_CORE_PATH})
	message(STATUS "Copy NutshellEngine\'s core from ${NTSHENGN_CORE_PATH} to ${CMAKE_SOURCE_DIR}/Core")
	file(COPY ${NTSHENGN_CORE_PATH}/ DESTINATION ${CMAKE_SOURCE_DIR}/Core)

	add_subdirectory(Core)
else()
	message(STATUS "Copy NutshellEngine\'s core from Git repository to ${CMAKE_CURRENT_SOURCE_DIR}/Core")
	FetchContent_Declare(
		Core
		GIT_REPOSITORY https://github.com/Team-Nutshell/NutshellEngine-Core
		GIT_TAG main
		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Core"
	)

	FetchContent_MakeAvailable(Core)
endif()

set(SCRIPTS_DIRECTORY "scripts/")
file(GLOB_RECURSE SCRIPTS "${SCRIPTS_DIRECTORY}/*.h")
message(STATUS ${SCRIPTS})

add_executable(${PROJECT_NAME} main.cpp ${SCRIPTS})

target_link_libraries(${PROJECT_NAME} PRIVATE NutshellEngine-Core ${NTSHENGN_LIBRARIES})

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	${NTSHENGN_DEFINES}
	PUBLIC
	$<$<CONFIG:Debug>:NTSHENGN_DEBUG>
	$<$<CONFIG:MinSizeRel>:NTSHENGN_RELEASE>
	$<$<CONFIG:Release>:NTSHENGN_RELEASE>
	$<$<CONFIG:RelWithDebInfo>:NTSHENGN_DEBUG>)