#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(TriListShape,MeshShape)

TriListShape::TriListShape( void ):m_nTriangles(0)
{

}

TriListShape::~TriListShape( void )
{

}

Reference<TriListShape> TriListShape::Create()
{
	return Reference<TriListShape>(new TriListShape());
}

NS_CH_END