#include "stdafx.h"

IMap::IMap() : m_pAStar(NULL)
{
	Objects::Get()->AddToTagList(TAG_MAP, this);
}
