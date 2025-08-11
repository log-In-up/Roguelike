#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "GameObject.h"
#include "Matrix2D.h"
#include "Vector.h"

namespace GameEngine
{
	class TransformComponent : public Component
	{
	private:
		TransformComponent* parent = nullptr;

		mutable Vector2Df localPosition = { 0, 0 };
		mutable Vector2Df localScale = { 1, 1 };

		mutable Vector2Df position = { 0, 0 };
		mutable Vector2Df scale = { 1, 1 };

		mutable float localRotation = 0.f;
		mutable float rotation = 0.f;

		mutable Matrix2D localTransform;

		mutable bool isUpdated = false;
	public:
		TransformComponent(GameObject* gameObject);

		const float GetLocalRotation() const;
		const float GetWorldRotation() const;
		const Matrix2D GetWorldTransform() const;
		const Vector2Df& GetLocalPosition() const;
		const Vector2Df& GetLocalScale() const;
		const Vector2Df& GetWorldPosition() const;
		const Vector2Df& GetWorldScale() const;
		TransformComponent* GetParent() const;
		void MoveBy(const Vector2Df& offset);
		void MoveBy(float offsetX, float offsetY);
		void Print() const;
		void Render(sf::RenderWindow& window) override;
		void RotateBy(float offset);
		void ScaleBy(const Vector2Df& scale);
		void ScaleBy(float scaleX, float scaleY);
		void SetLocalPosition(const Vector2Df& position);
		void SetLocalPosition(float positionX, float positionY);
		void SetLocalRotation(float angle);
		void SetLocalScale(const Vector2Df& scale);
		void SetLocalScale(float scaleX, float scaleY);
		void SetParent(TransformComponent* newParent);
		void SetWorldPosition(const Vector2Df& position);
		void SetWorldPosition(float positionX, float positionY);
		void SetWorldRotation(float angle);
		void SetWorldScale(const Vector2Df& scale);
		void SetWorldScale(float scaleX, float scaleY);
		void Update(float deltaTime) override;
	private:
		Matrix2D createTransform(const Vector2Df& position, float rotation, const Vector2Df& scale) const;
		void setLocalInfoFrom(const Matrix2D& transform) const;
		void setWorldInfoFrom(const Matrix2D& transform) const;
		void updateLocalTransform() const;
		void updateLocalTransform(const Vector2Df& position, float rotation, const Vector2Df& scale) const;
	};
}