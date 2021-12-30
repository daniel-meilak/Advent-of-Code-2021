cmake_minimum_required(VERSION 3.10)

project(AOC21 VERSION 1.0)

# compiler arguments
if (MSVC)
   add_compile_options(/Wall)
else()
   add_compile_options(-Wall -Werror -Wextra -pedantic)
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify build type
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Test Results for each day
list(APPEND part_1 1681 1893605 2498354 38594 5084 390923 344605 519 486 339537 1683 3576 770 4517 458 917 15400 4243 440 5464 893700 546724 10607 91699394894995 300) 
list(APPEND part_2 1704 2120734350 3277956 21184 17882 1749945484935 93699985 1027483 1059300 2412013412 788 84271 "####" 4704817645083 2800 2536453523344 5844 4701 13382 19228 568867175661958 1346544039176841 59071 51147191161261 "")

enable_testing()

# add executable and test each day
foreach(day RANGE 1 25)
   
   # set week
   if(day LESS 8)
      set(week 1)
   elseif(day LESS 15)
      set(week 2)
   elseif(day LESS 22)
      set(week 3)
   else()
      set(week 4)
   endif()

   # add each executable
   add_executable(day_${day} ${PROJECT_SOURCE_DIR}/week_${week}/day_${day}/day_${day}.cpp)
   set_target_properties(day_${day} PROPERTIES OUTPUT_NAME "day_${day}.exe")

   # copy input over
   configure_file(${PROJECT_SOURCE_DIR}/week_${week}/day_${day}/input_${day} ${PROJECT_BINARY_DIR}/input_${day} COPYONLY)

   # set output for testing
   math(EXPR index ${day}-1)
   list(GET part_1 ${index} output_1)
   list(GET part_2 ${index} output_2)

   # test results
   add_test(NAME day_${day}_test COMMAND day_${day}.exe)
   set_tests_properties(day_${day}_test PROPERTIES PASS_REGULAR_EXPRESSION "${output_1}\n.*${output_2}" TIMEOUT 15)
   
endforeach()
