
#include "TypeInfo.h"

int main()
{
#if 0
	for (auto& [id, typeInfo] : TypeId::GetAllTypeInformation())
	{
		std::cout << "Name: "			<< typeInfo.Name		<< '\n';
		std::cout << "ID: "				<< id					<< '\n';
		std::cout << "Size: "			<< typeInfo.Size		<< '\n';
		std::cout << "Align: "			<< typeInfo.Align		<< '\n';

		std::cout << "Is Fundamental: "			<< (typeInfo.Flags[TypeFlags_IsFundamental]			? "true" : "false") << '\n';
		std::cout << "Is Floating Point: "		<< (typeInfo.Flags[TypeFlags_IsFloatingPoint]		? "true" : "false") << '\n';
		std::cout << "Is Integral: "			<< (typeInfo.Flags[TypeFlags_IsIntegral]			? "true" : "false") << '\n';
		std::cout << "Is Trivially Copyable: "	<< (typeInfo.Flags[TypeFlags_IsTriviallyCopyable]	? "true" : "false") << '\n';

		if (typeInfo.GCConstructor)
		{
			std::cout << "GameComponent: ";
			std::unique_ptr<GameComponent> component{ typeInfo.GCConstructor() };
			component->Update(0.33f);
			component->Render();
		}

		std::cout << "\n\n";
	}
#else

	std::vector<TypeId> gameComponentsIds{};

	for (auto& [id, typeInfo] : TypeId::GetAllTypeInformation())
	{
		if (typeInfo.GCConstructor)
		{
			gameComponentsIds.emplace_back(id);
		}
	}

	while (true)
	{
		for (size_t i{}; i < gameComponentsIds.size(); ++i)
		{
			std::cout << "Enter '" << i << "' to create " << gameComponentsIds[i].GetTypeName() << '\n';
		}
		std::cout << "Enter 'q' to quit\n";

		char buffer{};
		std::cin >> buffer;

		if (buffer == 'q')
			break;

		size_t index = buffer - '0';
		if (index < gameComponentsIds.size())
		{
			std::cout << "Initialized " << gameComponentsIds[index].GetTypeName() << '\n';
			std::unique_ptr<GameComponent> component(gameComponentsIds[index].ConstructGC());
			
			component->Initialize();
			component->Update(0.1f);
			component->Render();
			
			std::cout << '\n';
		}
	}

#endif
}