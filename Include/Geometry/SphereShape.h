#pragma once


NS_CH_BEG

class SphereShape : public Shape
{
	CH_OBJ_TYPE_DECL(SphereShape,Shape)
protected:
	SphereShape(void);
	SphereShape(float radius);
public:
	virtual ~SphereShape(void);
public:

	Reference<SphereShape> Create();
	Reference<SphereShape> Create(float radius);

	virtual BBox ObjectBindBox() const;
	virtual bool IntersectP(const Ray &ray) const;

	inline float GetRadius() const { return m_radius; }
private:
	float m_radius;
	BBox m_bbox;
};

NS_CH_END