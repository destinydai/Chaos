#pragma once


NS_CH_BEG

class GLShader 
{
public:
	GLShader();
	virtual ~GLShader();

	string CreateFromFile(const string &szFileName,ShaderType::Type t);
	string CreateFromMemory(const char* szCodes,int nCodesLen,ShaderType::Type t);

	GLint GetShaderID() const { return m_nShaderID; }

private:
	GLint m_nShaderID;
	string m_szShaderCodes;
	ShaderType::Type m_eType;
};


NS_CH_END