/**
 * @file Logger.hpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Sistema de registro de eventos y errores para el motor LocalInsight.
 * * Provee una interfaz unificada para la depuracion y el monitoreo del 
 * estado del sistema en entornos multiplataforma.
 */

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

namespace LocalInsight::Utils {

/**
 * @enum LogLevel
 * @brief Niveles de severidad para el registro de eventos.
 */
enum class LogLevel {
    Info,    ///< Informacion general de operacion
    Warning, ///< Advertencias que no detienen la ejecucion
    Error    ///< Errores criticos del sistema
};

/**
 * @class Logger
 * @brief Clase estatica para el manejo de logs en consola y archivo.
 */
class Logger {
private:
    static std::mutex _logMutex; ///< Asegura que el log sea seguro entre hilos (Thread-safe)

    /**
     * @brief Convierte el nivel de log a una cadena de texto.
     */
    static std::string levelToString(LogLevel level);

public:
    /**
     * @brief Registra un mensaje en la salida estandar y opcionalmente en archivo.
     * @param message Texto descriptivo del evento.
     * @param level Severidad del evento (predeterminado: Info).
     */
    static void log(const std::string& message, LogLevel level = LogLevel::Info);

    /**
     * @brief Metodo de conveniencia para registrar errores criticos.
     * @param message Descripcion del error.
     */
    static void error(const std::string& message) { log(message, LogLevel::Error); }
};

} // namespace LocalInsight::Utils

/*
Consideraciones del Diseño
Thread-Safety: Al usar std::mutex, garantizamos que si el motor de IA está procesando tokens en un hilo y la UI envía una petición en otro, los mensajes de log no se mezclen ni corrompan la salida.

Facilidad de Uso: Al ser métodos estáticos, puedes llamar a Logger::error("Mensaje") desde cualquier archivo del proyecto simplemente incluyendo la cabecera.

Abstracción de Salida: Aunque ahora use std::cout, este diseño permite que en el futuro los logs se redirijan a un archivo en la carpeta data/ o a la consola de depuración de Visual Studio/Xcode.
*/