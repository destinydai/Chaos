

NS_CH_BEG

Tracer::Tracer()
{

}

Tracer::~Tracer()
{

}

void Tracer::Write( const char *szInfo,... )
{
	char pBuffer[CH_BUFSIZE];
	va_list argList;
	va_start(argList,szInfo);
	vsprintf(pBuffer,szInfo,argList);
	va_end(argList);
	printf(pBuffer);
	printf("\n");
}

Tracer* Tracer::GetInstancePtr()
{
	static Tracer instance;
	return &instance;
}

NS_CH_END