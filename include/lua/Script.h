/*
 * Copyright (C) 2009 Christopho, Solarus - http://www.solarus-engine.org
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
#ifndef SOLARUS_SCRIPT_H
#define SOLARUS_SCRIPT_H

#include "Common.h"
#include <list>
#include <map>

struct lua_State;

/**
 * @brief Handles a Lua script that is running.
 *
 * This class and its subclasses provide an API that allows Lua scripts to call C++ functions.
 */
class Script {

  protected:

    enum API {
      MAIN_API			= 0x0001,
      GAME_API			= 0x0002,
      MAP_API			= 0x0004,
      ITEM_API			= 0x0008
    };

  private:

    typedef int (FunctionAvailableToScript) (lua_State *l);		/**< type of the functions that can be called by a Lua script */

    // script data
    lua_State* context;							/**< the execution context of the Lua script */
    std::list<Timer*> timers;						/**< the timers currently running for this script */

    std::map<int, Sprite*> sprites;					/**< the sprites accessible from this script */
    int next_sprite_handle;						/**< next handle of a sprite */

    std::map<int, Movement*> movements;					/**< the movements accessible from this script */
    std::map<int, Movement*> unassigned_movements;			/**< the movements accessible from this script and that
    									 * are not assigned to an object yet (the script has to delete them) */
    int next_movement_handle;						/**< handle of the next movement created */

    // APIs
    uint32_t apis_enabled;						/**< an OR combination of APIs enabled */

    // calling a Lua function from C++
    bool find_lua_function(const std::string &function_name);

    // calling a C++ function from Lua (and also retreive the instance of Script)
    static void called_by_script(lua_State *context, int nb_arguments, Script **script);

    // initialization
    void register_apis();
    void register_main_api();
    void register_game_api();
    void register_map_api();
    void register_item_api();

    // timers
    void add_timer(Timer *timer);
    void remove_timer(const std::string &callback_name);
    bool is_new_timer_suspended(void);

    // sprites
    int create_sprite_handle(Sprite &sprite);
    Sprite& get_sprite(int sprite_handle);

    // movements
    int create_movement_handle(Movement &movement);
    Movement& get_movement(int movement_handle);
    Movement& start_movement(int movement_handle);

    // debugging
    void print_stack();

    static FunctionAvailableToScript 

      // main API
      main_api_play_sound,
      main_api_play_music,
      main_api_timer_start,
      main_api_timer_stop,
      main_api_sprite_get_animation,
      main_api_sprite_set_animation,
      main_api_sprite_get_direction,
      main_api_sprite_set_direction,
      main_api_sprite_get_frame,
      main_api_sprite_set_frame,
      main_api_sprite_get_frame_delay,
      main_api_sprite_set_frame_delay,
      main_api_sprite_is_paused,
      main_api_sprite_set_paused,
      main_api_sprite_set_animation_ignore_suspend,
      main_api_sprite_fade,
      main_api_pixel_movement_create,
      main_api_random_movement_create,
      main_api_path_movement_create,
      main_api_random_path_movement_create,
      main_api_jump_movement_create,
      main_api_movement_get_property,
      main_api_movement_set_property,

      // game API
      game_api_savegame_get_string,
      game_api_savegame_get_integer,
      game_api_savegame_get_boolean,
      game_api_savegame_set_string,
      game_api_savegame_set_integer,
      game_api_savegame_set_boolean,
      game_api_savegame_get_name,
      game_api_equipment_get_life,
      game_api_equipment_add_life,
      game_api_equipment_remove_life,
      game_api_equipment_get_max_life,
      game_api_equipment_set_max_life,
      game_api_equipment_add_max_life,
      game_api_equipment_get_money,
      game_api_equipment_add_money,
      game_api_equipment_remove_money,
      game_api_equipment_has_ability,
      game_api_equipment_get_ability,
      game_api_equipment_set_ability,
      game_api_equipment_has_item,
      game_api_equipment_get_item,
      game_api_equipment_set_item,
      game_api_equipment_has_item_amount,
      game_api_equipment_get_item_amount,
      game_api_equipment_add_item_amount,
      game_api_equipment_remove_item_amount,
      game_api_equipment_is_dungeon_finished,
      game_api_equipment_set_dungeon_finished,

      // map API
      map_api_hero_freeze,
      map_api_hero_unfreeze,
      map_api_dialog_start,
      map_api_dialog_set_variable,
      map_api_dialog_set_style,
      map_api_hud_set_enabled,
      map_api_hud_set_pause_enabled,
      map_api_camera_move,
      map_api_camera_restore,
      map_api_treasure_give,
      map_api_hero_set_map,
      map_api_hero_set_visible,
      map_api_hero_get_direction,
      map_api_hero_set_direction,
      map_api_hero_align_on_sensor,
      map_api_hero_walk,
      map_api_hero_start_jumping,
      map_api_hero_start_victory_sequence,
      map_api_hero_start_boomerang,
      map_api_hero_start_bow,
      map_api_hero_start_running,
      map_api_npc_get_position,
      map_api_npc_set_position,
      map_api_npc_start_movement,
      map_api_npc_get_sprite,
      map_api_npc_remove,
      map_api_interactive_entity_get_sprite,
      map_api_interactive_entity_remove,
      map_api_chest_set_open,
      map_api_chest_set_hidden,
      map_api_chest_is_hidden,
      map_api_tile_is_enabled,
      map_api_tile_set_enabled,
      map_api_tile_set_group_enabled,
      map_api_block_reset,
      map_api_block_reset_all,
      map_api_shop_item_remove,
      map_api_switch_is_enabled,
      map_api_switch_set_enabled,
      map_api_switch_set_locked,
      map_api_enemy_is_dead,
      map_api_enemy_is_group_dead,
      map_api_enemy_set_enabled,
      map_api_enemy_start_boss,
      map_api_enemy_end_boss,
      map_api_enemy_start_miniboss,
      map_api_enemy_end_miniboss,
      map_api_sensor_remove,
      map_api_door_open,
      map_api_door_close,
      map_api_door_is_open,
      map_api_door_set_open,

      // item API
      item_api_get_variant,
      item_api_set_variant,
      item_api_get_amount,
      item_api_set_amount,
      item_api_add_amount,
      item_api_remove_amount,
      item_api_start_movement,
      item_api_set_finished;

  protected:

    Script(uint32_t apis_enabled);

    bool notify_script(const std::string &function_name, const std::string &format = "", ...);
    void load(const std::string &script_name);
    void load_if_exists(const std::string &script_name);
    bool is_loaded();

    virtual Game& get_game();
    virtual Map& get_map();
    virtual ItemProperties& get_item_properties();

  public:

    virtual ~Script();

    virtual void update();
    virtual void set_suspended(bool suspended);
};

#endif
