include(biicode/boost/setup)

ADD_BII_TARGETS()

set(Boost_USE_STATIC_LIBS ON)
bii_find_boost()
target_include_directories(${BII_BLOCK_TARGET} INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(${BII_BLOCK_TARGET} INTERFACE ${Boost_LIBRARIES})
target_compile_features(${BII_BLOCK_TARGET} INTERFACE cxx_auto_type)
