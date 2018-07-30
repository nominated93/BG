#include "stdafx.h"
#include "Loading.h"



void Loading::Init()
{
}

void Loading::Update()
{
}

void Loading::Render()
{

}

void Loading::Destroy()
{
}

void Loading::LoadingSkinnedMesh(char * Name, IN char * szFolder, IN char * szFile)
{
	LoadItem* item = new LoadItem;
	item->InitforSkinnedMesh(Name, szFolder, szFile);
	_vloaditem.push_back(item);
}

void Loading::LoadingMesh(char * Name, IN char * szFolder, IN char * szFile)
{
	LoadItem* item = new LoadItem;
	item->InitforMesh(Name, szFolder, szFile);
	_vloaditem.push_back(item);
}

bool Loading::LoadingDone()
{
	if (_currentgauge >= _vloaditem.size())
	{
		return true;
	}
	LoadItem* item = _vloaditem[_currentgauge];

	tagresource img = item->Getimageresource();

	switch (item->GetLoadKind())
	{
	case LOAD_KIND_SKINNDEDMESH:
	{
		string key = string(img.keyname);
		g_pSkinnedMeshManager->Load(key, img.folder, img.filename);
	}
	case LOAD_KIND_MESH:
	{
		string key = string(img.keyname);
		g_pMeshManager->AddMesh(key, img.folder, img.filename);
	}
	break;
	}
	
	_currentgauge++;

	return false;
}

LoadItem::LoadItem()
{
}

LoadItem::~LoadItem()
{
}

void LoadItem::InitforSkinnedMesh(IN char * Name, IN char * szFolder, IN char * szFile)
{
	_kind = LOAD_KIND_SKINNDEDMESH;
	ZeroMemory(&_resource, sizeof(tagresource));

	_resource.keyname = Name;
	_resource.folder = szFolder;
	_resource.filename = szFile;
}

void LoadItem::InitforMesh(IN char * Name, IN char * szFolder, IN char * szFile)
{
	_kind = LOAD_KIND_MESH;
	ZeroMemory(&_resource, sizeof(tagresource));

	_resource.keyname = Name;
	_resource.folder = szFolder;
	_resource.filename = szFile;
}
