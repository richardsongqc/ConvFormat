#pragma once
#include <map>
#include <vector>

class CCoordinate
{
public:
	CCoordinate(double dX, double dY, double dZ = 0.0);
	~CCoordinate(void);

	CCoordinate( const CCoordinate& con );
	CCoordinate& operator = ( const CCoordinate& con );

	bool operator == ( const CCoordinate& con ) const;
	bool operator != ( const CCoordinate&  con ) const;
	bool operator > ( const CCoordinate&  con ) const;
	bool operator < ( const CCoordinate&  con ) const;
	

	double GetX() const;
	void   SetX( double dX);

	double GetY() const;
	void   SetY( double dY);

	double GetZ() const;
	void   SetZ( double dZ);

	void Transform();

private:
	double m_dX;
	double m_dY;
	double m_dZ;
};

struct CmpByKey
{  
	bool operator()(const CCoordinate& k1, const CCoordinate& k2) 
	{  
		return k1 < k2;  
	}  
};  

typedef std::vector<CCoordinate> VECPOINTS;
typedef std::map<double, VECPOINTS, std::less<double> > MAPPOINTS;



