# Build an executable that will test the various components
add_executable(UntitledTankGamesTests tests.cpp testConfiguration.cpp)
include_directories(../src/common)
target_link_libraries(UntitledTankGamesTests UntitledTankGameCommon Catch2::Catch2WithMain)

# Copy test data to the binary directory and ensure that if the orignals are updated we recopy the files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/Display.toml ${CMAKE_CURRENT_BINARY_DIR}/data/Display.toml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/GUI.toml ${CMAKE_CURRENT_BINARY_DIR}/data/GUI.toml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/Servers.toml ${CMAKE_CURRENT_BINARY_DIR}/data/Servers.toml COPYONLY)
