#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(DisplayTriStrip,DisplayObject)


DisplayTriStrip::DisplayTriStrip( Reference<TriStripShape> pShape ):
	m_pTriStripShape(pShape)
{

}

DisplayTriStrip::~DisplayTriStrip( void )
{

}

void DisplayTriStrip::Draw(const  Transform *pTransform )
{
	CH_ASSERT(false);
}

Reference<DisplayTriStrip> DisplayTriStrip::Create( Reference<TriStripShape> pShape )
{
	return Reference<DisplayTriStrip>(new DisplayTriStrip(pShape));
}

NS_CH_END