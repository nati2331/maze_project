import pygame
import sys
from src.player import Player
from src.enemy import Enemy
from src.maze import Maze
from src.raycasting import Raycasting
from src.collision import check_collision_with_walls
from src.mapping import create_map_surface
from src.utils import draw_health

pygame.init()

# Screen dimensions
WIDTH, HEIGHT = 640, 480
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

# Load images
WALL_IMAGE = pygame.image.load("images/wall.jpg")
FLOOR_IMAGE = pygame.image.load("images/floor.jpg")
PLAYER_IMAGE = pygame.image.load("images/player.png")
ENEMY_IMAGE = pygame.image.load("images/enemy.png")

# Load maze
maze = Maze("maze.txt")

# Initialize player and enemies
player = Player(maze.start_position(), PLAYER_IMAGE)
enemies = [Enemy(x, y, ENEMY_IMAGE) for x, y in maze.enemy_positions()]

# Main game loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()
    if keys[pygame.K_ESCAPE]:
        running = False

    player.update(keys)
    check_collision_with_walls(player, maze)

    for enemy in enemies:
        enemy.move_towards_player(player.x, player.y)
        if enemy.check_collision_with_player(player.x, player.y):
            player.health -= 1
            if player.health <= 0:
                print("Game Over")
                running = False

    # Rendering
    screen.fill((0, 0, 0))
    map_surface = create_map_surface(player, maze, WALL_IMAGE, FLOOR_IMAGE)
    screen.blit(map_surface, (0, 0))
    for enemy in enemies:
        screen.blit(enemy.image, (enemy.x, enemy.y))
    screen.blit(player.image, (player.x, player.y))
    draw_health(screen, player.health)
    pygame.display.flip()

    clock.tick(60)

pygame.quit()
sys.exit()
