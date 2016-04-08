﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include <gtest/gtest.h>

using namespace s3d;
using namespace s3d::literals;

TEST(Step, Iota)
{
	// 1 + 2 + 3 + ... + 100
	EXPECT_EQ(
		Iota(1, 101).reduce1(std::plus<>()),
		5050);

	// 100 の階乗
	EXPECT_EQ(
		Iota(1, 101).reduce1(std::multiplies<BigInt>()),
		L"93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"_big);
	
	// 100000000000000000000000000000000000000000000000001
	// +
	// 100000000000000000000000000000000000000000000000002
	// +
	// ...
	// +
	// 100000000000000000000000000000000000000000000000100
	EXPECT_EQ(
		Iota(L"100000000000000000000000000000000000000000000000001"_big, L"100000000000000000000000000000000000000000000000101"_big).reduce1(std::plus<>()),
		L"10000000000000000000000000000000000000000000000005050"_big);
}

TEST(Step, Range)
{
	// 1 + 2 + 3 + ... + 100
	EXPECT_EQ(
		Range(1, 100).reduce1(std::plus<>()),
		5050);

	// 100 の階乗
	EXPECT_EQ(
		Range(1, 100).reduce1(std::multiplies<BigInt>()),
		L"93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"_big);

	// 100000000000000000000000000000000000000000000000001
	// +
	// 100000000000000000000000000000000000000000000000002
	// +
	// ...
	// +
	// 100000000000000000000000000000000000000000000000100
	EXPECT_EQ(
		Range(L"100000000000000000000000000000000000000000000000001"_big, L"100000000000000000000000000000000000000000000000100"_big).reduce1(std::plus<>()),
		L"10000000000000000000000000000000000000000000000005050"_big);

	// FibBuzz
	{
		BigInt a = 0, b = 1;

		const auto result =
			Array<BigInt>{ 1 }
			.append(Range(1, 100).map([&](auto) { a = std::exchange(b, a + b); return b; }))
			.map([](const auto& n) { return n % 15 == 0 ? L"FizzBuzz" : n % 3 == 0 ? L"Fizz" : n % 5 == 0 ? L"Buzz" : n.str(); }).join();

		EXPECT_EQ(
			result,
			L"{1,1,2,Fizz,Buzz,8,13,Fizz,34,Buzz,89,Fizz,233,377,Buzz,Fizz,1597,2584,4181,FizzBuzz,10946,17711,28657,Fizz,Buzz,121393,196418,Fizz,514229,Buzz,1346269,Fizz,3524578,5702887,Buzz,Fizz,24157817,39088169,63245986,FizzBuzz,165580141,267914296,433494437,Fizz,Buzz,1836311903,2971215073,Fizz,7778742049,Buzz,20365011074,Fizz,53316291173,86267571272,Buzz,Fizz,365435296162,591286729879,956722026041,FizzBuzz,2504730781961,4052739537881,6557470319842,Fizz,Buzz,27777890035288,44945570212853,Fizz,117669030460994,Buzz,308061521170129,Fizz,806515533049393,1304969544928657,Buzz,Fizz,5527939700884757,8944394323791464,14472334024676221,FizzBuzz,37889062373143906,61305790721611591,99194853094755497,Fizz,Buzz,420196140727489673,679891637638612258,Fizz,1779979416004714189,Buzz,4660046610375530309,Fizz,12200160415121876738,19740274219868223167,Buzz,Fizz,83621143489848422977,135301852344706746049,218922995834555169026,FizzBuzz,573147844013817084101}");
	}
}
