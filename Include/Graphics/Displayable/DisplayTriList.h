#pragma once

NS_CH_BEG

class DisplayTriList : public DisplayObject
{
	CH_OBJ_TYPE_DECL(DisplayTriList,DisplayObject)
protected:
	DisplayTriList(Reference<TriListShape> pShape);
public:
	virtual ~DisplayTriList(void);
protected:
	void Draw(const Transform *pTransform);
public:

	static Reference<DisplayTriList> Create(Reference<TriListShape> pShape);

	Reference<TriListShape> GetTriListShape() { return m_pTriListShape; }
private:
	Reference<TriListShape> m_pTriListShape;
};

NS_CH_END