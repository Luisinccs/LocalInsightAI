/**
 * @file FileSystem.hpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Utilidades para la gestion de archivos y rutas multiplataforma.
 * * Facilita la localizacion de modelos y archivos de configuracion
 * asegurando la compatibilidad entre Windows y macOS.
 */

#pragma once

#include <string>
#include <filesystem>

namespace LocalInsight::Utils {

/**
 * @class FileSystem
 * @brief Clase de utilidad para operaciones comunes del sistema de archivos.
 */
class FileSystem {
public:
    /**
     * @brief Verifica si un archivo existe en la ruta especificada.
     * @param path Ruta al archivo (relativa o absoluta).
     */
    static bool exists(const std::string& path);

    /**
     * @brief Obtiene la ruta absoluta del directorio de ejecucion.
     * @return std::string Ruta completa al directorio del binario.
     */
    static std::string getExecutableDirectory();

    /**
     * @brief Combina dos fragmentos de ruta usando el separador nativo del OS.
     * @param base Directorio base.
     * @param relative Ruta relativa o archivo.
     */
    static std::string joinPaths(const std::string& base, const std::string& relative);

    /**
     * @brief Valida si la extension del archivo es un modelo compatible (ej. .gguf).
     * @param path Ruta al archivo del modelo.
     */
    static bool isValidModelExtension(const std::string& path);
};

} // namespace LocalInsight::Utils

/*
Importancia:

Rutas Relativas: Los modelos de IA suelen ser grandes. Este componente permite que la aplicación busque automáticamente en la carpeta ../models/ relativa al ejecutable, evitando que el usuario tenga que configurar rutas manualmente.

Seguridad: Antes de intentar cargar un modelo de 15GB en la RAM, el AIEngine usará exists() y isValidModelExtension() para evitar cierres inesperados (crashes).

Abstracción de Separadores: En Windows se usa \ y en Mac /. Al usar std::filesystem, el código se vuelve "ciego" a estas diferencias, eliminando bugs de archivos no encontrados.
*/