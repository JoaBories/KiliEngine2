#include "Test.h"

#include <cstdio>
#include <string>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Kili
{
	void Print()
	{
		printf("Hello World! \n");
		Vector3 test3 = Vector3(1.0f, 2.0f, 3.0f) + Vector3::UnitX * 2;
		test3.normalize();
		test3 = -test3;
		printf(test3.asString().c_str());
		
		printf("\n");
		
		Vector2 test2 = Vector2(1.0f, 2.0f) + Vector2::UnitX * 2;
		test2.normalize();
		test2 = -test2;
		printf(test2.asString().c_str());
		
		printf("\n");
		
		Vector4 test4 = Vector4(1.0f, 2.0f, 3.0f, 4.0f) + Vector4::UnitX * 2;
		test4.normalize();
		test4 = -test4;
		printf(test4.asString().c_str());
	}
}
