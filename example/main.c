#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sdl_gpud.h>

static SDL_Window* window;
static SDL_GPUDevice* device;

static bool init(
    const char* driver)
{
    char name[256] = {0};
    snprintf(name, sizeof(name), "sdl_gpud_%s", driver);
    SDL_SetAppMetadata(name, NULL, NULL);
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    if (!(window = SDL_CreateWindow(name, 1024, 768, SDL_WINDOW_RESIZABLE)))
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    if (!(device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV |
        SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, driver)))
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    if (!SDL_ClaimWindowForGPUDevice(device, window))
    {
        SDL_Log("Failed to create swapchain: %s", SDL_GetError());
        return false;
    }
    if (!SDL_InitGPUD(device, SDL_GetGPUSwapchainTextureFormat(device, window),
        SDL_GPU_TEXTUREFORMAT_D32_FLOAT))
    {
        SDL_Log("Failed to initialize SDL GPUD: %s", SDL_GetError());
        return false;
    }
    return true;
}

static bool poll()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            return false;
        }
    }
    return true;
}

int main(
    int argc,
    char** argv)
{
    if (argc < 2)
    {
        SDL_Log("Invalid arguments. Usage: ./sdl_gpud.exe <driver>");
        return EXIT_FAILURE;
    }
    if (!init(argv[1]))
    {
        SDL_Log("Fatal error occurred. Aborting");
        return EXIT_FAILURE;
    }
    while (poll())
    {
    }
    SDL_QuitGPUD();
    SDL_ReleaseWindowFromGPUDevice(device, window);
    SDL_DestroyGPUDevice(device);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}