#include "SDL3/SDL_render.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_opengl3.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <algorithm>
#include <cmath>
#include <print>
#include <stdio.h>
#include <string>
#include <vector>

void set_erarnitox_style() {
    ImVec4* colors = ImGui::GetStyle().Colors;

    // Convert brand colors to ImVec4
    const ImVec4 main_bg(0.11f, 0.114f, 0.133f, 1.00f);        // #1C1D22
    const ImVec4 sec_bg(0.192f, 0.231f, 0.267f, 1.00f);        // #313B44
    const ImVec4 highlight(1.00f, 0.184f, 0.463f, 1.00f);      // #ff2f76
    const ImVec4 form_bg(0.745f, 0.314f, 0.459f, 1.00f);       // #be5075
    const ImVec4 main_text(0.667f, 0.671f, 0.678f, 1.00f);     // #AAABAD
    const ImVec4 sec_text(0.365f, 0.486f, 0.514f, 1.00f);      // #5D7C83
    const ImVec4 white(0.988f, 0.992f, 1.00f, 1.00f);          // #fcfdff

    // Core colors
    colors[ImGuiCol_Text]                   = main_text;
    colors[ImGuiCol_TextDisabled]           = sec_text;
    colors[ImGuiCol_WindowBg]               = main_bg;
    colors[ImGuiCol_ChildBg]                = main_bg;
    colors[ImGuiCol_PopupBg]                = sec_bg;
    colors[ImGuiCol_Border]                 = sec_text;
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg]                = sec_bg;
    colors[ImGuiCol_FrameBgHovered]         = highlight;
    colors[ImGuiCol_FrameBgActive]          = form_bg;

    // Interactive elements
    colors[ImGuiCol_TitleBg]                = sec_bg;
    colors[ImGuiCol_TitleBgActive]          = form_bg;
    colors[ImGuiCol_TitleBgCollapsed]       = sec_bg;
    colors[ImGuiCol_MenuBarBg]              = sec_bg;
    colors[ImGuiCol_ScrollbarBg]            = sec_bg;
    colors[ImGuiCol_ScrollbarGrab]          = form_bg;
    colors[ImGuiCol_ScrollbarGrabHovered]   = highlight;
    colors[ImGuiCol_ScrollbarGrabActive]    = highlight;
    colors[ImGuiCol_CheckMark]              = white;
    colors[ImGuiCol_SliderGrab]             = form_bg;
    colors[ImGuiCol_SliderGrabActive]       = highlight;
    colors[ImGuiCol_Button]                 = form_bg;
    colors[ImGuiCol_ButtonHovered]          = highlight;
    colors[ImGuiCol_ButtonActive]           = form_bg;
    colors[ImGuiCol_Header]                 = form_bg;
    colors[ImGuiCol_HeaderHovered]          = highlight;
    colors[ImGuiCol_HeaderActive]           = form_bg;

    // Secondary UI elements
    colors[ImGuiCol_Separator]              = sec_text;
    colors[ImGuiCol_SeparatorHovered]       = highlight;
    colors[ImGuiCol_SeparatorActive]        = form_bg;
    colors[ImGuiCol_ResizeGrip]             = sec_text;
    colors[ImGuiCol_ResizeGripHovered]      = highlight;
    colors[ImGuiCol_ResizeGripActive]       = form_bg;
    colors[ImGuiCol_Tab]                    = sec_bg;
    colors[ImGuiCol_TabHovered]             = highlight;
    colors[ImGuiCol_TabActive]              = form_bg;
    colors[ImGuiCol_TabUnfocused]           = sec_bg;
    colors[ImGuiCol_TabUnfocusedActive]     = form_bg;

    // Special purpose
    colors[ImGuiCol_TextSelectedBg]         = highlight;
    colors[ImGuiCol_DragDropTarget]         = highlight;
    colors[ImGuiCol_NavHighlight]           = highlight;

    // Style adjustments
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding     = ImVec2(12.00f, 12.00f);
    style.FramePadding      = ImVec2(8.00f, 4.00f);
    style.CellPadding       = ImVec2(6.00f, 6.00f);
    style.ItemSpacing       = ImVec2(8.00f, 6.00f);
    style.ItemInnerSpacing  = ImVec2(6.00f, 6.00f);
    style.IndentSpacing     = 25;
    style.ScrollbarSize     = 16;
    style.GrabMinSize       = 12;

    // Border sizes
    style.WindowBorderSize  = 0.8f;
    style.ChildBorderSize   = 0.8f;
    style.PopupBorderSize   = 0.8f;
    style.FrameBorderSize   = 0.8f;
    style.TabBorderSize     = 0.8f;

    // Rounding
    style.WindowRounding    = 4.0f;
    style.ChildRounding     = 4.0f;
    style.FrameRounding     = 2.0f;
    style.PopupRounding     = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 2.0f;
    style.TabRounding       = 4.0f;
}

enum QuestState {
    QUEST_NOT_STARTED,
    QUEST_IN_PROGRESS,
    QUEST_COMPLETED
};

struct Quest {
    int id;
    std::string title;
    std::string description;
    QuestState state;
    std::vector<std::string> objectives;
    std::string category;
};

struct AppState {
    std::vector<Quest> quests;
    char newQuestTitle[256] = "";
    char newQuestDesc[1024] = "";
    char newObjectiveText[256] = "";
    std::vector<std::string> newQuestObjectives;
    int selectedQuest = -1;
    bool showCreationWindow = false;
    int nextQuestId = 1;
};

void ShowQuestCreationWindow(AppState& state) {
    if (state.showCreationWindow) {
        ImGui::OpenPopup("Create New Quest");
        if (ImGui::BeginPopupModal("Create New Quest", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            // Title input
            ImGui::InputText("Title", state.newQuestTitle, IM_ARRAYSIZE(state.newQuestTitle));
            
            // Description input
            ImGui::InputTextMultiline("Description", state.newQuestDesc, 
                                    IM_ARRAYSIZE(state.newQuestDesc), 
                                    ImVec2(300, 100));
            
            // Objectives management
            ImGui::SeparatorText("Objectives");
            for (size_t i = 0; i < state.newQuestObjectives.size(); i++) {
                ImGui::PushID(static_cast<int>(i));
                /*
                if (ImGui::InputText("##obj", &state.newQuestObjectives[i], 128)) {
                    // Handle objective text edit
                }*/
                ImGui::SameLine();
                if (ImGui::Button("X")) {
                    state.newQuestObjectives.erase(state.newQuestObjectives.begin() + (int)i);
                }
                ImGui::PopID();
            }
            
            // Add new objective
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##newobj", state.newObjectiveText, IM_ARRAYSIZE(state.newObjectiveText));
            ImGui::SameLine();
            if (ImGui::Button("Add Objective")) {
                if (strlen(state.newObjectiveText) > 0) {
                    state.newQuestObjectives.emplace_back(state.newObjectiveText);
                    memset(state.newObjectiveText, 0, sizeof(state.newObjectiveText));
                }
            }

            // Category selection
            static const char* categories[] = { "Main Quest", "Side Quest", "Faction Quest", "Miscellaneous" };
            static int currentCategory = 0;
            ImGui::Combo("Category", &currentCategory, categories, IM_ARRAYSIZE(categories));

            // Control buttons
            if (ImGui::Button("Create")) {
                // Create new quest
                Quest newQuest{
                    state.nextQuestId++,
                    state.newQuestTitle,
                    state.newQuestDesc,
                    QUEST_NOT_STARTED,
                    state.newQuestObjectives,
                    categories[currentCategory]
                };
                
                state.quests.push_back(newQuest);
                
                // Reset creation fields
                memset(state.newQuestTitle, 0, sizeof(state.newQuestTitle));
                memset(state.newQuestDesc, 0, sizeof(state.newQuestDesc));
                state.newQuestObjectives.clear();
                state.showCreationWindow = false;
                ImGui::CloseCurrentPopup();
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                state.showCreationWindow = false;
                ImGui::CloseCurrentPopup();
            }
            
            ImGui::EndPopup();
        }
    }
}

void ShowQuestTracker(AppState& state) {
    // Create quest button
    if (ImGui::Button("+ New Quest")) {
        state.showCreationWindow = true;
    }
    
    // Quest list
    ImGui::Separator();
    for (auto& quest : state.quests) {
        ImGui::PushID(quest.id);
        
        // Quest header
        ImGui::PushStyleColor(ImGuiCol_Header, 
            quest.state == QUEST_COMPLETED ? ImVec4(0.2f, 0.6f, 0.2f, 0.7f) :
            quest.state == QUEST_IN_PROGRESS ? ImVec4(0.2f, 0.4f, 0.8f, 0.7f) :
            ImVec4(0.5f, 0.5f, 0.5f, 0.7f));
        
        if (ImGui::CollapsingHeader(quest.title.c_str())) {
            // Quest details
            ImGui::Indent();
            ImGui::TextWrapped("Description: %s", quest.description.c_str());
            ImGui::Text("Category: %s", quest.category.c_str());
            
            // Objectives
            ImGui::SeparatorText("Objectives");
            for (const auto& objective : quest.objectives) {
                ImGui::BulletText("%s", objective.c_str());
            }
            
            // State management
            ImGui::Separator();
            if (ImGui::Button(quest.state == QUEST_COMPLETED ? "Completed!" : "Mark Complete")) {
                quest.state = quest.state == QUEST_COMPLETED ? QUEST_NOT_STARTED : QUEST_COMPLETED;
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Delete")) {
                state.quests.erase(
                    std::remove_if(state.quests.begin(), state.quests.end(),
                        [&](const Quest& q) { return q.id == quest.id; }),
                    state.quests.end());
                ImGui::PopStyleColor();
                ImGui::PopID();
                break;
            }
            
            ImGui::Unindent();
        }
        
        ImGui::PopStyleColor();
        ImGui::PopID();
    }
}

int main()
{
    // Setup SDL
    if (not SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return -1;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create window with graphics context
    SDL_Window* window = SDL_CreateWindow("Erarnitox's Quest Tracker", 800, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImFont* erarnitox_font = io.Fonts->AddFontFromFileTTF("../res/LeroyLettering.ttf", 20);
    
    set_erarnitox_style();

    /*
    bool is_dragging = false;
    int x, y;
    ImVec2 drag_start_pos;
    */
    
    AppState appState;

    // Main loop
    bool done = false;
    while (!done) {
        // Poll and handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::PushFont(erarnitox_font);

        // Create borderless window that fills the screen
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Erarnitox's Quest Tracker", nullptr, 
            ImGuiWindowFlags_NoDecoration | 
            ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoSavedSettings);

        /* Draging doesn't work properly for a "custom boarderless window"
        // Custom title bar for dragging
        ImGui::BeginChild("TitleBar", ImVec2(0, 40));
        {
            // Invisible button for dragging
            ImGui::InvisibleButton("##DragZone", ImVec2(-1, 40));

            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                const ImVec2 mouse_pos = ImGui::GetMousePos();
                
                if (!is_dragging) {
                    // Store initial positions when dragging starts
                    SDL_GetWindowPosition(window, &x, &y);
                    drag_start_pos = mouse_pos; // Store the mouse position at drag start
                    is_dragging = true;
                }

                // Calculate delta movement
                const ImVec2 delta = ImVec2(
                    mouse_pos.x - drag_start_pos.x,
                    mouse_pos.y - drag_start_pos.y
                );

                // Apply movement directly
                SDL_SetWindowPosition(window, 
                    x + static_cast<int>(delta.x), 
                    y + static_cast<int>(delta.y));
            } else {
                is_dragging = false;
            }

            // Custom title bar content
            ImGui::SetCursorPos(ImVec2(20, 10));
            ImGui::Text("Erarnitox's Quest Tracker");
        }
        ImGui::EndChild();
        */

        // Main content area
        ImGui::BeginChild("Content", ImVec2(0, 0), true);
        {
            ShowQuestCreationWindow(appState);
            ShowQuestTracker(appState);
        }

        ImGui::EndChild();

        ImGui::End();

        ImGui::PopFont();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}