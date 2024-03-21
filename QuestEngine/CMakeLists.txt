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




#add_subdirectory(QUEST_ROOT/Quest/vendor/glad)
#message("Building imgui...")
#add_subdirectory(${QUEST_ROOT}/Quest/vendor/imgui)
#message("Done building imgui")
#add_subdirectory(QUEST_ROOT/Quest/vendor/ImGuizmo)
#add_subdirectory(QUEST_ROOT/Quest/vendor/yaml-cpp)

set (QUEST_STATIC_LIBS
    glfw
    #VulkanRenderer
)

message("Building Quest Engine static library...")

set (SOURCES
    # LIBRARY CONSUMER INCLUDES
    include/QuestEngine.h
    include/QuestEngineEntrypoint.h

    # CORE
    src/Core/Application.h
    src/Core/Application.cpp
)
#file (GLOB_RECURSE SOURCES src/*.cpp src/*.h include/Quest.h include/QuestEntrypoint.h assets/shaders/*.vert assets/shaders/*.frag)
#list(REMOVE_ITEM SOURCES src/qepch.h src/qepch.cpp)
#file (GLOB_RECURSE HEADERS include/Quest.h src/*.h)
set (HEADERS
    include/
    src/    
)

# vendor includes
set(VENDOR_INCLUDES 
    ${QUEST_ROOT}/vendor/engine/glfw/include/
    #vendor/imgui/
    ${QUEST_ROOT}/vendor/engine/glm/
    #vendor/stb/
    #vendor/tinyobjloader/

    #${QUEST_ROOT}/VulkanRenderer/include/
)

#set(VENDOR_SOURCES
    #vendor/glad/src/glad.c
#)

set(VULKAN_LIBRARIES
    ${Vulkan_LIBRARY}
    ${Vulkan_glslang_LIBRARY}
    ${Vulkan_shaderc_combined_LIBRARY}
    ${Vulkan_SPIRV-Tools_LIBRARY}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})
#set (SOURCES "src/TestLib.cpp")
#set (HEADERS "src/TestLib.h")


add_library(${TARGET_NAME} ${QUEST_LIBRARY_TYPE} ${SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#target_precompile_headers(${TARGET_NAME} 
#    PRIVATE 
#    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/qepch.h>"
#)

target_compile_definitions(${TARGET_NAME} PRIVATE GLM_FORCE_DEPTH_ZERO_TO_ONE=1 _CRT_SECURE_NO_WARNINGS=1)

target_link_libraries(${TARGET_NAME} PRIVATE ${Vulkan_LIBRARIES} ${QUEST_STATIC_LIBS})

target_include_directories(${TARGET_NAME} PUBLIC ${HEADERS} ${Vulkan_INCLUDE_DIR} ${VENDOR_INCLUDES})
message("Done building Quest Engine")

