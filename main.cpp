extern "C"{
    #include <stdio.h>
    #include <Window.h>
    #include <Render.h>
    #include <NDI.h>
}

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>
#ifdef WIN32
int WinMain(int, char**) {
#else
int main(int, char**) {
#endif
    NDI_t ndi = APV_Create_NDI();

    window_t window = APV_Create_Window(800,600);

    render_t render = APV_Create_Render("shader.vert", "shader.frag");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window.Window, window.GLCtx);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    SDL_Event e;
    bool bShouldQuit = false;

    uint32_t no_sources;
    const NDIlib_source_t *sources = APV_Find_Sources(ndi, &no_sources);




    while (!bShouldQuit) {
        while (APV_Pool_Events(&e)) {
            ImGui_ImplSDL2_ProcessEvent(&e);
            switch (e.type) {
                case SDL_QUIT:
                    bShouldQuit = true;
                    break;
                default:
                    break;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        {

            ImGui::Begin("NDI Stream Selector");

            for (int n = 0; n < no_sources; n++) {
                NDIlib_source_t source = sources[n];

                if (ImGui::Button(source.p_ndi_name)) {
                    NDIlib_recv_connect(ndi.ndiRecv, &source);
                }
            }

            if (ImGui::Button("Reload")) {
                sources = APV_Find_Sources(ndi, &no_sources);
            }
            ImGui::End();
        }

        ImGui::Render();

        NDIlib_video_frame_v2_t video_frame;
        switch(NDIlib_recv_capture_v2(ndi.ndiRecv, &video_frame, nullptr, nullptr, 0)) {
            case NDIlib_frame_type_video: {
                APV_Update_Texture(render, video_frame.xres, video_frame.yres, video_frame.p_data);
                NDIlib_recv_free_video_v2(ndi.ndiRecv, &video_frame);
            }
            break;
            default:
                break;
        }

        APV_Start_Render();

        APV_Render_Quad(render);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window.Window);
        SDL_UpdateWindowSurface(window.Window);

    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    APV_Destroy_Window(window);
    return 0;
}
