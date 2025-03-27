#pragma once

#include <btn_manager/btn_manager.hpp>


namespace Scene {
    class Part {
    public:
        Part();

        virtual void render();
    };


    class Source {
    public:
        bool non_null = false;
        
        Source();
        explicit Source(bool non_null);

        virtual const Source& render();
        virtual void on_btn_action_click();
        virtual void on_btn_action_held_repeat();
        virtual void on_btn_up_click();
        virtual void on_btn_up_held_repeat();
        virtual void on_btn_down_click();
        virtual void on_btn_down_held_repeat();
    };

    class BlankSource : public Source {
    public:
        BlankSource();
        const Source& render() override;
    };

    extern const Source blank_source;


    class Loader {
    public:
        Source& source;
        BtnManager::Button btn_action;
        BtnManager::Button btn_up;
        BtnManager::Button btn_down;
        explicit Loader(Source& source);

        void on_tick();
    };
}