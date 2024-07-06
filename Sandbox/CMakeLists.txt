set_property(TARGET PROPERTY USE_FOLDERS ON)

file (GLOB_RECURSE SOURCES
	src/*.hpp
	src/*.h
	src/*.cpp 
)
#file (GLOB_RECURSE HEADERS src/*.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})
#set (CPP_SOURCES 
#	"src/SandboxText.cpp")


add_executable(Sandbox ${SOURCES})
target_compile_definitions(Sandbox PRIVATE _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS=1 _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING=1)
target_include_directories(Sandbox PRIVATE ${QUEST_ROOT}/QuestEngine/include ${QUEST_ROOT}/QuestEngine/src)
target_link_libraries(Sandbox QuestEngine)
#install(FILES $<TARGET_RUNTIME_DLLS:Sandbox> TYPE BIN)

add_custom_command(TARGET Sandbox POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:Sandbox> $<TARGET_RUNTIME_DLLS:Sandbox>
  COMMAND_EXPAND_LISTS
)