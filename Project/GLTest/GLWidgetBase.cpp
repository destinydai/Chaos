#include "stdafx.h"
#include "JuGLWidgetBase.h"
#include <QMessageBox>

JuGLWidgetBase::JuGLWidgetBase(QWidget *pParent):QWidget(pParent)
{
	m_pScene = nullptr;

	setMinimumSize( 400, 400); 
	setAttribute( Qt::WA_OpaquePaintEvent, true);  
	setAttribute( Qt::WA_PaintOnScreen, true); 
	const int width=1024;
	const int height=600;
	resize(width,height);

	/*
	JuRender::create();
	JuString szError = JuRender::getInstancePtr()->init((int)winId());
	if(!szError.empty())
	{
		QMessageBox::critical(this,"ERROR",szError.c_str(),QMessageBox::Ok);
		JU_ASSERTEX(false,"%s",szError.c_str());
	}
	*/
}

JuGLWidgetBase::~JuGLWidgetBase()
{

}

void JuGLWidgetBase::paintEvent( QPaintEvent* pEvent )
{

	update();
}
