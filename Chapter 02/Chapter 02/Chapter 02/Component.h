#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	Component(class Actor* owner, int updateorder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return this->updateOrder; }
protected:
	class Actor* owner;
	int updateOrder;
};

#endif // !COMPONENT_H