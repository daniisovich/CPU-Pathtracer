#pragma once

#include <optional>

#include "core/ray.h"
#include "core/intersection.h"
#include "scene/material/material.h"


class SceneObject {

public:
	virtual const std::optional<Intersection> intersect(const Ray& ray, float near, float far) const = 0;

};