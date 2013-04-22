#pragma once


NS_CH_BEG

class BBoxShape : public Shape
{
	CH_OBJ_TYPE_DECL(BBoxShape,Shape)
protected:
	BBoxShape(void);
	BBoxShape(const Point3 p1, const Point3 p2);
public:
	virtual ~BBoxShape(void);
public:

	static Reference<BBoxShape> Create();
	static Reference<BBoxShape> Create(const Point3 p1, const Point3 p2);

	virtual BBox ObjectBindBox() const;
	virtual bool IntersectP(const Ray &ray) const;

	const Point3 &GetMin() const { return m_bbox.pMin; }
	const Point3 &GetMax() const { return m_bbox.pMax; }

	void AddPoint(const Point3 &p) { Union(m_bbox,p);}
private:
	BBox m_bbox;
};


NS_CH_END