#include "stdafx.h"
#include <sstream>
#include <fstream>

using namespace std;

NS_CH_BEG

GLShader::GLShader():m_nShaderID(0),m_eType(ShaderType::UNKNOW)
{

}

GLShader::~GLShader()
{
	if(m_nShaderID!=0)
	{
		glDeleteShader(m_nShaderID);
		m_nShaderID=0;
	}
}

string GLShader::CreateFromFile( const string &szFileName,ShaderType::Type t)
{
	string fileString;
	string line;

	ifstream file(szFileName.c_str());
	if (file.is_open()) 
	{ 
		while (!file.eof()) 
		{ 
			getline(file, line); 
			fileString.append(line); 
			fileString.append("\n"); 
		}
		file.close(); 
	}
	else
	{
		stringstream sOut;
		sOut <<"files:"<<szFileName	<<"open failed."<<endl;
		return sOut.str();
	}

	return CreateFromMemory(fileString.c_str(),fileString.size(),t);
}

string GLShader::CreateFromMemory( const char* szCodes,int nCodesLen,ShaderType::Type t)
{
	CH_ASSERT(szCodes);

	m_eType = t;
	m_szShaderCodes = szCodes;

	switch(t)
	{
	case ShaderType::VERTEX:
		m_nShaderID = glCreateShader(GL_VERTEX_SHADER); 
		break;
	case ShaderType::PIXEL:
		m_nShaderID = glCreateShader(GL_FRAGMENT_SHADER); 
		break;
	default:
		CH_ASSERT(false);
		break;
	}

	glShaderSource(m_nShaderID, 1, &szCodes,&nCodesLen); 
	CH_GLFAILCHECK;
	glCompileShader(m_nShaderID); 
	CH_GLFAILCHECK;

	char buffer[CH_BUFSIZE];
	memset(buffer, 0, CH_BUFSIZE);
	GLsizei length = 0;

	GLint compiled = 0;
	glGetShaderiv(m_nShaderID, GL_COMPILE_STATUS, &compiled);
	if (!compiled) 
	{
		stringstream sOut;
		glGetShaderInfoLog(m_nShaderID, CH_BUFSIZE, &length, buffer); 
		if (length > 0) 
		{
			sOut << "Shader  compile error: " << buffer << endl; 
			return sOut.str();
		}
	}
	return "";
}



NS_CH_END