cmake_minimum_required(VERSION 3.5)

set(SEARCH_DIR
	/home/cs104/hw-chphu/hw3/search)

set(TEST_SOURCES
	gtest.cpp)

set(SEARCH_SOURCES
	${SEARCH_DIR}/cmdhandler.cpp  
	${SEARCH_DIR}/md_parser.cpp  
	${SEARCH_DIR}/test.cpp        
	${SEARCH_DIR}/util.cpp
	${SEARCH_DIR}/handler.cpp     
	${SEARCH_DIR}/searcheng.cpp  
	${SEARCH_DIR}/searchui.cpp      
	${SEARCH_DIR}/txt_parser.cpp  
	${SEARCH_DIR}/webpage.cpp)


include_directories(${SEARCH_DIR})

# 104 compile flags
add_compile_options(-g -Wall -std=c++11)

# find GTest
find_package(GTest)

add_executable(gtest ${TEST_SOURCES} ${SEARCH_SOURCES})
target_link_libraries(gtest GTest::GTest GTest::Main)

