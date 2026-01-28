/**
 * @file AIEngine.hpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Clase orquestadora central para la logica de LocalInsight AI.
 */

#pragma once

#include <memory>
#include <string>
#include "inference/IInferenceProvider.hpp"

namespace LocalInsight::Core {

/**
 * @class AIEngine
 * @brief Orquestador que vincula la interfaz externa con el motor de inferencia.
 */
class AIEngine {
private:
    
    std::unique_ptr<Inference::IInferenceProvider> _provider; ///< Proveedor de inferencia de IA
    std::string _modelPath; ///< Ruta al archivo del modelo cargado
    bool _isInitialized; ///< Estado de inicializacion del motor
    
    /**
     * @brief Valida si el archivo del modelo existe antes de cargar.
     * @param path Ruta al archivo .gguf.
     */
    bool validateModelPath(const std::string& path);
    

public:
    
    /**
     * @brief Constructor que inyecta una implementacion de inferencia.
     * @param provider Puntero unico a una instancia de IInferenceProvider.
     */
    AIEngine(std::unique_ptr<Inference::IInferenceProvider> provider);

    /**
     * @brief Inicializa el motor cargando el modelo especificado.
     * @param path Ruta completa o relativa al modelo Gemma 3.
     * @return true si la carga fue exitosa.
     */
    bool initialize(const std::string& path);

    /**
     * @brief Procesa una consulta y devuelve la respuesta del modelo.
     * @param prompt Texto de entrada del usuario.
     * @return std::string Respuesta generada localmente.
     */
    std::string ask(const std::string& prompt);

    /**
     * @brief Verifica el estado actual del motor.
     */
    bool isReady() const { return _isInitialized && _provider->isReady(); }
    
};

} // namespace LocalInsight::Core

/*
Análisis de Diseño
Inyección de Dependencias: El constructor recibe un std::unique_ptr<IInferenceProvider>. Esto significa que AIEngine no sabe (ni le importa) si está usando Gemma, Llama o un simulador de pruebas; solo sabe que puede llamar a predict().

Encapsulamiento de Errores: La función initialize devuelve un booleano, permitiendo que la UI nativa (Swift/C#) maneje visualmente un error de carga (por ejemplo, si falta el archivo del modelo en la carpeta models/).

Seguridad de Memoria: Al usar std::unique_ptr, el proveedor de inferencia se destruirá automáticamente cuando el AIEngine salga de alcance, evitando memory leaks en aplicaciones de larga duración.
*/