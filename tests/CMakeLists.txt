cmake_minimum_required(VERSION 3.22)
set (PROJECT_TEST_NAME ${PROJECT_NAME}-Test)

enable_testing()

set (TESTS_DIR tests)

set(PROJ_UT_SRC
    ${SRC_DIR}/TestSSO.cc
)

include_directories (${PROJECT_SOURCE_DIR}/${INCL_DIR})

add_executable (${PROJECT_TEST_NAME} ${PROJ_UT_SRC})

link_directories(/usr/local/lib)

# Link libraries
target_link_libraries(${PROJECT_TEST_NAME}
                      gtest)

