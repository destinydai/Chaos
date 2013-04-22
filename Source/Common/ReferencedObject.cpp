#include "stdafx.h"

NS_CH_BEG

CH_OBJ_TYPE_IMPL(ReferencedObject,Object)

ReferencedObject::ReferencedObject():
	m_nRefCount(1)
{

}

ReferencedObject::~ReferencedObject()
{

}


NS_CH_END
