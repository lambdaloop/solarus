/*
 * Copyright (C) 2006-2013 Christopho, Solarus - http://www.solarus-games.org
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
#ifndef SOLARUS_TRANSITION_H
#define SOLARUS_TRANSITION_H

#include "Common.h"
#include <cstdlib>

/**
 * @brief Abstract class for a transition effect between two phases.
 *
 * The transitions may be applied to maps or any surface.
 */
class Transition {

  public:

    /**
     * @brief Styles of transitions.
     */
    enum Style {
      IMMEDIATE = 0,  // no transition between the two surfaces
      FADE      = 1,  // fade in and fade out
      SCROLLING = 2   // scrolling between two maps
    };

    /**
     * @brief Possible directions of a transition.
     */
    enum Direction {
      IN  = 0,
      OUT = 1
    };

    virtual ~Transition();
    static Transition* create(Style style, Direction direction, Game* game = NULL);

    Game* get_game() const;
    Direction get_direction() const;
    void set_previous_surface(Surface* previous_surface);
    virtual bool needs_previous_surface() const;

    bool is_suspended() const;
    void set_suspended(bool suspended);

    /**
     * @brief Starts this transition effect.
     */
    virtual void start() = 0;

    /**
     * @brief Returns whether the transition effect is started.
     * @return true if the transition effect is started
     */
    virtual bool is_started() const = 0;

    /**
     * @brief Returns whether the transition effect is finished.
     * @return true if the transition effect is finished
     */
    virtual bool is_finished() const = 0;

    /**
     * @brief Updates this transition effect.
     */
    virtual void update() = 0;

    /**
     * @brief Draws the transition effect on a surface.
     * @param dst_surface the surface to draw
     */
    virtual void draw(Surface& dst_surface) = 0;

  protected:

    Transition(Direction direction);

    Surface* get_previous_surface() const;

    uint32_t get_when_suspended() const;

    /**
     * @brief Notifies the transition effect that it was just suspended
     * or resumed.
     */
    virtual void notify_suspended(bool suspended) = 0;

  private:

    Game* game;                   /**< The current game if any (required by some kinds of transitions). */
    Direction direction;          /**< Direction of the transition (in or out). */
    Surface* previous_surface;    /**< During an in transition, this is the surface that was displayed
                                    * when the out transition was played. */
    bool suspended;               /**< Indicates that the transition is currently paused. */
    uint32_t when_suspended;      /**< Date when the transition was suspended. */
};

#endif

