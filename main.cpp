#include <CacKit>

constexpr double gravity = 0.8214808;

CAC_HOOKS

class: public $PlayerObject {
	void updateJump(float delta) override {
		if (cac_this->_isShip()) {
			float direction = cac_this->_isUpsideDown() ? -1 : 1;

			float size = 1.0;
			if (cac_this->_vSize() != 1.0) 
				size = 0.85;

			double& yAccel = cac_this->_yAccel();

			// prevents weird stuff
			if (fabs(yAccel) > 6)
				gravity+=1;

			double n_yAccel = yAccel + (gravity * delta * direction * -0.5)/size;

			// speed cap
			if (!(fabs(yAccel) > 6 && fabs(n_yAccel) > fabs(yAccel)))
				yAccel = n_yAccel;

			if (cac_this->_isHolding() && cac_this->_hasJustHeld()) {
				cac_this->_hasJustHeld() = false;
				cac_this->flipGravity(direction==1.0, true);
			}
		} else $PlayerObject::updateJump(delta);
	}
} SwingCopter;

END_CAC_HOOKS