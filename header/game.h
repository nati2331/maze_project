#ifndef GAME_H
#define GAME_H

// Screen and Map dimensions
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 600
#define TILE_SIZE 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define MINIMAP_SCALE 0.25

// Game constants
#define GUN_SCALE 0.35
#define PI 3.14159265
#define HALF_PI (PI / 2)
#define ONE_HALF_PI (3 * PI / 2)
#define DEGREE_TO_RAD 0.0174533
#define FOV_ANGLE (PI / 3)
#define RAD_TO_DEGREE 57.296
#define NUM_RAYS 60
#define NUM_ENEMIES 5

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

// SDL_Instance: Represents the SDL window and renderer
typedef struct SDL_Instance {
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

// KeyInputs: Structure for handling keyboard inputs
typedef struct KeyInputs {
    int w, a, s, d, e, x;
} KeyInputs;

// Player: Represents the player in the game
typedef struct Player {
    float x, y, width, height, angle;
    float dx, dy;
} Player;

extern Player player;

// Enemy: Represents an enemy in the game
typedef struct Enemy {
    float x, y, z;
    char *texturePath;
} Enemy;

extern Enemy enemy;
extern float zBuffer[NUM_RAYS];

// Function declarations

/** main.c **/
void initialize_game(void);
void render(SDL_Instance instance);

/** input.c **/
int process_events(SDL_Instance instance);
void on_key_down(SDL_Instance instance);
void on_key_up(SDL_Event event);
void on_key_press(SDL_Event event);
void handle_door_interaction(void);

/** window.c **/
int initialize_SDL(SDL_Instance *instance);
float adjust_angle(float angle);

/** draw.c **/
void render_player(SDL_Instance instance);
void draw_map(SDL_Instance instance);
void render_scene(SDL_Instance instance, int n, float height, float rayAngle, 
                  float shade, float rayX, float rayY, int textureIndex);
void draw_floor(SDL_Instance instance, float lineOffset, int n, float lineHeight, float rayAngle);
void draw_ceiling(SDL_Instance instance, float lineOffset, int n, float lineHeight, float rayAngle);

/** cast.c **/
void cast_rays(SDL_Instance instance);
int check_wall_collision(float rayX, float rayY);
void handle_horizontal_collision(float rayAngle, float *distance, float *hitX, float *hitY, int *hitFlag);
void handle_vertical_collision(float rayAngle, float *distance, float *hitX, float *hitY, int *hitFlag);
float calculate_distance(float ax, float ay, float bx, float by);

/** sprite.c **/
void render_weapon(SDL_Instance instance);
void render_enemies(SDL_Instance instance);
float calculate_view_distance(void);
void draw_sprite_minimap(SDL_Instance instance);
void sort_sprites(int *spriteOrder, double *spriteDistances, int spriteCount);

/** texture.c **/
float get_texture_offset(int index);

/** map.c **/
void set_map_value(int mapX, int mapY, int value);
int get_map_value(int x, int y, int mapScale);
void free_2d_array(int **array);
void load_map(char **argv);

/** parser.c **/
int string_to_int(char *str);
char *duplicate_string(char *str);
int string_length(char *str);
int **parse_map_data(char **argv);
char **split_string(char *str, char *delimiter);

/** cleanup.c **/
void free_point_grid(SDL_Point ***grid);
void free_string_array(char **array);
void free_3d_string_array(char ***array);
void free_2d_int_array(int **array);

#endif /* GAME_H */
