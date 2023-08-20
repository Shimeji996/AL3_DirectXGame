#include "WorldTransform.h"
#include "MatrixMath.h"

void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	TransferMatrix();
}