#pragma once


NS_CH_BEG

class DisplayBBox : public DisplayObject
{
	CH_OBJ_TYPE_DECL(DisplayBBox,DisplayObject)
protected:
	DisplayBBox(const Point3 &p1,const Point3 &p2);
public:
	virtual ~DisplayBBox(void);

	static Reference<DisplayBBox> Create(const Point3 &p1,const Point3 &p2);

protected:
	void Draw(const Transform *pTransform);
private:
	BBox m_bbox;
};

class DisplayBoxLine : public DisplayObject
{
	CH_OBJ_TYPE_DECL(DisplayBoxLine,DisplayObject)
protected:
	DisplayBoxLine(const Point3 &p1, const Point3 &p2);
public:
	virtual ~DisplayBoxLine(void);

	static Reference<DisplayBoxLine> Create(const Point3 &p1, const Point3 &p2);
protected:
	void Draw(const Transform *pTransform);
private:
	BBox m_bbox;
};


NS_CH_END