#include "stdafx.h"



NS_CH_BEG

CH_OBJ_TYPE_IMPL(TransformShape,Shape)

TransformShape::TransformShape( void ):m_pRefShape(nullptr)
{

}

TransformShape::TransformShape( Reference<Shape> pShape,const Transform &tran ):
m_pRefShape(pShape),m_transform(tran)
{

}

TransformShape::~TransformShape( void )
{

}

BBox TransformShape::ObjectBindBox() const
{
	CH_ASSERT(false);
	return BBox();
}

bool TransformShape::IntersectP( const Ray &ray ) const
{
	CH_ASSERT(false);
	return false;
}

Reference<Shape> TransformShape::Create()
{
	return Reference<Shape>(new TransformShape());
}

Reference<Shape> TransformShape::Create(Reference<Shape> pShape,const Transform &tran)
{
	return Reference<Shape>(new TransformShape(pShape,tran));
}


NS_CH_END