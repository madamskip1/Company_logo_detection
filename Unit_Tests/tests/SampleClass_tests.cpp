#include <catch2/catch.hpp>

#include "SampleClass.h"

namespace DummyTests
{
	TEST_CASE("Dummy Test", "[Dummy]")
	{
		SampleClass sampleClass;
		CHECK(true);
		REQUIRE(sampleClass.testMe());
	}
}