# 2026-01-28 - LocalInsight AI Build System
cmake_minimum_required(VERSION 3.20)
project(LocalInsightAI VERSION 1.0.0 LANGUAGES CXX)

# Estándar C++20 requerido
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 1. LISTA DE ARCHIVOS FUENTE (Definirlos antes de usarlos)
set(CORE_SOURCES
    src/core/AIEngine.cpp
    src/core/ContextManager.cpp
    src/inference/GemmaProvider.cpp
    src/utils/FileSystem.cpp
    src/utils/Logger.cpp
)

# 2. DEFINIR LOS OBJETIVOS (Primero creamos la entidad)
add_library(LocalInsightCore SHARED 
    ${CORE_SOURCES}
    src/bridge/LocalInsightBridge.cpp
)

add_executable(LocalInsightTest 
    ${CORE_SOURCES}
    src/main.cpp
)

# 3. DIRECTORIOS DE CABECERAS DEL PROYECTO
target_include_directories(LocalInsightCore PUBLIC include)
target_include_directories(LocalInsightTest PUBLIC include)

# 4. INTEGRACIÓN DE LLAMA.CPP (Después de definir los objetivos)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/llama.cpp/CMakeLists.txt")
    # Optimizaciones para compilación rápida y soporte Metal en Mac
    set(LLAMA_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(LLAMA_BUILD_SERVER OFF CACHE BOOL "" FORCE)
    set(LLAMA_METAL ON CACHE BOOL "" FORCE) # Activa GPU en Apple Silicon
    
    add_subdirectory(external/llama.cpp)
    
    # Vincular llama y dar acceso a sus headers internos
    # Esto elimina el error de #include "llama.h"
    target_link_libraries(LocalInsightCore PRIVATE llama)
    target_include_directories(LocalInsightCore PRIVATE 
        external/llama.cpp/include 
        external/llama.cpp/src
    )
    
    target_link_libraries(LocalInsightTest PRIVATE llama)
    target_include_directories(LocalInsightTest PRIVATE 
        external/llama.cpp/include 
        external/llama.cpp/src
    )
else()
    message(FATAL_ERROR "No se encontro llama.cpp en external/. Ejecuta: git clone https://github.com/ggerganov/llama.cpp external/llama.cpp")
endif()

# 5. CONFIGURACIÓN ESPECÍFICA DE PLATAFORMA
if(WIN32)
    set_target_properties(LocalInsightCore PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )
elseif(APPLE)
    # Asegura que la dylib sea localizable por la app Swift
    set_target_properties(LocalInsightCore PROPERTIES 
        INSTALL_RPATH "@loader_path"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

message(STATUS "LocalInsight AI configured successfully for ${CMAKE_SYSTEM_NAME}")