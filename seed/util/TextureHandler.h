#pragma once

namespace GameUtil { 

    class TextureHandler { 
    public:
        static ID3D10Texture2D* GetTexture2DFromFile(LPCWSTR, ID3D10Device*);
        static void GetResourceViewFromTexture(ID3D10Texture2D*, ID3D10ShaderResourceView**, ID3D10Device*);

    }; // TextureHandler
} // GameUtil
/* eof */