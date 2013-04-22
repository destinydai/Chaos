#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(DisplayTriList,DisplayObject)

DisplayTriList::DisplayTriList( Reference<TriListShape> pShape ):
	m_pTriListShape(pShape)
{

}

DisplayTriList::~DisplayTriList( void )
{

}

void DisplayTriList::Draw(const  Transform *pTransform )
{
	CH_ASSERT(false);
}

Reference<DisplayTriList> DisplayTriList::Create( Reference<TriListShape> pShape )
{
	return Reference<DisplayTriList>(new DisplayTriList(pShape));
}


NS_CH_END