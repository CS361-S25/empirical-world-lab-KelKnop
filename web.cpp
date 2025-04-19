#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "World.h"
#include "Org.h"

emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    // Arena dimensions
    const int num_h_boxes = 10;
    const int num_w_boxes = 10;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::Random random{5};      // Random number generator for organism behavior
    OrgWorld world{random};     // World object containing organisms

    emp::web::Canvas canvas{width, height, "canvas"};

public:

    AEAnimator() {
        // Attach the canvas to the webpage, along with control buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        // Resize world (specifying world grid size)
        world.Resize(num_w_boxes, num_h_boxes);

        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);

        // Inject 100 organisms into the world at random positions
        for (int i = 0; i < 100; i++) {
            world.Inject(Organism(&random));   // Inject new organism
        }

        
    }

    void DoFrame() override {
        canvas.Clear();   // Clear the canvas at the beginning of each frame

        // Keep track of which organism we're currently rendering
        int org_num = 0;

        // Update the state of all organisms in the world
        world.Update();

        // Loop through all grid cells (representing the world)
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                // Check if the current grid cell is occupied by an organism
                if (world.IsOccupied(org_num)) {
                    // If occupied, draw a black rectangle to represent an organism
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                } else {
                    // If not occupied, draw a white rectangle (empty space)
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }

                // Move to the next organism (for the next grid cell)
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() {
    animator.Step();
    animator.DoFrame();
}
