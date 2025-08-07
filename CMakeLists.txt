cmake_minimum_required(VERSION 3.28)
project(SFMLGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} src/main.cpp
                    src/core/GameEngine.h src/core/GameEngine.cpp
                    src/core/State.h src/core/State.cpp
                    src/core/Action.h src/core/Action.cpp
                    src/core/animations/Animation.h src/core/animations/Animation.cpp
                    src/core/animations/CircleShapeAnimation.h src/core/animations/CircleShapeAnimation.cpp
                    src/core/components/Component.h
                    src/core/components/CTransform.h
                    src/core/components/CAnimation.h
                    src/core/entities/Entity.h src/core/entities/Entity.cpp
                    src/core/entities/EntityManager.h src/core/entities/EntityManager.cpp

                    src/states/GameState.h src/states/GameState.cpp
)

# Copy assets directory to the output directory
add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
            COMMENT "Copying assets directory to output directory"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
