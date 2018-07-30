#pragma once

enum LOAD_KIND
{
	LOAD_KIND_IMAGE,
	LOAD_KIND_SKINNDEDMESH,
	LOAD_KIND_MESH,
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagresource
{
	char* keyname;
	char* folder;
	char* filename;
};

class LoadItem
{
private:
	LOAD_KIND _kind;
	tagresource _resource;

public:
	LoadItem();
	~LoadItem();

	void InitforSkinnedMesh(IN char *  Name, IN char * szFolder, IN char * szFile);
	void InitforMesh(IN char *  Name, IN char * szFolder, IN char * szFile);
	LOAD_KIND GetLoadKind() { return _kind; }
	tagresource Getimageresource() { return _resource; }
};

class Loading
{
private:
	typedef std::vector<LoadItem*> arrLoadItem;
	arrLoadItem _vloaditem;
	int _currentgauge;

public:
	Loading() :_currentgauge(0) {};
	~Loading() {};

	void Init();
	void Update();
	void Render();
	void Destroy();

	void LoadingSkinnedMesh(char * Name, IN char * szFolder, IN char * szFile);
	void LoadingMesh(char * Name, IN char * szFolder, IN char * szFile);
	bool LoadingDone();

	std::vector<LoadItem*> GetLoadItem() { return _vloaditem; }
	int GetLoadItemSize() { return _currentgauge; }
};

