#include "MemberVars.h"
#include <iostream>

struct Vector
{
	float X{}, Y{}, Z{};
};

REGISTER_TYPE(Vector);
REGISTER_MEMBER(Vector, X);
REGISTER_MEMBER(Vector, Y);
REGISTER_MEMBER(Vector, Z);

struct Quaternion
{
	float X{}, Y{}, Z{}, W{};
};

REGISTER_TYPE(Quaternion);
REGISTER_MEMBER(Quaternion, X);
REGISTER_MEMBER(Quaternion, Y);
REGISTER_MEMBER(Quaternion, Z);
REGISTER_MEMBER(Quaternion, W);

#pragma warning(disable:4324) // disable padding warning
struct Transform
{
	alignas(16) Vector Translation{};
	alignas(16) Quaternion Rotation{};
	alignas(16) Vector Scale{};
};
#pragma warning(default:4324)

REGISTER_TYPE(Transform);
REGISTER_MEMBER(Transform, Translation);
REGISTER_MEMBER(Transform, Rotation);
REGISTER_MEMBER(Transform, Scale);

class GameObject
{
private:
	std::string Name{};
	uint32_t Id{};
	Transform Transform{};
	
	friend struct RegisterGameObject;
};

struct RegisterGameObject
{
	REGISTER_MEMBER(GameObject, Name);
	REGISTER_MEMBER(GameObject, Id);
	REGISTER_MEMBER(GameObject, Transform);
};

void PrintTypeInfo(TypeId id)
{
	std::cout << "Type: " << id.GetTypeName() << '\n';
	std::cout << "Size: " << id.GetTypeSize() << '\n';
	std::cout << "Alignment: " << id.GetTypeAlignment() << '\n';

	std::cout << "Member variables:\n";
	for (auto& info : MemberId::GetMemberInfos(id))
	{
		std::cout << '\t' << GetVariableName(info.VariableId) << " [" << info.Name << "] At Offset [" << info.Offset << "]\n";
	}
	std::cout << "\n\n";
}

int main()
{
	PrintTypeInfo(TypeId::Create<Vector>());
	PrintTypeInfo(TypeId::Create<Quaternion>());
	PrintTypeInfo(TypeId::Create<Transform>());
	PrintTypeInfo(TypeId::Create<GameObject>());
}