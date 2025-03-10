typedef enum
{
    SDL_GPUD_COMMAND_TYPE_2D_LINE,
    SDL_GPUD_COMMAND_TYPE_2D_TRIANGLE,
    SDL_GPUD_COMMAND_TYPE_2D_TEXT,
} SDL_GPUDCommandType2D;

typedef struct SDL_GPUDCommand SDL_GPUDCommand;
typedef struct SDL_GPUDCommand
{
    SDL_GPUDCommand* next;
    SDL_GPUDCommandType2D type;
    SDL_GPUTransferBuffer* transfer_buffer;
    SDL_GPUBuffer* buffer;
    Uint32 size;
    Uint32 capacity;
    void* data;
} SDL_GPUDCommand;

typedef enum
{
    SDL_GPUD_COMMAND_LIST_TYPE_2D,
    SDL_GPUD_COMMAND_LIST_TYPE_3D_LINE,
    SDL_GPUD_COMMAND_LIST_TYPE_3D_TRIANGLE,
    SDL_GPUD_COMMAND_LIST_TYPE_3D_TEXT,
    SDL_GPUD_COMMAND_LIST_TYPE_COUNT,
} SDL_GPUDComandListType;

typedef struct
{
    SDL_GPUDCommand* head;
    SDL_GPUDCommand* tail;
    SDL_GPUDCommand* curr;
}
SDL_GPUDCommandList;

static SDL_GPUDevice* device;
static SDL_GPUDCommandList* command_lists[SDL_GPUD_COMMAND_LIST_TYPE_COUNT];


bool SDL_InitGPUD(
    SDL_GPUDevice* device_,
    SDL_GPUTextureFormat color_texture_format,
    SDL_GPUTextureFormat depth_texture_format)
{
    if (!device_)
    {
        return SDL_InvalidParamError("device_");
    }
    device = device_;
    return true;
}

void SDL_QuitGPUD()
{
    device = NULL;
}