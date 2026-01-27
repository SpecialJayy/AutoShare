cmake_minimum_required(VERSION 3.20)
project(AutoShare)

set(CMAKE_CXX_STANDARD 20)

# ==========================================
# STATIC LINKING & FLAGS
# ==========================================
# To sprawia, że .exe jest samodzielny i nie płacze o biblioteki systemowe
set(CMAKE_CXX_FLAGS_RELEASE "-static -static-libgcc -static-libstdc++ -O3")
set(CMAKE_EXE_LINKER_FLAGS "-static")

# ==========================================
# PLIKI ŹRÓDŁOWE
# ==========================================
add_executable(AutoShare
        main.cpp
        sqlite3.c
        resources.rc
        DBM.cpp
        DBM.h
        clientManager.cpp
        clientManager.h
        Client.cpp
        Client.h
        Vehicle.h
        Color.cpp
        Color.h
        Car.h
        Bike.h
        Truck.h
        Bus.h
)

# Biblioteki systemowe potrzebne dla sqlite3 (szczególnie na Linux/Unix, na Windowsie nie zaszkodzi)
if(UNIX)
    target_link_libraries(AutoShare pthread dl)
endif()

# ==========================================
# AUTOMATYCZNE KOPIOWANIE BAZY DANYCH
# ==========================================
# To kopiuje plik autoshare.db z folderu projektu do folderu z .exe
set(DATABASE_FILE "autoshare.db")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET AutoShare POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/${DATABASE_FILE}"
            "$<TARGET_FILE_DIR:AutoShare>/${DATABASE_FILE}"
            COMMENT "Kopiowanie bazy danych dla wersji Release..."
    )
endif()

