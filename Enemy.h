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
		Approach, // 接近する
		Leave, // 離脱する
	};

	Phase phase_ = Phase::Approach;

};
