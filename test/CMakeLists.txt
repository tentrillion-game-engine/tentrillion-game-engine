# TenTrillion TenTest Testing Utility
# Must be linked against the TenTrillion!

add_executable(${TENTEST_UTILITY_PROJECT_NAME} src/main.cpp)
target_link_libraries(${TENTEST_UTILITY_PROJECT_NAME} PRIVATE ${PROJECT_NAME})