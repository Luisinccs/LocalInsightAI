/**
 * @file GemmaProvider.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion del proveedor de inferencia para Gemma 3.
 */

#include "inference/GemmaProvider.hpp"
#include "utils/Logger.hpp"
#include <thread>
#include <chrono>

namespace LocalInsight::Inference;

using namespace LocalInsight::Utils;

/**
 * @brief Constructor: Inicializa punteros en nulo y configura el hardware.
 */
GemmaProvider::GemmaProvider() {
    _isModelLoaded = false;
    _ctx = nullptr;
    _model = nullptr;
    configureHardware();
}

/**
 * @brief Destructor: Asegura que se liberen los recursos antes de cerrar.
 */
GemmaProvider::~GemmaProvider() {
    unload();
}

/**
 * @brief Configura la aceleracion por hardware segun disponibilidad.
 */
void GemmaProvider::configureHardware() {
    Logger::log("Configuring hardware acceleration...");
    // Aqui se detectaria CUDA (Windows) o Metal (macOS)
    #ifdef __APPLE__
        Logger::log("Hardware: Apple Silicon (Metal) detected.");
    #else
        Logger::log("Hardware: CPU/CUDA backend detected.");
    #endif
}

/**
 * @brief Carga el modelo Gemma 3 en la memoria.
 */
bool GemmaProvider::loadModel(const std::string& modelPath) {
    Logger::log("Loading Gemma weights from: " + modelPath);
    
    // Simulacion de carga de tensores
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    
    _isModelLoaded = true;
    Logger::log("Weights loaded into VRAM/RAM successfully.");
    return true;
}

/**
 * @brief Ejecuta la inferencia localmente.
 */
std::string GemmaProvider::predict(const std::string& prompt) {
    if (!isReady()) {
        return "Error: Provider not ready.";
    }

    Logger::log("Executing local inference on GPU...");
    
    // En una implementacion real, aqui se llamaria a la funcion de decodificacion
    // de la libreria nativa (ej. llama_decode)
    return "[Local Gemma 3 Response] Esta es una respuesta generada localmente en hardware nativo.";
}

/**
 * @brief Libera los punteros y limpia la memoria.
 */
void GemmaProvider::unload() {
    if (_isModelLoaded) {
        Logger::log("Unloading model and clearing VRAM...");
        // nullptr logic for internal contexts here
        _isModelLoaded = false;
    }
}

/*
Consideraciones de Inferencia Local
Detección de Hardware: La función configureHardware es crucial. En Caracas, donde el hardware varía mucho, tener una lógica que decida entre usar núcleos AVX2 de un procesador Intel o los Tensor Cores de una NVIDIA es lo que hará que tu software sea profesional.

Ciclo de Vida: El destructor llama a unload(). Esto es fundamental en aplicaciones que se integran en UIs nativas (Swift/C#), ya que si el usuario cierra una ventana de chat, debemos liberar esos 8GB-16GB de RAM de inmediato.

Simulación de Latencia: He añadido un pequeño sleep_for para imitar el tiempo que tarda el hardware en inicializar los pesos del modelo.
*/