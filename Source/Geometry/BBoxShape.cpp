#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(BBoxShape,Shape)

BBoxShape::BBoxShape( void )
{

}

BBoxShape::BBoxShape( const Point3 p1, const Point3 p2 ):m_bbox(p1,p2)
{

}

BBoxShape::~BBoxShape( void )
{

}

BBox BBoxShape::ObjectBindBox() const
{
	return m_bbox;
}

bool BBoxShape::IntersectP( const Ray &ray ) const
{
	return m_bbox.IntersectP(ray);
}

Reference<BBoxShape> BBoxShape::Create()
{
	return Reference<BBoxShape>(new BBoxShape());
}

Reference<BBoxShape> BBoxShape::Create( const Point3 p1, const Point3 p2 )
{
	return Reference<BBoxShape>(new BBoxShape(p1,p2));
}

NS_CH_END