#include "StdAfx.h"
#include "Coordinate.h"


CCoordinate::CCoordinate(double dX, double dY, double dZ)
	: m_dX(dX),
	  m_dY(dY),
	  m_dZ(dZ)
{
}


CCoordinate::~CCoordinate(void)
{
}

CCoordinate::CCoordinate( const CCoordinate& con )
{
	m_dX = con.m_dX;
	m_dY = con.m_dY;
	m_dZ = con.m_dZ;	


}

CCoordinate& CCoordinate::operator = ( const CCoordinate& con )
{
	m_dX = con.m_dX;
	m_dY = con.m_dY;
	m_dZ = con.m_dZ;

	return *this;
}

bool CCoordinate::operator == ( const CCoordinate& con ) const
{
	return ( m_dX == con.m_dX ) &&
		   ( m_dY == con.m_dY ) &&
		   ( m_dZ == con.m_dZ ) ;
}

bool CCoordinate::operator != ( const CCoordinate&  con ) const
{
	return ( m_dX != con.m_dX ) ||
		   ( m_dY != con.m_dY ) ||
		   ( m_dZ != con.m_dZ ) ;
}

bool CCoordinate::operator > ( const CCoordinate& con ) const
{
	return ( m_dX > con.m_dX ) &&
		   ( m_dY > con.m_dY ) &&
		   ( m_dZ > con.m_dZ );
}

bool CCoordinate::operator < ( const CCoordinate& con ) const
{
	return ( m_dX < con.m_dX ) &&
		   ( m_dY < con.m_dY ) &&
		   ( m_dZ < con.m_dZ );
}
	

double CCoordinate::GetX() const
{
	return m_dX;
}

void CCoordinate::SetX( double dX)
{
	m_dX = dX;
}

double CCoordinate::GetY() const
{
	return m_dY;
}

void CCoordinate::SetY( double dY)
{
	m_dY = dY;
}

double CCoordinate::GetZ() const
{
	return m_dZ;
}

void   CCoordinate::SetZ( double dZ)
{
	m_dZ = dZ;
}

void CCoordinate::Transform()
{

}
