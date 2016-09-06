#pragma once

/***
 * This is basically a translation of the WML schema described in the wesnoth
 * wiki
 */

#include <libwml/declare_wml_tag.hpp>
#include <libwml/tags.hpp>
#include <libwml/traits/tag.hpp>
#include <libwml/util/optional.hpp>
#include <libwml/util/variant.hpp>
#include <libwml/attributes.hpp>
#include <libwml/child_containers.hpp>
#include <libwml/heterogenous_sequence.hpp>
#include <libwml/util/variant.hpp>
#include <libwml/util/optional.hpp>
#include <vector>

namespace wml {
  using int_val = int;
  using bool_val = bool;
  using string_val = std::string;
  using string_list_val = std::vector<std::string>;
  using string_to_int_map = std::map<std::string, int_val>;

  template <typename T>
  using child_vector = std::vector<T>;

  using string_opt = util::optional<std::string>;
  using int_opt = util::optional<int>;
  using bool_opt = util::optional<bool>;
} // end namespace wml

namespace wml { struct unit_filter; }
namespace wml { typedef util::recursive_wrapper<unit_filter> unit_filter_wrapper; }

DECLARE_WML_TAG(unstructured, (all_children_map, all));

DECLARE_WML_TAG(attack_filter,
  (string_opt, range)
  (string_opt, name)
  (string_opt, type)
  (int_opt, damage)
  (string_opt, special));

DECLARE_WML_TAG_AND_NAME(frame_tag, "frame",
  (string_opt, image)
  (string_opt, sound)
  (string_opt, halo)
  (int_opt, alpha)
  (int_opt, duration)
  (int_opt, halo_x)
  (int_opt, halo_y)
  (int_opt, offset)
  (int_opt, directional_x)
  (bool_opt, auto_hflip)
  (bool_opt, auto_vflip)
  (string_opt, blend_color)
  (int_opt, blend_ratio)
  (string_opt, image_diagonal));

DECLARE_WML_TAG(animation_tag, 
  (string_opt, apply_to)
  (int_opt, start_time)
  (int_opt, offset)
  (bool_opt, hits)
  (int_opt, attack_sound_start_time)
  (int_opt, missile_start_time)
  (int_opt, sound_start_time)
  (int_opt, horse_sound_start_time)
  (int_opt, halo_start_time)
  (int_opt, halo1_start_time)
  (int_opt, halo2_start_time)
  (int_opt, halo3_start_time)
  (int_opt, halo4_start_time)
  (int_opt, halo5_start_time)
  (string_list_val, direction)
  (frame_tag, frame)
  (frame_tag, halo_frame)
  (frame_tag, missile_frame)
  (frame_tag, sound_frame)
  (frame_tag, attack_sound_frame)
  (frame_tag, die_sound_frame)
  (frame_tag, horse_sound_frame)
  (attack_filter, filter_attack)
  (unit_filter_wrapper, filter_second));

namespace wml { struct location_filter; }
namespace wml { struct side_filter; }
namespace wml { struct unit_filter_adjacent; }
namespace wml { struct unit_filter_vision; }
namespace wml { struct location_filter_adjacent; }
namespace wml { struct location_filter_vision; }

namespace wml { typedef util::recursive_wrapper<location_filter> location_filter_wrapper; }
namespace wml { typedef util::recursive_wrapper<side_filter> side_filter_wrapper; }
namespace wml { typedef util::recursive_wrapper<unit_filter_adjacent> unit_adjacent_filter_wrapper; }
namespace wml { typedef util::recursive_wrapper<unit_filter_vision> unit_filter_vision_wrapper; }
namespace wml { typedef util::recursive_wrapper<location_filter_adjacent> adjacent_location_filter_wrapper; }
namespace wml { typedef util::recursive_wrapper<location_filter_vision> vision_filter_wrapper; }

MAKE_HETEROGENOUS_SEQUENCE(unit_filter_children,
  (wml::unit_filter_wrapper, "filter")
  (wml::location_filter_wrapper, "filter_location")
  (wml::side_filter_wrapper, "filter_side")
  (wml::unit_adjacent_filter_wrapper, "filter_adjacent")
  (wml::unit_filter_vision_wrapper, "filter_vision")
  (wml::unit_filter_wrapper, "or")
  (wml::unit_filter_wrapper, "and")
  (wml::unit_filter_wrapper, "not"))

MAKE_HETEROGENOUS_SEQUENCE(location_filter_children,
  (wml::unit_filter_wrapper, "filter")
  (wml::vision_filter_wrapper, "filter_vision")
  (wml::side_filter_wrapper, "filter_owner")
  (wml::location_filter_wrapper, "filter_radius")
  (wml::adjacent_location_filter_wrapper, "filter_adjacent_location")
  (wml::location_filter_wrapper, "or")
  (wml::location_filter_wrapper, "and")
  (wml::location_filter_wrapper, "not"))

#define LOCATION_FILTER_ATTRIBUTES \
  (string_opt, x)  \
  (string_opt, y)  \
  (string_opt, time_of_day) \
  (string_list_val, time_of_day_id) \
  (string_list_val, terrain) \
  (string_opt, area) \
  (int_opt, owner_side) \
  (string_val, find_in) \
  (int_opt, radius) \

#define LOCATION_FILTER_CHILDREN \
  (location_filter_children, children)

DECLARE_WML_TAG(location_filter,
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(location_filter_adjacent,
//  (swallow_attribute, direction)
  (string_opt, count)
  (string_opt, adjacent)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(location_filter_vision,
  (bool_val, visible, true)
  (bool_val, respect_fog, true)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(store_locations,
  (string_val, variable)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

// TODO: side should be an int list
#define UNIT_FILTER_ATTRIBUTES \
  (string_opt, id)  \
  (string_opt, speaker)  \
  (string_opt, type)  \
  (string_opt, race)  \
  (string_opt, ability)  \
  (string_list_val, side)  \
  (string_list_val, status)  \
  (bool_opt, has_weapon)  \
  (string_opt, gender)    \
  (string_opt, role)    \
  (string_opt, variation)  \
  (int_opt, level)    \
  (int_opt, defense)    \
  (int_opt, movement_cost)  \
  (int_opt, x)  \
  (int_opt, y)  \
  (string_opt, find_in) \
  (string_opt, lua_function) \
  (bool_opt, canrecruit)

#define UNIT_FILTER_CHILDREN \
  (unit_filter_children, children) \
  (wml::raw_config, filter_wml)

DECLARE_WML_TAG(unit_filter,
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(unit_filter_adjacent,
  (string_val, direction)
  (int_opt, count)
  (string_list_val, adjacent)
  (bool_opt, is_enemy)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

namespace wml { struct side_filter; }

DECLARE_WML_TAG(side_filter_has_unit,
  (bool_val, search_recall_list, false)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

#define SIDE_FILTER_ATTRIBUTES \
  (string_opt, side) \
  (string_opt, team_name) \
  (string_opt, controller)


#define SIDE_FILTER_CHILDREN \
  (side_filter_has_unit, has_unit) \
  (util::recursive_wrapper<wml::side_filter> , enemy_of) \
  (util::recursive_wrapper<wml::side_filter> , allied_with) \
  (util::recursive_wrapper<wml::side_filter> , has_enemy) \
  (util::recursive_wrapper<wml::side_filter> , has_ally)


DECLARE_WML_TAG(side_filter,
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(unit_filter_vision,
  (bool_val, visible, true)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(store_side,
  (string_val, variable)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(store_gold,
  (string_val, variable)
  (string_list_val, side));

DECLARE_WML_TAG(store_starting_locations,
  (string_val, variable));

DECLARE_WML_TAG(store_time_of_day,
  (string_val, variable));

DECLARE_WML_TAG(store_turns,
  (string_val, variable));

DECLARE_WML_TAG(modify_turns,
  (int_opt, value)
  (int_opt, add));

DECLARE_WML_TAG(store_villages,
  (string_val, variable)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

/** specials wml **/

DECLARE_WML_TAG_AND_NAME(specials_tag, "specials", );

/** abilities wml **/

DECLARE_WML_TAG(abilities_tag, );

/** effect wml **/

DECLARE_WML_TAG(effect_set_specials,
  (string_val, mode)
  );

DECLARE_WML_TAG_AND_NAME(effect_tag, "effect",
  (string_val, apply_to)
  (string_opt, times)
  (string_opt, name)
  (string_opt, description)
  (string_opt, type)
  (string_opt, range)
  (string_opt, portrait)
  (int_opt, add)
  (int_opt, increase)
  (int_opt, increase_total)
  (int_opt, damage)
  (int_opt, number)
  (int_opt, value)
  (int_opt, increase_attacks)
  (int_opt, increase_damage)
  (bool_opt, heal_full)
  (bool_opt, replace)
  (string_opt, set_description)
  (string_opt, set_name)
  (string_opt, set_type)
  (string_opt, set_icon)
  (string_to_int_map, movement_costs)
  (string_to_int_map, resistance)
  (string_to_int_map, defense)
  (unit_filter, filter)
  (abilities_tag, abilities)
  (specials_tag, specials)
  (effect_set_specials, set_specials));

/***** [trait] *****/

DECLARE_WML_TAG(trait,
  (string_val, id)
  (string_opt, availability)
  (string_opt, male_name)
  (string_opt, female_name)
  (string_opt, name)
  (string_opt, description)
  (effect_tag, effect));

/** action wml **/

DECLARE_WML_TAG(label,
  (int_val, x, 0)
  (int_val, y, 0)
  (string_val, text));

DECLARE_WML_TAG(unit_status,
  (bool_val, poisoned, false)
  (bool_val, slowed, false)
  (bool_val, petrified, false)
  (bool_val, uncovered, false)
  (bool_val, guardian, false)
  (bool_val, unhealable, false));

namespace wml { struct object; }

DECLARE_WML_TAG(unit_ai, );
DECLARE_WML_TAG(unit_modifications,
  (util::recursive_wrapper<wml::object>, object)
  (util::recursive_wrapper<wml::trait>, trait));

#define UNIT_ATTRIBUTES \
  (string_opt, type)    \
  (string_opt, parent_type)  \
  (int_val, side, 1)    \
  (string_opt, gender)    \
  (int_val, x, 0)    \
  (int_val, y, 0)    \
  (string_list_val, placement)  \
  (string_opt, to_variable)  \
  (string_opt, id)    \
  (string_opt, name)    \
  (bool_val, generate_name, true)\
  (bool_val, unrenamable, false)    \
  (string_opt, traits_description)  \
  (bool_val, random_traits, false)  \
  (bool_opt, random_gender)    \
  (bool_val, canrecruit, false)    \
  (string_list_val, extra_recruit)  \
  (string_opt, variation)    \
  (string_opt, upkeep)      \
  (string_list_val, overlays)    \
  (int_opt, goto_x)      \
  (int_opt, goto_y)      \
  (int_opt, hitpoints)      \
  (int_opt, hp_bar_scaling)    \
  (int_val, experience, 0)    \
  (int_opt, moves)      \
  (int_val, attacks_left, 1)    \
  (bool_val, resting, true)    \
  (string_opt, role)      \
  (string_opt, ai_special)    \
  (string_opt, facing)      \
  (string_opt, profile)      \
  (string_opt, small_profile)    \
  (int_opt, max_attacks)    \
  (int_opt, max_experience)    \
  (int_opt, max_hitpoints)    \
  (int_opt, max_moves)      \
  (bool_opt, animate)      \
  (string_opt, unit_description)  \
  (string_opt, description)

#define UNIT_CHILDREN \
  (unit_filter, filter_recall)    \
  (unit_status, status)      \
  (wml::raw_config, variables)    \
  (unit_modifications, modifications)  \
  (unit_ai, ai)        \
  (specials_tag, specials)      \
  (abilities_tag, abilities)

// complete
DECLARE_WML_TAG(unit,
  UNIT_ATTRIBUTES
  UNIT_CHILDREN);

// complete
DECLARE_WML_TAG(item,
  (int_val, x, 0)
  (int_val, y, 0)
  (string_val, image)
  (string_val, halo)
  (string_list_val, team_name)
  (bool_val, visible_in_fog, true)
  (bool_val, redraw, true));

// complete
DECLARE_WML_TAG(remove_item,
  (string_opt, image)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG_AND_NAME(time_tag, "time",
  (string_val, id)
  (string_val, name)
  (string_val, image)
  (string_opt, mask)
  (int_val, lawful_bonus, 0)
  (int_val, red, 0)
  (int_val, green, 0)
  (int_val, blue, 0)
  (string_opt, sound));

DECLARE_WML_TAG(time_area,
  LOCATION_FILTER_ATTRIBUTES
  (string_opt, id)
  (bool_val, remove, false)
  (int_val, current_time, 0)
  LOCATION_FILTER_CHILDREN
  (time_tag, time));

DECLARE_WML_TAG(end_level,
  (string_val, result)
  (bool_opt, bonus)
  (string_opt, next_scenario)
  (bool_val, carryover_report, true)
  (bool_val, replay_save, true)
  (bool_val, save, true)
  (bool_val, linger_mode, true)
  (bool_val, reveal_map, true)
  (int_opt, carryover_percentage)
  (int_opt, carryover_add)
  (string_list_val, music)
  (bool_val, credits, true)
  (string_opt, end_text)
  (int_opt, end_text_duration)
  );
//  (all_children_set, all))

DECLARE_WML_TAG(print_val,
  (string_val, text)
  (int_opt, red)
  (int_opt, green)
  (int_opt, blue)
  (int_val, size, 12)
  (int_val, duration, 50));

DECLARE_WML_TAG(lua, 
  (string_val, code));

DECLARE_WML_TAG(clear_variable,
  (string_val, name));

DECLARE_WML_TAG(set_variable_join,
  (string_val, variable)
  (string_val, key)
  (string_val, separator)
  (bool_opt, remove_empty));

DECLARE_WML_TAG(set_variable,
  (string_val, name)
  (string_opt, value)
  (string_opt, literal)
  (string_opt, to_variable)
  (string_opt, add)
  (string_opt, sub)
  (string_opt, multiply)
  (string_opt, divide)
  (string_opt, modulo)
  (string_opt, rand)
  (string_opt, time_stamp)
  (string_opt, string_length)
  (string_opt, ipart)
  (string_opt, fpart)
  (string_opt, round)
  (set_variable_join, join));

DECLARE_WML_TAG(set_variables_split,
  (string_opt, list)
  (string_val, key)
  (string_opt, separator)
  (bool_opt, remove_empty));

DECLARE_WML_TAG(set_variables,
  (string_val, name)
  (string_opt, mode)
  (string_opt, to_variable)
  (wml::raw_config, value)
  (wml::raw_config, literal)
  (set_variables_split, split));

DECLARE_WML_TAG(fire_event,
  (string_val, name)
  (unit_filter, primary_unit)
  (unit_filter, secondary_unit)
  (wml::raw_config, primary_attack)
  (wml::raw_config, secondary_attack));

DECLARE_WML_TAG(remove_event,
  (string_list_val, id));

DECLARE_WML_TAG(terrain_tag,
  (string_opt, layer)
  (bool_val, replace_if_failed, false)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(terrain_mask_rule_tag, );

DECLARE_WML_TAG(terrain_mask_tag,
  (string_val, mask)
  (bool_opt, border)
  (terrain_mask_rule_tag, rule));

DECLARE_WML_TAG(gold,
  (int_val, amount, 0)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(allow_recruit,
  (string_list_val, type)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);
 
DECLARE_WML_TAG(allow_extra_recruit,
  (string_list_val, extra_recruit)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(disallow_recruit,
  (string_list_val, type)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(disallow_extra_recruit,
  (string_list_val, extra_recruit)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(set_recruit,
  (string_list_val, recruit)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(set_extra_recruit,
  (string_list_val, extra_recruit)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(modify_side_ai, );

DECLARE_WML_TAG(modify_side,
  (int_opt, income)
  (int_opt, side)
  (int_opt, gold)
  (int_opt, village_gold)
  (string_list_val, recruit)
  (string_list_val, team_name)
  (string_opt, user_team_name)
  (string_opt, controller)
  (bool_opt, fog)
  (bool_opt, shroud)
  (bool_opt, hidden)
  (string_opt, color)
  (string_opt, switch_ai)
  (bool_opt, reset_maps)
  (bool_opt, reset_view)
  (bool_opt, share_maps)
  (bool_opt, share_view)
  (string_opt, shroud_data)
  (bool_opt, suppress_end_turn_confirmation)
  (bool_opt, scroll_to_leader)
  (int_opt, village_support)
  (modify_side_ai, ai)
  (side_filter, filter_side));

DECLARE_WML_TAG(modify_unit,
  UNIT_ATTRIBUTES
  (unit_filter, filter)
  (unit_modifications, modifications)
  (string_to_int_map, movement_costs)
  (string_to_int_map, resistances)
  (string_to_int_map, defense)
  (wml::raw_config, variables));

DECLARE_WML_TAG(store_unit,
  (bool_val, kill, false)
  (string_val, variable)
  (string_opt, mode)
  (unit_filter, filter));

DECLARE_WML_TAG(unstore_unit,
  (string_val, variable)
  (bool_val, find_vacant, false)
  (bool_val, check_passability, true)
  (string_opt, text)
  (int_val, red, 0)
  (int_val, blue, 0)
  (int_val, green, 0)
  (bool_val, advance, true)
  (bool_val, fire_event, false)
  (bool_val, animate, true)
  (string_opt, x)
  (string_opt, y));

DECLARE_WML_TAG(transform_unit,
  (string_opt, transform_to)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(harm_unit,
  (string_opt, alignment)
  (bool_opt, animate)
  (int_opt, amount)
  (string_opt, damage_type)
  (bool_opt, kill)
  (bool_opt, poisoned)
  (bool_opt, slowed)
  (unit_filter, filter)
  (unit_filter, filter_second)
  (attack_filter, primary_attack));

// TODO: fix this
DECLARE_WML_TAG(heal_unit,
  (string_opt, alignment)
  (bool_opt, animate)
  (int_opt, amount)
  (string_opt, damage_type)
  (bool_opt, kill)
  (bool_opt, poisoned)
  (bool_opt, slowed)
  (bool_opt, restore_statuses)
  (unit_filter, filter)
  (unit_filter, filter_second)
  (attack_filter, primary_attack));

DECLARE_WML_TAG(kill,
  (bool_val, animate, false)
  (bool_val, fire_event, false)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN
  (unit_filter, secondary_unit));

DECLARE_WML_TAG(move_unit,
  (int_opt, to_x)
  (int_opt, to_y)
  (bool_val, fire_event, false)
  (bool_val, check_passability, true)
  (bool_val, force_scroll, false));

DECLARE_WML_TAG(move_unit_fake,
  (string_val, type)
  (string_list_val, x)
  (string_list_val, y)
  (int_opt, side)
  (string_opt, gender)
  (string_opt, variation)
  (string_val, image_mods)
  (bool_val, force_scroll, false));

DECLARE_WML_TAG(move_units_fake_fake_unit,
  (string_val, type)
  (string_list_val, x)
  (string_list_val, y)
  (int_opt, side)
  (int_opt, skip_steps));

DECLARE_WML_TAG(move_units_fake,
);
//  move_units_fake_fake_unit, fake_unit)
// TODO: Fix ^

DECLARE_WML_TAG(teleport,
  (bool_val, clear_shroud, true)
  (bool_val, animate, true)
  (bool_val, check_passability, true)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

namespace wml { struct animate_unit; }

DECLARE_WML_TAG(animate_unit,
  (string_opt, flag)
  (string_val, hits)
  (string_val, text)
  (int_opt, red)
  (int_opt, green)
  (int_opt, blue)
  (bool_opt, with_bars)
  (unit_filter, filter)
  (attack_filter, primary_attack)
  (attack_filter, secondary_attack)
  (util::recursive_wrapper<wml::animate_unit>, animate)
  (location_filter, facing));

DECLARE_WML_TAG(recall,
  (bool_val, show, true)
  (bool_val, fire_event, false)
  (bool_val, check_passability, true)
  (bool_opt, animate)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(place_shroud,
  (int_opt, side)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(remove_shroud,
  (int_opt, side)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(lift_fog,
  (bool_val, multiturn, false)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN
  (side_filter, filter_side));

DECLARE_WML_TAG(reset_fog,
  (bool_val, reset_view, false)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN
  (side_filter, filter_side));

DECLARE_WML_TAG(redraw,
  (bool_val, clear_shroud, false)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

namespace wml { struct condition_tag; }

DECLARE_WML_TAG(objectives_objective,
  (string_val, condition)
  (string_val, description)
  (bool_opt, show_turn_counter)
  (util::recursive_wrapper<wml::condition_tag>, show_if));

DECLARE_WML_TAG(objectives_gold_carryover,
  (bool_opt, bonus)
  (int_opt, carryover_percentage));

DECLARE_WML_TAG(objectives_note,
  (string_val, description));

DECLARE_WML_TAG(objectives,
  (bool_opt, silent)
  (bool_opt, show)
  (int_opt, side)
  (string_val, summary)
  (util::recursive_wrapper<wml::condition_tag>, show_if)
  (objectives_objective, objective)
  (objectives_note, note)
  (objectives_gold_carryover, gold_carryover));

DECLARE_WML_TAG(show_objectives, );

DECLARE_WML_TAG(music,
  (string_val, name)
  (bool_val, play_once, true)
  (bool_val, immediate, false)
  (bool_val, append, true)
  (int_opt, ms_before));

DECLARE_WML_TAG(sound,
  (string_val, name));

DECLARE_WML_TAG(delay,
  (int_val, time, 0)
  (bool_val, accelerate, false));

DECLARE_WML_TAG(volume,
  (int_opt, music)
  (int_opt, sound));

DECLARE_WML_TAG(color_adjust,
  (int_opt, red)
  (int_opt, blue)
  (int_opt, green));

DECLARE_WML_TAG(scroll,
  (int_opt, x)
  (int_opt, y)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);

DECLARE_WML_TAG(scroll_to,
  (int_val, x, 0)
  (int_val, y, 0)
  SIDE_FILTER_ATTRIBUTES
  SIDE_FILTER_CHILDREN);
  
DECLARE_WML_TAG(scroll_to_unit,
  (bool_val, check_fogged, false)
  (bool_val, immediate, false)
//  (string_list_val, for_side)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN
  (side_filter, for_side));

// conditional wml definitions, for [if]

DECLARE_WML_TAG(true_tag, );
DECLARE_WML_TAG(false_tag, );

DECLARE_WML_TAG(have_unit,
  (int_opt, count)
  (bool_val, search_recall_list, false)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(have_location,
  (int_opt, count)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(variable_tag,
  (string_val, name)
  (string_opt, value)
  (string_opt, contains)
  (string_opt, equals)
  (string_opt, not_equals)
  (string_opt, numerical_equals)
  (string_opt, numerical_not_equals)
  (string_opt, greater_than)
  (string_opt, greater_than_equal_to)
  (string_opt, less_than)
  (string_opt, less_than_equal_to)
  (string_opt, boolean_equals)
  (string_opt, boolean_not_equals));

MAKE_HETEROGENOUS_SEQUENCE(conditional_wml,
  (wml::true_tag, "true")
  (wml::false_tag, "false")
  (wml::have_unit, "have_unit")
  (wml::have_location, "have_location")
  (wml::variable_tag, "variable")
  (util::recursive_wrapper<wml::condition_tag>, "or")
  (util::recursive_wrapper<wml::condition_tag>, "and")
  (util::recursive_wrapper<wml::condition_tag>, "not"))

DECLARE_WML_TAG(condition_tag,
  (conditional_wml, conditionals));

/*
We have to do if_tag manually because preprocessor really doesn't like to use 'else' as a token
DECLARE_WML_TAG(if_tag, 
  , //children
  (conditional_wml, conditionals)
  (util::recursive_wrapper<action_tag> , then)
  (util::recursive_wrapper<action_tag>, ELSE_WORD))
*/

namespace wml { struct action_tag; }
// action_tag is used to represent tags that can only hold actions_wml, like [then] [else] [command] etc.

namespace wml { static const char * const if_tag_child_then_tag_key = "then"; }
namespace wml { static const char * const if_tag_child_else_tag_key = "else"; }
namespace wml { typedef child_vector<util::recursive_wrapper<action_tag>, &if_tag_child_then_tag_key> if_tag_child_then_type; }
namespace wml { typedef child_vector<util::recursive_wrapper<action_tag>, &if_tag_child_else_tag_key> if_tag_child_else_type; }
BOOST_FUSION_DEFINE_STRUCT( (wml), if_tag,
  (conditional_wml, conditionals)
  (wml::if_tag_child_then_type, then_children)
  (wml::if_tag_child_else_type, else_children))

namespace wml { struct case_tag; }

namespace wml { static const char * const switch_tag_variable_key = "variable"; }
namespace wml { static const char * const switch_tag_child_case_tag_key = "case"; }
namespace wml { static const char * const switch_tag_child_else_tag_key = "else"; }
namespace wml { typedef child_vector<util::recursive_wrapper<case_tag>, &switch_tag_child_case_tag_key> switch_tag_child_case_type; }
namespace wml { typedef child_vector<util::recursive_wrapper<action_tag>, &switch_tag_child_else_tag_key> switch_tag_child_else_type; }
BOOST_FUSION_DEFINE_STRUCT( (wml), switch_tag,
  (string_val< & wml::switch_tag_variable_key >, variable)
  (wml::switch_tag_child_case_type, case_children)
  (wml::switch_tag_child_else_type, else_children))

namespace wml { struct while_tag; }

namespace wml { static const char * const while_tag_child_do_key = "do"; }
namespace wml { typedef child_vector<util::recursive_wrapper<action_tag>, &while_tag_child_do_key> while_tag_child_do_type; }
BOOST_FUSION_DEFINE_STRUCT( (wml), while_tag,
  (conditional_wml, conditionals)
  (wml::while_tag_child_do_type, do_children))

DECLARE_WML_TAG(message_option,
  (string_val, message)
  (condition_tag, show_if)
  (util::recursive_wrapper<action_tag>, command));

DECLARE_WML_TAG(message_text_input,
  (string_val, variable)
  (string_opt, label)
  (int_opt, max_text_length)
  (string_opt, text));

DECLARE_WML_TAG(message_tag,
  (string_opt, image)
  (string_opt, message)
  (string_opt, caption)
  (int_opt, duration)
  (string_opt, side_for)
  (bool_def_true, scroll)
  (string_opt, sound)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN
  (condition_tag, show_if)
  (message_option, option)
  (message_text_input, text_input));
  
/***
 * Declare action_wml
 */
DECLARE_WML_TAG(end_turn, );

DECLARE_WML_TAG(object,
  (bool_opt, silent)
  (string_opt, description)
  (string_opt, image)
  (string_opt, duration)
  (string_opt, name)
  (string_opt, id)
  (unit_filter, filter)
  (effect_tag, effect));

DECLARE_WML_TAG(capture_village,
  (int_opt, side)
  (bool_val, fire_event, false)
  LOCATION_FILTER_ATTRIBUTES
  LOCATION_FILTER_CHILDREN);

DECLARE_WML_TAG(allow_undo,);

DECLARE_WML_TAG(lock_view, );
DECLARE_WML_TAG(unlock_view, );
DECLARE_WML_TAG(micro_ai,
  (string_opt, action)
  (string_opt, ai_type)
  (string_opt, side)
  (string_opt, weapon)
  (int_opt, waypoint_x)
  (int_opt, waypoint_y)
  (bool_opt, injured_units_only)
  (unit_filter, filter)
  (unit_filter, filter_second)
  (location_filter, filter_location)
  (location_filter, filter_location_wander));

DECLARE_WML_TAG(unit_overlay,
  (string_val, image)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(remove_unit_overlay,
  (string_val, image)
  UNIT_FILTER_ATTRIBUTES
  UNIT_FILTER_CHILDREN);

DECLARE_WML_TAG(set_menu_item,
  (string_val, id)
  (string_opt, description)
  (string_opt, icon)
  (wml::condition_tag, show_if)
  (util::recursive_wrapper<wml::action_tag>, command));

DECLARE_WML_TAG(spawn_units,)

namespace wml { struct event; }

MAKE_HETEROGENOUS_SEQUENCE(action_wml,
  (util::recursive_wrapper<wml::event>, "event" )
  (util::recursive_wrapper<wml::action_tag>, "command")
  (wml::if_tag, "if")
  (wml::while_tag, "while")
  (wml::switch_tag, "switch")
  (wml::set_variable, "set_variable")
  (wml::set_variables, "set_variables")
  (wml::clear_variable, "clear_variable")
  (wml::allow_recruit, "allow_recruit")
  (wml::disallow_recruit, "disallow_recruit")
  (wml::set_recruit, "set_recruit")
  (wml::allow_extra_recruit, "allow_extra_recruit")
  (wml::disallow_extra_recruit, "disallow_extra_recruit")
  (wml::set_extra_recruit, "set_extra_recruit")
  (wml::recall, "recall")
  (wml::gold, "gold")
  (wml::message_tag, "message")
  (wml::store_unit, "store_unit")
  (wml::unstore_unit, "unstore_unit")
  (wml::transform_unit, "transform_unit")
  (wml::unit_overlay, "unit_overlay")
  (wml::remove_unit_overlay, "remove_unit_overlay")
  (wml::kill, "kill")
  (wml::harm_unit, "harm_unit")
  (wml::heal_unit, "heal_unit")
  (wml::move_unit, "move_unit")
  (wml::move_unit_fake, "move_unit_fake")
  (wml::move_units_fake, "move_units_fake")
  (wml::spawn_units, "spawn_units")
  (wml::store_gold, "store_gold")
  (wml::store_locations, "store_locations")
  (wml::store_side, "store_side")
  (wml::store_starting_locations, "store_starting_locations")
  (wml::store_time_of_day, "store_time_of_day")
  (wml::store_villages, "store_villages")
  (wml::store_turns, "store_turns")
  (wml::modify_turns, "modify_turns")
  (wml::end_level, "endlevel")
  (wml::end_turn, "end_turn")
  (wml::capture_village, "capture_village")
  (wml::teleport, "teleport")
  (wml::music, "music")
  (wml::sound, "sound")
  (wml::volume, "volume")
  (wml::delay, "delay")
  (wml::color_adjust, "color_adjust")
  (wml::scroll, "scroll")
  (wml::scroll_to, "scroll_to")
  (wml::scroll_to_unit, "scroll_to_unit")
  (wml::print, "print")
  (wml::terrain_tag, "terrain")
  (wml::terrain_mask_tag, "terrain_mask")
  (wml::modify_side, "modify_side")
  (wml::modify_unit, "modify_unit")
  (wml::unit_filter, "petrify")
  (wml::unit_filter, "unpetrify")
  (wml::unit_filter, "hide_unit")
  (wml::unit_filter, "unhide_unit")
  (wml::objectives, "objectives")
  (wml::show_objectives, "show_objectives")
  (wml::lua, "lua")
  (wml::fire_event, "fire_event")
  (wml::remove_event, "remove_event")
  (wml::label, "label")
  (wml::time_area, "time_area")
  (wml::unit, "unit")
  (wml::object, "object")
  (wml::item, "item")
  (wml::remove_item, "remove_item")
  (wml::place_shroud, "place_shroud")
  (wml::remove_shroud, "remove_shroud")
  (wml::lift_fog, "lift_fog")
  (wml::reset_fog, "reset_fog")
  (wml::allow_undo, "allow_undo")
  (wml::lock_view, "lock_view")
  (wml::unlock_view, "unlock_view")
  (wml::teleport, "teleport")
  (wml::redraw, "redraw")
  (wml::unit_filter, "role")
  (wml::animate_unit, "animate_unit")
  (wml::micro_ai, "micro_ai")
  (wml::set_menu_item, "set_menu_item"))

DECLARE_WML_TAG(action_tag,
  (action_wml, actions));

DECLARE_WML_TAG(case_tag,
  (string_list_val, value)
  (action_wml, actions));

DECLARE_WML_TAG(event,
  (string_val, name)
  (string_val, id)
  (string_opt, remove)
  (bool_val, first_time_only, true)
  (bool_val, delayed_variable_substitution, true)
  (unit_filter, filter)
  (unit_filter, filter_second)
  (attack_filter, filter_attack)
  (attack_filter, filter_second_attack)
  (side_filter, filter_side)
  (condition_tag, filter_condition)
  (action_wml, action_wml));

/** [terrain_type] **/
DECLARE_WML_TAG(terrain_type,
  (string_val, symbol_image)
  (string_val, editor_image)
  (string_val, editor_group)
  (string_val, id)
  (string_val, name)
  (string_val, description)
  (string_val, editor_name)
  (string_val, string)
  (int_val, light, 0)
  (int_val, min_light, 0)
  (int_val, max_light, 0)
  (int_opt, unit_height_adjust)
  (bool_opt, heals)
  (bool_opt, submerge)
  (bool_opt, no_overlay)
  (bool_val, gives_income, false)
  (bool_val, recruit_onto, false)
  (bool_val, recruit_from, false)
  (string_val, aliasof)
  (string_val, def_alias)
  (string_val, mvt_alias)
  (bool_val, hidden, false)
  (bool_val, hide_help, false));

/** [terrain_graphics] **/

DECLARE_WML_TAG(terrain_graphics_tile_image_variant,
  (string_list_val, tod)
  (string_opt, name)
  (bool_val, random_start, true)
  (string_list_val, has_flag));


DECLARE_WML_TAG(terrain_graphics_tile_image,
  (int_val, layer, 0)
  (string_opt, name)
  (bool_val, random_start, true)
  (int_pair_opt, base)
  (terrain_graphics_tile_image_variant, variant));

DECLARE_WML_TAG(terrain_graphics_tile,
  (int_opt, x)
  (int_opt, y)
  (int_opt, pos)
  (string_list_val, type)
  (string_opt, name)
  (string_list_val, set_flag)
  (string_list_val, has_flag)
  (string_list_val, no_flag)
  (string_list_val, set_no_flag)
  (terrain_graphics_tile_image, image));

DECLARE_WML_TAG(terrain_graphics_image,
  (int_val, layer, 0)
  (string_opt, name)
  (bool_val, random_start, true)
  (int_pair_opt, base)
  (int_pair_opt, center));

DECLARE_WML_TAG(terrain_graphics,
  (int_opt, x)
  (int_opt, y)
  (int_opt, mod_x)
  (int_opt, mod_y)
  (int_val, probability, 100)
  (string_list_val, rotations)
  (string_list_val, set_flag)
  (string_list_val, has_flag)
  (string_list_val, no_flag)
  (string_list_val, set_no_flag)
  (string_opt, map)
  (terrain_graphics_tile, tile)
  (terrain_graphics_image, image));

/*** [units] ***/

/***** helpers *****/

#define MOVE_TYPE_CHILDREN \
  (string_to_int_map, movement_costs)  \
  (string_to_int_map, vision_costs)  \
  (string_to_int_map, defense)    \
  (string_to_int_map, resistance)

/***** [unit_type] *****/

DECLARE_WML_TAG(unit_type_advancement,
  (string_val, id)
  (bool_val, always_display, false)
  (string_val, description)
  (string_val, image)
  (int_val, max_times, 1)
  (bool_val, strict_amla, false)
  (string_list_val, require_amla)
  (effect_tag, effect));

DECLARE_WML_TAG(unit_type_attack,
  (string_opt, description)
  (string_val, name)
  (string_val, type)
  (string_val, icon)
  (string_val, range)
  (int_val, damage, 0)
  (int_val, number, 0)
  (int_opt, movement_used)
  (int_opt, attack_weight)
  (int_opt, defense_weight)
  (abilities_tag, abilities)
  (specials_tag, specials));

DECLARE_WML_TAG(unit_type_portrait, );

#define UNIT_TYPE_COMMON_ATTRS    \
  (string_list_val, advances_to)  \
  (string_opt, alignment)    \
  (int_opt, attacks)      \
  (int_val, cost, 0)      \
  (string_val, description)    \
  (string_val, ellipse)      \
  (int_val, experience, 1)    \
  (string_val, flag_rgb)    \
  (string_val, gender)      \
  (string_opt, halo)      \
  (bool_val, hide_help, false)    \
  (int_def_one, hitpoints)    \
  (string_val, id)      \
  (bool_val, ignore_race_traits, false)  \
  (string_val, image)      \
  (string_val, image_icon)    \
  (int_val, level, 0)      \
  (int_val, movement, 0)    \
  (string_opt, movement_type)    \
  (string_opt, name)      \
  (int_opt, num_traits)      \
  (string_opt, portrait)    \
  (string_opt, profile)      \
  (string_opt, small_portrait)    \
  (string_val, race)      \
  (string_opt, undead_variation)  \
  (string_opt, usage)      \
  (int_opt, vision)      \
  (bool_opt, zoc)      \
  (string_opt, die_sound)    \
  (string_opt, heal_sound)

#define UNIT_TYPE_COMMON_CHILDREN \
  (event, event) \
  MOVE_TYPE_CHILDREN \
  (animation_tag, movement_anim) \
  (animation_tag, attack_anim) \
  (animation_tag, defend) \
  (animation_tag, death)  \
  (animation_tag, healing_anim)  \
  (animation_tag, idle_anim)  \
  (animation_tag, leading_anim)  \
  (animation_tag, recruiting_anim) \
  (animation_tag, standing_anim) \
  (abilities_tag, abilities) \
  (unit_type_advancement, advancement) \

//  (unit_type_portrait, portrait)

DECLARE_WML_TAG(unit_type_base_unit,
  UNIT_TYPE_COMMON_ATTRS
  UNIT_TYPE_COMMON_CHILDREN);

DECLARE_WML_TAG(unit_type_variation,
  (string_val, variation_id)
  (string_val, variation_name)
  (bool_def_false, inherit)
  UNIT_TYPE_COMMON_ATTRS
  UNIT_TYPE_COMMON_CHILDREN
  (unit_type_attack, attack));

DECLARE_WML_TAG(unit_type_gender_variation,
  (bool_def_true, inherit)
  UNIT_TYPE_COMMON_ATTRS
  UNIT_TYPE_COMMON_CHILDREN
  (unit_type_attack, attack)
  (unit_type_variation, variation));

DECLARE_WML_TAG(unit_type,
  (bool_def_false, do_not_list)
  UNIT_TYPE_COMMON_ATTRS
  UNIT_TYPE_COMMON_CHILDREN
  (animation_tag, animation)
  (unit_type_attack, attack)
  (unit_type_base_unit, base_unit)
  (unit_type_variation, variation)
  (unit_type_gender_variation, male)
  (unit_type_gender_variation, female));


/***** [move_type] *****/

DECLARE_WML_TAG(move_type,
  (string_val, id)
  (string_opt, name)
  (bool_val, flies, 0)
  MOVE_TYPE_CHILDREN);

/***** [race] *****/

DECLARE_WML_TAG(race,
  (string_val, id)
  (string_val, plural_name)
  (string_opt, male_name)
  (string_opt, female_name)
  (string_opt, name)
  (string_val, description)
  (string_list_val, male_names)
  (string_list_val, female_names)
  (int_val, markov_chain_size, 2)
  (int_val, num_traits, 2)
  (bool_val, ignore_global_traits, false)
  (string_opt, undead_variation)
  (trait, trait));

/***** units *****/

DECLARE_WML_TAG(units, 
  (unit_type, unit_type)
  (trait, trait)
  (move_type, movetype)
  (race, race));

/*** scenario ***/

DECLARE_WML_TAG(village,
  (int_val, x, 0)
  (int_val, y, 0));

DECLARE_WML_TAG(side_ai_aspect,
  (string_val, id)
  (wml::raw_config, facet));

DECLARE_WML_TAG(side_ai_goal,
  (string_val, name)
  (int_opt, value)
  (int_opt, protect_radius)
  (wml::raw_config, criteria));

DECLARE_WML_TAG(side_ai,
  (int_opt, villages_per_scout)
  (int_opt, village_value)
  (int_opt, aggression)
  (string_opt, recruitment_pattern)
  (string_opt, ai_algorithm)
  (int_opt, caution)
  (int_opt, leader_value)
  (int_opt, attack_depth)
  (string_opt, grouping)
  (string_opt, time_of_day)
  (bool_val, passive_leader, false)
  (bool_val, passive_leader_shares_keep, false)
  (int_opt, leader_aggression)
  (int_opt, scout_village_targeting)
  (bool_val, simple_targeting, false)
  (bool_val, recruitment_ignore_bad_movement, false)
  (bool_val, recruitment_ignore_bad_combat, false)
//  (bool_def_false, recruitment_ignore_bad_recruit)
  (int_opt, turns)
  (wml::raw_config, attacks)
  (wml::raw_config, avoid)
  (side_ai_goal, goal)
  (side_ai_aspect, aspect)
  (wml::raw_config, leader_goal));

DECLARE_WML_TAG(side_tag,
//  (swallow_attribute, controler)
  (string_val, controller)
  (string_opt, ai_algorithm)
  (bool_val, no_leader, false)
  (string_list_val, recruit)
  (int_val, gold, 100)
  (int_val, income, 0)
  (bool_val, hidden, false)
  (bool_val, fog, true)
  (bool_val, shroud, true)
  (bool_opt, persistent)
  (string_opt, save_id)
  (string_list_val, team_name)
  (string_val, user_team_name)
  (string_val, current_player)
  (string_opt, color)
  (string_opt, flag)
  (string_opt, flag_icon)
  (int_opt, village_gold)
  (bool_val, share_maps, false)
  (bool_val, share_view, false)
  (bool_val, share_vision, false)
  (bool_val, scroll_to_leader, true)
  (bool_val, suppress_end_turn_confirmation, false)
  (string_opt, image)
  (string_val, defeat_condition)
  (bool_val, allow_player, true)
  (bool_val, disallow_observers, false)
  (bool_val, disallow_shuffle, false)
  (bool_opt, faction_from_recruit)
  (bool_opt, gold_lock)
  (bool_opt, income_lock)
  (bool_opt, team_lock)
  UNIT_ATTRIBUTES
  (side_ai, ai)
  (side_ai_goal, goal)
  (village, village)
  (unit, unit)
  (unit, leader)
  (unit_modifications, modifications)
  (wml::raw_config, variables));

DECLARE_WML_TAG(scenario, 
  (string_val, id)
  (swallow_attribute, snapshot)
  (string_opt, next_scenario)
  (string_opt, description)
  (string_opt, name)
  (string_opt, map_data)
  (string_opt, define)
  (int_val, turns, -1)
  (int_val, turns_at, 1)
  (string_list_val, random_start_time)
  (string_list_val, defeat_music)
  (string_list_val, victory_music)
  (string_val, theme)
  (bool_val, victory_when_enemies_defeated, true)
  (int_opt, bonus)
  (int_val, carryover_percentage, 80)
  (bool_val, carryover_add, true)
  (bool_val, remove_from_carryover_on_defeat, true)
  (bool_val, disallow_recall, false)
  (int_val, experience_modifier, 100)
  (int_opt, current_time)
  (string_opt, scenario_generation)
  (string_opt, map_generation)
  (label, label)
  (item, item)
  (time_tag, time)
  (time_area, time_area)
  (side_tag, side)
  (event, event)
  (music, music)
  (wml::raw_config, story)
  (wml::raw_config, generator));

/** [binary_path] **/

DECLARE_WML_TAG(binary_path,
  (string_val, path));

DECLARE_WML_TAG(top_level, 
  (scenario, scenario)
  (scenario, multiplayer)
  (scenario, test)
  (scenario, tutorial)
  (units, units)
  (terrain_type, terrain_type)
  (terrain_graphics, terrain_graphics)
  (binary_path, binary_path)
  (unit_type, unit_type)
  (move_type, movetype)
  (event, event));
