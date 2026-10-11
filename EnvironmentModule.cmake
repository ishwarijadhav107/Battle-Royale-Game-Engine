# Game Environment, Vehicles & Safe Zone module (Member 4).
# Include after PlayerLib has been defined in the root CMakeLists.txt:
#     include(EnvironmentModule.cmake)

add_library(EnvironmentLib STATIC
    src/environment/Vehicle.cpp
    src/environment/Car.cpp
    src/environment/Truck.cpp
    src/environment/Motorcycle.cpp
    src/environment/SafeZone.cpp
    src/environment/EnvironmentEvent.cpp
)
target_link_libraries(EnvironmentLib PUBLIC PlayerLib)

enable_testing()
add_executable(environment_tests tests/environment_tests.cpp)
target_link_libraries(environment_tests PRIVATE EnvironmentLib PlayerLib)
add_test(NAME EnvironmentTests COMMAND environment_tests)

add_executable(environment_demo tests/environment_demo.cpp)
target_link_libraries(environment_demo PRIVATE EnvironmentLib PlayerLib)
