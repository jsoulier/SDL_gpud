typedef enum
{
    BATCH_2D_LINE,
    BATCH_2D_TRIANGLE,
    BATCH_2D_TEXT,
    BATCH_3D,
    BATCH_COUNT,
}
BatchType;

typedef struct Batch Batch;
typedef struct Batch
{
    Batch* next;
    BatchType type;
    SDL_GPUTransferBuffer* transfer_buffer;
    SDL_GPUBuffer* buffer;
    Uint32 size;
    Uint32 capacity;
    void* data;
}
Batch;

typedef enum
{
    QUEUE_2D,
    QUEUE_3D_LINE,
    QUEUE_3D_TRIANGLE,
    QUEUE_3D_TEXT,
    QUEUE_COUNT,
}
QueueType;

typedef struct
{
    Batch* head;
    Batch* tail;
    Batch* curr;
}
Queue;

typedef enum
{
    SHADER_2D_SHAPE_VERT,
    SHADER_3D_SHAPE_VERT,
    SHADER_SHAPE_FRAG,
    SHADER_COUNT,
}
ShaderType;

typedef enum
{
    PIPELINE_2D_LINE,
    PIPELINE_2D_TRIANGLE,
    PIPELINE_3D_LINE,
    PIPELINE_3D_TRIANGLE,
    PIPELINE_COUNT,
}
PipelineType;

typedef enum
{
    DRIVER_SPV,
    DRIVER_DXIL,
    DRIVER_MSL,
    DRIVER_COUNT,
}
DriverType;

typedef struct
{
    SDL_GPUShader* shader;
    struct
    {
        size_t size;
        const Uint8 *data;
    }
    code[DRIVER_COUNT];
    SDL_GPUShaderStage stage;
    Uint32 samplers;
    Uint32 textures;
    Uint32 buffers;
    Uint32 uniforms;
}
Shader;

typedef struct
{
    float x;
    float y;
    float z;
    Uint32 color;
}
ShapePoint3D;

static SDL_GPUDevice* device;
static SDL_GPUGraphicsPipeline* pipelines[PIPELINE_COUNT];
static Queue queues[QUEUE_COUNT];
static Uint32 color;

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
        return SDL_InvalidParamError("device");
    }
    Shader shaders[SHADER_COUNT] =
    {
        [SHADER_2D_SHAPE_VERT] =
        {
            .code =
            {
                [DRIVER_SPV] =
                {
                    .data = shader_2d_shape_vert_spv,
                    .size = sizeof(shader_2d_shape_vert_spv),
                },
                [DRIVER_DXIL] =
                {
                    .data = shader_2d_shape_vert_dxil,
                    .size = sizeof(shader_2d_shape_vert_dxil),
                },
                [DRIVER_MSL] =
                {
                    .data = shader_2d_shape_vert_msl,
                    .size = sizeof(shader_2d_shape_vert_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_VERTEX,
            .samplers = 0,
            .textures = 0,
            .buffers = 0,
            .uniforms = 1,
        },
        [SHADER_3D_SHAPE_VERT] =
        {
            .code =
            {
                [DRIVER_SPV] =
                {
                    .data = shader_3d_shape_vert_spv,
                    .size = sizeof(shader_3d_shape_vert_spv),
                },
                [DRIVER_DXIL] =
                {
                    .data = shader_3d_shape_vert_dxil,
                    .size = sizeof(shader_3d_shape_vert_dxil),
                },
                [DRIVER_MSL] =
                {
                    .data = shader_3d_shape_vert_msl,
                    .size = sizeof(shader_3d_shape_vert_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_VERTEX,
            .samplers = 0,
            .textures = 0,
            .buffers = 0,
            .uniforms = 1,
        },
        [SHADER_SHAPE_FRAG] =
        {
            .code =
            {
                [DRIVER_SPV] =
                {
                    .data = shader_shape_frag_spv,
                    .size = sizeof(shader_shape_frag_spv),
                },
                [DRIVER_DXIL] =
                {
                    .data = shader_shape_frag_dxil,
                    .size = sizeof(shader_shape_frag_dxil),
                },
                [DRIVER_MSL] =
                {
                    .data = shader_shape_frag_msl,
                    .size = sizeof(shader_shape_frag_msl),
                },
            },
            .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
            .samplers = 0,
            .textures = 0,
            .buffers = 0,
            .uniforms = 0,
        },
    };
    DriverType driver_type;
    SDL_GPUShaderFormat shader_format;
    const char* entrypoint;
    if (SDL_GetGPUShaderFormats(device_) & SDL_GPU_SHADERFORMAT_SPIRV)
    {
        driver_type = DRIVER_SPV;
        shader_format = SDL_GPU_SHADERFORMAT_SPIRV;
        entrypoint = "main";
    }
    else if (SDL_GetGPUShaderFormats(device_) & SDL_GPU_SHADERFORMAT_DXIL)
    {
        driver_type = DRIVER_DXIL;
        shader_format = SDL_GPU_SHADERFORMAT_DXIL;
        entrypoint = "main";
    }
    else if (SDL_GetGPUShaderFormats(device_) & SDL_GPU_SHADERFORMAT_MSL)
    {
        driver_type = DRIVER_MSL;
        shader_format = SDL_GPU_SHADERFORMAT_MSL;
        entrypoint = "main0";
    }
    else
    {
        return SDL_SetError("Unsupported shader format");
    }
    for (ShaderType type = 0; type < SHADER_COUNT; type++)
    {
        shaders[type].shader = SDL_CreateGPUShader(device_,
            &(SDL_GPUShaderCreateInfo)
        {
            .code_size = shaders[type].code[driver_type].size,
            .code = shaders[type].code[driver_type].data,
            .entrypoint = entrypoint,
            .format = shader_format,
            .stage = shaders[type].stage,
            .num_samplers = shaders[type].samplers,
            .num_storage_textures = shaders[type].textures,
            .num_storage_buffers = shaders[type].buffers,
            .num_uniform_buffers = shaders[type].uniforms,
        });
        if (!shaders[type].shader)
        {
            return SDL_SetError("Failed to create shader: %s", SDL_GetError());
        }
    }
    pipelines[PIPELINE_2D_LINE] = SDL_CreateGPUGraphicsPipeline(device_,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SHADER_2D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SHADER_SHAPE_FRAG].shader,
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
    pipelines[PIPELINE_2D_TRIANGLE] = SDL_CreateGPUGraphicsPipeline(device_,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SHADER_2D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SHADER_SHAPE_FRAG].shader,
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
    pipelines[PIPELINE_3D_LINE] = SDL_CreateGPUGraphicsPipeline(device_,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SHADER_3D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SHADER_SHAPE_FRAG].shader,
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
    pipelines[PIPELINE_3D_TRIANGLE] = SDL_CreateGPUGraphicsPipeline(device_,
        &(SDL_GPUGraphicsPipelineCreateInfo)
    {
        .vertex_shader = shaders[SHADER_3D_SHAPE_VERT].shader,
        .fragment_shader = shaders[SHADER_SHAPE_FRAG].shader,
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
    for (PipelineType type = 0; type < PIPELINE_COUNT; type++)
    {
        if (!pipelines[type])
        {
            return SDL_SetError("Failed to create pipeline: %s", SDL_GetError());
        }
    }
    for (ShaderType type = 0; type < SHADER_COUNT; type++)
    {
        SDL_ReleaseGPUShader(device_, shaders[type].shader);
    }
    device = device_;
    return true;
}

void SDL_QuitGPUD()
{
    if (!device)
    {
        return;
    }
    for (PipelineType type = 0; type < PIPELINE_COUNT; type++)
    {
        SDL_ReleaseGPUGraphicsPipeline(device, pipelines[type]);
        pipelines[type] = NULL;
    }
    device = NULL;
}

void SDL_SetGPUDColor(
    const SDL_FColor* color_)
{
    if (!device)
    {
        return;
    }
    if (!color_)
    {
        SDL_InvalidParamError("color");
        return;
    }
    color = 0;
    color |= (Uint32) SDL_max((Uint8) (color_->r * 255.0f), 255) << 24;
    color |= (Uint32) SDL_max((Uint8) (color_->g * 255.0f), 255) << 16;
    color |= (Uint32) SDL_max((Uint8) (color_->b * 255.0f), 255) <<  8;
    color |= (Uint32) SDL_max((Uint8) (color_->a * 255.0f), 255) <<  0;
}

void SDL_DrawGPUDLine2D(
    float x1,
    float y1,
    float x2,
    float y2)
{
    if (!device)
    {
        return;
    }
}

void SDL_DrawGPUDPoint2D(
    float x,
    float y,
    float radius)
{
    if (!device)
    {
        return;
    }
    if (radius < SDL_FLT_EPSILON)
    {
        SDL_InvalidParamError("radius");
        return;
    }
}

void SDL_DrawGPUDBox2D(
    float x1,
    float y1,
    float x2,
    float y2)
{
    if (!device)
    {
        return;
    }
}

void SDL_DrawGPUDCircle2D(
    float x,
    float y,
    float radius)
{
    if (!device)
    {
        return;
    }
    if (radius < SDL_FLT_EPSILON)
    {
        SDL_InvalidParamError("radius");
        return;
    }
}

void SDL_DrawGPUDText2D(
    const char* text,
    float x,
    float y,
    float size)
{
    if (!device)
    {
        return;
    }
    if (!text)
    {
        SDL_InvalidParamError("text");
        return;
    }
    if (size < SDL_FLT_EPSILON)
    {
        SDL_InvalidParamError("size");
        return;
    }
}

void SDL_DrawGPUDLine3D(
    const SDL_GPUDPoint* start,
    const SDL_GPUDPoint* end)
{
    if (!device)
    {
        return;
    }
    if (!start)
    {
        SDL_InvalidParamError("start");
        return;
    }
    if (!end)
    {
        SDL_InvalidParamError("end");
        return;
    }
}

void SDL_DrawGPUDPoint3D(
    const SDL_GPUDPoint* center,
    float radius)
{
    if (!device)
    {
        return;
    }
    if (!center)
    {
        SDL_InvalidParamError("center");
        return;
    }
    if (radius < SDL_FLT_EPSILON)
    {
        SDL_InvalidParamError("radius");
        return;
    }
}

void SDL_DrawGPUDBox3D(
    const SDL_GPUDPoint* start,
    const SDL_GPUDPoint* end)
{
    if (!device)
    {
        return;
    }
    if (!start)
    {
        SDL_InvalidParamError("start");
        return;
    }
    if (!end)
    {
        SDL_InvalidParamError("end");
        return;
    }
}

void SDL_DrawGPUDSphere3D(
    const SDL_GPUDPoint* center,
    float radius)
{
    if (!device)
    {
        return;
    }
    if (!center)
    {
        SDL_InvalidParamError("center");
        return;
    }
    if (radius < SDL_FLT_EPSILON)
    {
        SDL_InvalidParamError("radius");
        return;
    }
}

void SDL_DrawGPUDText3D(
    const char* text,
    const SDL_GPUDPoint* center,
    float size)
{
    if (!device)
    {
        return;
    }
    if (!text)
    {
        SDL_InvalidParamError("text");
        return;
    }
    if (!center)
    {
        SDL_InvalidParamError("center");
        return;
    }
    if (size < SDL_FLT_EPSILON)
    {
        SDL_InvalidParamError("size");
        return;
    }
}

static void Present2D(
    SDL_GPUCommandBuffer* command_buffer,
    SDL_GPUTexture* color_texture,
    void* matrix)
{
    if (!matrix)
    {
        return;
    }
    SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(
        command_buffer,
        &(SDL_GPUColorTargetInfo)
    {
        .texture = color_texture,
        .load_op = SDL_GPU_LOADOP_LOAD,
        .store_op = SDL_GPU_STOREOP_STORE,
    }, 1, NULL);
    if (!render_pass)
    {
        SDL_Log("Failed to begin render pass: %s", SDL_GetError());
        return;
    }
    SDL_EndGPURenderPass(render_pass);
}

static void Present3D(
    SDL_GPUCommandBuffer* command_buffer,
    SDL_GPUTexture* color_texture,
    SDL_GPUTexture* depth_texture,
    void* matrix)
{
    if (!depth_texture || !matrix)
    {
        return;
    }
    SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(
        command_buffer,
        &(SDL_GPUColorTargetInfo)
    {
        .texture = color_texture,
        .load_op = SDL_GPU_LOADOP_LOAD,
        .store_op = SDL_GPU_STOREOP_STORE,
    }, 1,
        &(SDL_GPUDepthStencilTargetInfo)
    {
        .texture = depth_texture,
        .load_op = SDL_GPU_LOADOP_LOAD,
        .store_op = SDL_GPU_STOREOP_STORE,
        .stencil_load_op = SDL_GPU_LOADOP_LOAD,
        .stencil_store_op = SDL_GPU_STOREOP_STORE,
    });
    if (!render_pass)
    {
        SDL_Log("Failed to begin render pass: %s", SDL_GetError());
        return;
    }
    SDL_BindGPUGraphicsPipeline(render_pass, pipelines[PIPELINE_3D_LINE]);
    SDL_PushGPUVertexUniformData(command_buffer, 0, matrix, 64);
    for (Batch* batch = queues[QUEUE_3D_LINE].head;
        batch != queues[QUEUE_3D_LINE].curr->next; batch = batch->next)
    {
        SDL_BindGPUVertexBuffers(
            render_pass, 0,
            &(SDL_GPUBufferBinding)
        {
            .buffer = batch->buffer
        }, 1);
        SDL_DrawGPUPrimitives(
            render_pass,
            batch->size / sizeof(ShapePoint3D),
            1, 0, 0);
    }
    SDL_BindGPUGraphicsPipeline(render_pass, pipelines[PIPELINE_3D_TRIANGLE]);
    SDL_PushGPUVertexUniformData(command_buffer, 0, matrix, 64);
    for (Batch* batch = queues[QUEUE_3D_TRIANGLE].head;
        batch != queues[QUEUE_3D_TRIANGLE].curr->next; batch = batch->next)
    {
        SDL_BindGPUVertexBuffers(
            render_pass, 0,
            &(SDL_GPUBufferBinding)
        {
            .buffer = batch->buffer
        }, 1);
        SDL_DrawGPUPrimitives(
            render_pass,
            batch->size / sizeof(ShapePoint3D),
            1, 0, 0);
    }
    /* TODO: */
    // SDL_BindGPUGraphicsPipeline(render_pass, pipelines[PIPELINE_3D_TEXT]);
    // SDL_PushGPUVertexUniformData(command_buffer, 0, matrix, 64);
    // for (Batch* batch = queues[QUEUE_3D_TEXT].head;
    //     batch != queues[QUEUE_3D_TEXT].curr->next; batch = batch->next)
    // {
    // }
    SDL_EndGPURenderPass(render_pass);
}

void SDL_PresentGPUD(
    SDL_GPUCommandBuffer* command_buffer,
    SDL_GPUTexture* color_texture,
    SDL_GPUTexture* depth_texture,
    void* matrix_2d,
    void* matrix_3d)
{
    if (!device)
    {
        return;
    }
    if (!command_buffer)
    {
        SDL_InvalidParamError("command_buffer");
        return;
    }
    if (!color_texture)
    {
        SDL_InvalidParamError("color_texture");
        return;
    }
    if (!depth_texture)
    {
        SDL_InvalidParamError("depth_texture");
        return;
    }
    if (depth_texture && !matrix_3d)
    {
        SDL_Log("Provided depth texture but no 3D matrix");
    }
    if (!depth_texture && matrix_3d)
    {
        SDL_Log("Provided 3D matrix but no depth texture");
    }
    if (!matrix_2d && (
        queues[QUEUE_2D].curr !=
        queues[QUEUE_2D].head))
    {
        SDL_Log("Invoked 2D draw calls but not provided 2D matrix");
    }
    if (!matrix_3d && (
        queues[QUEUE_3D_LINE].curr !=
        queues[QUEUE_3D_LINE].head &&
        queues[QUEUE_3D_TRIANGLE].curr !=
        queues[QUEUE_3D_TRIANGLE].head &&
        queues[QUEUE_3D_TEXT].curr !=
        queues[QUEUE_3D_TEXT].head))
    {
        SDL_Log("Invoked 3D draw calls but not provided 3D matrix");
    }
    Present2D(command_buffer, color_texture, matrix_2d);
    Present3D(command_buffer, color_texture, depth_texture, matrix_3d);
}