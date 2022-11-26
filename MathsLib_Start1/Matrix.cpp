#include "Matrix.h"


// Constructors.
Matrix::Matrix(std::initializer_list<std::initializer_list<double>> matrix) {
	for (const auto& vector : matrix) {
		internal_storage.push_back(std::vector<double>(vector));
	}

	verify_size();
}

Matrix::Matrix(std::vector<std::vector<double>> matrix) : internal_storage{ matrix } { verify_size(); }

Matrix::Matrix(const Vector& V) {
	for (const auto& i : V) {
		internal_storage.emplace_back(1, i);
	}
	verify_size();
}

Matrix::Matrix(const size_t& size) : internal_storage{
	std::vector<std::vector<double>>{
	std::vector(size, std::vector<double>(size, 0.0))
} } { 
	verify_size();
}

Matrix::Matrix(const size_t& x, const size_t& y) : internal_storage{
	std::vector<std::vector<double>>{
	std::vector(y, std::vector<double>(x, 0.0))
} } { 
	verify_size();
}

void Matrix::verify_size() {
	if (internal_storage.empty()) {
		throw std::invalid_argument("Cannot construct an empty matrix.");
	}

	if (internal_storage[0].empty()) {
		throw std::invalid_argument("Cannot construct an empty matrix.");
	}
}

size_t Matrix::get_col_count() const noexcept {
	return internal_storage[0].size();
}

size_t Matrix::get_row_count() const noexcept {
	return internal_storage.size();
}

std::vector<std::vector<double>> Matrix::get_internal_storage() const noexcept {
	return internal_storage;
}

Matrix Matrix::transpose() const {

	Matrix M(get_row_count(), get_col_count());

	for (int x = 0; x < get_row_count(); x++) {
		for (int y = 0; y < get_col_count(); y++) {
			M[y][x] = internal_storage[x][y];
		}
	}

	return M;
}

Matrix Matrix::identity(const size_t& num) noexcept {
	Matrix M(num);

	for (int i = 0; i < num; i++) {
		M[i][i] = 1;
	}

	return M;
}

void Matrix::print() const noexcept {
	for (const auto& vector : internal_storage) {
		for (const auto& i : vector) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

double Matrix::trace() const {
	
	if (get_col_count() != get_row_count()) {
		throw std::invalid_argument("Trace of a matrix can only be obtained if the matrix is square.");
	}

	double sum = 0;

	for (int i = 0; i < get_col_count(); i++) {
		sum += internal_storage[i][i];
	}
	
	return sum;
}

// Operator overloads.
std::vector<double>& Matrix::operator[](const size_t& index) {
	return internal_storage[index];
}

bool Matrix::operator==(const Matrix& M) const noexcept {
	return internal_storage == get_internal_storage();
}

bool Matrix::operator==(const Vector& V) const noexcept {
	return Matrix(internal_storage).transpose().get_internal_storage()[0] == V.get_internal_storage();
}

Matrix operator*(const Matrix& M, const Vector& V) {
	return M * Matrix(V);
}

// Friend operator overload since Matrix * Matrix is not commutative under multplication.
Matrix operator*(const Matrix& M0, const Matrix& M1) {

	// mxp * pxn = mxn
	// 3x2 * 2x3 = 2X2

	if (M0.get_col_count() != M1.get_row_count()) {
		throw std::invalid_argument("Matrix multiplication must have valid dimensions.");
	}

	Matrix M(M0.get_row_count(), M1.get_col_count());

	int x = 0;
	int y = 0;
	for (const auto& V1 : M1.transpose()) {
		for (const auto& V0 : M0) {
			M[y][x] = Vector(V1).dot_product(V0);
			x++;
		}
		x = 0;
		y++;
	}

	return M.transpose();
}
