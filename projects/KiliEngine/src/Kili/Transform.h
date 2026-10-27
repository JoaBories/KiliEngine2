#pragma once

namespace Kili
{
	class Transform
	{
	protected:
		glm::vec3 mPosition;
		glm::quat mRotation; //Quaternion mRotation
		glm::vec3 mScale;

	public:
		Transform() : 
			mPosition(glm::vec3()), mRotation(glm::quat()), mScale(glm::vec3(1.0f,1.0f,1.0f)) {}
	
		Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) :
			mPosition(position), mRotation(rotation), mScale(scale) {}

		[[nodiscard]] constexpr glm::vec3 getPosition() const { return mPosition; }
		[[nodiscard]] constexpr glm::quat getRotation() const { return mRotation; }
		[[nodiscard]] constexpr glm::vec3 getScale() const { return mScale; }

		[[nodiscard]] constexpr glm::vec3 getForwardVector() const { return mRotation * glm::vec3(1.0f, 0.0f, 0.0f); }
		[[nodiscard]] constexpr glm::vec3 getUpVector() const {return mRotation * glm::vec3(0.0f,1.0f,0.0f); }
		[[nodiscard]] constexpr glm::vec3 getRightVector() const {return mRotation * glm::vec3(0.0f,0.0f,1.0f); }

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
		mutable glm::mat4 mTransformMatrix; // Mutable because it is cached and so th getter can be const
		mutable bool mNeedUpdate = true;
	
		void recomputeWorldTransformMatrix() const;

	public :
		WorldTransform() = default;
	
		WorldTransform(const Transform& transform) : 
			mTransform(transform) {}
	
		WorldTransform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) : 
			mTransform(Transform(position, rotation, scale)) {}

		[[nodiscard]] inline glm::mat4 getTransformMatrix() const { recomputeWorldTransformMatrix(); return mTransformMatrix; }
	
		[[nodiscard]] constexpr glm::vec3 getPosition() const { return mTransform.getPosition(); }
		[[nodiscard]] constexpr glm::quat getRotation() const { return mTransform.getRotation(); }
		[[nodiscard]] constexpr glm::vec3 getScale() const { return mTransform.getScale(); }
	
		[[nodiscard]] constexpr glm::vec3 getForwardVector() const { return mTransform.getForwardVector(); }
		[[nodiscard]] constexpr glm::vec3 getUpVector() const  { return mTransform.getUpVector(); }
		[[nodiscard]] constexpr glm::vec3 getRightVector() const { return mTransform.getRightVector(); }
	
		constexpr void setPosition(const glm::vec3& newPos) { mNeedUpdate = true; mTransform.setPosition(newPos); }
		constexpr void addPosition(const glm::vec3& movement) { mNeedUpdate = true; mTransform.addPosition(movement); }

		constexpr void setRotation(const glm::quat& newRot) { mNeedUpdate = true; mTransform.setRotation(newRot); }
		void rotate(const glm::quat& rotation) { mNeedUpdate = true; mTransform.rotate(rotation); }
		void rotate(const glm::vec3& axis, const float angle) { mNeedUpdate = true; mTransform.rotate(axis, angle); }

		constexpr void setScale(const glm::vec3& newScale) { mNeedUpdate = true; mTransform.setScale(newScale); }
	};
}
