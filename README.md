# LocalInsightAI
🚀 LocalInsight AI: High-performance C++ Core for local LLM inference (Gemma 3). Privacy-first, zero-token-cost architecture with native bridges for Swift (macOS) and C# (Windows).

# LocalInsight AI 🧠

**LocalInsight AI** es un motor de inferencia de alto rendimiento diseñado para ejecutar **Google Gemma 3** de forma local, privada y eficiente. Este proyecto nace de la necesidad de desvincular los costos operativos de la IA del crecimiento de usuarios, permitiendo un modelo de negocio basado en licencias y privacidad total.



---

## 🏗️ Arquitectura de Componentes

El proyecto utiliza una arquitectura desacoplada para garantizar el máximo rendimiento en hardware local:

* **Core Engine (C++20):** Gestiona la carga de tensores y la orquestación de la IA.
* **Inference Provider:** Abstracción nativa para aceleración por hardware (CUDA, Metal, AVX2).
* **Native Bridge:** Interfaz C-API compatible con Swift (macOS/iOS) y C# (Windows/WinUI3).

## 🚀 Ventajas Estratégicas (2026 Model)

1.  **Costo Operativo Cero:** Sin APIs de terceros. Una vez descargado el modelo, la inferencia no consume créditos.
2.  **Privacidad por Diseño:** Los datos nunca salen de la infraestructura del cliente. Ideal para sectores legales, médicos y financieros.
3.  **Independencia Tecnológica:** Control total sobre el ciclo de vida del modelo y sus actualizaciones.

---

## 📂 Estructura del Proyecto

| Carpeta | Descripción |
| :--- | :--- |
| `include/` | Cabeceras (.hpp) y definiciones del Bridge. |
| `src/` | Implementación del motor en C++ nativo. |
| `models/` | Directorio para archivos .gguf (Gemma 3). |
| `tests/` | Pruebas de rendimiento y precisión de tokens. |

---

## 🛠️ Guía de Inicio Rápido

### Requisitos Previos
* CMake 3.20+
* Compilador compatible con C++20 (MSVC, Clang o GCC).
* Gemma 3 Weights (.gguf format).

### Compilación (CLI)
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Uso del Bridge (C# / Swift)
El núcleo se compila como una librería dinámica (.dll / .dylib). Puedes consumirla importando el encabezado LocalInsightBridge.h en tu proyecto nativo.

## 📄 Estándares de Código
Este proyecto sigue normativas estrictas de desarrollo:

Doxygen: Documentación técnica integrada en el código.

Naming: Variables de clase con prefijo _ y notación camelCase.

Performance: Gestión manual de memoria optimizada para hardware limitado.

🗺️ Roadmap
[ ] Implementación de RAG local (SQLite Vector).

[ ] Soporte para cuantización de 4-bits (GGUF).

[ ] SDK para integración en aplicaciones móviles.

### **Ilustración: Branding del Repositorio**
Para el encabezado del README o la imagen de previsualización (social preview), aquí tienes el diseño unificado:

```xml
<svg viewBox="0 0 500 200" xmlns="http://www.w3.org/2000/svg">
  <rect width="100%" height="100%" fill="#f8f9fa"/>
  
  <rect x="50" y="50" width="100" height="100" rx="8" fill="none" stroke="#457b9d" stroke-width="3"/>
  <circle cx="100" cy="100" r="20" fill="#457b9d" opacity="0.2"/>
  <path d="M 85 100 L 115 100 M 100 85 L 100 115" stroke="#457b9d" stroke-width="3"/>

  <text x="170" y="90" font-family="sans-serif" font-size="32" font-weight="bold" fill="#333">LocalInsight AI</text>
  <text x="170" y="125" font-family="sans-serif" font-size="16" fill="#457b9d">High-Performance Local IA Core</text>
  
  <line x1="170" y1="105" x2="450" y2="105" stroke="#e9ecef" stroke-width="2"/>
  
  <rect x="170" y="140" width="60" height="20" rx="4" fill="#333"/>
  <text x="178" y="154" font-family="sans-serif" font-size="10" fill="white">C++20</text>
  
  <rect x="240" y="140" width="80" height="20" rx="4" fill="#333"/>
  <text x="248" y="154" font-family="sans-serif" font-size="10" fill="white">GEMMA 3</text>
</svg>
```
