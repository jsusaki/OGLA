#include "Shader.h"

Shader::Shader()
{

}

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
    m_ProgramID = glCreateProgram();

    std::string vertexSource = LoadFromFile(vertex_path);
    std::string fragmentSource = LoadFromFile(fragment_path);

    u32 vertexShader = Compile(VERTEX, vertexSource);
    u32 fragmentShader = Compile(FRAGMENT, fragmentSource);

    Attach(vertexShader);
    Attach(fragmentShader);

    Link();

    Detach(vertexShader);
    Detach(fragmentShader);

    Delete(vertexShader);
    Delete(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_ProgramID);
}

void Shader::Use()
{
    glUseProgram(m_ProgramID);
}

void Shader::Unuse()
{
    glUseProgram(0);
}

u32 Shader::GetID()
{
    return m_ProgramID;
}

std::string Shader::LoadFromFile(const std::string& filepath)
{
    std::string data;
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file.is_open())
        std::cout << "Could not open " << filepath;

    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(data));
    file.close();

    return data;
}

u32 Shader::Compile(ShaderType type, std::string& source)
{
    u32 shader = glCreateShader(type);

    const char* shader_src = source.c_str();
    glShaderSource(shader, 1, &shader_src, nullptr);

    glCompileShader(shader);

    int status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        int nMaxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &nMaxLength);

        std::vector<char> vErrorLog(nMaxLength);
        glGetShaderInfoLog(shader, nMaxLength, &nMaxLength, &vErrorLog[0]);

        glDeleteShader(shader);

        std::printf("%s\n", &(vErrorLog[0]));
    }

    return shader;
}

void Shader::Attach(u32& shader)
{
    glAttachShader(m_ProgramID, shader);
}

void Shader::Link()
{
    glLinkProgram(m_ProgramID);

    int status = 0;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        int maxLength = 0;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);
       
        std::vector<char> vErrorLog(maxLength);
        glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &vErrorLog[0]);
        
        glDeleteProgram(m_ProgramID);
        
        std::printf("%s\n", &(vErrorLog[0]));
    }
}

void Shader::Detach(u32& shader)
{
    glDetachShader(m_ProgramID, shader);
}

void Shader::Delete(u32& shader)
{
    glDeleteShader(shader);
}