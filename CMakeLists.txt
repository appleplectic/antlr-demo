cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(antlr-demo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(ANTLR4_WITH_STATIC_CRT OFF)
set(ANTLR_BUILD_CPP_TESTS OFF)
set(DISABLE_WARNINGS ON)
set(ANTLR_TAG 4.13.1)
add_definitions(-DANTLR4CPP_STATIC)

set(JAR_FILE_NAME antlr-${ANTLR_TAG}-complete.jar)
set(ANTLR_EXECUTABLE ${CMAKE_BINARY_DIR}/${JAR_FILE_NAME})
set(JAR_URL https://www.antlr.org/download/${JAR_FILE_NAME})
set(EXPECTED_JAR_HASH bc13a9c57a8dd7d5196888211e5ede657cb64a3ce968608697e4f668251a8487)

file(DOWNLOAD
        ${JAR_URL} ${CMAKE_BINARY_DIR}/${JAR_FILE_NAME}
        STATUS download_status
        LOG download_log
)
list(GET download_status 0 status_code)
if(NOT status_code EQUAL 0)
    message(FATAL_ERROR "Error downloading file: ${status_string}\nDetails: ${download_log}")
endif()
file(SHA256 ${CMAKE_BINARY_DIR}/${JAR_FILE_NAME} JAR_HASH)
if(NOT "${JAR_HASH}" STREQUAL ${EXPECTED_JAR_HASH})
    message(FATAL_ERROR "The downloaded file does not have the expected SHA256 hash: expected ${EXPECTED_JAR_HASH}, got ${JAR_HASH}")
endif()

include(FetchContent)
FetchContent_Declare(
        antlr
        GIT_REPOSITORY https://github.com/antlr/antlr4
        GIT_TAG ${ANTLR_TAG}
        SOURCE_SUBDIR "runtime/Cpp"
)
FetchContent_MakeAvailable(antlr)

include(${antlr_SOURCE_DIR}/runtime/Cpp/cmake/FindANTLR.cmake)

antlr_target(ANTLRDemoLexer ${CMAKE_SOURCE_DIR}/grammar/ANTLRDemoLexer.g4 LEXER
        PACKAGE ANTLRDemoGrammar
        OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ANTLRDemoGrammar
)
antlr_target(ANTLRDemoParser ${CMAKE_SOURCE_DIR}/grammar/ANTLRDemoParser.g4 PARSER VISITOR
        PACKAGE ANTLRDemoGrammar
        DEPENDS_ANTLR ANTLRDemoLexer
        OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ANTLRDemoGrammar
        COMPILE_FLAGS -lib ${CMAKE_BINARY_DIR}/ANTLRDemoGrammar
)

add_executable(ANTLRDemoInterpreter src/main.cpp
        ${ANTLR_ANTLRDemoParser_CXX_OUTPUTS}
        ${ANTLR_ANTLRDemoLexer_CXX_OUTPUTS}
        src/main.cpp
        src/ANTLRDemoAST.cpp
        src/ANTLRDemoAST.h
)
target_link_libraries(ANTLRDemoInterpreter PRIVATE antlr4_static)
target_include_directories(ANTLRDemoInterpreter PRIVATE
        "${antlr_SOURCE_DIR}/runtime/Cpp/runtime/src"
        ${CMAKE_BINARY_DIR}/ANTLRDemoGrammar
        src)