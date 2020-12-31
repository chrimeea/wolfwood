#ifndef ANIMATEDENTITY_H
#define ANIMATEDENTITY_H

#include "game\Entity.h"
#include "rendering\CMesh.h"

class AnimatedEntity : public Entity  
{
protected:
	anim_type_t animation, after;
public:
	AnimatedEntity();
	AnimatedEntity(unsigned int, float, float);
	virtual ~AnimatedEntity() {}
	void AnimateTo(float, float, anim_type_t);
	void SetAnimation(anim_type_t);
	void EndMove();
	void NextFrame(float);
};

#endif
