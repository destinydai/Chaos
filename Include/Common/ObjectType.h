#pragma once


NS_CH_BEG

class ObjectType
{
private:
	string typeName;
	const ObjectType * baseType;
public:
	ObjectType(const string & _typeName,const ObjectType * _parentType)
		:typeName(_typeName),baseType(_parentType)
	{

	}
	~ObjectType(void){}

	inline const string &GetTypeName() const
	{
		return this->typeName;
	}
	inline bool IsSameType(const ObjectType & _compareTo) const
	{
		return &_compareTo == this;
	}

	bool operator==(const ObjectType &_compareTo) const
	{
		return IsSameType(_compareTo);
	}

	bool IsDerivedType(const ObjectType & _compareTo) const
	{
		const ObjectType * search = this;
		while( search != nullptr)
		{
			if(search == &_compareTo)
			{
				return true;
			}
			search = search->baseType;
		}
		return false;
	}
};

NS_CH_END

//RTTI      
#define CH_OBJ_TYPE_DECL(classType,parentType)  \
	public:\
	static const ObjectType TYPE;\
	virtual const ObjectType & GetType() const;\
	virtual const string &ToString() const;

#define CH_OBJ_TYPE_IMPL(classType,parentType) \
	const ObjectType classType::TYPE(#classType,&parentType::TYPE);\
	const ObjectType & classType::GetType() const\
{\
	return this->TYPE;\
}\
	const string &classType::ToString() const\
{\
	return this->TYPE.GetTypeName();\
}


