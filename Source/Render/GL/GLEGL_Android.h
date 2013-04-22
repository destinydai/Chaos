#pragma once


NS_CH_BEG

class GLEGL
{
private:
	GLEGL();
public:
	~GLEGL();

	static GLEGL * Create(void* pWindow);

	void SwapBuffers();

	const char *GetVendor() const;
	const char *GetRenderer() const;
	const char *GetVersion() const;
	const char *GetShadingLanguageVersion() const;
};

NS_CH_END