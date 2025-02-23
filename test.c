# include "MLX42/MLX42.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 500

int main(void)
{
    mlx_t *mlx_ptr;

    // Initialize the MLX42 library and create the window at the same time
    mlx_ptr = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!", false);

    // Start the event loop to display the window
    mlx_loop(mlx_ptr);

    // Terminate MLX42 after closing the window
    mlx_terminate(mlx_ptr);

    return 0;
}