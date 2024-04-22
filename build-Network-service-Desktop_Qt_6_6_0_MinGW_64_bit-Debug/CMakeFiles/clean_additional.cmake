# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Network-service_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Network-service_autogen.dir\\ParseCache.txt"
  "Network-service_autogen"
  )
endif()
