/**
 * @file AIEngine.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion del orquestador central del motor de IA.
 */

#include "core/AIEngine.hpp"
#include "utils/FileSystem.hpp"
#include "utils/Logger.hpp"

namespace LocalInsight::Core { 

using namespace LocalInsight::Utils;

/**
 * @brief Constructor que inyecta la implementacion de inferencia.
 */
AIEngine::AIEngine(std::unique_ptr<Inference::IInferenceProvider> provider) {
    _provider = std::move(provider);
    _isInitialized = false;
    Logger::log("AIEngine instance created.");
}

/**
 * @brief Inicializa el motor y carga el modelo Gemma 3.
 */
bool AIEngine::initialize(const std::string& path) {
    Logger::log("Initializing engine with model: " + path);
    
    if (!validateModelPath(path)) {
        Logger::error("Invalid model path or file not found: " + path);
        return false;
    }

    if (_provider->loadModel(path)) {
        _modelPath = path;
        _isInitialized = true;
        Logger::log("Engine initialized successfully.");
        return true;
    }

    Logger::error("Provider failed to load the model.");
    return false;
}

/**
 * @brief Procesa la consulta del usuario y retorna la respuesta.
 */
std::string AIEngine::ask(const std::string& prompt) {
    if (!isReady()) {
        return "Error: Engine is not initialized.";
    }

    try {
        Logger::log("Processing prompt: " + prompt);
        return _provider->predict(prompt);
    } catch (const std::exception& e) {
        Logger::error("Exception during inference: " + std::string(e.what()));
        return "Error: An internal exception occurred.";
    }
}

/**
 * @brief Valida la existencia y extension del modelo.
 */
bool AIEngine::validateModelPath(const std::string& path) {
    return FileSystem::exists(path) && FileSystem::isValidModelExtension(path);
}

}

/*
Aspectos Destacados de la Implementación
Validación Previa: Antes de delegar la carga al InferenceProvider (que puede ser una operación costosa en tiempo y RAM), el motor usa el FileSystem para asegurar que el archivo es válido.

Manejo de Excepciones: Aunque el Bridge protege la UI, el AIEngine captura excepciones internamente para registrarlas a través del Logger, permitiéndote depurar fallos de inferencia en Caracas sin que el cliente vea un error crítico del sistema.

Inyección de Dependencias en Acción:  _provider->loadModel(path) se llama sin saber si es Gemma u otro modelo. Esto hace que el código sea robusto y fácil de testear.
*/