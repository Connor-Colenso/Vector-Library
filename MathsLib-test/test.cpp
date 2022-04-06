#include "pch.h"

// --------- This section tests that the vector class methods function correctly. ---------

// Tests the constructor and square brackets operator overload.
TEST(VectorIntilisationTest, TestName)
{
	std::vector<double> test = { -5, 3.1, 691, 391245, 0.0 };
	Vector v1(test);

	EXPECT_EQ(test[0], -5);
	EXPECT_EQ(test[1], 3.1);
	EXPECT_EQ(test[2], 691);
	EXPECT_EQ(test[3], 391245);
	EXPECT_EQ(test[4], 0.0);
}

TEST(TestVectorLength, TestName) 
{
	// Test basic length of positive vector
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);
	EXPECT_NEAR(v1.length(), 3.74165738, 10e-5);

	// Test negatives
	std::vector<double> test2 = { -1,2,-3 };
	Vector v2(test2);
	EXPECT_NEAR(v2.length(), 3.74165738, 10e-5);

	// Test vector of many dimensions.
	std::vector<double> test3 = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Vector v3(test3);
	EXPECT_NEAR(v3.length(), 25.4950978, 10e-5);
}


TEST(TestVectorIsZero, TestName) 
{
	std::vector<double> test1 = { 0,0,0,0,0,0 };
	Vector v1(test1);
	EXPECT_EQ(v1.is_zero(10e-6), true);

	std::vector<double> test2 = { 0,0,0,5,3,0 };
	Vector v2(test2);
	EXPECT_EQ(v2.is_zero(10e-6), false);

}

TEST(TestVectorNormalisation, TestName)
{
	// Basic test.
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);
	Vector normalised_v1 = v1.normalise();
	EXPECT_NEAR(normalised_v1[0], 0.26726124, 10e-5);
	EXPECT_NEAR(normalised_v1[1], 0.53452248, 10e-5);
	EXPECT_NEAR(normalised_v1[2], 0.80178372, 10e-5);

	// Test negative numbers and multiple dimensions.
	std::vector<double> test2 = { -15,12,0,5,1,5 };
	Vector v2(test2);
	Vector normalised_v2 = v2.normalise();
	EXPECT_NEAR(normalised_v2[0], -0.73192505, 10e-5);
	EXPECT_NEAR(normalised_v2[1], 0.58554004, 10e-5);
	EXPECT_NEAR(normalised_v2[2], 0, 10e-5);
	EXPECT_NEAR(normalised_v2[3], 0.24397501, 10e-5);
	EXPECT_NEAR(normalised_v2[4], 0.04879500, 10e-5);
	EXPECT_NEAR(normalised_v2[5], 0.24397501, 10e-5);
}

TEST(TestVectorDotProduct, TestName)
{
	// Basic test.
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	std::vector<double> test2 = { 3,2,1 };
	Vector v2(test2);

	EXPECT_EQ(v1.dot_product(v2), 10);

	// Test that an exception is thrown if dimensions of vectors do not match.
	std::vector<double> test3 = { 1,2,3,4,5 };
	Vector v3(test3);
	EXPECT_THROW(v1.dot_product(v3), std::invalid_argument);
}

TEST(TestVectorSize, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);
	EXPECT_EQ(v1.size(), 3);

	std::vector<double> test2 = { 1,2,3,4,5,6,7,8,9 };
	Vector v2(test2);
	EXPECT_EQ(v2.size(), 9);

}

TEST(TestVectorCrossProduct, TestName)
{
	// Basic test of a cross product.
	std::vector<double> test1 = { -1,2,7 };
	Vector v1(test1);

	std::vector<double> test2 = { 3,2,9 };
	Vector v2(test2);

	std::vector<double> test3 = { 4,30,-8 };
	Vector v1_v2_cross(test3);

	Vector test_cross = v1.cross_product(v2);

	EXPECT_EQ(test_cross[0], v1_v2_cross[0]);
	EXPECT_EQ(test_cross[1], v1_v2_cross[1]);
	EXPECT_EQ(test_cross[2], v1_v2_cross[2]);

	// Check that other dimensions throw an error.
	std::vector<double> test4 = { 1,2,3,4 };
	Vector v4(test4);

	EXPECT_THROW(v4.cross_product(v2), std::invalid_argument);
	EXPECT_THROW(v2.cross_product(v4), std::invalid_argument);

}

TEST(TestPointPointDistance, TestName)
{
	// Basic test of a cross product.
	std::vector<double> test1 = { -1,3,2 };
	Vector v1(test1);

	std::vector<double> test2 = { 3,10,-3 };
	Vector v2(test2);

	EXPECT_NEAR(v1.distance(v2), 9.4868329, 10e-5);
	EXPECT_NEAR(v2.distance(v1), 9.4868329, 10e-5);

}

// --------- This section tests operator overloading of the vector class. ---------

// Test operator overload for Vector + Vector and it's associativity.
TEST(TestVectorPlusVectorOperatorOverload, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	std::vector<double> test2 = { 9,1,5 };
	Vector v2(test2);

	// Check both ways to make sure it's associative.
	Vector v3 = v1 + v2;
	Vector v4 = v2 + v1;

	EXPECT_EQ(v3[0], 10);
	EXPECT_EQ(v3[1], 3);
	EXPECT_EQ(v3[2], 8);

	EXPECT_EQ(v4[0], 10);
	EXPECT_EQ(v4[1], 3);
	EXPECT_EQ(v4[2], 8);

}

// Test operator overload for Vector - Vector and it's associativity.
TEST(TestVectorSubtractVectorOperatorOverload, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	std::vector<double> test2 = { 9,1,5 };
	Vector v2(test2);

	// Check both ways to make sure it's associative.
	Vector v3 = v1 - v2;
	Vector v4 = v2 - v1;

	EXPECT_EQ(v3[0], -8);
	EXPECT_EQ(v3[1], 1);
	EXPECT_EQ(v3[2], -2);

	EXPECT_EQ(v4[0], 8);
	EXPECT_EQ(v4[1], -1);
	EXPECT_EQ(v4[2], 2);
}

// Test operator overload for Vector * Vector and it's associativity.
TEST(TestVectorMultiplyVectorOperatorOverload, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	std::vector<double> test2 = { 9,1,5 };
	Vector v2(test2);

	// Check both ways to make sure it's associative.
	Vector v3 = v1 * v2;
	Vector v4 = v2 * v1;

	EXPECT_EQ(v3[0], 9);
	EXPECT_EQ(v3[1], 2);
	EXPECT_EQ(v3[2], 15);

	EXPECT_EQ(v4[0], 9);
	EXPECT_EQ(v4[1], 2);
	EXPECT_EQ(v4[2], 15);

}

// check that multiplying a constant by a vector works as expected.
TEST(TestVectorMultiplyDoubleOperator, TestName) 
{
	std::vector<double> test1 = { 2,4,8 };
	Vector v1(test1);

	// We check this operation is associative, this is important given they are different types.
	Vector v_test_1 = v1 * 0.5;
	Vector v_test_2 = 0.5 * v1;

	EXPECT_EQ(v_test_1[0], 1);
	EXPECT_EQ(v_test_1[1], 2);
	EXPECT_EQ(v_test_1[2], 4);

	EXPECT_EQ(v_test_2[0], 1);
	EXPECT_EQ(v_test_2[1], 2);
	EXPECT_EQ(v_test_2[2], 4);

}

// Check that adding a constant to a vector works as expected. This is a nonsensical operation but the spec requires it so...
TEST(TestVectorAddDoubleOperator, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	Vector v_test_1 = v1 + 1.0;

	EXPECT_EQ(v_test_1[0], 2);
	EXPECT_EQ(v_test_1[1], 3);
	EXPECT_EQ(v_test_1[2], 4);

}

// Check that negating a vector will negate each element.
TEST(TestVectorNegation, TestName)
{
	std::vector<double> test1 = { 1,2,3,4,5 };
	Vector v1(test1);

	// We check this operation is associative, this is important given they are different types.
	Vector v_test_1 = -v1;

	EXPECT_EQ(v_test_1[0], -1);
	EXPECT_EQ(v_test_1[1], -2);
	EXPECT_EQ(v_test_1[2], -3);
	EXPECT_EQ(v_test_1[3], -4);
	EXPECT_EQ(v_test_1[4], -5);
}

// Check the unary negation operator works as expected.
TEST(TestRayNegationOperator, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	std::vector<double> test2 = { 9,1,5 };
	Vector v2(test2);

	// Check both ways to make sure it's associative.
	Ray ray(v1, v2);
	Ray ray_negative = -ray;

	// Check position.
	EXPECT_EQ(ray_negative.position[0], -1);
	EXPECT_EQ(ray_negative.position[1], -2);
	EXPECT_EQ(ray_negative.position[2], -3);

	// Check direction.
	EXPECT_EQ(ray_negative.direction[0], -9);
	EXPECT_EQ(ray_negative.direction[1], -1);
	EXPECT_EQ(ray_negative.direction[2], -5);

}

// -------- Ray class testing below -------------
TEST(TestRayPointDistance, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector v1(test1);

	std::vector<double> test2 = { 9,1,5 };
	Vector v2(test2);

	// Check both ways to make sure it's associative.
	Ray ray(v1, v2);
	Ray ray_negative = -ray;

	// Check position.
	EXPECT_EQ(ray_negative.position[0], -1);
	EXPECT_EQ(ray_negative.position[1], -2);
	EXPECT_EQ(ray_negative.position[2], -3);

	// Check direction.
	EXPECT_EQ(ray_negative.direction[0], -9);
	EXPECT_EQ(ray_negative.direction[1], -1);
	EXPECT_EQ(ray_negative.direction[2], -5);

}

TEST(TestRayMinPointDistance, TestName)
{
	std::vector<double> test1 = { 1,2,5 };
	Vector p1(test1);

	std::vector<double> test2 = { 4,8,-4 };
	Vector d1(test2);

	std::vector<double> test3 = { 4,5,1 };
	Vector new_point(test3);

	// Form the ray.
	Ray ray_1(p1, d1);

	EXPECT_NEAR(ray_1.point_distance(new_point), 2.41522945, 10e-5);
}

TEST(TestRayPlusRay, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector p1(test1);

	std::vector<double> test2 = { 9,1,-5 };
	Vector d1(test2);

	std::vector<double> test3 = { 6,-4,1 };
	Vector p2(test3);

	std::vector<double> test4 = { 9,1,-1 };
	Vector d2(test4);

	// Form two rays.
	Ray ray_1(p1, d1);
	Ray ray_2(p2, d2);

	Ray ray_3 = ray_1 + ray_2;

	EXPECT_EQ(ray_3.position[0], 7);
	EXPECT_EQ(ray_3.position[1], -2);
	EXPECT_EQ(ray_3.position[2], 4);

	EXPECT_EQ(ray_3.direction[0], 18);
	EXPECT_EQ(ray_3.direction[1], 2);
	EXPECT_EQ(ray_3.direction[2], -6);

}

TEST(TestRayMinusRay, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector p1(test1);

	std::vector<double> test2 = { 9,1,-5 };
	Vector d1(test2);

	std::vector<double> test3 = { 6,-4,1 };
	Vector p2(test3);

	std::vector<double> test4 = { 9,1,-1 };
	Vector d2(test4);

	// Form two rays.
	Ray ray_1(p1, d1);
	Ray ray_2(p2, d2);

	Ray ray_3 = ray_1 - ray_2;

	EXPECT_EQ(ray_3.position[0], -5);
	EXPECT_EQ(ray_3.position[1], 6);
	EXPECT_EQ(ray_3.position[2], 2);

	EXPECT_EQ(ray_3.direction[0], 0);
	EXPECT_EQ(ray_3.direction[1], 0);
	EXPECT_EQ(ray_3.direction[2], -4);

}

TEST(TestRayMultiplyDouble, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector p1(test1);

	std::vector<double> test2 = { 9,1,-5 };
	Vector d1(test2);


	// Form two rays.
	Ray ray_1(p1, d1);

	Ray ray_2 = ray_1 * 3;

	EXPECT_EQ(ray_2.position[0], 3);
	EXPECT_EQ(ray_2.position[1], 6);
	EXPECT_EQ(ray_2.position[2], 9);

	EXPECT_EQ(ray_2.direction[0], 27);
	EXPECT_EQ(ray_2.direction[1], 3);
	EXPECT_EQ(ray_2.direction[2], -15);

}

TEST(TestRayIntersection, TestName)
{
	std::vector<double> test1 = { 1,2,3 };
	Vector p1(test1);

	std::vector<double> test2 = { 1,2,3 };
	Vector p2(test2);

	std::vector<double> test3 = { 9,1,-5 };
	Vector d1(test3);

	std::vector<double> test4 = { 6,1,-3};
	Vector d2(test4);


	// Form two rays. These will obviously intersect.
	Ray ray_1(p1, d1);
	Ray ray_2(p2, d2);

	EXPECT_EQ(ray_1.intersect(ray_2), true);

}

TEST(VectorEqualityOperator, TestName)
{
	EXPECT_EQ(Vector({ 1,2,3 }), Vector({ 1,2,3 }));
	EXPECT_EQ(Vector({ 1,2,3 }), "TEST");
	EXPECT_THROW(Vector({ 1,2,3 }) == Vector({ 1,2,3,4 }), std::invalid_argument);
}

// ------------------------ Matrix tests ----------------------------

TEST(MatrixMultiplyVector, TestName)
{
	Matrix M({ Vector({ 1, 3, 4, 5 }), Vector({ 6, 5, 3, 1 }), Vector({ 9, 7, 7, 4 }) });
	Vector v({ 1,2,3,4 });

	Vector solution({ 40, 29, 60});

	EXPECT_EQ(M * v, solution);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
