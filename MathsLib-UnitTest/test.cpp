#include "pch.h"

// --------- This section tests that the vector class methods function correctly. ---------

TEST(Vector, constructors) {
	Vector v1({ -5, 3.1, 691, 391245, 0.0 });
	Vector v2 = { -5, 3.1, 691, 391245, 0.0 };
	Vector v3(3);

	EXPECT_EQ(v1[0], -5);
	EXPECT_EQ(v1[1], 3.1);
	EXPECT_EQ(v1[2], 691);
	EXPECT_EQ(v1[3], 391245);
	EXPECT_EQ(v1[4], 0.0);

	EXPECT_EQ(v2[0], -5);
	EXPECT_EQ(v2[1], 3.1);
	EXPECT_EQ(v2[2], 691);
	EXPECT_EQ(v2[3], 391245);
	EXPECT_EQ(v2[4], 0.0);

	for (const auto& i : v3) {
		EXPECT_EQ(i, 0);
	}
}


TEST(Vector, length) {
	// Test basic length of positive vector.
	Vector v1({ 1,2,3 });
	EXPECT_NEAR(v1.euclidean_length(), 3.74165738, 10e-5);

	// Test negatives.
	Vector v2({ -1,2,-3 });
	EXPECT_NEAR(v2.euclidean_length(), 3.74165738, 10e-5);

	// Test vector of many dimensions.
	Vector v3({ 1,2,3,4,5,6,7,8,9,10,11,12 });
	EXPECT_NEAR(v3.euclidean_length(), 25.4950978, 10e-5);
}


TEST(Vector, is_zero) {
	Vector v1({ 0,0,0,0,0,0 });
	EXPECT_EQ(v1.is_zero(10e-6), true);
	EXPECT_EQ(v1.is_zero(), true);

	Vector v2({ 0,0,0,5,3,0 });
	EXPECT_EQ(v2.is_zero(10e-6), false);
	EXPECT_EQ(v2.is_zero(), false);
}

TEST(Vector, normalise) {
	Vector v1({ 1,2,3 });
	Vector normalised_v1 = v1.normalise();
	EXPECT_NEAR(normalised_v1[0], 0.26726124, 10e-5);
	EXPECT_NEAR(normalised_v1[1], 0.53452248, 10e-5);
	EXPECT_NEAR(normalised_v1[2], 0.80178372, 10e-5);

	// Test negative numbers and multiple dimensions.
	Vector v2({ -15,12,0,5,1,5 });
	Vector normalised_v2 = v2.normalise();
	EXPECT_NEAR(normalised_v2[0], -0.73192505, 10e-5);
	EXPECT_NEAR(normalised_v2[1], 0.58554004, 10e-5);
	EXPECT_NEAR(normalised_v2[2], 0, 10e-5);
	EXPECT_NEAR(normalised_v2[3], 0.24397501, 10e-5);
	EXPECT_NEAR(normalised_v2[4], 0.04879500, 10e-5);
	EXPECT_NEAR(normalised_v2[5], 0.24397501, 10e-5);
}


TEST(Vector, dot_product) {
	Vector v1({ 1,2,3 });
	Vector v2({ 3,2,1 });

	EXPECT_EQ(v1.dot_product(v2), 10);

	// Test that an exception is thrown if dimensions of vectors do not match.
	Vector v3({ 1,2,3,4,5 });
	EXPECT_THROW(v1.dot_product(v3), std::invalid_argument);
}


TEST(Vector, size) {
	Vector v1({ 1,2,3 });
	EXPECT_EQ(v1.size(), 3);

	Vector v2({ 1,2,3,4,5,6,7,8,9 });
	EXPECT_EQ(v2.size(), 9);
}


TEST(Vector, cross_product) {
	// Basic test of a cross product.
	Vector v1({ -1,2,7 });
	Vector v2({ 3,2,9 });
	Vector v1_v2_cross({ 4,30,-8 });

	Vector test_cross = v1.cross_product(v2);

	EXPECT_EQ(test_cross[0], v1_v2_cross[0]);
	EXPECT_EQ(test_cross[1], v1_v2_cross[1]);
	EXPECT_EQ(test_cross[2], v1_v2_cross[2]);

	// Check that other dimensions throw an error.
	Vector v4({ 1,2,3,4 });

	EXPECT_THROW(v4.cross_product(v2), std::invalid_argument);
	EXPECT_THROW(v2.cross_product(v4), std::invalid_argument);
}

TEST(Vector, distance) {
	// Basic test of a cross product.
	Vector v1({ -1,3,2 });
	Vector v2({ 3,10,-3 });

	EXPECT_NEAR(v1.distance(v2), 9.4868329, 10e-5);
	EXPECT_NEAR(v2.distance(v1), 9.4868329, 10e-5);
}

// --------- This section tests operator overloading of the Vector class. ---------

// Test operator overload for Vector + Vector and it's associativity.
TEST(Vector, vector_plus_vector_operator) {
	Vector v1({ 1,2,3 });
	Vector v2({ 9,1,5 });

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
TEST(Vector, vector_minus_vector_operator) {
	Vector v1({ 1,2,3 });
	Vector v2({ 9,1,5 });

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

// check that multiplying a constant by a vector works as expected.
TEST(Vector, constant_multiply_vector_operator) {
	Vector v1({ 2,4,8 });

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

// Check that negating a vector will negate each element.
TEST(Vector, unary_negation_operator) {
	Vector v1({ 1,2,3,4,5 });

	// We check this operation is associative, this is important given they are different types.
	Vector v_test_1 = -v1;

	EXPECT_EQ(v_test_1[0], -1);
	EXPECT_EQ(v_test_1[1], -2);
	EXPECT_EQ(v_test_1[2], -3);
	EXPECT_EQ(v_test_1[3], -4);
	EXPECT_EQ(v_test_1[4], -5);
}

// Check the unary negation operator works as expected.
TEST(Ray, unary_negation_operator) {
	Vector v1({ 1,2,3 });
	Vector v2({ 9,1,5 });

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
TEST(Ray, constructors) {
	Vector v1({ 1,2,3 });
	Vector v2({ 9,1,5 });

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

TEST(Ray, point_distance) {
	Vector p1({ 1,2,5 });
	Vector d1({ 4,8,-4 });

	Vector new_point({ 4,5,1 });

	// Form the ray.
	Ray ray_1(p1, d1);

	EXPECT_NEAR(ray_1.point_distance(new_point), 2.41522945, 10e-5);
}

TEST(Ray, ray_add_ray_operator) {
	Vector p1({ 1,2,3 });
	Vector d1({ 9,1,-5 });

	Vector p2({ 6,-4,1 });
	Vector d2({ 9,1,-1 });

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

TEST(Ray, ray_minus_ray) {
	Vector p1({ 1,2,3 });
	Vector d1({ 9,1,-5 });

	Vector p2({ 6,-4,1 });
	Vector d2({ 9,1,-1 });

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

TEST(Ray, ray_multiply_integer) {
	Vector p1({ 1,2,3 });
	Vector d1({ 9,1,-5 });

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

TEST(Ray, intersect) {
	Vector p1({ 1,2,3 });
	Vector p2({ 1,2,3 });

	Vector d1({ 9,1,-5 });
	Vector d2({ 6,1,-3 });

	// Form two rays. These will obviously intersect.
	Ray ray_1(p1, d1);
	Ray ray_2(p2, d2);

	EXPECT_TRUE(ray_1.intersect(ray_2));
}

TEST(Vector, vector_equals_vector_operator) {
	EXPECT_EQ(Vector({ 1,2,3 }), Vector({ 1,2,3 }));
	EXPECT_THROW(Vector({ 1,2,3 }) == Vector({ 1,2,3,4 }), std::invalid_argument);
}

// ------------------------ Matrix tests ----------------------------

TEST(Matrix, constructors) {
	Matrix M0({ { 1, 3, 4, 5 }, { 6, 5, 3, 1 }, { 9, 7, 7, 4 } });
	Matrix M1 = { { 1, 3, 4, 5 }, { 6, 5, 3, 1 }, { 9, 7, 7, 4 } };
	Matrix M2(100);

	EXPECT_EQ(M0.get_col_count(), 4);
	EXPECT_EQ(M0.get_row_count(), 3);

	EXPECT_EQ(M1.get_col_count(), 4);
	EXPECT_EQ(M1.get_row_count(), 3);

	EXPECT_EQ(M2.get_col_count(), 100);
	EXPECT_EQ(M2.get_row_count(), 100);

	std::vector<std::vector<double>> comparison_matrix = { { 1, 3, 4, 5 }, { 6, 5, 3, 1 }, { 9, 7, 7, 4 } };
	for (int x = 0; x < M0.get_col_count(); x++) {
		for (int y = 0; y < M0.get_row_count(); y++) {
			EXPECT_EQ(M0[y][x], comparison_matrix[y][x]);
		}
	}

	for (int x = 0; x < M1.get_col_count(); x++) {
		for (int y = 0; y < M1.get_row_count(); y++) {
			EXPECT_EQ(M1[y][x], comparison_matrix[y][x]);
		}
	}

	for (const auto& V : M2) {
		for (const auto& E : V) {
			EXPECT_EQ(E, 0);
		}
	}

	Vector V0({ -5, 3.1, 691, 391245, 0.0 });
	Matrix M3(V0);

	EXPECT_EQ(M3.get_col_count(), 1);
	EXPECT_EQ(M3.get_row_count(), 5);

	int i = 0;
	for (const auto& V1 : M3) {
		EXPECT_EQ(V1[0], V0[i++]);
	}
}

TEST(Matrix, transpose) {
	Matrix M0 = { { 1, 3, 4, 5 }, { 6, 5, 3, 1 }, { 9, 7, 7, 4 } };
	Matrix M1 = { {1, 6, 9}, {3, 5, 7}, {4, 3, 7}, {5, 1, 4} };

	EXPECT_EQ(M0.get_col_count(), 4);
	EXPECT_EQ(M0.get_row_count(), 3);

	EXPECT_EQ(M1.get_col_count(), 3);
	EXPECT_EQ(M1.get_row_count(), 4);

	EXPECT_EQ(M0.transpose().get_col_count(), 3);
	EXPECT_EQ(M0.transpose().get_row_count(), 4);

	EXPECT_EQ(M1.transpose().get_col_count(), 4);
	EXPECT_EQ(M1.transpose().get_row_count(), 3);

	Matrix M2 = Matrix(Vector({ 1,2,3,4 }));

	EXPECT_EQ(M2.transpose().get_col_count(), 4);
	EXPECT_EQ(M2.transpose().get_row_count(), 1);

}

TEST(Matrix, matrix_equals_matrix_operator) {
	Matrix M0 = { { 1, 3, 4, 5 }, { 6, 5, 3, 1 }, { 9, 7, 7, 4 } };
	Matrix M1 = { { 1, 3, 4, 5 }, { 6, 5, 3, 1 }, { 9, 7, 7, 4 } };

	EXPECT_EQ(M0, M1);
}

TEST(Matrix, identity) {

	EXPECT_EQ(Matrix::identity(13).get_col_count(), 13);
	EXPECT_EQ(Matrix::identity(13).get_row_count(), 13);

	Matrix M({
		{10,  77, 45},
		{13,  60, 44},
		{21, 117, 85}
	});

	EXPECT_EQ(Matrix::identity(3) * M, M);
	EXPECT_EQ(M * Matrix::identity(3), M);
	EXPECT_EQ(Matrix::identity(3) * M * Matrix::identity(3), M);
}

TEST(Matrix, matrix_equals_vector_operator) {
	Matrix M = { { 1, 2, 3, 4 } };
	Vector V0({ 1,2,3,4 });
	Vector V1({ 1,2,3,4,5 });

	EXPECT_EQ(M.transpose(), V0);
	EXPECT_EQ(V0, M.transpose());

	EXPECT_FALSE(M.transpose() == V1);
	EXPECT_FALSE(V1 == M.transpose());
}

TEST(Matrix, matrix_multiply_vector_operator) {
	Matrix M({
		{ 1, 3, 4, 5 },
		{ 6, 5, 3, 1 },
		{ 9, 7, 7, 4 }
		});

	Vector V({ 1,2,3,4 });

	Vector solution({ 39, 29, 60 });

	EXPECT_EQ(M * V, solution);
}

TEST(Matrix, matrix_multiply_matrix_operator) {
	Matrix M0({
		{ 1, 3, 4, 5 },
		{ 6, 5, 3, 1 },
		{ 9, 7, 7, 4 }
		});

	Matrix M1({
		{0, 2, 3},
		{2, 6, 2},
		{1, 3, 4},
		{0, 9, 4}
		});

	Matrix solution_0({
		{10,  77, 45},
		{13,  60, 44},
		{21, 117, 85}
	});

	Matrix solution_1({
		{39, 31, 27, 14},
		{56, 50, 40, 24},
		{55, 46, 41, 24},
		{90, 73, 55, 25}
	});

	EXPECT_THROW(M0 * M0, std::invalid_argument);
	EXPECT_THROW(M1 * M1, std::invalid_argument);

	EXPECT_EQ(M0 * M1, solution_0);
	EXPECT_EQ(M1 * M0, solution_1);

	EXPECT_EQ(Matrix({{1}}) * Matrix({{1}}), Matrix({{1}}));
}

TEST(Matrix, trace) {
	Matrix M0({
		{ 1, 3, 4, 5 },
		{ 6, 5, 3, 1 },
		{ 9, 7, 7, 4 }
	});

	Matrix M1({
		{10,  77, 45},
		{13,  60, 44},
		{21, 117, 85}
	});

	EXPECT_THROW(M0.trace(), std::invalid_argument);
	EXPECT_EQ(M1.trace(), 155);
	EXPECT_EQ(Matrix::identity(103).trace(), 103);
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
