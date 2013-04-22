#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(MeshShape,Shape)

MeshShape::MeshShape():m_nVertex(0),
	m_bNormals(false),
	m_nTexCoords(0)
{

}

MeshShape::~MeshShape()
{

}

bool MeshShape::IntersectP( const Ray &ray ) const
{
	return m_objectBindBox.IntersectP(ray);
}

void MeshShape::ComputeBindBox()
{
	CH_ASSERT(false);
}



NS_CH_END