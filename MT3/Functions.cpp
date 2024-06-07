#include "Functions.h"

float DotProduct(
	float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY,
	float BendX, float BendY) {
	float VectorAX = AendX - AstartX;
	float VectorAY = AendY - AstartY;
	float VectorBX = BendX - BstartX;
	float VectorBY = BendY - BstartY;
	return VectorAX * VectorBX + VectorAY * VectorBY;
}

float CrossProduct(
	float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY,
	float BendX, float BendY) {
	float VectorAX = AendX - AstartX;
	float VectorAY = AendY - AstartY;
	float VectorBX = BendX - BstartX;
	float VectorBY = BendY - BstartY;
	return VectorAX * VectorBY - VectorAY * VectorBX;
}

float MAX(float x, float y) {
	if (x > y) {
		return x;
	}
	if (y > x) {
		return y;
	}
	return 0;
}

float pNorm(float x, float y, float p) {
	if (p > 255) {
		x = fabsf((float)x);
		y = fabsf((float)y);
		float norm2 = MAX(x, y);
		return norm2;
	}
	float norm = 0;
	x = sqrtf(x * x);
	y = sqrtf(y * y);
	x = powf(x, p);
	y = powf(y, p);
	norm = x + y;
	norm = powf(norm, 1.0f / p);
	return norm;
}

float GetRadianThree(
	float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY,
	float BendX, float BendY) {
	float Dot = DotProduct(AstartX, AstartY, AendX, AendY, BstartX, BstartY, BendX, BendY);
	float VectorAX = AendX - AstartX;
	float VectorAY = AendY - AstartY;
	float Dis1 = pNorm(VectorAX, VectorAY, 2);
	float VectorBX = BendX - BstartX;
	float VectorBY = BendY - BstartY;
	float Dis2 = pNorm(VectorBX, VectorBY, 2);
	float costheta = Dot / (Dis1 * Dis2);
	float radian = acosf(costheta);
	return radian;
}

float GetDegree(float radian) {
	float degree = radian * 180.0f / (float)M_PI;
	return degree;
}

float GetDis(Vector2Array pos1, Vector2Array pos2) {
	float DisX = pos2.vector2[0] - pos1.vector2[0];
	float DisY = pos2.vector2[1] - pos1.vector2[1];
	return sqrtf(DisX * DisX + DisY * DisY);
}

float GetDis(Vector2Float pos1, Vector2Float pos2) {
	float DisX = pos2.x - pos1.x;
	float DisY = pos2.y - pos1.y;
	return sqrtf(DisX * DisX + DisY * DisY);
}

float Normalize(float startX, float startY, float endX, float endY, int n) {
	float VectorX = endX - startX;
	float VectorY = endY - startY;
	float length = GetDis(Vector2Array{ startX, startY }, Vector2Array{ endX, endY });
	float normalizedX = 0;
	float normalizedY = 0;
	if (length != 0.0f) {
		normalizedX = VectorX / length;
		normalizedY = VectorY / length;
	}
	if (n == 1) {
		return normalizedX;
	}
	if (n == 2) {
		return normalizedY;
	}
	return 0;
}

Vector2Array NewNormalize(Vector2Array start, Vector2Array end) {
	Vector2Array result;
	float VectorX = end.vector2[0] - start.vector2[0];
	float VectorY = end.vector2[1] - start.vector2[1];
	float length = GetDis(start, end);
	float normalizedX = 0;
	float normalizedY = 0;
	if (length != 0.0f) {
		normalizedX = VectorX / length;
		normalizedY = VectorY / length;
	}
	result = { normalizedX,normalizedY };
	return result;
}

void Clamp(float& n, float min, float max) {
	if (n > max) {
		n = max;
	}
	if (n < min) {
		n = min;
	}
}

float isBoxCollisionBeta(
	float leftTopX1, float leftTopY1, float rightBottomX1, float rightBottomY1, float leftTopX2,
	float leftTopY2, float rightBottomX2, float rightBottomY2) {
	if (leftTopX2 < rightBottomX1 && leftTopX1 < rightBottomX2) {
		if (rightBottomY2 > leftTopY1 && rightBottomY1 > leftTopY2) {
			return 1;
		}
	}
	return 0;
}

float isCircleCollision(float posX1, float posY1, float posX2, float posY2, int radius1, int radius2) {
	float Dis = GetDis(Vector2Array{ posX1, posY1 }, Vector2Array{ posX2, posY2 });
	if (Dis < radius1 + radius2) {
		return 1;
	}
	return 0;
}

bool NewCircleCollision(Vector2Array pos1, Vector2Array pos2, int radius1, int radius2) {
	float Dis = GetDis(pos1, pos2);
	if (Dis < radius1 + radius2) {
		return true;
	}
	return false;
}

float CC(float posY) {
	float worldY = 500;
	return -posY + worldY;
}

float LeftTopX(float posX, float width) { return posX - width / 2; }

float LeftTopY(float posY, float height) { return posY - height / 2; }

float RightBottomX(float posX, float width) { return posX + width / 2; }

float RightBottomY(float posY, float height) { return posY + height / 2; }

float RightTopX(float posX, float width) { return posX + width / 2; }

float RightTopY(float posY, float height) { return posY - height / 2; }

float LeftBottomX(float posX, float width) { return posX - width / 2; }

float LeftBottomY(float posY, float height) { return posY + height / 2; }

float CenterC(float leftTopX, float leftTopY, float width, float height, int n) {
	float centerX = 0;
	float centerY = 0;
	centerX = leftTopX + width / 2;
	centerY = leftTopY + height / 2;
	if (n == 1) {
		return centerX;
	}
	if (n == 2) {
		return centerY;
	}
	else {
		return 0;
	}
}

float isBoxCollision(
	float posX1, float posY1, float posX2, float posY2, float width, float height, float width2,
	float height2) {
	float leftTopX1 = LeftTopX(posX1, width);
	float leftTopY1 = LeftTopY(posY1, height);
	float leftTopX2 = LeftTopX(posX2, width2);
	float leftTopY2 = LeftTopY(posY2, height2);
	float rightBottomX1 = RightBottomX(posX1, width);
	float rightBottomY1 = RightBottomY(posY1, height);
	float rightBottomX2 = RightBottomX(posX2, width2);
	float rightBottomY2 = RightBottomY(posY2, height2);
	if (leftTopX2 < rightBottomX1 && leftTopX1 < rightBottomX2) {
		if (rightBottomY2 > leftTopY1 && rightBottomY1 > leftTopY2) {
			return 1;
		}
	}
	return 0;
}

float IsOutOfScreen(float posX, float posYn, int ScreenSizeX, int ScreenSizeY) {
	if (posX < 0 || posX > ScreenSizeX || posYn < 0 || posYn > ScreenSizeY) {
		return 1;
	}
	else {
		return 0;
	}
}

float BoxPointCollision(
	float BoxLtX, float BoxLtY, float BoxRbX, float BoxRbY, int pointX, int pointY) {
	if (BoxLtX < pointX && BoxRbX > pointX) {
		if (BoxLtY < pointY && BoxRbY > pointY) {
			return 1;
		}
	}
	return 0;
}

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			result.matrix[row][column] = matrix1.matrix[row][column] + matrix2.matrix[row][column];
		}
	}
	return result;
}
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			result.matrix[row][column] = matrix1.matrix[row][column] - matrix2.matrix[row][column];
		}
	}
	return result;
}
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	result.matrix[0][0] =
		matrix1.matrix[0][0] * matrix2.matrix[0][0] + matrix1.matrix[0][1] * matrix2.matrix[1][0];
	result.matrix[0][1] =
		matrix1.matrix[0][0] * matrix2.matrix[0][1] + matrix1.matrix[0][1] * matrix2.matrix[1][1];
	result.matrix[1][0] =
		matrix1.matrix[1][0] * matrix2.matrix[0][0] + matrix1.matrix[1][1] * matrix2.matrix[1][0];
	result.matrix[1][1] =
		matrix1.matrix[1][0] * matrix2.matrix[0][1] + matrix1.matrix[1][1] * matrix2.matrix[1][1];
	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result{};
	for (int rows = 0; rows < 3; rows++) {
		for (int cols = 0; cols < 3; cols++) {
			for (int a = 0; a < 3; a++) {
				result.matrix[rows][cols] += matrix1.matrix[rows][a] * matrix2.matrix[a][cols];
			}
		}
	}
	return result;
}

Vector2Array MultiplyV(Matrix2x2 matrix1, Vector2Array vector2) {
	Vector2Array result;
	result.vector2[0] =
		matrix1.matrix[0][0] * vector2.vector2[0] + matrix1.matrix[1][0] * vector2.vector2[1];
	result.vector2[1] =
		matrix1.matrix[0][1] * vector2.vector2[0] + matrix1.matrix[1][1] * vector2.vector2[1];
	return result;
}

Vector2Array Transform(Vector2Array vector, Matrix3x3 matrix) {
	Vector2Array result;
	result.vector2[0] = vector.vector2[0] * matrix.matrix[0][0] +
		vector.vector2[1] * matrix.matrix[1][0] + 1.0f * matrix.matrix[2][0];
	result.vector2[1] = vector.vector2[0] * matrix.matrix[0][1] +
		vector.vector2[1] * matrix.matrix[1][1] + 1.0f * matrix.matrix[2][1];
	float w = vector.vector2[0] * matrix.matrix[0][2] + vector.vector2[1] * matrix.matrix[1][2] +
		1.0f * matrix.matrix[2][2];
	assert(w != 0.0f);
	result.vector2[0] /= w;
	result.vector2[1] /= w;
	return result;
}

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * 2, y + row * 2, "%.02f", matrix.matrix[row][column]);
		}
	}
}

void Vector2ScreenPrintf(int x, int y, Vector2Array vector2) {
	Novice::ScreenPrintf(x, y, "%.02f", vector2.vector2[0]);
	Novice::ScreenPrintf(x + 50, y, "%.02f", vector2.vector2[1]);
}

Matrix3x3 MakeScaleMatrix(Vector2Array scale) {
	Matrix3x3 result{};
	result.matrix[0][0] = scale.vector2[0];
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = scale.vector2[1];
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeTranslateMatrix(Vector2Array translate) {
	Matrix3x3 result{};
	result.matrix[0][0] = 1.0f;
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = 1.0f;
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = translate.vector2[0];
	result.matrix[2][1] = translate.vector2[1];
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result{};
	result.matrix[0][0] = cosf(theta);
	result.matrix[0][1] = sinf(theta);
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = -sinf(theta);
	result.matrix[1][1] = cosf(theta);
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2Array scale, float theta, Vector2Array translate) {
	Matrix3x3 result{};
	result.matrix[0][0] = scale.vector2[0] * cosf(theta);
	result.matrix[0][1] = scale.vector2[0] * sinf(theta);
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = -scale.vector2[1] * sinf(theta);
	result.matrix[1][1] = scale.vector2[0] * cosf(theta);
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = translate.vector2[0];
	result.matrix[2][1] = translate.vector2[1];
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 RenderingPipeline(Matrix3x3 worldMatrix, Matrix3x3 viewMatrix, Matrix3x3 orthographicMatrix, Matrix3x3 viewportMatrix) {
	Matrix3x3 wvpVpMatrix{};
	wvpVpMatrix = Multiply(worldMatrix, viewMatrix);
	wvpVpMatrix = Multiply(wvpVpMatrix, orthographicMatrix);
	wvpVpMatrix = Multiply(wvpVpMatrix, viewportMatrix);
	return wvpVpMatrix;
}

void VDrawQuad(Vector2Array lt, Vector2Array rt, Vector2Array lb, Vector2Array rb, int textureWidth, int textureHeight, int Tex, unsigned int color) {
	Novice::DrawQuad(
		int(lt.vector2[0]), int(lt.vector2[1]), int(rt.vector2[0]), int(rt.vector2[1]),
		int(lb.vector2[0]), int(lb.vector2[1]), int(rb.vector2[0]), int(rb.vector2[1]), 0, 0, textureWidth,
		textureHeight, Tex, color);
}


Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result{};
	result.matrix[0][0] = 2.0f / (right - left);
	result.matrix[0][1] = 0;
	result.matrix[0][2] = 0;
	result.matrix[1][0] = 0;
	result.matrix[1][1] = 2.0f / (top - bottom);
	result.matrix[1][2] = 0;
	result.matrix[2][0] = (left + right) / (left - right);
	result.matrix[2][1] = (top + bottom) / (bottom - top);
	result.matrix[2][2] = 1;
	return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 result{};
	result.matrix[0][0] = width / 2;
	result.matrix[0][1] = 0;
	result.matrix[0][2] = 0;
	result.matrix[1][0] = 0;
	result.matrix[1][1] = -(height / 2);
	result.matrix[1][2] = 0;
	result.matrix[2][0] = left + width / 2;
	result.matrix[2][1] = top + height / 2;
	result.matrix[2][2] = 1;
	return result;
}


Matrix3x3 inverse(Matrix3x3 matrix) {
	Matrix3x3 result{};
	static float a = 1 / (matrix.matrix[0][0] * matrix.matrix[1][1] * matrix.matrix[2][2] + matrix.matrix[0][1] * matrix.matrix[1][2] * matrix.matrix[2][0] +
		matrix.matrix[0][2] * matrix.matrix[1][0] * matrix.matrix[2][1] - matrix.matrix[0][2] * matrix.matrix[1][1] * matrix.matrix[2][1] -
		matrix.matrix[0][1] * matrix.matrix[1][0] * matrix.matrix[2][2] - matrix.matrix[0][0] * matrix.matrix[1][2] * matrix.matrix[2][1]);
	result.matrix[0][0] = a * (matrix.matrix[1][1] * matrix.matrix[2][2] - matrix.matrix[1][2] * matrix.matrix[2][1]);
	result.matrix[0][1] = a * -(matrix.matrix[0][1] * matrix.matrix[2][2] - matrix.matrix[1][2] * matrix.matrix[2][1]);
	result.matrix[0][2] = a * (matrix.matrix[0][1] * matrix.matrix[1][2] - matrix.matrix[0][2] * matrix.matrix[1][1]);

	result.matrix[1][0] = a * -(matrix.matrix[1][0] * matrix.matrix[2][2] - matrix.matrix[1][2] * matrix.matrix[2][1]);
	result.matrix[1][1] = a * (matrix.matrix[0][0] * matrix.matrix[2][2] - matrix.matrix[1][2] * matrix.matrix[2][1]);
	result.matrix[1][2] = a * -(matrix.matrix[0][0] * matrix.matrix[1][2] - matrix.matrix[0][2] * matrix.matrix[1][0]);

	result.matrix[2][0] = a * (matrix.matrix[1][0] * matrix.matrix[2][1] - matrix.matrix[1][1] * matrix.matrix[2][0]);
	result.matrix[2][1] = a * -(matrix.matrix[0][0] * matrix.matrix[2][1] - matrix.matrix[0][1] * matrix.matrix[2][0]);
	result.matrix[2][2] = a * (matrix.matrix[0][0] * matrix.matrix[1][1] - matrix.matrix[0][1] * matrix.matrix[1][0]);
	return result;
}

void Easing(Vector2Array& pos, Vector2Array start, Vector2Array end, float t) {
	pos.vector2[0] = (1.0f - t) * start.vector2[0] + t * end.vector2[0];
	pos.vector2[1] = (1.0f - t) * start.vector2[1] + t * end.vector2[1];
}

Vector2Array RotateDirection(Vector2Array direction, float theta) {
	Vector2Array result;
	result.vector2[0] = direction.vector2[0] * cosf(theta) - direction.vector2[1] * sinf(theta);
	result.vector2[1] = direction.vector2[0] * sinf(theta) + direction.vector2[1] * cosf(theta);
	return result;
}

int LinearInterpolation(int start, int end, float t) {
	int result{};
	result = int((1.0f - t) * start + t * end);
	return result;
}


float GetRadian(float degree) {
	return degree * (float(M_PI) / 180);
}

Vector3Array Project(const Vector3Array& v1, const Vector3Array& v2)
{
	Vector3Array result{};
	Vector3Array v2UnitVector = Normalize(v2);
	result = Multiply(Dot(v1, v2UnitVector), v2UnitVector);
	return result;
}

Vector3Array ClosestPoint(const Vector3Array& point, const Segment& segment)
{
	float t = Dot(Subtract(point, segment.origin), Subtract(segment.diff, segment.origin)) / powf(Length(Subtract(segment.diff, segment.origin)), 2);
	Clamp(t, 0, Length(segment.diff));
	Vector3Array result = Add(segment.origin, Multiply(t, Subtract(segment.diff, segment.origin)));
	return result;
}

Vector3Float Add(const Vector3Float& v1, const Vector3Float& v2) {
	Vector3Float result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3Float Subtract(const Vector3Float& v1, const Vector3Float& v2) {
	Vector3Float result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3Float Multiply(float scalar, const Vector3Float& v) {
	Vector3Float result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

Vector3Array Add(const Vector3Array& v1, const Vector3Array& v2) {
	Vector3Array result{};
	result.v[0] = v1.v[0] + v2.v[0];
	result.v[1] = v1.v[1] + v2.v[1];
	result.v[2] = v1.v[2] + v2.v[2];
	return result;
}

Vector3Array Subtract(const Vector3Array& v1, const Vector3Array& v2) {
	Vector3Array result{};
	result.v[0] = v1.v[0] - v2.v[0];
	result.v[1] = v1.v[1] - v2.v[1];
	result.v[2] = v1.v[2] - v2.v[2];
	return result;
}

Vector3Array Multiply(float scalar, const Vector3Array& v) {
	Vector3Array result{};
	result.v[0] = scalar * v.v[0];
	result.v[1] = scalar * v.v[1];
	result.v[2] = scalar * v.v[2];
	return result;
}

float Dot(const Vector3Float& v1, const Vector3Float& v2) {
	float result{};
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

float Dot(const Vector3Array& v1, const Vector3Array& v2) {
	float result{};
	result = v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
	return result;
}

float Length(const Vector3Float& v) {
	float result{};
	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}

float Length(const Vector3Array& v) {
	float result{};
	result = sqrtf((v.v[0] * v.v[0]) + (v.v[1] * v.v[1]) + (v.v[2] * v.v[2]));
	return result;
}

Vector3Float Normalize(const Vector3Float& v) {
	Vector3Float result{};
	float length = Length(v);
	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}

Vector3Array Normalize(const Vector3Array& v) {
	Vector3Array result{};
	float length = Length(v);
	if (length != 0) {
		result.v[0] = v.v[0] / length;
		result.v[1] = v.v[1] / length;
		result.v[2] = v.v[2] / length;
	}
	return result;
}

bool isCollision(const Sphere& s1, const Sphere& s2)
{
	float length = Length(Subtract(s1.center, s2.center));
	if (length <= s1.radius + s2.radius) {
		return true;
	}
	else {
		return false;
	}
}

bool isCollision(const Sphere& sphere, const Plane& plane)
{
	Vector3Array perpendicular = Normalize(Perpendicular(plane.normal));
	float dis = fabsf(Dot(plane.normal, sphere.center) - plane.distance);
	if (dis < sphere.radius) {
		return true;
	}
	return false;
}

bool isCollision(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	//Novice::ScreenPrintf(0, 0, "%f", t);
	if (t >= 1.0f || t <= 0.0f) {
		return false;
	}
	return true;
}

bool isCollision(const Triangle& triangle, const Segment& segment)
{
	Vector3Array v01 = Subtract(triangle.worldPos[1], triangle.worldPos[0]);
	Vector3Array v12 = Subtract(triangle.worldPos[2], triangle.worldPos[1]);
	Vector3Array n = Normalize(Cross(v01, v12));
	//float t = (Dot(triangle.worldPos[0], n) - Dot(segment.origin, n)) / dot;
	float t = Dot(triangle.worldPos[0], n) - Dot(segment.origin, n) / Dot(segment.diff, n);
	Novice::ScreenPrintf(0, 0, "%f", t);
	Vector3Array p = Add(segment.origin, Multiply(t, segment.diff));

	Vector3Array v20 = Subtract(triangle.worldPos[0], triangle.worldPos[2]);
	Vector3Array v0p = Subtract(p, triangle.worldPos[0]);
	Vector3Array v1p = Subtract(p, triangle.worldPos[1]);
	Vector3Array v2p = Subtract(p, triangle.worldPos[2]);

	Vector3Array cross01 = Cross(v01, v1p);
	Vector3Array cross12 = Cross(v12, v2p);
	Vector3Array cross20 = Cross(v20, v0p);

	if (Dot(cross01, n) >= 0.0f &&
		Dot(cross12, n) >= 0.0f &&
		Dot(cross20, n) >= 0.0f) {
		return true;
	}

	return false;
}

bool isCollision(const AABB& a, const AABB& b)
{
	if ((a.min.v[0] <= b.max.v[0] && a.max.v[0] >= b.min.v[0]) &&
		(a.min.v[1] <= b.max.v[1] && a.max.v[1] >= b.min.v[1]) &&
		(a.min.v[2] <= b.max.v[2] && a.max.v[2] >= b.min.v[2]))
	{
		return true;
	}
	return false;
}

bool isCollision(const AABB& aabb, const Sphere& sphere)
{
	Vector3Array closestPoint{ std::clamp(sphere.center.v[0],aabb.min.v[0],aabb.max.v[0]),
	std::clamp(sphere.center.v[1],aabb.min.v[1],aabb.max.v[1]),
	std::clamp(sphere.center.v[2],aabb.min.v[2],aabb.max.v[2]) };
	float distance = Length(Subtract(closestPoint, sphere.center));
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

bool isCollision(const AABB& aabb, const Segment& segment)
{
	float txMin = (aabb.min.v[0] - segment.origin.v[0]) / segment.diff.v[0];
	float txMax = (aabb.max.v[0] - segment.origin.v[0]) / segment.diff.v[0];
	float tyMin = (aabb.min.v[1] - segment.origin.v[1]) / segment.diff.v[1];
	float tyMax = (aabb.max.v[1] - segment.origin.v[1]) / segment.diff.v[1];
	float tzMin = (aabb.min.v[2] - segment.origin.v[2]) / segment.diff.v[2];
	float tzMax = (aabb.max.v[2] - segment.origin.v[2]) / segment.diff.v[2];

	float tNearX = min(txMin, txMax);
	float tNearY = min(tyMin, tyMax);
	float tNearZ = min(tzMin, tzMax);
	float tFarX = max(txMin, txMax);
	float tFarY = max(tyMin, tyMax);
	float tFarZ = max(tzMin, tzMax);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);
	if (tmin <= tmax) {
		if ((segment.origin.v[0] < tNearX && segment.origin.v[0] + segment.diff.v[0] < tNearX) &&
			(segment.origin.v[1] < tNearY && segment.origin.v[1] + segment.diff.v[1] < tNearY) &&
			(segment.origin.v[2] < tNearZ && segment.origin.v[2] + segment.diff.v[2] < tNearZ))
		{
			return false;
		}

		if ((segment.origin.v[0] > tFarX && segment.origin.v[0] + segment.diff.v[0] > tFarX) &&
			(segment.origin.v[1] > tFarY && segment.origin.v[1] + segment.diff.v[1] > tFarY) &&
			(segment.origin.v[2] > tFarZ && segment.origin.v[2] + segment.diff.v[2] > tFarZ))
		{
			return false;
		}

		return true;
	}
	return false;
}

bool isCollision(const OBB& obb, const Sphere& sphere)
{
	Matrix4x4 worldMatrix = {
		obb.orientations[0].v[0],obb.orientations[0].v[1],obb.orientations[0].v[2],0,
		obb.orientations[1].v[0],obb.orientations[1].v[1],obb.orientations[1].v[2],0,
		obb.orientations[2].v[0],obb.orientations[2].v[1],obb.orientations[2].v[2],0,
		obb.center.v[0],obb.center.v[1],obb.center.v[2],1
	};

	Matrix4x4 obbWorldMatrixInverce = inverse(worldMatrix);

	Vector3Array centerInOBBLocalSpace = Transform(sphere.center, obbWorldMatrixInverce);

	AABB aabbOBBLocal{ .min = { -obb.size.v[0],-obb.size.v[1],-obb.size.v[2]},.max = obb.size };
	Sphere sphereOBBLocal{ centerInOBBLocalSpace,sphere.radius };
	if (isCollision(aabbOBBLocal, sphereOBBLocal)) {
		return true;
	}
	return false;
}

bool isCollision(const OBB& obb, const Segment& segment)
{
	Matrix4x4 worldMatrix = {
		   obb.orientations[0].v[0],obb.orientations[0].v[1],obb.orientations[0].v[2],0,
		   obb.orientations[1].v[0],obb.orientations[1].v[1],obb.orientations[1].v[2],0,
		   obb.orientations[2].v[0],obb.orientations[2].v[1],obb.orientations[2].v[2],0,
		   obb.center.v[0],obb.center.v[1],obb.center.v[2],1
	};

	Matrix4x4 obbWorldMatrixInverce = inverse(worldMatrix);
	Vector3Array loaclOrigin = Transform(segment.origin, obbWorldMatrixInverce);
	Vector3Array localEnd = Transform(Add(segment.origin, segment.diff), obbWorldMatrixInverce);

	AABB localAABB{
		{-obb.size.v[0],-obb.size.v[1],-obb.size.v[2]},
		{obb.size.v[0],obb.size.v[1],obb.size.v[2]},
	};

	Segment localLine;
	localLine.origin = loaclOrigin;
	localLine.diff = Subtract(localEnd, loaclOrigin);
	return isCollision(localAABB, localLine);
}

Vector3Array Perpendicular(const Vector3Array& vector)
{
	if (vector.v[0] != 0.0f || vector.v[1] != 0.0f) {
		return { -vector.v[1],vector.v[0],0.0f };
	}
	return { 0.0f,-vector.v[2],vector.v[1] };
}

void DrawPlane(const Plane& plane, const Camera3dData& camera, uint32_t color)
{
	Vector3Array center = Multiply(plane.distance, plane.normal);
	Vector3Array perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].v[0], -perpendiculars[0].v[1], -perpendiculars[0].v[2] };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].v[0], -perpendiculars[2].v[1], -perpendiculars[2].v[2] };

	Vector3Array points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3Array extend = Multiply(2.0f, perpendiculars[index]);
		Vector3Array point = Add(center, extend);
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, point);
		points[index] = RenderingPipeline({ 0,0,0 }, worldMatrix, camera);
	}
	for (int i = 0; i < 4; i++) {
		Novice::DrawLine(int(points[0].v[0]), int(points[0].v[1]), int(points[2].v[0]), int(points[2].v[1]), color);
		Novice::DrawLine(int(points[1].v[0]), int(points[1].v[1]), int(points[2].v[0]), int(points[2].v[1]), color);
		Novice::DrawLine(int(points[1].v[0]), int(points[1].v[1]), int(points[3].v[0]), int(points[3].v[1]), color);
		Novice::DrawLine(int(points[3].v[0]), int(points[3].v[1]), int(points[0].v[0]), int(points[0].v[1]), color);
		Novice::ScreenPrintf(int(points[i].v[0]), int(points[i].v[1]), "%d", i);
	}
}

Vector3Array Cross(const Vector3Array& v1, const Vector3Array& v2) {
	Vector3Array result;
	result.v[0] = v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1];
	result.v[1] = v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2];
	result.v[2] = v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0];
	return result;
}

Vector3Float Cross(const Vector3Float& v1, const Vector3Float& v2) {
	Vector3Float result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

void VectorScreenPrintf(int x, int y, const Vector3Float& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void VectorScreenPrintf(int x, int y, const Vector3Array& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.v[0]);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.v[1]);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.v[2]);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4 matrix, const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth + 20, y + row * kRowHeight + 20, "%6.02f", matrix.matrix[row][column]);
		}
	}
	Novice::ScreenPrintf(x, y, label);
}
