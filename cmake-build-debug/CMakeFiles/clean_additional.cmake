# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\temaaa_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\temaaa_autogen.dir\\ParseCache.txt"
  "temaaa_autogen"
  )
endif()
