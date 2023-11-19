# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SkribbleFakeClient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SkribbleFakeClient_autogen.dir\\ParseCache.txt"
  "SkribbleFakeClient_autogen"
  )
endif()
