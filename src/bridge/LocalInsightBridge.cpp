/**
 * @file LocalInsightBridge.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion del puente de enlace C para consumo externo.
 */

#include "bridge/LocalInsightBridge.h"
#include "core/AIEngine.hpp"
#include "inference/GemmaProvider.hpp"
#include <memory>
#include <cstring>

using namespace LocalInsight::Core;
using namespace LocalInsight::Inference;

extern "C" {

/**
 * @brief Crea una instancia de AIEngine y carga el modelo.
 */
void* CreateEngine(const char* modelPath) {
    try {
        // Creamos el proveedor especifico de Gemma
        auto provider = std::make_unique<GemmaProvider>();
        
        // Instanciamos el motor orquestador
        auto engine = new AIEngine(std::move(provider));
        
        // Intentamos inicializar con la ruta del modelo
        if (engine->initialize(std::string(modelPath))) {
            return static_cast<void*>(engine);
        }
        
        delete engine;
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

/**
 * @brief Ejecuta una consulta y gestiona el paso de strings a la UI.
 */
const char* QueryEngine(void* enginePtr, const char* question) {
    if (enginePtr == nullptr) {
        return "Error: Engine instance is null.";
    }

    auto engine = static_cast<AIEngine*>(enginePtr);
    
    // Obtenemos la respuesta del motor (std::string)
    static std::string lastResponse; 
    lastResponse = engine->ask(std::string(question));
    
    // Retornamos el puntero al buffer de la cadena estatica
    return lastResponse.c_str();
}

/**
 * @brief Libera la memoria ocupada por el motor.
 */
void DestroyEngine(void* enginePtr) {
    if (enginePtr != nullptr) {
        auto engine = static_cast<AIEngine*>(enginePtr);
        delete engine;
    }
}

} // extern "C"

/*
Consideraciones Críticas de este Componente

Manejo de Memoria de Strings: En QueryEngine, se ha usado una variable static std::string. Esto es una técnica común en puentes C para evitar que el string desaparezca de la memoria antes de que C# o Swift lo lean. Nota: En una versión de producción, lo ideal sería copiar el buffer a una memoria asignada por el llamador o usar un buffer compartido.

Castings de Punteros: El uso de static_cast<AIEngine*> permite recuperar la funcionalidad completa de la clase C++ a partir del puntero anónimo (void*) que guardó la interfaz de usuario.

Seguridad (Try/Catch): Se ha incluido un bloque try-catch básico en la creación. Es vital que el motor de C++ nunca "lance" una excepción que llegue a la UI nativa, ya que esto causaría un cierre inesperado (crash) instantáneo de la aplicación en Windows o Mac.
*/