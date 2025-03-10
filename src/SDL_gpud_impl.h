typedef enum
{
    SDL_GPUD_COMMAND_TYPE_2D_LINE,
    SDL_GPUD_COMMAND_TYPE_2D_TRIANGLE,
    SDL_GPUD_COMMAND_TYPE_2D_TEXT,
}
SDL_GPUDCommandType2D;

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
}
SDL_GPUDCommand;

typedef enum
{
    SDL_GPUD_COMMAND_LIST_TYPE_2D,
    SDL_GPUD_COMMAND_LIST_TYPE_3D_LINE,
    SDL_GPUD_COMMAND_LIST_TYPE_3D_TRIANGLE,
    SDL_GPUD_COMMAND_LIST_TYPE_3D_TEXT,
    SDL_GPUD_COMMAND_LIST_TYPE_COUNT,
}
SDL_GPUDComandListType;

typedef struct
{
    SDL_GPUDCommand* head;
    SDL_GPUDCommand* tail;
    SDL_GPUDCommand* curr;
}
SDL_GPUDCommandList;

typedef enum
{
    SDL_GPUD_SHADER_TYPE_2D_SHAPE_VERT,
    SDL_GPUD_SHADER_TYPE_2D_SHAPE_FRAG,
    SDL_GPUD_SHADER_TYPE_3D_SHAPE_VERT,
    SDL_GPUD_SHADER_TYPE_3D_SHAPE_FRAG,
    SDL_GPUD_SHADER_TYPE_COUNT,
}
SDL_GPUDShaderType;

typedef enum
{
    SDL_GPUD_PIPELINE_TYPE_2D_LINE,
    SDL_GPUD_PIPELINE_TYPE_2D_TRIANGLE,
    SDL_GPUD_PIPELINE_TYPE_3D_LINE,
    SDL_GPUD_PIPELINE_TYPE_3D_TRIANGLE,
    SDL_GPUD_PIPELINE_TYPE_COUNT,
}
SDL_GPUDPipelineType;

typedef enum
{
    SDL_GPUD_DRIVER_TYPE_SPV,
    SDL_GPUD_DRIVER_TYPE_DXIL,
    SDL_GPUD_DRIVER_TYPE_MSL,
    SDL_GPUD_DRIVER_TYPE_COUNT,
}
SDL_GPUDDriverType;

typedef struct
{
    SDL_GPUShader* shader;
    struct
    {
        size_t size;
        const Uint8 *data;
    }
    code[SDL_GPUD_DRIVER_TYPE_COUNT];
    SDL_GPUShaderStage stage;
    Uint32 num_samplers;
    Uint32 num_storage_textures;
    Uint32 num_storage_buffers;
    Uint32 num_uniform_buffers;
}
SDL_GPUDShader;

static SDL_GPUDevice* device;
static SDL_GPUDCommandList* command_lists[SDL_GPUD_COMMAND_LIST_TYPE_COUNT];
static SDL_GPUGraphicsPipeline* pipelines[SDL_GPUD_PIPELINE_TYPE_COUNT];

bool SDL_InitGPUD(
    SDL_GPUDevice* device_,
    SDL_GPUTextureFormat color_texture_format,
    SDL_GPUTextureFormat depth_texture_format)
{
    if (device)
    {
        SDL_QuitGPUD();
    }
    if (!device_)
    {
        return SDL_InvalidParamError("device_");
    }
    device = device_;
    SDL_GPUDShader shaders[SDL_GPUD_SHADER_TYPE_COUNT] =
    {
        [SDL_GPUD_SHADER_TYPE_2D_SHAPE_VERT] =
        {
            .code =
            {
                [SDL_GPUD_DRIVER_TYPE_SPV] =
                {
                    .data = shader_2d_shape_vert_spv,
                    .size = sizeof(shader_2d_shape_vert_spv),
                },
                [SDL_GPUD_DRIVER_TYPE_DXIL] =
                {
                    .data = shader_2d_shape_vert_dxil,
                    .size = sizeof(shader_2d_shape_vert_dxil),
                },
                [SDL_GPUD_DRIVER_TYPE_MSL] =
                {
                    .data = shader_2d_shape_vert_msl,
                    .size = sizeof(shader_2d_shape_vert_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_VERTEX,
            .num_samplers = 0,
            .num_storage_textures = 0,
            .num_storage_buffers = 0,
            .num_uniform_buffers = 1,
        },
        [SDL_GPUD_SHADER_TYPE_2D_SHAPE_FRAG] =
        {
            .code =
            {
                [SDL_GPUD_DRIVER_TYPE_SPV] =
                {
                    .data = shader_2d_shape_frag_spv,
                    .size = sizeof(shader_2d_shape_frag_spv),
                },
                [SDL_GPUD_DRIVER_TYPE_DXIL] =
                {
                    .data = shader_2d_shape_frag_dxil,
                    .size = sizeof(shader_2d_shape_frag_dxil),
                },
                [SDL_GPUD_DRIVER_TYPE_MSL] =
                {
                    .data = shader_2d_shape_frag_msl,
                    .size = sizeof(shader_2d_shape_frag_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
            .num_samplers = 0,
            .num_storage_textures = 0,
            .num_storage_buffers = 0,
            .num_uniform_buffers = 0,
        },
        [SDL_GPUD_SHADER_TYPE_3D_SHAPE_VERT] =
        {
            .code =
            {
                [SDL_GPUD_DRIVER_TYPE_SPV] =
                {
                    .data = shader_2d_shape_vert_spv,
                    .size = sizeof(shader_2d_shape_vert_spv),
                },
                [SDL_GPUD_DRIVER_TYPE_DXIL] =
                {
                    .data = shader_2d_shape_vert_dxil,
                    .size = sizeof(shader_2d_shape_vert_dxil),
                },
                [SDL_GPUD_DRIVER_TYPE_MSL] =
                {
                    .data = shader_2d_shape_vert_msl,
                    .size = sizeof(shader_2d_shape_vert_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_VERTEX,
            .num_samplers = 0,
            .num_storage_textures = 0,
            .num_storage_buffers = 0,
            .num_uniform_buffers = 1,
        },
        [SDL_GPUD_SHADER_TYPE_3D_SHAPE_FRAG] =
        {
            .code =
            {
                [SDL_GPUD_DRIVER_TYPE_SPV] =
                {
                    .data = shader_2d_shape_frag_spv,
                    .size = sizeof(shader_2d_shape_frag_spv),
                },
                [SDL_GPUD_DRIVER_TYPE_DXIL] =
                {
                    .data = shader_2d_shape_frag_dxil,
                    .size = sizeof(shader_2d_shape_frag_dxil),
                },
                [SDL_GPUD_DRIVER_TYPE_MSL] =
                {
                    .data = shader_2d_shape_frag_msl,
                    .size = sizeof(shader_2d_shape_frag_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
            .num_samplers = 0,
            .num_storage_textures = 0,
            .num_storage_buffers = 0,
            .num_uniform_buffers = 0,
        },
    };
    SDL_GPUDDriverType driver_type;
    SDL_GPUShaderFormat shader_format;
    const char* entrypoint;
    if (SDL_GetGPUShaderFormats(device) & SDL_GPU_SHADERFORMAT_SPIRV)
    {
        driver_type = SDL_GPUD_DRIVER_TYPE_SPV;
        shader_format = SDL_GPU_SHADERFORMAT_SPIRV;
        entrypoint = "main";
    }
    else if (SDL_GetGPUShaderFormats(device) & SDL_GPU_SHADERFORMAT_DXIL)
    {
        driver_type = SDL_GPUD_DRIVER_TYPE_DXIL;
        shader_format = SDL_GPU_SHADERFORMAT_DXIL;
        entrypoint = "main";
    }
    else if (SDL_GetGPUShaderFormats(device) & SDL_GPU_SHADERFORMAT_MSL)
    {
        driver_type = SDL_GPUD_DRIVER_TYPE_MSL;
        shader_format = SDL_GPU_SHADERFORMAT_MSL;
        entrypoint = "main0";
    }
    else
    {
        return SDL_SetError("Unsupported shader format");
    }
    for (SDL_GPUDShaderType type = 0; type < SDL_GPUD_SHADER_TYPE_COUNT; type++)
    {
        SDL_GPUShaderCreateInfo info = {0};
        info.code_size = shaders[type].code[driver_type].size;
        info.code = shaders[type].code[driver_type].data;
        info.entrypoint = entrypoint;
        info.format = shader_format;
        info.stage = shaders[type].stage;
        info.num_samplers = shaders[type].num_samplers;
        info.num_storage_textures = shaders[type].num_storage_textures;
        info.num_storage_buffers = shaders[type].num_storage_buffers;
        info.num_uniform_buffers = shaders[type].num_uniform_buffers;
        shaders[type].shader = SDL_CreateGPUShader(device, &info);
        if (!shaders[type].shader)
        {
            return SDL_SetError("Failed to create shader: %s", SDL_GetError());
        }
    }
    pipelines[SDL_GPUD_PIPELINE_TYPE_2D_LINE] = SDL_CreateGPUGraphicsPipeline(device,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SDL_GPUD_SHADER_TYPE_2D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SDL_GPUD_SHADER_TYPE_2D_SHAPE_FRAG].shader,
        .target_info =
        {
            .num_color_targets = 1,
            .color_target_descriptions = (SDL_GPUColorTargetDescription[])
            {{
                .format = color_texture_format,
            }}
        },
        .vertex_input_state =
        {
            .num_vertex_attributes = 2,
            .vertex_attributes = (SDL_GPUVertexAttribute[])
            {{
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
                .location = 0,
                .offset = 0,
            },
            {
                .format = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
                .location = 1,
                .offset = 8,
            }},
            .num_vertex_buffers = 1,
            .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[])
            {{
                .pitch = 12,
            }},
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_LINELIST,
    });
    pipelines[SDL_GPUD_PIPELINE_TYPE_2D_TRIANGLE] = SDL_CreateGPUGraphicsPipeline(device,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SDL_GPUD_SHADER_TYPE_2D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SDL_GPUD_SHADER_TYPE_2D_SHAPE_FRAG].shader,
        .target_info =
        {
            .num_color_targets = 1,
            .color_target_descriptions = (SDL_GPUColorTargetDescription[])
            {{
                .format = color_texture_format,
            }}
        },
        .vertex_input_state =
        {
            .num_vertex_attributes = 2,
            .vertex_attributes = (SDL_GPUVertexAttribute[])
            {{
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
                .location = 0,
                .offset = 0,
            },
            {
                .format = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
                .location = 1,
                .offset = 8,
            }},
            .num_vertex_buffers = 1,
            .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[])
            {{
                .pitch = 12,
            }},
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
    });
    pipelines[SDL_GPUD_PIPELINE_TYPE_3D_LINE] = SDL_CreateGPUGraphicsPipeline(device,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SDL_GPUD_SHADER_TYPE_3D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SDL_GPUD_SHADER_TYPE_3D_SHAPE_FRAG].shader,
        .target_info =
        {
            .num_color_targets = 1,
            .color_target_descriptions = (SDL_GPUColorTargetDescription[])
            {{
                .format = color_texture_format,
            }},
            .has_depth_stencil_target = true,
            .depth_stencil_format = depth_texture_format,
        },
        .vertex_input_state =
        {
            .num_vertex_attributes = 2,
            .vertex_attributes = (SDL_GPUVertexAttribute[])
            {{
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .location = 0,
                .offset = 0,
            },
            {
                .format = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
                .location = 1,
                .offset = 12,
            }},
            .num_vertex_buffers = 1,
            .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[])
            {{
                .pitch = 16,
            }},
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_LINELIST,
        .depth_stencil_state =
        {
            .enable_depth_test = true,
            .enable_depth_write = true,
            .compare_op = SDL_GPU_COMPAREOP_LESS,
        },
    });
    pipelines[SDL_GPUD_PIPELINE_TYPE_3D_TRIANGLE] = SDL_CreateGPUGraphicsPipeline(device,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SDL_GPUD_SHADER_TYPE_3D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SDL_GPUD_SHADER_TYPE_3D_SHAPE_FRAG].shader,
        .target_info =
        {
            .num_color_targets = 1,
            .color_target_descriptions = (SDL_GPUColorTargetDescription[])
            {{
                .format = color_texture_format,
            }},
            .has_depth_stencil_target = true,
            .depth_stencil_format = depth_texture_format,
        },
        .vertex_input_state =
        {
            .num_vertex_attributes = 2,
            .vertex_attributes = (SDL_GPUVertexAttribute[])
            {{
                .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
                .location = 0,
                .offset = 0,
            },
            {
                .format = SDL_GPU_VERTEXELEMENTFORMAT_UINT,
                .location = 1,
                .offset = 12,
            }},
            .num_vertex_buffers = 1,
            .vertex_buffer_descriptions = (SDL_GPUVertexBufferDescription[])
            {{
                .pitch = 16,
            }},
        },
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .depth_stencil_state =
        {
            .enable_depth_test = true,
            .enable_depth_write = true,
            .compare_op = SDL_GPU_COMPAREOP_LESS,
        },
    });
    for (SDL_GPUDPipelineType type = 0; type < SDL_GPUD_PIPELINE_TYPE_COUNT; type++)
    {
        if (!pipelines[type])
        {
            return SDL_SetError("Failed to create pipeline: %s", SDL_GetError());
        }
    }
    for (SDL_GPUDShaderType type = 0; type < SDL_GPUD_SHADER_TYPE_COUNT; type++)
    {
        SDL_ReleaseGPUShader(device, shaders[type].shader);
    }
    return true;
}

void SDL_QuitGPUD()
{
    if (!device)
    {
        return;
    }
    for (SDL_GPUDPipelineType type = 0; type < SDL_GPUD_PIPELINE_TYPE_COUNT; type++)
    {
        SDL_ReleaseGPUGraphicsPipeline(device, pipelines[type]);
        pipelines[type] = NULL;
    }
    device = NULL;
}