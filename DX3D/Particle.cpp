#include "stdafx.h"
#include "Particle.h"


Particle::Particle()
{
}


Particle::~Particle()
{
	SAFE_RELEASE(_vb);
}

bool Particle::Init(char * FileName)
{
	g_pDevice->CreateVertexBuffer(
		_vbSize * sizeof(sParticle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		VERTEX_PC::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&_vb,
		0);
	std::string file = std::string(FileName);
	_tex = g_pTextureManager->GetTexture(file);
	return true;
}

void Particle::Reset()
{
	std::list<sAttribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		ResetParticle(&(*i));
	}
}

void Particle::AddParticle()
{
	sAttribute attribute;

	ResetParticle(&attribute);

	_particles.push_back(attribute);
}

void Particle::PreRender()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(_size));
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.2f));
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(20.0f));

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

}

void Particle::PostRender()
{


	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 0);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void Particle::RemoveDeadParticles()
{
	std::list<sAttribute>::iterator i;

	i = _particles.begin();

	while (i != _particles.end())
	{
		if (i->isAlive == false)
		{
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			i = _particles.erase(i);
		}
		else
		{
			i++; // next in list
		}
	}
}

void Particle::Render()
{

	if (!_particles.empty())
	{
		//
		// set render states
		//

		PreRender();

		g_pDevice->SetTexture(0, _tex);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->SetStreamSource(0, _vb, 0, sizeof(sParticle));

		//
		// render batches one by one
		//

		// start at beginning if we're at the end of the vb
		if (_vbOffset >= _vbSize)
			_vbOffset = 0;

		sParticle* v = 0;

		_vb->Lock(
			_vbOffset * sizeof(sParticle),
			_vbBatchSize * sizeof(sParticle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		//
		// Until all particles have been rendered.
		//
		std::list<sAttribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			if (i->isAlive)
			{
				//
				// Copy a batch of the living particles to the
				// next vertex buffer segment
				//


				v->position = i->position;
				v->color = (D3DCOLOR)i->color;
				v++; // next element;

				numParticlesInBatch++; //increase batch counter

									   // if this batch full?
				if (numParticlesInBatch == _vbBatchSize)
				{
					//
					// Draw the last batch of particles that was
					// copied to the vertex buffer. 
					//
					_vb->Unlock();

					g_pDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						_vbOffset,
						_vbBatchSize);

					//
					// While that batch is drawing, start filling the
					// next batch with particles.
					//

					// move the offset to the start of the next batch
					_vbOffset += _vbBatchSize;

					// don't offset into memory thats outside the vb's range.
					// If we're at the end, start at the beginning.
					if (_vbOffset >= _vbSize)
						_vbOffset = 0;

					_vb->Lock(
						_vbOffset * sizeof(sParticle),
						_vbBatchSize * sizeof(sParticle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // reset for new batch
				}
			}
		}

		_vb->Unlock();

		// its possible that the LAST batch being filled never 
		// got rendered because the condition 
		// (numParticlesInBatch == _vbBatchSize) would not have
		// been satisfied.  We draw the last partially filled batch now.

		if (numParticlesInBatch)
		{
			g_pDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				_vbOffset,
				numParticlesInBatch);
		}

		// next block
		_vbOffset += _vbBatchSize;

		//
		// reset render states
		//

		PostRender();
	}
}

bool Particle::IsEmpty()
{
	return _particles.empty();
}

bool Particle::isDead()
{
	std::list<sAttribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if (i->isAlive)
			return false;
	}
	// no living particles found, the system must be dead.
	return true;
}
