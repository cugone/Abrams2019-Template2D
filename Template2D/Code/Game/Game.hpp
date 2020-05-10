#pragma once

#include "Engine/Core/Console.hpp"
#include "Engine/Core/TimeUtils.hpp"
#include "Engine/Renderer/Camera2D.hpp"

#include "Game/GameCommon.hpp"

#include <memory>

class KerningFont;

class Game {
public:
    Game() = default;
    Game(const Game& other) = default;
    Game(Game&& other) = default;
    Game& operator=(const Game& other) = default;
    Game& operator=(Game&& other) = default;
    ~Game() noexcept;

    void Initialize();
    void BeginFrame();
    void Update(TimeUtils::FPSeconds deltaSeconds);
    void Render() const;
    void EndFrame();

protected:
private:

    void HandleDebugInput(Camera2D& base_camera);
    void HandleDebugKeyboardInput(Camera2D& base_camera);
    void HandleDebugMouseInput(Camera2D& base_camera);

    void HandlePlayerInput(Camera2D& base_camera);
    void HandleKeyboardInput(Camera2D& base_camera);
    void HandleMouseInput(Camera2D& base_camera);

    void RegisterCommands();
    void UnRegisterCommands();

    mutable Camera2D _ui_camera{};

    float _cam_speed = 1.0f;
    float _max_shake_angle = 0.0f;
    float _max_shake_x = 0.0f;
    float _max_shake_y = 0.0f;
    bool _debug_render = false;
    Console::CommandList _consoleCommands;

};

