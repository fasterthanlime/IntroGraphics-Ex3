//=============================================================================
//                                                                            
//   Exercise code for Introduction to Computer Graphics
//   LGG - EPFL
//   Thibaut Weise, Yuliy Schwartzburg
//                                                                            
//=============================================================================
//=============================================================================
//
//   CLASS Object3D
//
//=============================================================================


#ifndef OBJECT3D_HH
#define OBJECT3D_HH


//== INCLUDES =================================================================

#include "../math/Matrix4.h"

//== CLASS DEFINITION =========================================================




/*  
	 Basic 3D Object
*/

class Object3D
{
  
public:
    //------------------------------------------------ public methods

	//! constructor which sets the object to world transformation to identity
	Object3D()
    {
		m_transformationMatrix.loadIdentity();
	}
	
	//! destructor
	virtual ~Object3D() {}
	
	//! return the transformation from object to world coordinates
	const Matrix4 & getTransformation() const
    {
        return m_transformationMatrix;
    }

	//! set the current transformation
	void setTransformation( const Matrix4 & mat )
    {
        m_transformationMatrix = mat;
    }
	
	//! return origin of object in world coordinates
	Vector3 origin() const {
		  return m_transformationMatrix * Vector3(0,0,0);
	}

	//! set transformation matrix to identity
	void setIdentity() {
		  m_transformationMatrix.loadIdentity();
	}
	
	//! translates the object in the world coordinate system
	void translateWorld( const Vector3 & _trans )
	{
        m_transformationMatrix = m_transformationMatrix * getTranslationMatrix(_trans);      
  }
	
	
	//! translates the object in the object coordinate systems
	void translateObject( const Vector3 & _trans )
	{
        m_transformationMatrix = getTranslationMatrix(_trans) * m_transformationMatrix;
	}
	
	//! scales the object in the world coordinate system
	void scaleWorld( const Vector3 & _scl )
	{
        m_transformationMatrix = m_transformationMatrix * getScaleMatrix(_scl);
	}

	//! scales the object in the object coordinate systems
	void scaleObject( const Vector3 & _scl )
	{
        m_transformationMatrix = getScaleMatrix(_scl) * m_transformationMatrix; 
	}

	//! rotates the object in the world coordinate system
	void rotateWorld( const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = m_transformationMatrix * getRotationMatrix(_axis, _angle);
	}

	//! rotates the object in the object coordinate system
	void rotateObject( const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = getRotationMatrix(_axis, _angle) * m_transformationMatrix;
	}


	//! rotates the object around an arbitrary axis in world coordinate system
	void rotateAroundAxisWorld( const Vector3 & _pt, const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = m_transformationMatrix * (getTranslationMatrix(_pt) * getRotationMatrix(_axis, _angle) * getTranslationMatrix(-_pt));
	}

	//! rotates the object around an arbitrary axis in object coordinate system
	void rotateAroundAxisObject( const Vector3 & _pt, const Vector3& _axis, float _angle )
	{
        m_transformationMatrix = (getTranslationMatrix(_pt) * getRotationMatrix(_axis, _angle) * getTranslationMatrix(-_pt)) * m_transformationMatrix;
	}


	//! calculate translation matrix from vector
	static Matrix4 getTranslationMatrix(const Vector3 & _trans) {
	  return Matrix4(
        1, 0, 0, _trans.x,
        0, 1, 0, _trans.y,
        0, 0, 1, _trans.z,
        0, 0, 0, 1.0
    );
  }
	
	//! calculate scale matrix from vector
	static Matrix4 getScaleMatrix(const Vector3 & _scale) {
        return Matrix4(
        _scale.x, 0.0, 0.0, 0.0,
        0.0, _scale.y, 0.0, 0.0,
        0.0, 0.0, _scale.z, 0.0,
        0.0, 0.0, 0.0, 1.0);
	}
	
	//! calculate rotation matrix from rotation axis and angle in radian
	static Matrix4 getRotationMatrix(const Vector3 & axis, double angle) {
		Vector3 r = axis;
    double phi1 = atan2(r.x, r.z);
    
    double cosMinusPhi1 = cos(-phi1);
    double sinMinusPhi1 = sin(-phi1);
    Matrix4 RyMinus(
        cosMinusPhi1, 0, sinMinusPhi1, 0,
        0, 1, 0, 0,
       -sinMinusPhi1, 0, cosMinusPhi1, 0,
        0, 0, 0, 1
    );

    Vector3 rPrim = RyMinus * r;
    double phi2 = atan2(rPrim.y, rPrim.x);

    double cosPhi2 = cos(phi2);
    double sinPhi2 = sin(phi2);
    Matrix4 Rx(
      1, 0, 0, 0,
      0, cosPhi2, -sinPhi2, 0,
      0, sinPhi2,  cosPhi2, 0,
      0, 0, 0, 1
    );

    double cosa = cos(angle);
		double sina = sin(angle);

    Matrix4 Rz(
      cosa, -sina, 0, 0,
      sina,  cosa, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    );

    double cosPhi1 = cos(phi1);
    double sinPhi1 = sin(phi1);
    Matrix4 Ry(
        cosPhi1, 0, sinPhi1, 0,
        0, 1, 0, 0,
       -sinPhi1, 0, cosPhi1, 0,
        0, 0, 0, 1
    );

    double cosMinusPhi2 = cos(-phi2);
    double sinMinusPhi2 = sin(-phi2);
    Matrix4 RxMinus(
      1, 0, 0, 0,
      0, cosMinusPhi2, -sinMinusPhi2, 0,
      0, sinMinusPhi2,  cosMinusPhi2, 0,
      0, 0, 0, 1
    );

		Matrix4 rotationMatrix = Ry * RxMinus * Rz * Rx * RyMinus;
    return rotationMatrix;
        
		return rotationMatrix;
	
	}
	
protected:
    //------------------------------------------------------- protected data
    //------------- any subclasses of Object3D will have access to this data

	//! transformation matrix from object to world coordinate system
	Matrix4 m_transformationMatrix;
};


//=============================================================================
#endif // OBJECT3D_HH defined
//=============================================================================

