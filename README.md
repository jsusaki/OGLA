# OGLA: OpenGL Abstraction
OGLA : OpenGL Abstraction is a reference renderer implemented in C++. 

The objective of this project is to abstract renderer functionality to serve as a foundation for simple 2D/3D real-time applications.

The design principle applied was to identify rendering engine concepts, and ecapsulate these in a simple and inteligible abstraction to be easily readable, understandable and learnable.

### Architecture

- Insert architecture diagram here.

### Features

- [x] Input
    - Keyboard
    - Mouse
- [x] Window
    - Event Handling
    - Time Frame
- [x] Vertex
- [x] Vertex Buffer
- [x] Index Buffer
- [x] Vertex Array
- [x] Vertex Data
- [x] Shader
- [x] Texture
- [x] Mesh
- [x] Model
- [x] Camera
    - Key and Mouse Movement
    - Perspective Camera
    - Orthographic Camera
- [x] Primitive Geometry
- [X] Material
- [X] Light
- [X] Scene
- [ ] Layer
- [ ] Text

### Installation and Build

1. `git clone --recursive https://github.com/jsusaki/OGLA.git`
2. `cd OGLA`
3. `mkdir build`
4. `cd scripts`
5. `./config.sh`
6. `./build.sh`
7. `./run.sh`

#### Windows

Visual Studio Solution and batch script will be provided.

### Control

- Application Control
    - `ESCAPE`: Close
    - `F11`: Full Screen (Only on Primary Screen)
    - `TAB`: Toggle Mouse Focus

- Rendering Control
    - `1`: Normal Rendering
    - `2`: Wireframe Rendering

- Camera Control
    - `W`: Move Forward
    - `S`: Move Backward
    - `A`: Move Left
    - `D`: Move Right
    - `Q`: Move Down
    - `E`: Move Up
    - `F1`: Perspective Camera
    - `F2`: Orthographic Camera
    - `Cursor`: Focal Point
    - `Wheel`: Zoom in / Zoom Out

### Dependencies

- CMake: Build System
- GLFW: Cross-platform Input and Window
- glad: OpenGL Extension
- GLM: Mathematics
- stb_image: Image Loading
- assimp: Asset Loading