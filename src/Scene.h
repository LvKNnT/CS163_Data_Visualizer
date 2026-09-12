#ifndef SCENE_H
#define SCENE_H

#include "Button.h"
#include "Textbox.h"
#include "Slider.h"

class Scene {
public:
    Scene();
    ~Scene();

    void Init();
    void Run();
private:
    enum SCENE {
        MAIN,
        MODE,
        SLL,
        HASH,
        AVL,
        TRIE,
        MST,
        DIJKSTRA
    };
    SCENE currentScene;

    // List of buttons
    Button modeButton;
    Button backModeButton;
    Button backToolButton;

    Button importButton;
    Button exportButton;
    Button clearButton;
    Button initButton;
    Button addButton;
    Button ultilityButton;
    Button deleteButton;
    Button updateButton;

    Button randomInitButton;
    Button confirmInitButton;
    Textbox initText;

    Button randomAddButton;
    Button confirmAddButton;
    Textbox addText;

    Button randomUltilityButton;
    Button confirmUltilityButton;
    Textbox ultilityText;

    /*
    Closing due to no more demand
    */
    Button randomDeleteButton;
    Button confirmDeleteButton;
    Textbox deleteText;
    
    Button randomUpdateButton;
    Button confirmUpdateButton;
    Textbox updateText;
    
    Button playButton;
    Button replayButton;
    Button volumeButton;
    Slider loadingBar;
    Slider speedBar;

    Button SLLButton;
    Button HASHButton;
    Button AVLButton;
    Button TRIEButton;
    Button MSTButton;
    Button DIJKSTRAButton;

    // List of scenes
    void BaseScene();
    void ToolScene();
    void MainScene();
    void ModeScene();
    void SLLScene();
    void HASHScene();
    void AVLScene();
    void TRIEScene();
    void MSTScene();
    void DIJKSTRAScene();
};

extern Scene scene;

#endif // SCENE_H