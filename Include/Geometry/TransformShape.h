#pragma once


NS_CH_BEG

class TransformShape : public Shape
{
	CH_OBJ_TYPE_DECL(TransformShape,Shape)
protected:
	TransformShape(void);
	TransformShape(Reference<Shape> pShape,const Transform &tran);
public:
	virtual ~TransformShape(void);
public:
	static Reference<Shape> Create();
	static Reference<Shape> Create(Reference<Shape> pShape,const Transform &tran);

	virtual BBox ObjectBindBox() const;
	virtual bool IntersectP(const Ray &ray) const;

	inline const Transform &GetTransform() const { return m_transform; }
	inline Reference<Shape> GetShape() { return m_pRefShape; }

	inline void SetTransform(const Transform &tran) { m_transform = tran; }
	inline void SetShape(Reference<Shape> pShape) { m_pRefShape = pShape;  }
private:
	Reference<Shape> m_pRefShape;
	Transform m_transform;
};

NS_CH_END