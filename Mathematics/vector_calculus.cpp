#include <cstdint>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include <iostream>
#include <iomanip>

using uint8192_t = __int128;

// Type aliases for clarity
using Matrix = std::vector<std::vector<uint8192_t>>;
using Vector = std::vector<uint8192_t>;

class vector_calculus {
private:
    // Private helper functions
    void validate_dimensions(size_t rows, size_t cols) const {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Dimensions must be positive");
        }
    }

    void validate_vector(const Vector& vec) const {
        if (vec.empty()) {
            throw std::invalid_argument("Vector cannot be empty");
        }
    }

    void validate_matrix(const Matrix& mat) const {
        if (mat.empty() || mat[0].empty()) {
            throw std::invalid_argument("Matrix cannot be empty");
        }
        size_t cols = mat[0].size();
        for (const auto& row : mat) {
            if (row.size() != cols) {
                throw std::invalid_argument("Matrix rows must have consistent size");
            }
        }
    }

    // Helper function to create a submatrix by excluding a row and column
    Matrix get_submatrix(const Matrix& mat, size_t exclude_row, size_t exclude_col) const {
        size_t rows = mat.size();
        size_t cols = mat[0].size();
        Matrix submat(rows - 1, Vector(cols - 1));
        size_t sub_i = 0;
        for (size_t i = 0; i < rows; ++i) {
            if (i == exclude_row) continue;
            size_t sub_j = 0;
            for (size_t j = 0; j < cols; ++j) {
                if (j == exclude_col) continue;
                submat[sub_i][sub_j] = mat[i][j];
                ++sub_j;
            }
            ++sub_i;
        }
        return submat;
    }

public:
    // Matrix Operations
    void sum_of_subspaces(const Matrix& subspaces, Vector& subspace_sums) {
        size_t number_of_rows = subspaces.size();
        size_t number_of_columns = subspaces[0].size();
        validate_dimensions(number_of_rows, number_of_columns);
        subspace_sums.resize(number_of_columns, 0);
        for (size_t i = 0; i < number_of_columns; i++) {
            uint8192_t sum = 0;
            for (size_t j = 0; j < number_of_rows; j++) {
                sum += subspaces[j][i];
            }
            subspace_sums[i] = sum;
        }
    }

    uint8192_t direct_sum(const Matrix& subspaces_to_sum) {
        size_t number_of_rows = subspaces_to_sum.size();
        size_t number_of_columns = subspaces_to_sum[0].size();
        validate_dimensions(number_of_rows, number_of_columns);
        uint8192_t sum = 0;
        for (const auto& row : subspaces_to_sum) {
            for (const auto& elem : row) {
                sum += elem;
            }
        }
        return sum;
    }

    // Vector Operations
    bool is_a_linear_combination(const Vector& vector,
                                 const Vector& vector1,
                                 const Vector& vector2,
                                 uint8192_t lambda1,
                                 uint8192_t lambda2) {
        size_t vector_length = vector.size();
        if (vector1.size() != vector_length || vector2.size() != vector_length) {
            throw std::invalid_argument("Vectors must have the same length");
        }
        for (size_t i = 0; i < vector_length; i++) {
            if (vector[i] != lambda1 * vector1[i] + lambda2 * vector2[i]) {
                return false;
            }
        }
        return true;
    }

    uint8192_t dot_product(const Vector& vec1, const Vector& vec2) {
        if (vec1.size() != vec2.size()) {
            throw std::invalid_argument("Vectors must have the same length");
        }
        return std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), uint8192_t(0));
    }

    double vector_norm(const Vector& vec) {
        uint8192_t sum = dot_product(vec, vec);
        return std::sqrt(static_cast<double>(sum));
    }

    Vector cross_product(const Vector& vec1, const Vector& vec2) {
        if (vec1.size() != 3 || vec2.size() != 3) {
            throw std::invalid_argument("Cross product is only defined for 3D vectors");
        }
        Vector result(3);
        result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
        result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
        return result;
    }

    // Matrix Transpose
    Matrix transpose(const Matrix& input) {
        size_t rows = input.size();
        size_t cols = input[0].size();
        Matrix output(cols, Vector(rows));
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                output[j][i] = input[i][j];
            }
        }
        return output;
    }

    // Vector Projection
    Vector project_vector(const Vector& u, const Vector& v) {
        if (u.size() != v.size()) {
            throw std::invalid_argument("Vectors must have the same length");
        }
        uint8192_t dot_uv = dot_product(u, v);
        uint8192_t dot_vv = dot_product(v, v);
        if (dot_vv == 0) throw std::runtime_error("Division by zero in projection");
        double scalar = static_cast<double>(dot_uv) / dot_vv;
        Vector result(v.size());
        for (size_t i = 0; i < v.size(); i++) {
            result[i] = static_cast<uint8192_t>(scalar * v[i]);
        }
        return result;
    }

    // Angle between vectors (in radians)
    double angle_between_vectors(const Vector& vec1, const Vector& vec2) {
        if (vec1.size() != vec2.size()) {
            throw std::invalid_argument("Vectors must have the same length");
        }
        double norm1 = vector_norm(vec1);
        double norm2 = vector_norm(vec2);
        if (norm1 == 0 || norm2 == 0) {
            throw std::runtime_error("Zero vector in angle calculation");
        }
        double dot = static_cast<double>(dot_product(vec1, vec2));
        return std::acos(dot / (norm1 * norm2));
    }

    // Orthogonal check
    bool are_orthogonal(const Vector& vec1, const Vector& vec2) {
        if (vec1.size() != vec2.size()) {
            throw std::invalid_argument("Vectors must have the same length");
        }
        return dot_product(vec1, vec2) == 0;
    }

    // Vector scaling
    void scale_vector(Vector& vec, uint8192_t scalar) {
        for (auto& elem : vec) {
            elem *= scalar;
        }
    }

    // Matrix-Vector multiplication
    Vector matrix_vector_multiply(const Matrix& matrix, const Vector& vector) {
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        if (vector.size() != cols) {
            throw std::invalid_argument("Matrix columns must match vector size");
        }
        Vector result(rows, 0);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result[i] += matrix[i][j] * vector[j];
            }
        }
        return result;
    }

    // Linear independence check (simplified)
    bool are_linearly_independent(const std::vector<Vector>& vectors) {
        if (vectors.empty()) return false;
        size_t length = vectors[0].size();
        for (const auto& vec : vectors) {
            if (vec.size() != length) {
                throw std::invalid_argument("All vectors must have the same length");
            }
        }
        // Simplified check using orthogonality
        for (size_t i = 0; i < vectors.size(); i++) {
            for (size_t j = i + 1; j < vectors.size(); j++) {
                if (!are_orthogonal(vectors[i], vectors[j])) {
                    return false;
                }
            }
        }
        return true;
    }

    // **New Features**

    ### Matrix-Matrix Multiplication
    Matrix matrix_multiply(const Matrix& mat1, const Matrix& mat2) {
        size_t rows1 = mat1.size();
        size_t cols1 = mat1[0].size();
        size_t rows2 = mat2.size();
        size_t cols2 = mat2[0].size();
        if (cols1 != rows2) {
            throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
        }
        Matrix result(rows1, Vector(cols2, 0));
        for (size_t i = 0; i < rows1; i++) {
            for (size_t j = 0; j < cols2; j++) {
                for (size_t k = 0; k < cols1; k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return result;
    }

    ### Determinant Calculation (Recursive Laplace Expansion)
    uint8192_t determinant(const Matrix& mat) {
        size_t rows = mat.size();
        size_t cols = mat[0].size();
        if (rows != cols) {
            throw std::invalid_argument("Matrix must be square for determinant calculation");
        }
        if (rows == 1) return mat[0][0];
        if (rows == 2) {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }
        uint8192_t det = 0;
        for (size_t j = 0; j < cols; j++) {
            Matrix submat = get_submatrix(mat, 0, j);
            int sign = (j % 2 == 0) ? 1 : -1;
            det += sign * mat[0][j] * determinant(submat);
        }
        return det;
    }

    ### Matrix Inversion (Gaussian Elimination with Partial Pivoting)
    Matrix matrix_inverse(const Matrix& mat) {
        size_t n = mat.size();
        if (n != mat[0].size()) {
            throw std::invalid_argument("Matrix must be square for inversion");
        }
        Matrix aug(n, Vector(2 * n, 0));
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                aug[i][j] = mat[i][j];
            }
            aug[i][n + i] = 1; // Augment with identity matrix
        }
        // Forward elimination with partial pivoting
        for (size_t k = 0; k < n; k++) {
            size_t max_row = k;
            uint8192_t max_val = std::abs(aug[k][k]);
            for (size_t i = k + 1; i < n; i++) {
                if (std::abs(aug[i][k]) > max_val) {
                    max_val = std::abs(aug[i][k]);
                    max_row = i;
                }
            }
            if (max_val == 0) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }
            std::swap(aug[k], aug[max_row]);
            for (size_t i = k + 1; i < n; i++) {
                uint8192_t factor = aug[i][k] / aug[k][k];
                for (size_t j = k; j < 2 * n; j++) {
                    aug[i][j] -= factor * aug[k][j];
                }
            }
        }
        // Backward substitution
        for (int k = n - 1; k >= 0; k--) {
            uint8192_t pivot = aug[k][k];
            if (pivot == 0) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }
            for (int j = 2 * n - 1; j >= k; j--) {
                aug[k][j] /= pivot;
            }
            for (int i = 0; i < k; i++) {
                uint8192_t factor = aug[i][k];
                for (size_t j = k; j < 2 * n; j++) {
                    aug[i][j] -= factor * aug[k][j];
                }
            }
        }
        // Extract inverse
        Matrix inv(n, Vector(n));
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                inv[i][j] = aug[i][n + j];
            }
        }
        return inv;
    }

    ### Eigenvalue Computation (Power Iteration for Dominant Eigenvalue)
    std::pair<uint8192_t, Vector> power_iteration(const Matrix& mat, size_t max_iter = 1000, double tol = 1e-10) {
        size_t n = mat.size();
        if (n != mat[0].size()) {
            throw std::invalid_argument("Matrix must be square for eigenvalue computation");
        }
        Vector vec(n, 1); // Initial guess
        for (size_t iter = 0; iter < max_iter; iter++) {
            Vector new_vec = matrix_vector_multiply(mat, vec);
            double norm = vector_norm(new_vec);
            if (norm == 0) break;
            for (auto& elem : new_vec) elem /= norm;
            if (iter > 0 && vector_norm(subtract_vectors(vec, new_vec)) < tol) {
                break;
            }
            vec = new_vec;
        }
        uint8192_t eigenvalue = dot_product(vec, matrix_vector_multiply(mat, vec)) / dot_product(vec, vec);
        return {eigenvalue, vec};
    }

    ### QR Decomposition (Gram-Schmidt Process)
    std::pair<Matrix, Matrix> qr_decomposition(const Matrix& mat) {
        size_t rows = mat.size();
        size_t cols = mat[0].size();
        if (rows < cols) {
            throw std::invalid_argument("Matrix must have at least as many rows as columns for QR decomposition");
        }
        Matrix Q(rows, Vector(cols));
        Matrix R(cols, Vector(cols, 0));
        for (size_t j = 0; j < cols; j++) {
            Vector v(mat.size());
            for (size_t i = 0; i < rows; i++) {
                v[i] = mat[i][j];
            }
            for (size_t k = 0; k < j; k++) {
                Vector q_k(rows);
                for (size_t i = 0; i < rows; i++) {
                    q_k[i] = Q[i][k];
                }
                R[k][j] = dot_product(q_k, v);
                for (size_t i = 0; i < rows; i++) {
                    v[i] -= R[k][j] * q_k[i];
                }
            }
            double norm_v = vector_norm(v);
            if (norm_v == 0) {
                throw std::runtime_error("Matrix does not have full column rank");
            }
            for (size_t i = 0; i < rows; i++) {
                Q[i][j] = v[i] / norm_v;
            }
            R[j][j] = norm_v;
        }
        return {Q, R};
    }

    ### SVD Implementation (Outline)
    void svd(const Matrix& mat, Matrix& U, Vector& S, Matrix& V) {
        // Placeholder for SVD implementation
        // Steps: Compute A^T A and AA^T, find eigenvalues/eigenvectors, construct U, S, V
        // For production use, consider using a library like LAPACK
        throw std::runtime_error("SVD not fully implemented");
    }

    // Utility functions
    Vector subtract_vectors(const Vector& a, const Vector& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        Vector result(a.size());
        for (size_t i = 0; i < a.size(); i++) {
            result[i] = a[i] - b[i];
        }
        return result;
    }
};

// Utility function to print vectors
void print_vector(const Vector& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << static_cast<int64_t>(vec[i]);
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

// Utility function to print matrices
void print_matrix(const Matrix& mat) {
    for (const auto& row : mat) {
        print_vector(row);
    }
}

// Example usage
int main() {
    vector_calculus calc;

    // Example: Matrix-Matrix Multiplication
    Matrix mat1 = {{1, 2}, {3, 4}};
    Matrix mat2 = {{5, 6}, {7, 8}};
    Matrix mat_mult = calc.matrix_multiply(mat1, mat2);
    std::cout << "Matrix Multiplication Result:\n";
    print_matrix(mat_mult);

    // Example: Determinant
    Matrix mat3 = {{1, 2}, {3, 4}};
    std::cout << "Determinant: " << static_cast<int64_t>(calc.determinant(mat3)) << "\n";

    // Example: Matrix Inverse
    try {
        Matrix inv = calc.matrix_inverse(mat3);
        std::cout << "Matrix Inverse:\n";
        print_matrix(inv);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    // Example: Eigenvalue (Dominant)
    auto [eigenval, eigenvec] = calc.power_iteration(mat3);
    std::cout << "Dominant Eigenvalue: " << static_cast<int64_t>(eigenval) << "\nEigenvector:\n";
    print_vector(eigenvec);

    // Example: QR Decomposition
    Matrix mat4 = {{1, 2}, {3, 4}};
    auto [Q, R] = calc.qr_decomposition(mat4);
    std::cout << "Q Matrix:\n";
    print_matrix(Q);
    std::cout << "R Matrix:\n";
    print_matrix(R);

    return 0;
}
