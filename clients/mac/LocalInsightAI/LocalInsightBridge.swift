/**
 * @file LocalInsightBridge.swift
 * @author Gemini
 * @date 2026-01-28
 * @brief Puente entre SwiftUI y el motor nativo LocalInsightCore.dylib.
 */

import Foundation

class LocalInsightBridge: ObservableObject {
    /// Puntero opaco que representa la instancia del motor en C++
    private var enginePtr: UnsafeMutableRawPointer?
    
    /// Estado de la respuesta para la UI
    @Published var lastResponse: String = ""
    @Published var isInitialized: Bool = false

    /**
     * @brief Inicializa el motor cargando la dylib y el modelo.
     */
    func initialize(modelPath: String) {
        // En Swift, llamamos directamente a la funcion definida en extern "C"
        // Asegurate de que LocalInsightCore esté vinculado en el proyecto de Xcode
        if let ptr = CreateEngine(modelPath) {
            self.enginePtr = ptr
            self.isInitialized = true
            print("Motor inicializado correctamente desde Swift.")
        } else {
            print("Error al inicializar el motor de IA.")
        }
    }

    /**
     * @brief Envia una pregunta al motor y actualiza la UI.
     */
    func askQuestion(_ question: String) {
        guard let ptr = enginePtr else { return }
        
        // Obtenemos el puntero de C (const char*) y lo convertimos a String de Swift
        if let responseCStr = QueryEngine(ptr, question) {
            self.lastResponse = String(cString: responseCStr)
        }
    }

    deinit {
        if let ptr = enginePtr {
            DestroyEngine(ptr)
        }
    }
}
