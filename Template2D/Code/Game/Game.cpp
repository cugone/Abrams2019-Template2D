#include "Game/Game.hpp"

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Core/KerningFont.hpp"

#include "Engine/Input/InputSystem.hpp"

#include "Engine/UI/UISystem.hpp"

#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/Material.hpp"

#include "Engine/Services/ServiceLocator.hpp"
#include "Engine/Services/IAppService.hpp"

#include "Game/GameCommon.hpp"
#include "Game/GameConfig.hpp"

void Game::Initialize() noexcept {
    g_theRenderer->RegisterMaterialsFromFolder(std::string{ "Data/Materials" });
    g_theRenderer->RegisterFontsFromFolder(std::string{"Data/Fonts"});

    _cameraController = OrthographicCameraController();
    _cameraController.SetPosition(Vector2::ZERO);
}

void Game::BeginFrame() noexcept {
    /* DO NOTHING */
}

void Game::Update(TimeUtils::FPSeconds deltaSeconds) noexcept {
    g_theRenderer->UpdateGameTime(deltaSeconds);

    HandlePlayerInput(deltaSeconds);

    _ui_camera2D.Update(deltaSeconds);
    _cameraController.Update(deltaSeconds);
}

void Game::Render() const noexcept {
    g_theRenderer->BeginRenderToBackbuffer();


    //World View
    g_theRenderer->SetMaterial(g_theRenderer->GetMaterial("__2D"));
    const auto S = Matrix4::CreateScaleMatrix(Vector2::ONE * 100.0f);
    const auto R = Matrix4::I;
    const auto T = Matrix4::I;
    const auto M = Matrix4::MakeSRT(S, R, T);
    g_theRenderer->DrawQuad2D(M);

    // HUD View
    const float ui_view_height = currentGraphicsOptions.WindowHeight;
    const float ui_view_width = ui_view_height * _ui_camera2D.GetAspectRatio();
    const auto ui_view_extents = Vector2{ui_view_width, ui_view_height};
    const auto ui_view_half_extents = ui_view_extents * 0.5f;
    const auto ui_cam_pos = ui_view_half_extents;
    g_theRenderer->BeginHUDRender(_ui_camera2D, ui_cam_pos, ui_view_height);

}

void Game::EndFrame() noexcept {
    /* DO NOTHING */
}

void Game::HandlePlayerInput(TimeUtils::FPSeconds deltaSeconds) {
    HandleKeyboardInput(deltaSeconds);
    HandleControllerInput(deltaSeconds);
    HandleMouseInput(deltaSeconds);
}

void Game::HandleKeyboardInput(TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::Esc)) {
        auto& app = ServiceLocator::get<IAppService>();
        app.SetIsQuitting(true);
        return;
    }
}

void Game::HandleControllerInput(TimeUtils::FPSeconds /*deltaSeconds*/) {

}

void Game::HandleMouseInput(TimeUtils::FPSeconds /*deltaSeconds*/) {

}

void Game::HandleDebugInput(TimeUtils::FPSeconds deltaSeconds) {
    HandleDebugKeyboardInput(deltaSeconds);
    HandleDebugMouseInput(deltaSeconds);
}

void Game::HandleDebugKeyboardInput(TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theUISystem->WantsInputKeyboardCapture()) {
        return;
    }
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::F4)) {
        g_theUISystem->ToggleImguiDemoWindow();
    }
}

void Game::HandleDebugMouseInput(TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theUISystem->WantsInputMouseCapture()) {
        return;
    }
}
