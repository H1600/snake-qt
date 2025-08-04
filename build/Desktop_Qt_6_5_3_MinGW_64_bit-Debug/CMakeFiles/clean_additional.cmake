# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\snake_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\snake_autogen.dir\\ParseCache.txt"
  "snake_autogen"
  )
endif()
