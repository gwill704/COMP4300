include(FetchContent)

set(IMGUI_VERSION 1.91.1)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG 0fa201c969e48ecc253581c5841ce73f44d42f49 # 3.0.2
    #69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
)
add_subdirectory(sfml)

FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY "https://github.com/SFML/imgui-sfml.git"
    GIT_TAG        master
    # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
)
add_subdirectory(imgui-sfml)