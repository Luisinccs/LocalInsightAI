/**
 * @file ContextManager.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Implementacion de la gestion de historial y contexto.
 */

#include "core/ContextManager.hpp"
#include <sstream>

namespace LocalInsight::Core;

/**
 * @brief Constructor con inicializacion de limites.
 */
ContextManager::ContextManager(size_t maxEntries) {
    _maxHistorySize = maxEntries;
}

/**
 * @brief Agrega mensajes y mantiene el tamaño del buffer (FIFO).
 */
void ContextManager::addMessage(const std::string& role, const std::string& message) {
    // Si excedemos el limite, eliminamos el mensaje mas antiguo (el primero)
    if (_history.size() >= _maxHistorySize) {
        _history.erase(_history.begin());
    }

    _history.push_back({role, message});
}

/**
 * @brief Aplica el formato de plantilla (Prompt Template) de Gemma 3.
 */
std::string ContextManager::getFormattedPrompt() const {
    std::stringstream prompt;

    for (const auto& msg : _history) {
        // Formato estandar para Gemma: <start_of_turn>role\ncontent<end_of_turn>
        prompt << "<start_of_turn>" << msg.role << "\n" 
               << msg.content << "<end_of_turn>\n";
    }

    // Añadimos el disparador final para que el modelo responda
    prompt << "<start_of_turn>model\n";

    return prompt.str();
}

/**
 * @brief Resetea el historial de la sesion.
 */
void ContextManager::clearHistory() {
    _history.clear();
}

/*
Análisis de la Lógica de Contexto
Estrategia FIFO (First-In, First-Out): Al usar _history.erase(_history.begin()), garantizamos que la aplicación nunca colapse por falta de RAM al procesar conversaciones largas. Es una medida de seguridad vital para dispositivos con hardware limitado en entornos locales.

Prompt Template de Gemma 3: El uso de etiquetas como <start_of_turn> es lo que permite que el modelo entienda quién es el usuario y quién es el asistente. Sin esto, la IA podría confundirse y empezar a generar texto incoherente.

Eficiencia con Stringstream: Usamos std::stringstream para construir el prompt final, lo cual es mucho más eficiente en términos de memoria y CPU que concatenar strings repetidamente con el operador +.
*/