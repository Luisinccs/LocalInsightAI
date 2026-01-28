/**
 * @file LocalInsightBridge.h
 * @author Gemini
 * @date 2026-01-27
 * @brief Interfaz de enlace C para interoperabilidad multiplataforma.
 * * Este archivo define los puntos de entrada para que lenguajes como 
 * C# (Windows) y Swift (macOS) puedan interactuar con el motor 
 * de inferencia de Gemma 3 escrito en C++.
 */

#pragma once

// Macros para exportacion de DLL (Windows) o Visibilidad (macOS/Linux)
#if defined(_WIN32)
    #define LOCAL_API __declspec(dllexport)
#else
    #define LOCAL_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Crea e inicializa una instancia del motor de IA.
     * @param modelPath Ruta al archivo binario del modelo (.gguf).
     * @return Un puntero opaco a la instancia del motor, o null si falla.
     */
    LOCAL_API void* CreateEngine(const char* modelPath);

    /**
     * @brief Procesa una consulta de texto a traves del motor local.
     * @param enginePtr Puntero a la instancia del motor devuelto por CreateEngine.
     * @param question Texto de la pregunta del usuario.
     * @return Una cadena de texto con la respuesta (debe ser tratada como constante).
     */
    LOCAL_API const char* QueryEngine(void* enginePtr, const char* question);

    /**
     * @brief Libera la memoria y destruye la instancia del motor.
     * @param enginePtr Puntero a la instancia que se desea destruir.
     */
    LOCAL_API void DestroyEngine(void* enginePtr);

#ifdef __cplusplus
}
#endif

/*
Notas de Implementación Técnica
Punteros Opacos (void*): C# y Swift no conocen la estructura de las clases internas de C++. Al pasar un void*, les entregamos una "referencia" que ellos guardan y nos devuelven en cada llamada, permitiendo que el motor mantenga el estado de la conversación (contexto) sin exponer la memoria interna.

Manejo de Strings: se ha usado const char* por ser el tipo de dato universal para texto entre lenguajes. En la implementación (.cpp), deberemos tener cuidado con la memoria de los strings que devolvemos a la UI.

Directiva extern "C": Esta es vital. Evita que el compilador de C++ cambie el nombre de las funciones (mangling), permitiendo que DllImport en C# encuentre la función CreateEngine exactamente con ese nombre.
*/