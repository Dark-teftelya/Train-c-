# Train-c-


<!-- Общие требования -->
Репозиторий: Проект клонируется из git@github.com:Dark-teftelya/Train-c-.git.
Файлы проекта:
TNodeSortingYard/src/main.cpp
TNodeSortingYard/src/sorting_yard.h
TNodeSortingYard/src/sorting_yard.cpp
TNodeSortingYard/src/OpenSans.ttf
TNodeSortingYard/Makefile (для macOS/Linux)
TNodeSortingYard/TNodeSortingYard.sln, TNodeSortingYard.vcxproj (для Windows/Visual Studio)
Зависимости:
SFML 2.6 (графика, окна, система)
CMake (для кроссплатформенной сборки)
Компилятор: Clang (macOS), MSVC или MinGW (Windows)
Шрифт: OpenSans.ttf должен быть рядом с исполняемым файлом при запуске.
Инструкция для Visual Studio Code (VS Code)
VS Code используется как легковесная IDE с поддержкой CMake и C++ расширений. Инструкция охватывает macOS и Windows.

<!-- Windows -->
Установка зависимостей
Visual Studio (для MSVC):
Установите Visual Studio Community 2022 с официального сайта.
Выберите workload «Desktop development with C++».
CMake:
Скачайте с cmake.org и установите.
Добавьте CMake в PATH.
Проверьте:
text

Копировать
cmake --version
Git:
Скачайте с git-scm.com и установите.
Проверьте:
text

Копировать
git --version
SFML 2.6:
Скачайте SFML 2.6.0 для Windows (MSVC или MinGW) с sfml-dev.org.
Распакуйте в C:\SFML-2.6.0 (или другую папку).
Или используйте CMake FetchContent (см. CMakeLists.txt).
VS Code и расширения:
Установите VS Code с официального сайта.
Установите расширения:
C/C++ (ms-vscode.cpptools)
CMake Tools (ms-vscode.cmake-tools)
CMake (twxs.cmake)
Установите через Extensions или:
text

Копировать
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cmake-tools
code --install-extension twxs.cmake
Настройка проекта
Клонируйте репозиторий:
Откройте PowerShell или cmd:
text

Копировать
git clone https://github.com/Dark-teftelya/Train-c-.git
cd Train-c-
Откройте в VS Code:
text

Копировать
code .
Создайте CMakeLists.txt:
Используйте тот же CMakeLists.txt, что для macOS (см. выше). Если SFML установлена вручную, укажите путь:
text

Копировать
set(SFML_DIR "C:/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
Или используйте FetchContent для автоматической загрузки SFML:
text

Копировать
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)
Настройте VS Code:
Откройте CMakeLists.txt.
CMake Tools предложит выбрать комплект:
Выберите Visual Studio Community 2022 Release - amd64 (или MinGW для g++).
Вариант сборки: Release.
Или вручную:
text

Копировать
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
Соберите проект:
В VS Code: Ctrl+Shift+P > CMake: Build.
Или в терминале:
text

Копировать
cd build
cmake --build . --config Release
Исполняемый файл: build/Release/TNodeSortingYard.exe.
Запустите проект:
Скопируйте DLL-файлы SFML (sfml-graphics-2.dll, sfml-window-2.dll, sfml-system-2.dll) из C:\SFML-2.6.0\bin в build/Release.
В VS Code создайте .vscode/launch.json:
json

Копировать
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Run TNodeSortingYard",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/Release/TNodeSortingYard.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/build/Release",
            "environment": [],
            "console": "integratedTerminal"
        }
    ]
}
Нажмите F5.
Или в терминале:
text

Копировать
cd build/Release
.\TNodeSortingYard.exe


<!-- Инструкция для Visual Studio -->
Visual Studio — полноценная IDE для Windows, использующая MSVC. На macOS Visual Studio недоступна, поэтому этот раздел только для Windows.

Установка зависимостей
Visual Studio:
Установите Visual Studio Community 2022, выбрав «Desktop development with C++».
SFML 2.6:
Скачайте SFML 2.6.0 для MSVC с sfml-dev.org.
Распакуйте в C:\SFML-2.6.0.
Git:
Установите Git (см. выше).
Настройка проекта
Клонируйте репозиторий:
text

Копировать
git clone https://github.com/Dark-teftelya/Train-c-.git
cd Train-c-
Откройте проект:
Откройте TNodeSortingYard/TNodeSortingYard.sln в Visual Studio.
Если .sln отсутствует или некорректен, используйте CMake для генерации:
text

Копировать
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
Откройте build/TNodeSortingYard.sln.
Настройте SFML:
В Visual Studio:
Project > Properties:
C/C++ > General > Additional Include Directories: C:\SFML-2.6.0\include.
Linker > General > Additional Library Directories: C:\SFML-2.6.0\lib.
Linker > Input > Additional Dependencies: sfml-graphics.lib;sfml-window.lib;sfml-system.lib (Release) или sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib (Debug).
Скопируйте OpenSans.ttf в папку с .exe (например, build/Release).
Соберите и запустите:
Выберите конфигурацию Release (Solution Configurations).
Нажмите Ctrl+F5 или Build > Build Solution.
Скопируйте DLL-файлы SFML (sfml-graphics-2.dll, sfml-window-2.dll, sfml-system-2.dll) из C:\SFML-2.6.0\bin в папку с TNodeSortingYard.exe (обычно build/Release).
Запустите: Ctrl+F5.
Использование приложения
Окно 800x600.
Ввод: 101 1 (Enter).
S: сортировка и анимация.
R: сброс.
Результаты: таблица (середина), анимация (справа).