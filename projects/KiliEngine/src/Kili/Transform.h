#pragma once

constexpr glm::vec3 WORLD_FORWARD = glm::vec3(1, 0, 0);
constexpr glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);
constexpr glm::vec3 WORLD_RIGHT = glm::vec3(0, 0, 1);

namespace Kili
{
	class Transform
	{
	protected:
		glm::vec3 mPosition;
		glm::quat mRotation;
		glm::vec3 mScale;

	public:
		Transform() : 
			mPosition(glm::vec3()), mRotation(glm::quat()), mScale(glm::vec3(1.0f,1.0f,1.0f)) {}
	
		Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) :
			mPosition(position), mRotation(rotation), mScale(scale) {}

		[[nodiscard]] constexpr glm::vec3 position() const	{ return mPosition; }
		[[nodiscard]] constexpr glm::quat rotation() const	{ return mRotation; }
		[[nodiscard]] constexpr glm::vec3 scale() const		{ return mScale; }

		[[nodiscard]] constexpr glm::vec3 forward() const	{ return mRotation * WORLD_FORWARD; }
		[[nodiscard]] constexpr glm::vec3 up() const		{ return mRotation * WORLD_UP; }
		[[nodiscard]] constexpr glm::vec3 right() const		{ return mRotation * WORLD_RIGHT; }

		constexpr void setPosition(const glm::vec3& newPos) { mPosition = newPos; }
		constexpr void addPosition(const glm::vec3& movement) { mPosition += movement; }

		constexpr void setRotation(const glm::quat& newRot) { mRotation = newRot; }
		void rotate(const glm::quat& rotation);
		void rotate(const glm::vec3& axis, float angle);

		constexpr void setScale(const glm::vec3& newScale) { mScale = newScale; }
	};

	/** 
	 * World Transform, wrapper around Transform to a cached transform matrix.
	 **/
	class WorldTransform
	{
	private :
		Transform mTransform;
		mutable glm::mat4 mTransformMatrix; // Mutable because it is cached and so the getter can be const
		mutable bool mNeedUpdate = true;
	
		void recomputeWorldTransformMatrix() const;

	public :
		WorldTransform() = default;
	
		WorldTransform(const Transform& transform) : 
			mTransform(transform) {}
	
		WorldTransform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) : 
			mTransform(Transform(position, rotation, scale)) {}

		[[nodiscard]] glm::mat4 getTransformMatrix() const	{ recomputeWorldTransformMatrix(); return mTransformMatrix; }
	
		[[nodiscard]] constexpr glm::vec3 position() const	{ return mTransform.position(); }
		[[nodiscard]] constexpr glm::quat rotation() const	{ return mTransform.rotation(); }
		[[nodiscard]] constexpr glm::vec3 scale() const		{ return mTransform.scale(); }
	
		[[nodiscard]] constexpr glm::vec3 forward() const	{ return mTransform.forward(); }
		[[nodiscard]] constexpr glm::vec3 up() const		{ return mTransform.up(); }
		[[nodiscard]] constexpr glm::vec3 right() const		{ return mTransform.right(); }
	
		constexpr void setPosition(const glm::vec3& newPos) { mNeedUpdate = true; mTransform.setPosition(newPos); }
		constexpr void addPosition(const glm::vec3& movement) { mNeedUpdate = true; mTransform.addPosition(movement); }

		constexpr void setRotation(const glm::quat& newRot) { mNeedUpdate = true; mTransform.setRotation(newRot); }
		void rotate(const glm::quat& rotation) { mNeedUpdate = true; mTransform.rotate(rotation); }
		void rotate(const glm::vec3& axis, const float angle) { mNeedUpdate = true; mTransform.rotate(axis, angle); }

		constexpr void setScale(const glm::vec3& newScale) { mNeedUpdate = true; mTransform.setScale(newScale); }
	};
}
