

#ifndef _TNASDK_H_
#define _TNASDK_H_ value

#include <common.h>
#include <movement.h>
#include <transform.h>
#include <terrain.h>

namespace tnasdk {

class CollisionEngine;
class Unit;

extern CollisionEngine* cengine;
extern float_t          bat_xmin;
extern float_t          bat_ymin;
extern float_t          bat_xmax;
extern float_t          bat_ymax;

////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

/**
 * @brief Initializes the tnasdk
 *
 * @param cengine A pointer to a CollisionEngine proviging physical functionaliy 
 * @param bwidth  The width of the battlefield in inches
 * @param bheight The height of the battlefield in inches
 */
void init_tnasdk( CollisionEngine* cengine, float_t bwidth, float_t bheight );

/**
 * @brief Releases the resources acquired by tnasdk
 */
void release_tnasdk();

/**
 * @brief Creates a unit
 *
 * @param troop_type The troop type of the unit
 * @param num_ranks The number of ranks of the unit
 * @param num_files The number of files of the unit
 * @param troop_width The width of the troops forming the unit in inches
 * @param troop_height The height of the troops forming the unit in inches
 *
 * @return  Returns a newly created unit
 */
Unit* create_unit(TroopType troop_type,
                  int32_t num_ranks, 
                  int32_t num_files,
                  float_t troop_width,
                  float_t troop_height);

/**
 * @brief Destroys a given unit
 *
 * @param unit The unit to destroy
 */
void destroy_unit(Unit* unit);

/**
 * @brief Creates a terrain
 *
 * @param type The type of terrain
 * @param width The width of the terrain
 * @param height The height of the terrain
 *
 * @return Returns and instance of a terrain
 */
Terrain* create_terrain( TerrainFeature type, float_t width, float_t height );

/**
 * @brief Destroys a terrain
 *
 * @param terrain The terrain to destroy
 */
void destroy_terrain(Terrain* terrain);

/**
 * @brief Adds a bfobject to the battlefield
 *
 * @param object The bfobject to add
 * @param position A Vector2f indicating the position of the bfobject 
 * @param rotation The rotation angle indicating the orientation of the bfobject
 * @return True if the bfobject can be added to the given position and orientation
 */
bool_t deploy( BFObject* object, Vector2f position, float_t rotation );


/**
 * @brief  Removes a unit from the battlefield
 *
 * @param unit The unit to remove
 */
void remove( BFObject* unit );


/**
 * @brief Starts a movement of the given unit from its current position and
 * rotation
 *
 * @param unit The unit to move
 * @param marching Wether the unit is performing a marching move
 *
 * @return A movement struct representing the characteristics of the initiated
 * movement
 */
Movement start_movement(Unit* unit, bool_t marching);

/**
 * @brief Tests whether the unit can end its movemnet in the given position and
 * rotaiton. 
 *
 * @param unit The unit ending the movement
 * @param movement The movement struct storing the movement information 
 * @param position The position to end the movement of the unit at
 * @param rotation The rotation to end the movemnet of the unit with
 *
 * @return Returns true if the unit can end the movement in the given position
 */
bool_t end_movement( const Movement& movement, 
                     Vector2f position, 
                     float_t rotation );

/**
 * @brief Tells if the given position and rotation are valid for the given
 * object
 *
 * @param object The object to test the position and rotation for
 * @param position A Vector2f indicating the position of the object 
 * @param rotation The rotation angle indicating the orientation of the object
 *
 * @return Returns true if the pair <poisition,rotations> configures a valid
 * placement for the given object
 */
bool_t is_valid( BFObject* object, Vector2f position, float_t rotation );

/**
 * @brief Tests whether there is line of sight between two units
 *
 * @param from The unit performing the line of sight test from
 * @param to The unit performing the line of sight to
 *
 * @return Returns true if there is line of sight between the from unit to the
 * to unit
 */
bool_t los( const Unit* from, const Unit* to );

} /* tnasdk */ 


#endif /* ifndef _TNASDK_H_ */
