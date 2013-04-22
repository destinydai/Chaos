#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(DisplayBBox,DisplayObject)

DisplayBBox::DisplayBBox( const Point3 &p1,const Point3 &p2 ):m_bbox(p1,p2)
{

}

DisplayBBox::~DisplayBBox( void )
{

}

void DisplayBBox::Draw(const  Transform *pTransform )
{
	CH_ASSERT(false);
}

Reference<DisplayBBox> DisplayBBox::Create( const Point3 &p1,const Point3 &p2 )
{
	return Reference<DisplayBBox>(new DisplayBBox(p1,p2));
}

/*************************************************************/

CH_OBJ_TYPE_IMPL(DisplayBoxLine,DisplayObject)

DisplayBoxLine::DisplayBoxLine( const Point3 &p1, const Point3 &p2 ):m_bbox(p1,p2)
{

}

DisplayBoxLine::~DisplayBoxLine( void )
{

}

void DisplayBoxLine::Draw( const Transform *pTransform )
{
	CH_ASSERT(false);
}

Reference<DisplayBoxLine> DisplayBoxLine::Create( const Point3 &p1, const Point3 &p2 )
{
	return Reference<DisplayBoxLine>(new DisplayBoxLine(p1,p2));
}


NS_CH_END

