#include "stdafx.h"


NS_CH_BEG

CH_OBJ_TYPE_IMPL(TSReferencedObject,Object)

TSReferencedObject::TSReferencedObject():m_nRefCount(1)
{

}

TSReferencedObject::~TSReferencedObject()
{
	
}



NS_CH_END