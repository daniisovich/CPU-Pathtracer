#include "material.h"

Material::Material(const Vec3& color, float reflectiveness) : m_color{ color }, m_reflectiveness{ reflectiveness } { }

const Vec3 Material::color() const { return m_color; }
float Material::reflectiveness() const { return m_reflectiveness; }