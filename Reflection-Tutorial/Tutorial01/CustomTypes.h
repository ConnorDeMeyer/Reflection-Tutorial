#pragma once
#include <iostream>

struct Vector3
{
	float X{}, Y{}, Z{};
};

struct Matrix3
{
	Vector3 Row0{}, Row1{}, Row2{};
};

class GameComponent
{
public:

	GameComponent() = default;
	virtual ~GameComponent() = default;

public:
	virtual void Initialize() {};
	virtual void Update(float ) {};
	virtual void Render() const {};
	virtual void Copy() const {};
	virtual void Serialize() const {};
};

class TranformComponent final : public GameComponent
{
private:
	Matrix3 Transform{};

	virtual void Update(float )
	{
		std::cout << "Updated\n";
	}
};

class RenderComponent final : public GameComponent
{
private:
	class Texture* Texture{};

	virtual void Render() const override
	{
		std::cout << "Rendered\n";
	}
};