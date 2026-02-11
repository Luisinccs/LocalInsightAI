/**
 * @file ViewController.swift
 * @author Gemini
 * @date 2026-01-28
 * @brief Interfaz de usuario programatica en AppKit para LocalInsight.
 */

import Cocoa

class ViewController: NSViewController {
    
    // MARK: - UI Components
    private let scrollView = NSScrollView()
    private let outputText = NSTextView()
    private let inputField = NSTextField()
    private let sendButton = NSButton()
    
    // Bridge nativo
    private let aiBridge = LocalInsightBridge()

    // MARK: - Lifecycle
    override func loadView() {
        // Definimos la vista principal del controlador
        self.view = NSView(frame: NSRect(x: 0, y: 0, width: 600, height: 400))
        setupUI()
        setupConstraints()
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Inicializar el motor con la ruta del modelo
        // Nota: Ajusta la ruta segun donde coloques el .gguf en tu Mac
        let modelPath = "/Users/luis_sonoma/Desarrollo/LocalInsightAI/build/models/gemma-3-27b-q4.gguf"
        aiBridge.initialize(modelPath: modelPath)
    }

    // MARK: - Setup
    private func setupUI() {
        // Configuracion del area de salida (Chat History)
        outputText.isEditable = false
        outputText.font = .systemFont(ofSize: 13)
        outputText.backgroundColor = .clear
        
        scrollView.hasVerticalScroller = true
        scrollView.documentView = outputText
        scrollView.drawsBackground = false
        view.addSubview(scrollView)

        // Campo de entrada
        inputField.placeholderString = "Preguntale algo a Gemma 3..."
        inputField.bezelStyle = .roundedBezel
        inputField.font = .systemFont(ofSize: 14)
        view.addSubview(inputField)

        // Boton de envio
        sendButton.title = "Enviar"
        sendButton.bezelStyle = .rounded
        sendButton.target = self
        sendButton.action = #selector(sendClicked)
        view.addSubview(sendButton)
        
        // Activar Auto Layout para todos
        [scrollView, inputField, sendButton].forEach { $0.translatesAutoresizingMaskIntoConstraints = false }
    }

    private func setupConstraints() {
        NSLayoutConstraint.activate([
            // ScrollView (Area de chat)
            scrollView.topAnchor.constraint(equalTo: view.topAnchor, constant: 20),
            scrollView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20),
            scrollView.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20),
            scrollView.bottomAnchor.constraint(equalTo: inputField.topAnchor, constant: -12),

            // InputField
            inputField.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20),
            inputField.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -20),
            inputField.heightAnchor.constraint(equalToConstant: 30),

            // Button
            sendButton.leadingAnchor.constraint(equalTo: inputField.trailingAnchor, constant: 8),
            sendButton.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20),
            sendButton.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -20),
            sendButton.widthAnchor.constraint(equalToConstant: 80),
            sendButton.heightAnchor.constraint(equalToConstant: 32)
        ])
    }

    // MARK: - Actions
    @objc private func sendClicked() {
        let question = inputField.stringValue
        guard !question.isEmpty else { return }

        // Agregar pregunta al log visual
        outputText.string += "\nUser: \(question)\n"
        
        // Inferencia
        aiBridge.askQuestion(question)
        
        // Mostrar respuesta
        outputText.string += "Gemma: \(aiBridge.lastResponse)\n"
        inputField.stringValue = ""
        
        // Scroll al final
        outputText.scrollToEndOfDocument(nil)
    }
}
