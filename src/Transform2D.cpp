#include "../include/Transform2D.h"
#include "../include/Camera2D.h"
#include "../include/MainClass.h"
#include <iostream>

namespace Johnny
{
	Transform2D::Transform2D() :
		m_translation(0.0f, 0.0f),
		m_rotation(0.0f),
		m_scale(1.0f, 1.0f)
	{

	}

	Transform2D::Transform2D(const Vector2f& translation, const GLfloat& rotation, const Vector2f& scale) :
		m_translation(translation),
		m_rotation(rotation),
		m_scale(scale)
	{
		
	}

	Transform2D::~Transform2D()
	{

	}

	Matrix3f Transform2D::getTransformation() const
	{
		return Matrix3f::translate(m_translation) * Matrix3f::rotate(m_rotation) * Matrix3f::scale(m_scale);//Matrix3f::identity();
	}

	Matrix3f Transform2D::getProjectedTransformation(const Camera2D* cam) const
	{
		return cam->getViewMatrix() * getTransformation();
	}

	Vector2f TransformableObject2D::center;
	std::vector<TransformableObject2D*> TransformableObject2D::objects;

	const Vector2f& TransformableObject2D::getCenter()
	{
		return center;
	}

	void TransformableObject2D::setCenter(const Vector2f& v)
	{
		Vector2f prevCenter = center;
		center = v;
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (!objects[i]->m_affectedByCenter)
				continue;

			std::cout << "Size Before: " << objects[i]->m_transform.getTranslation() << std::endl;
			objects[i]->m_transform.setTranslation(objects[i]->m_transform.getTranslation() - objects[i]->m_size / 2.0f * objects[i]->m_transform.getScale() - prevCenter);
			std::cout << "Size after: " << objects[i]->m_transform.getTranslation() << std::endl;
			objects[i]->setPosition(objects[i]->m_transform.getTranslation());
			std::cout << "Size after after: " << objects[i]->m_transform.getTranslation() << std::endl;
		}
	}

	TransformableObject2D::TransformableObject2D()
	{
		objects.push_back(this);
	}

	TransformableObject2D::~TransformableObject2D()
	{

		if (objects.size() == 1)
			objects.clear();
		else
		{

			for (size_t i = 0; i < objects.size(); i++)
			{

				if (objects[i] == this)
				{
					objects[i] = objects.back();
					objects.pop_back();
					break;
				}
			}
		}
	}

	void TransformableObject2D::setPosition(const Vector2f& pos)
	{
		if (m_size.x == 0.0f && m_size.y == 0.0f)
		{
			m_transform.setTranslation(pos);
		}
		else
		{
			m_transform.setTranslation(pos + m_size / 2.0f * m_transform.getScale() + center);
		}
			
	}

	void TransformableObject2D::setPosition(const GLfloat& x, const GLfloat& y)
	{
		setPosition(Vector2f(x, y));
	}

	void TransformableObject2D::setRotation(const GLfloat& rotation)
	{
		m_transform.setRotation(rotation);
	}

	void TransformableObject2D::setScale(const Vector2f& v)
	{
		if (m_size.x == 0.0f && m_size.y == 0.0f)
			m_transform.setScale(v);
		else
		{
			m_transform.setTranslation(m_transform.getTranslation() - m_size / 2.0f * m_transform.getScale() - center);
			m_transform.setScale(v);
			setPosition(m_transform.getTranslation());
		}
		
	}

	void TransformableObject2D::setScale(const GLfloat& x, const GLfloat& y)
	{
		setScale(Vector2f(x, y));
	}

	void TransformableObject2D::setSize(const Vector2f& v)
	{
		if (m_size.x == 0.0f && m_size.y == 0.0f)
		{
			m_size = v;
		}
		else
		{
			m_transform.setTranslation(m_transform.getTranslation() - m_size / 2.0f * m_transform.getScale() - center);
			m_size = v;
		}
		
		setPosition(m_transform.getTranslation());
	}

	void TransformableObject2D::addPosition(const Vector2f& pos)
	{
		m_transform.setTranslation(m_transform.getTranslation() + pos);
	}

	void TransformableObject2D::addPosition(const GLfloat& x, const GLfloat& y)
	{
		m_transform.setTranslation(m_transform.getTranslation() + Vector2f(x, y));
	}

	void TransformableObject2D::addScale(const Vector2f& v)
	{
		m_transform.setScale(m_transform.getScale() + v);
	}

	void TransformableObject2D::addScale(const GLfloat& x, const GLfloat& y)
	{
		m_transform.setScale(m_transform.getScale() + Vector2f(x, y));
	}

	Vector2f TransformableObject2D::getPosition() const
	{
		return m_transform.getTranslation() - m_size / 2.0f * m_transform.getScale() - center;
	}
}
