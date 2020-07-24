#include "Game/Game.hpp"

#include "Game/GameCommon.hpp"
#include "Game/GameConfig.hpp"

void Game::Initialize() {
    g_theRenderer->RegisterMaterialsFromFolder(std::string{ "Data/Materials" });
    g_theRenderer->RegisterFontsFromFolder(std::string{"Data/Fonts"});

    _cameraController = OrthographicCameraController(g_theRenderer, g_theInputSystem);

}

void Game::BeginFrame() {
    /* DO NOTHING */
}

void Game::Update(TimeUtils::FPSeconds deltaSeconds) {
    g_theRenderer->UpdateGameTime(deltaSeconds);

    Camera2D base_camera = _ui_camera2D;
    HandlePlayerInput(deltaSeconds);

    _ui_camera2D.Update(deltaSeconds);
    _cameraController.Update(deltaSeconds);
}

void Game::Render() const {

    g_theRenderer->ResetModelViewProjection();
    g_theRenderer->SetRenderTarget();
    g_theRenderer->ClearColor(Rgba::Black);
    g_theRenderer->ClearDepthStencilBuffer();

    g_theRenderer->SetViewportAsPercent();

    // HUD View
    const auto view_height = currentGraphicsOptions.WindowHeight;
    const auto view_width = view_height * MathUtils::M_16_BY_9_RATIO;
    const auto view_half_extents = Vector2{view_width, view_height} * 0.5f;
    const auto leftBottom = Vector2{-view_half_extents.x, view_half_extents.y};
    const auto rightTop = Vector2{view_half_extents.x, -view_half_extents.y};
    _ui_camera2D.SetupView(leftBottom, rightTop);
    g_theRenderer->SetCamera(_ui_camera2D);

}

void Game::EndFrame() {
    /* DO NOTHING */
}

void Game::HandlePlayerInput(TimeUtils::FPSeconds deltaSeconds) {
    HandleKeyboardInput(deltaSeconds);
    HandleControllerInput(deltaSeconds);
    HandleMouseInput(deltaSeconds);
}

void Game::HandleKeyboardInput(TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::Esc)) {
        g_theApp->SetIsQuitting(true);
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
    if(g_theUISystem->GetIO().WantCaptureKeyboard) {
        return;
    }
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::F4)) {
        g_theUISystem->ToggleImguiDemoWindow();
    }
}

void Game::HandleDebugMouseInput(TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theUISystem->GetIO().WantCaptureMouse) {
        return;
    }
}
