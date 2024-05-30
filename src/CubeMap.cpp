#include "CubeMap.h"


CubeMap::CubeMap(ID3D11Device* dxdevice, ID3D11DeviceContext* dxdevice_context)
	: cm_dxdevice(dxdevice), cm_dxdevice_context(dxdevice_context)
{
    const char* cube_filenames[6] = {
           "/Users/marti/Documents/GitHub/eduRend/assets/cubemaps/brightday/posx.png",
           "/Users/marti/Documents/GitHub/eduRend/assets/cubemaps/brightday/negx.png",
           "/Users/marti/Documents/GitHub/eduRend/assets/cubemaps/brightday/posy.png",
           "/Users/marti/Documents/GitHub/eduRend/assets/cubemaps/brightday/negy.png",
           "/Users/marti/Documents/GitHub/eduRend/assets/cubemaps/brightday/posz.png",
           "/Users/marti/Documents/GitHub/eduRend/assets/cubemaps/brightday/negz.png"
    };

    HRESULT hr = LoadCubeTextureFromFile(cm_dxdevice, cube_filenames, &cube_texture);
    if (SUCCEEDED(hr)) {
        std::cout << "Cubemap OK" << std::endl;
    }
    else {
        std::cout << "Cubemap failed to load" << std::endl;
    }

    const unsigned cube_slot = 2;
    cm_dxdevice_context->PSSetShaderResources(cube_slot, 1, &cube_texture.TextureView);

    cm_dxdevice_context->PSSetSamplers(
        1, // slot #
        1, // number of samplers to bind (1)
        &cm_sampler);
}
