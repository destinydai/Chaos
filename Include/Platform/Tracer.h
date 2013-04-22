#pragma once

NS_CH_BEG

class Tracer
{
private:
	Tracer();
	~Tracer();
public:
	static Tracer* GetInstancePtr();

	void Write(const char *info,...);
};

NS_CH_END

