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
        std::cout << "Could not open " << filepath << "\n";

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

    s32 status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        s32 nMaxLength = 0;
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

    s32 status = 0;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        s32 maxLength = 0;
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

u32 Shader::GetAttribute(const std::string& name) const
{
    return glGetAttribLocation(m_ProgramID, name.c_str());
}

u32 Shader::GetUniform(const std::string& name) const
{
    if (m_UniformLocations.find(name) != m_UniformLocations.end())
        return m_UniformLocations[name];

    u32 location = glGetUniformLocation(m_ProgramID, name.c_str());
    m_UniformLocations[name] = location;
    return location;
}

void Shader::SetUniform(const std::string& name, const s32& val)
{
    glUniform1i(GetUniform(name), val);
}

void Shader::SetUniform(const std::string& name, f32* val, s32 count)
{
    glUniform1fv(GetUniform(name), count, val);
}

void Shader::SetUniform(const std::string& name, s32* val, s32 count)
{
    glUniform1iv(GetUniform(name), count, val);
}

void Shader::SetUniform(const std::string& name, const f64& val)
{
    glUniform1f(GetUniform(name), val);
}

void Shader::SetUniform(const std::string& name, const f32& val)
{
    glUniform1f(GetUniform(name), val);
}

void Shader::SetUniform(const std::string& name, const vf2& vector)
{
    glUniform2f(GetUniform(name), vector.x, vector.y);
}

void Shader::SetUniform(const std::string& name, const vf3& vector)
{
    glUniform3f(GetUniform(name), vector.x, vector.y, vector.z);
}

void Shader::SetUniform(const std::string& name, const vf4& vector)
{
    glUniform4f(GetUniform(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::SetUniform(const std::string& name, const mf4x4& matrix)
{
    glUniformMatrix4fv(GetUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}