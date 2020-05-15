#include "Game/Game.hpp"

#include "Game/GameCommon.hpp"
#include "Game/GameConfig.hpp"

Game::~Game() noexcept {
    UnRegisterCommands();
}

void Game::Initialize() {
    _consoleCommands = Console::CommandList(g_theConsole);
    RegisterCommands();
    g_theRenderer->RegisterMaterialsFromFolder(std::string{ "Data/Materials" });
    g_theRenderer->RegisterFontsFromFolder(std::string{"Data/Fonts"});
}

void Game::RegisterCommands() {
    {
        Console::Command echo{};
        echo.command_name = "echo";
        echo.help_text_short = "Echoes the command arguments";
        echo.help_text_long = "echo [args]";
        _consoleCommands.AddCommand(echo);
    }
    g_theConsole->PushCommandList(_consoleCommands);
}

void Game::UnRegisterCommands() {
    g_theConsole->PopCommandList(_consoleCommands);
}

void Game::BeginFrame() {
    /* DO NOTHING */
}

void Game::Update(TimeUtils::FPSeconds deltaSeconds) {
    g_theRenderer->UpdateGameTime(deltaSeconds);
    HandlePlayerInput(_ui_camera);
}

void Game::Render() const {

    g_theRenderer->ResetModelViewProjection();
    g_theRenderer->SetRenderTarget();
    g_theRenderer->ClearColor(Rgba::Black);
    g_theRenderer->ClearDepthStencilBuffer();

    g_theRenderer->SetViewportAsPercent();

    g_theRenderer->SetMaterial(g_theRenderer->GetMaterial("__2D"));
    g_theRenderer->DrawQuad2D(Vector2::ZERO, Vector2::ONE * 1.0f, Rgba::Red);

}

void Game::EndFrame() {
    /* DO NOTHING */
}

void Game::HandlePlayerInput(Camera2D& base_camera) {
    HandleKeyboardInput(base_camera);
    HandleMouseInput(base_camera);
}

void Game::HandleKeyboardInput(Camera2D& /*base_camera*/) {
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::Esc)) {
        g_theApp->SetIsQuitting(true);
    }
}

void Game::HandleMouseInput(Camera2D& /*base_camera*/) {
    /* DO NOTHING */
}

void Game::HandleDebugInput(Camera2D& base_camera) {
    HandleDebugKeyboardInput(base_camera);
    HandleDebugMouseInput(base_camera);
}

void Game::HandleDebugKeyboardInput(Camera2D& /*base_camera*/) {
    if(g_theUISystem->GetIO().WantCaptureKeyboard) {
        return;
    }
    if(g_theInputSystem->WasKeyJustPressed(KeyCode::F4)) {
        g_theUISystem->ToggleImguiDemoWindow();
    }
}

void Game::HandleDebugMouseInput(Camera2D& /*base_camera*/) {
    if(g_theUISystem->GetIO().WantCaptureMouse) {
        return;
    }
}
