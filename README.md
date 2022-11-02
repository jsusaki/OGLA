# OGLA: OpenGL Abstraction

OpenGL Abstraction
- Input
    - Keyboard
    - Mouse
- Window
    - Frame Time

### Development
Abstraction Currently Work In Progress
- [x] Vertex
- [x] Vertex Buffer
- [x] Index Buffer
- [x] Vertex Array
- [x] Vertex Data
- [x] Shader
- [x] Texture
- [ ] Mesh
- [ ] Layer
- [ ] Camera
- [ ] Material
- [ ] Light
- [ ] Primitive Geometry
- [ ] Font

### Building

After 
```
git clone --recursive https://github.com/jsusaki/OpenGLCore.git
```

#### Linux
```
mkdir build
cd scripts
./config.sh
./build.sh
./run.sh
```

### Dependency
- cmake
- glfw
- glad
- glm
- stb_image
- assimp