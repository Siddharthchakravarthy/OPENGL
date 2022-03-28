#include "Shader.h"
#include "Renderer.h"


Shader::Shader(const std::string& filepath):
	m_RendererID_of_sha(0), m_filepath(filepath)
{
    ShaderSourceCode source = ParseSource(filepath);
    m_RendererID_of_sha = CreateShader(source.sid_vertex_source, source.sid_fragment_source);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID_of_sha);
}


ShaderSourceCode Shader::ParseSource(const std::string& path) {
    std::ifstream op(path);
    enum class shade {
        NONE = -1, sid_vertex = 0, sid_fragment = 1
    };
    std::stringstream ss[2];
    std::string line;
    shade type = shade::NONE;
    while (getline(op, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("sid_vertex") != std::string::npos) {
                type = shade::sid_vertex;
            }
            else if (line.find("sid_fragment") != std::string::npos) {
                type = shade::sid_fragment;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}



unsigned int Shader::CreateShader(const std::string vertexShader, const std::string fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;

}



unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int sid = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(sid, 1, &src, nullptr);
    glCompileShader(sid);

    int result;
    glGetShaderiv(sid, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int sid_length;
        glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &sid_length);
        char* message = (char*)malloc(sid_length * sizeof(char));
        glGetShaderInfoLog(sid, sid_length, &sid_length, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ?
            "fragment shader" : "vertex shader")
            << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(sid);
        free(message);
        return 0;
    }

    return sid;
}






void Shader::Bind() const
{
    glUseProgram(m_RendererID_of_sha);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall( glUniform1i(GetUniformLocation(name), value) );
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
    GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformmat4f(const std::string& name,const glm::mat4& proj)
{
    //glm::mat4 *ptr = &proj;
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &proj[0][0] ));// &(*ptr)[0][0] idu sumne pointer pratice ge maadiddu you could simply use
                                                                              // &proj[0][0] 
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_Location.find(name) != m_Location.end()) {
        return m_Location[name];
    }
    int location = glGetUniformLocation(m_RendererID_of_sha, name.c_str());
    if (location == -1) {
        std::cout << "warning : uniform " << name << " doesn't exist " << std::endl;
    }

    m_Location[name] = location;
	return location;
}
