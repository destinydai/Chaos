#include "stdafx.h"

NS_CH_BEG

Window::Window( void ):
	m_nWidth(0),
	m_nHeight(0),
	m_pOnSizeChanged(0),
	m_pOnFocused(0),
	m_pOnLostFocus(0),
	m_pOnDestroyWindow(0)
{

}

Window::~Window( void )
{

}



NS_CH_END