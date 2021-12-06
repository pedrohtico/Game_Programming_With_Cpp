#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateorder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	virtual void ProcessInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return this->updateOrder; }
protected:
	class Actor* owner;
	int updateOrder;
};

#endif // !COMPONENT_H