#include <ui/SwitcherPopup.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

namespace switcher {

    struct HookPauseLayer : Modify<HookPauseLayer, PauseLayer> {
        void customSetup() {
            PauseLayer::customSetup();

            CCMenu* rightMenu = nullptr;
            auto children = this->getChildren();
            
            if (children) {
                for (int i = 0; i < children->count(); ++i) {
                    auto child = typeinfo_cast<CCMenu*>(children->objectAtIndex(i));
                    if (child && child->getPositionX() > 250.0f) {
                        rightMenu = child;
                        break;
                    }
                }
            }

            if(!rightMenu) {
                log::error("The right menu could not be found natively.");
                return;
            }

            auto button = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_editModeBtn_001.png", 0.675f, [=](CCObject*) {
                switcher::SwitcherPopup::create()->show();
            });

            rightMenu->addChild(button);
            
            rightMenu->updateLayout();
        }
    };
}
