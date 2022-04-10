# Create a Common library that would be used by both clients and servers
add_library(UntitledTankGameCommon Configuration.cpp Configuration.h)
target_link_libraries(UntitledTankGameCommon PRIVATE toml11::toml11)
