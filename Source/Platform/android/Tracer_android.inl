
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

	__android_log_print(ANDROID_LOG_ERROR,"ChaosAndroidjni",pBuffer);
}

Tracer* Tracer::GetInstancePtr()
{
	static Tracer instance;
	return &instance;
}

NS_CH_END
