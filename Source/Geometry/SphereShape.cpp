#include "stdafx.h"

NS_CH_BEG

CH_OBJ_TYPE_IMPL(SphereShape,Shape)

SphereShape::SphereShape( void ):m_radius(0)
{

}

SphereShape::SphereShape( float radius ):m_radius(0)
{

}

SphereShape::~SphereShape( void )
{

}

BBox SphereShape::ObjectBindBox() const
{
	CH_ASSERT(false);
	return m_bbox;
}

bool SphereShape::IntersectP( const Ray &ray ) const
{
	CH_ASSERT(false,"");
	return false;
}

Reference<SphereShape> SphereShape::Create()
{
	return Reference<SphereShape>(new SphereShape());
}

Reference<SphereShape> SphereShape::Create( float radius )
{
	return Reference<SphereShape>(new SphereShape(radius));
}

NS_CH_END