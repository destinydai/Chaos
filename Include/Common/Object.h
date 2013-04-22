#pragma once

NS_CH_BEG

class Object 
{
public:
	Object(void);
	virtual ~Object();
public:
	static const ObjectType TYPE;
	virtual const ObjectType & GetType() const;
	virtual const string &ToString() const;
};

NS_CH_END