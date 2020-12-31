#include "game\AnimatedEntity.h"
#include "rendering\CAnimatedMesh.h"
#include "rendering\CMD2Model.h"

AnimatedEntity::AnimatedEntity(unsigned int id, float px, float py) : Entity(px, py)
{
	mesh = new CMD2Model(id);
	SetAnimation(ANIM_STAND);
}

void AnimatedEntity::AnimateTo(float px, float py, anim_type_t inAnim)
{
	after = animation;
	SetAnimation(inAnim);
	TranslateTo(px, py);
}

void AnimatedEntity::SetAnimation(anim_type_t anim)
{
	animation = anim;
	((CAnimatedMesh *)mesh)->SetAnimation(anim);
}

void AnimatedEntity::EndMove()
{
	Entity::EndMove();
	SetAnimation(after);
}

void AnimatedEntity::NextFrame(float frameTime)
{
	Entity::NextFrame(frameTime);
	((CAnimatedMesh *)mesh)->NextFrame(frameTime);
}