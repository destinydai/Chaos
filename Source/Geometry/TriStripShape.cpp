#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(TriStripShape,MeshShape)

TriStripShape::TriStripShape( void ):m_nStrips(0)
{

}

TriStripShape::~TriStripShape( void )
{

}

Reference<TriStripShape> TriStripShape::Create()
{
	return Reference<TriStripShape>(new TriStripShape());
}



NS_CH_END