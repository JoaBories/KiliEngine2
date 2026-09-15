#pragma once

#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

namespace Kili
{
	class Transform
	{
	protected:
		Vector3 mPosition;
		Quaternion mRotation; //Quaternion mRotation
		Vector3 mScale;

	public:
		Transform() : 
			mPosition(Vector3::Zero), mRotation(Quaternion::Identity), mScale(Vector3::Unit) {}
	
		Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) :
			mPosition(position), mRotation(rotation), mScale(scale) {}

		[[nodiscard]] Vector3 getPosition() const { return mPosition; }
		[[nodiscard]] Quaternion getRotation() const { return mRotation; }
		[[nodiscard]] Vector3 getScale() const { return mScale; }

		[[nodiscard]] Vector3 getForwardVector() const { return Vector3::transform(Vector3::UnitX, mRotation);}
		[[nodiscard]] Vector3 getUpVector() const {return Vector3::transform(Vector3::UnitZ, mRotation);}
		[[nodiscard]] Vector3 getRightVector() const {return Vector3::transform(Vector3::UnitY, mRotation);}

		void setPosition(const Vector3& newPos) { mPosition = newPos; }
		void addPosition(const Vector3& movement) { mPosition += movement; }

		void setRotation(const Quaternion& newRot) { mRotation = newRot; }
		void rotate(const Quaternion& rotation);
		void rotate(const Vector3& axis, float angle);

		void setScale(const Vector3& newScale) { mScale = newScale; }
	};

	/** 
	 * World Transform, wrapper around Transform to a cached transform matrix.
	 **/
	class WorldTransform
	{
	private :
		Transform mTransform;
		mutable Matrix4 mWorldTransformMatrix; // Mutable because it is cached and so th getter can be const
		mutable bool mNeedUpdate = true;
	
		void recomputeWorldTransformMatrix() const;

	public :
		WorldTransform() = default;
	
		WorldTransform(const Transform& transform) : 
			mTransform(transform) {}
	
		WorldTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) : 
			mTransform(Transform(position, rotation, scale)) {}

		[[nodiscard]] inline Matrix4 getWorldTransformMatrix() const { recomputeWorldTransformMatrix(); return mWorldTransformMatrix; }
	
		[[nodiscard]] inline Vector3 getPosition() const { return mTransform.getPosition(); }
		[[nodiscard]] inline Quaternion getRotation() const { return mTransform.getRotation(); }
		[[nodiscard]] inline Vector3 getScale() const { return mTransform.getScale(); }
	
		[[nodiscard]] inline Vector3 getForwardVector() const { return mTransform.getForwardVector(); }
		[[nodiscard]] inline Vector3 getUpVector() const  { return mTransform.getUpVector(); }
		[[nodiscard]] inline Vector3 getRightVector() const { return mTransform.getRightVector(); }
	
		inline void setPosition(const Vector3& newPos) { mNeedUpdate = true; mTransform.setPosition(newPos); }
		inline void addPosition(const Vector3& movement) { mNeedUpdate = true; mTransform.addPosition(movement); }

		inline void setRotation(const Quaternion& newRot) { mNeedUpdate = true; mTransform.setRotation(newRot); }
		inline void rotate(const Quaternion& rotation) { mNeedUpdate = true; mTransform.rotate(rotation); }
		inline void rotate(const Vector3& axis, const float angle) { mNeedUpdate = true; mTransform.rotate(axis, angle); }

		inline void setScale(const Vector3& newScale) { mNeedUpdate = true; mTransform.setScale(newScale); }
	};
}
