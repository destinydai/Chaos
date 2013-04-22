#pragma once

NS_CH_BEG

class DisplayTriStrip : public DisplayObject
{
	CH_OBJ_TYPE_DECL(DisplayTriStrip,DisplayObject)
public:
	DisplayTriStrip(Reference<TriStripShape> pShape);
	virtual ~DisplayTriStrip(void);
protected:
	void Draw(const Transform *pTransform);
public:

	static Reference<DisplayTriStrip> Create(Reference<TriStripShape> pShape);

	Reference<TriStripShape> GetTriStripShape() { return m_pTriStripShape; }
private:
	Reference<TriStripShape> m_pTriStripShape;
};

NS_CH_END