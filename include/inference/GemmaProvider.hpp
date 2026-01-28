/**
 * @file GemmaProvider.hpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion especifica para el modelo Google Gemma 3.
 */

#pragma once


#include <string>
#include "inference/IInferenceProvider.hpp"

namespace LocalInsight::Inference {

/**
 * @class GemmaProvider
 * @brief Proveedor de inferencia optimizado para pesos de la familia Gemma.
 */
class GemmaProvider : public IInferenceProvider {
private:
    bool _isModelLoaded; ///< Indica si los pesos estan en memoria
    void* _ctx; ///< Puntero al contexto interno del backend (ej. llama_context)
    void* _model; ///< Puntero al modelo cargado (ej. llama_model)

    /**
     * @brief Configura los parametros de hardware (Hilos CPU / Backend GPU).
     */
    void configureHardware();

public:
    /**
     * @brief Constructor predeterminado del proveedor.
     */
    GemmaProvider();

    /**
     * @brief Destructor para liberar recursos de GPU/VRAM.
     */
    virtual ~GemmaProvider();

    /**
     * @brief Carga el archivo .gguf de Gemma 3 y prepara el grafo de computo.
     * @param modelPath Ruta local al archivo del modelo.
     */
    bool loadModel(const std::string& modelPath) override;

    /**
     * @brief Ejecuta la inferencia de tokens para generar texto.
     * @param prompt Consulta procesada por el orquestador.
     */
    std::string predict(const std::string& prompt) override;

    /**
     * @brief Comprueba si el motor esta listo para inferencia.
     */
    bool isReady() const override { return _isModelLoaded; }

    /**
     * @brief Descarga el modelo y limpia la memoria de video.
     */
    void unload() override;
};

} // namespace LocalInsight::Inference

/*
Detalles Técnicos Relevantes
Herencia: Al heredar de IInferenceProvider y usar override, garantizamos que AIEngine pueda usar esta clase de forma transparente.

Punteros void* internos: Se utilizaron punteros opacos para el contexto y el modelo. Esto permite que el archivo de cabecera (.hpp) sea ligero y no obligue a quien lo use a incluir todas las librerías pesadas de IA; solo el archivo .cpp conocerá los detalles de implementación del backend.

Gestión de Hardware: El método configureHardware (interno) es el que detectará si el usuario tiene una GPU en su oficina o si debe ejecutar el modelo en la CPU, algo crucial para el mercado de Caracas.
*/