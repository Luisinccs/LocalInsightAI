/**
 * @file ContextManager.hpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Gestion de memoria y contexto de conversacion para el motor de IA.
 * * Este componente administra el historial de mensajes para asegurar que 
 * el modelo mantenga la coherencia sin exceder el limite de tokens.
 */

#pragma once

#include <string>
#include <vector>

namespace LocalInsight::Core {

/**
 * @struct ChatMessage
 * @brief Estructura simple para representar un turno en la conversacion.
 */
struct ChatMessage {
    std::string role;    ///< "user" o "assistant"
    std::string content; ///< Contenido del mensaje
};

/**
 * @class ContextManager
 * @brief Administrador del historial de interacciones.
 */
class ContextManager {
private:
    std::vector<ChatMessage> _history; ///< Historial de mensajes acumulados
    size_t _maxHistorySize;           ///< Numero maximo de mensajes a recordar

public:
    /**
     * @brief Constructor con limite de memoria opcional.
     * @param maxEntries Cantidad de mensajes que el motor recordara.
     */
    ContextManager(size_t maxEntries = 10);

    /**
     * @brief Agrega un nuevo mensaje al historial.
     * @param role Identificador del emisor.
     * @param message Texto del mensaje.
     */
    void addMessage(const std::string& role, const std::string& message);

    /**
     * @brief Formatea el historial completo en un unico prompt para el modelo.
     * @return std::string Prompt formateado segun el estandar de Gemma 3.
     */
    std::string getFormattedPrompt() const;

    /**
     * @brief Limpia toda la memoria de la conversacion actual.
     */
    void clearHistory();

    /**
     * @brief Obtiene el numero actual de mensajes almacenados.
     */
    size_t getMessageCount() const { return _history.size(); }
};

} // namespace LocalInsight::Core

/*
Notas Técnicas sobre el Contexto
Gestión de Tokens: En un entorno local, el contexto es el recurso más caro después de la carga inicial del modelo. Este manager permite "olvidar" los mensajes más antiguos (FIFO) si se excede el _maxHistorySize, evitando que la aplicación colapse por falta de RAM.

Formateo de Prompt: Cada modelo (como Gemma 3) requiere un formato específico (ej: <start_of_turn>user...<end_of_turn>). El método getFormattedPrompt centraliza esta lógica para que el AIEngine no tenga que preocuparse por etiquetas especiales.

Eficiencia: El uso de std::vector<ChatMessage> permite un acceso rápido y secuencial, ideal para generar el prompt final en cada turno.
*/