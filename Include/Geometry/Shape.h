#pragma once

NS_CH_BEG

class Shape : public ReferencedObject
{
	CH_OBJ_TYPE_DECL(Shape,ReferencedObject)
public:
	Shape(void);
	virtual ~Shape();
public:
	virtual BBox ObjectBindBox() const =0;
	virtual bool IntersectP(const Ray &ray) const =0;
	
	virtual bool CanIntersect() const { return true; }
};

NS_CH_END