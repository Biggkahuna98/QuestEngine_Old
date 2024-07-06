set_property(TARGET PROPERTY USE_FOLDERS ON)

file (GLOB_RECURSE VS_TREE 
	Public/*.cpp Public/*.h
	Private/*.cpp Private/*.h
	Public/*.inl
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}  FILES ${VS_TREE})

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Public/TemplateLibTest.h
	${CMAKE_CURRENT_SOURCE_DIR}/Private/TemplateLibTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Public/TemplateLibTest.inl
)

add_library(TemplateLibTest SHARED ${SOURCES})

target_compile_definitions(TemplateLibTest
	PRIVATE
		TEMPLATELIBTEST_BUILD
)

# Export the public includes to dependents
target_include_directories(TemplateLibTest
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Public
)

# Make sure the private section can include the public
target_include_directories(TemplateLibTest
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/Public
)