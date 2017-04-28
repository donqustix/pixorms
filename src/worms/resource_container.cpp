#include "resource_container.h"
#include "resource.h"

using worms::ResourceContainer;

ResourceContainer::ResourceContainer() = default;

ResourceContainer::ResourceContainer(ResourceContainer&&) noexcept = default;

ResourceContainer::~ResourceContainer() = default;

ResourceContainer& ResourceContainer::operator=(ResourceContainer&&) noexcept = default;

