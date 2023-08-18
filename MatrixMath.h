#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <assert.h>
#include <cmath>

Vector3 VectorAdd(const Vector3& translation, const Vector3& move);

Matrix4x4 MakeRotateXmatrix(float radian);

Matrix4x4 MakeRotateYmatrix(float radian);

Matrix4x4 MakeRotateZmatrix(float radian);

Matrix4x4 MakeTranslateMatrix(Vector3 translate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);