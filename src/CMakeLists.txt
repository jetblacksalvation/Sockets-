add_executable (Sockets++ "Sockets++.cpp"  "main.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Sockets++ PROPERTY CXX_STANDARD 20)
endif()
