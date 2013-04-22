#include "stdafx.h"

NS_CH_BEG

const ObjectType Object::TYPE("Object",nullptr);

Object::Object( void )
{

}

Object::~Object()
{

}

const ObjectType & Chaos::Object::GetType() const
{
	return TYPE;
}

const string &Object::ToString() const
{
	return TYPE.GetTypeName();
}


NS_CH_END