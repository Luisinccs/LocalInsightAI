/**
 * @file main.cpp
 * @author Gemini
 * @date 2026-01-27
 * @brief Punto de entrada para pruebas de consola del motor LocalInsight AI.
 */

#include "core/AIEngine.hpp"
#include "inference/GemmaProvider.hpp"
#include "utils/Logger.hpp"
#include <iostream>
#include <string>
#include <memory>

using namespace LocalInsight::Core;
using namespace LocalInsight::Inference;
using namespace LocalInsight::Utils;

/**
 * @brief Funcion principal de prueba del sistema.
 */
int main(int argc, char* argv[]) {
    Logger::log("--- LocalInsight AI: Console Test Pilot ---");

    // 1. Configuracion de la ruta del modelo (por defecto o por argumento)
    std::string modelPath = "models/gemma-3-27b-q4.gguf";
    if (argc > 1) {
        modelPath = argv[1];
    }

    // 2. Inyeccion de dependencias: Creamos el proveedor y el motor
    auto provider = std::make_unique<GemmaProvider>();
    auto engine = std::make_unique<AIEngine>(std::move(provider));

    // 3. Inicializacion
    if (!engine->initialize(modelPath)) {
        Logger::error("Failed to initialize the engine. check model path.");
        return -1;
    }

    // 4. Bucle de interaccion simple (REPL)
    std::string userInput;
    std::cout << "\nAI Ready. Type 'exit' to quit." << std::endl;

    while (true) {
        std::cout << "\nUser > ";
        std::getline(std::cin, userInput);

        if (userInput == "exit" || userInput == "quit") {
            break;
        }

        if (userInput.empty()) {
            continue;
        }

        // Ejecutar inferencia
        std::string response = engine->ask(userInput);
        std::cout << "\nLocalInsight > " << response << std::endl;
    }

    Logger::log("Shutting down engine...");
    return 0;
}

/*
Cómo funciona este Piloto
Flexibilidad de Rutas: El programa busca el modelo en models/gemma-3-27b-q4.gguf por defecto, pero te permite pasarle una ruta distinta como argumento al ejecutarlo desde la terminal (ej: ./LocalInsightAI C:/AI/modelo.gguf).

Ciclo de Vida Controlado: Usamos std::unique_ptr para el engine. Esto garantiza que, al escribir "exit" y salir del main, el motor, el proveedor y el modelo se descarguen de la RAM/VRAM de forma limpia y automática.

Simulación de Interacción: Este bucle while imita exactamente lo que hará tu UI nativa en C# o Swift, pero en un entorno simplificado de texto.
*/