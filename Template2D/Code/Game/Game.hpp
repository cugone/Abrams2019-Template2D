#pragma once

#include "Engine/Core/TimeUtils.hpp"
#include "Engine/Renderer/Camera2D.hpp"

class Game {
public:
    Game() = default;
    Game(const Game& other) = default;
    Game(Game&& other) = default;
    Game& operator=(const Game& other) = default;
    Game& operator=(Game&& other) = default;
    ~Game() = default;

    void Initialize();
    void BeginFrame();
    void Update(TimeUtils::FPSeconds deltaSeconds);
    void Render() const;
    void EndFrame();

protected:
private:

    void HandleDebugInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);
    void HandleDebugKeyboardInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);
    void HandleDebugMouseInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);

    void HandlePlayerInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);
    void HandleKeyboardInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);
    void HandleControllerInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);
    void HandleMouseInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds);

    mutable Camera2D _camera2D{};

    bool _debug_render = false;
};

