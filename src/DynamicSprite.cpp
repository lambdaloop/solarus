/*
 * Copyright (C) 2009-2011 Christopho, Solarus - http://www.solarus-engine.org
 * 
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "DynamicSprite.h"
#include "Sprite.h"

/**
 * @brief Creates a dynamic sprite.
 * @param basic_sprite the basic sprite to encapsulate
 */
DynamicSprite::DynamicSprite(Sprite& basic_sprite):
  DynamicDisplayable(basic_sprite) {

}

/**
 * @brief Destructor.
 */
DynamicSprite::~DynamicSprite() {

}

/**
 * @brief Returns the sprite encapsulated.
 */
Sprite& DynamicSprite::get_basic_sprite() {

  return (Sprite&) get_displayable();
}
