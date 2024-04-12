#include "Window.h"


Window::Window(std::string title, int w, int h, bool fullscreen, bool vsync)
{
    Create(title, w, h, fullscreen, vsync);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::Create(std::string title, int w, int h, bool fullscreen, bool vsync)
{
    p.m_size = { w , h };
    p.m_pos = { 0, 0 };
    p.m_title = title;
    p.m_fullscreen = fullscreen;
    p.m_vsync = vsync;
    m_mouse_input_focus = true;
    m_render_mode = RenderMode::NORMAL;
    
    GLFW_Init();
    GLFW_CreateWindow(title, w, h, fullscreen, vsync);
    GLAD_Load();

    GLFW_SetFrameBufferSizeCallback();

    GetPrimaryMonitor();
    SetVsync(vsync);
    SetFullScreen(fullscreen);
    SetMouseInputFocus(m_mouse_input_focus);
    SetRenderMode(m_render_mode);
    UpdateViewport({ 0, 0 }, { w, h });
    PrepareDrawing();
}

void Window::UpdateViewport(const vi2& m_pos, const vi2& m_size)
{
    glViewport(m_pos.x, m_pos.y, m_size.x, m_size.y);
}

void Window::ClearBuffer(pixel p, bool depth)
{
    glClearColor(float(p.r) / 255.0f, float(p.g) / 255.0f, float(p.b) / 255.0f, float(p.a) / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (depth) glClear(GL_DEPTH_BUFFER_BIT);
}

void Window::PrepareDrawing(bool depth, bool cullface)
{
    if (depth)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    if (cullface)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::DisplayFrame()
{
    glfwSwapBuffers(m_window);
}

int Window::Width()
{
    return p.m_size.x;
}

int Window::Height()
{
    return p.m_size.y;
}

GLFWwindow* Window::GetWindow()
{
    return m_window;
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_window, true);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::ToggleFullScreen()
{
    SetFullScreen(!IsFullScreen());
}

void Window::SetFullScreen(bool fullscreen)
{
    if (IsFullScreen() == fullscreen)
        return;

    if (fullscreen)
    {
        // Cache original window position and window size
        glfwGetWindowPos(m_window, &p.m_pos.x, &p.m_pos.y);
        glfwGetWindowSize(m_window, &p.m_size.x, &p.m_size.y);
        // Get monitor resolution
        const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
        // Full screen
        glfwSetWindowMonitor(m_window, m_monitor, 0, 0, mode->width, mode->height, 0);
    }
    else
    {
        // Restore original window size and position
        glfwSetWindowMonitor(m_window, nullptr, p.m_pos.x, p.m_pos.y, p.m_size.x, p.m_size.y, 0);
    }
}

bool Window::IsFullScreen()
{
    return glfwGetWindowMonitor(m_window) != nullptr;
}

void Window::ToggleVsync()
{
    p.m_vsync = !p.m_vsync;
    SetVsync(p.m_vsync);
    //SetVsync(!IsVsync()); // does not work for unknown reason
}

void Window::SetVsync(bool vsync)
{
    if (vsync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0); // Remove Framecap
}

bool Window::IsVsync()
{
    return p.m_vsync;
}

void Window::ToggleMouseFocus()
{
    m_mouse_input_focus = !m_mouse_input_focus;
    SetMouseInputFocus(m_mouse_input_focus);
    //SetMouseInputFocus(!IsMouseFocused()); // does not work for unknown reason
}

void Window::SetMouseInputFocus(bool focus)
{
    if (focus)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Window::IsMouseFocused()
{
    return m_mouse_input_focus;
}

void Window::GetPrimaryMonitor()
{
    m_monitor = glfwGetPrimaryMonitor();
}

RenderMode Window::GetRenderMode()
{
    return m_render_mode;
}

void Window::SetRenderMode(RenderMode mode)
{
    m_render_mode = mode;

    switch (m_render_mode)
    {
    case RenderMode::NORMAL:    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    case RenderMode::WIREFRAME: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
    }
}

void Window::GLFW_Init()
{
    if (!glfwInit())
    {
        std::cout << "GLFW Initialization Failed" << std::endl;
        glfwTerminate();
    }
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile: No backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Enable Forward Compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    printf("GLFW %i.%i.%i\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION); 
 }

void Window::GLFW_CreateWindow(std::string title, int w, int h, bool fullscreen, bool vsync)
{
    p.m_vsync = vsync;
    p.m_fullscreen = fullscreen;

    m_window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cout << "GLFW Window Initialization Failed" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
}

void Window::GLAD_Load()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD Initialization Failed" << std::endl;
        glfwTerminate();
    }
}

void Window::GLFW_SetFrameBufferSizeCallback()
{
    glfwSetWindowUserPointer(m_window, &p);
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        param* p = static_cast<param*>(glfwGetWindowUserPointer(window));
        p->m_size.x = width;
        p->m_size.y = height;
        glViewport(0, 0, width, height);
    });
}