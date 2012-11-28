/*!
* \brief Distance entre deux points.
* \author Hiura
* \details Cette fonction nécessite que la fonction sqrt soit définie. Il est possible de procéder ainsi :
* \code 
#include <cmath>
using std::sqrt; // on pourrait utilisez la fonction de Carmack en notant a la place : "using gpl::sqrt;"
* \endcode
* \param x1 : abcisse du premier point.
* \param y1 : ordonnée du premier point.
* \param x2 : abcisse du deuxième point, par défaut nul.
* \param y2 : ordonnée du deuxième point, par défaut nul.
* \return Distance entre (x1;y1) et (x2;y2).
*/
inline float Distance(const float x1, const float y1, const float x2 = 0.f, const float y2 = 0.f)
{
    // Formule de calcul de la distance entre deux points :
    // sqrt( (x1 - x2)² + (y1 - y2)² )
 
    return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}
 
/*!
* \brief Distance entre deux points.
* \author Hiura
* \param p1 : Premier point.
* \param p2 : Deuxième point, par défaut nul.
* \return Distance entre p1 et p2.
*/
inline float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2 = sf::Vector2f(0.f, 0.f))
{
    // Utilisation de l'autre fonction Distance.
    return Distance(p1.x, p1.y, p2.x, p2.y);
}

namespace gpl
{
/**
\brief Racine carre
 
\param number : X
 
\return racine carre de X
*/
inline float sqrt(float number) {
    long i;
    float x, y;
    const float f = 1.5F;
 
    x = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( f - ( x * y * y ) );
    y  = y * ( f - ( x * y * y ) ); // si on veut plus de précision
    return number * y;
}
} // namespace gpl

/**
\brief Translation d'un point selon un axe
 
\param distance : Longueur de la translation
\param angle : Angle de l'axe en degrés
\param p : Point a translaté
 
\return Point translaté
*/
inline sf::Vector2f Translate(const float distance, const float angle, const sf::Vector2f& p = sf::Vector2f(0.f, 0.f))
{
    // X -1 en y car le repère est inversé dans SFML
    return sf::Vector2f(p.x + distance * std::cos(ToRad(angle)), p.y - distance * std::sin(ToRad(angle)));
}
/*!
* \brief Translation d'un point par un vecteur directeur.
* \author hiura
* \param p : point à translater.
* \param v : vecteur de translation.
* \return nouveau point.
*/
inline sf::Vector2f Translate(const sf::Vector2f& p, const sf::Vector2f& v)
{
    return sf::Vector2f(p.x + v.x, p.y + v.y);
}


/**
\brief Angle (en degrés) de l'axe formé par 2 points
 
\param x1 : Abcisse du premier point
\param y1 : Ordonnée du premier point
\param x2 : Abcisse du second point
\param y2 : Ordonnée du second point
 
\return Angle de l'axe formé par 2 points
*/
inline float Angle(const float x1, const float y1, const float x2 = 0.f, const float y2 = 0.f)
{
    float x = x1 - x2;
    float y = y1 - y2;
 
    if (y == 0.f)
    {
        if (x >= 0.f)
            return 0.f;
        else
            return 180.f;
    }
 
    if (y >= 0.f)
    {
        return ( ToDeg( std::atan(y/x) ) + 270.f );
    }
    else
    {
        return ( ToDeg( std::atan(y/x) ) + 90.f );
    }
}
 
/**
\brief Angle (en degrés) de l'axe formé par 2 points
 
\param p1 Premier point
\param p2 Second point
 
\return Angle de l'axe formé par 2 points
*/
inline float Angle(const sf::Vector2f& p1, const sf::Vector2f& p2 = sf::Vector2f(0.f, 0.f))
{
    return Angle(p1.x, p1.y, p2.x, p2.y);
}
 
/**
\brief Rotation d'un point autour d'un autre
 
\param p : Point a rotationer
\param AddedAngle : Angle ajouté
\param center : Centre de rotation
 
\return Point rotationé
*/
inline sf::Vector2f Rotation(const sf::Vector2f& p, const float angle, const sf::Vector2f& center = sf::Vector2f(0.f, 0.f))
{
    float distance = Distance(p, center);
    return Translate(distance, angle, center);
}
 
/**
\brief Rotation d'un point autour d'un autre
 
\param p : Point a rotationer
\param AddedAngle : Angle ajouté
\param center : Centre de rotation
 
\return Point rotationé
*/
inline sf::Vector2f Rotate(const sf::Vector2f& p, const float AddedAngle, const sf::Vector2f& center = sf::Vector2f(0.f, 0.f))
{
    float angle = Angle(p, center);
    return Rotation(p, angle + AddedAngle, center);
}
