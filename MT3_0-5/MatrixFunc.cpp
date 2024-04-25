#include "MatrixFunc.h"

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
		}
	}
	return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
		}
	}
	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
			}
		}
	}

	return result;
}

Matrix4x4 inverse(const Matrix4x4& matrix) {
	Matrix4x4 result{};

	float det = matrix.matrix[0][0] * (matrix.matrix[1][1] * (matrix.matrix[2][2] * matrix.matrix[3][3] - matrix.matrix[2][3] * matrix.matrix[3][2]) -
		matrix.matrix[1][2] * (matrix.matrix[2][1] * matrix.matrix[3][3] - matrix.matrix[2][3] * matrix.matrix[3][1]) +
		matrix.matrix[1][3] * (matrix.matrix[2][1] * matrix.matrix[3][2] - matrix.matrix[2][2] * matrix.matrix[3][1]));

	det -= matrix.matrix[0][1] * (matrix.matrix[1][0] * (matrix.matrix[2][2] * matrix.matrix[3][3] - matrix.matrix[2][3] * matrix.matrix[3][2]) -
		matrix.matrix[1][2] * (matrix.matrix[2][0] * matrix.matrix[3][3] - matrix.matrix[2][3] * matrix.matrix[3][0]) +
		matrix.matrix[1][3] * (matrix.matrix[2][0] * matrix.matrix[3][2] - matrix.matrix[2][2] * matrix.matrix[3][0]));

	det += matrix.matrix[0][2] * (matrix.matrix[1][0] * (matrix.matrix[2][1] * matrix.matrix[3][3] - matrix.matrix[2][3] * matrix.matrix[3][1]) -
		matrix.matrix[1][1] * (matrix.matrix[2][0] * matrix.matrix[3][3] - matrix.matrix[2][3] * matrix.matrix[3][0]) +
		matrix.matrix[1][3] * (matrix.matrix[2][0] * matrix.matrix[3][1] - matrix.matrix[2][1] * matrix.matrix[3][0]));

	det -= matrix.matrix[0][3] * (matrix.matrix[1][0] * (matrix.matrix[2][1] * matrix.matrix[3][2] - matrix.matrix[2][2] * matrix.matrix[3][1]) -
		matrix.matrix[1][1] * (matrix.matrix[2][0] * matrix.matrix[3][2] - matrix.matrix[2][2] * matrix.matrix[3][0]) +
		matrix.matrix[1][2] * (matrix.matrix[2][0] * matrix.matrix[3][1] - matrix.matrix[2][1] * matrix.matrix[3][0]));

	result.matrix[0][0] = (matrix.matrix[1][1] * matrix.matrix[2][2] * matrix.matrix[3][3] - matrix.matrix[1][1] * matrix.matrix[2][3] * matrix.matrix[3][2] -
		matrix.matrix[1][2] * matrix.matrix[2][1] * matrix.matrix[3][3] + matrix.matrix[1][2] * matrix.matrix[2][3] * matrix.matrix[3][1] +
		matrix.matrix[1][3] * matrix.matrix[2][1] * matrix.matrix[3][2] - matrix.matrix[1][3] * matrix.matrix[2][2] * matrix.matrix[3][1]) /
		det;

	result.matrix[0][1] = (-matrix.matrix[0][1] * matrix.matrix[2][2] * matrix.matrix[3][3] + matrix.matrix[0][1] * matrix.matrix[2][3] * matrix.matrix[3][2] +
		matrix.matrix[0][2] * matrix.matrix[2][1] * matrix.matrix[3][3] - matrix.matrix[0][2] * matrix.matrix[2][3] * matrix.matrix[3][1] -
		matrix.matrix[0][3] * matrix.matrix[2][1] * matrix.matrix[3][2] + matrix.matrix[0][3] * matrix.matrix[2][2] * matrix.matrix[3][1]) /
		det;

	result.matrix[0][2] = (matrix.matrix[0][1] * matrix.matrix[1][2] * matrix.matrix[3][3] - matrix.matrix[0][1] * matrix.matrix[1][3] * matrix.matrix[3][2] -
		matrix.matrix[0][2] * matrix.matrix[1][1] * matrix.matrix[3][3] + matrix.matrix[0][2] * matrix.matrix[1][3] * matrix.matrix[3][1] +
		matrix.matrix[0][3] * matrix.matrix[1][1] * matrix.matrix[3][2] - matrix.matrix[0][3] * matrix.matrix[1][2] * matrix.matrix[3][1]) /
		det;

	result.matrix[0][3] = (-matrix.matrix[0][1] * matrix.matrix[1][2] * matrix.matrix[2][3] + matrix.matrix[0][1] * matrix.matrix[1][3] * matrix.matrix[2][2] +
		matrix.matrix[0][2] * matrix.matrix[1][1] * matrix.matrix[2][3] - matrix.matrix[0][2] * matrix.matrix[1][3] * matrix.matrix[2][1] -
		matrix.matrix[0][3] * matrix.matrix[1][1] * matrix.matrix[2][2] + matrix.matrix[0][3] * matrix.matrix[1][2] * matrix.matrix[2][1]) /
		det;

	result.matrix[1][0] = (-matrix.matrix[0][0] * matrix.matrix[2][2] * matrix.matrix[3][3] + matrix.matrix[0][0] * matrix.matrix[2][3] * matrix.matrix[3][2] +
		matrix.matrix[0][2] * matrix.matrix[2][0] * matrix.matrix[3][3] - matrix.matrix[0][2] * matrix.matrix[2][3] * matrix.matrix[3][0] -
		matrix.matrix[0][3] * matrix.matrix[2][0] * matrix.matrix[3][2] + matrix.matrix[0][3] * matrix.matrix[2][2] * matrix.matrix[3][0]) /
		det;

	result.matrix[1][1] = (matrix.matrix[0][0] * matrix.matrix[1][2] * matrix.matrix[3][3] - matrix.matrix[0][0] * matrix.matrix[1][3] * matrix.matrix[3][2] -
		matrix.matrix[0][2] * matrix.matrix[1][0] * matrix.matrix[3][3] + matrix.matrix[0][2] * matrix.matrix[1][3] * matrix.matrix[3][0] +
		matrix.matrix[0][3] * matrix.matrix[1][0] * matrix.matrix[3][2] - matrix.matrix[0][3] * matrix.matrix[1][2] * matrix.matrix[3][0]) /
		det;

	result.matrix[1][2] = (-matrix.matrix[0][0] * matrix.matrix[1][1] * matrix.matrix[3][3] + matrix.matrix[0][0] * matrix.matrix[1][3] * matrix.matrix[3][1] +
		matrix.matrix[0][1] * matrix.matrix[1][0] * matrix.matrix[3][3] - matrix.matrix[0][1] * matrix.matrix[1][3] * matrix.matrix[3][0] -
		matrix.matrix[0][3] * matrix.matrix[1][0] * matrix.matrix[3][1] + matrix.matrix[0][3] * matrix.matrix[1][1] * matrix.matrix[3][0]) /
		det;

	result.matrix[1][3] = (matrix.matrix[0][0] * matrix.matrix[1][1] * matrix.matrix[2][3] - matrix.matrix[0][0] * matrix.matrix[1][3] * matrix.matrix[2][1] -
		matrix.matrix[0][1] * matrix.matrix[1][0] * matrix.matrix[2][3] + matrix.matrix[0][1] * matrix.matrix[1][3] * matrix.matrix[2][0] +
		matrix.matrix[0][3] * matrix.matrix[1][0] * matrix.matrix[2][1] - matrix.matrix[0][3] * matrix.matrix[1][1] * matrix.matrix[2][0]) /
		det;

	result.matrix[2][0] = (matrix.matrix[1][0] * matrix.matrix[2][2] * matrix.matrix[3][3] - matrix.matrix[1][0] * matrix.matrix[2][3] * matrix.matrix[3][2] -
		matrix.matrix[1][2] * matrix.matrix[2][0] * matrix.matrix[3][3] + matrix.matrix[1][2] * matrix.matrix[2][3] * matrix.matrix[3][0] +
		matrix.matrix[1][3] * matrix.matrix[2][0] * matrix.matrix[3][2] - matrix.matrix[1][3] * matrix.matrix[2][2] * matrix.matrix[3][0]) /
		det;

	result.matrix[2][1] = (-matrix.matrix[0][0] * matrix.matrix[2][2] * matrix.matrix[3][3] + matrix.matrix[0][0] * matrix.matrix[2][3] * matrix.matrix[3][2] +
		matrix.matrix[0][2] * matrix.matrix[2][0] * matrix.matrix[3][3] - matrix.matrix[0][2] * matrix.matrix[2][3] * matrix.matrix[3][0] -
		matrix.matrix[0][3] * matrix.matrix[2][0] * matrix.matrix[3][2] + matrix.matrix[0][3] * matrix.matrix[2][2] * matrix.matrix[3][0]) /
		det;

	result.matrix[2][2] = (matrix.matrix[0][0] * matrix.matrix[1][2] * matrix.matrix[3][3] - matrix.matrix[0][0] * matrix.matrix[1][3] * matrix.matrix[3][2] -
		matrix.matrix[0][2] * matrix.matrix[1][0] * matrix.matrix[3][3] + matrix.matrix[0][2] * matrix.matrix[1][3] * matrix.matrix[3][0] +
		matrix.matrix[0][3] * matrix.matrix[1][0] * matrix.matrix[3][2] - matrix.matrix[0][3] * matrix.matrix[1][2] * matrix.matrix[3][0]) /
		det;

	result.matrix[2][3] = (-matrix.matrix[0][0] * matrix.matrix[1][2] * matrix.matrix[2][3] + matrix.matrix[0][0] * matrix.matrix[1][3] * matrix.matrix[2][2] +
		matrix.matrix[0][2] * matrix.matrix[1][0] * matrix.matrix[2][3] - matrix.matrix[0][2] * matrix.matrix[1][3] * matrix.matrix[2][0] -
		matrix.matrix[0][3] * matrix.matrix[1][0] * matrix.matrix[2][2] + matrix.matrix[0][3] * matrix.matrix[1][2] * matrix.matrix[2][0]) /
		det;

	result.matrix[3][0] = (-matrix.matrix[1][0] * matrix.matrix[2][1] * matrix.matrix[3][2] + matrix.matrix[1][0] * matrix.matrix[2][2] * matrix.matrix[3][1] +
		matrix.matrix[1][1] * matrix.matrix[2][0] * matrix.matrix[3][2] - matrix.matrix[1][1] * matrix.matrix[2][2] * matrix.matrix[3][0] -
		matrix.matrix[1][2] * matrix.matrix[2][0] * matrix.matrix[3][1] + matrix.matrix[1][2] * matrix.matrix[2][1] * matrix.matrix[3][0]) /
		det;

	result.matrix[3][1] = (matrix.matrix[0][0] * matrix.matrix[2][1] * matrix.matrix[3][2] - matrix.matrix[0][0] * matrix.matrix[2][2] * matrix.matrix[3][1] -
		matrix.matrix[0][1] * matrix.matrix[2][0] * matrix.matrix[3][2] + matrix.matrix[0][1] * matrix.matrix[2][2] * matrix.matrix[3][0] +
		matrix.matrix[0][2] * matrix.matrix[2][0] * matrix.matrix[3][1] - matrix.matrix[0][2] * matrix.matrix[2][1] * matrix.matrix[3][0]) /
		det;

	result.matrix[3][2] = (-matrix.matrix[0][0] * matrix.matrix[1][1] * matrix.matrix[3][2] + matrix.matrix[0][0] * matrix.matrix[1][2] * matrix.matrix[3][1] +
		matrix.matrix[0][1] * matrix.matrix[1][0] * matrix.matrix[3][2] - matrix.matrix[0][1] * matrix.matrix[1][2] * matrix.matrix[3][0] -
		matrix.matrix[0][2] * matrix.matrix[1][0] * matrix.matrix[3][1] + matrix.matrix[0][2] * matrix.matrix[1][1] * matrix.matrix[3][0]) /
		det;

	result.matrix[3][3] = (matrix.matrix[0][0] * matrix.matrix[1][1] * matrix.matrix[2][2] - matrix.matrix[0][0] * matrix.matrix[1][2] * matrix.matrix[2][1] -
		matrix.matrix[0][1] * matrix.matrix[1][0] * matrix.matrix[2][2] + matrix.matrix[0][1] * matrix.matrix[1][2] * matrix.matrix[2][0] +
		matrix.matrix[0][2] * matrix.matrix[1][0] * matrix.matrix[2][1] - matrix.matrix[0][2] * matrix.matrix[1][1] * matrix.matrix[2][0]) /
		det;

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = m.matrix[j][i];
		}
	}

	return result;
}

Matrix4x4 MakeIdentityMatrix() {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.matrix[i][j] = 1.0f;
			}
		}
	}

	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3Array& translate) {
	Matrix4x4 result = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translate.vector3[0], translate.vector3[1], translate.vector3[2], 1.0f
	};

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3Array& scale) {
	Matrix4x4 result = {
		scale.vector3[0], 0.0f, 0.0f, 0.0f,
		0.0f, scale.vector3[1], 0.0f, 0.0f,
		0.0f, 0.0f, scale.vector3[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				1,0,0,0,
				0,std::cos(radian),std::sin(radian),0,
				0,-std::sin(radian),std::cos(radian),0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				std::cos(radian),0,-std::sin(radian),0,
				0,1,0,0,
				std::sin(radian),0,std::cos(radian),0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				std::cos(radian),std::sin(radian),0,0,
				-std::sin(radian),std::cos(radian),0,0,
				0,0,1,0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3Array& scale, const Vector3Array& rotate, const Vector3Array& translate) {
	Matrix4x4 result{};
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.vector3[0]);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.vector3[1]);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.vector3[2]);
	Matrix4x4 rotateXYZ = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 3) {
				result.matrix[i][j] = 0.0f;
			}
			else{
				result.matrix[i][j] = scale.vector3[i] * rotateXYZ.matrix[i][j];
			}
		}
	}
	for (int i = 0; i < 3; i++){
		result.matrix[3][i] = translate.vector3[i];
	}
	result.matrix[3][3] = 1.0f;

	return result;
}

Vector3Array Transform(const Vector3Array& vector, const Matrix4x4& matrix) {
	Vector3Array result{};
	for (int i = 0; i < 3; i++) {
		result.vector3[i] = vector.vector3[0] * matrix.matrix[0][i] +
			vector.vector3[1] * matrix.matrix[1][i] + vector.vector3[2] * matrix.matrix[2][i] + matrix.matrix[3][i];
	}
	float w = vector.vector3[0] * matrix.matrix[0][3] +
		vector.vector3[1] * matrix.matrix[1][3] + vector.vector3[2] * matrix.matrix[2][3] + matrix.matrix[3][3];
	assert(w != 0.0f);
	for (int i = 0; i < 3; i++) {
		result.vector3[i] /= w;
	}
	return result;
}