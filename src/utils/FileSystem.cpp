/**
 * @file FileSystem.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion de utilidades de sistema de archivos.
 */

#include "utils/FileSystem.hpp"
#include <algorithm>

namespace LocalInsight::Utils;

/**
 * @brief Verifica la existencia fisica de un archivo o carpeta.
 */
bool FileSystem::exists(const std::string& path) {
    return std::filesystem::exists(path);
}

/**
 * @brief Obtiene la ruta donde se encuentra el ejecutable actual.
 */
std::string FileSystem::getExecutableDirectory() {
    return std::filesystem::current_path().string();
}

/**
 * @brief Une dos rutas de forma segura segun el sistema operativo.
 */
std::string FileSystem::joinPaths(const std::string& base, const std::string& relative) {
    std::filesystem::path basePath(base);
    std::filesystem::path relativePath(relative);
    return (basePath / relativePath).string();
}

/**
 * @brief Valida si el archivo tiene una extension de modelo soportada.
 */
bool FileSystem::isValidModelExtension(const std::string& path) {
    std::string ext = std::filesystem::path(path).extension().string();
    
    // Convertir a minusculas para comparacion robusta
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c){ 
        return std::tolower(c); 
    });

    return (ext == ".gguf" || ext == ".bin");
}

/*
Detalles de la Implementación Multiplataforma
El Operador /: En joinPaths, se nota el uso de basePath / relativePath. Esta es una característica de C++ que selecciona automáticamente el separador correcto (\ en Windows, / en macOS/Linux). Es la clave para que el código funcione en Caracas sobre cualquier PC.

Normalización de Extensiones: En isValidModelExtension, convertimos la extensión a minúsculas. Esto evita errores comunes donde un archivo se llama GEMMA.GGUF y el sistema no lo reconoce por sensibilidad a mayúsculas.

Rutas Dinámicas: current_path() nos permite que, si el usuario instala tu aplicación en cualquier carpeta, el motor siempre sepa dónde está parado para buscar la subcarpeta models/.
*/