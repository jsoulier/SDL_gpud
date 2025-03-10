#ifndef SDL_GPUD_H
#define SDL_GPUD_H

#include <SDL3/SDL.h>

#ifdef __cplusplus
extern "C"
{
#endif /* ifdef __cplusplus */

bool SDL_InitGPUD(
    SDL_GPUDevice* device,
    SDL_GPUTextureFormat color_texture_format,
    SDL_GPUTextureFormat depth_texture_format);
void SDL_QuitGPUD();

#ifdef __cplusplus
} /* extern "C" */
#endif /* ifdef __cplusplus */

#ifdef SDL_GPUD_IMPL