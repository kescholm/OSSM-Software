//
// Created by Andrew Koenig on 2023-10-09.
//

#ifndef OSSM_SOFTWARE_APPSTATESEVENTS_H
#define OSSM_SOFTWARE_APPSTATESEVENTS_H

namespace App {

    enum class States {
        // None must always be defined as the first state.
        NONE,

        // Implement your states here.
        // Just make sure you manage state transitions in "handle event".
        INITIALIZING,
        HOMING,
        MENU,
        SIMPLE_STROKE,
        DEEPTHROAT_REPLAY,
        DEEPTHROAT_SPEED_REPLAY,

        // Finally, here's the size of the current state list.
        NUM_OPTIONS
    };

    enum class Events {
        // None must always be defined as the first event type.
        NONE,

        // Implement your events here.

        // Finally, here's the size of the current state list.
        NUM_OPTIONS
    };
}

#endif  // OSSM_SOFTWARE_APPSTATESEVENTS_H
