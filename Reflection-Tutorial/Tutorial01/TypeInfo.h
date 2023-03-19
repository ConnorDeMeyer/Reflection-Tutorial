#pragma once

#include "TypeHash.h"
#include "CustomTypes.h"

#include <bitset>
#include <cassert>
#include <functional>

enum TypeFlags
{
	TypeFlags_IsFundamental,
	TypeFlags_IsIntegral,
	TypeFlags_IsFloatingPoint,
	TypeFlags_IsTriviallyCopyable,

	TypeFlags_SIZE
};

struct TypeInfo final
{
	std::string_view				Name			{ };
	uint32_t						Size			{ };
	uint32_t						Align			{ };

	std::bitset<TypeFlags_SIZE>		Flags			{ };

	std::function<GameComponent*()>	GCConstructor	{ };

	template <typename T>
	static constexpr TypeInfo Create();
};

class TypeId final
{
public:

	constexpr TypeId(uint64_t id) : ID{ id } {};

public:

	template <typename T>
	static constexpr TypeId Create();

public:

	constexpr void			SetTypeId			(uint64_t typeId)	{ ID = typeId; }
	constexpr uint64_t		GetId				()	const			{ return ID; }

	const TypeInfo&			GetTypeInfo			()	const			{ return GetTypeInformation(*this); }
	
	const std::string_view	GetTypeName			()	const			{ return GetTypeInfo().Name; }
	uint32_t				GetTypeSize			()	const			{ return GetTypeInfo().Size; }
	uint32_t				GetTypeAlignment	()	const			{ return GetTypeInfo().Align; }

	bool					IsFundamental		()	const			{ return GetTypeInfo().Flags[TypeFlags_IsFundamental]; }
	bool					IsIntegral			()	const			{ return GetTypeInfo().Flags[TypeFlags_IsIntegral]; }
	bool					IsFloatingPoint		()	const			{ return GetTypeInfo().Flags[TypeFlags_IsFloatingPoint]; }
	bool					IsTriviallyCopyable	()	const			{ return GetTypeInfo().Flags[TypeFlags_IsTriviallyCopyable]; }
	bool					IsGameComponent		()	const			{ return static_cast<bool>(GetTypeInfo().GCConstructor); }

	GameComponent*			ConstructGC			()	const			{ return GetTypeInfo().GCConstructor(); }

public:

	template <typename T>
	static TypeInfo& RegisterTypeId()
	{
		auto& typeInfos = GetStatics().TypeInfos;
		const uint64_t typeId = TypeId::Create<T>().GetId();

		assert(!typeInfos.contains(typeId));
		
		return typeInfos.emplace(
			typeId,
			TypeInfo::Create<T>()
		).first->second;
	}

	static const TypeInfo& GetTypeInformation(TypeId typeInfo)
	{
		assert(GetStatics().TypeInfos.contains(typeInfo.GetId()));
		return GetStatics().TypeInfos[typeInfo.GetId()];
	}

	static const auto& GetAllTypeInformation() 
	{ 
		return GetStatics().TypeInfos; 
	}

private:

	struct StaticData
	{
		std::unordered_map<uint64_t, TypeInfo> TypeInfos{};
	};

	static StaticData& GetStatics()
	{
		static StaticData data{};
		return data;
	}

private:
	uint64_t ID{};
};

template <typename T>
class RegisterType
{
private:
	class RegisterTypeOnce
	{
	public:
		RegisterTypeOnce()
		{
			TypeId::RegisterTypeId<T>();
		}
	};
	inline static RegisterTypeOnce Registerer{};
};

#define _REGISTER_TYPE_INTERNAL(TYPE, VARNAME) RegisterType<TYPE> VARNAME##TYPE {};
#define REGISTER_TYPE(TYPE) _REGISTER_TYPE_INTERNAL(TYPE, RegisterType_)

// REGISTER_TYPE(int) == 
// RegisterType<int> RegisterType_int {};




template<typename T>
inline constexpr TypeInfo TypeInfo::Create()
{
	TypeInfo info{};

	info.Name			= Reflection::TypeName<T>();
	info.Size			= sizeof(T);
	info.Align			= alignof(T);

	info.Flags[TypeFlags_IsTriviallyCopyable]	= std::is_trivially_copyable_v<T>;
	info.Flags[TypeFlags_IsIntegral]			= std::is_integral_v<T>;
	info.Flags[TypeFlags_IsFloatingPoint]		= std::is_floating_point_v<T>;
	info.Flags[TypeFlags_IsFundamental]			= std::is_fundamental_v<T>;

	if constexpr (std::is_base_of_v<GameComponent, T>)
	{
		info.GCConstructor = []() -> GameComponent*
		{
			return new T();
		};
	}

	return info;
}

template<typename T>
inline constexpr TypeId TypeId::Create()
{
	return TypeId(Reflection::TypeId<T>());
}
