
#include "VariableId.h"

#include <iostream>

void TestFunction(int, double&, const char*, volatile uint64_t&&, float[64])
{}

void* TestFunction2(int = 5, float = 5.f)
{
	return 0;
}

struct TestStruct
{
	int Var0{};
	int& Var1;
	double* Var2{};
};

template <typename Parameter0, typename... Parameters>
void PrintParameters()
{
	std::cout << '\t' << GetVariableName(VariableId::Create<Parameter0>()) << '\n';
	if constexpr (sizeof...(Parameters) != 0)
	{
		PrintParameters<Parameters...>();
	}
}

template <typename ReturnType, typename... ParameterTypes>
void PrintFunction(ReturnType(*)(ParameterTypes...))
{
	std::cout << "Return type: " << GetVariableName(VariableId::Create<ReturnType>()) << '\n';
	std::cout << "Parameters{\n";
	PrintParameters<ParameterTypes...>();
	std::cout << "}\n";
}

int main()
{
	std::cout << GetVariableName(VariableId::Create<int>						()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int&>						()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int&&>						()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int*>						()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int**>						()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int[8]>						()) << '\n';

	std::cout << GetVariableName(VariableId::Create<const int>					()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const int&>					()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const int&&>				()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const int*>					()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const int**>				()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const int[8]>				()) << '\n';

	std::cout << GetVariableName(VariableId::Create<const volatile int>			()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const volatile int&>		()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const volatile int&&>		()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const volatile int*>		()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const volatile int**>		()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const volatile int[8]>		()) << '\n';

	std::cout << GetVariableName(VariableId::Create<const volatile int****&>	()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int[8][8][8]>				()) << '\n';
	std::cout << GetVariableName(VariableId::Create<int***[8]>					()) << '\n';
	std::cout << GetVariableName(VariableId::Create<const volatile int**[8][8]>	()) << '\n';
	
	std::cout << "\n";

	for (auto& [id, info] : TypeId::GetAllTypeInformation())
	{
		std::cout << info.Name << '\n';
	}

	std::cout << "\n";

	PrintFunction(TestFunction);

	std::cout << "\n";

	std::cout << "Struct [" << TypeId::Create<TestStruct>().GetTypeName() << "] Contains:";
	std::cout << "{\n";
	std::cout << '\t' << GetVariableName(VariableId::Create<decltype(TestStruct::Var0)>()) << '\n';
	std::cout << '\t' << GetVariableName(VariableId::Create<decltype(TestStruct::Var1)>()) << '\n';
	std::cout << '\t' << GetVariableName(VariableId::Create<decltype(TestStruct::Var2)>()) << '\n';
	std::cout << '}';

}
