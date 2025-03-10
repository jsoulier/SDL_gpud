#ifndef SDL_GPUD_H
#define SDL_GPUD_H

#include <SDL3/SDL.h>

#ifndef __cplusplus
#define SDL_GPUD_COLOR(r,g,b,a) &(SDL_FColor){r,g,b,a}
#else
#define SDL_GPUD_COLOR(r,g,b,a) {r,g,b,a}
#endif /* ifndef __cplusplus */
#define SDL_GPUD_ALICE_BLUE             SDL_GPUD_COLOR(0.941176f, 0.972549f, 1.000000f, 1.0f)
#define SDL_GPUD_ANTIQUE_WHITE          SDL_GPUD_COLOR(0.980392f, 0.921569f, 0.843137f, 1.0f)
#define SDL_GPUD_AQUAMARINE             SDL_GPUD_COLOR(0.498039f, 1.000000f, 0.831373f, 1.0f)
#define SDL_GPUD_AZURE                  SDL_GPUD_COLOR(0.941176f, 1.000000f, 1.000000f, 1.0f)
#define SDL_GPUD_BEIGE                  SDL_GPUD_COLOR(0.960784f, 0.960784f, 0.862745f, 1.0f)
#define SDL_GPUD_BISQUE                 SDL_GPUD_COLOR(1.000000f, 0.894118f, 0.768627f, 1.0f)
#define SDL_GPUD_BLACK                  SDL_GPUD_COLOR(0.000000f, 0.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_BLANCHED_ALMOND        SDL_GPUD_COLOR(1.000000f, 0.921569f, 0.803922f, 1.0f)
#define SDL_GPUD_BLUE                   SDL_GPUD_COLOR(0.000000f, 0.000000f, 1.000000f, 1.0f)
#define SDL_GPUD_BLUE_VIOLET            SDL_GPUD_COLOR(0.541176f, 0.168627f, 0.886275f, 1.0f)
#define SDL_GPUD_BROWN                  SDL_GPUD_COLOR(0.647059f, 0.164706f, 0.164706f, 1.0f)
#define SDL_GPUD_BURLYWOOD              SDL_GPUD_COLOR(0.870588f, 0.721569f, 0.529412f, 1.0f)
#define SDL_GPUD_CADET_BLUE             SDL_GPUD_COLOR(0.372549f, 0.619608f, 0.627451f, 1.0f)
#define SDL_GPUD_CHARTREUSE             SDL_GPUD_COLOR(0.498039f, 1.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_CHOCOLATE              SDL_GPUD_COLOR(0.823529f, 0.411765f, 0.117647f, 1.0f)
#define SDL_GPUD_CORAL                  SDL_GPUD_COLOR(1.000000f, 0.498039f, 0.313726f, 1.0f)
#define SDL_GPUD_CORNFLOWER_BLUE        SDL_GPUD_COLOR(0.392157f, 0.584314f, 0.929412f, 1.0f)
#define SDL_GPUD_CORNSILK               SDL_GPUD_COLOR(1.000000f, 0.972549f, 0.862745f, 1.0f)
#define SDL_GPUD_CRIMSON                SDL_GPUD_COLOR(0.862745f, 0.078431f, 0.235294f, 1.0f)
#define SDL_GPUD_CYAN                   SDL_GPUD_COLOR(0.000000f, 1.000000f, 1.000000f, 1.0f)
#define SDL_GPUD_DARK_BLUE              SDL_GPUD_COLOR(0.000000f, 0.000000f, 0.545098f, 1.0f)
#define SDL_GPUD_DARK_CYAN              SDL_GPUD_COLOR(0.000000f, 0.545098f, 0.545098f, 1.0f)
#define SDL_GPUD_DARK_GOLDENROD         SDL_GPUD_COLOR(0.721569f, 0.525490f, 0.043137f, 1.0f)
#define SDL_GPUD_DARK_GRAY              SDL_GPUD_COLOR(0.662745f, 0.662745f, 0.662745f, 1.0f)
#define SDL_GPUD_DARK_GREEN             SDL_GPUD_COLOR(0.000000f, 0.392157f, 0.000000f, 1.0f)
#define SDL_GPUD_DARK_KHAKI             SDL_GPUD_COLOR(0.741176f, 0.717647f, 0.419608f, 1.0f)
#define SDL_GPUD_DARK_MAGENTA           SDL_GPUD_COLOR(0.545098f, 0.000000f, 0.545098f, 1.0f)
#define SDL_GPUD_DARK_OLIVE_GREEN       SDL_GPUD_COLOR(0.333333f, 0.419608f, 0.184314f, 1.0f)
#define SDL_GPUD_DARK_ORANGE            SDL_GPUD_COLOR(1.000000f, 0.549020f, 0.000000f, 1.0f)
#define SDL_GPUD_DARK_ORCHID            SDL_GPUD_COLOR(0.600000f, 0.196078f, 0.800000f, 1.0f)
#define SDL_GPUD_DARK_RED               SDL_GPUD_COLOR(0.545098f, 0.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_DARK_SALMON            SDL_GPUD_COLOR(0.913725f, 0.588235f, 0.478431f, 1.0f)
#define SDL_GPUD_DARK_SEA_GREEN         SDL_GPUD_COLOR(0.560784f, 0.737255f, 0.560784f, 1.0f)
#define SDL_GPUD_DARK_SLATE_BLUE        SDL_GPUD_COLOR(0.282353f, 0.239216f, 0.545098f, 1.0f)
#define SDL_GPUD_DARK_SLATE_GRAY        SDL_GPUD_COLOR(0.184314f, 0.309804f, 0.309804f, 1.0f)
#define SDL_GPUD_DARK_TURQUOISE         SDL_GPUD_COLOR(0.000000f, 0.807843f, 0.819608f, 1.0f)
#define SDL_GPUD_DARK_VIOLET            SDL_GPUD_COLOR(0.580392f, 0.000000f, 0.827451f, 1.0f)
#define SDL_GPUD_DEEP_PINK              SDL_GPUD_COLOR(1.000000f, 0.078431f, 0.576471f, 1.0f)
#define SDL_GPUD_DEEP_SKY_BLUE          SDL_GPUD_COLOR(0.000000f, 0.749020f, 1.000000f, 1.0f)
#define SDL_GPUD_DIM_GRAY               SDL_GPUD_COLOR(0.411765f, 0.411765f, 0.411765f, 1.0f)
#define SDL_GPUD_DODGER_BLUE            SDL_GPUD_COLOR(0.117647f, 0.564706f, 1.000000f, 1.0f)
#define SDL_GPUD_FIREBRICK              SDL_GPUD_COLOR(0.698039f, 0.133333f, 0.133333f, 1.0f)
#define SDL_GPUD_FLORAL_WHITE           SDL_GPUD_COLOR(1.000000f, 0.980392f, 0.941176f, 1.0f)
#define SDL_GPUD_FOREST_GREEN           SDL_GPUD_COLOR(0.133333f, 0.545098f, 0.133333f, 1.0f)
#define SDL_GPUD_GAINSBORO              SDL_GPUD_COLOR(0.862745f, 0.862745f, 0.862745f, 1.0f)
#define SDL_GPUD_GHOST_WHITE            SDL_GPUD_COLOR(0.972549f, 0.972549f, 1.000000f, 1.0f)
#define SDL_GPUD_GOLD                   SDL_GPUD_COLOR(1.000000f, 0.843137f, 0.000000f, 1.0f)
#define SDL_GPUD_GOLDENROD              SDL_GPUD_COLOR(0.854902f, 0.647059f, 0.125490f, 1.0f)
#define SDL_GPUD_GRAY                   SDL_GPUD_COLOR(0.501961f, 0.501961f, 0.501961f, 1.0f)
#define SDL_GPUD_GREEN                  SDL_GPUD_COLOR(0.000000f, 0.501961f, 0.000000f, 1.0f)
#define SDL_GPUD_GREEN_YELLOW           SDL_GPUD_COLOR(0.678431f, 1.000000f, 0.184314f, 1.0f)
#define SDL_GPUD_HONEYDEW               SDL_GPUD_COLOR(0.941176f, 1.000000f, 0.941176f, 1.0f)
#define SDL_GPUD_HOT_PINK               SDL_GPUD_COLOR(1.000000f, 0.411765f, 0.705882f, 1.0f)
#define SDL_GPUD_INDIAN_RED             SDL_GPUD_COLOR(0.803922f, 0.360784f, 0.360784f, 1.0f)
#define SDL_GPUD_INDIGO                 SDL_GPUD_COLOR(0.294118f, 0.000000f, 0.509804f, 1.0f)
#define SDL_GPUD_IVORY                  SDL_GPUD_COLOR(1.000000f, 1.000000f, 0.941176f, 1.0f)
#define SDL_GPUD_KHAKI                  SDL_GPUD_COLOR(0.941176f, 0.901961f, 0.549020f, 1.0f)
#define SDL_GPUD_LAVENDER               SDL_GPUD_COLOR(0.901961f, 0.901961f, 0.980392f, 1.0f)
#define SDL_GPUD_LAVENDER_BLUSH         SDL_GPUD_COLOR(1.000000f, 0.941176f, 0.960784f, 1.0f)
#define SDL_GPUD_LAWN_GREEN             SDL_GPUD_COLOR(0.486275f, 0.988235f, 0.000000f, 1.0f)
#define SDL_GPUD_LEMON_CHIFFON          SDL_GPUD_COLOR(1.000000f, 0.980392f, 0.803922f, 1.0f)
#define SDL_GPUD_LIGHT_BLUE             SDL_GPUD_COLOR(0.678431f, 0.847059f, 0.901961f, 1.0f)
#define SDL_GPUD_LIGHT_CORAL            SDL_GPUD_COLOR(0.941176f, 0.501961f, 0.501961f, 1.0f)
#define SDL_GPUD_LIGHT_CYAN             SDL_GPUD_COLOR(0.878431f, 1.000000f, 1.000000f, 1.0f)
#define SDL_GPUD_LIGHT_GOLDENROD_YELLOW SDL_GPUD_COLOR(0.980392f, 0.980392f, 0.823529f, 1.0f)
#define SDL_GPUD_LIGHT_GRAY             SDL_GPUD_COLOR(0.827451f, 0.827451f, 0.827451f, 1.0f)
#define SDL_GPUD_LIGHT_GREEN            SDL_GPUD_COLOR(0.564706f, 0.933333f, 0.564706f, 1.0f)
#define SDL_GPUD_LIGHT_PINK             SDL_GPUD_COLOR(1.000000f, 0.713725f, 0.756863f, 1.0f)
#define SDL_GPUD_LIGHT_SALMON           SDL_GPUD_COLOR(1.000000f, 0.627451f, 0.478431f, 1.0f)
#define SDL_GPUD_LIGHT_SEA_GREEN        SDL_GPUD_COLOR(0.125490f, 0.698039f, 0.666667f, 1.0f)
#define SDL_GPUD_LIGHT_SKY_BLUE         SDL_GPUD_COLOR(0.529412f, 0.807843f, 0.980392f, 1.0f)
#define SDL_GPUD_LIGHT_SLATE_GRAY       SDL_GPUD_COLOR(0.466667f, 0.533333f, 0.600000f, 1.0f)
#define SDL_GPUD_LIGHT_STEEL_BLUE       SDL_GPUD_COLOR(0.690196f, 0.768627f, 0.870588f, 1.0f)
#define SDL_GPUD_LIGHT_YELLOW           SDL_GPUD_COLOR(1.000000f, 1.000000f, 0.878431f, 1.0f)
#define SDL_GPUD_LIME                   SDL_GPUD_COLOR(0.000000f, 1.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_LIME_GREEN             SDL_GPUD_COLOR(0.196078f, 0.803922f, 0.196078f, 1.0f)
#define SDL_GPUD_LINEN                  SDL_GPUD_COLOR(0.980392f, 0.941176f, 0.901961f, 1.0f)
#define SDL_GPUD_MAGENTA                SDL_GPUD_COLOR(1.000000f, 0.000000f, 1.000000f, 1.0f)
#define SDL_GPUD_MAROON                 SDL_GPUD_COLOR(0.501961f, 0.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_MEDIUM_AQUAMARINE      SDL_GPUD_COLOR(0.400000f, 0.803922f, 0.666667f, 1.0f)
#define SDL_GPUD_MEDIUM_BLUE            SDL_GPUD_COLOR(0.000000f, 0.000000f, 0.803922f, 1.0f)
#define SDL_GPUD_MEDIUM_ORCHID          SDL_GPUD_COLOR(0.729412f, 0.333333f, 0.827451f, 1.0f)
#define SDL_GPUD_MEDIUM_PURPLE          SDL_GPUD_COLOR(0.576471f, 0.439216f, 0.858824f, 1.0f)
#define SDL_GPUD_MEDIUM_SEA_GREEN       SDL_GPUD_COLOR(0.235294f, 0.701961f, 0.443137f, 1.0f)
#define SDL_GPUD_MEDIUM_SLATE_BLUE      SDL_GPUD_COLOR(0.482353f, 0.407843f, 0.933333f, 1.0f)
#define SDL_GPUD_MEDIUM_SPRING_GREEN    SDL_GPUD_COLOR(0.000000f, 0.980392f, 0.603922f, 1.0f)
#define SDL_GPUD_MEDIUM_TURQUOISE       SDL_GPUD_COLOR(0.282353f, 0.819608f, 0.800000f, 1.0f)
#define SDL_GPUD_MEDIUM_VIOLET_RED      SDL_GPUD_COLOR(0.780392f, 0.082353f, 0.521569f, 1.0f)
#define SDL_GPUD_MIDNIGHT_BLUE          SDL_GPUD_COLOR(0.098039f, 0.098039f, 0.439216f, 1.0f)
#define SDL_GPUD_MINT_CREAM             SDL_GPUD_COLOR(0.960784f, 1.000000f, 0.980392f, 1.0f)
#define SDL_GPUD_MISTY_ROSE             SDL_GPUD_COLOR(1.000000f, 0.894118f, 0.882353f, 1.0f)
#define SDL_GPUD_MOCCASIN               SDL_GPUD_COLOR(1.000000f, 0.894118f, 0.709804f, 1.0f)
#define SDL_GPUD_NAVY                   SDL_GPUD_COLOR(0.000000f, 0.000000f, 0.501961f, 1.0f)
#define SDL_GPUD_OLD_LACE               SDL_GPUD_COLOR(0.992157f, 0.960784f, 0.901961f, 1.0f)
#define SDL_GPUD_OLIVE                  SDL_GPUD_COLOR(0.501961f, 0.501961f, 0.000000f, 1.0f)
#define SDL_GPUD_OLIVE_DRAB             SDL_GPUD_COLOR(0.419608f, 0.556863f, 0.137255f, 1.0f)
#define SDL_GPUD_ORANGE                 SDL_GPUD_COLOR(1.000000f, 0.647059f, 0.000000f, 1.0f)
#define SDL_GPUD_ORANGE_RED             SDL_GPUD_COLOR(1.000000f, 0.270588f, 0.000000f, 1.0f)
#define SDL_GPUD_ORCHID                 SDL_GPUD_COLOR(0.854902f, 0.439216f, 0.839216f, 1.0f)
#define SDL_GPUD_PALE_GOLDENROD         SDL_GPUD_COLOR(0.933333f, 0.909804f, 0.666667f, 1.0f)
#define SDL_GPUD_PALE_GREEN             SDL_GPUD_COLOR(0.596078f, 0.984314f, 0.596078f, 1.0f)
#define SDL_GPUD_PALE_TURQUOISE         SDL_GPUD_COLOR(0.686275f, 0.933333f, 0.933333f, 1.0f)
#define SDL_GPUD_PALE_VIOLET_RED        SDL_GPUD_COLOR(0.858824f, 0.439216f, 0.576471f, 1.0f)
#define SDL_GPUD_PAPAYA_WHIP            SDL_GPUD_COLOR(1.000000f, 0.937255f, 0.835294f, 1.0f)
#define SDL_GPUD_PEACH_PUFF             SDL_GPUD_COLOR(1.000000f, 0.854902f, 0.725490f, 1.0f)
#define SDL_GPUD_PERU                   SDL_GPUD_COLOR(0.803922f, 0.521569f, 0.247059f, 1.0f)
#define SDL_GPUD_PINK                   SDL_GPUD_COLOR(1.000000f, 0.752941f, 0.796078f, 1.0f)
#define SDL_GPUD_PLUM                   SDL_GPUD_COLOR(0.866667f, 0.627451f, 0.866667f, 1.0f)
#define SDL_GPUD_POWDER_BLUE            SDL_GPUD_COLOR(0.690196f, 0.878431f, 0.901961f, 1.0f)
#define SDL_GPUD_PURPLE                 SDL_GPUD_COLOR(0.501961f, 0.000000f, 0.501961f, 1.0f)
#define SDL_GPUD_REBECCA_PURPLE         SDL_GPUD_COLOR(0.400000f, 0.200000f, 0.600000f, 1.0f)
#define SDL_GPUD_RED                    SDL_GPUD_COLOR(1.000000f, 0.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_ROSY_BROWN             SDL_GPUD_COLOR(0.737255f, 0.560784f, 0.560784f, 1.0f)
#define SDL_GPUD_ROYAL_BLUE             SDL_GPUD_COLOR(0.254902f, 0.411765f, 0.882353f, 1.0f)
#define SDL_GPUD_SADDLE_BROWN           SDL_GPUD_COLOR(0.545098f, 0.270588f, 0.074510f, 1.0f)
#define SDL_GPUD_SALMON                 SDL_GPUD_COLOR(0.980392f, 0.501961f, 0.447059f, 1.0f)
#define SDL_GPUD_SANDY_BROWN            SDL_GPUD_COLOR(0.956863f, 0.643137f, 0.376471f, 1.0f)
#define SDL_GPUD_SEA_GREEN              SDL_GPUD_COLOR(0.180392f, 0.545098f, 0.341176f, 1.0f)
#define SDL_GPUD_SEA_SHELL              SDL_GPUD_COLOR(1.000000f, 0.960784f, 0.933333f, 1.0f)
#define SDL_GPUD_SIENNA                 SDL_GPUD_COLOR(0.627451f, 0.321569f, 0.176471f, 1.0f)
#define SDL_GPUD_SILVER                 SDL_GPUD_COLOR(0.752941f, 0.752941f, 0.752941f, 1.0f)
#define SDL_GPUD_SKY_BLUE               SDL_GPUD_COLOR(0.529412f, 0.807843f, 0.921569f, 1.0f)
#define SDL_GPUD_SLATE_BLUE             SDL_GPUD_COLOR(0.415686f, 0.352941f, 0.803922f, 1.0f)
#define SDL_GPUD_SLATE_GRAY             SDL_GPUD_COLOR(0.439216f, 0.501961f, 0.564706f, 1.0f)
#define SDL_GPUD_SNOW                   SDL_GPUD_COLOR(1.000000f, 0.980392f, 0.980392f, 1.0f)
#define SDL_GPUD_SPRING_GREEN           SDL_GPUD_COLOR(0.000000f, 1.000000f, 0.498039f, 1.0f)
#define SDL_GPUD_STEEL_BLUE             SDL_GPUD_COLOR(0.274510f, 0.509804f, 0.705882f, 1.0f)
#define SDL_GPUD_TAN                    SDL_GPUD_COLOR(0.823529f, 0.705882f, 0.549020f, 1.0f)
#define SDL_GPUD_TEAL                   SDL_GPUD_COLOR(0.000000f, 0.501961f, 0.501961f, 1.0f)
#define SDL_GPUD_THISTLE                SDL_GPUD_COLOR(0.847059f, 0.749020f, 0.847059f, 1.0f)
#define SDL_GPUD_TOMATO                 SDL_GPUD_COLOR(1.000000f, 0.388235f, 0.278431f, 1.0f)
#define SDL_GPUD_TURQUOISE              SDL_GPUD_COLOR(0.250980f, 0.878431f, 0.815686f, 1.0f)
#define SDL_GPUD_VIOLET                 SDL_GPUD_COLOR(0.933333f, 0.509804f, 0.933333f, 1.0f)
#define SDL_GPUD_WHEAT                  SDL_GPUD_COLOR(0.960784f, 0.870588f, 0.701961f, 1.0f)
#define SDL_GPUD_WHITE                  SDL_GPUD_COLOR(1.000000f, 1.000000f, 1.000000f, 1.0f)
#define SDL_GPUD_WHITE_SMOKE            SDL_GPUD_COLOR(0.960784f, 0.960784f, 0.960784f, 1.0f)
#define SDL_GPUD_YELLOW                 SDL_GPUD_COLOR(1.000000f, 1.000000f, 0.000000f, 1.0f)
#define SDL_GPUD_YELLOW_GREEN           SDL_GPUD_COLOR(0.603922f, 0.803922f, 0.196078f, 1.0f)

#ifdef __cplusplus
extern "C"
{
#endif /* ifdef __cplusplus */

/**
 * @brief 
 * 
 */
typedef struct
{
    float x;
    float y;
    float z;
}
SDL_GPUDPoint;

/**
 * @brief 
 * 
 * @param device 
 * @param color_texture_format 
 * @param depth_texture_format 
 * @return
 */
bool SDL_InitGPUD(
    SDL_GPUDevice* device,
    SDL_GPUTextureFormat color_texture_format,
    SDL_GPUTextureFormat depth_texture_format);

/**
 * @brief 
 * 
 */
void SDL_QuitGPUD();

/**
 * @brief 
 * 
 * @param color 
 */
void SDL_SetGPUDColor(
    const SDL_FColor* color);

/**
 * @brief 
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 */
void SDL_DrawGPUDLine2D(
    float x1,
    float y1,
    float x2,
    float y2);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param radius 
 */
void SDL_DrawGPUDPoint2D(
    float x,
    float y,
    float radius);

/**
 * @brief 
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 */
void SDL_DrawGPUDBox2D(
    float x1,
    float y1,
    float x2,
    float y2);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param radius 
 */
void SDL_DrawGPUDCircle2D(
    float x,
    float y,
    float radius);

/**
 * @brief 
 * 
 * @param text 
 * @param x 
 * @param y 
 * @param size 
 */
void SDL_DrawGPUDText2D(
    const char* text,
    float x,
    float y,
    float size);

/**
 * @brief 
 * 
 * @param start 
 * @param end 
 */
void SDL_DrawGPUDLine3D(
    const SDL_GPUDPoint* start,
    const SDL_GPUDPoint* end);

/**
 * @brief 
 * 
 * @param center 
 * @param radius 
 */
void SDL_DrawGPUDPoint3D(
    const SDL_GPUDPoint* center,
    float radius);

/**
 * @brief 
 * 
 * @param start 
 * @param end 
 */
void SDL_DrawGPUDBox3D(
    const SDL_GPUDPoint* start,
    const SDL_GPUDPoint* end);

/**
 * @brief 
 * 
 * @param center 
 * @param radius 
 */
void SDL_DrawGPUDSphere3D(
    const SDL_GPUDPoint* center,
    float radius);

/**
 * @brief 
 * 
 * @param text 
 * @param center 
 * @param size 
 */
void SDL_DrawGPUDText3D(
    const char* text,
    const SDL_GPUDPoint* center,
    float size);

/**
 * @brief 
 * 
 * @param command_buffer 
 * @param color_texture 
 * @param depth_texture 
 * @param matrix_2d 
 * @param matrix_3d 
 */
void SDL_PresentGPUD(
    SDL_GPUCommandBuffer* command_buffer,
    SDL_GPUTexture* color_texture,
    SDL_GPUTexture* depth_texture,
    void* matrix_2d,
    void* matrix_3d);

#ifdef __cplusplus
} /* extern "C" */
#endif /* ifdef __cplusplus */
#ifdef __cplusplus

void SDL_SetGPUDColor(
    const SDL_FColor& color)
{
    SDL_SetGPUDColor(&color);
}

/* TODO: */

#endif /* ifdef __cplusplus */
#ifdef SDL_GPUD_IMPL