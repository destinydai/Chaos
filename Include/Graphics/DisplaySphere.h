#pragma once

NS_CH_BEG


class DisplaySphere : public DisplayObject
{
	CH_OBJ_TYPE_DECL(DisplaySphere,DisplayObject)
protected:
	DisplaySphere(float radius);
public:
	virtual ~DisplaySphere(void);
protected:
	void Draw(const Transform *pTransform);
public:

	static Reference<DisplaySphere> Create(float radius);

	inline float GetRadius() const { return m_radius; }

private:
	int GenSphere ( int numSlices, float radius, float **vertices, float **normals, float **texCoords, uint16 **indices );

private:
	float m_radius;
};

NS_CH_END