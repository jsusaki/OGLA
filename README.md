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
- [x] Mesh
- [ ] Model
- [ ] Primitive Geometry
- [ ] Camera
- [ ] Layer
- [ ] Material
- [ ] Light
- [ ] Font

### Building
```
git clone --recursive https://github.com/jsusaki/OGLA.git
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