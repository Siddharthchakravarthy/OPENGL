#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderSourceCode {
	std::string sid_vertex_source;
	std::string sid_fragment_source;
};

class Shader
{
private:
	std::string m_filepath;
	unsigned int m_RendererID_of_sha;
	std::unordered_map <std::string, int> m_Location;
public:

	Shader(const std::string& filepath);
	~Shader();
	
	void Bind() const;
	void UnBind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformmat4f(const std::string& name,const glm::mat4& proj);

private:
	ShaderSourceCode ParseSource(const std::string& filepath);

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);
	int GetUniformLocation(const std::string& name);
};

