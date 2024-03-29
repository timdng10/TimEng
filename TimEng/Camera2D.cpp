#include "Camera2D.h"

namespace TimEng{
	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_orthoMatrix(1.0f),
		_cameraMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(1),
		_screenWidth(500),
		_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight){
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);

	}


	void Camera2D::update(){
		if (_needsMatrixUpdate){
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords){
		screenCoords.y = _screenHeight - screenCoords.y;

		screenCoords -= glm::vec2(_screenWidth/2, _screenHeight/2);
		screenCoords /= _scale;
		screenCoords += _position;
		return screenCoords;
	}

	bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimentions){
		glm::vec2 scaledScreenDimentions = glm::vec2(_screenWidth, _screenHeight) / (_scale);

		const float MIN_DISTANCE_X = dimentions.x / 2.0f + scaledScreenDimentions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimentions.y / 2.0f + scaledScreenDimentions.y / 2.0f;

		glm::vec2 centerPos = position + dimentions / 2.0f;
		glm::vec2 centerCameraPos = _position;

		glm::vec2 distVec = centerPos - centerCameraPos;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		return xDepth > 0 && yDepth > 0;
	}
}

