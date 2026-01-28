/**
 * @file Logger.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion del sistema de registro de eventos.
 */

#include "utils/Logger.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

namespace LocalInsight::Utils;

// Inicializacion del miembro estatico (mutex)
std::mutex Logger::_logMutex;

/**
 * @brief Registra un mensaje con marca de tiempo y nivel de severidad.
 */
void Logger::log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(_logMutex);

    // Obtener la hora actual del sistema
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    auto localTime = *std::localtime(&timeT);

    // Formatear la salida: [AAAA-MM-DD HH:MM:SS] [LEVEL] Mensaje
    std::cout << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] "
              << "[" << levelToString(level) << "] "
              << message << std::endl;
}

/**
 * @brief Helper para convertir el enum en texto legible.
 */
std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Info:    return "INFO";
        case LogLevel::Warning: return "WARN";
        case LogLevel::Error:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

/*
Análisis de la Implementación
Thread-Safety: El std::lock_guard bloquea el acceso al flujo de salida (std::cout) mientras un hilo escribe. Esto evita que los logs salgan "mordidos" o desordenados cuando el motor de Gemma está trabajando en segundo plano.

Formato ISO: Se ha utilizado un formato de fecha estándar (%Y-%m-%d), al igual que en los encabezados, manteniendo la consistencia visual en todo el proyecto.

Extensibilidad: Aunque ahora imprimimos en consola, la estructura permite que en una fase posterior simplemente se añada un std::ofstream dentro del log() para guardar todo en un archivo .txt dentro de la carpeta data/.
*/