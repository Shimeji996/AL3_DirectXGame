#include "MatrixMath.h"
#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = Math::MakeAffineMatrix(scale_, rotation_, translation_);
	TransferMatrix();
}