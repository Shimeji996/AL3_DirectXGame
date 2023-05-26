#include "MatrixMath.h"
#include "Model.h"

class Enemy {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& view);

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;

	enum class Phase {
		Approach, // ê⁄ãﬂÇ∑ÇÈ
		Leave, // ó£íEÇ∑ÇÈ
	};

	Phase phase_ = Phase::Approach;

};
