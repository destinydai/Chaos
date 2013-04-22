#pragma once


NS_CH_BEG

class DisplayObject : public ReferencedObject
{
	CH_OBJ_TYPE_DECL(DisplayObject,ReferencedObject)
public:
	DisplayObject(void);
	virtual ~DisplayObject(void);
	
protected:
	virtual void Draw(const Transform *pTransform)=0;

	friend class GraphicsManager;

};



NS_CH_END