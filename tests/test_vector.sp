#include <wlib/vector>
#include <multicolors>

public void OnPluginStart() {
	Test_VectorAdd();
	Test_VectorMul();
	Test_VectorEqual();
}

void Test_VectorAdd() {
	float vec[3] = { 1.0, 1.0, 1.0 };
	float add[3] = { 1.0, 1.0, 1.0 };

	VectorAdd(vec, add);

	CPrintToChatAll("{lime}VectorAdd::True Statement::%s", vec[0] == 2.0 ? "True":"False");
	CPrintToChatAll("{lime}VectorAdd::False Statement::%s", vec[0] == 4.0 ? "True":"False");
}

void Test_VectorMul() {
	float vec[3] = { 2.0, 1.0, 1.0 };
	float add[3] = { 4.0, 2.0, 2.0 };

	VectorMul(vec, add);

	CPrintToChatAll("{azure}VectorMul::True Statement::%s", vec[0] == 8.0 ? "True":"False");
	CPrintToChatAll("{azure}VectorMul::False Statement::%s", vec[0] == 6.0 ? "True":"False");
}

void Test_VectorEqual() {
	float vec[3] = { 2.0, 1.0, 1.0 };
	float equal[3] = { 2.0, 1.0, 1.0 };
	float equal2[3] = { 2.0, 2.0, 1.0 };

	bool result = VectorEqual(vec, equal);
	bool result2 = VectorEqual(vec, equal2);

	CPrintToChatAll("{white}VectorEqual::True Statement::%s", result ? "True":"False");
	CPrintToChatAll("{white}VectorEqual::False Statement::%s", result2 ? "True":"False");
}