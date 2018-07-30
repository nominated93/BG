#pragma once
#include "Particle.h"

class EnemyParticle : public Particle
{
private:
	int	m_nsize;

public:
	EnemyParticle(int num, int size);
	virtual ~EnemyParticle();


	void ResetParticle(sAttribute* attribute);
	void Update(float timeDelta);


};
