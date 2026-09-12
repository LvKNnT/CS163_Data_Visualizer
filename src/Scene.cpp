#include "Scene.h"
#include "raylib.h"
#include "Properties.h"
#include "RenderUtilities.h"

#include "Visualizer.h"
#include "SLL.h"
#include "HASH.h"
#include "AVL.h"
#include "TRIE.h"

Scene scene;

// Init
Scene::Scene() {
    currentScene = MAIN;
}

Scene::~Scene() {

}

void Scene::Init() {
    modeButton.SetRatio(0.5f, -130.0f, 0.5f, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK,  {255, 255, 255, 100});
    modeButton.SetText("Get started!", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    modeButton.SetSound(Properties::sounds["buttonClick"]);

    backModeButton.SetRatio(0.5f, -130.0f, 10.0f / 12, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK,  {255, 255, 255, 100});
    backModeButton.SetText("Return", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    backModeButton.SetSound(Properties::sounds["buttonClick"]);

    backToolButton.SetRatio(9.0f / 10, -130.0f, 10.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    backToolButton.SetText("Return", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    backToolButton.SetSound(Properties::sounds["buttonClick"]);

    importButton.SetRatio(9.0f / 10, -130.0f, 2.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    importButton.SetText("Import", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    importButton.SetSound(Properties::sounds["buttonClick"]);
    
    exportButton.SetRatio(9.0f / 10, -130.0f, 3.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    exportButton.SetText("Export", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    exportButton.SetSound(Properties::sounds["buttonClick"]);

    clearButton.SetRatio(9.0f / 10, -130.0f, 4.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    clearButton.SetText("Clear", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    clearButton.SetSound(Properties::sounds["buttonClick"]);

    initButton.SetRatio(9.0f / 10, -130.0f, 5.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    initButton.SetText("Init", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    initButton.SetSound(Properties::sounds["buttonClick"]);
    initButton.SetSub();

    addButton.SetRatio(9.0f / 10, -130.0f, 6.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    addButton.SetText("Add", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    addButton.SetSound(Properties::sounds["buttonClick"]);
    addButton.SetSub();

    ultilityButton.SetRatio(9.0f / 10, -130.0f, 7.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    ultilityButton.SetText("None", 45, PINK, Properties::fonts["Rubik-Regular_45"]); // should not be 'none'
    ultilityButton.SetSound(Properties::sounds["buttonClick"]);
    ultilityButton.SetSub();

    deleteButton.SetRatio(9.0f / 10, -130.0f, 8.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    deleteButton.SetText("Delete", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    deleteButton.SetSound(Properties::sounds["buttonClick"]);
    deleteButton.SetSub();

    updateButton.SetRatio(9.0f / 10, -130.0f, 9.0f / 12, -30.0f, 0.0f, 260.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    updateButton.SetText("Update", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    updateButton.SetSound(Properties::sounds["buttonClick"]);
    updateButton.SetSub();

    randomInitButton.SetRatio(9.0f / 10, -250.0f, 5.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    randomInitButton.SetText("rd", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    randomInitButton.SetSound(Properties::sounds["buttonClick"]);

    confirmInitButton.SetRatio(9.0f / 10, -190.0f, 5.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    confirmInitButton.SetText("ok", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    confirmInitButton.SetSound(Properties::sounds["buttonClick"]);

    initText.SetRatio(9.0f / 10, -390.0f, 5.0f / 12, -30.0f, 0.0f, 140.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    initText.SetFont(45, PINK, Properties::fonts["Rubik-Regular_45"]);

    randomAddButton.SetRatio(9.0f / 10, -250.0f, 6.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    randomAddButton.SetText("rd", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    randomAddButton.SetSound(Properties::sounds["buttonClick"]);

    confirmAddButton.SetRatio(9.0f / 10, -190.0f, 6.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    confirmAddButton.SetText("ok", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    confirmAddButton.SetSound(Properties::sounds["buttonClick"]);

    addText.SetRatio(9.0f / 10, -390.0f, 6.0f / 12, -30.0f, 0.0f, 140.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    addText.SetFont(45, PINK, Properties::fonts["Rubik-Regular_45"]);

    randomUltilityButton.SetRatio(9.0f / 10, -250.0f, 7.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    randomUltilityButton.SetText("rd", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    randomUltilityButton.SetSound(Properties::sounds["buttonClick"]);

    confirmUltilityButton.SetRatio(9.0f / 10, -190.0f, 7.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    confirmUltilityButton.SetText("ok", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    confirmUltilityButton.SetSound(Properties::sounds["buttonClick"]);

    ultilityText.SetRatio(9.0f / 10, -390.0f, 7.0f / 12, -30.0f, 0.0f, 140.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    ultilityText.SetFont(45, PINK, Properties::fonts["Rubik-Regular_45"]);
    
    /*
    Closing due to no more demand
    */
    randomDeleteButton.SetRatio(9.0f / 10, -250.0f, 8.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    randomDeleteButton.SetText("rd", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    randomDeleteButton.SetSound(Properties::sounds["buttonClick"]);
    
    confirmDeleteButton.SetRatio(9.0f / 10, -190.0f, 8.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    confirmDeleteButton.SetText("ok", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    confirmDeleteButton.SetSound(Properties::sounds["buttonClick"]);
    
    deleteText.SetRatio(9.0f / 10, -390.0f, 8.0f / 12, -30.0f, 0.0f, 140.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    deleteText.SetFont(45, PINK, Properties::fonts["Rubik-Regular_45"]);
    
    randomUpdateButton.SetRatio(9.0f / 10, -250.0f, 9.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    randomUpdateButton.SetText("rd", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    randomUpdateButton.SetSound(Properties::sounds["buttonClick"]);
    
    confirmUpdateButton.SetRatio(9.0f / 10, -190.0f, 9.0f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    confirmUpdateButton.SetText("ok", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    confirmUpdateButton.SetSound(Properties::sounds["buttonClick"]);
    
    updateText.SetRatio(9.0f / 10, -390.0f, 9.0f / 12, -30.0f, 0.0f, 140.0f, 0.0f, 60.0f, BLANK,  {255, 255, 255, 100});
    updateText.SetFont(45, PINK, Properties::fonts["Rubik-Regular_45"]);

    playButton.SetRatio(0.0f, 0.0f, 11.5f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK, BLANK);
    playButton.SetSound(Properties::sounds["buttonClick"]);

    replayButton.SetRatio(0.0f, 70.0f, 11.5f / 12, -30.0f, 0.0f, 60.0f, 0.0f, 60.0f, BLANK, BLANK);
    replayButton.SetTexture("replay", "_replay");
    replayButton.SetSound(Properties::sounds["buttonClick"]);

    loadingBar.SetRatio(0.0f, 140.0f, 11.5f / 12, -30.0f, 0.0f, 300.0f, 0.0f, 60.f, Color{255, 255, 255, 100}, RAYWHITE, Color{255, 255, 255, 100});
    loadingBar.SetSound(Properties::sounds["buttonClick"]);
    
    speedBar.SetRatio(0.0f, 450.0f, 11.5f / 12, -30.0f, 0.0f, 300.0f, 0.0f, 60.f, Color{255, 255, 255, 100}, RAYWHITE, Color{255, 255, 255, 100});
    speedBar.SetSound(Properties::sounds["buttonClick"]);
    
    SLLButton.SetRatio(1.0f / 3, -200.0f, 0.5f, -35.0f, 0.0f, 400.0f, 0.0f, 70.0f, BLANK, {255, 255, 255, 100});
    SLLButton.SetText("Singly Linked List", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    SLLButton.SetSound(Properties::sounds["buttonClick"]);
    
    HASHButton.SetRatio(2.0f / 3, -130.0f, 0.5f, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK, {255, 255, 255, 100});
    HASHButton.SetText("Hash Table", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    HASHButton.SetSound(Properties::sounds["buttonClick"]);

    AVLButton.SetRatio(1.0f / 3, -130.0f, 7.0f / 12, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK, {255, 255, 255, 100});
    AVLButton.SetText("AVL Tree", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    AVLButton.SetSound(Properties::sounds["buttonClick"]);

    TRIEButton.SetRatio(2.0f / 3, -130.0f, 7.0f / 12, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK, {255, 255, 255, 100});
    TRIEButton.SetText("TRIE", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    TRIEButton.SetSound(Properties::sounds["buttonClick"]);

    MSTButton.SetRatio(1.0f / 3, -130.0f, 8.0f / 12, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK, {255, 255, 255, 100});
    MSTButton.SetText("MST", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    MSTButton.SetSound(Properties::sounds["buttonClick"]);

    DIJKSTRAButton.SetRatio(2.0f / 3, -130.0f, 8.0f / 12, -35.0f, 0.0f, 260.0f, 0.0f, 70.0f, BLANK, {255, 255, 255, 100});
    DIJKSTRAButton.SetText("Dijkstra", 45, PINK, Properties::fonts["Rubik-Regular_45"]);
    DIJKSTRAButton.SetSound(Properties::sounds["buttonClick"]);
}

void Scene::Run() { 
    ClearBackground(RAYWHITE);

    switch (currentScene) {
        case MAIN: {
            MainScene();
        } break;
        case MODE: {
            ModeScene();
        } break;
        case SLL: {
            SLLScene();
        } break;
        case HASH: {
            HASHScene();
        } break;
        case AVL: {
            AVLScene();
        } break;
        case TRIE: {
            TRIEScene();
        } break;    
        case MST: {
            MSTScene();
        } break;
        case DIJKSTRA: {
            DIJKSTRAScene();
        } break;
    }
}

void Scene::BaseScene() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() * 1.0f / 12, (Color){ 255, 109, 194, 255});
    DrawRectangle(0, GetScreenHeight() * 11.0f / 12, GetScreenWidth(), GetScreenHeight() * 1.0f / 12, (Color){ 255, 109, 194, 255});

    DrawTextCenEx(Properties::fonts["Rubik-Regular_45"], "DataChelf by Lam Vinh Khang", int(GetScreenWidth() / 2), int(GetScreenHeight() / 24), 45, 2, RAYWHITE);
}

void Scene::ToolScene() {
    if(IsFileDropped()) {
        FilePathList droppedFiles = LoadDroppedFiles();
        Properties::filePath = droppedFiles.paths[0];
        UnloadDroppedFiles(droppedFiles);

        if(Properties::filePath.find(".txt") == std::string::npos) Properties::filePath = "";
    }

    visualizer.SetArea(0.0f, GetScreenHeight() * 1.0f / 12, GetScreenWidth() * 4.0f / 5, GetScreenHeight() * 10.0f / 12);
    visualizer.Update();
    visualizer.Check();
    visualizer.Draw();
    
    DrawRectangle(GetScreenWidth() * 4 / 5, GetScreenHeight() * 1 / 12, GetScreenWidth() * 1 / 5, GetScreenHeight() * 5 / 6, (Color){ 255, 109, 194, 100});

    importButton.Render();
    exportButton.Render();
    exportButton.Render();
    clearButton.Render();
    initButton.Render();   
    addButton.Render();
    ultilityButton.Render();
    deleteButton.Render();
    updateButton.Render();
    backToolButton.Render();

    if(visualizer.GetIsProgress()) {
        playButton.SetTexture("pause", "_pause");
    }
    else playButton.SetTexture("play", "_play");
    playButton.Render();
    replayButton.Render();
    loadingBar.Render();
    speedBar.Render();

    /*
    if(importButton.Check()) {

    }
    
    if(exportButton.Check()) {

    }
    */
    
    if(initButton.Check()) {
        randomInitButton.Render();
        confirmInitButton.Render();
        initText.Render();
    }
    else initText.SetText("");

    if(addButton.Check()) {
        randomAddButton.Render();
        confirmAddButton.Render();
        addText.Render();
    }
    else addText.SetText("");

    if(ultilityButton.Check()) {
        randomUltilityButton.Render();
        confirmUltilityButton.Render();
        ultilityText.Render();
    }
    else ultilityText.SetText("");

    /*
    Closing due to no more demand
    */
    if(deleteButton.Check()) {
        randomDeleteButton.Render();
        confirmDeleteButton.Render();
        deleteText.Render();
    }
    else deleteText.SetText("");
   
    if(updateButton.Check()) {
        randomUpdateButton.Render();
        confirmUpdateButton.Render();
        updateText.Render();
    }
    else updateText.SetText("");

    if(playButton.Check()) {
        visualizer.SetIsProgress(!visualizer.GetIsProgress());
    }
    if(replayButton.Check()) {
        visualizer.ResetProgess();
    }

    loadingBar.SetProgressRatio(visualizer.GetProgress());
    if(loadingBar.Check()) {
        visualizer.SetProgress(loadingBar.Get());
    }

    speedBar.SetProgressRatio(visualizer.GetDif());
    if(speedBar.Check()) {
        visualizer.SetDif(speedBar.Get());
    }
}

void Scene::MainScene() {
    BaseScene();
    DrawTextCenEx(Properties::fonts["Mondwild_80"], "Data Chelf", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 80, 2, PINK);        
    
    modeButton.Render();
    
    if(modeButton.Check()) {
        currentScene = MODE;
    }
}

void Scene::ModeScene() {
    BaseScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "Choose a data structure to continue", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);    

    backModeButton.Render();
    SLLButton.Render();
    HASHButton.Render();
    AVLButton.Render();
    TRIEButton.Render();
    MSTButton.Render();
    DIJKSTRAButton.Render();
    
    if(backModeButton.Check()) {
        currentScene = MAIN;
    }
    if(SLLButton.Check()) {
        visualizer.SetArrow(true);

        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(true);

        singlylinkedlist.Init(0);
        currentScene = SLL;
    }
    if(HASHButton.Check()) {
        visualizer.SetArrow(true);

        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(true);

        hashtable.Init(0);
        currentScene = HASH;
    }
    if(AVLButton.Check()) {
        visualizer.SetArrow(true);

        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(true);

        avltree.Init(0);
        currentScene = AVL;
    }
    if(TRIEButton.Check()) {
        visualizer.SetArrow(true);

        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(true);

        trietree.Init("");
        currentScene = TRIE;
    }
    if(MSTButton.Check()) {
        currentScene = MST;
    }
    if(DIJKSTRAButton.Check()) {
        currentScene = DIJKSTRA;
    }
}

void Scene::SLLScene() {
    BaseScene();
    ToolScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "SLL", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);

    // re-init
    ultilityButton.SetText("Search", 45, PINK, Properties::fonts["Rubik-Regular_45"]); // should not be 'none'
    
    if(importButton.Check()) {
        if(singlylinkedlist.Import(Properties::filePath)) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);

            visualizer.ResetData();
            visualizer.ResetPoint();
            visualizer.ResetProgess();
            visualizer.SetIsProgress(true);
            singlylinkedlist.Import(Properties::filePath);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(exportButton.Check()) {
        if(singlylinkedlist.Export()) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(clearButton.Check()) {
        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(false);

        singlylinkedlist.Init(0);
    }

    if(initButton.Check()) {
        if(confirmInitButton.Check()) {
            if(initText.State()) {
                std::string text = "YES, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetPoint();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                singlylinkedlist.Init(std::stoi(initText.Get()));
            }
            else {
                std::string text = "NO, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomInitButton.Check()) {
            initText.SetText(std::to_string(rand()%1000));
        }
        if(initText.Check()) {
            initText.Input();
        }
    }
    
    if(addButton.Check()) {
        if(confirmAddButton.Check()) {
            if(addText.State()) {
                std::string text = "YES, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                singlylinkedlist.Add(std::stoi(addText.Get()));
            }
            else {
                std::string text = "NO, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomAddButton.Check()) {
            addText.SetText(std::to_string(rand()%1000));
        }
        if(addText.Check()) {
            addText.Input();
        }
    }

    if(ultilityButton.Check()) {
        if(confirmUltilityButton.Check()) {
            if(ultilityText.State()) {
                std::string text = "YES, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                singlylinkedlist.Search(std::stoi(ultilityText.Get()));
            }
            else {
                std::string text = "NO, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUltilityButton.Check()) {
            ultilityText.SetText(std::to_string(rand()%1000));
        }
        if(ultilityText.Check()) {
            ultilityText.Input();
        }
    }

    /*
    Closing due to no more demand
    */
    if(deleteButton.Check()) {
        if(visualizer.GetValueLastPick() != "") {
            deleteText.SetText(visualizer.GetValueLastPick());
        }

        if(confirmDeleteButton.Check()) {
            if(deleteText.State()) {
                std::string text = "YES, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                singlylinkedlist.Delete(std::stoi(deleteText.Get()));
            }
            else {
                std::string text = "NO, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomDeleteButton.Check()) {
            deleteText.SetText(std::to_string(rand()%1000));
        }
        if(deleteText.Check()) {
            deleteText.Input();
        }
    }
    
    if(updateButton.Check()) {
        if(confirmUpdateButton.Check()) {
            if(updateText.State()) {
                std::string text = "YES, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                singlylinkedlist.Update(visualizer.Check(), std::stoi(updateText.Get()));
            }
            else {
                std::string text = "NO, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUpdateButton.Check()) {
            updateText.SetText(std::to_string(rand()%1000));
        }
        if(updateText.Check()) {
            updateText.Input();
        }
    }
    
    if(backToolButton.Check()) { 
        visualizer.SetArrow(false);

        currentScene = MODE;
    }
}

void Scene::HASHScene() {
    BaseScene();
    ToolScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "HASH", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);

    // re-init
    ultilityButton.SetText("Search", 45, PINK, Properties::fonts["Rubik-Regular_45"]); // should not be 'none'
    
    if(importButton.Check()) {
        if(hashtable.Import(Properties::filePath)) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);

            visualizer.ResetData();
            visualizer.ResetPoint();
            visualizer.ResetProgess();
            visualizer.SetIsProgress(true);
            hashtable.Import(Properties::filePath);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(exportButton.Check()) {
        if(hashtable.Export()) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(clearButton.Check()) {
        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(false);

        hashtable.Init(0);
    }

    if(initButton.Check()) {
        if(confirmInitButton.Check()) {
            if(initText.State()) {
                std::string text = "YES, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetPoint();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                hashtable.Init(std::stoi(initText.Get()));
            }
            else {
                std::string text = "NO, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomInitButton.Check()) {
            initText.SetText(std::to_string(rand()%1000));
        }
        if(initText.Check()) {
            initText.Input();
        }
    }
    
    if(addButton.Check()) {
        if(confirmAddButton.Check()) {
            if(addText.State()) {
                std::string text = "YES, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                hashtable.Add(std::stoi(addText.Get()));
            }
            else {
                std::string text = "NO, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomAddButton.Check()) {
            addText.SetText(std::to_string(rand()%1000));
        }
        if(addText.Check()) {
            addText.Input();
        }
    }

    if(ultilityButton.Check()) {
        if(confirmUltilityButton.Check()) {
            if(ultilityText.State()) {
                std::string text = "YES, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                hashtable.Search(std::stoi(ultilityText.Get()));
            }
            else {
                std::string text = "NO, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUltilityButton.Check()) {
            ultilityText.SetText(std::to_string(rand()%1000));
        }
        if(ultilityText.Check()) {
            ultilityText.Input();
        }
    }

    /*
    Closing due to no more demand
    */
    if(deleteButton.Check()) {
        if(visualizer.GetValueLastPick() != "") {
            deleteText.SetText(visualizer.GetValueLastPick());
        }

        if(confirmDeleteButton.Check()) {
            if(deleteText.State()) {
                std::string text = "YES, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                hashtable.Delete(std::stoi(deleteText.Get()));
            }
            else {
                std::string text = "NO, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomDeleteButton.Check()) {
            deleteText.SetText(std::to_string(rand()%1000));
        }
        if(deleteText.Check()) {
            deleteText.Input();
        }
    }
    
    if(updateButton.Check()) {
        if(confirmUpdateButton.Check()) {
            if(updateText.State()) {
                std::string text = "YES, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                hashtable.Update(visualizer.Check(), std::stoi(updateText.Get()));
            }
            else {
                std::string text = "NO, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUpdateButton.Check()) {
            updateText.SetText(std::to_string(rand()%1000));
        }
        if(updateText.Check()) {
            updateText.Input();
        }
    }
    
    if(backToolButton.Check()) { 
        visualizer.SetArrow(false);

        currentScene = MODE;
    }
}

void Scene::AVLScene() {
    BaseScene();
    ToolScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "AVL", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);

    // re-init
    ultilityButton.SetText("Search", 45, PINK, Properties::fonts["Rubik-Regular_45"]); // should not be 'none'
    
    if(importButton.Check()) {
        if(avltree.Import(Properties::filePath)) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);

            visualizer.ResetData();
            visualizer.ResetPoint();
            visualizer.ResetProgess();
            visualizer.SetIsProgress(true);
            avltree.Import(Properties::filePath);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(exportButton.Check()) {
        if(avltree.Export()) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(clearButton.Check()) {
        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(false);

        avltree.Init(0);
    }

    if(initButton.Check()) {
        if(confirmInitButton.Check()) {
            if(initText.State()) {
                std::string text = "YES, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetPoint();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                avltree.Init(std::stoi(initText.Get()));
            }
            else {
                std::string text = "NO, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomInitButton.Check()) {
            initText.SetText(std::to_string(rand()%1000));
        }
        if(initText.Check()) {
            initText.Input();
        }
    }
    
    if(addButton.Check()) {
        if(confirmAddButton.Check()) {
            if(addText.State()) {
                std::string text = "YES, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                avltree.Add(std::stoi(addText.Get()));
            }
            else {
                std::string text = "NO, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomAddButton.Check()) {
            addText.SetText(std::to_string(rand()%1000));
        }
        if(addText.Check()) {
            addText.Input();
        }
    }

    if(ultilityButton.Check()) {
        if(confirmUltilityButton.Check()) {
            if(ultilityText.State()) {
                std::string text = "YES, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                avltree.Search(std::stoi(ultilityText.Get()));
            }
            else {
                std::string text = "NO, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUltilityButton.Check()) {
            ultilityText.SetText(std::to_string(rand()%1000));
        }
        if(ultilityText.Check()) {
            ultilityText.Input();
        }
    }

    /*
    Closing due to no more demand
    */
    if(deleteButton.Check()) {
        if(visualizer.GetValueLastPick() != "") {
            deleteText.SetText(visualizer.GetValueLastPick());
        }

        if(confirmDeleteButton.Check()) {
            if(deleteText.State()) {
                std::string text = "YES, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                avltree.Delete(std::stoi(deleteText.Get()));
            }
            else {
                std::string text = "NO, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomDeleteButton.Check()) {
            deleteText.SetText(std::to_string(rand()%1000));
        }
        if(deleteText.Check()) {
            deleteText.Input();
        }
    }
    
    if(updateButton.Check()) {
        if(confirmUpdateButton.Check()) {
            if(updateText.State()) {
                std::string text = "YES, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                avltree.Update(visualizer.Check(), std::stoi(updateText.Get()));
            }
            else {
                std::string text = "NO, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUpdateButton.Check()) {
            updateText.SetText(std::to_string(rand()%1000));
        }
        if(updateText.Check()) {
            updateText.Input();
        }
    }
    
    if(backToolButton.Check()) { 
        visualizer.SetArrow(false);

        currentScene = MODE;
    }
}

void Scene::TRIEScene() {
    BaseScene();
    ToolScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "TRIE", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);    
    
    // re-init
    ultilityButton.SetText("Search", 45, PINK, Properties::fonts["Rubik-Regular_45"]); // should not be 'none'
    
    if(importButton.Check()) {
        if(trietree.Import(Properties::filePath)) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);

            visualizer.ResetData();
            visualizer.ResetPoint();
            visualizer.ResetProgess();
            visualizer.SetIsProgress(true);
            trietree.Import(Properties::filePath);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(exportButton.Check()) {
        if(trietree.Export()) {
            std::string text = "YES, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
        else {
            std::string text = "NO, confirm ";
            DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
        }
    }

    if(clearButton.Check()) {
        visualizer.ResetData();
        visualizer.ResetPoint();
        visualizer.ResetProgess();
        visualizer.SetIsProgress(false);

        trietree.Init("");
    }

    if(initButton.Check()) {
        if(confirmInitButton.Check()) {
            if(initText.State()) {
                std::string text = "YES, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetPoint();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                trietree.Init(initText.Get());
            }
            else {
                std::string text = "NO, confirm " + initText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomInitButton.Check()) {
            initText.SetText(std::to_string(rand()%1000));
        }
        if(initText.Check()) {
            initText.Input();
        }
    }
    
    if(addButton.Check()) {
        if(confirmAddButton.Check()) {
            if(addText.State()) {
                std::string text = "YES, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                trietree.Add(addText.Get());
            }
            else {
                std::string text = "NO, confirm " + addText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomAddButton.Check()) {
            addText.SetText(std::to_string(rand()%1000));
        }
        if(addText.Check()) {
            addText.Input();
        }
    }

    if(ultilityButton.Check()) {
        if(confirmUltilityButton.Check()) {
            if(ultilityText.State()) {
                std::string text = "YES, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                trietree.Search(ultilityText.Get());
            }
            else {
                std::string text = "NO, confirm " + ultilityText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUltilityButton.Check()) {
            ultilityText.SetText(std::to_string(rand()%1000));
        }
        if(ultilityText.Check()) {
            ultilityText.Input();
        }
    }

    /*
    Closing due to no more demand
    */
    if(deleteButton.Check()) {
        if(visualizer.GetValueLastPick() != "") {
            deleteText.SetText(visualizer.GetValueLastPick());
        }

        if(confirmDeleteButton.Check()) {
            if(deleteText.State()) {
                std::string text = "YES, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                trietree.Delete(deleteText.Get());
            }
            else {
                std::string text = "NO, confirm " + deleteText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomDeleteButton.Check()) {
            deleteText.SetText(std::to_string(rand()%1000));
        }
        if(deleteText.Check()) {
            deleteText.Input();
        }
    }
    
    if(updateButton.Check()) {
        if(confirmUpdateButton.Check()) {
            if(updateText.State()) {
                std::string text = "YES, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
    
                visualizer.ResetData();
                visualizer.ResetProgess();
                visualizer.SetIsProgress(true);

                trietree.Update(visualizer.Check(), updateText.Get());
            }
            else {
                std::string text = "NO, confirm " + updateText.Get();
                DrawTextCenEx(Properties::fonts["Rubik-Regular_60"], text.c_str(), int(GetScreenWidth() / 2), int(GetScreenHeight() * 2 / 3), 60, 2, PINK);
            }
        }
        if(randomUpdateButton.Check()) {
            updateText.SetText(std::to_string(rand()%1000));
        }
        if(updateText.Check()) {
            updateText.Input();
        }
    }

    if(backToolButton.Check()) {
        currentScene = MODE;
    }
}

void Scene::MSTScene() {
    BaseScene();
    ToolScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "MST", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);    
    
    if(backToolButton.Check()) {
        currentScene = MODE;
    }
}

void Scene::DIJKSTRAScene() {
    BaseScene();
    ToolScene();
    DrawTextCenEx(Properties::fonts["Mondwild_60"], "DIJKSTRA", int(GetScreenWidth() / 2), int(GetScreenHeight() / 3), 60, 2, PINK);    
    
    if(backToolButton.Check()) {
        currentScene = MODE;
    }
}
