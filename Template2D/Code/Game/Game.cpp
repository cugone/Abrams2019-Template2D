#include "Game/Game.hpp"

#include "Game/GameCommon.hpp"
#include "Game/GameConfig.hpp"

void Game::Initialize() {
    g_theRenderer->RegisterMaterialsFromFolder(std::string{ "Data/Materials" });
    g_theRenderer->RegisterFontsFromFolder(std::string{"Data/Fonts"});
}

void Game::BeginFrame() {
    /* DO NOTHING */
}

void Game::Update(TimeUtils::FPSeconds deltaSeconds) {
    g_theRenderer->UpdateGameTime(deltaSeconds);

    Camera2D base_camera = _camera2D;
    HandlePlayerInput(base_camera, deltaSeconds);

    _camera2D.Update(deltaSeconds);
}

void Game::Render() const {

    g_theRenderer->ResetModelViewProjection();
    g_theRenderer->SetRenderTarget();
    g_theRenderer->ClearColor(Rgba::Black);
    g_theRenderer->ClearDepthStencilBuffer();

    g_theRenderer->SetViewportAsPercent();

    const auto view_height = static_cast<float>(g_theRenderer->GetOutput()->GetDimensions().y);
    const auto view_width = view_height * MathUtils::M_16_BY_9_RATIO;
    const auto view_half_extents = Vector2{view_width, view_height} * 0.5f;
    const auto leftBottom = Vector2{-view_half_extents.x, view_half_extents.y};
    const auto rightTop = Vector2{view_half_extents.x, -view_half_extents.y};
    _camera2D.SetupView(leftBottom, rightTop);
    g_theRenderer->SetCamera(_camera2D);

}

void Game::EndFrame() {
    /* DO NOTHING */
}

void Game::HandlePlayerInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds) {
    HandleKeyboardInput(base_camera, deltaSeconds);
    HandleControllerInput(base_camera, deltaSeconds);
    HandleMouseInput(base_camera, deltaSeconds);
}

void Game::HandleKeyboardInput(Camera2D& /*base_camera*/, TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::Esc)) {
        g_theApp->SetIsQuitting(true);
        return;
    }
}

void Game::HandleControllerInput(Camera2D& /*base_camera*/, TimeUtils::FPSeconds /*deltaSeconds*/) {

}

void Game::HandleMouseInput(Camera2D& /*base_camera*/, TimeUtils::FPSeconds /*deltaSeconds*/) {

}

void Game::HandleDebugInput(Camera2D& base_camera, TimeUtils::FPSeconds deltaSeconds) {
    HandleDebugKeyboardInput(base_camera, deltaSeconds);
    HandleDebugMouseInput(base_camera, deltaSeconds);
}

void Game::HandleDebugKeyboardInput(Camera2D& /*base_camera*/, TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theUISystem->GetIO().WantCaptureKeyboard) {
        return;
    }
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::F4)) {
        g_theUISystem->ToggleImguiDemoWindow();
    }
}

void Game::HandleDebugMouseInput(Camera2D& /*base_camera*/, TimeUtils::FPSeconds /*deltaSeconds*/) {
    if(g_theUISystem->GetIO().WantCaptureMouse) {
        return;
    }
}
