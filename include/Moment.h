#pragma once
namespace POBR
{
	struct Moment
	{
		double value;
		double i;
		double j;

		operator double() const
		{
			return value;
		}

		Moment() = delete;
		Moment(const double value, const double i, const double j)
			: value{ value }, i{ i }, j{ j } {};
		Moment(const double value, const int i, const int j)
			: value{ value }, i{ static_cast<double>(i) }, j{ static_cast<double>(j) } {};
	};
}