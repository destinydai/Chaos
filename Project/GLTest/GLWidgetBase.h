#pragma once

#include <QWidget>

class Scene;
class JuGLWidgetBase : public QWidget
{
public:
	JuGLWidgetBase(QWidget *pParent);
	virtual ~JuGLWidgetBase();

	/** a hint to Qt to give the widget as much space as possible */ 
	QSizePolicy sizePolicy() const { return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ); } 
	/** a hint to Qt that we take care of the drawing for ourselves, thankyouverymuch */ 
	QPaintEngine *paintEngine() const { return NULL; } 

	/** paints the scene */ 
	virtual void paintEvent( QPaintEvent* pEvent); 

public:
	Scene *m_pScene;
};

