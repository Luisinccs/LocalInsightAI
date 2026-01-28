/**
 * @file IInferenceProvider.hpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Definicion de la interfaz base para proveedores de inferencia.
 * * Este componente permite desacoplar el motor de IA (Gemma 3) de la 
 * implementacion tecnica del hardware (CPU/GPU) y las librerias externas.
 */

#pragma once

#include <string>
#include <vector>

namespace LocalInsight::Inference {

/**
 * @class IInferenceProvider
 * @brief Interfaz abstracta para la ejecucion de modelos de lenguaje.
 */
class IInferenceProvider {
public:
    /**
     * @brief Destructor virtual puro para asegurar la limpieza en clases derivadas.
     */
    virtual ~IInferenceProvider() = default;

    /**
     * @brief Carga los pesos del modelo en la memoria (RAM/VRAM).
     * @param modelPath Ruta al archivo del modelo cuantizado.
     * @return true si el modelo se cargo y el hardware es compatible.
     */
    virtual bool loadModel(const std::string& modelPath) = 0;

    /**
     * @brief Genera una respuesta basada en un prompt de entrada.
     * @param prompt Texto enviado por el usuario.
     * @return std::string Respuesta generada por el modelo.
     */
    virtual std::string predict(const std::string& prompt) = 0;

    /**
     * @brief Verifica si el proveedor esta listo para procesar consultas.
     * @return true si el modelo esta cargado y el contexto inicializado.
     */
    virtual bool isReady() const = 0;

    /**
     * @brief Libera los recursos de hardware utilizados por el proveedor.
     */
    virtual void unload() = 0;
};

} // namespace LocalInsight::Inference

/*
Puntos clave de este diseño
Polimorfismo: Al usar métodos virtuales puros (= 0), obligamos a cualquier implementación futura (como un GemmaProvider) a cumplir estrictamente con este contrato.

Abstracción de Hardware: El loadModel es el lugar donde se decidirá si se usa CUDA (NVIDIA), Metal (Apple) o simplemente la CPU. El resto de la aplicación no necesita saber cómo ocurre la magia.

Seguridad de Memoria: El uso de un destructor virtual es crítico en C++ cuando se trabaja con interfaces, para evitar fugas de memoria (memory leaks) al destruir objetos a través de un puntero a la interfaz.
*/