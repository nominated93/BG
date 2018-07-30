#pragma once
#include "IDisplayObject.h"
#include "IUnitObject.h"

class AseObject;

class AseCharacter : public IUnitObject
{
private:
	ASE_SCENE m_aseScene;
	AseObject * m_pCurrObj;
	AseObject * m_pStandObj;
	AseObject * m_pRunObj;

public:
	AseCharacter();
	~AseCharacter();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Load(OUT AseObject* &rootObj, const char* fullPath);
	void SetCurrentObject(AseObject* pObj) { m_pCurrObj = pObj; }
};

