
add_executable(UntitledTankGameClient main.cpp)
include_directories(../common)
target_link_libraries(UntitledTankGameClient PRIVATE UntitledTankGameCommon)

