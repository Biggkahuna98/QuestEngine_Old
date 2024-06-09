set_property(TARGET PROPERTY USE_FOLDERS ON)

set (TARGET_NAME QuestEngine)
set (QUEST_LIBRARY_TYPE STATIC)
set (CMAKE_CXX_STANDARD 20)

# vulkan
find_package(Vulkan REQUIRED COMPONENTS glslc SPIRV-Tools shaderc_combined)
#find_vulkan(REQUIRED COMPONENTS glslc glslang SPIRV-Tools shaderc_combined)

if (NOT Vulkan_FOUND)
	message(STATUS "Vulkan not found. Please install it.")
	return()
endif()

set (QUEST_STATIC_LIBS
	glfw
	#VulkanRenderer
)

message("Building Quest Engine static library...")

file (GLOB_RECURSE SOURCES 
	include/*.hpp
	include/*.h
	include/*.cpp
	src/*.h 
	src/*.hpp
	src/*.cpp 
)
list (APPEND SOURCES ${QUEST_ROOT}/ThirdParty/Engine/tracy/public/TracyClient.cpp)

file (GLOB_RECURSE HEADERS
	include/*.hpp
	include/*.h
	src/*.h
	src/*.hpp
)

file (GLOB_RECURSE VS_TREE 
	src/*.cpp src/*.h 
	include/QuestEngine/QuestEngine.h 
	include/QuestEngine/QuestEngineEntrypoint.h 
	assets/shaders/*.vert
	assets/shaders/*.frag
)

# vendor includes
set(VENDOR_INCLUDES 
	${QUEST_ROOT}/ThirdParty/Engine/glfw/include/
	#vendor/imgui/
	${QUEST_ROOT}/ThirdParty/Engine/glm/
	${QUEST_ROOT}/ThirdParty/Engine/fmt/include/
	${QUEST_ROOT}/ThirdParty/Engine/spdlog/include/
	${QUEST_ROOT}/ThirdParty/Engine/tracy/public/
	#vendor/stb/
	#vendor/tinyobjloader/

	#${QUEST_ROOT}/VulkanRenderer/include/
)

set(VULKAN_LIBRARIES
	${Vulkan_LIBRARY}
	${Vulkan_glslang_LIBRARY}
	${Vulkan_shaderc_combined_LIBRARY}
	${Vulkan_SPIRV-Tools_LIBRARY}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${VS_TREE})


add_library(${TARGET_NAME} ${QUEST_LIBRARY_TYPE} ${SOURCES} ${HEADERS})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#target_precompile_headers(${TARGET_NAME} 
#    PRIVATE 
#    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/qepch.h>"
#)

target_compile_definitions(${TARGET_NAME} PRIVATE 
	_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS=1
	_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING=1
	_CRT_SECURE_NO_WARNINGS=1
	GLM_FORCE_DEPTH_ZERO_TO_ONE=1
	QE_PLATFORM_WINDOWS=1
)
target_compile_definitions(${TARGET_NAME} PRIVATE 
	$<$<CONFIG:DEBUG>:QUEST_DEBUG_MODE=1> 
	$<$<CONFIG:RELWITHDEBINFO>:QUEST_DEBUG_MODE=1>
)

target_compile_options(${TARGET_NAME} PRIVATE -W4 -Wno-c++98-compat -Wno-c++98-compat-pedantic)

target_link_libraries(${TARGET_NAME} PRIVATE ${Vulkan_LIBRARIES} ${QUEST_STATIC_LIBS})

#include_directories(SYSTEM )
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${Vulkan_INCLUDE_DIR} ${VENDOR_INCLUDES})
#target_include_directories(${TARGET_NAME} PUBLIC ${SOURCES} ${HEADERS} ${Vulkan_INCLUDE_DIR} ${VENDOR_INCLUDES})
message("Done building Quest Engine")

