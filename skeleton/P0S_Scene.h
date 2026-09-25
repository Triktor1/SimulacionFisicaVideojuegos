#pragma once
#include "EmptyScene.h"
class P0S_Scene :
    public EmptyScene
{
public:
    explicit P0S_Scene(std::string name) : EmptyScene(std::move(name)) {}
    void init() override;
    void cleanup() override;
private:
    std::vector<physx::PxTransform*> transforms;
    std::vector<RenderItem*> renderItems;
};

